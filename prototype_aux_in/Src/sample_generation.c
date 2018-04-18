#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"

#include "tables.h"
#include "main.h"
#include "int64.h"
#include "interrupt_functions.h"

// wavetable size - 1 in fix16 and that number doubled
extern int span;
extern int spanx2;

// per family bit shift amounts to determine the morph  (defined on wavetable family change)
uint32_t morphBitShiftRight;
uint32_t morphBitShiftLeft;

extern uint32_t tableSizeCompensation;

// averaged ADC values
uint32_t morphCVAverage;
uint32_t morphKnobAverage;

// store and declare our exponential lookup table in RAM (defined in tables.h)
extern int expoTable[4095] = expotable10oct;

// mode indicators, defined in functions found in user_interface.c
enum speedTypes speed;
enum loopTypes loop;
enum trigModeTypes trigMode;
enum sampleHoldModeTypes sampleHoldMode;

// declare the necessary timer handles for use in these functions (set up in main.c, interrupts in stm32f3xx_it.c)
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim3;

// declarations for the functions defined below, attribute places them in "CCMRAM" for maximum efficiency
//void getSample(uint32_t) __attribute__((section("ccmram")));
//void getSampleCubicSpline(uint32_t) __attribute__((section("ccmram")));
void getSampleQuinticSpline(int position) __attribute__((section("ccmram")));

// this holds our current table
uint16_t fullTableHoldArray[9][517];

