#include "signals.h"
#include "user_interface.h"
#include "via_rev5_hardware_io.h"

#include "../inc/osc_fill_buffer.h"
#include "../inc/osc_main_states.h"
#include "../inc/osc_modes.h"

void mainRisingEdgeCallback(viaSignals * signals) {

	softwareSignaling * softwareSignals = signals->softwareSignals;

	if (softwareSignals->syncMode == hard) {
		// this is reset to 1 at every with every new sample aquisition
		softwareSignals->syncSignal = 0;
	} else {
		// toggle increment direction on rising and falling edges
		softwareSignals->reverseSignal = 1;
	}

}

void mainFallingEdgeCallback(viaSignals * signals) {

	signals->softwareSignals->reverseSignal = -1;

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
	inputWrite->hardSyncInput[readIndex] = softwareSignals->syncSignal;
	softwareSignals->syncSignal = 1;

	inputWrite->reverseInput[readIndex] = softwareSignals->reverseSignal;

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
void nextSampleCallback(viaSignals * signals) {

	// handled with fillBuffer

}
