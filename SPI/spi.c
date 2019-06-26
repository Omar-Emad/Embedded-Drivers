/**********************************************************
 *
 * File Name: spi.c
 *
 * Author: Omar Emad
 *
 * Date Created: 27/9/2018
 *
 * File Description: The source file for SPI driver
 *
 **********************************************************/

#include "spi.h"

/**************************************************************
 *                Functions Definitions                       *
 **************************************************************/

void SPI_initMaster(void)
{
	DDRB = DDRB | (1<<PB4);
	DDRB = DDRB | (1<<PB5);
	DDRB = DDRB & ~(1<<PB6);
	DDRB = DDRB | (1<<PB7);

	SPCR = (1<<SPE) | (1<<MSTR); // enable SPI + enable Master + choose SPI clock = Fosc/4
}

void SPI_initSlave(void)
{
	DDRB = DDRB & (~(1<<PB4));
	DDRB = DDRB & (~(1<<PB5));
	DDRB = DDRB | (1<<PB6);
	DDRB = DDRB & (~(1<<PB7));
	SPCR = (1<<SPE); // just enable SPI + choose SPI clock = Fosc/4
}

void SPI_sendChar(const uint8 data)
{
	SPDR = data;
	while(BIT_IS_CLEAR(SPSR,SPIF)){}
}

uint8 SPI_recieveChar(void)
{
   while(BIT_IS_CLEAR(SPSR,SPIF)){}
   return SPDR;
}

void SPI_SendString(const uint8 *str)
{
	while(*str != '\0')
	{
		SPI_sendChar(*str);
		str++;
	}
}

void SPI_ReceiveString(char *str)
{
	*str = SPI_recieveChar();
	while(*str != '#')   /* # means end of the message */
	{
		str++;;
		*str = SPI_recieveChar();
	}
	*str = '\0';
}

