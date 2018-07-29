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
#include "tables.h"

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

void handleAux4Tap(void) {
	TABLE_GROUP_MODE = incrementModeAndStore(TABLE_GROUP_MODE, AUX_MODE4_MASK, numAux4Modes);
	handleAux4ModeChange(TABLE_GROUP_MODE);
	uiClearLEDs();
	uiSetLEDs(TABLE_GROUP_MODE);
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
void handleAux4Hold(void) {
	uiTransition(&ui_newAuxMode);
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
	if (!TABLE_GROUP_MODE) {
		switchFamily();
		switch (currentFamily->familySize) {
			case 2:
				softwareSignals.morphShift = 1;
				break;
			case 3:
				softwareSignals.morphShift = 2;
				break;
			case 5:
				softwareSignals.morphShift = 3;
				break;
			case 9:
				softwareSignals.morphShift = 4;
				break;
		}
	}

}

void handleButton6ModeChange(int mode) {

	if (TABLE_GROUP_MODE) {
		switchGlobalFamily();
	} else {
		switchFamily();
		switch (currentFamily->familySize) {
			case 2:
				softwareSignals.morphShift = 1;
				break;
			case 3:
				softwareSignals.morphShift = 2;
				break;
			case 5:
				softwareSignals.morphShift = 3;
				break;
			case 9:
				softwareSignals.morphShift = 4;
				break;
		}
	}


}

void handleAux4ModeChange(int mode) {

	switchGlobalFamily();
	switch (currentFamily->familySize) {
		case 2:
			softwareSignals.morphShift = 1;
			break;
		case 3:
			softwareSignals.morphShift = 2;
			break;
		case 5:
			softwareSignals.morphShift = 3;
			break;
		case 9:
			softwareSignals.morphShift = 4;
			break;
	}

}
