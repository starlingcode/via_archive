
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
	X_TABLE = incrementModeAndStore(X_TABLE, BUTTON1_MASK, numButton1Modes);
	handleButton1ModeChange(X_TABLE);
	uiClearLEDs();
	uiSetLEDs(X_TABLE);
	uiTransition(&ui_newMode);
}
void handleButton2Tap(void) {
	Y_TABLE = incrementModeAndStore(Y_TABLE, BUTTON2_MASK, numButton2Modes);
	handleButton2ModeChange(Y_TABLE);
	uiClearLEDs();
	uiSetLEDs(Y_TABLE);
	uiTransition(&ui_newMode);
}
void handleButton3Tap(void) {
	X_TABLE = decrementModeAndStore(X_TABLE, BUTTON3_MASK, numButton3Modes);
	handleButton3ModeChange(X_TABLE);
	uiClearLEDs();
	uiSetLEDs(X_TABLE);
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
	Y_TABLE = decrementModeAndStore(Y_TABLE, BUTTON5_MASK, numButton5Modes);
	handleButton5ModeChange(Y_TABLE);
	uiClearLEDs();
	uiSetLEDs(Y_TABLE);
	uiTransition(&ui_newMode);
}
void handleButton6Tap(void) {
	TERRAIN_MODE = incrementModeAndStore(TERRAIN_MODE, BUTTON6_MASK, numButton6Modes);
	handleButton6ModeChange(TERRAIN_MODE);
	uiClearLEDs();
	uiSetLEDs(TERRAIN_MODE);
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

	loadSampleArray(familyArray[X_TABLE]);
	softwareSignals.xTable = familyArray[X_TABLE];

}

void switchYFamily(void) {

	loadSampleArray(familyArray[Y_TABLE]);
	softwareSignals.yTable = familyArray[Y_TABLE];

}
