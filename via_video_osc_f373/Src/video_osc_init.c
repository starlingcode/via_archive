#include "via_platform_binding.h"
#include "tsl_user.h"
#include "eeprom.h"
#include "user_interface.h"

#include "video_osc.h"

// eeprom storage array
extern uint16_t VirtAddVarTab[NB_OF_VAR] = { 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7,
		0x8, 0x9, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16 };

void video_osc_init(video_osc_signal_set * signals) {

	signals->controls = &controlRateInput;
	signals->inputs = &audioRateInput;
	signals->outputs = &audioRateOutput;
	signals->parameters = &oscParameters;

	via_ioStreamInit(&audioRateInput, &audioRateOutput, VIDEO_OSC_BUFFER_SIZE);

	video_osc_initPhaseDist();

	video_osc_initializeUICallbacks();

	// initialize our touch sensors
	//tsl_user_Init();
	uiInitialize();

	video_osc_fillWavetableArray();

	video_osc_switchWavetable(video_osc_wavetableArray[0], signals);

//	displaySHMode = displaySH_Off;
//	displaySyncMode = displaySync_Hard;
//	displayXCVMode = displayXCV_FM;
//	displayMorphMode = displayMorph_Morph;

	signals->parameters->fm = signals->inputs->cv2Samples;
	signals->parameters->pm = signals->inputs->cv2Samples;
	signals->parameters->morphMod = signals->inputs->cv3Samples;
	signals->parameters->pwm = signals->inputs->cv3Samples;

	signals->parameters->syncInput = 1;
	signals->parameters->reverseInput = 1;

}

