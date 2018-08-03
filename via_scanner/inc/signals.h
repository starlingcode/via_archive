/*
 * signals.h
 *
 *  Created on: Aug 1, 2018
 *      Author: willmitchell
 */

#ifndef SIGNALS_H_
#define SIGNALS_H_

#include "scanner_dsp.h"
#include "scanner_tables.h"

// declare a struct to hold the audio rate outputs

typedef struct {
	q31_t *samples;
	q31_t *dac3Samples;
	uint32_t *shAHandler;
	uint32_t *shBHandler;
	uint32_t *logicAHandler;
	uint32_t *auxLogicHandler;
} audioRateOutputs;

// declare a struct to hold the audio rate inputs

typedef struct {
	q31_t *cv2Input;
	q31_t *cv3Input;
	q31_t * syncBuffer;
} audioRateInputs;

// declare a struct to hold the signals passed between functions

typedef struct {
	q31_t syncSignal;
	q31_t morphShift;
	q31_t terrainType;
	q31_t syncMode;
	Family * xTable;
	Family * yTable;
} softwareSignaling;

// allocate a pair of buffers for each member of the above structs

// outputs

q31_t sampleBuffer1[BUFFER_SIZE];
q31_t sampleBuffer2[BUFFER_SIZE];

q31_t dac3SampleBuffer1[BUFFER_SIZE];
q31_t dac3SampleBuffer2[BUFFER_SIZE];

uint32_t shABuffer1[BUFFER_SIZE];
uint32_t shABuffer2[BUFFER_SIZE];

uint32_t shBBuffer1[BUFFER_SIZE];
uint32_t shBBuffer2[BUFFER_SIZE];

uint32_t logicABuffer1[BUFFER_SIZE];
uint32_t logicABuffer2[BUFFER_SIZE];

uint32_t auxLogicBuffer1[BUFFER_SIZE];
uint32_t auxLogicBuffer2[BUFFER_SIZE];

// inputs

q31_t t2CVBuffer1[BUFFER_SIZE];
q31_t t2CVBuffer2[BUFFER_SIZE];

q31_t morphCVBuffer1[BUFFER_SIZE];
q31_t morphCVBuffer2[BUFFER_SIZE];

// software signals

uint32_t syncBuffer1[BUFFER_SIZE];
uint32_t syncBuffer2[BUFFER_SIZE];

// create a pair each of input and output structs
// a pair of pointers can be found in the signals typedef

audioRateOutputs output1;
audioRateOutputs output2;

audioRateInputs input1;
audioRateInputs input2;

typedef struct {
	q31_t knob1Value;
	q31_t knob2Value;
	q31_t knob3Value;
	q31_t cv1Value;
} controlRateInputs;

controlRateInputs controlRateInput;

typedef struct {
	audioRateOutputs * outputRead;
	audioRateOutputs * outputWrite;
	audioRateInputs * inputRead;
	audioRateInputs * inputWrite;
	controlRateInputs * controls;
	softwareSignaling * softwareSignals;
} viaSignals;

controlRateInputs controlRateInput;
audioRateInputs audioRateInput;
audioRateOutputs audioRateOutput;
softwareSignaling softwareSignals;

viaSignals signals;

void viaSignalInit(void);

#endif /* INC_SIGNALS_H_ */
