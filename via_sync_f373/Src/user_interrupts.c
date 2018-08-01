
#include "signals.h"
#include "main.h"
#include "user_interface.h"
#include "via_rev5_hardware_io.h"
#include "sync_modes.h"
#include "sync_interrupt_handlers.h"


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

extern TIM_HandleTypeDef htim6;
extern TIM_HandleTypeDef htim7;
extern TIM_HandleTypeDef htim12;
extern TIM_HandleTypeDef htim13;
extern TIM_HandleTypeDef htim16;
extern TIM_HandleTypeDef htim17;

tsl_user_status_t tsl_status;

void TIM16_IRQHandler(void)
{

	SH_A_SAMPLE
	if (RUNTIME_DISPLAY) {
		LEDA_ON;
	}

	__HAL_TIM_CLEAR_FLAG(&htim16, TIM_FLAG_UPDATE);
	__HAL_TIM_DISABLE(&htim16);

}

void TIM17_IRQHandler(void)
{

	SH_B_SAMPLE;
	if (RUNTIME_DISPLAY) {
		LEDB_ON;
	}
	__HAL_TIM_CLEAR_FLAG(&htim17, TIM_FLAG_UPDATE);
	__HAL_TIM_DISABLE(&htim17);

}

void TIM12_IRQHandler(void)
{

	if (TRIGGER_RISING_EDGE) {
		mainRisingEdgeCallback(&signals);
	} else {
		mainFallingEdgeCallback(&signals);
	}

	__HAL_TIM_CLEAR_FLAG(&htim12, TIM_FLAG_CC2);

}


void TIM13_IRQHandler(void)
{

	// run the state machine from the STM Touch Library
	tsl_status = tsl_user_Exec();
	__HAL_TIM_CLEAR_FLAG(&htim13, TIM_FLAG_UPDATE);

}


void TIM6_DAC1_IRQHandler(void)
{

	ioProcessCallback(&signals);
	nextSampleCallback(&signals);


	__HAL_TIM_CLEAR_FLAG(&htim6, TIM_FLAG_UPDATE);

}

void TIM7_IRQHandler(void)
{

	uiDispatch(TIMEOUT_SIG);

	HAL_TIM_IRQHandler(&htim7);

}



void EXTI15_10_IRQHandler(void)
{

	if (EXPANDER_RISING_EDGE) {
		auxRisingEdgeCallback(&signals);
	} else { //falling edge
		auxFallingEdgeCallback(&signals);
	}

  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_11);

}



void EXTI1_IRQHandler(void)
{

	static int buttonPressed;

	buttonPressed = !buttonPressed;

	if (buttonPressed) {
		uiDispatch(EXPAND_SW_ON_SIG);
		buttonPressedCallback(&signals);
	} else { //falling edge
		uiDispatch(EXPAND_SW_OFF_SIG);
		buttonReleasedCallback(&signals);
	}

	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_1);

}
