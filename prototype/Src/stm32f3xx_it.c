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

//per family bit shift amounts to accomplish morph
uint8_t morphBitShiftRight;
uint8_t morphBitShiftLeft;

//import array of structs that contain our wavetable family info
Family familyArray[15];
uint8_t familyIndicator;

//this is used for our 1v/oct and bonus expo envelope
const int lookuptable[4096] = expotable10oct;

//these are the variables used to generate the phase information that feeds our interpolations
int fixMorph;
int morphBuffer[8];
int getMorph;
int position;
int mirror;
int inc;
int incFromADCs;
int incSign = 1;
int time1;
int time2;
int storePhaseMod;





//sample indices and interpolation fraction for the wavetable
int LnSample;
int RnSample;
uint16_t waveFrac;

//wavetable indices (within the family) and interpoation fraction for the morph interpolation
uint8_t LnFamily;
uint8_t RnFamily;
uint16_t morphFrac;

//actual values and interpolation result for one wavetable
int Lnvalue1;
int Rnvalue1;
int interp1;

//actual values and interpolation result for the adjacent wavetable
int Lnvalue2;
int Rnvalue2;
int interp2;

//most recent value from our expo decay
int exposcale;

//lastest result of the biinterpolation between interp1 and interp2 (scaled in drum mode)
extern int out;




void attack(void);
void release(void);
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


// "playback" flags that set the oscillator in motion
volatile int oscillatorActive = 0;
volatile int retrig = 0;

// logic used to signal oscillator phase position
uint8_t attackFlag;
uint8_t releaseFlag;
extern uint8_t phaseState;
uint8_t lastPhaseState;
uint8_t gateOn;
uint8_t rgbOn;
uint8_t drumRetrig;
uint8_t sampleHoldDirection;
enum sampleHoldDirection {toward_a, toward_b};


// timers used for clocking the expo envelope in drum mode and resampling the sample and holds
int drumCount;
int subCount;
uint8_t drumModeOn;
uint8_t pitchOn;
uint8_t morphOn;
uint8_t ampOn;
uint32_t drumOff;

uint8_t pendulumDirection;

// ADC/DAC DMA variables
uint32_t ADCReadings1[4];
uint32_t ADCReadings2[2];
uint32_t ADCReadings3[2];
#define time2Knob ADCReadings2[0]
#define MorphKnob ADCReadings2[1]
#define time1CV ADCReadings1[0]
#define time2CV ADCReadings1[1]
#define morphCV ADCReadings1[2]
#define time1Knob ADCReadings3[0]
uint16_t dacbuffer1[1];
uint16_t dacbuffer2[1];
buffer time2CVBuffer;
uint32_t time2Average;


// mode indicators, determined in the main loop
enum speedTypes speed;
enum loopTypes loop;
enum trigModeTypes trigMode;
enum sampleHoldModeTypes sampleHoldMode;

uint8_t family;

extern TIM_HandleTypeDef htim1;

uint32_t dac1HoldingReg;
uint32_t dac2HoldingReg;

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern DMA_HandleTypeDef hdma_adc1;
extern DMA_HandleTypeDef hdma_adc2;
extern DMA_HandleTypeDef hdma_adc3;
extern DAC_HandleTypeDef hdac;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim6;
extern TIM_HandleTypeDef htim7;
extern TIM_HandleTypeDef htim8;

/******************************************************************************/
/*            Cortex-M4 Processor Interruption and Exception Handlers         */ 
/******************************************************************************/

/**
* @brief This function handles Non maskable interrupt.
*/
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */

  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
* @brief This function handles Hard fault interrupt.
*/
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
  }
  /* USER CODE BEGIN HardFault_IRQn 1 */

  /* USER CODE END HardFault_IRQn 1 */
}

/**
* @brief This function handles Memory management fault.
*/
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
  }
  /* USER CODE BEGIN MemoryManagement_IRQn 1 */

  /* USER CODE END MemoryManagement_IRQn 1 */
}

