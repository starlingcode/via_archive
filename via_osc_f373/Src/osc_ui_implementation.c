#include "osc.h"

void osc_initializeUICallbacks(void) {

	button1EnterMenuCallback = osc_handleButton1EnterMenu;
	button2EnterMenuCallback = osc_handleButton2EnterMenu;
	button3EnterMenuCallback = osc_handleButton3EnterMenu;
	button4EnterMenuCallback = osc_handleButton4EnterMenu;
	button5EnterMenuCallback = osc_handleButton5EnterMenu;
	button6EnterMenuCallback = osc_handleButton6EnterMenu;

	aux1EnterMenuCallback = osc_handleAux1EnterMenu;
	aux2EnterMenuCallback = osc_handleAux2EnterMenu;
	aux3EnterMenuCallback = osc_handleAux3EnterMenu;
	aux4EnterMenuCallback = osc_handleAux4EnterMenu;

	button1TapCallback = osc_handleButton1Tap;
	button1HoldCallback = osc_handleButton1Hold;
	button2TapCallback = osc_handleButton2Tap;
	button2HoldCallback = osc_handleButton2Hold;
	button3TapCallback = osc_handleButton3Tap;
	button3HoldCallback = osc_handleButton3Hold;
	button4TapCallback = osc_handleButton4Tap;
	button4HoldCallback = osc_handleButton4Hold;
	button5TapCallback = osc_handleButton5Tap;
	button5HoldCallback = osc_handleButton5Hold;
	button6TapCallback = osc_handleButton6Tap;
	button6HoldCallback = osc_handleButton6Hold;

	aux1TapCallback = osc_handleButton1Tap;
	aux1HoldCallback = osc_handleButton1Hold;
	aux2TapCallback = osc_handleButton2Tap;
	aux2HoldCallback = osc_handleButton2Hold;
	aux3TapCallback = osc_handleButton3Tap;
	aux3HoldCallback = osc_handleButton3Hold;
	aux4TapCallback = osc_handleButton4Tap;
	aux4HoldCallback = osc_handleButton4Hold;
}

void osc_handleButton1EnterMenu(void) {
	uiSetLEDs(SH_MODE);
	uiResetTimerMenu();
}
void osc_handleButton2EnterMenu(void) {
	uiSetLEDs(TABLE);
	uiResetTimerMenu();
}
void osc_handleButton3EnterMenu(void) {
	uiSetLEDs(FM_PM_MODE);
	uiResetTimerMenu();
}
void osc_handleButton4EnterMenu(void) {
	uiSetLEDs(SYNC_MODE);
	uiResetTimerMenu();
}
void osc_handleButton5EnterMenu(void) {
	uiSetLEDs(TABLE);
	uiResetTimerMenu();
}
void osc_handleButton6EnterMenu(void) {
	uiSetLEDs(SYNC_MODE);
	uiResetTimerMenu();
}
void osc_handleAux1EnterMenu(void) {
	uiTransition(ui_button5Menu);
}
void osc_handleAux2EnterMenu(void) {
	uiTransition(ui_button5Menu);
}
void osc_handleAux3EnterMenu(void) {
	uiTransition(ui_button5Menu);
}
void osc_handleAux4EnterMenu(void) {
	uiTransition(ui_button5Menu);
}

void osc_handleButton1Tap(void) {
	SH_MODE = incrementModeAndStore(SH_MODE, BUTTON1_MASK, numButton1Modes);
	osc_handleButton1ModeChange(SH_MODE);
	uiClearLEDs();
	uiSetLEDs(SH_MODE);
	uiTransition(&ui_newMode);
}
void osc_handleButton2Tap(void) {
	TABLE = incrementModeAndStore(TABLE, BUTTON2_MASK, numButton2Modes);
	osc_handleButton2ModeChange(TABLE);
	uiClearLEDs();
	uiSetLEDs(TABLE);
	uiTransition(&ui_newMode);
}
void osc_handleButton3Tap(void) {
	FM_PM_MODE = decrementModeAndStore(FM_PM_MODE, BUTTON3_MASK,
			numButton3Modes);
	osc_handleButton3ModeChange(FM_PM_MODE);
	uiClearLEDs();
	uiSetLEDs(FM_PM_MODE);
	uiTransition(&ui_newMode);
}
void osc_handleButton4Tap(void) {
	SYNC_MODE = incrementModeAndStore(SYNC_MODE, BUTTON4_MASK, numButton4Modes);
	osc_handleButton4ModeChange(SYNC_MODE);
	uiClearLEDs();
	uiSetLEDs(SYNC_MODE);
	uiTransition(&ui_newMode);
}
void osc_handleButton5Tap(void) {
	TABLE = incrementModeAndStore(TABLE, BUTTON5_MASK, numButton5Modes);
	osc_handleButton5ModeChange(TABLE);
	uiClearLEDs();
	uiSetLEDs(TABLE);
	uiTransition(&ui_newMode);
}
void osc_handleButton6Tap(void) {
	MORPH_PWM_MODE = incrementModeAndStore(MORPH_PWM_MODE, BUTTON6_MASK,
			numButton6Modes);
	osc_handleButton6ModeChange(MORPH_PWM_MODE);
	uiClearLEDs();
	uiSetLEDs(MORPH_PWM_MODE);
	uiTransition(&ui_newMode);
}

void osc_handleAux1Tap(void) {
	uiTransition(ui_button5Menu);
}

void osc_handleAux2Tap(void) {
	uiTransition(ui_button5Menu);
}

void osc_handleAux3Tap(void) {
	uiTransition(ui_button5Menu);
}

void osc_handleAux4Tap(void) {
	uiTransition(ui_button5Menu);
}

void osc_handleButton1Hold(void) {
	uiTransition(&ui_default);
}
void osc_handleButton2Hold(void) {
	uiTransition(&ui_default);
}
void osc_handleButton3Hold(void) {
	uiTransition(&ui_default);
}
void osc_handleButton4Hold(void) {
	uiTransition(&ui_default);
}
void osc_handleButton5Hold(void) {
	uiTransition(&ui_default);
}
void osc_handleButton6Hold(void) {
	uiTransition(&ui_default);
}
void osc_handleAux1Hold(void) {
	uiTransition(&ui_button5Menu);
}
void osc_handleAux2Hold(void) {
	uiTransition(&ui_newAuxMode);
}
void osc_handleAux3Hold(void) {
	uiTransition(&ui_newAuxMode);
}
void osc_handleAux4Hold(void) {
	uiTransition(&ui_newAuxMode);
}

