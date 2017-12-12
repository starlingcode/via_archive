#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"

#include "tables.h"
#include "main.h"
#include "int64.h"
#include "interrupt_functions.h"

// wavetable size - 1 in fix16 and that number doubled
uint32_t span;
int spanx2;
int tableSizeCompensation;

//per family bit shift amounts to accomplish morph
uint32_t morphBitShiftRight;
uint32_t morphBitShiftLeft;

uint32_t ADCReadings1[4];
uint32_t ADCReadings2[2];
uint32_t ADCReadings3[2];
uint32_t time2Average;
uint32_t morphAverage;



int lookuptable[4095] = expotable10oct;

// mode indicators, determined in the main loop
enum speedTypes speed;
enum loopTypes loop;
enum trigModeTypes trigMode;
enum sampleHoldModeTypes sampleHoldMode;

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim3;


void getSample(uint32_t) __attribute__((section("ccmram")));
void getPhase(void) __attribute__((section("ccmram")));
int myfix16_mul(int, int) __attribute__((section("ccmram")));
int myfix16_lerp(int, int, uint16_t) __attribute__((section("ccmram")));
void getAverages(void) __attribute__((section("ccmram")));

void dacISR(void) {



	uint32_t storePhase;

	if (OSCILLATOR_ACTIVE) {

		//write the current oscillator value to dac1, and its inverse to dac2 (crossfading)

		((*(volatile uint32_t *) DAC1_ADDR) = (4095 - out));
		((*(volatile uint32_t *) DAC2_ADDR) = (out));

		// get our averages for t2 and morph cv (move to the ADC interrupt??)

		getAverages();

		storePhase = PHASE_STATE;



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
		EOA_JACK_HIGH;
		if (inc > 1048575) {inc = 1048575;}
		if (morphAverage >= 16384) {
			fixMorph = myfix16_mul(myfix16_lerp(morphKnob, 4095, (morphAverage - 16384) << 2), 65535 - (inc >> 4));
		}
		else {
			fixMorph = myfix16_mul(myfix16_lerp(0, morphKnob, morphAverage << 2) , 65535 - (inc >> 4));
		}


		// write that value to our RGB

		//if we are in high speed and not looping, activate drum mode

		if (DRUM_MODE_ON) {

			//call the fuction that generates our expo decay and scales amp



			//this gets the appropriate value for the expo table and scales into the range of the fix16 fractional component (16 bits)
			if (DRUM_ATTACK_ON) {

				attackCount = attackCount + (inc >> 11) ;

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
		EOA_JACK_LOW;

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


