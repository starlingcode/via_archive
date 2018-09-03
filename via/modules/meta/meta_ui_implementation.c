/*
 * meta_ui_implementation.c
 *
 *  Created on: Aug 29, 2018
 *      Author: willmitchell
 */

#include "meta.h"

void meta_initializeUICallbacks(void) {

	button1EnterMenuCallback = meta_handleButton1EnterMenu;
	button2EnterMenuCallback = meta_handleButton2EnterMenu;
	button3EnterMenuCallback = meta_handleButton3EnterMenu;
	button4EnterMenuCallback = meta_handleButton4EnterMenu;
	button5EnterMenuCallback = meta_handleButton5EnterMenu;
	button6EnterMenuCallback = meta_handleButton6EnterMenu;

	aux1EnterMenuCallback = meta_handleAux1EnterMenu;
	aux2EnterMenuCallback = meta_handleAux2EnterMenu;
	aux3EnterMenuCallback = meta_handleAux3EnterMenu;
	aux4EnterMenuCallback = meta_handleAux4EnterMenu;

	button1TapCallback = meta_handleButton1Tap;
	button1HoldCallback = meta_handleButton1Hold;
	button2TapCallback = meta_handleButton2Tap;
	button2HoldCallback = meta_handleButton2Hold;
	button3TapCallback = meta_handleButton3Tap;
	button3HoldCallback = meta_handleButton3Hold;
	button4TapCallback = meta_handleButton4Tap;
	button4HoldCallback = meta_handleButton4Hold;
	button5TapCallback = meta_handleButton5Tap;
	button5HoldCallback = meta_handleButton5Hold;
	button6TapCallback = meta_handleButton6Tap;
	button6HoldCallback = meta_handleButton6Hold;

	aux1TapCallback = meta_handleAux1Tap;
	aux1HoldCallback = meta_handleAux1Hold;
	aux2TapCallback = meta_handleAux2Tap;
	aux2HoldCallback = meta_handleAux2Hold;
	aux3TapCallback = meta_handleAux3Tap;
	aux3HoldCallback = meta_handleAux3Hold;
	aux4TapCallback = meta_handleAux4Tap;
	aux4HoldCallback = meta_handleAux4Hold;
}

void meta_handleButton1EnterMenu(void) {
	uiSetLEDs(SH_MODE);
	uiResetTimerMenu();
}
void meta_handleButton2EnterMenu(void) {
	uiSetLEDs(TABLE);
	uiResetTimerMenu();
}
void meta_handleButton3EnterMenu(void) {
	uiSetLEDs(FREQ_MODE);
	uiResetTimerMenu();
}
void meta_handleButton4EnterMenu(void) {
	if (!LOOP_MODE && !FREQ_MODE) {
		uiTransition(ui_aux3Menu);
	} else {
		uiSetLEDs(TRIG_MODE);
		uiResetTimerMenu();
	}
}
void meta_handleButton5EnterMenu(void) {
	uiSetLEDs(TABLE);
	uiResetTimerMenu();
}
void meta_handleButton6EnterMenu(void) {
	uiSetLEDs(LOOP_MODE);
	uiResetTimerMenu();
}
void meta_handleAux1EnterMenu(void) {
	uiTransition(ui_button5Menu);
}
void meta_handleAux2EnterMenu(void) {
	uiClearLEDs();
	uiSetLEDs(LOGIC_A_MODE);
	uiResetTimerMenu();
}
void meta_handleAux3EnterMenu(void) {
	uiClearLEDs();
	uiSetLEDs(DRUM_MODE);
	uiResetTimerMenu();
}
void meta_handleAux4EnterMenu(void) {
	uiClearLEDs();
	uiSetLEDs(DAC_3_MODE);
	uiResetTimerMenu();
}

