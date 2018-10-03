/*
 * oscillator_resources.c
 *
 *  Created on: Aug 26, 2018
 *      Author: willmitchell
 */

#include <oscillators.hpp>


/*
 *
 * Pll with scale grid multiplier
 *
 */


void PllController::parseControls(ViaControls * controls, ViaInputStreams * input) {

	int32_t tempNote = controls->knob1Value + controls->cv1Value - 2048;
	int32_t noteIndex = __USAT(tempNote, 12) >> 5;
	int32_t rootModLocal = rootMod[0];
	rootModLocal = rootModLocal >> 4;
	rootModLocal += controls->knob2Value;
	int32_t	rootIndex = (__USAT(rootModLocal, 12)) >> scale->t2Bitshift;

	fracMultiplier = scale->grid[rootIndex][noteIndex]->fractionalPart;
	intMultiplier = scale->grid[rootIndex][noteIndex]->integerPart;
	gcd = scale->grid[rootIndex][noteIndex]->fundamentalDivision;

}
void PllController::doPLL(void) {

	pllCounter++;

	pllCounter *= pllReset;
	pllReset = 1;
	phaseReset = 1;

	int32_t localPhaseOffset = fix48_mul(phaseOffset, fracMultiplier) + fix16_mul(phaseOffset, intMultiplier);

	int32_t phase = (phaseSignal + localPhaseOffset) & ((1 << 25) - 1);

	// this switch is always 0 unless pllCounter is 0, in which case its sync mode

#define IGNORE 0
#define PLL_OFF 1
#define TRUE_PLL 2
#define HARD_RESET 3

	if (pllCounter >= gcd) {

		switch (syncMode) {
			case IGNORE:
				break;
			case PLL_OFF:
				pllNudge = 0;
				pllCounter = 0;
				break;
			case TRUE_PLL:
				pllNudge = 0;
				pllNudge += (WAVETABLE_LENGTH - phase) * (phase >> 24);
				//pllNudge -= phase * !(phase >> 24);
				pllNudge = ((int64_t)pllNudge << 16) / intMultiplier;
				pllCounter = gcd;
				break;
			case HARD_RESET:
				pllNudge = 0;
				//phaseReset = 0;
				pllCounter = 0;
				phaseSignal = localPhaseOffset;
				break;
			default:
				pllCounter = 0;
				break;

		}
	}

	int32_t multKey = fracMultiplier + intMultiplier;

	if (lastMultiplier != multKey) {
		ratioChange = 1;
	} else {
		ratioChange = 0;
	}

	lastMultiplier = multKey;

}

void PllController::generateFrequency(void) {

#ifdef BUILD_F373

	int32_t incrementCalc = ((((uint64_t)((uint64_t)(WAVETABLE_LENGTH  + pllNudge) * 720))) / (periodCount));
	incrementCalc = fix48_mul(incrementCalc, fracMultiplier) + fix16_mul(incrementCalc, intMultiplier);
	increment = __USAT(incrementCalc, 24);

#endif

#ifdef BUILD_VIRTUAL

	int32_t incrementCalc = (WAVETABLE_LENGTH + pllNudge) / periodCount;
	incrementCalc = fix48_mul(incrementCalc, fracMultiplier) + fix16_mul(incrementCalc, intMultiplier);
	increment = __USAT(incrementCalc, 24);

#endif

}
