#ifndef REV5_HARDWARE_IO
#define REV5_HARDWARE_IO

#include "main.h"

/*
 * ADC Setup
 */

// initialize the arrays that will be used by DMA to store our Knob and CV values

uint32_t slowADCReadings[4];
int16_t fastADC1Readings[1];
int16_t fastADC2Readings[1];

// macros for DMA array (change to array name?)

#define knob2 slowADCReadings[3]
#define knob3 slowADCReadings[1]
#define knob1 slowADCReadings[2]
#define cv1 (4095 - slowADCReadings[0])
#define cv2 ((-fastADC1Readings[0] + 32768) >> 4)
#define cv3 ((-fastADC2Readings[0] + 32768) >> 4)

/**
 * Hardware IO Macros
 */

// Static GPIO handling functions

// LEDs

#define SET_RED_LED(X) __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, X);
#define SET_GREEN_LED(X) __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_4, X);
#define SET_BLUE_LED(X) __HAL_TIM_SET_COMPARE(&htim5, TIM_CHANNEL_1, X);

#define LEDB_ON GPIOC->BSRR = (uint32_t)GPIO_PIN_14;
#define LEDB_OFF GPIOC->BRR = (uint32_t)GPIO_PIN_14;

#define LEDA_ON GPIOF->BSRR = (uint32_t)GPIO_PIN_7;
#define LEDA_OFF GPIOF->BRR = (uint32_t)GPIO_PIN_7;

#define LEDC_ON GPIOA->BSRR = (uint32_t)GPIO_PIN_2;
#define LEDC_OFF GPIOA->BRR = (uint32_t)GPIO_PIN_2;

#define LEDD_ON GPIOB->BSRR = (uint32_t)GPIO_PIN_2;
#define LEDD_OFF GPIOB->BRR = (uint32_t)GPIO_PIN_2;

// Logic outs

#define ALOGIC_HIGH GPIOC->BRR = (uint32_t)GPIO_PIN_13;
#define ALOGIC_LOW GPIOC->BSRR = (uint32_t)GPIO_PIN_13;

#define BLOGIC_HIGH GPIOC->BRR = (uint32_t)GPIO_PIN_15;
#define BLOGIC_LOW GPIOC->BSRR = (uint32_t)GPIO_PIN_15;

#define REV2_GATE_HIGH GPIOA->BRR = (uint32_t)GPIO_PIN_11;
#define REV2_GATE_LOW GPIOA->BSRR = (uint32_t)GPIO_PIN_11;

#define EXPAND_LOGIC_HIGH GPIOA->BRR = (uint32_t)GPIO_PIN_12;
#define EXPAND_LOGIC_LOW GPIOA->BSRR = (uint32_t)GPIO_PIN_12;


// Sample and holds

#define SH_A_SAMPLE GPIOB->BRR = (uint32_t)GPIO_PIN_8;
#define SH_A_TRACK GPIOB->BSRR = (uint32_t)GPIO_PIN_8;

#define SH_B_SAMPLE GPIOB->BRR = (uint32_t)GPIO_PIN_9;
#define SH_B_TRACK GPIOB->BSRR = (uint32_t)GPIO_PIN_9;

// Variable GPIO handling functions

#define SET_A_B_LOGIC(X) GPIOC->BSRR = X;

#define ALOGIC_HIGH_MASK ((uint32_t)GPIO_PIN_13 << 16)
#define ALOGIC_LOW_MASK (uint32_t)GPIO_PIN_13
#define BLOGIC_HIGH_MASK ((uint32_t)GPIO_PIN_15 << 16)
#define BLOGIC_LOW_MASK (uint32_t)GPIO_PIN_15

#define SET_EXPAND_LOGIC(X) GPIOA->BSRR = X;

#define EXPAND_LOGIC_HIGH_MASK ((uint32_t)GPIO_PIN_12 << 16)
#define EXPAND_LOGIC_LOW_MASK (uint32_t)GPIO_PIN_12

#define SET_SH(X) GPIOB->BSRR = X;

#define SH_B_SAMPLE_MASK ((uint32_t)GPIO_PIN_9 << 16)
#define SH_B_TRACK_MASK (uint32_t)GPIO_PIN_9
#define SH_A_SAMPLE_MASK ((uint32_t)GPIO_PIN_8 << 16)
#define SH_A_TRACK_MASK (uint32_t)GPIO_PIN_8

