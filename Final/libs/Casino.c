
// Title
// @authors Griffin Davis and Sydnee Haney

#include <stdio.h>
#include <stdlib.h>
#include "Casino.h"
#include "LCD_Driver.h"
#include "Timer.h"
#include "StepMotor.h"

#define _winBonus 50
#define _hugeWinBonus 100

void WritePoints(int points) {
    char chPoints[4];
    sprintf(chPoints, "%i", points);
    LCD_SetPosition(1, 12);
    LCD_WriteString(chPoints);
}

void HugeWinner(int* points) {
    LCD_SetPosition(1,4);
    LCD_WriteString("HUGE");
    LCD_SetPosition(2,4);
    LCD_WriteString("WINNER!");
    *points += _hugeWinBonus;
    WritePoints(*points);
}

void Winner(int* points) {
    LCD_SetPosition(1,4);
    LCD_WriteString("WINNER!");
    *points += _winBonus;
    WritePoints(*points);
}

void CheckPoints(int* points) {
    if (*points<10) *points = 0;
}

void RunSlots(int* points) {
    int i,j=0;
    int slotDelayMs=25;
    char botRow[3] = "   ";
    char topRow[3];
    CheckPoints(points);
    if (points == 0) ;

    *points -= 10;
    LCD_Clear();
    WritePoints(*points);
    LCD_SetPosition(1,3);

    // 30 spins in the machine
    for(i=0; i<30; i++) {
        for(j=0; j<3; j++) {
            // Write the old character into the top row (spinning up)
            topRow[j] = botRow[j];
            LCD_SetPosition(1,j);
            LCD_WriteChar(topRow[j]);

            // Write a new character into the bottom row
            LCD_SetPosition(2,j);
            botRow[j] = rand()%5;
            LCD_WriteChar(botRow[j]);
            
            // After 10 spins, increase delay by 5.5% each spin
            delayMs(slotDelayMs);
            if(i>10) slotDelayMs *= 1.055;
        }
    }

    if((topRow[0] == topRow[1]) && (topRow[1] == topRow[2])) {
        if (topRow[0] == 4) {
            // If we hit all 7's
            HugeWinner(points);
        } else {
            Winner(points);
        }
    } else if ((botRow[0] == botRow[1]) && (botRow[1] == botRow[2])) {
        if (botRow[0] == 4) {
            // If we hit all 7's
            HugeWinner(points);
        } else {
            Winner(points);
        }
    } else {
        LCD_SetPosition(1,4);
        LCD_WriteString("loser.");
    }
}

void Slots_Init(int points) {
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
    char chPoints[4];

    LCD_CreateChar(0, martini);
    LCD_CreateChar(1, bell);
    LCD_CreateChar(2, heart);
    LCD_CreateChar(3, money);
    LCD_CreateChar(4, seven);

    LCD_WriteString("PULL LEVER");
    LCD_SetPosition(1, 12);
    sprintf(chPoints, "%i", points);
    LCD_WriteString(chPoints);
    LCD_SetPosition(2,0);
    LCD_WriteString("TO PLAY");
}

int RunWheel(int currentStep, int* points) {
    currentStep =  Step_Forward(currentStep, rand()%30+30);
    LCD_Clear();
    LCD_SetPosition(2,0);
    switch (currentStep) {
        case 0:
        case 1:
        case 2:
            LCD_WriteString("YOU LOSE 50!");
            *points -= 50;
            break;
        case 3:
            LCD_WriteString("YOU WON 75!");
            *points += 75;
            break;
        case 4:
            LCD_WriteString("YOU WON 50!");
            *points += 50;
            break;
    }
    CheckPoints(points);
    WritePoints(*points);
    return currentStep;
}
