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
#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"
#include "user_interface.h"


// uncommment to define a version compatible with rev2 (black PCB) boards
//#define _BUILD_REV_2

// these enums contain our mode information

enum syncTypes {none, true, hardSync};
enum controlSchemes {root, dutyCycle, FM, phaseMod};
enum scaleTypes {rhythm, arp, voltOct};
enum sampleHoldModeTypes {nosampleandhold, a, b, ab, antidecimate, decimate};
enum logicOutATypes {triggerA, gateA, deltaA, ratioDeltaA, pllClockA};
enum logicOutBTypes {triggerB, gateB, deltaB, ratioDeltaB, pllClockB};
enum autoDutyTypes {autoDutyOn, autoDutyOff};
uint32_t familyIndicator;

// the enum variables to be used are declared here

enum syncTypes button4Mode; // {none, true, hardSync}
enum controlSchemes controlScheme; // {gateLength, knobCV}
enum scaleTypes scaleType; // {rhythm, arp, voltOct};
enum sampleHoldModeTypes sampleHoldMode; // {nosampleandhold, a, b, ab, antidecimate, decimate}
enum logicOutATypes logicOutA; // {triggerA, gateA, deltaA, ratioDeltaA, pllClock};
enum logicOutBTypes logicOutB; // {triggerB, gateB, deltaB, ratioDeltaB, pllClock};
enum autoDutyTypes autoDuty; // {autoDutyOn, autoDutyOff};

volatile int position;
int flagHolder;

// int familyIndicator;
// int holdState;
// int holdLogicOut;
// int eepromStatus;

int (*attackTime) (void);
int (*releaseTime) (void);

void inputCaptureSetup(void);
void switchFamily(void);
void initializeScales(void);

uint32_t ADCReadings1[4];
uint32_t ADCReadings2[2];
uint32_t ADCReadings3[2];

int adcRef;

uint32_t time1CVAverage;
uint32_t time1KnobAverage;
uint32_t time2CVAverage;
uint32_t time2KnobAverage;

/* USER CODE END Includes */

/* Private define ------------------------------------------------------------*/

#define EOA_Pin GPIO_PIN_13
#define EOA_GPIO_Port GPIOC
#define ATTACK_GATE_Pin GPIO_PIN_14
#define ATTACK_GATE_GPIO_Port GPIOC
#define EOR_Pin GPIO_PIN_15
#define EOR_GPIO_Port GPIOC
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

///* USER CODE BEGIN Private defines */
//#define EOA_JACK_HIGH GPIOC->BRR = (uint32_t)GPIO_PIN_13;
//#define EOA_JACK_LOW GPIOC->BSRR = (uint32_t)GPIO_PIN_13;
//
//#define EOA_GATE_HIGH GPIOA->BRR = (uint32_t)GPIO_PIN_11;
//#define EOA_GATE_LOW GPIOA->BSRR = (uint32_t)GPIO_PIN_11;
//
//#define EOR_JACK_HIGH GPIOC->BRR = (uint32_t)GPIO_PIN_15;
//#define EOR_JACK_LOW GPIOC->BSRR = (uint32_t)GPIO_PIN_15;
//
//#define EOR_GATE_HIGH GPIOA->BRR = (uint32_t)GPIO_PIN_12;
//#define EOR_GATE_LOW GPIOA->BSRR = (uint32_t)GPIO_PIN_12;
//
//#define LEDB_ON GPIOC->BSRR = (uint32_t)GPIO_PIN_14;
//#define LEDB_OFF GPIOC->BRR = (uint32_t)GPIO_PIN_14;
//
//#define LEDA_ON GPIOB->BSRR = (uint32_t)GPIO_PIN_5;
//#define LEDA_OFF GPIOB->BRR = (uint32_t)GPIO_PIN_5;
//
//#define LEDC_ON GPIOB->BSRR = (uint32_t)GPIO_PIN_10;
//#define LEDC_OFF GPIOB->BRR = (uint32_t)GPIO_PIN_10;
//
//#define LEDD_ON GPIOB->BSRR = (uint32_t)GPIO_PIN_15;
//#define LEDD_OFF GPIOB->BRR = (uint32_t)GPIO_PIN_15;
//
//#define SH_A_SAMPLE GPIOB->BRR = (uint32_t)GPIO_PIN_8;
//#define SH_A_TRACK GPIOB->BSRR = (uint32_t)GPIO_PIN_8;
//
//#define SH_B_SAMPLE GPIOB->BRR = (uint32_t)GPIO_PIN_9;
//#define SH_B_TRACK GPIOB->BSRR = (uint32_t)GPIO_PIN_9;

#define BLOGIC_HIGH GPIOC->BRR = (uint32_t)GPIO_PIN_13;
#define BLOGIC_LOW GPIOC->BSRR = (uint32_t)GPIO_PIN_13;

#define REV2_GATE_HIGH GPIOA->BRR = (uint32_t)GPIO_PIN_11;
#define REV2_GATE_LOW GPIOA->BSRR = (uint32_t)GPIO_PIN_11;

