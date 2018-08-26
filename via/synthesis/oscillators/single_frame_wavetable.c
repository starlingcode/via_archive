/*
 * single_frame_wavetable.c
 *
 *  Created on: Aug 26, 2018
 *      Author: willmitchell
 */

#include "oscillators.h"

#define WAVETABLE_LENGTH 33554432
#define NEGATIVE_WAVETABLE_LENGTH -33554432 // wavetable length in 16 bit fixed point (512 << 16)
#define AT_B_PHASE 16777216 // wavetable midpoint in 16 bit fixed point (256 << 16)

void singleSampleWavetableParseControls(controlRateInputs * controls,
		singleSampleWavetableParameters * parameters) {

	parameters->morphBase = controls->knob3Value << 4;

}

static inline int singleSampleWavetableIncrementPhase(singleSampleWavetableParameters * parameters,
		uint32_t * phaseDistTable) {

	q31_t phase = parameters->phase;
	static q31_t previousPhase;

	// apply FM, which should be 1 at ground (offset is comensated for here)

	int fmAmount = (parameters->fm[0] - parameters->cv2Offset) + 65535;

	int increment = fix16_mul(parameters->increment, fmAmount);

	// apply phase modulation

	phase += increment + ((parameters->pm[0] - previousPhase) << 6);

	// a zero will resync

	phase *= parameters->phaseReset;
	parameters->phaseReset = 1;

	int phaseEventCalculator = 0;

	// add wavetable length if phase < 0

	phaseEventCalculator += ((uint32_t)(phase) >> 31) * WAVETABLE_LENGTH;

	// subtract wavetable length if phase > wavetable length

	phaseEventCalculator -= ((uint32_t)(WAVETABLE_LENGTH - phase) >> 31) * WAVETABLE_LENGTH;

	// apply the wrapping
	// no effect if the phase is in bounds

	phase += phaseEventCalculator;

	// log a -1 if the max value index of the wavetable is traversed from the left
	// log a 1 if traversed from the right
	// do this by subtracting the sign bit of the last phase from the current phase, both less the max phase index
	// this adds cruft to the wrap indicators, but that is deterministic and can be parsed out

	parameters->phase = phase;

	uint32_t pwm = (int) parameters->pwm[0] + 32768;
	uint32_t pwmIndex = (pwm >> 11);
	uint32_t pwmFrac = (pwm & 0x7FF) << 4;
	uint32_t * pwmTable1 = phaseDistTable + pwmIndex * 65;
	uint32_t * pwmTable2 = pwmTable1 + 65;
	uint32_t leftSample = phase >> 19;

#define pwmPhaseFrac (phase & 0x7FFFF) >> 4
		// use this with the precalculated pwm to perform bilinear interpolation
		// this accomplishes the
	int	ghostPhase = fix15_bilerp(pwmTable1[leftSample], pwmTable2[leftSample],
				pwmTable1[leftSample + 1], pwmTable2[leftSample + 1], pwmFrac,
				pwmPhaseFrac);

	int atBIndicator = ((uint32_t)(ghostPhase - AT_B_PHASE) >> 31) - ((uint32_t)(previousPhase - AT_B_PHASE) >> 31);

	phaseEventCalculator += atBIndicator;

	parameters->phaseEvent = phaseEventCalculator;

	// store the current phase
	previousPhase = ghostPhase;

	return ghostPhase;

}


uint32_t singleSampleWavetableAdvance(
		singleSampleWavetableParameters * parameters,
		uint32_t * wavetable, uint32_t * phaseDistTable) {

	uint32_t ghostPhase = singleSampleWavetableIncrementPhase(parameters);

	uint32_t morph = __USAT(parameters->morphMod[0] + parameters->morphBase, 16);

	morph *= parameters->tableSize;

	return getSampleQuinticSpline(ghostPhase, morph, wavetable, &(parameters->delta));

}
