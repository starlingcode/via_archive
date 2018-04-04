#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"

#include "tables.h"
#include "main.h"
#include "int64.h"
#include "interrupt_functions.h"

#define ARM_MATH_CM4
#include "arm_math.h"

// wavetable size - 1 in fix16 and that number doubled
int span;
int spanx2;

// per family bit shift amounts to determine the morph  (defined on wavetable family change)
uint32_t morphBitShiftRight;
uint32_t morphBitShiftLeft;

// averaged ADC values
uint32_t morphCVAverage;
uint32_t morphKnobAverage;

// store and declare our exponential lookup table in RAM (defined in tables.h)
extern int lookuptable[4095] = expotable10oct;

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
void getSampleQuinticSpline(uint32_t) __attribute__((section("ccmram")));


// this is called to write our last sample to the dacs and generate a new sample
void dacISR(void) {
	uint32_t storePhase;
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
			storePhase = PHASE_STATE;
			//PROFILING_EVENT("DAC Uptdated");

			// call the function to advance the phase of the contour generator
			position = (*getPhase)(position);
			//PROFILING_EVENT("Phase Accquired");

			// determine whether our newly calculated phase value "position" is in the "attack" or "release" portion of the cycle
			// call the function that generates our next sample based upon the phase value "position"
			// pass that function a 1 or a 0 to indicate whether we are in attack or release
			if (position < span) {
				RESET_PHASE_STATE;
				//getSample(0);
				//getSampleCubicSpline(0);
				getSampleQuinticSpline(0);
			}
			if (position >= span) {
				SET_PHASE_STATE;
				//getSample(1);
				//getSampleCubicSpline(1);
				getSampleQuinticSpline(1);
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
				fixMorph = myfix16_lerp(morphKnobAverage, 4095, ((131071 - morphCVAverage) - 65536));
			}
			else {
				// analogous to above except in this case, morphCV is less than halfway
				fixMorph = myfix16_lerp(0, morphKnobAverage, (131071 - morphCVAverage));
			}

			// if we are in high speed and not looping, activate drum mode
			if (DRUM_MODE_ON) {
				// this next bit generates our expo decay and scales amp
				// it gets the appropriate value for the expo table and scales into the range of the fix16 fractional component (16 bits)
				if (DRUM_ATTACK_ON) {
					// maintain a software-based counter to increment through a linear "attack" slope sample per sample
					attackCount = attackCount + (inc >> 11);
					// if we get to our maximum value (this is the index where the value is 2^26)
					// this overflow value gives us a known range for our values from the lookup table
					if (attackCount > 3840) {
						// write to the flag word that we are done with our attack slope
						RESET_DRUM_ATTACK_ON;
						// since we use this to look up from the table, clamp it at our max value
						attackCount = 3840;
						// enable the timer that will generate our release slope
						__HAL_TIM_ENABLE(&htim3);
						// get our value from the lookup table, scale it, this will be 2^16
						expoScale = lookuptable[attackCount] >> 10;
						// reset our counter to 0
						attackCount = 0;
						// indicate that we are now in the "release" phase of our drum envelope
						SET_DRUM_RELEASE_ON;
					}
					else {
						// otherwise, use our counter to look up a value from the table
						// that gets scaled to 0 - 2^16
						expoScale = lookuptable[attackCount] >> 10;
					}
				}
				else if (DRUM_RELEASE_ON) {
					//if we are in release, use timer counter to look up a value from the table
					//that gets scaled to 0 - 2^16
					expoScale = lookuptable[TIM3->CNT] >> 10;
				}
				//scale the contour generator, an integer 0 - 2^16 is 0-1 in our 16 bit fixed point
				if (AMP_ON) {
					out = myfix16_mul(out, expoScale);
				}
				//apply the scaling value to the morph knob
				if (MORPH_ON) {
					fixMorph = myfix16_mul(fixMorph, expoScale);
				}
			}
			else {
				if (BANDLIMIT) {
					morphLimit = myfix16_mul(4095, 65536 - ((my_abs(inc)) >> 5));
					if (morphLimit < 0) {morphLimit = 0;}
					if (fixMorph > morphLimit) {
						fixMorph = morphLimit;
					}
				}
			}

			// if we transition from one phase state to another, enable the transition handler interrupt
			if (((PHASE_STATE) != storePhase)) {
				HAL_NVIC_SetPendingIRQ(EXTI15_10_IRQn);
			}
			//PROFILING_EVENT("ISR_Complete");
			//PROFILING_STOP();
		}
		else {
			//turn off the display if the contour generator is inactive and we are not switching modes
			if (RGB_ON) {
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



void getSampleQuinticSpline(uint32_t phase) {
#define PRECALC1_6 2796202

	// in this function, we use our phase position to get the sample to give to our dacs using "biinterpolation"
	// essentially, we need to get 4 sample values and two "fractional arguments" (where are we at in between those sample values)
	// think of locating a position on a rectangular surface based upon how far you are between the bottom and top and how far you are between the left and right sides
	// that is basically what we are doing here
	uint32_t LnSample;  // indicates the nearest neighbor to our position in the wavetable
	uint32_t LnFamily;  // indicates the nearest neighbor (wavetable) to our morph value in the family
	uint32_t waveFrac;  // indicates the fractional distance between our nearest neighbors in the wavetable
	uint32_t morphFrac; // indicates the fractional distance between our nearest neighbors in the family
	uint32_t lFvalue0;  // sample values used by our two interpolations in
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
	uint32_t interp0;  // results of those two interpolations
	uint32_t interp1;
	uint32_t interp2;  // results of those two interpolations
	uint32_t interp3;
	uint32_t interp4;
	uint32_t interp5;
	int calc;

	// the above is used to perform our bi-interpolation
	// essentially, interp 1 and interp 2 are the interpolated values in the two adjacent wavetables per the playback position
	// out is the "crossfade" between those according to morphFrac

	if (phase == 0) {
		// we do a lot of tricky bitshifting to take advantage of the structure of a 16 bit fixed point number
		// truncate position then add one to find the relevant indices for our wavetables, first within the wavetable then the actual wavetables in the family
		LnSample = (position >> 16) + 2;

		// bit shifting to divide by the correct power of two takes a 12 bit number (our fixMorph) and returns the a quotient in the range of our family size
		LnFamily = fixMorph >> morphBitShiftRight;

		// determine the fractional part of our phase position by masking off the integer
		waveFrac = 0x0000FFFF & position;

		// we have to calculate the fractional portion and get it up to full scale
		morphFrac = (fixMorph - (LnFamily << morphBitShiftRight)) << morphBitShiftLeft;

		// get values from the relevant wavetables
		lFvalue0 = attackHoldArray[LnFamily][LnSample - 2];
		lFvalue1 = attackHoldArray[LnFamily][LnSample - 1];
		lFvalue2 = attackHoldArray[LnFamily][LnSample];
		lFvalue3 = attackHoldArray[LnFamily][LnSample + 1];
		lFvalue4 = attackHoldArray[LnFamily][LnSample + 2];
		lFvalue5 = attackHoldArray[LnFamily][LnSample + 3];
		rFvalue0 = attackHoldArray[LnFamily + 1][LnSample- 2];
		rFvalue1 = attackHoldArray[LnFamily + 1][LnSample - 1];
		rFvalue2 = attackHoldArray[LnFamily + 1][LnSample];
		rFvalue3 = attackHoldArray[LnFamily + 1][LnSample + 1];
		rFvalue4 = attackHoldArray[LnFamily + 1][LnSample + 2];
		rFvalue5 = attackHoldArray[LnFamily + 1][LnSample + 3];

		// find the interpolated values for the adjacent wavetables using an efficient fixed point linear interpolation
		interp0 = myfix16_lerp(lFvalue0, rFvalue0, morphFrac);
		interp1 = myfix16_lerp(lFvalue1, rFvalue1, morphFrac);
		interp2 = myfix16_lerp(lFvalue2, rFvalue2, morphFrac);
		interp3 = myfix16_lerp(lFvalue3, rFvalue3, morphFrac);
		interp4 = myfix16_lerp(lFvalue4, rFvalue4, morphFrac);
		interp5 = myfix16_lerp(lFvalue5, rFvalue5, morphFrac);

		out = interp2
				+ myfix24_mul(699051, myfix16_mul(waveFrac, ((interp3-interp1)*16 + (interp0-interp4)*2
						+ myfix16_mul(waveFrac, ((interp3+interp1)*16 - interp0 - interp2*30 - interp4
								+ myfix16_mul(waveFrac, (interp3*66 - interp2*70 - interp4*33 + interp1*39 + interp5*7 - interp0*9
										+ myfix16_mul(waveFrac, ( interp2*126 - interp3*124 + interp4*61 - interp1*64 - interp5*12 + interp0*13
												+ myfix16_mul(waveFrac, ((interp3-interp2)*50 + (interp1-interp4)*25 + (interp5-interp0) * 5))
										))
								))
						))
				))
				);

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
				if (RGB_ON) {
					LEDD_ON;
				}
			}
			if (DELTAA) {
				ALOGIC_LOW;
				if (RGB_ON) {
					LEDC_OFF;
				}
			}
		} else if (interp1 < interp2) {
			EXPAND_GATE_LOW;
			REV2_GATE_LOW;
			if (DELTAB) {
				BLOGIC_LOW;
				if (RGB_ON) {
					LEDD_OFF;
				}
			}
			if (DELTAA) {
				ALOGIC_HIGH;
				if (RGB_ON) {
					LEDC_ON;
				}
			}
		}

		if (RGB_ON) { // if the runtime display is on, show our mode
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, out);
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, fixMorph >> 2);
		}
	}

	else {

		// this section is similar, but subtly different to implement our "release"
		// notice, we reflect position back over span
		LnSample = ((spanx2 - position) >> 16) + 2;
		LnFamily = fixMorph >> morphBitShiftRight;

		// here, again, we use that reflected value
		waveFrac = 0x0000FFFF & (spanx2 - position);
		morphFrac = (uint16_t) ((fixMorph - (LnFamily << morphBitShiftRight)) << morphBitShiftLeft);

		// pull the values from our "release family"
		//		family = currentFamily.releaseFamily + LnFamily;
		//		Lnvalue1 = *(*(family) + LnSample);
		//		Rnvalue1 = *(*(family) + LnSample + 1);
		//		Lnvalue2 = *(*(family + 1) + LnSample);
		//		Rnvalue2 = *(*(family + 1) + LnSample + 1);

		lFvalue0 = releaseHoldArray[LnFamily][LnSample - 2];
		lFvalue1 = releaseHoldArray[LnFamily][LnSample - 1];
		lFvalue2 = releaseHoldArray[LnFamily][LnSample];
		lFvalue3 = releaseHoldArray[LnFamily][LnSample + 1];
		lFvalue4 = releaseHoldArray[LnFamily][LnSample + 2];
		lFvalue5 = releaseHoldArray[LnFamily][LnSample + 3];
		rFvalue0 = releaseHoldArray[LnFamily + 1][LnSample- 2];
		rFvalue1 = releaseHoldArray[LnFamily + 1][LnSample - 1];
		rFvalue2 = releaseHoldArray[LnFamily + 1][LnSample];
		rFvalue3 = releaseHoldArray[LnFamily + 1][LnSample + 1];
		rFvalue4 = releaseHoldArray[LnFamily + 1][LnSample + 2];
		rFvalue5 = releaseHoldArray[LnFamily + 1][LnSample + 3];

		// find the interpolated values for the adjacent wavetables using an efficient fixed point linear interpolation
		interp0 = myfix16_lerp(lFvalue0, rFvalue0, morphFrac);
		interp1 = myfix16_lerp(lFvalue1, rFvalue1, morphFrac);
		interp2 = myfix16_lerp(lFvalue2, rFvalue2, morphFrac);
		interp3 = myfix16_lerp(lFvalue3, rFvalue3, morphFrac);
		interp4 = myfix16_lerp(lFvalue4, rFvalue4, morphFrac);
		interp5 = myfix16_lerp(lFvalue5, rFvalue5, morphFrac);

		out = interp2
				+ myfix24_mul(699051, myfix16_mul(waveFrac, ((interp3-interp1)*16 + (interp0-interp4)*2
						+ myfix16_mul(waveFrac, ((interp3+interp1)*16 - interp0 - interp2*30 - interp4
								+ myfix16_mul(waveFrac, (interp3*66 - interp2*70 - interp4*33 + interp1*39 + interp5*7 - interp0*9
										+ myfix16_mul(waveFrac, ( interp2*126 - interp3*124 + interp4*61 - interp1*64 - interp5*12 + interp0*13
												+ myfix16_mul(waveFrac, ((interp3-interp2)*50 + (interp1-interp4)*25 + (interp5-interp0) * 5))
										))
								))
						))
				))
				);

		out = out >> 3;

		if (out > 4095){out = 4095;}
		if (out < 0){out = 0;}

		// we use the interpolated nearest neighbor samples to determine the sign of rate of change
		// aka, are we moving towrds a, or towards b
		// we use this to generate our gate output
		if (interp1 < interp2) {
			EXPAND_GATE_HIGH;
			REV2_GATE_HIGH;
			if (DELTAB) {
				BLOGIC_HIGH;
				if (RGB_ON) {
					LEDD_ON;
				}
			}
			if (DELTAA) {
				ALOGIC_LOW;
				if (RGB_ON) {
					LEDC_OFF;
				}
			}
		} else if (interp1 < interp2) {
			EXPAND_GATE_LOW;
			REV2_GATE_LOW;
			if (DELTAB) {
				BLOGIC_LOW;
				if (RGB_ON) {
					LEDD_OFF;
				}
			}
			if (DELTAA) {
				ALOGIC_HIGH;
				if (RGB_ON) {
					LEDC_ON;
				}
			}
		}
		if (RGB_ON) {
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, out);
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, fixMorph >> 2);
		}
	}
}



