/*
 * sequencers_shared_resources.c
 *
 *  Created on: Aug 21, 2018
 *      Author: willmitchell
 */

#include "sequencers.h"

/*
 *
 * Dual soft gate
 * (it seems a bit strange to do this with two groups of functions,
 * better to pass in a function pointer and use one each of the duplicated functions?)
 *
 */

void outputAHigh(int signal, int writePosition, audioRateOutputs * output) {

	int *outputLevel = output->dac1Samples + writePosition;

	switch (signal) {
	case SOFT_GATE_EXECUTE:
		*outputLevel = 4095;
		break;
	case SOFT_GATE_LOW:
		*outputLevel = 4095;
		manageOutputA = outputAFall;
		break;
	default:
		break;
	}
}
void outputALow(int signal, int writePosition, audioRateOutputs * output) {

	int *outputLevel = output->dac1Samples + writePosition;

	switch (signal) {
	case SOFT_GATE_EXECUTE:
		*outputLevel = 0;
		break;
	case SOFT_GATE_HIGH:
		*outputLevel = 0;
		manageOutputA = outputARise;
		break;
	default:
		break;
	}
}

void outputBHigh(int signal, int writePosition, audioRateOutputs * output) {

	int *outputLevel = output->dac2Samples + writePosition;

	switch (signal) {
	case SOFT_GATE_EXECUTE:
		*outputLevel = 4095;
		break;
	case SOFT_GATE_LOW:
		*outputLevel = 4095;
		manageOutputB = outputBFall;
		break;
	default:
		break;
	}
}
void outputBLow(int signal, int writePosition, audioRateOutputs * output) {

	int *outputLevel = output->dac2Samples + writePosition;

	switch (signal) {
	case SOFT_GATE_EXECUTE:
		*outputLevel = 0;
		break;
	case SOFT_GATE_HIGH:
		*outputLevel = 0;
		manageOutputB = outputBRise;
		break;
	default:
		break;
	}
}

void outputARise(int signal, int writePosition, audioRateOutputs * output) {

	int *outputLevel = output->dac1Samples + writePosition;

	switch (signal) {
	case SOFT_GATE_EXECUTE:
		*outputLevel += 50;
		if (*outputLevel >= 4095) {
			*outputLevel = 4095;
			manageOutputA = outputAHigh;
		}
		break;
	case SOFT_GATE_LOW:
		manageOutputA = outputAFall;
		break;
	default:
		break;
	}
}
void outputAFall(int signal, int writePosition, audioRateOutputs * output) {

	int *outputLevel = output->dac1Samples + writePosition;

	switch (signal) {
	case SOFT_GATE_EXECUTE:
		*outputLevel -= 50;
		if (*outputLevel <= 0) {
			*outputLevel = 0;
			manageOutputA = outputALow;
		}
		break;
	case SOFT_GATE_HIGH:
		manageOutputA = outputARise;
		break;
	default:
		break;
	}
}

void outputBRise(int signal, int writePosition, audioRateOutputs * output) {

	int *outputLevel = output->dac2Samples + writePosition;

	switch (signal) {
	case SOFT_GATE_EXECUTE:
		*outputLevel += 50;
		if (*outputLevel >= 4095) {
			*outputLevel = 4095;
			manageOutputB = outputBHigh;
		}
		break;
	case SOFT_GATE_LOW:
		manageOutputB = outputBFall;
		break;
	default:
		break;
	}
}
void outputBFall(int signal, int writePosition, audioRateOutputs * output) {

	int *outputLevel = output->dac2Samples + writePosition;

	switch (signal) {
	case SOFT_GATE_EXECUTE:
		*outputLevel -= 50;
		if (*outputLevel <= 0) {
			*outputLevel = 0;
			manageOutputB = outputBLow;
		}
		break;
	case SOFT_GATE_HIGH:
		manageOutputB = outputBRise;
	}
}

