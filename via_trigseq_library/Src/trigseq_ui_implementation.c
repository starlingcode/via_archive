#include "main.h"
#include "user_interface.h"
#include "dsp.h"
#include "trigseq_modes.h"
#include "via_rev5_hardware_io.h"
#include "trigseq_patterns.h"

void handleButton1Tap(void) {

	SH_A_MODE = incrementModeAndStore(SH_A_MODE, BUTTON1_MASK, numButton1Modes);
	handleButton1ModeChange(SH_A_MODE);
	uiClearLEDs();
	uiSetLEDs(SH_A_MODE);
	uiTransition(&ui_newMode);
}
void handleButton2Tap(void) {
	AND_A_MODE = incrementModeAndStore(AND_A_MODE, BUTTON2_MASK, numButton2Modes);
	handleButton2ModeChange(AND_A_MODE);
	uiClearLEDs();
	uiSetLEDs(AND_A_MODE);
	uiTransition(&ui_newMode);
}
void handleButton3Tap(void) {
	A_PATTERN_BANK = incrementModeAndStore(A_PATTERN_BANK, BUTTON3_MASK, numButton3Modes);
	handleButton3ModeChange(A_PATTERN_BANK);
	uiClearLEDs();
	uiSetLEDs(A_PATTERN_BANK);
	uiTransition(&ui_newMode);
}
void handleButton4Tap(void) {
	SH_B_MODE = incrementModeAndStore(SH_B_MODE, BUTTON4_MASK, numButton4Modes);
	handleButton4ModeChange(SH_B_MODE);
	uiClearLEDs();
	uiSetLEDs(SH_B_MODE);
	uiTransition(&ui_newMode);
}
void handleButton5Tap(void) {
	AND_B_MODE = incrementModeAndStore(AND_B_MODE, BUTTON5_MASK, numButton5Modes);
	handleButton5ModeChange(AND_B_MODE);
	uiClearLEDs();
	uiSetLEDs(AND_B_MODE);
	uiTransition(&ui_newMode);
}
void handleButton6Tap(void) {
	B_PATTERN_BANK = incrementModeAndStore(B_PATTERN_BANK, BUTTON6_MASK, numButton6Modes);
	handleButton6ModeChange(B_PATTERN_BANK);
	uiClearLEDs();
	uiSetLEDs(B_PATTERN_BANK);
	uiTransition(&ui_newMode);
}

void handleAux2Tap(void) {
	LOGIC_MODE = incrementModeAndStore(LOGIC_MODE, AUX_MODE2_MASK, numAux2Modes);
	handleAux2ModeChange(LOGIC_MODE);
	uiClearLEDs();
	uiSetLEDs(LOGIC_MODE);
	uiTransition(&ui_newAuxMode);
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
void handleAux2Hold(void) {
	uiTransition(&ui_newAuxMode);
}

void handleButton1ModeChange(int mode) {

	// if mode is 0, set sample and track should be 0
	// if mode is 1, set sample to 1 but track should be 0
	// if mode is 2, set sample to 1 and set track to 1

	softwareSignals.sampleA = __USAT(mode, 1);
	softwareSignals.trackA = mode >> 1;
	SH_A_TRACK;

}

void handleButton2ModeChange(int mode) {

	softwareSignals.andA = mode;

}

void handleButton3ModeChange(int mode) {

	softwareSignals.currentABank = patternBanks[mode];

}

void handleButton4ModeChange(int mode) {

	// if mode is 0, set sample and track should be 0
	// if mode is 1, set sample to 1 but track should be 0
	// if mode is 2, set sample to 1 and set track to 1

	softwareSignals.sampleB = __USAT(mode, 1);
	softwareSignals.trackB = mode >> 1;
	SH_B_TRACK;

}

void handleButton5ModeChange(int mode) {

	softwareSignals.andB = mode;

}

void handleButton6ModeChange(int mode) {

	softwareSignals.currentBBank = patternBanks[mode];

}

void handleAux2ModeChange(int mode) {

	softwareSignals.auxLogicMode = mode;

}
