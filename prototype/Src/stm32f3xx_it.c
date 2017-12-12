/**
 ******************************************************************************
 * @file    stm32f3xx_it.c
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

/* USER CODE BEGIN 0 */

#include "tables.h"
#include "main.h"
#include "int64.h"
#include "interrupt_functions.h"



uint32_t span;

// ADC variables and average variables
uint32_t ADCReadings1[4];
uint32_t ADCReadings2[2];
uint32_t ADCReadings3[2];


// mode indicators, determined in the main loop
enum speedTypes speed;
enum loopTypes loop;
enum trigModeTypes trigMode;
enum sampleHoldModeTypes sampleHoldMode;

extern TIM_HandleTypeDef htim1;

extern int lookuptable[4096];




/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern DMA_HandleTypeDef hdma_adc1;
extern DMA_HandleTypeDef hdma_adc2;
extern DMA_HandleTypeDef hdma_adc3;
extern DAC_HandleTypeDef hdac;
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
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

/**
 * @brief This function handles DMA1 channel1 global interrupt.
 */
void DMA1_Channel1_IRQHandler(void) {
	/* USER CODE BEGIN DMA1_Channel1_IRQn 0 */

	/* USER CODE END DMA1_Channel1_IRQn 0 */
	HAL_DMA_IRQHandler(&hdma_adc1);
	/* USER CODE BEGIN DMA1_Channel1_IRQn 1 */

	/* USER CODE END DMA1_Channel1_IRQn 1 */
}

/**
 * @brief This function handles TIM1 break and TIM15 interrupts.
 */
void TIM1_BRK_TIM15_IRQHandler(void) {
	/* USER CODE BEGIN TIM1_BRK_TIM15_IRQn 0 */
	EOA_JACK_LOW;
	EOR_JACK_LOW;
	__HAL_TIM_DISABLE(&htim15);
	__HAL_TIM_CLEAR_FLAG(&htim15, TIM_FLAG_UPDATE);
	/* USER CODE END TIM1_BRK_TIM15_IRQn 0 */
	//HAL_TIM_IRQHandler(&htim1);
	//HAL_TIM_IRQHandler(&htim15);
	/* USER CODE BEGIN TIM1_BRK_TIM15_IRQn 1 */

	/* USER CODE END TIM1_BRK_TIM15_IRQn 1 */
}

/**
 * @brief This function handles TIM2 global interrupt.
 */
