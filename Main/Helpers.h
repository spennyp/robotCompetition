// Helpers.h

#ifndef _HELPERS_h
#define _HELPERS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


// Sensors

extern bool clawIRTriggered();
extern bool foundCliff();
extern bool frontTouchSensorTriggered();
extern bool topHallTriggered();
extern bool bottomHallTriggered();


// Run Helpers

extern void activateDumper();
extern void resetDumper();
extern void deployBridge();
extern void resetBridge();

#endif
