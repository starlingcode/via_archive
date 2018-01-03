#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"

#include "tables.h"
#include "main.h"
#include "int64.h"
#include "interrupt_functions.h"

//wavetable size - 1 in fix16 and that number doubled
uint32_t span;
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
uint32_t morphAverage;

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
void getPhase(void) __attribute__((section("ccmram")));
int myfix16_mul(int, int) __attribute__((section("ccmram")));
int myfix16_lerp(int, int, uint16_t) __attribute__((section("ccmram")));
void getAverages(void) __attribute__((section("ccmram")));

//this is called to write our last sample to the dacs and generate a new sample
void dacISR(void) {

	uint32_t storePhase;

	if (OSCILLATOR_ACTIVE) {

		//write the current oscillator value to dac1, and its inverse to dac2 (this actually performs the interpolation)

		((*(volatile uint32_t *) DAC1_ADDR) = (4095 - out));
		((*(volatile uint32_t *) DAC2_ADDR) = (out));

		//get our averages for t2 and morph cv

		getAverages();

		//hold the phase state (attack or release) from the last sample

		storePhase = PHASE_STATE;



		//call the function to advance the phase of the oscillator

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

		//first we clamp our "inc" variable (which is analogous to our contour generator frequency) to max out at 2^20
		//this is our "maximum frequency" at which we find that our "morph" parameter is scaled all the way to 0

		if (inc > 1048575) {inc = 1048575;}

		//is our CV greater than half-scale (the big numbers are because we have a running sum of 8
		if ((32767 - morphAverage) >= 16383) {
			//this first does the aforementioned interpolation between the knob value and full scale then scales back the value according to frequency
			fixMorph = myfix16_mul(myfix16_lerp(morphKnob, 4095, ((32767 - morphAverage) - 16383) << 2), 65535 - (inc >> 4));
		}
		else {
			//analogous to above except in this case, morphCV is less than halfway
			fixMorph = myfix16_mul(myfix16_lerp(0, morphKnob, (32767 - morphAverage) << 2) , 65535 - (inc >> 4));
		}


		//if we are in high speed and not looping, activate drum mode

		if (DRUM_MODE_ON) {

			//this next bit generates our expo decay and scales amp
			//it gets the appropriate value for the expo table and scales into the range of the fix16 fractional component (16 bits)

			if (DRUM_ATTACK_ON) {

				//maintain a software-based counter to increment through a linear "attack" slope sample per sample
				attackCount = attackCount + (inc >> 11) ;

				//if we get to our maximum value (this is the index where the value is 2^26)
				//this gives us a known range for our values from the lookup table
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
					expoScale = lookuptable[attackCount] >> 10;
				}

			} else if (DRUM_RELEASE_ON) {
//				if (TIM3->EGR != TIM_EGR_UG) {
//
//				}
				expoScale = lookuptable[TIM3->CNT] >> 10;

			}

			//scale the oscillator
			if (AMP_ON) {
				out = myfix16_mul(out, expoScale);
			}

			//use the expo decay scaled by the manual morph control to modulate morph

			if (MORPH_ON) {
				fixMorph = myfix16_mul(fixMorph, expoScale);
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


}




//defines an increment then checks the trigger mode, making the appropriate changes to playback when the oscillator is retriggered
// Questioning whether this works properly when position has to be calculated using attack inc + decay inc (at transitions) i.e. increment rate overshoot

void getPhase(void) {

	//calculate our increment value in high speed mode
	static int incFromADCs;

	if (speed == audio) {

		/*multiply a base (modulated by linear FM) by a lookup value from a 10 octave expo table (modulated by expo FM)
		 if we are in drum mode, replace linear fm with the drum envelope*/
		if (loop == noloop) {


			incFromADCs = myfix16_mul(myfix16_mul(150000, lookuptable[4095 - time1CV] >> 5), lookuptable[(time1Knob >> 1) + 2047] >> 10) >> tableSizeCompensation;

			if (PITCH_ON) {incFromADCs = myfix16_mul(expoScale + 30000, incFromADCs);}

		}

		else {


			incFromADCs = myfix16_mul(myfix16_mul(myfix16_mul((3000 - time2CV) << 7, lookuptable[4095 - time1CV] >> 7), lookuptable[time1Knob] >> 4), lookuptable[time2Knob >> 4]) >> tableSizeCompensation;


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
			//out = 0;
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
			//out = 0;
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

int calcTime1Env(void) {

	time1 = ((lookuptable[time1CV] >> 13) * (lookuptable[(4095 - time1Knob)] >> 13)) >> (5 + tableSizeCompensation);
	return time1;

}

int calcTime2Env(void) {

	time2 = ((lookuptable[time2CV] >> 13) * (lookuptable[(4095 - time2Knob)] >> 13)) >> (7 + tableSizeCompensation);
	return time2;

}

int calcTime1Seq(void) {

	time1 = ((lookuptable[time1CV] >> 13) * (lookuptable[(4095 - time1Knob)] >> 13)) >> (9 + tableSizeCompensation);
	return time1;

}

int calcTime2Seq(void) {

	time2 = ((lookuptable[time2CV] >> 13) * (lookuptable[(4095 - time2Knob)] >> 13)) >> (9 + tableSizeCompensation);
	return time2;

}

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
	uint32_t sampleCalculation;
	uint32_t deltaSign;

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
		interp1 = myfix16_lerp(Lnvalue1, Lnvalue2, morphFrac);
		interp2 = myfix16_lerp(Rnvalue1, Rnvalue2, morphFrac);

		//interpolate between those based upon morph (biinterpolation)

		sampleCalculation = myfix16_lerp(interp1, interp2, waveFrac) >> 3;

		if (interp1 < interp2) {
			EOA_GATE_HIGH
		} else if (interp2 < interp1) {
			EOA_GATE_LOW
		}
		out = sampleCalculation;

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

		interp1 = myfix16_lerp(Lnvalue1, Lnvalue2, morphFrac);
		interp2 = myfix16_lerp(Rnvalue1, Rnvalue2, morphFrac);


		sampleCalculation = myfix16_lerp(interp1, interp2, waveFrac) >> 3;

		if (interp1 < interp2) {
			EOA_GATE_HIGH
		} else if (interp2 < interp1) {
			EOA_GATE_LOW
		}

		out = sampleCalculation;

		if (RGB_ON) {
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, out);
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, fixMorph);
		}
	}

}


void write(buffer* buffer, int value) {
	buffer->buff[(buffer->writeIndex++) & BUFF_SIZE_MASK] = value;
}

int readn(buffer* buffer, int Xn) {
	return buffer->buff[(buffer->writeIndex + (~Xn)) & BUFF_SIZE_MASK];
}

void getAverages(void) {

	//static buffer time2CVBuffer;
	static buffer morphCVBuffer;

//	write(&time2CVBuffer, time2CV);
//	time2Average = time2Average + time2CV- readn(&time2CVBuffer, 7);

	morphAverage = (morphAverage + morphCV- readn(&morphCVBuffer, 7));

	write(&morphCVBuffer, morphCV);

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


