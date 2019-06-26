
/***********************************************************************
 *
 * File Name: lcd.c
 *
 * Author: Omar Emad
 *
 * Date Created: 16/9/2018
 *
 * Description: Source file for LCD module
 *
 ************************************************************************/

#include "lcd.h"

/***********************************************************************
 *                    Functions Definitions                            *
 ***********************************************************************/

void LCD_init (void)
{
	LCD_CTRL_PORT_DIR |= (1<<RS) | (1<<RW) | (1<<E);  /* set RS,RW,E as output */

	#if(DATA_BITS_MODE == 4)
		#if(UPPER_PORT_PINS==1)
			LCD_DATA_PORT_DIR |= 0xF0 ;  /* data port is output */
		#elif (UPPER_PORT_PINS==0)
			LCD_DATA_PORT_DIR |= 0x0F;  /* lower pins are the output */
		#else
        	#error "UPPER_PORT_PINS must be 1 or 0"
		#endif
		LCD_sendCommand(FOUR_BITS_DATA_MODE);
		LCD_sendCommand(TWO_LINE_LCD_FOUR_BIT_MODE);

	#elif (DATA_BITS_MODE == 8)
		LCD_DATA_PORT_DIR = 0xFF ;  /* data port is output */
		LCD_sendCommand(TWO_LINE_LCD_EIGHT_BIT_MODE);
	#else
		#error "DATA_BITS_MODE must be 4 or 8"
	#endif

	LCD_clear();
	LCD_cursorOff();
}

void LCD_sendCommand (const uint8 a_command)
{
	CLEAR_BIT(LCD_CTRL_PORT,RS);  /* CLear RS for instructions mode */
	CLEAR_BIT(LCD_CTRL_PORT,RW);  /* clear RW for wrtie mode */
	_delay_ms(1);  /* delay tas */
	SET_BIT(LCD_CTRL_PORT,E);  /* set the enable */
	_delay_ms(1);  /* delay tpw-tdsw */

	#if (DATA_BITS_MODE == 4)
		#if (UPPER_PORT_PINS)
			LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | (a_command & 0xF0);
		#elif  ( !UPPER_PORT_PINS)
			LCD_DATA_PORT = (LCD_DATA_PORT & 0xF0) | ((a_command & 0xF0) >> 4);
		#endif

		_delay_ms(1);  /* delay tdsw */
		CLEAR_BIT(LCD_CTRL_PORT,E);  /* clear enable bit */
		_delay_ms(1);  /* delay th */
		SET_BIT(LCD_CTRL_PORT,E);  /* set the enable */
		_delay_ms(1);  /* delay tpw-tdsw */

		#if (UPPER_PORT_PINS)
			LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | ((a_command & 0x0F) << 4);
		#elif  ( !UPPER_PORT_PINS)
			LCD_DATA_PORT = (LCD_DATA_PORT & 0xF0) | (a_command & 0x0F);
		#endif

		_delay_ms(1);  /* delay tdsw */
		CLEAR_BIT(LCD_CTRL_PORT,E);  /* clear enable bit */
		_delay_ms(1);  /* delay th */

	#elif (DATA_BITS_MODE == 8)
		LCD_DATA_PORT = a_command;  /* send the command on the data port */
		_delay_ms(1);  /* delay tdsw */
		CLEAR_BIT(LCD_CTRL_PORT,E);  /* clear enable bit */
		_delay_ms(1);  /* delay th */
	#endif
}

void LCD_displayChar (const char a_data)
{
	SET_BIT(LCD_CTRL_PORT,RS);  /* SET RS for DATA mode */
	CLEAR_BIT(LCD_CTRL_PORT,RW);  /* clear RW for write mode */
	_delay_ms(1);  /* delay tas */
	SET_BIT(LCD_CTRL_PORT,E);  /* set the enable */
	_delay_ms(1);  /* delay tpw-tdsw */

	#if (DATA_BITS_MODE == 4)
		#if (UPPER_PORT_PINS)
			LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | (a_data & 0xF0);
		#elif  ( !UPPER_PORT_PINS)
			LCD_DATA_PORT = (LCD_DATA_PORT & 0xF0) | ((a_data & 0xF0) >> 4);
		#endif

		_delay_ms(1);  /* delay tdsw */
		CLEAR_BIT(LCD_CTRL_PORT,E);  /* clear enable bit */
		_delay_ms(1);  /* delay th */
		SET_BIT(LCD_CTRL_PORT,E);  /* set the enable */
		_delay_ms(1);  /* delay tpw-tdsw */

		#if (UPPER_PORT_PINS)
			LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | ((a_data & 0x0F) << 4);
		#elif  ( !UPPER_PORT_PINS)
			LCD_DATA_PORT = (LCD_DATA_PORT & 0xF0) | (a_data & 0x0F);
		#endif

		_delay_ms(1);  /* delay tdsw */
		CLEAR_BIT(LCD_CTRL_PORT,E);  /* clear enable bit */
		_delay_ms(1);  /* delay th */

	#elif (DATA_BITS_MODE == 8)
		LCD_DATA_PORT = a_data;  /* send the command on the data port */
		_delay_ms(1);  /* delay tdsw */
		CLEAR_BIT(LCD_CTRL_PORT,E);  /* clear enable bit */
		_delay_ms(1);  /* delay th */
	#endif
}

void LCD_displayString (const char *p_str)
{
	while((*p_str)!='\0')
	{
		LCD_displayChar(*p_str);
		p_str++;
	}
}

void LCD_displayAtPosition (uint8 row, uint8 column, const char *p_str)
{
	LCD_moveCursor(row,column);  /* move the curosr to the required position */
	LCD_displayString(p_str);  /* display the string */
}

void LCD_moveCursor (uint8 row, uint8 column)
{
	uint8 command;
	switch(row)
	{
		case 0: command = column;
	    	break;

		case 1: command = column+ 0x40;
			break;

		case 2: command = column+ 0x10;
			break;

		case 3: command = column+ 0x50;
			break;
	}
	LCD_sendCommand(command | SET_CURSOR_LOCATION);
}

void LCD_clear (void)
{
	LCD_sendCommand(CLEAR);
}

void LCD_cursorOff (void)
{
	LCD_sendCommand(CURSOR_OFF);
}

void LCD_cursorOn (void)
{
	LCD_sendCommand(CURSOR_ON);
}

void LCD_cursorBlinkOn (void)
{
	LCD_sendCommand(CURSOR_BLINKING_ON);
}

void LCD_cursorBlinkOff (void)
{
	LCD_sendCommand(CURSOR_BLINKING_OFF);
}

void LCD_shiftScreen (void)
{
	LCD_sendCommand(SHIFT_DISPLAY_RIGHT);
}

