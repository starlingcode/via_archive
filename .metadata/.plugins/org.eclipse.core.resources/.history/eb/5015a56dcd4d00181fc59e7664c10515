#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"
#include "patterns.h"
#include "sequence_functions.h"
#include "hardware_io.h"

void processSequence(void) {

	uint32_t aLength;
	uint32_t bLength;
	uint32_t aPatternMorph;
	uint32_t bPatternMorph;
	uint32_t aPatternIndex;
	uint32_t bPatternIndex;
	uint32_t aPatternValue;
	uint32_t bPatternValue;

	//determine a pattern index for the a and b grids
	//TODO add cv
	//TODO scale pattern lookup to number of patterns
	aPatternMorph = knob1 >> 9;
	bPatternMorph = knob2 >> 9;

	//get the lengths of the currently indexed patterns
	aLength = euclidean_simple.aLengths[aPatternMorph];
	bLength = euclidean_simple.bLengths[bPatternMorph];

	//inverse offset, phase aligned at knob all the way to the left
	//TODO relate offset to scale lengths
	//TODO add cv
	aPatternIndex = (aCounter + (knob3 >> 8)) % aLength;
	bPatternIndex = (bCounter + ((4200 - knob3) >> 8)) % bLength;

	//lookup the logic values
	aPatternValue = euclidean_simple.aPatternBank[aPatternMorph][aPatternIndex];
	bPatternValue = euclidean_simple.bPatternBank[bPatternMorph][bPatternIndex];

	//increment the sequence counter
	aCounter = (aCounter + 1) % aLength;
	bCounter = (bCounter + 1) % bLength;

	//call the appropriate handler functions
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
}

void handleFallingEdge(void) {
	handleALow();
	handleBLow();
}
