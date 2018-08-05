
#include "user_interface.h"
#include "signals.h"
#include "meta_tables.h"
#include "../inc/meta_fill_buffer.h"
#include "../inc/meta_modes.h"
#include "../inc/meta_ui_implementation.h"

void initializeUICallbacks(void) {

	button1TapCallback = handleButton1Tap;
	button1HoldCallback = handleButton1Hold;
	button2TapCallback = handleButton2Tap;
	button2HoldCallback = handleButton2Hold;
	button3TapCallback = handleButton3Tap;
	button3HoldCallback = handleButton3Hold;
	button4TapCallback = handleButton4Tap;
	button4HoldCallback = handleButton4Hold;
	button5TapCallback = handleButton5Tap;
	button5HoldCallback = handleButton5Hold;
	button6TapCallback = handleButton6Tap;
	button6HoldCallback = handleButton6Hold;

	aux1TapCallback = handleButton1Tap;
	aux1HoldCallback = handleButton1Hold;
	aux2TapCallback = handleButton2Tap;
	aux2HoldCallback = handleButton2Hold;
	aux3TapCallback = handleButton3Tap;
	aux3HoldCallback = handleButton3Hold;
	aux4TapCallback = handleButton4Tap;
	aux4HoldCallback = handleButton4Hold;
}

void handleButton1Tap(void) {
	SH_MODE = incrementModeAndStore(SH_MODE, BUTTON1_MASK, numButton1Modes);
	handleButton1ModeChange(SH_MODE);
	uiClearLEDs();
	uiSetLEDs(SH_MODE);
	uiTransition(&ui_newMode);
}
void handleButton2Tap(void) {
	TABLE = incrementModeAndStore(TABLE, BUTTON2_MASK, numButton2Modes);
	handleButton2ModeChange(TABLE);
	uiClearLEDs();
	uiSetLEDs(TABLE);
	uiTransition(&ui_newMode);
}
void handleButton3Tap(void) {
	FREQ_MODE = decrementModeAndStore(FREQ_MODE, BUTTON3_MASK, numButton3Modes);
	handleButton3ModeChange(FREQ_MODE);
	uiClearLEDs();
	uiSetLEDs(FREQ_MODE);
	uiTransition(&ui_newMode);
}
void handleButton4Tap(void) {
	TRIG_MODE = incrementModeAndStore(TRIG_MODE, BUTTON4_MASK, numButton4Modes);
	handleButton4ModeChange(TRIG_MODE);
	uiClearLEDs();
	uiSetLEDs(TRIG_MODE);
	uiTransition(&ui_newMode);
}
void handleButton5Tap(void) {
	TABLE = decrementModeAndStore(TABLE, BUTTON5_MASK, numButton5Modes);
	handleButton5ModeChange(TABLE);
	uiClearLEDs();
	uiSetLEDs(TABLE);
	uiTransition(&ui_newMode);
}
void handleButton6Tap(void) {
	LOOP_MODE = incrementModeAndStore(LOOP_MODE, BUTTON6_MASK, numButton6Modes);
	handleButton6ModeChange(LOOP_MODE);
	uiClearLEDs();
	uiSetLEDs(LOOP_MODE);
	uiTransition(&ui_newMode);
}

void handleAux4Tap(void) {

}

void handleButton1Hold(void) {
	uiTransition(&ui_default);
}
void handleButton2Hold(void) {
	uiTransition(&ui_default);
}
void handleButton3Hold(void) {
	uiTransition(&ui_default);
}
void handleButton4Hold(void) {
	uiTransition(&ui_default);
}
void handleButton5Hold(void) {
	uiTransition(&ui_default);
}
void handleButton6Hold(void) {
	uiTransition(&ui_default);
}
void handleAux4Hold(void) {

}

void handleButton1ModeChange(int mode) {

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
	case decimate:
		calculateSH = calculateSHMode6;
		break;
	}

	SH_A_TRACK;
	SH_B_TRACK;
}

void handleButton2ModeChange(int mode) {

	// change y family

	switchFamily();


}

void handleButton3ModeChange(int mode) {

	switch (mode) {
	case audio:
		getIncrements = getIncrementsAudio;
		getSamples = getSamplesNoPWM;
		updateRGB = updateRGBAudio;
		break;
	case env:
		getIncrements = getIncrementsEnv;
		getSamples = getSamplesNoPWM;
		updateRGB = updateRGBSubAudio;
		break;
	case seq:
		getIncrements = getIncrementsSeq;
		getSamples = getSamplesPWM;
		break;
	}

}

void handleButton4ModeChange(int mode) {

	switch (mode) {
	case noretrigger:
		advancePhase = advancePhaseNoRetrig;
		noRetrigStateMachine = noRetrigAttackState;
		break;
	case hardsync:
		advancePhase = advancePhaseHardSync;
		hardSyncStateMachine = hardSyncAttackState;
		break;
	case nongatedretrigger:
		advancePhase = advancePhaseEnv;
		envStateMachine = envAttackState;
		break;
	case gated:
		advancePhase = advancePhaseGate;
		gateStateMachine = gateAttackState;
		break;
	case pendulum:
		advancePhase = advancePhasePendulum;
		pendulumStateMachine = pendulumForwardAttackState;
		break;
	}

}

void handleButton5ModeChange(int mode) {

	switchFamily();

}

void handleButton6ModeChange(int mode) {

	switch (mode) {
	case noloop:
		handleLoop = handleLoopOff;
		break;
	case looping:
		handleLoop = handleLoopOn;
		break;
	}


}

void handleAux4ModeChange(int mode) {


}

void switchFamily(void) {

	loadSampleArray(familyArray[FREQ_MODE][TABLE]);
	softwareSignals.currentFamily = familyArray[FREQ_MODE][TABLE];

}


