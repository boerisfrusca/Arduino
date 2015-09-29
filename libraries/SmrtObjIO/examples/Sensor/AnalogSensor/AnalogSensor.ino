/*
 * AnalogSensor.ino
 * Reads an analog input on pin A0, prints the result to the serial monitor (ADC value and 
 * corrisponding voltage. To calculate the input voltage it is used the default value (5.0V).
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

// Analog sensor
smrtobj::AnalogSensor sensor;

void setup() {
  // Open serial monitor
  Serial.begin(9600);
  
  // Set reference voltage
  //analogReference(DEFAULT);
  smrtobj::AnalogSensor::setReferenceDefault(smrtobj::AnalogSensor::V5_0);
  
  /*
  // Set reference external voltage
  analogReference(EXTERNAL);
  smrtobj::AnalogSensor::setReference(2.5);  
  */  
  // Initialize sensor aas connected to pin 0
  sensor.init(A0);
  
  // Print value as ADC output and voltage
  Serial.print("reference: ");
  Serial.println( smrtobj::AnalogSensor::reference() );

  Serial.println(sensor.read());
  Serial.print("Value: ");
  Serial.println(sensor.value());
  Serial.print("Measure: ");
  Serial.println(sensor.measure());
}

void loop() {
}