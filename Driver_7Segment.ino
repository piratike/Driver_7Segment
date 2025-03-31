#include "Driver_7Segment.h"

Driver_7Segment myDriver;

void setup()
{

  Serial.begin(9600);
  myDriver.begin();

}

void loop()
{}