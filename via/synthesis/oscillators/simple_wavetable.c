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

	int morphMod = -parameters->morphMod[0];
	morphMod = __USAT(morphMod + parameters->morphBase, 16) * parameters->tableSize;

	return getSampleQuinticSpline(parameters->phase, morphMod,
			wavetable, &(parameters->delta)) >> 3;

}

