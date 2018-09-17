#include "scanner.hpp"

void ViaScanner::mainRisingEdgeCallback(void) {

	if (scanner.syncMode) {
		system.inputs.trigInput = 0;
	} else {
		reverseSignal *= -1;
	}

}

void ViaScanner::mainFallingEdgeCallback(void) {

}

void ViaScanner::auxRisingEdgeCallback(void) {
	system.inputs.auxTrigInput = 1;
}
void ViaScanner::auxFallingEdgeCallback(void) {
	system.inputs.auxTrigInput = 0;
}

void ViaScanner::buttonPressedCallback(void) {
	;
}
void ViaScanner::buttonReleasedCallback(void) {
	;
}

void ViaScanner::ioProcessCallback(void) {

	system.setLogicOut(readIndex, runtimeDisplay);
	system.inputs.trigSamples[readIndex] = system.inputs.trigInput;
	system.inputs.trigInput = 1;
	reverseBuffer[readIndex] = reverseSignal;
	system.inputs.auxTrigSamples[readIndex] = system.inputs.auxTrigInput;

	readIndex++;

	readIndex &= SCANNER_BUFFER_SIZE*2 - 1;

}

void ViaScanner::halfTransferCallback(void) {

	scanner.hardSync = system.inputs.trigSamples;
	scanner.reverse = reverseBuffer;


	scanner.fillBuffer(&system.inputs, &system.controls,
			(int *) wavetableXRead, (int *) wavetableYRead,
			0, SCANNER_BUFFER_SIZE);

	for (int i = 0; i < SCANNER_BUFFER_SIZE; i++) {
		system.outputs.dac2Samples[i] = scanner.altitude[i];
		system.outputs.dac1Samples[i] = 4095 - scanner.altitude[i];
		system.outputs.dac3Samples[i] = fix16_mul(scanner.xInput[i],
				scanner.yInput[i]) >> 4;
		system.outputs.logicA[i] = GET_ALOGIC_MASK(scanner.xDeltaBuffer[i] &
				scanner.yDeltaBuffer[i]);
		system.outputs.auxLogic[i] = GET_EXPAND_LOGIC_MASK(system.outputs.dac3Samples[i] >> 11);
		system.outputs.shA[i] = GET_SH_A_MASK(
				system.inputs.auxTrigSamples[i]);
		system.outputs.shB[i] = GET_SH_B_MASK(
				system.inputs.auxTrigSamples[i]);
	}

}

void ViaScanner::transferCompleteCallback(void) {

	scanner.hardSync = system.inputs.trigSamples + SCANNER_BUFFER_SIZE;
	scanner.reverse = reverseBuffer + SCANNER_BUFFER_SIZE;


	scanner.fillBuffer(&system.inputs, &system.controls,
			(int *) wavetableXRead, (int *) wavetableYRead,
			SCANNER_BUFFER_SIZE, SCANNER_BUFFER_SIZE);


	for (int i = 0; i < SCANNER_BUFFER_SIZE; i++) {
		system.outputs.dac2Samples[i + SCANNER_BUFFER_SIZE] = scanner.altitude[i];
		system.outputs.dac1Samples[i + SCANNER_BUFFER_SIZE] = 4095 - scanner.altitude[i];
		system.outputs.dac3Samples[i + SCANNER_BUFFER_SIZE] = fix16_mul(scanner.xInput[i],
				scanner.yInput[i]) >> 4;
		system.outputs.logicA[i + SCANNER_BUFFER_SIZE] = GET_ALOGIC_MASK(scanner.xDeltaBuffer[i] &
				scanner.yDeltaBuffer[i]);
		system.outputs.auxLogic[i + SCANNER_BUFFER_SIZE] = GET_EXPAND_LOGIC_MASK(
				system.outputs.dac3Samples[i + SCANNER_BUFFER_SIZE] >> 11);
		system.outputs.shA[i + SCANNER_BUFFER_SIZE] = GET_SH_A_MASK(system.inputs.auxTrigSamples[i + SCANNER_BUFFER_SIZE]);
		system.outputs.shB[i + SCANNER_BUFFER_SIZE] = GET_SH_B_MASK(system.inputs.auxTrigSamples[i + SCANNER_BUFFER_SIZE]);
	}

}

void ViaScanner::cv2HalfTransferCallback(void) {

	int16_t * cv2ReadIndex = system.inputs.cv2Samples;
	int * cv2WriteIndex = scanner.xInput;
	for (int i = 0; i < SCANNER_BUFFER_SIZE; i++) {
		int cv2Sample = (int) cv2ReadIndex[i*2];
		cv2Sample += 32768;
		cv2WriteIndex[i] = cv2Sample;
	}
}

void ViaScanner::cv2TransferCompleteCallback(void) {

	int16_t * cv2ReadIndex = system.inputs.cv2Samples + SCANNER_BUFFER_SIZE*2;
	int * cv2WriteIndex = scanner.xInput;
	for (int i = 0; i < SCANNER_BUFFER_SIZE; i++) {
		int cv2Sample = (int) cv2ReadIndex[i*2];
		cv2Sample += 32768;
		cv2WriteIndex[i] = cv2Sample;
	}
}

void ViaScanner::cv3HalfTransferCallback(void) {

	int16_t * cv3ReadIndex = system.inputs.cv3Samples;
	int * cv3WriteIndex = scanner.yInput;
	for (int i = 0; i < SCANNER_BUFFER_SIZE; i++) {
		int cv3Sample = (int) cv3ReadIndex[i*2];
		cv3Sample += 32768;
		cv3WriteIndex[i] = cv3Sample;
	}
}

void ViaScanner::cv3TransferCompleteCallback(void) {

	int16_t * cv3ReadIndex = system.inputs.cv3Samples + SCANNER_BUFFER_SIZE*2;
	int * cv3WriteIndex = scanner.yInput;
	for (int i = 0; i < SCANNER_BUFFER_SIZE; i++) {
		int cv3Sample = (int) cv3ReadIndex[i*2];
		cv3Sample += 32768;
		cv3WriteIndex[i] = cv3Sample;
	}
}

void ViaScanner::slowConversionCallback(void) {

	system.controls.update();
	scanner.parseControls(&system.controls);

	uint32_t redLevel = abs(scanner.xInput[0] - 32767) >> 4;
	uint32_t greenLevel = scanner.zIndex >> 7;
	uint32_t blueLevel = abs(scanner.yInput[0] - 32767) >> 4;

	if (runtimeDisplay) {
		updateRGBDisplay(redLevel, greenLevel, blueLevel);
	}

}

