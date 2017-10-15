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
int span;
int spanx2;

//import array of structs that contain our wavetable family info
Family familyArray[8];
uint8_t familyIndicator;

//import two arrays of structs that contain our scale info
Scale rowScaleArray[8];
uint8_t rowScaleIndicator;
Scale ratioScaleArray[8];
uint8_t ratioScaleIndicator;

uint8_t rowSelect;
uint8_t rowIndex;

//this is used for our 1v/oct and bonus expo envelope
const int lookuptable[4096] = expotable10oct;

//these are the variables used to generate the phase information that feeds our interpolations
uint8_t morphBitShiftRight;
uint8_t morphBitShiftLeft;
uint8_t rowSelectBitShift;
uint8_t rowIndexBitShift;
int fixMorph;
int morphBuffer[8];
int getMorph;
float position = 0;
float mirror;
float attackInc = 1;
float releaseInc = 1;
float numMult;
float denomMult;
float inc;
int (*attackTime) (void);
int (*releaseTime) (void);



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
int calcTime1(void);
int calcTime2(void);
int myfix16_mul(int, int);
int myfix16_lerp(int, int, uint16_t);
int myfix16_lerp8(int, int, uint16_t);
void setAttack(void);
void setRelease(void);
void getAverages(void);

// "playback" flags that set the oscillator in motion
volatile int oscillatorActive = 1;
volatile int retrig = 0;

// logic used to signal oscillator phase position
uint8_t attackFlag;
uint8_t releaseFlag;
extern uint8_t phaseState;
uint8_t lastPhaseState;
uint8_t gateOn;
uint8_t drumRetrig;
uint32_t periodCount = 10000;
uint32_t lastGateCount = 5000;
uint32_t lastPeriodCount = 10000;
uint32_t holdLastGateCount = 10000;
uint32_t holdLastPeriodCount = 10000;
uint32_t gateRatio12Bit;
extern uint8_t lastAttackFlag;
extern uint8_t lastReleaseFlag;
extern uint8_t intoattackfromr;
extern uint8_t intoattackfroml;
extern uint8_t intoreleasefromr;
extern uint8_t intoreleasefroml;
uint8_t sampleHoldDirection;
enum sampleHoldDirection {toward_a, toward_b};


// timers used for clocking the expo envelope in drum mode and resampling the sample and holds
extern uint16_t sampleHoldTimer;
int drumCount;
int subCount;

uint8_t pendulumDirection;

// ADC/DAC DMA variables
uint32_t ADCReadings1[4];
uint32_t ADCReadings2[2];
uint32_t ADCReadings3[2];
#define time1Knob ADCReadings2[0]
#define time2Knob ADCReadings2[1]
#define time1CV ADCReadings1[0]
#define time2CV ADCReadings1[1]
#define morphCV ADCReadings1[2]
#define morphKnob ADCReadings3[0];
uint16_t dacbuffer1[1];
uint16_t dacbuffer2[1];

// mode indicators, determined in the main loop
enum scaleModes scaleMode;
enum controlModes controlMode;
enum phaseLockModes phaseLockMode;
enum sampleHoldModes sampleHoldMode;


uint8_t family;

extern TIM_HandleTypeDef htim1;



/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern DMA_HandleTypeDef hdma_adc1;
extern DMA_HandleTypeDef hdma_adc2;
extern DMA_HandleTypeDef hdma_adc3;
extern DMA_HandleTypeDef hdma_dac_ch1;
extern DMA_HandleTypeDef hdma_dac_ch2;
extern DAC_HandleTypeDef hdac;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim6;

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
* @brief This function handles DMA1 channel3 global interrupt.
*/
void DMA1_Channel3_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Channel3_IRQn 0 */




  /* USER CODE END DMA1_Channel3_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_dac_ch1);
  /* USER CODE BEGIN DMA1_Channel3_IRQn 1 */

  /* USER CODE END DMA1_Channel3_IRQn 1 */
}

/**
* @brief This function handles DMA1 channel4 global interrupt.
*/
void DMA1_Channel4_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Channel4_IRQn 0 */

  /* USER CODE END DMA1_Channel4_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_dac_ch2);
  /* USER CODE BEGIN DMA1_Channel4_IRQn 1 */

  /* USER CODE END DMA1_Channel4_IRQn 1 */
}

