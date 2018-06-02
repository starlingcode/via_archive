#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"
#include "main_state_machine.h"
#include "tables.h"
#include "int64.h"
#include "dsp.h"
#include "pwm_tables.h"

q31_t phaseModPWMTables[33][65] = {phaseModPWM_0, phaseModPWM_1, phaseModPWM_2, phaseModPWM_3, phaseModPWM_4, phaseModPWM_5, phaseModPWM_6, phaseModPWM_7, phaseModPWM_8, phaseModPWM_9, phaseModPWM_10, phaseModPWM_11, phaseModPWM_12, phaseModPWM_13, phaseModPWM_14, phaseModPWM_15, phaseModPWM_16, phaseModPWM_17, phaseModPWM_18, phaseModPWM_19, phaseModPWM_20, phaseModPWM_21, phaseModPWM_22, phaseModPWM_23, phaseModPWM_24, phaseModPWM_25, phaseModPWM_26, phaseModPWM_27, phaseModPWM_28, phaseModPWM_29, phaseModPWM_30, phaseModPWM_31, phaseModPWM_32};

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

// ugly inline that sums of the morph controls and saturates at 12 bits
// this along with phase is scaled to q12.20
// that is plugged into the CMSIS arm optimized bilinear interpolation
// this is scaled to 12 bits and dropped to bipolar for better FIR filtering overflow protection (maybe dont need that?)

static inline int getSampleBilinear(arm_bilinear_interp_instance_q31* samples, q31_t phase, q31_t morph) {
	return (arm_bilinear_interp_q31(samples, (phase + (2 << 16))*16, morph*1024) >> 3) - 2048;
}

static inline int getSampleBilinearAlt(uint32_t phase, uint32_t morph) {

	uint32_t LnSample;  // indicates the left most sample in the neighborhood of sample values around the phase pointer
	uint32_t LnFamily;  // indicates the nearest neighbor (wavetable) to our morph value in the family
	uint32_t phaseFrac;  // indicates the fractional distance between the nearest sample values in terms of phase
	q31_t morphFrac; // indicates the fractional distance between our nearest neighbors in the family

	// we do a lot of tricky bitshifting to take advantage of the structure of a 16 bit fixed point number
	// truncate phase then add two to find the left neighboring sample of the phase pointer
	LnSample = (phase >> 16) + 2;

	// bit shifting to divide by the correct power of two takes a 12 bit number (our morph) and returns the a quotient in the range of our family size
	LnFamily = morph >> 9;

	// determine the fractional part of our phase phase by masking off the integer
	phaseFrac = 0x0000FFFF & phase;

	// we have to calculate the fractional portion and get it up to full scale q31_t
	morphFrac = (morph - (LnFamily << 9)) << 7;
	//morphFrac = 0;

	return (fix16_lerp(
				fix16_lerp(fullTableHoldArray[LnFamily][LnSample], fullTableHoldArray[LnFamily + 1][LnSample], morphFrac),
					fix16_lerp(fullTableHoldArray[LnFamily][LnSample + 1], fullTableHoldArray[LnFamily + 1][LnSample + 1], morphFrac),
						phaseFrac) >> 3) - 2048;

}

