/**
  ******************************************************************************
  * @file    stm32f0xx_it.c
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
#include "stm32f0xx_hal.h"
#include "stm32f0xx.h"
#include "stm32f0xx_it.h"

/* USER CODE BEGIN 0 */
#include "fixmath.h"
#define N 16 /*Entries per wavetable*/
#define M 2 /*Wavetables per family*/

#define sineslope {0,  39,  156,  345, 600, 910, 1264, 1648, 2048, 2447, 2831, 3185, 3495, 3750, 3939, 4056}
#define low {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
#define high {4095, 3500, 3000, 3500, 3900, 3400, 2900, 3100, 3600, 4000, 3500, 3000, 2500, 3000, 3600, 4095}
#define ramp {0, 256, 512, 768, 1024, 1280, 1536, 1792, 2048, 2304, 2560, 2816, 3072, 3328, 3584, 3840}
uint16_t sine2ramp[M][N] = {sineslope,
							ramp};
uint16_t ramp2sine[M][N] = {sineslope,
							ramp};
uint16_t attackfamily[M][N] = {sineslope, high};
uint16_t releasefamily[M][N] = {sineslope, ramp};
const int fs = 48000;
const fix16_t precalc = 81;
fix16_t last = 0;
fix16_t freq = 440;
float attackfreq = 880;
float releasefreq = 880;
float morph = 1;
fix16_t fixmorph;
fix16_t position;
fix16_t mirror;
fix16_t inc;
fix16_t interp1;
fix16_t interp2;
fix16_t biinterp;
fix16_t Lnvalue1;
fix16_t Rnvalue1;
fix16_t Lnvalue2;
fix16_t Rnvalue2;
int Ln;
int Rn;
int Lnm;
int Rnm;
uint16_t wavefrac;
uint16_t morphfrac;
volatile int trig = 0;
uint32_t todac;
void Attack(void);
void Release(void);
extern DAC_HandleTypeDef hdac;
extern TIM_HandleTypeDef htim1;
int benchmark;
int lastcount;
uint32_t ADCReadings[];
/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern DMA_HandleTypeDef hdma_adc;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;

/******************************************************************************/
/*            Cortex-M0 Processor Interruption and Exception Handlers         */ 
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
/* STM32F0xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f0xx.s).                    */
/******************************************************************************/

/**
* @brief This function handles DMA1 channel 1 global interrupt.
*/
void DMA1_Channel1_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Channel1_IRQn 0 */

  /* USER CODE END DMA1_Channel1_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_adc);
  /* USER CODE BEGIN DMA1_Channel1_IRQn 1 */

  /* USER CODE END DMA1_Channel1_IRQn 1 */
}

/**
* @brief This function handles TIM2 global interrupt.
*/
void TIM2_IRQHandler(void)
{
  /* USER CODE BEGIN TIM2_IRQn 0 */

  /* USER CODE END TIM2_IRQn 0 */
  HAL_TIM_IRQHandler(&htim2);
  /* USER CODE BEGIN TIM2_IRQn 1 */
	trig = 1;
  /* USER CODE END TIM2_IRQn 1 */
}

/**
* @brief This function handles TIM3 global interrupt.
*/
void TIM3_IRQHandler(void)
{
  /* USER CODE BEGIN TIM3_IRQn 0 */


  /* USER CODE END TIM3_IRQn 0 */
  HAL_TIM_IRQHandler(&htim3);
  /* USER CODE BEGIN TIM3_IRQn 1 */
  if (trig ==1){
  		if(position < fix16_sub(fix16_from_int(15), inc)) {Attack();}
  		if(position >= fix16_sub(fix16_from_int(15), inc) && position < fix16_from_int(30)) {Release();}
  		if(position >= fix16_from_int(30)) {position = 0, last = 0, biinterp = 0; last = wavefrac;}
  	}
  /* USER CODE END TIM3_IRQn 1 */
}

/* USER CODE BEGIN 1 */
void Attack(void) {
	HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, biinterp);
	inc = fix16_mul(precalc, ADCReadings[0] << 16);
	position = fix16_add(inc, last);
	last = position;
	Ln = (int) (position >> 16);
	Rn = (Ln + 1) % N;
	//fixmorph = fix16_from_float(morph);
	Lnm = (int) (fixmorph >> 16);
	Rnm = (Lnm + 1) % M;
	wavefrac = (uint16_t) position;
	morphfrac = (uint16_t) (ADCReadings[1] << 4);
	Lnvalue1 = attackfamily[Lnm][Ln];
	Rnvalue1 = attackfamily[Lnm][Rn];
	Lnvalue2 = attackfamily[Rnm][Ln];
	Rnvalue2 = attackfamily[Rnm][Rn];
	interp1 = fix16_lerp16(Lnvalue1, Rnvalue1, wavefrac);
	interp2 = fix16_lerp16(Lnvalue2, Rnvalue2, wavefrac);
	biinterp = fix16_lerp16(interp1, interp2, morphfrac);
}
void Release(void) {
	HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, biinterp);
	inc = fix16_mul(precalc, ADCReadings[0] << 16);
	position = fix16_add(inc, last);
	last = position;
	mirror = fix16_sub(fix16_from_int(30), position);
	Ln = (int) (mirror >> 16);
	Rn = (Ln + 1) % N;
	//fixmorph = fix16_from_float(morph);
	Lnm = (int) (fixmorph >> 16);
	Rnm = (Lnm + 1) % M;
	wavefrac = (uint16_t) mirror;
	morphfrac = (uint16_t) (ADCReadings[1] << 4);
	Lnvalue1 = releasefamily[Lnm][Ln];
	Rnvalue1 = releasefamily[Lnm][Rn];
	Lnvalue2 = releasefamily[Rnm][Ln];
	Rnvalue2 = releasefamily[Rnm][Rn];
	interp1 = fix16_lerp16(Lnvalue1, Rnvalue1, wavefrac);
	interp2 = fix16_lerp16(Lnvalue2, Rnvalue2, wavefrac);
	biinterp = fix16_lerp16(interp1, interp2, morphfrac);
}
/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
