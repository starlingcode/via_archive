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

enum syncTypes button4Mode; // {none, true, hardSync, catch}
enum controlSchemes controlScheme; // {root, dutyCycle, FM, phaseMod}
enum sampleHoldModeTypes sampleHoldMode;

uint32_t time2CVAverage;
uint32_t morphKnobAverage;
uint32_t morphCVAverage;

void getPhase(void)  __attribute__((section("ccmram")));
void getAverages(void)  __attribute__((section("ccmram")));

// calculates an increment then checks trigger mode, making the appropriate changes to playback when the contour generator is triggered
void getPhase(void) {

	static int lastCV;
	int attackTransferHolder;
	int releaseTransferHolder;

	if (controlScheme == phaseMod) {
		position = position + ((time2CV - lastCV) << 11);
		if (position < 0) {position = 0;}
		else if (position > spanx2) {position = spanx2;}
		lastCV = time2CV;
	}

	if (controlScheme == dutyCycle)  {
			holdPosition = attackInc + holdPosition;
			if (holdPosition >= spanx2) {
				holdPosition = holdPosition - spanx2;
			}

			if (holdPosition < 0) {
				holdPosition = holdPosition + spanx2;
			}

			if (time2CVAverage > 4094) {
				time2CVAverage = 4094;

			} else if (time2CVAverage < 1) {
				time2CVAverage = 1;
			}

			if (holdPosition < (fix16_mul(spanx2, (4095 - time2CVAverage) << 4))) {
				attackTransferHolder = (65535 << 11)/(4095 - time2CVAverage); // 1/(T2*2)
				position = fix16_mul(holdPosition, attackTransferHolder);
			} else {
				releaseTransferHolder = (65535 << 11)/(time2CVAverage); // 1/((1-T2)*2)
				position = fix16_mul(holdPosition, releaseTransferHolder) + spanx2 - fix16_mul(spanx2, releaseTransferHolder);
			}

	} else {
		if (controlScheme == FM) {
			if (PHASE_STATE) {
				position = position + ((attackInc * (4095 - time2CVAverage)) >> 11);
				if (position < 0) {position = 0;}
				else if (position > spanx2) {position = spanx2;}
			} else {
				position = position + ((releaseInc * time2CVAverage) >> 11);
				if (position < 0) {position = 0;}
				else if (position > spanx2) {position = spanx2;}
			}
		} else {
			if (PHASE_STATE) {
					position = position + attackInc;
			} else {
					position = position + releaseInc;
			}
		}
	}

	// if we have incremented outside of our table, wrap back around to the other side
	if (position >= spanx2) {
		position = position - spanx2;
	}

	if (position < 0) {
		position = position + spanx2;
	}

	lastCV = time2CV;
}


void getAverages(void) {

	static buffer time2CVBuffer;
	static buffer time1CVBuffer;
	static buffer morphCVBuffer;
	static buffer morphKnobBuffer;
	static buffer time2KnobBuffer;
	static buffer time1KnobBuffer;
	static uint32_t morphKnobSum;
	static uint32_t morphCVSum;
	static uint32_t time2CVSum;
	static uint32_t time2KnobSum;
	static uint32_t time1CVSum;
	static uint32_t time1KnobSum;

	time2CVSum = time2CVSum + time2CV- readn(&time2CVBuffer, 31);
	time1CVSum = time1CVSum + time1CV- readn(&time1CVBuffer, 1023);
	time1KnobSum = time1KnobSum + time1Knob- readn(&time1KnobBuffer, 1023);
	morphKnobSum = morphKnobSum + morphKnob - readn(&morphKnobBuffer, 1023);
	time2KnobSum = time2KnobSum + time2Knob - readn(&time2KnobBuffer, 1023);
	morphCVSum = (morphCVSum + morphCV - readn(&morphCVBuffer, 1023));

	time2KnobAverage = time2KnobSum >> 8;
	morphKnobAverage = morphKnobSum >> 8;
	morphCVAverage = morphCVSum >> 8;
	time2CVAverage = time2CVSum >> 5;
	time1CVAverage = time1CVSum >> 8;
	time1KnobAverage = time1KnobSum >> 8;

	write(&time2CVBuffer, time2CV);
	write(&morphCVBuffer, morphCV);
	write(&time1CVBuffer, time1CV);
	write(&morphKnobBuffer, morphKnob);
	write(&time2KnobBuffer, time2Knob);
	write(&time1KnobBuffer, time1Knob);
}

