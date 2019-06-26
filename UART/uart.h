/**********************************************************
 *
 * File Name: uart.h
 *
 * Author: Omar Emad
 *
 * Date Created: 27/9/2018
 *
 * File Description: The Header file for UART driver
 *
 **********************************************************/

#ifndef UART_H_
#define UART_H_


#include "common_macros.h"
#include "micro_config.h"
#include "std_types.h"

/********************************************************************
 *                      Preprocessor Macros                         *
 ********************************************************************/

/* UART Driver Baud Rate */
#define USART_BAUDRATE 9600

/* determine whether using double speed or not */
#define DOUBLE_SPEED 1

/***************************************************************
 *                  Types Declaration                          *
 ***************************************************************/

typedef enum
{
	disable, even = 2, odd = 3
}UART_parityBit;

typedef enum
{
	BITS_5, BITS_6, BITS_7, BITS_8, BITS_9 = 7
}UART_charSize;

typedef struct
{
	bool RX_interruptEnable;
	bool TX_interruptEnable;
	UART_charSize charSize;
	UART_parityBit  parity;

} UART_configType;


/*****************************************************************
 *                   Functions Prototypes                        *
 *****************************************************************/

void UART_init(UART_configType *UART_config);

void UART_sendChar(const uint8 data);

uint8 UART_recieveChar(void);

void UART_sendString(const uint8 *Str);

void UART_receiveString(uint8 *Str);

void UART_setRXCallBack (void (*a_callBackptr)(void));

void UART_setTXCallBack (void (*a_callBackptr)(void));


#endif /* UART_H_ */
