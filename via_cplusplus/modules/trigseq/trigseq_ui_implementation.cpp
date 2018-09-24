/*
 * meta_ui_implementation.cpp
 *
 *  Created on: Sep 12, 2018
 *      Author: willmitchell
 */


#include "trigseq.hpp"
#include "user_interface.hpp"

void ViaTrigseq::ViaTrigseqUI::initialize(void) {

#ifdef BUILD_VIRTUAL

	button1 = this_module.button1Input;
	button2 = this_module.button2Input;
	button3 = this_module.button3Input;
	button4 = this_module.button4Input;
	button5 = this_module.button5Input;
	button6 = this_module.button6Input;

#endif

#ifdef BUILD_F373

	tsl_user_Init();

	button1 = (int32_t *) &BUTTON1SENSOR;
	button2 = (int32_t *) &BUTTON2SENSOR;
	button3 = (int32_t *) &BUTTON3SENSOR;
	button4 = (int32_t *) &BUTTON4SENSOR;
	button5 = (int32_t *) &BUTTON5SENSOR;
	button6 = (int32_t *) &BUTTON6SENSOR;

#endif

	state = &ViaUI::defaultMenu;
	transition(&ViaUI::defaultMenu);
}

void trigseqTouchLink (void * uiVoid) {
	ViaTrigseq::ViaTrigseqUI * ui = (ViaTrigseq::ViaTrigseqUI *) uiVoid;
	ui->dispatch(SENSOR_EVENT_SIG);
}

void ViaTrigseq::ViaTrigseqUI::defaultEnterMenuCallback(void) {
	this_module.runtimeDisplay = 1;
}
void ViaTrigseq::ViaTrigseqUI::newModeEnterMenuCallback(void) {
	;
}
void ViaTrigseq::ViaTrigseqUI::newAuxModeEnterMenuCallback(void) {
	;
}
void ViaTrigseq::ViaTrigseqUI::presetEnterMenuCallback(void) {;

}

void ViaTrigseq::ViaTrigseqUI::button1EnterMenuCallback(void) {
	this_module.runtimeDisplay = 0;
	this_module.clearLEDs();
	this_module.clearRGB();
	this_module.setLEDs(SH_A_MODE);
	resetTimerMenu();
}
void ViaTrigseq::ViaTrigseqUI::button2EnterMenuCallback(void) {
	this_module.runtimeDisplay = 0;
	this_module.clearLEDs();
	this_module.clearRGB();
	this_module.setLEDs(AND_A_MODE);
	resetTimerMenu();
}
void ViaTrigseq::ViaTrigseqUI::button3EnterMenuCallback(void) {
	this_module.runtimeDisplay = 0;
	this_module.clearLEDs();
	this_module.clearRGB();
	this_module.setLEDs(A_PATTERN_BANK);
	resetTimerMenu();
}
void ViaTrigseq::ViaTrigseqUI::button4EnterMenuCallback(void) {
	this_module.runtimeDisplay = 0;
	this_module.clearLEDs();
	this_module.clearRGB();
	if (!B_PATTERN_BANK && !A_PATTERN_BANK) {
		this->transition(&ViaTrigseq::ViaTrigseqUI::aux3Menu);
	} else {
		this_module.setLEDs(AND_A_MODE);
		resetTimerMenu();
	}
}
void ViaTrigseq::ViaTrigseqUI::button5EnterMenuCallback(void) {
	this_module.runtimeDisplay = 0;
	this_module.clearLEDs();
	this_module.clearRGB();
	this_module.setLEDs(AND_B_MODE);
	resetTimerMenu();
}
void ViaTrigseq::ViaTrigseqUI::button6EnterMenuCallback(void) {
	this_module.runtimeDisplay = 0;
	this_module.clearLEDs();
	this_module.clearRGB();
	this_module.setLEDs(B_PATTERN_BANK);
	resetTimerMenu();
}
void ViaTrigseq::ViaTrigseqUI::aux1EnterMenuCallback(void) {
	transition(&ViaTrigseq::ViaTrigseqUI::button5Menu);
}
void ViaTrigseq::ViaTrigseqUI::aux2EnterMenuCallback(void) {
	this_module.clearLEDs();
	this_module.setLEDs(LOGIC_MODE);
	resetTimerMenu();
}
void ViaTrigseq::ViaTrigseqUI::aux3EnterMenuCallback(void) {
	transition(&ViaTrigseq::ViaTrigseqUI::button5Menu);
}
void ViaTrigseq::ViaTrigseqUI::aux4EnterMenuCallback(void) {
	transition(&ViaTrigseq::ViaTrigseqUI::button5Menu);
}

