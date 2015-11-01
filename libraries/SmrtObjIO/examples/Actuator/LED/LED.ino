/*
 * LED.ino
 * Turns on an LED on for one second, then off for one second, repeatedly.
 * 
 * Authors:
 *         Marco Boeris Frusca 
 * 
 */
#include <smrtobjio.h>

// The digital actuator is a LED
smrtobj::io::DigitalActuator led;

void setup() {
  // Initializes LED as connected to pin 6
 led.init(6);
}

void loop() {
  // Turn on/off LED every second
  if ( !led.isOn() )
  {
    led.on();
  }
  else
  {
    led.off();
  }
  delay(1000);
}