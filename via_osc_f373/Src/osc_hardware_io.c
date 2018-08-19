#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"
#include "via_io_binding.h"

#include "../inc/osc_ui_implementation.h"
#include "signals.h"

void updateRGB(controlRateInputs *, audioRateInputs *);

extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim5;


/**
 *
 * Helper functions for display handling
 *
 */

void displayXCV_FM(void) {
	LEDC_OFF;
}

void displayXCV_PM(void) {
	LEDC_ON;
}

void displayMorph_Morph(void) {
	LEDD_OFF;
}

void displayMorph_PMW(void) {
	LEDD_ON;
}

void displaySH_On(void) {
	LEDA_ON;
}

void displaySH_Off(void) {
	LEDA_OFF;
}

void displaySync_Hard(void) {
	LEDB_OFF;
}

void displaySync_Soft(void) {
	LEDB_ON;
}


//void updateRGB(controlRateInputs * controls) {
//	SET_RED_LED(controls->frequency);
//	SET_GREEN_LED(controls->morph);
//	SET_BLUE_LED(4095 - controls->frequency);
//}

