// Lifecycle.cpp

#include "Lifecycle.h"
#include "Globals.h"
#include "Helpers.h"


// ***CONFIGURATION, DETERMINES IF TOP BOT ONLY OR BOTH BOTS WILL BE RUNNING***
bool topBotOnly = false;


// Initialization (helpers use these)
MotorWheel motorWheel(motorSpeed, PID(proportionalGain, derivativeGain, pidThreshold));
Claw claw;
int numberOfTeddiesGrabbed;
int communicationCount;
bool onBottomBot;
bool grabbed;

void run() {
	unsigned long prevLoopStartTime = millis();
	LCD.clear(); LCD.print("Running"); LCD.setCursor(0, 1); LCD.print("Stop to return");

	setupRobot();
	
	// Main run loop, regulated to 10ms
	while(true) {
		while (millis() - prevLoopStartTime < 10) {}
		prevLoopStartTime = millis();

		if(shouldDetatchFromBottomBot()) {
			detatchFromBottom();
		} 

		LCD.clear(); LCD.print(numberOfTeddiesGrabbed);
		if(shouldGrabTeddy()) {
			grabTeddy();
		}

		if(claw.poll(numberOfTeddiesGrabbed)) {
			grabbed = false;

			if(numberOfTeddiesGrabbed == 1 || numberOfTeddiesGrabbed == 2) {
				digitalWrite(communicationOut, HIGH);
				if(numberOfTeddiesGrabbed == 1) {
					firstTeddyCode();
				}
			} else if(numberOfTeddiesGrabbed == 3) {
				thirdTeddyCode();
			} else if(numberOfTeddiesGrabbed == 4) {
				fourthTeddyCode();
			} else if(numberOfTeddiesGrabbed == 5) {
				fifthTeddyCode();
			}
		}

		motorWheel.poll();

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

	while(true) {
		while (millis() - prevLoopStartTime < 10) {}
		prevLoopStartTime = millis();

		// TODO: Write this
	}
}













