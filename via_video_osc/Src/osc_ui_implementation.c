
#include "user_interface.h"
#include "signals.h"
#include "osc_tables.h"
#include "osc_fill_buffer.h"
#include "osc_modes.h"
#include "osc_ui_implementation.h"

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

	aux1TapCallback = handleButton1Tap;
	aux1HoldCallback = handleButton1Hold;
	aux2TapCallback = handleButton2Tap;
	aux2HoldCallback = handleButton2Hold;
	aux3TapCallback = handleButton3Tap;
	aux3HoldCallback = handleButton3Hold;
	aux4TapCallback = handleButton4Tap;
	aux4HoldCallback = handleButton4Hold;
}

void handleButton1EnterMenu(void) {
	uiSetLEDs(SH_MODE);
	uiResetTimerMenu();
}
void handleButton2EnterMenu(void) {
	uiSetLEDs(TABLE);
	uiResetTimerMenu();
}
void handleButton3EnterMenu(void) {
	uiSetLEDs(FM_PM_MODE);
	uiResetTimerMenu();
}
void handleButton4EnterMenu(void) {
	uiSetLEDs(SYNC_MODE);
	uiResetTimerMenu();
}
void handleButton5EnterMenu(void) {
	uiSetLEDs(TABLE);
	uiResetTimerMenu();
}
void handleButton6EnterMenu(void) {
	uiSetLEDs(SYNC_MODE);
	uiResetTimerMenu();
}
void handleAux1EnterMenu(void) {
	uiTransition(ui_button5Menu);
}
void handleAux2EnterMenu(void) {
	uiTransition(ui_button5Menu);
}
void handleAux3EnterMenu(void) {
	uiTransition(ui_button5Menu);
}
void handleAux4EnterMenu(void) {
	uiTransition(ui_button5Menu);
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
	FM_PM_MODE = decrementModeAndStore(FM_PM_MODE, BUTTON3_MASK, numButton3Modes);
	handleButton3ModeChange(FM_PM_MODE);
	uiClearLEDs();
	uiSetLEDs(FM_PM_MODE);
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

void handleAux1Tap(void) {
	uiTransition(ui_button5Menu);
}

void handleAux2Tap(void) {
	uiTransition(ui_button5Menu);
}

void handleAux3Tap(void) {
	uiTransition(ui_button5Menu);
}

void handleAux4Tap(void) {
	uiTransition(ui_button5Menu);
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

//	switch (mode) {
//	case none:
//		logicAndFilter = &logicAndFilterSHOff;
//		displaySHMode = &displaySH_Off;
//		break;
//	case decimate:
//		logicAndFilter = &logicAndFilterSHOn;
//		displaySHMode = &displaySH_On;
//		break;
//	}

	SH_A_TRACK;
	SH_B_TRACK;
}

void handleButton2ModeChange(int mode) {

	switchFamily();


}

void handleButton3ModeChange(int mode) {

	switch (mode) {
	case FM:
		signals.inputs->fm = cv2SampleBuffer;
		signals.inputs->pm = virtualGround;
		displayXCVMode = &displayXCV_FM;
		break;
	case PM:
		signals.inputs->fm = virtualGround;
		signals.inputs->pm = cv2SampleBuffer;
		displayXCVMode = &displayXCV_PM;
		break;
	}

}

void handleButton4ModeChange(int mode) {

	softwareSignals.syncMode = mode;
	// sync modes handled in IRQ handler
	if (button4Mode == hard) {
		displaySyncMode = &displaySync_Hard;
	} else {
		displaySyncMode = &displaySync_Soft;
	}

}

void handleButton5ModeChange(int mode) {

	switchFamily();

}

void handleButton6ModeChange(int mode) {

	switch (mode) {
	case morphCV:
		signals.inputs->morphMod = cv3SampleBuffer;
		signals.inputs->pwm = virtualGround;
		displayMorphMode = &displayMorph_Morph;
		break;
	case pwmCV:
		signals.inputs->morphMod = virtualGround;
		signals.inputs->pwm = cv3SampleBuffer;
		displayMorphMode = &displayMorph_PMW;
		break;
	}


}

void handleAux4ModeChange(int mode) {


}

void switchFamily(void) {

	loadSampleArray(familyArray[TABLE]);
	softwareSignals.currentFamily = familyArray[TABLE];

}


