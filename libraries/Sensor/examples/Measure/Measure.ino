#include <measure.h>
#include <oserialstream.h>

OSerialStream debug;

void setup() {
  // put your setup code here, to run once:  
  debug.on();
  
  Measure m;
  byte coordError = 0;
  
  int err = m.setPosition("45.065670", "7.658086", "253", coordError);
  
  m.setValue(3.14);
  m.setTimestamp(now());

  debug.print("Timestamp: %ld", m.timestamp() );
  debug.println("  [%s]", m.timestamp(0) );
  debug.println("Value ( x 100): %d ]", (int) (m.value() * 100));
  debug.println("Position: [ %s %s %s ]", m.position().latitude(), m.position().longitude(), m.position().altitude());
  
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