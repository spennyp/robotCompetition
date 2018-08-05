// Test.cpp

#include "Test.h"
#include "Globals.h"
#include "Helpers.h"
#include "MotorWheel.h"
#include "Claw.h"

Claw testClawInstance;
MotorWheel testMotorWheel(motorSpeed, PID(proportionalGain, derivativeGain, pidThreshold));
bool grabbed = false;

void systemDiagnostics() {
    LCD.clear(); LCD.print("Diagnostics"); 
    LCD.setCursor(0,1); LCD.print("Exit -> HoldStop");
    while(true) {
        Serial.println("");
        Serial.println("");
        Serial.print("Top hall: "); Serial.println(topHallTriggered());
        Serial.print("Bottom hall: "); Serial.println(bottomHallTriggered());
        Serial.print("Front Touch: "); Serial.println(frontTouchSensorTriggered());
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

void testFullSystem() {
	unsigned long prevLoopStartTime = millis();
	testClawInstance = Claw();

	LCD.clear(); LCD.print("Test edgeSensors"); LCD.setCursor(0, 1); LCD.print("QRD's"); delay(1000);
	while(!startbutton()) {
		testPidQRDSensors();
		delay(100);
	}

	// LCD.clear(); LCD.print("Testing PID"); LCD.setCursor(0, 1); LCD.print("stop -> next"); delay(1000);
	// testMotorWheel.runWithPID = true;
	// while(!stopbutton()) {
	// 	while (millis() - prevLoopStartTime < 10) {} //Regulate speed of the main loop to 10 ms
	// 	prevLoopStartTime = millis();
	// 	testMotorWheel.poll();
	// }

	// LCD.clear(); LCD.print("Testing turning"); LCD.setCursor(0, 1); LCD.print("start -> next"); delay(1000);
	// while(!startbutton()) {
	// 	testTurning();
	// }

	LCD.clear(); LCD.print("Testing Claw IR "); LCD.setCursor(0, 1); LCD.print("Detector"); delay(1000);
	while(!stopbutton()) {
		testClawIR();
		delay(100);
	}

	LCD.clear(); LCD.print("Testing Cliff "); LCD.setCursor(0, 1); LCD.print("QRD's"); delay(1000);
	while(!startbutton()) {
		testCliffQRD();
		delay(100);
	}

	LCD.clear(); LCD.print("Testing Dumper"); delay(1000);
	while(!startbutton()) {
		testDump();
	}


	LCD.clear(); LCD.print("Test Claw Bottom"); delay(1000);
	testClawInstance.reset();
	grabbed = false;
	while(!stopbutton()) {
		while (millis() - prevLoopStartTime < 10) {} //Regulate speed of the main loop to 10 ms
		prevLoopStartTime = millis();
		testClaw();
	}

	LCD.clear(); LCD.print("Test Claw Top"); delay(1000);
	testClawInstance.switchToTopBot();
	grabbed = false;
	while(!stopbutton()) {
		while (millis() - prevLoopStartTime < 10) {} //Regulate speed of the main loop to 10 ms
		prevLoopStartTime = millis();
		testClaw();
	}

	LCD.clear(); LCD.print("Claw bridge drop"); delay(1000);
	while(!startbutton()) {
		testClawInstance.reset();
		delay(2000);
		if(startbutton()) { break; }
		testClawInstance.raiseForBridgeDrop();
		delay(2000);
	}

	LCD.clear(); LCD.print("Testing Bridge"); delay(1000);
	while(!startbutton()) {
		testBridge();
	}

	LCD.clear(); LCD.print("Leaving testing"); delay(1000);
}

void testPidQRDSensors() {
	LCD.clear(); LCD.print("FarQRD: "); LCD.print(analogRead(farTapeFollowQRD));
	LCD.setCursor(0,1); LCD.print("NearQRD: "); LCD.print(analogRead(nearTapeFollowQRD));
}

void testCliffQRD() {
	LCD.clear(); LCD.print("CliffQRD: "); LCD.print(analogRead(cliffQRD));
}

void testClawIR() {
	LCD.clear(); LCD.print("ClawIR: "); LCD.print(analogRead(clawIR));
}

void testDump() {
	LCD.clear(); LCD.print("Reset"); LCD.setCursor(0, 1); LCD.print("start -> next");
	resetDumper();
	delay(2000);
	LCD.clear(); LCD.print("Dump"); LCD.setCursor(0, 1); LCD.print("start -> next");
	activateDumper();
	delay(2000);
}

void testClaw() {	
	bool triggered = clawIRTriggered();
	LCD.clear(); LCD.print("IR Triggered: "); LCD.print(triggered);
	LCD.setCursor(0, 1); LCD.print("stop -> next");
	if(triggered && !grabbed) {
		grabbed = true;
		testClawInstance.grab();
	}
	if(testClawInstance.poll()) {
		grabbed = false;
	}
}

void testTurning() {
	// testMotorWheel.turnRight(90);
	// delay(1000);
	// if(startbutton()) { return; }
	testMotorWheel.turnLeft(90);
	delay(1000);
	// if(startbutton()) { return; }
	// testMotorWheel.turnRight(180);
	// delay(1000);
	// if(startbutton()) { return; }
	// testMotorWheel.turnLeft(180);
	// delay(1000);
}

void testBridge() {
	LCD.clear(); LCD.print("Reset"); LCD.setCursor(0, 1); LCD.print("start -> end");
	resetBridge();
	delay(15000);
	LCD.clear(); LCD.print("Deploy"); LCD.setCursor(0, 1); LCD.print("start -> end");
	deployBridge();
	delay(2000);
}



