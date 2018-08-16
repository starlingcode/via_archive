/*
 * simple_wavetable.c
 *
 *  Created on: Aug 8, 2018
 *      Author: willmitchell
 */

#include "simple_wavetable.h"
#include "via_rev5_hardware_io.h"
#include "tables.h"
#include "stm32f3xx.h"
#include "stm32f3xx_hal.h"
#include "pwm_tables.h"

uint32_t phase;

uint32_t phaseModPWMTables[33][65] = {phaseModPWM_0, phaseModPWM_1, phaseModPWM_2, phaseModPWM_3, phaseModPWM_4, phaseModPWM_5, phaseModPWM_6, phaseModPWM_7, phaseModPWM_8, phaseModPWM_9, phaseModPWM_10, phaseModPWM_11, phaseModPWM_12, phaseModPWM_13, phaseModPWM_14, phaseModPWM_15, phaseModPWM_16, phaseModPWM_17, phaseModPWM_18, phaseModPWM_19, phaseModPWM_20, phaseModPWM_21, phaseModPWM_22, phaseModPWM_23, phaseModPWM_24, phaseModPWM_25, phaseModPWM_26, phaseModPWM_27, phaseModPWM_28, phaseModPWM_29, phaseModPWM_30, phaseModPWM_31, phaseModPWM_32};

void oscillatorInit(void) {

	  for (int i = 0; i < 256; i++) {
		  wavetable1[i] = __USAT(tenor257Atk0[i] >> 3, 12);
	  }

	  for (int i = 0; i < 257; i++) {
		  wavetable1[255 + i] = __USAT(tenor257Rls0[256 - i] >> 3, 12);
	  }

	  wavetable1[512] = tenor257Atk0[0];

	  for (int i = 0; i < 256; i++) {
		  wavetable2[i] = __USAT(sinwavefold_257_Family0[i] >> 3, 12);
	  }

	  for (int i = 0; i < 257; i++) {
		  wavetable2[255 + i] = __USAT(sinwavefold_257_Family0[256 - i] >> 3, 12);
	  }

//	  for (int i = 0; i < 513; i ++) {
//		  __PKHBT(wavetable1[i], wavetable2[i] - wavetable1[i], 16);
//	  }

	  wavetable2[512] = sinwavefold_257_Family0[0];

	  SH_A_TRACK;
	  SH_B_TRACK;

}



void renderBuffer0(controlRateInputs * controls) {

	// profiling at A logic high
	GPIOC->BRR = (uint32_t)GPIO_PIN_13;

	/*
	 * Phase accumulator -> phase distortion -> sample lookup
	 * Simple waveshape (saw/square) is derived from the phasor
	 *
	 */

	// oscillator parameters and calcalculated per buffer
	uint32_t increment = (((controls->timeBase1) * (cv2[0])));
	uint32_t morph = __USAT(controls->morphBase + cv3[0], 16);
	uint32_t pwm = controls->timeBase2;
	//uint32_t pwm = 2000;
	uint32_t pwmIndex = (pwm >> 7);
	uint32_t pwmFrac = (pwm & 0b00000000000000001111111) << 8;
	uint32_t * pwmTable1 = phaseModPWMTables[pwmIndex];
	uint32_t * pwmTable2 = phaseModPWMTables[pwmIndex + 1];
	// start writing at the start or halfway point of the buffer depending on
	uint32_t * buffer1 = dacBuffer1;
	uint32_t * buffer2 = dacBuffer2;
	uint32_t * buffer3 = dacBuffer3;

	uint32_t leftSample;
	uint32_t result;

	phase = 0;

	for (int i = 0; i < BUFFER_SIZE; i++) {
		// phase pointer wraps at 32 bits
		phase = (phase + increment);
		// treat the msb of phase as a 6.15 (tablesize.interpolationbits) fixed point number
		// divide by right shifting phase size (32 bits) less table size (6 bits) to find the nearest sample to the left
//		leftSample = phase >> 26;
//		// extract the less significant bits as fractional phase
//#define pwmPhaseFrac (phase & 0x3FFFFFF) >> 11
//		// use this with the precalculated pwm to perform bilinear interpolation
//		// this accomplishes the
//		result = fix15_bilerp(pwmTable1[leftSample], pwmTable2[leftSample],
//					pwmTable1[leftSample + 1], pwmTable2[leftSample + 1],
//						pwmFrac, pwmPhaseFrac);
//		// output of phase distortion is a 9.16 (tablesize.interpolationbits) fixed point number
//		// scale to 12 bits for saw out
		result = phase >> 7;
		//buffer3[i] = result >> 13;
		// get the actual wavetable output sample as above
		// but with the appropriate scaling as phase is now 25 bits and table length is 9 bits
		leftSample = result >> 16;
#define phaseFrac (result & 0xFFFF)
		result = fast_15_16_bilerp(wavetable1[leftSample], wavetable2[leftSample],
					wavetable1[leftSample + 1], wavetable2[leftSample + 1],
						morph, phaseFrac);
		// write crossfader attenuation values
		//buffer1[i] = 4095 - result;
		buffer3[i] = result;
	}

	// profiling low
	GPIOC->BSRR = (uint32_t)GPIO_PIN_13;

}

