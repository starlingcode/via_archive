#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"
#include "main_state_machine.h"
#include "dsp.h"
#include "tables.h"

void fillBuffer(void) {

	q31_t incrementBuffer[BUFFER_SIZE];
	q31_t phaseModBuffer[BUFFER_SIZE];
	q31_t morphBuffer[BUFFER_SIZE];
	q31_t pwmBuffer[BUFFER_SIZE];
	uint32_t phaseEvents[BUFFER_SIZE];



	// profiling pin a logic out high
	GPIOC->BRR = (uint32_t)GPIO_PIN_13;


	(*prepareCV)(inputRead, &controlRateInput, incrementBuffer, phaseModBuffer, morphBuffer, pwmBuffer);

	incrementOscillator(incrementBuffer, phaseModBuffer, morphBuffer, pwmBuffer, inputRead->hardSyncInput, inputRead->reverseInput, outputWrite->samples, phaseEvents);

	// profiling pin a logic out low
	GPIOC->BSRR = (uint32_t)GPIO_PIN_13;

	// profiling pin b logic out high
	GPIOC->BRR = (uint32_t)GPIO_PIN_15;


	(*logicAndFilter)(phaseEvents, outputWrite);

	// profiling pin b logic out low
	GPIOC->BSRR = (uint32_t)GPIO_PIN_15;


}


void initializeDoubleBuffer() {

	// the logic handlers need to be initialized to a valid address
	for (int i = 0; i < BUFFER_SIZE; i++) {
		shABuffer1[i] = &logicNoOp;
		shBBuffer1[i] = &logicNoOp;
		logicABuffer1[i] = &logicNoOp;
		logicBBuffer1[i] = &logicNoOp;
		auxLogicBuffer1[i]= &logicNoOp;
		shABuffer2[i] = &logicNoOp;
		shBBuffer2[i] = &logicNoOp;
		logicABuffer2[i] = &logicNoOp;
		logicBBuffer2[i] = &logicNoOp;
		auxLogicBuffer2[i]= &logicNoOp;
	}


	// initialize double buffers used for DSP
	output1.samples = sampleBuffer1;
	output2.samples = sampleBuffer2;

	output1.shAHandler = shABuffer1;
	output2.shAHandler = shABuffer2;

	output1.shBHandler = shBBuffer1;
	output2.shBHandler = shBBuffer2;

	output1.logicAHandler = logicABuffer1;
	output2.logicAHandler = logicABuffer2;

	output1.logicBHandler = logicBBuffer1;
	output2.logicBHandler = logicBBuffer2;

	output1.auxLogicHandler = auxLogicBuffer1;
	output2.auxLogicHandler = auxLogicBuffer2;

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
