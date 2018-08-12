/*
 * simple_wavetable.h
 *
 *  Created on: Aug 8, 2018
 *      Author: willmitchell
 */

#ifndef WAVETABLE_H
#define WAVETABLE_H

#include "stm32f3xx.h"

uint32_t wavetable1[513];
uint32_t wavetable2[513];
int16_t cv2[1];
int16_t cv3[1];
uint32_t adcReadings[64];
uint32_t dacBuffer1[32];
uint32_t dacBuffer2[32];
uint32_t dacBuffer3[32];

// macros for DMA array (change to array name?)

#define knob2 adcReadings[3]
#define knob3 adcReadings[1]
#define knob1 adcReadings[2]
#define cv1 (4095 - adcReadings[0])

typedef struct {
	uint32_t timeBase1;
	uint32_t timeBase2;
	uint32_t morphBase;
} controlRateInputs;

void handleConversionSlow(controlRateInputs * controls);

controlRateInputs controls;

void oscillatorInit(void);
void renderLine1(controlRateInputs * controls);
void renderLine2(controlRateInputs * controls);

// Circular buffer

typedef struct {
    int buff[32];
    int writeIndex;
}buffer;

// fixed point math functions

static inline int fix16_mul(int in0, int in1) {

	int lsb;
	  int msb;

	  // multiply the inputs, store the top 32 bits in msb and bottom in lsb

	  __asm ("SMULL %[result_1], %[result_2], %[input_1], %[input_2]"
	    : [result_1] "=r" (lsb), [result_2] "=r" (msb)
	    : [input_1] "r" (in0), [input_2] "r" (in1)
	  );

	  // reconstruct the result with a left shift by 16
	  // pack the bottom halfword of msb into the top halfword of the result
	  // top halfword of lsb goes into the bottom halfword of the result

	  return __ROR(__PKHBT(msb, lsb, 0), 16);

}

static inline int fix16_lerp(int in0, int in1, int frac) {
	return in0 + fix16_mul(in1 - in0, frac);
}

static inline int fix24_lerp(int in0, int in1, int frac) {
	return in0 + (((int64_t)(in1 - in0) * frac) >> 24);
}

// this is a decent improvement over the above for the case of 16 bit interpolation points
// no need to cast a 16bit by 16bit multiplication to 64 bit

static inline int fast_16_16_mul(int in0, int in1) {
	return (in0 * in1) >> 16;
}

static inline int fast_16_16_lerp(int in0, int in1, int frac) {
	return in0 + fast_16_16_mul(in1 - in0, frac);
}

#endif
