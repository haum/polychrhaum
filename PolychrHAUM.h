#ifndef POLYCHRHAUM_POLYCHRHAUM_H
#define POLYCHRHAUM_POLYCHRHAUM_H

namespace polychrhaum {

/** Basic animation period **/
const int dtms = 16;

/** PolychrHAUM controller class (non template dependant part) **/
class PolychrHAUMcommon {
	public:
		/** Build object **/
		PolychrHAUMcommon() :
			pin_btn1(-1),
			pin_btn2(-1),
			pin_power_btn(-1),
			pin_power_cmd(-1),
			pin_power_status(-1),
			pin_pot_light(-1),
			pin_pot_speed(-1),
			last_frame_time(0),
			fct_animate(0) {}

		/** Get number of leds of each side [-HALF_WIDTH:HALF_WIDTH] **/
		virtual int get_halfsize() = 0;

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
			pin_power_cmd = cmd;
			pin_power_status = status;
			pin_power_btn = btn;
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
		void setup();

		/** Non blocking loop
		  * @note Should be called as often as possible
		  */
		void loop_step();

	private:
		int pin_btn1,         /// Button 1 pin
		    pin_btn2,         /// Button 2 pin
		    pin_power_btn,    /// Power button pin
		    pin_power_cmd,    /// Power command pin
		    pin_power_status, /// Power status pin
		    pin_pot_light,    /// Light potentiometer pin
		    pin_pot_speed;    /// Speed potentiometer pin

		long last_frame_time; /// Time of last frame

		void (*fct_animate)(); /// Animation function
};

};

/** PolychrHAUM controller class
  * @param FULLSIZE    Number of total leds
  * @param PIN_LEDDATA Pin on which ledstrip data line is driven
  */
template <int FULLSIZE, int PIN_LEDDATA>
class PolychrHAUM : public polychrhaum::PolychrHAUMcommon {
	public:
		int get_halfsize() { return (FULLSIZE-1) / 2; }
};

#endif

