// Helpers.cpp

#include "Helpers.h"
#include "Globals.h"


// Sensors

bool clawIRTriggered() {
	return digitalRead(clawIR);
}

bool foundCliff() {
	return (analogRead(cliffQRD) > cliffThreshold.value);
}

bool frontTouchSensorTriggered() {
    return digitalRead(frontTouchSensor);
}

bool topHallTriggered() {
    return !digitalRead(topHall);
}

bool bottomHallTriggered() {
    return !digitalRead(bottomHall);
}


// RunHelpers

// Reset constants
const int bottomBridgeServoResetPosition = 90;
const int topBridgeLowerServoResetPosition = 0;
const int topBridgeUpperServoResetPosition = 90;
const int leftDumpServoResetPosition = 160;
const int rightDumpServoResetPosition = 10;

// Deploy constants
const int bottomBridgeServoDeployPosition = 150;
const int topBridgeLowerServoDeployPosition = 90;
const int topBridgeUpperServoDeployPosition = 0;
const int dumpDeployAngle = 150;

const int bridgeDropDelay = 2000; // [ms]

void activateDumper() {
	// setServo(storageDumpServoLeft, leftDumpServoResetPosition - dumpDeployAngle, false);
	// setServo(storageDumpServoRight, rightDumpServoResetPosition + dumpDeployAngle, false);
}

void resetDumper() {

}

void deployBridge() {
	// setServo(topBridgeLowerServo, topBridgeLowerServoDeployPosition);
	// delay(bridgeDropDelay / 2);
	// setServo(topBridgeUpperServo, topBridgeUpperServoDeployPosition);
	// delay(bridgeDropDelay);
}

void resetBridge() {

}

