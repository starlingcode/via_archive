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
		scanner.xInterpolateOn = 1;
	} else {
		scanner.xInterpolateOn = 0;
	}

}

void ViaScanner::handleButton2ModeChange(int32_t mode) {

	switchWavetableY(wavetableArray[mode]);

	if (mode >= 6) {
		scanner.yInterpolateOn = 1;
	} else {
		scanner.yInterpolateOn = 0;
	}

}

void ViaScanner::handleButton6ModeChange(int32_t mode) {

	switchWavetableX(wavetableArray[mode]);

	if (mode >= 6) {
		scanner.xInterpolateOn = 1;
	} else {
		scanner.xInterpolateOn = 0;
	}
}

void ViaScanner::handleButton1ModeChange(int32_t mode) {

	scanner.syncMode = mode;

}

void ViaScanner::handleButton5ModeChange(int32_t mode) {

	switchWavetableY(wavetableArray[mode]);

	if (mode >= 6) {
		scanner.xInterpolateOn = 1;
	} else {
		scanner.xInterpolateOn = 0;
	}

}

void ViaScanner::handleButton3ModeChange(int32_t mode) {

	scanner.terrainType = mode;

}


