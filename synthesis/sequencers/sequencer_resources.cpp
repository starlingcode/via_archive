/*
 * sequencers_shared_resources.c
 *
 *  Created on: Aug 21, 2018
 *      Author: willmitchell
 */

#include "sequencers.hpp"

/*
 *
 * Dual soft gate
 *
 */


int32_t SoftGate::updateGateA(int32_t signal) {
	aSignal = signal;
	(this->*manageGateA)();
	return gateA;
}

int32_t SoftGate::updateGateB(int32_t signal) {
	bSignal = signal;
	(this->*manageGateB)();
	return gateB;
}


void SoftGate::gateAHigh(void) {

	switch (aSignal) {
	case SOFT_GATE_EXECUTE:
		gateA = 4095;
		break;
	case SOFT_GATE_LOW:
		gateA = 4095;
		manageGateA = &SoftGate::gateAFall;
		break;
	default:
		break;
	}
}
void SoftGate::gateALow(void) {

	switch (aSignal) {
	case SOFT_GATE_EXECUTE:
		gateA = 0;
		break;
	case SOFT_GATE_HIGH:
		gateA = 0;
		manageGateA = &SoftGate::gateARise;
		break;
	default:
		break;
	}
}

void SoftGate::gateBHigh(void) {

	switch (bSignal) {
	case SOFT_GATE_EXECUTE:
		gateB = 4095;
		break;
	case SOFT_GATE_LOW:
		gateB = 4095;
		manageGateB = &SoftGate::gateBFall;
		break;
	default:
		break;
	}
}
void SoftGate::gateBLow(void) {

	switch (bSignal) {
	case SOFT_GATE_EXECUTE:
		gateB = 0;
		break;
	case SOFT_GATE_HIGH:
		gateB = 0;
		manageGateB = &SoftGate::gateBRise;
		break;
	default:
		break;
	}
}

void SoftGate::gateARise(void) {

	switch (aSignal) {
	case SOFT_GATE_EXECUTE:
		gateA += attackTimeA;
		if (gateA >= 4095) {
			gateA = 4095;
			manageGateA = &SoftGate::gateAHigh;
		}
		break;
	case SOFT_GATE_LOW:
		manageGateA = &SoftGate::gateAFall;
		break;
	default:
		break;
	}
}
void SoftGate::gateAFall(void) {

	switch (aSignal) {
	case SOFT_GATE_EXECUTE:
		gateA -= releaseTimeA;
		if (gateA <= 0) {
			gateA = 0;
			manageGateA = &SoftGate::gateALow;
		}
		break;
	case SOFT_GATE_HIGH:
		manageGateA = &SoftGate::gateARise;
		break;
	default:
		break;
	}
}

void SoftGate::gateBRise(void) {

	switch (bSignal) {
	case SOFT_GATE_EXECUTE:
		gateB += attackTimeB;
		if (gateB >= 4095) {
			gateB = 4095;
			manageGateB = &SoftGate::gateBHigh;
		}
		break;
	case SOFT_GATE_LOW:
		manageGateB = &SoftGate::gateBFall;
		break;
	default:
		break;
	}
}
void SoftGate::gateBFall(void) {

	switch (bSignal) {
	case SOFT_GATE_EXECUTE:
		gateB -= releaseTimeB;
		if (gateB <= 0) {
			gateB = 0;
			manageGateB = &SoftGate::gateBLow;
		}
		break;
	case SOFT_GATE_HIGH:
		manageGateB = &SoftGate::gateBRise;
	}
}
