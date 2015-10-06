#ifndef POLYCHRHAUM_HMI_LEDS_H
#define POLYCHRHAUM_HMI_LEDS_H

#ifdef BUILD_PC
struct CRGB { unsigned char r, g, b; };
#else
#include <FastLED.h>
#endif

class PolychrHAUM; // Forward declaration

namespace polychrhaum {

class HmiLeds {
	public:
		/** Constructor
		  * @param p PolychrHAUM instance
		  * @param leds pointer to CFastLED
		  */
		HmiLeds(PolychrHAUM & p) : polychrhaum(p) {}

		/** Init leds controller **/
		void init(CFastLED*);

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
		PolychrHAUM & polychrhaum; /// PolychrHAUM instance
		unsigned char brightness; /// Gloabl brightness [0-255]
		CFastLED * fleds; /// Pointer to FastLED instance
};

};

#endif