void ViaTrigseq::ViaTrigseqUI::button1TapCallback(void) {
	SH_A_MODE = incrementModeAndStore(SH_A_MODE, BUTTON1_MASK, numButton1Modes);
	this_module.handleButton1ModeChange(SH_A_MODE);
	this_module.clearLEDs();
	this_module.setLEDs(SH_A_MODE);
	transition(&ViaTrigseq::ViaTrigseqUI::newModeMenu);
}
void ViaTrigseq::ViaTrigseqUI::button2TapCallback(void) {
	AND_A_MODE = incrementModeAndStore(AND_A_MODE, BUTTON2_MASK, numButton2Modes);
	this_module.handleButton2ModeChange(AND_A_MODE);
	this_module.clearLEDs();
	this_module.setLEDs(AND_A_MODE);
	transition(&ViaTrigseq::ViaTrigseqUI::newModeMenu);
}
void ViaTrigseq::ViaTrigseqUI::button3TapCallback(void) {
	A_PATTERN_BANK = incrementModeAndStore(A_PATTERN_BANK, BUTTON3_MASK, numButton3Modes);
	this_module.handleButton3ModeChange(A_PATTERN_BANK);
	this_module.clearLEDs();
	this_module.setLEDs(A_PATTERN_BANK);
	transition(&ViaTrigseq::ViaTrigseqUI::newModeMenu);
}
void ViaTrigseq::ViaTrigseqUI::button4TapCallback(void) {
	AND_A_MODE = incrementModeAndStore(AND_A_MODE, BUTTON4_MASK, numButton4Modes);
	this_module.handleButton4ModeChange(AND_A_MODE);
	this_module.clearLEDs();
	this_module.setLEDs(AND_A_MODE);
	transition(&ViaTrigseq::ViaTrigseqUI::newModeMenu);
}
void ViaTrigseq::ViaTrigseqUI::button5TapCallback(void) {
	AND_B_MODE = decrementModeAndStore(AND_B_MODE, BUTTON5_MASK, numButton5Modes);
	this_module.handleButton5ModeChange(AND_B_MODE);
	this_module.clearLEDs();
	this_module.setLEDs(AND_B_MODE);
	transition(&ViaTrigseq::ViaTrigseqUI::newModeMenu);
}
void ViaTrigseq::ViaTrigseqUI::button6TapCallback(void) {
	B_PATTERN_BANK = incrementModeAndStore(B_PATTERN_BANK, BUTTON6_MASK, numButton6Modes);
	this_module.handleButton6ModeChange(B_PATTERN_BANK);
	this_module.clearLEDs();
	this_module.setLEDs(B_PATTERN_BANK);
	transition(&ViaTrigseq::ViaTrigseqUI::newModeMenu);
}

void ViaTrigseq::ViaTrigseqUI::aux1TapCallback(void) {
	transition(&ViaTrigseq::ViaTrigseqUI::button5Menu);
}

void ViaTrigseq::ViaTrigseqUI::aux2TapCallback(void) {
	LOGIC_MODE = incrementModeAndStore(LOGIC_MODE, AUX_MODE2_MASK, numAux2Modes);
	this_module.handleAux2ModeChange(LOGIC_MODE);
	this_module.clearLEDs();
	this_module.setLEDs(LOGIC_MODE);
	transition(&ViaTrigseq::ViaTrigseqUI::newAuxModeMenu);
}

void ViaTrigseq::ViaTrigseqUI::aux3TapCallback(void) {
	transition(&ViaTrigseq::ViaTrigseqUI::button5Menu);
}

void ViaTrigseq::ViaTrigseqUI::aux4TapCallback(void) {
	transition(&ViaTrigseq::ViaTrigseqUI::button5Menu);
}

void ViaTrigseq::ViaTrigseqUI::button1HoldCallback(void) {
	transition(&ViaTrigseq::ViaTrigseqUI::defaultMenu);
}
void ViaTrigseq::ViaTrigseqUI::button2HoldCallback(void) {
	transition(&ViaTrigseq::ViaTrigseqUI::defaultMenu);
}
void ViaTrigseq::ViaTrigseqUI::button3HoldCallback(void) {
	transition(&ViaTrigseq::ViaTrigseqUI::defaultMenu);
}
void ViaTrigseq::ViaTrigseqUI::button4HoldCallback(void) {
	transition(&ViaTrigseq::ViaTrigseqUI::defaultMenu);
}
void ViaTrigseq::ViaTrigseqUI::button5HoldCallback(void) {
	transition(&ViaTrigseq::ViaTrigseqUI::defaultMenu);
}
void ViaTrigseq::ViaTrigseqUI::button6HoldCallback(void) {
	transition(&ViaTrigseq::ViaTrigseqUI::defaultMenu);
}

void ViaTrigseq::ViaTrigseqUI::aux1HoldCallback(void) {
	transition(&ViaTrigseq::ViaTrigseqUI::button5Menu);
}

void ViaTrigseq::ViaTrigseqUI::aux2HoldCallback(void) {
	transition(&ViaTrigseq::ViaTrigseqUI::defaultMenu);
}

void ViaTrigseq::ViaTrigseqUI::aux3HoldCallback(void) {
	transition(&ViaTrigseq::ViaTrigseqUI::defaultMenu);
}

void ViaTrigseq::ViaTrigseqUI::aux4HoldCallback(void) {
	transition(&ViaTrigseq::ViaTrigseqUI::defaultMenu);
}


