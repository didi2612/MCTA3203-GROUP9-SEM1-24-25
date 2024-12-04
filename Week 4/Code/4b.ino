#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
#include <ArduinoJson.h>
#include <EEPROM.h>

#define RST_PIN 9
#define SS_PIN 10
#define GREEN_LED 7
#define RED_LED 8
#define SERVO_PIN 6

MFRC522 mfrc522(SS_PIN, RST_PIN);
Servo myServo;

const int bufferSize = 512;
String jsonData = R"({
  "uids": [
    "E2801105200072DAF3A70ACE",
    "123456789ABCDEF012345678"
  ],
  "servo_position": {
    "recognized": 90,
    "unrecognized": 0
  }
})";

DynamicJsonDocument doc(bufferSize);


const int eepromStartAddress = 0;


String byteToHexString(byte *buffer, byte bufferSize) {
  String result = "";
  for (byte i = 0; i < bufferSize; i++) {
    if (buffer[i] < 0x10) result += "0";
    result += String(buffer[i], HEX);
  }
  result.toUpperCase();
  return result;
}


bool isRecognizedUID(String uid) {
  JsonArray uids = doc["uids"].as<JsonArray>();
  for (String storedUID : uids) {
    if (uid == storedUID) return true;
  }
  return false;
}


void saveToEEPROM() {
  String jsonString;
  serializeJson(doc, jsonString);

  for (unsigned int i = 0; i < jsonString.length(); i++) {
    EEPROM.write(eepromStartAddress + i, jsonString[i]);
  }
  EEPROM.write(eepromStartAddress + jsonString.length(), '\0'); 
}

void loadFromEEPROM() {
  char jsonBuffer[bufferSize];
  int i = 0;
  char ch;

  
  while ((ch = EEPROM.read(eepromStartAddress + i)) != '\0' && i < bufferSize - 1) {
    jsonBuffer[i++] = ch;
  }
  jsonBuffer[i] = '\0'; 

  
  DeserializationError error = deserializeJson(doc, jsonBuffer);
  if (error) {
    
    Serial.println("Failed to load JSON from EEPROM. Using default.");
    Serial.print("Error: ");
    Serial.println(error.c_str());

    deserializeJson(doc, jsonData); 
    saveToEEPROM();                
    Serial.println("Default JSON saved to EEPROM.");
  } else {
    Serial.println("JSON successfully loaded from EEPROM.");
  }
}


// Register a new UID
void registerUID(String uid) {
  JsonArray uids = doc["uids"].as<JsonArray>();
  uids.add(uid);
  saveToEEPROM();
  Serial.println("New UID registered: " + uid);
}

void setServoAngle(int angle) {
  myServo.write(angle);
  delay(500);
}

void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  myServo.attach(SERVO_PIN);

  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);

  loadFromEEPROM(); 

  Serial.println("Ready to scan RFID cards.");
}

void loop() {
  
  if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  
  String uid = byteToHexString(mfrc522.uid.uidByte, mfrc522.uid.size);
  Serial.println("Scanned UID: " + uid);

  
  if (isRecognizedUID(uid)) {
    
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(RED_LED, LOW);
    int angle = doc["servo_position"]["recognized"];
    setServoAngle(angle);
    Serial.println("UID recognized. Servo set to angle: " + String(angle));
  } else {
    
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED, HIGH);
    int angle = doc["servo_position"]["unrecognized"];
    setServoAngle(angle);
    Serial.println("UID unrecognized. Servo set to angle: " + String(angle));

    
    registerUID(uid);
    Serial.println("UID has been registered automatically.");
  }

  
  delay(2000);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(RED_LED, LOW);
}
