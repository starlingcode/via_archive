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
				switch (shAMode) {
					case aSHOff:
						CLEAR_SAMPLE_A;
						CLEAR_TRACK_A;
						SH_A_TRACK;
						break;
					case aResample:
						SET_SAMPLE_A;
						CLEAR_TRACK_A;
						break;
					case aSampleTrack:
						SET_SAMPLE_A;
						SET_TRACK_A;
						break;
					default:
						break;
				}
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
				modeStateBuffer = (modeStateBuffer & ~(SH_B_MASK)) | (andAMode << SH_B_SHIFT);
				switch (shBMode) {
					case bSHOff:
						CLEAR_SAMPLE_B;
						CLEAR_TRACK_B;
						SH_B_TRACK;
						break;
					case bResample:
						SET_SAMPLE_B;
						CLEAR_TRACK_B;
						break;
					case bSampleTrack:
						SET_SAMPLE_B;
						SET_TRACK_B;
						break;
					default:
						break;
				}
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
		uiSetLEDs(patternBankIndex);
		break;

	case SENSOR_EVENT_SIG:
		if (BUTTON2SENSOR == RELEASED){
			if(UI_TIMER_READ < 3000){
				patternBankIndex = (patternBankIndex + 1) % 8;
				modeStateBuffer = (modeStateBuffer & ~(BANK_MASK)) | (patternBankIndex << BANK_SHIFT);
				currentBank = patternBanks[patternBankIndex];
				uiSetLEDs(patternBankIndex);
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
		uiSetLEDs(patternBankIndex);
		break;

	case SENSOR_EVENT_SIG:
		if (BUTTON5SENSOR == RELEASED){
			if(UI_TIMER_READ < 3000){
				if (patternBankIndex == 0) {
					patternBankIndex = 7;  // wrap around
				} else {
					patternBankIndex--;
				}
				modeStateBuffer = (modeStateBuffer & ~(BANK_MASK)) | (patternBankIndex << BANK_SHIFT);
				currentBank = patternBanks[patternBankIndex];
				uiSetLEDs(patternBankIndex);
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
		uiSetLEDs(andAMode);
		UI_TIMER_RESET;
		UI_TIMER_SET_OVERFLOW(65535);
		UI_TIMER_ENABLE;
		break;

	case SENSOR_EVENT_SIG:
		if(BUTTON3SENSOR == RELEASED){
			if (UI_TIMER_READ < 3000) {
				andAMode = (andAMode + 1) % 2;
				modeStateBuffer = AND_A_MASK | (andAMode << AND_A_MASK);
				if (andAMode != 0) {
					SET_AND_A;
				} else {
					CLEAR_AND_A;
					manageADac(DAC_GATE_HIGH);
				}
				uiSetLEDs(andAMode);
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
		uiSetLEDs(andBMode);
		break;

	case SENSOR_EVENT_SIG:
		if (BUTTON6SENSOR == RELEASED){

			if(UI_TIMER_READ < 3000){
				andBMode = (andBMode + 1) % 2;
				modeStateBuffer = (modeStateBuffer & ~(AND_B_MASK)) | (andBMode << AND_B_SHIFT);
				if (andBMode != 0) {
					SET_AND_B;
				} else {
					CLEAR_AND_B;
					manageBDac(DAC_GATE_HIGH);
				}
				uiClearLEDs();
				uiSetLEDs(andBMode);
				uiTransition( &ui_newMode);
			} else {
				uiTransition(&ui_default);
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
		uiSetLEDs(auxLogicMode);
		break;

	case SENSOR_EVENT_SIG:
		if (BUTTON3SENSOR == RELEASED){

			if(UI_TIMER_READ < 3000){
				auxLogicMode = (auxLogicMode + 1) % 4;
				modeStateBuffer = (modeStateBuffer & ~(AND_B_MASK)) | (auxLogicMode << AUX_LOGIC_SHIFT);
				uiClearLEDs();
				uiSetLEDs(auxLogicMode);
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