/**
* @brief This function handles TIM2 global interrupt.
*/
void TIM2_IRQHandler(void)
{
  /* USER CODE BEGIN TIM2_IRQn 0 */
    if(	HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_15) == GPIO_PIN_RESET) {

    	holdLastPeriodCount = lastPeriodCount;
    	lastPeriodCount = periodCount;
    	if (lastPeriodCount < 20) {lastPeriodCount = holdLastPeriodCount;};
    	periodCount = 0;

    	if (controlMode == knobDutyCycle) {
    		gateRatio12Bit = (lastGateCount << 12) / (lastPeriodCount << 12);

    		lastGateCount = (lastPeriodCount * time2Knob) >> 12; // last period count times the ratio of the adc to full scale

    		if (scaleMode == row) {
    		    		denomMult = 1;
    		    		rowSelect = gateRatio12Bit >> rowSelectBitShift;
    		    		rowIndex = time1Knob >> rowIndexBitShift;
    		    		numMult = *(*(rowScaleArray[rowScaleIndicator].scaleGrid + rowSelect) + rowIndex);
    		    	}

    		if (scaleMode == ratio) {
    		    		denomMult = 1;
    		    		rowIndex = time1Knob >> rowIndexBitShift;
    		    		numMult = *(*(ratioScaleArray[ratioScaleIndicator].scaleGrid) + rowIndex);
    		    		rowIndex = gateRatio12Bit >> rowIndexBitShift;
    		    		denomMult = *(*(ratioScaleArray[ratioScaleIndicator].scaleGrid + 1) + rowIndex);
    		    	}

    	}


    	else {

    		if (scaleMode == row) {
    			denomMult = 1;
    			rowSelect = time2Knob >> rowSelectBitShift;
    			rowIndex = time1CV >> rowIndexBitShift;
    			numMult = *(*(rowScaleArray[rowScaleIndicator].scaleGrid + rowSelect) + rowIndex);
    		}

    		if (scaleMode == ratio) {
    			denomMult = 1;
    			rowIndex = time1Knob >> rowIndexBitShift;
    			numMult = *(*(ratioScaleArray[ratioScaleIndicator].scaleGrid) + rowIndex);
    			rowIndex = time2Knob >> rowIndexBitShift;
    			denomMult = *(*(ratioScaleArray[ratioScaleIndicator].scaleGrid + 1) + rowIndex);
    		}

    	}

		attackInc = (span * numMult) / (float)(lastGateCount * denomMult);
		releaseInc = (span * numMult) / (float)((lastPeriodCount - lastGateCount) * denomMult);

    }
    else {

    	holdLastGateCount = lastGateCount;
    	lastGateCount = periodCount;
    	if (lastGateCount < 20) {lastGateCount = holdLastGateCount;};

    }


  /* USER CODE END TIM2_IRQn 0 */
  HAL_TIM_IRQHandler(&htim2);
  /* USER CODE BEGIN TIM2_IRQn 1 */

  /* USER CODE END TIM2_IRQn 1 */
}

/**
* @brief This function handles EXTI line[15:10] interrupts.
*/
void EXTI15_10_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI15_10_IRQn 0 */

	if (phaseState == 1) {
		LEDC_ON;
		LEDD_OFF;
	}
	if (phaseState == 2) {
		LEDC_OFF;
		LEDD_ON;
	}
	if (phaseState == 0) {
		LEDC_OFF;
		LEDD_OFF;
	}

  /* USER CODE END EXTI15_10_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_12);
  /* USER CODE BEGIN EXTI15_10_IRQn 1 */

  /* USER CODE END EXTI15_10_IRQn 1 */
}

