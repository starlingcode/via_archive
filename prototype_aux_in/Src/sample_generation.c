#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"

#include "tables.h"
#include "main.h"
#include "int64.h"
#include "interrupt_functions.h"

//wavetable size - 1 in fix16 and that number doubled
int span;
int spanx2;

//this is an integer that compensates for wavetable size in our frequency calculation (defined on wavetable family change)
int tableSizeCompensation;

//per family bit shift amounts to determine the morph  (defined on wavetable family change)
uint32_t morphBitShiftRight;
uint32_t morphBitShiftLeft;

//these arrays are filled with our ADC values using DMA (set up in main.c)
uint32_t ADCReadings1[4];
uint32_t ADCReadings2[2];
uint32_t ADCReadings3[2];

//averaged ADC values
uint32_t time2Average;
uint32_t morphCVAverage;
uint32_t t1KnobAverage;
uint32_t t2KnobAverage;
uint32_t morphKnobAverage;
uint32_t t1CVAverage;
uint32_t t2CVAverage;

//store and decalre our exponential lookup tabe in RAM (defined in tables.h)
int lookuptable[4095] = expotable10oct;

//mode indicators, defined in functions found in user_interface.c
enum speedTypes speed;
enum loopTypes loop;
enum trigModeTypes trigMode;
enum sampleHoldModeTypes sampleHoldMode;

//declare the necessary timer handles for use in these functions (set up in main.c, interrupts in stm32f3xx_it.c)
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim3;

//declarations for the functions defined below, attribute places them in "CCMRAM" for maximum efficiency
void getSample(uint32_t) __attribute__((section("ccmram")));
void getBandlimitedSample(uint32_t) __attribute__((section("ccmram")));
void getPhase(void) __attribute__((section("ccmram")));
int myfix16_mul(int, int) __attribute__((section("ccmram")));
int myfix24_mul(int, int) __attribute__((section("ccmram")));

int myfix16_lerp(int, int, uint16_t) __attribute__((section("ccmram")));
void getAverages(void) __attribute__((section("ccmram")));
void getAveragesAudio(void) __attribute__((section("ccmram")));
void implementButter10(void) __attribute__((section("ccmram")));


