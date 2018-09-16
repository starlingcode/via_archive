/*
 * meta_aux_outputs.cpp
 *
 *  Created on: Sep 12, 2018
 *      Author: willmitchell
 */


#include "meta.hpp"

void ViaMeta::drumModeOff(int writeIndex) {
	system.outputs.dac1Samples[writeIndex] = 4095 - system.outputs.dac2Samples[writeIndex];
}

void ViaMeta::drumModeOn(int writeIndex) {
	drumEnvelope.advance(&system.inputs, wavetableReadDrum);
	uint32_t ampScale = drumEnvelope.output[0] << 1;
	int sample = system.outputs.dac2Samples[writeIndex];
	system.outputs.dac2Samples[writeIndex] = (__USAT(sample - 2048, 12) * ampScale) >> 16;
	system.outputs.dac1Samples[writeIndex] = ((4095 - __USAT(sample + 2048, 12)) * ampScale) >> 16;
}

void ViaMeta::calculateLogicAReleaseGate(int writeIndex) {

		switch (metaController.phaseEvent) {
			//no logic events
			case 0:
				system.outputs.logicA[writeIndex] = GPIO_NOP;
				break;
			//dummy at a handling
			case AT_A_FROM_RELEASE:
			case AT_A_FROM_ATTACK:
				system.outputs.logicA[writeIndex] = ALOGIC_LOW_MASK;
				break;
			//dummy at b handling
			case AT_B_FROM_RELEASE:
			case AT_B_FROM_ATTACK:
				system.outputs.logicA[writeIndex] = ALOGIC_HIGH_MASK;
				break;
			default:
				break;
		}

}

void ViaMeta::calculateLogicAAttackGate(int writeIndex) {

		switch (metaController.phaseEvent) {
			//no logic events
			case 0:
				system.outputs.logicA[writeIndex] = GPIO_NOP;
				break;
			//dummy at a handling
			case AT_A_FROM_RELEASE:
			case AT_A_FROM_ATTACK:
				system.outputs.logicA[writeIndex] = ALOGIC_HIGH_MASK;
				break;
			//dummy at b handling
			case AT_B_FROM_RELEASE:
			case AT_B_FROM_ATTACK:
				system.outputs.logicA[writeIndex] = ALOGIC_LOW_MASK;
				break;
			default:
				break;
		}

}

void ViaMeta::calculateDac3Phasor(int writeIndex) {

	int phase = metaWavetable.phase;

	if (phase >> 24) {
		system.outputs.dac3Samples[writeIndex] = 8191 - (phase >> 12);
	} else {
		system.outputs.dac3Samples[writeIndex] = phase >> 12;
	}
}

void ViaMeta::calculateDac3Contour(int writeIndex) {

	system.outputs.dac3Samples[writeIndex] = system.outputs.dac2Samples[writeIndex];

}

// No S&H

void ViaMeta::calculateSHMode1(int writeIndex) {

	switch (metaController.phaseEvent) {
		//no logic events
		case 0:
			system.outputs.shA[writeIndex] = SH_A_TRACK_MASK;
			system.outputs.shB[writeIndex] = SH_B_TRACK_MASK;
			break;
		//dummy at a handling
		case AT_A_FROM_RELEASE:
		case AT_A_FROM_ATTACK:
			system.outputs.shA[writeIndex] = SH_A_TRACK_MASK;
			system.outputs.shB[writeIndex] = SH_B_TRACK_MASK;
			break;
		//dummy at b handling
		case AT_B_FROM_RELEASE:
		case AT_B_FROM_ATTACK:
			system.outputs.shA[writeIndex] = SH_A_TRACK_MASK;
			system.outputs.shB[writeIndex] = SH_B_TRACK_MASK;
			break;
		default:
			break;
	}

}

// Sample A from A to B

void ViaMeta::calculateSHMode2(int writeIndex) {

	switch (metaController.phaseEvent) {
		//no logic events
		case 0:
			system.outputs.shA[writeIndex] = GPIO_NOP;
			system.outputs.shB[writeIndex] = SH_B_TRACK_MASK;
			break;
		//dummy at a handling
		case AT_A_FROM_RELEASE:
		case AT_A_FROM_ATTACK:
			system.outputs.shA[writeIndex] = SH_A_SAMPLE_MASK;
			system.outputs.shB[writeIndex] = SH_B_TRACK_MASK;
			break;
		//dummy at b handling
		case AT_B_FROM_RELEASE:
		case AT_B_FROM_ATTACK:
			system.outputs.shA[writeIndex] = SH_A_TRACK_MASK;
			system.outputs.shB[writeIndex] = SH_B_TRACK_MASK;
			break;
		default:
			break;
	}

}

