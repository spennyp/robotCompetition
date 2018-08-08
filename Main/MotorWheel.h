// Motor.h

#ifndef _MOTORWHEEL_h
#define _MOTORWHEEL_h
#include "PID.h"

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

class MotorWheel {
private:
	uint16_t motorWheelSpeed;
	uint16_t menuMotorSpeed;
	PID pid;
	bool runningWithPID;
public:
	MotorWheel(MenuItem speed, PID pid);
	void turnLeft(int angle, bool backup = true);
	void turnRight(int angle, bool backup = true);
	void forward(int speed = 0);
	void reverse(int speed = 0);
	void stop();
	void hardStop(bool goingForward = true);
	void runWithPID(int speed = 0);
	void poll();
};

#endif