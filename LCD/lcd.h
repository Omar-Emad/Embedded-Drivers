
/*************************************************************
 *
 * File Name: lcd.h
 *
 * Author: Omar Emad
 *
 * Date Created: 15/9/2018
 *
 * Description: Header file for LCD module
 *
 *************************************************************/

#ifndef LCD_H_
#define LCD_H_

#include "micro_config.h"
#include "common_macros.h"
#include "std_types.h"
#include "lcd_config.h"

/*****************************************************************
 *                   Preprocessor                                *
 *****************************************************************/

/* Commands */
#define CLEAR 0x01
#define TWO_LINE_LCD_FOUR_BIT_MODE 0x28
#define TWO_LINE_LCD_EIGHT_BIT_MODE 0x38
#define FOUR_BITS_DATA_MODE 0x02
#define CURSOR_OFF 0x0C
#define CURSOR_ON 0x0E
#define SHIFT_DISPLAY_LEFT 0x18
#define SHIFT_DISPLAY_RIGHT 0x1C
#define SET_CURSOR_LOCATION 0x80
#define CURSOR_BLINKING_ON 0x0D
#define CURSOR_BLINKING_OFF 0x0C

/***************************************************************
 *                  Functions Prototypes                       *
 ***************************************************************/

void LCD_init (void);
void LCD_sendCommand (const uint8 a_command);
void LCD_displayChar (const char a_data);
void LCD_displayString (const char *p_str);
void LCD_displayAtPosition (uint8 row, uint8 column, const char *p_str);
void LCD_moveCursor (uint8 row, uint8 column);
void LCD_clear (void);
void LCD_cursorOn (void);
void LCD_cursorOff (void);
void LCD_cursorBlinkOn (void);
void LCD_cursorBlinkOff (void;);
void LCD_shiftScreen (void);

#endif /* LCD_H_ */
