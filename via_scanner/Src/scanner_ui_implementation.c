
#include "user_interface.h"
#include "signals.h"
#include "scanner_modes.h"
#include "scanner_tables.h"
#include "scanner_ui_implementation.h"

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
	SH_MODE = decrementModeAndStore(SH_MODE, BUTTON3_MASK, numButton3Modes);
	handleButton3ModeChange(SH_MODE);
	uiClearLEDs();
	uiSetLEDs(SH_MODE);
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
	TABLE = decrementModeAndStore(TABLE, BUTTON5_MASK, numButton5Modes);
	handleButton5ModeChange(TABLE);
	uiClearLEDs();
	uiSetLEDs(TABLE);
	uiTransition(&ui_newMode);
}
void handleButton6Tap(void) {
	MORPH_PWM_MODE = incrementModeAndStore(MORPH_PWM_MODE, BUTTON6_MASK, numButton6Modes);
	handleButton6ModeChange(MORPH_PWM_MODE);
	uiClearLEDs();
	uiSetLEDs(MORPH_PWM_MODE);
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

	// change x family

	switchXFamily();
	switch (softwareSignals.xTable->familySize) {
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

void handleButton2ModeChange(int mode) {

	// change y family

	switchYFamily();
	switch (softwareSignals.yTable->familySize) {
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

void handleButton3ModeChange(int mode) {

	// change x family

	switchXFamily();
	switch (softwareSignals.xTable->familySize) {
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

void handleButton4ModeChange(int mode) {

	softwareSignals.syncMode = mode;

}

void handleButton5ModeChange(int mode) {

	switchYFamily();
	switch (softwareSignals.yTable->familySize) {
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

void handleButton6ModeChange(int mode) {

	softwareSignals.terrainType = mode;


}

void handleAux4ModeChange(int mode) {


}

void switchXFamily(void) {

	loadSampleArrayX(familyArray[SH_MODE]);
	softwareSignals.xTable = familyArray[SH_MODE];

}

void switchYFamily(void) {

	loadSampleArrayY(familyArray[TABLE]);
	softwareSignals.yTable = familyArray[TABLE];

}
