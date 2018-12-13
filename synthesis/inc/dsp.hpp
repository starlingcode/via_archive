
#ifndef INC_VIA_DSP_H_
#define INC_VIA_DSP_H_

#ifdef BUILD_F373

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f3xx.h"
#include <stdint.h>

/** \file dsp.hpp
 * Some math functions.
 * Fixed point arithmetic, interpolation, averaging.
 */

///
/// Circular buffer, max length 32.
///
typedef struct {
	/// Data buffer
	int32_t buff[32];
	/// Write head position
	int32_t writeIndex;
} buffer;

///
/// Circular buffer, max length 256.
///
typedef struct {
	/// Data buffer
	int32_t buff[256];
	/// Write head position
	int32_t writeIndex;
} longBuffer;

///
/// Write to value buffer at current write index and increment index.
///
static inline void writeBuffer(buffer* buffer, int32_t value) {
	buffer->buff[(buffer->writeIndex++) & 31] = value;
}

///
/// Read value at index in buffer relative to write position.
///
static inline int32_t readBuffer(buffer* buffer, int32_t Xn) {
	return buffer->buff[(buffer->writeIndex + (~Xn)) & 31];
}

///
/// Write to value long buffer at current write index and increment index.
///
static inline void writeLongBuffer(longBuffer* buffer, int32_t value) {
	buffer->buff[(buffer->writeIndex++) & 255] = value;
}

/// Read value at index relative to write position.
static inline int32_t readLongBuffer(longBuffer* buffer, int32_t Xn) {
	return buffer->buff[(buffer->writeIndex + (~Xn)) & 255];
}

/**
 *
 * Absolute value for 32 bit int32_t
 *
 */

inline int32_t int32_abs(int32_t n) {
  int32_t mask = n >> 31;
  return ((n + mask) ^ mask);
}

/*
 *
 * Fixed point math
 * (mostly 16 bit)
 *
 */

