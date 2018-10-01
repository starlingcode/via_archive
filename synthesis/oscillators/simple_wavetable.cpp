/*
 * simple_wavetable.c
 *
 *  Created on: Aug 29, 2018
 *      Author: willmitchell
 */

#include <oscillators.hpp>

void SimpleWavetable::parseControls(ViaControls * controls) {

	morphBase = controls->knob3Value << 4;

};

int32_t SimpleWavetable::advance(uint32_t * wavetable) {

	int32_t morphScaleLocal = (int32_t) morphScale[0];
	morphScaleLocal = fix16_mul(morphBase, morphScaleLocal);
	int32_t morphModLocal = (int32_t) -morphMod[0];
	morphModLocal = __USAT(morphScaleLocal + morphModLocal, 16) * tableSize;

	return getSampleQuinticSpline(phase, (uint32_t) morphModLocal,
			wavetable, &delta) >> 3;

};

