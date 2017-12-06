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
int spanx2;
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
volatile int position;
volatile int inc;
volatile int incSign = 1;
int time1;
int time2;

//most recent value from our expo decay
int expoScale;

//lastest result of the biinterpolation between interp1 and interp2 (scaled in drum mode)
int out;

//counter used to increment our drum attack envelope
int attackCount;

void getSample(uint32_t);
void getPhase(void);
void drum(void);
int calcTime1Env(void);
int calcTime2Env(void);
int calcTime1Seq(void);
int calcTime2Seq(void);
int myfix16_mul(int, int);
int myfix16_lerp(int, int, uint16_t);
void getInc(void);
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
enum speedTypes speed;
enum loopTypes loop;
enum trigModeTypes trigMode;
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
	if (((GPIOA->IDR & GPIO_PIN_15) == (uint32_t) GPIO_PIN_RESET) || (TRIGGER_BUTTON)) {

		if (!(OSCILLATOR_ACTIVE)) { // oscillator at rest
			SET_OSCILLATOR_ACTIVE; // set the oscillator flag
			if (DRUM_MODE_ON) { // perform the operations needed to initiate a drum sound
				SET_DRUM_ATTACK_ON; //set global flag indicating we are using the timer to generate "attack"
				SET_UPDATE_PRESCALER; //logic to be used in the timer interrupt so we pass through and just load prescaler to shadow register
				TIM3->PSC = (lookuptable[time2Knob] >> 12) + (lookuptable[time2CV] >> 13); // release time prescaler loaded to holding register
				TIM3->EGR = TIM_EGR_UG; //immediately set an update event
				TIM3->CNT = 3840; //reset the count for the down counter
				//TIM3->CR1 |= TIM_CR1_CEN; //enable timer

			}
			if (speed == env) {
				attackTime = calcTime1Env; //set the function pointers for attack and release to the envelope time scale
				releaseTime = calcTime2Env; //i believe this needs to be done here to ensure that we recover from retrigger behavior
			} else if (speed == seq) {
				attackTime = calcTime1Seq; //set the function pointer for attack and release to the sequence time scale
				releaseTime = calcTime2Seq;
			}
			//incSign = 1;
			if (trigMode == gated) {
				SET_GATE_ON;
			} //turn the gate flag on in gatemode
			sampHoldA();
		} else {

			if ((DRUM_MODE_ON) && !(DRUM_ATTACK_ON)) {
				SET_UPDATE_PRESCALER; //same logic flag as before
				SET_DRUM_ATTACK_ON;
				attackCount = TIM3->CNT;
				__HAL_TIM_DISABLE(&htim3);
				TIM3->PSC = (lookuptable[time2Knob] >> 12) + (lookuptable[time2CV] >> 13);
				TIM3->EGR = TIM_EGR_UG; //immediately set an update event to load the prescaler register

			}

			else {

				switch (trigMode) {

				case hardsync:

					position = 0; // hard reset to 0

					break;

				case gated:

					if (position < span) { //look to see if we are backtracking, if so, reset the envelope behavior

						if (attackTime == &calcTime2Env) {
							attackTime = &calcTime1Env;
						} else if (attackTime == &calcTime2Seq) {
							attackTime = &calcTime1Seq;
						}
						incSign = 1; // this reverts our direction
						SET_GATE_ON; // signal that the gate is on

					}

					else { //if we are releasing and we get a new gate on, run back up the release slope at attack timescale

						if (speed == env) {
							releaseTime = calcTime1Env;
						} else if (speed == seq) {
							releaseTime = calcTime1Seq;
						}
						incSign = -1; // this reverses the direction
						SET_GATE_ON;

					}

					break;

				case nongatedretrigger:

					if (position >= span) { //if we are releasing and we get a new gate on, run back up the release slope at attack timescale

						if (speed == env) {
							releaseTime = calcTime1Env;
						} else if (speed == seq) {
							releaseTime = calcTime1Seq;
						}
						incSign = -1;

					}

					break;

				case pendulum:

					if (!(HOLD_AT_B)) { // if we arent currently gated, reverse the direction of the oscillator
						incSign = incSign * -1;
					}

					break;

				default:
					break;

				}

			}
		}
		if (trigMode == pendulum && loop == noloop) { // regardless of whether the oscillator is at rest or not, toggle the gateOn every trigger with pendulum

			TOGGLE_GATE_ON;

		}

	}

	else {

		if (trigMode == gated && !(DRUM_MODE_ON)) { //aka, gate off when we aren't in drum mode

			if (position < span) { //if we release the gate before making it through attack, run back through attack at release speed

				if (speed == env) {
					attackTime = calcTime2Env;
				}
				if (speed == seq) {
					attackTime = calcTime2Seq;
				}
				incSign = -1; // -1 in int
				RESET_GATE_ON;

			} else { //if we get a release when we are at or after span, reset the oscillator behavior and let it finish release

				if (speed == env) {
					releaseTime = calcTime2Env;
				};
				if (speed == seq) {
					releaseTime = calcTime2Seq;
				};
				incSign = 1;
				RESET_GATE_ON;

			}

		}
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

	if (OSCILLATOR_ACTIVE) {

		//write the current oscillator value to dac1, and its inverse to dac2 (crossfading)

		((*(volatile uint32_t *) DAC1_ADDR) = (4095 - out));
		((*(volatile uint32_t *) DAC2_ADDR) = (out));

		// get our averages for t2 and morph cv (move to the ADC interrupt??)

		getAverages();

		storePhase = PHASE_STATE;


		// call the function that calculates our increment from the ADC values

		getInc();

		//call the function to advance the phase of the oscillator using that increment

		getPhase();

		//store last "Phase State" (attack or release)



		//call the appropriate interpolation routine per phase in the two part table and declare phase state as such

		if (position < span) {
			RESET_PHASE_STATE;
			getSample(0);
		}
		if (position >= span) {
			SET_PHASE_STATE;
			getSample(1);
		}

		//calculate our morph amount per sample as a function of inc and the morph knob and CV (move to the interrupt?)

		if (inc > 1048575) {inc = 1048575;}
		if (morphAverage >= 16384) {
			fixMorph = myfix16_mul(myfix16_lerp(morphKnob, 4095, (morphAverage - 16384) << 2), 65535 - (inc >> 4));
		}
		else {
			fixMorph = myfix16_mul(myfix16_lerp(0, morphKnob, morphAverage << 2) , 65535 - (inc >> 4));
		}

		// write that value to our RGB

		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, fixMorph);

		//if we are in high speed and not looping, activate drum mode

		if (DRUM_MODE_ON) {

			//call the fuction that generates our expo decay and scales amp

			drum();

			//use the expo decay scaled by the manual morph control to modulate morph

			if (MORPH_ON) {
				fixMorph = myfix16_mul(expoScale, fixMorph);
			}

		}

		// if we transition from one phase state to another, enable the transition handler interrupt

		if ((PHASE_STATE) != storePhase) {

			HAL_NVIC_SetPendingIRQ(EXTI15_10_IRQn);

		}

	}

	else {

		//turn off the display if the oscillator is inactive and we are not switching modes

		if (RGB_ON) {

			LEDC_OFF
			LEDD_OFF
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);

		}

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
	uint16_t **family;

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
		family = currentFamily.attackFamily + LnFamily;
		Lnvalue1 = *(*(family) + LnSample);
		Rnvalue1 = *(*(family) + LnSample + 1);
		Lnvalue2 = *(*(family + 1) + LnSample);
		Rnvalue2 = *(*(family + 1) + LnSample + 1);

		//find the interpolated values for the adjacent wavetables using an efficient fixed point linear interpolation
		interp1 = myfix16_lerp(Lnvalue1, Rnvalue1, waveFrac);

		interp2 = myfix16_lerp(Lnvalue2, Rnvalue2, waveFrac);

		//interpolate between those based upon morph (biinterpolation)

		out = myfix16_lerp(interp1, interp2, morphFrac) >> 3;

		if (RGB_ON) { //if the runtime display is on, show our mode
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, out);
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
		family = currentFamily.releaseFamily + LnFamily;
		Lnvalue1 = *(*(family) + LnSample);
		Rnvalue1 = *(*(family) + LnSample + 1);
		Lnvalue2 = *(*(family + 1) + LnSample);
		Rnvalue2 = *(*(family + 1) + LnSample + 1);

		interp1 = myfix16_lerp(Lnvalue1, Rnvalue1, waveFrac);
		interp2 = myfix16_lerp(Lnvalue2, Rnvalue2, waveFrac);

		out = myfix16_lerp(interp1, interp2, morphFrac) >> 3;

		if (RGB_ON) {
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, out);
		}
	}

}

