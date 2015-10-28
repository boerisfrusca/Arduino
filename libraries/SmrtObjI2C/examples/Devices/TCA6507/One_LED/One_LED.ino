/*
 * One_LED.ino
 * Simple demo to flash one LED. 
 * 
 * Authors:
 *         Marco Boeris Frusca 
 * 
 */

// I2Cdev and IAQ2000 must be installed as libraries, or else the .cpp/.h files
// for both classes must be in the include path of your project3
#include "I2Cdev.h"


// SmartObject library
#include <smrtobjio.h>                        // Generic analog/digital sensors
#include <smrtobji2c.h>

#include <Wire.h>    // include Wire library

// Create instance of tca6507, map IC reset pin, and put device in shutdown mode. (can be changed to any arduino pin).
smrtobj::TCA6507 tca6507(5); 

// Pin number where LED is connected
uint8_t pin = smrtobj::TCA6507::P1;

// Device connected flag
bool connected = false;

void setup() {

  Serial.begin(9600);
  Wire.begin(8);

  delay(2000);

  // Enable IC for communications
  tca6507.initialize();
  tca6507.start();  
  
  if ( tca6507.isConnected() )
  {
    /* Set up with following parameters: Setup Bank Number 0, Fade On Time=0ms, On Time=256ms, Fade Off Time=64ms, Off Time=256ms, Second Off Time=1024ms */
    connected = true;
    tca6507.basicBankSetup(smrtobj::TCA6507::BANK0, smrtobj::TCA6507::TMS0, smrtobj::TCA6507::TMS256, smrtobj::TCA6507::TMS64, smrtobj::TCA6507::TMS256, smrtobj::TCA6507::TMS1024);  // Setup of flash and fade bank zero. (See library manual for detailed description of commands being send)
  }    
}

void loop() {
  Serial.println( F("loop") );

  if ( tca6507.isConnected() )
  {
    Serial.println( F("TCA6507 OK") );
    /* Attach pin one of tca6507 to memory bank zero */
    // Sets specified pin to specified mode. Used for driving separate pins.
    tca6507.pinSetState(pin, smrtobj::TCA6507::LED_BLINK_BANK0); 

    // Pretend to do something useful.
    delay(10000);  

    // Turn off LED on pin 1.
    tca6507.pinSetState(pin, smrtobj::TCA6507::LED_OFF);

    // Pretend to do something useful.
    delay(1000);

    // Turn on LED on pin 1.
    tca6507.pinSetState(pin, smrtobj::TCA6507::LED_ON); 
  
    // Pretend to do something useful.
    delay(10000);  
 
    // Turn off LED on pin 1.
    tca6507.pinSetState(pin, smrtobj::TCA6507::LED_OFF); 
  }
  else
    Serial.println( F("TCA6507 KO") );
  // Pretend to do something useful.
  delay(10000);  
 }