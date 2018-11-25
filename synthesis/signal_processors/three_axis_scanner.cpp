/*
 * three_axis_scanner.c
 *
 *  Created on: Aug 22, 2018
 *      Author: willmitchell
 */

#include "signal_processors.hpp"


void ThreeAxisScanner::parseControls(ViaControls * controls) {

	xOffset = (controls->knob2Value - 2048) << 13;
	yOffset = (controls->knob3Value - 2048) << 13;

	int32_t zKnobCV = controls->knob1Value - 2200 + controls->cv1Value;
	zIndex = __USAT(zKnobCV, 12) << 6;

}

void ThreeAxisScanner::fillBuffer() {

	int32_t xIncrement = (xInput - lastXInput) * reverse;
	int32_t yIncrement = (yInput - lastYInput) * reverse;

	if (abs(xIncrement) > 512 || abs(yIncrement) > 512) {
		oversample = 1;
	} else {
		oversample = 0;
	}

	// store last value
	lastXInput = xInput;
	lastYInput = yInput;

	int32_t xIndex = lastXIndex * hardSync;
	int32_t yIndex = lastYIndex * hardSync;

	int32_t samplesRemaining = bufferSize;
	int32_t writeIndex = 0;

	while (samplesRemaining) {

		xIndex += xIncrement;
		yIndex += yIncrement;

		xIndexBuffer[writeIndex] = foldSignal25Bit((xIndex << 8) + xOffset);
		yIndexBuffer[writeIndex] = foldSignal25Bit((yIndex << 8) + yOffset);

		samplesRemaining --;
		writeIndex ++;

	}

	// store
	lastXIndex = xIndex;
	lastYIndex = yIndex;


	switch (terrainType) {

	// get samples and combine
	case THREE_AXIS_SCANNER_SUM:
		scanTerrainSum();
		break;

	case THREE_AXIS_SCANNER_Multiply:
		scanTerrainMultiply();
		break;

	case THREE_AXIS_SCANNER_DIFFERENCE:
		scanTerrainDifference();
		break;

	case THREE_AXIS_SCANNER_LIGHTEN:
		scanTerrainLighten();
		break;

	}

}

inline void ThreeAxisScanner::scanTerrainSum(void) {

	uint32_t writeIndex = 0;

	int32_t xDelta;
	int32_t yDelta;

	int32_t xSample;
	int32_t ySample;

	int32_t * xTableRead = (int32_t *) xTable + (517 * (zIndex >> 16)) + 2;
	int32_t * yTableRead = (int32_t *) yTable + (517 * (zIndex >> 16)) + 2;

	int32_t leftSample;
	int32_t morphFrac;
	int32_t phaseFrac;

	int32_t samplesRemaining = bufferSize - 1;

	if (oversample == 0) {

		xSample = getSampleQuinticSplineDeltaValue(xIndexBuffer[writeIndex], zIndex,
				(uint32_t *) xTable, &xDelta);
		ySample = getSampleQuinticSplineDeltaValue(yIndexBuffer[writeIndex], zIndex,
				(uint32_t *) yTable, &yDelta);

		int32_t mainScan = __SSAT(((xSample - 16383) + (ySample - 16383)) >> 3, 11) + 2047;

		int32_t samplesRemaining = bufferSize;

		while (samplesRemaining) {
			altitude[writeIndex] = mainScan;
			locationBlend[writeIndex] = __SSAT(((xIndexBuffer[writeIndex] - 0xFFFFFF) + (yIndexBuffer[writeIndex] - 0xFFFFFF)) >> 13, 11) + 2047;

			writeIndex ++;
			samplesRemaining --;

		}

	} else {

		while (samplesRemaining) {

			leftSample = xIndexBuffer[writeIndex] >> 16;
			phaseFrac = (xIndexBuffer[writeIndex]) & 0xFFFF;
			morphFrac =  zIndex & 0xFFFF;

			xSample = fast_15_16_bilerp_prediff(xTableRead[leftSample], xTableRead[leftSample + 1], morphFrac, phaseFrac);

			leftSample = yIndexBuffer[writeIndex] >> 16;
			phaseFrac = (yIndexBuffer[writeIndex]) & 0xFFFF;

			ySample = fast_15_16_bilerp_prediff(yTableRead[leftSample], yTableRead[leftSample + 1], morphFrac, phaseFrac);

			altitude[writeIndex] = __SSAT(((xSample - 16383) + (ySample - 16383)) >> 3, 11) + 2047;
			locationBlend[writeIndex] = __SSAT(((xIndexBuffer[writeIndex] - 0xFFFFFF) + (yIndexBuffer[writeIndex] - 0xFFFFFF)) >> 13, 11) + 2047;
			writeIndex ++;
			samplesRemaining --;

		}

		leftSample = xIndexBuffer[writeIndex] >> 16;
		phaseFrac = (xIndexBuffer[writeIndex]) & 0xFFFF;
		morphFrac =  zIndex & 0xFFFF;

		xSample = fast_15_16_bilerp_prediff_deltaValue(xTableRead[leftSample], xTableRead[leftSample + 1], morphFrac, phaseFrac, &xDelta);

		leftSample = yIndexBuffer[writeIndex]>> 16;
		phaseFrac = (yIndexBuffer[writeIndex]) & 0xFFFF;

		ySample = fast_15_16_bilerp_prediff_deltaValue(yTableRead[leftSample], yTableRead[leftSample + 1], morphFrac, phaseFrac, &yDelta);

		altitude[writeIndex] = __SSAT(((xSample - 16383) + (ySample - 16383)) >> 3, 11) + 2047;
		locationBlend[writeIndex] = __SSAT(((xIndexBuffer[writeIndex] - 0xFFFFFF) + (yIndexBuffer[writeIndex] - 0xFFFFFF)) >> 13, 11) + 2047;
	}

	xHemisphereLast = getHemisphereHysteresis(xSample, xHemisphereLast);
	yHemisphereLast = getHemisphereHysteresis(ySample, yHemisphereLast);

	xDeltaLast = getDeltaHysterisis(xDelta, xDeltaLast);
	yDeltaLast = getDeltaHysterisis(yDelta, yDeltaLast);

	hemisphereBlend = xHemisphereLast | yHemisphereLast;
	deltaBlend = xDeltaLast | yDeltaLast;

}

