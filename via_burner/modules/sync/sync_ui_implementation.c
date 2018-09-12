#include "sync.h"

void sync_initializeUICallbacks(void) {

	button1EnterMenuCallback = sync_handleButton1EnterMenu;
	button2EnterMenuCallback = sync_handleButton2EnterMenu;
	button3EnterMenuCallback = sync_handleButton3EnterMenu;
	button4EnterMenuCallback = sync_handleButton4EnterMenu;
	button5EnterMenuCallback = sync_handleButton5EnterMenu;
	button6EnterMenuCallback = sync_handleButton6EnterMenu;

	aux1EnterMenuCallback = sync_handleAux1EnterMenu;
	aux2EnterMenuCallback = sync_handleAux2EnterMenu;
	aux3EnterMenuCallback = sync_handleAux3EnterMenu;
	aux4EnterMenuCallback = sync_handleAux4EnterMenu;

	button1TapCallback = sync_handleButton1Tap;
	button1HoldCallback = sync_handleButton1Hold;
	button2TapCallback = sync_handleButton2Tap;
	button2HoldCallback = sync_handleButton2Hold;
	button3TapCallback = sync_handleButton3Tap;
	button3HoldCallback = sync_handleButton3Hold;
	button4TapCallback = sync_handleButton4Tap;
	button4HoldCallback = sync_handleButton4Hold;
	button5TapCallback = sync_handleButton5Tap;
	button5HoldCallback = sync_handleButton5Hold;
	button6TapCallback = sync_handleButton6Tap;
	button6HoldCallback = sync_handleButton6Hold;

	aux1TapCallback = sync_handleAux1Tap;
	aux1HoldCallback = sync_handleAux1Hold;
	aux2TapCallback = sync_handleAux2Tap;
	aux2HoldCallback = sync_handleAux2Hold;
	aux3TapCallback = sync_handleAux3Tap;
	aux3HoldCallback = sync_handleAux3Hold;
	aux4TapCallback = sync_handleAux4Tap;
	aux4HoldCallback = sync_handleAux4Hold;
}
void sync_handleButton1EnterMenu(void) {
	uiSetLEDs(SH_MODE);
	uiResetTimerMenu();
}
void sync_handleButton2EnterMenu(void) {
	uiSetLEDs(SCALE_MODE);
	uiResetTimerMenu();
}
void sync_handleButton3EnterMenu(void) {
	uiSetLEDs(X_MODE);
	uiResetTimerMenu();
}
void sync_handleButton4EnterMenu(void) {
	uiSetLEDs(SYNC_MODE);
	uiResetTimerMenu();
}
void sync_handleButton5EnterMenu(void) {
	uiSetLEDs(GROUP_MODE);
	uiResetTimerMenu();
}
void sync_handleButton6EnterMenu(void) {
	uiSetLEDs(TABLE_MODE);
	uiResetTimerMenu();
}
void sync_handleAux1EnterMenu(void) {
	uiClearLEDs();
	uiSetLEDs(LOGIC_A_MODE);
	uiResetTimerMenu();
}
void sync_handleAux2EnterMenu(void) {
	uiClearLEDs();
	uiSetLEDs(AUX_OUT_MODE);
	uiResetTimerMenu();
}
void sync_handleAux3EnterMenu(void) {
	uiClearLEDs();
	uiSetLEDs(QUADRATURE_MODE);
	uiResetTimerMenu();
}
void sync_handleAux4EnterMenu(void) {
	uiClearLEDs();
	uiSetLEDs(TABLE_GROUP_MODE);
	uiResetTimerMenu();
}

