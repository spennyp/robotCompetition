#include "Menu.h"
#include <phys253.h>

void setup() {
	#include <phys253setup.txt>
	Serial.begin(9600);
	LCD.clear();
	LCD.print("Uploaded :D");

	// Swithing first row of digital ins to outs
	pinMode(0, OUTPUT);
	pinMode(1, OUTPUT);
	pinMode(2, OUTPUT);
	pinMode(3, OUTPUT);
	pinMode(4, OUTPUT);
	pinMode(5, OUTPUT);
	pinMode(6, OUTPUT);
	pinMode(7, OUTPUT);
	delay(1000);
}

void loop() {
	LCD.clear(); LCD.home();
	LCD.print("Start -> RunMenu");
	LCD.setCursor(0, 1);
	LCD.print("Stop -> ConMenu");
	delay(100);

	if (stopbutton()) {
		delay(100);
		if (stopbutton()) {
			configurationMenu();
		}
	}
	else if (startbutton()) {
		delay(100);
		if (startbutton()) {
			LCD.clear();
			runMenu();
		}
	}
}
