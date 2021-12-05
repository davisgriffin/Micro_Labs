
// Title
// @authors Griffin Davis and Sydnee Haney

#include <stdlib.h>
#include "LCD_Driver.h"
#include "Timer.h"
#include "Casino.h"

void RunSlots(void) {
    int i,j=0;
    int slotDelayMs=25;
    char botRow[3] = "   ";
    char topRow[3];

    LCD_Clear();
    LCD_SetPosition(1,3);

    // 30 spins in the machine
    for(i=0; i<30; i++) {
        for(j=0; j<3; j++) {
            // Write the old character into the top row (spinning up)
            topRow[j] = botRow[j];
            LCD_SetPosition(1,j+3);
            LCD_WriteChar(topRow[j]);

            // Write a new character into the bottom row
            LCD_SetPosition(2,j+3);
            botRow[j] = rand()%5;
            LCD_WriteChar(botRow[j]);
            
            // After 10 spins, increase delay by 5.5% each spin
            delayMs(slotDelayMs);
            if(i>10) slotDelayMs *= 1.055;
        }
    }

    LCD_SetPosition(1,9);
    if((topRow[0] == topRow[1]) && (topRow[1] == topRow[2])) {
        if (topRow[0] == 4) {
            // If we hit all 7's
            LCD_WriteString("HUGE");
            LCD_SetPosition(2,9);
            LCD_WriteString("WINNER!");
        } else {
            LCD_WriteString("WINNER!");
        }
    } else {
        LCD_WriteString("loser.");
    }
}

void Slots_Init(void) {
    unsigned char martini[] = {
        0x00,
        0x1F,
        0x0E,
        0x04,
        0x04,
        0x0E,
        0x00,
        0x00
    };
    unsigned char bell[] = {
        0x00,
        0x04,
        0x0E,
        0x0E,
        0x1F,
        0x04,
        0x00,
        0x00
    };
    unsigned char heart[] = {
        0x00,
        0x0A,
        0x1F,
        0x1F,
        0x0E,
        0x04,
        0x00,
        0x00
    };
    unsigned char money[] = {
        0x00,
        0x04,
        0x0E,
        0x0C,
        0x06,
        0x0E,
        0x04,
        0x00
    };
    unsigned char seven[] = {
        0x00,
        0x1F,
        0x01,
        0x02,
        0x04,
        0x04,
        0x04,
        0x00
    };

    LCD_CreateChar(0, martini);
    LCD_CreateChar(1, bell);
    LCD_CreateChar(2, heart);
    LCD_CreateChar(3, money);
    LCD_CreateChar(4, seven);

    LCD_WriteString("PULL LEVER");
    LCD_SetPosition(2,0);
    LCD_WriteString("TO PLAY");
}
