/*
 * DigitalOutput.ino
 * Turns on an output (e.g. a LED) on for one second, then off for one second, repeatedly.
 * 
 * Authors:
 *         Marco Boeris Frusca 
 * 
 */
#include <smrtobjio.h>

// Digital output
smrtobj::io::DigitalOutput Pout;

void setup(){
  // Initialize the pin of the digital output
  Pout.init(3);
}

void loop(){
  if ( Pout.isOpen() )
  {
    // Turn on
    Pout.write(HIGH);
    delay(1000);

    // Turn off
    Pout.write(LOW);
  }
  delay(1000);  
}