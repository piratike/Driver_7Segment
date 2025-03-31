#include "Driver_7Segment.h"

Driver_7Segment::Driver_7Segment() : _address(0x70)
{
}

bool Driver_7Segment::begin()
{

  Wire.begin();
  bool device_found = false;

  for(uint8_t addr = 0x70 ; addr <= 0x77 ; addr++)
  {

    Wire.beginTransmission(addr);
    if(Wire.endTransmission() == 0)
    {

      Wire.beginTransmission(addr);
      Wire.write(0x21);
      if(Wire.endTransmission() == 0)
      {

        _address = addr;
        device_found = true;
        break;

      }

    }

  }

  if(!device_found) return false;

  displayOn();
  setBrightness(15);
  clear();

  return true;

}

void Driver_7Segment::setBrightness(uint8_t brightness)
{

  if(brightness > 15) brightness = 15;
  Wire.beginTransmission(_address);
  Wire.write(0xE0 | brightness);
  Wire.endTransmission();

}

void Driver_7Segment::clear()
{

  for(uint8_t i = 0 ; i < 8 ; i++)
    _displayBuffer[i] = 0x00;

  _writeDisplay();

}

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
{

  Wire.beginTransmission(_address);
  Wire.write(0x00);
  for(uint8_t i = 0 ; i < 8 ; i++)
  {

    Wire.write(_displayBuffer[i]);
    Wire.write(0x00);

  }

  Wire.endTransmission();

}

uint8_t Driver_7Segment::_charToSegment(char c)
{}