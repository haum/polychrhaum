#include "hmi_supply.h"

#ifdef BUILD_PC
extern bool pc_powered;
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
#endif
	powered = false;
#ifdef BUILD_PC
	pc_powered = powered;
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
#endif
	powered = true;
#ifdef BUILD_PC
	pc_powered = powered;
#endif
}

void HmiSupply::poweroff() {
#ifndef BUILD_PC
	digitalWrite(pin_power_cmd, HIGH);
	if (pin_power_status >= 0)
		while(digitalRead(pin_power_status) == HIGH);
#endif
	powered = false;
#ifdef BUILD_PC
	pc_powered = powered;
#endif
}

};