#define SET_LEDA(X) GPIOF->BSRR = X;

#define GPIO_NOP 0

static inline void setLogicOutputs(uint32_t logicA, uint32_t logicB, uint32_t logicExpander, uint32_t shA, uint32_t shB) {

	// LEDA_HIGH_MASK -> SH_A_SAMPLE_MASK >> 16 >> 1 (pin 8 to pin 7, F)
	// LEDB_HIGH_MASK -> SH_B_SAMPLE_MASK >> 16 << 5 (pin 9 to pin 14, C)
	// LEDC_HIGH_MASK -> ALOGIC_HIGH_MASK >> 16 >> 11 (pin 13 to pin 2, A)
	// LEDD_HIGH_MASK -> BLOGIC_HIGH_MASK >> 16 >> 13 (pin 15 to pin 2, B)

	#define LEDA_MASK (__ROR(shA, 16) >> 1)
	#define LEDB_MASK (__ROR(shB, 16) << 5)
	#define LEDC_MASK (__ROR(logicA, 16) >> 11)
	#define LEDD_MASK (__ROR(logicB, 16) >> 13)

	//combine the mask variables for a shared GPIO group with a bitwise or
	SET_A_B_LOGIC(logicA | logicB | LEDB_MASK);

	SET_EXPAND_LOGIC(logicExpander | LEDC_MASK);

	SET_SH(shA | shB | LEDD_MASK);

	SET_LEDA(LEDA_MASK);

}

static inline void setLogicOutputsNoLEDs(uint32_t logicA, uint32_t logicExpander, uint32_t shA, uint32_t shB) {

	// LEDA_HIGH_MASK -> SH_A_SAMPLE_MASK >> 16 >> 1 (pin 8 to pin 7, F)
	// LEDB_HIGH_MASK -> SH_B_SAMPLE_MASK >> 16 << 5 (pin 9 to pin 14, C)
	// LEDC_HIGH_MASK -> ALOGIC_HIGH_MASK >> 16 >> 11 (pin 13 to pin 2, A)
	// LEDD_HIGH_MASK -> BLOGIC_HIGH_MASK >> 16 >> 13 (pin 15 to pin 2, B)

	#define LEDA_MASK (__ROR(shA, 16) >> 1)
	#define LEDB_MASK (__ROR(shB, 16) << 5)
	#define LEDC_MASK (__ROR(logicA, 16) >> 11)
	#define LEDD_MASK (__ROR(logicB, 16) >> 13)

	//combine the mask variables for a shared GPIO group with a bitwise or
	SET_A_B_LOGIC(logicA);

	SET_EXPAND_LOGIC(logicExpander);

	SET_SH(shA | shB);

}


// DAC register address

#define DAC1_ADDR     1073771528
#define DAC2_ADDR     1073771540
#define DAC3_ADDR     1073780744

#define WRITE_DAC1(X) ((*(volatile uint32_t *) DAC1_ADDR) = X);
#define WRITE_DAC2(X) ((*(volatile uint32_t *) DAC2_ADDR) = X);
#define WRITE_DAC3(X) ((*(volatile uint32_t *) DAC3_ADDR) = X);

// Trigger input and button "high" (inverted in hardware)

#define TRIGGER_RISING_EDGE ((GPIOA->IDR & GPIO_PIN_15) == (uint32_t) GPIO_PIN_RESET)
#define EXPANDER_RISING_EDGE ((GPIOA->IDR & GPIO_PIN_11) == (uint32_t) GPIO_PIN_RESET)
#define EXPANDER_BUTTON_PRESSED ((GPIOB->IDR & GPIO_PIN_1) == (uint32_t) GPIO_PIN_RESET)

/*
 * Touch sensors
 */

#define BUTTON2SENSOR MyTKeys[0].p_Data->StateId
#define BUTTON1SENSOR MyTKeys[1].p_Data->StateId
#define BUTTON3SENSOR MyTKeys[2].p_Data->StateId
#define BUTTON4SENSOR MyTKeys[3].p_Data->StateId
#define BUTTON6SENSOR MyTKeys[4].p_Data->StateId
#define BUTTON5SENSOR MyTKeys[5].p_Data->StateId

#define PRESSED TSL_STATEID_DETECT
#define RELEASED TSL_STATEID_RELEASE


#endif
