#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"
#include "main_state_machine.h"
#include "tables.h"
#include "int64.h"
#include "dsp.h"
#include "pwm_tables.h"

static inline int foldIndex(int);
static inline int getSampleQuinticSpline(int, uint32_t);
static inline int getSampleProduct(int, int, int);
static inline int getSampleSum(int, int, int);



/**
 *
 * Helper functions for filling the sample buffer
 *
 */

void prepareCV(audioRateInputs * audioInputs, controlRateInputs *controlInputs, q31_t *xIndices, q31_t *yIndices) {

	// scale the CVs by the knob value cast from 0 to full scale q31_t, then shift left by 3

	arm_offset_q31(audioInputs->xCV, (controlInputs->knob1Value - 2048) << 3, xIndices, BUFFER_SIZE);
	arm_scale_q31(xIndices, 1 << 31, 1, xIndices, BUFFER_SIZE);


	arm_offset_q31(audioInputs->yCV, (controlInputs->knob2Value - 2048) << 3, yIndices, BUFFER_SIZE);
	arm_scale_q31(yIndices, 1 << 31, 1, yIndices, BUFFER_SIZE);



}

// generate the sample values and phase events for the buffer with the above modulation inputs

void scanTerrainProduct(q31_t * xIndexArray, q31_t * yIndexArray, int * reverseArray, int zIndex, q31_t * output) {

	int foldedX;
	int foldedY;

	for (int i = 0; i < (BUFFER_SIZE); i++) {

		foldedX = foldIndex(xIndexArray[i] + reverseArray[i]);
		foldedY = foldIndex(yIndexArray[i] + reverseArray[i]);

		// calculate the sample value
		output[i] = getSampleProduct(foldedX, foldedY, zIndex);

	}
}

void scanTerrainSum(q31_t * xIndexArray, q31_t * yIndexArray, int * reverseArray, int zIndex, q31_t * output) {

	int foldedX;
	int foldedY;

	for (int i = 0; i < (BUFFER_SIZE); i++) {

		foldedX = foldIndex(xIndexArray[i] + reverseArray[i]);
		foldedY = foldIndex(yIndexArray[i] + reverseArray[i]);

		// calculate the sample value
		output[i] = getSampleSum(foldedX, foldedY, zIndex);

	}
}

static inline int getSampleProduct(int xIndex, int yIndex, int zIndex) {

	// waveterrain = sin(2pi * z * x) * sin(2pi * z * y)

	int xSample = getSampleQuinticSpline(xIndex << 10, zIndex >> 3);
	int ySample = getSampleQuinticSpline(yIndex << 10, zIndex >> 3);

	return (xSample * ySample) >> 18; //15 bit fixed point multiply and right shift by 3



}

static inline int getSampleSum(int xIndex, int yIndex, int zIndex) {

	// waveterrain = sin(2pi * z * x) * sin(2pi * z * y)

	int xSample = getSampleQuinticSpline(xIndex << 10, zIndex >> 3);
	int ySample = getSampleQuinticSpline(yIndex << 10, zIndex >> 3);

	return (xSample + ySample) >> 4;


}

static inline int foldIndex(int phaseIn) {

	// fold into the space [0, 2^15)

	int absPhase = abs(phaseIn);

	return ((absPhase >> 15) & 1)*(32767 - (absPhase & 0b111111111111111)) +
				(!((absPhase >> 15) & 1))*(absPhase & 0b111111111111111);

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

	return __USAT(out, 15);
}

