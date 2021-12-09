
/**
 * LCD Driver source file. This contains many of the functions required to
 * efficiently drive the LMB162A LCD on board the LPC2148 education board.
 * @authors Griffin Davis and Sydnee Haney
 */

#include "LPC214x.h"
#include "LCD_Driver.h"
#include "Timer.h"

void LCD_Command(unsigned char cmd) {
    IOCLR1 |= _rs_pin | 0xFF << _d0_pin;
    IOCLR0 |= _rw_pin;
    IOSET1 |= _enable_pin | cmd << _d0_pin;
    IOCLR1 |= _enable_pin;
    delayUs(4000);
}

void LCD_Init(void) {
    PINSEL0 &= ~(_rw_pin | _backlight);
	PINSEL2 &= ~(0xFF << _d0_pin | _rs_pin | _enable_pin);
	IODIR0 |= (_rw_pin | _backlight);           // RW and Backlight as outputs
    // Data, RS, and E pins as outputs
	IODIR1 |= (0xFF << _d0_pin | _rs_pin | _enable_pin);

    delayMs(30);                        // allow LCD to initialize

    LCD_Command(0x38);                  // 2 line display with 5x7 characters
    LCD_Command(0x0C);                  // Display on, cursor and blink off
    LCD_Command(LCD_CLEARDISPLAY);
    LCD_Command(0x06);                  // Entry mode, increment, no shift
    IOSET0 |= _backlight;
    LCD_Command(LCD_SETDDRAM);
}

void LCD_WriteChar(char ch) {
    IOCLR1 |= 0xFF << _d0_pin;
    IOCLR0 |= _rw_pin;
    IOSET1 |= _enable_pin | _rs_pin | ch << _d0_pin;;
    IOCLR1 |= _enable_pin;
    delayUs(100);
}

void LCD_WriteString(char* string) {
    int i=0;
    while(string[i] != '\0') {
        LCD_WriteChar(string[i]);
        i++;
    }
}

void LCD_CreateChar(unsigned char location, unsigned char charmap[]) {
    int i=0;
    location &= 0x07;  // Only 8 locations available
    LCD_Command(LCD_SETCGRAM | location << 3);
    for(i=0; i<8; i++) {
      LCD_WriteChar(charmap[i]);
    }
    LCD_Command(LCD_SETDDRAM);
}

void LCD_SetPosition(unsigned char row, unsigned char col) {
    LCD_Command(LCD_SETDDRAM | (row & 0x2) << 5 | col & 0xF);
}

void LCD_Clear(void) {
    LCD_Command(LCD_CLEARDISPLAY);
}
