// Lifecycle.cpp

#include "Lifecycle.h"
#include "Globals.h"
#include "Helpers.h"
#include "MotorWheel.h"
#include "Claw.h"
#include "Test.h"

Claw claw;
MotorWheel motorWheel(motorSpeed, PID(proportionalGain, derivativeGain, pidThreshold));

int cliffCount = 0;

// API
void run() {
	reset();
	unsigned long prevLoopStartTime = millis();
	int numberOfTeddiesGrabbed = 0;
	systemDiagnostics();


	LCD.clear(); LCD.print("Running"); LCD.setCursor(0, 1); LCD.print("Stop to return");

	reset();
	delay(2000);

	while(true) {
		while (millis() - prevLoopStartTime < 10) {} //Regulate speed of the main loop to 10 ms
		prevLoopStartTime = millis();

		// TODO: Add run code
		systemDiagnostics();

		// TODO: Remove this for competition
		if (stopbutton()) {
			delay(100);
			if (stopbutton()) {
				LCD.print("Stop");
				motorWheel.stop();
				break;
			}
		}
	}
}

// If all else fails
void codeRed() {
	unsigned long prevLoopStartTime = millis();
	delay(3000); // Time to take top bot off bottom
	motorWheel.runWithPID = true;

	while(true) {
		while (millis() - prevLoopStartTime < 10) {}
		prevLoopStartTime = millis();

		// TODO: Write this
	}
}

void reset() {

}



