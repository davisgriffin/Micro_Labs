#include <LPC214x.H>

/**
 * ECE5450 Lab 5
 * This program will display LEDs blinking from left-to-right and then right-to-
 * left using P0.8-P0.15, the Pclk interrupts of the microcontroller, and its
 * ADC.
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
 * NOTE: P0.12 and P0.21 control direction of the stepper motor. If P0.12 is
 * leading then the motor moves forward, if it is lagging it moves backwards.
 * 
 * 
 * @authors Griffin Davis, Sydnee Haney
 */

void forward(void);
void reverse(void);
void wait(void);
unsigned int fPhase = 1<<12;
unsigned int rPhase = 1<<21;

int main (void) {
    int i=0;
    
    IODIR0 = (0x1<<12 | 0x1<<21);
    IOCLR0 = (0x1<<12 | 0x1<<21);

	while(1){
        for(i=0; i<50; i++) forward();
        for(i=0; i<50; i++) reverse();
	}

    
}

void forward(void) {
    wait();
    IOSET0 |= fPhase;
    wait();
    IOSET0 |= rPhase;
    wait();
    IOCLR0 |= fPhase;
    wait();
    IOCLR0 |= rPhase;
}

void reverse(void) {
    wait();
    IOSET0 |= rPhase;
    wait();
    IOSET0 |= fPhase;
    wait();
    IOCLR0 |= rPhase;
    wait();
    IOCLR0 |= fPhase;
}

void wait(void) {
    int speed = 50000;
    int d = 0;
    for(d=0; d<speed; d++);
}
