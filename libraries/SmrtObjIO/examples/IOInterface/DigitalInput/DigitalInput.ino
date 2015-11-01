/*
 * DigitalInput.ino
 * Reads an digital input on pin 0, prints the result to the serial monitor.
 * 
 * Authors:
 *         Marco Boeris Frusca 
 * 
 */
#include <iosignal.h>

// Digital input
smrtobj::io::DigitalInput Pin;

void setup(){
  // Open serial monitor
  Serial.begin(9600);
  
  // Initialize and open input pin
  Pin.init(3);
}

void loop(){
  // Read and print value from digital input
  Serial.print("Value: ");
  Serial.println(Pin.read());
  delay(5000);
}