#include "via_rev5_hardware_io.h"
#include "tsl_user.h"
#include "eeprom.h"
#include "user_interface.h"
#include "scanner_dsp.h"
#include "scanner_tables.h"
#include "scanner_ui_implementation.h"
#include "scanner_fill_buffer.h"
#include "scanner_modes.h"
#include "scanner_main_states.h"

// eeprom storage array
extern uint16_t VirtAddVarTab[NB_OF_VAR] = {0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16};

void scannerInit(void) {

	initializeUICallbacks();

	// initialize our touch sensors
	tsl_user_Init();
	uiInitialize();

	fillFamilyArray();

	uiSetLEDA = uiSetLEDAOff;
	uiSetLEDB = uiSetLEDBOff;
	uiSetLEDC = uiSetLEDCOff;
	uiSetLEDD = uiSetLEDDOff;

	// initialize our touch sensors
	tsl_user_Init();
	uiInitialize();

	// initialize the main state machine to handle the UI first
	main_state = &main_idle;

}

void viaSignalInit(void) {

	// initialize double buffers used for DSP
	output1.samples = sampleBuffer1;
	output2.samples = sampleBuffer2;

	output1.dac3Samples = dac3SampleBuffer1;
	output2.dac3Samples = dac3SampleBuffer2;

	output1.shAHandler = shABuffer1;
	output2.shAHandler = shABuffer2;

	output1.shBHandler = shBBuffer1;
	output2.shBHandler = shBBuffer2;

	output1.logicAHandler = logicABuffer1;
	output2.logicAHandler = logicABuffer2;

	output1.auxLogicHandler = auxLogicBuffer1;
	output2.auxLogicHandler = auxLogicBuffer2;

	input1.cv2Input = t2CVBuffer1;
	input1.cv3Input = morphCVBuffer1;
	input1.syncBuffer = syncBuffer1;


	input2.cv2Input = t2CVBuffer2;
	input2.cv3Input = morphCVBuffer2;
	input2.syncBuffer = syncBuffer2;

	signals.controls = &controlRateInput;
	signals.inputRead = &input1;
	signals.inputWrite = &input2;
	signals.outputRead = &output1;
	signals.outputWrite = &output2;
	signals.softwareSignals = &softwareSignals;

}

