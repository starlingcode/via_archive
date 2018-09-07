#ifndef DSP_H
#define DSP_H

#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"
#define ARM_MATH_CM4
#include "arm_math.h"


#define WAVETABLE_LENGTH 33554432
#define NEGATIVE_WAVETABLE_LENGTH -33554432 // wavetable length in 16 bit fixed point (512 << 16)
#define AT_B_PHASE 16777216 // wavetable midpoint in 16 bit fixed point (256 << 16)

#define BUFFER_SIZE 16

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

static inline int fast_fix15_lerp(int in0, int in1, int frac) {


	  __asm ("SMLAWB %[result_1], %[input_1], %[input_2], %[input_3]"
	    : [result_1] "=r" (in0)
	    : [input_1] "r" (in1 - in0), [input_2] "r" (frac), [input_3] "r" (in0 >> 1)
	  );


	return in0 << 1;
}

// lower quality but faster?
static inline int fix15_bilerp(int in0, int in1, int in2, int in3, int frac0, int frac1) {

	in0 = fast_fix15_lerp(in0, in1, frac0);
	in2 = fast_fix15_lerp(in2, in3, frac0);

	return fast_fix15_lerp(in0, in2, frac1);
}

static inline int fix15_bilerp_alt(int in0, int in1, int in2, int in3, int frac0, int frac1) {

	int invFrac = 32767 - frac0;

	  __asm ("SMULWB %[result_1], %[input_1], %[input_2]"
	    : [result_1] "=r" (in0)
	    : [input_1] "r" (in0), [input_2] "r" (invFrac)
	  );

	  __asm ("SMLAWB %[result_1], %[input_1], %[input_2], %[input_3]"
	    : [result_1] "=r" (in0)
	    : [input_1] "r" (in1), [input_2] "r" (frac0), [input_3] "r" (in0)
	  );

	  __asm ("SMULWB %[result_1], %[input_1], %[input_2]"
	    : [result_1] "=r" (in2)
	    : [input_1] "r" (in2), [input_2] "r" (invFrac)
	  );

	  __asm ("SMLAWB %[result_1], %[input_1], %[input_2], %[input_3]"
	    : [result_1] "=r" (in2)
	    : [input_1] "r" (in3), [input_2] "r" (frac0), [input_3] "r" (in2)
	  );

	  __asm ("SMULWB %[result_1], %[input_1], %[input_2]"
	    : [result_1] "=r" (in0)
	    : [input_1] "r" (in0 << 1), [input_2] "r" (32767 - frac1)
	  );

	  __asm ("SMLAWB %[result_1], %[input_1], %[input_2], %[input_3]"
	    : [result_1] "=r" (in0)
	    : [input_1] "r" (in2 << 1), [input_2] "r" (frac1), [input_3] "r" (in0)
	  );

	return in0 << 1;
}

static inline int fix24_lerp(int in0, int in1, int frac) {
	return in0 + (((int64_t)(in1 - in0) * frac) >> 24);
}

static inline int fast_15_16_lerp(int in0, int in1, int frac) {

	__asm ("SMLAWB %[result_1], %[input_1], %[input_2], %[input_3]"
	    : [result_1] "=r" (in0)
	    : [input_1] "r" (frac), [input_2] "r" (in1 - in0), [input_3] "r" (in0)
	  );

	return in0;
}

static inline int fast_15_16_bilerp(int in0, int in1, int in2, int in3, int frac0, int frac1) {

	__asm ("SMLAWB %[result_1], %[input_1], %[input_2], %[input_3]"
	    : [result_1] "=r" (in0)
	    : [input_1] "r" (frac0), [input_2] "r" (in1 - in0), [input_3] "r" (in0)
	  );

	__asm ("SMLAWB %[result_1], %[input_1], %[input_2], %[input_3]"
	    : [result_1] "=r" (in2)
	    : [input_1] "r" (frac0), [input_2] "r" (in3 - in2), [input_3] "r" (in2)
	  );

	__asm ("SMLAWB %[result_1], %[input_1], %[input_2], %[input_3]"
	    : [result_1] "=r" (in0)
	    : [input_1] "r" (frac1), [input_2] "r" (in2 - in0), [input_3] "r" (in0)
	  );

	return in0;
}

static inline int fast_15_16_bilerp_prediff(int in0, int in1, int frac0, int frac1) {

	__asm ("SMLAWT %[result_1], %[input_1], %[input_2], %[input_3]"
	    : [result_1] "=r" (in0)
	    : [input_1] "r" (frac0), [input_2] "r" (in0), [input_3] "r" (in0 & 0xFFFF)
	  );

	__asm ("SMLAWT %[result_1], %[input_1], %[input_2], %[input_3]"
	    : [result_1] "=r" (in1)
	    : [input_1] "r" (frac0), [input_2] "r" (in1), [input_3] "r" (in1 & 0xFFFF)
	  );

	__asm ("SMLAWB %[result_1], %[input_1], %[input_2], %[input_3]"
	    : [result_1] "=r" (in0)
	    : [input_1] "r" (frac1), [input_2] "r" (in1 - in0), [input_3] "r" (in0)
	  );

	return in0;
}

static inline int wavetableDelta(int in0, int in1, int frac0) {

	// subtract both the difference and the base sample from the left sample with those of the right sample
	in0 = __QSUB(in1, in0);
	// pack a 1 in the bottom 16 bits and the fractional interpolation in the top
	frac0 = __PKHBT(1, frac0, 16);
	// multiply halfwords and accumulate
	return __SMLAD(frac0, in0, 0) >> 31;

}



#endif