void sync_handleButton1Tap(void) {
	SH_MODE = incrementModeAndStore(SH_MODE, BUTTON1_MASK, numButton1Modes);
	sync_handleButton1ModeChange(SH_MODE);
	uiClearLEDs();
	uiSetLEDs(SH_MODE);
	uiTransition(&ui_newMode);
}
void sync_handleButton2Tap(void) {
	SCALE_MODE = incrementModeAndStore(SCALE_MODE, BUTTON2_MASK, numButton2Modes);
	sync_handleButton2ModeChange(SCALE_MODE);
	uiClearLEDs();
	uiSetLEDs(SCALE_MODE);
	uiTransition(&ui_newMode);
}
void sync_handleButton3Tap(void) {
	X_MODE = incrementModeAndStore(X_MODE, BUTTON3_MASK, numButton3Modes);
	sync_handleButton3ModeChange(X_MODE);
	uiClearLEDs();
	uiSetLEDs(X_MODE);
	uiTransition(&ui_newMode);
}
void sync_handleButton4Tap(void) {
	SYNC_MODE = incrementModeAndStore(SYNC_MODE, BUTTON4_MASK, numButton4Modes);
	sync_handleButton4ModeChange(SYNC_MODE);
	uiClearLEDs();
	uiSetLEDs(SYNC_MODE);
	uiTransition(&ui_newMode);
}
void sync_handleButton5Tap(void) {
	GROUP_MODE = incrementModeAndStore(GROUP_MODE, BUTTON5_MASK, numButton5Modes);
	sync_handleButton5ModeChange(GROUP_MODE);
	uiClearLEDs();
	uiSetLEDs(GROUP_MODE);
	uiTransition(&ui_newMode);
}
void sync_handleButton6Tap(void) {
	TABLE_MODE = incrementModeAndStore(TABLE_MODE, BUTTON6_MASK, numButton6Modes);
	sync_handleButton6ModeChange(TABLE_MODE);
	uiClearLEDs();
	uiSetLEDs(TABLE_MODE);
	uiTransition(&ui_newMode);
}

void sync_handleAux1Tap(void) {
	AUX_OUT_MODE = incrementModeAndStore(AUX_OUT_MODE, AUX_MODE1_MASK, numAux1Modes);
	sync_handleAux1ModeChange(AUX_OUT_MODE);
	uiClearLEDs();
	uiSetLEDs(AUX_OUT_MODE);
	uiTransition(&ui_newAuxMode);
}

void sync_handleAux2Tap(void) {
	LOGIC_A_MODE = incrementModeAndStore(LOGIC_A_MODE, AUX_MODE2_MASK, numAux2Modes);
	sync_handleAux2ModeChange(LOGIC_A_MODE);
	uiClearLEDs();
	uiSetLEDs(LOGIC_A_MODE);
	uiTransition(&ui_newAuxMode);
}

void sync_handleAux3Tap(void) {
	QUADRATURE_MODE = incrementModeAndStore(QUADRATURE_MODE, AUX_MODE3_MASK, numAux3Modes);
	sync_handleAux3ModeChange(QUADRATURE_MODE);
	uiClearLEDs();
	uiSetLEDs(QUADRATURE_MODE);
	uiTransition(&ui_newAuxMode);
}

void sync_handleAux4Tap(void) {
	TABLE_GROUP_MODE = incrementModeAndStore(TABLE_GROUP_MODE, AUX_MODE4_MASK, numAux4Modes);
	sync_handleAux4ModeChange(TABLE_GROUP_MODE);
	uiClearLEDs();
	uiSetLEDs(TABLE_GROUP_MODE);
	uiTransition(&ui_newAuxMode);
}

void sync_handleButton1Hold(void) {
	uiTransition(&ui_default);
}
void sync_handleButton2Hold(void) {
	uiTransition(&ui_default);
}
void sync_handleButton3Hold(void) {
	uiTransition(&ui_default);
}
void sync_handleButton4Hold(void) {
	uiTransition(&ui_default);
}
void sync_handleButton5Hold(void) {
	uiTransition(&ui_default);
}
void sync_handleButton6Hold(void) {
	uiTransition(&ui_default);
}
void sync_handleAux1Hold(void) {
	uiTransition(&ui_newAuxMode);
}
void sync_handleAux2Hold(void) {
	uiTransition(&ui_newAuxMode);
}
void sync_handleAux3Hold(void) {
	uiTransition(&ui_newAuxMode);
}
void sync_handleAux4Hold(void) {
	uiTransition(&ui_newAuxMode);
}