/**
* @brief This function handles Timer 6 interrupt and DAC underrun interrupts.
*/
void TIM6_DAC_IRQHandler(void)
{
  /* USER CODE BEGIN TIM6_DAC_IRQn 0 */
	periodCount ++;


	if (oscillatorActive){

					//write the current oscillator value to dac1, and its inverse to dac2 (crossfading)
	  				dacbuffer2[0] = out;
					dacbuffer1[0] = 4095 - out;





	  				//call the function to advance the phase of the oscillator

	  		  	  	getPhase();
	  		  	  	//GPIOC->BSRR = (uint32_t)GPIO_PIN_13;
	  		  	  	// pin reset
	  		  	  	//call the appropriate
	  	  	  		lastPhaseState = phaseState;
	  	  	  		if (position < span) {attack(); phaseState = 1;}
	  	  	  		if (position >= span && position < spanx2) {release(); phaseState = 2;}
	  	  	  		// pin set
	  	  	  		//calculate the next morph index (we have it here for now so that it is ready to be scaled by drum mode, technically it is one sample behind)
	  	  	  		fixMorph = ADCReadings3[0] + ADCReadings1[2];
	  	  	  		//fixMorph = 0;
		  	  		if (fixMorph > 4095) {fixMorph = 4095;}
		  	  		if (fixMorph < 0) {fixMorph = 0;}


	  	  	  		//if we are in high speed and not looping, activate drum mode
	  		  	  	//if (speed == high && loop == noloop){
	  		  	  		//call the fuction that generates our expo decay and increments the oscillator
	  		  	  		//drum();
	  		  	  		//use the expo decay scaled by the manual morph control to modulate morph
	  		  	  		//fixMorph = myfix16_mul(exposcale, fixMorph);
	  		  	  	//}
	  	  	  		if (phaseState != lastPhaseState) {

	  	  	  			HAL_NVIC_SetPendingIRQ(EXTI15_10_IRQn);
	  	  	  		}

	}







					/*
	  		  	  	//moving towards a, trigger the appropriate sample and hold routine with flag toa
	  	  	  		if (intoattackfroml || intoreleasefromr) {
	  	  	  			sampleHoldDirection = toward_a;
	  	  	  			HAL_NVIC_SetPendingIRQ(EXTI15_10_IRQn);
	  	  	  		}
	  	  	  		//moving towards a, trigger the appropriate sample and hold routine with flag toa
	  	  			if (intoattackfromr || intoreleasefroml) {
		  	  	  		sampleHoldDirection = toward_b;
		  	  	  		HAL_NVIC_SetPendingIRQ(EXTI15_10_IRQn);
	  	  			}
	  	  			//grab the sample for b that was dropped in the interrupt after a 4 sample delay for aquisition
	  	  			if ((sampleHoldMode == b || sampleHoldMode == ab) && sampleHoldTimer == 4) {
	  	  				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);
	  	  			}
	  	  			//grab the sample that was dropped in the interrupt after a 4 sample delay for aquisition
	  	  			if (sampleHoldMode == decimate && sampleHoldTimer == 4) {
	  	  			  	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);
	  	  			  	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);
	  	  			}
	}
	//allow the sample and holds to pass when the oscillator is at rest
	else  {
				  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET);
				  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);
		  }*/




	/*TIM Update event*/
	if(__HAL_TIM_GET_FLAG(&htim6, TIM_FLAG_UPDATE) != RESET)
	  {
	    if(__HAL_TIM_GET_IT_SOURCE(&htim6, TIM_IT_UPDATE) !=RESET)
	    {
	      __HAL_TIM_CLEAR_FLAG(&htim6, TIM_FLAG_UPDATE);
	      HAL_TIM_PeriodElapsedCallback(&htim6);
	    }
	  }


  /* USER CODE END TIM6_DAC_IRQn 0 */
//  HAL_TIM_IRQHandler(&htim6);
  HAL_DAC_IRQHandler(&hdac);
  /* USER CODE BEGIN TIM6_DAC_IRQn 1 */

  /* USER CODE END TIM6_DAC_IRQn 1 */
}

/**
* @brief This function handles DMA2 channel1 global interrupt.
*/
void DMA2_Channel1_IRQHandler(void)
{
  /* USER CODE BEGIN DMA2_Channel1_IRQn 0 */
	//GPIOC->BRR = (uint32_t)GPIO_PIN_13; // pin reset
  /* USER CODE END DMA2_Channel1_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_adc2);
  /* USER CODE BEGIN DMA2_Channel1_IRQn 1 */
	//GPIOC->BSRR = (uint32_t)GPIO_PIN_13; // pin set
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
	LnSample = (int) position;
	//RnSample = (LnSample + 1);
	//bit shifting to divide by 512 takes full scale 12 bit and returns the quotient moudulo 512 (0-7)
	LnFamily = (uint32_t) fixMorph >> morphBitShiftRight;
	//RnFamily = (LnFamily + 1);
	//determine the fractional parts of the above truncations, which should be 0 to full scale 16 bit
	waveFrac = (uint16_t) ((position - LnSample) * 65536);
	morphFrac = ((fixMorph - (LnFamily << morphBitShiftRight)) << morphBitShiftLeft);
	//get values from the relevant wavetables
	Lnvalue1 = *(*(familyArray[familyIndicator].attackFamily + LnFamily) + LnSample);
	Rnvalue1 = *(*(familyArray[familyIndicator].attackFamily + LnFamily) + LnSample + 1);
	Lnvalue2 = *(*(familyArray[familyIndicator].attackFamily + LnFamily + 1) + LnSample);
	Rnvalue2 = *(*(familyArray[familyIndicator].attackFamily + LnFamily + 1) + LnSample + 1);
	//find the interpolated values for the adjacent wavetables
	interp1 = myfix16_lerp(Lnvalue1, Rnvalue1, waveFrac);
	//
	interp2 = myfix16_lerp(Lnvalue2, Rnvalue2, waveFrac);
	//interpolate between those based upon morph (biinterpolation)
	out = myfix16_lerp(interp1, interp2, morphFrac) >> 3;
	if (out > 4095) {out = 4095;};
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, out);




}








