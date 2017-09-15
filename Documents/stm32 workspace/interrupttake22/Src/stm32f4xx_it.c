/**
  ******************************************************************************
  * @file    stm32f4xx_it.c
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
#include "stm32f4xx_hal.h"
#include "stm32f4xx.h"
#include "stm32f4xx_it.h"

/* USER CODE BEGIN 0 */
#define N 16 /*entries per wavetable */
#define M 3	/*wavetables per family*/

#define sineslope {0,  39,  156,  345, 600, 910, 1264, 1648, 2048, 2447, 2831, 3185, 3495, 3750, 3939, 4056}
#define low {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
#define high {4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095}
#define ramp {0, 256, 512, 768, 1024, 1280, 1536, 1792, 2048, 2304, 2560, 2816, 3072, 3328, 3584, 3840}
uint16_t sine2ramp[2][N] = {sineslope,
							ramp};
uint16_t ramp2sine[2][N] = {ramp,
							sineslope};
/*   [2] triangle  */
const int fs = 48000;
float last = 0;
float freq = 440;
float attacktime = 1;
float decaytime = 1;
float biinterpa = 0;
float biinterpb = 0;
float morph = 0;
float position;
float mirror = N;
float inc;
float interp1;
float interp2;
float interp1b;
float interp2b;
float Lnvalue;
float Rnvalue;
float Ln2value;
float Rn2value;
int Ln;
int Rn;
int Lnm;
int Rnm;
float remain;
volatile int trig = 0;
/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim5;
extern DAC_HandleTypeDef hdac;

/******************************************************************************/
/*            Cortex-M4 Processor Interruption and Exception Handlers         */ 
/******************************************************************************/

/**
* @brief This function handles System tick timer.
*/
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  HAL_SYSTICK_IRQHandler();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F4xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f4xx.s).                    */
/******************************************************************************/

/**
* @brief This function handles TIM2 global interrupt.
*/
void TIM2_IRQHandler(void)
{
  /* USER CODE BEGIN TIM2_IRQn 0 */
	if (trig == 1){
	  if (position > N - 1 && position < 31) {
		  HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1,  DAC_ALIGN_12B_L, interp1b);
	  	   		  	  	  inc = N / (fs * decaytime);
	  	   		   		  position = last + inc;
	  	   		   		  last = position;
	  	   		   		  mirror = 15 - (position - 15);
	  	   		   		  Ln = (int)mirror;
	  	   		   		  Rn = (Ln + 1) % N;
	  	   		   		  Lnm = (int)morph;
	  	   		   		  Rnm = (Lnm + 1) % 1; /* note that there are 3 wavetables in family, this makes the family a ring*/
	  	   		   		  remain = mirror - Ln;
	  	   		   		  Lnvalue = (sine2ramp[Lnm][Ln] << 4);
	  	   		   		  Rnvalue = (sine2ramp[Lnm][Rn] << 4);
	  	   		   		  Ln2value = (sine2ramp[Rnm][Ln] << 4);
	  	   		   		  Rn2value = (sine2ramp[Rnm][Rn] << 4);
	  	   		   		  interp1b = Lnvalue + remain * (Rnvalue - Lnvalue);
	  	   		   		  interp2b = Ln2value + remain * (Rn2value - Ln2value);};

	  if (position <= N - 1) {
		  HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1,  DAC_ALIGN_12B_L, biinterpa);
	  	  	  inc = N / (fs * attacktime);
	   		  position = last + inc;
	   		  last = position;
	   		  Ln = (int)position;
	   		  Rn = (Ln + 1) % N;
	   		  Lnm = (int)morph;
	   		  Rnm = (Lnm + 1) % 1; /* note that there are 3 wavetables in family, this makes the family a ring*/
	   		  remain = position - Ln;
	   		  Lnvalue = (sine2ramp[Lnm][Ln] << 4);
	   		  Rnvalue = (sine2ramp[Lnm][Rn] << 4);
	   		  Ln2value = (sine2ramp[Rnm][Ln] << 4);
	   		  Rn2value = (sine2ramp[Rnm][Rn] << 4);
	   		  interp1 = Lnvalue + remain * (Rnvalue - Lnvalue);
	   		  interp2 = Ln2value + remain * (Rn2value - Ln2value);
	   		  biinterpa = interp1 + (morph - Lnm) * (interp2 - interp1);};


				if (position >= 31) {
	   			  /*position = position - N;*/
	   		  	  trig = 0;
	   		  	position = 0;
				last = 0;};};
  /* USER CODE END TIM2_IRQn 0 */
  HAL_TIM_IRQHandler(&htim2);
  /* USER CODE BEGIN TIM2_IRQn 1 */

  /* USER CODE END TIM2_IRQn 1 */
}

/**
* @brief This function handles TIM5 global interrupt.
*/
void TIM5_IRQHandler(void)
{
  /* USER CODE BEGIN TIM5_IRQn 0 */
	trig = 1;
  /* USER CODE END TIM5_IRQn 0 */
  HAL_TIM_IRQHandler(&htim5);
  /* USER CODE BEGIN TIM5_IRQn 1 */

  /* USER CODE END TIM5_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
