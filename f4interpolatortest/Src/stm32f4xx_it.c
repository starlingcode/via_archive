/**
  ******************************************************************************
  * @file    stm32f4xx_it.c
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
#include "stm32f4xx_hal.h"
#include "stm32f4xx.h"
#include "stm32f4xx_it.h"

/* USER CODE BEGIN 0 */
#include "fixmath.h"
#include "int64.h"
#include "fix16.h"
#include "tables.h"

//entries per wavetable
#define N 65
//wavetables per family
#define M 9

// wavetable size - 1 in fix16 and that number doubled
#define span 4194304
#define spanx2 8388608

//assign names to our ADC readings that correspond to how they interface with the UI
#define time1knob ADCReadings[0]
#define time2knob ADCReadings[1]
#define time1cv ADCReadings[2]
#define time2cv ADCReadings[3]
#define morphcv ADCReadings[4]
#define morphknob ADCReadings[5]

//define our wavetable family as two arrays of 9 wavetables (defined in tables.h), one for attack, one for release

//uint16_t attackfamily[M][N] = {perlin6_1, perlin6_2, perlin6_3, perlin6_4, perlin6_5, perlin6_6, perlin6_7, perlin6_8, perlin6_8};
//uint16_t releasefamily[M][N] = {perlin6_1, perlin6_2, perlin6_3, perlin6_4, perlin6_5, perlin6_6, perlin6_7, perlin6_8, perlin6_8};
//uint16_t releasefamily[M][N] = {bittab1, bittab2, bittab3, bittab4, bittab5, bittab6, bittab7, bittab8, bittab9};
//uint16_t attackfamily[M][N] = {bittab1, bittab2, bittab3, bittab4, bittab5, bittab6, bittab7, bittab8, bittab9};
uint16_t attackfamily[M][N] = {sinefold_ctr_1, sinefold_ctr_2, sinefold_ctr_3, sinefold_ctr_4, sinefold_ctr_5, sinefold_ctr_6, sinefold_ctr_7, sinefold_ctr_8, sinefold_ctr_9};
uint16_t releasefamily[M][N] = {sinefold_ctr_1, sinefold_ctr_2, sinefold_ctr_3, sinefold_ctr_4, sinefold_ctr_5, sinefold_ctr_6, sinefold_ctr_7, sinefold_ctr_8, sinefold_ctr_9};
//uint16_t attackfamily[M][N] = {bounce1, bounce2, bounce3, bounce4, bounce5, bounce6, bounce7, bounce8, bounce9};
//uint16_t releasefamily[M][N] = {bounce1, bounce2, bounce3, bounce4, bounce5, bounce6, bounce7, bounce8, bounce9};
//uint16_t attackfamily[M][N] = {trifold_1, trifold_2, trifold_3, trifold_4, trifold_5, trifold_6, trifold_7, trifold_8, trifold_9};
//uint16_t releasefamily[M][N] = {trifold_1, trifold_2, trifold_3, trifold_4, trifold_5, trifold_6, trifold_7, trifold_8, trifold_9};
//uint16_t attackfamily[M][N] = {triodd_1, triodd_2, triodd_3, triodd_4, triodd_5, triodd_6, triodd_7, triodd_8, triodd_9};
//uint16_t releasefamily[M][N] = {triodd_1, triodd_2, triodd_3, triodd_4, triodd_5, triodd_6, triodd_7, triodd_8, triodd_9};
//uint16_t attackfamily[M][N] = {trifudge_1, trifudge_2, trifudge_3, trifudge_4, trifudge_5, trifudge_6, trifudge_7, trifudge_8, trifudge_9};
//uint16_t releasefamily[M][N] = {trifudge_1, trifudge_2, trifudge_3, trifudge_4, trifudge_5, trifudge_6, trifudge_7, trifudge_8, trifudge_9};

//this is used for our 1v/oct and bonus expo envelope
const fix16_t lookuptable[4096] = expotable10oct;

//these are the variables used to generate the phase information that feeds our interpolations
uint32_t fixmorph;
fix16_t position;
fix16_t mirror;
fix16_t inc;

//sample indices and interpolation fraction for the wavetable
int LnSample;
int RnSample;
uint16_t wavefrac;

//wavetable indices (within the family) and interpoation fraction for the morph interpolation
int LnFamily;
int RnFamily;
uint16_t morphfrac;