inline void ThreeAxisScanner::scanTerrainMultiply(void) {

	uint32_t writeIndex = 0;

	int32_t xDelta;
	int32_t yDelta;

	int32_t xSample;
	int32_t ySample;

	int32_t samplesRemaining = bufferSize - 1;

	int32_t * xTableRead = (int32_t *) xTable + (517 * (zIndex >> 16)) + 2;
	int32_t * yTableRead = (int32_t *) yTable + (517 * (zIndex >> 16)) + 2;

	int32_t leftSample;
	int32_t morphFrac;
	int32_t phaseFrac;

	if (oversample == 0) {

		xSample = getSampleQuinticSplineDeltaValue(xIndexBuffer[writeIndex], zIndex,
				(uint32_t *) xTable, &xDelta);
		ySample = getSampleQuinticSplineDeltaValue(yIndexBuffer[writeIndex], zIndex,
				(uint32_t *) yTable, &yDelta);

		int32_t mainScan = (xSample * ySample) >> 18; //15 bit fixed point multiply and right shift by 3

		int32_t samplesRemaining = bufferSize;

		while (samplesRemaining) {
			altitude[writeIndex] = mainScan;
			locationBlend[writeIndex] = fix16_mul(xIndexBuffer[writeIndex] >> 2, yIndexBuffer[writeIndex] >> 2) >> 18;

			writeIndex ++;
			samplesRemaining --;
		}

	} else {

		while (samplesRemaining) {

			leftSample = xIndexBuffer[writeIndex]>> 16;
			phaseFrac = (xIndexBuffer[writeIndex]) & 0xFFFF;
			morphFrac =  zIndex & 0xFFFF;

			xSample = fast_15_16_bilerp_prediff(xTableRead[leftSample], xTableRead[leftSample + 1], morphFrac, phaseFrac);

			leftSample = yIndexBuffer[writeIndex]>> 16;
			phaseFrac = (yIndexBuffer[writeIndex]) & 0xFFFF;

			ySample = fast_15_16_bilerp_prediff(yTableRead[leftSample], yTableRead[leftSample + 1], morphFrac, phaseFrac);

			altitude[writeIndex] = (xSample * ySample) >> 18;
			locationBlend[writeIndex] = fix16_mul(xIndexBuffer[writeIndex] >> 2, yIndexBuffer[writeIndex] >> 2) >> 18;

			writeIndex ++;
			samplesRemaining --;

		}

		leftSample = xIndexBuffer[writeIndex]>> 16;
		phaseFrac = (xIndexBuffer[writeIndex]) & 0xFFFF;
		morphFrac =  zIndex & 0xFFFF;

		xSample = fast_15_16_bilerp_prediff_deltaValue(xTableRead[leftSample], xTableRead[leftSample + 1], morphFrac, phaseFrac, &xDelta);

		leftSample = yIndexBuffer[writeIndex]>> 16;
		phaseFrac = (yIndexBuffer[writeIndex]) & 0xFFFF;

		ySample = fast_15_16_bilerp_prediff_deltaValue(yTableRead[leftSample], yTableRead[leftSample + 1], morphFrac, phaseFrac, &yDelta);

		altitude[writeIndex] = (xSample * ySample) >> 18;
		locationBlend[writeIndex] = fix16_mul(xIndexBuffer[writeIndex] >> 2, yIndexBuffer[writeIndex] >> 2) >> 18;

	}

	xHemisphereLast = getHemisphereHysteresis(xSample, xHemisphereLast);
	yHemisphereLast = getHemisphereHysteresis(ySample, yHemisphereLast);

	xDeltaLast = getDeltaHysterisis(xDelta, xDeltaLast);
	yDeltaLast = getDeltaHysterisis(yDelta, yDeltaLast);

	hemisphereBlend = xHemisphereLast & yHemisphereLast;
	deltaBlend = xDeltaLast & yDeltaLast;


}

