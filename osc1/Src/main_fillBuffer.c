#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"
#include "main_state_machine.h"
#include "dsp.h"

arm_fir_instance_q31 fir;

// declare filter coefficients
q31_t firCoefficients[NUM_TAPS] = FIR24TAPS5_12;

// Declare State buffer of size (numTaps + blockSize - 1)
q31_t firState[BUFFER_SIZE + NUM_TAPS - 1];

void fillBufferSHOff(void) {

	int phaseArray[BUFFER_SIZE];

	for (int i = 0; i < (BUFFER_SIZE); i++) {
		(*incrementOscillator)(inputRead, &controlRateInput, outputWrite, &phaseArray, i);
	}

	// always track a and b
	for (int i = 0; i < (BUFFER_SIZE); i++) {
		calculateLogicSHOff(&phaseArray, outputWrite, i);
	}

	//turn off for s&h (ripple allows the sound of the input tracking to bleed)
	arm_fir_fast_q31(&fir, outputWrite->samples, outputWrite->samples, BUFFER_SIZE);

}

void fillBufferSHOn(void) {

	int phaseArray[BUFFER_SIZE];

	for (int i = 0; i < (BUFFER_SIZE); i++) {
		(*incrementOscillator)(inputRead, &controlRateInput, outputWrite, &phaseArray, i);
	}

	// resample A when at B and B when at A for smooth decimation
	for (int i = 0; i < (BUFFER_SIZE); i++) {
		calculateLogicSHOn(&phaseArray, outputWrite, i);
	}

}

void initializeDoubleBuffer() {

	// TODO needs more comments

	// initialize logic state buffers to point to a valid address
	logicInit();

	// initialize double buffers used for DSP
	output1.samples = sampleBuffer1;
	output1.logicStates = logicStateBuffer1;

	output2.samples = sampleBuffer2;
	output2.logicStates = logicStateBuffer2;

	input1.xCV = xCVBuffer1;
	input1.morphCV = morphCVBuffer1;
	input1.hardSyncInput = hardSyncBuffer1;
	input1.reverseInput = reverseBuffer1;

	input2.xCV = xCVBuffer2;
	input2.morphCV = morphCVBuffer2;
	input2.hardSyncInput = hardSyncBuffer2;
	input2.reverseInput = reverseBuffer2;

	outputRead = &output1;
	outputWrite = &output2;

	inputRead = &input1;
	inputWrite = &input2;
}

void initializeFilter() {
	// initialize the FIR filter
	arm_fir_init_q31(&fir, NUM_TAPS, &firCoefficients[0], &firState[0], BUFFER_SIZE);
}
