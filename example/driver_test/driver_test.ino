#include <Wire.h>
#include "Driver_7Segment.h"

Driver_7Segment display;

void setup() {
    Serial.begin(9600);
    
    if (!display.begin()) {
        Serial.println("HT16K33 not found!");
        while (1);
    }
    
    Serial.println("HT16K33 initialized successfully!");
    display.clear();
    display.setBrightness(10);
}

void loop() {
    // Show a number
    display.print(4, 0);
    display.print(2, 1);
    display.print(3, 2);
    display.print(1, 3);
    delay(2000);
    
    // Show characters
    display.print('A', 0);
    display.print('b', 1);
    display.print('C', 2);
    display.print('d', 3);
    delay(2000);
    
    // Show a word
    display.print("Test");
    delay(2000);
    
    // Turn on and off some individual segments
    display.clear();
    display.turnOnSegment(0, 1);
    display.turnOnSegment(1, 3);
    delay(2000);
    
    display.turnOffSegment(0, 1);
    display.turnOffSegment(1, 3);
    delay(2000);
}