// Resample B at A

void ViaMeta::calculateSHMode3(int writeIndex) {


	switch (metaController.phaseEvent) {
		//no logic events
		case 0:
			system.outputs.shA[writeIndex] = SH_A_TRACK_MASK;
			system.outputs.shB[writeIndex] = SH_B_SAMPLE_MASK;
			break;
		//dummy at a handling
		case AT_A_FROM_RELEASE:
		case AT_A_FROM_ATTACK:
			system.outputs.shA[writeIndex] = SH_A_SAMPLE_MASK;
			system.outputs.shB[writeIndex] = SH_B_TRACK_MASK;
			break;
		//dummy at b handling
		case AT_B_FROM_RELEASE:
		case AT_B_FROM_ATTACK:
			system.outputs.shA[writeIndex] = SH_A_TRACK_MASK;
			system.outputs.shB[writeIndex] = SH_B_SAMPLE_MASK;
			break;
		default:
			break;
	}


}

// Sample A from A to B and resample B at A

void ViaMeta::calculateSHMode4(int writeIndex) {

	switch (metaController.phaseEvent) {
		//no logic events
		case 0:
			system.outputs.shA[writeIndex] = GPIO_NOP;
			system.outputs.shB[writeIndex] = SH_B_SAMPLE_MASK;
			break;
		//dummy at a handling
		case AT_A_FROM_RELEASE:
		case AT_A_FROM_ATTACK:
			system.outputs.shA[writeIndex] = SH_A_SAMPLE_MASK;
			system.outputs.shB[writeIndex] = SH_B_TRACK_MASK;
			break;
		//dummy at b handling
		case AT_B_FROM_RELEASE:
		case AT_B_FROM_ATTACK:
			system.outputs.shA[writeIndex] = SH_A_TRACK_MASK;
			system.outputs.shB[writeIndex] = SH_B_SAMPLE_MASK;
			break;
		default:
			break;
	}

}

// Half Decimate (Sample A from A to B sample B from B to A

void ViaMeta::calculateSHMode5(int writeIndex) {

	switch (metaController.phaseEvent) {
		//no logic events
		case 0:
			system.outputs.shA[writeIndex] = GPIO_NOP;
			system.outputs.shB[writeIndex] = GPIO_NOP;
			break;
		//dummy at a handling
		case AT_A_FROM_RELEASE:
		case AT_A_FROM_ATTACK:
			system.outputs.shA[writeIndex] = SH_A_SAMPLE_MASK;
			system.outputs.shB[writeIndex] = SH_B_TRACK_MASK;
			break;
		//dummy at b handling
		case AT_B_FROM_RELEASE:
		case AT_B_FROM_ATTACK:
			system.outputs.shA[writeIndex] = SH_A_TRACK_MASK;
			system.outputs.shB[writeIndex] = SH_B_SAMPLE_MASK;
			break;
		default:
			break;
	}

}

// Decimate (Resample A at B, resample B at A

void ViaMeta::calculateSHMode6(int writeIndex) {


	switch (metaController.phaseEvent) {
		//no logic events
		case 0:
			system.outputs.shA[writeIndex] = SH_A_SAMPLE_MASK;
			system.outputs.shB[writeIndex] = SH_B_SAMPLE_MASK;
			break;
		//dummy at a handling
		case AT_A_FROM_RELEASE:
		case AT_A_FROM_ATTACK:
			system.outputs.shA[writeIndex] = SH_A_SAMPLE_MASK;
			system.outputs.shB[writeIndex] = SH_B_TRACK_MASK;
			break;
		//dummy at b handling
		case AT_B_FROM_RELEASE:
		case AT_B_FROM_ATTACK:
			system.outputs.shA[writeIndex] = SH_A_TRACK_MASK;
			system.outputs.shB[writeIndex] = SH_B_SAMPLE_MASK;
			break;
		default:
			break;
	}

}

