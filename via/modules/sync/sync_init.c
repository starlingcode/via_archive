#include "via_platform_binding.h"
#include "tsl_user.h"
#include "eeprom.h"
#include "user_interface.h"

#include "sync.h"

// eeprom storage array
extern uint16_t VirtAddVarTab[NB_OF_VAR] = { 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7,
		0x8, 0x9, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16 };

void sync_init(sync_signal_set * signals) {

	signals->controls = &controlRateInput;
	signals->inputs = &audioRateInput;
	signals->outputs = &audioRateOutput;
	signals->parameters = &syncParameters;

	via_ioStreamInit(&audioRateInput, &audioRateOutput, SYNC_BUFFER_SIZE);

	sync_initPhaseDist();

	sync_initializeUICallbacks();

	// initialize our touch sensors
	tsl_user_Init();
	uiInitialize();

	sync_fillWavetableArray();

	sync_switchWavetable(sync_wavetableArray[0], signals);

//	displaySHMode = displaySH_Off;
//	displaySyncMode = displaySync_Hard;
//	displayXCVMode = displayXCV_FM;
//	displayMorphMode = displayMorph_Morph;

	signals->parameters->fm = signals->inputs->cv2VirtualGround;
	signals->parameters->pm = signals->inputs->cv2VirtualGround;
	signals->parameters->pwm = signals->inputs->cv2VirtualGround;

	signals->parameters->morphMod = signals->inputs->cv3Samples;

	signals->parameters->phaseReset = 1;

}

