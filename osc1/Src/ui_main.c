#include "main.h"
#include "tsl_user.h"
#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"
#include "eeprom.h"
#include "user_interface.h"
#include "hardware_io.h"
#include "patterns.h"

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

// Call the current state with a signal


void uiDispatch(int sig) {(*ui_State)(sig);}

/**
 *
 * Transition to new UI state
 * Send the exit signal to the current state
 * Change the state pointer to the new state
 * Send the entry signal to the new state
 *
 */

void uiTransition(void (*func)(int)) {
	uiDispatch(EXIT_SIG);
	ui_State = func;
	uiDispatch(ENTRY_SIG);
}

/**
 *
 * Default runtime state
 * Looks for detect or trigger button to launch menu
 * Runtime display is active in this state
 *
 */

void ui_default(int sig)
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
			uiTransition(&ui_button3Menu);

		} else if (BUTTON1SENSOR == PRESSED){
			uiTransition(&ui_button1Menu);

		} else if (BUTTON4SENSOR == PRESSED){
			uiTransition(&ui_button4Menu);

		} else if (BUTTON6SENSOR == PRESSED){
			uiTransition(&ui_button6Menu);

		} else if (BUTTON2SENSOR == PRESSED){
			uiTransition(&ui_button2Menu);

		} else if (BUTTON5SENSOR == PRESSED){
			uiTransition(&ui_button5Menu);
		}
		break;

	case EXPAND_SW_ON_SIG:
		uiTransition(&ui_presetMenu);
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
 * Display new mode
 * Write to EEPROM on entry
 * Display new mode until timeout
 * Look for new user interaction
 *
 */

void ui_newMode(int sig)
{
	switch (sig)
	{
	case ENTRY_SIG:
		CLEAR_RUNTIME_DISPLAY;
		uiStoreToEEPROM(0);
		UI_TIMER_RESET;
		UI_TIMER_SET_OVERFLOW(5000);
		UI_TIMER_ENABLE;
		break;

	// once uiTimerRead() times out, clear display and return to default state
	case TIMEOUT_SIG:
		uiTransition(&ui_default);
		break;

	case EXPAND_SW_ON_SIG:
		uiTransition(&ui_presetMenu);
		break;

	// in case of new events immediately jump to relevant menu
	case SENSOR_EVENT_SIG:

		if (BUTTON3SENSOR == PRESSED){
			uiTransition( &ui_button3Menu);

		} else if (BUTTON1SENSOR == PRESSED){
			uiTransition( &ui_button1Menu);

		} else if (BUTTON4SENSOR == PRESSED){
			uiTransition( &ui_button4Menu);

		} else if (BUTTON6SENSOR == PRESSED){
			uiTransition( &ui_button6Menu);

		} else if (BUTTON2SENSOR == PRESSED){
			uiTransition( &ui_button2Menu);

		} else if (BUTTON5SENSOR == PRESSED){
			uiTransition( &ui_button5Menu);
		}
		break;

	case EXIT_SIG:
		uiClearLEDs();
		uiClearRGB();
		break;
	}

}

/**
 *
 * Transition to this state after AND A is tapped while AND B is pressed
 * Wait for a release of AND B or a new tap of AND A and show the current aux logic mode
 *
 */

void ui_button6SubMenu(int sig)
{
	switch (sig)
	{
	case ENTRY_SIG:
		UI_TIMER_RESET;// start count over
		uiStoreToEEPROM(0);  // store in preset 0 (current state)
		break;

	case SENSOR_EVENT_SIG:
		// in case either logic mode sensors are pressed, jump to their menu
		if (BUTTON3SENSOR == PRESSED){
			uiTransition(&ui_button6_3Menu);
		} else if (BUTTON6SENSOR == RELEASED){
			uiTransition(&ui_default);
		}
		break;
	}
}

/**
 *
 * UI error state
 * catches error states and gives display feedback
 *
 */

void ui_error(int sig){

	// not yet implemented

}







