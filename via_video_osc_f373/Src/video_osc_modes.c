/*
 * video_osc_modes.c
 *
 *  Created on: Aug 21, 2018
 *      Author: willmitchell
 */

#include <video_osc.h>

void video_osc_handleButton6ModeChange(int mode) {

	switch (mode) {
	case none:
		video_osc_signals.parameters->shOn = 0;
		//displaySHMode = &displaySH_Off;
		break;
	case decimate:
		video_osc_signals.parameters->shOn = 1;
		//displaySHMode = &displaySH_On;
		break;
	}

	SH_A_TRACK
	;
	SH_B_TRACK
	;
}

void video_osc_handleButton2ModeChange(int mode) {

	video_osc_switchWavetable(video_osc_wavetableArray[mode], &video_osc_signals);

}

void video_osc_handleButton3ModeChange(int mode) {

	switch (mode) {
	case FM:
		video_osc_signals.parameters->fm = video_osc_signals.inputs->cv2Samples;
		video_osc_signals.parameters->pm = video_osc_signals.inputs->cv2VirtualGround;
		//displayXCVMode = &displayXCV_FM;
		break;
	case PM:
		video_osc_signals.parameters->fm = video_osc_signals.inputs->cv2VirtualGround;
		video_osc_signals.parameters->pm = video_osc_signals.inputs->cv2Samples;
		//displayXCVMode = &displayXCV_PM;
		break;
	}

}

void video_osc_handleButton4ModeChange(int mode) {

	video_osc_signals.parameters->syncMode = mode;
	// sync modes video_osc_handled in IRQ video_osc_handler
	if (mode == hard) {
		//displaySyncMode = &displaySync_Hard;
	} else {
		//displaySyncMode = &displaySync_Soft;
	}

}

void video_osc_handleButton5ModeChange(int mode) {

	video_osc_switchWavetable(video_osc_wavetableArray[mode], &video_osc_signals);
}

void video_osc_handleButton1ModeChange(int mode) {

	switch (mode) {
	case morphCV:
		video_osc_signals.parameters->morphMod = video_osc_signals.inputs->cv3Samples;
		video_osc_signals.parameters->pwm = video_osc_signals.inputs->cv3VirtualGround;
		//displayMorphMode = &displayMorph_Morph;
		break;
	case pwmCV:
		video_osc_signals.parameters->morphMod = video_osc_signals.inputs->cv3VirtualGround;
		video_osc_signals.parameters->pwm = video_osc_signals.inputs->cv3Samples;
		//displayMorphMode = &displayMorph_PMW;
		break;
	}

}
