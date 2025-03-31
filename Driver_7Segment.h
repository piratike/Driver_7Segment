#ifndef DRIVER_7SEGMENT_H
#define DRIVER_7SEGMENT_H

#include <Wire.h>

/**
 * @class Driver_7Segment
 * @brief A driver for controlling a 7-segment display using the HT16K33 controller.
 */
class Driver_7Segment
{

    public:
        /**
         * @brief Constructor for the 7-segment driver.
         */
        Driver_7Segment();

        /**
         * @brief Initializes the HT16K33 display.
         * @return True if a valid I2C address is found, false otherwise.
         */
        bool begin();

        /**
         * @brief Sets the display brightness.
         * @param brightness Value from 0 (dim) to 15 (bright).
         */
        void setBrightness(uint8_t brightness);

        /**
         * @brief Clears the display (turns off all segments).
         */
        void clear();

        /**
         * @brief Turns on the display.
         */
        void displayOn();

        /**
         * @brief Turns off the display.
         */
        void displayOff();

        /**
         * @brief Displays a single digit number at a specific position.
         * @param number The number (0-9) to display.
         * @param digit The digit position (0-3 for a 4-digit display).
         */
        void print(int number, uint8_t digit);

        /**
         * @brief Displays a character at a specific position.
         * @param character The character to display.
         * @param digit The digit position (0-3 for a 4-digit display).
         */
        void print(char character, uint8_t digit);

        /**
         * @brief Displays a string on the 7-segment display (up to 4 characters).
         * @param str The null-terminated string to display.
         */
        void print(const char* str);

        /**
         * @brief Sets the segment data for a specific digit.
         * @param digit The digit position (0-3).
         * @param value The segment bitmask (each bit represents a segment).
         */
        void setSegments(uint8_t digit, uint8_t value);

        /**
         * @brief Turns on a specific segment in a digit.
         * @param digit The digit position (0-3).
         * @param segment The segment index (0-7).
         */
        void turnOnSegment(uint8_t digit, uint8_t segment);

        /**
         * @brief Turns off a specific segment in a digit.
         * @param digit The digit position (0-3).
         * @param segment The segment index (0-7).
         */
        void turnOffSegment(uint8_t digit, uint8_t segment);

    private:

        uint8_t _address;           // I2C address of the HT16K33
        uint8_t _displayBuffer[8];  // Buffer storing display data

        /**
         * @brief Writes the display buffer to the HT16K33.
         */
        void _writeDisplay();

        /**
         * @brief Converts a character into its 7-segment representation.
         * @param c The character to convert.
         * @return The corresponding segment bitmask.
         */
        uint8_t _charToSegment(char c);

};

#endif