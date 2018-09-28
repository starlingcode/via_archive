/*
 * via_global_signals.h
 *
 *  Created on: Aug 21, 2018
 *      Author: willmitchell
 */

#ifndef INC_VIA_GLOBAL_SIGNALS_HPP_
#define INC_VIA_GLOBAL_SIGNALS_HPP_

#include <stdlib.h>
#include "dsp.hpp"

// declare a struct to hold the control rate inputs

class ViaControls {

	// uint32_t knob1Sum = 0;
	// uint32_t knob2Sum = 0;
	// uint32_t knob3Sum = 0;
	// uint32_t cv1Sum = 0;

	// buffer knob1Buffer;
	// buffer knob2Buffer;
	// buffer knob3Buffer;
	// buffer cv1Buffer;

#define knob2 controlRateInputs[3]
#define knob3 controlRateInputs[1]
#define knob1 controlRateInputs[2]
#define cv1 (4095 - controlRateInputs[0])

public:

	uint32_t knob1Sum = 0;
	uint32_t knob2Sum = 0;
	uint32_t knob3Sum = 0;
	uint32_t cv1Sum = 0;

	buffer knob1Buffer;
	buffer knob2Buffer;
	buffer knob3Buffer;
	buffer cv1Buffer;

	ViaControls() {

		for (int32_t i = 0; i < 32; i++) {
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
	int32_t * trigSamples;
	int32_t trigInput;
	int32_t * auxTrigSamples;
	int32_t auxTrigInput;

	int32_t bufferSize;

	void init(int32_t size) {

		bufferSize = size;

		trigInput = 1;
		auxTrigInput = 1;

		cv2Samples = (int16_t*) malloc(2 * bufferSize * sizeof(int32_t));
		cv3Samples = (int16_t*) malloc(2 * bufferSize * sizeof(int32_t));
		cv2VirtualGround = (int16_t*) malloc(2 * bufferSize * sizeof(int32_t));
		cv3VirtualGround = (int16_t*) malloc(2 * bufferSize * sizeof(int32_t));

		trigSamples = (int32_t*) malloc(2 * bufferSize * sizeof(int32_t));
		auxTrigSamples = (int32_t*) malloc(2 * bufferSize * sizeof(int32_t));

		for (int32_t i = 0; i < bufferSize; i++) {

			cv2Samples[i] = 0;
			cv3Samples[i] = 0;
			cv2VirtualGround[i] = 0;
			cv3VirtualGround[i] = 0;

			trigSamples[i] = 0;
			auxTrigSamples[i] = 0;

		}

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

	int32_t bufferSize;

	void init(int32_t size) {

		bufferSize = size;

		dac1Samples = (uint32_t*) malloc(2 * bufferSize * sizeof(int32_t));
		dac2Samples = (uint32_t*) malloc(2 * bufferSize * sizeof(int32_t));
		dac3Samples = (uint32_t*) malloc(2 * bufferSize * sizeof(int32_t));

		shA = (uint32_t*) malloc(2 * bufferSize * sizeof(int32_t));
		shB = (uint32_t*) malloc(2 * bufferSize * sizeof(int32_t));
		logicA = (uint32_t*) malloc(2 * bufferSize * sizeof(int32_t));
		auxLogic = (uint32_t*) malloc(2 * bufferSize * sizeof(int32_t));

		for (int32_t i = 0; i < bufferSize; i++) {
			dac1Samples[i] = 0;
			dac2Samples[i] = 0;
			dac3Samples[i] = 0;

			shA[i] = 0;
			shB[i] = 0;
			logicA[i] = 0;
			auxLogic[i] = 0;
		}

	}

};

typedef struct {
	int32_t r;
	int32_t b;
	int32_t g;
} rgb;

// shortcuts for commonly used colors as macro defines of rgb struct values
#define __RED {4095, 0, 0}
#define __GREEN {0, 4095, 0}
#define __BLUE {0, 0, 4095}
#define __ORANGE {4095, 4095, 0}
#define __MAGENTA {4095, 0, 4095}
#define __CYAN {0, 4095, 4095}

// used for software implementations

class ViaVirtualHardware {
public:
	uint32_t aLogic = 0;
	uint32_t auxLogic = 0;
	uint32_t shA = 0;
	uint32_t shB = 0;

	uint32_t red = 0;
	uint32_t green = 0;
	uint32_t blue = 0;

	uint32_t ledA = 0;
	uint32_t ledB = 0;
	uint32_t ledC = 0;
	uint32_t ledD = 0;

	int32_t button1 = 0;
	int32_t button2 = 0;
	int32_t button3 = 0;
	int32_t button4 = 0;
	int32_t button5 = 0;
	int32_t button6 = 0;
};

#endif /* INC_VIA_GLOBAL_SIGNALS_HPP_ */
