/*
 * simple_wavetable.c
 *
 *  Created on: Aug 29, 2018
 *      Author: willmitchell
 */

#include "oscillators.h"

void simpleWavetableParseControls(controlRateInputs * controls, simpleWavetableParameters * parameters) {

	parameters->morphBase = controls->knob3Value << 4;

}

int simpleWavetableAdvance(simpleWavetableParameters * parameters, uint32_t * wavetable) {

	int morphScale = parameters->morphScale[0];
	morphScale = fix16_mul(parameters->morphBase, morphScale);
	int morphMod = -parameters->morphMod[0];
	morphMod = __USAT(morphScale + morphMod, 16) * parameters->tableSize;

	return getSampleQuinticSpline(parameters->phase, morphMod,
			wavetable, &(parameters->delta)) >> 3;

}

