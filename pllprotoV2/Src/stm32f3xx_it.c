/**
 ******************************************************************************
 * @file    stm32f3xx_it.c
 * @brief   Interrupt Service Routines.
 ******************************************************************************
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
/* Includes ------------------------------------------------------------------*/
#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"

/* USER CODE BEGIN 0 */

#include "tables.h"
#include "main.h"
#include "int64.h"

// wavetable size - 1 in fix16 and that number doubled
uint32_t span;
uint32_t spanx2;
int tableSizeCompensation;

//per family bit shift amounts to accomplish morph
uint32_t morphBitShiftRight;
uint32_t morphBitShiftLeft;

//import pointer to struct that contains our wavetable family info
Family currentFamily;

//this is used for our 1v/oct and bonus expo envelope
int lookuptable[4096] = expotable10oct;

//these are the variables used to generate the phase information that feeds our interpolations
int fixMorph;
int morphBuffer[8];
int getMorph;
volatile uint32_t position;
volatile uint32_t attackInc = 100;
volatile uint32_t releaseInc = 100;
volatile uint32_t catchupInc;
uint32_t gateOnCount = 10000;
uint32_t periodCount = 10000;
volatile int incSign = 1;
int time1;
int time2;


//most recent value from our expo decay
int expoScale;

//lastest result of the biinterpolation between interp1 and interp2 (scaled in drum mode)
int out;


void getSample(uint32_t);
void getPhase(void);
int myfix16_mul(int, int);
int myfix16_lerp(int, int, uint16_t);
void sampHoldB(void);
void sampHoldA(void);
void getAverages(void);


// ADC variables and defines
uint32_t ADCReadings1[4];
uint32_t ADCReadings2[2];
uint32_t ADCReadings3[2];
#define time2Knob ADCReadings2[0]
#define morphKnob ADCReadings2[1]
#define time1CV ADCReadings1[0]
#define time2CV ADCReadings1[1]
#define morphCV ADCReadings1[2]
#define time1Knob ADCReadings3[0]
uint32_t time2Average;
uint32_t morphAverage;

// mode indicators, determined in the main loop
enum pllTypes pll; // {none, true, catch, setCatch}
enum controlSchemes controlScheme; // {gateLength, knobCV}
enum scaleTypes scaleType; // {rhythms, pitches}
enum sampleHoldModeTypes sampleHoldMode;

extern TIM_HandleTypeDef htim1;



/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern DMA_HandleTypeDef hdma_adc1;
extern DMA_HandleTypeDef hdma_adc2;
extern DMA_HandleTypeDef hdma_adc3;
extern DAC_HandleTypeDef hdac;
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim6;
extern TIM_HandleTypeDef htim7;
extern TIM_HandleTypeDef htim8;
extern TIM_HandleTypeDef htim15;

/******************************************************************************/
/*            Cortex-M4 Processor Interruption and Exception Handlers         */
/******************************************************************************/

/**
 * @brief This function handles Non maskable interrupt.
 */
