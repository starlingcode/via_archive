/*
 * sync_aux_outputs.c
 *
 *  Created on: Aug 30, 2018
 *      Author: willmitchell
 */

#include "sync.hpp"

void ViaSync::calculateLogicAGate(int32_t writeIndex) {

		switch (syncWavetable.phaseEvent) {
			//no logic events
			case 0:
				outputs.logicA[writeIndex] = GPIO_NOP;
				break;
			//dummy at a handling
			case AT_A_FROM_RELEASE:
			case AT_A_FROM_ATTACK:
				outputs.logicA[writeIndex] = ALOGIC_HIGH_MASK;
				break;
			//dummy at b handling
			case AT_B_FROM_RELEASE:
			case AT_B_FROM_ATTACK:
				outputs.logicA[writeIndex] = ALOGIC_LOW_MASK;
				break;
			default:
				break;
		}

}

void ViaSync::calculateLogicADelta(int32_t writeIndex) {

	outputs.logicA[writeIndex] = GET_ALOGIC_MASK(syncWavetable.delta);

}

void ViaSync::calculateDac3Phasor(int32_t writeIndex) {

	int32_t phase = syncWavetable.phase;

	if (phase >> 24) {
		outputs.dac3Samples[writeIndex] = 8191 - (phase >> 12);
	} else {
		outputs.dac3Samples[writeIndex] = phase >> 12;
	}
}

void ViaSync::calculateDac3Contour(int32_t writeIndex) {

	outputs.dac3Samples[writeIndex] = outputs.dac2Samples[writeIndex];

}

// No S&H

void ViaSync::calculateSHMode1(int32_t writeIndex) {

	switch (syncWavetable.phaseEvent) {
		//no logic events
		case 0:
			outputs.shA[writeIndex] = SH_A_TRACK_MASK;
			outputs.shB[writeIndex] = SH_B_TRACK_MASK;
			break;
		//dummy at a handling
		case AT_A_FROM_RELEASE:
		case AT_A_FROM_ATTACK:
			outputs.shA[writeIndex] = SH_A_TRACK_MASK;
			outputs.shB[writeIndex] = SH_B_TRACK_MASK;
			break;
		//dummy at b handling
		case AT_B_FROM_RELEASE:
		case AT_B_FROM_ATTACK:
			outputs.shA[writeIndex] = SH_A_TRACK_MASK;
			outputs.shB[writeIndex] = SH_B_TRACK_MASK;
			break;
		default:
			break;
	}

}

// Sample A from A to B

void ViaSync::calculateSHMode2(int32_t writeIndex) {

	switch (syncWavetable.phaseEvent) {
		//no logic events
		case 0:
			outputs.shA[writeIndex] = GPIO_NOP;
			outputs.shB[writeIndex] = GPIO_NOP;
			break;
		//dummy at a handling
		case AT_A_FROM_RELEASE:
		case AT_A_FROM_ATTACK:
			outputs.shA[writeIndex] = SH_A_SAMPLE_MASK;
			outputs.shB[writeIndex] = SH_B_TRACK_MASK;
			break;
		//dummy at b handling
		case AT_B_FROM_RELEASE:
		case AT_B_FROM_ATTACK:
			outputs.shA[writeIndex] = SH_A_TRACK_MASK;
			outputs.shB[writeIndex] = SH_B_SAMPLE_MASK;
			break;
		default:
			break;
	}

}

// Resample B at A

void ViaSync::calculateSHMode3(int32_t writeIndex) {


	switch (syncWavetable.phaseEvent) {
		//no logic events
		case 0:
			outputs.shA[writeIndex] = SH_A_SAMPLE_MASK;
			outputs.shB[writeIndex] = SH_B_SAMPLE_MASK;
			break;
		//dummy at a handling
		case AT_A_FROM_RELEASE:
		case AT_A_FROM_ATTACK:
			outputs.shA[writeIndex] = SH_A_SAMPLE_MASK;
			outputs.shB[writeIndex] = SH_B_TRACK_MASK;
			break;
		//dummy at b handling
		case AT_B_FROM_RELEASE:
		case AT_B_FROM_ATTACK:
			outputs.shA[writeIndex] = SH_A_TRACK_MASK;
			outputs.shB[writeIndex] = SH_B_SAMPLE_MASK;
			break;
		default:
			break;
	}


}
