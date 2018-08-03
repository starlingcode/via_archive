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

#define BUFFER_SIZE 64

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

// initialization functions

void initializeFilter(void);
void initialializeVirtualGround(void);
void initializeDoubleBuffer(void);

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

// doubting such an optimization would work here
// probaby not needed (called once per sample)

static inline int fix24_mul(int in0, int in1) {
	int64_t result = (uint64_t) in0 * in1;
	return result >> 24;
}


static inline int fix16_lerp(q31_t in0, q31_t in1, int frac) {
	return in0 + fix16_mul(in1 - in0, frac);

}

// experimental approach condensing the two lienar interpolations into one function, no performance increase
//static inline int fast_16_16_bilerp(int inA_0, int inA_1, int inB_0, int inB_1, int fracA, int fracB) {
//	return inA_0 + fix16_mul(inA_1 - inA_0, fracA)
//				+ fix16_mul(fracB, (inB_0 - inA_0) + fix16_mul(fracA, inB_1 + inA_0 - inB_0 - inA_1));
//}

// this is a decent improvement over the above for the case of 16 bit interpolation points
// no need to cast a 16bit by 16bit multiplication to 64 bit

static inline int fast_16_16_mul(int in0, int in1) {
	return (in0 * in1) >> 16;
}

static inline int fast_16_16_lerp(int in0, int in1, int frac) {
	return in0 + fast_16_16_mul(in1 - in0, frac);
}



#endif


