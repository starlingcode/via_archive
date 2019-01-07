/*
 * meta_interrupt_handlers.cpp
 *
 *  Created on: Sep 12, 2018
 *      Author: willmitchell
 */


/*
 * meta_interrupt_handlers.c
 *
 *  Created on: Aug 29, 2018
 *      Author: willmitchell
 */

#include "calib.hpp"

constexpr int32_t Sine::big_sine[4097];

void ViaCalib::mainRisingEdgeCallback(void) {
	setLEDA(1);
	setLEDB(1);
}

void ViaCalib::mainFallingEdgeCallback(void) {
	setLEDA(0);
	setLEDB(0);
}

void ViaCalib::auxRisingEdgeCallback(void) {
	setLEDC(1);
	setLEDD(1);
}
void ViaCalib::auxFallingEdgeCallback(void) {
	setLEDC(0);
	setLEDD(0);
}

void ViaCalib::buttonPressedCallback(void) {

	if (checkTouch) {

		setGreenLED(1024);

	} else {

		advanceState();

	}

}
void ViaCalib::buttonReleasedCallback(void) {


}

void ViaCalib::ioProcessCallback(void) {

	// no need

}

void ViaCalib::halfTransferCallback(void) {

	if (calibrateCVs) {

		measureCVOffsets();

	} else if (!checkTouch) {

		renderTestOutputs(0);

	}

}

void ViaCalib::transferCompleteCallback(void) {

	 if (!calibrateCVs && !checkTouch) {

		 renderTestOutputs(CALIB_BUFFER_SIZE);

	 }

}

void ViaCalib::slowConversionCallback(void) {

	if (!calibrateCVs && !checkTouch) {

		cv1TunerExecute();

		sineFreq = expo.convert(controls.cv1Value) >> 1;

		advanceLFO();

		verifyCV2CV3();

	} else {

		dac3Output = 2048;

	}

	controls.update();

}

void ViaCalib::auxTimer1InterruptCallback(void) {


}

void ViaCalib::auxTimer2InterruptCallback(void) {


}




