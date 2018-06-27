#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"
#include "main_state_machine.h"
#include "led_display.h"
#include "dsp.h"
#include "via_rev5_hardware_io.h"

extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim5;

/**
 *
 * Helper function for display handling
 * These should probably move to hardware_io
 * This is a test mock up, the 4 leds could show the 4 modes if they were 2 options each
 *
 */

void displayButton3ModeOff(void) {
	LEDC_OFF;
}

void displayButton3ModeOn(void) {
	LEDC_ON;
}

void displayButton6ModeOff(void) {
	LEDD_OFF;
}

void displayButton6ModeOn(void) {
	LEDD_ON;
}

void displayButton1ModeOn(void) {
	LEDA_ON;
}

void displayButton1ModeOff(void) {
	LEDA_OFF;
}

void displayButton4ModeOff(void) {
	LEDB_OFF;
}

void displayButton4ModeOn(void) {
	LEDB_ON;
}


void updateRGB(controlRateInputs * controlInputs, audioRateInputs * audioInputs) {
	SET_RED_LED((4095 + controlInputs->knob1Value - controlInputs->cv1Value) >> 1);
	SET_GREEN_LED(controlInputs->knob3Value);
	SET_BLUE_LED(4095 - ((4095 + controlInputs->knob1Value - controlInputs->cv1Value) >> 1));

}
