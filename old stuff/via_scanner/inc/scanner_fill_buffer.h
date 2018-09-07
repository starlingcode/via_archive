/*
 * scanner_fill_buffer.h
 *
 *  Created on: Aug 2, 2018
 *      Author: willmitchell
 */

#ifndef INC_SCANNER_FILL_BUFFER_H_
#define INC_SCANNER_FILL_BUFFER_H_

#include "signals.h"

// function calling subfunctions to fill the sample buffer

void fillBuffer(osc_signal_set *);

// pointer to the function that calculates samples and phase events

void foldBuffer(q31_t *, q31_t, q31_t *);
void wrapBuffer(q31_t *, q31_t, q31_t *);

void scanTerrainProduct(q31_t *, q31_t *, int *, int, q31_t *);
void scanTerrainSum(q31_t *, q31_t *, int *, int, q31_t *);
void scanTerrainSubtract(q31_t * xIndexArray, q31_t * yIndexArray, int * reverseArray, int zIndex, q31_t * output);
void scanTerrainPM(q31_t * xIndexArray, q31_t * yIndexArray, int * reverseArray, int zIndex, q31_t * output);

void (*logicAndFilter)(uint32_t *, audioRateOutputs *);

// parse the phase events into logic outputs and filter according to the S&H mode

void logicAndFilterSHOn(uint32_t *, audioRateOutputs *);
void logicAndFilterSHOff(uint32_t *, audioRateOutputs *);

// logic output helper functions

void logicInit(void);
void logicNoOp(void);

#endif /* INC_SCANNER_FILL_BUFFER_H_ */
