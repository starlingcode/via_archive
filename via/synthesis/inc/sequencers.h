/*
 * sequencers.h
 *
 *  Created on: Aug 18, 2018
 *      Author: willmitchell
 */

#ifndef INC_SEQUENCERS_H_
#define INC_SEQUENCERS_H_

#include "via_platform_binding.h"
#include "boolean_sequences.h"

/*
 *
 * Dual euclidean sequencer
 *
 */

typedef struct {

	// "inputs"
	uint32_t aCounter;
	uint32_t bCounter;
	uint32_t sampleA;
	uint32_t sampleB;
	uint32_t trackA;
	uint32_t trackB;
	uint32_t andA;
	uint32_t andB;
	uint32_t outputAEvent;
	uint32_t outputBEvent;
	uint32_t auxLogicMode;
	dualBooleanSequence *currentABank;
	dualBooleanSequence *currentBBank;

	// "outputs"
	uint32_t aOutput;
	uint32_t bOutput;
	uint32_t logicOutput;

} dualEuclideanParameters;

void dualEuclideanProcessClock(controlRateInputs *, audioRateInputs *,
		dualEuclideanParameters *);

/*
 *
 * Shared resources
 *
 */

// Dual soft gate (use crossfader as dual and gate with followed by mixing "or" stage)
#define	SOFT_GATE_HIGH 0
#define	SOFT_GATE_LOW 1
#define SOFT_GATE_EXECUTE 2

void (*manageOutputA)(int * signal, int writePosition,
		audioRateOutputs * outputs);
void (*manageOutputB)(int * signal, int writePosition,
		audioRateOutputs * outputs);

void outputAHigh(int signal, int writePosition, audioRateOutputs * outputs);
void outputALow(int signal, int writePosition, audioRateOutputs * outputs);

void outputARise(int signal, int writePosition, audioRateOutputs * outputs);
void outputAFall(int signal, int writePosition, audioRateOutputs * outputs);

void outputBHigh(int signal, int writePosition, audioRateOutputs * outputs);
void outputBLow(int signal, int writePosition, audioRateOutputs * outputs);

void outputBRise(int signal, int writePosition, audioRateOutputs * outputs);
void outputBFall(int signal, int writePosition, audioRateOutputs * outputs);

#endif /* INC_SEQUENCERS_H_ */
