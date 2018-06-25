#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"
#include "main_state_machine.h"
#include "tables.h"
#include "int64.h"
#include "dsp.h"
#include "pwm_tables.h"

static inline int getSampleSineProduct(int, int, int);
static inline int foldIndex(int);

/**
 *
 * Helper functions for filling the sample buffer
 *
 */

void prepareCV(audioRateInputs * audioInputs, controlRateInputs *controlInputs, q31_t *preFold) {

	// scale the CVs by the knob value cast from 0 to full scale q31_t, then shift left by 3

	arm_offset_q31(audioInputs->yCV, (controlInputs->knob2Value + controlInputs->cv1Value - 4095) << 2, preFold, BUFFER_SIZE);
	arm_scale_q31(preFold, controlInputs->knob1Value << 19, 5, preFold, BUFFER_SIZE);
	arm_shift_q31(audioInputs->xCV, 16, audioInputs->xCV, BUFFER_SIZE);
	arm_mult_q31(preFold, audioInputs->xCV, preFold, BUFFER_SIZE);




}

// generate the sample values and phase events for the buffer with the above modulation inputs

void incrementOscillator(q31_t * preFoldArray, int * reverseArray, int zIndex, q31_t * output) {

	int foldedX;
	int foldedY;

	for (int i = 0; i < (BUFFER_SIZE); i++) {

		output[i] = foldIndex(preFoldArray[i]) >> 3;

	}
}

static inline int getSampleSineProduct(int xIndex, int yIndex, int zIndex) {

	// waveterrain = sin(2pi * z * x) * sin(2pi * z * y)

	// multiply by the z input as a 3.9 fixed point number, mask off all but the last 15 bit, scale to 31 bits
	int scaledX = ((xIndex * zIndex >> 9) & 32676) << 16;
	int scaledY = ((yIndex * zIndex >> 9) & 32676) << 16;

	// use the 1.31 phase inputs we just generated to calculate the waveterrain
	// scale to -2048 to 2047
	// offset to by 2048 to get into range 0-4095 for dac output
	int result = ((arm_sin_q31(scaledX) >> 16) * (arm_sin_q31(scaledY) >> 16)) >> 20;
	return result + 2048;
}

static inline int foldIndex(int phaseIn) {

	// fold into the space [0, 2^15)

	int absPhase = abs(phaseIn);

	return ((absPhase >> 15) & 1)*(32767 - (absPhase & 0b111111111111111)) +
				(!((absPhase >> 15) & 1))*(absPhase & 0b111111111111111);

}

