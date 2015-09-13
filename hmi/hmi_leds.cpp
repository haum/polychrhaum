#include "hmi_leds.h"
#include "../PolychrHAUM.h"

#ifdef BUILD_PC
#include <SDL2/SDL.h>
extern SDL_Surface * screen;
extern unsigned int pixel_size;
extern unsigned int pixel_jump;
extern bool pc_powered;
void pc_update_screen();
#else
#include <Arduino.h>
#include <FastLED.h>
#endif

namespace polychrhaum {

void HmiLedsCommon::init() {
	clear();
}

void HmiLedsCommon::clear() {
#ifdef BUILD_PC
	SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
#else
	memset(ledvalues, 0, (polychrhaum.get_halfsize() * 2 + 1) * sizeof(*ledvalues));
#endif
}

void HmiLedsCommon::set_rgb(int led, unsigned char r, unsigned char g, unsigned char b) {
	int hwidth = polychrhaum.get_halfsize();
	if (led < -hwidth || led > hwidth) return;
#ifdef BUILD_PC
	if (screen && pc_powered) {
		SDL_Rect led_rect;
		led_rect.x = (hwidth + led) * pixel_jump;
		led_rect.y = (100 - pixel_size) / 2;
		led_rect.w = pixel_size;
		led_rect.h = pixel_size;
		SDL_FillRect(screen, &led_rect, SDL_MapRGB(screen->format, r, g, b));
	}
#else
	ledvalues[led + hwidth].r = r * brightness / 255.0;
	ledvalues[led + hwidth].b = b * brightness / 255.0;
	ledvalues[led + hwidth].g = g * brightness / 255.0;
#endif
}

void HmiLedsCommon::set_brightness(unsigned char value) {
	brightness = value;
}

void HmiLedsCommon::update() {
#ifdef BUILD_PC
	pc_update_screen();
#else
	FastLED.show(brightness);
#endif
}

};

