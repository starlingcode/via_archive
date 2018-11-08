
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

	switchWavetableX(wavetableArray[0]);
	switchWavetableY(wavetableArray[0]);

	scanner.xTable = (uint32_t *) &wavetableXRead[0][0];
	scanner.yTable = (uint32_t *) &wavetableYRead[0][0];

	inputs.trigInput = 1;
	inputs.auxTrigInput = 0;
	reverseSignal = 1;

	for (int i = 0; i < (SCANNER_BUFFER_SIZE * 2); i++) {
		inputs.auxTrigSamples[i] = 1;
		reverseBuffer[i] = 1;
	}

	scannerUI.initialize();

}

