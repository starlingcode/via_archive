/*
 * user_interface.hpp
 *
 *  Created on: Sep 11, 2018
 *      Author: willmitchell
 */

#ifndef INC_USER_INTERFACE_HPP_
#define INC_USER_INTERFACE_HPP_

#include "via_platform_binding.h"
#include "tsl_user.h"
#include "eeprom.h"

enum uiSignals {
	NULL_SIG, // Null signal, all state functions should ignore this signal and return their parent state or NONE if it's the top level state
	ENTRY_SIG, // Entry signal, a state function should perform its entry actions (if any)
	EXIT_SIG,// Exit signal, a state function should pEntry signal, a state function should perform its entry actions (if any)erform its exit actions (if any)
	INIT_SIG, // Just look to global value and initialize, return to default state.  For recalling (presets, memory)
	TIMEOUT_SIG, // timer timeout
	SENSOR_EVENT_SIG, // Sensor state machine not busy, can be queried for events
	EXPAND_SW_ON_SIG,  // expander button depressed
	EXPAND_SW_OFF_SIG, // expander button released
	TSL_ERROR_SIG
};

enum uiSignals uiSignalCopy;

class ViaUI {
public:
	// holds the mode state as a EEPROM-formatted value.
	int modeStateBuffer;

	// TODO HALF ASSED
	int runtimeDisplay;

	int presetNumber;

	// initial setup of UI
	void initialize(void);
	void loadFromEEPROM(int);
	void storeToEEPROM(int);

	// UI States
	void (ViaUI::*state)(int);

	// dispatch a signal to current state
	void dispatch(int);  // dispatch signal to state
	void transition(void (ViaUI::*func)(int));

	// Main
	void defaultMenu(int sig);
	void newModeMenu(int sig);
	void newAuxModeMenu(int sig);

	// Button menus
	void button4Menu(int sig);
	void button1Menu(int sig);
	void button2Menu(int sig);
	void button5Menu(int sig);
	void button3Menu(int sig);
	void button6Menu(int sig);
	void aux1Menu(int sig);
	void aux2Menu(int sig);
	void aux3Menu(int sig);
	void aux4Menu(int sig);

	// Preset menus
	void presetMenu(int sig);
	void presetPressedMenu(int sig);
	void newPreset(int sig);
	void switchPreset(int sig);

	// Factory reset
	void factoryReset(int sig);

	virtual void button1TapCallback(void);
	virtual void button1HoldCallback(void);
	virtual void button2TapCallback(void);
	virtual void button2HoldCallback(void);
	virtual void button3TapCallback(void);
	virtual void button3HoldCallback(void);
	virtual void button4TapCallback(void);
	virtual void button4HoldCallback(void);
	virtual void button5TapCallback(void);
	virtual void button5HoldCallback(void);
	virtual void button6TapCallback(void);
	virtual void button6HoldCallback(void);

	virtual void aux1TapCallback(void);
	virtual void aux1HoldCallback(void);
	virtual void aux2TapCallback(void);
	virtual void aux2HoldCallback(void);
	virtual void aux3TapCallback(void);
	virtual void aux3HoldCallback(void);
	virtual void aux4TapCallback(void);
	virtual void aux4HoldCallback(void);

	virtual void defaultEnterMenuCallback(void);
	virtual void newModeEnterMenuCallback(void);
	virtual void newAuxModeEnterMenuCallback(void);
	virtual void presetEnterMenuCallback(void);

	virtual void button1EnterMenuCallback(void);
	virtual void button2EnterMenuCallback(void);
	virtual void button3EnterMenuCallback(void);
	virtual void button4EnterMenuCallback(void);
	virtual void button5EnterMenuCallback(void);
	virtual void button6EnterMenuCallback(void);

	virtual void aux1EnterMenuCallback(void);
	virtual void aux2EnterMenuCallback(void);
	virtual void aux3EnterMenuCallback(void);
	virtual void aux4EnterMenuCallback(void);

	void (*timerReset)(void);
	void (*timerEnable)(void);
	void (*timerDisable)(void);
	void (*timerSetOverflow)(int);
	int (*timerRead)(void);

	void initializeUICallbacks(void);

	int incrementModeAndStore(int, int, int);
	int decrementModeAndStore(int, int, int);

};

// how modes are arranged by size and location in modeStateBuffer (formatted for EEPROM storage).
#define BUTTON1_MASK 		0b00000000000000000000000000000111

#define BUTTON2_MASK 		0b00000000000000000000000000111000
#define BUTTON2_SHIFT		3

#define BUTTON3_MASK 		0b00000000000000000000000111000000
#define BUTTON3_SHIFT 		6

#define BUTTON4_MASK 		0b00000000000000000000111000000000
#define BUTTON4_SHIFT 		9

#define BUTTON5_MASK	 	0b00000000000000000111000000000000
#define BUTTON5_SHIFT	 	12

#define BUTTON6_MASK		0b00000000000000111000000000000000
#define BUTTON6_SHIFT		15

#define AUX_MODE1_MASK		0b00000000000111000000000000000000
#define AUX_MODE1_SHIFT		18

#define AUX_MODE2_MASK		0b00000000111000000000000000000000
#define AUX_MODE2_SHIFT		21

#define AUX_MODE3_MASK		0b00000111000000000000000000000000
#define AUX_MODE3_SHIFT		24

#define AUX_MODE4_MASK		0b00111000000000000000000000000000
#define AUX_MODE4_SHIFT		27

#define DEFAULTPRESET1 0b0000000000000000
#define DEFAULTPRESET2 0b0000000000000000
#define DEFAULTPRESET3 0b0000000000000000
#define DEFAULTPRESET4 0b0000000000000000
#define DEFAULTPRESET5 0b0000000000000000
#define DEFAULTPRESET6 0b0000000000000000



#endif /* INC_USER_INTERFACE_HPP_ */
