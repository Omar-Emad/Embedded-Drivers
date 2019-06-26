/**********************************************************
 *
 * File Name: icu.c
 *
 * Author: Omar Emad
 *
 * Date Created: 27/9/2018
 *
 * File Description: The source file for UART driver
 *
 **********************************************************/

#include "uart.h"

#if(DOUBLE_SPEED==1)
	#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 8UL))) - 1)
#else
	#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)
#endif

/**********************************************************
 * 				   Global Variables                       *
 **********************************************************/

/* Global variables to hold the address of the call back function
 * of the RX interrupt */
static volatile void (*g_UART_RXcallBackPtr)(void) = '\0';
/* Global variables to hold the address of the call back function
 * of the TX interrupt */
static volatile void (*g_UART_TXcallBackPtr)(void) = '\0';

/************************************************************
 *                Interrupt Service Routines                *
 ************************************************************/

ISR(USART_RXC_vect)
{
	if(g_UART_RXcallBackPtr != '\0')
	{
		(*g_UART_RXcallBackPtr)();
	}
}

ISR(USART_TXC_vect)
{
	if(g_UART_TXcallBackPtr != '\0')
	{
		(*g_UART_TXcallBackPtr)();
	}
}
/**********************************************************
 *                 Functions Definitions                  *
 **********************************************************/

void UART_init (UART_configType *UART_config)
{
	if(DOUBLE_SPEED == 1)
		UCSRA |= (1<<U2X);
	else
		UCSRA &= ~(1<<U2X);

	UCSRB = ( UCSRB & 0x7F) | (UART_config->RX_interruptEnable << RXCIE);
	UCSRB = ( UCSRB & 0xBF) | (UART_config->TX_interruptEnable << TXCIE);

	UCSRB |= (1<<RXEN) | (1<<TXEN);

	UCSRB = ( UCSRB & 0xFB) | ( (UART_config->charSize & 0x4) >> 2);

	UCSRC = (1<<URSEL);

	UCSRC = ( UCSRC & 0xDF) | (UART_config->parity << UPM0);

	UCSRC = ( UCSRC & 0xFC) | (UART_config->charSize & 0x3);

	UBRRH = BAUD_PRESCALE>>8;
	UBRRL = BAUD_PRESCALE;
}

void UART_sendChar(const uint8 data)
{
	while(BIT_IS_CLEAR(UCSRA,UDRE)){}
	UDR = data;
}

uint8 UART_recieveChar(void)
{

	while(BIT_IS_CLEAR(UCSRA,RXC)){}
    return UDR;
}

void UART_sendString(const uint8 *str)
{
	while(*str != '\0')
	{
		UART_sendChar(*str);
		str++;
	}
}

void UART_receiveString(uint8 *str)
{
	*str = UART_recieveChar();
	while(*str != '#')
	{
		str++;
		*str = UART_recieveChar();
	}
	*str = '\0';
}

void UART_setRXCallBack (void (*a_callBackptr)(void))
{
	g_UART_RXcallBackPtr = a_callBackptr;
}
void UART_setTXCallBack (void (*a_callBackptr)(void))
{
	g_UART_TXcallBackPtr = a_callBackptr;
}
