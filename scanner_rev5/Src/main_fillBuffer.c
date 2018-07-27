#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"
#include "main_state_machine.h"
#include "dsp.h"
#include "tables.h"

arm_fir_instance_q31 fir;


void fillBuffer(void) {

	q31_t xIndexBuffer[BUFFER_SIZE];
	q31_t yIndexBuffer[BUFFER_SIZE];
	uint32_t zIndex;
	static uint32_t slowConversionCounter;

	// profiling pin a logic out high
	GPIOC->BRR = (uint32_t)GPIO_PIN_13;

	switch(button3Mode) {
		case foldX:
			foldBuffer(inputRead->xCV, controlRateInput.knob2Value, xIndexBuffer);
			break;

		case wrapX:
			wrapBuffer(inputRead->xCV, controlRateInput.knob2Value, xIndexBuffer);
			break;
	}

	switch(button6Mode) {
		case foldY:
			foldBuffer(inputRead->yCV, controlRateInput.knob3Value, yIndexBuffer);
			break;

		case wrapY:
			wrapBuffer(inputRead->yCV, controlRateInput.knob3Value, yIndexBuffer);
			break;
	}

	zIndex = __USAT((int)controlRateInput.knob1Value + 2200 - (int)controlRateInput.cv1Value, 12);

	switch(button1Mode)  {

		case sum:
			scanTerrainSum(xIndexBuffer, yIndexBuffer, inputRead->reverseInput, zIndex, outputWrite->samples);
			break;

		case subtract:
			scanTerrainSubtract(xIndexBuffer, yIndexBuffer, inputRead->reverseInput, zIndex, outputWrite->samples);
			break;

		case product:
			scanTerrainProduct(xIndexBuffer, yIndexBuffer, inputRead->reverseInput, zIndex, outputWrite->samples);
			break;

		case PM:
			scanTerrainPM(xIndexBuffer, yIndexBuffer, inputRead->reverseInput, zIndex, outputWrite->samples);
			break;


	}

	// profiling pin a logic out low
	GPIOC->BSRR = (uint32_t)GPIO_PIN_13;

	slowConversionCounter++;

	slowConversionCounter = handleCoversionSlow(&controlRateInput, slowConversionCounter);

	main_State = main_handleUI;

//	// profiling pin b logic out low
//	GPIOC->BSRR = (uint32_t)GPIO_PIN_15;

}


void initializeDoubleBuffer() {

	// the logic handlers need to be initialized to a valid address
	for (int i = 0; i < BUFFER_SIZE; i++) {
		shABuffer1[i] = &logicNoOp;
		shBBuffer1[i] = &logicNoOp;
		logicABuffer1[i] = &logicNoOp;
		dac3SampleBuffer1[i] = &logicNoOp;
		auxLogicBuffer1[i]= &logicNoOp;
		shABuffer2[i] = &logicNoOp;
		shBBuffer2[i] = &logicNoOp;
		logicABuffer2[i] = &logicNoOp;
		dac3SampleBuffer2[i] = &logicNoOp;
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

	output1.logicBHandler = dac3SampleBuffer1;
	output2.logicBHandler = dac3SampleBuffer2;

	output1.auxLogicHandler = auxLogicBuffer1;
	output2.auxLogicHandler = auxLogicBuffer2;

	input1.xCV = t2CVBuffer1;
	input1.yCV = morphCVBuffer1;
	input1.hardSyncInput = hardSyncBuffer1;
	input1.reverseInput = reverseBuffer1;

	input2.xCV = t2CVBuffer2;
	input2.yCV = morphCVBuffer2;
	input2.hardSyncInput = hardSyncBuffer2;
	input2.reverseInput = reverseBuffer2;

	outputs = &output1;
	outputWrite = &output2;

	inputRead = &input1;
	inputWrite = &input2;
}
