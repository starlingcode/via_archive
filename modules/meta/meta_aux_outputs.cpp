/*
 * meta_aux_outputs.cpp
 *
 *  Created on: Sep 12, 2018
 *      Author: willmitchell
 */


#include "meta.hpp"

void ViaMeta::drumModeOff(int32_t writeIndex) {
	outputs.dac1Samples[writeIndex] = 4095 - outputs.dac2Samples[writeIndex];
}

void ViaMeta::drumModeOn(int32_t writeIndex) {
	drumEnvelope.advance(&inputs, wavetableReadDrum);
	uint32_t ampScale = drumEnvelope.output[0] << 1;
	int32_t sample = outputs.dac2Samples[writeIndex];
	outputs.dac2Samples[writeIndex] = (__USAT(sample - 2048, 12) * ampScale) >> 15;
	outputs.dac1Samples[writeIndex] = ((4095 - __USAT(sample + 2048, 12)) * ampScale) >> 15;
}

void ViaMeta::calculateLogicAReleaseGate(int32_t writeIndex) {

		switch (metaController.phaseEvent) {
			//no logic events
			case 0:
				outputs.logicA[writeIndex] = GPIO_NOP;
				break;
			//dummy at a handling
			case AT_A_FROM_RELEASE:
			case AT_A_FROM_ATTACK:
				outputs.logicA[writeIndex] = ALOGIC_LOW_MASK;
				break;
			//dummy at b handling
			case AT_B_FROM_RELEASE:
			case AT_B_FROM_ATTACK:
				outputs.logicA[writeIndex] = ALOGIC_HIGH_MASK;
				break;
			default:
				break;
		}

}

void ViaMeta::calculateLogicAAttackGate(int32_t writeIndex) {

		switch (metaController.phaseEvent) {
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

void ViaMeta::calculateDac3Phasor(int32_t writeIndex) {

	int32_t phase = metaWavetable.phase;

	if (phase >> 24) {
		outputs.dac3Samples[writeIndex] = 8191 - (phase >> 12);
	} else {
		outputs.dac3Samples[writeIndex] = phase >> 12;
	}

	outputs.dac3Samples[writeIndex] = 4095 - outputs.dac3Samples[writeIndex];

}

void ViaMeta::calculateDac3Contour(int32_t writeIndex) {

	outputs.dac3Samples[writeIndex] = (4095 - outputs.dac2Samples[writeIndex]);

}

void ViaMeta::calculateDac3PhasorEnv(int32_t writeIndex) {

	int32_t phase = metaWavetable.phase;

	if (phase >> 24) {
		outputs.dac3Samples[writeIndex] = 8191 - (phase >> 12);
	} else {
		outputs.dac3Samples[writeIndex] = phase >> 12;
	}

	outputs.dac3Samples[writeIndex] = 2048 - (outputs.dac3Samples[writeIndex] >> 1);

}

void ViaMeta::calculateDac3ContourEnv(int32_t writeIndex) {

	outputs.dac3Samples[writeIndex] = 2048 - (outputs.dac2Samples[writeIndex] >> 1);

}

// No S&H

void ViaMeta::calculateSHMode1(int32_t writeIndex) {

	switch (metaController.phaseEvent) {
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

void ViaMeta::calculateSHMode2(int32_t writeIndex) {

	switch (metaController.phaseEvent) {
		//no logic events
		case 0:
			outputs.shA[writeIndex] = GPIO_NOP;
			outputs.shB[writeIndex] = SH_B_TRACK_MASK;
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
			outputs.shB[writeIndex] = SH_B_TRACK_MASK;
			break;
		default:
			break;
	}

}

// Resample B at A

void ViaMeta::calculateSHMode3(int32_t writeIndex) {


	switch (metaController.phaseEvent) {
		//no logic events
		case 0:
			outputs.shA[writeIndex] = SH_A_TRACK_MASK;
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

// Sample A from A to B and resample B at A

void ViaMeta::calculateSHMode4(int32_t writeIndex) {

	switch (metaController.phaseEvent) {
		//no logic events
		case 0:
			outputs.shA[writeIndex] = GPIO_NOP;
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

// Half Decimate (Sample A from A to B sample B from B to A

void ViaMeta::calculateSHMode5(int32_t writeIndex) {

	switch (metaController.phaseEvent) {
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

// Decimate (Resample A at B, resample B at A

void ViaMeta::calculateSHMode6(int32_t writeIndex) {


	switch (metaController.phaseEvent) {
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

