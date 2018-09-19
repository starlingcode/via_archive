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

	setLogicOut(readIndex, runtimeDisplay);
	inputs.trigSamples[readIndex] = inputs.trigInput;
	inputs.trigInput = 1;
	reverseBuffer[readIndex] = reverseSignal;
	inputs.auxTrigSamples[readIndex] = inputs.auxTrigInput;

	readIndex++;

	readIndex &= SCANNER_BUFFER_SIZE*2 - 1;

}

void ViaScanner::halfTransferCallback(void) {

	scanner.hardSync = inputs.trigSamples;
	scanner.reverse = reverseBuffer;

	scanner.fillBuffer(&inputs, &controls,
			(int *) wavetableXRead, (int *) wavetableYRead,
			0, SCANNER_BUFFER_SIZE);

	arm_shift_q31((q31_t *) scanner.xInput, -4, (q31_t *) outputs.dac3Samples, 8);

	for (int i = 0; i < SCANNER_BUFFER_SIZE; i++) {
		outputs.dac2Samples[i] = scanner.altitude[i];
		outputs.dac1Samples[i] = 4095 - scanner.altitude[i];
		outputs.dac3Samples[i] = (fix16_mul(scanner.xIndexBuffer[i],
				scanner.yIndexBuffer[i] - 32767) >> 4) + 2048;
		outputs.logicA[i] = GET_ALOGIC_MASK(scanner.xDeltaBuffer[i] &
				scanner.yDeltaBuffer[i]);
		outputs.auxLogic[i] = GET_EXPAND_LOGIC_MASK(outputs.dac3Samples[i] >> 11);
		outputs.shA[i] = GPIO_NOP;
		outputs.shB[i] = GPIO_NOP;
	}

}

void ViaScanner::transferCompleteCallback(void) {

	scanner.hardSync = inputs.trigSamples + SCANNER_BUFFER_SIZE;
	scanner.reverse = reverseBuffer + SCANNER_BUFFER_SIZE;

	scanner.fillBuffer(&inputs, &controls,
			(int *) wavetableXRead, (int *) wavetableYRead,
			SCANNER_BUFFER_SIZE, SCANNER_BUFFER_SIZE);

	arm_shift_q31((q31_t *) scanner.xInput, -4, ((q31_t *) outputs.dac3Samples) + 8, 8);

	for (int i = 0; i < SCANNER_BUFFER_SIZE; i++) {
		outputs.dac2Samples[i + SCANNER_BUFFER_SIZE] = scanner.altitude[i];
		outputs.dac1Samples[i + SCANNER_BUFFER_SIZE] = 4095 - scanner.altitude[i];
		outputs.dac3Samples[i + SCANNER_BUFFER_SIZE] = (fix16_mul(scanner.xIndexBuffer[i],
				scanner.yIndexBuffer[i] - 32767) >> 4) + 2048;
		outputs.logicA[i + SCANNER_BUFFER_SIZE] = GET_ALOGIC_MASK(scanner.xDeltaBuffer[i] &
				scanner.yDeltaBuffer[i]);
		outputs.auxLogic[i + SCANNER_BUFFER_SIZE] = GET_EXPAND_LOGIC_MASK(
				outputs.dac3Samples[i + SCANNER_BUFFER_SIZE] >> 11);
//		outputs.shA[i + SCANNER_BUFFER_SIZE] = GET_SH_A_MASK(inputs.auxTrigSamples[i + SCANNER_BUFFER_SIZE]);
//		outputs.shB[i + SCANNER_BUFFER_SIZE] = GET_SH_B_MASK(inputs.auxTrigSamples[i + SCANNER_BUFFER_SIZE]);
		outputs.shA[i + SCANNER_BUFFER_SIZE] = GPIO_NOP;
		outputs.shB[i + SCANNER_BUFFER_SIZE] = GPIO_NOP;

	}

}

void ViaScanner::cv2HalfTransferCallback(void) {

	arm_offset_q31(((q31_t *) inputs.cv2Samples), 32767, (q31_t *) scanner.xInput, SCANNER_BUFFER_SIZE);

}

void ViaScanner::cv2TransferCompleteCallback(void) {

	arm_offset_q31(((q31_t *) inputs.cv2Samples) + SCANNER_BUFFER_SIZE, 32767, (q31_t *) scanner.xInput, SCANNER_BUFFER_SIZE);

}

void ViaScanner::cv3HalfTransferCallback(void) {

	arm_offset_q31(((q31_t *) inputs.cv3Samples), 32767, (q31_t *) scanner.yInput, SCANNER_BUFFER_SIZE);

}

void ViaScanner::cv3TransferCompleteCallback(void) {

	arm_offset_q31(((q31_t *) inputs.cv3Samples)  + SCANNER_BUFFER_SIZE, 32767, (q31_t *) scanner.yInput, SCANNER_BUFFER_SIZE);
}

void ViaScanner::slowConversionCallback(void) {

	controls.update();
	scanner.parseControls(&controls);

	uint32_t redLevel = abs(scanner.xInput[0] - 32767) >> 4;
	uint32_t greenLevel = scanner.zIndex >> 7;
	uint32_t blueLevel = abs(scanner.yInput[0] - 32767) >> 4;

	updateRGBDisplay(redLevel, greenLevel, blueLevel, runtimeDisplay);

}

