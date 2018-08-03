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
	unsigned long prevLoopStartTime = millis();
	LCD.clear(); LCD.print("Running"); LCD.setCursor(0, 1); LCD.print("Stop to return");

	// With bottom bot
	int numberOfTeddiesGrabbed = 0;
	bool onBottomBot = true;
	bool grabbed = false;
	reset();
	startBottomBot();
	delay(1000);


	// Temporary for testing top bot only
	// int numberOfTeddiesGrabbed = 2;
	// bool onBottomBot = false;
	// claw.switchToTopBot();
	// delay(2000);
	// motorWheel.forward();

	
	while(true) {
		while (millis() - prevLoopStartTime < 10) {} //Regulate speed of the main loop to 10 ms
		prevLoopStartTime = millis();

		// TODO: Write this

		// if(onBottomBot && digitalRead(bottomBotTransitionPin)) {
		// 	onBottomBot = false;
		// 	motorWheel.forward(100);
		// } 

		LCD.clear(); LCD.print("Trig: "); LCD.print(clawIRTriggered());
		if(clawIRTriggered() && grabbed == false) {
			grabbed = true;
			if(onBottomBot) {
				foundTeddyWithBottom();
			} else {
				motorWheel.stop();
				if(numberOfTeddiesGrabbed == 3) { // Drive forward to get the 4th teddy into the claw better
					motorWheel.forward();
					delay(800);
					motorWheel.stop();
				}
			}
			claw.grab();
			numberOfTeddiesGrabbed ++;
		}

		motorWheel.poll();
		if(claw.poll()) {
			grabbed = false;

			// digitalWrite(stopPin, HIGH); // For first half
			// if(numberOfTeddiesGrabbed == 1 || numberOfTeddiesGrabbed == 2) {
			// 	digitalWrite(stopPin, HIGH);
			// }


			// } else if(numberOfTeddiesGrabbed == 3) {
			// 	motorWheel.forward();
			// 	while(!foundCliff()) {}
			// 	motorWheel.stop();
			// 	delay(500);
			// 	// motorWheel.reverse();
			// 	// delay(00);
			// 	motorWheel.stop();
			// 	delay(800);
			// 	motorWheel.turnLeft(80);
			// 	delay(2000);
			// 	// delay(20000);
			// 	// motorWheel.forward();
			// 	// delay(200);
			// 	// motorWheel.stop();
			// 	// LCD.clear(); LCD.print("Hit here");
			// 	// delay(20000);
			// } else if(numberOfTeddiesGrabbed == 4) {
			// 	delay(2000);
			// 	motorWheel.forward();
			// 	while(!foundCliff()) {}
			// 	motorWheel.stop();
			// 	delay(1000);
			// 	motorWheel.turnLeft(90);
			// 	delay(1000);
			// 	motorWheel.forward();
			// 	while(!foundCliff()) {}
			// 	motorWheel.stop();
			// 	delay(20000);
				
			// 	// while(!foundCliff()) {}
			// 	// motorWheel.stop();
			// }

			if(numberOfTeddiesGrabbed != 1 && numberOfTeddiesGrabbed != 2) {
				// motorWheel.runWithPID = true;
			}
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
	motorWheel.runWithPID = false;
	// digitalWrite(stopPin, HIGH);
	claw.reset();
	// resetBridge();
	// resetDumper();
}

void foundTeddyWithBottom() {
	digitalWrite(stopPin, LOW);
	delay(250); // Pulse LOW for 250 ms
	digitalWrite(stopPin, HIGH);
	while(!clawIRTriggered()) {}
	digitalWrite(stopPin, LOW);
	delay(500);
}

void startBottomBot() {
	digitalWrite(stopPin, LOW);
	delay(250);
	digitalWrite(stopPin, HIGH);
}