// this is called to write our last sample to the dacs and generate a new sample
void dacISR(void) {
	uint32_t lastPhase;
	int morphLimit;

	//PROFILING_START("MAIN startup timing");

#ifndef _BUILD_REV_2
#else
	// remove for compatibility w/ rev2 (black back) boards
	if ((GPIOA->IDR & GPIO_PIN_11) != (uint32_t) GPIO_PIN_RESET) {
#endif
		if ((OSCILLATOR_ACTIVE)) {

			// write the current contour generator value to dac1, and its inverse to dac2 (this actually performs the interpolation)
			((*(volatile uint32_t *) DAC1_ADDR) = (4095 - out));
			((*(volatile uint32_t *) DAC2_ADDR) = (out));

			// get our averages for t2 and morph cv

			// hold the phase state (attack or release) from the last sample
			lastPhase = PHASE_STATE;
			//PROFILING_EVENT("DAC Uptdated");

			// call the function to advance the phase of the contour generator
			position = (*getPhase)(position);
			//PROFILING_EVENT("Phase Accquired");

			// determine whether our newly calculated phase value "position" is in the "attack" or "release" portion of the cycle
			// call the function that generates our next sample based upon the phase value "position"
			// pass that function a 1 or a 0 to indicate whether we are in attack or release

			getSampleQuinticSpline(position);

			if (position < span) {
				CLEAR_PHASE_STATE;
				//getSample(0);
				//getSampleCubicSpline(0);
				if (RUNTIME_DISPLAY) { // if the runtime display is on, show our mode
					__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, out);
					__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, fixMorph >> 2);
				}
			}
			if (position >= span) {
				SET_PHASE_STATE;
				//getSample(1);
				//getSampleCubicSpline(1);
				if (RUNTIME_DISPLAY) { // if the runtime display is on, show our mode
					__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, out);
					__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, fixMorph >> 2);
				}

			}

			//PROFILING_EVENT("Sampling Complete");

			// calculate our "morph" parameter as a function of the morph knob, CV, and our contour generator frequency
			// we use morphAverage, which is a running sum of the last 8 values (a running average without the division)
			// we basically check whether the morphCV is less than or greater than half of its full scale value
			// if it is less than half of full scale, we do a linear interpolation between our current knob value and 0 using the CV value as the interpolation fraction
			// if it is more than half of full scale, we do a linear interpolation between our current knob value and full scale using the CV value as the interpolation fraction
			// in both of these cases, we generate our interpolation fraction by simple bit shifting a sum involving the halfway scale value and the CV
			// basically, we figure out how far our morphCV is away from the halfway point and then scale that up to a 16 bit integer
			// this works because we assume that all of our ADC ranges are a power of two

			// we then scale back our morph value as frequency increases. with a table that exhibits a steadily increasing spectral content as morph increases, this serves as anti-aliasing

			// is our CV greater than half-scale (the big numbers are because we have a running sum of 8
			if ((131071 - morphCVAverage) >= 65536) {
				// this first does the aforementioned interpolation between the knob value and full scale then scales back the value according to frequency
				fixMorph = fix16_lerp(morphKnobAverage, 4095, ((131071 - morphCVAverage) - 65536));
			}
			else {
				// analogous to above except in this case, morphCV is less than halfway
				fixMorph = fix16_lerp(0, morphKnobAverage, (131071 - morphCVAverage));
			}

			// if we are in high speed and not looping, activate drum mode
			if (DRUM_MODE) {
				// this next bit generates our expo decay and scales amp
				// it gets the appropriate value for the expo table and scales into the range of the fix16 fractional component (16 bits)
				if (DRUM_ATTACK) {
					// maintain a software-based counter to increment through a linear "attack" slope sample per sample
					attackCount = attackCount + (inc >> 11);
					// if we get to our maximum value (this is the index where the value is 2^26)
					// this overflow value gives us a known range for our values from the lookup table
					if (attackCount > 3840) {
						// write to the flag word that we are done with our attack slope
						CLEAR_DRUM_ATTACK_ON;
						// since we use this to look up from the table, clamp it at our max value
						attackCount = 3840;
						// enable the timer that will generate our release slope
						__HAL_TIM_ENABLE(&htim3);
						// get our value from the lookup table, scale it, this will be 2^16
						drumModValue = expoTable[attackCount] >> 10;
						// reset our counter to 0
						attackCount = 0;
						// indicate that we are now in the "release" phase of our drum envelope
						SET_DRUM_RELEASE;
					}
					else {
						// otherwise, use our counter to look up a value from the table
						// that gets scaled to 0 - 2^16
						drumModValue = expoTable[attackCount] >> 10;
					}
				}
				else if (DRUM_RELEASE) {
					//if we are in release, use timer counter to look up a value from the table
					//that gets scaled to 0 - 2^16
					drumModValue = expoTable[TIM3->CNT] >> 10;
				}
				//scale the contour generator, an integer 0 - 2^16 is 0-1 in our 16 bit fixed point
				if (AMP_MOD) {
					out = fix16_mul(out, drumModValue);
				}
				//apply the scaling value to the morph knob
				if (MORPH_MOD) {
					fixMorph = fix16_mul(fixMorph, drumModValue);
				}
			}
			else {
				if (BANDLIMIT) {
					morphLimit = fix16_mul(4095, 65536 - ((my_abs(inc)) >> 5));
					if (morphLimit < 0) {morphLimit = 0;}
					if (fixMorph > morphLimit) {
						fixMorph = morphLimit;
					}
				}
			}

			// if we transition from one phase state to another, enable the transition handler interrupt
			if (((PHASE_STATE) != lastPhase)) {
				HAL_NVIC_SetPendingIRQ(EXTI15_10_IRQn);
			}
			//PROFILING_EVENT("ISR_Complete");
			//PROFILING_STOP();
		}
		else {
			//turn off the display if the contour generator is inactive and we are not switching modes
			if (RUNTIME_DISPLAY) {
				((*(volatile uint32_t *) DAC1_ADDR) = (4095));
				((*(volatile uint32_t *) DAC2_ADDR) = (0));
				LEDC_OFF
				LEDD_OFF
				__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);
				__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);
				__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
			}
		}
#ifndef _BUILD_REV_2
#else
	} //remove for compativility with rev2 boards
#endif
}



