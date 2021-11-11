#include <LPC214x.H>

/**
 * ECE5450 Lab 4
 * This program will display LEDs blinking from left-to-right and then right-to-
 * left using P0.8-P0.15, the Pclk interrupts of the microcontroller, and its
 * ADC.
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
 * NOTE: AD0CR is a control register.
 * -    Bit 21      : PDN - operational
 * -    Bit 19:17   : 000 = 11 clocks = 10 bit accuracy
 * -    Bit 15:8    : CLKDIV = (Pclk/Adclk) - 1
 * -    Bit 7:0     : SEL - channel select
 * -    Bit 24      : START
 * 
 * AD0DR7:0 is the data register.
 * -    Bit 31      : DONE
 * -    Bit 15:6    : RESULT
 * 
 * @authors Griffin Davis, Sydnee Haney
 */

void delayU (int intUSeconds) {
    T1TCR = 0x02;
    T1PR = 0x00;
    T1MR0 = intUSeconds;
    T1IR = 0xFF;
    T1MCR = 0x04;
    T1TCR = 0x01;
    while(T1TCR & 0x01);
}

void delay(void) {
    unsigned int val;

    AD0CR |= 0x01000000; // start conversion
    do {
        val = AD0DR2;
    } while((val & 0x80000000)==0); // while DONE bit not set
    AD0CR &= ~0x01000000;
    val = (~(val >> 6) & 0x03FF);
    val = ((val + 100) >> 2) << 10;

    delayU(val);
}

int main (void) {
    unsigned int i = 0;

    PINSEL1 = (0x1 << 26); // set P0.29 to AD0.2
    AD0CR |= (1 << 21); // set operational
    AD0CR |= ((0x0<<17) | (0x05 << 8) | (1 << 2)); // 10bit res, 2.5MHz, A0.2 selected
    
    IODIR0 = 0x0000FF00;
    IOSET0 = 0x0000FF00;

	while(1){
        for(i=0; i<7; i++) {
            IOCLR0 = 1<< i + 8;
            delay();
            IOSET0 = 1 << i + 8;
        }
        for(i=0; i<7; i++) {
            IOCLR0 = 1 << 15-i;
            delay();
            IOSET0 = 1<<15-i;
        }
	}

    
}
