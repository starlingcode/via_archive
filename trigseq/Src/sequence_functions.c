#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"
#include "patterns.h"
#include "sequence_functions.h"
#include "hardware_io.h"

// RGB led timer
TIM_HandleTypeDef htim1;

void processClock(void) {

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

	if ((4095 - cv1) >= 2048) {
		aPatternMorph = (fix16_lerp(knob1, 4095, ((4095 - cv1) - 2048) << 5)) >> 9;
			}
	else {
		aPatternMorph = (fix16_lerp(0, knob1, (4095 - cv1) << 5)) >> 9;
	}
	if ((4095 - cv2) >= 2048) {
		bPatternMorph = (fix16_lerp(knob2, 4095, ((4095 - cv2) - 2048) << 5)) >> 9;
			}
	else {
		bPatternMorph = (fix16_lerp(0, knob2, (4095 - cv2) << 5)) >> 9;
	}
	if ((4095 - cv3) >= 2048) {
		offset = (fix16_lerp(knob3, 4095, ((4095 - cv3) - 2048) << 5)) >> 8;
			}
	else {
		offset = (fix16_lerp(0, knob3, (4095 - cv3) << 5)) >> 8;
	}

	//get the lengths of the currently indexed patterns
	//this was cool when locked to one of the two by accident
	//button menu?
	aLength = currentBank->aLengths[aPatternMorph];
	bLength = currentBank->bLengths[bPatternMorph];

	//TODO relate offset to scale lengths
	aPatternIndex = (aCounter + offset) % aLength;
	//inverse offset, phase aligned at knob all the way to the left
	//bPatternIndex = (aCounter (4200 - offset)) % bLength;
	// b is locked (I like both, button menu?)
	bPatternIndex = (bCounter) % bLength;

	//lookup the logic values
	aPatternValue = currentBank->aPatternBank[aPatternMorph][aPatternIndex];
	bPatternValue = currentBank->bPatternBank[bPatternMorph][bPatternIndex];

	//increment the sequence counter
	aCounter = (aCounter + 1) % aLength;
	bCounter = (bCounter + 1) % bLength;

	//call the appropriate handler functions
	//maybe turn these into function pointers that are called in the nvic handler
	if (aPatternValue == 0) {
		handleALow();
	} else {
		handleAHigh();
	}

	if (bPatternValue == 0) {
		handleBLow();
	} else {
		handleBHigh();
	}

	//jump to the conditional check appropriate for the currently selected logic operation
	//handle the result on the expander board
	switch (auxLogicMode) {
		case or:
			if (aPatternValue || bPatternValue) {
				handleAuxHigh();
			} else {
				handleAuxLow();
			}
			break;
		case and:
			if (aPatternValue && bPatternValue) {
				handleAuxHigh();
			} else {
				handleAuxLow();
			}
			break;
		case xor:
			if (aPatternValue ^ bPatternValue) {
				handleAuxHigh();
			} else {
				handleAuxLow();
			}
			break;
		case nand:
			if ((!aPatternValue) && (!bPatternValue)) {
				handleAuxHigh();
			} else {
				handleAuxLow();
			}
			break;
	}

}

void handleFallingEdge(void) {
	handleALow();
	handleBLow();
	//0 and 0 = 0, 0 or 0 = 0, 0 xor 0 = 0, 0 nand 0 = 1.
	if (auxLogicMode == nand) {
		handleAuxHigh();
	} else {
		handleAuxLow();
	}

}
