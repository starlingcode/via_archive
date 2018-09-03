/*
 * sync_aux_outputs.c
 *
 *  Created on: Aug 30, 2018
 *      Author: willmitchell
 */

#include "sync.h"

void sync_calculateLogicAGate(sync_signal_set *signals, int writeIndex) {

		switch (signals->wavetable_parameters->phaseEvent) {
			//no logic events
			case 0:
				signals->outputs->logicA[writeIndex] = GPIO_NOP;
				break;
			//dummy at a handling
			case AT_A_FROM_RELEASE:
			case AT_A_FROM_ATTACK:
				signals->outputs->logicA[writeIndex] = ALOGIC_HIGH_MASK;
				break;
			//dummy at b handling
			case AT_B_FROM_RELEASE:
			case AT_B_FROM_ATTACK:
				signals->outputs->logicA[writeIndex] = ALOGIC_LOW_MASK;
				break;
			default:
				break;
		}

}

void sync_calculateLogicADelta(sync_signal_set *signals, int writeIndex) {

	signals->outputs->logicA[writeIndex] = GET_ALOGIC_MASK(signals->wavetable_parameters->delta);

}

void sync_calculateDac3Phasor(sync_signal_set * signals, int writeIndex) {

	int phase = signals->wavetable_parameters->phase;

	if (phase >> 24) {
		signals->outputs->dac3Samples[writeIndex] = 8191 - (phase >> 12);
	} else {
		signals->outputs->dac3Samples[writeIndex] = phase >> 12;
	}
}

void sync_calculateDac3Contour(sync_signal_set * signals, int writeIndex) {

	signals->outputs->dac3Samples[writeIndex] = signals->outputs->dac2Samples[writeIndex];

}

// No S&H

void sync_calculateSHMode1(sync_signal_set * signals, int writeIndex) {

	switch (signals->wavetable_parameters->phaseEvent) {
		//no logic events
		case 0:
			signals->outputs->shA[writeIndex] = SH_A_TRACK_MASK;
			signals->outputs->shB[writeIndex] = SH_B_TRACK_MASK;
			break;
		//dummy at a handling
		case AT_A_FROM_RELEASE:
		case AT_A_FROM_ATTACK:
			signals->outputs->shA[writeIndex] = SH_A_TRACK_MASK;
			signals->outputs->shB[writeIndex] = SH_B_TRACK_MASK;
			break;
		//dummy at b handling
		case AT_B_FROM_RELEASE:
		case AT_B_FROM_ATTACK:
			signals->outputs->shA[writeIndex] = SH_A_TRACK_MASK;
			signals->outputs->shB[writeIndex] = SH_B_TRACK_MASK;
			break;
		default:
			break;
	}

}

// Sample A from A to B

void sync_calculateSHMode2(sync_signal_set * signals, int writeIndex) {

	switch (signals->wavetable_parameters->phaseEvent) {
		//no logic events
		case 0:
			signals->outputs->shA[writeIndex] = GPIO_NOP;
			signals->outputs->shB[writeIndex] = GPIO_NOP;
			break;
		//dummy at a handling
		case AT_A_FROM_RELEASE:
		case AT_A_FROM_ATTACK:
			signals->outputs->shA[writeIndex] = SH_A_SAMPLE_MASK;
			signals->outputs->shB[writeIndex] = SH_B_TRACK_MASK;
			break;
		//dummy at b handling
		case AT_B_FROM_RELEASE:
		case AT_B_FROM_ATTACK:
			signals->outputs->shA[writeIndex] = SH_A_TRACK_MASK;
			signals->outputs->shB[writeIndex] = SH_B_SAMPLE_MASK;
			break;
		default:
			break;
	}

}

// Resample B at A

void sync_calculateSHMode3(sync_signal_set * signals, int writeIndex) {


	switch (signals->wavetable_parameters->phaseEvent) {
		//no logic events
		case 0:
			signals->outputs->shA[writeIndex] = SH_A_SAMPLE_MASK;
			signals->outputs->shB[writeIndex] = SH_B_SAMPLE_MASK;
			break;
		//dummy at a handling
		case AT_A_FROM_RELEASE:
		case AT_A_FROM_ATTACK:
			signals->outputs->shA[writeIndex] = SH_A_SAMPLE_MASK;
			signals->outputs->shB[writeIndex] = SH_B_TRACK_MASK;
			break;
		//dummy at b handling
		case AT_B_FROM_RELEASE:
		case AT_B_FROM_ATTACK:
			signals->outputs->shA[writeIndex] = SH_A_TRACK_MASK;
			signals->outputs->shB[writeIndex] = SH_B_SAMPLE_MASK;
			break;
		default:
			break;
	}


}
