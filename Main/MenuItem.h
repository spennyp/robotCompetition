// MenuItem.h

#ifndef _MENUITEM_h
#define _MENUITEM_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class MenuItem {
	public:
		MenuItem(String name);
		static uint16_t menuItemCount;
		String name;
		uint16_t value;
		uint16_t* EEPROMAddress;
		void save();
};

#endif

