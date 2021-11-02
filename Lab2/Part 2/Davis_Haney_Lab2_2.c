#include <LPC214x.H>

/**
 * ECE5450 Lab 2 Exercise 1
 * This program will alternate blinking pins P0.8-P0.11 and pins P0.12-P0.15.
 * One half of the LEDs will be on while the other is off and vice versa.
 * NOTE: LEDs are tied to VCC and IO, so a high IO leads to an extinguished LED
 * due to an open circuit. No current will flow unless the pin is low.
 * @authors Griffin Davis, Sydnee Haney
 */
void wait (void) {
    int d;

    for(d=0; d<2500000; d++);
}

int main (void) {
	unsigned int mask1 = 0x0000F000;
	unsigned int mask2 = 0x00000F00;
	IODIR0 = 0x0000FF00;
	IOSET0 = 0x0000FF00;

	while(1){
		IOCLR0 = mask1;
		wait();
		IOSET0 = mask1;
		IOCLR0 = mask2;
		wait();
		IOSET0 = mask2;
	}
}
