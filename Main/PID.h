// PID.h

#ifndef _PID_h
#define _PID_h
#include "MenuItem.h"

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class PID {
	private:
		uint16_t threshold, i, p, d;
		int8_t getState();
	public:
		PID(MenuItem pGain, MenuItem dGain, MenuItem PIDThreshold);
		int16_t getError();
		int8_t state, lastState;
};

#endif

