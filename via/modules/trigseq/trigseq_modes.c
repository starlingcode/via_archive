/*
 * osc_modes.c
 *
 *  Created on: Aug 21, 2018
 *      Author: willmitchell
 */

#include "trigseq.h"

void trigseq_handleButton1ModeChange(int mode) {

	switch (mode) {
	case 0:
		scanner_signals.parameters->sampleA = 0;
		scanner_signals.parameters->trackA = 0;
		break;
	case 1:
		scanner_signals.parameters->sampleA = 1;
		scanner_signals.parameters->trackA = 0;
		break;
	case 2:
		scanner_signals.parameters->sampleA = 0;
		scanner_signals.parameters->trackA = 1;
		break;
	}

}

void trigseq_handleButton2ModeChange(int mode) {

	scanner_signals.parameters->andA = mode;

}

void trigseq_handleButton3ModeChange(int mode) {

	scanner_signals.parameters->currentABank = trigseq_patternBank[mode];

}

void trigseq_handleButton4ModeChange(int mode) {

	switch (mode) {
	case 0:
		scanner_signals.parameters->sampleB = 0;
		scanner_signals.parameters->trackB = 0;
		break;
	case 1:
		scanner_signals.parameters->sampleB = 1;
		scanner_signals.parameters->trackB = 0;
		break;
	case 2:
		scanner_signals.parameters->sampleB = 0;
		scanner_signals.parameters->trackB = 1;
		break;
	}

}

void trigseq_handleButton5ModeChange(int mode) {

	scanner_signals.parameters->andB = mode;

}

void trigseq_handleButton6ModeChange(int mode) {

	scanner_signals.parameters->currentBBank = trigseq_patternBank[mode];

}

void trigseq_handleAux2ModeChange(int mode) {

	scanner_signals.parameters->auxLogicMode = mode;

}
