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

	int32_t ratioX = controls->knob1Value + controls->cv1Value - 2048;
	ratioX = __USAT(ratioX, 12);

	ratioX = ratioXHysterisis(ratioX >> 5, ratioX);

	int32_t rootModLocal = -rootMod[0];
	rootModLocal = rootModLocal >> 4;
	rootModLocal += controls->knob2Value;
	int32_t	ratioY = __USAT(rootModLocal, 12);

	ratioY = ratioYHysterisis(ratioY, scale->t2Bitshift);

	if (ratioY != lastYIndex) {
		yIndexChange = 1;
	}

	lastYIndex = ratioY;

	fracMultiplier = scale->grid[ratioY][ratioX]->fractionalPart;
	intMultiplier = scale->grid[ratioY][ratioX]->integerPart;
	gcd = scale->grid[ratioY][ratioX]->fundamentalDivision;

}
void PllController::doPLL(void) {

	pllCounter++;
	pllCounter = (pllCounter >= gcd) ? 0 : pllCounter;


	pllCounter *= pllReset;
	pllReset = 1;
	phaseReset = 1;

	int32_t localPhaseOffset = fix48_mul(phaseOffset, fracMultiplier) + fix16_mul(phaseOffset, intMultiplier);

	int32_t phase = (phaseSignal - phaseModSignal + localPhaseOffset) & ((1 << 25) - 1);

	// this can be more efficient, multiply by wavetable length is a bitshift ..

	int32_t span = fix48_mul(WAVETABLE_LENGTH, fracMultiplier) + fix16_mul(WAVETABLE_LENGTH, intMultiplier);

	int32_t target = pllCounter * span;

	target &= (WAVETABLE_LENGTH - 1);

	int32_t error = (phase - target) & (WAVETABLE_LENGTH - 1);

	error -= (error >> 24) * WAVETABLE_LENGTH;
	if (abs(error) > 1000) {
		printf("error %d \n", error);
		printf("target %d \n", target >> 16);
	}

	error *= -1;

#define IGNORE 0
#define SLOW_PLL 1
#define FAST_PLL 2
#define WILD_PLL 3
#define HARD_SYNC 4

	int32_t pTerm;
	int32_t iTerm;
	int32_t dTerm;

	switch (syncMode) {
		case IGNORE:
			break;
		case SLOW_PLL:

			nudgeSum = error + nudgeSum - readBuffer(&nudgeBuffer, 31);
			writeBuffer(&nudgeBuffer, error);
			pTerm = error;
			iTerm = nudgeSum >> 5;
			dTerm = (error - readBuffer(&nudgeBuffer, 1)) >> 1;
			
			pllNudge = pTerm + iTerm + dTerm;
			


			break;
		case FAST_PLL:

			nudgeSum = error + nudgeSum - readBuffer(&nudgeBuffer, 7);
			writeBuffer(&nudgeBuffer, error);
			error += nudgeSum >> 3;
			pllNudge = error;

			break;
		case WILD_PLL:

			pllNudge = error;

			break;
		case HARD_SYNC:

			pllNudge = error;
			nudgeSum = 0;
			phaseSignal = localPhaseOffset + phaseModSignal + target;
			phaseSignal &= (WAVETABLE_LENGTH - 1);

			break;

		default:
			break;

	}
	
	int32_t multKey = fracMultiplier + intMultiplier;

	ratioChange = (lastMultiplier != multKey);

	lastMultiplier = multKey;

}

void PllController::generateFrequency(void) {

#ifdef BUILD_F373

	int32_t incrementCalc = ((uint64_t)(0x100000000 + (uint64_t) pllNudge) * 1440) / (periodCount * 8);
	incrementCalc = (fix48_mul(incrementCalc, fracMultiplier) + fix16_mul(incrementCalc, intMultiplier));
	increment = __USAT(incrementCalc, 31);

#endif

#ifdef BUILD_VIRTUAL

	int32_t incrementCalc = ((uint64_t)(0x100000000 + (uint64_t) pllNudge)) / (periodCount * 8);
	//int32_t incrementCalc = ((uint64_t)0x100000000) / (periodCount * 8);
	incrementCalc = fix48_mul(incrementCalc, fracMultiplier) + fix16_mul(incrementCalc, intMultiplier);
	increment = __USAT(incrementCalc, 24);

#endif

}
