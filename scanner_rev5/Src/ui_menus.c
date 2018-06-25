#include "main.h"
#include "tsl_user.h"
#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"
#include "eeprom.h"
#include "user_interface.h"
#include "via_rev5_hardware_io.h"

// UI timer
TIM_HandleTypeDef htim7;

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
		//uiSetLEDs(shMode);
		break;

	case SENSOR_EVENT_SIG:
		if (BUTTON1SENSOR == RELEASED){

				shMode = (shMode + 1) % 2;
				modeStateBuffer = (modeStateBuffer & ~(SH_MASK)) | shMode;
				handleSHModeChange(shMode);
				uiClearLEDs();
				//uiSetLEDs(shMode);
				uiTransition(&ui_default);

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
		//uiSetLEDs(syncMode);

		break;

	case SENSOR_EVENT_SIG:

		if (BUTTON4SENSOR == RELEASED){

				syncMode = (syncMode + 1) % 2;
				// initialize some essential retrigger variables
				modeStateBuffer = (modeStateBuffer & ~(SYNC_MASK)) | (syncMode << SYNC_SHIFT);
				handleSyncModeChange(syncMode);
				uiClearLEDs();
				//uiSetLEDs(syncMode);
				uiTransition(&ui_default);

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
				modeStateBuffer = (modeStateBuffer & ~(TABLE_MASK)) | (familyIndicator << TABLE_SHIFT);
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
				modeStateBuffer = (modeStateBuffer & ~(TABLE_MASK)) | (familyIndicator << TABLE_SHIFT);
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
		//uiSetLEDs(xMode);
		UI_TIMER_RESET;
		UI_TIMER_SET_OVERFLOW(65535);
		UI_TIMER_ENABLE;
		break;

	case SENSOR_EVENT_SIG:
		if(BUTTON3SENSOR == RELEASED){
			if (UI_TIMER_READ < 3000) {
				xMode = (xMode + 1) % 2;
				modeStateBuffer = XCV_MASK | (xMode << XCV_MASK);
				handleXModeChange(xMode);
				uiClearLEDs();
				//uiSetLEDs(xMode);
				uiTransition(&ui_default);
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
		//uiSetLEDs(morphMode);
		break;

	case SENSOR_EVENT_SIG:
		if (BUTTON6SENSOR == RELEASED){

			if(UI_TIMER_READ < 3000){
				morphMode = (morphMode + 1) % 2;
				modeStateBuffer = (modeStateBuffer & ~(MORPH_MASK)) | (syncMode << MORPH_SHIFT);
				handleMorphModeChange(morphMode);
				uiClearLEDs();
				//uiSetLEDs(morphMode);
				uiTransition(&ui_default);
			} else {
				uiTransition(&ui_default);
			}
		}
		break;

	case INIT_SIG:
		break;
	}
}




