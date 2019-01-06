/*
 * meta_init.cpp
 *
 *  Created on: Sep 12, 2018
 *      Author: willmitchell
 */

#include "calib.hpp"

void ViaCalib::init() {

	//writeOptionBytes(0,0);

	calibTest = readOptionBytes();

	initializeAuxOutputs();

	inputs.init(CALIB_BUFFER_SIZE);
	outputs.init(CALIB_BUFFER_SIZE);
	outputBufferSize = CALIB_BUFFER_SIZE;
	inputBufferSize = 1;

	for (int i = 0; i < CALIB_BUFFER_SIZE*2; i++) {
		outputs.dac3Samples[i] = 2048;
	}

	calibUI.initialize();

	readCalibrationPacket();

}
