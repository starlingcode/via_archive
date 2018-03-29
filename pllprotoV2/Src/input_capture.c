#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"
#include "scales.h"
#include "interrupt_functions.h"


#include "tables.h"
#include "main.h"



	int lookuptable[4096] = expotable10oct;

	// mode indicators, determined in the main loop
	enum pllTypes pll; // {none, true, catch, setCatch}
	enum controlSchemes controlScheme; // {gateLength, knobCV}
	enum scaleTypes scaleType; // {rhythms, pitches}
	enum sampleHoldModeTypes sampleHoldMode;

	extern TIM_HandleTypeDef htim15;
	extern TIM_HandleTypeDef htim2;



void inputCapture(void) {


	int pllNudge = 0;
	static uint32_t pllCounter;
	uint32_t fracMultiplier;
	uint32_t intMultiplier;
	uint32_t gcd;
	uint32_t noteIndex;
	uint32_t rootIndex;
	uint32_t multKey;
	static uint32_t lastMultiplier;
	Scale currentScale;



	if ((GPIOA->IDR & GPIO_PIN_15) == (uint32_t) GPIO_PIN_RESET) {

		//get the timer value that which was reset on last rising edge
		periodCount = __HAL_TIM_GET_COUNTER(&htim2);



		//reset the timer value
		__HAL_TIM_SET_COUNTER(&htim2, 0);

		//PROFILING_START("ScaleGen");

		currentScale = scaleGroup[scaleType];

		if (currentScale.oneVoltOct == 0) {
			if ((4095 - time1CV) >= 2048) {
				noteIndex = (myfix16_lerp(time1Knob, 4095, ((4095 - time1CV) - 2048) << 5)) >> 5;
			}
			else {
				noteIndex = (myfix16_lerp(0, time1Knob, (4095 - time1CV) << 5)) >> 5;
			}
		} else {
			int holdT1 = (4095 - time1CV) + (time1Knob >> 2) -1390;
			if (holdT1 > 4095) {
				holdT1 = 4095;
			} else if (holdT1 < 0) {
				holdT1 = 0;
			}
			noteIndex = holdT1 >> 5;
		}


		if (controlScheme == root) {
			if ((4095 - time2CV) >= 2048) {
				rootIndex = (myfix16_lerp(time2Knob, 4095, ((4095 - time2CV) - 2048) << 5)) >> currentScale.t2Bitshift;
			}
			else {
				rootIndex = (myfix16_lerp(0, time2Knob, (4095 - time2CV) << 5)) >> currentScale.t2Bitshift;
			}
		} else {
			rootIndex = time2Knob >> currentScale.t2Bitshift;
		}


		fracMultiplier = currentScale.grid[rootIndex][noteIndex]->fractionalPart;
		intMultiplier = currentScale.grid[rootIndex][noteIndex]->integerPart;
		gcd = currentScale.grid[rootIndex][noteIndex]->fundamentalDivision;
		multKey = fracMultiplier + intMultiplier;

		//PROFILING_EVENT("Ratio Acquired");

		if (lastMultiplier != multKey) {
			if (RATIO_DELTAA) {
				EOR_JACK_HIGH
				__HAL_TIM_SET_COUNTER(&htim15, 0);
				__HAL_TIM_ENABLE(&htim15);
				if (RGB_ON) {
					LEDC_ON;
				}
			}
			if (RATIO_DELTAB) {
				EOA_JACK_HIGH
				__HAL_TIM_SET_COUNTER(&htim15, 0);
				__HAL_TIM_ENABLE(&htim15);
				if (RGB_ON) {
					LEDD_ON;
				}
			}
		}
		lastMultiplier = multKey;


		if (controlScheme == dutyCycle) {

			gateOnCount = periodCount >> 1;

		}


		pllCounter ++;
		if (pllCounter >= gcd || (TRIGGER_BUTTON)) {

			RESET_TRIGGER_BUTTON;

			if (PLL_DIVA) {
				EOR_JACK_HIGH
				__HAL_TIM_SET_COUNTER(&htim15, 0);
				__HAL_TIM_ENABLE(&htim15);
				if (RGB_ON) {
					LEDC_ON;
				}
			}
			if (PLL_DIVB) {
				EOA_JACK_HIGH
				__HAL_TIM_SET_COUNTER(&htim15, 0);
				__HAL_TIM_ENABLE(&htim15);
				if (RGB_ON) {
					LEDD_ON;
				}
			}

			if (pll == hardSync) {

				position = 0;
				holdPosition =0;
				RESET_TRIGGER_BUTTON;
				if (GATEA) {
					EOR_JACK_HIGH;
					if (RGB_ON) {
						LEDC_ON;
					}
				} else if (TRIGA) {
					EOR_JACK_HIGH;
					if (RGB_ON) {
						LEDC_ON;
					}
					__HAL_TIM_SET_COUNTER(&htim15, 0);
					__HAL_TIM_ENABLE(&htim15);
				}

			} else if (pll == true) {
				// if we are behind the phase of the clock, go faster, otherwise, go slower
				if (position > span) {

					pllNudge = (spanx2 - position) << 4;

				} else {

					pllNudge = -(position) << 4;

				}

				RESET_TRIGGER_BUTTON;
			}


			pllCounter = 0;
		}


		//PROFILING_EVENT("SetupComplete");



		attackInc = (((span << 7) + pllNudge) / gateOnCount) << 2;
		releaseInc = (((span << 7) + pllNudge) / (periodCount - gateOnCount)) << 2;




		attackInc = myfix48_mul(attackInc, fracMultiplier) + myfix16_mul(attackInc, intMultiplier);
		releaseInc = myfix48_mul(releaseInc, fracMultiplier) + myfix16_mul(releaseInc, intMultiplier);


		if (attackInc >= span - 1) {attackInc = span - 1;}
		if (releaseInc >= span - 1) {releaseInc = span - 1;}

		//PROFILING_EVENT("Inc Gen Complete");
		//PROFILING_STOP();

	}

	else {


		//get the timer value that which was reset on last rising edge
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

