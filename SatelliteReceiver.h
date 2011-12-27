/*
 * SpectrumReceiver.h
 *
 *  Created on: 9. jan. 2011
 *      Author: develop
 */

#ifndef SPECTRUMRECEIVER_H_
#define SPECTRUMRECEIVER_H_

#define RXCENTER 511
#define RXTRAVEL 358 // (511 center - 63 trim) / 1,25 maxTravel
#define RXMIN 0//153 // 511center - 358travel
#define RXMAX 1022//869 // 511center + 358travel

#include "Arduino.h"

class SatelliteReceiver{
public:
	// void regByte(int byte);
	void getFrame(void);
	int getErrors();
	int getBindType();
	int getThro();
	int getAile();
	int getElev();
	int getRudd();
	int getGear();
	int getFlap();
	int getAux2();

private:
	// int channels[8];
	// int prevByte;
	// int channel;
	// bool cByte;
	
	int inData[16];
	int index;
	int inByte;
};


#endif /* SPECTRUMRECEIVER_H_ */
