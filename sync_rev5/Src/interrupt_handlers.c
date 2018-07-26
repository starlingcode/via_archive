#include "main_state_machine.h"
#include "dsp.h"
#include "main.h"
#include "user_interface.h"
#include "via_rev5_hardware_io.h"
#include "modes.h"

void generateFrequency(controlRateInputs * controls, audioRateInputs * inputs, softwareSignaling * softwareSignals);
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim16;
extern TIM_HandleTypeDef htim17;

void mainRisingEdgeCallback(controlRateInputs * controls, audioRateInputs * inputs, softwareSignaling * softwareSignals) {

	// store the length of the last period
	softwareSignals->periodCount = __HAL_TIM_GET_COUNTER(&htim2);

	// reset the timer value
	__HAL_TIM_SET_COUNTER(&htim2, 0);

	// generate increments from the timing reading
	generateFrequency(controls, inputs, softwareSignals);

}

void mainFallingEdgeCallback(softwareSignaling * softwareSignals) {

	EXPAND_LOGIC_LOW;

}

void auxRisingEdgeCallback(controlRateInputs * controls, audioRateInputs * inputs, softwareSignaling * softwareSignals) {
	;
}
void auxFallingEdgeCallback(softwareSignaling * softwareSignals) {
	;
}

void buttonPressedCallback(controlRateInputs * controls, audioRateInputs * inputs, softwareSignaling * softwareSignals) {
	;
}
void buttonReleasedCallback(softwareSignaling * softwareSignals) {
	;
}

void ioProcessCallback(audioRateInputs * inputWrite, audioRateOutputs * outputRead) {


	WRITE_DAC1(__USAT((4095 - outputRead->samples), 12));
	WRITE_DAC2(__USAT(outputRead->samples, 12));
	WRITE_DAC3(__USAT(outputRead->dac3Sample, 12));


	// replace with one function using runtime display as a mask
//	if (RUNTIME_DISPLAY) {
//		setLogicOutputs(outputRead->logicAHandler, outputRead->logicBHandler, outputRead->auxLogicHandler, outputRead->shAHandler, outputRead->shBHandler);
//	} else {
		setLogicOutputsNoLEDs(outputRead->logicAHandler, outputRead->auxLogicHandler, outputRead->shAHandler, outputRead->shBHandler);
//	}

	// store the x and morph CVs at sample rate
	inputWrite->cv2Input = __USAT(cv2, 12);
	inputWrite->cv3Input = __USAT(cv3, 12);


}
void nextSampleCallback(void) {

	main_State = &main_nextSample;
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

	noteIndex = (controls->knob1Value) >> 5;
//	rootIndex = (controls->knob2Value) >> scale->t2Bitshift;
	rootIndex = (controls->knob2Value) >> 9;

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
		pllNudge = (((phase >> 24)*WAVETABLE_LENGTH - phase) << 8);
		pllCounter = 0;
	}

	uint32_t attackInc = ((((uint64_t)((uint64_t)AT_B_PHASE << 18) + pllNudge)) / (softwareSignals->periodCount));
//	uint32_t releaseInc = ((((uint64_t)AT_B_PHASE << 9) + pllNudge) / (softwareSignals->periodCount - softwareSignals->gateOnCount));
	attackInc = fix48_mul(attackInc, fracMultiplier) + fix16_mul(attackInc, intMultiplier);
//	releaseInc = fix48_mul(releaseInc, fracMultiplier) + fix16_mul(releaseInc, intMultiplier);

	softwareSignals->attackIncrement = __USAT(attackInc >> 8, 24);
	softwareSignals->releaseIncrement = __USAT(attackInc >> 8, 24);
}

