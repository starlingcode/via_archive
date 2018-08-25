/*
 * signal_processor_resources.c
 *
 *  Created on: Aug 22, 2018
 *      Author: willmitchell
 */

#include "signal_processors.h"
#include "dsp.h"
#include "cmsis_dsp.h"

/**
 *
 * Helper functions for filling the sample buffer
 *
 */

void foldBuffer(int * input, int offset, int * output, uint32_t bufferSize) {

	// scale the CVs by the knob value cast from 0 to full scale int, then shift left by 3

	arm_scale_q31(input, 1 << 31, 2, output, bufferSize);
	arm_offset_q31(output, (offset - 2048) << 5, output, bufferSize);

	for (int i = 0; i < (bufferSize); i++) {

		output[i] = foldSignal16Bit(output[i]);

	}

}

void wrapBuffer(int * input, int offset, int * output, uint32_t bufferSize) {

	// scale the CVs by the knob value cast from 0 to full scale int, then shift left by 3

	arm_scale_q31(input, 1 << 31, 6, output, bufferSize);
	arm_offset_q31(output, (offset - 2048) << 3, output, bufferSize);

	for (int i = 0; i < (bufferSize); i++) {

		output[i] = wrapSignal16Bit(output[i]);

	}

}

