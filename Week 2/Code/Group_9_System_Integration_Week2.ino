#define BUTTON_PIN 10

// Define segment pins
const int segmentPins[7] = {2, 3, 4, 5, 6, 7, 8};

// Segment patterns for numbers 0-9
const int segmentPatterns[10][7] = {
    {0, 0, 0, 0, 0, 0, 1}, // Display number 0
    {1, 0, 0, 1, 1, 1, 1}, // Display number 1
    {0, 0, 1, 0, 0, 1, 0}, // Display number 2
    {0, 0, 0, 0, 1, 1, 0}, // Display number 3
    {1, 0, 0, 1, 1, 0, 0}, // Display number 4
    {0, 1, 0, 0, 1, 0, 0}, // Display number 5
    {0, 1, 0, 0, 0, 0, 0}, // Display number 6
    {0, 0, 0, 1, 1, 1, 1}, // Display number 7
    {0, 0, 0, 0, 0, 0, 0}, // Display number 8
    {0, 0, 0, 0, 1, 0, 0}, // Display number 9
};

int currentNumber = 0; // start dengan 0

void setup() {
    // Set up segment pins as output
    for (int i = 0; i < 7; i++) {
        pinMode(segmentPins[i], OUTPUT);
    }

    // Set up button pin
    pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void loop() {
    displayNumber(currentNumber); 
    
    if (digitalRead(BUTTON_PIN) == LOW) {
        while (digitalRead(BUTTON_PIN) == LOW) {
           
        }
        incrementNumber(); 
    }

    delay(100); 
}


void displayNumber(int number) {
    
    if (number < 0) number = 0;
    if (number > 9) number = 9;

    for (int j = 0; j < 7; j++) {
        digitalWrite(segmentPins[j], segmentPatterns[number][j]);
    }
}


void incrementNumber() {
    currentNumber++; 
    if (currentNumber == 10) {
        currentNumber = 0;
    }
}