//defines an increment then checks the trigger mode, making the appropriate changes to playback when the oscillator is retriggered
// Questioning whether this works properly when position has to be calculated using attack inc + decay inc (at transitions) i.e. increment rate overshoot

void getPhase(void) {

	//calculate our increment value in high speed mode
	static int expoIndex;
	static int incFromADCs;

	if (speed == audio) {

		/*multiply a base (modulated by linear FM) by a lookup value from a 10 octave expo table (modulated by expo FM)
		 if we are in drum mode, replace linear fm with the drum envelope*/
		if (loop == noloop) {


			expoIndex = 4095 - (1200 + time1CV- time1Knob);
			if (expoIndex > 4095) {expoIndex = 4095;}
			else if (expoIndex < 0) {expoIndex = 0;}

			if (PITCH_ON) {incFromADCs = myfix16_mul((expoScale >> 8) + 100, lookuptable[expoIndex]) >> tableSizeCompensation;}

			else {incFromADCs = myfix16_mul(1000, lookuptable[expoIndex] >> 2) >> tableSizeCompensation;}

		}

		else {


			incFromADCs = myfix16_mul(myfix16_mul(myfix16_mul((3000 - time2CV) << 5, lookuptable[4095 - time1CV] >> 5), lookuptable[time1Knob] >> 4), lookuptable[time2Knob >> 4]) >> tableSizeCompensation;


		}

	}

	//define increment for env speed mode using function pointers to the appropriate knob/cv combo per the retirgger mode
	else {

		if (position < span) {
			incFromADCs = (*attackTime)();
		}
		else {
			incFromADCs = (*releaseTime)();
		}

	}

	// apply the approrpiate signage to our inc per the retrigger behavior
	inc = incFromADCs * incSign;

	// if trigmode is gated and we arent in Drum Mode
	if (trigMode > 2 && !(DRUM_MODE_ON)) { // we look to see if we are about to increment past span

		if ((GATE_ON) && (abs(inc) > abs(span - position))) {

			SET_HOLD_AT_B; // if so, we
			inc = span - position;

		}

		else {
			RESET_HOLD_AT_B;
		}

	}

	if (inc > 2097151) {inc = 2097151;}
	else if (inc < -2097151) {inc = -2097151;}

	position = position + inc;

	// if we have incremented outside of our table, wrap back around to the other side and stop/reset if we are in LF 1 shot mode

	if (position >= spanx2) {

		position = position - spanx2;

		if ((loop == noloop && speed != audio) || (LAST_CYCLE)) {
			RESET_LAST_CYCLE;
			RESET_OSCILLATOR_ACTIVE;
			incSign = 1;
			//pendulumDirection = 0;
			position = 0;
			SET_PHASE_STATE;
			SH_A_TRACK
			SH_B_TRACK
			if (RGB_ON) {
				LEDA_OFF
				LEDB_OFF
				LEDC_OFF
				LEDD_OFF
			}

		}

	}
	// same as above but for when we are backtracking through the attack phase aka negative increment
	else if (position < 0) {

		position = position + spanx2;

		if ((loop == noloop && speed != audio) || (LAST_CYCLE)) {
			RESET_LAST_CYCLE;
			RESET_OSCILLATOR_ACTIVE;
			incSign = 1;
			//pendulumDirection = 0;
			position = 0;
			RESET_PHASE_STATE;
			SH_A_TRACK
			SH_B_TRACK
			if (RGB_ON) {
				LEDA_OFF
				LEDB_OFF
				LEDC_OFF
				LEDD_OFF
			}

		}

	}

}

