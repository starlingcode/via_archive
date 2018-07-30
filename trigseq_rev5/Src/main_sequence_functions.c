#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"
#include "patterns.h"
#include "interrupt_handlers.h"
#include "via_rev5_hardware_io.h"
#include "dsp.h"
#include "modes.h"

// RGB led timer
TIM_HandleTypeDef htim1;

void processClock(controlRateInputs * controls, audioRateInputs * inputs, softwareSignaling * softwareSignals) {

	//TODO aux logic
	//TODO move heavy lifting out of interrupt and only update hardware?

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
	//TODO add cv (this is ugly, there should be a slick inline for this process)
	//TODO scale pattern lookup to number of patterns

	if ((4095 - controls->cv1Value) >= 2048) {
		aPatternMorph = (fix16_lerp(controls->knob1Value, 4095, ((4095 - controls->cv1Value) - 2048) << 5)) >> 9;
			}
	else {
		aPatternMorph = (fix16_lerp(0, controls->knob1Value, (4095 - controls->cv1Value) << 5)) >> 9;
	}
	if ((4095 - inputs->cv2Input) >= 2048) {
		bPatternMorph = (fix16_lerp(controls->knob2Value, 4095, ((4095 - inputs->cv2Input) - 2048) << 5)) >> 9;
			}
	else {
		bPatternMorph = (fix16_lerp(0, controls->knob2Value, (4095 - inputs->cv2Input) << 5)) >> 9;
	}
	if ((4095 - inputs->cv3Input) >= 2048) {
		offset = (fix16_lerp(controls->knob3Value, 4095, ((4095 - inputs->cv3Input) - 2048) << 5)) >> 8;
			}
	else {
		offset = (fix16_lerp(0, controls->knob3Value, (4095 - inputs->cv3Input) << 5)) >> 8;
	}

	//get the lengths of the currently indexed patterns
	pattern_bank * currentABank = softwareSignals->currentABank;
	pattern_bank * currentBBank = softwareSignals->currentBBank;

	aLength = currentABank->aLengths[aPatternMorph];
	bLength = currentBBank->bLengths[bPatternMorph];

	//TODO relate offset to scale lengths
	aPatternIndex = (softwareSignals->aCounter + offset) % aLength;
	bPatternIndex = (softwareSignals->bCounter) % bLength;

	//lookup the logic values
	aPatternValue = currentABank->aPatternBank[aPatternMorph][aPatternIndex];
	bPatternValue = currentABank->bPatternBank[bPatternMorph][bPatternIndex];

	//increment the sequence counter
	softwareSignals->aCounter = (softwareSignals->aCounter + 1) % aLength;
	softwareSignals->bCounter = (softwareSignals->bCounter + 1) % bLength;

	//call the appropriate handler functions
	if (aPatternValue) {
		handleAHigh(softwareSignals);
	} else {
		handleALow(softwareSignals);
	}

	if (bPatternValue) {
		handleBHigh(softwareSignals);
	} else {
		handleBLow(softwareSignals);
	}

	//jump to the conditional check appropriate for the currently selected logic operation
	//handle the result on the expander board
	switch (softwareSignals->auxLogicMode) {
		case or:
			if (aPatternValue || bPatternValue) {
				handleAuxHigh(softwareSignals);
			} else {
				handleAuxLow(softwareSignals);
			}
			break;
		case and:
			if (aPatternValue && bPatternValue) {
				handleAuxHigh(softwareSignals);
			} else {
				handleAuxLow(softwareSignals);
			}
			break;
		case xor:
			if (aPatternValue ^ bPatternValue) {
				handleAuxHigh(softwareSignals);
			} else {
				handleAuxLow(softwareSignals);
			}
			break;
		case nand:

			if ((!aPatternValue) && (!bPatternValue)) {
				handleAuxHigh(softwareSignals);
			} else {
				handleAuxLow(softwareSignals);
			}
			break;
	}

}

void handleFallingEdge(softwareSignaling * softwareSignals) {
	handleALow(softwareSignals);
	handleBLow(softwareSignals);
	handleAuxLow(softwareSignals);
}
