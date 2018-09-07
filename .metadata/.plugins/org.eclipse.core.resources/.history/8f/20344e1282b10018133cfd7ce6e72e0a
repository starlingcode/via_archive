/*
 * osc_modes.c
 *
 *  Created on: Aug 21, 2018
 *      Author: willmitchell
 */

#include "osc.h"

void osc_handleButton1ModeChange(int mode) {

	switch (mode) {
	case none:
		osc_signals.parameters->shOn = 0;
		//displaySHMode = &displaySH_Off;
		break;
	case decimate:
		osc_signals.parameters->shOn = 1;
		//displaySHMode = &displaySH_On;
		break;
	}

	SH_A_TRACK
	;
	SH_B_TRACK
	;
}

void osc_handleButton2ModeChange(int mode) {

	osc_switchWavetable(osc_wavetableArray[mode], &osc_signals);

}

void osc_handleButton3ModeChange(int mode) {

	switch (mode) {
	case FM:
		osc_signals.parameters->fm = osc_signals.inputs->cv2Samples;
		osc_signals.parameters->pm = osc_signals.inputs->cv2VirtualGround;
		//displayXCVMode = &displayXCV_FM;
		break;
	case PM:
		osc_signals.parameters->fm = osc_signals.inputs->cv2VirtualGround;
		osc_signals.parameters->pm = osc_signals.inputs->cv2Samples;
		//displayXCVMode = &displayXCV_PM;
		break;
	}

}

void osc_handleButton4ModeChange(int mode) {

	osc_signals.parameters->syncMode = mode;
	// sync modes osc_handled in IRQ osc_handler
	if (mode == hard) {
		//displaySyncMode = &displaySync_Hard;
	} else {
		//displaySyncMode = &displaySync_Soft;
	}

}

void osc_handleButton5ModeChange(int mode) {

	osc_switchWavetable(osc_wavetableArray[mode], &osc_signals);
}

void osc_handleButton6ModeChange(int mode) {

	switch (mode) {
	case morphCV:
		osc_signals.parameters->morphMod = osc_signals.inputs->cv3Samples;
		osc_signals.parameters->pwm = osc_signals.inputs->cv3VirtualGround;
		//displayMorphMode = &displayMorph_Morph;
		break;
	case pwmCV:
		osc_signals.parameters->morphMod = osc_signals.inputs->cv3VirtualGround;
		osc_signals.parameters->pwm = osc_signals.inputs->cv3Samples;
		//displayMorphMode = &displayMorph_PMW;
		break;
	}

}
