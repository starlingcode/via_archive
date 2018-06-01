#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"
#include "main_state_machine.h"
#include "tables.h"
#include "int64.h"
#include "dsp.h"
#include "pwm_tables.h"

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

q31_t phaseModPWMTables[33][65] = {phaseModPWM_0, phaseModPWM_1, phaseModPWM_2, phaseModPWM_3, phaseModPWM_4, phaseModPWM_5, phaseModPWM_6, phaseModPWM_7, phaseModPWM_8, phaseModPWM_9, phaseModPWM_10, phaseModPWM_11, phaseModPWM_12, phaseModPWM_13, phaseModPWM_14, phaseModPWM_15, phaseModPWM_16, phaseModPWM_17, phaseModPWM_18, phaseModPWM_19, phaseModPWM_20, phaseModPWM_21, phaseModPWM_22, phaseModPWM_23, phaseModPWM_24, phaseModPWM_25, phaseModPWM_26, phaseModPWM_27, phaseModPWM_28, phaseModPWM_29, phaseModPWM_30, phaseModPWM_31, phaseModPWM_32};

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
	increment = fix16_mul(fix16_mul(fix16_mul(expoTable[controls->knob1Value], expoTable[controls->knob2Value] >> 8), expoTable[4095 - controls->cv1Value] >> 4), (2048
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
	// ugly inline that sums of the morph controls and saturates at 12 bits
	// this along with phase is scaled to q12.20
	// that is plugged into the CMSIS arm optimized bilinear interpolation
	// this is scaled to 12 bits and dropped to bipolar for better FIR filtering overflow protection (maybe dont need that?)
	output->samples[index] = (arm_bilinear_interp_q31(&wavetable, phase*16, __USAT(controls->knob3Value + 2048 - input->morphCV[index], 12)*1024) >> 3) - 2048;

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
	increment = fix16_mul(fix16_mul(expoTable[controls->knob1Value] >> 4, expoTable[controls->knob2Value] >> 8), expoTable[4095 - controls->cv1Value] >> 4);

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
	output->samples[index] = (arm_bilinear_interp_q31(&wavetable, phase*16, __USAT(controls->knob3Value + 2048 - input->morphCV[index], 12)*1024) >> 3) - 2048;

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
	increment = fix16_mul(fix16_mul(fix16_mul(expoTable[controls->knob1Value], expoTable[controls->knob2Value] >> 8), expoTable[4095 - controls->cv1Value] >> 4), (2048
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
	output->samples[index] = (arm_bilinear_interp_q31(&wavetable, ghostPhase*16, (controls->knob3Value) * 1024) >> 3) - 2048;

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
	increment = fix16_mul(fix16_mul(expoTable[controls->knob1Value] >> 4, expoTable[controls->knob2Value] >> 8), expoTable[4095 - controls->cv1Value] >> 4);

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
	output->samples[index] = (arm_bilinear_interp_q31(&wavetable, ghostPhase*16, (controls->knob3Value) * 1024) >> 3) - 2048;

}
