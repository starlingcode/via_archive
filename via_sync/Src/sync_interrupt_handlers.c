#include "sync_dsp.h"
#include "user_interface.h"
#include "via_rev5_hardware_io.h"
#include "sync_modes.h"
#include "sync_next_sample.h"

void generateFrequency(controlRateInputs * controls, audioRateInputs * inputs, softwareSignaling * softwareSignals);
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim16;
extern TIM_HandleTypeDef htim17;

void mainRisingEdgeCallback(viaSignals * signals) {

	// store the length of the last period
	signals->softwareSignals->periodCount = __HAL_TIM_GET_COUNTER(&htim2);

	// reset the timer value
	__HAL_TIM_SET_COUNTER(&htim2, 0);

	// generate increments from the timing reading
	generateFrequency(signals->controls, signals->inputs, signals->softwareSignals);

}

void mainFallingEdgeCallback(softwareSignaling * softwareSignals) {

	EXPAND_LOGIC_LOW;

}

void auxRisingEdgeCallback(viaSignals * signals) {
	;
}
void auxFallingEdgeCallback(viaSignals * signals) {
	;
}

void buttonPressedCallback(viaSignals * signals) {
	;
}
void buttonReleasedCallback(viaSignals * signals) {
	;
}

void ioProcessCallback(viaSignals * signals) {

	audioRateOutputs* outputRead = signals->outputs;
	int outputSample =  signals->outputs->samples;

	WRITE_DAC1(4095 - outputSample);
	WRITE_DAC2(outputSample);
	WRITE_DAC3(__USAT(outputRead->dac3Sample, 12));


	// replace with one function using runtime display as a mask
	if (RUNTIME_DISPLAY) {
		setLogicOutputs(outputRead->logicAHandler, outputRead->auxLogicHandler, outputRead->shAHandler, outputRead->shBHandler);
	} else {
		setLogicOutputsNoLEDs(outputRead->logicAHandler, outputRead->auxLogicHandler, outputRead->shAHandler, outputRead->shBHandler);
	}

	audioRateInputs* inputWrite = signals->inputs;
	// store the x and morph CVs at sample rate
	inputWrite->cv2Input = __USAT(cv2, 12);
	inputWrite->cv3Input = __USAT(cv3, 12);


}
void nextSampleCallback(viaSignals * signals) {

	nextSample(signals->controls, signals->inputs, signals->outputs, signals->softwareSignals);

}

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

	int phase = softwareSignals->phaseSignal;

	if (pllCounter >= gcd) {
		switch (softwareSignals->syncMode) {
		case nosync:
			pllNudge = 0;
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

	softwareSignals->attackIncrement = __USAT(attackInc, 24);
	softwareSignals->releaseIncrement = __USAT(attackInc, 24);
}

