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

uint32_t phase;

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

	  wavetable2[512] = sinwavefold_257_Family0[0];

	  SH_A_TRACK;
	  SH_B_TRACK;

}


void renderLine1(controlRateInputs * controls) {

	uint32_t increment = (((controls->timeBase1) * (cv2[0])));
	uint32_t morph = __USAT(controls->morphBase + cv3[0], 16);
//	uint32_t morph = 0;
	uint32_t leftSample;
	uint32_t phaseFrac;
	uint32_t interp1;
	uint32_t interp2;
	uint32_t sample;


	GPIOC->BRR = (uint32_t)GPIO_PIN_13;

	for (int i = 0; i < 16; i++) {
		// wraps at full scale uint32_t
		phase = (phase + increment);
		leftSample = phase >> 23;
		phaseFrac = (phase - (leftSample << 23)) >> 7;
		interp1 = fix16_lerp(wavetable1[leftSample], wavetable1[leftSample + 1], phaseFrac);
		interp2 = fix16_lerp(wavetable2[leftSample], wavetable2[leftSample + 1], phaseFrac);
		sample = fix16_lerp(interp1, interp2, morph);
		dacBuffer1[i] = 4095 - sample;
		dacBuffer2[i] = sample;
		dacBuffer3[i] = (!(phase >> 31)) * 4095;
	}
	GPIOC->BSRR = (uint32_t)GPIO_PIN_13;

}

void renderLine2(controlRateInputs * controls) {

	uint32_t increment = (((controls->timeBase1) * (cv2[0])));
	uint32_t morph = __USAT(controls->morphBase + cv3[0], 16);
//	uint32_t morph = 0;
	uint32_t leftSample;
	uint32_t phaseFrac;
	uint32_t interp1;
	uint32_t interp2;
	uint32_t sample;

	GPIOC->BRR = (uint32_t)GPIO_PIN_13;

	for (int i = 16; i < 32; i++) {
		// wraps at full scale uint32_t
		phase = (phase + increment);
		leftSample = phase >> 23;
		phaseFrac = (phase - (leftSample << 23)) >> 7;
		interp1 = fix16_lerp(wavetable1[leftSample], wavetable1[leftSample + 1], phaseFrac);
		interp2 = fix16_lerp(wavetable2[leftSample], wavetable2[leftSample + 1], phaseFrac);
		sample = fix16_lerp(interp1, interp2, morph);
		dacBuffer3[i] = 4095 - sample;
		dacBuffer2[i] = sample;
		dacBuffer1[i] = (!(phase >> 31)) * 4095;
	}
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

