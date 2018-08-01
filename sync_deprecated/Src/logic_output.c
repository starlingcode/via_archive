#include "tables.h"
#include "main.h"
#include "tsl_user.h"
#include "scales.h"
#include "eeprom.h"
#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"
#include "interrupt_functions.h"
#include "int64.h"

extern TIM_HandleTypeDef htim15;
extern TIM_HandleTypeDef htim8;
extern TIM_HandleTypeDef htim7;
extern TIM_HandleTypeDef htim1;

void sampHoldB(void) __attribute__((section("ccmram")));
void sampHoldA(void) __attribute__((section("ccmram")));

void EXTI15_10_IRQHandler(void) {
	// Handler for the rising edge at our expander aux logic input
	if(__HAL_GPIO_EXTI_GET_FLAG(GPIO_PIN_11)) {
		generateFrequency();
		SET_EXTPLL;
		__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_11);
	} else {

		if (!(PHASE_STATE)) {
			EXPAND_GATE_HIGH;
			REV2_GATE_LOW;

			if (TRIGA) {
				ALOGIC_HIGH;
				if (RUNTIME_DISPLAY) {
					LEDC_ON;
				}
				__HAL_TIM_SET_COUNTER(&htim15, 0);
				__HAL_TIM_ENABLE(&htim15);
			} else if (GATEA) {
				ALOGIC_HIGH;
				if (RUNTIME_DISPLAY) {
					LEDC_ON;
				}
			}
			if (GATEB) {
				BLOGIC_LOW;
				if (RUNTIME_DISPLAY) {
					LEDD_OFF;
				}
			}
			sampHoldA();

			if (RUNTIME_DISPLAY) {
				__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
			}

			if ((NOCLOCK) && periodCount > 0) {
				generateFrequency();
			}
		} else {

			REV2_GATE_HIGH;
			EXPAND_GATE_LOW;

			if (TRIGB) {
				BLOGIC_HIGH;
				__HAL_TIM_SET_COUNTER(&htim15, 0);
				__HAL_TIM_ENABLE(&htim15);
				if (RUNTIME_DISPLAY) {
					LEDD_ON;
				}
			} else if (GATEB) {
				BLOGIC_HIGH;
				if (RUNTIME_DISPLAY) {
					LEDD_ON;
				}
			}
			if (GATEA) {
				ALOGIC_LOW;
				if (RUNTIME_DISPLAY) {
					LEDC_OFF;
				}
			}
			sampHoldB();

			if (RUNTIME_DISPLAY) {
				__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);
			}
		}
	}

}

void sampHoldB(void) {
	switch (sampleHoldMode) {

	case a:
		SH_A_TRACK;
		if (RUNTIME_DISPLAY) {
			LEDA_ON;
		}
		break;

		// case b: b remains sampled
	case ab:
		SH_A_TRACK;
		if (RUNTIME_DISPLAY) {
			LEDA_OFF;
		}
		// b remains sampled
		break;

	case antidecimate:
		SH_B_SAMPLE;
		SH_A_TRACK;
		if (RUNTIME_DISPLAY) {
			LEDB_OFF;
			LEDA_ON;
		}
		break;

	case decimate:
		SH_A_TRACK;
		__HAL_TIM_SET_COUNTER(&htim7, 0);
		__HAL_TIM_ENABLE(&htim7);
		if (RUNTIME_DISPLAY) {
					LEDA_OFF;
					LEDB_OFF;
				}
		break;

	default:
		break;
	}
}

void sampHoldA(void) {
	switch (sampleHoldMode) {

	case a:
		SH_A_SAMPLE;
		if (RUNTIME_DISPLAY) {
			LEDA_OFF;
		}
		break;

	case b:
		SH_B_TRACK;
		__HAL_TIM_SET_COUNTER(&htim8, 0);
		__HAL_TIM_ENABLE(&htim8);
		if (RUNTIME_DISPLAY) {
			LEDB_OFF;
		}
		break;

	case ab:
		SH_A_SAMPLE;
		SH_B_TRACK;
		if (RUNTIME_DISPLAY) {
			LEDB_OFF;
			LEDA_ON;
		}
		__HAL_TIM_SET_COUNTER(&htim8, 0);
		__HAL_TIM_ENABLE(&htim8);
		break;

	case antidecimate:
		SH_A_SAMPLE;
		SH_B_TRACK;
		if (RUNTIME_DISPLAY) {
			LEDA_OFF;
			LEDB_ON;
		}
		break;

	case decimate:
		SH_B_TRACK;
		__HAL_TIM_SET_COUNTER(&htim7, 0);
		__HAL_TIM_ENABLE(&htim7);
		if (RUNTIME_DISPLAY) {
			LEDA_OFF;
			LEDB_OFF;
		}
		break;

	default:
		break;
	}
}

