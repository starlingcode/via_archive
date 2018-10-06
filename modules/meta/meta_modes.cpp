/*
 * modes.cpp
 *
 *  Created on: Sep 12, 2018
 *      Author: willmitchell
 */

#include "meta.hpp"

void ViaMeta::handleButton1ModeChange(int32_t mode) {

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

	setSH(0, 0);
}

void ViaMeta::handleButton2ModeChange(int32_t mode) {

	switchWavetable(wavetableArray[metaUI.FREQ_MODE][mode]);

}

void ViaMeta::handleButton3ModeChange(int32_t mode) {

	switch (mode) {
	case audio:
		if (metaUI.LOOP_MODE == noloop) {
			updateRGBDisplay(0, 4095, 4095, 1);
			updateRGB = &ViaMeta::updateRGBDrum;
			metaController.generateIncrements = &MetaController::generateIncrementsDrum;
			metaController.parseControls = &MetaController::parseControlsDrum;
			metaController.fm = drumFullScale;
			drumMode = &ViaMeta::drumModeOn;
			metaController.loopHandler = &MetaController::handleLoopOn;
			metaController.loopMode = 1;
			handleButton4ModeChange(0);
			handleAux3ModeChange(metaUI.DRUM_MODE);
		} else {
			updateRGBDisplay(0, 0, 4095, 1);
			updateRGB = &ViaMeta::updateRGBOsc;
			metaController.parseControls = &MetaController::parseControlsAudio;
			metaController.generateIncrements = &MetaController::generateIncrementsAudio;
			metaController.fm = inputs.cv2Samples;
			metaWavetable.morphScale = drumFullScale;
			drumMode = &ViaMeta::drumModeOff;
		}
		switchWavetable(wavetableArray[mode][metaUI.TABLE]);
		break;
	case env:
		updateRGBDisplay(0, 4095, 0, 1);
		updateRGB = &ViaMeta::updateRGBSubaudio;
		metaController.parseControls = &MetaController::parseControlsEnv;
		metaController.generateIncrements = &MetaController::generateIncrementsEnv;
		if (metaUI.DAC_3_MODE == phasor) {
			calculateDac3 = &ViaMeta::calculateDac3PhasorEnv;
		} else {
			calculateDac3 = &ViaMeta::calculateDac3ContourEnv;
		}
		
		if (metaUI.LOOP_MODE == noloop) {
			switchWavetable(wavetableArray[mode][metaUI.TABLE]);
			metaController.fm = inputs.cv2Samples;
			metaWavetable.morphScale = drumFullScale;
			drumMode = &ViaMeta::drumModeOff;
			metaController.loopHandler = &MetaController::handleLoopOff;
			metaController.loopMode = 0;
			handleButton4ModeChange(metaUI.TRIG_MODE);
		}
		break;
	case seq:
		updateRGBDisplay(4095, 0, 0, 1);
		if (metaUI.DAC_3_MODE == phasor) {
			calculateDac3 = &ViaMeta::calculateDac3Phasor;
		} else {
			calculateDac3 = &ViaMeta::calculateDac3Contour;
		}
		metaController.parseControls = &MetaController::parseControlsSeq;
		metaController.generateIncrements = &MetaController::generateIncrementsSeq;
		switchWavetable(wavetableArray[mode][metaUI.TABLE]);
		break;
	}

}

void ViaMeta::handleButton4ModeChange(int32_t mode) {

	switch (mode) {
	case noretrigger:
		metaController.incrementArbiter = &MetaController::noRetrigAttackState;
		break;
	case meta_hardsync:
		metaController.incrementArbiter = &MetaController::hardSyncAttackState;
		break;
	case nongatedretrigger:
		metaController.incrementArbiter = &MetaController::envAttackState;
		break;
	case gated:
		metaController.incrementArbiter = &MetaController::gateAttackState;
		metaController.phase = 0;
		metaController.gateOn = 1;
		break;
	case meta_pendulum:
		metaController.incrementArbiter = &MetaController::pendulumForwardAttackState;
		metaController.gateOn = 0;
		break;
	}

}

void ViaMeta::handleButton5ModeChange(int32_t mode) {

	switchWavetable(wavetableArray[metaUI.FREQ_MODE][mode]);

}

void ViaMeta::handleButton6ModeChange(int32_t mode) {

	switch (mode) {
	case noloop:
		if (metaUI.FREQ_MODE == audio) {
			handleAux3ModeChange(metaUI.DRUM_MODE);
			handleButton3ModeChange(0);
			handleButton4ModeChange(0);
		} else {
			metaController.loopHandler = &MetaController::handleLoopOff;
			metaController.loopMode = 0;
		}
		break;
	case looping:
		if (metaUI.FREQ_MODE == audio) {
			handleButton3ModeChange(0);
			handleButton4ModeChange(metaUI.TRIG_MODE);
		}
		metaController.loopHandler = &MetaController::handleLoopOn;
		metaController.loopMode = 1;
		break;
	}

}

void ViaMeta::handleAux1ModeChange(int32_t mode) {


}

void ViaMeta::handleAux2ModeChange(int32_t mode) {

	switch (mode) {
	case releaseGate:
		calculateLogicA = &ViaMeta::calculateLogicAReleaseGate;
		break;
	case attackGate:
		calculateLogicA = &ViaMeta::calculateLogicAAttackGate;
		break;
	}

}

void ViaMeta::handleAux3ModeChange(int32_t mode) {

	switch (mode) {
	case pitchMorphAmp:
		metaController.fm = (int16_t*) drumEnvelope.output;
		metaWavetable.morphScale = (int16_t*) drumEnvelope.output;
		break;
	case morphAmp:
		metaController.fm = drumFullScale;
		metaWavetable.morphScale = (int16_t*) drumEnvelope.output;
		break;
	case pitchAmp:
		metaController.fm = (int16_t*) drumEnvelope.output;
		metaWavetable.morphScale = drumFullScale;
		break;
	case amp:
		metaController.fm = drumFullScale;
		metaWavetable.morphScale = drumFullScale;
		break;
	}

}

void ViaMeta::handleAux4ModeChange(int32_t mode) {

	switch (mode) {
	case phasor:
		if (metaUI.FREQ_MODE == env) {
			calculateDac3 = &ViaMeta::calculateDac3PhasorEnv;
		} else {
			calculateDac3 = &ViaMeta::calculateDac3Phasor;
		}
		break;
	case contour:
		if (metaUI.FREQ_MODE == env) {
			calculateDac3 = &ViaMeta::calculateDac3ContourEnv;
		} else {
			calculateDac3 = &ViaMeta::calculateDac3Contour;
		}
		break;
	}

}



