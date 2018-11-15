/*
 * main.cpp
 *
 *  Created on: Sep 11, 2018
 *      Author: willmitchell
 */

#include "user_interface.hpp"


// Call the current state with a signal

void ViaUI::dispatch(int32_t sig) {
	(this->*state)(sig);
}

/**
 *
 * Transition to new UI state
 * Send the exit signal to the current state
 * Change the state pointer to the new state
 * Send the entry signal to the new state
 *
 */

void ViaUI::transition(void (ViaUI::*func)(int32_t)) {
	dispatch(EXIT_SIG);
	state = func;
	dispatch(ENTRY_SIG);
}

/**
 *
 * Default runtime state
 * Looks for detect or trigger button to launch menu
 * Runtime display is active in this state
 *
 */

void ViaUI::defaultMenu(int32_t sig) {
	switch (sig) {

	case ENTRY_SIG:
		defaultEnterMenuCallback();
		timerReset();
		timerDisable();
		break;

	case SENSOR_EVENT_SIG:

		if (*button3 == pressedState) {
			transition(&ViaUI::button3Menu);

		} else if (*button1 == pressedState) {
			transition(&ViaUI::button1Menu);

		} else if (*button4 == pressedState) {
			transition(&ViaUI::button4Menu);

		} else if (*button6 == pressedState) {
			transition(&ViaUI::button6Menu);

		} else if (*button2 == pressedState) {
			transition(&ViaUI::button2Menu);

		} else if (*button5 == pressedState) {
			transition(&ViaUI::button5Menu);
		}
		break;

	case EXPAND_SW_ON_SIG:
		transition(&ViaUI::presetMenu);
		break;

	case EXIT_SIG:

		break;

	default:
		break;
	}
}

/**
 *
 * Display new mode
 * Write to EEPROM on entry
 * Display new mode until timeout
 * Look for new user interaction
 *
 */

void ViaUI::newModeMenu(int32_t sig) {
	switch (sig) {
	case ENTRY_SIG:
		newModeEnterMenuCallback();
#ifdef BUILD_F373
		storeToEEPROM(0);
#endif
		timerReset();
		timerSetOverflow(5000);
		timerEnable();
		break;


		// once timerRead() times out, clear display and return to default state
	case TIMEOUT_SIG:
		transition(&ViaUI::defaultMenu);
		break;

	case EXPAND_SW_ON_SIG:
		transition(&ViaUI::presetMenu);
		break;

		// in case of new events immediately jump to relevant menu
	case SENSOR_EVENT_SIG:

		if (*button3== pressedState) {
			transition(&ViaUI::button3Menu);

		} else if (*button1 == pressedState) {
			transition(&ViaUI::button1Menu);

		} else if (*button4 == pressedState) {
			transition(&ViaUI::button4Menu);

		} else if (*button6 == pressedState) {
			transition(&ViaUI::button6Menu);

		} else if (*button2 == pressedState) {
			transition(&ViaUI::button2Menu);

		} else if (*button5 == pressedState) {
			transition(&ViaUI::button5Menu);
		}
		break;

		case EXIT_SIG:

		break;
	}

}

/**
 *
 * Transition to this state after AND A is tapped while AND B is pressed
 * Wait for a release of AND B or a new tap of AND A and show the current aux logic mode
 *
 */

void ViaUI::newAuxModeMenu(int32_t sig) {
	switch (sig) {
	case ENTRY_SIG:
		newAuxModeEnterMenuCallback();
		break;

	case SENSOR_EVENT_SIG:
		if (*button1 == pressedState) {
			transition(&ViaUI::aux1Menu);
		} else if (*button3 == pressedState) {
			transition(&ViaUI::aux2Menu);
		} else if (*button2 == pressedState) {
			transition(&ViaUI::aux2MenuAlt);
		} else if (*button4 == pressedState) {
			transition(&ViaUI::aux3Menu);
		} else if (*button6 == pressedState) {
			transition(&ViaUI::aux4Menu);
		} else if (*button5 == releasedState) {
			transition(&ViaUI::defaultMenu);
		}
		break;
	}
}


