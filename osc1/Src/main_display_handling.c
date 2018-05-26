#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"
#include "main_state_machine.h"
#include "dsp.h"

extern TIM_HandleTypeDef htim1;

/**
 *
 * Helper function for display handling
 * These should probably move to hardware_io
 * This is a test mock up, the 4 leds could show the 4 modes if they were 2 options each
 *
 */

void displayXCV_FM(void) {
	LEDC_ON;
}

void displayXCV_PM(void) {
	LEDD_ON;
}

void displaySH_On(void) {
	LEDA_ON;
	LEDB_ON;
}

void displaySH_Off(void) {
	LEDA_OFF;
	LEDB_OFF;
}

void updateRGB(controlRateInputs * controlInputs, audioRateInputs * audioInputs) {
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, (4095 + controlInputs->knob1Value - controlInputs->cv1Value) >> 1);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, __USAT(2048 + controlInputs->knob3Value - audioInputs->morphCV[0], 12));
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 4095 - ((4095 + controlInputs->knob1Value - controlInputs->cv1Value) >> 1));
}