//this is called to write our last sample to the dacs and generate a new sample
void dacISR(void) {

	uint32_t storePhase;
	uint32_t interp2;
	int morphLimit;


	// remove for compatibility w/ rev2 (black back) boards
	if ((GPIOA->IDR & GPIO_PIN_11) != (uint32_t) GPIO_PIN_RESET) {
	if ((OSCILLATOR_ACTIVE)) {


		//write the current contour generator value to dac1, and its inverse to dac2 (this actually performs the interpolation)

		((*(volatile uint32_t *) DAC1_ADDR) = (4095 - out));
		((*(volatile uint32_t *) DAC2_ADDR) = (out));


		//get our averages for t2 and morph cv

		//hold the phase state (attack or release) from the last sample

		storePhase = PHASE_STATE;

		//call the function to advance the phase of the contour generator

		getPhase();

		//determine whether our newly calculated phase value "position" is in the "attack" or "release" portion of the cycle
		//call the function that generates our next sample based upon the phase value "position"
		//pass that function a 1 or a 0 to indicate whether we are in attack or release

		if (position < span) {
			RESET_PHASE_STATE;
			getSample(0);
		}
		if (position >= span) {
			SET_PHASE_STATE;
			getSample(1);
		}

		//calculate our "morph" parameter as a function of the morph knob, CV, and our contour generator frequency

		//we use morphAverage, which is a running sum of the last 8 values (a running average without the division)

		//we basically check whether the morphCV is less than or greater than half of its full scale value
		//if it is less than half of full scale, we do a linear interpolation between our current knob value and 0 using the CV value as the interpolation fraction
		//if it is more than half of full scale, we do a linear interpolation between our current knob value and full scale using the CV value as the interpolation fraction
		//in both of these cases, we generate our interpolation fraction by simple bit shifting a sum involving the halfway scale value and the CV
		//basically, we figure out how far our morphCV is away from the halfway point and then scale that up to a 16 bit integer
		//this works because we assume that all of our ADC ranges are a power of two

		//we then scale back our morph value as frequency increases. with a table that exhibits a steadily increasing spectral content as morph increases, this serves as anti-aliasing



		//is our CV greater than half-scale (the big numbers are because we have a running sum of 8
		if ((131071 - morphCVAverage) >= 65536) {
			//this first does the aforementioned interpolation between the knob value and full scale then scales back the value according to frequency
			fixMorph = myfix16_lerp(morphKnobAverage, 4095, ((131071 - morphCVAverage) - 65536));

		}
		else {
			//analogous to above except in this case, morphCV is less than halfway
			fixMorph = myfix16_lerp(0, morphKnobAverage, (131071 - morphCVAverage));

		}




//		fixMorph = 2000;

		//if we are in high speed and not looping, activate drum mode

		if (DRUM_MODE_ON) {

			//this next bit generates our expo decay and scales amp
			//it gets the appropriate value for the expo table and scales into the range of the fix16 fractional component (16 bits)

			if (DRUM_ATTACK_ON) {

				//maintain a software-based counter to increment through a linear "attack" slope sample per sample
				attackCount = attackCount + (inc >> 11);

				//if we get to our maximum value (this is the index where the value is 2^26)
				//this overflow value gives us a known range for our values from the lookup table
				if (attackCount > 3840) {
					//write to the flag word that we are done with our attack slope
					RESET_DRUM_ATTACK_ON;
					//since we use this to look up from the table, clamp it at our max value
					attackCount = 3840;
					//enable the timer that will generate our release slope
					__HAL_TIM_ENABLE(&htim3);
					//get our value from the lookup table, scale it, this will be 2^16
					expoScale = lookuptable[attackCount] >> 10;
					//reset our counter to 0
					attackCount = 0;
					//indicate that we are now in the "release" phase of our drum envelope
					SET_DRUM_RELEASE_ON;
				} else {
					//otherwise, use our counter to look up a value from the table
					//that gets scaled to 0 - 2^16
					expoScale = lookuptable[attackCount] >> 10;
				}

			} else if (DRUM_RELEASE_ON) {
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

		} else {
			if (BANDLIMIT) {
				morphLimit = myfix16_mul(4095, 65536 - ((abs(inc) - 110000) >> 4));
				if (morphLimit < 0) {morphLimit = 0;}
				if (fixMorph > morphLimit) {
					fixMorph = morphLimit;
				}
			}
		}

		//implementButter10();
//		implementBiquadFilter();




		// if we transition from one phase state to another, enable the transition handler interrupt

		if (((PHASE_STATE) != storePhase)) {

			HAL_NVIC_SetPendingIRQ(EXTI15_10_IRQn);

		}

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
} //remove for compativility with rev2 boards

}

void getPhase(void) {

	static int incFromADCs;

	int attackTransferHolder;
	int releaseTransferHolder;


	//calculate our increment value in high speed mode

	if (speed == audio) {

		/*
		 contour generator frequency is a function of phase increment, wavetable size, and sample rate
		 we multiply our ADC readings (knobs and CVs) to get a phase increment for our wavetable playback
		 t1 knob and CV are mapped to an exponential curve with a lookup table
		 this is scaled to 1v/oct for the t1CV
		 t2 is linear FM
		 we fiddled with scale using constant values and bitshifts to make the controls span the audio range
		 if we are in drum mode, replace linear fm with the scaling factor from the drum envelope*/
		if (loop == noloop) {

			getAveragesDrum();

			incFromADCs = myfix16_mul(
					myfix16_mul(150000, lookuptable[4095 - t1CVAverage] >> 6), lookuptable[(t1KnobAverage >> 1) + 2047] >> 10) >> tableSizeCompensation;

			if (PITCH_ON) {incFromADCs = myfix16_mul(expoScale + 30000, incFromADCs);}

		}

		else {

			getAveragesAudio();

			incFromADCs = myfix16_mul(myfix16_mul(myfix16_mul((2050 - t2CVAverage) << 9, lookuptable[4095 - t1CVAverage] >> 5), lookuptable[t1KnobAverage] >> 4), lookuptable[t2KnobAverage >> 4]) >> tableSizeCompensation;

		}

	}

	//define increment for env and seq modes using function pointers to the appropriate knob/cv combo
	//these can be swapped around by the retrigger interrupt
	else if (speed == env) {

		getAverages();

		if (position < span) {
			incFromADCs = (*attackTime)();
		}
		else {
			incFromADCs = (*releaseTime)();
		}

	}

	else if (speed == seq) {

		getAverages();

		inc = incSign*calcTime1Seq();

		incFromADCs = 0;



		if (!(HOLD_AT_B)) {
			holdPosition = inc + holdPosition;
		}

		if (holdPosition >= spanx2) {

			holdPosition = holdPosition - spanx2;
			if ((loop == noloop) || (LAST_CYCLE)) {

				//this is the logic maintenance needed to properly put the contour generator to rest
				//this keeps behavior on the next trigger predictable

				RESET_LAST_CYCLE;
				RESET_OSCILLATOR_ACTIVE;
				if (trigMode == pendulum && !(DRUM_MODE_ON))  {
					incSign = -1;
					position = spanx2;
					holdPosition = spanx2;
				}
				else {
					incSign = 1;
					position = 0;
					holdPosition = 0;
				}
				out = 0;
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


		if (holdPosition < 0) {

			holdPosition = holdPosition + spanx2;

			if ((loop == noloop) || (LAST_CYCLE)) {

					//same as above, we are putting our contour generator to rest

					RESET_LAST_CYCLE;
					RESET_OSCILLATOR_ACTIVE;
					incSign = 1;
					position = 0;
					holdPosition = 0;
					out = 0;
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

		if ((4095 - t2CVAverage) >= 2047) {
			//this first does the aforementioned interpolation between the knob value and full scale then scales back the value according to frequency
			skewMod = myfix16_lerp(t2KnobAverage, 4095, ((4095 - t2CVAverage) - 2048) << 4);
		}
		else {
			//analogous to above except in this case, morphCV is less than halfway
			skewMod = myfix16_lerp(0, t2KnobAverage, (4095 - t2CVAverage) << 4);
		}


		if (holdPosition < (myfix16_mul(spanx2, (4095 - skewMod) << 4))) {
			attackTransferHolder = (65535 << 16)/((4095 - skewMod) << 5); // 1/(T2*2)
			position = myfix16_mul(holdPosition, attackTransferHolder);

		} else if (!(HOLD_AT_B)) {
			releaseTransferHolder = (65535 << 16)/(skewMod << 5); // 1/((1-T2)*2)
			position = myfix16_mul(holdPosition, releaseTransferHolder) + spanx2 - myfix16_mul(spanx2, releaseTransferHolder);

		}

		if ((GATE_ON) && ((abs(inc) > abs(span - position)) || (HOLD_AT_B))) {

			// if so, we set a logic flag that we have frozen the contour generator in this transition
			SET_HOLD_AT_B;

		}

		//if any of the above changes, we indicate that we are no longer frozen
		else {
			RESET_HOLD_AT_B;
		}



	}

	// apply the approrpiate signage to our inc per the retrigger behavior
	// this is how we get the contour generator to run backwards
	inc = incFromADCs * incSign;

	// if trigmode is gated and we arent in Drum Mode
	if (trigMode > 2 && !(DRUM_MODE_ON) && speed != seq) {

		// we look to see if we are about to increment past the attack->release transition

		if ((GATE_ON) && (abs(inc) > abs(span - position))) {

			// if so, we set a logic flag that we have frozen the contour generator in this transition
			SET_HOLD_AT_B;

			//and we hold it in place
			inc = span - position;

		}

		//if any of the above changes, we indicate that we are no longer frozen
		else {
			RESET_HOLD_AT_B;
		}

	}

	//this keeps us from asking the contour generator to jump all the way through the wavetable

	if (inc >= span) {
		inc = span;
	} else if (inc <= -span) {
		inc = -span;
	}

	//increment our phase pointer by the newly calculated increment value

	position = position + inc;

	// if we have incremented outside of our table, wrap back around to the other side and stop/reset if we are in LF 1 shot mode

	if (position >= spanx2) {

		position = position - spanx2;

		if ((loop == noloop && speed != audio) || (LAST_CYCLE)) {

			//this is the logic maintenance needed to properly put the contour generator to rest
			//this keeps behavior on the next trigger predictable

			RESET_LAST_CYCLE;
			RESET_OSCILLATOR_ACTIVE;
			if (trigMode == pendulum && !(DRUM_MODE_ON))  {
				incSign = -1;
				position = spanx2;
				holdPosition = position;
			}
			else {
				incSign = 1;
				position = 0;
				holdPosition = position;
			}
			SET_PHASE_STATE;
			SH_A_TRACK
			SH_B_TRACK
			if (RGB_ON) {
				LEDA_OFF
				LEDB_OFF
				LEDC_OFF
				LEDD_OFF
			}
			//HAL_NVIC_SetPendingIRQ(EXTI15_10_IRQn);

		}

	}
	// same as above but for when we are backtracking through the attack phase aka negative increment
	else if (position < 0) {

		position = position + spanx2;

		if ((loop == noloop && speed != audio) || (LAST_CYCLE)) {

			//same as above, we are putting our contour generator to rest

			RESET_LAST_CYCLE;
			RESET_OSCILLATOR_ACTIVE;
			incSign = 1;
			position = 0;
			holdPosition = 0;
			RESET_PHASE_STATE;
			SH_A_TRACK
			SH_B_TRACK
			if (RGB_ON) {
				LEDA_OFF
				LEDB_OFF
				LEDC_OFF
				LEDD_OFF
			}
			//HAL_NVIC_SetPendingIRQ(EXTI15_10_IRQn);

		}

	}

}

//multiply our knobs with our CVs with the appropriate scaling per the current frequency mode

int calcTime1Env(void) {

	time1 = ((lookuptable[t1CVAverage] >> 13) * (lookuptable[(4095 - t1KnobAverage)] >> 13)) >> (6 + tableSizeCompensation);
	return time1;

}

int calcTime2Env(void) {

	time2 = ((lookuptable[t2CVAverage] >> 13) * (lookuptable[(4095 - t2KnobAverage)] >> 13)) >> (8 + tableSizeCompensation);
	return time2;

}

int calcTime1Seq(void) {

	time1 = ((lookuptable[t1CVAverage] >> 13) * (lookuptable[(4095 - t1KnobAverage)] >> 13)) >> (8 + tableSizeCompensation);
	return time1;

}

int calcTime2Seq(void) {

	time2 = ((lookuptable[t2CVAverage] >> 13) * (lookuptable[(4095 - t2KnobAverage)] >> 13)) >> (8 + tableSizeCompensation);
	return time2;

}

void getSample(uint32_t phase) {

	// in this function, we use our phase position to get the sample to give to our dacs using biinterpolation
	// essentially, we need to get 4 sample values and two "fractional arguments" (where are we at in between those sample values)
	// think of locating a position on a rectangular surface based upon how far you are between the bottom and top and how far you are between the left and right sides
	// that is basically what we are doing here

	uint32_t LnSample; // indicates the nearest neighbor to our position in the wavetable
	uint32_t LnFamily; // indicates the nearest neighbor (wavetable) to our morph value in the family
	uint32_t phaseFrac; // indicates the factional distance between our nearest neighbors in the wavetable
	uint32_t morphFrac; // indicates the factional distance between our nearest neighbors in the family
	uint32_t Lnvalue1; // sample values used by our two interpolations in
	uint32_t Rnvalue1;
	uint32_t Lnvalue2;
	uint32_t Rnvalue2;
	uint32_t interp1; // results of those two interpolations
	uint32_t interp2; // results of those two interpolations


	// 0 means we are attacking from A to B, aka we are reading from the slopetable from left to right
	// 1 means we are releasing from B to A, aka we are reading from the slopetable from right to left
	if (phase == 0) {

		// we do a lot of tricky bitshifting to take advantage of the structure of a 16 bit fixed point number
		//truncate position then add one to find the relevant indices for our wavetables, first within the wavetable then the actual wavetables in the family
		LnSample = (position >> 16);

		//bit shifting to divide by the correct power of two takes a 12 bit number (our fixMorph) and returns the a quotient in the range of our family size
		LnFamily = fixMorph >> morphBitShiftRight;

		//determine the fractional part of our phase position by masking off the integer
		phaseFrac = 0x0000FFFF & position;
		// we have to calculate the fractional portion and get it up to full scale
		morphFrac = (fixMorph - (LnFamily << morphBitShiftRight))
				<< morphBitShiftLeft;

		//get values from the relevant wavetables

		Lnvalue1 = attackHoldArray[LnFamily][LnSample];
		Rnvalue1 = attackHoldArray[LnFamily][LnSample + 1];
		Lnvalue2 = attackHoldArray[LnFamily + 1][LnSample];
		Rnvalue2 = attackHoldArray[LnFamily + 1][LnSample + 1];

		//find the interpolated values for the adjacent wavetables using an efficient fixed point linear interpolation
		interp1 = myfix16_lerp(Lnvalue1, Lnvalue2, morphFrac);
		interp2 = myfix16_lerp(Rnvalue1, Rnvalue2, morphFrac);

		//interpolate between those based upon the fractional part of our phase pointer

		out = myfix16_lerp(interp1, interp2, phaseFrac) >> 3;

		//we use the interpolated nearest neighbor samples to determine the sign of rate of change
		//aka, are we moving towrds a, or towards b
		//we use this to generate our gate output
		if (interp1 < interp2) {
			EXPAND_GATE_HIGH
			REV2_GATE_HIGH
			if (DELTAB) {
				BLOGIC_HIGH
				if (RGB_ON) {
					LEDD_ON
				}
			}
			if (DELTAA) {
				ALOGIC_LOW
				if (RGB_ON) {
					LEDC_OFF
				}
			}
		} else if (interp2 < interp1) {
			EXPAND_GATE_LOW
			REV2_GATE_LOW
			if (DELTAB) {
				BLOGIC_LOW
				if (RGB_ON) {
					LEDD_OFF
				}
			}
			if (DELTAA) {
				ALOGIC_HIGH
				if (RGB_ON) {
					LEDC_ON
				}
			}
		}



		if (RGB_ON) {
			//if the runtime display is on, show the current value of our contour generator in blue and morph in green
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, out);
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, fixMorph >> 2);
		}
	}

	else {

		//this section is mostly the same as the "attack" above
		// however, we reflect position back over span to move backwards through our wavetable slope
		LnSample = ((spanx2 - position) >> 16);

		LnFamily = fixMorph >> morphBitShiftRight;

		// here, again, we use that reflected value
		phaseFrac = 0x0000FFFF & (spanx2 - position);

		morphFrac = (uint16_t) ((fixMorph - (LnFamily << morphBitShiftRight))
				<< morphBitShiftLeft);

		Lnvalue1 = releaseHoldArray[LnFamily][LnSample];
		Rnvalue1 = releaseHoldArray[LnFamily][LnSample + 1];
		Lnvalue2 = releaseHoldArray[LnFamily + 1][LnSample];
		Rnvalue2 = releaseHoldArray[LnFamily + 1][LnSample + 1];

		interp1 = myfix16_lerp(Lnvalue1, Lnvalue2, morphFrac);
		interp2 = myfix16_lerp(Rnvalue1, Rnvalue2, morphFrac);

		out = myfix16_lerp(interp1, interp2, phaseFrac) >> 3;

		if (interp2 < interp1) {
			EXPAND_GATE_HIGH
			REV2_GATE_HIGH
			if (DELTAB) {
				BLOGIC_HIGH
				if (RGB_ON) {
					LEDD_ON
				}
			}
			if (DELTAA) {
				ALOGIC_LOW
				if (RGB_ON) {
					LEDC_OFF
				}
			}
		} else if (interp1 < interp2) {
			EXPAND_GATE_LOW
			REV2_GATE_LOW
			if (DELTAB) {
				BLOGIC_LOW
				if (RGB_ON) {
					LEDD_OFF
				}
			}
			if (DELTAA) {
				ALOGIC_HIGH
				if (RGB_ON) {
					LEDC_ON
				}
			}
		}



		//if the runtime display is on, show the current value of our contour generator in blue and morph in green
		if (RGB_ON) {
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, out);
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, fixMorph >> 2);
		}
	}

}



//helper functions to maintain and read from a circular buffer

void write1024(buffer1024* buffer, int value) {
	buffer->buff[(buffer->writeIndex++) & 1023] = value;
}

int readn1024(buffer1024* buffer, int Xn) {
	return buffer->buff[(buffer->writeIndex + (~Xn)) & 1023];
}

void write256(buffer256* buffer, int value) {
	buffer->buff[(buffer->writeIndex++) & 255] = value;
}

int readn256(buffer256* buffer, int Xn) {
	return buffer->buff[(buffer->writeIndex + (~Xn)) & 255];
}

void write32(buffer32* buffer, int value) {
	buffer->buff[(buffer->writeIndex++) & 31] = value;
}

int readn32(buffer32* buffer, int Xn) {
	return buffer->buff[(buffer->writeIndex + (~Xn)) & 31];
}

//noise at the morph CV is noise in the contour generator signal

void getAverages(void) {

	static buffer256 t1KnobBuffer;
	static buffer256 t2KnobBuffer;
	static buffer256 t1CVBuffer;
	static buffer256 t2CVBuffer;
	static buffer256 morphKnobBuffer;
	static buffer256 morphCVBuffer;
	static uint32_t t1KnobSum;
	static uint32_t t2KnobSum;
	static uint32_t morphKnobSum;
	static uint32_t morphCVSum;
	static uint32_t t1CVSum;
	static uint32_t t2CVSum;
	static uint32_t bufferCounter;

	t1KnobSum = (t1KnobSum + time1Knob- readn256(&t1KnobBuffer, 255));
	t2KnobSum = (t2KnobSum + time2Knob- readn256(&t2KnobBuffer, 255));
	morphKnobSum = (morphKnobSum + morphKnob- readn256(&morphKnobBuffer, 255));
	morphCVSum = (morphCVSum + morphCV- readn256(&morphCVBuffer, 255));
	t1CVSum = (t1CVSum + time1CV- readn256(&t1CVBuffer, 255));
	t2CVSum = (t2CVSum + time2CV- readn256(&t2CVBuffer, 255));

	t1KnobAverage = t1KnobSum >> 8;
	t2KnobAverage = t2KnobSum >> 8;
	morphKnobAverage = morphKnobSum >> 8;
	t1CVAverage = t1CVSum >> 8;
	t2CVAverage = t2CVSum >> 8;
	morphCVAverage = morphCVSum >> 3;


	write256(&morphCVBuffer, morphCV);
	write256(&t1CVBuffer, time1CV);
	write256(&t2CVBuffer, time2CV);
	write256(&t1KnobBuffer, time1Knob);
	write256(&t2KnobBuffer, time2Knob);
	write256(&morphKnobBuffer, morphKnob);

}

void getAveragesAudio(void) {

	static buffer32 t1KnobBuffer;
	static buffer32 t2KnobBuffer;
	static buffer32 t1CVBuffer;
	static buffer32 t2CVBuffer;
	static buffer1024 morphKnobBuffer;
	static buffer32 morphCVBuffer;
	static uint32_t t1KnobSum;
	static uint32_t t2KnobSum;
	static uint32_t morphKnobSum;
	static uint32_t morphCVSum;
	static uint32_t t1CVSum;
	static uint32_t t2CVSum;

	t1KnobSum = (t1KnobSum + time1Knob- readn32(&t1KnobBuffer, 31));
	t2KnobSum = (t2KnobSum + time2Knob- readn32(&t2KnobBuffer, 31));
	morphKnobSum = (morphKnobSum + morphKnob- readn1024(&morphKnobBuffer, 1023));
	morphCVSum = (morphCVSum + morphCV- readn32(&morphCVBuffer, 31));
	t1CVSum = (t1CVSum + time1CV- readn32(&t1CVBuffer, 31));
	t2CVSum = (t2CVSum + time2CV- readn32(&t2CVBuffer, 31));

	t1KnobAverage = t1KnobSum >> 5;
	t2KnobAverage = t2KnobSum >> 5;
	morphKnobAverage = morphKnobSum >> 10;
	t1CVAverage = t1CVSum >> 5;
	t2CVAverage = t2CVSum >> 5;
	morphCVAverage = morphCVSum;

	write32(&morphCVBuffer, morphCV);
	write32(&t1CVBuffer, time1CV);
	write32(&t2CVBuffer, time2CV);
	write32(&t1KnobBuffer, time1Knob);
	write32(&t2KnobBuffer, time2Knob);
	write1024(&morphKnobBuffer, morphKnob);

}

void getAveragesDrum(void) {

	t1KnobAverage = time1Knob;
	t2KnobAverage = time2Knob;
	morphKnobAverage = morphKnob;
	t1CVAverage = time1CV;
	t2CVAverage = time1CV;
	morphCVAverage = morphCV << 5;

}

void implementButter10(void) {


#define a0 65536
#define a1 262144
#define a2 393216

#define b0 -172925
#define b1 -181490
#define b2 -87771
#define b3 -16372
#define GAIN 134166020

	static buffer32 inputs;
	static buffer32 outputs;


	write32(&inputs, myfix24_mul(GAIN, out));

	out =
		(myfix24_mul(readn32(&inputs, 4) + readn32(&inputs, 0), a0) +
		myfix24_mul(readn32(&inputs, 3) + readn32(&inputs, 1), a1) +
		myfix24_mul(readn32(&inputs, 2), a2) +

		myfix24_mul(readn32(&outputs, 0), b0) +
		myfix24_mul(readn32(&outputs, 1), b1) +
		myfix24_mul(readn32(&outputs, 2), b2) +
		myfix24_mul(readn32(&outputs, 3), b3)) << 1;


	if (out > 4095) {
		out = 4095;
	}
	if (out < 0) {
		out = 0;
	}


	write32(&outputs, out);


//
//
////20k
//#define a0 65536
//#define a1 655360
//#define a2 2949120
//#define a3 7864320
//#define a4 13762560
//#define a5 16515072
//#define a6 13762560
//#define a7 7864320
//#define a8 2949120
//#define a9 655360
//#define a10 65536
//#define b0 -436164
//#define b1 -1332764
//#define b2 -2455439
//#define b3 -3014375
//#define b4 -2572360
//#define b5 -1543337
//#define b6 -642126
//#define b7 -177149
//#define b8 -29239
//#define b9 -2191
//
//#define GAIN 3067671
//
////20k
////#define a0 29
////#define a1 57
////#define a2 29
////#define b0 -33492315
////#define b1 16715214
//
//	static buffer32 inputs;
//	static buffer32 outputs;
//
//
//	write32(&inputs, myfix24_mul(GAIN, out));
//
//	out =
//		myfix16_mul(readn32(&inputs, 10) + readn32(&inputs, 0), a0) +
//		myfix16_mul(readn32(&inputs, 9) + readn32(&inputs, 1), a1) +
//		myfix16_mul(readn32(&inputs, 8) + readn32(&inputs, 2), a2) +
//		myfix16_mul(readn32(&inputs, 7) + readn32(&inputs, 3), a3) +
//		myfix16_mul(readn32(&inputs, 6) + readn32(&inputs, 4), a4) +
//		myfix16_mul(readn32(&inputs, 5), a5) +
//		myfix16_mul(readn32(&outputs, 0), b0) +
//		myfix16_mul(readn32(&outputs, 1), b1) +
//		myfix16_mul(readn32(&outputs, 2), b2) +
//		myfix16_mul(readn32(&outputs, 3), b3) +
//		myfix16_mul(readn32(&outputs, 4), b4) +
//		myfix16_mul(readn32(&outputs, 5), b5) +
//		myfix16_mul(readn32(&outputs, 6), b6) +
//		myfix16_mul(readn32(&outputs, 7), b7) +
//		myfix16_mul(readn32(&outputs, 8), b8) +
//		myfix16_mul(readn32(&outputs, 9), b9);
//
//	if (out > 4095) {
//		out = 4095;
//	}
//	if (out < 0) {
//		out = 0;
//	}
//
//
//	write32(&outputs, out);
//




}

//our 16 bit fixed point multiply and linear interpolate functions

int myfix16_mul(int in0, int in1) {
	//taken from the fixmathlib library
	int64_t result = (uint64_t) in0 * in1;
	return result >> 16;
}

int myfix24_mul(int in0, int in1) {
	//taken from the fixmathlib library
	int64_t result = (uint64_t) in0 * in1;
	return result >> 24;
}

int myfix16_lerp(int in0, int in1, uint16_t inFract) {
	//taken from the fixmathlib library
	int64_t tempOut = int64_mul_i32_i32(in0, (((int32_t) 1 << 16) - inFract));
	tempOut = int64_add(tempOut, int64_mul_i32_i32(in1, inFract));
	tempOut = int64_shift(tempOut, -16);
	return (int) int64_lo(tempOut);
}

