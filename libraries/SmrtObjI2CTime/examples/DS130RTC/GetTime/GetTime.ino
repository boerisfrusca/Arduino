/*
 * Set_Time.ino
 * Simple demo to read date and time from RTC DS139RTC. 
 * 
 * Authors:
 *         Marco Boeris Frusca 
 * 
 */

// Arduino libraries
#include <Time.h>                             // Time library
#include <Wire.h>                             // I2C

// I2Cdev and DS130RTC must be installed as libraries
#include "I2Cdev.h"

#include <smrtobjio.h>                        // Generic analog/digital sensors
#include <smrtobji2c.h>                       // I2C sensors and devices
#include <smrtobji2ctime.h>                   // I2C devices related to time

smrtobj::i2c::DS130RTC rtc;                        // RTC handler

void setup() {
  // Open I2C communication
  Wire.begin();

  // Open serial monitor
  Serial.begin(9600);

  delay(2000);
  
  Serial.print( F("Set time: ") );

  // GMT: Thu, 29 Oct 2015 10:06:35
  time_t t = 1446113195;
  
  if ( rtc.write(t) )
    Serial.println( F("ok") );
  else
    Serial.println( F("ko") );

  if ( rtc.write(t) )
    Serial.println( F("ok") );
  else
    Serial.println( F("ko") );

  if ( rtc.read() )
  {
    Serial.print( F("Time in epoch format: ") );
    Serial.println( rtc.time() );
  }
  else
    Serial.println( F("RTC read error!") );
    
  delay(2000);
}

void loop() {  
  delay(100);  
}