/*
 * single_frame_wavetable.c
 *
 *  Created on: Aug 26, 2018
 *      Author: willmitchell
 */

#include "oscillators.hpp"

void SingleSampleWavetable::parseControls(ViaControls * controls) {

	morphBase = controls->knob3Value << 4;

}

inline int32_t SingleSampleWavetable::incrementPhase(uint32_t * phaseDistTable) {

	int32_t localPhase = phase;

	// apply FM, which should be 1 at ground (offset is comensated for here)

	int32_t fmAmount = (int32_t) -fm[0];

	fmAmount += 65535 - cv2Offset;

	//int32_t increment = fix16_mul(parameters->increment, fmAmount);

	int32_t localIncrement = increment;

	// apply phase modulation

	int32_t pmAmount = (int32_t) -pm[0];

	pmAmount += 32767;

	localPhase += localIncrement + ((pmAmount - previousPhaseMod) << 9);

	previousPhaseMod = pmAmount;

	//phase += parameters->increment;

	// a zero will resync

	localPhase *= phaseReset;
	phaseReset = 1;

	int32_t phaseEventCalculator = 0;

	// add wavetable length if phase < 0

	phaseEventCalculator += ((uint32_t)(localPhase) >> 31) * WAVETABLE_LENGTH;

	// subtract wavetable length if phase > wavetable length

	phaseEventCalculator -= ((uint32_t)(WAVETABLE_LENGTH - localPhase) >> 31) * WAVETABLE_LENGTH;

	// apply the wrapping
	// no effect if the phase is in bounds

	localPhase += phaseEventCalculator;

	// log a -1 if the max value index of the wavetable is traversed from the left
	// log a 1 if traversed from the right
	// do this by subtracting the sign bit of the last phase from the current phase, both less the max phase index
	// this adds cruft to the wrap indicators, but that is deterministic and can be parsed out

	phase = localPhase;

	int32_t localPWM = (int32_t) pwm[0];
	localPWM += 32768;
	uint32_t pwmIndex = (localPWM >> 11);
	uint32_t pwmFrac = (localPWM & 0x7FF) << 4;
	// assuming that each phase distortion lookup table is 65 samples long stored as int32_t
	uint32_t * pwmTable1 = phaseDistTable + pwmIndex * 65;
	uint32_t * pwmTable2 = pwmTable1 + 65;
	uint32_t leftSample = localPhase >> 19;

#define pwmPhaseFrac (phase & 0x7FFFF) >> 4
		// use this with the precalculated pwm to perform bilinear interpolation
		// this accomplishes the
	int32_t	localGhostPhase = fix15_bilerp(pwmTable1[leftSample], pwmTable2[leftSample],
				pwmTable1[leftSample + 1], pwmTable2[leftSample + 1], pwmFrac,
				pwmPhaseFrac);

	int32_t atBIndicator = ((uint32_t)(localGhostPhase - AT_B_PHASE) >> 31) - ((uint32_t)(previousPhase - AT_B_PHASE) >> 31);

	phaseEventCalculator += atBIndicator;

	phaseEvent = phaseEventCalculator;

	// store the current phase
	previousPhase = localGhostPhase;

	return localGhostPhase;

}


uint32_t SingleSampleWavetable::advance(uint32_t * wavetable, uint32_t * phaseDistTable) {

	uint32_t localGhostPhase = incrementPhase(phaseDistTable);

	int32_t morph = (int32_t) -morphMod[0];

	morph = __USAT(morph + morphBase, 16);

	morph *= tableSize;

	ghostPhase = localGhostPhase;

	return getSampleQuinticSpline(ghostPhase, morph, wavetable, &delta);

}
