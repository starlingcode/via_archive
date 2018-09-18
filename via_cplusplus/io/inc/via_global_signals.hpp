/*
 * via_global_signals.h
 *
 *  Created on: Aug 21, 2018
 *      Author: willmitchell
 */

#ifndef INC_VIA_GLOBAL_SIGNALS_HPP_
#define INC_VIA_GLOBAL_SIGNALS_HPP_

#include "dsp.hpp"
#include "f373_rev6_io.hpp"
#include <stdlib.h>

// declare a struct to hold the control rate inputs

class ViaControls {

	uint32_t knob1Sum = 0;
	uint32_t knob2Sum = 0;
	uint32_t knob3Sum = 0;
	uint32_t cv1Sum = 0;

	buffer knob1Buffer;
	buffer knob2Buffer;
	buffer knob3Buffer;
	buffer cv1Buffer;

#define knob2 controlRateInputs[3]
#define knob3 controlRateInputs[1]
#define knob1 controlRateInputs[2]
#define cv1 (4095 - controlRateInputs[0])

public:

	ViaControls() {

		for (int i = 0; i < 32; i++) {
			writeBuffer(&cv1Buffer, 0);
			writeBuffer(&knob1Buffer, 0);
			writeBuffer(&knob2Buffer, 0);
			writeBuffer(&knob3Buffer, 0);
		}

	}

	uint32_t controlRateInputs[4];

	uint32_t knob1Value = 0;
	uint32_t knob2Value = 0;
	uint32_t knob3Value = 0;
	uint32_t cv1Value = 0;

	void update(void);

};


// declare a struct to point to the audio rate inputs

class ViaInputStreams {

public:
	int16_t * cv2Samples;
	int16_t * cv3Samples;
	int16_t * cv2VirtualGround;
	int16_t * cv3VirtualGround;
	int * trigSamples;
	int trigInput;
	int * auxTrigSamples;
	int auxTrigInput;

	int bufferSize;

	void init(int size) {

		bufferSize = size;

		trigInput = 1;
		auxTrigInput = 1;

		cv2Samples = (int16_t*) malloc(2 * bufferSize * sizeof(int));
		cv3Samples = (int16_t*) malloc(2 * bufferSize * sizeof(int));
		cv2VirtualGround = (int16_t*) malloc(2 * bufferSize * sizeof(int));
		cv3VirtualGround = (int16_t*) malloc(2 * bufferSize * sizeof(int));

		trigSamples = (int*) malloc(2 * bufferSize * sizeof(int));
		auxTrigSamples = (int*) malloc(2 * bufferSize * sizeof(int));

	}

};

// declare a struct to point to the audio rate outputs

class ViaOutputStreams {
public:
	uint32_t * dac1Samples;
	uint32_t * dac2Samples;
	uint32_t * dac3Samples;
	uint32_t * shA;
	uint32_t * shB;
	uint32_t * logicA;
	uint32_t * auxLogic;

	int bufferSize;

	void init(int size) {

		bufferSize = size;

		dac1Samples = (uint32_t*) malloc(2 * bufferSize * sizeof(int));
		dac2Samples = (uint32_t*) malloc(2 * bufferSize * sizeof(int));
		dac3Samples = (uint32_t*) malloc(2 * bufferSize * sizeof(int));

		shA = (uint32_t*) malloc(2 * bufferSize * sizeof(int));
		shB = (uint32_t*) malloc(2 * bufferSize * sizeof(int));
		logicA = (uint32_t*) malloc(2 * bufferSize * sizeof(int));
		auxLogic = (uint32_t*) malloc(2 * bufferSize * sizeof(int));

	}



};

class ViaModule {
public:
	ViaControls controls;

	int bufferSize;

	ViaInputStreams inputs;
	ViaOutputStreams outputs;

	void ioStreamInit(void);

	void setLogicOut(int writeIndex, int runtimeDisplay) {

		if (runtimeDisplay) {
			setLogicOutputsLEDOn(outputs.logicA[writeIndex],
					outputs.auxLogic[writeIndex], outputs.shA[writeIndex], outputs.shB[writeIndex]);
		} else {
			setLogicOutputsLEDOff(outputs.logicA[writeIndex],
					outputs.auxLogic[writeIndex], outputs.shA[writeIndex], outputs.shB[writeIndex]);
		}

	}

};


#endif /* INC_VIA_GLOBAL_SIGNALS_HPP_ */
