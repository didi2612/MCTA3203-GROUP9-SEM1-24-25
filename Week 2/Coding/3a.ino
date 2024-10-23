// Pin definitions
const int potPin = A0; 
const int ledPin = 9;   

void setup() {
  
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  
  int potValue = analogRead(potPin);
  Serial.println(potValue);
  int pwmValue = map(potValue, 0, 1023, 255, 0);
  analogWrite(ledPin, pwmValue);
   delay(10);
}