/*
 * SatelliteReceiver.cpp
 *
 *  Created on: 9. jan. 2011
 *      Author: develop
 */
#include "SatelliteReceiver.h"

// The preamble byte vary between Rx
// The first byte is number of errors and maxs out at FF
// The second byte is the bind type
// 01 == DSM2 1024/22ms
// A2 == DSMX 22ms

void SatelliteReceiver::getFrame(void){
  while(Serial.available() > 16)
  {
    for(index = 0; index <= 15; index++)
    {
      inByte = Serial.read();
      inData[index] = inByte;
    }
  }  
}

int SatelliteReceiver::getErrors(){
	return inData[0];
}	
int SatelliteReceiver::getBindType(){
	return inData[1];
}
int SatelliteReceiver::getAile(){
	return inData[2] * 256 + inData[3] - 1 * 1024;
}
int SatelliteReceiver::getFlap(){
	return inData[4] * 256 + inData[5] - 5 * 1024;
}
int SatelliteReceiver::getGear(){
	return inData[6] * 256 + inData[7] - 4 * 1024;
}
int SatelliteReceiver::getElev(){
	return inData[8] * 256 + inData[9] - 2 * 1024;
}
int SatelliteReceiver::getAux2(){
	return inData[10] * 256 + inData[11] - 6 * 1024;
}
int SatelliteReceiver::getThro(){
	return inData[12] * 256 + inData[13] - 0 * 1024;
}
int SatelliteReceiver::getRudd(){
	return inData[14] * 256 + inData[15] - 3 * 1024;
}
