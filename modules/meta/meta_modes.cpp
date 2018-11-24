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
			currentRGBBehavior = &ViaMeta::updateRGBDrum;
			metaController.generateIncrements = &MetaController::generateIncrementsDrum;
			metaController.parseControls = &MetaController::parseControlsDrum;
			metaController.fm = drumFullScale;
			metaController.expoFM = freqTransient.output;
			outputStage = &ViaMeta::drumMode;
			metaController.advancePhase = &MetaController::advancePhaseOversampled;
			metaWavetable.oversamplingFactor = 0;
			metaController.loopHandler = &MetaController::handleLoopOn;
			metaController.loopMode = 1;
			handleButton4ModeChange(0);
			handleAux3ModeChange(metaUI.DRUM_MODE);
		} else {
			updateRGBDisplay(0, 0, 4095, 1);
			updateRGB = &ViaMeta::updateRGBOsc;
			currentRGBBehavior = &ViaMeta::updateRGBOsc;
			metaController.parseControls = &MetaController::parseControlsAudio;
			metaController.generateIncrements = &MetaController::generateIncrementsAudio;
			outputStage = &ViaMeta::oversample;
			metaController.expoFM = drumOff;
			metaController.advancePhase = &MetaController::advancePhaseOversampled;
			metaWavetable.oversamplingFactor = 3;
			metaController.fm = inputs.cv2Samples;
			metaWavetable.morphScale = drumFullScale;

		}
		switchWavetable(wavetableArray[mode][metaUI.TABLE]);
		break;
	case env:

		updateRGBDisplay(0, 4095, 0, 1);
		updateRGB = &ViaMeta::updateRGBSubaudio;
		currentRGBBehavior = &ViaMeta::updateRGBSubaudio;
		metaController.parseControls = &MetaController::parseControlsEnv;
		metaController.generateIncrements = &MetaController::generateIncrementsEnv;

		outputStage = &ViaMeta::addThreeBits;
		metaController.advancePhase = &MetaController::advancePhasePWM;
		metaWavetable.oversamplingFactor = 0;

		switchWavetable(wavetableArray[mode][metaUI.TABLE]);

		if (metaUI.DAC_3_MODE == phasor) {
			calculateDac3 = &ViaMeta::calculateDac3PhasorEnv;
		} else {
			calculateDac3 = &ViaMeta::calculateDac3ContourEnv;
		}
		
		if (metaUI.LOOP_MODE == noloop) {
			metaController.fm = inputs.cv2Samples;
			metaWavetable.morphScale = drumFullScale;
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
		updateRGB = &ViaMeta::updateRGBSubaudio;
		currentRGBBehavior = &ViaMeta::updateRGBSubaudio;
		metaController.parseControls = &MetaController::parseControlsSeq;
		metaController.generateIncrements = &MetaController::generateIncrementsSeq;

		outputStage = &ViaMeta::addThreeBits;
		metaController.advancePhase = &MetaController::advancePhasePWM;

		switchWavetable(wavetableArray[mode][metaUI.TABLE]);
		break;
	}

}

void ViaMeta::handleButton4ModeChange(int32_t mode) {

	metaController.atB = 0;

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
		if (metaUI.LOOP_MODE == 1) {
			metaController.incrementArbiter = &MetaController::pendulumForwardAttackState;
		} else {
			metaController.incrementArbiter = &MetaController::stickyPendulumRestingState;
		}
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
			outputStage = &ViaMeta::drumMode;
			metaController.expoFM = freqTransient.output;
			metaController.advancePhase = &MetaController::advancePhaseOversampled;
			metaWavetable.oversamplingFactor = 0;
		} else {
			metaController.loopHandler = &MetaController::handleLoopOff;
			metaController.loopMode = 0;
		}
		if (metaUI.TRIG_MODE == meta_pendulum)  {
			metaController.incrementArbiter = &MetaController::stickyPendulumRestingState;
		}
		break;
	case looping:
		if (metaUI.FREQ_MODE == audio) {
			handleButton3ModeChange(0);
			handleButton4ModeChange(metaUI.TRIG_MODE);
			outputStage = &ViaMeta::oversample;
			metaController.expoFM = drumOff;
			metaController.advancePhase = &MetaController::advancePhaseOversampled;
			metaWavetable.oversamplingFactor = 3;
		}
		metaController.loopHandler = &MetaController::handleLoopOn;
		metaController.loopMode = 1;
		if (metaUI.TRIG_MODE == meta_pendulum)  {
			metaController.incrementArbiter = &MetaController::pendulumRestingState;
		}
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
		metaController.fm = (int16_t*) morphEnvelope.output;
		metaWavetable.morphScale = (int16_t*) ampEnvelope.output;

		ampEnvelope.attack = 2 << 16;
		morphAttackMultiplier = 1 << 8;
		morphReleaseMultiplier = 1 << 2;
		freqAttackMultiplier = 1 << 13;
		freqReleaseMultiplier = 1<< 12;
		transientScale = 1 << 3;
		minTransientLength = 10000;

		break;
	case morphAmp:
		metaController.fm = drumFullScale;
		metaWavetable.morphScale = (int16_t*) morphEnvelope.output;

		ampEnvelope.attack = 2 << 16;
		morphAttackMultiplier = 1 << 6;
		morphReleaseMultiplier = 1;
		freqAttackMultiplier = 1 << 13;
		freqReleaseMultiplier = 1<< 12;
		transientScale = 1 << 2;
		minTransientLength = 0;

		break;
	case pitchAmp:
		metaController.fm = (int16_t*) morphEnvelope.output;
		metaWavetable.morphScale = drumFullScale;

		ampEnvelope.attack = 1 << 16;
		morphAttackMultiplier = 1 << 8;
		morphReleaseMultiplier = 1 << 1;
		freqAttackMultiplier = 1 << 11;
		freqReleaseMultiplier = 1<< 7;
		transientScale = 1 << 1;
		minTransientLength = 10000;

		break;
	case amp:
		metaController.fm = drumFullScale;
		metaWavetable.morphScale = drumFullScale;

		ampEnvelope.attack = 2 << 16;
		morphAttackMultiplier = 1 << 8;
		morphReleaseMultiplier = 1 << 2;
		freqAttackMultiplier = 1 << 13;
		freqReleaseMultiplier = 1<< 12;
		transientScale = 1;
		minTransientLength = 20;

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