void renderBuffer1(controlRateInputs * controls) {

	// profiling at A logic high
	GPIOC->BRR = (uint32_t)GPIO_PIN_13;

	/*
	 * Phase accumulator -> phase distortion -> sample lookup
	 * Simple waveshape (saw/square) is derived from the phasor
	 *
	 */

	uint32_t increment = (((controls->timeBase2) * (cv2[0]))) << 3;
	uint32_t morph = __USAT(controls->morphBase + cv3[0], 16);
	uint32_t pwm = controls->timeBase2;
	uint32_t pwmIndex = (pwm >> 7);
	uint32_t pwmFrac = (pwm & 0b00000000000000001111111) << 8;
	uint32_t * pwmTable1 = phaseModPWMTables[pwmIndex];
	uint32_t * pwmTable2 = phaseModPWMTables[pwmIndex + 1];
	// start writing at the start or halfway point of the buffer depending on
	uint32_t * buffer1 = dacBuffer1;
	uint32_t * buffer2 = dacBuffer2;
	uint32_t * buffer3 = dacBuffer3;

	uint32_t leftSample;
	uint32_t result;

	for (int i = BUFFER_SIZE; i < 2*BUFFER_SIZE; i++) {
		// phase pointer wraps at 32 bits
		phase = (phase + increment);

		// treat the msb of phase as a 6.15 (tablesize.interpolationbits) fixed point number
		// divide by right shifting phase size (32 bits) less table size (6 bits) to find the nearest sample to the left
//		leftSample = phase >> 26;
//		// extract the less significant bits as fractional phase
//#define pwmPhaseFrac (phase & 0x3FFFFFF) >> 11
//		// use this with the precalculated pwm to perform bilinear interpolation
//		// this accomplishes the
//		result = fix15_bilerp(pwmTable1[leftSample], pwmTable2[leftSample],
//					pwmTable1[leftSample + 1], pwmTable2[leftSample + 1],
//						pwmFrac, pwmPhaseFrac);
//		// output of phase distortion is a 9.16 (tablesize.interpolationbits) fixed point number
//		// scale to 12 bits for saw out
		result = phase >> 7;
		//buffer3[i] = result >> 13;
		// get the actual wavetable output sample as above
		// but with the appropriate scaling as phase is now 25 bits and table length is 9 bits
		leftSample = result >> 16;
#define phaseFrac (result & 0xFFFF)
		result = fast_15_16_bilerp(wavetable1[leftSample], wavetable2[leftSample],
					wavetable1[leftSample + 1], wavetable2[leftSample + 1],
						morph, phaseFrac);
		// write crossfader attenuation values
		//buffer1[i] = 4095 - result;
		buffer3[i] = result;
	}

	// profiling low
	GPIOC->BSRR = (uint32_t)GPIO_PIN_13;

}



/**
 *
 * ADC Averaging
 *
 */

void writeBuffer(buffer* buffer, int value) {
	buffer->buff[(buffer->writeIndex++) & 31] = value;
}

int readBuffer(buffer* buffer, int Xn) {
	return buffer->buff[(buffer->writeIndex + (~Xn)) & 31];
}

void handleConversionSlow(controlRateInputs * controls) {

	// TODO apply SIMD instructions?

	static uint32_t knob1Sum;
	static uint32_t knob2Sum;
	static uint32_t knob3Sum;
	static uint32_t cv1Sum;
	static buffer knob1Buffer;
	static buffer knob2Buffer;
	static buffer knob3Buffer;
	static buffer cv1Buffer;
	uint32_t knob1Value;
	uint32_t knob2Value;
	uint32_t knob3Value;
	uint32_t cv1Value;


		// implement a running average on the control rate CV controls
		knob1Sum = knob1 + knob1Sum - readBuffer(&knob1Buffer, 31);
		knob2Sum = knob2 + knob2Sum - readBuffer(&knob2Buffer, 31);

		// store the newest value in a ring buffer
		writeBuffer(&knob1Buffer, knob1);
		writeBuffer(&knob2Buffer, knob2);

		// write the averaged controls to the holding struct
		knob1Value = knob1Sum >> 5;
		knob2Value = knob2Sum >> 5;

		// implement a running average on the control rate CV controls
		knob3Sum = knob3 + knob3Sum - readBuffer(&knob3Buffer, 31);
		cv1Sum = cv1 + cv1Sum - readBuffer(&cv1Buffer, 31);

		// store the newest value in a ring buffer
		writeBuffer(&knob3Buffer, knob3);
		writeBuffer(&cv1Buffer, cv1);

		// write the averaged controls to the holding struct
		knob3Value = knob3Sum >> 5;
		cv1Value = cv1Sum >> 5;

		controls->timeBase1 = knob1Value;
		controls->timeBase2 = knob2Value;
		controls->morphBase = (knob3Value & 0xFFF0) << 4;

}

