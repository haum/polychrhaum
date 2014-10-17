#ifndef POLYCHRHAUM_HMI_LEDS_H
#define POLYCHRHAUM_HMI_LEDS_H

#ifdef BUILD_PC
struct CRGB { unsigned char r, g, b; };
#else
#include <FastLED.h>
#endif

namespace polychrhaum {

class PolychrHAUMcommon; // Forward declaration

class HmiLedsCommon {
	public:
		/** Constructor
		  * @param p PolychrHAUM instance
		  */
		HmiLedsCommon(PolychrHAUMcommon & p) : polychrhaum(p) {}

		/** Init leds controller **/
		void init();

		/** Clears all leds **/
		void clear();

		/** Set a led color
		  * @param [in] led Led number
		  * @param [in] r   Red intensity   [0-255]
		  * @param [in] g   Green intensity [0-255]
		  * @param [in] b   Blue intensity  [0-255]
		  */
		void set_rgb(int led, unsigned char r, unsigned char g, unsigned char b);

		/** Set global brightness value
		  * @param value Brightness [0-255]
		  */
		void set_brightness(unsigned char value);

		/** Update leds status **/
		void update();

	protected:
		CRGB * ledvalues; /// Pointer to values

	private:
		PolychrHAUMcommon & polychrhaum; /// PolychrHAUM instance
		unsigned char brightness; /// Gloabl brightness [0-255]
};

/** Leds interface **/
template <int FULLSIZE, int PIN_LEDDATA>
class HmiLeds : public HmiLedsCommon {
	public:
		/** Constructor
		  * @param p PolychrHAUM instance
		  */
		HmiLeds(PolychrHAUMcommon & p) : HmiLedsCommon(p) {
			ledvalues = theleds;
#ifndef BUILD_PC
			FastLED.addLeds<NEOPIXEL, PIN_LEDDATA>(theleds, sizeof(theleds)/sizeof(*theleds));
#endif
		}

	private:
		CRGB theleds[FULLSIZE]; /// Real led color storage
};

};

#endif