void meta_handleButton1Tap(void) {
	SH_MODE = incrementModeAndStore(SH_MODE, BUTTON1_MASK, numButton1Modes);
	meta_handleButton1ModeChange(SH_MODE);
	uiClearLEDs();
	uiSetLEDs(SH_MODE);
	uiTransition(&ui_newMode);
}
void meta_handleButton2Tap(void) {
	TABLE = incrementModeAndStore(TABLE, BUTTON2_MASK, numButton2Modes);
	meta_handleButton2ModeChange(TABLE);
	uiClearLEDs();
	uiSetLEDs(TABLE);
	uiTransition(&ui_newMode);
}
void meta_handleButton3Tap(void) {
	FREQ_MODE = incrementModeAndStore(FREQ_MODE, BUTTON3_MASK, numButton3Modes);
	meta_handleButton3ModeChange(FREQ_MODE);
	uiClearLEDs();
	uiSetLEDs(FREQ_MODE);
	uiTransition(&ui_newMode);
}
void meta_handleButton4Tap(void) {
	TRIG_MODE = incrementModeAndStore(TRIG_MODE, BUTTON4_MASK, numButton4Modes);
	meta_handleButton4ModeChange(TRIG_MODE);
	uiClearLEDs();
	uiSetLEDs(TRIG_MODE);
	uiTransition(&ui_newMode);
}
void meta_handleButton5Tap(void) {
	TABLE = decrementModeAndStore(TABLE, BUTTON5_MASK, numButton5Modes);
	meta_handleButton5ModeChange(TABLE);
	uiClearLEDs();
	uiSetLEDs(TABLE);
	uiTransition(&ui_newMode);
}
void meta_handleButton6Tap(void) {
	LOOP_MODE = incrementModeAndStore(LOOP_MODE, BUTTON6_MASK, numButton6Modes);
	meta_handleButton6ModeChange(LOOP_MODE);
	uiClearLEDs();
	uiSetLEDs(LOOP_MODE);
	uiTransition(&ui_newMode);
}

void meta_handleAux1Tap(void) {
	uiTransition(ui_button5Menu);
}

void meta_handleAux2Tap(void) {
	LOGIC_A_MODE = incrementModeAndStore(LOGIC_A_MODE, AUX_MODE2_MASK, numAux2Modes);
	meta_handleAux2ModeChange(LOGIC_A_MODE);
	uiClearLEDs();
	uiSetLEDs(LOGIC_A_MODE);
	uiTransition(&ui_newAuxMode);
}

void meta_handleAux3Tap(void) {
	DRUM_MODE = incrementModeAndStore(DRUM_MODE, AUX_MODE3_MASK, numAux3Modes);
	meta_handleAux3ModeChange(DRUM_MODE);
	uiClearLEDs();
	uiSetLEDs(DRUM_MODE);
	uiTransition(&ui_newMode);
}

void meta_handleAux4Tap(void) {
	DAC_3_MODE = incrementModeAndStore(DAC_3_MODE, AUX_MODE4_MASK, numAux4Modes);
	meta_handleAux4ModeChange(DAC_3_MODE);
	uiClearLEDs();
	uiSetLEDs(DAC_3_MODE);
	uiTransition(&ui_newAuxMode);
}

void meta_handleButton1Hold(void) {
	uiTransition(&ui_default);
}
void meta_handleButton2Hold(void) {
	uiTransition(&ui_default);
}
void meta_handleButton3Hold(void) {
	uiTransition(&ui_default);
}
void meta_handleButton4Hold(void) {
	uiTransition(&ui_default);
}
void meta_handleButton5Hold(void) {
	uiTransition(&ui_default);
}
void meta_handleButton6Hold(void) {
	uiTransition(&ui_default);
}

void meta_handleAux1Hold(void) {
	uiTransition(ui_button5Menu);
}

void meta_handleAux2Hold(void) {
	uiTransition(&ui_default);
}

void meta_handleAux3Hold(void) {
	uiTransition(&ui_default);
}

void meta_handleAux4Hold(void) {
	uiTransition(&ui_default);
}

