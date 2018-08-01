
#include "signals.h"
#include "sync_next_sample.h"
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

	static int lastDelta;
	static int lastPhase;
	static int lastSample;
	static int deltaChanged;
	int thisSample;
	int blep;
	int delta;
	int phase;

	delta = (stateVariables->delta) * 2 - 1;
	phase = stateVariables->phase;

	if (lastDelta != delta) {

		int impulsePhase = phase & 0xFFFF0000;
		int thisFractionalPhase = phase - impulsePhase;
		int lastFractionalPhase = impulsePhase - lastPhase;
		int increment = stateVariables->incrementValue1;

		int lastBlepCoefficient = (lastFractionalPhase << 16) / increment;
		int lastBlep = (lastBlepCoefficient << 1) - fix16_square(lastBlepCoefficient) - (1 << 16);
		lastSample -= lastBlep * (delta);

		int thisBlepCoefficient = (thisFractionalPhase << 16) / increment;
		int thisBlep = fix16_square(thisBlepCoefficient) + (thisBlepCoefficient << 1) + (1 << 16);
		thisSample = (delta << 16) - thisBlep * (delta);

	}
	else {
		thisSample = (delta << 16);
	}

	output->dac3Sample = ((lastSample >> 6) + 2048);

	lastSample = thisSample;
	lastPhase = phase;
	lastDelta = delta;

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



