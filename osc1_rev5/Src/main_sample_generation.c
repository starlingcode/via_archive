#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"
#include "main_state_machine.h"
#include "tables.h"
#include "int64.h"
#include "dsp.h"
#include "pwm_tables.h"

// expo scaling for 1voct
const uint32_t expoTable[4096] = expotable10oct;

q31_t phaseModPWMTables[33][65] = {phaseModPWM_0, phaseModPWM_1, phaseModPWM_2, phaseModPWM_3, phaseModPWM_4, phaseModPWM_5, phaseModPWM_6, phaseModPWM_7, phaseModPWM_8, phaseModPWM_9, phaseModPWM_10, phaseModPWM_11, phaseModPWM_12, phaseModPWM_13, phaseModPWM_14, phaseModPWM_15, phaseModPWM_16, phaseModPWM_17, phaseModPWM_18, phaseModPWM_19, phaseModPWM_20, phaseModPWM_21, phaseModPWM_22, phaseModPWM_23, phaseModPWM_24, phaseModPWM_25, phaseModPWM_26, phaseModPWM_27, phaseModPWM_28, phaseModPWM_29, phaseModPWM_30, phaseModPWM_31, phaseModPWM_32};

q31_t virtualGround[BUFFER_SIZE];

static inline int getSampleQuinticSpline(int, uint32_t);
static inline int calculatePWMPhase(int, uint32_t);

/**
 *
 * Helper functions for filling the sample buffer
 *
 */


void initialializeVirtualGround(void) {

	// fill a dsp buffer sized array with 2048
	for (int i; i < BUFFER_SIZE; i++) {
		virtualGround[i] = 2048;
	}

}

void prepareCV_FM_Morph(audioRateInputs * audioInputs, controlRateInputs *controlInputs, q31_t *incrementValues, q31_t *phaseModValues, q31_t * morphValues, q31_t *pwmValues) {

	// generate increment array
	// calculate a frequency multiplier from the control rate CVs
	// shift the xCV up to the maximum allowed value
	// scale that down with the frequency multiplier

	q31_t frequencyMultiplier = fix16_mul(fix16_mul(expoTable[controlInputs->knob1Value] >> 3, expoTable[controlInputs->knob2Value >> 3]), expoTable[4095 - controlInputs->cv1Value] >> 2);
	arm_offset_q31(audioInputs->xCV, -1024, incrementValues, BUFFER_SIZE);
	arm_shift_q31(incrementValues, 19, incrementValues, BUFFER_SIZE);
	arm_scale_q31(incrementValues, frequencyMultiplier, 0, incrementValues, BUFFER_SIZE);

	// generate phase modulation values with x cv as source
	// shift the values so that the maximum possible swing is half of the wavetable length in fix16
	arm_shift_q31(virtualGround, 12, phaseModValues, BUFFER_SIZE);

	// generate audio rate morph modulation values
	arm_offset_q31(audioInputs->morphCV, controlInputs->knob3Value - 2048, morphValues, BUFFER_SIZE);

	// assign pwm values
	arm_shift_q31(virtualGround, 9, pwmValues, BUFFER_SIZE);


}
void prepareCV_PM_Morph(audioRateInputs * audioInputs, controlRateInputs *controlInputs, q31_t *incrementValues, q31_t *phaseModValues, q31_t * morphValues, q31_t *pwmValues) {

	// generate increment array
	q31_t frequencyMultiplier = fix16_mul(fix16_mul(expoTable[controlInputs->knob1Value] >> 3, expoTable[controlInputs->knob2Value >> 3]), expoTable[4095 - controlInputs->cv1Value] >> 2);
	arm_offset_q31(virtualGround, -1024, incrementValues, BUFFER_SIZE);
	arm_shift_q31(incrementValues, 19, incrementValues, BUFFER_SIZE);
	arm_scale_q31(incrementValues, frequencyMultiplier, 0, incrementValues, BUFFER_SIZE);

	// assign phase modulation values
	arm_shift_q31(audioInputs->xCV, 13, phaseModValues, BUFFER_SIZE);

	// assign audio rate morph modulation values
	arm_offset_q31(audioInputs->morphCV, controlInputs->knob3Value - 2048, morphValues, BUFFER_SIZE);

	// assign pwm values
	arm_shift_q31(virtualGround, 9, pwmValues, BUFFER_SIZE);


}
void prepareCV_FM_PWM(audioRateInputs * audioInputs, controlRateInputs *controlInputs, q31_t *incrementValues, q31_t *phaseModValues, q31_t * morphValues, q31_t *pwmValues) {

	// generate increment array
	q31_t frequencyMultiplier = fix16_mul(fix16_mul(expoTable[controlInputs->knob1Value] >> 3, expoTable[controlInputs->knob2Value >> 3]), expoTable[4095 - controlInputs->cv1Value] >> 2);
	arm_offset_q31(audioInputs->xCV, -1024, incrementValues, BUFFER_SIZE);
	arm_shift_q31(incrementValues, 19, incrementValues, BUFFER_SIZE);
	arm_scale_q31(incrementValues, frequencyMultiplier, 0, incrementValues, BUFFER_SIZE);

	// generate phase modulation values
	arm_shift_q31(virtualGround, 12, phaseModValues, BUFFER_SIZE);

	// generate audio rate morph modulation values
	arm_offset_q31(virtualGround, controlInputs->knob3Value - 2048, morphValues, BUFFER_SIZE);

	// assign pwm values
	arm_shift_q31(audioInputs->morphCV, 9, pwmValues, BUFFER_SIZE);

}
void prepareCV_PM_PWM(audioRateInputs * audioInputs, controlRateInputs *controlInputs, q31_t *incrementValues, q31_t *phaseModValues, q31_t * morphValues, q31_t *pwmValues) {

	// generate increment array with virtual ground as source
	q31_t frequencyMultiplier = fix16_mul(fix16_mul(expoTable[controlInputs->knob1Value] >> 3, expoTable[controlInputs->knob2Value >> 3]), expoTable[4095 - controlInputs->cv1Value] >> 2);
	arm_offset_q31(virtualGround, -1024, incrementValues, BUFFER_SIZE);
	arm_shift_q31(incrementValues, 20, incrementValues, BUFFER_SIZE);
	arm_scale_q31(incrementValues, frequencyMultiplier, 0, incrementValues, BUFFER_SIZE);

	// generate phase modulation values with x cv as source
	// shift the values so that the maximum possible swing is half of the wavetable length in fix16
	arm_shift_q31(audioInputs->xCV, 12, phaseModValues, BUFFER_SIZE);

	// generate audio rate morph modulation values
	arm_offset_q31(virtualGround, controlInputs->knob3Value - 2048, morphValues, BUFFER_SIZE);

	// assign pwm values
	arm_shift_q31(audioInputs->morphCV, 9, pwmValues, BUFFER_SIZE);

}

