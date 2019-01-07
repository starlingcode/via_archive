/*
 * user_interface.hpp
 *
 *  Created on: Sep 11, 2018
 *      Author: willmitchell
 */

// comment so I can push the case change of the src folder

#ifndef INC_USER_INTERFACE_HPP_
#define INC_USER_INTERFACE_HPP_

#include <via_platform_binding.hpp>


#ifdef __cplusplus
extern "C" {
#endif

#ifdef BUILD_F373
#include "tsl_user.h"
#include "eeprom.h"
#endif

void linkUI(void *, void *);

#ifdef __cplusplus
}
#endif

class ViaVirtualButtons {
public:
	int32_t button1 = 0;
	int32_t button2 = 0;
	int32_t button3 = 0;
	int32_t button4 = 0;
	int32_t button5 = 0;
	int32_t button6 = 0;
};

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

class ViaUI {

public:

	// UI States
	void (ViaUI::*state)(int32_t);

	int32_t virtualTimer = 0;
	int32_t virtualTimerEnable = 0;
	int32_t virtualTimerOverflow = 0;

	int32_t * button1;
	int32_t * button2;
	int32_t * button3;
	int32_t * button4;
	int32_t * button5;
	int32_t * button6;

#ifdef BUILD_F373
	int32_t pressedState = PRESSED;
	int32_t releasedState = RELEASED;
#endif

#ifdef BUILD_VIRTUAL
	int32_t pressedState = 1;
	int32_t releasedState = 0;

	int32_t trigButton;

	#define EXPANDER_BUTTON_PRESSED trigButton

#endif

	virtual void transition(void (ViaUI::*func)(int32_t));

	// Main
	void defaultMenu(int32_t sig);
	void newModeMenu(int32_t sig);
	void newAuxModeMenu(int32_t sig);

	// Button menus
	void button4Menu(int32_t sig);
	void button1Menu(int32_t sig);
	void button2Menu(int32_t sig);
	void button5Menu(int32_t sig);
	void button3Menu(int32_t sig);
	void button6Menu(int32_t sig);
	void aux1Menu(int32_t sig);
	void aux2Menu(int32_t sig);
	void aux2MenuAlt(int32_t sig);
	void aux3Menu(int32_t sig);
	void aux4Menu(int32_t sig);

	// Preset menus
	void presetMenu(int32_t sig);
	void presetPressedMenu(int32_t sig);
	void newPreset(int32_t sig);
	void switchPreset(int32_t sig);
	void overwritePresets(int32_t sig);

	// Factory reset
	void factoryReset(int32_t sig);

	virtual void button1TapCallback(void) = 0;
	virtual void button1HoldCallback(void) = 0;
	virtual void button2TapCallback(void) = 0;
	virtual void button2HoldCallback(void) = 0;
	virtual void button3TapCallback(void) = 0;
	virtual void button3HoldCallback(void) = 0;
	virtual void button4TapCallback(void) = 0;
	virtual void button4HoldCallback(void) = 0;
	virtual void button5TapCallback(void) = 0;
	virtual void button5HoldCallback(void) = 0;
	virtual void button6TapCallback(void) = 0;
	virtual void button6HoldCallback(void) = 0;

	virtual void aux1TapCallback(void) = 0;
	virtual void aux1HoldCallback(void) = 0;
	virtual void aux2TapCallback(void) = 0;
	virtual void aux2HoldCallback(void) = 0;
	virtual void aux2AltTapCallback(void) = 0;
	virtual void aux2AltHoldCallback(void) = 0;
	virtual void aux3TapCallback(void) = 0;
	virtual void aux3HoldCallback(void) = 0;
	virtual void aux4TapCallback(void) = 0;
	virtual void aux4HoldCallback(void) = 0;

	virtual void defaultEnterMenuCallback(void) = 0;
	virtual void newModeEnterMenuCallback(void) = 0;
	virtual void newAuxModeEnterMenuCallback(void) = 0;
	virtual void presetEnterMenuCallback(void) = 0;

	virtual void button1EnterMenuCallback(void) = 0;
	virtual void button2EnterMenuCallback(void) = 0;
	virtual void button3EnterMenuCallback(void) = 0;
	virtual void button4EnterMenuCallback(void) = 0;
	virtual void button5EnterMenuCallback(void) = 0;
	virtual void button6EnterMenuCallback(void) = 0;

	virtual void aux1EnterMenuCallback(void) = 0;
	virtual void aux2EnterMenuCallback(void) = 0;
	virtual void aux2AltEnterMenuCallback(void) = 0;
	virtual void aux3EnterMenuCallback(void) = 0;
	virtual void aux4EnterMenuCallback(void) = 0;