static inline int getSampleQuinticSpline(q31_t** samples, q31_t phase, q31_t morph) {

    /* in this function, we use our phase position to get the sample to give to our dacs using a quintic spline interpolation technique
    essentially, we need to get 6 pairs of sample values and two "fractional arguments" (where are we at in between those sample values)
    one fractional argument determines the relative position in a linear interpolation between the sample values (morph)
    the other is the fractional phase argument used in the interpolation calculation
    */

    uint32_t LnSample;  // indicates the left most sample in the neighborhood of sample values around the phase pointer
    uint32_t LnFamily;  // indicates the nearest neighbor (wavetable) to our morph value in the family
    uint32_t phaseFrac;  // indicates the fractional distance between the nearest sample values in terms of phase
    q31_t morphFrac; // indicates the fractional distance between our nearest neighbors in the family
	q31_t interpArray[6];
	q31_t interp1Array[6];

	// we do a lot of tricky bitshifting to take advantage of the structure of a 16 bit fixed point number
	// truncate phase then add two to find the left neighboring sample of the phase pointer
	LnSample = (phase >> 16);

	// bit shifting to divide by the correct power of two takes a 12 bit number (our morph) and returns the a quotient in the range of our family size
	LnFamily = morph >> 9;

	// determine the fractional part of our phase phase by masking off the integer
	phaseFrac = 0x0000FFFF & phase;

	// we have to calculate the fractional portion and get it up to full scale q31_t
	morphFrac = (morph - (LnFamily << 9)) << 22;

	// perform the 6 bilinear interpolations to get the sample values
	arm_negate_q31(samples[LnFamily][LnSample], interp1Array, 6);
	arm_add_q31(samples[LnFamily + 1][LnSample], interp1Array, interpArray, 6);
	arm_scale_q31(interpArray, morphFrac, 0, interpArray, 6);
	arm_add_q31(samples[LnFamily][LnSample], interpArray, interpArray, 6);
	arm_shift_q31(interpArray, -16, interpArray, 6);

	int sample0 = interpArray[0];
	int sample1 = interpArray[1];
	int sample2 = interpArray[2];
	int sample3 = interpArray[3];
	int sample4 = interpArray[4];
	int sample5 = interpArray[5];

	// an expansion of the spline forumula from Josh Scholar on the musicdsp mailing list
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

	return __USAT(out >> 3, 12) - 2048;
}

/**
 *
 * Helper functions for filling the sample buffer
 *
 */

void incrementOscillatorFM_Morph(audioRateInputs * input, controlRateInputs * controls, audioRateOutputs * output, uint32_t * phaseArray, uint32_t index) {

	q31_t increment;
	q31_t phaseMod;
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
	increment = fix16_mul(fix16_mul(fix16_mul((expoTable[controls->knob2Value] >> 4) + 1000000, (expoTable[controls->knob1Value] >> 4) + 10000), (expoTable[4095 - controls->cv1Value] >> 4) + 10000), (2048
			- input->xCV[index])*64);

	// saturate increment at half of span to prevent crash
	increment = __SSAT(increment, 25);

	// increment the phase pointer
	// this has a hacked in hard sync using a value of 0 in the buffer to resync phase
	// it avoids a conditional which seemed to slow the loop down tremendously

	phase = (phase + increment * input->reverseInput[index]) * input->hardSyncInput[index];


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

	//output->samples[index] = getSampleBilinear(&wavetable, phase, __USAT(controls->knob3Value + 2048 - input->morphCV[index], 12));
	output->samples[index] = getSampleBilinearAlt(phase, __USAT(controls->knob3Value + 2048 - input->morphCV[index], 12));

}

void incrementOscillatorPM_Morph(audioRateInputs * input, controlRateInputs * controls, audioRateOutputs * output, uint32_t * phaseArray, uint32_t index) {

	q31_t increment;
	q31_t phaseMod;
	static q31_t phase;
	static q31_t lastPhase;
	static q31_t lastCV;

	// expo scaling for 1voct
	static uint32_t expoTable[4096] = expotable10oct;

	// data structure for the interpolation
	static arm_bilinear_interp_instance_q31 wavetable = {
			.numRows = 517,
			.numCols = 517,
			.pData = &fullTableHoldArray
	};

	// no t2CV in this calculation
	increment = fix16_mul(fix16_mul((expoTable[controls->knob2Value] >> 4) + 360000, (expoTable[controls->knob1Value] >> 4) + 10000), (expoTable[4095 - controls->cv1Value] >> 11) + 10000);

	// saturate increment at half of span to prevent crash
	increment = __SSAT(increment, 25);

	phaseMod = (lastCV - input->xCV[index]) * 4096;
	lastCV = input->xCV[index];

	// increment the phase pointer
	// this has a hacked in hard sync using a value of 0 in the buffer to resync phase
	// it avoids a conditional which seemed to slow the loop down tremendously

	phase = (phase + phaseMod + increment * input->reverseInput[index]) * input->hardSyncInput[index];


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
	output->samples[index] = getSampleBilinear(&wavetable, phase, __USAT(controls->knob3Value + 2048 - input->morphCV[index], 12));

}

