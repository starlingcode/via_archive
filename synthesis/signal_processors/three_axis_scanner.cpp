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

inline int32_t ThreeAxisScanner::getSampleProduct(int32_t xIndex, int32_t yIndex, int32_t zIndex,
		int32_t * xTable, int32_t * yTable, int32_t * xDelta, int32_t * yDelta) {

	// waveterrain = wavetable(x, z) * wavetable(y, z)

	int32_t xSample = getSampleQuinticSpline(xIndex << 9, zIndex,
			(uint32_t *) xTable, xDelta);
	int32_t ySample = getSampleQuinticSpline(yIndex << 9, zIndex,
			(uint32_t *) yTable, yDelta);

	return (xSample * ySample) >> 18; //15 bit fixed point multiply and right shift by 3

}

inline int32_t ThreeAxisScanner::getSamplePM(int32_t xIndex, int32_t yIndex, int32_t zIndex, int32_t * xTable,
		int32_t*yTable, int32_t * xDelta, int32_t * yDelta) {

	// waveterrain = wavetable(x + wavetable(y, z), z)

	int32_t xSample = getSampleQuinticSpline(xIndex << 9, zIndex,
			(uint32_t *) xTable, xDelta);
	int32_t ySample = getSampleQuinticSpline(
			((yIndex << 9) + (xSample << 4)) & ((1 << 25) - 1), zIndex,
			(uint32_t *) yTable, yDelta);

	return ySample >> 3; //right shift by 3 tp scale 15bit to 12bit

}

inline int32_t ThreeAxisScanner::getSampleSum(int32_t xIndex, int32_t yIndex, int32_t zIndex, int32_t * xTable,
		int32_t*yTable, int32_t * xDelta, int32_t * yDelta) {

	// waveterrain = wavetable(x, z) + wavetable(y, z)

	int32_t xSample = getSampleQuinticSpline(xIndex << 9, zIndex,
			(uint32_t *) xTable, xDelta);
	int32_t ySample = getSampleQuinticSpline(yIndex << 9, zIndex,
			(uint32_t *) yTable, yDelta);

	return (xSample + ySample) >> 4; // scale from 15bit to 12 bit and divide by two to normalize the space (max value = 1+1)

}

inline int32_t ThreeAxisScanner::getSampleSubtract(int32_t xIndex, int32_t yIndex, int32_t zIndex, int32_t * xTable,
		int32_t*yTable, int32_t * xDelta, int32_t * yDelta) {

	// waveterrain = wavetable(x, z) + wavetable(y, z)

	int32_t xSample = getSampleQuinticSpline(xIndex << 9, zIndex,
			(uint32_t *) xTable, xDelta);
	int32_t ySample = getSampleQuinticSpline(yIndex << 9, zIndex,
			(uint32_t *) yTable, yDelta);

	return ((xSample - ySample) >> 4) + 2048; // scale from 15bit to 12 bit and divide by two to normalize the space (max value = 1+1)

}

void ThreeAxisScanner::scanTerrainProduct(int32_t * xIndexBuffer, int32_t * yIndexBuffer, int32_t zIndex,
		int32_t * xTable, int32_t * yTable, int32_t * xDelta, int32_t * yDelta, uint32_t * output,
		uint32_t writePosition, uint32_t samplesRemaining) {

	uint32_t writeIndex = 0;

	output = output + writePosition;

	while (samplesRemaining) {

		output[writeIndex] = getSampleProduct(xIndexBuffer[writeIndex],
				yIndexBuffer[writeIndex], zIndex, xTable, yTable,
				xDelta + writeIndex, yDelta + writeIndex);

		writeIndex++;
		samplesRemaining--;

	}

}

void ThreeAxisScanner::scanTerrainSum(int32_t * xIndexBuffer, int32_t * yIndexBuffer, int32_t zIndex,
		int32_t * xTable, int32_t * yTable, int32_t * xDelta, int32_t * yDelta, uint32_t * output,
		uint32_t writePosition, uint32_t samplesRemaining) {

	uint32_t writeIndex = 0;

	output = output + writePosition;

	while (samplesRemaining) {

		output[writeIndex] = getSampleSum(xIndexBuffer[writeIndex],
				yIndexBuffer[writeIndex], zIndex, xTable, yTable,
				xDelta + writeIndex, yDelta + writeIndex);

		writeIndex++;
		samplesRemaining--;

	}

}

void ThreeAxisScanner::scanTerrainSubtract(int32_t * xIndexBuffer, int32_t * yIndexBuffer, int32_t zIndex,
		int32_t * xTable, int32_t * yTable, int32_t * xDelta, int32_t * yDelta, uint32_t * output,
		uint32_t writePosition, uint32_t samplesRemaining) {

	uint32_t writeIndex = 0;

	output = output + writePosition;

	while (samplesRemaining) {

		output[writeIndex] = getSampleSubtract(xIndexBuffer[writeIndex],
				yIndexBuffer[writeIndex], zIndex, xTable, yTable,
				xDelta + writeIndex, yDelta + writeIndex);

		writeIndex++;
		samplesRemaining--;

	}

}

void ThreeAxisScanner::scanTerrainPM(int32_t * xIndexBuffer, int32_t * yIndexBuffer, int32_t zIndex,
		int32_t * xTable, int32_t * yTable, int32_t * xDelta, int32_t * yDelta, uint32_t * output,
		uint32_t writePosition, uint32_t samplesRemaining) {

	uint32_t writeIndex = 0;

	output = output + writePosition;

	while (samplesRemaining) {

		output[writeIndex] = getSamplePM(xIndexBuffer[writeIndex],
				yIndexBuffer[writeIndex], zIndex, xTable, yTable,
				xDelta + writeIndex, yDelta + writeIndex);

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
				xTable, yTable, xDeltaBuffer, yDeltaBuffer, (uint32_t *) altitude,
				0, bufferSize);
		break;

	case THREE_AXIS_SCANNER_PRODUCT:
		scanTerrainSubtract(xIndexBuffer, yIndexBuffer, zIndex,
				xTable, yTable, xDeltaBuffer, yDeltaBuffer, (uint32_t *) altitude,
				0, bufferSize);
		break;

	case THREE_AXIS_SCANNER_DIFFERENCE:
		scanTerrainProduct(xIndexBuffer, yIndexBuffer, zIndex,
				xTable, yTable, xDeltaBuffer, yDeltaBuffer, (uint32_t *) altitude,
				0, bufferSize);
		break;

	case THREE_AXIS_SCANNER_PHASE_MOD:
		scanTerrainPM(xIndexBuffer, yIndexBuffer, zIndex,
				xTable, yTable, xDeltaBuffer, yDeltaBuffer, (uint32_t *) altitude,
				0, bufferSize);
		break;

	}

}
