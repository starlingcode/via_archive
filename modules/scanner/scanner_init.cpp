
#include "scanner.hpp"

void ViaScanner::init(void) {

	initializeAuxOutputs();

	scanner.bufferSize = SCANNER_BUFFER_SIZE;
	scanner.init();

	inputs.init(SCANNER_BUFFER_SIZE);
	outputs.init(SCANNER_BUFFER_SIZE);
	outputBufferSize = SCANNER_BUFFER_SIZE;
	inputBufferSize = SCANNER_BUFFER_SIZE;


	scanner.hardSync = inputs.trigSamples;
	scanner.reverse = reverseBuffer;
	scanner.sh = inputs.auxTrigSamples;

	fillWavetableArray();

	switchWavetableX(wavetableArray[0]);
	switchWavetableY(wavetableArray[0]);

	inputs.trigInput = 1;
	inputs.auxTrigInput = 0;
	reverseSignal = 1;

	for (int i = 0; i < (SCANNER_BUFFER_SIZE * 2); i++) {
		inputs.auxTrigSamples[i] = 1;
		reverseBuffer[i] = 1;
	}

	scannerUI.initialize();

}

