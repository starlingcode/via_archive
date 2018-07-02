#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"
#include "main_state_machine.h"
#include "tables.h"
#include "int64.h"
#include "dsp.h"
#include "pwm_tables.h"

#define WAVETABLE_LENGTH 33554432
#define NEGATIVE_WAVETABLE_LENGTH -33554432 // wavetable length in 16 bit fixed point (512 << 16)
#define WAVETABLE_MAX_VALUE_PHASE 16777216 // wavetable midpoint in 16 bit fixed point (256 << 16)

const uint32_t expoTable[4096] = expotable10oct;

void getIncrementsAudio(q31_t * t2CV, controlRateInputs * controlInputs, q31_t * reverseArray, int lastPhase, int tableSizeCompensation, int span, q31_t * incrementValues) {

	q31_t frequencyMultiplier = fix16_mul(fix16_mul(expoTable[controlInputs->knob1Value] >> 3, expoTable[controlInputs->knob2Value >> 3]), expoTable[controlInputs->cv1Value] >> 2);
	arm_offset_q31(t2CV, -1024, incrementValues, BUFFER_SIZE);
	arm_shift_q31(incrementValues, 19 - tableSizeCompensation, incrementValues, BUFFER_SIZE);
	arm_scale_q31(incrementValues, frequencyMultiplier, 0, incrementValues, BUFFER_SIZE);
//	arm_mult_q31(incrementValues, reverseArray, incrementValues, BUFFER_SIZE);

}

void getIncrementsSimple(q31_t * t2CV, controlRateInputs * controlInputs, q31_t * reverseArray, int lastPhase, int tableSizeCompensation, int span, q31_t * incrementValues) {

	int attackTime = expoTable[4095 - controlInputs->knob1Value] >> 10;
	int releaseTime = expoTable[4095 - controlInputs->knob2Value] >> 10;

	int dummyPhase = lastPhase;

	if (lastPhase < (span >> 1)) {
		for (int i = 0; i < BUFFER_SIZE; i++) {
			incrementValues[i] = attackTime;
		}
	} else {
		for (int i = 0; i < BUFFER_SIZE; i++) {
			incrementValues[i] = releaseTime;
		}
	}

	//arm_mult_q31(incrementValues, reverseArray, incrementValues, BUFFER_SIZE);

}


void getIncrementsComplex(q31_t * t2CV, controlRateInputs * controlInputs, q31_t * reverseArray, int lastPhase, int tableSizeCompensation, int span, q31_t * incrementValues) {

	q31_t frequencyMultiplier = fix16_mul(expoTable[4095 - controlInputs->knob1Value] >> 6, expoTable[4095 - controlInputs->cv1Value] >> 6);
	arm_shift_q31(t2CV, 19 - tableSizeCompensation, incrementValues, BUFFER_SIZE);
	arm_scale_q31(incrementValues, frequencyMultiplier, 0, incrementValues, BUFFER_SIZE);
	//arm_mult_q31(incrementValues, reverseArray, incrementValues, BUFFER_SIZE);

}


int advancePhaseLoopNoGate(q31_t * incrementValues, q31_t * hardSyncValues, int phase, int span, q31_t * phaseArray, q31_t * phaseEventArray) {


	static q31_t previousPhase;
	q31_t wrapPhase;

	for (int i = 0; i < BUFFER_SIZE; i++) {

		phase = (phase + incrementValues[i]) * hardSyncValues[i] * (OSCILLATOR_ACTIVE);

		wrapPhase = 0;

		wrapPhase += ((uint32_t)(phase) >> 31) * span;
		wrapPhase -= ((uint32_t)(WAVETABLE_LENGTH - phase) >> 31) * span;

		// apply the wrapping offset
		// no effect if there is no overflow

		phase += wrapPhase;

		// log a -1 if the max value index of the wavetable is traversed from the left
		// log a 1 if traversed from the right
		// do this by subtracting the sign bit of the last phase from the current phase, both less the max phase index
		// this adds cruft to the wrap indicators, but that is deterministic and can be parsed out

		wrapPhase += ((uint32_t)(phase - (span >> 1)) >> 31) - ((uint32_t)(previousPhase - (span >> 1)) >> 31);

		// log the phase event by accumulating the indicative variables
		// log 0 if no event

		phaseEventArray[i] = wrapPhase;

		// TODO rewrite logic parsing function

		// store the current phase
		previousPhase = phase;

		// calculate the sample value
		phaseArray[i] = phase;

	}

	return phase;

}

