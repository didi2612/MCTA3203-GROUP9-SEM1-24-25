#include<Servo.h>


Servo servo1;
const int servoPin = 9;
void setup() {
  int angle;
  servo1.attach(servoPin);
  Serial.begin(9600);
}

void loop() {
  if(Serial.available()>0){
    int angle = Serial.parseInt();
    servo1.write(angle);
    Serial.println(angle);
  }
  delay(50);
  }