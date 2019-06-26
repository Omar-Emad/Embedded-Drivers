
/******************************************************************
 *
 * File Name: adc.c
 *
 * Author: Omar Emad
 *
 * Date Created: 20/9/2018
 *
 * Description: Source file of ADC module
 *
 *******************************************************************/

#include "adc.h"

/*******************************************************************
 *                   Interrupt Service Routines 				   *
 *******************************************************************/


/*******************************************************************
 *                    Functions Definitions                        *
 *******************************************************************/

void ADC_init (const ADC_configType * config_ptr)
{
	ADMUX = (ADMUX & 0x3F) | ((config_ptr->Vref)<<6);

	ADCSRA |= (1<<ADEN) | (1<<ADATE);
	ADCSRA = (ADCSRA & 0xF7) | ((config_ptr->interruptEnable)<<ADIE);
	ADCSRA = (ADCSRA & 0xF8) | (config_ptr->prescaler);
	SFIOR = (SFIOR & 0x1F) | ((config_ptr->trigger)<<5);
}

uint16 ADC_readChannel(const uint8 a_chNum)
{
	ADCSRA |= (1<<ADEN);
	ADMUX = (ADMUX & ~(0x1F)) | a_chNum;
	ADCSRA |= (1<<ADSC);
	while(  BIT_IS_CLEAR(ADCSRA,ADIF))
		{};
	SET_BIT(ADCSRA,ADIF);

	return (ADC & 0x3FF);
}

void ADC_disable (void)
{
	ADCSRA &= ~(1<<ADEN);
}

