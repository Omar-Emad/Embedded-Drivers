/**********************************************************
 *
 * File Name: i2c.c
 *
 * Author: Omar Emad
 *
 * Date Created: 3/10/2018
 *
 * File Description: The source file for I2C driver
 *
 **********************************************************/

#include "i2c.h"

void TWI_init(void)
{
    TWBR = 0x02;
	TWSR = 0x00;

    TWAR = 0b00000010; // my address = 0x01 :)

    TWCR = (1<<TWEN); /* enable TWI */
}

void TWI_start(void)
{
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    while(BIT_IS_CLEAR(TWCR,TWINT));
}

void TWI_stop(void)
{

    TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}

void TWI_write(uint8 data)
{
    TWDR = data;

    TWCR = (1 << TWINT) | (1 << TWEN);

    while(BIT_IS_CLEAR(TWCR,TWINT));
}

uint8 TWI_readWithACK(void)
{

    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
    while(BIT_IS_CLEAR(TWCR,TWINT));

    return TWDR;
}

uint8 TWI_readWithNACK(void)
{
    TWCR = (1 << TWINT) | (1 << TWEN);
    while(BIT_IS_CLEAR(TWCR,TWINT));

    return TWDR;
}

uint8 TWI_getStatus(void)
{
    uint8 status;

    /* masking to eliminate first 3 bits and get the last 5 bits (status bits) */
    status = TWSR & 0xF8;
    return status;
}

