#include "PolychrHAUM.h"

#ifdef BUILD_PC
#include <stdio.h>
long long millis();
extern int pc_btn_pwr;
extern int pc_btn_1;
extern int pc_btn_2;
#else
#include "Arduino.h"
#endif

namespace polychrhaum {

void PolychrHAUMcommon::setup() {
#ifndef BUILD_PC
	pinMode(pin_btn1, INPUT_PULLUP);
	pinMode(pin_btn2, INPUT_PULLUP);
	pinMode(pin_power_status, INPUT);
	pinMode(pin_power_btn, INPUT_PULLUP);
	digitalWrite(pin_power_cmd, LOW);
	pinMode(pin_power_cmd, OUTPUT);
	Serial.begin(115200);
#endif
	last_frame_time = millis();
}

void PolychrHAUMcommon::loop_step() {
	long time = millis();
	if (time >= last_frame_time + dtms) {
		last_frame_time = time;
		if (fct_animate)
			fct_animate();
	}
}

};