inline void ThreeAxisScanner::scanTerrainDifference(void) {

	uint32_t writeIndex = 0;

	int32_t xDelta;
	int32_t yDelta;

	int32_t xSample;
	int32_t ySample;

	int32_t samplesRemaining = bufferSize - 1;

	int32_t * xTableRead = (int32_t *) xTable + (517 * (zIndex >> 16)) + 2;
	int32_t * yTableRead = (int32_t *) yTable + (517 * (zIndex >> 16)) + 2;

	int32_t leftSample;
	int32_t morphFrac;
	int32_t phaseFrac;

	if (oversample == 0) {

		xSample = getSampleQuinticSplineDeltaValue(xIndexBuffer[writeIndex], zIndex,
				(uint32_t *) xTable, &xDelta);
		ySample = getSampleQuinticSplineDeltaValue(yIndexBuffer[writeIndex], zIndex,
				(uint32_t *) yTable, &yDelta);

		int32_t mainScan = abs((xSample - ySample) >> 3); //15 bit fixed point multiply and right shift by 3

		int32_t samplesRemaining = bufferSize;

		while (samplesRemaining) {
			altitude[writeIndex] = mainScan;
			locationBlend[writeIndex] = abs((xIndexBuffer[writeIndex] - yIndexBuffer[writeIndex]) >> 13);

			writeIndex ++;
			samplesRemaining --;

		}

	} else {

		while (samplesRemaining) {

			leftSample = xIndexBuffer[writeIndex]>> 16;
			phaseFrac = (xIndexBuffer[writeIndex]) & 0xFFFF;
			morphFrac =  zIndex & 0xFFFF;

			xSample = fast_15_16_bilerp_prediff(xTableRead[leftSample], xTableRead[leftSample + 1], morphFrac, phaseFrac);

			leftSample = yIndexBuffer[writeIndex]>> 16;
			phaseFrac = (yIndexBuffer[writeIndex]) & 0xFFFF;

			ySample = fast_15_16_bilerp_prediff(yTableRead[leftSample], yTableRead[leftSample + 1], morphFrac, phaseFrac);

			altitude[writeIndex] = abs((xSample - ySample) >> 3);
			locationBlend[writeIndex] = abs((xIndexBuffer[writeIndex] - yIndexBuffer[writeIndex]) >> 13);

			writeIndex ++;
			samplesRemaining --;

		}

		leftSample = xIndexBuffer[writeIndex]>> 16;
		phaseFrac = (xIndexBuffer[writeIndex]) & 0xFFFF;
		morphFrac =  zIndex & 0xFFFF;

		xSample = fast_15_16_bilerp_prediff_deltaValue(xTableRead[leftSample], xTableRead[leftSample + 1], morphFrac, phaseFrac, &xDelta);

		leftSample = yIndexBuffer[writeIndex]>> 16;
		phaseFrac = (yIndexBuffer[writeIndex]) & 0xFFFF;

		ySample = fast_15_16_bilerp_prediff_deltaValue(yTableRead[leftSample], yTableRead[leftSample + 1], morphFrac, phaseFrac, &yDelta);

		altitude[writeIndex] = abs((xSample - ySample) >> 3);
		locationBlend[writeIndex] = abs((xIndexBuffer[writeIndex] - yIndexBuffer[writeIndex]) >> 13);

	}

	xHemisphereLast = getHemisphereHysteresis(xSample, xHemisphereLast);
	yHemisphereLast = getHemisphereHysteresis(ySample, yHemisphereLast);

	xDeltaLast = getDeltaHysterisis(xDelta, xDeltaLast);
	yDeltaLast = getDeltaHysterisis(yDelta, yDeltaLast);

	hemisphereBlend = xHemisphereLast ^ yHemisphereLast;
	deltaBlend = xDeltaLast ^ yDeltaLast;

}

