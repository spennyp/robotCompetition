// Menu.h

#include "MenuItem.h"

#ifndef _MENU_h
#define _MENU_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

// Configuration Menu
extern void configurationMenu();
extern MenuItem menuItems[];

// Add menu items here
extern MenuItem motorSpeed; 
extern MenuItem proportionalGain;
extern MenuItem derivativeGain;
extern MenuItem pidThreshold;
extern MenuItem cliffThreshold;
extern MenuItem delayPerDegreeTurn;
extern MenuItem winchUpSpeed;
extern MenuItem winchDownSpeed;
extern MenuItem clawIRThreshold;
extern MenuItem leftSideQRDThreshold;


// Run Menu

extern void runMenu();
extern String runBot;
extern String runSystemTest;
extern String runDiagonistics;

#endif
