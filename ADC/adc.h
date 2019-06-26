
/******************************************************************
 *
 * File Name: adc.h
 *
 * Author: Omar Emad
 *
 * Date Created: 20/9/2018
 *
 * Description: Header file of ADC module
 *
 *******************************************************************/

#ifndef ADC_H_
#define ADC_H_

#include "micro_config.h"
#include "common_macros.h"
#include "std_types.h"

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/

/* reference voltage for ADC */
/* AREF: internal 5 v
 * AVCC: any external voltage
 * Internal_2_5 internal 2.56 voltage
 */
typedef enum
{
	AREF=0, AVCC=1, Internal_2_5=3
}ADC_refernceVoltage;

typedef enum
{
	clock_2=1, clock_4, clock_8, clock_16, clock_32, clock_64, clock_128
}ADC_prescaler;

/* no_trigger: start conversion only when ADSC bit is high
 * external_interrupt: when there is external interrupt 0
 * timer_0_compare: when there is compare match in timer 0
 * timer_1_compare: when there is compare match in timer 1 channel B
 */
typedef enum
{
	no_trigger=0, external_interrupt=2, timer_0_compare=3, timer_1_compare=5
}ADC_autoTrigger;

/* configuration structure for ADC module */
typedef struct
{
	ADC_refernceVoltage Vref;
	ADC_prescaler prescaler;
	ADC_autoTrigger trigger;
	bool interruptEnable;
}ADC_configType;

/*******************************************************************
 *                   Functions Prototypes                          *
 *******************************************************************/

void ADC_init (const ADC_configType * config_ptr);
uint16 ADC_readChannel (const uint8 channelNum);
void ADC_disable (void);

#endif /* ADC_H_ */
