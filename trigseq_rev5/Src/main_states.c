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
void main_nextSample(void) {

	// transition to the UI handling state when complete
	main_State = &main_handleUI;

}

// execute the touch sensor state machine and expander button
void main_handleUI(void) {

	implementUI();

	// continue to call the handle UI state until the end of current output read buffer

}