void getInc(void) {

}

int calcTime1Env(void) {

	time1 = ((lookuptable[time1CV] >> 13) * (lookuptable[(4095 - time1Knob)] >> 13)) >> 6;
	return time1;

}

int calcTime2Env(void) {

	time2 = ((lookuptable[time2CV] >> 13) * (lookuptable[(4095 - time2Knob)] >> 13)) >> 6;
	return time2;

}

int calcTime1Seq(void) {

	time1 = ((lookuptable[time1CV] >> 13) * (lookuptable[(4095 - time1Knob)] >> 13)) >> 10;
	return time1;

}

int calcTime2Seq(void) {

	time2 = ((lookuptable[time2CV] >> 13) * (lookuptable[(4095 - time2Knob)] >> 13)) >> 10;
	return time2;

}

void drum(void) {

	//this gets the appropriate value for the expo table and scales into the range of the fix16 fractional component (16 bits)
	if (DRUM_ATTACK_ON) {

		attackCount = attackCount + 10;

		if (attackCount > 3840) {
			RESET_DRUM_ATTACK_ON;
			attackCount = 3840;
			__HAL_TIM_ENABLE(&htim3);
			expoScale = lookuptable[attackCount] >> 10;
			attackCount = 0;
			SET_DRUM_RELEASE_ON;
		} else {
			expoScale = lookuptable[attackCount] >> 10;
		}

	} else if (DRUM_RELEASE_ON) {
		if (!__HAL_TIM_GET_FLAG(&htim3, TIM_FLAG_UPDATE)) {
			expoScale = lookuptable[TIM3->CNT] >> 10;
		}
	}

	//scale the oscillator
	if (AMP_ON) {
		out = myfix16_mul(out, expoScale);
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

		if (trigMode == nongatedretrigger) {
			incSign = 1;

			if (speed == env) {
				releaseTime = calcTime2Env;
			} else if (speed == seq) {
				releaseTime = calcTime2Seq;
			}
		}

		EOR_JACK_HIGH
		EOA_JACK_LOW
		EOR_GATE_HIGH
		EOA_GATE_LOW
		__HAL_TIM_SET_COUNTER(&htim15, 0);
		__HAL_TIM_ENABLE(&htim15);

		if (inc < 0) {
			sampHoldB();
		} else if (OSCILLATOR_ACTIVE) {
			sampHoldA();
		}

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

		if (inc < 0) {
			sampHoldA();
		} else {
			sampHoldB();
		}

		if (RGB_ON) {
			LEDC_OFF
			LEDD_ON
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);
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
