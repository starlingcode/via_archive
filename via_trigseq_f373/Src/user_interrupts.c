
#include "dsp.h"
#include "main.h"
#include "user_interface.h"
#include "via_rev5_hardware_io.h"
#include "trigseq_modes.h"
#include "trigseq_interrupt_handlers.h"


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

/**
* @brief This function handles TIM16 global interrupt.
*/
void TIM16_IRQHandler(void)
{
  /* USER CODE BEGIN TIM16_IRQn 0 */

	SH_A_SAMPLE
	if (RUNTIME_DISPLAY) {
		LEDA_ON;
	}

	__HAL_TIM_CLEAR_FLAG(&htim16, TIM_FLAG_UPDATE);
	__HAL_TIM_DISABLE(&htim16);

  /* USER CODE END TIM16_IRQn 0 */
  //HAL_TIM_IRQHandler(&htim16);
  /* USER CODE BEGIN TIM16_IRQn 1 */

  /* USER CODE END TIM16_IRQn 1 */
}

/**
* @brief This function handles TIM17 global interrupt.
*/
void TIM17_IRQHandler(void)
{
  /* USER CODE BEGIN TIM17_IRQn 0 */

	SH_B_SAMPLE;
	if (RUNTIME_DISPLAY) {
		LEDB_ON;
	}
	__HAL_TIM_CLEAR_FLAG(&htim17, TIM_FLAG_UPDATE);
	__HAL_TIM_DISABLE(&htim17);

  /* USER CODE END TIM17_IRQn 0 */
  //HAL_TIM_IRQHandler(&htim17);
  /* USER CODE BEGIN TIM17_IRQn 1 */

  /* USER CODE END TIM17_IRQn 1 */
}

/**
* @brief This function handles TIM12 global interrupt.
*/
void TIM12_IRQHandler(void)
{
  /* USER CODE BEGIN TIM12_IRQn 0 */

	if (TRIGGER_RISING_EDGE) {
		mainRisingEdgeCallback(&controlRateInput, &audioRateInput, &softwareSignals);
	} else { //falling edge
		mainFallingEdgeCallback(&softwareSignals);
	}

	__HAL_TIM_CLEAR_FLAG(&htim12, TIM_FLAG_CC2);

  /* USER CODE END TIM12_IRQn 0 */
  //HAL_TIM_IRQHandler(&htim12);
  /* USER CODE BEGIN TIM12_IRQn 1 */

  /* USER CODE END TIM12_IRQn 1 */
}

/**
* @brief This function handles TIM13 global interrupt.
*/
void TIM13_IRQHandler(void)
{
  /* USER CODE BEGIN TIM13_IRQn 0 */

	// run the state machine from the STM Touch Library
	tsl_status = tsl_user_Exec();
	__HAL_TIM_CLEAR_FLAG(&htim13, TIM_FLAG_UPDATE);


  /* USER CODE END TIM13_IRQn 1 */
}

/**
* @brief This function handles TIM6 global interrupt and DAC1 underrun error interrupts.
*/
void TIM6_DAC1_IRQHandler(void)
{

	ioProcessCallback(&audioRateInput, &controlRateInput, &audioRateOutput);
	generateSample(&softwareSignals, &audioRateOutput);


	// clear timer update flag
	__HAL_TIM_CLEAR_FLAG(&htim6, TIM_FLAG_UPDATE);

}

/**
* @brief This function handles TIM7 global interrupt.
*/
void TIM7_IRQHandler(void)
{
  /* USER CODE BEGIN TIM7_IRQn 0 */

	uiDispatch(TIMEOUT_SIG);

  /* USER CODE END TIM7_IRQn 0 */
  HAL_TIM_IRQHandler(&htim7);
  /* USER CODE BEGIN TIM7_IRQn 1 */

  /* USER CODE END TIM7_IRQn 1 */
}

// trigger input interrupt

void EXTI15_10_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI15_10_IRQn 0 */

	if (EXPANDER_RISING_EDGE) {
		auxRisingEdgeCallback(&softwareSignals);
	} else { //falling edge
		auxFallingEdgeCallback(&softwareSignals);
	}

  /* USER CODE END EXTI15_10_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_11);
  /* USER CODE BEGIN EXTI15_10_IRQn 1 */

  /* USER CODE END EXTI15_10_IRQn 1 */
}

//trigger button interrupt

void EXTI1_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI1_IRQn 0 */

	static int buttonPressed;

	buttonPressed = !buttonPressed;

	if (buttonPressed) {
		uiDispatch(EXPAND_SW_ON_SIG);
		buttonPressedCallback(&softwareSignals);
	} else { //falling edge
		uiDispatch(EXPAND_SW_OFF_SIG);
		buttonReleasedCallback(&softwareSignals);
	}

  /* USER CODE END EXTI1_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_1);
  /* USER CODE BEGIN EXTI1_IRQn 1 */

  /* USER CODE END EXTI1_IRQn 1 */
}
