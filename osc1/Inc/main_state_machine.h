#ifndef MAIN_STATE_MACHINE
#define MAIN_STATE_MACHINE


#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"
#include "dsp.h"


/**
 *
 * Main oscillator state machine
 *
 */

void (*main_State)(void);

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
void main_fillBuffer(void);

// execute the touch sensor state machine and expander button
void main_handleUI(void);

/**
 *
 * Main state machine helper functions
 *
 */

// wrapper for implementing the UI
void implementUI(void);

// pointers and functions to show the mode
// these are probably out of place here
// TODO show sync mode
// TODO show (and implement) morph mode
void (*displaySHMode)(void);
void (*displaySyncMode)(void);
void (*displayXCVMode)(void);
void (*displayMorphMode)(void);

void displayXCV_FM(void);
void displayXCV_PM(void);
void displayMorph_Morph(void);
void displayMorph_PMW(void);
void displaySH_On(void);
void displaySH_Off(void);
void displaySync_Hard(void);
void displaySync_Soft(void);

void updateRGB(controlRateInputs *, audioRateInputs *);

#endif




