/*
 * modes.cpp
 *
 *  Created on: Sep 12, 2018
 *      Author: willmitchell
 */

#include "meta.hpp"

void ViaMeta::handleButton1ModeChange(int mode) {

	switch (mode) {
	case nosampleandhold:
		calculateSH = &ViaMeta::calculateSHMode1;
		break;
	case a:
		calculateSH = &ViaMeta::calculateSHMode2;
		break;
	case b:
		calculateSH = &ViaMeta::calculateSHMode3;
		break;
	case ab:
		calculateSH = &ViaMeta::calculateSHMode4;
		break;
	case halfdecimate:
		calculateSH = &ViaMeta::calculateSHMode5;
		break;
	case meta_decimate:
		calculateSH = &ViaMeta::calculateSHMode6;
		break;
	}

	SH_A_TRACK;
	SH_B_TRACK;
}

void ViaMeta::handleButton2ModeChange(int mode) {

	switchWavetable(wavetableArray[metaUI.FREQ_MODE][mode]);

}

void ViaMeta::handleButton3ModeChange(int mode) {

	switch (mode) {
	case audio:
		if (metaUI.LOOP_MODE == noloop) {
			metaControllerGenerateIncrements = metaControllerGenerateIncrementsDrum;
			metaControllerParseControls = metaControllerParseControlsDrum;
			signals.meta_parameters->fm = drumFullScale;
			drumMode = &ViaMeta::drumModeOn;
			metaControllerLoopHandler = handleLoopOn;
			signals.meta_parameters->loopMode = 1;
			handleButton4ModeChange(0);
			handleAux3ModeChange(metaUI.DRUM_MODE);
		} else {
			metaControllerParseControls = metaControllerParseControlsAudio;
			metaControllerGenerateIncrements = metaControllerGenerateIncrementsAudio;
			signals.meta_parameters->fm = signals.inputs->cv2Samples;
			signals.wavetable_parameters->morphScale = drumFullScale;
			drumMode = &ViaMeta::drumModeOff;
		}
		switchWavetable(wavetableArray[mode][metaUI.TABLE]);
		//updateRGB = updateRGBAudio;
		break;
	case env:
		metaControllerParseControls = metaControllerParseControlsEnv;
		metaControllerGenerateIncrements = metaControllerGenerateIncrementsEnv;
		if (metaUI.LOOP_MODE == noloop) {
			switchWavetable(wavetableArray[mode][metaUI.TABLE]);
			signals.meta_parameters->fm = signals.inputs->cv2Samples;
			signals.wavetable_parameters->morphScale = drumFullScale;
			drumMode = &ViaMeta::drumModeOff;
			metaControllerLoopHandler = handleLoopOff;
			signals.meta_parameters->loopMode = 0;
			handleButton4ModeChange(metaUI.TRIG_MODE);
		}
		//updateRGB = updateRGBSubAudio;
		break;
	case seq:
		metaControllerParseControls = metaControllerParseControlsSeq;
		metaControllerGenerateIncrements = metaControllerGenerateIncrementsSeq;
		switchWavetable(wavetableArray[mode][metaUI.TABLE]);
		break;
	}

}

void ViaMeta::handleButton4ModeChange(int mode) {

	switch (mode) {
	case noretrigger:
		metaControllerIncrementArbiter = noRetrigAttackState;
		break;
	case meta_hardsync:
		metaControllerIncrementArbiter = hardSyncAttackState;
		break;
	case nongatedretrigger:
		metaControllerIncrementArbiter = envAttackState;
		break;
	case gated:
		metaControllerIncrementArbiter = gateAttackState;
		signals.meta_parameters->phase = 0;
		signals.meta_parameters->gateOn = 1;
		break;
	case meta_pendulum:
		metaControllerIncrementArbiter = pendulumForwardAttackState;
		signals.meta_parameters->gateOn = 0;
		break;
	}

}

void ViaMeta::handleButton5ModeChange(int mode) {

	switchWavetable(wavetableArray[metaUI.FREQ_MODE][mode]);

}

void ViaMeta::handleButton6ModeChange(int mode) {

	switch (mode) {
	case noloop:
		if (metaUI.FREQ_MODE == audio) {
			handleAux3ModeChange(metaUI.DRUM_MODE);
			handleButton3ModeChange(0);
			handleButton4ModeChange(0);
		} else {
			metaControllerLoopHandler = handleLoopOff;
			signals.meta_parameters->loopMode = 0;
		}
		break;
	case looping:
		if (metaUI.FREQ_MODE == audio) {
			handleButton3ModeChange(0);
			handleButton4ModeChange(metaUI.TRIG_MODE);
		}
		metaControllerLoopHandler = handleLoopOn;
		signals.meta_parameters->loopMode = 1;
		break;
	}

}

void ViaMeta::handleAux1ModeChange(int mode) {


}

void ViaMeta::handleAux2ModeChange(int mode) {

	switch (mode) {
	case releaseGate:
		calculateLogicA = &ViaMeta::calculateLogicAReleaseGate;
		break;
	case attackGate:
		calculateLogicA = &ViaMeta::calculateLogicAAttackGate;
		break;
	}

}

void ViaMeta::handleAux3ModeChange(int mode) {

	switch (mode) {
	case pitchMorphAmp:
		signals.meta_parameters->fm = (int16_t*) signals.drum_parameters->output;
		signals.wavetable_parameters->morphScale = (int16_t*) signals.drum_parameters->output;
		break;
	case morphAmp:
		signals.meta_parameters->fm = drumFullScale;
		signals.wavetable_parameters->morphScale = (int16_t*) signals.drum_parameters->output;
		break;
	case pitchAmp:
		signals.meta_parameters->fm = (int16_t*) signals.drum_parameters->output;
		signals.wavetable_parameters->morphScale = drumFullScale;
		break;
	case amp:
		signals.meta_parameters->fm = drumFullScale;
		signals.wavetable_parameters->morphScale = drumFullScale;
		break;
	}

}

void ViaMeta::handleAux4ModeChange(int mode) {

	switch (mode) {
	case phasor:
		calculateDac3 = &ViaMeta::calculateDac3Phasor;
		break;
	case contour:
		calculateDac3 = &ViaMeta::calculateDac3Contour;
		break;
	}

}



