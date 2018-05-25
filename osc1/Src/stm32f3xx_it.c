/**
 ******************************************************************************
GAT * @file    stm32f3xx_it.c
 * @brief   Interrupt Service Routines.
 ******************************************************************************
 *
 * COPYRIGHT(c) 2017 STMicroelectronics
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of STMicroelectronics nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************
 */
/* Includes ------------------------------------------------------------------*/
#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"
#include "main_state_machine.h"
#include "dsp.h"
#include "main.h"

/* USER CODE BEGIN 0 */

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

uint32_t hardSyncMultiplier;

q31_t reverseMultiplier = 1;

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern DMA_HandleTypeDef hdma_adc1;
extern DMA_HandleTypeDef hdma_adc2;
extern DMA_HandleTypeDef hdma_adc3;

extern DAC_HandleTypeDef hdac;

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim6;
extern TIM_HandleTypeDef htim7;
extern TIM_HandleTypeDef htim8;
extern TIM_HandleTypeDef htim15;

/******************************************************************************/
/*            Cortex-M4 Processor Interruption and Exception Handlers         */
/******************************************************************************/

/**
 * @brief This function handles Non maskable interrupt.
 */
void NMI_Handler(void) {
	/* USER CODE BEGIN NonMaskableInt_IRQn 0 */

	/* USER CODE END NonMaskableInt_IRQn 0 */
	/* USER CODE BEGIN NonMaskableInt_IRQn 1 */

	/* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
 * @brief This function handles Hard fault interrupt.
 */


void HardFault_Handler(void) {
	/* USER CODE BEGIN HardFault_IRQn 0 */

	/* USER CODE END HardFault_IRQn 0 */
	while (1) {
	}
	/* USER CODE BEGIN HardFault_IRQn 1 */

	/* USER CODE END HardFault_IRQn 1 */
}

/**
 * @brief This function handles Memory management fault.
 */
void MemManage_Handler(void) {
	/* USER CODE BEGIN MemoryManagement_IRQn 0 */

	/* USER CODE END MemoryManagement_IRQn 0 */
	while (1) {
	}
	/* USER CODE BEGIN MemoryManagement_IRQn 1 */

	/* USER CODE END MemoryManagement_IRQn 1 */
}

/**
 * @brief This function handles Pre-fetch fault, memory access fault.
 */
void BusFault_Handler(void) {
	/* USER CODE BEGIN BusFault_IRQn 0 */

	/* USER CODE END BusFault_IRQn 0 */
	while (1) {
	}
	/* USER CODE BEGIN BusFault_IRQn 1 */

	/* USER CODE END BusFault_IRQn 1 */
}

/**
 * @brief This function handles Undefined instruction or illegal state.
 */
void UsageFault_Handler(void) {
	/* USER CODE BEGIN UsageFault_IRQn 0 */

	/* USER CODE END UsageFault_IRQn 0 */
	while (1) {
	}
	/* USER CODE BEGIN UsageFault_IRQn 1 */

	/* USER CODE END UsageFault_IRQn 1 */
}

/**
 * @brief This function handles System service call via SWI instruction.
 */
void SVC_Handler(void) {
	/* USER CODE BEGIN SVCall_IRQn 0 */

	/* USER CODE END SVCall_IRQn 0 */
	/* USER CODE BEGIN SVCall_IRQn 1 */

	/* USER CODE END SVCall_IRQn 1 */
}

/**
 * @brief This function handles Debug monitor.
 */
void DebugMon_Handler(void) {
	/* USER CODE BEGIN DebugMonitor_IRQn 0 */

	/* USER CODE END DebugMonitor_IRQn 0 */
	/* USER CODE BEGIN DebugMonitor_IRQn 1 */

	/* USER CODE END DebugMonitor_IRQn 1 */
}

/**
 * @brief This function handles Pendable request for system service.
 */
void PendSV_Handler(void) {
	/* USER CODE BEGIN PendSV_IRQn 0 */

	/* USER CODE END PendSV_IRQn 0 */
	/* USER CODE BEGIN PendSV_IRQn 1 */

	/* USER CODE END PendSV_IRQn 1 */
}

/**
 * @brief This function handles System tick timer.
 */
void SysTick_Handler(void) {
	/* USER CODE BEGIN SysTick_IRQn 0 */

	/* USER CODE END SysTick_IRQn 0 */
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
	/* USER CODE BEGIN SysTick_IRQn 1 */

	/* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F3xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f3xx.s).                    */
/******************************************************************************/

void TIM1_BRK_TIM15_IRQHandler(void) {
	/* USER CODE BEGIN TIM1_BRK_TIM15_IRQn 0 */

	handleCoversionSlow(&controlRateInput);

	__HAL_TIM_CLEAR_FLAG(&htim15, TIM_FLAG_UPDATE);
	/* USER CODE END TIM1_BRK_TIM15_IRQn 0 */
	//HAL_TIM_IRQHandler(&htim1);
	//HAL_TIM_IRQHandler(&htim15);
	/* USER CODE BEGIN TIM1_BRK_TIM15_IRQn 1 */

	/* USER CODE END TIM1_BRK_TIM15_IRQn 1 */
}


/**
 * @brief This function handles DMA1 channel1 global interrupt.
 */
void DMA1_Channel1_IRQHandler(void) {
	/* USER CODE BEGIN DMA1_Channel1_IRQn 0 */

	//mainRequest(MAIN_ADC1_CONV_COMPLETE);

	/* USER CODE END DMA1_Channel1_IRQn 0 */
	HAL_DMA_IRQHandler(&hdma_adc1);
	/* USER CODE BEGIN DMA1_Channel1_IRQn 1 */

	/* USER CODE END DMA1_Channel1_IRQn 1 */
}

/**
 * @brief This function handles TIM2 global interrupt.
 */
void TIM2_IRQHandler(void) {
	/* USER CODE BEGIN TIM2_IRQn 0 */

	if (TRIGGER_RISING_EDGE) {
		if (syncMode == hard) {
			hardSyncMultiplier = 0;
		} else {
			reverseMultiplier = 1;
		}
	} else {
		reverseMultiplier = -1;
	}

	__HAL_TIM_CLEAR_FLAG(&htim2, TIM_FLAG_CC1);
	/* USER CODE END TIM2_IRQn 0 */
	//HAL_TIM_IRQHandler(&htim2);
	/* USER CODE BEGIN TIM2_IRQn 1 */

	/* USER CODE END TIM2_IRQn 1 */
}

/**
 * @brief This function handles TIM3 global interrupt.
 */
void TIM3_IRQHandler(void) {
	/* USER CODE BEGIN TIM3_IRQn 0 */

	__HAL_TIM_CLEAR_FLAG(&htim3, TIM_FLAG_UPDATE);
	/* USER CODE END TIM3_IRQn 0 */
	//HAL_TIM_IRQHandler(&htim3);
	/* USER CODE BEGIN TIM3_IRQn 1 */

	/* USER CODE END TIM3_IRQn 1 */
}

/**
 * @brief This function handles Timer 6 interrupt and DAC underrun interrupts.
 */
void TIM6_DAC_IRQHandler(void) {
	/* USER CODE BEGIN TIM6_DAC_IRQn 0 */

	static uint32_t readIndex;

//	// write the sample to the dac
	WRITE_DAC1(__USAT(4095 - (outputRead->samples[readIndex] + 2048), 12));
	WRITE_DAC2(__USAT(outputRead->samples[readIndex] + 2048, 12));


	// execute the GPIO handlers
	(*outputRead->logicStates[readIndex].shAHandler)();
	(*outputRead->logicStates[readIndex].shBHandler)();
	(*outputRead->logicStates[readIndex].logicAHandler)();
	(*outputRead->logicStates[readIndex].logicBHandler)();
	(*outputRead->logicStates[readIndex].auxLogicHandler)();

	// store the x and morph CVs at sample rate
	inputWrite->xCV[readIndex] = cv2;
	inputWrite->morphCV[readIndex] = cv3;

	// write the current trig multiplier (used for sync) to the buffer
	// reset it to 1
	inputWrite->hardSyncInput[readIndex] = hardSyncMultiplier;
	hardSyncMultiplier = 1;

	inputWrite->reverseInput[readIndex] = reverseMultiplier;

	// TODO replace with linked list implementation that makes this prettier

	// check the buffer read counter to see if we just read the last sample in the current buffer
	if (readIndex == BUFFER_SIZE - 1) {

		// if so, reset the buffer index counter
		readIndex = 0;

		// switch out the read/write struct pointers for inputs and outputs
		audioRateInputs *temp1 = inputWrite;
		inputWrite = inputRead;
		inputRead = temp1;

		audioRateOutputs *temp2 = outputWrite;
		outputWrite = outputRead;
		outputRead = temp2;

		// tell the main loop to fill the next buffer
		main_State = main_fillBuffer;

	} else {
		// otherwise, increment the buffer read counter
		readIndex++;
	}

	// clear timer update flag
	__HAL_TIM_CLEAR_FLAG(&htim6, TIM_FLAG_UPDATE);
}

/**
 * @brief This function handles TIM7 global interrupt.
 */
void TIM7_IRQHandler(void) {
	/* USER CODE BEGIN TIM7_IRQn 0 */

	SH_A_SAMPLE;
	SET_SAMPLE_A;

	__HAL_TIM_CLEAR_FLAG(&htim7, TIM_FLAG_UPDATE);
	__HAL_TIM_DISABLE(&htim7);
	/* USER CODE END TIM7_IRQn 0 */
	//HAL_TIM_IRQHandler(&htim7);
	/* USER CODE BEGIN TIM7_IRQn 1 */

	/* USER CODE END TIM7_IRQn 1 */
}

/**
 * @brief This function handles TIM8 update interrupt.
 */
void TIM8_UP_IRQHandler(void) {
	/* USER CODE BEGIN TIM8_UP_IRQn 0 */

	SH_B_SAMPLE;
	SET_SAMPLE_B;

	__HAL_TIM_CLEAR_FLAG(&htim8, TIM_FLAG_UPDATE);
	__HAL_TIM_DISABLE(&htim8);

	/* USER CODE END TIM8_UP_IRQn 0 */
	//HAL_TIM_IRQHandler(&htim8);
	/* USER CODE BEGIN TIM8_UP_IRQn 1 */

	/* USER CODE END TIM8_UP_IRQn 1 */
}

/**
 * @brief This function handles DMA2 channel1 global interrupt.
 */
void DMA2_Channel1_IRQHandler(void) {
	/* USER CODE BEGIN DMA2_Channel1_IRQn 0 */


	/* USER CODE END DMA2_Channel1_IRQn 0 */
	HAL_DMA_IRQHandler(&hdma_adc2);
	/* USER CODE BEGIN DMA2_Channel1_IRQn 1 */

	/* USER CODE END DMA2_Channel1_IRQn 1 */
}

/**
 * @brief This function handles DMA2 channel5 global interrupt.
 */
void DMA2_Channel5_IRQHandler(void) {
	/* USER CODE BEGIN DMA2_Channel5_IRQn 0 */


	/* USER CODE END DMA2_Channel5_IRQn 0 */
	HAL_DMA_IRQHandler(&hdma_adc3);
	/* USER CODE BEGIN DMA2_Channel5_IRQn 1 */

	/* USER CODE END DMA2_Channel5_IRQn 1 */
}

/* USER CODE BEGIN 1 */

void TIM4_IRQHandler(void) {
	/* USER CODE BEGIN TIM8_UP_IRQn 0 */

	uiDispatch(TIMEOUT_SIG);

	/* USER CODE END TIM8_UP_IRQn 0 */
	HAL_TIM_IRQHandler(&htim4);
	/* USER CODE BEGIN TIM8_UP_IRQn 1 */

	/* USER CODE END TIM8_UP_IRQn 1 */
}

void EXTI15_10_IRQHandler(void) {

	// falling edge interrupt not yet implemented
	//mainPush(MAIN_AUX_RISING_EDGE);


	__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_11);
}

/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
