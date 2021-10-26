#include <LPC214x.H>

void wait (void) {
    int d;

    for(d=0; d<10000000; d++);
}

int main (void) {
    unsigned int i;

	while(1){
    IODIR0 = 0x0000FF00;
    IOSET0 = 0x0000FF00;
    wait();
    IOCLR0 = 0x0000FF00;
    wait();
	}
}