// Helpers.cpp

#include "Helpers.h"
#include "Globals.h"
#include "Lifecycle.h"


// Lifecycle veriables
extern MotorWheel motorWheel;
extern Claw claw;
extern int numberOfTeddiesGrabbed;
extern int communicationCount;
extern bool onBottomBot;
extern bool grabbed;
extern bool topBotOnly;


// Sensors

bool clawIRTriggered() {
	return (analogRead(clawIR) < clawIRThreshold.value);
}

bool topHallTriggered() {
    return !digitalRead(topHall);
}

bool bottomHallTriggered() {
    return !digitalRead(bottomHall);
}

bool foundCliff() {
	return (analogRead(cliffQRD) > cliffThreshold.value);
}

bool leftSideQRDFoundCliff() {
	return (analogRead(leftSideQRD) > leftSideQRDThreshold.value);
}

bool frontTouchSensorTriggered() {
    return !digitalRead(frontTouchSensor);
} 


// Core Functionality

// Deploy constants
const int bottomBridgeServoDeployPosition = 150;
const int leftBridgeServoDeployPosition = 0;
const int rightBridgeServoDeployPosition = 150;
const int dumpDeployAngle = 160;

// Reset constants
const int bottomBridgeServoResetPosition = 45;
const int leftBridgeServoResetPosition = 100;
const int rightBridgeServoResetPosition = 45;
const int leftDumpServoResetPosition = 10;
const int rightDumpServoResetPosition = 170;

void activateDumper() {
	setServo(leftStorageDumpServo, leftDumpServoResetPosition + dumpDeployAngle);
	setServo(rightStorageDumpServo, rightDumpServoResetPosition - dumpDeployAngle);
}

void resetDumper() {
	setServo(leftStorageDumpServo, leftDumpServoResetPosition);
	setServo(rightStorageDumpServo, rightDumpServoResetPosition);
}

void deployBridge() {
	setServo(leftBridgeServo, leftBridgeServoDeployPosition);
	setServo(rightBridgeServo, rightBridgeServoDeployPosition);
}

void resetBridge() {
	setServo(leftBridgeServo, leftBridgeServoResetPosition);
	setServo(rightBridgeServo, rightBridgeServoResetPosition);
}


// Run helpers

void startBottomBot() {
	digitalWrite(communicationOut, LOW);
	delay(250);
	digitalWrite(communicationOut, HIGH);
}

bool shouldGrabTeddy() {
	return (clawIRTriggered() && (grabbed == false));
}

void grabTeddy() {
	grabbed = true;
	if(onBottomBot) {
		foundTeddyWithBottom();
	} else {
		// If we are on the 4th teddy, drive forward to push it into claw
		if(numberOfTeddiesGrabbed == 3) {
			motorWheel.forward(80);
			delay(300);
		}
		motorWheel.stop();
	}
	delay(400);
	claw.grab();
	numberOfTeddiesGrabbed ++;
}

void foundTeddyWithBottom() {
	digitalWrite(communicationOut, LOW); // Writes low and stays there until done grabbing
}

bool shouldDetatchFromBottomBot() {
	return (onBottomBot && digitalRead(communicationIn) == LOW && communicationCount == 1);
}

void detatchFromBottom() {
	onBottomBot = false;
	motorWheel.forward(230);
	delay(100);
	motorWheel.forward(150);
}

// Returns true once left sensor goes off the edge
bool sweepLeft() {
	if(!leftSideQRDFoundCliff()) {
		motor.speed(leftMotor, -130);
		motor.speed(rightMotor, 150);
		return false;
	} else {
		motorWheel.stop();
		return true;
	}
}

bool veerRight() {
	if(!leftSideQRDFoundCliff()) {
		motor.speed(leftMotor, 150);
		motor.speed(rightMotor, 20);
		return false;
	} else {
		motorWheel.stop();
		return true;
	}
}


// State helpers

void firstTeddyCode() {
	// keeps claw up until told to lower it by bottom for first bridge drop
	while(digitalRead(communicationIn) == LOW) {} 
	communicationCount++;
	claw.reset();
}

void thirdTeddyCode() {
	motorWheel.forward(90);
	while(!foundCliff()) {}
	motorWheel.stop();
	delay(500);
	claw.dump(numberOfTeddiesGrabbed);
	delay(500);
	motorWheel.reverse(150);
	delay(350);
	motorWheel.stop();
	delay(200);
	while(!sweepLeft()) { delay(10); }
	delay(1000);
	motorWheel.runWithPID();
}

void fourthTeddyCode() {
	delay(2000);
	motorWheel.forward(90);
	while(!foundCliff()) {}
	motorWheel.stop();
	claw.dump(numberOfTeddiesGrabbed);
	motorWheel.turnLeft(90);
	delay(1000);
	motorWheel.forward();
	while(!foundCliff()) {}
	motorWheel.stop();
	delay(1000);
	deployBridge();
	delay(1000);

	// Shake
	motorWheel.forward(200);
	delay(80);
	motorWheel.reverse(200);
	delay(80);
	motorWheel.forward(200);
	delay(80);
	motorWheel.reverse(200);
	delay(80);

	motorWheel.stop(); 
	delay(1000);
	motorWheel.reverse(100);
	delay(300);
	motorWheel.stop();
	delay(1000);
	motorWheel.forward(250);
	delay(200);
	motorWheel.stop();
	delay(500);
	motorWheel.reverse(150);
	delay(200);
	motorWheel.stop();
	delay(2000);
	motorWheel.forward(100);
	claw.reset();
}

void fifthTeddyCode() {
	motorWheel.stop();
	while(!veerRight()) { delay(10); }
	motorWheel.runWithPID();
	while(!frontTouchSensorTriggered()) { 
		motorWheel.poll(); 
		delay(10);
	}
	motorWheel.stop();
	delay(1000);
	activateDumper();
	delay(20000);
}


// Setup

void setupRobot() {
	if(topBotOnly) {
		topBotOnlySetupRobot();
	} else {
		setupForFullCourse();
	}
}

void setupForFullCourse() {
	communicationCount = 0;
	numberOfTeddiesGrabbed = 0;
	onBottomBot = true;
	grabbed = false;

	motorWheel.stop();
	reset();
	startBottomBot();
	delay(500);
}

void topBotOnlySetupRobot() {
	numberOfTeddiesGrabbed = 2;
	onBottomBot = false;
	grabbed = false;

	motorWheel.stop();
	claw.switchToTopBot(); 
	reset(); // Redundent claw reset
	detatchFromBottom();
}


// Reset

void reset() {
	motorWheel.stop();
	digitalWrite(communicationOut, HIGH);
	delay(500);
	resetBridge();
	delay(500);
	resetDumper();
	delay(500);
	claw.reset();
}

// Resets all servos but claw, for main
void softReset() {
	motorWheel.stop();
	digitalWrite(communicationOut, HIGH);
	resetBridge();
	delay(500);
	setServo(leftStorageDumpServo, leftDumpServoResetPosition + dumpDeployAngle / 2);
	setServo(rightStorageDumpServo, rightDumpServoResetPosition - dumpDeployAngle / 2);
}




