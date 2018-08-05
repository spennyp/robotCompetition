// Motor.cpp

#include "MotorWheel.h"
#include "Globals.h"

const int defualtTurnSpeed = 150;

MotorWheel::MotorWheel(MenuItem _motorSpeed, PID pid) : pid(pid) {
	motorSpeed = _motorSpeed.value;
	runWithPID = true;
}

// Default perapeter of 0, which runs at defualtTurnSpeed
void MotorWheel::turnLeft(int angle, int speed, bool backup) {
	runWithPID = false;
	int turnSpeed = (speed == 0) ? defualtTurnSpeed : speed;
	motor.speed(leftMotor, -turnSpeed);
	if(backup) {
		motor.speed(rightMotor, -turnSpeed);
		delay(400);
	}
	motor.speed(rightMotor, turnSpeed);
	delay(angle * delayPerDegreeTurn.value);
	stop();
}

// Default perapeter of 0, which runs at defualtTurnSpeed
void MotorWheel::turnRight(int angle, int speed, bool backup) {
	runWithPID = false;
	int turnSpeed = (speed == 0) ? defualtTurnSpeed : speed;
	motor.speed(rightMotor, -turnSpeed);
	if(backup) {
		motor.speed(leftMotor, -turnSpeed);
		delay(200);
	}
	motor.speed(leftMotor, turnSpeed);
	delay(angle * delayPerDegreeTurn.value);
	stop();
}

// Default perapeter of 0, which runs motorSpeed from the menu
void MotorWheel::forward(int speed) {
	runWithPID = false;
	if(speed == 0) {
		motor.speed(leftMotor, motorSpeed);
		motor.speed(rightMotor, motorSpeed);
	} else {
		motor.speed(leftMotor, speed);
		motor.speed(rightMotor, speed);
	}
}

void MotorWheel::reverse() {
	runWithPID = false;
	motor.speed(leftMotor, -motorSpeed);
	motor.speed(rightMotor, -motorSpeed);
}

void MotorWheel::stop() {
	runWithPID = false;
	motor.stop(rightMotor);
	motor.stop(leftMotor);
}


// Lifecycle

void MotorWheel::poll() {
	if(runWithPID) {
		int err = pid.getError();
		LCD.clear(); LCD.print("Speed: "); LCD.print(err);

		// when err < 0 turns right. when err > 0 turns left
		motor.speed(leftMotor, motorSpeed - err);
		motor.speed(rightMotor, motorSpeed + err);
	} 
}


