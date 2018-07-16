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
	int phaseEvents[BUFFER_SIZE];
	static uint32_t slowConversionCounter;

	// profiling pin a logic out high
	GPIOC->BRR = (uint32_t)GPIO_PIN_13;


	(*prepareCV)(inputRead, &controlRateInput, incrementBuffer, phaseModBuffer, morphBuffer, pwmBuffer);

	incrementOscillator(incrementBuffer, phaseModBuffer, morphBuffer, pwmBuffer, inputRead->hardSyncInput, inputRead->reverseInput, outputWrite->samples, phaseEvents);

	// profiling pin a logic out low
	GPIOC->BSRR = (uint32_t)GPIO_PIN_13;

//	// profiling pin b logic out high
//	GPIOC->BRR = (uint32_t)GPIO_PIN_15;


	(*logicAndFilter)(phaseEvents, outputWrite);

	slowConversionCounter++;

	handleCoversionSlow(&controlRateInput, slowConversionCounter);

	main_State = main_handleUI;

	// profiling pin b logic out low
//	GPIOC->BSRR = (uint32_t)GPIO_PIN_15;

}


void initializeDoubleBuffer() {


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

	input1.xCV = t2CVBuffer1;
	input1.morphCV = morphCVBuffer1;
	input1.hardSyncInput = hardSyncBuffer1;
	input1.reverseInput = reverseBuffer1;

	input2.xCV = t2CVBuffer2;
	input2.morphCV = morphCVBuffer2;
	input2.hardSyncInput = hardSyncBuffer2;
	input2.reverseInput = reverseBuffer2;

	outputRead = &output1;
	outputWrite = &output2;

	inputRead = &input1;
	inputWrite = &input2;
}
