#include "via_rev5_hardware_io.h"
#include "tsl_user.h"
#include "eeprom.h"
#include "user_interface.h"

#include "osc_dsp.h"
#include "osc_fill_buffer.h"
#include "osc_tables.h"

#include "osc_main_states.h"
#include "osc_modes.h"
#include "osc_ui_implementation.h"

// eeprom storage array
extern uint16_t VirtAddVarTab[NB_OF_VAR] = {0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16};

void oscInit(void) {

	initializeVirtualGround();

	initializeUICallbacks();

	// initialize our touch sensors
	tsl_user_Init();
	uiInitialize();

	fillFamilyArray();

	logicAndFilter = &logicAndFilterSHOff;
	prepareCV = &prepareCV_FM_Morph;

	displaySHMode = displaySH_Off;
	displaySyncMode = displaySync_Hard;
	displayXCVMode = displayXCV_FM;
	displayMorphMode = displayMorph_Morph;

	signals.softwareSignals->reverseSignal = 1;

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
	input1.hardSyncInput = syncBuffer1;
	input1.reverseInput = reverseBuffer1;


	input2.cv2Input = t2CVBuffer2;
	input2.cv3Input = morphCVBuffer2;
	input2.hardSyncInput = syncBuffer2;
	input2.reverseInput = reverseBuffer2;

	signals.controls = &controlRateInput;
	signals.inputRead = &input1;
	signals.inputWrite = &input2;
	signals.outputRead = &output1;
	signals.outputWrite = &output2;
	signals.softwareSignals = &softwareSignals;

}

