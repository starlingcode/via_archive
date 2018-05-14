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

/**
 *
 * S&H A menu
 *
 */

void ui_button1Menu(int sig)
{
	switch (sig)
	{
	case ENTRY_SIG:
		UI_TIMER_RESET;
		UI_TIMER_SET_OVERFLOW(65535);
		UI_TIMER_ENABLE;
		uiSetLEDs(shAMode);
		break;

	case SENSOR_EVENT_SIG:
		if (BUTTON1SENSOR == RELEASED){
			if(UI_TIMER_READ < 3000){
				shAMode = (shAMode + 1) % 3;
				modeStateBuffer = (modeStateBuffer & ~(SH_A_MASK)) | shAMode;
				handleSHAModeChange(shAMode);
				uiClearLEDs();
				uiSetLEDs(shAMode);
				uiTransition(&ui_newMode);
			} else {
				uiTransition(&ui_default);
			}
		}
		break;

	case INIT_SIG:
		SH_A_TRACK;
		SH_B_TRACK;
		break;
	}
}

/**
 *
 * S&H B menu
 *
 */

void ui_button4Menu(int sig)
{
	switch (sig)
	{
	case ENTRY_SIG:
		UI_TIMER_RESET;
		UI_TIMER_SET_OVERFLOW(65535);
		UI_TIMER_ENABLE;
		uiSetLEDs(shBMode);

		break;

	case SENSOR_EVENT_SIG:

		if (BUTTON4SENSOR == RELEASED){
			if(UI_TIMER_READ < 3000){
				shBMode = (shBMode + 1) % 3;
				// initialize some essential retrigger variables
				modeStateBuffer = (modeStateBuffer & ~(SH_B_MASK)) | (shBMode << SH_B_SHIFT);
				handleSHBModeChange(shBMode);
				uiClearLEDs();
				uiSetLEDs(shBMode);
				uiTransition(&ui_newMode);
			} else {
				//no mode change
				uiTransition(&ui_default);
			}

		}
		break;

	case INIT_SIG:
		break;

	default:
		break;
	}

}

/**
 *
 * Grid select up menu
 *
 */


void ui_button2Menu(int sig)
{
	switch (sig)
	{
	case ENTRY_SIG:

		UI_TIMER_RESET;
		UI_TIMER_SET_OVERFLOW(65535);
		UI_TIMER_ENABLE;
		uiSetLEDs(familyIndicator);
		break;

	case SENSOR_EVENT_SIG:
		if (BUTTON2SENSOR == RELEASED){
			if(UI_TIMER_READ < 3000){
				familyIndicator = (familyIndicator + 1) % 8;
				modeStateBuffer = (modeStateBuffer & ~(BANK_MASK)) | (familyIndicator << BANK_SHIFT);
				switchFamily();
				uiClearLEDs();
				uiSetLEDs(familyIndicator);
				uiTransition( &ui_newMode);
			} else {
				uiTransition( &ui_default);
			}
		}
		break;
	}
}

/**
 *
 * Grid select down menu
 *
 */

void ui_button5Menu(int sig)
{
	switch (sig)
	{
	case ENTRY_SIG:
		UI_TIMER_RESET;
		UI_TIMER_SET_OVERFLOW(65535);
		UI_TIMER_ENABLE;
		uiSetLEDs(familyIndicator);
		break;

	case SENSOR_EVENT_SIG:
		if (BUTTON5SENSOR == RELEASED){
			if(UI_TIMER_READ < 3000){
				if (familyIndicator == 0) {
					familyIndicator = 7;  // wrap around
				} else {
					familyIndicator--;
				}
				modeStateBuffer = (modeStateBuffer & ~(BANK_MASK)) | (familyIndicator << BANK_SHIFT);
				switchFamily();
				uiClearLEDs();
				uiSetLEDs(familyIndicator);
				uiTransition( &ui_newMode);
			} else {
				uiTransition(&ui_default);
			}
		}
		break;
	}
}

/**
 *
 * And A menu
 *
 */

void ui_button3Menu(int sig) {
	switch (sig) {

	case ENTRY_SIG:
		uiSetLEDs(xMode);
		UI_TIMER_RESET;
		UI_TIMER_SET_OVERFLOW(65535);
		UI_TIMER_ENABLE;
		break;

	case SENSOR_EVENT_SIG:
		if(BUTTON3SENSOR == RELEASED){
			if (UI_TIMER_READ < 3000) {
				xMode = (xMode + 1) % 2;
				modeStateBuffer = AND_A_MASK | (xMode << AND_A_MASK);
				handleXModeChange(xMode);
				uiClearLEDs();
				uiSetLEDs(xMode);
				uiTransition(&ui_newMode);
			} else {
				uiTransition(&ui_default);
			}
		}
		break;

	case INIT_SIG:
		break;
	}
}

/**
 *
 * And B menu
 *
 */

void ui_button6Menu(int sig)
{
	switch (sig) {

	case ENTRY_SIG:
		UI_TIMER_RESET;
		UI_TIMER_SET_OVERFLOW(65535);
		UI_TIMER_ENABLE;
		uiSetLEDs(syncMode);
		break;

	case SENSOR_EVENT_SIG:
		if (BUTTON6SENSOR == RELEASED){

			if(UI_TIMER_READ < 3000){
				syncMode = (syncMode + 1) % 3;
				modeStateBuffer = (modeStateBuffer & ~(AND_B_MASK)) | (syncMode << AND_B_SHIFT);
				//handleSyncModeChange(syncMode)
				uiClearLEDs();
				uiSetLEDs(syncMode);
				uiTransition( &ui_newMode);
			} else {
				uiTransition(&syncMode);
			}
		} else if (BUTTON3SENSOR == PRESSED) {
			uiTransition(&ui_button6_3Menu);
		}

		if ((BUTTON4SENSOR == PRESSED) && (BUTTON1SENSOR == PRESSED) && (BUTTON3SENSOR == PRESSED)){
			uiTransition(&ui_factoryReset);
		}
		break;

	case INIT_SIG:
		break;
	}
}

/**
 *
 * Aux logic out menu
 *
 */

void ui_button6_3Menu(int sig)
{
	switch (sig) {

	case ENTRY_SIG:
		UI_TIMER_RESET;
		UI_TIMER_SET_OVERFLOW(65535);
		UI_TIMER_ENABLE;
		uiSetLEDs(auxSyncMode);
		break;

	case SENSOR_EVENT_SIG:
		if (BUTTON3SENSOR == RELEASED){

			if(UI_TIMER_READ < 3000){
				auxSyncMode = (auxSyncMode + 1) % 3;
				modeStateBuffer = (modeStateBuffer & ~(AUX_LOGIC_MASK)) | (auxSyncMode << AUX_LOGIC_SHIFT);
				uiClearLEDs();
				uiSetLEDs(auxSyncMode);
				uiTransition( &ui_button6SubMenu);
			} else {
				uiTransition(&ui_default);
			}
		}

		break;

	case INIT_SIG:
		break;
	}
}