void incrementOscillatorFM_PWM(audioRateInputs * input, controlRateInputs * controls, audioRateOutputs * output, uint32_t * phaseArray, uint32_t index) {

	q31_t increment;
	static q31_t phase;
	q31_t ghostPhase;
	static q31_t lastPhase;

	// expo scaling for 1voct
	static uint32_t expoTable[4096] = expotable10oct;

	// data structure for the sample interpolation
	static arm_bilinear_interp_instance_q31 wavetable = {
			.numRows = 517,
			.numCols = 517,
			.pData = &fullTableHoldArray
	};

	// data structure for the phase interpolation
	static arm_bilinear_interp_instance_q31 pwmTable = {
			.numRows = 65,
			.numCols = 65,
			.pData = &phaseModPWMTables
	};



	// calculate increment as a function of pitch control inputs
	// sample by sample linear FM using array store during last processing block
	increment = fix16_mul(fix16_mul(fix16_mul((expoTable[controls->knob2Value] >> 4) + 1000000, (expoTable[controls->knob1Value] >> 4) + 10000), (expoTable[4095 - controls->cv1Value] >> 4) + 10000), (2048
			- input->xCV[index])*64);

	// saturate increment at half of span to prevent crash
	increment = __SSAT(increment, 25);

	// increment the phase pointer
	// this has a hacked in hard sync using a value of 0 in the buffer to resync phase
	// it avoids a conditional which seemed to slow the loop down tremendously

	phase = (phase + increment * input->reverseInput[index]) * input->hardSyncInput[index];


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



	ghostPhase = arm_bilinear_interp_q31(&pwmTable, phase * 2, (input->morphCV[index]) * 8192);

	// calculate the sample value
	// ugly inline that sums of the morph controls and saturates at 12 bits
	// this along with phase is scaled to q12.20
	// that is plugged into the CMSIS arm optimized bilinear interpolation
	// this is scaled to 12 bits and dropped to bipolar for better FIR filtering overflow protection (maybe dont need that?)
	output->samples[index] = getSampleBilinear(&wavetable, ghostPhase, controls->knob3Value);

}

void incrementOscillatorPM_PWM(audioRateInputs * input, controlRateInputs * controls, audioRateOutputs * output, uint32_t * phaseArray, uint32_t index) {

	q31_t increment;
	q31_t phaseMod;
	static q31_t phase;
	q31_t ghostPhase;
	static q31_t lastPhase;
	static q31_t lastCV;

	// expo scaling for 1voct
	static uint32_t expoTable[4096] = expotable10oct;

	// data structure for the interpolation
	static arm_bilinear_interp_instance_q31 wavetable = {
			.numRows = 517,
			.numCols = 517,
			.pData = &fullTableHoldArray
	};

	// data structure for the phase interpolation
	static arm_bilinear_interp_instance_q31 pwmTable = {
			.numRows = 65,
			.numCols = 65,
			.pData = &phaseModPWMTables
	};

	// no t2CV in this calculation
	increment = fix16_mul(fix16_mul((expoTable[controls->knob2Value] >> 4) + 360000, (expoTable[controls->knob1Value] >> 4) + 10000), (expoTable[4095 - controls->cv1Value] >> 11) + 10000);

	// saturate increment at half of span to prevent crash
	increment = __SSAT(increment, 25);

	phaseMod = (lastCV - input->xCV[index]) * 4096;
	lastCV = input->xCV[index];

	// increment the phase pointer
	// this has a hacked in hard sync using a value of 0 in the buffer to resync phase
	// it avoids a conditional which seemed to slow the loop down tremendously

	phase = (phase + phaseMod + increment * input->reverseInput[index]) * input->hardSyncInput[index];


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

	ghostPhase = arm_bilinear_interp_q31(&pwmTable, phase * 2, (input->morphCV[index]) * 8192);

	// calculate the sample value
	// ugly inline that sums of the morph controls and saturates at 12 bits
	// this along with phase is scaled to q12.20
	// that is plugged into the CMSIS arm optimized bilinear interpolation
	// this is scaled to 12 bits and dropped to bipolar for better FIR filtering overflow protection (maybe dont need that?)
	output->samples[index] = getSampleBilinear(&wavetable, ghostPhase, controls->knob3Value);
}


