/*
 * FlexTimer.c
 *
 *  Created on: 25/03/2019
 *      Author: Charles
 *     brief: implementation of funcions in FlexTimer.h
 */
#include "FlexTimer.h"

void FlexTimer_update_channel_value(int16_t channel_value)
{
	/**Assigns a new value for the duty cycle*/
	FTM0->CONTROLS[0].CnV = channel_value;
}


void FlexTimer_Init(flexTimer_channels_t channel)
{

	/**Clock gating for FlexTimer*/
	SIM->SCGC6 |= SIM_SCGC6_FTM0(1);
	Fleximer_mode(CHANNEL_0,TOGGLE_OUTPUT_ON_MATCH ,TOGGLE_OUTPUT_ON_MATCH);
	FlexTimer_update_channel_value(0x03);
	FlexTimer_clockSource_and_prescaler(CHANNEL_0);
}
void Fleximer_mode(flexTimer_channels_t channel, flexTimer_modes_t mode, flexTimer_mode_configurations_t config)
{

	switch(mode)
	{
	case OUTPUT_COMPARE:
		/**It enable the FTM*/
		FTM0->MODE |= FTM_MODE_FTMEN_MASK;
		/**Selects the FTM behavior in BDM mode.In this case in functional mode*/
		FTM0->CONF |= FTM_CONF_BDMMODE(3);
		/**Assign modulo register with a predefined value*/
		FTM0->MOD = 0x05;
		/*setting channel on output compare mode*/
		FTM0->CONTROLS[0].CnSC = FTM_CnSC_MSA(1);

		/* setting  output compare configuration*/
		if( TOGGLE_OUTPUT_ON_MATCH== config)
			/**Configure FlexTimer in output compare in toggle mode*/
			FTM0->CONTROLS[0].CnSC =  FTM_CnSC_ELSA(1);

		else if(CLEAR_OUTPUT_ON_MATCH== config)
			/**Configure FlexTimer in output compare in clear output on match*/
			FTM0->CONTROLS[0].CnSC = FTM_CnSC_ELSB(1);

		else if(SET_OUTPUT_ON_MATCH== config)
			/**Configure FlexTimer in output compare  in set output on match*/
			FTM0->CONTROLS[0].CnSC =  FTM_CnSC_ELSB(1) | FTM_CnSC_ELSA(1);


		break;
	case TIMER_OVERFLOW:
		FTM0->MODE |= FTM_MODE_FTMEN_MASK;
		/**Selects the FTM behavior in BDM mode.In this case in functional mode*/
		FTM0->CONF |= FTM_CONF_BDMMODE(3);
		/**Assigning a default value for modulo register*/
		FTM0->MOD = 0xF0;
		/**Enabling the interrupt*/
		FTM0->SC |=  FTM_SC_TOIE(1);
		break;
	case PWM		   :
		/**When write protection is enabled (WPDIS = 0), write protected bits cannot be written.
		 * When write protection is disabled (WPDIS = 1), write protected bits can be written.*/
		FTM0->MODE |= FTM_MODE_WPDIS_MASK;
		/**Enables the writing over all registers*/
		FTM0->MODE &= ~ FTM_MODE_FTMEN_MASK;
		/**Assigning a default value for modulo register*/
		FTM0->MOD = 0x00FF;
		/**Selects the Edge-Aligned PWM mode mode*/
		FTM0->CONTROLS[0].CnSC = FTM_CnSC_MSB(1) | FTM_CnSC_ELSB(1);
		/**Assign a duty cycle of 50%*/
		FTM0->CONTROLS[0].CnV = FTM0->MOD/2;


		break;

	}

}
void FlexTimer_clockSource_and_prescaler(flexTimer_channels_t channel)
{
	switch(channel)
	{
	case CHANNEL_0:
		FTM0->SC |= FTM_SC_CLKS(FLEX_TIMER_CLKS_1)| FTM_SC_PS(FLEX_TIMER_PS_128);
		break;
	default:
		break;
	}


}