/// Multiply 16.16 point numbers, overflows when in0*in1 > 1<<48, no saturation.
static inline int32_t fix16_mul(int32_t in0, int32_t in1) {

	int32_t lsb;
	  int32_t msb;

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

/// Multiply 8.24 point numbers, overflows when in0*in1 > 1<<56, no saturation.
static inline int32_t fix24_mul(int32_t in0, int32_t in1) {
	int64_t result = (uint64_t) in0 * in1;
	return result >> 24;
}

/// Multiply 8.24 point numbers, overflows when in0*in1 > 1<<64, no saturation.
static inline int32_t fix48_mul(uint32_t in0, uint32_t in1) {
	// taken from the fixmathlib library
	int64_t result = (uint64_t) in0 * in1;
	return result >> 48;
}

/*
 *
 * Interpolation
 *
 */

/// Linear interpolation. in0 and in1 can be full scale 32 bit, frac ranges from 0 - 0xFFFF
static inline int32_t fix16_lerp(int32_t in0, int32_t in1, int32_t frac) {
	// maybe could do this better by shoving frac up by 16,
	// loading in0 in the msb of a 64 bit accumulator,
	// and taking the topword of SMLLA
	return in0 + fix16_mul(in1 - in0, frac);
}

/// Faster linear interpolation. in0 and in1 must be 16 bit, frac ranges from 0 - 0xFFFF
static inline int32_t fast16_16_lerp(int32_t in0, int32_t in1, int32_t frac) {
	return in0 + (((in1 - in0) * frac) >> 16);
}

/// Fastest linear interpolation. in0 and in1 must be 16 bit, frac ranges from 0 - 0x7FFF
static inline int32_t fast_fix15_lerp(int32_t in0, int32_t in1, int32_t frac) {

	__asm ("SMLAWB %[result_1], %[input_1], %[input_2], %[input_3]"
			: [result_1] "=r" (in0)
			: [input_1] "r" (in1 - in0), [input_2] "r" (frac), [input_3] "r" (in0 >> 1)
	);

	return in0 << 1;
}

/// Fastest linear interpolation, good for sample values
static inline int32_t fast_15_16_lerp(int32_t in0, int32_t in1, int32_t frac) {

	__asm ("SMLAWB %[result_1], %[input_1], %[input_2], %[input_3]"
			: [result_1] "=r" (in0)
			: [input_1] "r" (frac), [input_2] "r" (in1 - in0), [input_3] "r" (in0)
	);

	return in0;
}

/// Bilinear interpolation using fast_fix15_lerp, frac0 interpolates between in0 and in1 then in2 and in3, frac 1 interpolates between those results
static inline int32_t fix15_bilerp(int32_t in0, int32_t in1, int32_t in2, int32_t in3, int32_t frac0,
		int32_t frac1) {

	in0 = fast_fix15_lerp(in0, in1, frac0);
	in2 = fast_fix15_lerp(in2, in3, frac0);

	return fast_fix15_lerp(in0, in2, frac1);
}

/// Bilinear interpolation alt form, frac0 interpolates between in0 and in1 then in2 and in3, frac 1 interpolates between those results
static inline int32_t fix15_bilerp_alt(int32_t in0, int32_t in1, int32_t in2, int32_t in3,
		int32_t frac0, int32_t frac1) {

	int32_t invFrac = 32767 - frac0;

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

static inline int32_t fast_15_16_lerp_prediff(int32_t in0, int32_t frac) {

	__asm ("SMLAWT %[result_1], %[input_1], %[input_2], %[input_3]"
			: [result_1] "=r" (in0)
			: [input_1] "r" (frac), [input_2] "r" (in0), [input_3] "r" (in0 & 0xFFFF)
	);

	return in0;
}

// inherits those values

static inline int32_t fast_15_16_bilerp(int32_t in0, int32_t in1, int32_t in2, int32_t in3,
		int32_t frac0, int32_t frac1) {

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

static inline int32_t fast_15_16_bilerp_prediff(int32_t in0, int32_t in1, int32_t frac0,
		int32_t frac1) {

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

static inline int32_t fast_15_16_bilerp_prediff_delta(int32_t in0, int32_t in1, int32_t frac0,
		int32_t frac1, int32_t * delta) {

	__asm ("SMLAWT %[result_1], %[input_1], %[input_2], %[input_3]"
			: [result_1] "=r" (in0)
			: [input_1] "r" (frac0), [input_2] "r" (in0), [input_3] "r" (in0 & 0xFFFF)
	);

	__asm ("SMLAWT %[result_1], %[input_1], %[input_2], %[input_3]"
			: [result_1] "=r" (in1)
			: [input_1] "r" (frac0), [input_2] "r" (in1), [input_3] "r" (in1 & 0xFFFF)
	);

	*delta = ((uint32_t) in1 - in0) >> 31;

	__asm ("SMLAWB %[result_1], %[input_1], %[input_2], %[input_3]"
			: [result_1] "=r" (in0)
			: [input_1] "r" (frac1), [input_2] "r" (in1 - in0), [input_3] "r" (in0)
	);

	return in0;
}

static inline int32_t fast_15_16_bilerp_prediff_deltaValue(int32_t in0, int32_t in1, int32_t frac0,
		int32_t frac1, int32_t * delta) {

	__asm ("SMLAWT %[result_1], %[input_1], %[input_2], %[input_3]"
			: [result_1] "=r" (in0)
			: [input_1] "r" (frac0), [input_2] "r" (in0), [input_3] "r" (in0 & 0xFFFF)
	);

	__asm ("SMLAWT %[result_1], %[input_1], %[input_2], %[input_3]"
			: [result_1] "=r" (in1)
			: [input_1] "r" (frac0), [input_2] "r" (in1), [input_3] "r" (in1 & 0xFFFF)
	);

	*delta = (uint32_t) in1 - in0;

	__asm ("SMLAWB %[result_1], %[input_1], %[input_2], %[input_3]"
			: [result_1] "=r" (in0)
			: [input_1] "r" (frac1), [input_2] "r" (in1 - in0), [input_3] "r" (in0)
	);

	return in0;
}

// overkill probably, assumes 9 tables and 517 samples padded with two at the start and end of each waveform
// this is fortunately the default table load
// morph should have a max value of the table size

static inline int32_t getSampleQuinticSpline(uint32_t phase, uint32_t morph,
		uint32_t *fullTableHoldArray, int32_t *delta) {

	/* in this function, we use our phase position to get the sample to give to our dacs using a quintic spline interpolation technique
	 essentially, we need to get 6 pairs of sample values and two "fractional arguments" (where are we at in between those sample values)
	 one fractional argument determines the relative position in a linear interpolation between the sample values (morph)
	 the other is the fractional phase argument used in the interpolation calculation
	 */

	uint32_t LnSample; // indicates the left most sample in the neighborhood of sample values around the phase pointer
	uint32_t LnFamily; // indicates the nearest neighbor (wavetable) to our morph value in the family
	uint32_t phaseFrac; // indicates the fractional distance between the nearest sample values in terms of phase
	uint32_t morphFrac; // indicates the fractional distance between our nearest neighbors in the family
	uint32_t * leftIndex;

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

	int32_t sample0 = fast_15_16_lerp_prediff(*leftIndex, morphFrac);
	int32_t sample1 = fast_15_16_lerp_prediff(*(leftIndex + 1), morphFrac);
	int32_t sample2 = fast_15_16_lerp_prediff(*(leftIndex + 2), morphFrac);
	int32_t sample3 = fast_15_16_lerp_prediff(*(leftIndex + 3), morphFrac);
	int32_t sample4 = fast_15_16_lerp_prediff(*(leftIndex + 4), morphFrac);
	int32_t sample5 = fast_15_16_lerp_prediff(*(leftIndex + 5), morphFrac);

	// a version of the spline forumula from Josh Scholar on the musicdsp mailing list
	// https://web.archive.org/web/20170705065209/http://www.musicdsp.org/showArchiveComment.php?ArchiveID=60

	int32_t out = (sample2 + fix24_mul(699051, fix16_mul(phaseFrac, ((sample3-sample1)*16 + (sample0-sample4)*2
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

static inline int32_t getSampleQuinticSplineDeltaValue(uint32_t phase, uint32_t morph,
		uint32_t *fullTableHoldArray, int32_t *delta, uint32_t interpOff) {

	/* in this function, we use our phase position to get the sample to give to our dacs using a quintic spline interpolation technique
	 essentially, we need to get 6 pairs of sample values and two "fractional arguments" (where are we at in between those sample values)
	 one fractional argument determines the relative position in a linear interpolation between the sample values (morph)
	 the other is the fractional phase argument used in the interpolation calculation
	 */

	uint32_t LnSample; // indicates the left most sample in the neighborhood of sample values around the phase pointer
	uint32_t LnFamily; // indicates the nearest neighbor (wavetable) to our morph value in the family
	uint32_t phaseFrac; // indicates the fractional distance between the nearest sample values in terms of phase
	uint32_t morphFrac; // indicates the fractional distance between our nearest neighbors in the family
	uint32_t * leftIndex;

	// we do a lot of tricky bitshifting to take advantage of the structure of a 16 bit fixed point number
	// truncate phase then add two to find the left neighboring sample of the phase pointer

	LnSample = phase >> 16;

	// bit shifting to divide by the correct power of two takes a 12 bit number (our morph) and returns the a quotient in the range of our family size

	LnFamily = morph >> 16;

	leftIndex = (fullTableHoldArray + LnFamily * 517) + LnSample;

	// determine the fractional part of our phase phase by masking off the integer

	phaseFrac = (0xFFFF & phase);

	// we have to calculate the fractional portion and get it up to full scale q16

	morphFrac = (morph & 0xFFFF);

	// perform the 6 linear interpolations to get the sample values and apply morph
	// TODO track delta change in the phase event array

	int32_t sample0 = fast_15_16_lerp_prediff(*leftIndex, morphFrac);
	int32_t sample1 = fast_15_16_lerp_prediff(*(leftIndex + 1), morphFrac);
	int32_t sample2 = fast_15_16_lerp_prediff(*(leftIndex + 2), morphFrac);
	int32_t sample3 = fast_15_16_lerp_prediff(*(leftIndex + 3), morphFrac);
	int32_t sample4 = fast_15_16_lerp_prediff(*(leftIndex + 4), morphFrac);
	int32_t sample5 = fast_15_16_lerp_prediff(*(leftIndex + 5), morphFrac);

	// a version of the spline forumula from Josh Scholar on the musicdsp mailing list
	// https://web.archive.org/web/20170705065209/http://www.musicdsp.org/showArchiveComment.php?ArchiveID=60

	int32_t out = (sample2 + fix24_mul(699051, fix16_mul(phaseFrac, ((sample3-sample1)*16 + (sample0-sample4)*2
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

	out += (sample2 - out) * interpOff;

	*delta = (sample3 - sample2);

	return __USAT(out, 15);
}


/*
 *
 * Fold/wrap
 *
 */

static inline int32_t foldSignal16Bit(int32_t phaseIn) {

	// fold into the space [0, 2^16)
	// check the lsb of abs(input) >> 15 (is phaseIn / 2^15 even or odd)
	// mathematical conditional that adds the modulo 2^15 for odd and the inversion of that in 15 bit space for even

	return ((phaseIn >> 16) & 1) ?
			(65535 - (phaseIn & 0xFFFF)) : (phaseIn & 0xFFFF);

}

static inline int32_t foldSignal25Bit(int32_t phaseIn) {

	// fold into the space [0, 2^25)
	// check the lsb of abs(input) >> 15 (is phaseIn / 2^15 even or odd)
	// mathematical conditional that adds the modulo 2^15 for odd and the inversion of that in 15 bit space for even

	return ((phaseIn >> 25) & 1) ?
			(0x1FFFFFF - (phaseIn & 0x1FFFFFF)) : (phaseIn & 0x1FFFFFF);

}

static inline int32_t wrapSignal16Bit(int32_t phaseIn) {

	// wrap into the space [0, 2^15) by calculating the input modulo 2^15

	return phaseIn & 0xFFFF;

}

/*
 *
 * Odball notes
 *
 *
 */

static inline int32_t wavetableDelta(int32_t in0, int32_t in1, int32_t frac0) {

	// subtract both the difference and the base sample from the left sample with those of the right sample
	in0 = __QSUB(in1, in0);
	// pack a 1 in the bottom 16 bits and the fractional interpolation in the top
	frac0 = __PKHBT(1, frac0, 16);
	// multiply halfwords and accumulate
	return __SMLAD(frac0, in0, 0) >> 31;

}

#ifdef __cplusplus
}
#endif

#endif

#ifdef BUILD_VIRTUAL

#include <cstdint>
//#include <algorithm>
typedef struct {
	int32_t buff[32];
	int32_t writeIndex;
} buffer;

typedef struct {
	int32_t buff[256];
	int32_t writeIndex;
} longBuffer;

static inline void writeBuffer(buffer* buffer, int32_t value) {
	buffer->buff[(buffer->writeIndex++) & 31] = value;
}

static inline int32_t readBuffer(buffer* buffer, int32_t Xn) {
	return buffer->buff[(buffer->writeIndex + (~Xn)) & 31];
}

static inline void writeLongBuffer(longBuffer* buffer, int32_t value) {
	buffer->buff[(buffer->writeIndex++) & 255] = value;
}

static inline int32_t readLongBuffer(longBuffer* buffer, int32_t Xn) {
	return buffer->buff[(buffer->writeIndex + (~Xn)) & 255];
}

static inline int32_t __USAT(int32_t X, int32_t Y) {

	if (X > ((1 << Y) - 1)) {
		return ((1 << Y) - 1);
	} else if (X < 0) {
		return 0;
	} else {
		return X;
	}

}

static inline int32_t __SSAT(int32_t X, int32_t Y) {
	if (X > ((1 << Y) - 1)) {
		return ((1 << Y) - 1);
	} else if (X < ((-1 << Y) + 1)) {
		return ((-1 << Y) + 1);
	} else {
		return X;
	}

}

inline int32_t int32_abs(int32_t n) {
  int32_t mask = n >> 31;
  return ((n + mask) ^ mask);
}

static inline int32_t fix16_mul(int32_t in0, int32_t in1) {
	int64_t result = (uint64_t) in0 * in1;
	return result >> 16;
}

static inline int32_t fix24_mul(int32_t in0, int32_t in1) {
	int64_t result = (uint64_t) in0 * in1;
	return result >> 24;
}

static inline int32_t fix48_mul(uint32_t in0, uint32_t in1) {
	// taken from the fixmathlib library
	int64_t result = (uint64_t) in0 * in1;
	return result >> 48;
}

static inline int32_t fix16_lerp(int32_t in0, int32_t in1, int32_t frac) {
	return in0 + fix16_mul(in1 - in0, frac);
}

// in0 and in1 can be full scale 32 bit, frac max is 15 bits (!!!)

static inline int32_t fast_fix15_lerp(int32_t in0, int32_t in1, int32_t frac) {
	return in0 + fix16_mul(in1 - in0, frac << 1);
}

static inline int32_t fast_15_16_lerp(int32_t in0, int32_t in1, int32_t frac) {

	return in0 + (((in1 - in0) * frac) >> 16);
}

// same value ranges

// lower quality but faster?
static inline int32_t fix15_bilerp(int32_t in0, int32_t in1, int32_t in2, int32_t in3, int32_t frac0,
		int32_t frac1) {

	in0 = fast_fix15_lerp(in0, in1, frac0);
	in2 = fast_fix15_lerp(in2, in3, frac0);

	return fast_fix15_lerp(in0, in2, frac1);
}

static inline int32_t fast_15_16_lerp_prediff(int32_t in0, int32_t frac) {

	return (in0 & 0xFFFF) + (((in0 >> 16)*frac) >> 16);
}

// assume in0 and in have the base value and the difference to the next point packed in bottom and top word
// frac0 and frac1 can be up to 16 bits

static inline int32_t fast_15_16_bilerp_prediff(int32_t in0, int32_t in1, int32_t frac0,
		int32_t frac1) {

	in0 = (in0 & 0xFFFF) + (((in0 >> 16)*frac0) >> 16);

	in1 = (in1 & 0xFFFF) + (((in1 >> 16)*frac0) >> 16);

	return in0 + ((in1 - in0)*frac1 >> 16); 

}

static inline int32_t fast_15_16_bilerp_prediff_delta(int32_t in0, int32_t in1, int32_t frac0,
		int32_t frac1, int32_t * delta) {

	in0 = (in0 & 0xFFFF) + (((in0 >> 16)*frac0) >> 16);

	in1 = (in1 & 0xFFFF) + (((in1 >> 16)*frac0) >> 16);

	*delta = ((uint32_t) in1 - in0) >> 31;

	return in0 + ((in1 - in0)*frac1 >> 16); 

}

static inline int32_t fast_15_16_bilerp_prediff_deltaValue(int32_t in0, int32_t in1, int32_t frac0,
		int32_t frac1, int32_t * delta) {

	in0 = (in0 & 0xFFFF) + (((in0 >> 16)*frac0) >> 16);

	in1 = (in1 & 0xFFFF) + (((in1 >> 16)*frac0) >> 16);

	*delta = in1 - in0;

	return in0 + ((in1 - in0)*frac1 >> 16); 

}


// overkill probably, assumes 9 tables and 517 samples padded with two at the start and end of each waveform
// this is fortunately the default table load
// morph should have a max value of the table size

static inline int32_t getSampleQuinticSpline(uint32_t phase, uint32_t morph,
		uint32_t *fullTableHoldArray, int32_t *delta) {

	/* in this function, we use our phase position to get the sample to give to our dacs using a quintic spline interpolation technique
	 essentially, we need to get 6 pairs of sample values and two "fractional arguments" (where are we at in between those sample values)
	 one fractional argument determines the relative position in a linear interpolation between the sample values (morph)
	 the other is the fractional phase argument used in the interpolation calculation
	 */

	uint32_t LnSample; // indicates the left most sample in the neighborhood of sample values around the phase pointer
	uint32_t LnFamily; // indicates the nearest neighbor (wavetable) to our morph value in the family
	uint32_t phaseFrac; // indicates the fractional distance between the nearest sample values in terms of phase
	uint32_t morphFrac; // indicates the fractional distance between our nearest neighbors in the family
	uint32_t * leftIndex;

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

	int32_t sample0 = fast_15_16_lerp_prediff(*leftIndex, morphFrac);
	int32_t sample1 = fast_15_16_lerp_prediff(*(leftIndex + 1), morphFrac);
	int32_t sample2 = fast_15_16_lerp_prediff(*(leftIndex + 2), morphFrac);
	int32_t sample3 = fast_15_16_lerp_prediff(*(leftIndex + 3), morphFrac);
	int32_t sample4 = fast_15_16_lerp_prediff(*(leftIndex + 4), morphFrac);
	int32_t sample5 = fast_15_16_lerp_prediff(*(leftIndex + 5), morphFrac);

	// a version of the spline forumula from Josh Scholar on the musicdsp mailing list
	// https://web.archive.org/web/20170705065209/http://www.musicdsp.org/showArchiveComment.php?ArchiveID=60

	int32_t out = (sample2 + fix24_mul(699051, fix16_mul(phaseFrac, ((sample3-sample1)*16 + (sample0-sample4)*2
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

static inline int32_t getSampleQuinticSplineDeltaValue(uint32_t phase, uint32_t morph,
		uint32_t *fullTableHoldArray, int32_t *delta) {

	/* in this function, we use our phase position to get the sample to give to our dacs using a quintic spline interpolation technique
	 essentially, we need to get 6 pairs of sample values and two "fractional arguments" (where are we at in between those sample values)
	 one fractional argument determines the relative position in a linear interpolation between the sample values (morph)
	 the other is the fractional phase argument used in the interpolation calculation
	 */

	uint32_t LnSample; // indicates the left most sample in the neighborhood of sample values around the phase pointer
	uint32_t LnFamily; // indicates the nearest neighbor (wavetable) to our morph value in the family
	uint32_t phaseFrac; // indicates the fractional distance between the nearest sample values in terms of phase
	uint32_t morphFrac; // indicates the fractional distance between our nearest neighbors in the family
	uint32_t * leftIndex;

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

	int32_t sample0 = fast_15_16_lerp_prediff(*leftIndex, morphFrac);
	int32_t sample1 = fast_15_16_lerp_prediff(*(leftIndex + 1), morphFrac);
	int32_t sample2 = fast_15_16_lerp_prediff(*(leftIndex + 2), morphFrac);
	int32_t sample3 = fast_15_16_lerp_prediff(*(leftIndex + 3), morphFrac);
	int32_t sample4 = fast_15_16_lerp_prediff(*(leftIndex + 4), morphFrac);
	int32_t sample5 = fast_15_16_lerp_prediff(*(leftIndex + 5), morphFrac);

	// a version of the spline forumula from Josh Scholar on the musicdsp mailing list
	// https://web.archive.org/web/20170705065209/http://www.musicdsp.org/showArchiveComment.php?ArchiveID=60

	int32_t out = (sample2 + fix24_mul(699051, fix16_mul(phaseFrac, ((sample3-sample1)*16 + (sample0-sample4)*2
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

	*delta = (sample3 - sample2);

	return __USAT(out, 15);
}

static inline int32_t getSampleQuinticSplineDeltaValue(uint32_t phase, uint32_t morph,
		uint32_t *fullTableHoldArray, int32_t *delta, uint32_t interpOff) {

	/* in this function, we use our phase position to get the sample to give to our dacs using a quintic spline interpolation technique
	 essentially, we need to get 6 pairs of sample values and two "fractional arguments" (where are we at in between those sample values)
	 one fractional argument determines the relative position in a linear interpolation between the sample values (morph)
	 the other is the fractional phase argument used in the interpolation calculation
	 */

	uint32_t LnSample; // indicates the left most sample in the neighborhood of sample values around the phase pointer
	uint32_t LnFamily; // indicates the nearest neighbor (wavetable) to our morph value in the family
	uint32_t phaseFrac; // indicates the fractional distance between the nearest sample values in terms of phase
	uint32_t morphFrac; // indicates the fractional distance between our nearest neighbors in the family
	uint32_t * leftIndex;

	// we do a lot of tricky bitshifting to take advantage of the structure of a 16 bit fixed point number
	// truncate phase then add two to find the left neighboring sample of the phase pointer

	LnSample = phase >> 16;

	// bit shifting to divide by the correct power of two takes a 12 bit number (our morph) and returns the a quotient in the range of our family size

	LnFamily = morph >> 16;

	leftIndex = (fullTableHoldArray + LnFamily * 517) + LnSample;

	// determine the fractional part of our phase phase by masking off the integer

	phaseFrac = (0xFFFF & phase);

	// we have to calculate the fractional portion and get it up to full scale q16

	morphFrac = (morph & 0xFFFF);

	// perform the 6 linear interpolations to get the sample values and apply morph
	// TODO track delta change in the phase event array

	int32_t sample0 = fast_15_16_lerp_prediff(*leftIndex, morphFrac);
	int32_t sample1 = fast_15_16_lerp_prediff(*(leftIndex + 1), morphFrac);
	int32_t sample2 = fast_15_16_lerp_prediff(*(leftIndex + 2), morphFrac);
	int32_t sample3 = fast_15_16_lerp_prediff(*(leftIndex + 3), morphFrac);
	int32_t sample4 = fast_15_16_lerp_prediff(*(leftIndex + 4), morphFrac);
	int32_t sample5 = fast_15_16_lerp_prediff(*(leftIndex + 5), morphFrac);

	// a version of the spline forumula from Josh Scholar on the musicdsp mailing list
	// https://web.archive.org/web/20170705065209/http://www.musicdsp.org/showArchiveComment.php?ArchiveID=60

	int32_t out = (sample2 + fix24_mul(699051, fix16_mul(phaseFrac, ((sample3-sample1)*16 + (sample0-sample4)*2
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

	out += (sample2 - out) * interpOff;

	*delta = (sample3 - sample2);

	return __USAT(out, 15);
}


/*
 *
 * Fold/wrap
 *
 */

static inline int32_t foldSignal16Bit(int32_t phaseIn) {

	// fold into the space [0, 2^16)
	// check the lsb of abs(input) >> 15 (is phaseIn / 2^15 even or odd)
	// mathematical conditional that adds the modulo 2^15 for odd and the inversion of that in 15 bit space for even

	return ((phaseIn >> 16) & 1) ?
			(65535 - (phaseIn & 0xFFFF)) : (phaseIn & 0xFFFF);

}


static inline int32_t foldSignal25Bit(int32_t phaseIn) {

	// fold into the space [0, 2^25)
	// check the lsb of abs(input) >> 15 (is phaseIn / 2^15 even or odd)
	// mathematical conditional that adds the modulo 2^15 for odd and the inversion of that in 15 bit space for even

	return ((phaseIn >> 25) & 1) ?
			(0x1FFFFFF - (phaseIn & 0x1FFFFFF)) : (phaseIn & 0x1FFFFFF);

}

static inline int32_t wrapSignal16Bit(int32_t phaseIn) {

	// wrap into the space [0, 2^15) by calculating the input modulo 2^15

	return phaseIn & 0xFFFF;

}

#endif



#endif /* INC_DSP_INLINES_H_ */