/**
* @brief This function handles Pre-fetch fault, memory access fault.
*/
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
  }
  /* USER CODE BEGIN BusFault_IRQn 1 */

  /* USER CODE END BusFault_IRQn 1 */
}

/**
* @brief This function handles Undefined instruction or illegal state.
*/
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
  }
  /* USER CODE BEGIN UsageFault_IRQn 1 */

  /* USER CODE END UsageFault_IRQn 1 */
}

/**
* @brief This function handles System service call via SWI instruction.
*/
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVCall_IRQn 0 */

  /* USER CODE END SVCall_IRQn 0 */
  /* USER CODE BEGIN SVCall_IRQn 1 */

  /* USER CODE END SVCall_IRQn 1 */
}

/**
* @brief This function handles Debug monitor.
*/
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/**
* @brief This function handles Pendable request for system service.
*/
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
* @brief This function handles System tick timer.
*/
void SysTick_Handler(void)
{
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
void DMA1_Channel1_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Channel1_IRQn 0 */



  /* USER CODE END DMA1_Channel1_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_adc1);
  /* USER CODE BEGIN DMA1_Channel1_IRQn 1 */

  /* USER CODE END DMA1_Channel1_IRQn 1 */
}

/**
* @brief This function handles TIM2 global interrupt.
*/
void TIM2_IRQHandler(void)
{
  /* USER CODE BEGIN TIM2_IRQn 0 */
    if((GPIOA->IDR & GPIO_PIN_15) != (uint32_t)GPIO_PIN_RESET){

	  if (oscillatorActive == 0) {
		oscillatorActive = 1;
		if (drumModeOn) {__HAL_TIM_SET_COUNTER(&htim3, 3840);
						 __HAL_TIM_SET_PRESCALER(&htim3, (lookuptable[(time2CV >> 2) + (time2Knob >> 2)] >> 6));
						 __HAL_TIM_ENABLE(&htim3);
		}
		if (speed == env) {
		attackTime = calcTime1Env;
		releaseTime = calcTime2Env;
		}
		else if (speed == seq) {
		attackTime = calcTime1Seq;
		releaseTime = calcTime2Seq;
		}
		//incSign = 1;
		if (trigMode == gated) {gateOn = 1;}
	  }
	  else {

	   if (drumModeOn == 1) {
			drumRetrig = 1;
	   }

	   else {

		switch (trigMode) {

		case hardsync:

			position = 0;

			break;


		case gated :

			if (position < span) {

				if (attackTime == &calcTime2Env) {attackTime = &calcTime1Env;}
				else if (attackTime == &calcTime2Seq) {attackTime = &calcTime1Seq;}
				incSign = 1; // 1 in int
				gateOn = 1;

			}

			else  {

				if (speed == env) {releaseTime = calcTime1Env;}
				else if (speed == seq) {releaseTime = calcTime1Seq;}
				incSign = -1;
				gateOn = 1;


			}


			break;


		case nongatedretrigger:

			if (position >= span) {

				if (speed == env) {releaseTime = calcTime1Env;}
				else if (speed == seq) {releaseTime = calcTime1Seq;}
				incSign = -1;

				}

			break;


		case pendulum:

			pendulumDirection = !pendulumDirection;

			//reset our count to 0 so we always increment forward through attack when triggering from rest
			//if  (position <= 0 || position >= spanx2) {pendulumDirection = 0;}

			//reverse direction of the oscillator
			if (pendulumDirection == 1) {
				incSign = -1;
			}
			else {incSign = 1;}


			break;

		}

	  }
	 }

    }

    else {

    	if (trigMode == gated && drumModeOn == 0) {

    		if (position < span) {

				if (speed == env) {attackTime = calcTime2Env;}
				if (speed == seq) {attackTime = calcTime2Seq;}
				incSign = -1; // -1 in int
				gateOn = 0;

			}
    		else {

    			if (speed == env) {releaseTime = calcTime2Env;};
    			if (speed == seq) {releaseTime = calcTime2Seq;};
    			incSign = 1;
    			gateOn = 0;

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
void TIM3_IRQHandler(void)
{
  /* USER CODE BEGIN TIM3_IRQn 0 */
	if (drumRetrig) {
		drumRetrig = 0;
		__HAL_TIM_SET_COUNTER(&htim3, 3840);
		position = 0;
	}
	else {
	oscillatorActive = 0;
	position = 0;
	out = 0;
	__HAL_TIM_DISABLE(&htim3);
	SH_A_TRACK
	SH_B_TRACK
	if (rgbOn) {
		LEDA_OFF
		LEDB_OFF
	}
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
void TIM8_UP_IRQHandler(void)
{
  /* USER CODE BEGIN TIM8_UP_IRQn 0 */
	SH_B_SAMPLE
	if (rgbOn) {
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
void TIM6_DAC_IRQHandler(void)
{
  /* USER CODE BEGIN TIM6_DAC_IRQn 0 */


	__HAL_TIM_CLEAR_FLAG(&htim6, TIM_FLAG_UPDATE);



	if (oscillatorActive || loop == looping){

					//write the current oscillator value to dac1, and its inverse to dac2 (crossfading)

					((*(volatile uint32_t *)DAC1_ADDR) = (4095 - out));
					((*(volatile uint32_t *)DAC2_ADDR) = (out));
					//((*(volatile uint32_t *)DAC1_ADDR) = (0));
					//((*(volatile uint32_t *)DAC2_ADDR) = (4095));
					getAverages();

					// call the function that calculates our increment from the ADC values

					getInc();

	  				//call the function to advance the phase of the oscillator using that increment

	  		  	  	getPhase();

	  		  	  	//store last "Phase State" (attack or release)

	  	  	  		lastPhaseState = phaseState;

	  	  	  		//call the appropriate interpolation routine per phase in the two part table and declare phase state as such

	  	  	  		if (position < span) {attack(); phaseState = 1;}
	  	  	  		if (position >= span) {release(); phaseState = 2;}

	  	  	  		//calculate our morph amount per sample as a function of inc and the morph knob and CV

	  	  	  		fixMorph = ADCReadings2[1] - (ADCReadings1[2] + (abs(inc) >> 8));

	  	  	  		//constrain it to an appropriate range

					if (fixMorph > 4095) {fixMorph = 4095;}
					if (fixMorph < 0) {fixMorph = 0;}

					// write that value to our RGB

					__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, fixMorph);



	  	  	  		//if we are in high speed and not looping, activate drum mode

					if (drumModeOn == 1){

	  		  	  		//call the fuction that generates our expo decay and scales amp

						drum();

	  		  	  		//use the expo decay scaled by the manual morph control to modulate morph

						if (morphOn != 0) {fixMorph = myfix16_mul(exposcale, fixMorph);}

	  		  	  	}

	  		  	  	// if we transition from one phase state to another, enable the transition handler interrupt

					if (phaseState != lastPhaseState) {

	  	  	  			HAL_NVIC_SetPendingIRQ(EXTI15_10_IRQn);

	  	  	  		}

	}

	else {

		//turn off the display if the oscillator is inactive and we are not switching modes

		if (rgbOn != 0) {

			//LEDC_OFF;
			LEDD_OFF;
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);

		}

	}





  /* USER CODE END TIM6_DAC_IRQn 0 */
  //HAL_TIM_IRQHandler(&htim6);
  //HAL_DAC_IRQHandler(&hdac);
  /* USER CODE BEGIN TIM6_DAC_IRQn 1 */

  /* USER CODE END TIM6_DAC_IRQn 1 */
}

/**
* @brief This function handles TIM7 global interrupt.
*/
void TIM7_IRQHandler(void)
{
  /* USER CODE BEGIN TIM7_IRQn 0 */
	SH_A_SAMPLE
	SH_B_SAMPLE
	if (rgbOn) {
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
void DMA2_Channel1_IRQHandler(void)
{
  /* USER CODE BEGIN DMA2_Channel1_IRQn 0 */

  /* USER CODE END DMA2_Channel1_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_adc2);
  /* USER CODE BEGIN DMA2_Channel1_IRQn 1 */

  /* USER CODE END DMA2_Channel1_IRQn 1 */
}

/**
* @brief This function handles DMA2 channel5 global interrupt.
*/
void DMA2_Channel5_IRQHandler(void)
{
  /* USER CODE BEGIN DMA2_Channel5_IRQn 0 */

  /* USER CODE END DMA2_Channel5_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_adc3);
  /* USER CODE BEGIN DMA2_Channel5_IRQn 1 */

  /* USER CODE END DMA2_Channel5_IRQn 1 */
}

/* USER CODE BEGIN 1 */

void attack(void) {

	//calculate value based upon phase pointer "position"

	//truncate position then add one to find the relevant indices for our wavetables, first within the wavetable then the actual wavetables in the family
	LnSample = (int) (position >> 16);

	//bit shifting to divide by 512 takes full scale 12 bit and returns the quotient moudulo 512 (0-7)
	LnFamily = (uint32_t) fixMorph >> morphBitShiftRight;

	//determine the fractional parts of the above truncations, which should be 0 to full scale 16 bit
	waveFrac = (uint16_t) position;
	morphFrac = (fixMorph - (LnFamily << morphBitShiftRight)) << morphBitShiftLeft;

	//get values from the relevant wavetables
	Lnvalue1 = *(*(familyArray[familyIndicator].attackFamily + LnFamily) + LnSample);
	Rnvalue1 = *(*(familyArray[familyIndicator].attackFamily + LnFamily) + LnSample + 1);
	Lnvalue2 = *(*(familyArray[familyIndicator].attackFamily + LnFamily + 1) + LnSample);
	Rnvalue2 = *(*(familyArray[familyIndicator].attackFamily + LnFamily + 1) + LnSample + 1);

	//find the interpolated values for the adjacent wavetables
	interp1 = myfix16_lerp(Lnvalue1, Rnvalue1, waveFrac);

	interp2 = myfix16_lerp(Lnvalue2, Rnvalue2, waveFrac);

	//interpolate between those based upon morph (biinterpolation)

	out = myfix16_lerp(interp1, interp2, morphFrac) >> 3;

	if (out > 4095) {out = 4095;};

	if (rgbOn != 0) {__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, out);}





}








void release(void) {

	//calculate value based upon phase pointer "position" reflected over the span of the wavetable
	//mirror = spanx2 - position;

	//truncate position then add one to find the relevant indices for our wavetables, first within the wavetable then the actual wavetables in the family
	LnSample = (int) ((spanx2 - position) >> 16);

	//bit shifting to divide by 512 takes full scale 12 bit and returns the quotient moudulo 512 (0-7)
	//bit shift 9 for morph 6
	LnFamily = (uint32_t) fixMorph >> morphBitShiftRight;

	//determine the fractional parts of the above truncations, which should be 0 to full scale 16 bit
	waveFrac = (uint16_t) (spanx2 - position);
	morphFrac = (uint16_t) ((fixMorph - (LnFamily <<  morphBitShiftRight)) << morphBitShiftLeft);

	//get values from the relevant wavetables
	Lnvalue1 = *(*(familyArray[familyIndicator].releaseFamily + LnFamily) + LnSample);
	Rnvalue1 = *(*(familyArray[familyIndicator].releaseFamily + LnFamily) + LnSample + 1);
	Lnvalue2 = *(*(familyArray[familyIndicator].releaseFamily + LnFamily + 1) + LnSample);
	Rnvalue2 = *(*(familyArray[familyIndicator].releaseFamily + LnFamily + 1) + LnSample + 1);

	//find the interpolated values for the adjacent wavetables
	interp1 = myfix16_lerp(Lnvalue1, Rnvalue1, waveFrac);
	interp2 = myfix16_lerp(Lnvalue2, Rnvalue2, waveFrac);

	//interpolate between those based upon morph (biinterpolation)
	out = myfix16_lerp(interp1, interp2, morphFrac) >> 3;
	if (out > 4095) {out = 4095;};
	if (rgbOn != 0) {__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, out);}



}






//defines an increment then checks the trigger mode, making the appropriate changes to playback when the oscillator is retriggered
// Questioning whether this works properly when position has to be calculated using attack inc + decay inc (at transitions) i.e. increment rate overshoot

void getPhase(void) {

	// apply the approrpiate signage to our inc per the retrigger behavior
	inc = incFromADCs * incSign;

	// if trigmode is gated and we arent in Drum Mode
	if (trigMode == gated && drumModeOn == 0) {
		if (gateOn == 1 && (abs(inc) > abs(span - position))) {

			inc = span - position;

		}
	}





	// increment our phase position with our newly calculated value
	position = position + inc + (storePhaseMod - (time2Average << 7));

	storePhaseMod = time2Average << 7;



	//position = position + ((2000 - time2CV) * 4096);
	// if we have incremented outside of our table, wrap back around to the other side and stop/reset if we are in LF 1 shot mode

	if (position >= spanx2) {

		position = position - spanx2;

		if (loop == noloop && speed == env){

			oscillatorActive = 0;
			position = 0;
			pendulumDirection = 0;
			phaseState = 0;
			SH_A_TRACK
			SH_B_TRACK
			if (rgbOn) {
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

		if (speed == env && loop == noloop){

			oscillatorActive = 0;
			pendulumDirection = 0;
			position = 0;
			phaseState = 0;
			SH_A_TRACK
			SH_B_TRACK
			if (rgbOn) {
				LEDA_OFF
				LEDB_OFF
				LEDC_OFF
				LEDD_OFF
			}

		}

	}

}

void getInc(void) {


	//calculate our increment value in high speed mode
	uint16_t expoIndex;
	if (speed == audio) {
		if (drumModeOn == 0) {
			expoIndex = 4095 - (1200 + time1CV - (time1Knob + (time2Knob >> 4)));
			if (expoIndex > 4095) {expoIndex = 4095;}
			else if (expoIndex < 0) {expoIndex = 0;}
		}
		else  {
					expoIndex = 4095 - (1200 + time1CV - time1Knob);
					if (expoIndex > 4095) {expoIndex = 4095;}
					else if (expoIndex < 0) {expoIndex = 0;}
				}



		/*multiply a base (modulated by linear FM) by a lookup value from a 10 octave expo table (modulated by expo FM)
		  if we are in drum mode, replace linear fm with the drum envelope*/
		if (loop == noloop) {

			if (pitchOn == 1) {incFromADCs = myfix16_mul((exposcale >> 8) + 100, lookuptable[expoIndex]);}

			else {incFromADCs = myfix16_mul(1000, lookuptable[expoIndex] >> 2);}

		}

		else {

			//incFromADCs = myfix16_mul((1800 - time2CV) + time2Knob, lookuptable[expoIndex] >> 2);
			incFromADCs = myfix16_mul(3000, lookuptable[expoIndex] >> 2);

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

}

int calcTime1Env(void) {

	time1 = lookuptable[((4095 - (time1Knob - (4095 - time1CV))) >> 1) + 700] >> 13;
	return time1;

}

int calcTime2Env(void) {

	time2 = lookuptable[(4095 - (time2Knob - (4095 - time2CV))) >> 1] >> 14;
	return time2;

}

int calcTime1Seq(void) {

	time1 = lookuptable[(4095 - (time1Knob - (4095 - time1CV))) >> 1] >> 16;
	return time1;

}

int calcTime2Seq(void) {

	time2 = lookuptable[(4095 - (time2Knob - (4095 - time2CV))) >> 1] >> 16;
	return time2;

}

void drum(void) {


	//this gets the appropriate value for the expo table and scales into the range of the fix16 fractional component (16 bits)
	exposcale = lookuptable[__HAL_TIM_GET_COUNTER(&htim3)] >> 10;

	//scale the oscillator
	if (ampOn != 0) {out = myfix16_mul(out, exposcale);}

}

int myfix16_mul(int in0, int in1) {
	//taken from the fixmathlib library
	int64_t result = (uint64_t)in0*in1;
	return result >> 16;
}

int myfix16_lerp(int in0, int in1, uint16_t inFract) {
	//taken from the fixmathlib library
	int64_t tempOut = int64_mul_i32_i32(in0, (((int32_t)1 << 16) - inFract));
	tempOut = int64_add(tempOut, int64_mul_i32_i32(in1, inFract));
	tempOut = int64_shift(tempOut, -16);
	return (int)int64_lo(tempOut);
}

void EXTI15_10_IRQHandler(void)
{


	if (phaseState == 1) {

		if (drumRetrig) {	__HAL_TIM_SET_PRESCALER(&htim3, (lookuptable[(time2CV >> 2) + (time2Knob >> 2)] >> 6));
							HAL_TIM_GenerateEvent(&htim3, TIM_EVENTSOURCE_UPDATE);
		}

		else if (trigMode == nongatedretrigger) {
			incSign = 1;
			if (speed == env) {releaseTime = calcTime2Env;}
			else if (speed == seq) {releaseTime = calcTime2Seq;}
		}

		EOR_JACK_HIGH
		EOA_JACK_LOW
		EOR_GATE_HIGH
		EOA_GATE_LOW

		if (inc < 0) {sampHoldB();}
		else {sampHoldA();}

		if (rgbOn != 0) {
		LEDC_ON;
		LEDD_OFF;
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
		}

	}
	else if (phaseState == 2) {

		EOA_JACK_HIGH
		EOR_JACK_LOW
		EOA_GATE_HIGH
		EOR_GATE_LOW

		if (inc < 0) {sampHoldA();}
		else {sampHoldB();}

		if (rgbOn != 0) {
			LEDC_OFF;
			LEDD_ON;
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);
		}

	}

}

void sampHoldB (void) {

	switch (sampleHoldMode) {

	case a: SH_A_TRACK
			if (rgbOn){
			LEDA_ON
			}
			break;

	// case b: b remains sampled

	case ab: 	SH_A_TRACK
				if (rgbOn){
					LEDA_OFF
				}
				// b remains sampled
				break;


	case antidecimate:  SH_B_SAMPLE
						SH_A_TRACK
						if (rgbOn){
							LEDB_OFF
							LEDA_ON
						}
						break;

	case decimate: 	SH_A_TRACK;
					if (rgbOn) {
						LEDA_OFF;
						LEDB_OFF;
					}

					__HAL_TIM_SET_COUNTER(&htim7, 0);
					__HAL_TIM_ENABLE(&htim7);
					break;

	}

}

void sampHoldA (void) {

	switch (sampleHoldMode) {

	case a: SH_A_SAMPLE
			if (rgbOn) {
				LEDA_OFF
			}
			break;

	case b: SH_B_TRACK
			__HAL_TIM_SET_COUNTER(&htim8, 0);
			__HAL_TIM_ENABLE(&htim8);
			if (rgbOn) {
				LEDB_OFF;
			}
			break;

	case ab: 	SH_A_SAMPLE
				SH_B_TRACK
		 	 	if (rgbOn) {
		 	 		LEDB_OFF
					LEDA_ON
		 	 	}
				 __HAL_TIM_SET_COUNTER(&htim8, 0);
				 __HAL_TIM_ENABLE(&htim8);
				 break;


	case antidecimate:  SH_A_SAMPLE
						SH_B_TRACK
						if (rgbOn) {
							LEDA_OFF
							LEDB_ON
						}
						break;

	case decimate:
					SH_B_TRACK;
					if (rgbOn) {
						LEDA_OFF;
						LEDB_OFF;
					}

					__HAL_TIM_SET_COUNTER(&htim7, 0);
					__HAL_TIM_ENABLE(&htim7);
					break;

	}
}

void write(buffer* buffer,int value){
    buffer->buff[(buffer->writeIndex++) & BUFF_SIZE_MASK] = value;
}

int readn(buffer* buffer, int Xn){
    return buffer->buff[(buffer->writeIndex + (~Xn)) & BUFF_SIZE_MASK];
}

void getAverages(void) {
	write(&time2CVBuffer, time2CV);
	time2Average = time2Average + time2CV - readn(&time2CVBuffer, 7);
}

/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
