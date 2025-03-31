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
{

  if(digit > 3) return;
  if(number < 0 || number > 9) return;
  _displayBuffer[digit] = _charToSegment('0' + number);
  _writeDisplay();

}

void Driver_7Segment::print(char character, uint8_t digit)
{

  if(digit > 3) return;
  _displayBuffer[digit] = _charToSegment(character);
  _writeDisplay();

}

void Driver_7Segment::print(const char* str)
{

  for(uint8_t i = 0 ; i < 4 && str[i] != '\0' ; i++)
    _displayBuffer[i] = _charToSegment(str[i]);

  _writeDisplay();

}

void Driver_7Segment::setSegments(uint8_t digit, uint8_t value)
{

  if(digit > 3) return;
  _displayBuffer[digit] = value;
  _writeDisplay();

}

void Driver_7Segment::turnOnSegment(uint8_t digit, uint8_t segment)
{

  if(digit > 3 || segment > 7) return;
  _displayBuffer[digit] |= (1 << segment);
  _writeDisplay();

}

void Driver_7Segment::turnOffSegment(uint8_t digit, uint8_t segment)
{

  if(digit > 3 || segment > 7) return;
  _displayBuffer[digit] &= ~(1 << segment);
  _writeDisplay();

}

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
{

  switch (c)
  {
    case '0': return 0b00111111; // 0
    case '1': return 0b00000110; // 1
    case '2': return 0b01011011; // 2
    case '3': return 0b01001111; // 3
    case '4': return 0b01100110; // 4
    case '5': return 0b01101101; // 5
    case '6': return 0b01111101; // 6
    case '7': return 0b00000111; // 7
    case '8': return 0b01111111; // 8
    case '9': return 0b01101111; // 9
    case 'A': case 'a': return 0b01110111; // A
    case 'B': case 'b': return 0b01111100; // B
    case 'C': case 'c': return 0b00111001; // C
    case 'D': case 'd': return 0b01011110; // D
    case 'E': case 'e': return 0b01111001; // E
    case 'F': case 'f': return 0b01110001; // F
    case 'G': case 'g': return 0b00111101; // G
    case 'H': case 'h': return 0b01110100; // H
    case 'I': case 'i': return 0b00000100; // I
    case 'J': case 'j': return 0b00011110; // J
    case 'L': case 'l': return 0b00111000; // L
    case 'N': case 'n': return 0b01010100; // N
    case 'O': case 'o': return 0b00111111; // O
    case 'P': case 'p': return 0b01110011; // P
    case 'Q': case 'q': return 0b01100111; // Q
    case 'R': case 'r': return 0b01010000; // R
    case 'S': case 's': return 0b01101101; // S
    case 'T': case 't': return 0b01111000; // T
    case 'U': case 'u': return 0b00111110; // U
    case 'Y': case 'y': return 0b01101110; // Y
    case '-': return 0b01000000;
    case '_': return 0b00001000;
    default: return 0b00000000;
  }

}