#include "hmi_supply.h"

#ifdef BUILD_PC
#else
#include <Arduino.h>
#endif

namespace polychrhaum {

void HmiSupply::config(int cmd, int status) {
	pin_power_cmd = cmd;
	pin_power_status = status;
}

void HmiSupply::init() {
#ifndef BUILD_PC
	digitalWrite(pin_power_cmd, HIGH);
	pinMode(pin_power_cmd, OUTPUT);
	pinMode(pin_power_status, INPUT);
	powered = false;
#endif
}

bool HmiSupply::is_powered() {
	return powered;
}

void HmiSupply::poweron() {
#ifndef BUILD_PC
	digitalWrite(pin_power_cmd, LOW);
	if (pin_power_status >= 0)
		while(digitalRead(pin_power_status) == LOW);
	powered = true;
#endif
}

void HmiSupply::poweroff() {
#ifndef BUILD_PC
	digitalWrite(pin_power_cmd, HIGH);
	if (pin_power_status >= 0)
		while(digitalRead(pin_power_status) == HIGH);
	powered = false;
#endif
}

};

