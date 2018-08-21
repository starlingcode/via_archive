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

void parseControls(controlRateInputs * controls);
void renderBuffer0(osc_signals * signals);
void renderBuffer1(osc_signals * signals);

#endif /* INC_OSC_FILL_BUFFER_H_ */
