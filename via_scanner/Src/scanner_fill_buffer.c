
#include "scanner_main_states.h"
#include "scanner_tables.h"
#include "scanner_modes.h"
#include "signals.h"
#include "via_rev5_hardware_io.h"

void fillBuffer(viaSignals * signals) {

	q31_t xIndexBuffer[BUFFER_SIZE];
	q31_t yIndexBuffer[BUFFER_SIZE];
	uint32_t zIndex;
	static uint32_t slowConversionCounter;

	ALOGIC_HIGH;

	audioRateInputs * inputRead = signals->inputRead;
	audioRateOutputs * outputWrite = signals->outputWrite;
	softwareSignaling * softwareSignals = signals->softwareSignals;
	controlRateInputs * controls = signals->controls;




	// not implemented in ui

//	switch(button3Mode) {
//		case foldX:
//			foldBuffer(inputRead->cv2Input, controls->knob2Value, xIndexBuffer);
//			break;
//
//		case wrapX:
//			wrapBuffer(inputRead->xCV, controls->knob2Value, xIndexBuffer);
//			break;
//	}
//
//	switch(button6Mode) {
//		case foldY:
//			foldBuffer(inputRead->yCV, controls->knob3Value, yIndexBuffer);
//			break;
//
//		case wrapY:
//			wrapBuffer(inputRead->yCV, controls->knob3Value, yIndexBuffer);
//			break;
//	}

	wrapBuffer(inputRead->cv2Input, controls->knob2Value, xIndexBuffer);
	wrapBuffer(inputRead->cv3Input, controls->knob3Value, yIndexBuffer);

//	for (int i = 0; i < BUFFER_SIZE; i++) {
//		xIndexBuffer[i] = inputRead->cv2Input[i] << 3;
//		yIndexBuffer[i] = inputRead->cv3Input[i] << 3;
//	}


	zIndex = __USAT((int)controls->knob1Value + 2200 - (int)controls->cv1Value, 12);

	switch(softwareSignals->terrainType)  {

		case sum:
			scanTerrainSum(xIndexBuffer, yIndexBuffer, inputRead->syncBuffer, zIndex, outputWrite->samples);
			break;

		case subtract:
			scanTerrainSubtract(xIndexBuffer, yIndexBuffer, inputRead->syncBuffer, zIndex, outputWrite->samples);
			break;

		case product:
			scanTerrainProduct(xIndexBuffer, yIndexBuffer, inputRead->syncBuffer, zIndex, outputWrite->samples);
			break;

		case PM:
			scanTerrainPM(xIndexBuffer, yIndexBuffer, inputRead->syncBuffer, zIndex, outputWrite->samples);
			break;

	}

	ALOGIC_LOW

	slowConversionCounter++;

	slowConversionCounter = handleConversionSlow(signals->controls, slowConversionCounter);

}

