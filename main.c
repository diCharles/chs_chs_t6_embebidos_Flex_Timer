/**
	\file
	\brief
		This project shows how to configure FlexTimer in output compare mode.
	\author J. Luis Pizano Escalante, luispizano@iteso.mx
	\date	21/03/2019
	\todo
	    Add configuration structures.
 */


#include "MK64F12.h" /* include peripheral declarations */
#include "GPIO.h"
#include "FlexTimer.h"
#include "NVIC.h"
#include "Bits.h"
//#include "GlobalFunctions.h"

/**
 * Output compare frequency = (bus clock)/(Prescaler(mod+1)).
 * Note that is the same frequency of the overflow flow.
 */

int main(void)
{
	/** Configuration for pin 1 on port c.
	 * Output compare is on option 4 in the pin control register*/
	SIM->SCGC5 |= GPIO_CLOCK_GATING_PORTA | GPIO_CLOCK_GATING_PORTC;
	gpio_pin_control_register_t pin_control_register_bit_c_1 = GPIO_MUX4;
	GPIO_clock_gating(GPIO_C);
	GPIO_clock_gating(GPIO_A);
	GPIO_pin_control_register(GPIO_C, bit_1, &pin_control_register_bit_c_1);

	/**Initialization of FlexTimer in output compare mode*/
	FlexTimer_Init(CHANNEL_0);


	for(;;) {


	}

	return 0;
}
