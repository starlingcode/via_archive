
/* USER CODE BEGIN Includes */

#include "via_rev5_hardware_io.h"
#include "main.h"
#include "stm32f3xx_hal.h"
#include "adc.h"
#include "dac.h"
#include "dma.h"
#include "sdadc.h"
#include "tim.h"
#include "touchsensing.h"
#include "tsc.h"
#include "gpio.h"


extern void mainHardwareInit(void);

void mainHardwareInit(void) {

/* Start Calibration in polling mode */

	if (HAL_SDADC_CalibrationStart(&hsdadc1, SDADC_CALIBRATION_SEQ_1) != HAL_OK)
	{
		LEDA_ON;
	}

	/* Pool for the end of calibration */
	if (HAL_SDADC_PollForCalibEvent(&hsdadc1, 100) != HAL_OK)
	{
		LEDB_ON;
	}


	if (HAL_SDADC_CalibrationStart(&hsdadc2, SDADC_CALIBRATION_SEQ_1) != HAL_OK)
	{
		LEDA_ON;
	}

	/* Pool for the end of calibration */
	if (HAL_SDADC_PollForCalibEvent(&hsdadc2, 100) != HAL_OK)
	{
		LEDB_ON;
	}

	// set the priority and enable an interrupt line to be used by the trigger button input and aux trigger
	HAL_NVIC_SetPriority(EXTI1_IRQn, 1, 0);
	HAL_NVIC_EnableIRQ(EXTI1_IRQn);

	HAL_NVIC_SetPriority(EXTI15_10_IRQn, 1, 0);
	HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

	// initialize RGB led
	HAL_TIM_Base_Start(&htim3);
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
	HAL_TIM_Base_Start(&htim4);
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_4);
	HAL_TIM_Base_Start(&htim5);
	HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_1);

	// initialize the ADCs and their respective DMA arrays
	HAL_ADC_Start_DMA(&hadc1, slowADCReadings, 4);
	HAL_SDADC_Start_DMA(&hsdadc1, fastADC1Readings, 1);
	HAL_SDADC_Start_DMA(&hsdadc2, fastADC2Readings, 1);

	// initialize the DAC
	HAL_DAC_Start(&hdac1, DAC_CHANNEL_1);
	HAL_DAC_Start(&hdac1, DAC_CHANNEL_2);
	HAL_DAC_Start(&hdac2, DAC_CHANNEL_1);

	//start our DAC time base
	HAL_TIM_Base_Start_IT(&htim6);


//	 initialize the timer that is used for touch sensor press timeout
	__HAL_TIM_ENABLE_IT(&htim7, TIM_IT_UPDATE);

	// set the dac timer overflow to 1023 to facilitate frequency division
	TIM2->ARR = 1023;

	__HAL_TIM_ENABLE(&htim2);
	 //initialize the timer that is used to detect rising and falling edges at the trigger input
	HAL_TIM_IC_Start_IT(&htim12, TIM_CHANNEL_2);

	//initialize the touch sensor time base
	HAL_TIM_Base_Start_IT(&htim13);
	// initialize the shA timer
	__HAL_TIM_ENABLE_IT(&htim16, TIM_IT_UPDATE);
	// initialize the shB timer
	__HAL_TIM_ENABLE_IT(&htim17, TIM_IT_UPDATE);


}
