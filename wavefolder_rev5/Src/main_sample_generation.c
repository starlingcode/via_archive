#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"
#include "main_state_machine.h"
#include "tables.h"
#include "int64.h"
#include "dsp.h"
#include "pwm_tables.h"

static inline int getSampleQuinticSpline(int, uint32_t);
static inline int linearFold(int);
static inline int sineFold(int);

/**
 *
 * Helper functions for filling the sample buffer
 *
 */

void prepareCV(audioRateInputs * audioInputs, controlRateInputs *controlInputs, q31_t *preFold) {

	// scale the CVs by the knob value cast from 0 to full scale q31_t, then shift left by 3

	arm_shift_q31(audioInputs->xCV, 16, audioInputs->xCV, BUFFER_SIZE);
	arm_scale_q31(audioInputs->yCV, controlInputs->knob1Value << 19, 0, preFold, BUFFER_SIZE);
	arm_mult_q31(preFold, audioInputs->xCV, preFold, BUFFER_SIZE);
	arm_shift_q31(preFold, 3, preFold, BUFFER_SIZE);
	arm_offset_q31(preFold, (controlInputs->knob2Value + controlInputs->cv1Value - 4095) << 2, preFold, BUFFER_SIZE);





}

// generate the sample values and phase events for the buffer with the above modulation inputs

void foldBufferSine(q31_t * preFoldArray, int * reverseArray, int zIndex, q31_t * output) {

	for (int i = 0; i < (BUFFER_SIZE); i++) {

		output[i] = getSampleQuinticSpline(((sineFold(preFoldArray[i]) >> 20) + 2048) << 13, zIndex);

	}

}

void foldBufferLinear(q31_t * preFoldArray, int * reverseArray, int zIndex, q31_t * output) {

	for (int i = 0; i < (BUFFER_SIZE); i++) {

		output[i] = getSampleQuinticSpline(linearFold(preFoldArray[i] << 3) << 10, zIndex);

	}

}



static inline int linearFold(int phaseIn) {

	// fold into the space [0, 2^15)

	int absPhase = abs(phaseIn >> 2);

	return ((absPhase >> 15) & 1)*(32767 - (absPhase & 0b111111111111111)) +
				(!((absPhase >> 15) & 1))*(absPhase & 0b111111111111111);

}

static inline int sineFold(int phaseIn) {

	// fold into the space [0, 2^15)

	int absPhase = abs(phaseIn);

	return arm_sin_q31((absPhase & 32767) << 16);

}

static inline int getSampleQuinticSpline(int phase, uint32_t morph) {

    /* in this function, we use our phase position to get the sample to give to our dacs using a quintic spline interpolation technique
    essentially, we need to get 6 pairs of sample values and two "fractional arguments" (where are we at in between those sample values)
    one fractional argument determines the relative position in a linear interpolation between the sample values (morph)
    the other is the fractional phase argument used in the interpolation calculation
    */

    uint32_t LnSample;  // indicates the left most sample in the neighborhood of sample values around the phase pointer
    uint32_t LnFamily;  // indicates the nearest neighbor (wavetable) to our morph value in the family
    uint32_t phaseFrac;  // indicates the fractional distance between the nearest sample values in terms of phase
    uint32_t morphFrac; // indicates the fractional distance between our nearest neighbors in the family
    q31_t * leftIndex;
    q31_t * rightIndex;


	// we do a lot of tricky bitshifting to take advantage of the structure of a 16 bit fixed point number
	// truncate phase then add two to find the left neighboring sample of the phase pointer

    LnSample = (phase >> 16);

	// bit shifting to divide by the correct power of two takes a 12 bit number (our morph) and returns the a quotient in the range of our family size

	LnFamily = morph >> 10;

	leftIndex = &fullTableHoldArray[LnFamily][LnSample];
	rightIndex = &fullTableHoldArray[LnFamily + 1][LnSample];

	// determine the fractional part of our phase phase by masking off the integer

	phaseFrac = 0x0000FFFF & phase;

	// we have to calculate the fractional portion and get it up to full scale q16

	morphFrac = (morph - (LnFamily << 10)) << 6;

	// perform the 6 linear interpolations to get the sample values and apply morph
	// TODO track delta change in the phase event array

	int sample0 = fast_16_16_lerp(*leftIndex, *rightIndex, morphFrac);
	int sample1 = fast_16_16_lerp(*(leftIndex + 1), *(rightIndex + 1), morphFrac);
	int sample2 = fast_16_16_lerp(*(leftIndex + 2), *(rightIndex + 2), morphFrac);
	int sample3 = fast_16_16_lerp(*(leftIndex + 3), *(rightIndex + 3), morphFrac);
	int sample4 = fast_16_16_lerp(*(leftIndex + 4), *(rightIndex + 4), morphFrac);
	int sample5 = fast_16_16_lerp(*(leftIndex + 5), *(rightIndex + 5), morphFrac);


	// a version of the spline forumula from Josh Scholar on the musicdsp mailing list
	// https://web.archive.org/web/20170705065209/http://www.musicdsp.org/showArchiveComment.php?ArchiveID=60

	int out = (sample2
			+ fix24_mul(699051, fix16_mul(phaseFrac, ((sample3-sample1)*16 + (sample0-sample4)*2
					+ fix16_mul(phaseFrac, ((sample3+sample1)*16 - sample0 - sample2*30 - sample4
							+ fix16_mul(phaseFrac, (sample3*66 - sample2*70 - sample4*33 + sample1*39 + sample5*7 - sample0*9
									+ fix16_mul(phaseFrac, ( sample2*126 - sample3*124 + sample4*61 - sample1*64 - sample5*12 + sample0*13
											+ fix16_mul(phaseFrac, ((sample3-sample2)*50 + (sample1-sample4)*25 + (sample5-sample0) * 5
											))
									))
							))
					))
			))
		));

	return __USAT(out >> 3, 12);
}