void getSampleQuinticSpline(int position) {

	// adapted from code shared by Josh Scholar on musicDSP.org
	// https://web.archive.org/web/20170705065209/http://www.musicdsp.org/showArchiveComment.php?ArchiveID=60

#define PRECALC1_6 2796202

    /* in this function, we use our phase position to get the sample to give to our dacs using a quintic spline interpolation technique
    essentially, we need to get 6 pairs of sample values and two "fractional arguments" (where are we at in between those sample values)
    one fractional argument determines the relative position in a linear interpolation between the sample values (morph)
    the other is the fractional phase argument used in the interpolation calculation
    */

    uint32_t LnSample;  // indicates the left most sample in the neighborhood of sample values around the phase pointer
    uint32_t LnFamily;  // indicates the nearest neighbor (wavetable) to our morph value in the family
    uint32_t waveFrac;  // indicates the fractional distance between the nearest sample values in terms of phase
    q31_t morphFrac; // indicates the fractional distance between our nearest neighbors in the family
    uint32_t lFvalue0; // samples
    uint32_t rFvalue0;
    uint32_t lFvalue1;
    uint32_t rFvalue1;
    uint32_t lFvalue2;
    uint32_t rFvalue2;
    uint32_t lFvalue3;
    uint32_t rFvalue3;
    uint32_t lFvalue4;
    uint32_t rFvalue4;
    uint32_t lFvalue5;
    uint32_t rFvalue5;
    uint32_t interp0;  // results of the interpolations between sample pairs
	uint32_t interp1;
	uint32_t interp2;
	uint32_t interp3;
	uint32_t interp4;
	uint32_t interp5;





	// we do a lot of tricky bitshifting to take advantage of the structure of a 16 bit fixed point number
	// truncate position then add two to find the left neighboring sample of the phase pointer
	LnSample = (position >> 16) + 2;

	// bit shifting to divide by the correct power of two takes a 12 bit number (our fixMorph) and returns the a quotient in the range of our family size
	LnFamily = fixMorph >> morphBitShiftRight;

	// determine the fractional part of our phase position by masking off the integer
	waveFrac = 0x0000FFFF & position;

	// we have to calculate the fractional portion and get it up to full scale q31_t
	morphFrac = (fixMorph - (LnFamily << morphBitShiftRight)) << morphBitShiftLeft;

		lFvalue0 = fullTableHoldArray[LnFamily][LnSample - 2];
		lFvalue1 = fullTableHoldArray[LnFamily][LnSample - 1];
		lFvalue2 = fullTableHoldArray[LnFamily][LnSample];
		lFvalue3 = fullTableHoldArray[LnFamily][LnSample + 1];
		lFvalue4 = fullTableHoldArray[LnFamily][LnSample + 2];
		lFvalue5 = fullTableHoldArray[LnFamily][LnSample + 3];
		rFvalue0 = fullTableHoldArray[LnFamily + 1][LnSample- 2];
		rFvalue1 = fullTableHoldArray[LnFamily + 1][LnSample - 1];
		rFvalue2 = fullTableHoldArray[LnFamily + 1][LnSample];
		rFvalue3 = fullTableHoldArray[LnFamily + 1][LnSample + 1];
		rFvalue4 = fullTableHoldArray[LnFamily + 1][LnSample + 2];
		rFvalue5 = fullTableHoldArray[LnFamily + 1][LnSample + 3];

		// find the interpolated values for the adjacent wavetables using an efficient fixed point linear interpolation
		interp0 = fix16_lerp(lFvalue0, rFvalue0, morphFrac);
		interp1 = fix16_lerp(lFvalue1, rFvalue1, morphFrac);
		interp2 = fix16_lerp(lFvalue2, rFvalue2, morphFrac);
		interp3 = fix16_lerp(lFvalue3, rFvalue3, morphFrac);
		interp4 = fix16_lerp(lFvalue4, rFvalue4, morphFrac);
		interp5 = fix16_lerp(lFvalue5, rFvalue5, morphFrac);

//	arm_negate_q31(&fullTableHoldArray[LnFamily][LnSample - 2], interp1Array, 6);
//	arm_add_q31(&fullTableHoldArray[LnFamily + 1][LnSample - 2], interp1Array, interpArray, 6);
//	arm_scale_q31(interpArray, morphFrac, 0, interpArray, 6);
//	arm_add_q31(&fullTableHoldArray[LnFamily][LnSample - 2], interpArray, interpArray, 6);
//	arm_shift_q31(interpArray, -16, interpArray, 6);
//
//	interp0 = interpArray[0];
//	interp1 = interpArray[1];
//	interp2 = interpArray[2];
//	interp3 = interpArray[3];
//	interp4 = interpArray[4];
//	interp5 = interpArray[5];

	out = (interp2
			+ fix24_mul(699051, fix16_mul(waveFrac, ((interp3-interp1)*16 + (interp0-interp4)*2
					+ fix16_mul(waveFrac, ((interp3+interp1)*16 - interp0 - interp2*30 - interp4
							+ fix16_mul(waveFrac, (interp3*66 - interp2*70 - interp4*33 + interp1*39 + interp5*7 - interp0*9
									+ fix16_mul(waveFrac, ( interp2*126 - interp3*124 + interp4*61 - interp1*64 - interp5*12 + interp0*13
											+ fix16_mul(waveFrac, ((interp3-interp2)*50 + (interp1-interp4)*25 + (interp5-interp0) * 5
											))
									))
							))
					))
			))
			));

	out = out >> 3;

	if (out > 4095){out = 4095;}
	else if (out < 0){out = 0;}

	// we use the interpolated nearest neighbor samples to determine the sign of rate of change
	// aka, are we moving towrds a, or towards b
	// we use this to generate our gate output
	if (interp2 < interp3) {
		EXPAND_GATE_HIGH;
		REV2_GATE_HIGH;
		if (DELTAB) {
			BLOGIC_HIGH;
			if (RUNTIME_DISPLAY) {
				LEDD_ON;
			}
		}
		if (DELTAA) {
			ALOGIC_LOW;
			if (RUNTIME_DISPLAY) {
				LEDC_OFF;
			}
		}
	} else if (interp3 < interp2) {
		EXPAND_GATE_LOW;
		REV2_GATE_LOW;
		if (DELTAB) {
			BLOGIC_LOW;
			if (RUNTIME_DISPLAY) {
				LEDD_OFF;
			}
		}
		if (DELTAA) {
			ALOGIC_HIGH;
			if (RUNTIME_DISPLAY) {
				LEDC_ON;
			}
		}
	}

}

