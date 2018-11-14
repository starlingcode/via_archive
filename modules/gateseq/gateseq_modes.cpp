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

	setRedLED((mode >> 1) * 4095);
	setGreenLED(!(mode >> 1) * 4095);
	if (mode == 1 || mode == 3) {
		SET_BLUE_LED_ONOFF(1);
	} else {
		SET_BLUE_LED_ONOFF(0);
	}

	switch (mode) {
	case 0:
		TIM2->CR1 &= ~TIM_CR1_CEN;
		sequencer.clockOn = 0;
		sequencer.modulateMultiplier = 0;
		sequencer.multiplier = 1;
		sequencer.shuffleOn = 0;
		sequencer.shuffle = 0;
		break;
	case 1:
		TIM2->CR1 |= TIM_CR1_CEN;
		sequencer.clockOn = 1;
		sequencer.modulateMultiplier = 0;
		sequencer.multiplier = 3;
		sequencer.shuffleOn = 0;
		sequencer.shuffle = 0;
		break;
	case 2:
		TIM2->CR1 |= TIM_CR1_CEN;
		sequencer.clockOn = 1;
		sequencer.modulateMultiplier = 0;
		sequencer.multiplier = 4;
		sequencer.shuffleOn = 1;
		sequencer.shuffle = 0;
		break;
	case 3:
		TIM2->CR1 |= TIM_CR1_CEN;
		sequencer.clockOn = 1;
		sequencer.modulateMultiplier = 1;
		sequencer.offset = 0;
		sequencer.shuffleOn = 0;
		sequencer.shuffle = 0;
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
