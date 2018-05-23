#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"
#include "main_state_machine.h"
#include "dsp.h"

/**
 *
 * States
 *
 */

// get next sample(s) then switch to ui handling state
void main_fillBuffer(int signal) {

	// call the appropriate function to fill the sample buffer per the current mode
	(*fillBuffer)();

	// transition to the UI handling state when complete
	main_State = &main_handleUI;

}

// execute the touch sensor state machine and expander button
void main_handleUI(int signal) {

	implementUI();

	// continue to call the handle UI state until the end of current output read buffer

}
