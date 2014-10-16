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
	btn1.init();
	btn2.init();
	btn_power.init();
#ifndef BUILD_PC
	pinMode(pin_btn1, INPUT_PULLUP);
	pinMode(pin_btn2, INPUT_PULLUP);
	pinMode(pin_power_status, INPUT);
	pinMode(pin_power_btn, INPUT_PULLUP);
	digitalWrite(pin_power_cmd, LOW);
	pinMode(pin_power_cmd, OUTPUT);
	Serial.begin(115200);
#endif
	last_btn_time = millis();
	last_frame_time = millis();
}

void PolychrHAUMcommon::loop_step() {
	long time = millis();

	// Compute button press
	if (time >= last_btn_time + dtms / 4) {
		last_btn_time = time;
#ifdef BUILD_PC
		btn_power.compute(pc_btn_pwr);
		btn1.compute(pc_btn_1);
		btn2.compute(pc_btn_2);
#else
		btn_power.compute(!digitalRead(pin_power_btn));
		btn1.compute(!digitalRead(pin_btn1));
		btn2.compute(!digitalRead(pin_btn2));
#endif
	}

	// Compute animation
	if (time >= last_frame_time + dtms) {
		last_frame_time = time;

		// Animation
		if (fct_animate)
			fct_animate();

		// Reset buttons reports
		btn1.endframe();
		btn2.endframe();
		btn_power.endframe();
	}
}

};