void NMI_Handler(void) {
	/* USER CODE BEGIN NonMaskableInt_IRQn 0 */

	/* USER CODE END NonMaskableInt_IRQn 0 */
	/* USER CODE BEGIN NonMaskableInt_IRQn 1 */

	/* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
 * @brief This function handles Hard fault interrupt.
 */
void HardFault_Handler(void) {
	/* USER CODE BEGIN HardFault_IRQn 0 */

	/* USER CODE END HardFault_IRQn 0 */
	while (1) {
	}
	/* USER CODE BEGIN HardFault_IRQn 1 */

	/* USER CODE END HardFault_IRQn 1 */
}

/**
 * @brief This function handles Memory management fault.
 */
void MemManage_Handler(void) {
	/* USER CODE BEGIN MemoryManagement_IRQn 0 */

	/* USER CODE END MemoryManagement_IRQn 0 */
	while (1) {
	}
	/* USER CODE BEGIN MemoryManagement_IRQn 1 */

	/* USER CODE END MemoryManagement_IRQn 1 */
}

/**
 * @brief This function handles Pre-fetch fault, memory access fault.
 */
void BusFault_Handler(void) {
	/* USER CODE BEGIN BusFault_IRQn 0 */

	/* USER CODE END BusFault_IRQn 0 */
	while (1) {
	}
	/* USER CODE BEGIN BusFault_IRQn 1 */

	/* USER CODE END BusFault_IRQn 1 */
}

/**
 * @brief This function handles Undefined instruction or illegal state.
 */
void UsageFault_Handler(void) {
	/* USER CODE BEGIN UsageFault_IRQn 0 */

	/* USER CODE END UsageFault_IRQn 0 */
	while (1) {
	}
	/* USER CODE BEGIN UsageFault_IRQn 1 */

	/* USER CODE END UsageFault_IRQn 1 */
}

/**
 * @brief This function handles System service call via SWI instruction.
 */
void SVC_Handler(void) {
	/* USER CODE BEGIN SVCall_IRQn 0 */

	/* USER CODE END SVCall_IRQn 0 */
	/* USER CODE BEGIN SVCall_IRQn 1 */

	/* USER CODE END SVCall_IRQn 1 */
}

/**
 * @brief This function handles Debug monitor.
 */
void DebugMon_Handler(void) {
	/* USER CODE BEGIN DebugMonitor_IRQn 0 */

	/* USER CODE END DebugMonitor_IRQn 0 */
	/* USER CODE BEGIN DebugMonitor_IRQn 1 */

	/* USER CODE END DebugMonitor_IRQn 1 */
}

/**
 * @brief This function handles Pendable request for system service.
 */
void PendSV_Handler(void) {
	/* USER CODE BEGIN PendSV_IRQn 0 */

	/* USER CODE END PendSV_IRQn 0 */
	/* USER CODE BEGIN PendSV_IRQn 1 */

	/* USER CODE END PendSV_IRQn 1 */
}

/**
 * @brief This function handles System tick timer.
 */
void SysTick_Handler(void) {
	/* USER CODE BEGIN SysTick_IRQn 0 */

	/* USER CODE END SysTick_IRQn 0 */
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
	/* USER CODE BEGIN SysTick_IRQn 1 */

	/* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F3xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f3xx.s).                    */
/******************************************************************************/

/**
 * @brief This function handles DMA1 channel1 global interrupt.
 */
void DMA1_Channel1_IRQHandler(void) {
	/* USER CODE BEGIN DMA1_Channel1_IRQn 0 */

	/* USER CODE END DMA1_Channel1_IRQn 0 */
	HAL_DMA_IRQHandler(&hdma_adc1);
	/* USER CODE BEGIN DMA1_Channel1_IRQn 1 */

	/* USER CODE END DMA1_Channel1_IRQn 1 */
}

/**
 * @brief This function handles TIM1 break and TIM15 interrupts.
 */
void TIM1_BRK_TIM15_IRQHandler(void) {
	/* USER CODE BEGIN TIM1_BRK_TIM15_IRQn 0 */
	EOA_JACK_LOW;
	EOR_JACK_LOW;
	__HAL_TIM_DISABLE(&htim15);
	__HAL_TIM_CLEAR_FLAG(&htim15, TIM_FLAG_UPDATE);
	/* USER CODE END TIM1_BRK_TIM15_IRQn 0 */
	//HAL_TIM_IRQHandler(&htim1);
	//HAL_TIM_IRQHandler(&htim15);
	/* USER CODE BEGIN TIM1_BRK_TIM15_IRQn 1 */

	/* USER CODE END TIM1_BRK_TIM15_IRQn 1 */
}

/**
 * @brief This function handles TIM2 global interrupt.
 */
void TIM2_IRQHandler(void) {

	/* USER CODE BEGIN TIM2_IRQn 0 */

	int pllNudge = 0;
	static uint32_t pllCounter;
	uint32_t multiplier;
	uint32_t divider;
	uint32_t adjustedSpan;
	uint32_t rhythmCoefficients[8] = {1, 2, 3, 4, 6, 8, 12, 16};
	uint32_t diatonicCoefficients[8] = {1, 2, 3, 4, 5, 6, 8, 10};
	uint32_t primesCoefficients[8] = {1, 2, 3, 5, 7, 11, 13, 17};
	uint32_t scaleIndex1;
	uint32_t scaleIndex2;



	if ((GPIOA->IDR & GPIO_PIN_15) == (uint32_t) GPIO_PIN_RESET) {

		//get the timer value that which was reset on last rising edge
		periodCount = __HAL_TIM_GET_COUNTER(&htim2);



		//reset the timer value
		__HAL_TIM_SET_COUNTER(&htim2, 0);


		switch (scaleType) {
		case rhythm:
			multiplier = rhythmCoefficients[time1Knob >> 9] * rhythmCoefficients[time1CV >> 9];
			divider = rhythmCoefficients[time2Knob >> 9] * rhythmCoefficients[time2CV >> 9];
			break;

		case diatonic:
			multiplier = diatonicCoefficients[time1Knob >> 9] * diatonicCoefficients[time1CV >> 9];
			divider = diatonicCoefficients[time2Knob >> 9] * diatonicCoefficients[time2CV >> 9];
			break;

		case primes:
			multiplier = primesCoefficients[time1Knob >> 9] * primesCoefficients[time1CV >> 9];
			divider = primesCoefficients[time2Knob >> 9] * primesCoefficients[time2CV >> 9];
			break;

		default:
			break;
		}


		if (controlScheme == CV) {
			gateOnCount = myfix16_mul(periodCount, time2CV << 4);
			// replace with
			switch (scaleType) {
			case rhythm:
				divider = rhythmCoefficients[time2Knob >> 9];
				break;
			case diatonic:
				divider = diatonicCoefficients[time2Knob >> 9];
				break;
			case primes:
				divider = primesCoefficients[time2Knob >> 9];
				break;
			default:
				break;
			}
		} else if (controlScheme == knob) {
			gateOnCount = myfix16_mul(periodCount, time2Knob << 4);
			// replace with
			switch (scaleType) {
			case rhythm:
				divider = rhythmCoefficients[time2CV >> 9];
				break;
			case diatonic:
				divider = diatonicCoefficients[time2CV >> 9];
				break;
			case primes:
				divider = primesCoefficients[time2CV >> 9];
				break;
			default:
				break;
			}
		} else if (controlScheme == knobCV) {
			gateOnCount = myfix16_mul(periodCount, (time2Knob + time2CV) << 3);
			// replace with
			divider = 1;
		}


		pllCounter ++;
		if (pllCounter >= divider || (TRIGGER_BUTTON)) {

			RESET_TRIGGER_BUTTON;

			if (pll == hardSync) {

				position = 0;
				RESET_TRIGGER_BUTTON;

			} else if (pll == true) {
				// if we are behind the phase of the clock, go faster, otherwise, go slower
				if (position > span) {

					pllNudge = (spanx2 - position) << 5;

				} else {

					pllNudge = -(position << 5);

				}

				RESET_TRIGGER_BUTTON;
			} else if (pll == catch) {

				// catch the next falling edge right on phase

				RESET_CATCH_UP;



				adjustedSpan = span*divider/multiplier;

				if (position < (adjustedSpan - (adjustedSpan >> 1))) {
					SET_CATCH_UP;
					RESET_TRIGGER_BUTTON;

					catchupInc =  ((adjustedSpan - position) << 9) / gateOnCount;



				} else if (position >= (spanx2 - adjustedSpan)) {
					SET_CATCH_UP;
					RESET_TRIGGER_BUTTON;

					catchupInc =  (((spanx2 - position) + adjustedSpan) << 9) / gateOnCount;

				} else {
					RESET_TRIGGER_BUTTON;
				}

			}


			pllCounter = 0;
		}


		//use this value to calculate our oscillator frequency
		attackInc = ((span << 8) + pllNudge) / (gateOnCount * divider);
		releaseInc = ((span << 8) + pllNudge) / ((periodCount - gateOnCount) * divider);

		attackInc = (attackInc << 1) * multiplier;
		releaseInc = (releaseInc << 1) * multiplier;

		if (attackInc > 1048575) {attackInc = 1048575;}
		if (releaseInc > 1048575) {releaseInc = 1048575;}



	}

	else {


		//get the timer value that which was reset on last rising edge
		gateOnCount = __HAL_TIM_GET_COUNTER(&htim2);

	}

	__HAL_TIM_CLEAR_FLAG(&htim2, TIM_FLAG_CC1);

	/* USER CODE END TIM2_IRQn 0 */
	//HAL_TIM_IRQHandler(&htim2);
	/* USER CODE BEGIN TIM2_IRQn 1 */

	/* USER CODE END TIM2_IRQn 1 */
}

/**
 * @brief This function handles TIM3 global interrupt.
 */
void TIM3_IRQHandler(void) {
	/* USER CODE BEGIN TIM3_IRQn 0 */
	//drumReleaseOn = 0;

	__HAL_TIM_CLEAR_FLAG(&htim3, TIM_FLAG_UPDATE);

	if (UPDATE_PRESCALER) { // handle the update event to load the prescaler initially
		RESET_UPDATE_PRESCALER;
	}

	else { // raise the flag to put the drum mode to rest after overflowing the release portion
		RESET_DRUM_RELEASE_ON;
		expoScale = 0;
		__HAL_TIM_DISABLE(&htim3);
		__HAL_TIM_SET_COUNTER(&htim3, 0);
		SET_LAST_CYCLE;
	}

	__HAL_TIM_CLEAR_FLAG(&htim3, TIM_FLAG_UPDATE);

	/* USER CODE END TIM3_IRQn 0 */
	//HAL_TIM_IRQHandler(&htim3);
	/* USER CODE BEGIN TIM3_IRQn 1 */

	/* USER CODE END TIM3_IRQn 1 */
}

/**
 * @brief This function handles TIM8 update interrupt.
 */
void TIM8_UP_IRQHandler(void) {
	/* USER CODE BEGIN TIM8_UP_IRQn 0 */
	SH_B_SAMPLE
	//this handles the logic where we resample b at a
	if (RGB_ON) {
		LEDB_ON
	}

	__HAL_TIM_CLEAR_FLAG(&htim8, TIM_FLAG_UPDATE);
	__HAL_TIM_DISABLE(&htim8);

	/* USER CODE END TIM8_UP_IRQn 0 */
	//HAL_TIM_IRQHandler(&htim8);
	/* USER CODE BEGIN TIM8_UP_IRQn 1 */

	/* USER CODE END TIM8_UP_IRQn 1 */
}

/**
 * @brief This function handles Timer 6 interrupt and DAC underrun interrupts.
 */
void TIM6_DAC_IRQHandler(void) {
	/* USER CODE BEGIN TIM6_DAC_IRQn 0 */

	uint32_t storePhase;

	__HAL_TIM_CLEAR_FLAG(&htim6, TIM_FLAG_UPDATE);



		//write the current oscillator value to dac1, and its inverse to dac2 (crossfading)

		((*(volatile uint32_t *) DAC1_ADDR) = (4095 - out));
		((*(volatile uint32_t *) DAC2_ADDR) = (out));



		// get our averages for t2 and morph cv (move to the ADC interrupt??)

		getAverages();


		//store last "Phase State" (attack or release)

		storePhase = PHASE_STATE;

		//call the function to advance the phase of the oscillator using that increment

		getPhase();

		//calculate our morph amount per sample as a function of inc and the morph knob and CV (move to the interrupt?)

		if ((32767 - morphAverage) >= 16384) {
			fixMorph = myfix16_lerp(morphKnob, 4095, ((32767 - morphAverage) - 16384) << 2);
		}
		else {
			fixMorph = myfix16_lerp(0, morphKnob, (32767 - morphAverage) << 2);
		}

		//call the appropriate interpolation routine per phase in the two part table and declare phase state as such

		if (position < span) {
			RESET_PHASE_STATE;
			getSample(0);
		}
		if (position >= span) {
			SET_PHASE_STATE;
			getSample(1);
		}

		// write that value to our RGB

		if (RGB_ON) {__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, fixMorph);}

		// if we transition from one phase state to another, enable the transition handler interrupt

		if ((PHASE_STATE) != storePhase) {

			HAL_NVIC_SetPendingIRQ(EXTI15_10_IRQn);

		}


	/* USER CODE END TIM6_DAC_IRQn 0 */
	// HAL_TIM_IRQHandler(&htim6);
	//HAL_DAC_IRQHandler(&hdac);
	/* USER CODE BEGIN TIM6_DAC_IRQn 1 */

	/* USER CODE END TIM6_DAC_IRQn 1 */
}

/**
 * @brief This function handles TIM7 global interrupt.
 */
void TIM7_IRQHandler(void) {
	/* USER CODE BEGIN TIM7_IRQn 0 */
	SH_A_SAMPLE
	// this handles our decimate resampling
	SH_B_SAMPLE
	if (RGB_ON) {
		LEDA_ON
		LEDB_ON
	}
	__HAL_TIM_CLEAR_FLAG(&htim7, TIM_FLAG_UPDATE);
	/* USER CODE END TIM7_IRQn 0 */
	//HAL_TIM_IRQHandler(&htim7);
	/* USER CODE BEGIN TIM7_IRQn 1 */
	__HAL_TIM_DISABLE(&htim7);

	/* USER CODE END TIM7_IRQn 1 */
}

/**
 * @brief This function handles DMA2 channel1 global interrupt.
 */
void DMA2_Channel1_IRQHandler(void) {
	/* USER CODE BEGIN DMA2_Channel1_IRQn 0 */

	/* USER CODE END DMA2_Channel1_IRQn 0 */
	HAL_DMA_IRQHandler(&hdma_adc2);
	/* USER CODE BEGIN DMA2_Channel1_IRQn 1 */

	/* USER CODE END DMA2_Channel1_IRQn 1 */
}

/**
 * @brief This function handles DMA2 channel5 global interrupt.
 */
void DMA2_Channel5_IRQHandler(void) {
	/* USER CODE BEGIN DMA2_Channel5_IRQn 0 */

	/* USER CODE END DMA2_Channel5_IRQn 0 */
	HAL_DMA_IRQHandler(&hdma_adc3);
	/* USER CODE BEGIN DMA2_Channel5_IRQn 1 */

	/* USER CODE END DMA2_Channel5_IRQn 1 */
}

/* USER CODE BEGIN 1 */

void getSample(uint32_t phase) {

	// in this function, we use our phase position to get the sample to give to our dacs using "biinterpolation"
	// essentially, we need to get 4 sample values and two "fractional arguments" (where are we at in between those sample values)
	// think of locating a position on a rectangular surface based upon how far you are between the bottom and top and how far you are between the left and right sides
	// that is basically what we are doing here

	uint32_t LnSample; // indicates the nearest neighbor to our position in the wavetable
	uint32_t LnFamily; // indicates the nearest neighbor (wavetable) to our morph value in the family
	uint32_t waveFrac; // indicates the factional distance between our nearest neighbors in the wavetable
	uint32_t morphFrac; // indicates the factional distance between our nearest neighbors in the family
	uint32_t Lnvalue1; // sample values used by our two interpolations in
	uint32_t Rnvalue1;
	uint32_t Lnvalue2;
	uint32_t Rnvalue2;
	uint32_t interp1; // results of those two interpolations
	uint32_t interp2;

	// the above is used to perform our bi-interpolation
	// essentially, interp 1 and interp 2 are the interpolated values in the two adjacent wavetables per the playback position
	// out is the "crossfade" between those according to morphFrac



	if (phase == 0) {
		// we do a lot of tricky bitshifting to take advantage of the structure of a 16 bit fixed point number
		//truncate position then add one to find the relevant indices for our wavetables, first within the wavetable then the actual wavetables in the family
		LnSample = (position >> 16);

		//bit shifting to divide by the correct power of two takes a 12 bit number (our fixMorph) and returns the a quotient in the range of our family size
		LnFamily = fixMorph >> morphBitShiftRight;

		//determine the fractional part of our phase position by masking off the integer
		waveFrac = 0x0000FFFF & position;
		// we have to calculate the fractional portion and get it up to full scale
		morphFrac = (fixMorph - (LnFamily << morphBitShiftRight)) << morphBitShiftLeft;

		//get values from the relevant wavetables
		// this is a funny looking method of referencing elements in a two dimensional array
		// we need to do it like this because our struct contains a pointer to the array being used
		// i feel like this could be optimized if we are loading from flash
//		family = currentFamily.attackFamily + LnFamily;
//		Lnvalue1 = *(*(family) + LnSample);
//		Rnvalue1 = *(*(family) + LnSample + 1);
//		Lnvalue2 = *(*(family + 1) + LnSample);
//		Rnvalue2 = *(*(family + 1) + LnSample + 1);

		//attempt at optimizing using fixed size array on the heap

		Lnvalue1 = attackHoldArray[LnFamily][LnSample];
		Rnvalue1 = attackHoldArray[LnFamily][LnSample + 1];
		Lnvalue2 = attackHoldArray[LnFamily + 1][LnSample];
		Rnvalue2 = attackHoldArray[LnFamily + 1][LnSample + 1];

		//find the interpolated values for the adjacent wavetables using an efficient fixed point linear interpolation
		interp1 = myfix16_lerp(Lnvalue1, Rnvalue1, waveFrac);

		interp2 = myfix16_lerp(Lnvalue2, Rnvalue2, waveFrac);

		//interpolate between those based upon morph (biinterpolation)

		out = myfix16_lerp(interp1, interp2, morphFrac) >> 3;

		if (RGB_ON) { //if the runtime display is on, show our mode
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, out);
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, fixMorph);
		}
	}

	else {

		//this section is similar, but subtly different to implement our "release"
		// notice, we reflect position back over span
		LnSample = ((spanx2 - position) >> 16);

		LnFamily = fixMorph >> morphBitShiftRight;

		// here, again, we use that reflected value
		waveFrac = 0x0000FFFF & (spanx2 - position);
		//
		morphFrac = (uint16_t) ((fixMorph - (LnFamily << morphBitShiftRight)) << morphBitShiftLeft);

		//pull the values from our "release family"
//		family = currentFamily.releaseFamily + LnFamily;
//		Lnvalue1 = *(*(family) + LnSample);
//		Rnvalue1 = *(*(family) + LnSample + 1);
//		Lnvalue2 = *(*(family + 1) + LnSample);
//		Rnvalue2 = *(*(family + 1) + LnSample + 1);


		//attempt at optimizing using fixed size array on the heap

		Lnvalue1 = releaseHoldArray[LnFamily][LnSample];
		Rnvalue1 = releaseHoldArray[LnFamily][LnSample + 1];
		Lnvalue2 = releaseHoldArray[LnFamily + 1][LnSample];
		Rnvalue2 = releaseHoldArray[LnFamily + 1][LnSample + 1];

		interp1 = myfix16_lerp(Lnvalue1, Rnvalue1, waveFrac);
		interp2 = myfix16_lerp(Lnvalue2, Rnvalue2, waveFrac);

		out = myfix16_lerp(interp1, interp2, morphFrac) >> 3;

		if (RGB_ON) {
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, out);
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, fixMorph);
		}
	}


}

