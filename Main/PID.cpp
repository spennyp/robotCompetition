// PID.cpp

#include "PID.h"
#include "Globals.h"

const int8_t left = -1, straight = 0, right = 1;

PID::PID(MenuItem pGain, MenuItem dGain, MenuItem PIDThreshold) {
	threshold = PIDThreshold.value;
	p = pGain.value;
	d = dGain.value;
}

int8_t PID::getState() {
	lastState = state;
	int nearSensor = analogRead(nearTapeFollowQRD);
	int farSensor = analogRead(farTapeFollowQRD);
	if(nearSensor <= threshold && farSensor >= threshold) {
		state = straight;
	} else if(nearSensor < threshold && farSensor <= threshold) {
		state = left;
	} else if(nearSensor >= threshold && farSensor > threshold) {
		state = right;
	} else {
		state = lastState;
	}
	return state;
}

int16_t PID::getError() {
	int16_t pErr = 0, dErr = 0;
	int16_t err = 0;
	int8_t state = getState();
	pErr = p * (state);
	dErr = d * (state - lastState);
	err = pErr + dErr;
	return err;
}



