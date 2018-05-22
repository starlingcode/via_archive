#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"
#include "main_state_machine.h"
#include "dsp.h"
#include "hardware_io.h"


void calculateLogic(uint32_t * phase, audioRateOutputs * output, uint32_t index) {

	switch (phase[index]) {
		//no logic events
		case 0:
			output->logicStates[index].shAHandler = &holdLogic;
			output->logicStates[index].shBHandler = &holdLogic;
			output->logicStates[index].logicAHandler = &holdLogic;
			output->logicStates[index].logicBHandler = &holdLogic;
			output->logicStates[index].auxLogicHandler= &holdLogic;
			break;
		//dummy at a handling
		case 1:
			output->logicStates[index].shAHandler = &holdLogic;
			output->logicStates[index].shBHandler = &resampleB;
			output->logicStates[index].logicAHandler = &logicAHigh;
			output->logicStates[index].logicBHandler = &logicBLow;
			output->logicStates[index].auxLogicHandler= &holdLogic;
			break;
		//dummy at b handling
		case 2:
			output->logicStates[index].shAHandler = &resampleA;
			output->logicStates[index].shBHandler = &holdLogic;
			output->logicStates[index].logicAHandler = &logicALow;
			output->logicStates[index].logicBHandler = &logicBHigh;
			output->logicStates[index].auxLogicHandler= &holdLogic;
			break;
		default:
			break;
	}

}
void logicInit(void) {
	for (int i = 0; i < BUFFER_SIZE; i++) {
		logicStateBuffer1[i].shAHandler = &holdLogic;
		logicStateBuffer1[i].shBHandler = &holdLogic;
		logicStateBuffer1[i].logicAHandler = &holdLogic;
		logicStateBuffer1[i].logicBHandler = &holdLogic;
		logicStateBuffer1[i].auxLogicHandler= &holdLogic;
		logicStateBuffer2[i].shAHandler = &holdLogic;
		logicStateBuffer2[i].shBHandler = &holdLogic;
		logicStateBuffer2[i].logicAHandler = &holdLogic;
		logicStateBuffer2[i].logicBHandler = &holdLogic;
		logicStateBuffer2[i].auxLogicHandler= &holdLogic;
	}
}

void holdLogic(void) {
	LEDA_ON;
}
void logicAHigh(void) {
	ALOGIC_HIGH;
}
void logicALow(void) {
	ALOGIC_LOW;
}
void logicBHigh(void) {
	BLOGIC_HIGH;
}
void logicBLow(void) {
	BLOGIC_LOW;
}
void shASample(void) {
	SH_A_SAMPLE;
}
void shATrack(void) {
	SH_A_TRACK;
}
void shBSample(void) {
	SH_B_SAMPLE;
}
void shBTrack(void) {
	SH_B_TRACK;
}


