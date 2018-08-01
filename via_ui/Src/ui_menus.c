
// TODO this is a hole in the implementation along with setruntime display
#define AUX2_MODE_USED

#include "user_interface.h"


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
				(*button1TapCallback)();
			} else {
				(*button1HoldCallback)();
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
				(*button2TapCallback)();
			} else {
				(*button2HoldCallback)();
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
				(*button3TapCallback)();
			} else {
				(*button3HoldCallback)();
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
				(*button4TapCallback)();
			} else {
				(*button4HoldCallback)();
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

#ifdef AUX1_MODE_USED
		if (BUTTON1SENSOR == PRESSED) {
			uiTransition(&ui_aux1Menu);
		}
#endif
#ifdef AUX2_MODE_USED
		if (BUTTON3SENSOR == PRESSED) {
			uiTransition(&ui_aux2Menu);
		}
#endif
#ifdef AUX3_MODE_USED
		if (BUTTON4SENSOR == PRESSED) {
			uiTransition(&ui_aux3Menu);
		}
#endif
#ifdef AUX4_MODE_USED
		if (BUTTON6SENSOR == PRESSED) {
			uiTransition(&ui_aux4Menu);
		}
#endif

		if (BUTTON5SENSOR == RELEASED){
			if(UI_TIMER_READ < 3000){
				(*button5TapCallback)();
			} else {
				(*button5HoldCallback)();
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
				(*button6TapCallback)();
			} else {
				(*button6HoldCallback)();
			}
		}
		break;

	case INIT_SIG:
		break;
	}
}

void ui_aux1Menu(int sig)
{
	switch (sig) {

	case ENTRY_SIG:
		uiSetLEDs(aux1Mode);
		UI_TIMER_RESET;
		UI_TIMER_SET_OVERFLOW(65535);
		UI_TIMER_ENABLE;
		break;

	case SENSOR_EVENT_SIG:
		if (BUTTON1SENSOR == RELEASED){
			if(UI_TIMER_READ < 3000){
				(*aux1TapCallback)();
			} else {
				(*aux1HoldCallback)();
			}
		}
		break;

	case INIT_SIG:
		break;
	}
}

void ui_aux2Menu(int sig)
{
	switch (sig) {

	case ENTRY_SIG:
		uiSetLEDs(aux2Mode);
		UI_TIMER_RESET;
		UI_TIMER_SET_OVERFLOW(65535);
		UI_TIMER_ENABLE;
		break;

	case SENSOR_EVENT_SIG:
		if (BUTTON3SENSOR == RELEASED){
			if(UI_TIMER_READ < 3000){
				(*aux2TapCallback)();
			} else {
				(*aux2HoldCallback)();
			}
		}
		break;

	case INIT_SIG:
		break;
	}
}

void ui_aux3Menu(int sig)
{
	switch (sig) {

	case ENTRY_SIG:
		uiSetLEDs(aux3Mode);
		UI_TIMER_RESET;
		UI_TIMER_SET_OVERFLOW(65535);
		UI_TIMER_ENABLE;
		break;

	case SENSOR_EVENT_SIG:
		if (BUTTON4SENSOR == RELEASED){
			if(UI_TIMER_READ < 3000){
				(*aux3TapCallback)();
			} else {
				(*aux3HoldCallback)();
			}
		}
		break;

	case INIT_SIG:
		break;
	}
}

void ui_aux4Menu(int sig)
{
	switch (sig) {

	case ENTRY_SIG:
		uiSetLEDs(aux4Mode);
		UI_TIMER_RESET;
		UI_TIMER_SET_OVERFLOW(65535);
		UI_TIMER_ENABLE;
		break;

	case SENSOR_EVENT_SIG:
		if (BUTTON6SENSOR == RELEASED){
			if(UI_TIMER_READ < 3000){
				(*aux4TapCallback)();
			} else {
				(*aux4HoldCallback)();
			}
		}
		break;

	case INIT_SIG:
		break;
	}
}




