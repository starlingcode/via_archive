/*
 * signals.h
 *
 *  Created on: Aug 1, 2018
 *      Author: willmitchell
 */

#ifndef SIGNALS_H_
#define SIGNALS_H_

#include "sync_dsp.h"

typedef struct {
	q31_t samples;
	q31_t dac3Sample;
	uint32_t shAHandler;
	uint32_t shBHandler;
	uint32_t logicAHandler;
	uint32_t auxLogicHandler;
} audioRateOutputs;

typedef struct {
	q31_t cv2Input;
	q31_t cv3Input;
	q31_t triggerInput;
	q31_t gateInput;
} audioRateInputs;

typedef struct {
	q31_t knob1Value;
	q31_t knob2Value;
	q31_t knob3Value;
	q31_t cv1Value;
} controlRateInputs;

typedef struct {
	uint32_t attackIncrement;
	uint32_t releaseIncrement;
	uint32_t periodCount;
	uint32_t gateOnCount;
	uint32_t pllReset;
	uint32_t phaseOffset;
	uint32_t tapTempo;
	uint32_t phaseSignal;
	uint32_t syncMode;
	uint32_t morphShift;
	Scale * scale;
} softwareSignaling;

typedef struct {
	audioRateOutputs * outputs;
	audioRateInputs * inputs;
	controlRateInputs * controls;
	softwareSignaling * softwareSignals;
} osc_signals;

controlRateInputs controlRateInput;
audioRateInputs audioRateInput;
audioRateOutputs audioRateOutput;
softwareSignaling softwareSignals;

controlRateInputs * controlRateInputAddress;
audioRateInputs * audioRateInputAddress;
audioRateOutputs * audioRateOutputAddress;
softwareSignaling * softwareSignalsAddress;

osc_signals signals;

static inline void viaSignalInit(void) {

	controlRateInputAddress = &controlRateInput;
	audioRateInputAddress = &audioRateInput;
	audioRateOutputAddress = &audioRateOutput;
	softwareSignalsAddress = &softwareSignals;

	signals.controls = controlRateInputAddress;
	signals.inputs = audioRateInputAddress;
	signals.outputs = audioRateOutputAddress;
	signals.softwareSignals = softwareSignalsAddress;

}

#endif /* INC_SIGNALS_H_ */
