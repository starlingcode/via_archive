
#include "signals.h"
#include "sync_next_sample.h"
#include "via_rev5_hardware_io.h"

/*
 *
 * Logic functions
 *
 */

void calculateLogicAGate(viaStateVariableSet * stateVariables, audioRateOutputs * output) {

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

void calculateLogicADelta(viaStateVariableSet * stateVariables, audioRateOutputs * output) {

		switch (stateVariables->delta) {
			//no logic events
			case 0:
				output->logicAHandler = ALOGIC_LOW_MASK;
				break;
			//dummy at a handling
			case 1:
				output->logicAHandler = ALOGIC_HIGH_MASK;
				break;
			default:
				break;
		}

}

void calculateDac3(viaStateVariableSet * stateVariables, audioRateOutputs * output) {

	int phase = stateVariables->phase;

	if (phase >> 24) {
		output->dac3Sample = 8191 - (phase >> 12);
	} else {
		output->dac3Sample = phase >> 12;
	}

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



