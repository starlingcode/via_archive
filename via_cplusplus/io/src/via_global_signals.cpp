/*
 * via_global_signals.cpp
 *
 *  Created on: Sep 14, 2018
 *      Author: willmitchell
 */

#include "via_global_signals.hpp"

void ViaControls::update(void) {

	// TODO apply SIMD instructions?

	// store the newest value in a ring buffer
	writeBuffer(&cv1Buffer, cv1);
	writeBuffer(&knob1Buffer, knob1);
	writeBuffer(&knob2Buffer, knob2);
	writeBuffer(&knob3Buffer, knob3);

	// implement a running average on the control rate CV controls
	cv1Sum = cv1 + cv1Sum - readBuffer(&cv1Buffer, 31);
	knob1Sum = knob1 + knob1Sum - readBuffer(&knob1Buffer, 31);
	knob2Sum = knob2 + knob2Sum - readBuffer(&knob2Buffer, 31);
	knob3Sum = knob3 + knob3Sum - readBuffer(&knob3Buffer, 31);

	// write the averaged controls to the holding struct
	cv1Value = cv1Sum >> 5;
	knob1Value = knob1Sum >> 5;
	knob2Value = knob2Sum >> 5;
	knob3Value = knob3Sum >> 5;

}

// hard coded for stm32f373
void ViaModule::ioStreamInit() {

	inputs.init(bufferSize);
	outputs.init(bufferSize);

	int16_t cv2Offset = HAL_FLASHEx_OBGetUserData(OB_DATA_ADDRESS_DATA0) << 2;
	int16_t cv3Offset = HAL_FLASHEx_OBGetUserData(OB_DATA_ADDRESS_DATA1) << 2;

	for (int i = 0; i < 2 * bufferSize; i++) {
		inputs.cv2VirtualGround[i] = cv2Offset;
		inputs.cv3VirtualGround[i] = cv3Offset;
	}

	// initialize the ADCs and their respective DMA arrays
	HAL_ADC_Start_DMA(&hadc1, controls.controlRateInputs, 4);

//	if (HAL_SDADC_CalibrationStart(&hsdadc1, SDADC_CALIBRATION_SEQ_1)
//			!= HAL_OK) {
//		LEDA_ON;
//	}
//
//	/* Pool for the end of calibration */
//	if (HAL_SDADC_PollForCalibEvent(&hsdadc1, 100) != HAL_OK) {
//		LEDB_ON;
//	}
//
//	if (HAL_SDADC_CalibrationStart(&hsdadc2, SDADC_CALIBRATION_SEQ_1)
//			!= HAL_OK) {
//		LEDA_ON;
//	}
//
//	/* Pool for the end of calibration */
//	if (HAL_SDADC_PollForCalibEvent(&hsdadc2, 100) != HAL_OK) {
//		LEDB_ON;
//	}

	HAL_DAC_Start_DMA(&hdac1, DAC_CHANNEL_1, outputs.dac1Samples,
			2 * bufferSize, DAC_ALIGN_12B_R);
	HAL_DAC_Start_DMA(&hdac1, DAC_CHANNEL_2, outputs.dac2Samples,
			2 * bufferSize, DAC_ALIGN_12B_R);
	HAL_DAC_Start_DMA(&hdac2, DAC_CHANNEL_1, outputs.dac3Samples,
			2 * bufferSize, DAC_ALIGN_12B_R);

	// set the dac sample rate and start the dac timer
	HAL_SDADC_Start_DMA(&hsdadc1, (uint32_t *) inputs.cv2Samples, 2 * bufferSize);
	HAL_SDADC_Start_DMA(&hsdadc2, (uint32_t *) inputs.cv3Samples, 2 * bufferSize);

}
