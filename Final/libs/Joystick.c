
// Title
// @authors Griffin Davis and Sydnee Haney

#include "LPC214x.h"
#include "Joystick.h"

void Joystick_Init(unsigned int pinMask) {
    PINSEL1 &= ~(pinMask);
    IODIR0 &= ~(pinMask);
}

void Joystick_Interrupt_Down_Init(unsigned int ISR) {
    PINSEL1 |= 1<<8 | 1<<9; // P0.20 as EINT3
    VICIntSelect &= ~(1<<17); // EINT3 as IRQ
    VICVectAddr3 = ISR; // joystick ISR relation
    VICVectCntl3 = (1<<5) | 17; // EINT3 vectored
    VICIntEnable = 1<<17; // enable EINT3
    EXTINT &= ~(0x8); // clear interrupt
}