//actual values and interpolation result for one wavetable
fix16_t Lnvalue1;
fix16_t Rnvalue1;
fix16_t interp1;

//actual values and interpolation result for the adjacent wavetable
fix16_t Lnvalue2;
fix16_t Rnvalue2;
fix16_t interp2;

//most recent value from our expo decay
fix16_t exposcale;

//lastest result of the biinterpolation between interp1 and interp2 (scaled in drum mode)
extern fix16_t out;




void Attack(void);
void Release(void);
void GetPhase(void);
void Drum(void);
void setattackflag(void);
void setreleaseflag(void);

// "playback" flags that set the oscillator in motion
volatile int trig = 0;
volatile int retrig = 0;

// logic used to signal oscillator phase position
uint8_t attackflag;
uint8_t releaseflag;
extern uint8_t lastattackflag;
extern uint8_t lastreleaseflag;
extern uint8_t intoattackfromr;
extern uint8_t intoattackfroml;
extern uint8_t intoreleasefromr;
extern uint8_t intoreleasefroml;
uint8_t toa;

// timers used for clocking the expo envelope in drum mode and resampling the sample and holds
extern uint16_t decimatecounter;
fix16_t drumcount;
fix16_t subcount;
uint8_t pendulumcount;

// ADC/DAC DMA variables
uint32_t ADCReadings[6];
uint16_t dacbuffer1;
uint16_t dacbuffer2;

// mode indicators, determined in the main loop
uint8_t speed;
uint8_t loop;
uint8_t trigmode;
uint8_t samphold;
uint8_t family;




/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern DMA_HandleTypeDef hdma_adc1;
extern DMA_HandleTypeDef hdma_dac1;
extern DMA_HandleTypeDef hdma_dac2;
extern DAC_HandleTypeDef hdac;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim6;

/******************************************************************************/
/*            Cortex-M4 Processor Interruption and Exception Handlers         */ 
/******************************************************************************/

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
/* STM32F4xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f4xx.s).                    */
/******************************************************************************/

/**
* @brief This function handles DMA1 stream5 global interrupt.
*/
void DMA1_Stream5_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Stream5_IRQn 0 */

  /* USER CODE END DMA1_Stream5_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_dac1);
  /* USER CODE BEGIN DMA1_Stream5_IRQn 1 */

  /* USER CODE END DMA1_Stream5_IRQn 1 */
}

/**
* @brief This function handles DMA1 stream6 global interrupt.
*/
void DMA1_Stream6_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Stream6_IRQn 0 */

  /* USER CODE END DMA1_Stream6_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_dac2);
  /* USER CODE BEGIN DMA1_Stream6_IRQn 1 */

  /* USER CODE END DMA1_Stream6_IRQn 1 */
}

/**
* @brief This function handles TIM2 global interrupt.
*/
void TIM2_IRQHandler(void)
{
  /* USER CODE BEGIN TIM2_IRQn 0 */
	trig = 1;
	retrig = 1;

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
	if (toa == 0) { //this indicates that the pointer is "moving towards a", which informs our logic about which sample and hold operation should be performed per mode

		  if (samphold == 1) { // sample a, for the sample and hold, pin low or GPIO_PIN_RESET holds and pin high or GPIO_PIN_SET tracks
			  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);
		  }
		  else if (samphold == 2) { // drop b to be picked up by decimate counter (which samples after a delay allowing the sample and hold to track to the new value (time constant dependent on sampling cap size) so that b can be "resampled" per cycle to keep things interesting
			  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);
		  	  	decimatecounter = 0;
		  }
		  else if (samphold == 3) { // sample a and drop b to be picked up by decimate counter as above. since our oscillator generally rests at 0, b needs to remain sampled through the attack and release phase to avoid a discontinuity in attack
			  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);
			  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);
		  	  	decimatecounter = 0;
		  }
		  else if (samphold == 4) { // sample a and drop b, weird pseudo decimate mode where a is sampled when moving to b while b tracks and likewise
			  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);
			  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);
		  }
	      else if (samphold == 5) {// drop b to be picked up by decimate counter, aka resample b when at a. this is true decimate mode
			  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);
		  	  	decimatecounter = 0;
		  }
	}
	if (toa == 1) {
			if (samphold == 1) { // release a
		  	  	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET);
		  	}
			// if samphold == 2, b remains sampled

		  	else if (samphold == 3) { // release a, b remains sampled
		  	  	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET);
		  	}
		  	else if (samphold == 4) {// sample b and drop a, mirroring what happens when moving towards b above
		  	  	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET);
		  	  	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);
		  	}
		  	else if (samphold == 5) {// drop a to be picked up by decimate counter
		  	  	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET);
		  	  	decimatecounter = 0;
		  	}
	}

  /* USER CODE END EXTI15_10_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_12);
  /* USER CODE BEGIN EXTI15_10_IRQn 1 */

  /* USER CODE END EXTI15_10_IRQn 1 */
}

