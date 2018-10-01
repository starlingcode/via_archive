/*
 * signal_processor_resources.c
 *
 *  Created on: Aug 22, 2018
 *      Author: willmitchell
 */

#include <cmsis_dsp.hpp>
#include "signal_processors.hpp"

extern "C" {


/**
 *
 * Helper functions for filling the sample buffer
 *
 */

void extractDeltas(int32_t * input, int32_t * output, int32_t initialValue, uint32_t bufferSize) {

	output[0] = input[0] - initialValue;
	for (uint32_t i = 1; i< bufferSize; i++) {
		output[i] = input[i] - input[i-1];
	}

}
void incrementFromDeltas(int32_t * input, int32_t * output, int32_t * hardSync, int32_t * reverse,
		int32_t initialPhase, uint32_t bufferSize) {

	output[0] = (initialPhase + (input[0] * reverse[0])) * hardSync[0];
	for (uint32_t i = 1; i< bufferSize; i++) {
		output[i] = (output[i-1] + (input[i] * reverse[i])) * hardSync[i];
	}

}

void foldBuffer(int32_t * input, int32_t offset, int32_t * output, uint32_t bufferSize) {

	// scale the CVs by the knob value cast from 0 to full scale int32_t, then shift left by 3

	VIA_SCALE_Q31((q31_t *) input, 1 << 31, 1, (q31_t *) output, bufferSize);
	VIA_OFFSET_Q31((q31_t *) output, (offset - 2048) << 4, (q31_t *) output, bufferSize);

	for (uint32_t i = 0; i < (bufferSize); i++) {

		output[i] = foldSignal16Bit(output[i]);

	}

}

void wrapBuffer(int32_t * input, int32_t offset, int32_t * output, uint32_t bufferSize) {

	// scale the CVs by the knob value cast from 0 to full scale int32_t, then shift left by 3

	VIA_SCALE_Q31((q31_t *) input, 1 << 31, 6, (q31_t *) output, bufferSize);
	VIA_OFFSET_Q31((q31_t *) output, (offset - 2048) << 3, (q31_t *) output, bufferSize);

	for (uint32_t i = 0; i < (bufferSize); i++) {

		output[i] = wrapSignal16Bit(output[i]);

	}

}

}