void release(void) {
	//calculate value based upon phase pointer "position" reflected over the span of the wavetable
	mirror = spanx2 - position; //changed from myfix16_mul
	//truncate position then add one to find the relevant indices for our wavetables, first within the wavetable then the actual wavetables in the family
	LnSample = (int) mirror;
	//RnSample = (LnSample + 1);
	//bit shifting to divide by 512 takes full scale 12 bit and returns the quotient moudulo 512 (0-7)
	LnFamily = (uint32_t) fixMorph >> morphBitShiftRight;
	//RnFamily = (LnFamily + 1);
	//determine the fractional parts of the above truncations, which should be 0 to full scale 16 bit
	waveFrac = (uint16_t) ((mirror - LnSample) * 65536);
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
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, out);


}






//defines an increment then checks the trigger mode, making the appropriate changes to playback when the oscillator is retriggered
// Questioning whether this works properly when position has to be calculated using attack inc + decay inc (at transitions) i.e. increment rate overshoot

void getPhase(void) {


		if (position < span) {
			inc = attackInc;
		}
		else if (position >= span && position < spanx2) {
			inc = releaseInc;
			}

		position = position + inc;

		if (position >= spanx2) {
			position = position - spanx2;
		}
		if (position < 0) {
			position = position + spanx2;
		}

}

int calcTime1(void) {

	//time1 = (time1Knob + time1CV) >> 4;
	//return time1;

}

int calcTime2(void) {

	//time2 = (time2Knob + time2CV) >> 4;
	//return time2;

}

void drum(void) {
	//advance the drumCount pointer according to the time2 knob
	drumCount = drumCount + ((time2Knob + (4095 - time2CV)) >> 7) + 1;
	//take the inverse of that in 12 bits
	subCount = 3840 - (drumCount >> 7);
	//if we get a retrigger, wait to cycle back through the period then retrigger (no pops)
	//if (intoattackfroml == 1 && retrig == 1) {retrig = 0, drumCount = 0;}
	//if we get to the end of the table, reset the envelope
	if (subCount <= 0) {oscillatorActive = 0, retrig = 0, drumCount = 0, position = 0; subCount = 0;}
	//this gets the appropriate value for the expo table and scales into the range of the fix16 fractional component (16 bits)
	exposcale = lookuptable[subCount] >> 10;
	//scale the oscillator
	out = myfix16_mul(out, exposcale);
}

int myfix16_mul(int in0, int in1) {
	int64_t result = (uint64_t)in0*in1;
	return result >> 16;
}

int myfix16_lerp(int in0, int in1, uint16_t inFract)
{
	int64_t tempOut = int64_mul_i32_i32(in0, (((int32_t)1 << 16) - inFract));
	tempOut = int64_add(tempOut, int64_mul_i32_i32(in1, inFract));
	tempOut = int64_shift(tempOut, -16);
	return (int)int64_lo(tempOut);
}

int myfix16_lerp8(int in0, int in1, uint16_t inFract)
{
	int64_t tempOut = int64_mul_i32_i32(in0, (((int32_t)1 << 8) - inFract));
	tempOut = int64_add(tempOut, int64_mul_i32_i32(in1, inFract));
	tempOut = int64_shift(tempOut, -16);
	return (int)int64_lo(tempOut);
}

