
#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"

struct parameters {

	int coarsePitch;
	int finePitch;
	int voltOct;
	int xCV;
	int morph;
	int direction;

};

struct oscillator {

	int increment;
	int phase;

};

//declare output separately to be passed to the interrupt
int output;

/**
 *
 * Main oscillator state machine
 *
 */

enum mainSignal {

	MAIN_EXECUTE,
	MAIN_RISING_EDGE,
	MAIN_FALLING_EDGE,
	MAIN_AUX_RISING_EDGE,
	MAIN_AUX_FALLING_EDGE,
	MAIN_ADC1_CONV_COMPLETE,
	MAIN_ADC2_CONV_COMPLETE,
	MAIN_ADC3_CONV_COMPLETE,

};

// main state machine
void *(main_State)(int);

// output info from last sample
void main_handleLogic(int);
void main_updateDisplay(int);

// get next sample
void main_fillBuffer(int);

// execute the touch sensor state machine and expander button
void main_handleUI(int);

// dispatch signal to state machine
void mainDispatch(int);

// generate sample from parameters (separated to be later rolled into DSP loop)
void generatePhase(void);
void interpolate(void);

// helper functions to parse hardware inputs and generate oscillator parameters
void handleADC1Conversion(int);
void handleADC2Conversion(int);
void handleADC3Conversion(int);
void handleRisingEdge(int);
void handleFallingEdge(int);
void handleAuxRisingEdge(int);
void handleAuxFallingEdge(int);






