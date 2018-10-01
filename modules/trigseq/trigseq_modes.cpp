/*
 * osc_modes.c
 *
 *  Created on: Aug 21, 2018
 *      Author: willmitchell
 */

#include <trigseq.hpp>

void ViaTrigseq::handleButton1ModeChange(int32_t mode) {

	switch (mode) {
	case 0:
		sequencer.sampleA = 0;
		sequencer.trackA = 0;
		break;
	case 1:
		sequencer.sampleA = 1;
		sequencer.trackA = 0;
		break;
	case 2:
		sequencer.sampleA = 0;
		sequencer.trackA = 1;
		break;
	}

}

void ViaTrigseq::handleButton2ModeChange(int32_t mode) {

	sequencer.andA = mode;

	if (mode) {
		sequencer.gateAEvent = SOFT_GATE_LOW;
	} else {
		sequencer.gateAEvent = SOFT_GATE_HIGH;
	}

}

void ViaTrigseq::handleButton3ModeChange(int32_t mode) {

	sequencer.currentABank = patternBank[mode];

}

void ViaTrigseq::handleButton4ModeChange(int32_t mode) {

	switch (mode) {
	case 0:
		sequencer.sampleB = 0;
		sequencer.trackB = 0;
		break;
	case 1:
		sequencer.sampleB = 1;
		sequencer.trackB = 0;
		break;
	case 2:
		sequencer.sampleB = 0;
		sequencer.trackB = 1;
		break;
	}

}

void ViaTrigseq::handleButton5ModeChange(int32_t mode) {

	sequencer.andB = mode;
	if (mode) {
		sequencer.gateBEvent = SOFT_GATE_LOW;
	} else {
		sequencer.gateBEvent = SOFT_GATE_HIGH;
	}

}

void ViaTrigseq::handleButton6ModeChange(int32_t mode) {

	sequencer.currentBBank = patternBank[mode];

}

void ViaTrigseq::handleAux2ModeChange(int32_t mode) {

	sequencer.auxLogicMode = mode;

}
