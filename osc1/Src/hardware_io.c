#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"
#include "hardware_io.h"

extern TIM_HandleTypeDef htim8;
extern TIM_HandleTypeDef htim7;


//////////////////////////
// s&h handling functions
//////////////////////////

void resampleA(void){
	SH_A_TRACK;
	__HAL_TIM_SET_COUNTER(&htim7, 0);
	__HAL_TIM_ENABLE(&htim7);
}
void resampleB(void){
	SH_B_TRACK;
	__HAL_TIM_SET_COUNTER(&htim8, 0);
	__HAL_TIM_ENABLE(&htim8);
}


