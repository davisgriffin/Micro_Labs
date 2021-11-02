#include <LPC214x.H>

/**
 * ECE5450 Lab 3 Exercise 1
 * This program will display LEDs blinking from left-to-right and then right-to-
 * left using P0.8-P0.15 and the Pclk interrupts of the microcontroller.
 * NOTE: LEDs are tied to VCC and IO, so a high IO leads to an extinguished LED
 * due to an open circuit. No current will flow unless the pin is low.
 * 
 * NOTE: T1TCR enables counter with 1 at bit 0, or resets with 1 at bit 1
 * T1PR allows prescaling, 0 is 1:1, 1 is half speed, 2 is third speed, etc.
 * T1MCR controls whether a timer generates an interrupt, is reset, or stops
 * when TC matches MR
 * T1MR0 is one match register for TC to be compared to and generate the
 * appropriate function from T1MCR
 * T1IR is the interrupt register which flags 1 when an interrupt is generated
 * This also requires an assignment of 1 to reset interrupt
 * 
 * @authors Griffin Davis, Sydnee Haney
 */

void delay (int intSeconds) {
    T1TCR &= 0xFE; // turn off counter
    T1PR = 0; // 1:1 TC scaling
    T1IR |= 0x01; // clear interrupts
    T1MCR |= 0x07; // allow interrupts for MR0
    
    T1MR0 = 15000000 * intSeconds; // 15000000 cycles per second
    T1TCR  |= 0x01; // enable counter
    while(T1IR ^ 0x01); // wait until MR0 interrupt generated
    return; // return to code
}

int main (void) {
    unsigned int mask = 0x00008000;
    unsigned int dir = 0;
    unsigned int delayTime = 2;

    IODIR0 = 0x0000FF00;
    IOSET0 = 0x0000FF00;

	while(1){
        IOCLR0 = mask;
        delay(delayTime);
        IOSET0 = mask;
        
        if (dir) mask = mask << 1;
        else mask = mask >> 1;

        if( (mask & 0x00008000) || (mask & 0x00000100)) dir = !dir;
	}
}
