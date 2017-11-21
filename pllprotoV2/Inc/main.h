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


enum pllTypes {none, true, catch, hardSync};

enum controlSchemes {gateLength, knobCV};

enum scaleTypes {rhythms, pitches};

enum sampleHoldModeTypes {nosampleandhold, a, b, ab, antidecimate, decimate};

int (*attackTime) (void);
int (*releaseTime) (void);

int calcTime1Env(void);
int calcTime2Env(void);
int calcTime1Seq(void);
int calcTime2Seq(void);



#define BUFF_SIZE 8
#define BUFF_SIZE_MASK (BUFF_SIZE-1)

typedef struct buffer{
    int buff[BUFF_SIZE];
    int writeIndex;
}buffer;

void write(buffer*,int);
int readn(buffer*, int);



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

/* USER CODE BEGIN Private defines */
#define EOA_JACK_HIGH GPIOC->BRR = (uint32_t)GPIO_PIN_13;
#define EOA_JACK_LOW GPIOC->BSRR = (uint32_t)GPIO_PIN_13;

#define EOA_GATE_HIGH GPIOA->BRR = (uint32_t)GPIO_PIN_11;
#define EOA_GATE_LOW GPIOA->BSRR = (uint32_t)GPIO_PIN_11;

#define EOR_JACK_HIGH GPIOC->BRR = (uint32_t)GPIO_PIN_15;
#define EOR_JACK_LOW GPIOC->BSRR = (uint32_t)GPIO_PIN_15;

#define EOR_GATE_HIGH GPIOA->BRR = (uint32_t)GPIO_PIN_12;
#define EOR_GATE_LOW GPIOA->BSRR = (uint32_t)GPIO_PIN_12;

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


int flagHolder;

#define PHASE_STATE 		flagHolder & 0b00000000000000000000000000000001
#define LAST_PHASE_STATE 	flagHolder & 0b00000000000000000000000000000010
#define CATCH_UP 			flagHolder & 0b00000000000000000000000000000100
#define RGB_ON 				flagHolder & 0b00000000000000000000000000001000
#define UPDATE_PRESCALER 	flagHolder & 0b00000000000000000000000000010000
#define DRUM_MODE_ON 		flagHolder & 0b00000000000000000000000000100000
#define DRUM_ATTACK_ON 		flagHolder & 0b00000000000000000000000001000000
#define DRUM_RELEASE_ON 	flagHolder & 0b00000000000000000000000010000000
#define PITCH_ON 			flagHolder & 0b00000000000000000000000100000000
#define MORPH_ON 			flagHolder & 0b00000000000000000000001000000000
#define AMP_ON 				flagHolder & 0b00000000000000000000010000000000
#define DRUM_OFF 			flagHolder & 0b00000000000000000000100000000000
#define LAST_CYCLE 			flagHolder & 0b00000000000000000001000000000000
#define HOLD_AT_B 			flagHolder & 0b00000000000000000010000000000000
#define OSCILLATOR_ACTIVE 	flagHolder & 0b00000000000000000100000000000000
#define TRIGGER_BUTTON	 	flagHolder & 0b00000000000000001000000000000000


#define SET_PHASE_STATE 		flagHolder |= 0b00000000000000000000000000000001
#define SET_LAST_PHASE_STATE 	flagHolder |= 0b00000000000000000000000000000010
#define SET_CATCH_UP 			flagHolder |= 0b00000000000000000000000000000100
#define SET_RGB_ON 				flagHolder |= 0b00000000000000000000000000001000
#define SET_UPDATE_PRESCALER 	flagHolder |= 0b00000000000000000000000000010000
#define SET_DRUM_MODE_ON 		flagHolder |= 0b00000000000000000000000000100000
#define SET_DRUM_ATTACK_ON 		flagHolder |= 0b00000000000000000000000001000000
#define SET_DRUM_RELEASE_ON 	flagHolder |= 0b00000000000000000000000010000000
#define SET_PITCH_ON 			flagHolder |= 0b00000000000000000000000100000000
#define SET_MORPH_ON 			flagHolder |= 0b00000000000000000000001000000000
#define SET_AMP_ON 				flagHolder |= 0b00000000000000000000010000000000
#define SET_DRUM_OFF 			flagHolder |= 0b00000000000000000000100000000000
#define SET_LAST_CYCLE 			flagHolder |= 0b00000000000000000001000000000000
#define SET_HOLD_AT_B 			flagHolder |= 0b00000000000000000010000000000000
#define SET_OSCILLATOR_ACTIVE 	flagHolder |= 0b00000000000000000100000000000000
#define SET_TRIGGER_BUTTON	 	flagHolder |= 0b00000000000000001000000000000000

#define RESET_PHASE_STATE 		flagHolder &= 0b11111111111111111111111111111110
#define RESET_LAST_PHASE_STATE 	flagHolder &= 0b11111111111111111111111111111101
#define RESET_CATCH_UP 			flagHolder &= 0b11111111111111111111111111111011
#define RESET_RGB_ON 			flagHolder &= 0b11111111111111111111111111110111
#define RESET_UPDATE_PRESCALER 	flagHolder &= 0b11111111111111111111111111101111
#define RESET_DRUM_MODE_ON 		flagHolder &= 0b11111111111111111111111111011111
#define RESET_DRUM_ATTACK_ON 	flagHolder &= 0b11111111111111111111111110111111
#define RESET_DRUM_RELEASE_ON 	flagHolder &= 0b11111111111111111111111101111111
#define RESET_PITCH_ON 			flagHolder &= 0b11111111111111111111111011111111
#define RESET_MORPH_ON 			flagHolder &= 0b11111111111111111111110111111111
#define RESET_AMP_ON 			flagHolder &= 0b11111111111111111111101111111111
#define RESET_DRUM_OFF 			flagHolder &= 0b11111111111111111111011111111111
#define RESET_LAST_CYCLE 		flagHolder &= 0b11111111111111111110111111111111
#define RESET_HOLD_AT_B 		flagHolder &= 0b11111111111111111101111111111111
#define RESET_OSCILLATOR_ACTIVE flagHolder &= 0b11111111111111111011111111111111
#define RESET_TRIGGER_BUTTON	flagHolder &= 0b11111111111111110111111111111111

#define TOGGLE_GATE_ON 			flagHolder ^= 0b00000000000000000000000000000100

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
