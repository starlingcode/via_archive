
#include "scanner.hpp"

void ViaScanner::init(void) {

	initializeAuxOutputs();

	scanner.bufferSize = SCANNER_BUFFER_SIZE;
	scanner.init();

	inputs.init(SCANNER_BUFFER_SIZE);
	outputs.init(SCANNER_BUFFER_SIZE);
	outputBufferSize = SCANNER_BUFFER_SIZE;
	inputBufferSize = 1;

	scanner.hardSync = 1;
	scanner.reverse = 1;

	fillWavetableArray();

	inputs.trigInput = 1;
	inputs.auxTrigInput = 0;
	reverseSignal = 1;

	scannerUI.initialize();

	uint32_t optionBytes = readOptionBytes();
	uint32_t ob1Data = optionBytes &0xFFFF;
	uint32_t ob2Data = optionBytes &0xFFFF;

	if (ob1Data == 255 && ob2Data == 254) {
		readCalibrationPacket();
		scannerUI.writeStockPresets();
		writeOptionBytes(3, 0);
	} else if (ob1Data == 3) {
		readCalibrationPacket();
	} else if (ob1Data != 0) {
		writeOptionBytes(0, 0);
	}

	scanner.cv1Offset = cv1Calibration;
	scanner.cv2Offset = cv2Calibration;
	scanner.cv3Offset = cv3Calibration;

}