/*this logic communicates entering and leaving the two stages in the main loop
void setAttack(void) {
	//indicate that we are not in release phase, and write the release gate low
	lastReleaseFlag = 0;
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11, GPIO_PIN_RESET);

	//this is a handy time to increment our decimate counter every sample
	//addachange
	sampleHoldTimer++;

	//indicate the direction in which the oscillator is moving in the value of the attack flag variable
	if (inc < 0) {attackFlag = 2;}
	else {attackFlag = 1;};

	//if the attack flag has changed since the last sample, raise the appropriate flag, if not, make sure that flag is set to 0
	if (attackFlag == 2 && attackFlag ==! lastAttackFlag) {
		intoattackfromr = 1;
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_10, GPIO_PIN_SET);
		sampleHoldTimer = 0;}

	else if (attackFlag == 1 && attackFlag ==! lastAttackFlag) {
		intoattackfroml = 1;
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_10, GPIO_PIN_SET);
		sampleHoldTimer = 0;}

	else {intoattackfroml = 0; intoattackfroml = 0;};
	//remember the value we set
	lastAttackFlag = attackFlag;
}



//parallel to setAttack
void setRelease(void) {
	lastAttackFlag = 0;
	sampleHoldTimer++;
	if (inc < 0) {releaseFlag = 2;}
	else {releaseFlag = 1;};
	if (releaseFlag == 2 && releaseFlag ==! lastReleaseFlag) {
		intoreleasefromr = 1;
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11, GPIO_PIN_SET);
		sampleHoldTimer = 0;}
	else if (releaseFlag == 1 && releaseFlag ==! lastReleaseFlag) {
		intoreleasefroml = 1;
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11, GPIO_PIN_SET);
		sampleHoldTimer = 0;}
	else {intoreleasefroml = 0; intoreleasefroml = 0;};
	lastReleaseFlag = releaseFlag;
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_10, GPIO_PIN_RESET);
}





/*
void getAverages(void) {
	time1Knob = doAverage(0);
	time2Knob  = doAverage(1);
	time1CV = doAverage(2);
	time2CV = doAverage(3);
	morphCV = doAverage(4);
	morphKnob = doAverage(5);
}

uint32_t doAverage(uint32_t reading) {
	uint32_t averageCounter = 0;
	for(int u = reading; reading < 48; reading + 6) {
		averageCounter = averageCounter + ADCReadings[u];
	}
	return averageCounter >> 3;
}
*/

//void EXTI15_10_IRQHandler(void)
//{

  /* USER CODE BEGIN EXTI15_10_IRQn 0 */
	/*
	if (sampleHoldDirection == toward_a) { //this indicates that the pointer is "moving towards a", which informs our logic about which sample and hold operation should be performed per mode

		  if (sampleHoldMode == a) { // sample a, for the sample and hold, pin low or GPIO_PIN_RESET holds and pin high or GPIO_PIN_SET tracks
			  //HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);
			  GPIOB->BSRR = (uint32_t)4 << 16U;
		  }
		  else if (sampleHoldMode == b) { // drop b to be picked up by decimate counter (which samples after a delay allowing the sample and hold to track to the new value (time constant dependent on sampling cap size) so that b can be "resampled" per cycle to keep things interesting
			  //HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);
			  GPIOB->BSRR = 5;
		  	  sampleHoldTimer = 0;
		  }
		  else if (sampleHoldMode == ab) { // sample a and drop b to be picked up by decimate counter as above. since our oscillator generally rests at 0, b needs to remain sampled through the attack and release phase to avoid a discontinuity in attack
			  //HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);
			  //HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);
			  GPIOB->BSRR = (uint32_t)4 << 16U;
			  GPIOB->BSRR = 5;
			  sampleHoldTimer = 0;
		  }
		  else if (sampleHoldMode == antidecimate) { // sample a and drop b, weird pseudo decimate mode where a is sampled when moving to b while b tracks and likewise
			  //HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);
			  //HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);
			  GPIOB->BSRR = (uint32_t)4 << 16U;
			  GPIOB->BSRR = 5;
		  }
	      else if (sampleHoldMode == decimate) {// drop b to be picked up by decimate counter, aka resample b when at a. this is true decimate mode
			  //HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);
			  GPIOB->BSRR = 5;
		  	  sampleHoldTimer = 0;
		  }
	}
	else {  // if we are moving toward b
			if (sampleHoldMode == a) { // release a
		  	  	//HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET);
		  	    GPIOB->BSRR = 4;
		  	}
			// if sampleHoldMode == 2, b remains sampled

		  	else if (sampleHoldMode == ab) { // release a, b remains sampled
		  	  	//HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET);
		  	    GPIOB->BSRR = 4;
		  	}
		  	else if (sampleHoldMode == antidecimate) {// sample b and drop a, mirroring what happens when moving towards b above
		  	  	//HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET);
		  	  	//HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);
		  		GPIOB->BSRR = 4;
		  		GPIOB->BSRR = (uint32_t)5 << 16U;

		  	}
		  	else if (sampleHoldMode == decimate) {// drop a to be picked up by decimate counter
		  	  	//HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET);
		  		GPIOB->BSRR = 4;
		  		sampleHoldTimer = 0;
		  	}

	}*/
//}

/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
