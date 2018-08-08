// Claw.cpp

#include "Claw.h"
#include "Globals.h"
#include "Helpers.h"

// TODO: Figure out what these 6 values should be
const int clawServoOpenAngle = 145;
const int clawServoGrabAngle = 0;
const int dumpServoNormalAngleTopBot = 150;
const int dumpServoNormalAngleBottomBot = 180;
const int dumpServoDumpAngle = 0;
const int dumpServoHoldAngle = 100;
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


// Lifecycle

// Returns true once starts to lower
bool Claw::poll(int numberOfTeddiesGrabbed) {
    bool topSwitch = topHallTriggered();
    if(topSwitch || bottomHallTriggered()) {
        motor.speed(winchMotor, 0);
        if(topSwitch && grabbed) {
            if(numberOfTeddiesGrabbed == 3 || numberOfTeddiesGrabbed == 4) { // Manually call from lifecycle once hit the cliff
                setServo(clawDumpServo, dumpServoHoldAngle);
            } else if (numberOfTeddiesGrabbed == 5) {
                setServo(clawDumpServo, 80);
            } else {
                dump(numberOfTeddiesGrabbed);
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

void Claw::dump(int numberOfTeddiesGrabbed) {
    setServo(clawDumpServo, dumpServoDumpAngle);
    delay(1000);
    open();
    delay(1000);
    if(numberOfTeddiesGrabbed == 1) {
        positionForBridgeDrop();
    } else if(numberOfTeddiesGrabbed == 2) {
        switchToTopBot();
    } else if(numberOfTeddiesGrabbed != 4) {
        reset();
    }
    grabbed = false;
}

void Claw::open() {
    setServo(clawGrabServo, clawServoOpenAngle); 
}

void Claw::close() {
    setServo(clawGrabServo, clawServoGrabAngle); 
}

void Claw::positionForBridgeDrop() {
    close();
    delay(500);
    setServo(clawDumpServo, transitionAngle);
    if(!topHallTriggered()) {
        raise();
        while (!topHallTriggered()) {}
    }
    motor.speed(winchMotor, 0);
}
