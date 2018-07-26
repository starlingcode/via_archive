#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"
#include "main_state_machine.h"
#include "dsp.h"
#include "fill_buffer.h"
#include "via_rev5_hardware_io.h"

/*
 *
 * Logic functions
 *
 */

void calculateLogicA(viaStateVariableSet * stateVariables, audioRateOutputs * output) {

		switch (stateVariables->phaseEvent) {
			//no logic events
			case 0:
				output->logicAHandler = GPIO_NOP;
				break;
			//dummy at a handling
			case AT_A_FROM_RELEASE:
			case AT_A_FROM_ATTACK:
				output->logicAHandler = ALOGIC_HIGH_MASK;
				break;
			//dummy at b handling
			case AT_B_FROM_RELEASE:
			case AT_B_FROM_ATTACK:
				output->logicAHandler = ALOGIC_LOW_MASK;
				break;
			default:
				break;
		}


}

void calculateDac3(viaStateVariableSet * stateVariables, audioRateOutputs * output) {


	output->dac3Sample = stateVariables->delta << 12;



}



// No S&H

void calculateSHMode1(viaStateVariableSet * stateVariables, audioRateOutputs * output) {

		switch (stateVariables->phaseEvent) {
			//no logic events
			case 0:
				output->shAHandler = SH_A_TRACK_MASK;
				output->shBHandler = SH_B_TRACK_MASK;
				break;
			//dummy at a handling
			case AT_A_FROM_RELEASE:
			case AT_A_FROM_ATTACK:
				output->shAHandler = SH_A_TRACK_MASK;
				output->shBHandler = SH_B_TRACK_MASK;
				break;
			//dummy at b handling
			case AT_B_FROM_RELEASE:
			case AT_B_FROM_ATTACK:
				output->shAHandler = SH_A_TRACK_MASK;
				output->shBHandler = SH_B_TRACK_MASK;
				break;
			default:
				break;
		}


}

// Sample and track

void calculateSHMode2(viaStateVariableSet * stateVariables, audioRateOutputs * output) {

		switch (stateVariables->phaseEvent) {
			//no logic events
			case 0:
				output->shAHandler = GPIO_NOP;
				output->shBHandler = GPIO_NOP;
				break;
			//dummy at a handling
			case AT_A_FROM_RELEASE:
			case AT_A_FROM_ATTACK:
				output->shAHandler = SH_A_SAMPLE_MASK;
				output->shBHandler = SH_B_TRACK_MASK;
				break;
			//dummy at b handling
			case AT_B_FROM_RELEASE:
			case AT_B_FROM_ATTACK:
				output->shAHandler = SH_A_TRACK_MASK;
				output->shBHandler = SH_B_SAMPLE_MASK;
				break;
			default:
				break;
		}

}

// Decimate

void calculateSHMode3(viaStateVariableSet * stateVariables, audioRateOutputs * output) {

		switch (stateVariables->phaseEvent) {
			//no logic events
			case 0:
				output->shAHandler = SH_A_SAMPLE_MASK;
				output->shBHandler = SH_B_SAMPLE_MASK;
				break;
			//dummy at a handling
			case AT_A_FROM_RELEASE:
			case AT_A_FROM_ATTACK:
				output->shAHandler = SH_A_SAMPLE_MASK;
				output->shBHandler = SH_B_TRACK_MASK;
				break;
			//dummy at b handling
			case AT_B_FROM_RELEASE:
			case AT_B_FROM_ATTACK:
				output->shAHandler = SH_A_TRACK_MASK;
				output->shBHandler = SH_B_SAMPLE_MASK;
				break;
			default:
				break;
		}

}



