/*
 * AvgValue.ino
 * Example showing how calculate a moving average. 
 * This program use a cumulative moving average formula:
 * 
 * CMA(n+1) = CMA(n) +   [ X(n+1) - CMA(n) ] / ( n + 1 )
 * 
 * Authors:
 *         Marco Boeris Frusca 
 * 
 */
#include <avgvalue.h> 

float value = 0;
uint8_t index = 0;

avgValue avg;

void setup() {
  Serial.begin(9600);
  Serial.println("Calculate average using a cumulative moving average formula");
}

void loop() {
  // Create a random value
  value = 0;  
  value = random(300);
  value /= 10;
  
  // Update average
  avg.add(value);
  
  // Print data
  Serial.print( "index = " );
  Serial.println( index );
  Serial.print( "value = " );
  Serial.println( value );
  Serial.print( "avg   = " );
  Serial.println( avg.value() );

  // Reset average after 50 values
  index++;
  if ( index == 50 )
  {
    value = 0;
    index = 0;  
  }
    
  delay(5000);  
}