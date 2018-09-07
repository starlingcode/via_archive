
#include "user_interface.h"
#include "sync_dsp.h"
#include "sync_modes.h"
#include "sync_next_sample.h"
#include "sync_tables.h"
#include "sync_ui_implementation.h"

void initializeUICallbacks(void) {

	button1EnterMenuCallback = handleButton1EnterMenu;
	button2EnterMenuCallback = handleButton2EnterMenu;
	button3EnterMenuCallback = handleButton3EnterMenu;
	button4EnterMenuCallback = handleButton4EnterMenu;
	button5EnterMenuCallback = handleButton5EnterMenu;
	button6EnterMenuCallback = handleButton6EnterMenu;

	aux1EnterMenuCallback = handleAux1EnterMenu;
	aux2EnterMenuCallback = handleAux2EnterMenu;
	aux3EnterMenuCallback = handleAux3EnterMenu;
	aux4EnterMenuCallback = handleAux4EnterMenu;

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

	aux1TapCallback = handleAux1Tap;
	aux1HoldCallback = handleAux1Hold;
	aux2TapCallback = handleAux2Tap;
	aux2HoldCallback = handleAux2Hold;
	aux3TapCallback = handleAux3Tap;
	aux3HoldCallback = handleAux3Hold;
	aux4TapCallback = handleAux4Tap;
	aux4HoldCallback = handleAux4Hold;
}

void handleButton1EnterMenu(void) {
	uiSetLEDs(SH_MODE);
	uiResetTimerMenu();
}
void handleButton2EnterMenu(void) {
	uiSetLEDs(SCALE_MODE);
	uiResetTimerMenu();
}
void handleButton3EnterMenu(void) {
	uiSetLEDs(X_MODE);
	uiResetTimerMenu();
}
void handleButton4EnterMenu(void) {
	uiSetLEDs(SYNC_MODE);
	uiResetTimerMenu();
}
void handleButton5EnterMenu(void) {
	uiSetLEDs(GROUP_MODE);
	uiResetTimerMenu();
}
void handleButton6EnterMenu(void) {
	uiSetLEDs(TABLE_MODE);
	uiResetTimerMenu();
}
void handleAux1EnterMenu(void) {
	uiTransition(ui_button5Menu);
}
void handleAux2EnterMenu(void) {
	uiClearLEDs();
	uiSetLEDs(LOGIC_A_MODE);
	uiResetTimerMenu();
}
void handleAux3EnterMenu(void) {
	uiClearLEDs();
	uiSetLEDs(QUADRATURE_MODE);
	uiResetTimerMenu();
}
void handleAux4EnterMenu(void) {
	uiClearLEDs();
	uiSetLEDs(TABLE_GROUP_MODE);
	uiResetTimerMenu();
}

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

void handleAux1Tap(void) {
	uiTransition(ui_button5Menu);
}

void handleAux2Tap(void) {
	LOGIC_A_MODE = incrementModeAndStore(LOGIC_A_MODE, AUX_MODE2_MASK, numAux2Modes);
	handleAux2ModeChange(LOGIC_A_MODE);
	uiClearLEDs();
	uiSetLEDs(LOGIC_A_MODE);
	uiTransition(&ui_newAuxMode);
}

void handleAux3Tap(void) {
	QUADRATURE_MODE = incrementModeAndStore(QUADRATURE_MODE, AUX_MODE3_MASK, numAux3Modes);
	handleAux3ModeChange(QUADRATURE_MODE);
	uiClearLEDs();
	uiSetLEDs(QUADRATURE_MODE);
	uiTransition(&ui_newAuxMode);
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
void handleAux1Hold(void) {
	uiTransition(&ui_button5Menu);
}
void handleAux2Hold(void) {
	uiTransition(&ui_newAuxMode);
}
void handleAux3Hold(void) {
	uiTransition(&ui_newAuxMode);
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

void handleAux1ModeChange(int mode) {


}


void handleAux2ModeChange(int mode) {

	switch (mode) {
	case gate:
		calculateLogicA = calculateLogicAGate;
		break;
	case delta:
		calculateLogicA = calculateLogicADelta;
		break;
	default:
		break;
	}

}


void handleAux3ModeChange(int mode) {

	switch (mode) {
	case noOffset:
		softwareSignals.phaseOffset = 0;
		break;
	case quarter:
		softwareSignals.phaseOffset = 1 << 23;
		break;
	case half:
		softwareSignals.phaseOffset = 1 << 24;
		break;
	case threeQuarters:
		softwareSignals.phaseOffset = (3 << 23);
		break;
	default:
		break;
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
