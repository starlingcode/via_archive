/*
 * signal_processors.h
 *
 *  Created on: Aug 18, 2018
 *      Author: willmitchell
 */

#ifndef INC_SIGNAL_PROCESSORS_HPP_
#define INC_SIGNAL_PROCESSORS_HPP_

#include "via_platform_binding.hpp"
#include "tables.hpp"

/*
 *
 * Three axis scanner
 *
 */

class ThreeAxisScanner {

	int32_t lastXInput = 0;
	int32_t lastYInput = 0;
	int32_t lastXIndex = 0;
	int32_t lastYIndex = 0;

	inline int32_t getSampleMultiply(int32_t xIndex, int32_t yIndex, int32_t zIndex,
    		int32_t * xTable, int32_t * yTable, int32_t * locationBlend, int32_t * hemisphereBlend, int32_t * deltaBlend);

	inline int32_t getSampleLighten(int32_t xIndex, int32_t yIndex, int32_t zIndex,
    		int32_t * xTable, int32_t * yTable, int32_t * locationBlend, int32_t * hemisphereBlend, int32_t * deltaBlend);

	inline int32_t getSampleSum(int32_t xIndex, int32_t yIndex, int32_t zIndex,
    		int32_t * xTable, int32_t * yTable, int32_t * locationBlend, int32_t * hemisphereBlend, int32_t * deltaBlend);

	inline int32_t getSampleDifference(int32_t xIndex, int32_t yIndex, int32_t zIndex,
    		int32_t * xTable, int32_t * yTable, int32_t * locationBlend, int32_t * hemisphereBlend, int32_t * deltaBlend);

	void scanTerrainMultiply(int32_t * xIndexBuffer, int32_t * yIndexBuffer, int32_t zIndex,
			int32_t * xTable, int32_t * yTable, int32_t * locationBlend, int32_t * hemisphereBlend, int32_t * deltaBlend, uint32_t * output,
			uint32_t writePosition, uint32_t samplesRemaining);

	void scanTerrainLighten(int32_t * xIndexBuffer, int32_t * yIndexBuffer, int32_t zIndex,
			int32_t * xTable, int32_t * yTable, int32_t * locationBlend, int32_t * hemisphereBlend, int32_t * deltaBlend, uint32_t * output,
			uint32_t writePosition, uint32_t samplesRemaining);

	void scanTerrainSum(int32_t * xIndexBuffer, int32_t * yIndexBuffer, int32_t zIndex,
			int32_t * xTable, int32_t * yTable, int32_t * locationBlend, int32_t * hemisphereBlend, int32_t * deltaBlend, uint32_t * output,
			uint32_t writePosition, uint32_t samplesRemaining);

	void scanTerrainDifference(int32_t * xIndexBuffer, int32_t * yIndexBuffer, int32_t zIndex,
			int32_t * xTable, int32_t * yTable, int32_t * locationBlend, int32_t * hemisphereBlend, int32_t * deltaBlend, uint32_t * output,
			uint32_t writePosition, uint32_t samplesRemaining);

	int32_t xHemisphereLast;
	int32_t yHemisphereLast;
	int32_t signalCompare;
	int32_t xDeltaLast;
	int32_t yDeltaLast;


	int32_t getHemisphereHysteresis(int32_t signal, int32_t last) {
		if (last && (signal < (1 << 14) - 5000)) {
			return 0;
		} else if (!last && signal > (1 << 14) + 5000) {
			return 1;
		} else {
			return last;
		}
	}

	int32_t compareWithHysterisis(int32_t xSignal, int32_t ySignal, int32_t yGreater) {

		if (yGreater && ySignal < (xSignal - 100)) {
			return 0;
		} else if (!yGreater && ySignal > (xSignal + 100)) {
			return 1;
		} else {
			return yGreater;
		}

	}

public:

#define THREE_AXIS_SCANNER_SUM 0
#define THREE_AXIS_SCANNER_Multiply 1
#define THREE_AXIS_SCANNER_DIFFERENCE 2
#define THREE_AXIS_SCANNER_LIGHTEN 3

	int32_t * xInput;
	int32_t * yInput;
	int32_t * hardSync;
	int32_t * reverse;
	int32_t * sh;

	//control rate input
	uint32_t zIndex = 0;

	// mode parameters
	uint32_t terrainType = 0;
	uint32_t syncMode = 0;
	uint32_t xTableSize = 0;
	uint32_t yTableSize = 0;

	// outputs
	int32_t * xIndexBuffer;
	int32_t * yIndexBuffer;
	int32_t * locationBlend;
	int32_t * mainLogicBlend;
	int32_t * auxLogicBlend;
	int32_t * altitude;

	void fillBuffer(ViaInputStreams * inputs,
			ViaControls * controls,
			int32_t * xTable, int32_t * yTable,
			uint32_t writePosition, uint32_t bufferSize);

	void parseControls(ViaControls * controls);

	int32_t bufferSize = 8;

	void init(void) {

		xIndexBuffer = (int32_t *) malloc(bufferSize * sizeof(int32_t));
		yIndexBuffer = (int32_t *) malloc(bufferSize * sizeof(int32_t));
		locationBlend = (int32_t *) malloc(bufferSize * sizeof(int32_t));
		mainLogicBlend = (int32_t *) malloc(bufferSize * sizeof(int32_t));
		auxLogicBlend = (int32_t *) malloc(bufferSize * sizeof(int32_t));
		altitude = (int32_t *) malloc(bufferSize * sizeof(int32_t));

		xInput = (int32_t *) malloc(bufferSize * sizeof(int32_t));
		yInput = (int32_t *) malloc(bufferSize * sizeof(int32_t));
		hardSync = (int32_t *) malloc(bufferSize * sizeof(int32_t));
		reverse = (int32_t *) malloc(bufferSize * sizeof(int32_t));
		sh = (int32_t *) malloc(bufferSize * sizeof(int32_t));

		for (int32_t i = 0; i < bufferSize; i++) {
			xIndexBuffer[i] = 0;
			yIndexBuffer[i] = 0;
			mainLogicBlend[i] = 0;
			auxLogicBlend[i] = 0;
			altitude[i] = 0;

			xInput[i] = 0;
			yInput[i] = 0;
			hardSync[i] = 0;
			reverse[i] = 0;
			sh[i] = 0;
		}

	}



};

/*
 *
 * Shared resources
 *
 */

extern "C" {

void extractDeltas(int32_t * input, int32_t * output, int32_t initialValue, uint32_t bufferSize);
void incrementFromDeltas(int32_t * input, int32_t * output, int32_t * hardSync, int32_t * reverse,
		int32_t initialPhase, uint32_t bufferSize);
void foldBuffer(int32_t * input, int32_t offset, int32_t * output, uint32_t bufferSize);
void wrapBuffer(int32_t * input, int32_t offset, int32_t * output, uint32_t bufferSize);

}


#endif /* INC_SIGNAL_PROCESSORS_HPP_ */
