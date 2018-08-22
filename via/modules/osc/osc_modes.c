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
		signals.parameters->shOn = 0;
		//displaySHMode = &displaySH_Off;
		break;
	case decimate:
		signals.parameters->shOn = 1;
		//displaySHMode = &displaySH_On;
		break;
	}

	SH_A_TRACK;
	SH_B_TRACK;
}

void osc_handleButton2ModeChange(int mode) {

	osc_switchWavetable(osc_wavetableArray[mode], &signals);

}

void osc_handleButton3ModeChange(int mode) {

	switch (mode) {
	case FM:
		signals.parameters->fm = signals.inputs->cv2Samples;
		signals.parameters->pm = signals.inputs->cv2VirtualGround;
		//displayXCVMode = &displayXCV_FM;
		break;
	case PM:
		signals.parameters->fm = signals.inputs->cv2VirtualGround;
		signals.parameters->pm = signals.inputs->cv2Samples;
		//displayXCVMode = &displayXCV_PM;
		break;
	}

}

void osc_handleButton4ModeChange(int mode) {

	signals.parameters->syncMode = mode;
	// sync modes osc_handled in IRQ osc_handler
	if (button4Mode == hard) {
		//displaySyncMode = &displaySync_Hard;
	} else {
		//displaySyncMode = &displaySync_Soft;
	}

}

void osc_handleButton5ModeChange(int mode) {

	osc_switchWavetable(osc_wavetableArray[mode], &signals);
}

void osc_handleButton6ModeChange(int mode) {

	switch (mode) {
	case morphCV:
		signals.parameters->morphMod = signals.inputs->cv3Samples;
		signals.parameters->pwm = signals.inputs->cv3VirtualGround;
		//displayMorphMode = &displayMorph_Morph;
		break;
	case pwmCV:
		signals.parameters->morphMod = signals.inputs->cv3VirtualGround;
		signals.parameters->pwm = signals.inputs->cv3Samples;
		//displayMorphMode = &displayMorph_PMW;
		break;
	}


}

void osc_handleAux4ModeChange(int mode) {


}
