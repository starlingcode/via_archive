/*
 * sequencers.h
 *
 *  Created on: Aug 18, 2018
 *      Author: willmitchell
 */

#ifndef INC_SEQUENCERS_HPP_
#define INC_SEQUENCERS_HPP_

#include "via_platform_binding.hpp"
#include "boolean_sequences.hpp"

enum {
	// Dual soft gate (use crossfader as dual and gate with followed by mixing "or" stage)
	SOFT_GATE_EXECUTE,
	SOFT_GATE_HIGH,
	SOFT_GATE_LOW
};

/*
 *
 * Dual euclidean sequencer
 *
 */

class DualEuclidean {

	uint32_t aLength = 0;
	uint32_t bLength = 0;
	uint32_t aPatternMorph = 0;
	uint32_t bPatternMorph = 0;
	uint32_t offset = 0;
	uint32_t aPatternIndex = 0;
	uint32_t bPatternIndex = 0;

public:

	// "inputs"
	uint32_t aCounter = 0;
	uint32_t bCounter = 0;
	uint32_t sampleA = 0;
	uint32_t sampleB = 0;
	uint32_t trackA = 0;
	uint32_t trackB = 0;
	uint32_t andA = 0;
	uint32_t andB = 0;
	uint32_t gateAEvent = 0;
	uint32_t gateBEvent = 0;
	uint32_t auxLogicMode = 0;

	const dualBooleanSequence *currentABank;
	const dualBooleanSequence *currentBBank;

	// "outputs"
	uint32_t aOutput = 0;
	uint32_t bOutput = 0;
	uint32_t logicOutput = 0;

	uint32_t shASignal = 0;
	uint32_t shBSignal = 0;

	void processClock(void);
	void parseControls(ViaControls *, ViaInputStreams *);

};


/*
 *
 * Shared resources
 *
 */

class SoftGate {

	void gateAHigh(void);
	void gateALow(void);

	void gateARise(void);
	void gateAFall(void);

	void gateBHigh(void);
	void gateBLow(void);

	void gateBRise(void);
	void gateBFall(void);

	void (SoftGate::*manageGateA)(void);
	void (SoftGate::*manageGateB)(void);

	int gateA = 0;
	int gateB = 0;

public:

	int attackTimeA = 500;
	int releaseTimeA = 100;
	int attackTimeB = 500;
	int releaseTimeB = 100;

	int aSignal = 0;
	int bSignal = 0;

	int updateGateA(int signal);

	int updateGateB(int signal);

	SoftGate(void) {
		manageGateA = &SoftGate::gateALow;
		manageGateB = &SoftGate::gateBLow;
	}

};


#endif /* INC_SEQUENCERS_HPP_ */
