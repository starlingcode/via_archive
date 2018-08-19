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
#include "via_io_binding.h"

// declare a struct to hold the signals passed between functions

typedef struct {
	int16_t * fm;
	int16_t * pm;
	int16_t * pwm;
	int16_t * morphMod;
	int syncInput;
	int reverseInput;
	int frequencyBase;
	int pmBase;
	int pwmBase;
	int morphBase;
	int morphMultiplier;
	int syncMode;
	Family * currentFamily;
} softwareSignaling;

softwareSignaling softwareSignals;

// declare and initialize a struct to contain those

typedef struct {
	audioRateOutputs * outputs;
	audioRateInputs * inputs;
	controlRateInputs * controls;
	softwareSignaling * softwareSignals;
} viaSignals;

viaSignals signals;

#endif /* INC_SIGNALS_H_ */
