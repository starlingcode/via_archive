#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"
#include "scales.h"
#include "interrupt_functions.h"


#include "tables.h"
#include "main.h"

int expoTable[4096] = expotable10oct;

// mode indicators, determined in the main loop
enum syncTypes syncMode; // {none, true, hardSync, catch}
enum controlSchemes controlScheme; // {gateLength, knobCV}
enum scaleTypes scaleType; // {rhythms, pitches}
enum sampleHoldModeTypes sampleHoldMode;

extern TIM_HandleTypeDef htim15;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim16;

extern int currentScale;

void inputCapture(void) {

	if ((GPIOA->IDR & GPIO_PIN_15) == (uint32_t) GPIO_PIN_RESET) {
		// get the timer value that which was reset on last rising edge
		periodCount = __HAL_TIM_GET_COUNTER(&htim2);

		// reset the timer value
		__HAL_TIM_SET_COUNTER(&htim2, 0);

		generateFrequency();

		CLEAR_NOCLOCK;

	}
	else {
		// get the timer value that which was reset on last rising edge
		if (AUTODUTY) {
			gateOnCount = __HAL_TIM_GET_COUNTER(&htim2);
		} else {
			gateOnCount = periodCount >> 1;
		}
	}
}

void inputCaptureSetup(void) {
	attackInc = 100;
	releaseInc = 100;
	gateOnCount = 10000;
	periodCount = 10000;
	incSign = 1;
}

void tapTempo(void) {

	if (TRIGGER_BUTTON) {
		if (!(NOCLOCK)) {
			SET_NOCLOCK;
		} else {
		periodCount = __HAL_TIM_GET_COUNTER(&htim16) << 12;
		// reset the timer value
		__HAL_TIM_SET_COUNTER(&htim16, 0);
		TIM16->CR1 |= TIM_CR1_CEN;

		if (periodCount > 0) {
			gateOnCount = periodCount >> 1;
			generateFrequency();
		}
		}

	} else {
		//gateOnCount = __HAL_TIM_GET_COUNTER(&htim16) << 12;
	}

}

void generateFrequency(void) {

	int pllNudge = 0;
	static uint32_t pllCounter;
	uint32_t fracMultiplier;
	uint32_t intMultiplier;
	uint32_t gcd;
	uint32_t noteIndex;
	uint32_t rootIndex;
	uint32_t multKey;
	static uint32_t lastMultiplier;
	Scale scale;

	//PROFILING_START("ScaleGen");

			scale = scaleGroup[currentScale];

			if (scale.oneVoltOct == 0) {
				if ((4095 - time1CVAverage) >= 2048) {
					noteIndex = (fix16_lerp(time1Knob, 4095, ((4095 - time1CVAverage) - 2048) << 5)) >> 5;
				}
				else {
					noteIndex = (fix16_lerp(0, time1Knob, (4095 - time1CVAverage) << 5)) >> 5;
				}
			} else {
				int holdT1 = (4095 - time1CVAverage) + (time1Knob >> 2) -1390;
				if (holdT1 > 4095) {
					holdT1 = 4095;
				} else if (holdT1 < 0) {
					holdT1 = 0;
				}
				noteIndex = holdT1 >> 5;
			}

			if (controlScheme == root) {
				if ((4095 - time2CV) >= 2048) {
					rootIndex = (fix16_lerp(time2KnobAverage, 4095, ((4095 - time2CV) - 2048) << 5)) >> scale.t2Bitshift;
				}
				else {
					rootIndex = (fix16_lerp(0, time2KnobAverage, (4095 - time2CV) << 5)) >> scale.t2Bitshift;
				}
			} else {
				rootIndex = time2KnobAverage >> scale.t2Bitshift;
			}

			fracMultiplier = scale.grid[rootIndex][noteIndex]->fractionalPart;
			intMultiplier = scale.grid[rootIndex][noteIndex]->integerPart;
			gcd = scale.grid[rootIndex][noteIndex]->fundamentalDivision;
			multKey = fracMultiplier + intMultiplier;

			//PROFILING_EVENT("Ratio Acquired");

			if (lastMultiplier != multKey) {
				if (RATIO_DELTAA) {
					ALOGIC_HIGH;
					__HAL_TIM_SET_COUNTER(&htim15, 0);
					__HAL_TIM_ENABLE(&htim15);
					if (RUNTIME_DISPLAY) {
						LEDC_ON;
					}
				}
				if (RATIO_DELTAB) {
					BLOGIC_HIGH;
					__HAL_TIM_SET_COUNTER(&htim15, 0);
					__HAL_TIM_ENABLE(&htim15);
					if (RUNTIME_DISPLAY) {
						LEDD_ON;
					}
				}
			}

			lastMultiplier = multKey;

			if (controlScheme == dutyCycle) {
				gateOnCount = periodCount >> 1;
			}

			pllCounter ++;

			if (pllCounter >= gcd || (EXTPLL)) {

				if (PLL_DIVA) {
					ALOGIC_HIGH;
					__HAL_TIM_SET_COUNTER(&htim15, 0);
					__HAL_TIM_ENABLE(&htim15);
					if (RUNTIME_DISPLAY) {
						LEDC_ON;
					}
				}
				if (PLL_DIVB) {
					BLOGIC_HIGH;
					__HAL_TIM_SET_COUNTER(&htim15, 0);
					__HAL_TIM_ENABLE(&htim15);
					if (RUNTIME_DISPLAY) {
						LEDD_ON;
					}
				}

				if (syncMode == hardSync) {

					position = 0;
					holdPosition =0;
					if (GATEA) {
						ALOGIC_HIGH;
						if (RUNTIME_DISPLAY) {
							LEDC_ON;
						}
					} else if (TRIGA) {
						ALOGIC_HIGH;
						if (RUNTIME_DISPLAY) {
							LEDC_ON;
						}
						__HAL_TIM_SET_COUNTER(&htim15, 0);
						__HAL_TIM_ENABLE(&htim15);
					}

				} else if (syncMode == true) {
					// if we are behind the phase of the clock, go faster, otherwise, go slower
					if (position > span) {
						pllNudge = (spanx2 - position) << 4;
					} else {
						pllNudge = -(position) << 4;
					}
				}
				pllCounter = 0;
				CLEAR_EXTPLL;
			}

			//PROFILING_EVENT("SetupComplete");

			attackInc = (((span << 7) + pllNudge) / gateOnCount) << 1;
			releaseInc = (((span << 7) + pllNudge) / (periodCount - gateOnCount)) << 1;
			attackInc = fix48_mul(attackInc, fracMultiplier) + fix16_mul(attackInc, intMultiplier);
			releaseInc = fix48_mul(releaseInc, fracMultiplier) + fix16_mul(releaseInc, intMultiplier);
			attackInc = attackInc*3;
			releaseInc = releaseInc*3;

			if (attackInc >= span - 1) {attackInc = span - 1;}
			if (releaseInc >= span - 1) {releaseInc = span - 1;}

			//PROFILING_EVENT("Inc Gen Complete");
			//PROFILING_STOP();

}
