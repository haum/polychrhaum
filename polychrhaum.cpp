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

void PolychrHAUM::setup(unsigned int fullsize, CFastLED * fleds) {
	if (fullsize == 0)
		fullsize = fleds->size();

	halfsize = (fullsize - 1) / 2;

	btn1.init();
	btn2.init();
	btn_power.init();
	power.init();
	leds.init(fleds);
#ifndef BUILD_PC
	pinMode(pin_btn1, INPUT_PULLUP);
	pinMode(pin_btn2, INPUT_PULLUP);
	pinMode(pin_power_btn, INPUT_PULLUP);
	Serial.begin(115200);
#endif
	last_btn_time = millis();
	last_frame_time = millis();
}

void PolychrHAUM::loop_step() {
	long time = millis();

	// Compute button press
	if (time >= last_btn_time + polychrhaum::dtms / 4) {
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
	if (time >= last_frame_time + polychrhaum::dtms + adj_time) {
		last_frame_time = time;

		// Power management
		if (!power.is_powered()) {
			if (btn_power.touched() || btn1.touched() || btn2.touched())
				power.poweron();
		} else {
			if (btn_power.slpressed())
				power.poweroff();
		}

		// Potentiometers
#ifndef BUILD_PC
		if (pin_pot_light >= 0) {
			int val = analogRead(pin_pot_light) >> 2;
			leds.set_brightness(val);
		}
		if (pin_pot_speed >= 0) {
			int val = analogRead(pin_pot_speed);
			adj_time = (1 - (val / 640.0)) * polychrhaum::dtms * 3 - polychrhaum::dtms / 2;
			if (val > 640)
				adj_time = 0;
		}
#endif
		// Animation
		leds.update();
		leds.clear();
		if (fct_animate)
			fct_animate();

		// Reset buttons reports
		btn1.endframe();
		btn2.endframe();
		btn_power.endframe();
	}
}

void PolychrHAUM::log(const char *msg) {
#ifdef BUILD_PC
        printf("%s", msg);
#else
        Serial.print(msg);
#endif
}

void PolychrHAUM::log(int msg) {
#ifdef BUILD_PC
        printf("%d", msg);
#else
        Serial.print(msg);
#endif
}

