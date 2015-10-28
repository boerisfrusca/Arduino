/*
 * ADS1100.ino
 * Reads from an Analog-to-Digital (A/D) converter TI ADS1100 and prints the corrisponding voltage to the serial monitor. 
 * 
 * Authors:
 *         Marco Boeris Frusca 
 * 
 */
#include <Wire.h>           // I2C

// I2Cdev  must be installed as libraries, or else the .cpp/.h files
// this class must be in the include path of your project
#include "I2Cdev.h"

// SmartObject library
#include <smrtobjio.h>      // Generic analog/digital sensors
#include <smrtobji2c.h>     // I2C device

#define DEVICE_ADDRESS 0x48 // Device address

// I2C device
smrtobj::ADS1100 adc(DEVICE_ADDRESS);

// local flag: True if device id connected
bool connected = false;

void setup()
{
  // Open serial monitor
  Serial.begin(9600);

  // Open I2C
  Wire.begin();

  // Test if device is connected 
  if( adc.isConnected() )
  {
    connected = true;
    Serial.println( "ADC connected" );
  }
  else
    Serial.println( "ADC not connected" );
}

void loop()
{
  if (connected)
  {
    // Read value from ADC
    if ( adc.read() )
    {
      // Print value
      Serial.print( "Value: ");
      Serial.print( adc.value() , DEC );
      Serial.print( " - ");
      
      // Print voltage
      float voltage = adc.measure();
      Serial.print( "Voltage: ");
      Serial.print( voltage , DEC );
      Serial.println( " V");
    }
  }
 delay(10000);
}