// generate the sample values and phase events for the buffer with the above modulation inputs

void incrementOscillator(q31_t * incrementArray, q31_t * phaseModArray, q31_t * morphArray, q31_t * pwmArray, q31_t * hardSyncArray, q31_t * reverseArray, q31_t * output, int * phaseEventArray) {

	#define WAVETABLE_LENGTH 33554432
	#define NEGATIVE_WAVETABLE_LENGTH -33554432 // wavetable length in 16 bit fixed point (512 << 16)
	#define AT_B_PHASE 16777216 // wavetable midpoint in 16 bit fixed point (256 << 16)

	static int phase;
	static int lastPhase;
	static int lastPhaseMod;
	int wrapPhase;
	int phaseEvent;
	int ghostPhase;

	for (int i = 0; i < (BUFFER_SIZE); i++) {

		// increment the phase pointer
		// saturate increment at half of span to prevent crash
		// a 0 in the hard sync buffer is a reset
		// a -1 in the reverse array reverses direction of increment
		// the difference between the current and last phase mod value offsets the phase

		phase += __SSAT(incrementArray[i], 25) * reverseArray[i];
		phase += (phaseModArray[i] - lastPhaseMod);
		phase *= hardSyncArray[i];

		lastPhaseMod = phaseModArray[i];

		// wrap the phase pointer when it overflows either end of the wavetable
		// perform a mathematical operation with the right conditional properties
		// the most significant bit is 1 when a number is negative, 0 otherwise
		// cast to unsigned to enforce a logical shift
		// the two top bit checks should be mutually exclusive

		wrapPhase = 0;

		wrapPhase = ((uint32_t)(phase) >> 31) * WAVETABLE_LENGTH;
		wrapPhase += ((uint32_t)(WAVETABLE_LENGTH - phase) >> 31) * NEGATIVE_WAVETABLE_LENGTH;

		// apply the wrapping offset
		// no effect if there is no overflow

		phase += wrapPhase;

		// log a -1 if the max value index of the wavetable is traversed from the left
		// log a 1 if traversed from the right
		// do this by subtracting the sign bit of the last phase from the current phase, both less the max phase index
		// this adds cruft to the wrap indicators, but that is deterministic and can be parsed out

		wrapPhase += ((uint32_t)(phase - AT_B_PHASE) >> 31) - ((uint32_t)(lastPhase - AT_B_PHASE) >> 31);

		// log the phase event by accumulating the indicative variables
		// log 0 if no event

		phaseEventArray[i] = wrapPhase;

		// TODO rewrite logic parsing function

		// store the current phase
		lastPhase = phase;

		// calculate the phase waveshaping function for PWM
		ghostPhase = calculatePWMPhase(phase, pwmArray[i]);

		// calculate the sample value
		output[i] = getSampleQuinticSpline(ghostPhase, __USAT(morphArray[i], 12));

	}
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

static inline int calculatePWMPhase(int phaseIn, uint32_t pwm) {

	#define phaseIndex (phaseIn >> 19)
	#define phaseFrac (phaseIn & 0b0000000000001111111111111111111) >> 3
	#define pwmIndex (pwm >> 16)
	#define pwmFrac (pwm & 0b00000000000000001111111111111111)
	uint32_t sampleA_0 = phaseModPWMTables[pwmIndex][phaseIndex];
	uint32_t sampleA_1 = phaseModPWMTables[pwmIndex][phaseIndex + 1];
	uint32_t sampleB_0 = phaseModPWMTables[pwmIndex + 1][phaseIndex];
	uint32_t sampleB_1 = phaseModPWMTables[pwmIndex + 1][phaseIndex + 1];

	int interp0 = fix16_lerp(sampleA_0, sampleA_1, phaseFrac);
	int interp1 = fix16_lerp(sampleB_0, sampleB_1, phaseFrac);

	return fix16_lerp(interp0, interp1, pwmFrac);

}