/**
* @brief This function handles TIM6 global interrupt, DAC1 and DAC2 underrun error interrupts.
*/
void TIM6_DAC_IRQHandler(void)
{
  /* USER CODE BEGIN TIM6_DAC_IRQn 0 */
	// when trig is 1, the oscillator is active
	if (trig ==1){
					//writing this pin low at the start of our interrupt then setting it upon completion allows easy clocking with a scope
					HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_RESET);

					//write the current oscillator value to dac1, and its inverse to dac2 (crossfading)
	  				dacbuffer2 = out;
	  				dacbuffer1 = (65535 - out);

	  				//call the function to advance the phase of the oscillator
	  		  	  	GetPhase();

	  		  	  	//call the appropriate
	  	  	  		if (position < span) {Attack(); setattackflag();}
	  	  	  		if (position >= span && position < spanx2) {Release(); setreleaseflag();}

	  	  	  		//if we are in high speed and not looping, activate drum mode
	  		  	  	if (speed == 0 && loop == 0){
	  		  	  		//call the fuction that generates our expo decay and increments the oscillator
	  		  	  		Drum();
	  		  	  		//use the expo decay scaled by the manual morph control to modulate morph
	  		  	  		fixmorph = fix16_mul(exposcale, morphknob);
	  		  	  	}
	  		  	  	else {fixmorph = morphknob + morphcv;}

	  		  	  	//moving towards a, trigger the appropriate sample and hold routine with flag toa
	  	  	  		if (intoattackfroml == 1 || intoreleasefromr == 1) {
	  	  	  			toa = 0;
	  	  	  			HAL_NVIC_SetPendingIRQ(EXTI15_10_IRQn);
	  	  	  		}
	  	  	  		//moving towards a, trigger the appropriate sample and hold routine with flag toa
	  	  			if (intoattackfromr == 1 || intoreleasefroml == 1) {
		  	  	  		toa = 1;
		  	  	  		HAL_NVIC_SetPendingIRQ(EXTI15_10_IRQn);
	  	  			}
	  	  			//grab the sample for b that was dropped in the interrupt after a 4 sample delay for aquisition
	  	  			if ((samphold == 2 || samphold == 3) && decimatecounter == 4) {
	  	  				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);
	  	  			}
	  	  			//grab the sample that was dropped in the interrupt after a 4 sample delay for aquisition
	  	  			if (samphold == 5 && decimatecounter == 4) {
	  	  			  	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);
	  	  			  	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);
	  	  			}
	  	  			//this completes the benchmark test
	  				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_SET);
	}
	//allow the sample and holds to pass when the oscillator is at rest
	if (trig == 0) {
				  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET);
				  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);
		  }

  /* USER CODE END TIM6_DAC_IRQn 0 */
  HAL_DAC_IRQHandler(&hdac);
  HAL_TIM_IRQHandler(&htim6);
  /* USER CODE BEGIN TIM6_DAC_IRQn 1 */

  /* USER CODE END TIM6_DAC_IRQn 1 */
}

/**
* @brief This function handles DMA2 stream0 global interrupt.
*/
void DMA2_Stream0_IRQHandler(void)
{
  /* USER CODE BEGIN DMA2_Stream0_IRQn 0 */

  /* USER CODE END DMA2_Stream0_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_adc1);
  /* USER CODE BEGIN DMA2_Stream0_IRQn 1 */

  /* USER CODE END DMA2_Stream0_IRQn 1 */
}

/* USER CODE BEGIN 1 */

