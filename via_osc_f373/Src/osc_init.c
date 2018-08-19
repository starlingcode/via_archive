#include "via_io_binding.h"
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

void oscInit(viaSignals * signals) {

	signals->controls = &controlRateInput;
	signals->inputs = &audioRateInput;
	signals->outputs = &audioRateOutput;
	signals->softwareSignals = &softwareSignals;

	viaSignalInit(&audioRateInput, &audioRateOutput, BUFFER_SIZE);

	initializeUICallbacks();

	// initialize our touch sensors
	tsl_user_Init();
	uiInitialize();

	fillFamilyArray();

	displaySHMode = displaySH_Off;
	displaySyncMode = displaySync_Hard;
	displayXCVMode = displayXCV_FM;
	displayMorphMode = displayMorph_Morph;

	signals->softwareSignals->fm = signals->inputs->cv2Samples;
	signals->softwareSignals->pm = signals->inputs->cv2VirtualGround;
	signals->softwareSignals->morphMod = signals->inputs->cv3Samples;
	signals->softwareSignals->pwm = signals->inputs->cv3VirtualGround;

	signals->softwareSignals->syncInput = 1;
	signals->softwareSignals->reverseInput = 1;


}


