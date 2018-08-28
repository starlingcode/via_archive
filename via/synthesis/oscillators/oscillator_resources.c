/*
 * oscillator_resources.c
 *
 *  Created on: Aug 26, 2018
 *      Author: willmitchell
 */

#include "oscillators.h"

void pllMultiplierParseControls(controlRateInputs * controls, audioRateInputs * input,
		pllMultiplierParameters * parameters) {

	Scale * scale = parameters->scale;

	int noteIndex = __USAT(controls->knob1Value + controls->cv1Value - 2048, 12) >> 5;
	int rootMod = parameters->rootMod[0];
	rootMod = rootMod >> 4;
	int	rootIndex = (__USAT(controls->knob2Value + rootMod, 12)) >> scale->t2Bitshift;

	parameters->fracMultiplier = scale->grid[rootIndex][noteIndex]->fractionalPart;
	parameters->intMultiplier = scale->grid[rootIndex][noteIndex]->integerPart;
	parameters->gcd = scale->grid[rootIndex][noteIndex]->fundamentalDivision;

}
void pllMultiplierDoPLL(pllMultiplierParameters * parameters) {

	static int pllCounter;
	static int lastMultiplier;

	pllCounter++;

	pllCounter *= parameters->pllReset;
	parameters->pllReset = 1;
	parameters->phaseReset = 1;

	int phase = (parameters->phaseSignal + parameters->phaseOffset) & ((1 << 25) - 1);

	// this switch is always 0 unless pllCounter is 0, in which case its sync mode

#define IGNORE 0
#define PLL_OFF 1
#define TRUE_PLL 2
#define HARD_RESET 3

	if (pllCounter >= parameters->gcd) {

		switch (parameters->syncMode) {
			case IGNORE:
				break;
			case PLL_OFF:
				parameters->pllNudge = 0;
				pllCounter = 0;
				break;
			case TRUE_PLL:
				parameters->pllNudge = (((phase >> 24)*WAVETABLE_LENGTH - phase) << 16);
				pllCounter = parameters->gcd;
				break;
			case HARD_RESET:
				parameters->phaseReset = 0;
				pllCounter = 0;
				break;
			default:
				pllCounter = 0;
				break;

		}
	}

	int multKey = parameters->fracMultiplier + parameters->intMultiplier;

	if (lastMultiplier != multKey) {
		EXPAND_LOGIC_HIGH
	}

	lastMultiplier = multKey;

}
void pllMultiplierGenerateFrequency(pllMultiplierParameters * parameters) {

	uint32_t increment = ((((uint64_t)((uint64_t)WAVETABLE_LENGTH << 18) + parameters->pllNudge)) / (parameters->periodCount));
	increment = fix48_mul(increment >> 8, parameters->fracMultiplier) + fix16_mul(increment >> 8, parameters->intMultiplier);
	parameters->increment = __USAT(increment, 24);

}
