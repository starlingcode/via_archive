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

	int32_t oversample = 0;

	int32_t lastXInput = 0;
	int32_t lastYInput = 0;
	int32_t lastXIndex = 0;
	int32_t lastYIndex = 0;

	inline void scanTerrainMultiply(void);

	inline void scanTerrainLighten(void);

	inline void scanTerrainSum(void);

	inline void scanTerrainDifference(void);

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

	uint32_t *xTable;
	uint32_t *yTable;

	int32_t xInput;
	int32_t yInput;
	int32_t hardSync;
	int32_t reverse;

	int32_t xOffset;
	int32_t yOffset;

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
	int32_t * altitude;

	int32_t hemisphereBlend;
	int32_t deltaBlend;

	void fillBuffer(void);

	void parseControls(ViaControls * controls);

	int32_t bufferSize = 8;

	void init(void) {

		xIndexBuffer = (int32_t *) malloc(bufferSize * sizeof(int32_t));
		yIndexBuffer = (int32_t *) malloc(bufferSize * sizeof(int32_t));
		locationBlend = (int32_t *) malloc(bufferSize * sizeof(int32_t));
		altitude = (int32_t *) malloc(bufferSize * sizeof(int32_t));

		for (int32_t i = 0; i < bufferSize; i++) {
			xIndexBuffer[i] = 0;
			yIndexBuffer[i] = 0;
			locationBlend[i] = 0;
			altitude[i] = 0;
		}

	}

};


#endif /* INC_SIGNAL_PROCESSORS_HPP_ */
