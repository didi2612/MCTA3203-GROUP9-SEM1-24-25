#include <Servo.h>

Servo myServo;  // Create a Servo object

int ledPin7 = 7;  // LED on pin 7
int ledPin8 = 8;  // LED on pin 8

void setup() {
  pinMode(ledPin7, INPUT);  // Set LED pins as inputs
  pinMode(ledPin8, INPUT);

  myServo.attach(9);  // Attach the servo to pin 9 (you can change it if needed)
}

void loop() {
  unsigned long startTime = millis();  // Record the start time

  while (millis() - startTime < 4000) {  // Loop for 4 seconds
    int state7 = digitalRead(ledPin7);  // Read state of LED at pin 7
    int state8 = digitalRead(ledPin8);  // Read state of LED at pin 8

    if (state7 == HIGH) {
      myServo.write(0);  // Move the servo to 0° if LED 7 is HIGH
    } else if (state8 == HIGH) {
      myServo.write(90);  // Move the servo to 90° if LED 8 is HIGH
    }

    delay(500);  // Delay for 500ms to ensure smooth servo movement
  }

  // Reset servo back to 0° after 4 seconds
  myServo.write(0);
  delay(1000);  // Wait for a second before repeating
}
