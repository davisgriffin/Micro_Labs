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

void delayU (int intUSeconds) {
    T1TCR &= 0xFE; // turn off counter
    T1PR = 0; // 1:1 TC scaling
    T1IR |= 0x01; // clear interrupts
    T1MCR |= 0x07; // allow interrupts for MR0
    
    T1MR0 = 15 * intUSeconds; // 15000 cycles per second
    T1TCR  |= 0x01; // enable counter
    while(T1IR ^ 0x01); // wait until MR0 interrupt generated
    return; // return to code
}

void delay(void) {
    unsigned int val;

    AD0CR |= (1<<21 | 0x5 << 8 | 1 << 2); // operational, 2.5MHz, A0.2 selected
    AD0CR &= 0 << 17; // 10 bit resolution
    AD0CR |= 1 << 24; // start conversion
    do {
        val = (AD0DR2 >> 6) & 0x03FF;
    } while((AD0DR2 & 0x10000000) == 0);
    AD0CR &= ~0x01000000;
    //val = (~(val >> _) & _);
    val = ((val + 100) >> 2) << 10;

    delayU(val);
}

int main (void) {
    unsigned int mask = 0x00008000;
    unsigned int dir = 0;

    IODIR0 = 0x0000FF00;
    IOSET0 = 0x0000FF00;

	while(1){
        IOCLR0 = mask;
        delay();
        IOSET0 = mask;
        
        if (dir) mask = mask << 1;
        else mask = mask >> 1;

        if( (mask & 0x00008000) || (mask & 0x00000100)) dir = !dir;
	}

    
}
