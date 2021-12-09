
/**
 * Casino source file. This contains each of the games initialization and
 * running functions. Reference Davis_Haney_Final on how to set up your own
 * casino.
 * @authors Griffin Davis and Sydnee Haney
 */

#include <stdio.h>
#include <stdlib.h>
#include "Casino.h"
#include "LCD_Driver.h"
#include "Timer.h"
#include "StepMotor.h"

void WritePoints(int points) {
    char chPoints[4];
    sprintf(chPoints, "%i", points);
    LCD_SetPosition(1, 12);
    LCD_WriteString(chPoints);
}

void WriteInt(int num) {
    char chNum[4];
    sprintf(chNum, "%i", num);
    LCD_WriteString(chNum);
}

void HugeWinner(int* points) {
    LCD_SetPosition(1,4);
    LCD_WriteString("HUGE");
    LCD_SetPosition(2,4);
    LCD_WriteString("WINNER!");
    *points += _slots_hugeWinBonus;
    WritePoints(*points);
}

void Winner(int* points) {
    LCD_SetPosition(1,4);
    LCD_WriteString("WINNER!");
    *points += _slots_winBonus;
    WritePoints(*points);
}

void CheckPoints(int* points) {
    if (*points<_slots_cost) *points = 0;
}

void GameSelect(void) {
    LCD_Clear();
    LCD_SetPosition(1,0);
    LCD_WriteString("DWN-SLOTS BTN-21");
    LCD_SetPosition(2,0);
    LCD_WriteString("IN-WHEEL");
    
}

void RunSlots(int* points) {
    int i,j=0;
    int slotDelayMs=25;
    char botRow[3] = "   ";
    char topRow[3];
    CheckPoints(points);
    if (points == 0) ;

    *points -= _slots_cost;
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

    LCD_WriteString("PULL TO PLAY");
    LCD_SetPosition(1, 13);
    sprintf(chPoints, "%i", points);
    LCD_WriteString(chPoints);
    LCD_SetPosition(2,0);
    LCD_WriteString("PUSH TO CHANGE");
}

void Wheel_Init(int points) {
    LCD_Clear();
    LCD_SetPosition(2,0);
    LCD_WriteString("WHEEL OF FORTUNE");
    WritePoints(points);
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
            *points -= _wheel_loseCost;
            break;
        case 3:
            LCD_WriteString("YOU WON 75!");
            WritePoints(_wheel_hugeWinBonus);
            *points += _wheel_hugeWinBonus;
            break;
        case 4:
            LCD_WriteString("YOU WON 50!");
            WritePoints(_wheel_winBonus);
            *points += _wheel_winBonus;
            break;
    }
    CheckPoints(points);
    WritePoints(*points);
    return currentStep;
}

void BlackJack_Init(int points) {
    LCD_Clear();
    LCD_SetPosition(1,0);
    LCD_WriteString("BLACKJACK");
    LCD_SetPosition(2,0);
    LCD_WriteString("PULL TO HIT");
    WritePoints(points);
}

void WriteCard(int card) {
    if (card < 10) {
        LCD_WriteChar(card+0x30);
        return;
    }
    switch(card) {
    case 10:
        LCD_WriteChar('T');
        break;
    case 11:
        LCD_WriteChar('J');
        break;
    case 12:
        LCD_WriteChar('Q');
        break;
    case 13:
        LCD_WriteChar('K');
        break;
    case 14:
        LCD_WriteChar('A');
        break;
    }
}

int CheckValue(int card, int sum) {
    if(card!=14) {
        if(card<10) return card;
        else return 10;
    }
    if(sum+11 > 21) return 1;
    return 11;
}

int RunBlackJack(int* points, int* plyrSum, int* dlrSum, int* dlrDown, int turn) {
    int i=0;
    int card=0;
    // Game starting
    if (!turn) {
        LCD_Clear();
        LCD_SetPosition(1,0);
        LCD_WriteString("DEALER");
        LCD_SetPosition(2,0);
        LCD_WriteString("PLAYER");
        for(i=0; i<2; i++) {
            LCD_SetPosition(2, i+7);
            card = rand()%13 + 2;
            WriteCard(card);
            card = CheckValue(card, *plyrSum);
            *plyrSum += card;

            LCD_SetPosition(1,i+7);
            card = rand()%13 + 2;
            if (i==0) WriteCard(card);
            else {
                LCD_WriteChar(0xFF);
                *dlrDown = card;
            }
            card = CheckValue(card, *dlrSum);
            *dlrSum += card;
        }
        *points -= _blackjack_cost;
    }
    // Chose to Stand
    else if(turn == -1) {
        LCD_SetPosition(1, 8);
        WriteCard(*dlrDown);
        while(*dlrSum < 17) {
            card = rand()%13 + 2;
            WriteCard(card);
            card = CheckValue(card, *dlrSum);
            *dlrSum += card;
        }
        LCD_SetPosition(1,0);
        if(*dlrSum > 21 || *dlrSum < *plyrSum) {
            LCD_WriteString("U WIN!");
            *points += _blackjack_cost + _blackjack_cost;
        } else if(*dlrSum == *plyrSum) {
            LCD_WriteString("U TIE!");
            *points += _blackjack_cost;
        } else {
            LCD_WriteString("U LOSE");
        }
        WritePoints(*points);
        *dlrDown = 0;
        *plyrSum = 0;
        *dlrSum = 0;
        return 0;
    }
    // New Hit
    else {
        LCD_SetPosition(2,turn+8);
        card = rand()%13 + 2;
        WriteCard(card);
        card = CheckValue(card, *plyrSum);
        *plyrSum += card;
    }

    // Bust
    if(*plyrSum > 21) {
        LCD_SetPosition(1,0);
        LCD_WriteString("U LOSE");
        WritePoints(*points);
        *dlrDown = 0;
        *plyrSum = 0;
        *dlrSum = 0;
        return 0;
    }

    WritePoints(*points);
    return ++turn;
}
