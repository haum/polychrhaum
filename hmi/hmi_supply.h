#ifndef POLYCHRHAUM_HMI_SUPPLY_H
#define POLYCHRHAUM_HMI_SUPPLY_H

namespace polychrhaum {

/** Power supply interface **/
class HmiSupply {
	public:
		/** Constructor **/
		HmiSupply() :
			pin_power_cmd(-1),
			pin_power_status(-1),
			powered(false) {}

		/** Configure on which pins power management is connected
		  * @param cmd    Pin of command signal
		  * @param status Pin of status signal
		  */
		void config(int cmd, int status);

		/** Init alim controller **/
		void init();

		/** Is ledstrip powered
		  * @return true when powered
		  */
		bool is_powered();

		/** Power alim on **/
		void poweron();

		/** Power alim off **/
		void poweroff();

	private:
		int pin_power_cmd,    /// Power command pin
		    pin_power_status; /// Power status pin

		bool powered; /// Is device currently powered
};

};

#endif
