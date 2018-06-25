#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"
#include "main_state_machine.h"
#include "tsl_user.h"
#include "main.h"
#include "user_interface.h"
#include "via_rev5_hardware_io.h"

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

tsl_user_status_t tsl_status;

// wrapper for implementing the UI
void implementUI(void) {

	static uint32_t debounce;

//check if the trigger button has been pressed
		if (EXPANDER_BUTTON_PRESSED){

			//if we havent raised the trigger button flag, do so and set a pending interrupt
			if (!(TRIGGER_BUTTON)) {
				debounce++;

				if (debounce == 10) {
					SET_TRIGGER_BUTTON;
					uiDispatch(EXPAND_SW_ON_SIG);
					//trigger an interrupt
					HAL_NVIC_SetPendingIRQ(EXTI15_10_IRQn);
					debounce = 0;
				}

			}
		}
		//if the trigger button has been released but the trigger button flag is still high, lower it and set an IRQ
		else if (TRIGGER_BUTTON){
			debounce++;
			if (debounce == 10) {
				CLEAR_TRIGGER_BUTTON;
				uiDispatch(EXPAND_SW_OFF_SIG);
				debounce = 0;
			}
		}

		// run the state machine from the STM Touch Library
		tsl_status = tsl_user_Exec();

		// when acquisition is complete, send a signal to the UI state machine to parse the sensor readings
		if (tsl_status != TSL_USER_STATUS_BUSY) {
			uiDispatch(SENSOR_EVENT_SIG);
		}
}
