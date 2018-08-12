#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"
#include "via_rev5_hardware_io.h"

#include "../inc/osc_ui_implementation.h"
#include "signals.h"

int handleConversionSlow(controlRateInputs * controls, audioRateInputs * inputs, uint32_t sequencingSignal);

void updateRGB(controlRateInputs *, audioRateInputs *);

extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim5;

/**
 *
 * S&H handling functions
 *
 */



/**
 *
 * ADC Averaging
 *
 */

void writeBuffer(buffer* buffer, int value) {
	buffer->buff[(buffer->writeIndex++) & 31] = value;
}

int readBuffer(buffer* buffer, int Xn) {
	return buffer->buff[(buffer->writeIndex + (~Xn)) & 31];
}

int handleConversionSlow(controlRateInputs * controls, audioRateInputs * inputs, uint32_t sequencingSignal) {

	// TODO apply SIMD instructions?

	static uint32_t knob1Sum;
	static uint32_t knob2Sum;
	static uint32_t knob3Sum;
	static uint32_t cv1Sum;
	static buffer knob1Buffer;
	static buffer knob2Buffer;
	static buffer knob3Buffer;
	static buffer cv1Buffer;

	switch (sequencingSignal) {
	case 1:
		// implement a running average on the control rate CV controls
		knob1Sum = knob1 + knob1Sum - readBuffer(&knob1Buffer, 31);
		knob2Sum = knob2 + knob2Sum - readBuffer(&knob2Buffer, 31);

		// store the newest value in a ring buffer
		writeBuffer(&knob1Buffer, knob1);
		writeBuffer(&knob2Buffer, knob2);

		// write the averaged controls to the holding struct
		controls->knob1Value = knob1Sum >> 5;
		controls->knob2Value = knob2Sum >> 5;

		break;

	case 2:
		// implement a running average on the control rate CV controls
		knob3Sum = knob3 + knob3Sum - readBuffer(&knob3Buffer, 31);
		cv1Sum = cv1 + cv1Sum - readBuffer(&cv1Buffer, 7);

		// store the newest value in a ring buffer
		writeBuffer(&knob3Buffer, knob3);
		writeBuffer(&cv1Buffer, cv1);

		// write the averaged controls to the holding struct
		controls->knob3Value = knob3Sum >> 5;
		controls->cv1Value = cv1Sum >> 3;

		break;

	case 3:
		// update the runtime display if the UI menu is not turned on
		if (RUNTIME_DISPLAY) {
			updateRGB(controls, inputs);
			(*displaySHMode)();
			(*displaySyncMode)();
			(*displayXCVMode)();
			(*displayMorphMode)();
		}

		sequencingSignal = 0;

		break;

	}

	sequencingSignal++;

	return sequencingSignal;

}


/**
 *
 * Helper functions for display handling
 *
 */

void displayXCV_FM(void) {
	LEDC_OFF;
}

void displayXCV_PM(void) {
	LEDC_ON;
}

void displayMorph_Morph(void) {
	LEDD_OFF;
}

void displayMorph_PMW(void) {
	LEDD_ON;
}

void displaySH_On(void) {
	LEDA_ON;
}

void displaySH_Off(void) {
	LEDA_OFF;
}

void displaySync_Hard(void) {
	LEDB_OFF;
}

void displaySync_Soft(void) {
	LEDB_ON;
}


void updateRGB(controlRateInputs * controlInputs, audioRateInputs * audioInputs) {
	SET_RED_LED((controlInputs->knob1Value + controlInputs->cv1Value) >> 1);
	SET_GREEN_LED(__USAT(2400 + controlInputs->knob3Value - audioInputs->cv3Input[0], 12) >> 1);
	SET_BLUE_LED(4095 - (controlInputs->knob1Value + controlInputs->cv1Value) >> 1);

}