//defines an increment then checks the trigger mode, making the appropriate changes to playback when the oscillator is retriggered
// Questioning whether this works properly when position has to be calculated using attack inc + decay inc (at transitions) i.e. increment rate overshoot

void getPhase(void) {

	if (CATCH_UP) {
		position = position + catchupInc;
	} else {
		if (PHASE_STATE) {
			position = position + attackInc;
		} else {
			position = position + releaseInc;
		}
	}

	// if we have incremented outside of our table, wrap back around to the other side and stop/reset if we are in LF 1 shot mode

	if (position >= spanx2) {

		position = position - spanx2;

	}
}





int myfix16_mul(int in0, int in1) {
	//taken from the fixmathlib library
	int64_t result = (uint64_t) in0 * in1;
	return result >> 16;
}

int myfix16_lerp(int in0, int in1, uint16_t inFract) {
	//taken from the fixmathlib library
	int64_t tempOut = int64_mul_i32_i32(in0, (((int32_t) 1 << 16) - inFract));
	tempOut = int64_add(tempOut, int64_mul_i32_i32(in1, inFract));
	tempOut = int64_shift(tempOut, -16);
	return (int) int64_lo(tempOut);
}

void EXTI15_10_IRQHandler(void) {

	if (!(PHASE_STATE)) {


		EOR_JACK_HIGH
		EOA_JACK_LOW
		EOR_GATE_HIGH
		EOA_GATE_LOW
		__HAL_TIM_SET_COUNTER(&htim15, 0);
		__HAL_TIM_ENABLE(&htim15);
		RESET_CATCH_UP;

		sampHoldA();

		if (RGB_ON) {
			LEDC_ON
			LEDD_OFF
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
		}

	} else {



		EOA_JACK_HIGH
		EOR_JACK_LOW
		EOA_GATE_HIGH
		EOR_GATE_LOW
		__HAL_TIM_SET_COUNTER(&htim15, 0);
		__HAL_TIM_ENABLE(&htim15);
		RESET_CATCH_UP;



		sampHoldB();

		if (RGB_ON) {
			LEDC_OFF
			LEDD_ON
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
		}

	}

}

