/*
 * TimeIntervalSeconds.ino
 * Example showing time interval in seconds.
 * This program prints message on serial monitor every 20 seconds.
 * 
 * At every loop cycle, it resets the start time (into the constructor of 
 * interval object), waits 5 seconds and then gets the passed time to 
 * sleep. 
 * 
 * Authors:
 *         Marco Boeris Frusca 
 * 
 */
#include <intervalseconds.h>
#include <Time.h>

#define PERIOD 20

//! Time interval in seconds
smrtobj::timer::IntervalSeconds t;

void setup() {
  // Open serial port to debug
  Serial.begin(9600);
}

void loop() {
  // update start time 
  t.update();
  Serial.print( "Interval start time is " );
  Serial.println( t.start() );
  
  //put your code here
  Serial.println("Code for 5 seconds delay");
  delay(5000);
  
  unsigned long tdelay = PERIOD - t.time();

  Serial.print( "It is passed " );
  Serial.print( t.time() ); 
  Serial.println( "s" );
  Serial.print( "Time to sleep " );
  Serial.print( tdelay );
  Serial.println( "s" );
  
  delay((tdelay < 0)?0:tdelay);
}