// this sets the flags to be used in the interrupt and also fills the holding array on the heap
void switchFamily(void) {
	static int lastSpan;

	currentFamily = *familyArray[speed][familyIndicator];
	loadSampleArray(currentFamily);
	if (currentFamily.bandlimitOff) {
		CLEAR_BANDLIMIT;
	}
	else {
		SET_BANDLIMIT;
	}

	span = (currentFamily.tableLength) << 16;
	spanx2 = (currentFamily.tableLength) << 17;

	//protect from crashing with a phase pointer outside of the new span
	if (lastSpan != span) {
		position = 0;
	}
	lastSpan = span;

	switch (currentFamily.familySize) {
	// these are values that properly allow us to select a family and interpolation fraction for our morph
	case 3:
		morphBitShiftRight = 11;
		morphBitShiftLeft = 5;
		break;

	case 5:
		morphBitShiftRight = 10;
		morphBitShiftLeft = 6;
		break;

	case 9:
		morphBitShiftRight = 9;
		morphBitShiftLeft = 7;
		break;

	case 17:
		morphBitShiftRight = 8;
		morphBitShiftLeft = 8;
		break;

	case 33:
		morphBitShiftRight = 7;
		morphBitShiftLeft = 9;
		break;
	}
	switch (currentFamily.tableLength) {
	// these are values that properly allow us to select a family and interpolation fraction for our morph
	case 4:
		tableSizeCompensation = 6;
		break;

	case 8:
		tableSizeCompensation = 5;
		break;

	case 16:
		tableSizeCompensation = 4;
		break;

	case 32:
		tableSizeCompensation = 3;
		break;

	case 64:
		tableSizeCompensation = 2;
		break;

	case 128:
		tableSizeCompensation = 1;
		break;

	case 256:
		tableSizeCompensation = 0;
		break;
	}
}



// this shuttles the data from flash to ram and fills our holding array
void loadSampleArray(Family family) {

	uint32_t numSamples = family.tableLength;

	//for each table in the family
	for (int i = 0; i < family.familySize; i++) {
		//include the "last two" samples from release
		fullTableHoldArray[i][0] = *(*(family.releaseFamily + i) + 0);
		fullTableHoldArray[i][1] = *(*(family.releaseFamily + i) + 0);
		//fill in a full cycle's worth of samples
		//the release gets reversed
		//we drop the last sample from attack and the first from releas
		for (int j = 0;j < numSamples; j++) {
			fullTableHoldArray[i][2 + j] = *(*(family.attackFamily + i) + j);
			fullTableHoldArray[i][2 + numSamples + j] = *(*(family.releaseFamily + i) + family.tableLength - j);
		}
		//pad out the "first two" samples from attack
		fullTableHoldArray[i][(numSamples << 1) + 2] = *(*(family.attackFamily + i) + 0);
		fullTableHoldArray[i][(numSamples << 1) + 3] = *(*(family.attackFamily + i) + 0);
		fullTableHoldArray[i][(numSamples << 1) + 4] = *(*(family.attackFamily + i) + 0);
	}

}

