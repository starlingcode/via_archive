/*
 * meta_ui_implementation.cpp
 *
 *  Created on: Sep 12, 2018
 *      Author: willmitchell
 */


#include "gateseq.hpp"
#include "user_interface.hpp"

void ViaGateseq::ViaGateseqUI::initialize(void) {

#ifdef BUILD_VIRTUAL

	button1 = (int32_t *) &this_module.button1Input;
	button2 = (int32_t *) &this_module.button2Input;
	button3 = (int32_t *) &this_module.button3Input;
	button4 = (int32_t *) &this_module.button4Input;
	button5 = (int32_t *) &this_module.button5Input;
	button6 = (int32_t *) &this_module.button6Input;

#endif

#ifdef BUILD_F373

	tsl_user_Init();

	button1 = (int32_t *) &BUTTON1SENSOR;
	button2 = (int32_t *) &BUTTON2SENSOR;
	button3 = (int32_t *) &BUTTON3SENSOR;
	button4 = (int32_t *) &BUTTON4SENSOR;
	button5 = (int32_t *) &BUTTON5SENSOR;
	button6 = (int32_t *) &BUTTON6SENSOR;

	initializeMemory();

#endif

	loadFromEEPROM(0);

#ifdef BUILD_F373

	recallModuleState();

#endif

	state = &ViaUI::defaultMenu;
	transition(&ViaUI::defaultMenu);
}

void gateseqTouchLink (void * uiVoid) {
	ViaGateseq::ViaGateseqUI * ui = (ViaGateseq::ViaGateseqUI *) uiVoid;
	ui->dispatch(SENSOR_EVENT_SIG);
}

void ViaGateseq::ViaGateseqUI::recallModuleState(void) {

	this_module.handleButton1ModeChange(this_module.gateseqUI.button1Mode);
	this_module.handleButton2ModeChange(this_module.gateseqUI.button2Mode);
	this_module.handleButton3ModeChange(this_module.gateseqUI.button3Mode);
	this_module.handleButton4ModeChange(this_module.gateseqUI.button4Mode);
	this_module.handleButton5ModeChange(this_module.gateseqUI.button5Mode);
	this_module.handleButton6ModeChange(this_module.gateseqUI.button6Mode);
	this_module.handleAux2ModeChange(this_module.gateseqUI.aux2Mode);

}

void ViaGateseq::ViaGateseqUI::uiSetLEDs(int mode) {
	this_module.setLEDs(mode);
}

void ViaGateseq::ViaGateseqUI::defaultEnterMenuCallback(void) {
	this_module.runtimeDisplay = 1;
}
void ViaGateseq::ViaGateseqUI::newModeEnterMenuCallback(void) {
	;
}
void ViaGateseq::ViaGateseqUI::newAuxModeEnterMenuCallback(void) {
	;
}
void ViaGateseq::ViaGateseqUI::presetEnterMenuCallback(void) {;

	this_module.runtimeDisplay = 0;
	this_module.clearLEDs();
	this_module.clearRGB();

}

void ViaGateseq::ViaGateseqUI::button1EnterMenuCallback(void) {
	this_module.runtimeDisplay = 0;
	this_module.clearLEDs();
	this_module.clearRGB();
	this_module.setLEDs(SH_A_MODE);
	resetTimerMenu();
}
void ViaGateseq::ViaGateseqUI::button2EnterMenuCallback(void) {
	this_module.runtimeDisplay = 0;
	this_module.clearLEDs();
	this_module.clearRGB();
	this_module.setLEDs(AND_A_MODE);
	resetTimerMenu();
}
void ViaGateseq::ViaGateseqUI::button3EnterMenuCallback(void) {
	this_module.runtimeDisplay = 0;
	this_module.clearLEDs();
	this_module.clearRGB();
	this_module.setLEDs(A_PATTERN_BANK);
	this_module.setRedLED((button3Mode >> 1) * 4095);
	this_module.setGreenLED(!(button3Mode >> 1) * 4095);
	if (button3Mode == 1 || button3Mode == 3) {
		SET_BLUE_LED_ONOFF(1);
	} else {
		SET_BLUE_LED_ONOFF(0);
	}
	resetTimerMenu();
}
void ViaGateseq::ViaGateseqUI::button4EnterMenuCallback(void) {
	this_module.runtimeDisplay = 0;
	this_module.clearLEDs();
	this_module.clearRGB();
	this_module.setLEDs(SH_B_MODE);
	resetTimerMenu();
}
void ViaGateseq::ViaGateseqUI::button5EnterMenuCallback(void) {
	this_module.runtimeDisplay = 0;
	this_module.clearLEDs();
	this_module.clearRGB();
	this_module.setLEDs(AND_B_MODE);
	resetTimerMenu();
}
void ViaGateseq::ViaGateseqUI::button6EnterMenuCallback(void) {
	this_module.runtimeDisplay = 0;
	this_module.clearLEDs();
	this_module.clearRGB();
	this_module.setLEDs(B_PATTERN_BANK);
	resetTimerMenu();
}
void ViaGateseq::ViaGateseqUI::aux1EnterMenuCallback(void) {
	transition(&ViaGateseq::ViaGateseqUI::button5Menu);
}
void ViaGateseq::ViaGateseqUI::aux2EnterMenuCallback(void) {
	this_module.clearLEDs();
	this_module.setLEDs(LOGIC_MODE);
	resetTimerMenu();
}
void ViaGateseq::ViaGateseqUI::aux3EnterMenuCallback(void) {
	transition(&ViaGateseq::ViaGateseqUI::button5Menu);
}
void ViaGateseq::ViaGateseqUI::aux4EnterMenuCallback(void) {
	transition(&ViaGateseq::ViaGateseqUI::button5Menu);
}

