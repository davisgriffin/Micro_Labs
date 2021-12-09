
/**
 * LCD Driver header file. This contains many of the functions required to
 * efficiently drive the LMB162A LCD on board the LPC2148 education board.
 * @authors Griffin Davis and Sydnee Haney
 */

#ifndef LCD_DRIVER_H
#define LCD_DRIVER_H

// LCD Pins
#define _rs_pin  1 << 24 // LOW: Command.  HIGH: Character.
#define _rw_pin  1 << 22 // LOW: Write.    HIGH: Read.
#define _enable_pin  1 << 25
#define _backlight  1 << 30
#define _d0_pin  16

// Commands
#define LCD_CLEARDISPLAY  0x01
#define LCD_SETCGRAM  0x40
#define LCD_SETDDRAM  0x80

// Functions

/* LCD_Init
 * Sets the display to two lines, 8-bit, no cursor or blink.
 */
void LCD_Init(void);

/* LCD_WriteChar
 * Writes a character to the display
 * ------------------------------------------
 * Paramaters: ch
 *  - Character to be written
 */
void LCD_WriteChar(char ch);

/* LCD_WriteString
 * Clears the display and writes the given string.
 * ------------------------------------------
 * Paramaters: string
 *  - String to be written to the display
 */
void LCD_WriteString(char* string);

/* LCD_CreateChar
 * Create custom characters for use with the display.
 * ------------------------------------------
 * Paramaters:
 *  location :: unsigned char
 *  - Location of the custom character in LCD memory. Must be 0-7.
 *  charmap :: unsigned char[]
 *  - 5x8 bit representation of the character.
 */
void LCD_CreateChar(unsigned char location, unsigned char charmap[]);

/* LCD_SetPosition
 * Set the cursor to where you'd like to begin your next write.
 * * NOTE that row is one indexed while col is zero indexed.
 * ------------------------------------------
 * Paramaters:
 *  row :: unsigned char
 *  - Line 1 or 2
 *  col :: unsigned char
 *  - Allows 0 through 15 for the 16 characters
 */
void LCD_SetPosition(unsigned char row, unsigned char col);

/* LCD_Clear
 * Clear the LCD.
 */
void LCD_Clear(void);

#endif
