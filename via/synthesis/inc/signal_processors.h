/*
 * signal_processors.h
 *
 *  Created on: Aug 18, 2018
 *      Author: willmitchell
 */

#ifndef INC_SIGNAL_PROCESSORS_H_
#define INC_SIGNAL_PROCESSORS_H_

#include "via_platform_binding.h"
#include "tables.h"
#include "dsp.h"

/*
 *
 * Three axis scanner
 *
 */

typedef struct {

	int xInput[8];
	int yInput[8];

	// logic input
	uint32_t syncInput;
	uint32_t auxTrigInput;

	//control rate input
	uint32_t zIndex;

	// mode parameters
	uint32_t terrainType;
	uint32_t syncMode;
	uint32_t xTableSize;
	uint32_t yTableSize;

} threeAxisScannerParameters;

void threeAxisScannerFillBuffer(audioRateInputs * inputs,
		controlRateInputs * controls, threeAxisScannerParameters * parameters,
		int * xTable, int * yTable,
		audioRateOutputs * outputs, uint32_t writePosition, uint32_t bufferSize);

void threeAxisScannerParseControls(controlRateInputs * controls,
		threeAxisScannerParameters * parameters);

#define THREE_AXIS_SCANNER_SUM 0
#define THREE_AXIS_SCANNER_PRODUCT 1
#define THREE_AXIS_SCANNER_DIFFERENCE 2
#define THREE_AXIS_SCANNER_PHASE_MOD 3


/*
 *
 * Shared resources
 *
 */

void foldBuffer(int * input, int offset, int * output, uint32_t bufferSize);
void wrapBuffer(int * input, int offset, int * output, uint32_t bufferSize);

#endif /* INC_SIGNAL_PROCESSORS_H_ */
