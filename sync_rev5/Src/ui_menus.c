#include "main.h"
#include "tsl_user.h"
#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"
#include "eeprom.h"
#include "modes.h"
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

void ui_button1Menu(int sig)
{
	switch (sig)
	{
	case ENTRY_SIG:
		uiSetLEDs(button1Mode);
		UI_TIMER_RESET;
		UI_TIMER_SET_OVERFLOW(65535);
		UI_TIMER_ENABLE;
		break;

	case SENSOR_EVENT_SIG:
		if (BUTTON1SENSOR == RELEASED){
			if(UI_TIMER_READ < 3000){
				handleButton1Tap();
			} else {
				handleButton1Hold();
			}
		}
		break;

	case INIT_SIG:
		SH_A_TRACK;
		SH_B_TRACK;
		break;
	}
}

void ui_button2Menu(int sig)
{
	switch (sig)
	{
	case ENTRY_SIG:

		UI_TIMER_RESET;
		UI_TIMER_SET_OVERFLOW(65535);
		UI_TIMER_ENABLE;
		uiSetLEDs(button2Mode);
		break;

	case SENSOR_EVENT_SIG:
		if (BUTTON2SENSOR == RELEASED){
			if(UI_TIMER_READ < 3000){
				handleButton2Tap();
			} else {
				handleButton2Hold();
			}
		}
		break;
	}
}

void ui_button3Menu(int sig) {
	switch (sig) {

	case ENTRY_SIG:
		uiSetLEDs(button3Mode);
		UI_TIMER_RESET;
		UI_TIMER_SET_OVERFLOW(65535);
		UI_TIMER_ENABLE;
		break;

	case SENSOR_EVENT_SIG:
		if(BUTTON3SENSOR == RELEASED){
			if(UI_TIMER_READ < 3000){
				handleButton3Tap();
			} else {
				handleButton3Hold();
			}
		}
		break;

	case INIT_SIG:
		break;
	}
}

void ui_button4Menu(int sig)
{
	switch (sig)
	{
	case ENTRY_SIG:
		uiSetLEDs(button4Mode);
		UI_TIMER_RESET;
		UI_TIMER_SET_OVERFLOW(65535);
		UI_TIMER_ENABLE;

		break;

	case SENSOR_EVENT_SIG:

		if (BUTTON4SENSOR == RELEASED){
			if(UI_TIMER_READ < 3000){
				handleButton4Tap();
			} else {
				handleButton4Hold();
			}
		}
		break;

	case INIT_SIG:
		break;

	default:
		break;
	}

}


void ui_button5Menu(int sig)
{
	switch (sig)
	{
	case ENTRY_SIG:
		UI_TIMER_RESET;
		UI_TIMER_SET_OVERFLOW(65535);
		UI_TIMER_ENABLE;
		uiSetLEDs(button5Mode);
		break;

	case SENSOR_EVENT_SIG:
		if (BUTTON5SENSOR == RELEASED){
			if(UI_TIMER_READ < 3000){
				handleButton5Tap();
			} else {
				handleButton5Hold();
			}
		}
		break;
	}
}


void ui_button6Menu(int sig)
{
	switch (sig) {

	case ENTRY_SIG:
		uiSetLEDs(button6Mode);
		UI_TIMER_RESET;
		UI_TIMER_SET_OVERFLOW(65535);
		UI_TIMER_ENABLE;
		break;

	case SENSOR_EVENT_SIG:
		if (BUTTON6SENSOR == RELEASED){
			if(UI_TIMER_READ < 3000){
				handleButton6Tap();
			} else {
				handleButton6Hold();
			}
		}
		break;

	case INIT_SIG:
		break;
	}
}