void TIM2_IRQHandler(void) {
	/* USER CODE BEGIN TIM2_IRQn 0 */
	if (((GPIOA->IDR & GPIO_PIN_15) == (uint32_t) GPIO_PIN_RESET) || (TRIGGER_BUTTON)) {

		if (!(OSCILLATOR_ACTIVE)) { // oscillator at rest
			SET_OSCILLATOR_ACTIVE; // set the oscillator flag
			if (DRUM_MODE_ON) { // perform the operations needed to initiate a drum sound
				SET_DRUM_ATTACK_ON; //set global flag indicating we are using the timer to generate "attack"
				SET_UPDATE_PRESCALER; //logic to be used in the timer interrupt so we pass through and just load prescaler to shadow register
				TIM3->PSC = (lookuptable[time2Knob] >> 11) + (lookuptable[time2CV] >> 11); // release time prescaler loaded to holding register
				TIM3->EGR = TIM_EGR_UG; //immediately set an update event
				TIM3->CNT = 3840; //reset the count for the down counter
				//TIM3->CR1 |= TIM_CR1_CEN; //enable timer

			}
			if (speed == env) {
				attackTime = calcTime1Env; //set the function pointers for attack and release to the envelope time scale
				releaseTime = calcTime2Env; //i believe this needs to be done here to ensure that we recover from retrigger behavior
			} else if (speed == seq) {
				attackTime = calcTime1Seq; //set the function pointer for attack and release to the sequence time scale
				releaseTime = calcTime2Seq;
			}
			//incSign = 1;
			if (trigMode == gated) {
				SET_GATE_ON;
			} //turn the gate flag on in gatemode
			sampHoldA();
		} else {

			if ((DRUM_MODE_ON) && !(DRUM_ATTACK_ON)) {
				SET_UPDATE_PRESCALER; //same logic flag as before
				SET_DRUM_ATTACK_ON;
				attackCount = TIM3->CNT;
				__HAL_TIM_DISABLE(&htim3);
				TIM3->PSC = (lookuptable[time2Knob] >> 11) + (lookuptable[time2CV] >> 11);
				TIM3->EGR = TIM_EGR_UG; //immediately set an update event to load the prescaler register


			}

			else {

				switch (trigMode) {

				case hardsync:

					position = 0; // hard reset to 0

					break;

				case gated:

					if (position < span) { //look to see if we are backtracking, if so, reset the envelope behavior

						if (attackTime == &calcTime2Env) {
							attackTime = &calcTime1Env;
						} else if (attackTime == &calcTime2Seq) {
							attackTime = &calcTime1Seq;
						}
						incSign = 1; // this reverts our direction
						SET_GATE_ON; // signal that the gate is on

					}

					else { //if we are releasing and we get a new gate on, run back up the release slope at attack timescale

						if (speed == env) {
							releaseTime = calcTime1Env;
						} else if (speed == seq) {
							releaseTime = calcTime1Seq;
						}
						incSign = -1; // this reverses the direction
						SET_GATE_ON;

					}

					break;

				case nongatedretrigger:

					if (position >= span) { //if we are releasing and we get a new gate on, run back up the release slope at attack timescale

						if (speed == env) {
							releaseTime = calcTime1Env;
						} else if (speed == seq) {
							releaseTime = calcTime1Seq;
						}
						incSign = -1;

					}

					break;

				case pendulum:

					if (!(HOLD_AT_B)) { // if we arent currently gated, reverse the direction of the oscillator
						incSign = incSign * -1;
					}

					break;

				default:
					break;

				}

			}
		}
		if (trigMode == pendulum && loop == noloop) { // regardless of whether the oscillator is at rest or not, toggle the gateOn every trigger with pendulum

			TOGGLE_GATE_ON;

		}

	}

	else {

		if (trigMode == gated && !(DRUM_MODE_ON)) { //aka, gate off when we aren't in drum mode

			if (position < span) { //if we release the gate before making it through attack, run back through attack at release speed

				if (speed == env) {
					attackTime = calcTime2Env;
				}
				if (speed == seq) {
					attackTime = calcTime2Seq;
				}
				incSign = -1; // -1 in int
				RESET_GATE_ON;

			} else { //if we get a release when we are at or after span, reset the oscillator behavior and let it finish release

				if (speed == env) {
					releaseTime = calcTime2Env;
				};
				if (speed == seq) {
					releaseTime = calcTime2Seq;
				};
				incSign = 1;
				RESET_GATE_ON;

			}

		}
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
	//drumReleaseOn = 0;

	__HAL_TIM_CLEAR_FLAG(&htim3, TIM_FLAG_UPDATE);

	if (UPDATE_PRESCALER) { // handle the update event to load the prescaler initially
		RESET_UPDATE_PRESCALER;
	}

	else { // raise the flag to put the drum mode to rest after overflowing the release portion
		RESET_DRUM_RELEASE_ON;
		expoScale = 0;
		__HAL_TIM_DISABLE(&htim3);
		__HAL_TIM_SET_COUNTER(&htim3, 0);
		SET_LAST_CYCLE;
	}

	__HAL_TIM_CLEAR_FLAG(&htim3, TIM_FLAG_UPDATE);


	/* USER CODE END TIM3_IRQn 0 */
	//HAL_TIM_IRQHandler(&htim3);
	/* USER CODE BEGIN TIM3_IRQn 1 */

	/* USER CODE END TIM3_IRQn 1 */
}

/**
 * @brief This function handles TIM8 update interrupt.
 */
void TIM8_UP_IRQHandler(void) {
	/* USER CODE BEGIN TIM8_UP_IRQn 0 */
	SH_B_SAMPLE
	//this handles the logic where we resample b at a
	if (RGB_ON) {
		LEDB_ON
	}

	__HAL_TIM_CLEAR_FLAG(&htim8, TIM_FLAG_UPDATE);
	__HAL_TIM_DISABLE(&htim8);

	/* USER CODE END TIM8_UP_IRQn 0 */
	//HAL_TIM_IRQHandler(&htim8);
	/* USER CODE BEGIN TIM8_UP_IRQn 1 */

	/* USER CODE END TIM8_UP_IRQn 1 */
}

/**
 * @brief This function handles Timer 6 interrupt and DAC underrun interrupts.
 */
void TIM6_DAC_IRQHandler(void) {
	/* USER CODE BEGIN TIM6_DAC_IRQn 0 */



	__HAL_TIM_CLEAR_FLAG(&htim6, TIM_FLAG_UPDATE);

	dacISR();


	/* USER CODE END TIM6_DAC_IRQn 0 */
	// HAL_TIM_IRQHandler(&htim6);
	//HAL_DAC_IRQHandler(&hdac);
	/* USER CODE BEGIN TIM6_DAC_IRQn 1 */

	/* USER CODE END TIM6_DAC_IRQn 1 */
}

/**
 * @brief This function handles TIM7 global interrupt.
 */
void TIM7_IRQHandler(void) {
	/* USER CODE BEGIN TIM7_IRQn 0 */
	SH_A_SAMPLE
	// this handles our decimate resampling
	SH_B_SAMPLE
	if (RGB_ON) {
		LEDA_ON
		LEDB_ON
	}
	__HAL_TIM_CLEAR_FLAG(&htim7, TIM_FLAG_UPDATE);
	/* USER CODE END TIM7_IRQn 0 */
	//HAL_TIM_IRQHandler(&htim7);
	/* USER CODE BEGIN TIM7_IRQn 1 */
	__HAL_TIM_DISABLE(&htim7);

	/* USER CODE END TIM7_IRQn 1 */
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

void EXTI15_10_IRQHandler(void) {

	if (!(PHASE_STATE)) {

		if (trigMode == nongatedretrigger) {
			incSign = 1;

			if (speed == env) {
				releaseTime = calcTime2Env;
			} else if (speed == seq) {
				releaseTime = calcTime2Seq;
			}
		}

		EOR_JACK_HIGH
		EOA_JACK_LOW
		EOR_GATE_HIGH
		EOA_GATE_LOW
		__HAL_TIM_SET_COUNTER(&htim15, 0);
		__HAL_TIM_ENABLE(&htim15);

		if (inc < 0) {
			sampHoldB();
		} else if (OSCILLATOR_ACTIVE) {
			sampHoldA();
		}

		if (RGB_ON) {
			LEDC_ON
			LEDD_OFF
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
		}

	} else {

		EOA_JACK_HIGH
		EOR_JACK_LOW
		EOA_GATE_HIGH
		EOR_GATE_LOW
		__HAL_TIM_SET_COUNTER(&htim15, 0);
		__HAL_TIM_ENABLE(&htim15);

		if (inc < 0) {
			sampHoldA();
		} else {
			sampHoldB();
		}

		if (RGB_ON) {
			LEDC_OFF
			LEDD_ON
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);
		}

	}

}

void sampHoldB(void) {

	switch (sampleHoldMode) {

	case a:
		SH_A_TRACK
		if (RGB_ON) {
			LEDA_ON
		}
		break;

		// case b: b remains sampled

	case ab:
		SH_A_TRACK
		if (RGB_ON) {
			LEDA_OFF
		}
		// b remains sampled
		break;

	case antidecimate:
		SH_B_SAMPLE
		SH_A_TRACK
		if (RGB_ON) {
			LEDB_OFF
			LEDA_ON
		}
		break;

	case decimate:
		SH_A_TRACK
		if (RGB_ON) {
			LEDA_OFF
			LEDB_OFF
		}

		__HAL_TIM_SET_COUNTER(&htim7, 0);
		__HAL_TIM_ENABLE(&htim7);
		break;

	default:
		break;

	}

}

void sampHoldA(void) {

	switch (sampleHoldMode) {

	case a:
		SH_A_SAMPLE
		if (RGB_ON) {
			LEDA_OFF
		}
		break;

	case b:
		SH_B_TRACK
		__HAL_TIM_SET_COUNTER(&htim8, 0);
		__HAL_TIM_ENABLE(&htim8);
		if (RGB_ON) {
			LEDB_OFF
		}
		break;

	case ab:
		SH_A_SAMPLE
		SH_B_TRACK
		if (RGB_ON) {
			LEDB_OFF
			LEDA_ON
		}
		__HAL_TIM_SET_COUNTER(&htim8, 0);
		__HAL_TIM_ENABLE(&htim8);
		break;

	case antidecimate:
		SH_A_SAMPLE
		SH_B_TRACK
		if (RGB_ON) {
			LEDA_OFF
			LEDB_ON
		}
		break;

	case decimate:
		SH_B_TRACK
		;
		if (RGB_ON) {
			LEDA_OFF
			;
			LEDB_OFF
			;
		}

		__HAL_TIM_SET_COUNTER(&htim7, 0);
		__HAL_TIM_ENABLE(&htim7);
		break;

	default:
		break;

	}

}



/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
