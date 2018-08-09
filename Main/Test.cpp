// Test.cpp

#include "Test.h"
#include "Globals.h"
#include "Helpers.h"
#include "MotorWheel.h"
#include "Claw.h"

extern Claw claw;
extern MotorWheel motorWheel;
bool grabbedInTest = false;


// Diagnositcs

void systemDiagnostics() {
    LCD.clear(); LCD.print("Diagnostics"); 
    LCD.setCursor(0,1); LCD.print("Exit -> HoldStop");
    while(true) {
        Serial.println("");
        Serial.println("");
        Serial.print("Top hall: "); Serial.println(topHallTriggered());
        Serial.print("Bottom hall: "); Serial.println(bottomHallTriggered());
        Serial.print("Left Touch: "); Serial.println(rightTouchTriggered());
		Serial.print("Right Touch: "); Serial.println(leftTouchTriggered());
        Serial.print("Far QRD: "); Serial.println(analogRead(farTapeFollowQRD));
        Serial.print("Near QRD: "); Serial.println(analogRead(nearTapeFollowQRD));
        Serial.print("Cliff QRD: "); Serial.println(analogRead(cliffQRD));
        Serial.print("Claw IR: "); Serial.println(analogRead(clawIR));
        delay(1000);

        if (stopbutton()) {
			delay(100);
			if (stopbutton()) {
				LCD.clear(); LCD.print("Leaving "); LCD.setCursor(0, 1); LCD.print("Diagnositcs");
				delay(1000);
				return;
			}
		}
    }
}


// Sensor Test

void sensorTest() {
	LCD.clear(); LCD.print("Sensor Test"); delay(1000);

	LCD.clear(); LCD.print("PID QRD"); LCD.setCursor(0, 1); LCD.print("QRD's"); delay(1000);
	while(!startbutton()) {
		testPidQRD();
	}

	LCD.clear(); LCD.print("Cliff QRD"); delay(1000);
	while(!startbutton()) {
		testCliffQRD();
	}

	LCD.clear(); LCD.print("Side QRD"); delay(1000);
	while(!startbutton()) {
		testLeftSideQRD();
	}

	LCD.clear(); LCD.print("Claw IR "); LCD.setCursor(0, 1); LCD.print("Detector"); delay(1000);
	while(!startbutton()) {
		testClawIR();
	}

	LCD.clear(); LCD.print("Touch Sensor"); delay(1000);
	while(!startbutton()) {
		testTouchSensor();
	}

	LCD.clear(); LCD.print("Testing comIn"); delay(1000);
	while(!startbutton()) {
		testCommunicationIn();
	}

	LCD.clear(); LCD.print("Leaving Sensor"); LCD.setCursor(0, 1); LCD.print("Test"); delay(1000);
}

void testPidQRD() {
	LCD.clear(); LCD.print("FarQRD: "); LCD.print(analogRead(farTapeFollowQRD));
	LCD.setCursor(0,1); LCD.print("NearQRD: "); LCD.print(analogRead(nearTapeFollowQRD));
	delay(100);
}

void testCliffQRD() {
	LCD.clear(); LCD.print("CliffQRD: "); LCD.print(analogRead(cliffQRD));
	delay(100);
}

void testLeftSideQRD() {
	LCD.clear(); LCD.print("SideQRD: "); LCD.print(analogRead(leftSideQRD));
	delay(100);
}

void testClawIR() {
	LCD.clear(); LCD.print("ClawIR: "); LCD.print(analogRead(clawIR));
	delay(100);
}

void testTouchSensor() {
	LCD.clear(); LCD.print("Left Touch: "); LCD.print(leftTouchTriggered());
	LCD.setCursor(0, 1); LCD.print("Right Touch: "); LCD.print(rightTouchTriggered());
	delay(100);
}

void testCommunicationIn() {
	LCD.clear(); LCD.print("Com In: "); LCD.print(digitalRead(communicationIn));
	delay(100);
}


// System Test

