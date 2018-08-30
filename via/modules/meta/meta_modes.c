/*
 * meta_modes.c
 *
 *  Created on: Aug 29, 2018
 *      Author: willmitchell
 */

#include "meta.h"

void meta_handleButton1ModeChange(int mode) {

	switch (mode) {
	case nosampleandhold:
		meta_calculateSH = meta_calculateSHMode1;
		break;
	case a:
		meta_calculateSH = meta_calculateSHMode2;
		break;
	case b:
		meta_calculateSH = meta_calculateSHMode3;
		break;
	case ab:
		meta_calculateSH = meta_calculateSHMode4;
		break;
	case halfdecimate:
		meta_calculateSH = meta_calculateSHMode5;
		break;
	case meta_decimate:
		meta_calculateSH = meta_calculateSHMode6;
		break;
	}

	SH_A_TRACK;
	SH_B_TRACK;
}

void meta_handleButton2ModeChange(int mode) {

	meta_switchWavetable(meta_wavetableArray[FREQ_MODE][mode], &meta_signals);

}

void meta_handleButton3ModeChange(int mode) {

	switch (mode) {
	case audio:
		metaControllerGenerateIncrements = metaControllerGenerateIncrementsAudio;
		metaControllerParseControls = metaControllerParseControlsAudio;
		meta_switchWavetable(meta_wavetableArray[mode][TABLE], &meta_signals);
		//updateRGB = updateRGBAudio;
		break;
	case env:
		metaControllerParseControls = metaControllerParseControlsEnv;
		metaControllerGenerateIncrements = metaControllerGenerateIncrementsEnv;
		meta_switchWavetable(meta_wavetableArray[mode][TABLE], &meta_signals);
		//updateRGB = updateRGBSubAudio;
		break;
	case seq:
		metaControllerParseControls = metaControllerParseControlsSeq;
		metaControllerGenerateIncrements = metaControllerGenerateIncrementsSeq;
		meta_switchWavetable(meta_wavetableArray[mode][TABLE], &meta_signals);
		break;
	}

}

void meta_handleButton4ModeChange(int mode) {

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
		break;
	case meta_pendulum:
		metaControllerIncrementArbiter = pendulumForwardAttackState;
		break;
	}

}

void meta_handleButton5ModeChange(int mode) {

	meta_switchWavetable(meta_wavetableArray[FREQ_MODE][mode], &meta_signals);

}

void meta_handleButton6ModeChange(int mode) {

	switch (mode) {
	case noloop:
		metaControllerLoopHandler = handleLoopOff;
		break;
	case looping:
		metaControllerLoopHandler = handleLoopOn;
		break;
	}

}

void meta_handleAux1ModeChange(int mode) {


}

void meta_handleAux2ModeChange(int mode) {


}

void meta_handleAux3ModeChange(int mode) {


}

void meta_handleAux4ModeChange(int mode) {

	switch (mode) {
	case phasor:
		meta_calculateDac3 = meta_calculateDac3Phasor;
		break;
	case contour:
		meta_calculateDac3 = meta_calculateDac3Contour;
		break;
	}

}