void Attack(void) {
	//calculate value based upon phase pointer "position"
	//truncate position then add one to find the relevant indices for our wavetables, first within the wavetable then the actual wavetables in the family
	LnSample = (int) (position >> 16);
	RnSample = (LnSample + 1);
	//bit shifting to divide by 512 takes full scale 12 bit and returns the quotient moudulo 512 (0-7)
	LnFamily = (uint32_t) fixmorph >> 9;
	RnFamily = (LnFamily + 1);
	//determine the fractional parts of the above truncations, which should be 0 to full scale 16 bit
	wavefrac = (uint16_t) position;
	morphfrac = ((fixmorph - (LnFamily << 9)) << 7);
	//get values from the relevant wavetables
	Lnvalue1 = attackfamily[LnFamily][LnSample];
	Rnvalue1 = attackfamily[LnFamily][RnSample];
	Lnvalue2 = attackfamily[RnFamily][LnSample];
	Rnvalue2 = attackfamily[RnFamily][RnSample];
	//find the interpolated values for the adjacent wavetables
	interp1 = fix16_lerp16(Lnvalue1, Rnvalue1, wavefrac);
	interp2 = fix16_lerp16(Lnvalue2, Rnvalue2, wavefrac);
	//interpolate between those based upon morph (biinterpolation)
	out = fix16_lerp16(interp1, interp2, morphfrac) >> 3;
}








void Release(void) {
	//calculate value based upon phase pointer "position" reflected over the span of the wavetable
	mirror = fix16_sub(spanx2, position);
	//truncate position then add one to find the relevant indices for our wavetables, first within the wavetable then the actual wavetables in the family
	LnSample = (int) (mirror >> 16);
	RnSample = (LnSample + 1);
	//bit shifting to divide by 512 takes full scale 12 bit and returns the quotient moudulo 512 (0-7)
	LnFamily = (uint32_t) fixmorph >> 9;
	RnFamily = (LnFamily + 1);
	//determine the fractional parts of the above truncations, which should be 0 to full scale 16 bit
	wavefrac = (uint16_t) mirror;
	morphfrac = ((fixmorph - (LnFamily <<  9)) << 7);
	//get values from the relevant wavetables
	Lnvalue1 = releasefamily[LnFamily][LnSample];
	Rnvalue1 = releasefamily[LnFamily][RnSample];
	Lnvalue2 = releasefamily[RnFamily][LnSample];
	Rnvalue2 = releasefamily[RnFamily][RnSample];
	//find the interpolated values for the adjacent wavetables
	interp1 = fix16_lerp16(Lnvalue1, Rnvalue1, wavefrac);
	interp2 = fix16_lerp16(Lnvalue2, Rnvalue2, wavefrac);
	//interpolate between those based upon morph (biinterpolation)
	out = fix16_lerp16(interp1, interp2, morphfrac) >> 3;
}






//defines an increment then checks the trigger mode, making the appropriate changes to playback when the oscillator is retriggered
void GetPhase(void) {
	//define increment function for high speed mode with limits, tim2 parameter controls is removed from the equation if we are in drum mode
	if (speed == 0) {
		//multiply a base (modualted by linear FM) by a lookup value from a 10 octave expo table (modulated by expo FM)
		//if we are in drum mode, no linear FM
		if (loop == 0) {inc = fix16_mul(2000, (lookuptable[(4095 - (time1knob + time1cv) - 24)] >> 2));}
		else {inc = fix16_mul((time2cv - 2048) + (time2knob - 4096), (lookuptable[(4095 - (time1knob + time1cv) - 24)] >> 2));}
		if (inc > 1048576) {inc = 1048576;}
		if (inc < -1048576) {inc = -1048576;}
	}

	//define increment for low speed mode, split up timing over two pot/cv combos
	else if (speed == 1) {
		//use tim1 knob + cv for setting inc in attack phase, blank the retrigger flag if not in hard sync mode
		if (position < span) {
			inc = time1knob + time1cv;
			//wipe any retrigger flags unless we are in hard sync mode during attack
			if (trigmode ==! 1) {retrig = 0;}}
		//use tim2 knob + cv for setting inc in release phase
		if (position >= span) {inc = time2knob + time2cv;}
	};

	//in gate (2) mode, if retrig flag is raised when in release, work backwards to attack so long as gate is high
	//if gate is released when in attack phase, increment backwards through attack at the release speed
	//this mimics a retrigger on a traditional ADSR
	if (trigmode == 2){
		if (position < span && HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_RESET) {
			if (speed == 1) {inc = -time2knob;}
			if (speed == 0) {inc = -inc;}
		}
		if (position > span && retrig == 1 && HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_SET) {
			if (speed == 1) {inc = -time1knob;}
			if (speed == 0) {inc = -inc;}
		}
	}

	//in non gated retrigger (3) mode, work backwards to attack if retrig flag is raised in release regardless of gating
	else if (trigmode == 3){
		if (position <= span) {retrig = 0;}
		if (position > span && retrig == 1) {
			if (speed == 1) {inc = -time1knob;}
			if (speed == 0) {inc = -inc;}
		}
	}

	 //in pendulum mode,a retrtrigger increments a counter modulo 2, then the retrigger flag is reset to 0
	//when that counter is 1, we make flip the sign of the increment, changing direction of playback in the wavetable
	else if (trigmode == 4) {
		if  (retrig == 1) {
			pendulumcount = (pendulumcount + 1) % 2;
			retrig = 0;}
		//reset our count to 0 so we always increment forward through attack when triggering from rest
		if  (loop == 0 && (position <= 0 || position >= spanx2)) {pendulumcount = 0;}

		//reverse direction of the oscillator
		if (pendulumcount == 1) {
			inc = -inc;
		}

	};

	// and here is the result of what we have done
	position = position + inc;

	// a retrigger in hard sync overrides everything above, notice we didnt wipe the retrigger flag during attack in this mode
	if (trigmode == 1 && retrig == 1) {
		position = 0;
		retrig = 0;
	}
	// if we have incremented outside of our table, wrap back around to the other side and stop/reset if we are in LF 1 shot mode
	if (position >= spanx2) {
		position = position - spanx2;
		if (loop == 0 && speed ==! 0){
			trig = 0;
			retrig = 0;
			position = 0;
		}
	}
	// same as above but for when we are backtracking through the attack phase aka negative increment
	else if (position < 0) {
		position = position + spanx2;
		if (loop == 0 && speed ==! 0){
		trig = 0;
		retrig = 0;
		position = 0;
		}
	}
}




