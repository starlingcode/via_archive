/*
 * modes.cpp
 *
 *  Created on: Sep 12, 2018
 *      Author: willmitchell
 */

#include "meta.hpp"

void ViaMeta::ViaMetaUI::handleButton1ModeChange(int mode) {

	switch (mode) {
	case nosampleandhold:
		calculateSH = calculateSHMode1;
		break;
	case a:
		calculateSH = calculateSHMode2;
		break;
	case b:
		calculateSH = calculateSHMode3;
		break;
	case ab:
		calculateSH = calculateSHMode4;
		break;
	case halfdecimate:
		calculateSH = calculateSHMode5;
		break;
	case meta_decimate:
		calculateSH = calculateSHMode6;
		break;
	}

	SH_A_TRACK;
	SH_B_TRACK;
}

void ViaMeta::ViaMetaUI::handleButton2ModeChange(int mode) {

	switchWavetable(wavetableArray[FREQ_MODE][mode]);

}

void ViaMeta::ViaMetaUI::handleButton3ModeChange(int mode) {

	switch (mode) {
	case audio:
		if (LOOP_MODE == noloop) {
			metaControllerGenerateIncrements = metaControllerGenerateIncrementsDrum;
			metaControllerParseControls = metaControllerParseControlsDrum;
			signals.meta_parameters->fm = drumFullScale;
			drumMode = drumModeOn;
			metaControllerLoopHandler = handleLoopOn;
			signals.meta_parameters->loopMode = 1;
			handleButton4ModeChange(0);
			handleAux3ModeChange(DRUM_MODE);
		} else {
			metaControllerParseControls = metaControllerParseControlsAudio;
			metaControllerGenerateIncrements = metaControllerGenerateIncrementsAudio;
			signals.meta_parameters->fm = signals.inputs->cv2Samples;
			signals.wavetable_parameters->morphScale = drumFullScale;
			drumMode = drumModeOff;
		}
		switchWavetable(wavetableArray[mode][TABLE]);
		//updateRGB = updateRGBAudio;
		break;
	case env:
		metaControllerParseControls = metaControllerParseControlsEnv;
		metaControllerGenerateIncrements = metaControllerGenerateIncrementsEnv;
		if (LOOP_MODE == noloop) {
			switchWavetable(wavetableArray[mode][TABLE]);
			signals.meta_parameters->fm = signals.inputs->cv2Samples;
			signals.wavetable_parameters->morphScale = drumFullScale;
			drumMode = drumModeOff;
			metaControllerLoopHandler = handleLoopOff;
			signals.meta_parameters->loopMode = 0;
			handleButton4ModeChange(TRIG_MODE);
		}
		//updateRGB = updateRGBSubAudio;
		break;
	case seq:
		metaControllerParseControls = metaControllerParseControlsSeq;
		metaControllerGenerateIncrements = metaControllerGenerateIncrementsSeq;
		switchWavetable(wavetableArray[mode][TABLE]);
		break;
	}

}

void ViaMeta::ViaMetaUI::handleButton4ModeChange(int mode) {

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

void ViaMeta::ViaMetaUI::handleButton5ModeChange(int mode) {

	switchWavetable(wavetableArray[FREQ_MODE][mode]);

}

void ViaMeta::ViaMetaUI::handleButton6ModeChange(int mode) {

	switch (mode) {
	case noloop:
		if (FREQ_MODE == audio) {
			handleAux3ModeChange(DRUM_MODE);
			handleButton3ModeChange(0);
			handleButton4ModeChange(0);
		} else {
			metaControllerLoopHandler = handleLoopOff;
			signals.meta_parameters->loopMode = 0;
		}
		break;
	case looping:
		if (FREQ_MODE == audio) {
			handleButton3ModeChange(0);
			handleButton4ModeChange(TRIG_MODE);
		}
		metaControllerLoopHandler = handleLoopOn;
		signals.meta_parameters->loopMode = 1;
		break;
	}

}

void ViaMeta::ViaMetaUI::handleAux1ModeChange(int mode) {


}

void ViaMeta::ViaMetaUI::handleAux2ModeChange(int mode) {

	switch (mode) {
	case releaseGate:
		calculateLogicA = calculateLogicAReleaseGate;
		break;
	case attackGate:
		calculateLogicA = calculateLogicAAttackGate;
		break;
	}

}

void ViaMeta::ViaMetaUI::handleAux3ModeChange(int mode) {

	switch (mode) {
	case pitchMorphAmp:
		signals.meta_parameters->fm = signals.drum_parameters->output;
		signals.wavetable_parameters->morphScale = signals.drum_parameters->output;
		break;
	case morphAmp:
		signals.meta_parameters->fm = drumFullScale;
		signals.wavetable_parameters->morphScale = signals.drum_parameters->output;
		break;
	case pitchAmp:
		signals.meta_parameters->fm = signals.drum_parameters->output;
		signals.wavetable_parameters->morphScale = drumFullScale;
		break;
	case amp:
		signals.meta_parameters->fm = drumFullScale;
		signals.wavetable_parameters->morphScale = drumFullScale;
		break;
	}

}

void ViaMeta::ViaMetaUI::handleAux4ModeChange(int mode) {

	switch (mode) {
	case phasor:
		calculateDac3 = calculateDac3Phasor;
		break;
	case contour:
		calculateDac3 = calculateDac3Contour;
		break;
	}

}



