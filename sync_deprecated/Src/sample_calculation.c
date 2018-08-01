#include "tables.h"
#include "main.h"
#include "tsl_user.h"
#include "scales.h"
#include "eeprom.h"
#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"
#include "interrupt_functions.h"
#include "int64.h"

uint32_t time2CVAverage;
uint32_t morphKnobAverage;
uint32_t morphCVAverage;

// this holds our current table
uint16_t fullTableHoldArray[9][517];

// this fills that array
void loadSampleArray(Family family);

void getSampleQuinticSpline(void) __attribute__((section("ccmram")));

extern TIM_HandleTypeDef htim1;

void dacISR(void) {
	uint32_t storePhase;

	// write the current contour generator value to DAC1, and its inverse to DAC2 (crossfading)
	((*(volatile uint32_t *) DAC1_ADDR) = (4095 - out));
	((*(volatile uint32_t *) DAC2_ADDR) = (out));

	// get averages for T2 and morph CV (move to the ADC interrupt??)
	getAverages();

	// store last "Phase State" (attack or release)
	storePhase = PHASE_STATE;

//		PROFILING_EVENT("DAC Updated");

	// call the function to advance the phase of the contour generator using that increment
	getPhase();

	//PROFILING_EVENT("Phase Acquired");

	// calculate morph amount per sample as a function of the morph knob and CV
	if ((4095 - morphCVAverage) >= 2048) {
		fixMorph = fix16_lerp(morphKnobAverage, 4095, ((4095 - morphCVAverage) - 2048) << 5);
	} else {
		fixMorph = fix16_lerp(0, morphKnobAverage, (4095 - morphCVAverage) << 5);
	}
	//	fixMorph = morphKnobAverage;

	getSampleQuinticSpline();

	// call the appropriate interpolation routine per phase in the two part table and declare phase state as such
	if (position < span) {
		CLEAR_PHASE_STATE;
		if (RUNTIME_DISPLAY) { // if the runtime display is on, show our mode
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, out);
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, fixMorph >> 2);
		}
	}
	if (position >= span) {
		SET_PHASE_STATE;
		if (RUNTIME_DISPLAY) { // if the runtime display is on, show our mode
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, out);
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, fixMorph >> 2);
		}
	}
//		PROFILING_EVENT("Sampling Complete");

	// if we transition from one phase state to another, enable the transition handler interrupt
	if ((PHASE_STATE) != storePhase) {
		HAL_NVIC_SetPendingIRQ(EXTI15_10_IRQn);
	}
//		PROFILING_STOP();
}

void getSampleQuinticSpline(void) {

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
    uint32_t morphFrac; // indicates the fractional distance between our nearest neighbors in the family
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
		if (DELTAA) {
			ALOGIC_HIGH;
			if (RUNTIME_DISPLAY) {
				LEDC_ON;
			}
		}
		if (DELTAB) {
			BLOGIC_LOW;
			if (RUNTIME_DISPLAY) {
				LEDC_OFF;
			}
		}
	} else if (interp3 < interp2) {
		EXPAND_GATE_LOW;
		REV2_GATE_LOW;
		if (DELTAA) {
			ALOGIC_LOW;
			if (RUNTIME_DISPLAY) {
				LEDC_OFF;
			}
		}
		if (DELTAB) {
			BLOGIC_HIGH;
			if (RUNTIME_DISPLAY) {
				LEDD_ON;
			}
		}
	}

}


// this sets the flags to be used in the interrupt and also fills the holding array on the heap
void switchFamily(void) {
	static int lastSpan;

	currentFamily = familyArray[scaleType][familyIndicator];
	loadSampleArray(currentFamily);

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
