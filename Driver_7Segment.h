#ifndef DRIVER_7SEGMENT_H
#define DRIVER_7SEGMENT_H

#include <Wire.h>

class Driver_7Segment
{

    public:

        Driver_7Segment(uint8_t address = 0x70);
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

        uint8_t address;
        uint8_t displayBuffer[8];
        void writeDisplay();
        uint8_t charToSegment(char c);

};

#endif