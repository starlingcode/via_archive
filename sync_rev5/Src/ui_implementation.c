#include "main.h"
#include "tsl_user.h"
#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"
#include "user_interface.h"
#include "dsp.h"
#include "main_state_machine.h"
#include "modes.h"
#include "via_rev5_hardware_io.h"
#include "fill_buffer.h"


void handleButton1Tap(void) {
	SH_MODE = incrementModeAndStore(SH_MODE, BUTTON1_MASK, numButton1Modes);
	handleButton1ModeChange(SH_MODE);
	uiClearLEDs();
	uiSetLEDs(SH_MODE);
	uiTransition(&ui_newMode);
}
void handleButton2Tap(void) {
	SCALE_MODE = incrementModeAndStore(SCALE_MODE, BUTTON2_MASK, numButton2Modes);
	handleButton2ModeChange(SCALE_MODE);
	uiClearLEDs();
	uiSetLEDs(SCALE_MODE);
	uiTransition(&ui_newMode);
}
void handleButton3Tap(void) {
	X_MODE = incrementModeAndStore(X_MODE, BUTTON3_MASK, numButton3Modes);
	handleButton3ModeChange(X_MODE);
	uiClearLEDs();
	uiSetLEDs(X_MODE);
	uiTransition(&ui_newMode);
}
void handleButton4Tap(void) {
	SYNC_MODE = incrementModeAndStore(SYNC_MODE, BUTTON4_MASK, numButton4Modes);
	handleButton4ModeChange(SYNC_MODE);
	uiClearLEDs();
	uiSetLEDs(SYNC_MODE);
	uiTransition(&ui_newMode);
}
void handleButton5Tap(void) {
	GROUP_MODE = incrementModeAndStore(GROUP_MODE, BUTTON5_MASK, numButton5Modes);
	handleButton5ModeChange(GROUP_MODE);
	uiClearLEDs();
	uiSetLEDs(GROUP_MODE);
	uiTransition(&ui_newMode);
}
void handleButton6Tap(void) {
	TABLE_MODE = incrementModeAndStore(TABLE_MODE, BUTTON6_MASK, numButton6Modes);
	handleButton6ModeChange(TABLE_MODE);
	uiClearLEDs();
	uiSetLEDs(TABLE_MODE);
	uiTransition(&ui_newMode);
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

void handleButton1ModeChange(int mode) {

	switch (mode) {
	case noSH:
		calculateSH = calculateSHMode1;
		break;
	case sampletrack:
		calculateSH = calculateSHMode2;
		break;
	case resample:
		calculateSH = calculateSHMode3;
		break;
	default:
		break;
	}

}

void handleButton2ModeChange(int mode) {

	softwareSignals.scale = scaleArray[GROUP_MODE][mode];

}

void handleButton3ModeChange(int mode) {

	switch (mode) {
	case root:
		advancePhase = advancePhaseRoot;
		break;
	case pm:
		advancePhase = advancePhasePM;
		break;
	case fm:
		advancePhase = advancePhaseFM;
		break;
	case pwm:
		advancePhase = advancePhasePWM;
		break;
	default:
		break;
	}


}

void handleButton4ModeChange(int mode) {

	softwareSignals.syncMode = mode;

}

void handleButton5ModeChange(int mode) {

	softwareSignals.scale = scaleArray[mode][SCALE_MODE];
	switchFamily();

}

void handleButton6ModeChange(int mode) {

	switchFamily();

}
