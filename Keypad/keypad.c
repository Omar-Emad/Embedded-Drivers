/*********************************************************
 *
 * File Name: keypad.c
 *
 * Author: Omar Emad
 *
 * Date Created: 14/9/2018
 *
 * Description : Source file for the keypad driver
 *
 *********************************************************/

#include "keypad.h"

/*************************************************************************
 *                      Functions Prototypes(Private)                    *
 *************************************************************************/

static uint8 adjustKeyNumber (const uint8 a_number);

/*************************************************************************
 *                          Functions Definitions                        *
 *************************************************************************/

uint8 KEYPAD_getPressedKey (void)
{
	uint8 col,row;
	while(1)
	{
		for(col=0;col<N_col;col++)
		{
			KEYPAD_PORT_DIR=(0b00010000<<col);
			KEYPAD_PORT_OUT=~(0b00010000<<col);

			for(row=0;row<N_row;row++)
			{
				if(BIT_IS_CLEAR(KEYPAD_PORT_IN,row))
				{
					return adjustKeyNumber((N_col*row)+col+1);
				}
			}
		}
	}
}

static uint8 adjustKeyNumber (const uint8 a_number)
{
#if (N_col==3)
	switch(a_number)
	{
		case 10: return '*';
			break;
		case 11: return '0';
			break;
		case 12: return '#';
			break;
		default: return 'a_number';
	}
#elif (N_col==4)
	switch(a_number)
	{
		case 1: return '7';
			break;
		case 2: return '8';
			break;
		case 3: return '9';
			break;
		case 4: return '/';
			break;
		case 5: return '4';
			break;
		case 6: return '5';
			break;
		case 7: return '6';
			break;
		case 8: return '*';
			break;
		case 9: return '1';
			break;
		case 10: return '2';
			break;
		case 11: return '3';
			break;
		case 12: return '-';
			break;
		case 13: return 13;  /* ASCII code of Enter */
			break;
		case 14: return '0';
			break;
		case 15: return '=';
			break;
		case 16: return '+';
			break;
	}
#endif
	return -1;
}



