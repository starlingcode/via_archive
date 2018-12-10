/*
 * meta_init.cpp
 *
 *  Created on: Sep 12, 2018
 *      Author: willmitchell
 */

#include "calib.hpp"

void ViaCalib::init() {

	initializeAuxOutputs();

	inputs.init(CALIB_BUFFER_SIZE);
	outputs.init(CALIB_BUFFER_SIZE);
	outputBufferSize = CALIB_BUFFER_SIZE;
	inputBufferSize = 1;

	CalibUI.initialize();

}
