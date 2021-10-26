#include <LPC214x.H>

/**
 * @authors Griffin Davis, Sydnee Haney
 */
void wait (void) {
    int d;

    for(d=0; d<2500000; d++);
}

int main (void) {
    unsigned int mask = 0x00000100;
    unsigned int dir = 0;
    IODIR0 = 0x0000FF00;
    IOCLR0 = 0x0000FF00;

	while(1){
        if (dir) mask = mask << 1;
        else mask = mask >> 1;

        IOSET0 = mask;
        wait();
        IOCLR0 = mask;

        if( (mask & 0x00008000) || (mask & 0x00000100)) dir = !dir;
	}
}
