/*
 * ViaUI::save_recall.cpp
 *
 *  Created on: Sep 11, 2018
 *      Author: willmitchell
 */

#include "user_interface.hpp"

/**
 *
 * Initialization routine for the UI state machine
 * Initialize the eeprom and read the last saved mode set
 * Initialize those modes
 * Set the UI state default
 *
 */
void ViaUI::initialize(void) {

	// link to virtual module buttons at class initialization

#ifdef BUILD_F373

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

void ViaUI::loadFromEEPROM(int32_t position) {

//	eepromStatus = EE_ReadVariable(VirtAddVarTab[position * 2], &EEPROMTemp);
//	modeStateBuffer = EEPROMTemp;  // load bottom 16 bits
//	eepromStatus |= EE_ReadVariable(VirtAddVarTab[(position * 2) + 1],
//			&EEPROMTemp);
//	modeStateBuffer |= EEPROMTemp << 16;  // load 16 upper bits
//
//	if (eepromStatus != HAL_OK) {
//		uiSetLEDs(2);
//		transition(&ViaUI::error);
//	}

	//button1Mode = modeStateBuffer & BUTTON1_MASK;
	//button3Mode = (modeStateBuffer & BUTTON3_MASK) >> BUTTON3_SHIFT;
	//button4Mode = (modeStateBuffer & BUTTON4_MASK) >> BUTTON4_SHIFT;

	/* ... initialization of ui attributes */
	// call each menu to initialize, to make UI process the stored modes

}

// writes 2 16-bit values representing modeState to EEPROM per position,  1 runtime + 6 presets + calibration word
void ViaUI::storeToEEPROM(int32_t position) {
//	// store lower 16 bits
//	eepromStatus = EE_WriteVariable(VirtAddVarTab[position * 2],
//			(uint16_t) modeStateBuffer);
//	eepromStatus |= EE_WriteVariable(VirtAddVarTab[(position * 2) + 1],
//			(uint16_t) (modeStateBuffer >> 16)); // make sure i'm shifting in the right direction here!!
//
//	if (eepromStatus != HAL_OK) {
//		uiSetLEDs(1);
//		transition(&ViaUI::error);
//	}
}

//// calibration and default preset initialization
//void ViaUI::factoryReset(int32_t sig) {
//	switch (sig) {
//	case ENTRY_SIG:
//		UI_TIMER_RESET
//		;
//		UI_TIMER_SET_OVERFLOW(1000)
//		;
//		UI_TIMER_ENABLE
//		;
//		modeStateBuffer = DEFAULTPRESET1;
//		uiStoreToEEPROM(1);
//		modeStateBuffer = DEFAULTPRESET2;
//		uiStoreToEEPROM(2);
//		modeStateBuffer = DEFAULTPRESET3;
//		uiStoreToEEPROM(3);
//		modeStateBuffer = DEFAULTPRESET4;
//		uiStoreToEEPROM(4);
//		modeStateBuffer = DEFAULTPRESET5;
//		uiStoreToEEPROM(5);
//		modeStateBuffer = DEFAULTPRESET6;
//		uiStoreToEEPROM(6);
//		uiLoadFromEEPROM(1);
//		break;
//
//	case TIMEOUT_SIG:
//		if (eepromStatus != EE_OK) {
//			uiSetLEDs(4);
//			transition(&ViaUI::error);
//		} else {
//			transition(&ViaUI::default);
//		}
//	}
//}

