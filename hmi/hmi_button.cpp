#include "hmi_button.h"

namespace polychrhaum {

void HmiButton::init() {
	state = HmiButtonState_NOTHING;
	press = HmiButtonPress_NOTHING;
	timer = 0;
}

bool HmiButton::released() {
	return (press == HmiButtonPress_NOTHING && state == HmiButtonState_NOTHING);
}

bool HmiButton::sclicked() {
	return (press == HmiButtonPress_CLICKED1);
}

bool HmiButton::spressed(bool still) {
	return (
		(press == HmiButtonPress_PRESSED1) ||
		(still && (state == HmiButtonState_SIMPLE_PRESSED || state == HmiButtonState_SIMPLE_LONGPRESSED))
	);
}

bool HmiButton::stouched(bool still) {
	return (sclicked() || spressed(still));
}

bool HmiButton::slpressed(bool still) {
	return (
		(press == HmiButtonPress_LONGPRESSED1) ||
		(still && state == HmiButtonState_SIMPLE_LONGPRESSED)
	);
}

bool HmiButton::dclicked() {
	return (press == HmiButtonPress_CLICKED2);
}

bool HmiButton::dpressed(bool still) {
	return (
		(press == HmiButtonPress_PRESSED2) ||
		(still && (state == HmiButtonState_DOUBLE_PRESSED || state == HmiButtonState_DOUBLE_LONGPRESSED))
	);
}

bool HmiButton::dtouched(bool still) {
	return (dclicked() || dpressed(still));
}

bool HmiButton::dlpressed(bool still) {
	return (
		(press == HmiButtonPress_LONGPRESSED2) ||
		(still && state == HmiButtonState_DOUBLE_LONGPRESSED)
	);
}

bool HmiButton::touched(bool still) {
	return (stouched(still) || dtouched(still));
}

void HmiButton::endframe() {
	press = HmiButtonPress_NOTHING;
}

void HmiButton::compute(bool value) {
	timer += 2 * value - 1;
	switch (state) {
		case HmiButtonState_NOTHING:
			if (timer < 0) {
				timer = 0;
			} else if (timer == 4) {
				timer = 0;
				state = HmiButtonState_SIMPLE_STARTED;
			}
			break;

		case HmiButtonState_SIMPLE_STARTED:
			if (timer == 8) {
				state = HmiButtonState_SIMPLE_PRESSED;
				press = HmiButtonPress_PRESSED1;
				timer = 0;
			} else if (timer == -3) {
				state = HmiButtonState_SIMPLE_ALMOSTRELEASED;
				timer = 0;
			}
			break;

		case HmiButtonState_SIMPLE_ALMOSTRELEASED:
			if (timer == 8) {
				state = HmiButtonState_DOUBLE_STARTED;
				timer = 0;
			} else if (timer == -25) {
				state = HmiButtonState_NOTHING;
				press = HmiButtonPress_CLICKED1;
				timer = 0;
			}
			break;

		case HmiButtonState_DOUBLE_STARTED:
			if (timer == 8) {
				state = HmiButtonState_DOUBLE_PRESSED;
				press = HmiButtonPress_PRESSED2;
				timer = 0;
			} else if (timer == -3) {
				state = HmiButtonState_DOUBLE_ALMOSTRELEASED;
				timer = 0;
			}
			break;

		case HmiButtonState_DOUBLE_ALMOSTRELEASED:
			if (timer == 8) {
				state = HmiButtonState_DOUBLE_PRESSED;
				timer = 0;
			} else if (timer == -8) {
				state = HmiButtonState_NOTHING;
				press = HmiButtonPress_CLICKED2;
				timer = 0;
			}
			break;

		case HmiButtonState_SIMPLE_PRESSED:
			if (timer > 80) {
				state = HmiButtonState_SIMPLE_LONGPRESSED;
				press = HmiButtonPress_LONGPRESSED1;
				timer = 0;
			} else if (timer == -10) {
				state = HmiButtonState_NOTHING;
				timer = 0;
			}
			break;

		case HmiButtonState_DOUBLE_PRESSED:
			if (timer > 80) {
				state = HmiButtonState_DOUBLE_LONGPRESSED;
				press = HmiButtonPress_LONGPRESSED2;
				timer = 0;
			} else if (timer == -10) {
				state = HmiButtonState_NOTHING;
				timer = 0;
			}
			break;

		case HmiButtonState_SIMPLE_LONGPRESSED:
		case HmiButtonState_DOUBLE_LONGPRESSED:
			if (timer > 0) {
				timer = 0;
			} else if (timer == -10) {
				state = HmiButtonState_NOTHING;
				timer = 0;
			}
			break;
	}
}

};

