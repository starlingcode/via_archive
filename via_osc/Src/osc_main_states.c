#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"

#include "../inc/osc_main_states.h"
#include "signals.h"

/**
 *
 * States
 *
 */

// get next sample(s) then switch to ui handling state
void main_nextSample(void) {

	// call the appropriate function to fill the sample buffer per the current mode
	fillBuffer(&signals);

	// transition to the UI handling state when complete
	main_state = &main_idle;

}

// execute the touch sensor state machine and expander button
void main_idle(void) {


}

