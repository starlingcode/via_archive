#ifndef MAIN_STATE_MACHINE
#define MAIN_STATE_MACHINE

/**
 *
 * Main oscillator state machine
 *
 */

void (*main_state)(void);

/**
 *
 * States
 *
 *  the state machine is scarcely more than a function pointer
 *  signals have not needed to be implemented, but the function calls in an int
 *  a DSP buffer overrun switches the state to fillBuffer
 *  the completion of the fillBuffer function initiates a transition to the handleUI state
 *
 *
 */

// get next sample(s) then switch to ui handling state
void main_nextSample(void);

// execute the touch sensor state machine and expander button
void main_idle(void);

void scannerInit(void);


#endif




