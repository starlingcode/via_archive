/*
 * dual_euclidean.c
 *
 *  Created on: Aug 21, 2018
 *      Author: willmitchell
 */

#include <sequencers.hpp>

#include "dsp.hpp"

#define RUNTIME_DISPLAY 1

void DualEuclidean::parseControls(ViaControls * controls,
		ViaInputStreams * inputs) {

	//determine a pattern index for the a and b grids and the offset
	//the positve going excursion of the cv scales all the way to the maximum value
	//the negative does the same to the maximum value

	int32_t cv2Sample = (int32_t) -inputs->cv2Samples[0];
	cv2Sample = cv2Sample >> 4;
	cv2Sample += 2048;
	int32_t cv3Sample = (int32_t) -inputs->cv3Samples[0];
	cv3Sample = cv3Sample >> 4;
	cv3Sample += 2048;

	if (controls->cv1Value >= 2048) {
		aPatternMorph = (fix16_lerp(controls->knob1Value, 4095,
				(controls->cv1Value - 2048) << 5)) >> 8;
	} else {
		aPatternMorph = (fix16_lerp(0, controls->knob1Value,
				controls->cv1Value << 5)) >> 8;
	}

	if (modulateMultiplier) {

		if (cv2Sample >= 2048) {
			multiplier = (fix16_lerp(controls->knob2Value, 4095,
					(cv2Sample - 2048) << 5)) >> 9;
		} else {
			multiplier = (fix16_lerp(0, controls->knob2Value,
					cv2Sample << 5)) >> 9;
		}
		//0-7 -> 1-8
		multiplier += 2;

	} else {

		if (cv2Sample >= 2048) {
			offset = (fix16_lerp(controls->knob2Value, 4095,
					(cv2Sample - 2048) << 5)) >> 9;
		} else {
			offset = (fix16_lerp(0, controls->knob2Value,
					cv2Sample << 5)) >> 9;
		}

	}

	if (cv3Sample >= 2048) {
		bPatternMorph = (fix16_lerp(controls->knob3Value, 4095,
				(cv3Sample - 2048) << 5)) >> 8;
	} else {
		bPatternMorph = (fix16_lerp(0, controls->knob3Value,
				cv3Sample << 5)) >> 8;
	}

	//get the lengths of the currently indexed patterns

	aLength = currentABank->lengths[aPatternMorph];
	bLength = currentBBank->lengths[bPatternMorph];

}

void DualEuclidean::processClock(void) {

	advanceSequencerB();

	if (skipClock) {
		skipClock = 0;
	} else {
#ifdef BUILD_VIRTUAL
	periodCount = virtualTimer1Count;
	virtualTimer1Count = 0;
	virtualTimer3Enable = 0;
	//virtualTimer2Prescaler = divider - 1; // no division implemented yet
	virtualTimer2Overflow = periodCount/multiplier;
	virtualTimer2Count = 0;
	// then "handle an interrupt" on the multiplier timer and update the aux logic output in the module interrupt handler
	skipClock = 1;
	}
#endif
#ifdef BUILD_F373
	periodCount = TIM5->CNT;
	TIM5->CNT = 0;
	TIM17->CR1 &= ~TIM_CR1_CEN;
	TIM2->PSC = divider-1;
	TIM2->EGR = TIM_EGR_UG;
	TIM2->ARR = periodCount/multiplier;
	TIM2->CNT = 0;
	skipClock = 1;
	}
	updateLogicOutput();
#endif


}

void DualEuclidean::advanceSequencerA(void) {

	uint32_t aPatternValue;

	//TODO relate offset to scale lengths
	aPatternIndex = (aCounter + offset) % aLength;

	//lookup the logic values
	aPatternValue = currentABank->patternBank[aPatternMorph][aPatternIndex];

	//increment the sequence counter
	aCounter = (aCounter + 1) % aLength;

	aOutput = aPatternValue;

}

void DualEuclidean::advanceSequencerB(void) {

	uint32_t bPatternValue;

	//TODO relate offset to scale lengths
	bPatternIndex = bCounter;

	//lookup the logic values
	bPatternValue = currentBBank->patternBank[bPatternMorph][bPatternIndex];

	//increment the sequence counter
	bCounter = (bCounter + 1) % bLength;

	bOutput = bPatternValue;

}

void DualEuclidean::updateLogicOutput(void) {

	// jump to the conditional check appropriate for the currently selected logic operation

#define __AND 0
#define __OR 1
#define __XOR 2
#define __NOR 3

	switch (auxLogicMode) {
	case __OR:
		if (aOutput || bOutput) {
			logicOutput = 1;
		} else {
			logicOutput = 0;
		}
		break;
	case __AND:
		if (aOutput && bOutput) {
			logicOutput = 1;
		} else {
			logicOutput = 0;
		}
		break;
	case __XOR:
		if (aOutput ^ bOutput) {
			logicOutput = 1;
		} else {
			logicOutput = 0;
		}
		break;
	case __NOR:
		// nand instead?
		if (!aOutput && !bOutput) {
			logicOutput = 1;
		} else {
			logicOutput = 0;
		}
		break;
	}

	logicOutput &= virtualGateHigh;

}
