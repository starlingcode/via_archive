#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"
#include "main_state_machine.h"
#include "dsp.h"
#include "fill_buffer.h"
#include "tables.h"

arm_fir_instance_q31 fir;


void fillBuffer(void) {

	static q31_t incrementValues1[BUFFER_SIZE];
	static q31_t incrementValues2[BUFFER_SIZE];
	static q31_t phaseArray[BUFFER_SIZE];
	static q31_t phaseEventArray[BUFFER_SIZE];
	static int lastPhase;
	static int oscillatorOn;
	static uint32_t slowConversionCounter;

	// eventually,
	// static struct viaStateInfoHolder viaStateInfo;


	// profiling pin a logic out high
	GPIOC->BRR = (uint32_t)GPIO_PIN_13;

	getIncrementsEnv(inputRead->cv3Input, &controlRateInput, incrementValues1, incrementValues2);

	lastPhase = (*advancePhase)(incrementValues1, incrementValues2, inputRead->triggerInput, inputRead->gateInput, lastPhase, &oscillatorOn, phaseArray, phaseEventArray);

	arm_offset_q31(inputRead->cv3Input, controlRateInput.knob3Value - 2048, inputRead->cv3Input, BUFFER_SIZE);

	(*getSamples)(phaseArray, __USAT(inputRead->cv2Input[0] + controlRateInput.knob2Value - 2048, 12), inputRead->cv3Input, outputWrite->samples, outputWrite->auxLogicHandler);

	(*calculateSHA)(phaseEventArray, outputWrite);

	(*calculateSHB)(phaseEventArray, outputWrite);

	(*calculateLogicA)(phaseEventArray, inputRead->triggerInput, oscillatorOn, outputWrite);

	(*calculateLogicB)(phaseEventArray, outputWrite);

	// profiling pin a logic out low
	GPIOC->BSRR = (uint32_t)GPIO_PIN_13;

	slowConversionCounter++;

	slowConversionCounter = handleCoversionSlow(outputWrite->samples[BUFFER_SIZE - 1], lastPhase, &controlRateInput, inputRead, slowConversionCounter);

	main_state = main_handleUI;

//	// profiling pin b logic out low
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

	output1.logicBHandler = dac3SampleBuffer1;
	output2.logicBHandler = dac3SampleBuffer2;

	output1.auxLogicHandler = auxLogicBuffer1;
	output2.auxLogicHandler = auxLogicBuffer2;

	input1.cv2Input = t2CVBuffer1;
	input1.cv3Input = morphCVBuffer1;
	input1.triggerInput = hardSyncBuffer1;
	input1.gateInput = reverseBuffer1;

	input2.cv2Input = t2CVBuffer2;
	input2.cv3Input = morphCVBuffer2;
	input2.triggerInput = hardSyncBuffer2;
	input2.gateInput = reverseBuffer2;

	outputs = &output1;
	outputWrite = &output2;

	inputRead = &input1;
	inputWrite = &input2;
}
