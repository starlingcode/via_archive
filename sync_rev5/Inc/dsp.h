#ifndef DSP_H
#define DSP_H

#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"
#define ARM_MATH_CM4
#include "arm_math.h"
#include "int64.h"
#include "scales.h"

#define WAVETABLE_LENGTH 33554432
#define NEGATIVE_WAVETABLE_LENGTH -33554432 // wavetable length in 16 bit fixed point (512 << 16)
#define AT_B_PHASE 16777216 // wavetable midpoint in 16 bit fixed point (256 << 16)

#define BUFFER_SIZE 8

#define NUM_TAPS 24

#define FIR8TAPS1_24 {37653504, 103041591, 262708334, 424417055, 491842679, 424417055, 262708334, 103041591 , 37653504}

#define FIR16TAPS5_24 {-5268880, 20286907, 45192374, -47794798, -227426832, -51762506, 769600018, 1644657365, 1644657365, 769600018, -51762506, -227426832, -47794798, 45192374, 20286907, -5268880}

#define FIR24TAPS6_24 {1499280, 3097718, -6929872, -34955643, -49795015, -9487274, 49070362, 22354339, -80649134, -68021400, 179184179, 459216960, 459216960, 179184179, -68021400, -80649134, 22354339, 49070362, -9487274, -49795015, -34955643, -6929872, 3097718, 1499280}

#define FIR24TAPS5_12 {3016239, 5738308, -1679970, -18021039, -10780765, 37693189, 55436335, -41562717, -155240046, -30053218, 404571402, 824624103, 824624103, 404571402, -30053218, -155240046, -41562717, 55436335, 37693189, -10780765, -18021039, -1679970, 5738308, 3016239}

#define NUM_STAGES 4

#define BIQUAD20K_8STAGE {740135009, 1480270018, 740135009, 1373991412, 512806799, 40135009, 1480270018, 740135009, 1373991412, 512806799, 40135009, 1480270018, 740135009, 1373991412, 512806799, 40135009, 1480270018, 740135009, 1373991412, 512806799}

// Circular buffer

typedef struct {
    int buff[32];
    int writeIndex;
}buffer;

// IO buffers

// GPIO pin mask for set and clear handling functions
typedef uint32_t logicHandler;

typedef struct {
	q31_t samples;
	logicHandler shAHandler;
	logicHandler shBHandler;
	logicHandler logicAHandler;
	q31_t dac3Sample;
	logicHandler auxLogicHandler;
} audioRateOutputs;

typedef struct {
	q31_t cv2Input;
	q31_t cv3Input;
	q31_t triggerInput;
	q31_t gateInput;
} audioRateInputs;

typedef struct {
	q31_t knob1Value;
	q31_t knob2Value;
	q31_t knob3Value;
	q31_t cv1Value;
} controlRateInputs;

typedef struct {
	uint32_t attackIncrement;
	uint32_t releaseIncrement;
	uint32_t periodCount;
	uint32_t gateOnCount;
	uint32_t flagWord;
	uint32_t phaseSignal;
	Scale * scale;
} softwareSignaling;


controlRateInputs controlRateInput;
audioRateInputs audioRateInput;
audioRateOutputs audioRateOutput;
softwareSignaling softwareSignals;





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

#define fix16_square(X) fix16_mul(X,X)

// doubting such an optimization would work here
// probaby not needed (called once per sample)

static inline int fix24_mul(int in0, int in1) {
	int64_t result = (uint64_t) in0 * in1;
	return result >> 24;
}

static inline int fix48_mul(uint32_t in0, uint32_t in1) {
	// taken from the fixmathlib library
	int64_t result = (uint64_t) in0 * in1;
	return result >> 48;
}


static inline int fix16_lerp(q31_t in0, q31_t in1, int frac) {
	return in0 + fix16_mul(in1 - in0, frac);

}

// this is a decent improvement over the above for the case of 16 bit interpolation points
// no need to cast a 16bit by 16bit multiplication to 64 bit

static inline int fast_16_16_mul(int in0, int in1) {
	return (in0 * in1) >> 16;
}

static inline int fast_16_16_lerp(int in0, int in1, int frac) {
	return in0 + fast_16_16_mul(in1 - in0, frac);
}

// twos complement absolute value

static inline int abs(int n) {
  int mask = n >> 31;
  return ((n + mask) ^ mask);
}

// if cv greater than half scale from knob value to maximum
// otherwise, scale from knob value to minimum

#define combine12BitKnobCVBranchless(KNOB, CV) (CV >> 11)(fix16_lerp(KNOB, 4095, (CV - 2048) << 5)) + !(CV >> 11)(fix16_lerp(KNOB, 4095, (CV) << 5))

#define combine12BitKnobCVTernary(KNOB, CV) ((CV >> 11) ? (fix16_lerp(KNOB, 4095, (CV - 2048) << 5)) : (fix16_lerp(KNOB, 4095, (CV) << 5)))



#endif