	virtual void uiSetLEDs(int) = 0;

	virtual void recallModuleState(void) = 0;

	virtual void writeStockPresets(void) = 0;

	// initial setup of UI
	virtual void initialize(void) = 0;

	virtual ~ViaUI(void) {};

#ifdef BUILD_F373

	inline void timerReset(void) {
		TIM7->CNT = 1;
	}
	inline void timerEnable(void) {
		TIM7->CR1 |= TIM_CR1_CEN;
	}
	inline void timerDisable(void) {
		TIM7->CR1 &= ~TIM_CR1_CEN;
	}
	inline void timerSetOverflow(int32_t arr) {
		TIM7->ARR = arr;
	}
	inline int32_t timerRead(void) {
		return TIM7->CNT;
	}

	int32_t eepromStatus;

	uint16_t VirtAddVarTab[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};

	void initializeMemory(void) {
		eepromStatus = EE_Init();
	}

	void loadStateFromMemory(int32_t position) {

		uint16_t eepromTemp;

		eepromStatus = EE_ReadVariable(VirtAddVarTab[position * 2], &eepromTemp);
		modeStateBuffer = (int32_t) eepromTemp;  // load bottom 16 bits
		eepromStatus |= EE_ReadVariable(VirtAddVarTab[(position * 2) + 1],
				&eepromTemp);
		modeStateBuffer |= ((int32_t) eepromTemp) << 16;  // load 16 upper bits

	}

	uint32_t loadFromMemory(int32_t position) {

		uint16_t eepromTemp;
		uint32_t data;

		eepromStatus = EE_ReadVariable(VirtAddVarTab[position * 2], &eepromTemp);
		data = (int32_t) eepromTemp;  // load bottom 16 bits
		eepromStatus |= EE_ReadVariable(VirtAddVarTab[(position * 2) + 1],
				&eepromTemp);
		data |= ((int32_t) eepromTemp) << 16;  // load 16 upper bits
		return data;

	}

#endif

#ifdef BUILD_VIRTUAL

	void loadStateFromMemory(int32_t position) {
		;
	}

	void timerReset(void) {
		virtualTimer = 0;
	}
	void timerEnable(void) {
		virtualTimerEnable = 1;
	}
	void timerDisable(void) {
		virtualTimerEnable = 0;
	}
	void timerSetOverflow(int32_t arr) {
		virtualTimerOverflow = arr;
	}
	int32_t timerRead(void) {
		return virtualTimer;
	}

	void incrementTimer(void) {
		virtualTimer += virtualTimerEnable;
		if (virtualTimer >= virtualTimerOverflow) {
            virtualTimer = 0;
            dispatch(TIMEOUT_SIG);
        }
	}

#endif

	void resetTimerMenu(void) {
		timerReset();
		timerSetOverflow(65535);
		timerEnable();
	}

	// holds the mode state as a EEPROM-formatted value.
	int32_t modeStateBuffer = 0;
	int32_t presetNumber = 0;

	void loadFromEEPROM(int32_t);
	void storeStateToEEPROM(int32_t);
	void storeToEEPROM(int32_t, uint32_t);

	int32_t incrementModeAndStore(int32_t, int32_t, int32_t, int32_t);
	int32_t decrementModeAndStore(int32_t, int32_t, int32_t, int32_t);

	int32_t button1Mode = 0;
	int32_t button2Mode = 0;
	int32_t button3Mode = 0;
	int32_t button4Mode = 0;
	int32_t button5Mode = 0;
	int32_t button6Mode = 0;
	int32_t aux1Mode = 0;
	int32_t aux2Mode = 0;
	int32_t aux3Mode = 0;
	int32_t aux4Mode = 0;

	// dispatch a signal to current state
	void dispatch(int32_t);  // dispatch signal to state

};

// how modes are arranged by size and location in modeStateBuffer (formatted for EEPROM storage).
#define BUTTON1_MASK 		0b00000000000000000000000000000111
#define BUTTON1_SHIFT		0

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

#define ENCODE_PRESET(B1, B2, B3, B4, B5, B6, A1, A2, A3, A4) \
	(B1 | (B2 << BUTTON2_SHIFT) | (B3 << BUTTON3_SHIFT) | (B4 << BUTTON4_SHIFT) | \
		(B5 << BUTTON5_SHIFT) | (B6 << BUTTON6_SHIFT) | (A1 << AUX_MODE1_SHIFT) | \
			(A2 << AUX_MODE2_SHIFT) | (A3 << AUX_MODE3_SHIFT) | (A4 << AUX_MODE4_SHIFT))



#endif /* INC_USER_INTERFACE_HPP_ */