void ViaGateseq::ViaGateseqUI::button1TapCallback(void) {
	SH_A_MODE = incrementModeAndStore(SH_A_MODE, BUTTON1_MASK, numButton1Modes, BUTTON1_MASK);
	this_module.handleButton1ModeChange(SH_A_MODE);
	this_module.clearLEDs();
	this_module.setLEDs(SH_A_MODE);
	transition(&ViaGateseq::ViaGateseqUI::newModeMenu);
}
void ViaGateseq::ViaGateseqUI::button2TapCallback(void) {
	AND_A_MODE = incrementModeAndStore(AND_A_MODE, BUTTON2_MASK, numButton2Modes, BUTTON2_MASK);
	this_module.handleButton2ModeChange(AND_A_MODE);
	this_module.clearLEDs();
	this_module.setLEDs(AND_A_MODE);
	transition(&ViaGateseq::ViaGateseqUI::newModeMenu);
}
void ViaGateseq::ViaGateseqUI::button3TapCallback(void) {
	A_PATTERN_BANK = incrementModeAndStore(A_PATTERN_BANK, BUTTON3_MASK, numButton3Modes, BUTTON3_MASK);
	this_module.handleButton3ModeChange(A_PATTERN_BANK);
	this_module.clearLEDs();
	this_module.setLEDs(A_PATTERN_BANK);
	transition(&ViaGateseq::ViaGateseqUI::newModeMenu);
}
void ViaGateseq::ViaGateseqUI::button4TapCallback(void) {
	SH_B_MODE = incrementModeAndStore(SH_B_MODE, BUTTON4_MASK, numButton4Modes, BUTTON4_MASK);
	this_module.handleButton4ModeChange(SH_B_MODE);
	this_module.clearLEDs();
	this_module.setLEDs(SH_B_MODE);
	transition(&ViaGateseq::ViaGateseqUI::newModeMenu);
}
void ViaGateseq::ViaGateseqUI::button5TapCallback(void) {
	AND_B_MODE = incrementModeAndStore(AND_B_MODE, BUTTON5_MASK, numButton5Modes, BUTTON5_MASK);
	this_module.handleButton5ModeChange(AND_B_MODE);
	this_module.clearLEDs();
	this_module.setLEDs(AND_B_MODE);
	transition(&ViaGateseq::ViaGateseqUI::newModeMenu);
}
void ViaGateseq::ViaGateseqUI::button6TapCallback(void) {
	B_PATTERN_BANK = incrementModeAndStore(B_PATTERN_BANK, BUTTON6_MASK, numButton6Modes, BUTTON6_MASK);
	this_module.handleButton6ModeChange(B_PATTERN_BANK);
	this_module.clearLEDs();
	this_module.setLEDs(B_PATTERN_BANK);
	transition(&ViaGateseq::ViaGateseqUI::newModeMenu);
}

void ViaGateseq::ViaGateseqUI::aux1TapCallback(void) {
	transition(&ViaGateseq::ViaGateseqUI::button5Menu);
}

void ViaGateseq::ViaGateseqUI::aux2TapCallback(void) {
	LOGIC_MODE = incrementModeAndStore(LOGIC_MODE, AUX_MODE2_MASK, numAux2Modes, AUX_MODE2_MASK);
	this_module.handleAux2ModeChange(LOGIC_MODE);
	this_module.clearLEDs();
	this_module.setLEDs(LOGIC_MODE);
	transition(&ViaGateseq::ViaGateseqUI::newAuxModeMenu);
}

void ViaGateseq::ViaGateseqUI::aux3TapCallback(void) {
	transition(&ViaGateseq::ViaGateseqUI::button5Menu);
}

void ViaGateseq::ViaGateseqUI::aux4TapCallback(void) {
	transition(&ViaGateseq::ViaGateseqUI::button5Menu);
}

void ViaGateseq::ViaGateseqUI::button1HoldCallback(void) {
	transition(&ViaGateseq::ViaGateseqUI::defaultMenu);
}
void ViaGateseq::ViaGateseqUI::button2HoldCallback(void) {
	transition(&ViaGateseq::ViaGateseqUI::defaultMenu);
}
void ViaGateseq::ViaGateseqUI::button3HoldCallback(void) {
	transition(&ViaGateseq::ViaGateseqUI::defaultMenu);
}
void ViaGateseq::ViaGateseqUI::button4HoldCallback(void) {
	transition(&ViaGateseq::ViaGateseqUI::defaultMenu);
}
void ViaGateseq::ViaGateseqUI::button5HoldCallback(void) {
	transition(&ViaGateseq::ViaGateseqUI::defaultMenu);
}
void ViaGateseq::ViaGateseqUI::button6HoldCallback(void) {
	transition(&ViaGateseq::ViaGateseqUI::defaultMenu);
}

void ViaGateseq::ViaGateseqUI::aux1HoldCallback(void) {
	transition(&ViaGateseq::ViaGateseqUI::button5Menu);
}

void ViaGateseq::ViaGateseqUI::aux2HoldCallback(void) {
	transition(&ViaGateseq::ViaGateseqUI::defaultMenu);
}

void ViaGateseq::ViaGateseqUI::aux3HoldCallback(void) {
	transition(&ViaGateseq::ViaGateseqUI::defaultMenu);
}

void ViaGateseq::ViaGateseqUI::aux4HoldCallback(void) {
	transition(&ViaGateseq::ViaGateseqUI::defaultMenu);
}


