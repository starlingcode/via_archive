/*
 * via_global_signals.h
 *
 *  Created on: Aug 21, 2018
 *      Author: willmitchell
 */

#ifndef INC_VIA_GLOBAL_SIGNALS_H_
#define INC_VIA_GLOBAL_SIGNALS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "dsp.h"

// declare a struct to hold the control rate inputs

typedef struct {

	uint32_t knob1Value;
	uint32_t knob2Value;
	uint32_t knob3Value;
	uint32_t cv1Value;

	uint32_t knob1Sum;
	uint32_t knob2Sum;
	uint32_t knob3Sum;
	uint32_t cv1Sum;

	buffer knob1Buffer;
	buffer knob2Buffer;
	buffer knob3Buffer;
	buffer cv1Buffer;

} controlRateInputs;

// declare a struct to point to the audio rate inputs

typedef struct {
	int16_t * cv2Samples;
	int16_t * cv3Samples;
	int16_t * cv2VirtualGround;
	int16_t * cv3VirtualGround;
	int * trigSamples;
	int trigInput;
	int * auxTrigSamples;
	int auxTrigInput;
} audioRateInputs;

// declare a struct to point to the audio rate outputs

typedef struct {
	uint32_t * dac1Samples;
	uint32_t * dac2Samples;
	uint32_t * dac3Samples;
	uint32_t * shA;
	uint32_t * shB;
	uint32_t * logicA;
	uint32_t * auxLogic;
} audioRateOutputs;

controlRateInputs controlRateInput;
audioRateInputs audioRateInput;
audioRateOutputs audioRateOutput;

#ifdef __cplusplus
}
#endif


#endif /* INC_VIA_GLOBAL_SIGNALS_H_ */