int advancePhaseLoopGate(q31_t * incrementValues, q31_t * hardSyncValues, int phase, int span, q31_t * phaseArray, q31_t * phaseEventArray) {

	static q31_t lastPhase;
	q31_t wrapPhase;

	for (int i = 0; i < BUFFER_SIZE; i++) {

		phase = (phase + incrementValues[i]) * hardSyncValues[i] * (OSCILLATOR_ACTIVE);

		wrapPhase = 0;

		wrapPhase = ((uint32_t)(phase) >> 31) * span;
		wrapPhase -= ((uint32_t)(WAVETABLE_LENGTH - phase) >> 31) * span;

		// apply the wrapping offset
		// no effect if there is no overflow

		phase += wrapPhase;

		// log a -1 if the max value index of the wavetable is traversed from the left
		// log a 1 if traversed from the right
		// do this by subtracting the sign bit of the last phase from the current phase, both less the max phase index
		// this adds cruft to the wrap indicators, but that is deterministic and can be parsed out

		int atBIndicator = ((uint32_t)(phase - (span >> 1)) >> 31) - ((uint32_t)(lastPhase - (span >> 1)) >> 31);
		wrapPhase += atBIndicator;

		// log the phase event by accumulating the indicative variables
		// log 0 if no event

		phaseEventArray[i] = wrapPhase;

		// if GATE = 1 and atBIndicator = 1, undo the increment

		phase -= (incrementValues[i]) * (GATE) * (abs(atBIndicator));


		// store the current phase
		lastPhase = phase;


		phaseArray[i] = phase;


	}

	return lastPhase;

}

int advancePhaseNoLoopNoGate(q31_t * incrementValues, q31_t * hardSyncValues, int phase, int span, q31_t * phaseArray, q31_t * phaseEventArray) {

	static q31_t lastPhase;
	q31_t wrapPhase;

	for (int i = 0; i < BUFFER_SIZE; i++) {

		phase = (phase + incrementValues[i]) * hardSyncValues[i] * (OSCILLATOR_ACTIVE);

		wrapPhase = 0;

		wrapPhase = ((uint32_t)(phase) >> 31) * span;
		wrapPhase -= ((uint32_t)(WAVETABLE_LENGTH - phase) >> 31) * span;

		// apply the wrapping offset
		// no effect if there is no overflow

		phase += wrapPhase;

		// log a -1 if the max value index of the wavetable is traversed from the left
		// log a 1 if traversed from the right
		// do this by subtracting the sign bit of the last phase from the current phase, both less the max phase index
		// this adds cruft to the wrap indicators, but that is deterministic and can be parsed out

		wrapPhase += ((uint32_t)(phase - (span >> 1)) >> 31) - ((uint32_t)(lastPhase - (span >> 1)) >> 31);

		// log the phase event by accumulating the indicative variables
		// log 0 if no event

		phaseEventArray[i] = wrapPhase;

		// store the current phase
		lastPhase = phase;

		if (abs(wrapPhase) > 5) {

			phase = 0;
			CLEAR_OSCILLATOR_ACTIVE;

		}

		// calculate the sample value
		phaseArray[i] = phase;

	}

	return lastPhase;

}

int advancePhaseNoLoopGate(q31_t * incrementValues, q31_t * hardSyncValues, int phase, int span, q31_t * phaseArray, q31_t * phaseEventArray) {

	static q31_t lastPhase;
	q31_t wrapPhase;

	for (int i = 0; i < BUFFER_SIZE; i++) {

		phase = (phase + incrementValues[i]) * (OSCILLATOR_ACTIVE);

		wrapPhase = 0;

		wrapPhase = ((uint32_t)(phase) >> 31) * span;
		wrapPhase -= ((uint32_t)(WAVETABLE_LENGTH - phase) >> 31) * span;

		// apply the wrapping offset
		// no effect if there is no overflow

		phase += wrapPhase;

		// log a -1 if the max value index of the wavetable is traversed from the left
		// log a 1 if traversed from the right
		// do this by subtracting the sign bit of the last phase from the current phase, both less the max phase index
		// this adds cruft to the wrap indicators, but that is deterministic and can be parsed out

		int atBIndicator = ((uint32_t)(phase - (span >> 1)) >> 31) - ((uint32_t)(lastPhase - (span >> 1)) >> 31);

		wrapPhase += atBIndicator;

		// log the phase event by accumulating the indicative variables
		// log 0 if no event

		phaseEventArray[i] = wrapPhase;

		// if GATE = 1 and atBIndicator = 1, undo the increment

		phase -= (incrementValues[i]) * (GATE) * (abs(atBIndicator));

		// store the current phase
		lastPhase = phase;

		if (abs(wrapPhase) > 5) {

			phase = 0;
			CLEAR_OSCILLATOR_ACTIVE;

		}

		// calculate the sample value
		phaseArray[i] = phase;
	}

	return lastPhase;
}



