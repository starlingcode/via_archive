#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"
#include "signals.h"
#include "via_rev5_hardware_io.h"
#include "../inc/meta_dsp.h"
#include "../inc/meta_fill_buffer.h"


/*
 *
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

void calculateDac3Phasor(q31_t * phase, audioRateOutputs * output) {

	for (int i = 0; i < BUFFER_SIZE; i++) {

		if (phase[i] >> 24) {
			output->dac3Samples[i] = 8191 - (phase[i] >> 12);
		} else {
			output->dac3Samples[i] = phase[i] >> 12;
		}
	}

}

void calculateDac3Contour(q31_t * phase, audioRateOutputs * output) {

	for (int i = 0; i < BUFFER_SIZE; i++) {

			output->dac3Samples[i] = output->samples[i];

	}

}



// No S&H

void calculateSHMode1(q31_t * phaseEvents, audioRateOutputs * output) {

	for (int i = 0; i < BUFFER_SIZE; i++) {

		switch (phaseEvents[i]) {
			//no logic events
			case 0:
				output->shAHandler[i] = SH_A_TRACK_MASK;
				output->shBHandler[i] = SH_B_TRACK_MASK;
				break;
			//dummy at a handling
			case AT_A_FROM_RELEASE:
			case AT_A_FROM_ATTACK:
				output->shAHandler[i] = SH_A_TRACK_MASK;
				output->shBHandler[i] = SH_B_TRACK_MASK;
				break;
			//dummy at b handling
			case AT_B_FROM_RELEASE:
			case AT_B_FROM_ATTACK:
				output->shAHandler[i] = SH_A_TRACK_MASK;
				output->shBHandler[i] = SH_B_TRACK_MASK;
				break;
			default:
				break;
		}

	}

}

// Sample A from A to B

void calculateSHMode2(q31_t * phaseEvents, audioRateOutputs * output) {

	for (int i = 0; i < BUFFER_SIZE; i++) {

		switch (phaseEvents[i]) {
			//no logic events
			case 0:
				output->shAHandler[i] = GPIO_NOP;
				output->shBHandler[i] = SH_B_TRACK_MASK;
				break;
			//dummy at a handling
			case AT_A_FROM_RELEASE:
			case AT_A_FROM_ATTACK:
				output->shAHandler[i] = SH_A_SAMPLE_MASK;
				output->shBHandler[i] = SH_B_TRACK_MASK;
				break;
			//dummy at b handling
			case AT_B_FROM_RELEASE:
			case AT_B_FROM_ATTACK:
				output->shAHandler[i] = SH_A_TRACK_MASK;
				output->shBHandler[i] = SH_B_TRACK_MASK;
				break;
			default:
				break;
		}

	}

}

// Resample B at A

void calculateSHMode3(q31_t * phaseEvents, audioRateOutputs * output) {

	for (int i = 0; i < BUFFER_SIZE; i++) {

		switch (phaseEvents[i]) {
			//no logic events
			case 0:
				output->shAHandler[i] = SH_A_TRACK_MASK;
				output->shBHandler[i] = SH_B_SAMPLE_MASK;
				break;
			//dummy at a handling
			case AT_A_FROM_RELEASE:
			case AT_A_FROM_ATTACK:
				output->shAHandler[i] = SH_A_SAMPLE_MASK;
				output->shBHandler[i] = SH_B_TRACK_MASK;
				break;
			//dummy at b handling
			case AT_B_FROM_RELEASE:
			case AT_B_FROM_ATTACK:
				output->shAHandler[i] = SH_A_TRACK_MASK;
				output->shBHandler[i] = SH_B_SAMPLE_MASK;
				break;
			default:
				break;
		}

	}

}

// Sample A from A to B and resample B at A

void calculateSHMode4(q31_t * phaseEvents, audioRateOutputs * output) {

	for (int i = 0; i < BUFFER_SIZE; i++) {

		switch (phaseEvents[i]) {
			//no logic events
			case 0:
				output->shAHandler[i] = GPIO_NOP;
				output->shBHandler[i] = SH_B_SAMPLE_MASK;
				break;
			//dummy at a handling
			case AT_A_FROM_RELEASE:
			case AT_A_FROM_ATTACK:
				output->shAHandler[i] = SH_A_SAMPLE_MASK;
				output->shBHandler[i] = SH_B_TRACK_MASK;
				break;
			//dummy at b handling
			case AT_B_FROM_RELEASE:
			case AT_B_FROM_ATTACK:
				output->shAHandler[i] = SH_A_TRACK_MASK;
				output->shBHandler[i] = SH_B_SAMPLE_MASK;
				break;
			default:
				break;
		}

	}

}

// Half Decimate (Sample A from A to B sample B from B to A

void calculateSHMode5(q31_t * phaseEvents, audioRateOutputs * output) {

	for (int i = 0; i < BUFFER_SIZE; i++) {

		switch (phaseEvents[i]) {
			//no logic events
			case 0:
				output->shAHandler[i] = GPIO_NOP;
				output->shBHandler[i] = GPIO_NOP;
				break;
			//dummy at a handling
			case AT_A_FROM_RELEASE:
			case AT_A_FROM_ATTACK:
				output->shAHandler[i] = SH_A_SAMPLE_MASK;
				output->shBHandler[i] = SH_B_TRACK_MASK;
				break;
			//dummy at b handling
			case AT_B_FROM_RELEASE:
			case AT_B_FROM_ATTACK:
				output->shAHandler[i] = SH_A_TRACK_MASK;
				output->shBHandler[i] = SH_B_SAMPLE_MASK;
				break;
			default:
				break;
		}

	}

}

// Decimate (Resample A at B, resample B at A

void calculateSHMode6(q31_t * phaseEvents, audioRateOutputs * output) {

	for (int i = 0; i < BUFFER_SIZE; i++) {

		switch (phaseEvents[i]) {
			//no logic events
			case 0:
				output->shAHandler[i] = SH_A_SAMPLE_MASK;
				output->shBHandler[i] = SH_B_SAMPLE_MASK;
				break;
			//dummy at a handling
			case AT_A_FROM_RELEASE:
			case AT_A_FROM_ATTACK:
				output->shAHandler[i] = SH_A_SAMPLE_MASK;
				output->shBHandler[i] = SH_B_TRACK_MASK;
				break;
			//dummy at b handling
			case AT_B_FROM_RELEASE:
			case AT_B_FROM_ATTACK:
				output->shAHandler[i] = SH_A_TRACK_MASK;
				output->shBHandler[i] = SH_B_SAMPLE_MASK;
				break;
			default:
				break;
		}

	}

}
