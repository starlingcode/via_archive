/*
 * oversampled_wavetable.c
 *
 *  Created on: Aug 19, 2018
 *      Author: willmitchell
 */

#include "oscillators.h"
#include "dsp.h"

uint32_t phase;

void oversampledWavetableParseControls(controlRateInputs * controls,
		oversampledWavetableParameters * parameters) {

	parameters->frequencyBase1 = fix16_mul(expoTable[controls->cv1Value] >> 6,
			expoTable[controls->knob1Value >> 2]);
	parameters->frequencyBase1 = fix16_mul(parameters->frequencyBase1,
			expoTable[controls->knob2Value >> 4]);
	parameters->morphBase = controls->knob3Value;
	parameters->fmAmount = controls->linTouchValue << 4;
	parameters->pmAmount = (4095 - (controls->linTouchValue << 4));

}

uint32_t oversampledWavetableAdvance0(
		oversampledWavetableParameters * parameters, audioRateOutputs * outputs,
		uint32_t * wavetable, uint32_t writePosition,
		uint32_t bufferSize) {

	int pm = -parameters->pm[0];
	pm = pm >> 6;
	pm = fix16_mul(pm, parameters->pmAmount);
	pm += 512;
	phase = pm << 26;
	// calculate buffer rate parameters
	int fm = -parameters->fm[0];
	fm = fix16_mul(fm, parameters->fmAmount);
	fm = fm >> 6;
	fm += 512;
	int increment = (parameters->frequencyBase1 * fm);

	// combine knob and CV then to table size in 16.16 fixed point
	int morph = -parameters->morphMod[0];
	morph = __USAT(((parameters->morphBase << 4)
							+ morph), 16)
					* parameters->tableSize;
	uint32_t morphIndex = morph >> 16;
	uint32_t morphFrac = morph & 0xFFFF;
	// assuming that each phase distortion lookup table is 517 samples long stored as int
	uint32_t * wavetable1 = wavetable + (morphIndex * 517) + 2;

	uint32_t * dac1Buffer = outputs->dac1Samples;
	uint32_t * dac2Buffer = outputs->dac2Samples;
	uint32_t * dac3Buffer = outputs->dac3Samples;

	uint32_t leftSample;

	uint32_t writeIndex = writePosition;
	uint32_t samplesRemaining = bufferSize;

	while (samplesRemaining) {
		// phase pointer wraps at 32 bits
		phase = (phase + increment);
		//dac3Buffer[writeIndex] = dummyCV;
		// get the actual wavetable output sample as above
		// but with the appropriate scaling as phase is now 25 bits and table length is 9 bits
		leftSample = phase >> 23;
#define phaseFrac ((phase >> 7) & 0xFFFF)
		dac3Buffer[writeIndex] = ((fast_15_16_bilerp_prediff(
				wavetable1[leftSample], wavetable1[leftSample + 1], morphFrac,
				phaseFrac)) >> 1);
		writeIndex++;
		samplesRemaining--;
	}

	return phase;

}

uint32_t oversampledWavetableAdvance1(
		oversampledWavetableParameters * parameters, audioRateOutputs * outputs,
		uint32_t * wavetable, uint32_t writePosition,
		uint32_t bufferSize) {

	// calculate buffer rate parameters
	int fm = -parameters->fm[0];
	fm = fix16_mul(fm, parameters->fmAmount);
	fm = fm >> 6;
	fm += 512;
	int increment = (parameters->frequencyBase1 * fm);

	// combine knob and CV then to table size in 16.16 fixed point
	int morph = -parameters->morphMod[0];
	morph = __USAT(((parameters->morphBase << 4)
							+ morph), 16)
					* parameters->tableSize;
	uint32_t morphIndex = morph >> 16;
	uint32_t morphFrac = morph & 0xFFFF;
	// assuming that each phase distortion lookup table is 517 samples long stored as int
	uint32_t * wavetable1 = wavetable + (morphIndex * 517) + 2;

//	uint32_t * dac1Buffer = outputs->dac1Samples;
//	uint32_t * dac2Buffer = outputs->dac2Samples;
	uint32_t * dac3Buffer = outputs->dac3Samples;

	uint32_t leftSample;

	uint32_t writeIndex = writePosition;
	uint32_t samplesRemaining = bufferSize;

	while (samplesRemaining) {
		// phase pointer wraps at 32 bits
		phase = (phase + increment);
		// get the actual wavetable output sample as above
		// but with the appropriate scaling as phase is now 25 bits and table length is 9 bits
		leftSample = phase >> 23;
#define phaseFrac ((phase >> 7) & 0xFFFF)
		dac3Buffer[writeIndex] = ((fast_15_16_bilerp_prediff(
				wavetable1[leftSample], wavetable1[leftSample + 1], morphFrac,
				phaseFrac)) >> 1);
		writeIndex++;
		samplesRemaining--;
	}

	return phase;

}


void oversampledWavetableParsePhase(uint32_t phase,
		oversampledWavetableParameters * parameters, audioRateOutputs *output) {

	static uint32_t lastPhaseHemisphere;
	static int lastSample;

	// 1 if phase is greater than half, else 0
	uint32_t phaseHemisphere = phase >> 24;

	// -1 if transition from upper hemisphere to lower
	// 1 if transition from lower hemisphere to upper
	// 0 otherwise
	int transition = phaseHemisphere - lastPhaseHemisphere;

	// 1 if we are moving backwards through the wavetable (negative multiplier), 0 otherwise
	uint32_t reverse = (uint32_t) ((int) parameters->fm[0]
			* parameters->reverseInput) >> 31;

	uint32_t atA;
	uint32_t atB;
	if (parameters->shOn == 0) {
			atA = 0;
			atB = 0;
	} else if (transition > 0) {
		atA = !reverse;
		atB = reverse;
	} else if (transition < 0) {
		atA = reverse;
		atB = !reverse;
	} else {
		atA = 1;
		atB = 1;
	}

	// generate square wave at A
	output->logicA[0] = ALOGIC_LOW_MASK << (phaseHemisphere * 16);

	int delta = ((uint32_t) (output->dac2Samples[0] - lastSample)) >> 31;
	output->auxLogic[0] = GET_EXPAND_LOGIC_MASK(delta);

	output->shA[0] = SH_A_TRACK_MASK << (atB * 16);
	output->shB[0] = SH_B_TRACK_MASK << (atA * 16);

	lastSample = output->dac2Samples[0];
	lastPhaseHemisphere = phaseHemisphere;

}
