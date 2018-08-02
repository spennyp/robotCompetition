// Helpers.cpp

#include "Helpers.h"
#include "Globals.h"


// Sensors

bool clawIRTriggered() {
	return (analogRead(clawIR) < clawIRThreshold.value);
}

bool foundCliff() {
	return (analogRead(cliffQRD) > cliffThreshold.value);
}

bool frontTouchSensorTriggered() {
    return !digitalRead(frontTouchSensor);
} 

bool topHallTriggered() {
    return !digitalRead(topHall);
}

bool bottomHallTriggered() {
    return !digitalRead(bottomHall);
}


// RunHelpers

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
	setServo(bottomBridgeServo, bottomBridgeServoDeployPosition);
	delay(1000);
	setServo(leftBridgeServo, leftBridgeServoDeployPosition);
	setServo(rightBridgeServo, rightBridgeServoDeployPosition);
}

void resetBridge() {
	setServo(bottomBridgeServo, bottomBridgeServoResetPosition);
	delay(1000);
	setServo(leftBridgeServo, leftBridgeServoResetPosition);
	setServo(rightBridgeServo, rightBridgeServoResetPosition);
}
