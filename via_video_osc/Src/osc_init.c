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

void osc_init(void) {

	initializeUICallbacks();

	// initialize our touch sensors
	tsl_user_Init();
	uiInitialize();

	fillFamilyArray();

	displaySHMode = displaySH_Off;
	displaySyncMode = displaySync_Hard;
	displayXCVMode = displayXCV_FM;
	displayMorphMode = displayMorph_Morph;

	signals.inputs->fm = cv2SampleBuffer;
	signals.inputs->pm = virtualGround;
	signals.inputs->morphMod = cv3SampleBuffer;
	signals.inputs->pwm = virtualGround;


	signals.inputs->syncInput = 1;
	signals.inputs->reverseInput = 1;

}

void viaSignalInit(void) {

	virtualGround[0] = 0;
	virtualGround[1] = 0;

	audioRateOutput.dac1Samples = dac1SampleBuffer;
	audioRateOutput.dac2Samples = dac2SampleBuffer;
	audioRateOutput.dac3Samples = dac3SampleBuffer;

	signals.controls = &controlRateInput;
	signals.inputs = &audioRateInput;
	signals.outputs= &audioRateOutput;
	signals.softwareSignals = &softwareSignals;

}

