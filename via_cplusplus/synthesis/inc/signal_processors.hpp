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
#include "dsp.hpp"

/*
 *
 * Three axis scanner
 *
 */

class ThreeAxisScanner {

	int lastXInput = 0;
	int lastYInput = 0;
	int lastXIndex = 0;
	int lastYIndex = 0;

	inline int getSampleProduct(int xIndex, int yIndex, int zIndex,
    		int * xTable, int * yTable, int * xDelta, int * yDelta);

	inline int getSamplePM(int xIndex, int yIndex, int zIndex,
    		int * xTable, int * yTable, int * xDelta, int * yDelta);

	inline int getSampleSum(int xIndex, int yIndex, int zIndex,
    		int * xTable, int * yTable, int * xDelta, int * yDelta);

	inline int getSampleSubtract(int xIndex, int yIndex, int zIndex,
    		int * xTable, int * yTable, int * xDelta, int * yDelta);

	void scanTerrainProduct(int * xIndexBuffer, int * yIndexBuffer, int zIndex,
			int * xTable, int * yTable, int * xDelta, int * yDelta, uint32_t * output,
			uint32_t writePosition, uint32_t samplesRemaining);

	void scanTerrainPM(int * xIndexBuffer, int * yIndexBuffer, int zIndex,
			int * xTable, int * yTable, int * xDelta, int * yDelta, uint32_t * output,
			uint32_t writePosition, uint32_t samplesRemaining);

	void scanTerrainSum(int * xIndexBuffer, int * yIndexBuffer, int zIndex,
			int * xTable, int * yTable, int * xDelta, int * yDelta, uint32_t * output,
			uint32_t writePosition, uint32_t samplesRemaining);

	void scanTerrainSubtract(int * xIndexBuffer, int * yIndexBuffer, int zIndex,
			int * xTable, int * yTable, int * xDelta, int * yDelta, uint32_t * output,
			uint32_t writePosition, uint32_t samplesRemaining);

public:

#define THREE_AXIS_SCANNER_SUM 0
#define THREE_AXIS_SCANNER_PRODUCT 1
#define THREE_AXIS_SCANNER_DIFFERENCE 2
#define THREE_AXIS_SCANNER_PHASE_MOD 3

	int * xInput;
	int * yInput;
	int * hardSync;
	int * reverse;
	int * sh;

	//control rate input
	uint32_t zIndex = 0;

	// mode parameters
	uint32_t terrainType = 0;
	uint32_t syncMode = 0;
	uint32_t xTableSize = 0;
	uint32_t yTableSize = 0;

	// outputs
	int * xIndexBuffer;
	int * yIndexBuffer;
	int * xDeltaBuffer;
	int * yDeltaBuffer;
	int * altitude;

	void fillBuffer(ViaInputStreams * inputs,
			ViaControls * controls,
			int * xTable, int * yTable,
			uint32_t writePosition, uint32_t bufferSize);

	void parseControls(ViaControls * controls);

	int bufferSize = 8;

	void init(void) {

		xIndexBuffer = (int *) malloc(bufferSize * sizeof(int));
		yIndexBuffer = (int *) malloc(bufferSize * sizeof(int));
		xDeltaBuffer = (int *) malloc(bufferSize * sizeof(int));
		yDeltaBuffer = (int *) malloc(bufferSize * sizeof(int));
		altitude = (int *) malloc(bufferSize * sizeof(int));

		xInput = (int *) malloc(bufferSize * sizeof(int));
		yInput = (int *) malloc(bufferSize * sizeof(int));
		hardSync = (int *) malloc(bufferSize * sizeof(int));
		reverse = (int *) malloc(bufferSize * sizeof(int));
		sh = (int *) malloc(bufferSize * sizeof(int));
	}



};

/*
 *
 * Shared resources
 *
 */

extern "C" {

void extractDeltas(int * input, int * output, int initialValue, uint32_t bufferSize);
void incrementFromDeltas(int * input, int * output, int * hardSync, int * reverse,
		int initialPhase, uint32_t bufferSize);
void foldBuffer(int * input, int offset, int * output, uint32_t bufferSize);
void wrapBuffer(int * input, int offset, int * output, uint32_t bufferSize);

}


#endif /* INC_SIGNAL_PROCESSORS_HPP_ */
