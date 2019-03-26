/*
 * FlexTimer.h
 *
 *  Created on: 25/03/2019
 *      Author: Charles
 *      \brief
		This is the header file for the FlexTimer divice driver.
		Add configuration structures.
 */


#ifndef FLEXTIMER_H_
#define FLEXTIMER_H_


#include "MK64F12.h"

#define FLEX_TIMER_CLKS_0  (0U)
#define FLEX_TIMER_CLKS_1  (1U)
#define FLEX_TIMER_CLKS_2  (2U)
#define FLEX_TIMER_CLKS_3  (3U)


#define FLEX_TIMER_PS_1    (0U)
#define FLEX_TIMER_PS_2    (1U)
#define FLEX_TIMER_PS_4    (2U)
#define FLEX_TIMER_PS_8    (3U)
#define FLEX_TIMER_PS_16    (4U)
#define FLEX_TIMER_PS_32    (5U)
#define FLEX_TIMER_PS_64    (6U)
#define FLEX_TIMER_PS_128    (7U)


#define  FLEX_TIMER_DMA   0x01
#define  FLEX_TIMER_ELSA  0x04
#define  FLEX_TIMER_ELSB  0x08
#define  FLEX_TIMER_MSA   0x10
#define  FLEX_TIMER_MSB   0x20
#define  FLEX_TIMER_CHIE  0x40
#define  FLEX_TIMER_CHF   0x80

/*FLEX TIMER OPERATION MODES*/
typedef enum{
			OUTPUT_COMPARE,
			TIMER_OVERFLOW,
			PWM
			}flexTimer_modes_t;
/* FLEX TIMER CONFIGURATION OF OPERATION MODES*/
typedef enum{
			TOGGLE_OUTPUT_ON_MATCH,
			CLEAR_OUTPUT_ON_MATCH,
			SET_OUTPUT_ON_MATCH
			}flexTimer_mode_configurations_t;
/*FLEX TIMER CHANNELS*/
typedef enum{CHANNEL_0,
			CHANNEL_1,
			CHANNEL_2,
			CHANNEL_3
			}flexTimer_channels_t;


void FlexTimer_update_channel_value(int16_t channel_value);

/*brief for flex timer initialization in a specific mode from flexTimer_mode_t*/
/*channel argument still not implemented*/
void FlexTimer_Init(flexTimer_channels_t channel);
void Fleximer_mode(flexTimer_channels_t channel, flexTimer_modes_t mode, flexTimer_mode_configurations_t);

void FlexTimer_clockSource_and_prescaler(flexTimer_channels_t channel);

#endif /* FLEXTIMER_H_ */
