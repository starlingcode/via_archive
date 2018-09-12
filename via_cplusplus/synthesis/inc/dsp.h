/*
 * dsp.h
 *
 *  Created on: Aug 18, 2018
 *      Author: willmitchell
 */

#ifndef INC_VIA_DSP_H_
#define INC_VIA_DSP_H_

/*
 *
 * Circular buffer
 *
 */

typedef struct {
	int buff[32];
	int writeIndex;
} buffer;

static inline void writeBuffer(buffer* buffer, int value) {
	buffer->buff[(buffer->writeIndex++) & 31] = value;
}

static inline int readBuffer(buffer* buffer, int Xn) {
	return buffer->buff[(buffer->writeIndex + (~Xn)) & 31];
}

/*
 *
 * Absolute value for 32 bit int
 *
 */

static inline int abs(int n) {
  int mask = n >> 31;
  return ((n + mask) ^ mask);
}

/*
 *
 * Fixed point math
 * (mostly 16 bit)
 *
 */

// overflows when in0*in1 > 1<<48, no saturation
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
static inline int fix24_mul(int in0, int in1) {
	int64_t result = (uint64_t) in0 * in1;
	return result >> 24;
}


static inline int fix48_mul(uint32_t in0, uint32_t in1) {
	// taken from the fixmathlib library
	int64_t result = (uint64_t) in0 * in1;
	return result >> 48;
}

/*
 *
 * Interpolation
 *
 */

// in0 and in1 can be full scale 32 bit, frac max is 16 bits
static inline int fix16_lerp(int in0, int in1, int frac) {
	// maybe could do this better by shoving frac up by 16,
	// loading in0 in the msb of a 64 bit accumulator,
	// and taking the topword of SMLLA
	return in0 + fix16_mul(in1 - in0, frac);
}

// in0 and in1 must each be 16 bits max, frac max is 16 bits

static inline int fast16_16_lerp(int in0, int in1, int frac) {
	return in0 + (((in1 - in0) * frac) >> 16);
}

// in0 and in1 can be full scale 32 bit, frac max is 15 bits (!!!)

static inline int fast_fix15_lerp(int in0, int in1, int frac) {

	__asm ("SMLAWB %[result_1], %[input_1], %[input_2], %[input_3]"
			: [result_1] "=r" (in0)
			: [input_1] "r" (in1 - in0), [input_2] "r" (frac), [input_3] "r" (in0 >> 1)
	);

	return in0 << 1;
}

// same value ranges

// lower quality but faster?
static inline int fix15_bilerp(int in0, int in1, int in2, int in3, int frac0,
		int frac1) {

	in0 = fast_fix15_lerp(in0, in1, frac0);
	in2 = fast_fix15_lerp(in2, in3, frac0);

	return fast_fix15_lerp(in0, in2, frac1);
}

