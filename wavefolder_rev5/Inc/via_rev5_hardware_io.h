#ifndef REV5_HARDWARE_IO
#define REV5_HARDWARE_IO

#include "main.h"

/*
 * ADC Setup
 */

// initialize the arrays that will be used by DMA to store our Knob and CV values

uint32_t slowADCReadings[4];
uint32_t fastADC1Readings[1];
uint32_t fastADC2Readings[1];

// macros for DMA array (change to array name?)

#define knob2 (slowADCReadings[3] & 0b111111111100)
#define knob3 (slowADCReadings[1] & 0b111111111100)
#define knob1 (slowADCReadings[2] & 0b111111111100)
#define cv1 slowADCReadings[0]
#define cv2 (fastADC1Readings[0] >> 1)
#define cv3 (fastADC2Readings[0] >> 1)


/**
 * Hardware IO Macros
 */

// Logic outs

#define BLOGIC_HIGH GPIOC->BRR = (uint32_t)GPIO_PIN_15;
#define BLOGIC_LOW GPIOC->BSRR = (uint32_t)GPIO_PIN_15;

#define REV2_GATE_HIGH GPIOA->BRR = (uint32_t)GPIO_PIN_11;
#define REV2_GATE_LOW GPIOA->BSRR = (uint32_t)GPIO_PIN_11;

#define ALOGIC_HIGH GPIOC->BRR = (uint32_t)GPIO_PIN_13;
#define ALOGIC_LOW GPIOC->BSRR = (uint32_t)GPIO_PIN_13;

#define EXPAND_GATE_HIGH GPIOA->BRR = (uint32_t)GPIO_PIN_12;
#define EXPAND_GATE_LOW GPIOA->BSRR = (uint32_t)GPIO_PIN_12;

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

// Sample and holds

#define SH_A_SAMPLE GPIOB->BRR = (uint32_t)GPIO_PIN_8;
#define SH_A_TRACK GPIOB->BSRR = (uint32_t)GPIO_PIN_8;

#define SH_B_SAMPLE GPIOB->BRR = (uint32_t)GPIO_PIN_9;
#define SH_B_TRACK GPIOB->BSRR = (uint32_t)GPIO_PIN_9;

// DAC register address

#define DAC1_ADDR     1073771528
#define DAC2_ADDR     1073771540

#define WRITE_DAC1(X) ((*(volatile uint32_t *) DAC1_ADDR) = X);
#define WRITE_DAC2(X) ((*(volatile uint32_t *) DAC2_ADDR) = X);

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