//
//
//void getSample(uint32_t phase) {
//	// in this function, we use our phase position to get the sample to give to our dacs using biinterpolation
//	// essentially, we need to get 4 sample values and two "fractional arguments" (where are we at in between those sample values)
//	// think of locating a position on a rectangular surface based upon how far you are between the bottom and top and how far you are between the left and right sides
//	// that is basically what we are doing here
//	uint32_t LnSample; // indicates the nearest neighbor to our position in the wavetable
//	uint32_t LnFamily; // indicates the nearest neighbor (wavetable) to our morph value in the family
//	uint32_t phaseFrac; // indicates the factional distance between our nearest neighbors in the wavetable
//	uint32_t morphFrac; // indicates the factional distance between our nearest neighbors in the family
//	uint32_t Lnvalue1; // sample values used by our two interpolations in
//	uint32_t Rnvalue1;
//	uint32_t Lnvalue2;
//	uint32_t Rnvalue2;
//	uint32_t interp1; // results of those two interpolations
//	uint32_t interp2; // results of those two interpolations
//
//	// 0 means we are attacking from A to B, aka we are reading from the slopetable from left to right
//	// 1 means we are releasing from B to A, aka we are reading from the slopetable from right to left
//	if (phase == 0) {
//		// we do a lot of tricky bitshifting to take advantage of the structure of a 16 bit fixed point number
//		// truncate position then add one to find the relevant indices for our wavetables, first within the wavetable then the actual wavetables in the family
//		LnSample = (position >> 16);
//
//		//bit shifting to divide by the correct power of two takes a 12 bit number (our fixMorph) and returns the a quotient in the range of our family size
//		LnFamily = fixMorph >> morphBitShiftRight;
//
//		// determine the fractional part of our phase position by masking off the integer
//		phaseFrac = 0x0000FFFF & position;
//		// we have to calculate the fractional portion and get it up to full scale
//		morphFrac = (fixMorph - (LnFamily << morphBitShiftRight))
//						<< morphBitShiftLeft;
//
//		// get values from the relevant wavetables
//		Lnvalue1 = attackHoldArray[LnFamily][LnSample];
//		Rnvalue1 = attackHoldArray[LnFamily][LnSample + 1];
//		Lnvalue2 = attackHoldArray[LnFamily + 1][LnSample];
//		Rnvalue2 = attackHoldArray[LnFamily + 1][LnSample + 1];
//
//		// find the interpolated values for the adjacent wavetables using an efficient fixed point linear interpolation
//		interp1 = myfix16_lerp(Lnvalue1, Lnvalue2, morphFrac);
//		interp2 = myfix16_lerp(Rnvalue1, Rnvalue2, morphFrac);
//
//		// interpolate between those based upon the fractional part of our phase pointer
//		out = myfix16_lerp(interp1, interp2, phaseFrac) >> 3;
//
//		// we use the interpolated nearest neighbor samples to determine the sign of rate of change
//		// aka, are we moving towards a, or towards b
//		// we use this to generate our gate output
//		if (interp1 < interp2) {
//			EXPAND_GATE_HIGH;
//			REV2_GATE_HIGH;
//			if (DELTAB) {
//				BLOGIC_HIGH;
//				if (RGB_ON) {
//					LEDD_ON;
//				}
//			}
//			if (DELTAA) {
//				ALOGIC_LOW;
//				if (RGB_ON) {
//					LEDC_OFF;
//				}
//			}
//		} else if (interp2 < interp1) {
//			EXPAND_GATE_LOW;
//			REV2_GATE_LOW;
//			if (DELTAB) {
//				BLOGIC_LOW;
//				if (RGB_ON) {
//					LEDD_OFF;
//				}
//			}
//			if (DELTAA) {
//				ALOGIC_HIGH;
//				if (RGB_ON) {
//					LEDC_ON;
//				}
//			}
//		}
//
//		if (RGB_ON) {
//			// if the runtime display is on, show the current value of our contour generator in blue and morph in green
//			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, out);
//			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, fixMorph >> 2);
//		}
//	}
//	else {
//		// this section is mostly the same as the "attack" above
//		// however, we reflect position back over span to move backwards through our wavetable slope
//		LnSample = ((spanx2 - position) >> 16);
//		LnFamily = fixMorph >> morphBitShiftRight;
//
//		// here, again, we use that reflected value
//		phaseFrac = 0x0000FFFF & (spanx2 - position);
//		morphFrac = (uint16_t) ((fixMorph - (LnFamily << morphBitShiftRight))
//				<< morphBitShiftLeft);
//
//		Lnvalue1 = releaseHoldArray[LnFamily][LnSample];
//		Rnvalue1 = releaseHoldArray[LnFamily][LnSample + 1];
//		Lnvalue2 = releaseHoldArray[LnFamily + 1][LnSample];
//		Rnvalue2 = releaseHoldArray[LnFamily + 1][LnSample + 1];
//
//		interp1 = myfix16_lerp(Lnvalue1, Lnvalue2, morphFrac);
//		interp2 = myfix16_lerp(Rnvalue1, Rnvalue2, morphFrac);
//
//		out = myfix16_lerp(interp1, interp2, phaseFrac) >> 3;
//
//		if (interp2 < interp1) {
//			EXPAND_GATE_HIGH;
//			REV2_GATE_HIGH;
//			if (DELTAB) {
//				BLOGIC_HIGH;
//				if (RGB_ON) {
//					LEDD_ON;
//				}
//			}
//			if (DELTAA) {
//				ALOGIC_LOW;
//				if (RGB_ON) {
//					LEDC_OFF;
//				}
//			}
//		} else if (interp1 < interp2) {
//			EXPAND_GATE_LOW;
//			REV2_GATE_LOW;
//			if (DELTAB) {
//				BLOGIC_LOW;
//				if (RGB_ON) {
//					LEDD_OFF;
//				}
//			}
//			if (DELTAA) {
//				ALOGIC_HIGH;
//				if (RGB_ON) {
//					LEDC_ON;
//				}
//			}
//		}
//
//		//if the runtime display is on, show the current value of our contour generator in blue and morph in green
//		if (RGB_ON) {
//			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, out);
//			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, fixMorph >> 2);
//		}
//	}
//}
//
//void getSampleCubicSpline(uint32_t phase) {
//#define PRECALC1_6 2796203
//
//
//	// in this function, we use our phase position to get the sample to give to our DACs using "biinterpolation"
//	// essentially, we need to get 4 sample values and two "fractional arguments" (where are we at in between those sample values)
//	// think of locating a position on a rectangular surface based upon how far you are between the bottom and top and how far you are between the left and right sides
//	// that is basically what we are doing here
//
//	uint32_t LnSample;  // indicates the nearest neighbor to our position in the wavetable
//	uint32_t LnFamily;  // indicates the nearest neighbor (wavetable) to our morph value in the family
//	uint32_t waveFrac;  // indicates the fractional distance between our nearest neighbors in the wavetable
//	uint32_t morphFrac; // indicates the fractional distance between our nearest neighbors in the family
//	uint32_t lFValue0;  // sample values used by our two interpolations in
//	uint32_t rFValue0;
//	uint32_t lFValue1;
//	uint32_t rFValue1;
//	uint32_t lFValue2;
//	uint32_t rFValue2;
//	uint32_t lFValue3;
//	uint32_t rFValue3;
//	q15_t lFValues[4];
//	q15_t interpHelper1[4];
//	q15_t interpHelper2[4];
//	q15_t rFValues[4];
//	q15_t scaling[4] = {-5461, 16384, -16384, 5461};
//	uint32_t interp0;
//	uint32_t interp1;
//	uint32_t interp2;
//	uint32_t interp3;
//	uint32_t a0;
//	uint32_t a1;
//	uint32_t a2;
//	uint32_t a3;
//
//	// the above is used to perform our bi-interpolation
//	// essentially, interp 1 and interp 2 are the interpolated values in the two adjacent wavetables per the playback position
//	// out is the "crossfade" between those according to morphFrac
//
//	if (phase == 0) {
//		// we do a lot of tricky bitshifting to take advantage of the structure of a 16 bit fixed point number
//		// truncate position then add one to find the relevant indices for our wavetables, first within the wavetable then the actual wavetables in the family
//		LnSample = (position >> 16) + 2; //+ 2 because we define lookup overflow in our tables
//
//		// bit shifting to divide by the correct power of two takes a 12 bit number (our fixMorph) and returns the a quotient in the range of our family size
//		LnFamily = fixMorph >> morphBitShiftRight;
//
//		// determine the fractional part of our phase position by masking off the integer
//		waveFrac = 0x0000FFFF & position;
//		//  we have to calculate the fractional portion and get it up to full scale
//		morphFrac = (fixMorph - (LnFamily << morphBitShiftRight)) << morphBitShiftLeft;
//
//		// get values from the relevant wavetables
//
//		lFValue0 = attackHoldArray[LnFamily][LnSample - 1];
//		lFValue1 = attackHoldArray[LnFamily][LnSample];
//		lFValue2 = attackHoldArray[LnFamily][LnSample + 1];
//		lFValue3 = attackHoldArray[LnFamily][LnSample + 2];
//		rFValue0 = attackHoldArray[LnFamily + 1][LnSample - 1];
//		rFValue1 = attackHoldArray[LnFamily + 1][LnSample];
//		rFValue2 = attackHoldArray[LnFamily + 1][LnSample + 1];
//		rFValue3 = attackHoldArray[LnFamily + 1][LnSample + 2];
//
//		// find the interpolated values for the adjacent wavetables using an efficient fixed point linear interpolation
//		interp0 = myfix16_lerp(lFValue0, rFValue0, morphFrac);
//		interp1 = myfix16_lerp(lFValue1, rFValue1, morphFrac);
//		interp2 = myfix16_lerp(lFValue2, rFValue2, morphFrac);
//		interp3 = myfix16_lerp(lFValue3, rFValue3, morphFrac);
//
//		// interpolate between those based upon the fractional part of our phase pointer
//		a0 = myfix16_mul(waveFrac, myfix16_mul(waveFrac - 65536, waveFrac - 131072));
//		a1 = myfix16_mul(waveFrac + 65536, myfix16_mul(waveFrac - 65536, waveFrac - 131072));
//		a2 = myfix16_mul(waveFrac, myfix16_mul(waveFrac + 65536, waveFrac - 131072));
//		a3 = myfix16_mul(waveFrac, myfix16_mul(waveFrac + 65536, waveFrac - 65536));
//
//		out = (myfix16_mul(a0, myfix24_mul(interp0, -PRECALC1_6)) +
//				(myfix16_mul(a1, interp1) >> 1) +
//				(myfix16_mul(a2, -interp2) >> 1) +
//				myfix16_mul(a3, myfix24_mul(interp3, PRECALC1_6))) >> 3;
//
//		if (out > 4095){out = 4095;}
//		else if (out < 0){out = 0;}
//
//		// we use the interpolated nearest neighbor samples to determine the sign of rate of change
//		// aka, are we moving towards a, or towards b
//		// we use this to generate our gate output
//		if (interp1 < interp2) {
//			EXPAND_GATE_HIGH;
//			REV2_GATE_HIGH;
//			if (DELTAB) {
//				BLOGIC_HIGH;
//				if (RGB_ON) {
//					LEDD_ON;
//				}
//			}
//			if (DELTAA) {
//				ALOGIC_LOW;
//				if (RGB_ON) {
//					LEDC_OFF;
//				}
//			}
//		}
//		else {
//			EXPAND_GATE_LOW;
//			REV2_GATE_LOW;
//			if (DELTAB) {
//				BLOGIC_LOW;
//				if (RGB_ON) {
//					LEDD_OFF;
//				}
//			}
//			if (DELTAA) {
//				ALOGIC_HIGH;
//				if (RGB_ON) {
//					LEDC_ON;
//				}
//			}
//		}
//
//		if (RGB_ON) { // if the runtime display is on, show our mode
//			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, out);
//			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, fixMorph >> 2);
//		}
//	}
//	else {
//
//		// this section is similar, but subtly different to implement our "release"
//		// notice, we reflect position back over span
//		LnSample = ((spanx2 - position) >> 16) + 2;
//		LnFamily = fixMorph >> morphBitShiftRight;
//
//		// here, again, we use that reflected value
//		waveFrac = 0x0000FFFF & (spanx2 - position);
//		morphFrac = (uint16_t) ((fixMorph - (LnFamily << morphBitShiftRight)) << morphBitShiftLeft);
//
//		// pull the values from our "release family"
//		lFValue0 = releaseHoldArray[LnFamily][LnSample - 1];
//		lFValue1 = releaseHoldArray[LnFamily][LnSample];
//		lFValue2 = releaseHoldArray[LnFamily][LnSample + 1];
//		lFValue3 = releaseHoldArray[LnFamily][LnSample + 2];
//		rFValue0 = releaseHoldArray[LnFamily + 1][LnSample - 1];
//		rFValue1 = releaseHoldArray[LnFamily + 1][LnSample];
//		rFValue2 = releaseHoldArray[LnFamily + 1][LnSample + 1];
//		rFValue3 = releaseHoldArray[LnFamily + 1][LnSample + 2];
//
//		interp0 = myfix16_lerp(lFValue0, rFValue0, morphFrac);
//		interp1 = myfix16_lerp(lFValue1, rFValue1, morphFrac);
//		interp2 = myfix16_lerp(lFValue2, rFValue2, morphFrac);
//		interp3 = myfix16_lerp(lFValue3, rFValue3, morphFrac);
//
//		a0 = myfix16_mul(waveFrac, myfix16_mul(waveFrac - 65536, waveFrac - 131072));
//		a1 = myfix16_mul(waveFrac + 65536, myfix16_mul(waveFrac - 65536, waveFrac - 131072));
//		a2 = myfix16_mul(waveFrac, myfix16_mul(waveFrac + 65536, waveFrac - 131072));
//		a3 = myfix16_mul(waveFrac, myfix16_mul(waveFrac + 65536, waveFrac - 65536));
//
//		out = (myfix16_mul(a0, myfix24_mul(interp0, -PRECALC1_6)) +
//				(myfix16_mul(a1, interp1) >> 1) +
//				(myfix16_mul(a2, -interp2) >> 1) +
//				myfix16_mul(a3, myfix24_mul(interp3, PRECALC1_6))) >> 3;
//
//		if (out > 4095){out = 4095;}
//		else if (out < 0){out = 0;}
//
//		// we use the interpolated nearest neighbor samples to determine the sign of rate of change
//		// aka, are we moving towards a, or towards b
//		// we use this to generate our gate output
//		if (interp1 < interp2) {
//			EXPAND_GATE_HIGH;
//			REV2_GATE_HIGH;
//			if (DELTAB) {
//				BLOGIC_HIGH;
//				if (RGB_ON) {
//					LEDD_ON;
//				}
//			}
//			if (DELTAA) {
//				ALOGIC_LOW;
//				if (RGB_ON) {
//					LEDC_OFF;
//				}
//			}
//		} else {
//			EXPAND_GATE_LOW;
//			REV2_GATE_LOW;
//			if (DELTAB) {
//				BLOGIC_LOW;
//				if (RGB_ON) {
//					LEDD_OFF;
//				}
//			}
//			if (DELTAA) {
//				ALOGIC_HIGH;
//				if (RGB_ON) {
//					LEDC_ON;
//				}
//			}
//		}
//		if (RGB_ON) {
//			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, out);
//			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, fixMorph >> 2);
//		}
//	}
//}

