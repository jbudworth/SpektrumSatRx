// Confirmed working on Arduino Pro Mini 328 5V 16Mhz
// Arduino Pro Mini 328 3.3V 8Mhz is not fast enough 
// to capture the serial stream correctly
// RXCENTER 511
// RXTRAVEL 358 // (511 center - 63 trim) / 125 maxTravel
// RXMIN 0//153 // 511center - 358travel
// RXMAX 1022//869 // 511center + 358travel


#include <SatelliteReceiver.h>

#define ledPin 13
SatelliteReceiver Rx;

void setup(){
  pinMode(ledPin, OUTPUT);
  Serial.begin(115200);
}

void loop()
{
  Rx.getFrame();

  Serial.print(Rx.getAile());
  Serial.print(" ");
  Serial.print(Rx.getElev());
  Serial.print(" ");
  Serial.print(Rx.getThro());
  Serial.print(" ");
  Serial.print(Rx.getRudd());
  Serial.print(" ");
  Serial.print(Rx.getFlap());
  Serial.print(" ");
  Serial.print(Rx.getGear());
  Serial.print(" ");
  Serial.print(Rx.getAux2());
  Serial.print(" ");
  Serial.println();
  
  if(Rx.getGear() > RXCENTER) {
  	digitalWrite(ledPin,1);
  }
  else {digitalWrite(ledPin,0);
  }
  
}