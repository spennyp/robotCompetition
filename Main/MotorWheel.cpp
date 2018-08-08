// Motor.cpp

#include "MotorWheel.h"
#include "Globals.h"

const int defaultTurnSpeed = 150;

MotorWheel::MotorWheel(MenuItem speed, PID pid) : pid(pid) {
	menuMotorSpeed = speed.value;
	motorWheelSpeed = menuMotorSpeed;
	runningWithPID = true;
}

void MotorWheel::runWithPID(int speed) {
	runningWithPID = true;
	motorWheelSpeed = (speed == 0) ? menuMotorSpeed : speed;
}

// Default parameter of 0, which runs at defualtTurnSpeed
void MotorWheel::turnLeft(int angle, bool backup) {
	runningWithPID = false;
	motor.speed(leftMotor, -defaultTurnSpeed);
	if (backup) {
		motor.speed(rightMotor, -defaultTurnSpeed);
		delay(200);
	}
	motor.speed(rightMotor, defaultTurnSpeed);
	LCD.clear(); LCD.print(delayPerDegreeTurn.value);
	delay(angle * delayPerDegreeTurn.value / 2.0); // Diveded by 2 which makes tuning more sensitive
	stop();
}

// Default parameter of 0, which runs at defualtTurnSpeed
void MotorWheel::turnRight(int angle, bool backup) {
	runningWithPID = false;
	motor.speed(rightMotor, -defaultTurnSpeed);
	if (backup) {
		motor.speed(leftMotor, -defaultTurnSpeed);
		delay(200);
	}
	motor.speed(leftMotor, defaultTurnSpeed);
	LCD.clear(); LCD.print(delayPerDegreeTurn.value);
	delay(angle * delayPerDegreeTurn.value / 2.0);
	stop();
}

// Default perapeter of 0, which runs motorSpeed from the menu
void MotorWheel::forward(int speed) {
	runningWithPID = false;
	int forwardSpeed = (speed == 0) ? menuMotorSpeed : speed;

	motor.speed(leftMotor, forwardSpeed);
	motor.speed(rightMotor, forwardSpeed);
}

void MotorWheel::reverse(int speed) {
	runningWithPID = false;
	int reverseSpeed = (speed == 0) ? menuMotorSpeed : speed;

	motor.speed(leftMotor, -reverseSpeed);
	motor.speed(rightMotor, -reverseSpeed);
}

void MotorWheel::stop() {
	runningWithPID = false;
	motor.stop_all();
}

void MotorWheel::hardStop(bool goingForward) {
	if(goingForward) {
		reverse(200);
		delay(30);
		stop();
	} else {
		forward(200);
		delay(30);
		stop();
	}
}

// Lifecycle

void MotorWheel::poll() {
	if(runningWithPID) {
		int err = pid.getError();
		// when err < 0 turns right. when err > 0 turns left
		motor.speed(leftMotor, motorWheelSpeed - err);
		motor.speed(rightMotor, motorWheelSpeed + err);
	}
}