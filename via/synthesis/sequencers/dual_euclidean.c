/*
 * dual_euclidean.c
 *
 *  Created on: Aug 21, 2018
 *      Author: willmitchell
 */

#include "sequencers.h"
#include "dsp.h"

#define RUNTIME_DISPLAY 1

void dualEuclideanProcessClock(controlRateInputs * controls,
		audioRateInputs * inputs, dualEuclideanParameters * parameters) {

	uint32_t aLength;
	uint32_t bLength;
	uint32_t aPatternMorph;
	uint32_t bPatternMorph;
	uint32_t aPatternIndex;
	uint32_t bPatternIndex;
	uint32_t aPatternValue;
	uint32_t bPatternValue;
	uint32_t offset;

	//determine a pattern index for the a and b grids and the offset
	//the positve going excursion of the cv scales all the way to the maximum value
	//the negative does the same to the maximum value

	if ((4095 - controls->cv1Value) >= 2048) {
		aPatternMorph = (fix16_lerp(controls->knob1Value, 4095,
				((4095 - controls->cv1Value) - 2048) << 5)) >> 9;
	} else {
		aPatternMorph = (fix16_lerp(0, controls->knob1Value,
				(4095 - controls->cv1Value) << 5)) >> 9;
	}
	if ((4095 - inputs->cv2Samples[0]) >= 2048) {
		offset = (fix16_lerp(controls->knob2Value, 4095,
				((4095 - inputs->cv2Samples[0]) - 2048) << 5)) >> 8;
	} else {
		offset = (fix16_lerp(0, controls->knob2Value,
				(4095 - inputs->cv2Samples[0]) << 5)) >> 8;
	}
	if ((4095 - inputs->cv3Samples[0]) >= 2048) {
		bPatternMorph = (fix16_lerp(controls->knob3Value, 4095,
				((4095 - inputs->cv3Samples[0]) - 2048) << 5)) >> 9;
	} else {
		bPatternMorph = (fix16_lerp(0, controls->knob3Value,
				(4095 - inputs->cv3Samples[0]) << 5)) >> 9;
	}

	//get the lengths of the currently indexed patterns
	dualBooleanSequence * currentABank = parameters->currentABank;
	dualBooleanSequence * currentBBank = parameters->currentBBank;

	aLength = currentABank->aLengths[aPatternMorph];
	bLength = currentBBank->bLengths[bPatternMorph];

	//TODO relate offset to scale lengths
	aPatternIndex = (parameters->aCounter + offset) % aLength;
	bPatternIndex = (parameters->bCounter) % bLength;

	//lookup the logic values
	aPatternValue = currentABank->aPatternBank[aPatternMorph][aPatternIndex];
	bPatternValue = currentABank->bPatternBank[bPatternMorph][bPatternIndex];

	//increment the sequence counter
	parameters->aCounter = (parameters->aCounter + 1) % aLength;
	parameters->bCounter = (parameters->bCounter + 1) % bLength;

	// jump to the conditional check appropriate for the currently selected logic operation

#define __OR 0
#define __AND 1
#define __XOR 2
#define __NAND 3

	switch (parameters->auxLogicMode) {
	case __OR:
		if (aPatternValue || bPatternValue) {
			parameters->logicOutput = 1;
		} else {
			parameters->logicOutput = 0;
		}
		break;
	case __AND:
		if (aPatternValue && bPatternValue) {
			parameters->logicOutput = 1;
		} else {
			parameters->logicOutput = 0;
		}
		break;
	case __XOR:
		if (aPatternValue ^ bPatternValue) {
			parameters->logicOutput = 1;
		} else {
			parameters->logicOutput = 0;
		}
		break;
	case __NAND:

//		if ((!aPatternValue) && (!bPatternValue)) {
//			parameters->logicOutput = 1;
//		} else {
//			parameters->logicOutput = 0;
//		}

		// set/reset

		if (parameters->logicOutput) {
			parameters->logicOutput = aPatternValue;
		} else {
			parameters->logicOutput = bPatternValue;
		}



		break;
	}

	parameters->aOutput = aPatternValue;
	parameters->bOutput = bPatternValue;

}

