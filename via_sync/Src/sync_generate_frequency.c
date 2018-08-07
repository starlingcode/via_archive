/*
 * sync_generate_frequency.c
 *
 *  Created on: Aug 6, 2018
 *      Author: willmitchell
 */

#include "sync_next_sample.h"
#include "via_rev5_hardware_io.h"
#include "sync_modes.h"

void generateFrequency(controlRateInputs * controls, audioRateInputs * inputs, softwareSignaling * softwareSignals) {

	int pllNudge = 0;
	static uint32_t pllCounter;
	uint32_t fracMultiplier;
	uint32_t intMultiplier;
	uint32_t gcd;
	uint32_t noteIndex;
	uint32_t rootIndex;
	uint32_t multKey;
	static uint32_t lastMultiplier;

	Scale * scale = softwareSignals->scale;

	noteIndex = __USAT(controls->knob1Value + 2048 - controls->cv1Value, 12) >> 5;
	if (advancePhase == &advancePhaseRoot) {
		rootIndex = (__USAT(controls->knob2Value + 2048 - inputs->cv2Input, 12)) >> scale->t2Bitshift;
	} else {
		rootIndex = controls->knob2Value >> scale->t2Bitshift;
	}

	fracMultiplier = scale->grid[rootIndex][noteIndex]->fractionalPart;
	intMultiplier = scale->grid[rootIndex][noteIndex]->integerPart;
	gcd = scale->grid[rootIndex][noteIndex]->fundamentalDivision;
	multKey = fracMultiplier + intMultiplier;

	if (lastMultiplier != multKey) {
		EXPAND_LOGIC_HIGH;
	}

	lastMultiplier = multKey;

	pllCounter ++;

	pllCounter += softwareSignals->pllReset;
	softwareSignals->pllReset = 0;

	int phase = softwareSignals->phaseSignal;

	if (pllCounter >= gcd) {
		switch (softwareSignals->syncMode) {
		case nosync:
			pllNudge = 0;
			pllCounter = 0;
			break;
		case true:
			pllNudge = (((phase >> 24)*WAVETABLE_LENGTH - phase) << 8);
			pllCounter = 0;
			break;
		case hardsync:
			softwareSignals->phaseSignal = 0;
			pllCounter = 0;
			break;
		default:
			break;
		}
	}



	uint32_t attackInc = ((((uint64_t)((uint64_t)WAVETABLE_LENGTH << 17) + pllNudge)) / (softwareSignals->periodCount));
	attackInc = fix48_mul(attackInc >> 8, fracMultiplier) + fix16_mul(attackInc >> 8, intMultiplier);

	softwareSignals->attackIncrement = __USAT(3 * (attackInc >> 1), 24);
}


