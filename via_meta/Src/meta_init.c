#include "via_rev5_hardware_io.h"
#include "tsl_user.h"
#include "eeprom.h"
#include "user_interface.h"

#include "../inc/meta_dsp.h"
#include "../inc/meta_fill_buffer.h"
#include "../inc/meta_main_states.h"
#include "../inc/meta_modes.h"
#include "../inc/meta_tables.h"
#include "../inc/meta_ui_implementation.h"

// eeprom storage array
extern uint16_t VirtAddVarTab[NB_OF_VAR] = {0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16};

void metaInit(void) {

	initializeUICallbacks();

	// initialize our touch sensors
	tsl_user_Init();
	uiInitialize();

	fillFamilyArray();

	getIncrements = getIncrementsAudio;
	advancePhase = advancePhaseNoRetrig;
	getSamples = getSamplesNoPWM;
	handleLoop = handleLoopOn;
	calculateSH = calculateSHMode1;
	updateRGB = updateRGBAudio;
	calculateLogicA = calculateLogicAGate;
	calculateDac3 = calculateDac3Phasor;

	noRetrigStateMachine = noRetrigAttackState;

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
	input1.triggerInput = syncBuffer1;
	input1.gateInput = reverseBuffer1;


	input2.cv2Input = t2CVBuffer2;
	input2.cv3Input = morphCVBuffer2;
	input2.triggerInput = syncBuffer2;
	input2.gateInput = reverseBuffer2;

	scanner_signals.controls = &controlRateInput;
	scanner_signals.inputRead = &input1;
	scanner_signals.inputWrite = &input2;
	scanner_signals.outputRead = &output1;
	scanner_signals.outputWrite = &output2;
	scanner_signals.softwareSignals = &softwareSignals;

}

