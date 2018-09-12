#include "trigseq.h"

void trigseq_initializeUICallbacks(void) {

	button1EnterMenuCallback = trigseq_handleButton1EnterMenu;
	button2EnterMenuCallback = trigseq_handleButton2EnterMenu;
	button3EnterMenuCallback = trigseq_handleButton3EnterMenu;
	button4EnterMenuCallback = trigseq_handleButton4EnterMenu;
	button5EnterMenuCallback = trigseq_handleButton5EnterMenu;
	button6EnterMenuCallback = trigseq_handleButton6EnterMenu;

	aux1EnterMenuCallback = trigseq_handleAux1EnterMenu;
	aux2EnterMenuCallback = trigseq_handleAux2EnterMenu;
	aux3EnterMenuCallback = trigseq_handleAux3EnterMenu;
	aux4EnterMenuCallback = trigseq_handleAux4EnterMenu;

	button1TapCallback = trigseq_handleButton1Tap;
	button1HoldCallback = trigseq_handleButton1Hold;
	button2TapCallback = trigseq_handleButton2Tap;
	button2HoldCallback = trigseq_handleButton2Hold;
	button3TapCallback = trigseq_handleButton3Tap;
	button3HoldCallback = trigseq_handleButton3Hold;
	button4TapCallback = trigseq_handleButton4Tap;
	button4HoldCallback = trigseq_handleButton4Hold;
	button5TapCallback = trigseq_handleButton5Tap;
	button5HoldCallback = trigseq_handleButton5Hold;
	button6TapCallback = trigseq_handleButton6Tap;
	button6HoldCallback = trigseq_handleButton6Hold;

	aux1TapCallback = trigseq_handleAux1Tap;
	aux1HoldCallback = trigseq_handleAux1Hold;
	aux2TapCallback = trigseq_handleAux2Tap;
	aux2HoldCallback = trigseq_handleAux2Hold;
	aux3TapCallback = trigseq_handleAux3Tap;
	aux3HoldCallback = trigseq_handleAux3Hold;
	aux4TapCallback = trigseq_handleAux4Tap;
	aux4HoldCallback = trigseq_handleAux4Hold;
}

void trigseq_handleButton1EnterMenu(void) {
	uiSetLEDs(SH_A_MODE);
	uiResetTimerMenu();
}
void trigseq_handleButton2EnterMenu(void) {
	uiSetLEDs(AND_A_MODE);
	uiResetTimerMenu();
}
void trigseq_handleButton3EnterMenu(void) {
	uiSetLEDs(A_PATTERN_BANK);
	uiResetTimerMenu();
}
void trigseq_handleButton4EnterMenu(void) {
	uiSetLEDs(SH_B_MODE);
	uiResetTimerMenu();
}
void trigseq_handleButton5EnterMenu(void) {
	uiSetLEDs(AND_B_MODE);
	uiResetTimerMenu();
}
void trigseq_handleButton6EnterMenu(void) {
	uiSetLEDs(B_PATTERN_BANK);
	uiResetTimerMenu();
}
void trigseq_handleAux1EnterMenu(void) {
	uiTransition(ui_button5Menu);
}
void trigseq_handleAux2EnterMenu(void) {
	uiSetLEDs(LOGIC_MODE);
	uiResetTimerMenu();
}
void trigseq_handleAux3EnterMenu(void) {
	uiTransition(ui_button5Menu);
}
void trigseq_handleAux4EnterMenu(void) {
	uiTransition(ui_button5Menu);
}

void trigseq_handleButton1Tap(void) {

	SH_A_MODE = incrementModeAndStore(SH_A_MODE, BUTTON1_MASK, numButton1Modes);
	trigseq_handleButton1ModeChange(SH_A_MODE);
	uiClearLEDs();
	uiSetLEDs(SH_A_MODE);
	uiTransition(&ui_newMode);
}
void trigseq_handleButton2Tap(void) {
	AND_A_MODE = incrementModeAndStore(AND_A_MODE, BUTTON2_MASK,
			numButton2Modes);
	trigseq_handleButton2ModeChange(AND_A_MODE);
	uiClearLEDs();
	uiSetLEDs(AND_A_MODE);
	uiTransition(&ui_newMode);
}
void trigseq_handleButton3Tap(void) {
	A_PATTERN_BANK = incrementModeAndStore(A_PATTERN_BANK, BUTTON3_MASK,
			numButton3Modes);
	trigseq_handleButton3ModeChange(A_PATTERN_BANK);
	uiClearLEDs();
	uiSetLEDs(A_PATTERN_BANK);
	uiTransition(&ui_newMode);
}
void trigseq_handleButton4Tap(void) {
	SH_B_MODE = incrementModeAndStore(SH_B_MODE, BUTTON4_MASK, numButton4Modes);
	trigseq_handleButton4ModeChange(SH_B_MODE);
	uiClearLEDs();
	uiSetLEDs(SH_B_MODE);
	uiTransition(&ui_newMode);
}
void trigseq_handleButton5Tap(void) {
	AND_B_MODE = incrementModeAndStore(AND_B_MODE, BUTTON5_MASK,
			numButton5Modes);
	trigseq_handleButton5ModeChange(AND_B_MODE);
	uiClearLEDs();
	uiSetLEDs(AND_B_MODE);
	uiTransition(&ui_newMode);
}
void trigseq_handleButton6Tap(void) {
	B_PATTERN_BANK = incrementModeAndStore(B_PATTERN_BANK, BUTTON6_MASK,
			numButton6Modes);
	trigseq_handleButton6ModeChange(B_PATTERN_BANK);
	uiClearLEDs();
	uiSetLEDs(B_PATTERN_BANK);
	uiTransition(&ui_newMode);
}

void trigseq_handleAux1Tap(void) {
	uiTransition(ui_button5Menu);
}

void trigseq_handleAux2Tap(void) {
	LOGIC_MODE = incrementModeAndStore(LOGIC_MODE, AUX_MODE2_MASK,
			numAux2Modes);
	trigseq_handleAux2ModeChange(LOGIC_MODE);
	uiClearLEDs();
	uiSetLEDs(LOGIC_MODE);
	uiTransition(&ui_newAuxMode);
}

void trigseq_handleAux3Tap(void) {
	uiTransition(ui_button5Menu);
}

void trigseq_handleAux4Tap(void) {
	uiTransition(ui_button5Menu);
}

void trigseq_handleButton1Hold(void) {
	uiTransition(&ui_default);
}
void trigseq_handleButton2Hold(void) {
	uiTransition(&ui_default);
}
void trigseq_handleButton3Hold(void) {
	uiTransition(&ui_default);
}
void trigseq_handleButton4Hold(void) {
	uiTransition(&ui_default);
}
void trigseq_handleButton5Hold(void) {
	uiTransition(&ui_default);
}
void trigseq_handleButton6Hold(void) {
	uiTransition(&ui_default);
}
void trigseq_handleAux1Hold(void) {
	uiTransition(&ui_button5Menu);
}
void trigseq_handleAux2Hold(void) {
	uiTransition(&ui_button5Menu);
}
void trigseq_handleAux3Hold(void) {
	uiTransition(&ui_button5Menu);
}
void trigseq_handleAux4Hold(void) {
	uiTransition(&ui_button5Menu);
}
