#include "scanner.hpp"
#include "cmsis_dsp.hpp"

void ViaScanner::mainRisingEdgeCallback(void) {

	if (scanner.syncMode) {
		inputs.trigInput = 0;
	} else {
		reverseSignal *= -1;
	}

}

void ViaScanner::mainFallingEdgeCallback(void) {

}

void ViaScanner::auxRisingEdgeCallback(void) {
	setSH(1, 1);
	setLEDA(1);
	setLEDB(1);
	inputs.auxTrigInput = 1;
}
void ViaScanner::auxFallingEdgeCallback(void) {
	setSH(0, 0);
	setLEDA(0);
	setLEDB(0);
	inputs.auxTrigInput = 0;
}

void ViaScanner::buttonPressedCallback(void) {
	;
}
void ViaScanner::buttonReleasedCallback(void) {
	;
}

void ViaScanner::ioProcessCallback(void) {

//	setLogicOut(readIndex, runtimeDisplay);
//	inputs.trigSamples[readIndex] = inputs.trigInput;
//	inputs.trigInput = 1;
//	reverseBuffer[readIndex] = reverseSignal;
//	inputs.auxTrigSamples[readIndex] = inputs.auxTrigInput;
//
//	readIndex++;
//
//	readIndex &= SCANNER_BUFFER_SIZE*2 - 1;

}

void ViaScanner::halfTransferCallback(void) {

	setLogicOut(0, runtimeDisplay);

	scanner.hardSync = inputs.trigInput;
	inputs.trigInput = 1;
	scanner.reverse = reverseSignal;

	scanner.xInput = (int32_t)-inputs.cv2Samples[0];

	scanner.yInput = (int32_t)-inputs.cv3Samples[0];

	scanner.fillBuffer();

	for (int32_t i = 0; i < SCANNER_BUFFER_SIZE; i++) {
		outputs.dac2Samples[i] = scanner.altitude[i];
		outputs.dac1Samples[i] = 4095 - scanner.altitude[i];
		outputs.dac3Samples[i] = scanner.locationBlend[i];
	}

	outputs.logicA[0] = GET_ALOGIC_MASK(scanner.hemisphereBlend);
	outputs.auxLogic[0] = GET_EXPAND_LOGIC_MASK(scanner.deltaBlend);
	outputs.auxLogic[0] = GPIO_NOP;
	outputs.shA[0] = GPIO_NOP;
	outputs.shB[0] = GPIO_NOP;

}

void ViaScanner::transferCompleteCallback(void) {

	setLogicOut(0, runtimeDisplay);

	scanner.hardSync = inputs.trigInput;
	inputs.trigInput = 1;
	scanner.reverse = reverseSignal;

	scanner.xInput = (int32_t)-inputs.cv2Samples[0];

	scanner.yInput = (int32_t)-inputs.cv3Samples[0];

	scanner.fillBuffer();

	for (int32_t i = 0; i < SCANNER_BUFFER_SIZE; i++) {
		outputs.dac2Samples[i + SCANNER_BUFFER_SIZE] = scanner.altitude[i];
		outputs.dac1Samples[i + SCANNER_BUFFER_SIZE] = 4095 - scanner.altitude[i];
		outputs.dac3Samples[i + SCANNER_BUFFER_SIZE] = scanner.locationBlend[i];
	}

	outputs.logicA[0] = GET_ALOGIC_MASK(scanner.hemisphereBlend);
	outputs.auxLogic[0] = GET_EXPAND_LOGIC_MASK(scanner.deltaBlend);
	outputs.auxLogic[0] = GPIO_NOP;
	outputs.shA[0] = GPIO_NOP;
	outputs.shB[0] = GPIO_NOP;

}


void ViaScanner::slowConversionCallback(void) {

	controls.update();
	scanner.parseControls(&controls);

	uint32_t redLevel = abs(scanner.xInput - 32767) >> 4;
	uint32_t greenLevel = scanner.zIndex >> 7;
	uint32_t blueLevel = abs(scanner.xInput - 32767) >> 4;

	updateRGBDisplay(redLevel, greenLevel, blueLevel, runtimeDisplay);

}

