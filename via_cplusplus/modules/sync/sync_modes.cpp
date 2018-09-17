/*
 * modes.c
 *
 *  Created on: Aug 21, 2018
 *      Author: willmitchell
 */

#include "sync.hpp"

void ViaSync::handleButton1ModeChange(int mode) {

	switch (mode) {
	case noSH:
		calculateSH = &ViaSync::calculateSHMode1;
		break;
	case sampletrack:
		calculateSH = &ViaSync::calculateSHMode2;
		break;
	case resample:
		calculateSH = &ViaSync::calculateSHMode3;
		break;
	default:
		break;
	}

}

void ViaSync::handleButton2ModeChange(int mode) {

	pllController.scale = (Scale *) scaleArray[syncUI.GROUP_MODE][mode];

}

void ViaSync::handleButton3ModeChange(int mode) {

	switch (mode) {
	case root:
		pllController.rootMod = system.inputs.cv2Samples;
		syncWavetable.fm = system.inputs.cv2VirtualGround;
		syncWavetable.pm = system.inputs.cv2VirtualGround;
		syncWavetable.pwm = system.inputs.cv2VirtualGround;
		break;
	case pm:
		pllController.rootMod = system.inputs.cv2VirtualGround;
		syncWavetable.fm = system.inputs.cv2VirtualGround;
		syncWavetable.pm = system.inputs.cv2Samples;
		syncWavetable.pwm = system.inputs.cv2VirtualGround;
		break;
	case fm:
		pllController.rootMod = system.inputs.cv2VirtualGround;
		syncWavetable.fm = system.inputs.cv2Samples;
		syncWavetable.pm = system.inputs.cv2VirtualGround;
		syncWavetable.pwm = system.inputs.cv2VirtualGround;
		break;
	case pwm:
		pllController.rootMod = system.inputs.cv2VirtualGround;
		syncWavetable.fm = system.inputs.cv2VirtualGround;
		syncWavetable.pm = system.inputs.cv2VirtualGround;
		syncWavetable.pwm = system.inputs.cv2Samples;
		break;
	default:
		break;
	}


}

void ViaSync::handleButton4ModeChange(int mode) {

	// see pllMultiplierMeasureFrequency for why this is in range 1, 2, 3

	pllController.syncMode = mode + 1;

}

void ViaSync::handleButton5ModeChange(int mode) {

	pllController.scale = (Scale *) scaleArray[mode][syncUI.SCALE_MODE];
	if (syncUI.TABLE_GROUP_MODE) {
		switchWavetable(wavetableArray[syncUI.SCALE_MODE][mode]);
	} else {
		switchWavetableGlobal(wavetableArrayGlobal[mode]);
	}

}

void ViaSync::handleButton6ModeChange(int mode) {

	if (syncUI.TABLE_GROUP_MODE) {
		switchWavetable(wavetableArray[syncUI.SCALE_MODE][mode]);
	} else {
		switchWavetableGlobal(wavetableArrayGlobal[mode]);
	}

}

void ViaSync::handleAux1ModeChange(int mode) {

	switch (mode) {
	case sync_gate:
		calculateLogicA = &ViaSync::calculateLogicAGate;
		break;
	case sync_delta:
		calculateLogicA = &ViaSync::calculateLogicADelta;
		break;
	default:
		break;
	}

}


void ViaSync::handleAux2ModeChange(int mode) {

	switch (mode) {
	case sync_phasor:
		calculateDac3 = &ViaSync::calculateDac3Phasor;
		break;
	case sync_contour:
		calculateDac3 = &ViaSync::calculateDac3Contour;
		break;
	default:
		break;
	}

}


void ViaSync::handleAux3ModeChange(int mode) {

	switch (mode) {
	case noOffset:
		pllController.phaseOffset = 0;
		break;
	case quarter:
		pllController.phaseOffset = 1 << 23;
		break;
	case half:
		pllController.phaseOffset = 1 << 24;
		break;
	case threeQuarters:
		pllController.phaseOffset = (3 << 23);
		break;
	default:
		break;
	}

}

void ViaSync::handleAux4ModeChange(int mode) {

	if (syncUI.TABLE_GROUP_MODE) {
		switchWavetable(wavetableArray[syncUI.SCALE_MODE][mode]);
	} else {
		switchWavetableGlobal(wavetableArrayGlobal[mode]);
	}

}
