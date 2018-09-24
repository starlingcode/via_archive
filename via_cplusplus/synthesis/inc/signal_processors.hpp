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

	inline int32_t getSampleProduct(int32_t xIndex, int32_t yIndex, int32_t zIndex,
    		int32_t * xTable, int32_t * yTable, int32_t * xDelta, int32_t * yDelta);

	inline int32_t getSamplePM(int32_t xIndex, int32_t yIndex, int32_t zIndex,
    		int32_t * xTable, int32_t * yTable, int32_t * xDelta, int32_t * yDelta);

	inline int32_t getSampleSum(int32_t xIndex, int32_t yIndex, int32_t zIndex,
    		int32_t * xTable, int32_t * yTable, int32_t * xDelta, int32_t * yDelta);

	inline int32_t getSampleSubtract(int32_t xIndex, int32_t yIndex, int32_t zIndex,
    		int32_t * xTable, int32_t * yTable, int32_t * xDelta, int32_t * yDelta);

	void scanTerrainProduct(int32_t * xIndexBuffer, int32_t * yIndexBuffer, int32_t zIndex,
			int32_t * xTable, int32_t * yTable, int32_t * xDelta, int32_t * yDelta, uint32_t * output,
			uint32_t writePosition, uint32_t samplesRemaining);

	void scanTerrainPM(int32_t * xIndexBuffer, int32_t * yIndexBuffer, int32_t zIndex,
			int32_t * xTable, int32_t * yTable, int32_t * xDelta, int32_t * yDelta, uint32_t * output,
			uint32_t writePosition, uint32_t samplesRemaining);

	void scanTerrainSum(int32_t * xIndexBuffer, int32_t * yIndexBuffer, int32_t zIndex,
			int32_t * xTable, int32_t * yTable, int32_t * xDelta, int32_t * yDelta, uint32_t * output,
			uint32_t writePosition, uint32_t samplesRemaining);

	void scanTerrainSubtract(int32_t * xIndexBuffer, int32_t * yIndexBuffer, int32_t zIndex,
			int32_t * xTable, int32_t * yTable, int32_t * xDelta, int32_t * yDelta, uint32_t * output,
			uint32_t writePosition, uint32_t samplesRemaining);

public:

#define THREE_AXIS_SCANNER_SUM 0
#define THREE_AXIS_SCANNER_PRODUCT 1
#define THREE_AXIS_SCANNER_DIFFERENCE 2
#define THREE_AXIS_SCANNER_PHASE_MOD 3

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
	int32_t * xDeltaBuffer;
	int32_t * yDeltaBuffer;
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
		xDeltaBuffer = (int32_t *) malloc(bufferSize * sizeof(int32_t));
		yDeltaBuffer = (int32_t *) malloc(bufferSize * sizeof(int32_t));
		altitude = (int32_t *) malloc(bufferSize * sizeof(int32_t));

		xInput = (int32_t *) malloc(bufferSize * sizeof(int32_t));
		yInput = (int32_t *) malloc(bufferSize * sizeof(int32_t));
		hardSync = (int32_t *) malloc(bufferSize * sizeof(int32_t));
		reverse = (int32_t *) malloc(bufferSize * sizeof(int32_t));
		sh = (int32_t *) malloc(bufferSize * sizeof(int32_t));

		for (int32_t i = 0; i < bufferSize; i++) {
			xIndexBuffer[i] = 0;
			yIndexBuffer[i] = 0;
			xDeltaBuffer[i] = 0;
			yDeltaBuffer[i] = 0;
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
