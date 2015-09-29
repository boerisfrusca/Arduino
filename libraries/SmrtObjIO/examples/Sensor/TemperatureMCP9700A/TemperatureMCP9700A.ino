/*
 * TemperatureMCP9700A.ino
 * Reads a Linear Active Thermistor sensor (MCP9700A) connected to the analog input A0 the prints the result 
 * to the serial monitor. To calculate the input voltage it is used the default value (5.0V).
 * If you use an external voltage ad Vref, you have remove the comments and use the functions:
 * - analogReference(EXTERNAL)
 * - smrtobj::AnalogSensor::setReference(<Vref>);
 * where Vref is your reference voltage.
 * 
 * Authors:
 *         Marco Boeris Frusca 
 * 
 */
#include <smrtobjio.h>

smrtobj::MCP9700A temperature;

void setup() {
  Serial.begin(9600);
  
  // Set reference voltage
  //analogReference(DEFAULT);
  smrtobj::AnalogSensor::setReferenceDefault(smrtobj::AnalogSensor::V5_0);
  
  /*
  // Set reference external voltage
  analogReference(EXTERNAL);
  smrtobj::AnalogSensor::setReference(2.5);  
  */  
  // Initialize sensor
  temperature.init(A0);
  
  Serial.print("reference: ");
  Serial.println( smrtobj::AnalogSensor::reference() );

  Serial.println(temperature.read());
  Serial.print("Value: ");
  Serial.println(temperature.value());
  Serial.print("Celsius: ");
  Serial.println(temperature.celsius());
  Serial.print("Kelvin: ");
  Serial.println(temperature.kelvin());
  Serial.print("Farenheit: ");
  Serial.println(temperature.farenheit());
}

void loop() {
}