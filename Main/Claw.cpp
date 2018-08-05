// Claw.cpp

#include "Claw.h"
#include "Globals.h"
#include "Helpers.h"

// TODO: Figure out what these 6 values should be
const int clawServoOpenAngle = 170;
const int clawServoGrabAngle = 30;
const int dumpServoNormalAngleTopBot = 140;
const int dumpServoNormalAngleBottomBot = 170;
const int dumpServoDumpAngle = 0;
const int dumpServoDumpTime = 2000;
const int grabServoDumpReleaseTime = 1000;

const int transitionAngle = 40;


// API

Claw::Claw() {
    bottomBot = true;
    grabbed = false;
}

void Claw::grab() {
    int normalAngle = (bottomBot) ? dumpServoNormalAngleBottomBot : dumpServoNormalAngleTopBot;
    setServo(clawGrabServo, clawServoGrabAngle); 
    setServo(clawDumpServo, normalAngle); // Need to set this explicitly
    grabbed = true;
    delay(500);
    if(bottomBot) {
        raise();
        delay(500); // time to leave bottom limit switch before next poll
    }
}

void Claw::switchToTopBot() {
    bottomBot = false;
    grabbed = false;
    reset();
}

void Claw::reset() {
    int normalAngle = (bottomBot) ? dumpServoNormalAngleBottomBot : dumpServoNormalAngleTopBot;
    if(bottomBot) {
        if(!bottomHallTriggered()) {
            close();
            setServo(clawDumpServo, transitionAngle);
            delay(1000);
            lower();
            while(!bottomHallTriggered()) {} 
            motor.speed(winchMotor, 0);
        }
    } else if(!topHallTriggered()){
        close();
        delay(500);
        raise();
        while(!topHallTriggered()) {} 
        motor.speed(winchMotor, 0);
    }
    setServo(clawDumpServo, normalAngle);
    delay(500);
    open();
    grabbed = false;
    delay(500);
}

void Claw::raiseForBridgeDrop() {
    close();
    delay(500);
    raise();
    while(!topHallTriggered()) {}
    motor.speed(winchMotor, 0);
}


// Lifecycle

// Returns true once starts to lower
bool Claw::poll() {
    bool topSwitch = topHallTriggered();
    if(topSwitch || bottomHallTriggered()) {
        motor.speed(winchMotor, 0);
        if(topSwitch && grabbed) {
            dump();
            grabbed = false;
            if(bottomBot) {
                lower();
            }
            return true;
        }
    }
    return false;
}


// Helpers

void Claw::raise() {
    if (!topHallTriggered()) {
        motor.speed(winchMotor, winchUpSpeed.value);
    }
}

void Claw::lower() {
    if (!bottomHallTriggered()) {
        motor.speed(winchMotor, -winchDownSpeed.value);  
    }
}

void Claw::dump() {
    setServo(clawDumpServo, dumpServoDumpAngle);
    delay(1000);
    open();
    delay(1000);
    reset();
}

void Claw::open() {
    setServo(clawGrabServo, clawServoOpenAngle); 
}

void Claw::close() {
    setServo(clawGrabServo, clawServoGrabAngle); 
}

