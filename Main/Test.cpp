// Test.cpp

#include "Test.h"
#include "Globals.h"
#include "Helpers.h"
#include <Arduino.h>
#include "Menu.h"



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
        Serial.print("Claw IR: "); Serial.println(clawIRTriggered());
        delay(4000);

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
	LCD.clear(); LCD.print("Testing PID "); LCD.setCursor(0, 1); LCD.print("QRD's"); delay(1000);
	while(!startbutton()) {
		testPidQRDSensors();
		delay(100);
	}
	LCD.clear(); LCD.print("Testing Cliff "); LCD.setCursor(0, 1); LCD.print("QRD's"); delay(1000);
	while(!stopbutton()) {
		testCliffQRD();
		delay(100);
	}
	LCD.clear(); LCD.print("Testing Dumper"); delay(1000);
	while(!startbutton()) {
		testDump();
	}
	LCD.clear(); LCD.print("Testing Claw"); delay(1000);
	while(!stopbutton()) {
		testClaw();
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

void testDump() {
	LCD.clear(); LCD.print("Reset");
	resetDumper();
	delay(2000);
	LCD.clear(); LCD.print("Dump");
	activateDumper();
	delay(2000);

}

void testClaw() {	
	// bool triggered = clawIRTriggered();
	// LCD.clear(); LCD.print("Claw IR triggered: "); LCD.print(triggered);
	// if(triggered) {
	// 	claw.grab();
	// 	delay(1000);
	// 	setServo(clawDumpServo, 8);
	// 	delay(1000);
	// 	setServo(clawGrabServo, 18); 
	// 	delay(1000);
	// 	setServo(clawDumpServo, 125);
	// 	delay(1000);
	// }
}



