#ifndef DRIVER_7SEGMENT_H
#define DRIVER_7SEGMENT_H

#include <Wire.h>
#include <Arduino.h>

class Driver_7Segment
{

    public:

        Driver_7Segment();
        void begin();
        void setBrightness(uint8_t brightness);
        void clear();
        void displayOn();
        void displayOff();
        void print(int number, uint8_t digit);
        void print(char character, uint8_t digit);
        void print(const char* str);
        void setSegments(uint8_t digit, uint8_t value);
        void turnOnSegment(uint8_t digit, uint8_t segment);
        void turnOffSegment(uint8_t digit, uint8_t segment);

    private:

        uint8_t _address;
        uint8_t _displayBuffer[8];
        void _writeDisplay();
        uint8_t _charToSegment(char c);

};

#endif