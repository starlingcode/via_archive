/*
 * scanner_fill_buffer.h
 *
 *  Created on: Aug 2, 2018
 *      Author: willmitchell
 */

#ifndef INC_OSC_FILL_BUFFER_H_
#define INC_OSC_FILL_BUFFER_H_

#include "signals.h"

// function calling subfunctions to fill the sample buffer

void fillBuffer(viaSignals *);

// pointer to the function that calculates samples and phase events

void (*prepareCV)(audioRateInputs *, controlRateInputs *, q31_t *, q31_t *, q31_t *, q31_t *);

void prepareCV_FM_Morph(audioRateInputs *, controlRateInputs *, q31_t *, q31_t *, q31_t *, q31_t *);
void prepareCV_PM_Morph(audioRateInputs *, controlRateInputs *, q31_t *, q31_t *, q31_t *, q31_t *);
void prepareCV_FM_PWM(audioRateInputs *, controlRateInputs *, q31_t *, q31_t *, q31_t *, q31_t *);
void prepareCV_PM_PWM(audioRateInputs *, controlRateInputs *, q31_t *, q31_t *, q31_t *, q31_t *);

void incrementOscillator(q31_t * , q31_t *, q31_t *, q31_t *, q31_t *, q31_t *, q31_t *, int *, q31_t *);

// TODO change name

void (*logicAndFilter)(uint32_t *, audioRateOutputs *);

// parse the phase events into logic outputs and filter according to the S&H mode

void logicAndFilterSHOn(uint32_t *, audioRateOutputs *);
void logicAndFilterSHOff(uint32_t *, audioRateOutputs *);

void initializeVirtualGround(void);



#endif /* INC_OSC_FILL_BUFFER_H_ */
