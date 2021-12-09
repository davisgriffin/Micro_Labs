
/**
 * The MicroSino
 * This program uses the included libraries to drive the LCD, step motor, push
 * button, and joystick on board the LPC2148 education board to simulate a
 * casino. The three playable games are the slot machine, the wheel of fortune,
 * and blackjack. All that is required is trackers of points and other game
 * globals for the Casino source file, and interrupt service routines to handle
 * game-running logic.
 * *NOTE: The step motor must be horizontally aligned before playing wheel of
 * fortune if using a physical wheel with the motor.
 * @authors Griffin Davis and Sydnee Haney
 */

#include <stdlib.h>
#include "LPC214x.h"
#include "libs/LCD_Driver.h"
#include "libs/Interrupts.h"
#include "libs/Casino.h"
#include "libs/StepMotor.h"
#include "libs/Timer.h"

int points = 100;
int currentStep, turn = 0;
int dlrDown;
int plyrSum, dlrSum = 0;
int game = 1;

void JoystickDown_ISR(void) __irq {
    if (points == 0 && turn == 0) {
        LCD_Clear();
        LCD_SetPosition(1,0);
        LCD_WriteString("OUT OF POINTS...");
        LCD_SetPosition(2,0);
        LCD_WriteString("PRESS BTN 4 MORE");
    }
    else {
        switch (game) {
        case 0:
            game = 1;
        case 1:
            RunSlots(&points);
            break;
        case 2:
            currentStep = RunWheel(currentStep, &points);
            break;
        case 3:
            turn = RunBlackJack(&points, &plyrSum, &dlrSum, &dlrDown, turn);
            break;
        }
    }
    delayMs(300);
    EXTINT |= 0x8;
    VICVectAddr = 0;
}

void PushButton_ISR(void) __irq {
    if(points<=0) {
        points = 100;
        LCD_Clear();   
        Slots_Init(points);
    }
    else if(game==3) {
        turn = RunBlackJack(&points, &plyrSum, &dlrSum, &dlrDown, -1);
    }
    else if(!game) {
        game = 3;
        LCD_Clear();
        BlackJack_Init(points);
    }
    delayMs(300);
    EXTINT |= 0x2;
    VICVectAddr = 0;
}

void JoystickPress_ISR(void) __irq {
    if(!game) {
        game = 2;
        Wheel_Init(points);
    }
    else if(game && turn == 0) {
        game = 0;
        GameSelect();
    }
    delayMs(300);
    EXTINT |= 0x1;
    VICVectAddr = 0;
}

int main(void) {
    LCD_Init();
    Interrupt_Init_JoystickDown((unsigned int) JoystickDown_ISR);
    Interrupt_Init_PushButton((unsigned int) PushButton_ISR);
    Interrupt_Init_JoystickPress((unsigned int) JoystickPress_ISR);
    Slots_Init(points);
    Step_Init();
    srand(CTIME0);

    while(1);
}
