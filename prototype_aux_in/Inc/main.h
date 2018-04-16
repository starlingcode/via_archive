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
#include "eeprom.h"
#include "user_interface.h"

// uncommment to define a version compatible with rev2 (black PCB) boards
#define _BUILD_REV_2

#define time2Knob (ADCReadings2[0] & 0b11111111111111111111111111111111)
#define morphKnob (ADCReadings2[1] & 0b11111111111111111111111111110000)
#define time1CV ADCReadings1[0]
#define time2CV ADCReadings1[1]
#define morphCV (ADCReadings1[2] & 0b1111111111111111111111111100000)
#define time1Knob ADCReadings3[0]

//#define time2Knob 3000
//#define morphKnob 2000
//#define time1CV 2000
//#define time2CV 2000
//#define morphCV 2000
//#define time1Knob 3000

#define DOWNSENSOR MyTKeys[0].p_Data->StateId
#define LOOPSENSOR MyTKeys[1].p_Data->StateId
#define TRIGSENSOR MyTKeys[2].p_Data->StateId
#define FREQSENSOR MyTKeys[3].p_Data->StateId
#define SHSENSOR MyTKeys[4].p_Data->StateId
#define UPSENSOR MyTKeys[5].p_Data->StateId

#define PRESSED TSL_STATEID_DETECT
#define RELEASED TSL_STATEID_RELEASE

enum speedTypes {audio, env, seq};
enum loopTypes {noloop, looping};
enum trigModeTypes {noretrigger, hardsync, nongatedretrigger, gated, pendulum, pendulum2};
enum sampleHoldModeTypes {nosampleandhold, a, b, ab, antidecimate, decimate};
enum logicOutATypes {triggerA, gateA, deltaA};
enum logicOutBTypes {triggerB, gateB, deltaB};
enum drumModeTypes {APM, AM, A, M, PM, P};

// UI signals
enum
{	NULL_SIG,     // Null signal, all state functions should ignore this signal and return their parent state or NONE if it's the top level state
	ENTRY_SIG,    // Entry signal, a state function should perform its entry actions (if any)
	EXIT_SIG,	  // Exit signal, a state function should pEntry signal, a state function should perform its entry actions (if any)erform its exit actions (if any)
	INIT_SIG,     // Just look to global value and initialize, return to default state.  For recalling (presets, memory)
	TIMEOUT_SIG,  // timer timeout
	SENSOR_EVENT_SIG,  // Sensor state machine not busy, can be queried for events
	TSL_ERROR_SIG
};

int familyIndicator;
int flagHolder;

typedef struct buffer512 {
    int buff[512];
    int writeIndex;
}buffer512;

typedef struct buffer256 {
    int buff[256];
    int writeIndex;
}buffer256;

typedef struct buffer32 {
    int buff[32];
    int writeIndex;
}buffer32;

void switchFamily(void) __attribute__((section("ccmram")));
void fillFamilyArray(void) __attribute__((section("ccmram")));
void restoreState(void) __attribute__((section("ccmram")));
static inline void write512(buffer512*,int) __attribute__((section("ccmram")));
static inline int readn512(buffer512*, int) __attribute__((section("ccmram")));
static inline void write256(buffer256*,int) __attribute__((section("ccmram")));
static inline int readn256(buffer256*, int) __attribute__((section("ccmram")));
static inline void write32(buffer32*,int) __attribute__((section("ccmram")));
static inline int readn32(buffer32*, int) __attribute__((section("ccmram")));



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


#define PHASE_STATE 		flagHolder & 0b00000000000000000000000000000001
#define LAST_PHASE_STATE 	flagHolder & 0b00000000000000000000000000000010
#define GATE	 			flagHolder & 0b00000000000000000000000000000100
#define RUNTIME_DISPLAY 	flagHolder & 0b00000000000000000000000000001000
#define UPDATE_PRESCALER 	flagHolder & 0b00000000000000000000000000010000
#define DRUM_MODE	 		flagHolder & 0b00000000000000000000000000100000
#define DRUM_ATTACK 		flagHolder & 0b00000000000000000000000001000000
#define DRUM_RELEASE	 	flagHolder & 0b00000000000000000000000010000000
#define PITCH_MOD 			flagHolder & 0b00000000000000000000000100000000
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
#define BANDLIMIT		 	flagHolder & 0b00000001000000000000000000000000
#define CLEARBUFFER		 	flagHolder & 0b00000010000000000000000000000000


#define SET_PHASE_STATE 		flagHolder |= 0b00000000000000000000000000000001
#define SET_LAST_PHASE_STATE 	flagHolder |= 0b00000000000000000000000000000010
#define SET_GATE	 			flagHolder |= 0b00000000000000000000000000000100
#define SET_RUNTIME_DISPLAY 	flagHolder |= 0b00000000000000000000000000001000
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
#define SET_BANDLIMIT		 	flagHolder |= 0b00000001000000000000000000000000
#define SET_CLEARBUFFER		 	flagHolder |= 0b00000010000000000000000000000000


#define CLEAR_PHASE_STATE 		flagHolder &= 0b11111111111111111111111111111110
#define CLEAR_LAST_PHASE_STATE 	flagHolder &= 0b11111111111111111111111111111101
#define CLEAR_GATE	 			flagHolder &= 0b11111111111111111111111111111011
#define CLEAR_RUNTIME_DISPLAY 	flagHolder &= 0b11111111111111111111111111110111
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
#define CLEAR_BANDLIMIT			flagHolder &= 0b11111110111111111111111111111111
#define CLEAR_CLEARBUFFER		flagHolder &= 0b11111101111111111111111111111111


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
