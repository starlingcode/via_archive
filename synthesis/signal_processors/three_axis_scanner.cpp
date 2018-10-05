/*
 * three_axis_scanner.c
 *
 *  Created on: Aug 22, 2018
 *      Author: willmitchell
 */

#include "signal_processors.hpp"


void ThreeAxisScanner::parseControls(ViaControls * controls) {

	int32_t zKnobCV = controls->knob1Value + 2200 - controls->cv1Value;
	zIndex = __USAT(zKnobCV, 12) << 6;

}

inline int32_t ThreeAxisScanner::getSampleMultiply(int32_t xIndex, int32_t yIndex, int32_t zIndex,
		int32_t * xTable, int32_t * yTable, int32_t * locationBlend, int32_t * hemisphereBlend, int32_t * deltaBlend) {

	// waveterrain = wavetable(x, z) * wavetable(y, z)

	int32_t xDelta;
	int32_t yDelta;

	int32_t xSample = getSampleQuinticSpline(xIndex << 9, zIndex,
			(uint32_t *) xTable, &xDelta);
	int32_t ySample = getSampleQuinticSpline(yIndex << 9, zIndex,
			(uint32_t *) yTable, &yDelta);

	*hemisphereBlend = (xSample >> 14) & (ySample >> 14);
	*deltaBlend = xDelta & yDelta;
	*locationBlend = fix16_mul(xIndex, yIndex) >> 4;

	return (xSample * ySample) >> 18; //15 bit fixed point multiply and right shift by 3

}

inline int32_t ThreeAxisScanner::getSampleLighten(int32_t xIndex, int32_t yIndex, int32_t zIndex, int32_t * xTable,
		int32_t * yTable, int32_t * locationBlend, int32_t * hemisphereBlend, int32_t * deltaBlend) {

	// waveterrain = wavetable(x + wavetable(y, z), z)

	int32_t xDelta;
	int32_t yDelta;

	int32_t xSample = getSampleQuinticSpline(xIndex << 9, zIndex,
			(uint32_t *) xTable, &xDelta) >> 3;
	int32_t ySample = getSampleQuinticSpline(yIndex << 9, zIndex,
			(uint32_t *) yTable, &yDelta) >> 3;

	uint32_t minmax = ((uint32_t)(ySample - xSample) >> 31);
	*hemisphereBlend = minmax;
	*deltaBlend = (yDelta > xDelta) ? yDelta : xDelta;
	*locationBlend = ((yIndex > xIndex) ? yIndex : xIndex) >> 4;

	return minmax * xSample + !minmax * ySample; //right shift by 3 tp scale 15bit to 12bit

}

inline int32_t ThreeAxisScanner::getSampleSum(int32_t xIndex, int32_t yIndex, int32_t zIndex, int32_t * xTable,
		int32_t * yTable, int32_t * locationBlend, int32_t * hemisphereBlend, int32_t * deltaBlend) {

	// waveterrain = wavetable(x, z) + wavetable(y, z)

	int32_t xDelta;
	int32_t yDelta;

	int32_t xSample = getSampleQuinticSpline(xIndex << 9, zIndex,
			(uint32_t *) xTable, &xDelta);
	int32_t ySample = getSampleQuinticSpline(yIndex << 9, zIndex,
			(uint32_t *) yTable, &yDelta);

	*hemisphereBlend = (xSample >> 14) | (ySample >> 14);
	*deltaBlend = xDelta | yDelta;
	*locationBlend = foldSignal16Bit(xIndex + yIndex) >> 4;

	return (xSample + ySample) >> 4; // scale from 15bit to 12 bit and divide by two to normalize the space (max value = 1+1)

}

inline int32_t ThreeAxisScanner::getSampleDifference(int32_t xIndex, int32_t yIndex, int32_t zIndex, int32_t * xTable,
		int32_t*yTable, int32_t * locationBlend, int32_t * hemisphereBlend, int32_t * deltaBlend) {

	// waveterrain = wavetable(x, z) + wavetable(y, z)

	int32_t xDelta;
	int32_t yDelta;

	int32_t xSample = getSampleQuinticSpline(xIndex << 9, zIndex,
			(uint32_t *) xTable, &xDelta);
	int32_t ySample = getSampleQuinticSpline(yIndex << 9, zIndex,
			(uint32_t *) yTable, &yDelta);

	*hemisphereBlend = (xSample >> 14) ^ (ySample >> 14);
	*deltaBlend = xDelta ^ yDelta;
	*locationBlend = abs((xIndex - yIndex) >> 4);

	return abs((xSample - ySample) >> 3); // scale from 15bit to 12 bit and divide by two to normalize the space (max value = 1+1)

}

void ThreeAxisScanner::scanTerrainMultiply(int32_t * xIndexBuffer, int32_t * yIndexBuffer, int32_t zIndex,
		int32_t * xTable, int32_t * yTable, int32_t * locationBlend, int32_t * hemisphereBlend, int32_t * deltaBlend, uint32_t * output,
		uint32_t writePosition, uint32_t samplesRemaining) {

	uint32_t writeIndex = 0;

	output = output + writePosition;

	while (samplesRemaining) {

		output[writeIndex] = getSampleMultiply(xIndexBuffer[writeIndex],
				yIndexBuffer[writeIndex], zIndex, xTable, yTable, locationBlend + writeIndex,
				hemisphereBlend + writeIndex, deltaBlend + writeIndex);

		writeIndex++;
		samplesRemaining--;

	}

}

