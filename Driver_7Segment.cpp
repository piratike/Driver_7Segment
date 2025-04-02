#include "Driver_7Segment.h"

/**
 * @brief Constructor initializes the I2C address to the default 0x70.
 */
Driver_7Segment::Driver_7Segment() : _address(0x70)
{
}

/**
 * @brief Initializes the HT16K33 display by searching for its I2C address.
 * @return True if a valid I2C address is found, false otherwise.
 */
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

/**
 * @brief Sets the display brightness.
 * @param brightness Value from 0 (dim) to 15 (bright).
 */
void Driver_7Segment::setBrightness(uint8_t brightness)
{

  if(brightness > 15) brightness = 15;
  Wire.beginTransmission(_address);
  Wire.write(0xE0 | brightness);
  Wire.endTransmission();

}

/**
 * @brief Clears the display buffer and updates the display.
 */
void Driver_7Segment::clear()
{

  for(uint8_t i = 0 ; i < 8 ; i++)
    _displayBuffer[i] = 0x00;

  _writeDisplay();

}

/**
 * @brief Turns on the display.
 */
void Driver_7Segment::displayOn()
{

  Wire.beginTransmission(_address);
  Wire.write(0x81);
  Wire.endTransmission();

}

/**
 * @brief Turns off the display.
 */
void Driver_7Segment::displayOff()
{

  Wire.beginTransmission(_address);
  Wire.write(0x80);
  Wire.endTransmission();

}

/**
 * @brief Displays a single digit number at a specific position.
 * @param number The number (0-9) to display.
 * @param digit The digit position (0-3 for a 4-digit display).
 */
void Driver_7Segment::print(int number, uint8_t digit)
{

  if(digit > 3) return;
  if(number < 0 || number > 9) return;
  _displayBuffer[digit] = _charToSegment('0' + number);
  _writeDisplay();

}

/**
 * @brief Displays a character at a specific position.
 * @param character The character to display.
 * @param digit The digit position (0-3 for a 4-digit display).
 */
void Driver_7Segment::print(char character, uint8_t digit)
{

  if(digit > 3) return;
  _displayBuffer[digit] = _charToSegment(character);
  _writeDisplay();

}

/**
 * @brief Displays a string on the 7-segment display (up to 4 characters).
 * @param str The null-terminated string to display.
 */
void Driver_7Segment::print(const char* str)
{

  for(uint8_t i = 0 ; i < 4 && str[i] != '\0' ; i++)
    _displayBuffer[i] = _charToSegment(str[i]);

  _writeDisplay();

}

/**
 * @brief Displays an integer on the 7-segment display (0-9999).
 * @param number The integer to display (0-9999).
 */
void Driver_7Segment::print(int number)
{

  if(number < 0 || number > 9999) return;
  char buffer[5];
  snprintf(buffer, sizeof(buffer), "%4d", number);
  print(buffer);

}

/**
 * @brief Displays a floating-point number on the 7-segment display (up to 3 decimal places).
 * @param number The floating-point number to display.
 */
void Driver_7Segment::print(double number)
{

  String value_string = String(number, 3);
  uint8_t comma_index = value_string.indexOf('.');
  String integer_part = value_string.substring(0, comma_index);
  String decimal_part = value_string.substring(comma_index + 1);
  value_string = integer_part + decimal_part;
  if(value_string.length() > 4) value_string = value_string.substring(0, 4);
  print(value_string.c_str());
  _displayBuffer[comma_index - 1] |= 0b10000000;
  _writeDisplay();

}

/**
 * @brief Sets the segment data for a specific digit.
 * @param digit The digit position (0-3).
 * @param value The segment bitmask (each bit represents a segment).
 */
void Driver_7Segment::setSegments(uint8_t digit, uint8_t value)
{

  if(digit > 3) return;
  _displayBuffer[digit] = value;
  _writeDisplay();

}

/**
 * @brief Turns on a specific segment in a digit.
 * @param digit The digit position (0-3).
 * @param segment The segment index (0-7).
 */
void Driver_7Segment::turnOnSegment(uint8_t digit, uint8_t segment)
{

  if(digit > 3 || segment > 7) return;
  _displayBuffer[digit] |= (1 << segment);
  _writeDisplay();

}

/**
 * @brief Turns off a specific segment in a digit.
 * @param digit The digit position (0-3).
 * @param segment The segment index (0-7).
 */
void Driver_7Segment::turnOffSegment(uint8_t digit, uint8_t segment)
{

  if(digit > 3 || segment > 7) return;
  _displayBuffer[digit] &= ~(1 << segment);
  _writeDisplay();

}

/**
 * @brief Writes the display buffer to the HT16K33.
 */
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

/**
 * @brief Converts a character into its 7-segment representation.
 * @param c The character to convert.
 * @return The corresponding segment bitmask.
 */
uint8_t Driver_7Segment::_charToSegment(char c)
{

  switch (c)
  {
    case '0': return 0b00111111;
    case '1': return 0b00000110;
    case '2': return 0b01011011;
    case '3': return 0b01001111;
    case '4': return 0b01100110;
    case '5': return 0b01101101;
    case '6': return 0b01111101;
    case '7': return 0b00000111;
    case '8': return 0b01111111;
    case '9': return 0b01101111;
    case 'A': case 'a': return 0b01110111;
    case 'B': case 'b': return 0b01111100;
    case 'C': case 'c': return 0b00111001;
    case 'D': case 'd': return 0b01011110;
    case 'E': case 'e': return 0b01111001;
    case 'F': case 'f': return 0b01110001;
    case 'G': case 'g': return 0b00111101;
    case 'H': case 'h': return 0b01110100;
    case 'I': case 'i': return 0b00000100;
    case 'J': case 'j': return 0b00011110;
    case 'L': case 'l': return 0b00111000;
    case 'N': case 'n': return 0b01010100;
    case 'O': case 'o': return 0b00111111;
    case 'P': case 'p': return 0b01110011;
    case 'Q': case 'q': return 0b01100111;
    case 'R': case 'r': return 0b01010000;
    case 'S': case 's': return 0b01101101;
    case 'T': case 't': return 0b01111000;
    case 'U': case 'u': return 0b00111110;
    case 'Y': case 'y': return 0b01101110;
    case '-': return 0b01000000;
    case '_': return 0b00001000;
    default: return 0b00000000;
  }

}