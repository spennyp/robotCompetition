// Helpers.h

#ifndef _HELPERS_h
#define _HELPERS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "MotorWheel.h"


// Sensors

extern bool clawIRTriggered();
extern bool topHallTriggered();
extern bool bottomHallTriggered();
extern bool foundCliff();
extern bool leftSideQRDFoundCliff();
extern bool frontTouchSensorTriggered();


// Core Functionality

extern void activateDumper();
extern void resetDumper();
extern void deployBridge();
extern void resetBridge();


// Run helpers

extern void startBottomBot();
extern void foundTeddyWithBottom();
extern bool shouldGrabTeddy();
extern void grabTeddy();
extern bool shouldDetatchFromBottomBot();
extern void detatchFromBottom();
extern bool sweepLeft();
extern bool veerRight();


// State Helpers

extern void firstTeddyCode();
extern void thirdTeddyCode();
extern void fourthTeddyCode();
extern void fifthTeddyCode();


// Setup

extern void setupRobot();
void topBotOnlySetupRobot();
void setupForFullCourse();

// Reset 
extern void reset();
extern void softReset();






#endif
