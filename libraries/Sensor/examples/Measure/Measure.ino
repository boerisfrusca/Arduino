#include <measure.h>
#include <Time.h>

void setup() {
  // put your setup code here, to run once:  
  Serial.begin(9600);
  
  Measure m;
  byte coordError = 0;
  
  int err = m.setPosition("45.065670", "7.658086", "253", coordError);
  
  m.setValue(3.14);
  m.setTimestamp(now());

  Serial.print( "Timestamp: " );
  Serial.print(  m.timestamp() );
  Serial.println("  [%s]", m.timestamp(0) );
  Serial.println("Value ( x 100): %d ]", (int) (m.value() * 100));
  Serial.println("Position: [ %s %s %s ]", m.position().latitude(), m.position().longitude(), m.position().altitude());
  
  if (!coordError)
  {
    debug.println("Position: [ %s %s %s ]", m.position().latitude(), m.position().longitude(), m.position().altitude());
  }
  else  
  {
    debug.println("Invalid position: %d %d", coordError, err);
  }
  

}

void loop() {
  // put your main code here, to run repeatedly: 
  
}