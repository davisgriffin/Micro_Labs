
// Title
// @authors Griffin Davis and Sydnee Haney

#include "LPC214x.h"
#include "Interrupts.h"

void Interrupt_Init_JoystickDown(unsigned int ISR) {
    PINSEL1 |= 1<<8 | 1<<9; // P0.20 as EINT3
    VICIntSelect &= ~(1<<_bit_EINT3); // EINT3 as IRQ
    VICVectAddr3 = ISR; // joystick ISR relation
    VICVectCntl3 = (1<<5) | _bit_EINT3; // EINT3 vectored
    VICIntEnable = 1<<_bit_EINT3; // enable EINT3
    EXTINT &= ~(0x8); // clear interrupt
}

void Interrupt_Init_JoystickPress(unsigned int ISR) {
    PINSEL1 |= 0x1;
    PINSEL1 &= ~(0x2);
    VICIntSelect &= ~(1<<_bit_EINT0);
    VICVectAddr7 = ISR;
    VICVectCntl7 = (1<<5) | _bit_EINT0;
    VICIntEnable = 1<<_bit_EINT0;
    EXTINT &= ~(0x1);
}

void Interrupt_Init_PushButton(unsigned int ISR) {
    PINSEL0 |= 1 << 29;
    PINSEL0 &= ~(1 << 28);
    VICIntSelect &= ~(1<<_bit_EINT1);
    VICVectAddr5 = ISR;
    VICVectCntl5 = (1<<5) | _bit_EINT1;
    VICIntEnable = 1<<_bit_EINT1;
    EXTINT &= ~(0x2);
}
