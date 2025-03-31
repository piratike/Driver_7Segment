#include "Driver_7Segment.h"

Driver_7Segment::Driver_7Segment() : _address(0x70)
{
}

void Driver_7Segment::begin()
{

  Wire.begin();

  for(uint8_t addr = 0x70 ; addr <= 0x77 ; addr++)
  {

    Wire.beginTransmission(addr);
    if(Wire.endTransmission() == 0)
    {

      _address = addr;
      break;

    }

  }

  Wire.beginTransmission(_address);
  Wire.write(0x21);
  Wire.endTransmission();

  displayOn();

}

void Driver_7Segment::setBrightness(uint8_t brightness)
{

  if(brightness > 15) brightness = 15;
  Wire.beginTransmission(_address);
  Wire.write(0xE0 | brightness);
  Wirte.endTransmission();

}

void Driver_7Segment::clear()
{}

void Driver_7Segment::displayOn()
{

  Wire.beginTransmission(_address);
  Wire.write(0x81);
  Wire.endTransmission();

}

void Driver_7Segment::displayOff()
{

  Wire.beginTransmission(_address);
  Wire.write(0x80);
  Wire.endTransmission();

}

void Driver_7Segment::print(int number, uint8_t digit)
{}

void Driver_7Segment::print(char character, uint8_t digit)
{}

void Driver_7Segment::print(const char* str)
{}

void Driver_7Segment::setSegments(uint8_t digit, uint8_t value)
{}

void Driver_7Segment::turnOnSegment(uint8_t digit, uint8_t segment)
{}

void Driver_7Segment::turnOffSegment(uint8_t digit, uint8_t segment)
{}

void Driver_7Segment::_writeDisplay()
{}

uint8_t Driver_7Segment::_charToSegment(char c)
{}