void systemTest() {
	unsigned long prevLoopStartTime = millis();

	LCD.clear(); LCD.print("System Test"); LCD.setCursor(0, 1); LCD.print("Warning motors!!"); delay(1000);

	LCD.clear(); LCD.print("Test Dump Align"); delay(1000); // From 5th teddy

	while(!startbutton()) {
		resetDumper();
		delay(1000);
		setServo(clawDumpServo, 100);
		claw.close();
		delay(1000);
		while(!veerRight()) { delay(10); }
		motorWheel.runWithPID(80);
		while(!rightTouchTriggered() && !leftTouchTriggered()) { 
			motorWheel.poll(); 
			delay(10);
		}
		motorWheel.stop();
		delay(500);
		while(!alignTouchSensors()) { delay(100); }
		delay(1000);
		activateDumper();
		delay(5000);
	}


	LCD.clear(); LCD.print("Test Claw Bottom"); delay(1000);
	claw.reset();
	grabbedInTest = false;
	while(!startbutton()) {
		while (millis() - prevLoopStartTime < 10) {} //Regulate speed of the main loop to 10 ms
		prevLoopStartTime = millis();
		testClaw();
	}

	LCD.clear(); LCD.print("Claw bridge"); LCD.setCursor(0, 1); LCD.print("drop position"); delay(1000);
	claw = Claw();
	while(!startbutton()) {
		testClawBridgeDropPosition();
	}

	LCD.clear(); LCD.print("Test Claw Top"); delay(1000);
	claw.switchToTopBot();
	grabbedInTest = false;
	while(!startbutton()) {
		while (millis() - prevLoopStartTime < 10) {} //Regulate speed of the main loop to 10 ms
		prevLoopStartTime = millis();
		testClaw();
	}

	LCD.clear(); LCD.print("Reverse"); delay(1000);
	motorWheel.reverse(200);
	while(!startbutton()) {
		delay(10);
	}
	motorWheel.stop();

	LCD.clear(); LCD.print("Test Left Sweep"); delay(1000);
	while(!startbutton()) {
		testLeftSweep();
	}

	LCD.clear(); LCD.print("WARNING MOTORS"); LCD.setCursor(0, 1); LCD.print("in 3 sec"); delay(3000);
	LCD.clear(); LCD.print("Testing turning"); LCD.setCursor(0, 1); LCD.print("start -> next"); delay(1000);
	while(!startbutton()) {
		testTurning();
	}

	LCD.clear(); LCD.print("Hard stop"); LCD.setCursor(0, 1); LCD.print("start -> next"); delay(1000);
	while(!startbutton()) {
		testHardStop();
	}

	LCD.clear(); LCD.print("Testing Bridge"); delay(1000);
	while(!startbutton()) {
		testBridge();
	}

	LCD.clear(); LCD.print("Testing Dumper"); delay(1000);
	while(!startbutton()) {
		testDump();
	}

	LCD.clear(); LCD.print("Leaving system"); LCD.setCursor(0, 1); LCD.print("testing"); delay(1000);
}

void testDump() {
	LCD.clear(); LCD.print("Reset");
	resetDumper();
	delay(2000);
	if(startbutton()) { return; }
	LCD.clear(); LCD.print("Dump"); 
	activateDumper();
	delay(2000);
}

void testClaw() {	
	bool triggered = clawIRTriggered();
	LCD.clear(); LCD.print("IR Triggered: "); LCD.print(triggered);
	if(triggered && !grabbedInTest) {
		grabbedInTest = true;
		claw.grab();
	}
	if(claw.poll()) {
		grabbedInTest = false;
	}
}

void testClawBridgeDropPosition() {
	claw.reset();
	delay(2000);
	if(startbutton()) { return; }
	claw.positionForBridgeDrop();
	delay(2000);
}

void testBridge() {
	LCD.clear(); LCD.print("Reset");
	resetBridge();
	delay(2000);
	if(startbutton()) { return; }
	LCD.clear(); LCD.print("Deploy");
	deployBridge();
	delay(2000);
}

void testTurning() {
	motorWheel.turnRight(90);
	delay(1000);
	if(startbutton()) { return; }
	motorWheel.turnLeft(90);
	delay(1000);
}

void testLeftSweep() {
	while(!sweepLeft()) { delay(10); }
	delay(5000);
}

void testHardStop() {
	motorWheel.forward(200);
	delay(1000);
	if(startbutton()) { return; }
	motorWheel.hardStop();
	delay(1000);
	if(startbutton()) { return; }
	motorWheel.reverse(200);
	delay(1000);
	if(startbutton()) { return; }
	motorWheel.hardStop(false);
	delay(1000);
}




