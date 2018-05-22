#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"
#include "main_state_machine.h"
#include "dsp.h"

arm_fir_instance_q31 fir;

/**
 *
 * States
 *
 */

// update logic outs then switch to the appropriate state per the runtime display flag
void main_handleLogic(int signal) {

	// the logic handling actually happens in signal handlers

	// otherwise, switch to the sample generation state

	main_State = &main_fillBuffer;


	// call the appropriate handler function per the signal
	parseSignal(signal);

}

// get next sample(s) then switch to ui handling state
void main_fillBuffer(int signal) {

	int phaseArray[BUFFER_SIZE];

	for (int i = 0; i < (BUFFER_SIZE); i++) {
		incrementOscillator(inputRead, outputWrite, &phaseArray, i);
	}

	for (int i = 0; i < (BUFFER_SIZE); i++) {
		calculateLogic(&phaseArray, outputWrite, i);
	}

	//arm_fir_fast_q31(&fir, outputWrite->samples, outputWrite->samples, BUFFER_SIZE);

	// TODO in separate timer interrupt, service LED display from logic struct

	main_State = &main_handleUI;

	parseSignal(signal);

}

// execute the touch sensor state machine and expander button
void main_handleUI(int signal) {

	implementUI();

	parseSignal(signal);

	// continue to call the handle UI state until a DAC timer overrun

}
