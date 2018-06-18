#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"
#include "main_state_machine.h"
#include "dsp.h"
#include "via_rev5_hardware_io.h"

/*
 *
 * FIR filter setup
 *
 */

// fir filter data structure
arm_fir_instance_q31 fir;

// declare filter coefficients
q31_t firCoefficients[NUM_TAPS] = FIR24TAPS5_12;

// Declare State buffer of size (numTaps + blockSize - 1)
q31_t firState[BUFFER_SIZE + NUM_TAPS - 1];


void initializeFilter() {
	// initialize the FIR filter
	arm_fir_init_q31(&fir, NUM_TAPS, &firCoefficients[0], &firState[0], BUFFER_SIZE);
}

/*
 *
 * Logic functions
 *
 */

// resampling management timers

extern TIM_HandleTypeDef htim18;
extern TIM_HandleTypeDef htim17;

void logicAHigh(void);
void logicALow(void);
void logicBHigh(void);
void logicBLow(void);
void shASample(void);
void shATrack(void);
void shBSample(void);
void shBTrack(void);
void resampleA(void);
void resampleB(void);

// assign a set of logic output function per the phase event at that sample
// SH on or off is wrapped up in this pair of functions

static inline void calculateLogicSHOn(uint32_t * phaseEvents, audioRateOutputs * output) {

	for (int i; i < BUFFER_SIZE; i++) {

		switch (phaseEvents[i]) {
			//no logic events
			case 0:
				output->shAHandler[i] = &logicNoOp;
				output->shBHandler[i] = &logicNoOp;
				output->logicAHandler[i] = &logicNoOp;
				output->logicBHandler[i] = &logicNoOp;
				output->auxLogicHandler[i]= &logicNoOp;
				break;
			//dummy at a handling
			case 1:
				output->shAHandler[i] = &logicNoOp;
				output->shBHandler[i] = &resampleB;
				output->logicAHandler[i] = &logicAHigh;
				output->logicBHandler[i] = &logicBLow;
				output->auxLogicHandler[i]= &logicNoOp;
				break;
			//dummy at b handling
			case 2:
				output->shAHandler[i] = &resampleA;
				output->shBHandler[i] = &logicNoOp;
				output->logicAHandler[i] = &logicALow;
				output->logicBHandler[i] = &logicBHigh;
				output->auxLogicHandler[i]= &logicNoOp;
				break;
			default:
				break;
		}

	}

}

static inline void calculateLogicSHOff(uint32_t * phase, audioRateOutputs * output) {

	for (int i; i < BUFFER_SIZE; i++) {

		switch (phase[i]) {
			//no logic events
			case 0:
				output->shAHandler[i] = &logicNoOp;
				output->shBHandler[i] = &logicNoOp;
				output->logicAHandler[i] = &logicNoOp;
				output->logicBHandler[i] = &logicNoOp;
				output->auxLogicHandler[i]= &logicNoOp;
				break;
			//dummy at a handling
			case 1:
				output->shAHandler[i] = &logicNoOp;
				output->shBHandler[i] = &logicNoOp;
				output->logicAHandler[i] = &logicAHigh;
				output->logicBHandler[i] = &logicBLow;
				output->auxLogicHandler[i]= &logicNoOp;
				break;
			//dummy at b handling
			case 2:
				output->shAHandler[i] = &logicNoOp;
				output->shBHandler[i] = &logicNoOp;
				output->logicAHandler[i] = &logicALow;
				output->logicBHandler[i] = &logicBHigh;
				output->auxLogicHandler[i]= &logicNoOp;
				break;
			default:
				break;
		}

	}

}

void logicAndFilterSHOn(uint32_t * phaseEvents, audioRateOutputs * output) {
	calculateLogicSHOn(phaseEvents, output);
}
void logicAndFilterSHOff(uint32_t * phaseEvents, audioRateOutputs * output) {
	calculateLogicSHOff(phaseEvents, output);
	arm_fir_fast_q31(&fir, output->samples, output->samples, BUFFER_SIZE);

}

// wrap register address functions to be loaded into the logic struct (which is loaded into a playback buffer)
void logicNoOp(void) {

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

void resampleA(void){
	SH_A_TRACK;
	__HAL_TIM_SET_COUNTER(&htim17, 0);
	__HAL_TIM_ENABLE(&htim17);
}
void resampleB(void){
	SH_B_TRACK;
	__HAL_TIM_SET_COUNTER(&htim18, 0);
	__HAL_TIM_ENABLE(&htim18);
}