inline void ThreeAxisScanner::scanTerrainLighten(void) {

	uint32_t writeIndex = 0;

	int32_t xDelta;
	int32_t yDelta;

	int32_t xSample;
	int32_t ySample;

	int32_t samplesRemaining = bufferSize - 1;

	int32_t * xTableRead = (int32_t *) xTable + (517 * (zIndex >> 16)) + 2;
	int32_t * yTableRead = (int32_t *) yTable + (517 * (zIndex >> 16)) + 2;

	int32_t leftSample;
	int32_t morphFrac;
	int32_t phaseFrac;

	if (oversample == 0) {

		xSample = getSampleQuinticSplineDeltaValue(xIndexBuffer[writeIndex], zIndex,
				(uint32_t *) xTable, &xDelta);
		ySample = getSampleQuinticSplineDeltaValue(yIndexBuffer[writeIndex], zIndex,
				(uint32_t *) yTable, &yDelta);

		int32_t mainScan = (ySample > xSample) ? ySample >> 3 : xSample >> 3; //15 bit fixed point multiply and right shift by 3

		int32_t samplesRemaining = bufferSize;

		while (samplesRemaining) {
			altitude[writeIndex] = mainScan;
			locationBlend[writeIndex] = ((yIndexBuffer[writeIndex] > xIndexBuffer[writeIndex]) ? yIndexBuffer[writeIndex] : xIndexBuffer[writeIndex]) >> 13;

			writeIndex ++;
			samplesRemaining --;

		}

	} else {

		while (samplesRemaining) {

			leftSample = xIndexBuffer[writeIndex]>> 16;
			phaseFrac = (xIndexBuffer[writeIndex]) & 0xFFFF;
			morphFrac =  zIndex & 0xFFFF;

			xSample = fast_15_16_bilerp_prediff(xTableRead[leftSample], xTableRead[leftSample + 1], morphFrac, phaseFrac);

			leftSample = yIndexBuffer[writeIndex]>> 16;
			phaseFrac = (yIndexBuffer[writeIndex]) & 0xFFFF;

			ySample = fast_15_16_bilerp_prediff(yTableRead[leftSample], yTableRead[leftSample + 1], morphFrac, phaseFrac);

			altitude[writeIndex] = (ySample > xSample) ? ySample >> 3 : xSample >> 3;
			locationBlend[writeIndex] = ((yIndexBuffer[writeIndex] > xIndexBuffer[writeIndex]) ? yIndexBuffer[writeIndex] : xIndexBuffer[writeIndex]) >> 13;

			writeIndex ++;
			samplesRemaining --;

		}

		leftSample = xIndexBuffer[writeIndex]>> 16;
		phaseFrac = (xIndexBuffer[writeIndex]) & 0xFFFF;
		morphFrac =  zIndex & 0xFFFF;

		xSample = fast_15_16_bilerp_prediff_deltaValue(xTableRead[leftSample], xTableRead[leftSample + 1], morphFrac, phaseFrac, &xDelta);

		leftSample = yIndexBuffer[writeIndex]>> 16;
		phaseFrac = (yIndexBuffer[writeIndex]) & 0xFFFF;

		ySample = fast_15_16_bilerp_prediff_deltaValue(yTableRead[leftSample], yTableRead[leftSample + 1], morphFrac, phaseFrac, &yDelta);

		altitude[writeIndex] = (ySample > xSample) ? ySample >> 3 : xSample >> 3;
		locationBlend[writeIndex] = ((yIndexBuffer[writeIndex] > xIndexBuffer[writeIndex]) ? yIndexBuffer[writeIndex] : xIndexBuffer[writeIndex]) >> 13;

	}

	xHemisphereLast = getHemisphereHysteresis(xSample, xHemisphereLast);
	yHemisphereLast = getHemisphereHysteresis(ySample, yHemisphereLast);

	xDeltaLast = getDeltaHysterisis(xDelta, xDeltaLast);
	yDeltaLast = getDeltaHysterisis(yDelta, yDeltaLast);

	hemisphereBlend = (yHemisphereLast > xHemisphereLast);
	deltaBlend = (yDeltaLast > xDeltaLast);

}
