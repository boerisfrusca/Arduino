/*
 * PWMOutput.ino
 * Turns on an output (e.g. a LED) increase gradually its lighting intensity.
 * 
 * Authors:
 *         Marco Boeris Frusca 
 * 
 */
#include <smrtobjio.h>

// PWM output
smrtobj::io::PWMOutput Pout;

// Duty cycle value
byte value = 0;

void setup(){
  // Initialize the pin of the digital output
  Pout.init(3);
}

void loop(){
  // change duty cycle and create new signal
  Pout.write(value++);
  delay(100);
}