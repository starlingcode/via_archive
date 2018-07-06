#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"
#include "main_state_machine.h"
#include "dsp.h"
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


	// profiling pin a logic out high
	GPIOC->BRR = (uint32_t)GPIO_PIN_13;

	(*getIncrements)(inputRead->t2CV, &controlRateInput, incrementValues1, incrementValues2);

	lastPhase = (*advancePhase)(incrementValues1, incrementValues2, inputRead->triggerInput, inputRead->gateInput, lastPhase, oscillatorOn, phaseArray, phaseEventArray);

	arm_offset_q31(inputRead->morphCV, controlRateInput.knob3Value - 2048, inputRead->morphCV, BUFFER_SIZE);

	//arm_shift_q31(phaseArray, -13, outputWrite->samples, BUFFER_SIZE);

	(*getSamples)(phaseArray, __USAT(inputRead->t2CV[0] + controlRateInput.knob2Value - 2048, 12), inputRead->morphCV, outputWrite->samples);

	oscillatorOn = (*handleLoop)(phaseEventArray, inputRead->triggerInput, outputWrite->samples, oscillatorOn);

	// profiling pin a logic out low
	GPIOC->BSRR = (uint32_t)GPIO_PIN_13;

	slowConversionCounter++;

	slowConversionCounter = handleCoversionSlow(&controlRateInput, slowConversionCounter);

	main_State = main_handleUI;

//	// profiling pin b logic out low
//	GPIOC->BSRR = (uint32_t)GPIO_PIN_15;

}

int handleLoopOff(q31_t * phaseEvents, q31_t * triggers, q31_t * samples, int oscillatorOn) {
	return 1;
}

int handleLoopOn(q31_t * phaseEvents, q31_t * triggers, q31_t * samples, int oscillatorOn) {

	if (oscillatorOn) {

		for (int i = 0; i < BUFFER_SIZE; i++) {

			switch (phaseEvents[i]) {
				case (AT_A_FROM_ATTACK):
				case (AT_A_FROM_RELEASE):
					pendulumStateMachine = pendulumRestingState;
					oscillatorOn = 0;
					for (int j = i; j < BUFFER_SIZE; j ++) {
						samples[j] = 0;
					}
					break;

				default:
					break;

			}

			if (triggers[i] == 0) {
				pendulumStateMachine = pendulumForwardAttackState;
				oscillatorOn = 1;
			}
		}
	} else {
		for (int i = 0; i < BUFFER_SIZE; i++) {
			if (triggers[i] == 0) {
				oscillatorOn = 1;
			}
		}
	}



	return oscillatorOn;

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

	input1.t2CV = t2CVBuffer1;
	input1.morphCV = morphCVBuffer1;
	input1.triggerInput = hardSyncBuffer1;
	input1.gateInput = reverseBuffer1;

	input2.t2CV = t2CVBuffer2;
	input2.morphCV = morphCVBuffer2;
	input2.triggerInput = hardSyncBuffer2;
	input2.gateInput = reverseBuffer2;

	outputRead = &output1;
	outputWrite = &output2;

	inputRead = &input1;
	inputWrite = &input2;
}