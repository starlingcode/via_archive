/*
 * meta_aux_outputs.cpp
 *
 *  Created on: Sep 12, 2018
 *      Author: willmitchell
 */


#include "meta.hpp"

void ViaMeta::oversample(int32_t writeIndex) {

	int32_t samplesRemaining = outputBufferSize;

	int32_t readIndex = 0;

	while (samplesRemaining) {

		outputs.dac1Samples[writeIndex] = 4095 - metaWavetable.signalOut[readIndex];
		outputs.dac2Samples[writeIndex] = metaWavetable.signalOut[readIndex];

		readIndex ++;
		writeIndex ++;
		samplesRemaining --;

	}
}

void ViaMeta::addThreeBits(int32_t writeIndex) {

	int32_t dac2Sample = metaWavetable.signalOut[0];
	int32_t dac2Base = dac2Sample >> 3;
	int32_t dac1Sample = (32767 - dac2Sample);
	int32_t dac1Base = dac1Sample >> 3;

	int32_t dac1LSB = -(dac2Sample & 0b111);
	int32_t dac2LSB = -(dac2Sample & 0b111);

	int32_t samplesRemaining = outputBufferSize;

	while (samplesRemaining) {

		outputs.dac1Samples[writeIndex] = __USAT(dac1Base + (dac1LSB > 0), 12);
		outputs.dac2Samples[writeIndex] = __USAT(dac2Base + (dac2LSB > 0), 12);

//		outputs.dac1Samples[writeIndex] = dac1Base;
//		outputs.dac2Samples[writeIndex] = dac2Base;

		dac1LSB++;
		dac2LSB++;
		writeIndex ++;
		samplesRemaining --;

	}
}

void ViaMeta::drumMode(int32_t writeIndex) {

	ampEnvelope.advance(&inputs, wavetableReadDrum);
	freqTransient.advance(&inputs, wavetableReadDrum);
	morphEnvelope.advance(&inputs, wavetableReadDrum);

	freqTransient.output[0] *= transientScale;

	uint32_t ampScale = ampEnvelope.output[0] << 1;
	int32_t sample = metaWavetable.signalOut[0];

	int32_t dac1Sample = fix16_mul(32767 - sample, ampScale);
	int32_t dac2Sample = fix16_mul(sample, ampScale);

	// rectified
//	int32_t dac2Sample = (__USAT(sample - 2048, 12) * ampScale) >> 15;
//	int32_t dac1Sample = ((4095 - __USAT(sample + 2047, 12)) * ampScale) >> 15;

	int32_t dac1Base = dac1Sample >> 3;
	int32_t dac2Base = dac2Sample >> 3;
//
//	int32_t dac1LSB = -(dac1Sample - dac1Base);
//	int32_t dac2LSB = -(dac2Sample - dac2Base);

	int32_t samplesRemaining = outputBufferSize;

	while (samplesRemaining) {

		outputs.dac1Samples[writeIndex] = dac1Base;
		outputs.dac2Samples[writeIndex] = dac2Base;


//		outputs.dac1Samples[writeIndex] = __USAT(dac1Base + (dac1LSB > 0), 12);
//		outputs.dac2Samples[writeIndex] = __USAT(dac2Base + (dac2LSB > 0), 12);
//
//		dac1LSB ++;
//		dac2LSB ++;
		samplesRemaining --;
		writeIndex ++;

	}

}

void ViaMeta::calculateLogicAReleaseGate(int32_t writeIndex) {

	int32_t incrementReversed = ((uint32_t) metaController.incrementUsed >> 31);

	int32_t releasing = (metaController.ghostPhase >> 24) | metaController.atB;

	int32_t attacking = !releasing;

	outputs.logicA[writeIndex] = GET_ALOGIC_MASK((releasing | (attacking & incrementReversed)) * metaController.oscillatorOn);

}

void ViaMeta::calculateLogicAAttackGate(int32_t writeIndex) {

	int32_t incrementReversed = (uint32_t) metaController.incrementUsed >> 31;

	int32_t releasing = (metaController.ghostPhase >> 24) | metaController.atB;

	int32_t attacking = !releasing;

	outputs.logicA[writeIndex] = GET_ALOGIC_MASK(attacking | (releasing & incrementReversed));


}

