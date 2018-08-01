#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"
#include "main_state_machine.h"
#include "dsp.h"
#include "hardware_io.h"

// minimal implementation of logic outputs with s&h on or off
// TODO more s&h modes? pulse out on expander (easy), delta out on logic B (harder)

void calculateLogicSHOn(uint32_t * phase, audioRateOutputs * output, uint32_t index) {

	switch (phase[index]) {
		//no logic events
		case 0:
			output->logicStates[index].shAHandler = &logicNoOp;
			output->logicStates[index].shBHandler = &logicNoOp;
			output->logicStates[index].logicAHandler = &logicNoOp;
			output->logicStates[index].logicBHandler = &logicNoOp;
			output->logicStates[index].auxLogicHandler= &logicNoOp;
			break;
		//dummy at a handling
		case 1:
			output->logicStates[index].shAHandler = &logicNoOp;
			output->logicStates[index].shBHandler = &resampleB;
			output->logicStates[index].logicAHandler = &logicAHigh;
			output->logicStates[index].logicBHandler = &logicBLow;
			output->logicStates[index].auxLogicHandler= &logicNoOp;
			break;
		//dummy at b handling
		case 2:
			output->logicStates[index].shAHandler = &resampleA;
			output->logicStates[index].shBHandler = &logicNoOp;
			output->logicStates[index].logicAHandler = &logicALow;
			output->logicStates[index].logicBHandler = &logicBHigh;
			output->logicStates[index].auxLogicHandler= &logicNoOp;
			break;
		default:
			break;
	}

}

void calculateLogicSHOff(uint32_t * phase, audioRateOutputs * output, uint32_t index) {

	switch (phase[index]) {
		//no logic events
		case 0:
			output->logicStates[index].shAHandler = &logicNoOp;
			output->logicStates[index].shBHandler = &logicNoOp;
			output->logicStates[index].logicAHandler = &logicNoOp;
			output->logicStates[index].logicBHandler = &logicNoOp;
			output->logicStates[index].auxLogicHandler= &logicNoOp;
			break;
		//dummy at a handling
		case 1:
			output->logicStates[index].shAHandler = &logicNoOp;
			output->logicStates[index].shBHandler = &logicNoOp;
			output->logicStates[index].logicAHandler = &logicAHigh;
			output->logicStates[index].logicBHandler = &logicBLow;
			output->logicStates[index].auxLogicHandler= &logicNoOp;
			break;
		//dummy at b handling
		case 2:
			output->logicStates[index].shAHandler = &logicNoOp;
			output->logicStates[index].shBHandler = &logicNoOp;
			output->logicStates[index].logicAHandler = &logicALow;
			output->logicStates[index].logicBHandler = &logicBHigh;
			output->logicStates[index].auxLogicHandler= &logicNoOp;
			break;
		default:
			break;
	}

}

// initialize the logic state buffers with valid function addresses

void logicInit(void) {
	for (int i = 0; i < BUFFER_SIZE; i++) {
		logicStateBuffer1[i].shAHandler = &logicNoOp;
		logicStateBuffer1[i].shBHandler = &logicNoOp;
		logicStateBuffer1[i].logicAHandler = &logicNoOp;
		logicStateBuffer1[i].logicBHandler = &logicNoOp;
		logicStateBuffer1[i].auxLogicHandler= &logicNoOp;
		logicStateBuffer2[i].shAHandler = &logicNoOp;
		logicStateBuffer2[i].shBHandler = &logicNoOp;
		logicStateBuffer2[i].logicAHandler = &logicNoOp;
		logicStateBuffer2[i].logicBHandler = &logicNoOp;
		logicStateBuffer2[i].auxLogicHandler= &logicNoOp;
	}
}




