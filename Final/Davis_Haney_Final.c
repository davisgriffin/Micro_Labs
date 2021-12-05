
// Title
// @authors Griffin Davis and Sydnee Haney

#include <stdlib.h>
#include "LPC214x.h"
#include "libs/LCD_Driver.h"
#include "libs/Timer.h"
#include "libs/Joystick.h"
#include "libs/Casino.h"

void Joystick_ISR(void) __irq {
    RunSlots();
    EXTINT |= 0x8;
    VICVectAddr = 0;
}

int main(void) {
    LCD_Init();
    Joystick_Interrupt_Down_Init((unsigned int) Joystick_ISR);
    Slots_Init();
    srand(CTIME0);

    while(1);
}
