#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"
#include "main_state_machine.h"
#include "dsp.h"
#include "tables.h"

void calculateDac3Samples(q31_t *, q31_t *, q31_t *);

void fillBuffer(void) {

	q31_t incrementBuffer[BUFFER_SIZE];
	q31_t phaseModBuffer[BUFFER_SIZE];
	q31_t morphBuffer[BUFFER_SIZE];
	q31_t pwmBuffer[BUFFER_SIZE];
	int phaseEvents[BUFFER_SIZE];
	static uint32_t slowConversionCounter;


	(*prepareCV)(inputRead, &controlRateInput, incrementBuffer, phaseModBuffer, morphBuffer, pwmBuffer);

	incrementOscillator(incrementBuffer, phaseModBuffer, morphBuffer, pwmBuffer, inputRead->hardSyncInput, inputRead->reverseInput, outputWrite->samples, phaseEvents, outputWrite->dac3Samples);

	(*logicAndFilter)(phaseEvents, outputWrite);

	calculateDac3Samples(outputWrite->dac3Samples, phaseModBuffer, incrementBuffer);

	slowConversionCounter++;

	handleCoversionSlow(&controlRateInput, slowConversionCounter);

	main_state = main_handleUI;

	// profiling pin b logic out low
//	GPIOC->BSRR = (uint32_t)GPIO_PIN_15;

}

void calculateDac3Samples(q31_t * deltaBuffer, q31_t * phaseBuffer, q31_t * incrementBuffer) {

	static int lastDelta;
	static int lastPhase;
	static int lastSample;
	int thisSample;
	int delta;
	int phase;

	for (int i = 0; i < BUFFER_SIZE; i++) {

		delta = deltaBuffer[i] * 2 - 1;
		phase = phaseBuffer[i];

		if (lastDelta != delta) {

			int impulsePhase = phase & 0xFFFF0000;
			int thisFractionalPhase = phase - impulsePhase;
			int lastFractionalPhase = impulsePhase - lastPhase;
			int increment = incrementBuffer[i];

			int lastBlepCoefficient = (lastFractionalPhase << 16) / increment;
			int lastBlep = (lastBlepCoefficient << 1) - fix16_square(lastBlepCoefficient) - (1 << 16);
			lastSample -= lastBlep * (delta);

			int thisBlepCoefficient = (thisFractionalPhase << 16) / increment;
			int thisBlep = fix16_square(thisBlepCoefficient) + (thisBlepCoefficient << 1) + (1 << 16);
			thisSample = (delta << 16) - thisBlep * (delta);

		} else {
			thisSample = (delta << 16);
		}

		deltaBuffer[i] = ((lastSample >> 6) + 2048);

		lastSample = thisSample;
		lastPhase = phase;
		lastDelta = delta;


	}


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

	output1.dac3Samples = dac3SampleBuffer1;
	output2.dac3Samples = dac3SampleBuffer2;

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

	outputs = &output1;
	outputWrite = &output2;

	inputRead = &input1;
	inputWrite = &input2;
}