void ThreeAxisScanner::scanTerrainSum(int32_t * xIndexBuffer, int32_t * yIndexBuffer, int32_t zIndex,
		int32_t * xTable, int32_t * yTable, int32_t * locationBlend, int32_t * hemisphereBlend, int32_t * deltaBlend, uint32_t * output,
		uint32_t writePosition, uint32_t samplesRemaining) {

	uint32_t writeIndex = 0;

	output = output + writePosition;

	while (samplesRemaining) {

		output[writeIndex] = getSampleSum(xIndexBuffer[writeIndex],
				yIndexBuffer[writeIndex], zIndex, xTable, yTable, locationBlend + writeIndex,
				hemisphereBlend + writeIndex, deltaBlend + writeIndex);

		writeIndex++;
		samplesRemaining--;

	}

}

void ThreeAxisScanner::scanTerrainDifference(int32_t * xIndexBuffer, int32_t * yIndexBuffer, int32_t zIndex,
		int32_t * xTable, int32_t * yTable, int32_t * locationBlend, int32_t * hemisphereBlend, int32_t * deltaBlend, uint32_t * output,
		uint32_t writePosition, uint32_t samplesRemaining) {

	uint32_t writeIndex = 0;

	output = output + writePosition;

	while (samplesRemaining) {

		output[writeIndex] = getSampleDifference(xIndexBuffer[writeIndex],
				yIndexBuffer[writeIndex], zIndex, xTable, yTable, locationBlend + writeIndex,
				hemisphereBlend + writeIndex, deltaBlend + writeIndex);

		writeIndex++;
		samplesRemaining--;

	}

}

void ThreeAxisScanner::scanTerrainLighten(int32_t * xIndexBuffer, int32_t * yIndexBuffer, int32_t zIndex,
		int32_t * xTable, int32_t * yTable, int32_t * locationBlend, int32_t * hemisphereBlend, int32_t * deltaBlend, uint32_t * output,
		uint32_t writePosition, uint32_t samplesRemaining) {

	uint32_t writeIndex = 0;

	output = output + writePosition;

	while (samplesRemaining) {

		output[writeIndex] = getSampleLighten(xIndexBuffer[writeIndex],
				yIndexBuffer[writeIndex], zIndex, xTable, yTable, locationBlend + writeIndex,
				hemisphereBlend + writeIndex, deltaBlend + writeIndex);

		writeIndex++;
		samplesRemaining--;

	}

}

void ThreeAxisScanner::fillBuffer(ViaInputStreams * inputs,
		ViaControls * controls,
		int32_t * xTable, int32_t * yTable,
		uint32_t writePosition, uint32_t bufferSize) {

	extractDeltas(xInput, xIndexBuffer, lastXInput, bufferSize);
	extractDeltas(yInput, yIndexBuffer, lastYInput, bufferSize);

	lastXInput = xInput[bufferSize - 1];
	lastYInput = yInput[bufferSize - 1];

	incrementFromDeltas(xIndexBuffer, xIndexBuffer, hardSync, reverse,
			lastXIndex, bufferSize);
	incrementFromDeltas(yIndexBuffer, yIndexBuffer, hardSync, reverse,
			lastYIndex, bufferSize);

	lastXIndex = xIndexBuffer[bufferSize - 1];
	lastYIndex = yIndexBuffer[bufferSize - 1];

	foldBuffer(xIndexBuffer, controls->knob2Value, xIndexBuffer,
			bufferSize);
	foldBuffer(yIndexBuffer, controls->knob3Value, yIndexBuffer,
			bufferSize);

	switch (terrainType) {

	case THREE_AXIS_SCANNER_SUM:
		scanTerrainSum(xIndexBuffer, yIndexBuffer, zIndex,
				xTable, yTable, locationBlend, mainLogicBlend, auxLogicBlend, (uint32_t *) altitude,
				0, bufferSize);
		break;

	case THREE_AXIS_SCANNER_Multiply:
		scanTerrainMultiply(xIndexBuffer, yIndexBuffer, zIndex,
				xTable, yTable, locationBlend, mainLogicBlend, auxLogicBlend, (uint32_t *) altitude,
				0, bufferSize);
		break;

	case THREE_AXIS_SCANNER_DIFFERENCE:
		scanTerrainDifference(xIndexBuffer, yIndexBuffer, zIndex,
				xTable, yTable, locationBlend, mainLogicBlend, auxLogicBlend, (uint32_t *) altitude,
				0, bufferSize);
		break;

	case THREE_AXIS_SCANNER_LIGHTEN:
		scanTerrainLighten(xIndexBuffer, yIndexBuffer, zIndex,
				xTable, yTable, locationBlend, mainLogicBlend, auxLogicBlend, (uint32_t *) altitude,
				0, bufferSize);
		break;

	}

}