#define ALOGIC_HIGH GPIOC->BRR = (uint32_t)GPIO_PIN_15;
#define ALOGIC_LOW GPIOC->BSRR = (uint32_t)GPIO_PIN_15;

#define EXPAND_GATE_HIGH GPIOA->BRR = (uint32_t)GPIO_PIN_12;
#define EXPAND_GATE_LOW GPIOA->BSRR = (uint32_t)GPIO_PIN_12;

#define LEDB_ON GPIOC->BSRR = (uint32_t)GPIO_PIN_14;
#define LEDB_OFF GPIOC->BRR = (uint32_t)GPIO_PIN_14;

#define LEDA_ON GPIOB->BSRR = (uint32_t)GPIO_PIN_5;
#define LEDA_OFF GPIOB->BRR = (uint32_t)GPIO_PIN_5;

#define LEDC_ON GPIOB->BSRR = (uint32_t)GPIO_PIN_10;
#define LEDC_OFF GPIOB->BRR = (uint32_t)GPIO_PIN_10;

#define LEDD_ON GPIOB->BSRR = (uint32_t)GPIO_PIN_15;
#define LEDD_OFF GPIOB->BRR = (uint32_t)GPIO_PIN_15;

#define SH_A_SAMPLE GPIOB->BRR = (uint32_t)GPIO_PIN_8;
#define SH_A_TRACK GPIOB->BSRR = (uint32_t)GPIO_PIN_8;

#define SH_B_SAMPLE GPIOB->BRR = (uint32_t)GPIO_PIN_9;
#define SH_B_TRACK GPIOB->BSRR = (uint32_t)GPIO_PIN_9;

#define ClearTimCount(n)           (n.TIMx->CNT = 0)

#define DAC1_ADDR     0x40007408
#define DAC2_ADDR     0x40007414

#define WRITE_DAC1(data) ((*(volatile uint32_t *)DAC1_ADDR) = (val))
#define WRITE_DAC2(data) ((*(volatile uint32_t *)DAC2_ADDR) = (val))

#define BUFF_SIZE 256
#define BUFF_SIZE_MASK (BUFF_SIZE-1)


#define PHASE_STATE 		flagHolder & 0b00000000000000000000000000000001
#define LAST_PHASE_STATE 	flagHolder & 0b00000000000000000000000000000010
#define GATE 				flagHolder & 0b00000000000000000000000000000100
#define RUNTIME_DISPLAY 	flagHolder & 0b00000000000000000000000000001000
#define RATIO_DELTAA		flagHolder & 0b00000000000000000000000000010000
#define RATIO_DELTAB		flagHolder & 0b00000000000000000000000000100000
#define PLL_DIVA	 		flagHolder & 0b00000000000000000000000001000000
#define PLL_DIVB		 	flagHolder & 0b00000000000000000000000010000000
#define CATCH_UP			flagHolder & 0b00000000000000000000000100000000
#define MORPH_MOD 			flagHolder & 0b00000000000000000000001000000000
#define AMP_MOD 			flagHolder & 0b00000000000000000000010000000000
#define DRUM_OFF 			flagHolder & 0b00000000000000000000100000000000
#define LAST_CYCLE 			flagHolder & 0b00000000000000000001000000000000
#define HOLD_AT_B 			flagHolder & 0b00000000000000000010000000000000
#define OSCILLATOR_ACTIVE 	flagHolder & 0b00000000000000000100000000000000
#define TRIGGER_BUTTON	 	flagHolder & 0b00000000000000001000000000000000
#define DETECT_ON	 		flagHolder & 0b00000000000000010000000000000000
#define AUX_MENU	 		flagHolder & 0b00000000000000100000000000000000
#define GATEA		 		flagHolder & 0b00000000000001000000000000000000
#define TRIGA		 		flagHolder & 0b00000000000010000000000000000000
#define DELTAA		 		flagHolder & 0b00000000000100000000000000000000
#define GATEB		 		flagHolder & 0b00000000001000000000000000000000
#define TRIGB		 		flagHolder & 0b00000000010000000000000000000000
#define DELTAB		 		flagHolder & 0b00000000100000000000000000000000
#define AUTODUTY		 	flagHolder & 0b00000001000000000000000000000000
#define NOCLOCK			 	flagHolder & 0b00000010000000000000000000000000
#define EXTPLL			 	flagHolder & 0b00000100000000000000000000000000


