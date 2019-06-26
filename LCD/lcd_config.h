
/*************************************************************
 *
 * File Name: lcd_congif.h
 *
 * Author: Omar Emad
 *
 * Date Created: 15/9/2018
 *
 * Description: Configuration file for LCD module
 *
 *************************************************************/

#ifndef LCD_CONFIG_H_
#define LCD_CONFIG_H_

/***************************************************************
 *                      Data Mode                              *
 ***************************************************************/

/* LCD mode */
#define DATA_BITS_MODE 4      /* 4 or 8 bits mode */

/* (in case if the DATA_BITS_MODE is 4)
 * if UPPER_PORT_PINS = 1 the upper pins in the port will be initialized
 * if UPPER_PORT_PINS = 0 the lower pins in the port will be initialized
 */
#define UPPER_PORT_PINS 1

/* Hardware Pins */
#define RS PC0
#define RW PC1
#define E PC2
#define LCD_CTRL_PORT PORTC
#define LCD_CTRL_PORT_DIR DDRC
#define LCD_DATA_PORT  PORTA
#define LCD_DATA_PORT_DIR DDRA



#endif /* LCD_CONFIG_H_ */