//this logic communicates entering and leaving the two stages in the main loop
void setattackflag(void) {
	//indicate that we are not in release phase, and write the release gate low
	lastreleaseflag = 0;
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11, GPIO_PIN_RESET);

	//this is a handy time to increment our decimate counter every sample
	//addachange
	decimatecounter = decimatecounter + 1;

	//indicate the direction in which the oscillator is moving in the value of the attack flag variable
	if (inc < 0) {attackflag = 2;}
	else {attackflag = 1;};

	//if the attack flag has changed since the last sample, raise the appropriate flag, if not, make sure that flag is set to 0
	if (attackflag == 2 && attackflag ==! lastattackflag) {
		intoattackfromr = 1;
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_10, GPIO_PIN_SET);
		decimatecounter = 0;}

	else if (attackflag == 1 && attackflag ==! lastattackflag) {
		intoattackfroml = 1;
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_10, GPIO_PIN_SET);
		decimatecounter = 0;}

	else {intoattackfroml = 0; intoattackfroml = 0;};
	//remember the value we set
	lastattackflag = attackflag;
}



//parallel to setattackflag
void setreleaseflag(void) {
	lastattackflag = 0;
	decimatecounter = decimatecounter + 1;
	if (inc < 0) {releaseflag = 2;}
	else {releaseflag = 1;};
	if (releaseflag == 2 && releaseflag ==! lastreleaseflag) {
		intoreleasefromr = 1;
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11, GPIO_PIN_SET);
		decimatecounter = 0;}
	else if (releaseflag == 1 && releaseflag ==! lastreleaseflag) {
		intoreleasefroml = 1;
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11, GPIO_PIN_SET);
		decimatecounter = 0;}
	else {intoreleasefroml = 0; intoreleasefroml = 0;};
	lastreleaseflag = releaseflag;
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_10, GPIO_PIN_RESET);
}




void Drum(void) {
	//advance the drumcount pointer according to the time2 knob
	drumcount = drumcount + (time2knob >> 6) + 1;
	//take the inverse of that in 12 bits
	subcount = 4096 - (drumcount >> 4);
	//if we get a retrigger, wait to cycle back through the period then retrigger (no pops)
	if (intoattackfroml == 1 && retrig == 1) {retrig = 0, drumcount = 0;}
	//if we get to the end of the table, reset the envelope
	if (subcount <= 0) {trig = 0, retrig = 0, drumcount = 0, position = 0;}
	//this gets the appropriate value for the expo table and scales into the range of the fix16 fractional component (16 bits)
	exposcale = lookuptable[subcount] >> 10;
	//scale the oscillator
	out = fix16_mul (out, exposcale);
}


/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
