#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"
#include "main_state_machine.h"
#include "tables.h"
#include "int64.h"
#include "dsp.h"

// 16.16 fixed point math taken from fixmathlib

static inline int fix16_mul(int in0, int in1) {
	int64_t result = (uint64_t) in0 * in1;
	return result >> 16;
}


static inline int fix16_lerp(int in0, int in1, uint16_t inFract) {
	int64_t tempOut = int64_mul_i32_i32(in0, (((int32_t) 1 << 16) - inFract));
	tempOut = int64_add(tempOut, int64_mul_i32_i32(in1, inFract));
	tempOut = int64_shift(tempOut, -16);
	return (int) int64_lo(tempOut);
}

static inline int fix24_mul(int in0, int in1) {
	int64_t result = (uint64_t) in0 * in1;
	return result >> 24;
}

/**
 *
 * Helper functions for filling the sample buffer
 *
 */

// TODO oscillator function per sync mode wrapped in the for loop. mode change points to dsp loop.


void incrementOscillator(audioRateInputs * input, audioRateOutputs * output, uint32_t * phaseArray, uint32_t index) {

	// TODO average low frequency CV inputs

	static int increment;
	static q31_t phase;
	static q31_t lastPhase;

	// expo scaling for 1voct
	static uint32_t expoTable[4096] = expotable10oct;

	// data structure for the interpolation
	static arm_bilinear_interp_instance_q31 wavetable = {
			.numRows = 517,
			.numCols = 517,
			.pData = &fullTableHoldArray
	};

	// calculate increment as a function of pitch control inputs
	// sample by sample linear FM using array store during last processing block
	increment = fix16_mul(fix16_mul(fix16_mul(expoTable[knob1] >> 4, expoTable[knob2] >> 4), expoTable[4095 - cv1] >> 4), (2048
			- input->xCV[index]) << 4);

	// saturate increment at half of span to prevent crash
	increment = __SSAT(increment, 23) ;

	// increment the phase pointer
	// this has a hacked in hard sync using a value of 0 in the buffer to resync phase
	// it avoids a conditional which seemed to slow the loop down tremendously
	phase = (phase + increment) * input->trigInput[index];

	// check for overflow of wavetable index, if so, write a 1 to the phase event buffer
	// then check for traversal of "b" point (hard coded here as index 256)
	// do this by checking the sign bit of the difference of phase and the "b" index
	// if so, write a 2 to the phase event buffer
	// if neither of those conditions are met, write a 0 to the phase event buffer
	// TODO turn the above an enum
	// TODO wrap into handle logic by storing phase value in phaseArray

	if (phase >= 512 << 16) {
		phase -= 512 << 16;
		phaseArray[index] = 1;
	} else if (phase < 0) {
		phase += 512 << 16;
		phaseArray[index] = 1;
	}else if (((phase - (256 << 16)) >> 31) != ((lastPhase - (256 << 16)) >> 31)) {
		phaseArray[index] = 2;
	} else {
		phaseArray[index] = 0;
	}

	// store the current phase
	lastPhase = phase;

	// calculate the sample value
	// ugly inline that sums of the morph controls and saturates at 12 bits
	// this along with phase is scaled to q12.20
	// that is plugged into the CMSIS arm optimized bilinear interpolation
	// this is scaled to 12 bits and dropped to bipolar for better FIR filtering overflow protection (maybe dont need that?)
	output->samples[index] = (arm_bilinear_interp_q31(&wavetable, phase*16, __USAT(knob3 + input->morphCV[index] - 2048, 12)*1024) >> 3) - 2048;

}

