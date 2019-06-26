/**********************************************************
 *
 * File Name: icu.c
 *
 * Author: Omar Emad
 *
 * Date Created: 20/9/2018
 *
 * File Description: The source file for ICU driver
 *
 **********************************************************/

#include "icu.h"

/**********************************************************
 * 				   Global Variables                       *
 **********************************************************/

/* Global variables to hold the address of the call back function */
static volatile void (*g_callBackPtr)(void) = '\0';

/************************************************************
 *                Interrupt Service Routines                *
 ************************************************************/

ISR(TIMER1_CAPT_vect)
{
	if(g_callBackPtr != '\0')
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}

/**********************************************************
 *                 Functions Definitions                  *
 **********************************************************/

void ICU_init (ICU_configType *config_ptr)
{
	DDRD &= ~(1<<PD6);

	TCCR1A = (1<<FOC1A) | (1<<FOC1B);
	TCCR1B = (TCCR1B & 0xF8) | (config_ptr->prescaler);
	TCCR1B = (TCCR1B & 0xBF) | ((config_ptr->edge)<<6);
	TCNT1 = 0;
	ICR1 = 0;
	TIMSK = ( TIMSK & 0xDF) | (config_ptr->interruptEnable <<5);
}

uint16 ICU_getInputCaptureValue(void)
{
	return ICR1;
}

void ICU_clearTimerValue(void)
{
	TCNT1 = 0;

}

void ICU_setEdgeDetectionType(const ICU_edgeType edgeType)
{
	TCCR1B = (TCCR1B & 0xBF) | (edgeType << 6);
}

void ICU_setCallBack (void (*a_callBackptr)(void))
{
	g_callBackPtr = a_callBackptr;
}

void Icu_DeInit(void)
{
	/* Clear All Timer1 Registers */
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1 = 0;
	ICR1 = 0;

	/* Disable the Input Capture interrupt */
	TIMSK &= ~(1<<TICIE1);
}
