/*
 * meta_aux_outputs.c
 *
 *  Created on: Aug 30, 2018
 *      Author: willmitchell
 */

#include "meta.h"

void meta_calculateLogicAGate(meta_signal_set *signals, int writeIndex) {

		switch (signals->meta_parameters->phaseEvent) {
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

void meta_calculateDac3Phasor(meta_signal_set * signals, int writeIndex) {

	int phase = signals->wavetable_parameters->phase;

	if (phase >> 24) {
		signals->outputs->dac3Samples[writeIndex] = 8191 - (phase >> 12);
	} else {
		signals->outputs->dac3Samples[writeIndex] = phase >> 12;
	}
}

void meta_calculateDac3Contour(meta_signal_set * signals, int writeIndex) {

	signals->outputs->dac3Samples[writeIndex] = signals->outputs->dac2Samples[writeIndex];

}

// No S&H

void meta_calculateSHMode1(meta_signal_set * signals, int writeIndex) {

	switch (signals->meta_parameters->phaseEvent) {
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

void meta_calculateSHMode2(meta_signal_set * signals, int writeIndex) {

	switch (signals->meta_parameters->phaseEvent) {
		//no logic events
		case 0:
			signals->outputs->shA[writeIndex] = GPIO_NOP;
			signals->outputs->shB[writeIndex] = SH_B_TRACK_MASK;
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
			signals->outputs->shB[writeIndex] = SH_B_TRACK_MASK;
			break;
		default:
			break;
	}

}

// Resample B at A

void meta_calculateSHMode3(meta_signal_set * signals, int writeIndex) {


	switch (signals->meta_parameters->phaseEvent) {
		//no logic events
		case 0:
			signals->outputs->shA[writeIndex] = SH_A_TRACK_MASK;
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

// Sample A from A to B and resample B at A

void meta_calculateSHMode4(meta_signal_set * signals, int writeIndex) {

	switch (signals->meta_parameters->phaseEvent) {
		//no logic events
		case 0:
			signals->outputs->shA[writeIndex] = GPIO_NOP;
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

// Half Decimate (Sample A from A to B sample B from B to A

void meta_calculateSHMode5(meta_signal_set * signals, int writeIndex) {

	switch (signals->meta_parameters->phaseEvent) {
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

// Decimate (Resample A at B, resample B at A

void meta_calculateSHMode6(meta_signal_set * signals, int writeIndex) {


	switch (signals->meta_parameters->phaseEvent) {
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