void sampHoldB(void) {

	switch (sampleHoldMode) {

	case a:
		SH_A_TRACK
		if (RGB_ON) {
			LEDA_ON
		}
		break;

		// case b: b remains sampled

	case ab:
		SH_A_TRACK
		if (RGB_ON) {
			LEDA_OFF
		}
		// b remains sampled
		break;

	case antidecimate:
		SH_B_SAMPLE
		SH_A_TRACK
		if (RGB_ON) {
			LEDB_OFF
			LEDA_ON
		}
		break;

	case decimate:
		SH_A_TRACK
		if (RGB_ON) {
			LEDA_OFF
			LEDB_OFF
		}

		__HAL_TIM_SET_COUNTER(&htim7, 0);
		__HAL_TIM_ENABLE(&htim7);
		break;

	default:
		break;

	}

}

void sampHoldA(void) {

	switch (sampleHoldMode) {

	case a:
		SH_A_SAMPLE
		if (RGB_ON) {
			LEDA_OFF
		}
		break;

	case b:
		SH_B_TRACK
		__HAL_TIM_SET_COUNTER(&htim8, 0);
		__HAL_TIM_ENABLE(&htim8);
		if (RGB_ON) {
			LEDB_OFF
		}
		break;

	case ab:
		SH_A_SAMPLE
		SH_B_TRACK
		if (RGB_ON) {
			LEDB_OFF
			LEDA_ON
		}
		__HAL_TIM_SET_COUNTER(&htim8, 0);
		__HAL_TIM_ENABLE(&htim8);
		break;

	case antidecimate:
		SH_A_SAMPLE
		SH_B_TRACK
		if (RGB_ON) {
			LEDA_OFF
			LEDB_ON
		}
		break;

	case decimate:
		SH_B_TRACK
		;
		if (RGB_ON) {
			LEDA_OFF
			;
			LEDB_OFF
			;
		}

		__HAL_TIM_SET_COUNTER(&htim7, 0);
		__HAL_TIM_ENABLE(&htim7);
		break;

	default:
		break;

	}

}

void write(buffer* buffer, int value) {
	buffer->buff[(buffer->writeIndex++) & BUFF_SIZE_MASK] = value;
}

int readn(buffer* buffer, int Xn) {
	return buffer->buff[(buffer->writeIndex + (~Xn)) & BUFF_SIZE_MASK];
}

void getAverages(void) {

	static buffer time2CVBuffer;
	static buffer morphCVBuffer;

	write(&time2CVBuffer, time2CV);
	time2Average = time2Average + time2CV- readn(&time2CVBuffer, 7);
	write(&morphCVBuffer, morphCV);
	morphAverage = (morphAverage + morphCV- readn(&morphCVBuffer, 7));

}

/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
