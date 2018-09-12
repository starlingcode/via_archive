
#include "scanner.h"

void scanner_initializeUICallbacks(void) {

	button1EnterMenuCallback = scanner_handleButton1EnterMenu;
	button2EnterMenuCallback = scanner_handleButton2EnterMenu;
	button3EnterMenuCallback = scanner_handleButton3EnterMenu;
	button4EnterMenuCallback = scanner_handleButton4EnterMenu;
	button5EnterMenuCallback = scanner_handleButton5EnterMenu;
	button6EnterMenuCallback = scanner_handleButton6EnterMenu;

	aux1EnterMenuCallback = scanner_handleAux1EnterMenu;
	aux2EnterMenuCallback = scanner_handleAux2EnterMenu;
	aux3EnterMenuCallback = scanner_handleAux3EnterMenu;
	aux4EnterMenuCallback = scanner_handleAux4EnterMenu;

	button1TapCallback = scanner_handleButton1Tap;
	button1HoldCallback = scanner_handleButton1Hold;
	button2TapCallback = scanner_handleButton2Tap;
	button2HoldCallback = scanner_handleButton2Hold;
	button3TapCallback = scanner_handleButton3Tap;
	button3HoldCallback = scanner_handleButton3Hold;
	button4TapCallback = scanner_handleButton4Tap;
	button4HoldCallback = scanner_handleButton4Hold;
	button5TapCallback = scanner_handleButton5Tap;
	button5HoldCallback = scanner_handleButton5Hold;
	button6TapCallback = scanner_handleButton6Tap;
	button6HoldCallback = scanner_handleButton6Hold;

	aux1TapCallback = scanner_handleButton1Tap;
	aux1HoldCallback = scanner_handleButton1Hold;
	aux2TapCallback = scanner_handleButton2Tap;
	aux2HoldCallback = scanner_handleButton2Hold;
	aux3TapCallback = scanner_handleButton3Tap;
	aux3HoldCallback = scanner_handleButton3Hold;
	aux4TapCallback = scanner_handleButton4Tap;
	aux4HoldCallback = scanner_handleButton4Hold;
}

void scanner_handleButton1EnterMenu(void) {
	uiSetLEDs(X_TABLE);
	uiResetTimerMenu();
}
void scanner_handleButton2EnterMenu(void) {
	uiSetLEDs(Y_TABLE);
	uiResetTimerMenu();
}
void scanner_handleButton3EnterMenu(void) {
	uiSetLEDs(X_TABLE);
	uiResetTimerMenu();
}
void scanner_handleButton4EnterMenu(void) {
	uiSetLEDs(SYNC_MODE);
	uiResetTimerMenu();
}
void scanner_handleButton5EnterMenu(void) {
	uiSetLEDs(Y_TABLE);
	uiResetTimerMenu();
}
void scanner_handleButton6EnterMenu(void) {
	uiSetLEDs(TERRAIN);
	uiResetTimerMenu();
}
void scanner_handleAux1EnterMenu(void) {
	uiTransition(ui_button5Menu);
}
void scanner_handleAux2EnterMenu(void) {
	uiTransition(ui_button5Menu);
}
void scanner_handleAux3EnterMenu(void) {
	uiTransition(ui_button5Menu);
}
void scanner_handleAux4EnterMenu(void) {
	uiTransition(ui_button5Menu);
}

void scanner_handleButton1Tap(void) {
	X_TABLE = incrementModeAndStore(X_TABLE, BUTTON1_MASK, numButton1Modes);
	scanner_handleButton1ModeChange(X_TABLE);
	uiClearLEDs();
	uiSetLEDs(X_TABLE);
	uiTransition(&ui_newMode);
}
void scanner_handleButton2Tap(void) {
	Y_TABLE = incrementModeAndStore(Y_TABLE, BUTTON2_MASK, numButton2Modes);
	scanner_handleButton2ModeChange(Y_TABLE);
	uiClearLEDs();
	uiSetLEDs(Y_TABLE);
	uiTransition(&ui_newMode);
}
void scanner_handleButton3Tap(void) {
	X_TABLE = decrementModeAndStore(X_TABLE, BUTTON3_MASK, numButton3Modes);
	scanner_handleButton3ModeChange(X_TABLE);
	uiClearLEDs();
	uiSetLEDs(X_TABLE);
	uiTransition(&ui_newMode);
}
void scanner_handleButton4Tap(void) {
	SYNC_MODE = incrementModeAndStore(SYNC_MODE, BUTTON4_MASK, numButton4Modes);
	scanner_handleButton4ModeChange(SYNC_MODE);
	uiClearLEDs();
	uiSetLEDs(SYNC_MODE);
	uiTransition(&ui_newMode);
}
void scanner_handleButton5Tap(void) {
	Y_TABLE = decrementModeAndStore(Y_TABLE, BUTTON5_MASK, numButton5Modes);
	scanner_handleButton5ModeChange(Y_TABLE);
	uiClearLEDs();
	uiSetLEDs(Y_TABLE);
	uiTransition(&ui_newMode);
}
void scanner_handleButton6Tap(void) {
	TERRAIN = incrementModeAndStore(TERRAIN, BUTTON6_MASK,
			numButton6Modes);
	scanner_handleButton6ModeChange(TERRAIN);
	uiClearLEDs();
	uiSetLEDs(TERRAIN);
	uiTransition(&ui_newMode);
}

void scanner_handleAux1Tap(void) {
	uiTransition(ui_button5Menu);
}

void scanner_handleAux2Tap(void) {
	uiTransition(ui_button5Menu);
}

void scanner_handleAux3Tap(void) {
	uiTransition(ui_button5Menu);
}

void scanner_handleAux4Tap(void) {
	uiTransition(ui_button5Menu);
}

void scanner_handleButton1Hold(void) {
	uiTransition(&ui_default);
}
void scanner_handleButton2Hold(void) {
	uiTransition(&ui_default);
}
void scanner_handleButton3Hold(void) {
	uiTransition(&ui_default);
}
void scanner_handleButton4Hold(void) {
	uiTransition(&ui_default);
}
void scanner_handleButton5Hold(void) {
	uiTransition(&ui_default);
}
void scanner_handleButton6Hold(void) {
	uiTransition(&ui_default);
}
void scanner_handleAux1Hold(void) {
	uiTransition(&ui_button5Menu);
}
void scanner_handleAux2Hold(void) {
	uiTransition(&ui_newAuxMode);
}
void scanner_handleAux3Hold(void) {
	uiTransition(&ui_newAuxMode);
}
void scanner_handleAux4Hold(void) {
	uiTransition(&ui_newAuxMode);
}

