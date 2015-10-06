#ifndef POLYCHRHAUM_POLYCHRHAUM_H
#define POLYCHRHAUM_POLYCHRHAUM_H

#include "animators/animators.h"
#include "hmi/hmi_supply.h"
#include "hmi/hmi_button.h"
#include "hmi/hmi_leds.h"

namespace polychrhaum {

/** Basic animation period **/
const int dtms = 40;

};

/** PolychrHAUM controller class **/
class PolychrHAUM {
	public:
		/** Build object **/
		PolychrHAUM() :
			leds(*this),
			pin_btn1(-1),
			pin_btn2(-1),
			pin_power_btn(-1),
			pin_pot_light(-1),
			pin_pot_speed(-1),
			halfsize(0),
			adj_time(0),
			last_frame_time(0),
			fct_animate(0) {}

		/** Get number of leds of each side [-HALF_WIDTH:HALF_WIDTH] **/
		int get_halfsize() { return halfsize; }

		/** Configure on which pins buttons are connected
		  * @param btn1 Pin of button 1
		  * @param btn2 Pin of button 2
		  */
		void config_buttons(int btn1, int btn2) {
			pin_btn1 = btn1;
			pin_btn2 = btn2;
		}

		/** Configure on which pins power management is connected
		  * @param cmd    Pin of command signal
		  * @param status Pin of status signal
		  * @param btn    Pin of power button
		  */
		void config_power(int cmd, int status, int btn) {
			pin_power_btn = btn;
			power.config(cmd, status);
		}

		/** Configure on which pin light control potentiometer is connected
		  * @param pin Pin of potentiometer
		  */
		void config_light_ctrl(int pin) {
			pin_pot_light = pin;
		}

		/** Configure on which pin speed control potentiometer is connected
		  * @param pin Pin of potentiometer
		  */
		void config_speed_ctrl(int pin) {
			pin_pot_speed = pin;
		}

		/** Configure which animation function to use
		  * @param fct Animation function
		  */
		void config_animate(void (*fct_ani)()) {
			fct_animate = fct_ani;
		}

		/** Initialization **/
		void setup(unsigned int fullsize = 0, CFastLED * fleds = &FastLED);

		/** Non blocking loop
		  * @note Should be called as often as possible
		  */
		void loop_step();

		/** Send message to console
		  * @param [in] msg Null-terminated c-string to send
		  */
		void log(const char *msg);

		/** Send number to console
		  * @param [in] msg Number to send
		  */
		void log(int msg);

		polychrhaum::HmiLeds leds; /// LEDs
		polychrhaum::HmiSupply power; /// Power supply interface
		polychrhaum::HmiButton btn1;  /// Button 1
		polychrhaum::HmiButton btn2;  /// Button 2

	private:
		int pin_btn1,         /// Button 1 pin
		    pin_btn2,         /// Button 2 pin
		    pin_power_btn,    /// Power button pin
		    pin_pot_light,    /// Light potentiometer pin
		    pin_pot_speed;    /// Speed potentiometer pin

		unsigned int halfsize; /// Half size

		char adj_time; /// Adjust timing loop

		long last_frame_time, /// Time of last frame
		     last_btn_time;   /// Time of last button computation

		void (*fct_animate)(); /// Animation function

		polychrhaum::HmiButton btn_power; /// Power button
};

#endif