// alternate form
static inline int fix15_bilerp_alt(int in0, int in1, int in2, int in3,
		int frac0, int frac1) {

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

// naive implmentation kinda cruft
static inline int fix24_lerp(int in0, int in1, int frac) {
	return in0 + (((signed long long) (in1 - in0) * frac) >> 24);
}

// fastest, good for sample values
// in0 and in1 must be each max 15 bits, frac is max 16 bits

static inline int fast_15_16_lerp(int in0, int in1, int frac) {

	__asm ("SMLAWB %[result_1], %[input_1], %[input_2], %[input_3]"
			: [result_1] "=r" (in0)
			: [input_1] "r" (frac), [input_2] "r" (in1 - in0), [input_3] "r" (in0)
	);

	return in0;
}

static inline int fast_15_16_lerp_prediff(int in0, int frac) {

	__asm ("SMLAWT %[result_1], %[input_1], %[input_2], %[input_3]"
			: [result_1] "=r" (in0)
			: [input_1] "r" (frac), [input_2] "r" (in0), [input_3] "r" (in0 & 0xFFFF)
	);

	return in0;
}

// inherits those values

static inline int fast_15_16_bilerp(int in0, int in1, int in2, int in3,
		int frac0, int frac1) {

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

// assume in0 and in have the base value and the difference to the next point packed in bottom and top word
// frac0 and frac1 can be up to 16 bits

static inline int fast_15_16_bilerp_prediff(int in0, int in1, int frac0,
		int frac1) {

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

// overkill probably, assumes 9 tables and 517 samples padded with two at the start and end of each waveform
// this is fortunately the default table load
// morph should have a max value of the table size

static inline int getSampleQuinticSpline(int phase, uint32_t morph,
		int *fullTableHoldArray, int *delta) {

	/* in this function, we use our phase position to get the sample to give to our dacs using a quintic spline interpolation technique
	 essentially, we need to get 6 pairs of sample values and two "fractional arguments" (where are we at in between those sample values)
	 one fractional argument determines the relative position in a linear interpolation between the sample values (morph)
	 the other is the fractional phase argument used in the interpolation calculation
	 */

	uint32_t LnSample; // indicates the left most sample in the neighborhood of sample values around the phase pointer
	uint32_t LnFamily; // indicates the nearest neighbor (wavetable) to our morph value in the family
	uint32_t phaseFrac; // indicates the fractional distance between the nearest sample values in terms of phase
	uint32_t morphFrac; // indicates the fractional distance between our nearest neighbors in the family
	int * leftIndex;
	int * rightIndex;

	// we do a lot of tricky bitshifting to take advantage of the structure of a 16 bit fixed point number
	// truncate phase then add two to find the left neighboring sample of the phase pointer

	LnSample = phase >> 16;

	// bit shifting to divide by the correct power of two takes a 12 bit number (our morph) and returns the a quotient in the range of our family size

	LnFamily = morph >> 16;

	leftIndex = (fullTableHoldArray + LnFamily * 517) + LnSample;

	// determine the fractional part of our phase phase by masking off the integer

	phaseFrac = 0xFFFF & phase;

	// we have to calculate the fractional portion and get it up to full scale q16

	morphFrac = (morph & 0xFFFF);

	// perform the 6 linear interpolations to get the sample values and apply morph
	// TODO track delta change in the phase event array

	int sample0 = fast_15_16_lerp_prediff(*leftIndex, morphFrac);
	int sample1 = fast_15_16_lerp_prediff(*(leftIndex + 1), morphFrac);
	int sample2 = fast_15_16_lerp_prediff(*(leftIndex + 2), morphFrac);
	int sample3 = fast_15_16_lerp_prediff(*(leftIndex + 3), morphFrac);
	int sample4 = fast_15_16_lerp_prediff(*(leftIndex + 4), morphFrac);
	int sample5 = fast_15_16_lerp_prediff(*(leftIndex + 5), morphFrac);

	// a version of the spline forumula from Josh Scholar on the musicdsp mailing list
	// https://web.archive.org/web/20170705065209/http://www.musicdsp.org/showArchiveComment.php?ArchiveID=60

	int out = (sample2 + fix24_mul(699051, fix16_mul(phaseFrac, ((sample3-sample1)*16 + (sample0-sample4)*2
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

	*delta = ((uint32_t) (sample3 - sample2)) >> 31;

	return __USAT(out, 15);
}

/*
 *
 * Fold/wrap
 *
 */

static inline int foldSignal16Bit(int phaseIn) {

	// fold into the space [0, 2^16)
	// check the lsb of abs(input) >> 15 (is phaseIn / 2^15 even or odd)
	// mathematical conditional that adds the modulo 2^15 for odd and the inversion of that in 15 bit space for even

	return ((phaseIn >> 16) & 1) ?
			(65535 - (phaseIn & 0xFFFF)) : (phaseIn & 0xFFFF);

}

static inline int wrapSignal16Bit(int phaseIn) {

	// wrap into the space [0, 2^15) by calculating the input modulo 2^15

	return phaseIn & 0xFFFF;

}

/*
 *
 * Odball notes
 *
 *
 */

static inline int wavetableDelta(int in0, int in1, int frac0) {

	// subtract both the difference and the base sample from the left sample with those of the right sample
	in0 = __QSUB(in1, in0);
	// pack a 1 in the bottom 16 bits and the fractional interpolation in the top
	frac0 = __PKHBT(1, frac0, 16);
	// multiply halfwords and accumulate
	return __SMLAD(frac0, in0, 0) >> 31;

}

#endif /* INC_DSP_INLINES_H_ */
