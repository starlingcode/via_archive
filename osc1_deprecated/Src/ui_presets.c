#include "main.h"
#include "tsl_user.h"
#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"
#include "eeprom.h"
#include "user_interface.h"
#include "hardware_io.h"


// UI timer
TIM_HandleTypeDef htim4;

enum
{	NULL_SIG,     // Null signal, all state functions should ignore this signal and return their parent state or NONE if it's the top level state
	ENTRY_SIG,    // Entry signal, a state function should perform its entry actions (if any)
	EXIT_SIG,	  // Exit signal, a state function should pEntry signal, a state function should perform its entry actions (if any)erform its exit actions (if any)
	INIT_SIG,     // Just look to global value and initialize, return to default state.  For recalling (presets, memory)
	TIMEOUT_SIG,// timer timeout
	SENSOR_EVENT_SIG,  // Sensor state machine not busy, can be queried for events
	EXPAND_SW_ON_SIG,  // expander button depressed
	EXPAND_SW_OFF_SIG, // expander button released
	TSL_ERROR_SIG
};

enum {
	DAC_GATE_HIGH,
	DAC_GATE_LOW,
	DAC_EXECUTE,
};

/**
 *
 * Preset select menu
 *
 */

void ui_presetMenu(int sig)
{
	switch (sig){

	case ENTRY_SIG:
		SET_RUNTIME_DISPLAY;
		uiClearLEDs();
		uiClearRGB();
		UI_TIMER_RESET;
		UI_TIMER_DISABLE;
		break;

	case SENSOR_EVENT_SIG:

		if (BUTTON3SENSOR == PRESSED){
			uiTransition(&ui_presetPressedMenu);
			presetNumber = 3;
		} else if (BUTTON1SENSOR == PRESSED){
			uiTransition(&ui_presetPressedMenu);
			presetNumber = 1;
		} else if (BUTTON4SENSOR == PRESSED){
			uiTransition(&ui_presetPressedMenu);
			presetNumber = 4;
		} else if (BUTTON6SENSOR == PRESSED){
			uiTransition(&ui_presetPressedMenu);
			presetNumber = 6;
		} else if (BUTTON2SENSOR == PRESSED){
			uiTransition(&ui_presetPressedMenu);
			presetNumber = 2;
		} else if (BUTTON5SENSOR == PRESSED){
			uiTransition(&ui_presetPressedMenu);
			presetNumber = 5;
		}
		break;

	case EXPAND_SW_OFF_SIG:
		uiTransition(&ui_default);
		break;

	case EXIT_SIG:
		CLEAR_RUNTIME_DISPLAY;
		uiClearLEDs();
		uiClearRGB();
		break;

	default:
		break;
	}
}

/**
 *
 * Preset selected menu
 * Watches for release while a sensor is pressed from the preset menu.
 * Loads or stores preset according to the length of the press.
 *
 */

void ui_presetPressedMenu(int sig){
	switch (sig){
	case ENTRY_SIG:
		UI_TIMER_RESET;
		UI_TIMER_SET_OVERFLOW(10000);
		UI_TIMER_ENABLE;
		break;

	case SENSOR_EVENT_SIG:
		switch(presetNumber){
		case 1:
			if (BUTTON1SENSOR == RELEASED){
				uiLoadFromEEPROM(presetNumber);
				uiTransition(&ui_switchPreset);
			}
			break;
		case 2:
			if (BUTTON4SENSOR == RELEASED){
				uiLoadFromEEPROM(presetNumber);
				uiTransition(&ui_switchPreset);
			}
			break;
		case 3:
			if (BUTTON2SENSOR == RELEASED){
				uiLoadFromEEPROM(presetNumber);
				uiTransition(&ui_switchPreset);
			}
			break;
		case 4:
			if (BUTTON5SENSOR == RELEASED){
				uiLoadFromEEPROM(presetNumber);
				uiTransition(&ui_switchPreset);
			}
			break;
		case 5:
			if (BUTTON3SENSOR == RELEASED){
				uiLoadFromEEPROM(presetNumber);
				uiTransition(&ui_switchPreset);
			}
			break;
		case 6:
			if (BUTTON6SENSOR == RELEASED){
				uiLoadFromEEPROM(presetNumber);
				uiTransition(&ui_switchPreset);
			}
			break;
		}
		break;

	case TIMEOUT_SIG:
		uiStoreToEEPROM(presetNumber);
		uiTransition(&ui_newPreset);
		break;


	// if trig button is released, exit menu
	case EXPAND_SW_OFF_SIG:
		uiTransition(&ui_default);
		break;

	case EXIT_SIG:
		break;
	}
}

/**
 *
 * Preset storage indicator state
 * Flashes around the white leds 4 times
 *
 */

void ui_newPreset(int sig){
	static int flashCounter = 0;
	switch (sig){
	case ENTRY_SIG:
		UI_TIMER_RESET;
		UI_TIMER_SET_OVERFLOW(500);
		UI_TIMER_ENABLE;
		break;

	case TIMEOUT_SIG:
		if (flashCounter < 16){
			UI_TIMER_ENABLE;
			flashCounter++;
			uiSetLEDs(flashCounter % 4);
		} else {
			flashCounter = 0;
			uiTransition(&ui_default);
		}
	}
}

/**
 *
 * Switch to preset indicator state
 * Flashes around the white leds once
 *
 */

void ui_switchPreset(int sig){
	static int flashCounter = 0;
	switch (sig){
	case ENTRY_SIG:
		UI_TIMER_RESET;
		UI_TIMER_SET_OVERFLOW(500);
		UI_TIMER_ENABLE;
		break;

	case TIMEOUT_SIG:
		if (flashCounter < 4){
			UI_TIMER_ENABLE;
			flashCounter++;
			uiSetLEDs(flashCounter % 4);
		} else {
			flashCounter = 0;
			uiTransition(&ui_presetMenu);
		}
	}
}
