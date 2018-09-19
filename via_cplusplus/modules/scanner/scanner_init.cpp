
#include "scanner.hpp"

// eeprom storage array
extern uint16_t VirtAddVarTab[NB_OF_VAR] = { 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7,
		0x8, 0x9, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16 };

void ViaScanner::init(void) {

	initializeAuxOutputs();

	scanner.bufferSize = SCANNER_BUFFER_SIZE;
	scanner.init();

	inputs.init(SCANNER_BUFFER_SIZE);
	outputs.init(SCANNER_BUFFER_SIZE);
	bufferSize = SCANNER_BUFFER_SIZE;

	scanner.hardSync = inputs.trigSamples;
	scanner.reverse = reverseBuffer;
	scanner.sh = inputs.auxTrigSamples;

	// initialize our touch sensors
	tsl_user_Init();
	scannerUI.initialize();

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

	//ioStreamInit();

}

