// Claw.cpp

#include "Claw.h"
#include "Globals.h"
#include "Helpers.h"

// TODO: Figure out what these 6 values should be
const int clawServoOpenAngle = 180;
const int clawServoGrabAngle = 50;
const int dumpServoNormalAngle = 125;
const int dumpServoDumpAngle = 8;
const int dumpServoDumpTime = 2000;
const int grabServoDumpReleaseTime = 1000;


// API

Claw::Claw() {}

void Claw::grab() {
    setServo(clawGrabServo, clawServoGrabAngle); 
    delay(500);
    raise();
}

void Claw::switchToTopBot() {
    raise();
}

// TODO: Fix this to angle down for the bottom bot
void Claw::reset() {
    setServo(clawDumpServo, dumpServoNormalAngle);
    close();
    delay(1000);
    lower();
    open();
}


// Lifecycle

// Returns true once starts to lower
void Claw::poll() {
    bool topSwitch = topHallTriggered();
    if(topSwitch || bottomHallTriggered()) {
        motor.speed(winchMotor, 0);
        if(topSwitch) {
            dump();
            lower();
        } else {
            open();
        }
    }
}


// Helpers

void Claw::raise() {
    if (!topHallTriggered()) {
        motor.speed(winchMotor, winchSpeed.value);
    }
}

void Claw::lower() {
    if (!bottomHallTriggered()) {
        motor.speed(winchMotor, -winchSpeed.value);  
    }
}

void Claw::dump() {
    setServo(clawDumpServo, dumpServoDumpAngle);
    delay(1000);
    open();
    delay(1000);
    setServo(clawDumpServo, dumpServoNormalAngle);
    delay(500);
}

void Claw::open() {
    setServo(clawGrabServo, clawServoOpenAngle); 
}

void Claw::close() {
    setServo(clawGrabServo, clawServoGrabAngle); 
}