#define SET_PHASE_STATE 		flagHolder |= 0b00000000000000000000000000000001
#define SET_LAST_PHASE_STATE 	flagHolder |= 0b00000000000000000000000000000010
#define SET_GATE 				flagHolder |= 0b00000000000000000000000000000100
#define SET_RUNTIME_DISPLAY 	flagHolder |= 0b00000000000000000000000000001000
#define SET_RATIO_DELTAA	 	flagHolder |= 0b00000000000000000000000000010000
#define SET_RATIO_DELTAB 		flagHolder |= 0b00000000000000000000000000100000
#define SET_PLL_DIVA			flagHolder |= 0b00000000000000000000000001000000
#define SET_PLL_DIVB		 	flagHolder |= 0b00000000000000000000000010000000
#define SET_CATCH_UP 			flagHolder |= 0b00000000000000000000000100000000
#define SET_MORPH_MOD 			flagHolder |= 0b00000000000000000000001000000000
#define SET_AMP_MOD 			flagHolder |= 0b00000000000000000000010000000000
#define SET_DRUM_OFF 			flagHolder |= 0b00000000000000000000100000000000
#define SET_LAST_CYCLE 			flagHolder |= 0b00000000000000000001000000000000
#define SET_HOLD_AT_B 			flagHolder |= 0b00000000000000000010000000000000
#define SET_OSCILLATOR_ACTIVE 	flagHolder |= 0b00000000000000000100000000000000
#define SET_TRIGGER_BUTTON	 	flagHolder |= 0b00000000000000001000000000000000
#define SET_DETECT_ON	 		flagHolder |= 0b00000000000000010000000000000000
#define SET_AUX_MENU			flagHolder |= 0b00000000000000100000000000000000
#define SET_GATEA		 		flagHolder |= 0b00000000000001000000000000000000
#define SET_TRIGA		 		flagHolder |= 0b00000000000010000000000000000000
#define SET_DELTAA		 		flagHolder |= 0b00000000000100000000000000000000
#define SET_GATEB		 		flagHolder |= 0b00000000001000000000000000000000
#define SET_TRIGB		 		flagHolder |= 0b00000000010000000000000000000000
#define SET_DELTAB		 		flagHolder |= 0b00000000100000000000000000000000
#define SET_AUTODUTY	 		flagHolder |= 0b00000001000000000000000000000000
#define SET_NOCLOCK		 		flagHolder |= 0b00000010000000000000000000000000
#define SET_EXTPLL		 		flagHolder |= 0b00000100000000000000000000000000


#define CLEAR_PHASE_STATE 		flagHolder &= 0b11111111111111111111111111111110
#define CLEAR_LAST_PHASE_STATE 	flagHolder &= 0b11111111111111111111111111111101
#define CLEAR_GATE 				flagHolder &= 0b11111111111111111111111111111011
#define CLEAR_RUNTIME_DISPLAY 	flagHolder &= 0b11111111111111111111111111110111
#define CLEAR_RATIO_DELTAA	 	flagHolder &= 0b11111111111111111111111111101111
#define CLEAR_RATIO_DELTAB 		flagHolder &= 0b11111111111111111111111111011111
#define CLEAR_PLL_DIVA			flagHolder &= 0b11111111111111111111111110111111
#define CLEAR_PLL_DIVB		 	flagHolder &= 0b11111111111111111111111101111111
#define CLEAR_CATCH_UP			flagHolder &= 0b11111111111111111111111011111111
#define CLEAR_MORPH_MOD 		flagHolder &= 0b11111111111111111111110111111111
#define CLEAR_AMP_MOD 			flagHolder &= 0b11111111111111111111101111111111
#define RESET_DRUM_OFF 			flagHolder &= 0b11111111111111111111011111111111
#define CLEAR_LAST_CYCLE 		flagHolder &= 0b11111111111111111110111111111111
#define CLEAR_HOLD_AT_B 		flagHolder &= 0b11111111111111111101111111111111
#define CLEAR_OSCILLATOR_ACTIVE flagHolder &= 0b11111111111111111011111111111111
#define CLEAR_TRIGGER_BUTTON	flagHolder &= 0b11111111111111110111111111111111
#define CLEAR_DETECT_ON			flagHolder &= 0b11111111111111101111111111111111
#define CLEAR_AUX_MENU			flagHolder &= 0b11111111111111011111111111111111
#define CLEAR_GATEA				flagHolder &= 0b11111111111110111111111111111111
#define CLEAR_TRIGA				flagHolder &= 0b11111111111101111111111111111111
#define CLEAR_DELTAA			flagHolder &= 0b11111111111011111111111111111111
#define CLEAR_GATEB				flagHolder &= 0b11111111110111111111111111111111
#define CLEAR_TRIGB				flagHolder &= 0b11111111101111111111111111111111
#define CLEAR_DELTAB			flagHolder &= 0b11111111011111111111111111111111
#define CLEAR_AUTODUTY			flagHolder &= 0b11111110111111111111111111111111
#define CLEAR_NOCLOCK			flagHolder &= 0b11111101111111111111111111111111
#define CLEAR_EXTPLL			flagHolder &= 0b11111011111111111111111111111111


#define TOGGLE_GATE 			flagHolder ^= 0b00000000000000000000000000000100

#define REMEMBER_PHASE_STATE	flagHolder ^= (-((PHASE_STATE) ^ flagHolder) & (1UL << 1))

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
