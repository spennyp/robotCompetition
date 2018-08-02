// Lifecycle.cpp

#include "Lifecycle.h"
#include "Globals.h"
#include "Helpers.h"
#include "MotorWheel.h"
#include "Claw.h"

MotorWheel motorWheel(motorSpeed, PID(proportionalGain, derivativeGain, pidThreshold));
Claw claw;

int cliffCount = 0;

// API
void run() {
	reset();
	unsigned long prevLoopStartTime = millis();

	LCD.clear(); LCD.print("Running"); LCD.setCursor(0, 1); LCD.print("Stop to return");

	// Temporary for testing top bot only
	int numberOfTeddiesGrabbed = 2;
	bool onBottomBot = false;
	claw.switchToTopBot();
	// reset();
	delay(2000);
	motorWheel.forward();

	while(true) {
		while (millis() - prevLoopStartTime < 10) {} //Regulate speed of the main loop to 10 ms
		prevLoopStartTime = millis();

		// TODO: Write this

		// if(onBottomBot && digitalRead(bottomBotTransitionPin)) {
		// 	onBottomBot = false;
		// 	motorWheel.forward(100);
		// } 

		LCD.clear(); LCD.print("Trig: "); LCD.print(clawIRTriggered());
		if(clawIRTriggered()) {
			if(onBottomBot) {
				// runClawForBottomBot();
			} else {
				motorWheel.stop();
				claw.grab();
			}
			numberOfTeddiesGrabbed ++;
		}


		motorWheel.poll();
		if(claw.poll()) {
			LCD.clear(); LCD.print("Hit here");
			delay(20000);
			if(numberOfTeddiesGrabbed == 3) {
				delay(20000);
				motorWheel.turnLeft(90, 100);
				motorWheel.forward();
				delay(100);
			} else if(numberOfTeddiesGrabbed == 4) {
				motorWheel.turnLeft(90);
				motorWheel.forward();
				while(!foundCliff()) {}
				motorWheel.stop();
			}
			motorWheel.runWithPID = true;
		}

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

void runClawForBottomBot() {
	// TODO: Add code to tell bottom bot to stop and to trigger claw when in position
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
	motorWheel.runWithPID = true;
	// claw.reset();
	resetBridge();
	resetDumper();
}



