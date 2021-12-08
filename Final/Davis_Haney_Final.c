
// Title
// @authors Griffin Davis and Sydnee Haney

#include <stdlib.h>
#include "LPC214x.h"
#include "libs/LCD_Driver.h"
#include "libs/Interrupts.h"
#include "libs/Casino.h"
#include "libs/StepMotor.h"
#include "libs/Timer.h"

int points = 100;
int currentStep = 0;
int game = 0;

void JoystickDown_ISR(void) __irq {
    if (points == 0) {
        LCD_Clear();
        LCD_SetPosition(1,0);
        LCD_WriteString("OUT OF POINTS...");
        LCD_SetPosition(2,0);
        LCD_WriteString("PRESS BTN 4 MORE");
    }
    else if (game) {
        LCD_Clear();
        LCD_SetPosition(1,0);
        LCD_WriteString("WHEEL OF FORTUNE");
        delayMs(300);
        currentStep = RunWheel(currentStep, &points);
    } else {
        if (points>0) {
            RunSlots(&points);
        } 
    }
    EXTINT |= 0x8;
    VICVectAddr = 0;
}

void PushButton_ISR(void) __irq {
    if(points<=0) {
        points = 100;
        LCD_Clear();
        Slots_Init(points);
    }
    EXTINT |= 0x2;
    VICVectAddr = 0;
}

void JoystickPress_ISR(void) __irq {
    game = !game;
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
