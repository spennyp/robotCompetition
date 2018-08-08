#include "Menu.h"
#include <phys253.h>
#include "Globals.h"
#include "Helpers.h"

void setup() {
	#include <phys253setup.txt>
	Serial.begin(9600);
	LCD.clear(); LCD.print("Uploaded");
	LCD.setCursor(0, 1); LCD.print("TURN ON SENSORS!");

	// Swithing first row of digital ins to outs
	pinMode(0, OUTPUT);
	pinMode(1, OUTPUT);
	pinMode(2, OUTPUT);
	pinMode(3, OUTPUT);
	pinMode(4, OUTPUT);
	pinMode(5, OUTPUT);
	pinMode(6, OUTPUT);
	pinMode(7, OUTPUT);
	softReset();
	delay(2000);
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