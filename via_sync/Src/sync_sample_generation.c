
#include "sync_tables.h"
#include "sync_dsp.h"
#include "sync_next_sample.h"
#include "via_rev5_hardware_io.h"
#include "sync_pwm_tables.h"

const q31_t phaseModPWMTables[33][65] = {phaseModPWM_0, phaseModPWM_1, phaseModPWM_2, phaseModPWM_3, phaseModPWM_4, phaseModPWM_5, phaseModPWM_6, phaseModPWM_7, phaseModPWM_8, phaseModPWM_9, phaseModPWM_10, phaseModPWM_11, phaseModPWM_12, phaseModPWM_13, phaseModPWM_14, phaseModPWM_15, phaseModPWM_16, phaseModPWM_17, phaseModPWM_18, phaseModPWM_19, phaseModPWM_20, phaseModPWM_21, phaseModPWM_22, phaseModPWM_23, phaseModPWM_24, phaseModPWM_25, phaseModPWM_26, phaseModPWM_27, phaseModPWM_28, phaseModPWM_29, phaseModPWM_30, phaseModPWM_31, phaseModPWM_32};

static inline int calculatePWMPhase(int, uint32_t);

static inline int getSampleQuinticSpline(int, uint32_t, int *);
static inline int getSampleLinear(int, uint32_t, int *);


void calculateSample(controlRateInputs * controls, audioRateInputs * inputs, viaStateVariableSet * stateVariables, audioRateOutputs * output) {

	int phase = calculatePWMPhase(stateVariables->phase, stateVariables->dutyCycle);

	output->samples = getSampleQuinticSpline(phase, stateVariables->morph, &(stateVariables->delta));
//	output->samples = getSampleLinear(phase, stateVariables->morph, &(stateVariables->delta));


}

static inline int getSampleQuinticSpline(int phase, uint32_t morph, int * delta) {

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

	LnFamily = morph >> 13;

	leftIndex = &fullTableHoldArray[LnFamily][LnSample];
	rightIndex = &fullTableHoldArray[LnFamily + 1][LnSample];

	// determine the fractional part of our phase phase by masking off the integer

	phaseFrac = phase & 0x0000FFFF;

	// we have to calculate the fractional portion and get it up to full scale q16

	morphFrac = (morph & 0x1FFF) << 3;

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

	int deltaSign = ((uint32_t)(sample3 - sample2) >> 31);

	*delta = deltaSign;

	return __USAT(out >> 3, 12);
}

static inline int getSampleLinear(int phase, uint32_t morph, int * delta) {

	#define phaseIndex (phase >> 16)
	#define phaseFrac (phase & 0x0000FFFF)
	#define pwmIndex (morph >> 13)
	#define pwmFrac (morph & 0x1FFF) << 3
	uint32_t sampleA_0 = fullTableHoldArray[pwmIndex][phaseIndex];
	uint32_t sampleA_1 = fullTableHoldArray[pwmIndex][phaseIndex + 1];
	uint32_t sampleB_0 = fullTableHoldArray[pwmIndex + 1][phaseIndex];
	uint32_t sampleB_1 = fullTableHoldArray[pwmIndex + 1][phaseIndex + 1];

	int interp0 = fix16_lerp(sampleA_0, sampleA_1, phaseFrac);
	int interp1 = fix16_lerp(sampleB_0, sampleB_1, phaseFrac);

	int deltaSign = ((uint32_t)(interp1 - interp0) >> 31);

	*delta = deltaSign;

	return fix16_lerp(interp0, interp1, pwmFrac) >> 3;

}


static inline int calculatePWMPhase(int phaseIn, uint32_t pwm) {

	#define phaseIndex (phaseIn >> 19)
	#define phaseFrac (phaseIn & 0b0000000000001111111111111111111) >> 3
	#define pwmIndex (pwm >> 7)
	#define pwmFrac (pwm & 0b00000000000000001111111) << 9
	uint32_t sampleA_0 = phaseModPWMTables[pwmIndex][phaseIndex];
	uint32_t sampleA_1 = phaseModPWMTables[pwmIndex][phaseIndex + 1];
	uint32_t sampleB_0 = phaseModPWMTables[pwmIndex + 1][phaseIndex];
	uint32_t sampleB_1 = phaseModPWMTables[pwmIndex + 1][phaseIndex + 1];

	int interp0 = fix16_lerp(sampleA_0, sampleA_1, phaseFrac);
	int interp1 = fix16_lerp(sampleB_0, sampleB_1, phaseFrac);

	return fix16_lerp(interp0, interp1, pwmFrac);

}

