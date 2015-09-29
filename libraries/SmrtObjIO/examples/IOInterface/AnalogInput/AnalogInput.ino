/*
 * AnalogInput.ino
 * Reads an analog input on pin 0, prints the result to the serial monitor.
 * Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.
 * 
 * Authors:
 *         Marco Boeris Frusca 
 * 
 */
#include <smrtobjio.h>

// Analog input
smrtobj::AnalogInput Pin;

void setup(){
  // Open serial monitor
  Serial.begin(9600);
  
  // Initialize and open input pin
  Pin.init(0);
}

void loop(){
  // Read and print value from digital input
  Serial.print("Value: ");
  Serial.println(Pin.read());
  Serial.print("Voltage: ");
  Serial.println(Pin.inputVoltage());
  delay(5000);
}