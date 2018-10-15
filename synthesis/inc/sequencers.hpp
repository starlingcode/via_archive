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

	uint32_t aLength = 1;
	uint32_t bLength = 1;
	uint32_t aPatternMorph = 0;
	uint32_t bPatternMorph = 0;
	uint32_t offset = 0;
	uint32_t aPatternIndex = 0;
	uint32_t bPatternIndex = 0;

public:

	uint32_t periodCount;
	uint32_t multiplier = 3;
	uint32_t divider = 1;
	uint32_t auxTimerRisingEdge;

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
	void advanceSequencerA(void);
	void advanceSequencerB(void);
	void updateLogicOutput(void);
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

	int32_t gateA = 0;
	int32_t gateB = 0;

public:

	int32_t attackTimeA = 500;
	int32_t releaseTimeA = 100;
	int32_t attackTimeB = 500;
	int32_t releaseTimeB = 100;

	int32_t aSignal = 0;
	int32_t bSignal = 0;

	int32_t updateGateA(int32_t signal);

	int32_t updateGateB(int32_t signal);

	SoftGate(void) {
		manageGateA = &SoftGate::gateALow;
		manageGateB = &SoftGate::gateBLow;
	}

};


#endif /* INC_SEQUENCERS_HPP_ */
