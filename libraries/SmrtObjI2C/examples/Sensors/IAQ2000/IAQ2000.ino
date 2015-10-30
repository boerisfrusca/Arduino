/*
 * IAQ200.ino
 * Reads from a IAQ2000 sensor and prints to the serial monitor. 
 * 
 * Authors:
 *         Marco Boeris Frusca 
 * 
 */
#include <Wire.h>           // I2C

// I2Cdev and IAQ2000 must be installed as libraries, or else the .cpp/.h files
// for both classes must be in the include path of your project
#include "I2Cdev.h"

// SmartObject library
#include <smrtobjio.h>      // Generic analog/digital sensors
#include <smrtobji2c.h>     // I2C device

// I2C device
smrtobj::i2c::IAQ2000 iaq;

// local flag: True if device id connected
bool connected = false;

void setup()
{
  // Open serial monitor
  Serial.begin(9600);

  // Open I2C
  Wire.begin();

  // Test if device is connected 
  if( iaq.isConnected() )
  {
    connected = true;
    Serial.println( F("iaq2000 connected") );
  }
  else
    Serial.println( F("iaq2000 connected") );
}

void loop()
{
  if (connected)
  {
    // Read value from ADC
    if ( iaq.read() )
    {
      Serial.print( F("VOC: ") );
      Serial.print( iaq.measure() , DEC );
      Serial.println( F(" ppm") );
    }
  }
 delay(10000);
}
