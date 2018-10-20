/*
 * osc_modes.c
 *
 *  Created on: Aug 21, 2018
 *      Author: willmitchell
 */

#include <gateseq.hpp>

void ViaGateseq::handleButton1ModeChange(int32_t mode) {

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

void ViaGateseq::handleButton2ModeChange(int32_t mode) {

	sequencer.andA = mode;

	if (mode) {
		sequencer.gateAEvent = SOFT_GATE_LOW;
	} else {
		sequencer.gateAEvent = SOFT_GATE_HIGH;
	}

}

void ViaGateseq::handleButton3ModeChange(int32_t mode) {

	sequencer.currentABank = seq1PatternBank[mode];

	switch (mode) {
	case 0:
		sequencer.modulateMultiplier = 0;
		sequencer.multiplier = 2;
		break;
	case 1:
		sequencer.modulateMultiplier = 0;
		sequencer.multiplier = 3;
		break;
	case 2:
		sequencer.modulateMultiplier = 0;
		sequencer.multiplier = 4;
		break;
	case 3:
		sequencer.modulateMultiplier = 1;
		sequencer.offset = 0;
		break;
	}

	sequencer.aCounter = 0;
	sequencer.bCounter = 0;


}

void ViaGateseq::handleButton4ModeChange(int32_t mode) {

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

void ViaGateseq::handleButton5ModeChange(int32_t mode) {

	sequencer.andB = mode;
	if (mode) {
		sequencer.gateBEvent = SOFT_GATE_LOW;
	} else {
		sequencer.gateBEvent = SOFT_GATE_HIGH;
	}

}

void ViaGateseq::handleButton6ModeChange(int32_t mode) {

	sequencer.currentBBank = seq2PatternBank[mode];

	sequencer.aCounter = 0;
	sequencer.bCounter = 0;

}

void ViaGateseq::handleAux2ModeChange(int32_t mode) {

	sequencer.auxLogicMode = mode;

}
