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
#include "switches_k64.h"
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
	init_sw2(NO_PRIORITY_TH,NO_PRIORITY,NO_INT_EDGE_DEFINED);
	/*    priority threshold=10,priority number 4, interrupt launched as button is pressed */
	init_sw3(NO_PRIORITY_TH,NO_PRIORITY,NO_INT_EDGE_DEFINED);

	//this varaibles are incremented by sw3 and sw3
	uint16_t module=20;
	uint16_t CnValue=16;
	for(;;) {
		sw2_pressed();//reads sw2 state
		sw3_pressed();//read sw3 state

		if(sw2_one_shot())
		{
			module--;
			CnValue--;
			FlexTimer_mod(CHANNEL_0, module);
			FlexTimer_update_channel_value(CnValue);
		}
		sw3_pressed();//reads sw2 state

		if(sw3_one_shot())
		{
			module=module-3;
			CnValue=CnValue-3;
			FlexTimer_mod(CHANNEL_0, module);
			FlexTimer_update_channel_value(CnValue);
		}

	}

	return 0;
}
