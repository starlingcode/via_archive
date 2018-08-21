/*
 * signals.h
 *
 *  Created on: Aug 1, 2018
 *      Author: willmitchell
 */

#ifndef SIGNALS_H_
#define SIGNALS_H_

#include "oscillators.h"
#include "via_io_binding.h"

// declare a struct to hold the signals passed between functions

typedef struct {
	Wavetable * selectedTable;
} softwareSignaling;

softwareSignaling softwareSignals;
oversampledWavetableParameters oscParameters;

// declare and initialize a struct to contain those

typedef struct {
	audioRateOutputs * outputs;
	audioRateInputs * inputs;
	controlRateInputs * controls;
	oversampledWavetableParameters * parameters;
	softwareSignaling * softwareSignals;
} viaSignals;

viaSignals signals;

#define OSC_BUFFER_SIZE 16

#endif /* INC_SIGNALS_H_ */
