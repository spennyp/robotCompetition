// MenuItem.cpp

#include "MenuItem.h"
#include <avr/EEPROM.h>

MenuItem::MenuItem(String _name) {
	menuItemCount++;
	EEPROMAddress = (uint16_t*)(2 * menuItemCount);
	name = _name;
	value = eeprom_read_word(EEPROMAddress);
}

void MenuItem::save() {
	eeprom_write_word(EEPROMAddress, value);
}
