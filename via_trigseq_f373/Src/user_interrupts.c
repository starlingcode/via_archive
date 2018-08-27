
#include "trigseq.h"

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

/*
 *
 *  Logic input interrupts
 *
 */

// Main trigger input

void TIM12_IRQHandler(void)
{

	if (TRIGGER_RISING_EDGE) {
		trigseq_mainRisingEdgeCallback(&trigseq_signals);
	} else {
		trigseq_mainFallingEdgeCallback(&trigseq_signals);
	}

	__HAL_TIM_CLEAR_FLAG(&htim12, TIM_FLAG_CC2);

}

// Aux trigger input

void EXTI15_10_IRQHandler(void)
{

	if (EXPANDER_RISING_EDGE) {
		trigseq_auxRisingEdgeCallback(&trigseq_signals);
	} else {
		trigseq_auxFallingEdgeCallback(&trigseq_signals);
	}

  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_11);

}

// Expander button

void EXTI1_IRQHandler(void)
{

	if (EXPANDER_BUTTON_PRESSED) {
		uiDispatch(EXPAND_SW_ON_SIG);
		trigseq_buttonPressedCallback(&trigseq_signals);
	} else {
		uiDispatch(EXPAND_SW_OFF_SIG);
		trigseq_buttonReleasedCallback(&trigseq_signals);
	}

	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_1);

}

/*
 *
 * Timer interrputs
 *
 */

// SH A

void TIM16_IRQHandler(void)
{

	SH_A_SAMPLE
	if (RUNTIME_DISPLAY) {
		LEDA_ON;
	}

	__HAL_TIM_CLEAR_FLAG(&htim16, TIM_FLAG_UPDATE);
	__HAL_TIM_DISABLE(&htim16);

}

// SH B

void TIM17_IRQHandler(void)
{

	SH_B_SAMPLE;
	if (RUNTIME_DISPLAY) {
		LEDB_ON;
	}
	__HAL_TIM_CLEAR_FLAG(&htim17, TIM_FLAG_UPDATE);
	__HAL_TIM_DISABLE(&htim17);

}

// run touch sensor state machine

void TIM13_IRQHandler(void)
{

	// run the state machine from the STM Touch Library
	tsl_status = tsl_user_Exec();
	__HAL_TIM_CLEAR_FLAG(&htim13, TIM_FLAG_UPDATE);

}

// ui timer

void TIM7_IRQHandler(void)
{

	uiDispatch(TIMEOUT_SIG);

	HAL_TIM_IRQHandler(&htim7);

}

/*
 *
 * DMA transfer complete interrupts
 *
 */

// slow ADCs

void DMA1_Channel1_IRQHandler(void)
{

	//minimal interrupt handler for circular buffer

	if ((DMA1->ISR & (DMA_FLAG_HT1)) != 0) {
		DMA1->IFCR = DMA_FLAG_HT1;
	} else {
		DMA1->IFCR = DMA_FLAG_TC1;
		// VIA_UPDATE_CONTROLS_CALLBACK(&signals)
		trigseq_slowConversionCallback(&trigseq_signals);
	}

}

void DMA1_Channel5_IRQHandler(void)
{


	if ((DMA1->ISR & (DMA_FLAG_HT1 << 16)) != 0) {
		DMA1->IFCR = DMA_FLAG_HT1 << 16;
		//
		trigseq_halfTransferCallback(&trigseq_signals);
	} else if ((DMA1->ISR & (DMA_FLAG_TC1 << 16)) != 0)  {
		DMA1->IFCR = DMA_FLAG_TC1 << 16;
		trigseq_transferCompleteCallback(&trigseq_signals);
	}

}




