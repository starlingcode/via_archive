/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * Copyright (c) 2018 STMicroelectronics International N.V. 
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H__
#define __MAIN_H__

/* Includes ------------------------------------------------------------------*/

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private define ------------------------------------------------------------*/

#define A_LOGIC_Pin GPIO_PIN_13
#define A_LOGIC_GPIO_Port GPIOC
#define B_LED_Pin GPIO_PIN_14
#define B_LED_GPIO_Port GPIOC
#define B_LOGIC_Pin GPIO_PIN_15
#define B_LOGIC_GPIO_Port GPIOC
#define CV_1_Pin GPIO_PIN_0
#define CV_1_GPIO_Port GPIOA
#define KNOB_2_Pin GPIO_PIN_1
#define KNOB_2_GPIO_Port GPIOA
#define C_LED_Pin GPIO_PIN_2
#define C_LED_GPIO_Port GPIOA
#define KNOB_3_Pin GPIO_PIN_3
#define KNOB_3_GPIO_Port GPIOA
#define A_LEVEL_Pin GPIO_PIN_4
#define A_LEVEL_GPIO_Port GPIOA
#define B_LEVEL_Pin GPIO_PIN_5
#define B_LEVEL_GPIO_Port GPIOA
#define KNOB_1_Pin GPIO_PIN_6
#define KNOB_1_GPIO_Port GPIOA
#define D_LED_Pin GPIO_PIN_2
#define D_LED_GPIO_Port GPIOB
#define CV_3_Pin GPIO_PIN_8
#define CV_3_GPIO_Port GPIOE
#define CV_2_Pin GPIO_PIN_9
#define CV_2_GPIO_Port GPIOE
#define GROUP_6_SAMPLING_Pin GPIO_PIN_14
#define GROUP_6_SAMPLING_GPIO_Port GPIOB
#define BLUE_LED_Pin GPIO_PIN_8
#define BLUE_LED_GPIO_Port GPIOA
#define GROUP_4_SAMPLING_Pin GPIO_PIN_9
#define GROUP_4_SAMPLING_GPIO_Port GPIOA
#define GREEN_LED_Pin GPIO_PIN_6
#define GREEN_LED_GPIO_Port GPIOF
#define A_LED_Pin GPIO_PIN_7
#define A_LED_GPIO_Port GPIOF
#define RED_LED_Pin GPIO_PIN_5
#define RED_LED_GPIO_Port GPIOB
#define SH_A_Pin GPIO_PIN_8
#define SH_A_GPIO_Port GPIOB
#define SH_B_Pin GPIO_PIN_9
#define SH_B_GPIO_Port GPIOB

// Flag word bit packing macros (stale from a different fimware)

int flagHolder;

#define OSCILLATOR_ACTIVE 	flagHolder & 0b00000000000000000000000000000001
#define LAST_PHASE_STATE 	flagHolder & 0b00000000000000000000000000000010
#define GATE	 			flagHolder & 0b00000000000000000000000000000100
//#define RUNTIME_DISPLAY 	flagHolder & 0b00000000000000000000000000001000
#define UPDATE_PRESCALER 	flagHolder & 0b00000000000000000000000000010000
#define DRUM_MODE_FLAG	 	flagHolder & 0b00000000000000000000000000100000
#define DRUM_ATTACK 		flagHolder & 0b00000000000000000000000001000000
#define DRUM_RELEASE	 	flagHolder & 0b00000000000000000000000010000000
#define PITCH_MOD 			flagHolder & 0b00000000000000000000000100000000
#define MORPH_MOD 			flagHolder & 0b00000000000000000000001000000000
#define AMP_MOD 			flagHolder & 0b00000000000000000000010000000000
#define DRUM_OFF 			flagHolder & 0b00000000000000000000100000000000
#define LAST_CYCLE 			flagHolder & 0b00000000000000000001000000000000
#define HOLD_AT_B 			flagHolder & 0b00000000000000000010000000000000
#define PHASE_STATE 		flagHolder & 0b00000000000000000100000000000000
#define TRIGGER_BUTTON	 	flagHolder & 0b00000000000000001000000000000000
#define DETECT_ON	 		flagHolder & 0b00000000000000010000000000000000
#define AUX_MENU	 		flagHolder & 0b00000000000000100000000000000000
#define GATEA		 		flagHolder & 0b00000000000001000000000000000000
#define TRIGA		 		flagHolder & 0b00000000000010000000000000000000
#define DELTAA		 		flagHolder & 0b00000000000100000000000000000000
#define GATEB		 		flagHolder & 0b00000000001000000000000000000000
#define TRIGB		 		flagHolder & 0b00000000010000000000000000000000
#define DELTAB		 		flagHolder & 0b00000000100000000000000000000000
#define BANDLIMIT		 	flagHolder & 0b00000001000000000000000000000000
#define DRUM_SAFETY		 	flagHolder & 0b00000010000000000000000000000000


