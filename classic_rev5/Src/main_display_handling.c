#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"
#include "main_state_machine.h"
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


void updateRGB(controlRateInputs * controlInputs, audioRateInputs * audioInputs) {
	SET_RED_LED((4095 + controlInputs->knob1Value - controlInputs->cv1Value) >> 1);
	SET_GREEN_LED(controlInputs->knob3Value);
	SET_BLUE_LED(4095 - ((4095 + controlInputs->knob1Value - controlInputs->cv1Value) >> 1));
}

