
// Title
// @authors Griffin Davis and Sydnee Haney

#include "LPC214x.h"
#include "StepMotor.h"
#include "Timer.h"

void Step_Init(void) {
    IODIR0 |= _fwd_phase | _rev_phase;
    IOCLR0 |= _fwd_phase | _rev_phase;
}

int Step_Forward(unsigned int currentStep, unsigned int steps) {
    int i=0;
    for (i=0; i<steps; i++) {
        delayMs(_stepDelay_ms);
        IOSET0 |= _fwd_phase;
        delayMs(_stepDelay_ms);
        IOSET0 |= _rev_phase;
        delayMs(_stepDelay_ms);
        IOCLR0 |= _fwd_phase;
        delayMs(_stepDelay_ms);
        IOCLR0 |= _rev_phase;
    }
    return (currentStep + steps) % 5;
}