#define SET_OSCILLATOR_ACTIVE	flagHolder |= 0b00000000000000000000000000000001
#define SET_LAST_PHASE_STATE 	flagHolder |= 0b00000000000000000000000000000010
#define SET_GATE	 			flagHolder |= 0b00000000000000000000000000000100
//#define SET_RUNTIME_DISPLAY 	flagHolder |= 0b00000000000000000000000000001000
#define SET_UPDATE_PRESCALER 	flagHolder |= 0b00000000000000000000000000010000
#define SET_DRUM_MODE	 		flagHolder |= 0b00000000000000000000000000100000
#define SET_DRUM_ATTACK 		flagHolder |= 0b00000000000000000000000001000000
#define SET_DRUM_RELEASE	 	flagHolder |= 0b00000000000000000000000010000000
#define SET_PITCH_MOD 			flagHolder |= 0b00000000000000000000000100000000
#define SET_MORPH_MOD 			flagHolder |= 0b00000000000000000000001000000000
#define SET_AMP_MOD 			flagHolder |= 0b00000000000000000000010000000000
#define SET_DRUM_OFF 			flagHolder |= 0b00000000000000000000100000000000
#define SET_LAST_CYCLE 			flagHolder |= 0b00000000000000000001000000000000
#define SET_HOLD_AT_B 			flagHolder |= 0b00000000000000000010000000000000
#define SET_PHASE_STATE 		flagHolder |= 0b00000000000000000100000000000000
#define SET_TRIGGER_BUTTON	 	flagHolder |= 0b00000000000000001000000000000000
#define SET_DETECT_ON	 		flagHolder |= 0b00000000000000010000000000000000
#define SET_AUX_MENU			flagHolder |= 0b00000000000000100000000000000000
#define SET_GATEA		 		flagHolder |= 0b00000000000001000000000000000000
#define SET_TRIGA		 		flagHolder |= 0b00000000000010000000000000000000
#define SET_DELTAA		 		flagHolder |= 0b00000000000100000000000000000000
#define SET_GATEB		 		flagHolder |= 0b00000000001000000000000000000000
#define SET_TRIGB		 		flagHolder |= 0b00000000010000000000000000000000
#define SET_DELTAB		 		flagHolder |= 0b00000000100000000000000000000000
#define SET_BANDLIMIT		 	flagHolder |= 0b00000001000000000000000000000000
#define SET_DRUM_SAFETY		 	flagHolder |= 0b00000010000000000000000000000000


#define CLEAR_OSCILLATOR_ACTIVE	flagHolder &= 0b11111111111111111111111111111110
#define CLEAR_LAST_PHASE_STATE 	flagHolder &= 0b11111111111111111111111111111101
#define CLEAR_GATE	 			flagHolder &= 0b11111111111111111111111111111011
//#define CLEAR_RUNTIME_DISPLAY 	flagHolder &= 0b11111111111111111111111111110111
#define CLEAR_UPDATE_PRESCALER 	flagHolder &= 0b11111111111111111111111111101111
#define CLEAR_DRUM_MODE 		flagHolder &= 0b11111111111111111111111111011111
#define CLEAR_DRUM_ATTACK	 	flagHolder &= 0b11111111111111111111111110111111
#define CLEAR_DRUM_RELEASE 		flagHolder &= 0b11111111111111111111111101111111
#define CLEAR_PITCH_MOD 		flagHolder &= 0b11111111111111111111111011111111
#define CLEAR_MORPH_MOD 		flagHolder &= 0b11111111111111111111110111111111
#define CLEAR_AMP_MOD 			flagHolder &= 0b11111111111111111111101111111111
#define RESET_DRUM_OFF 			flagHolder &= 0b11111111111111111111011111111111
#define CLEAR_LAST_CYCLE 		flagHolder &= 0b11111111111111111110111111111111
#define CLEAR_HOLD_AT_B 		flagHolder &= 0b11111111111111111101111111111111
#define CLEAR_PHASE_STATE		 flagHolder &= 0b11111111111111111011111111111111
#define CLEAR_TRIGGER_BUTTON	flagHolder &= 0b11111111111111110111111111111111
#define CLEAR_DETECT_ON			flagHolder &= 0b11111111111111101111111111111111
#define CLEAR_AUX_MENU			flagHolder &= 0b11111111111111011111111111111111
#define CLEAR_GATEA				flagHolder &= 0b11111111111110111111111111111111
#define CLEAR_TRIGA				flagHolder &= 0b11111111111101111111111111111111
#define CLEAR_DELTAA			flagHolder &= 0b11111111111011111111111111111111
#define CLEAR_GATEB				flagHolder &= 0b11111111110111111111111111111111
#define CLEAR_TRIGB				flagHolder &= 0b11111111101111111111111111111111
#define CLEAR_DELTAB			flagHolder &= 0b11111111011111111111111111111111
#define CLEAR_BANDLIMIT			flagHolder &= 0b11111110111111111111111111111111
#define CLEAR_DRUM_SAFETY		flagHolder &= 0b11111101111111111111111111111111


/* ########################## Assert Selection ############################## */
/**
  * @brief Uncomment the line below to expanse the "assert_param" macro in the 
  *        HAL drivers code
  */
/* #define USE_FULL_ASSERT    1U */

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
 extern "C" {
#endif
void _Error_Handler(char *, int);

#define Error_Handler() _Error_Handler(__FILE__, __LINE__)
#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
