// Globals.cpp

#include "Globals.h"
#include <TINAH_Pins.h>


// Constants
const DigitalState digitalOn = on;
const DigitalState digitalOff = off;
const int servoControlPin1 = 1;
const int servoControlPin2 = 2;


// Motors
int leftMotor = 0;
int rightMotor = 1;
int winchMotor = 2;


// Servos
TINAH::Servo servo0(TINAH::pins::servo[0]);
TINAH::Servo servo1(TINAH::pins::servo[1]);
TINAH::Servo servo2(TINAH::pins::servo[2]);

ServoOutput::ServoOutput(TINAH::Servo _servo, DigitalState digitalState1, DigitalState digitalState2) {
    servo = _servo;
    DigitalPinAndValue pinAndVal1(servoControlPin1, digitalState1);
    DigitalPinAndValue pinAndVal2(servoControlPin2, digitalState2);
    digitalControl1 = pinAndVal1;
    digitalControl2 = pinAndVal2;
}
ServoOutput::ServoOutput() {};

void setServo(ServoOutput servoInfo, int angle) {
    if(digitalRead(servoInfo.digitalControl1.pinNumber) != servoInfo.digitalControl1.state || digitalRead(servoInfo.digitalControl2.pinNumber) != servoInfo.digitalControl2.state) {
        servoInfo.servo.detach();
        digitalWrite(servoInfo.digitalControl1.pinNumber, servoInfo.digitalControl1.state);
        digitalWrite(servoInfo.digitalControl2.pinNumber, servoInfo.digitalControl2.state);
    }

    servoInfo.servo.write(angle);
}

struct ServoOutput leftStorageDumpServo(servo1, digitalOff, digitalOff);
struct ServoOutput rightStorageDumpServo(servo0, digitalOff, digitalOff);
struct ServoOutput rightBridgeServo(servo1, digitalOff, digitalOn);
struct ServoOutput leftBridgeServo(servo0, digitalOff, digitalOn);
struct ServoOutput clawDumpServo(servo1, digitalOn, digitalOff);
struct ServoOutput clawGrabServo(servo0, digitalOn, digitalOff);
struct ServoOutput ejectServo(servo1, digitalOn, digitalOn);
struct ServoOutput bottomBridgeServo(servo0, digitalOn, digitalOn);


// Digital pins
int bottomHall = 13;
int topHall = 14;
int frontTouchSensor = 15;
int communicationOut = 7;
int communicationIn = 8;


// Analog Pins
int farTapeFollowQRD = 5;
int nearTapeFollowQRD = 4;
int cliffQRD = 3;
int clawIR = 2;
int leftSideQRD = 1;


// Helpers
DigitalPinAndValue::DigitalPinAndValue(int pinNum, DigitalState _state) {
    pinNumber = pinNum;
    state = _state;
};
DigitalPinAndValue::DigitalPinAndValue() {};



















