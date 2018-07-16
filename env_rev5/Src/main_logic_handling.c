#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"
#include "main_state_machine.h"
#include "dsp.h"
#include "fill_buffer.h"
#include "via_rev5_hardware_io.h"

/*
 *
 * FIR filter setup
 *
 */

// fir filter data structure
extern arm_fir_instance_q31 fir;

// declare filter coefficients
q31_t firCoefficients[NUM_TAPS] = FIR24TAPS5_12;

// declare state buffer of size (numTaps + blockSize - 1)
q31_t firState[BUFFER_SIZE + NUM_TAPS - 1];

// iir filter data structure
arm_biquad_casd_df1_inst_q31 biquad;

// declare filter coefficients (a set of 5 for each stage)
q31_t biquadCoefficients[NUM_STAGES * 5] = BIQUAD20K_8STAGE;

// Declare state buffer of size (numStages*4, 4 states per stage)
q31_t biquadState[NUM_STAGES*4];


void initializeFilter() {
	// initialize the FIR filter
	arm_fir_init_q31(&fir, NUM_TAPS, &firCoefficients[0], &firState[0], BUFFER_SIZE);
}

//void initializeFilter() {
//	// initialize the IIR filter (cascaded biquad filter)
//	arm_biquad_cascade_df1_init_q31(&biquad, NUM_STAGES, &biquadCoefficients[0], &biquadState[0], 0);
//}

/*
 *
 * Logic functions
 *
 */

void calculateLogicAGate(q31_t * phaseEvents, q31_t * triggers, int oscillatorOn, audioRateOutputs * output) {

	static int lastOscillatorOn;

	for (int i = 0; i < BUFFER_SIZE; i++) {

		switch (phaseEvents[i]) {
			//no logic events
			case 0:
				output->logicAHandler[i] = GPIO_NOP;
				break;
			//dummy at a handling
			case AT_A_FROM_RELEASE:
			case AT_A_FROM_ATTACK:
				output->logicAHandler[i] = ALOGIC_HIGH_MASK;
				break;
			//dummy at b handling
			case AT_B_FROM_RELEASE:
			case AT_B_FROM_ATTACK:
				output->logicAHandler[i] = ALOGIC_LOW_MASK;
				break;
			default:
				break;
		}


	}

}

void calculateLogicBGate(q31_t * phaseEvents, audioRateOutputs * output) {


	for (int i = 0; i < BUFFER_SIZE; i++) {

		switch (phaseEvents[i]) {
			//no logic events
			case 0:
				output->logicBHandler[i] = GPIO_NOP;
				break;
			//dummy at a handling
			case AT_A_FROM_RELEASE:
			case AT_A_FROM_ATTACK:
				output->logicBHandler[i] = BLOGIC_LOW_MASK;
				break;
			//dummy at b handling
			case AT_B_FROM_RELEASE:
			case AT_B_FROM_ATTACK:
				output->logicBHandler[i] = BLOGIC_HIGH_MASK;
				break;
			default:
				break;
		}

	}

}



// No S&H

void calculateSHAMode1(q31_t * phaseEvents, audioRateOutputs * output) {


	for (int i = 0; i < BUFFER_SIZE; i++) {

		switch (phaseEvents[i]) {
			//no logic events
			case 0:
				output->shAHandler[i] = SH_A_TRACK_MASK;
				break;
			//dummy at a handling
			case AT_A_FROM_RELEASE:
			case AT_A_FROM_ATTACK:
				output->shAHandler[i] = SH_A_TRACK_MASK;
				break;
			//dummy at b handling
			case AT_B_FROM_RELEASE:
			case AT_B_FROM_ATTACK:
				output->shAHandler[i] = SH_A_TRACK_MASK;
				break;
			default:
				break;
		}

	}

}

// Sample A from A to B

void calculateSHAMode2(q31_t * phaseEvents, audioRateOutputs * output) {

	for (int i = 0; i < BUFFER_SIZE; i++) {

		switch (phaseEvents[i]) {
			//no logic events
			case 0:
				output->shAHandler[i] = GPIO_NOP;
				break;
			//dummy at a handling
			case AT_A_FROM_RELEASE:
			case AT_A_FROM_ATTACK:
				output->shAHandler[i] = SH_A_SAMPLE_MASK;
				break;
			//dummy at b handling
			case AT_B_FROM_RELEASE:
			case AT_B_FROM_ATTACK:
				output->shAHandler[i] = SH_A_TRACK_MASK;
				break;
			default:
				break;
		}

	}

}

// Resample B at A

void calculateSHAMode3(q31_t * phaseEvents, audioRateOutputs * output) {

	for (int i = 0; i < BUFFER_SIZE; i++) {

		switch (phaseEvents[i]) {
			//no logic events
			case 0:
				output->shAHandler[i] = SH_A_SAMPLE_MASK;
				break;
			//dummy at a handling
			case AT_A_FROM_RELEASE:
			case AT_A_FROM_ATTACK:
				output->shAHandler[i] = SH_A_TRACK_MASK;
				break;
			//dummy at b handling
			case AT_B_FROM_RELEASE:
			case AT_B_FROM_ATTACK:
				output->shAHandler[i] = SH_A_SAMPLE_MASK;
				break;
			default:
				break;
		}

	}

}

// Sample A from A to B and resample B at A

void calculateSHBMode1(q31_t * phaseEvents, audioRateOutputs * output) {

	for (int i = 0; i < BUFFER_SIZE; i++) {

		switch (phaseEvents[i]) {
			//no logic events
			case 0:
				output->shBHandler[i] = SH_B_TRACK_MASK;
				break;
			//dummy at a handling
			case AT_A_FROM_RELEASE:
			case AT_A_FROM_ATTACK:
				output->shBHandler[i] = SH_B_TRACK_MASK;
				break;
			//dummy at b handling
			case AT_B_FROM_RELEASE:
			case AT_B_FROM_ATTACK:
				output->shBHandler[i] = SH_B_TRACK_MASK;
				break;
			default:
				break;
		}

	}

}

// Half Decimate (Sample A from A to B sample B from B to A

void calculateSHBMode2(q31_t * phaseEvents, audioRateOutputs * output) {

	for (int i = 0; i < BUFFER_SIZE; i++) {

		switch (phaseEvents[i]) {
			//no logic events
			case 0:
				output->shBHandler[i] = GPIO_NOP;
				break;
			//dummy at a handling
			case AT_A_FROM_RELEASE:
			case AT_A_FROM_ATTACK:
				output->shBHandler[i] = SH_B_TRACK_MASK;
				break;
			//dummy at b handling
			case AT_B_FROM_RELEASE:
			case AT_B_FROM_ATTACK:
				output->shBHandler[i] = SH_B_SAMPLE_MASK;
				break;
			default:
				break;
		}

	}

}

// Decimate (Resample A at B, resample B at A

void calculateSHBMode3(q31_t * phaseEvents, audioRateOutputs * output) {

	for (int i = 0; i < BUFFER_SIZE; i++) {

		switch (phaseEvents[i]) {
			//no logic events
			case 0:
				output->shBHandler[i] = SH_B_SAMPLE_MASK;
				break;
			//dummy at a handling
			case AT_A_FROM_RELEASE:
			case AT_A_FROM_ATTACK:
				output->shBHandler[i] = SH_B_TRACK_MASK;
				break;
			//dummy at b handling
			case AT_B_FROM_RELEASE:
			case AT_B_FROM_ATTACK:
				output->shBHandler[i] = SH_B_SAMPLE_MASK;
				break;
			default:
				break;
		}

	}

}


