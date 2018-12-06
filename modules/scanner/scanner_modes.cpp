/*
 * modes.c
 *
 *  Created on: Aug 22, 2018
 *      Author: willmitchell
 */

#include "scanner.hpp"

void ViaScanner::handleButton4ModeChange(int32_t mode) {

	switchWavetableX(wavetableArray[mode]);

	if (mode >= 6) {
		// scanner.xInterpolationOn = 0;
	} else {
		// scanner.xInterpolationOn = 1;
	}

}

void ViaScanner::handleButton2ModeChange(int32_t mode) {

	switchWavetableY(wavetableArray[mode]);

	if (mode >= 6) {
		// scanner.yInterpolationOn = 0;
	} else {
		// scanner.yInterpolationOn = 1;
	}

}

void ViaScanner::handleButton6ModeChange(int32_t mode) {

	switchWavetableX(wavetableArray[mode]);

	if (mode >= 6) {
		// scanner.xInterpolationOn = 0;
	} else {
		// scanner.xInterpolationOn = 1;
	}
}

void ViaScanner::handleButton1ModeChange(int32_t mode) {

	scanner.syncMode = mode;

}

void ViaScanner::handleButton5ModeChange(int32_t mode) {

	switchWavetableY(wavetableArray[mode]);

	if (mode >= 6) {
		// scanner.xInterpolationOn = 0;
	} else {
		// scanner.xInterpolationOn = 1;
	}

}

void ViaScanner::handleButton3ModeChange(int32_t mode) {

	scanner.terrainType = mode;

}


