

#include "via_platform_binding.h"
#include "scanner.h"

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
		scanner_mainRisingEdgeCallback(&scanner_signals);
	} else {
		scanner_mainFallingEdgeCallback(&scanner_signals);
	}

	__HAL_TIM_CLEAR_FLAG(&htim12, TIM_FLAG_CC2);

}

// Aux trigger input

void EXTI15_10_IRQHandler(void)
{

	if (EXPANDER_RISING_EDGE) {
		scanner_auxRisingEdgeCallback(&scanner_signals);
	} else {
		scanner_auxFallingEdgeCallback(&scanner_signals);
	}

  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_11);

}

// Expander button

void EXTI1_IRQHandler(void)
{

	if (EXPANDER_BUTTON_PRESSED) {
		uiDispatch(EXPAND_SW_ON_SIG);
		scanner_buttonPressedCallback(&scanner_signals);
	} else {
		uiDispatch(EXPAND_SW_OFF_SIG);
		scanner_buttonReleasedCallback(&scanner_signals);
	}

	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_1);

}

/*
 *
 * Timer interrputs
 *
 */

//// SH A
//
//void TIM16_IRQHandler(void)
//{
//
//	SH_A_SAMPLE
//	if (RUNTIME_DISPLAY) {
//		LEDA_ON;
//	}
//
//	__HAL_TIM_CLEAR_FLAG(&htim16, TIM_FLAG_UPDATE);
//	__HAL_TIM_DISABLE(&htim16);
//
//}
//
//// SH B
//
//void TIM17_IRQHandler(void)
//{
//
//	SH_B_SAMPLE;
//	if (RUNTIME_DISPLAY) {
//		LEDB_ON;
//	}
//	__HAL_TIM_CLEAR_FLAG(&htim17, TIM_FLAG_UPDATE);
//	__HAL_TIM_DISABLE(&htim17);
//
//}

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
		scanner_slowConversionCallback(&scanner_signals);
	}

}

void DMA1_Channel5_IRQHandler(void)
{


	if ((DMA1->ISR & (DMA_FLAG_HT1 << 16)) != 0) {
		DMA1->IFCR = DMA_FLAG_HT1 << 16;
		scanner_halfTransferCallback(&scanner_signals);
	} else if ((DMA1->ISR & (DMA_FLAG_TC1 << 16)) != 0)  {
		DMA1->IFCR = DMA_FLAG_TC1 << 16;
		scanner_transferCompleteCallback(&scanner_signals);
	}

}

/**
* @brief This function handles DMA2 channel3 global interrupt.
*/
void DMA2_Channel3_IRQHandler(void)
{
  /* USER CODE BEGIN DMA2_Channel3_IRQn 0 */

	if ((DMA2->ISR & (DMA_FLAG_HT1 << 8)) != 0) {
		DMA2->IFCR = DMA_FLAG_HT1 << 8;
		uint16_t * cv2ReadIndex = scanner_signals.inputs->cv2Samples;
		for (int i = 0; i < SCANNER_BUFFER_SIZE; i++) {
			int cv2Sample = cv2ReadIndex[i*2] + 32768;
			scanner_signals.parameters->xInput[i] = cv2Sample;
		}
	} else if ((DMA2->ISR & (DMA_FLAG_TC1 << 8)) != 0)  {
		DMA2->IFCR = DMA_FLAG_TC1 << 8;
		uint16_t * cv2ReadIndex = scanner_signals.inputs->cv2Samples + SCANNER_BUFFER_SIZE*2;
		for (int i = 0; i < SCANNER_BUFFER_SIZE; i++) {
			int cv2Sample = cv2ReadIndex[i*2] + 32768;
			scanner_signals.parameters->xInput[i] = cv2Sample;
		}

	}


  /* USER CODE END DMA2_Channel3_IRQn 0 */
  //HAL_DMA_IRQHandler(&hdma_sdadc1);
  /* USER CODE BEGIN DMA2_Channel3_IRQn 1 */

  /* USER CODE END DMA2_Channel3_IRQn 1 */
}

/**
* @brief This function handles DMA2 channel4 global interrupt.
*/
void DMA2_Channel4_IRQHandler(void)
{
  /* USER CODE BEGIN DMA2_Channel4_IRQn 0 */

	if ((DMA2->ISR & (DMA_FLAG_HT1 << 12)) != 0) {
		DMA2->IFCR = DMA_FLAG_HT1 << 12;
		uint16_t * cv3ReadIndex = scanner_signals.inputs->cv3Samples;
		for (int i = 0; i < SCANNER_BUFFER_SIZE; i++) {
			int cv3Sample = cv3ReadIndex[i*2] + 32768;
			scanner_signals.parameters->yInput[i] = cv3Sample;
		}
	} else if ((DMA2->ISR & (DMA_FLAG_TC1 << 12)) != 0)  {
		DMA2->IFCR = DMA_FLAG_TC1 << 12;
		uint16_t * cv3ReadIndex = scanner_signals.inputs->cv3Samples + SCANNER_BUFFER_SIZE*2;
		for (int i = 0; i < SCANNER_BUFFER_SIZE; i++) {
			int cv3Sample = cv3ReadIndex[i*2] + 32768;
			scanner_signals.parameters->yInput[i] = cv3Sample;
		}
	}

  /* USER CODE END DMA2_Channel4_IRQn 0 */
  //HAL_DMA_IRQHandler(&hdma_sdadc2);
  /* USER CODE BEGIN DMA2_Channel4_IRQn 1 */

  /* USER CODE END DMA2_Channel4_IRQn 1 */
}

void TIM6_DAC1_IRQHandler(void) {

	scanner_ioProcessCallback(&scanner_signals);


	// clear timer update flag
	__HAL_TIM_CLEAR_FLAG(&htim6, TIM_FLAG_UPDATE);
}




