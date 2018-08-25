#include "signals.h"
#include "user_interface.h"
#include "via_rev5_hardware_io.h"

#include "../inc/meta_fill_buffer.h"
#include "../inc/meta_main_states.h"
#include "../inc/meta_modes.h"
#include "../inc/meta_ui_implementation.h"

extern TIM_HandleTypeDef htim16;
extern TIM_HandleTypeDef htim17;

void mainRisingEdgeCallback(osc_signal_set * signals) {

	softwareSignaling * softwareSignals = signals->softwareSignals;

	softwareSignals->gateSignal = 1;
	softwareSignals->triggerSignal = 0;
	if (TRIG_MODE != 0) {
		updateRGB = &updateRGBTrigger;
		__HAL_TIM_SET_COUNTER(&htim17, 0);
		__HAL_TIM_SET_COUNTER(&htim16, 0);
		__HAL_TIM_DISABLE(&htim16);
		__HAL_TIM_ENABLE(&htim17);
	}

}

void mainFallingEdgeCallback(osc_signal_set * signals) {

	signals->softwareSignals->gateSignal = 0;

}

void auxRisingEdgeCallback(osc_signal_set * signals) {
	;
}
void auxFallingEdgeCallback(osc_signal_set * signals) {
	;
}

void buttonPressedCallback(osc_signal_set * signals) {
	;
}
void buttonReleasedCallback(osc_signal_set * signals) {
	;
}

void ioProcessCallback(osc_signal_set * signals) {

	static int readIndex;

	audioRateOutputs* outputRead = signals->outputRead;
	int outputSample = outputRead->samples[readIndex];

	WRITE_DAC1(4095 - outputSample);
	WRITE_DAC2(outputSample);
	WRITE_DAC3(__USAT(outputRead->dac3Samples[readIndex], 12));


	setLogicOutputsNoLEDs(outputRead->logicAHandler[readIndex], outputRead->auxLogicHandler[readIndex], outputRead->shAHandler[readIndex], outputRead->shBHandler[readIndex]);


	audioRateInputs* inputWrite = signals->inputWrite;
	// store the x and morph CVs at sample rate
	inputWrite->cv2Input[readIndex] = __USAT(cv2, 12);
	inputWrite->cv3Input[readIndex] = __USAT(cv3, 12);

	// store the sync signal and reset it to 1 after reading
	// this writes a 0 at every rising edge
	softwareSignaling * softwareSignals = signals->softwareSignals;
	inputWrite->triggerInput[readIndex] = softwareSignals->triggerSignal;
	softwareSignals->triggerSignal = 1;

	inputWrite->gateInput[readIndex] = softwareSignals->gateSignal;

	// TODO replace with linked list implementation that makes this prettier
	// I can think of a few other better ways of doing this
	// one buffer, fillbuffer fills different halves
	// numerical approach to the accumulator

	// check the buffer read counter to see if we just read the last sample in the current buffer
	if (readIndex - (BUFFER_SIZE - 1) == 0) {

		// if so, reset the buffer index counter
		readIndex = 0;

		// switch out the read/write struct pointers for inputs and outputs
		audioRateInputs *temp1 = inputWrite;
		signals->inputWrite = signals->inputRead;
		signals->inputRead = temp1;

		audioRateOutputs *temp2 = signals->outputWrite;
		signals->outputWrite = signals->outputRead;
		signals->outputRead = temp2;

		// tell the main loop to fill the next buffer
		main_state = main_nextSample;

	} else {
		// otherwise, increment the buffer read counter
		readIndex++;
	}

}
void generateSample(osc_signal_set * signals) {

	// handled with fillBuffer

}
