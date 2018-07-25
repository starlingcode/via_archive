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
	// get the timer value that which was reset on last rising edge
//
//	softwareSignals->gateOnCount = __HAL_TIM_GET_COUNTER(&htim2);
	softwareSignals->gateOnCount = softwareSignals->periodCount >> 1;

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


	// replace with one function using runtime display as a mask
//	if (RUNTIME_DISPLAY) {
//		setLogicOutputs(outputRead->logicAHandler, outputRead->logicBHandler, outputRead->auxLogicHandler, outputRead->shAHandler, outputRead->shBHandler);
//	} else {
//		setLogicOutputsNoLEDs(outputRead->logicAHandler, outputRead->logicBHandler, outputRead->auxLogicHandler, outputRead->shAHandler, outputRead->shBHandler);
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

	if (scale->oneVoltOct == 0) {
		noteIndex = combine12BitKnobCVTernary(controls->knob1Value, (4095 - controls->cv1Value)) >> 5;
	} else {
		noteIndex = __USAT((4095 - controls->cv1Value) + (controls->knob1Value >> 2) -1390, 12) >> 5;
	}

	rootIndex = combine12BitKnobCVTernary(controls->knob2Value, (4095 - inputs->cv2Input)) >> scale->t2Bitshift;

	fracMultiplier = scale->grid[rootIndex][noteIndex]->fractionalPart;
	intMultiplier = scale->grid[rootIndex][noteIndex]->integerPart;
	gcd = scale->grid[rootIndex][noteIndex]->fundamentalDivision;
	multKey = fracMultiplier + intMultiplier;

	if (lastMultiplier != multKey) {
		// TODO ratio change trigger
	}

	lastMultiplier = multKey;

	//pllCounter ++;

//	if (pllCounter >= gcd || (EXTPLL)) {
//
//		if (button4Mode == hardSync) {
//
//			position = 0;
//			holdPosition =0;
//			if (GATEA) {
//				ALOGIC_HIGH;
//				if (RUNTIME_DISPLAY) {
//					LEDC_ON;
//				}
//			} else if (TRIGA) {
//				ALOGIC_HIGH;
//				if (RUNTIME_DISPLAY) {
//					LEDC_ON;
//				}
//				__HAL_TIM_SET_COUNTER(&htim15, 0);
//				__HAL_TIM_ENABLE(&htim15);
//			}
//
//		} else if (button4Mode == true) {
//			// if we are behind the phase of the clock, go faster, otherwise, go slower
//			if (position > span) {
//				pllNudge = (spanx2 - position) << 4;
//			} else {
//				pllNudge = -(position) << 4;
//			}
//		}
//		pllCounter = 0;
//		CLEAR_EXTPLL;
//	}

	uint32_t attackInc = (((AT_B_PHASE << 7)) / softwareSignals->gateOnCount);
	uint32_t releaseInc = (((AT_B_PHASE << 7) + pllNudge) / (softwareSignals->periodCount - softwareSignals->gateOnCount));
	attackInc = fix48_mul(attackInc, fracMultiplier) + fix16_mul(attackInc, intMultiplier);
	releaseInc = fix48_mul(releaseInc, fracMultiplier) + fix16_mul(releaseInc, intMultiplier);

	softwareSignals->attackIncrement = __USAT(attackInc, 24);
	softwareSignals->releaseIncrement = __USAT(releaseInc, 24);


}

