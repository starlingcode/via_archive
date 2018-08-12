/*
 * signals.h
 *
 *  Created on: Aug 1, 2018
 *      Author: willmitchell
 */

#ifndef SIGNALS_H_
#define SIGNALS_H_

#include "osc_dsp.h"
#include "osc_tables.h"

// declare a struct to hold the audio rate outputs

typedef struct {
	q31_t *dac1Samples;
	q31_t *dac2Samples;
	q31_t *dac3Samples;
	uint32_t shAHandler;
	uint32_t shBHandler;
	uint32_t logicAHandler;
	uint32_t auxLogicHandler;
} audioRateOutputs;

// declare a struct to hold the audio rate inputs

typedef struct {
	q31_t cv2Input;
	q31_t cv3Input;
	q31_t mainLogicInput;
	q31_t auxLogicInnput;
} audioRateInputs;

typedef struct {
	q31_t knob1Value;
	q31_t knob2Value;
	q31_t knob3Value;
	q31_t cv1Value;
} controlRateInputs;

// declare a struct to hold the signals passed between functions

typedef struct {
	q31_t morphShift;
	q31_t syncMode;
	Family * currentFamily;
} softwareSignaling;

// allocate a DMA buffer for each oversampled output

q31_t dac1SampleBuffer[BUFFER_SIZE*2];
q31_t dac2SampleBuffer[BUFFER_SIZE*2];
q31_t dac3SampleBuffer[BUFFER_SIZE*2];

audioRateOutputs audioRateOutput;
audioRateInputs audioRateInput;
controlRateInputs controlRateInput;
softwareSignaling softwareSignals;

typedef struct {
	audioRateOutputs * outputs;
	audioRateInputs * inputs;
	controlRateInputs * controls;
	softwareSignaling * softwareSignals;
} viaSignals;

viaSignals signals;

void viaSignalInit(void);

#endif /* INC_SIGNALS_H_ */