void ViaMeta::calculateDac3Phasor(int32_t writeIndex) {

	int32_t samplesRemaining = outputBufferSize;
	int32_t readIndex = 0;

	while (samplesRemaining) {

		if (metaWavetable.phaseOut[readIndex] >> 31) {
			outputs.dac3Samples[writeIndex] = 8191 - (metaWavetable.phaseOut[readIndex] >> 19);
		} else {
			outputs.dac3Samples[writeIndex] = metaWavetable.phaseOut[readIndex] >> 19;
		}

		samplesRemaining --;
		readIndex ++;
		writeIndex ++;

	}
}

void ViaMeta::calculateDac3Contour(int32_t writeIndex) {

	int32_t samplesRemaining = outputBufferSize;
	int32_t readIndex = 0;

	while (samplesRemaining) {

		outputs.dac3Samples[writeIndex] = metaWavetable.signalOut[readIndex];

		samplesRemaining --;
		readIndex ++;
		writeIndex ++;

	}

}

void ViaMeta::calculateDac3PhasorEnv(int32_t writeIndex) {

	int32_t phasor = metaController.ghostPhase;

	if (phasor >> 24) {
		phasor = 8191 - (phasor >> 12);
	} else {
		phasor = phasor >> 12;
	}

	int32_t dac3OffsetScale = 61983;
	int32_t dac3Offset = 111;

	phasor = fix16_mul((phasor >> 1), dac3OffsetScale);

	phasor = __USAT(2048 - phasor - dac3Offset, 12) ;

	int32_t samplesRemaining = outputBufferSize;

	while (samplesRemaining) {

		outputs.dac3Samples[writeIndex] = phasor;

		samplesRemaining --;
		writeIndex ++;

	}

}

void ViaMeta::calculateDac3ContourEnv(int32_t writeIndex) {

	int32_t dac3OffsetScale = 61983;
	int32_t dac3Offset = 111;

	int32_t contour = fix16_mul(outputs.dac2Samples[writeIndex] >> 1, dac3OffsetScale);

	contour = 2048 - contour - dac3Offset;

	int32_t samplesRemaining = outputBufferSize;

	while (samplesRemaining) {

		outputs.dac3Samples[writeIndex] = contour;

		samplesRemaining --;
		writeIndex ++;

	}

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
			outputs.shA[writeIndex] = SH_A_SAMPLE_MASK * metaController.loopMode;
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

	outputs.shA[writeIndex] += SH_A_SAMPLE_MASK * !metaController.loopMode * !metaController.triggerSignal;

	if (!metaController.oscillatorOn) {
		outputs.shA[writeIndex] = SH_A_TRACK_MASK;
	}

}

// Resample B at A

void ViaMeta::calculateSHMode3(int32_t writeIndex) {


	switch (metaController.phaseEvent) {
		//no logic events
		case 0:
			outputs.shA[writeIndex] = SH_A_TRACK_MASK;
			outputs.shB[writeIndex] = SH_B_SAMPLE_MASK * metaController.oscillatorOn;
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
			outputs.shB[writeIndex] = SH_B_SAMPLE_MASK * metaController.oscillatorOn;
			break;
		//dummy at a handling
		case AT_A_FROM_RELEASE:
		case AT_A_FROM_ATTACK:
			outputs.shA[writeIndex] = SH_A_SAMPLE_MASK  * metaController.loopMode;
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

	outputs.shA[writeIndex] += SH_A_SAMPLE_MASK * !metaController.loopMode * !metaController.triggerSignal;

	if (!metaController.oscillatorOn) {
		outputs.shA[writeIndex] = SH_A_TRACK_MASK;
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
			outputs.shA[writeIndex] = SH_A_SAMPLE_MASK * metaController.loopMode;
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

	outputs.shA[writeIndex] += SH_A_SAMPLE_MASK * !metaController.loopMode * !metaController.triggerSignal;

	if (!metaController.oscillatorOn) {
		outputs.shA[writeIndex] = SH_A_TRACK_MASK;
	}

}

// Decimate (Resample A at B, resample B at A

void ViaMeta::calculateSHMode6(int32_t writeIndex) {


	switch (metaController.phaseEvent) {
		//no logic events
		case 0:
			outputs.shA[writeIndex] = SH_A_SAMPLE_MASK;
			outputs.shB[writeIndex] = SH_B_SAMPLE_MASK  * metaController.oscillatorOn;
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

