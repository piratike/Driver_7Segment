# Driver 7-Segment Library

A simple and easy-to-use library to control 7-segment displays using the HT16K33 I2C driver.

## Features
- Supports up to 4-digit 7-segment displays driven by HT16K33.
- Controls display brightness (0 to 15).
- Displays numbers, characters, and custom segments.
- I2C communication for easy wiring and control.

## Installation

1. Download the repository or use the Arduino Library Manager to install it.
2. Include the library in your sketch:
   ```cpp
   #include <Driver_7Segment.h>
   ```

## Usage

### Initialize the Display
   ```cpp
   Driver_7Segment display;
   if (!display.begin()) {
       Serial.println("HT16K33 not found!");
       while (1);  // Stop execution if the display is not found.
   }
   ```

### Set Brightness
   ```cpp
   display.setBrightness(10);  // Set brightness level (0-15)
   ```

### Clear the Display
   ```cpp
   display.clear();  // Clear the display buffer
   ```

### Display Numbers
   ```cpp
   display.print(4, 0);  // Display 4 on the first digit
   display.print(5, 1);  // Display 5 on the second digit
   display.print(9, 2);  // Display 9 on the third digit
   display.print(2, 3);  // Display 2 on the fourth digit
   ```

### Display Characters
   ```cpp
   display.print('A', 0);  // Display 'A' on the first digit
   display.print('b', 1);  // Display 'b' on the second digit
   display.print('C', 2);  // Display 'C' on the third digit
   display.print('d', 3);  // Display 'd' on the fourth digit
   ```

### Display a String
   ```cpp
   display.print("Test");  // Display 'T', 'e', 's', 't'
   ```

### Turn On and Off Specific Segments
   ```cpp
   display.turnOnSegment(0, 1);  // Turn on segment 1 of the first digit
   display.turnOffSegment(0, 1);  // Turn off segment 1 of the first digit
   ```

## Example
   ```cpp
   #include <Wire.h>
   #include <Driver_7Segment.h>

   Driver_7Segment display;

   void setup() {
       Serial.begin(9600);
       if (!display.begin()) {
           Serial.println("HT16K33 not found!");
           while (1); // Stop execution if the display is not found.
       }
       display.setBrightness(10);
   }

   void loop() {
       display.print(4, 0);
       display.print(2, 1);
       display.print(3, 2);
       display.print(1, 3);
       delay(2000);
       display.print('A', 0);
       display.print('b', 1);
       display.print('C', 2);
       display.print('d', 3);
       delay(2000);
   }
   ```
