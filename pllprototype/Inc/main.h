/**
  ******************************************************************************
  * File Name          : main.h
  * Description        : This file contains the common defines of the application
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H
  /* Includes ------------------------------------------------------------------*/

/* USER CODE BEGIN Includes */

enum scaleModes {row, ratio};

enum controlModes {gatedDutyCycle, knobDutyCycle};

enum phaseLockModes {none, average, hardSync, phaseLock};

enum sampleHoldModes {nosampleandhold, a, b, ab, antidecimate, decimate};

/* USER CODE END Includes */

/* Private define ------------------------------------------------------------*/

#define EOA_Pin GPIO_PIN_13
#define EOA_GPIO_Port GPIOC
#define ATTACK_GATE_Pin GPIO_PIN_14
#define ATTACK_GATE_GPIO_Port GPIOC
#define EOR_Pin GPIO_PIN_15
#define EOR_GPIO_Port GPIOC
#define RELEASE_GATE_Pin GPIO_PIN_0
#define RELEASE_GATE_GPIO_Port GPIOF
#define A_LED_Pin GPIO_PIN_1
#define A_LED_GPIO_Port GPIOF
#define _1v_oct_Pin GPIO_PIN_0
#define _1v_oct_GPIO_Port GPIOA
#define t2_cv_Pin GPIO_PIN_1
#define t2_cv_GPIO_Port GPIOA
#define morph_cv_Pin GPIO_PIN_2
#define morph_cv_GPIO_Port GPIOA
#define resampling_Pin GPIO_PIN_3
#define resampling_GPIO_Port GPIOA
#define manual_t1_Pin GPIO_PIN_6
#define manual_t1_GPIO_Port GPIOA
#define manual_t2_Pin GPIO_PIN_7
#define manual_t2_GPIO_Port GPIOA
#define manual_morph_Pin GPIO_PIN_0
#define manual_morph_GPIO_Port GPIOB
#define Shield_sampling_Pin GPIO_PIN_1
#define Shield_sampling_GPIO_Port GPIOB
#define active_shield_Pin GPIO_PIN_2
#define active_shield_GPIO_Port GPIOB
#define C_LED_Pin GPIO_PIN_10
#define C_LED_GPIO_Port GPIOB
#define TSC_G6_SAMPLING_Pin GPIO_PIN_11
#define TSC_G6_SAMPLING_GPIO_Port GPIOB
#define D_LED_Pin GPIO_PIN_15
#define D_LED_GPIO_Port GPIOB
#define RED_LED_Pin GPIO_PIN_8
#define RED_LED_GPIO_Port GPIOA
#define GREEN_LED_Pin GPIO_PIN_9
#define GREEN_LED_GPIO_Port GPIOA
#define BLUE_LED_Pin GPIO_PIN_10
#define BLUE_LED_GPIO_Port GPIOA
#define B_LED_Pin GPIO_PIN_5
#define B_LED_GPIO_Port GPIOB
#define TSC_G5_SAMPLING_Pin GPIO_PIN_7
#define TSC_G5_SAMPLING_GPIO_Port GPIOB
#define S_H_A_Pin GPIO_PIN_8
#define S_H_A_GPIO_Port GPIOB
#define S_H_B_Pin GPIO_PIN_9
#define S_H_B_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */
#define EOA_JACK_HIGH GPIOC->BRR = (uint32_t)GPIO_PIN_13;
#define EOA_JACK_LOW GPIOC->BSRR = (uint32_t)GPIO_PIN_13;

#define EOA_GATE_HIGH GPIOC->BRR = (uint32_t)GPIO_PIN_14;
#define EOA_GATE_LOW GPIOC->BSRR = (uint32_t)GPIO_PIN_14;

#define EOR_JACK_HIGH GPIOC->BRR = (uint32_t)GPIO_PIN_15;
#define EOR_JACK_LOW GPIOC->BSRR = (uint32_t)GPIO_PIN_15;

#define EOR_GATE_HIGH GPIOF->BRR = (uint32_t)GPIO_PIN_0;
#define EOR_GATE_LOW GPIOF->BSRR = (uint32_t)GPIO_PIN_0;

#define LEDA_ON GPIOF->BSRR = (uint32_t)GPIO_PIN_1;
#define LEDA_OFF GPIOF->BRR = (uint32_t)GPIO_PIN_1;

#define LEDB_ON GPIOB->BSRR = (uint32_t)GPIO_PIN_5;
#define LEDB_OFF GPIOB->BRR = (uint32_t)GPIO_PIN_5;

#define LEDC_ON GPIOB->BSRR = (uint32_t)GPIO_PIN_10;
#define LEDC_OFF GPIOB->BRR = (uint32_t)GPIO_PIN_10;

#define LEDD_ON GPIOB->BSRR = (uint32_t)GPIO_PIN_15;
#define LEDD_OFF GPIOB->BRR = (uint32_t)GPIO_PIN_15;

#define SH_A_SAMPLE GPIOB->BRR = (uint32_t)GPIO_PIN_8;
#define SH_A_TRACK GPIOB->BSRR = (uint32_t)GPIO_PIN_8;

#define SH_B_SAMPLE GPIOB->BRR = (uint32_t)GPIO_PIN_9;
#define SH_B_TRACK GPIOB->BSRR = (uint32_t)GPIO_PIN_9;


#define noteC1 1
#define noteCsharp1 1.05946309436
#define noteD1 1.12246204831
#define noteDsharp1 1.189207115
#define noteE1 1.25992104989
#define noteF1 1.33483985417
#define noteFsharp1 1.41421356237
#define noteG1 1.49830707688
#define noteGsharp1 1.58740105197
#define noteA1 1.68179283051
#define noteAsharp1 1.78179743628
#define noteB1 1.88774862536
#define noteC2 2
#define noteCsharp2 2.11892618872
#define noteD2 2.24492409662
#define noteDsharp2 2.37841423001
#define noteE2 2.51984209979
#define noteF2 2.66967970834
#define noteFsharp2 2.82842712475
#define noteG2 2.99661415375
#define noteGsharp2 3.17480210394
#define noteA2 3.36358566101
#define noteAsharp2 3.56359487256
#define noteB2 3.77549725073
#define noteC3 4
#define noteCsharp3 4.23785237744
#define noteD3 4.48984819324
#define noteDsharp3 4.75682846001
#define noteE3 5.03968419958
#define noteF3 5.33935941668
#define noteFsharp3 5.65685424949
#define noteG3 5.99322830751
#define noteGsharp3 6.34960420787
#define noteA3 6.72717132203
#define noteAsharp3 7.12718974512
#define noteB3 7.55099450145
#define noteC4 8

/* USER CODE END Private defines */

void _Error_Handler(char *, int);

#define Error_Handler() _Error_Handler(__FILE__, __LINE__)

/**
  * @}
  */ 

/**
  * @}
*/ 

#endif /* __MAIN_H */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
