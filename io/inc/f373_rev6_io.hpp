#ifndef REV5_HARDWARE_IO
#define REV5_HARDWARE_IO


#include "main.h"
#include "stm32f3xx_hal.h"

/**
 * Hardware IO Macros
 */

#ifdef __cplusplus
extern "C" {
#endif

// red pwm timer
extern TIM_HandleTypeDef htim3;
// blue pwm timer
extern TIM_HandleTypeDef htim4;
// green pwm timer
extern TIM_HandleTypeDef htim5;

// UI timer
extern TIM_HandleTypeDef htim7;

//#define SET_RED_LED(X) __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, X);
//#define SET_GREEN_LED(X) __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_4, X);
//#define SET_BLUE_LED(X) __HAL_TIM_SET_COMPARE(&htim5, TIM_CHANNEL_1, X);


extern ADC_HandleTypeDef hadc1;
extern DAC_HandleTypeDef hdac1;
extern DAC_HandleTypeDef hdac2;
extern SDADC_HandleTypeDef hsdadc1;
extern SDADC_HandleTypeDef hsdadc2;

#ifdef __cplusplus
}
#endif

#define GPIO_NOP 0

#define ALOGIC_LOW_MASK (uint32_t)GPIO_PIN_13
#define EXPAND_LOGIC_LOW_MASK (uint32_t)GPIO_PIN_12
#define SH_A_TRACK_MASK (uint32_t)GPIO_PIN_8
#define SH_B_TRACK_MASK (uint32_t)GPIO_PIN_9

#define ALOGIC_HIGH_MASK ((uint32_t)GPIO_PIN_13 << 16)
#define EXPAND_LOGIC_HIGH_MASK ((uint32_t)GPIO_PIN_12 << 16)
#define SH_A_SAMPLE_MASK ((uint32_t)GPIO_PIN_8 << 16)
#define SH_B_SAMPLE_MASK ((uint32_t)GPIO_PIN_9 << 16)

#define GET_ALOGIC_MASK(X) (ALOGIC_LOW_MASK << (16*(X)))
#define GET_EXPAND_LOGIC_MASK(X) (EXPAND_LOGIC_LOW_MASK << (16*(X)))
#define GET_SH_A_MASK(X) (SH_A_TRACK_MASK << (16*(X)))
#define GET_SH_B_MASK(X) (SH_B_TRACK_MASK << (16*(X)))

#define SET_BLUE_LED_ONOFF(X) GPIOA->BSRR |= ((uint32_t)GPIO_PIN_8 << (16 * !X))


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
