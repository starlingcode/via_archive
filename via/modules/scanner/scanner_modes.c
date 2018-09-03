/*
 * scanner_modes.c
 *
 *  Created on: Aug 22, 2018
 *      Author: willmitchell
 */

#include "scanner.h"

void scanner_handleButton4ModeChange(int mode) {

	scanner_switchWavetableX(scanner_wavetableArray[mode], &scanner_signals);

}

void scanner_handleButton2ModeChange(int mode) {

	scanner_switchWavetableY(scanner_wavetableArray[mode], &scanner_signals);


}

void scanner_handleButton6ModeChange(int mode) {

	scanner_switchWavetableX(scanner_wavetableArray[mode], &scanner_signals);


}

void scanner_handleButton1ModeChange(int mode) {

	scanner_signals.parameters->syncMode = mode;

}

void scanner_handleButton5ModeChange(int mode) {

	scanner_switchWavetableY(scanner_wavetableArray[mode], &scanner_signals);

}

void scanner_handleButton3ModeChange(int mode) {

	scanner_signals.parameters->terrainType = mode;

}


