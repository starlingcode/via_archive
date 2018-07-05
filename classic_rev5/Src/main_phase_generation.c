#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"
#include "main_state_machine.h"
#include "tables.h"
#include "int64.h"
#include "dsp.h"

const uint32_t expoTable[4096] = expotable10oct;

// fill incrementValues 1 and 2 with the attack and release time increments, respectively

void getIncrementsAudio(q31_t * t2CV, controlRateInputs * controlInputs, q31_t * incrementValues1,  q31_t * incrementValues2) {

	// t1 is coarse, t2 is fine, release time = attack time

	q31_t frequencyMultiplier = fix16_mul(fix16_mul(expoTable[controlInputs->knob1Value] >> 3, expoTable[controlInputs->knob2Value >> 3]), expoTable[controlInputs->cv1Value] >> 2);
	arm_offset_q31(t2CV, -1024, incrementValues1, BUFFER_SIZE);
	arm_shift_q31(incrementValues1, 19, incrementValues1, BUFFER_SIZE);
	arm_scale_q31(incrementValues1, frequencyMultiplier, 0, incrementValues1, BUFFER_SIZE);
	arm_copy_q31(incrementValues1, incrementValues2, BUFFER_SIZE);

}

void getIncrementsEnv(q31_t * t2CV, controlRateInputs * controlInputs, q31_t * incrementValues1,  q31_t * incrementValues2) {

	// t1 is attack time (incrementValues1), t2 is release time (incrementValues2)

	int attackTime = expoTable[4095 - controlInputs->knob1Value] >> 10;
	int releaseTime = expoTable[4095 - controlInputs->knob2Value] >> 10;

	arm_fill_q31(attackTime, incrementValues1, BUFFER_SIZE);
	arm_fill_q31(releaseTime, incrementValues2, BUFFER_SIZE);


}


void getIncrementsSeq(q31_t * t2CV, controlRateInputs * controlInputs, q31_t * incrementValues1,  q31_t * incrementValues2) {

	// t1 is cycle time, t2 is used to feed the duty cycle input for getSamples

	q31_t frequencyMultiplier = fix16_mul(expoTable[4095 - controlInputs->knob1Value] >> 6, expoTable[4095 - controlInputs->cv1Value] >> 6);
	arm_shift_q31(t2CV, 19, incrementValues1, BUFFER_SIZE);
	arm_scale_q31(incrementValues1, frequencyMultiplier, 0, incrementValues1, BUFFER_SIZE);
	arm_copy_q31(incrementValues1, incrementValues2, BUFFER_SIZE);

}

// use those increment values to calculate a phase array and phase event array
// see main_trigger_states.c for more

int advancePhaseNoRetrig(q31_t * incrementValues1, q31_t * incrementValues2, q31_t * triggerValues, q31_t * gateValues, int phase, int oscillatorActive, q31_t * phaseArray, q31_t * phaseEventArray) {


	static q31_t previousPhase;
	static q31_t previousPhaseEvent;
	q31_t phaseWrapper = 0;

	for (int i = 0; i < BUFFER_SIZE; i++) {

		int increment = (*noRetrigStateMachine)(triggerValues[i], previousPhaseEvent, incrementValues1[i], incrementValues2[i]);

		phase = (phase + increment); //* (oscillatorActive);

		phaseWrapper = 0;

		// add wavetable length if phase < 0

		phaseWrapper += ((uint32_t)(phase) >> 31) * WAVETABLE_LENGTH;

		// subtract wavetable length if phase > wavetable length

		phaseWrapper -= ((uint32_t)(WAVETABLE_LENGTH - phase) >> 31) * WAVETABLE_LENGTH;

		// apply the wrapping
		// no effect if the phase is in bounds

		phase += phaseWrapper;

		// log a -1 if the max value index of the wavetable is traversed from the left
		// log a 1 if traversed from the right
		// do this by subtracting the sign bit of the last phase from the current phase, both less the max phase index
		// this adds cruft to the wrap indicators, but that is deterministic and can be parsed out

		phaseWrapper += ((uint32_t)(phase - WAVETABLE_MAX_VALUE_PHASE) >> 31) - ((uint32_t)(previousPhase - WAVETABLE_MAX_VALUE_PHASE) >> 31);

		phaseEventArray[i] = phaseWrapper;

		// TODO rewrite logic parsing function

		// store the current phase
		previousPhase = phase;
		previousPhaseEvent = phaseWrapper;

		// calculate the sample value
		phaseArray[i] = phase;
	}

	return phase;

}

int advancePhaseHardSync(q31_t * incrementValues1, q31_t * incrementValues2, q31_t * triggerValues, q31_t * gateValues, int phase, int oscillatorActive, q31_t * phaseArray, q31_t * phaseEventArray) {


	static q31_t previousPhase;
	static q31_t previousPhaseEvent;
	q31_t phaseWrapper;

	for (int i = 0; i < BUFFER_SIZE; i++) {

		int increment = (*hardSyncStateMachine)(triggerValues[i], previousPhaseEvent, incrementValues1[i], incrementValues2[i]);

		phase = (phase + increment) * triggerValues[i];// * (oscillatorActive);

		phaseWrapper = 0;

		// add wavetable length if phase < 0

		phaseWrapper += ((uint32_t)(phase) >> 31) * WAVETABLE_LENGTH;

		// subtract wavetable length if phase > wavetable length

		phaseWrapper -= ((uint32_t)(WAVETABLE_LENGTH - phase) >> 31) * WAVETABLE_LENGTH;

		// apply the wrapping
		// no effect if the phase is in bounds

		phase += phaseWrapper;

		// log a -1 if the max value index of the wavetable is traversed from the left
		// log a 1 if traversed from the right
		// do this by subtracting the sign bit of the last phase from the current phase, both less the max phase index
		// this adds cruft to the wrap indicators, but that is deterministic and can be parsed out

		phaseWrapper += ((uint32_t)(phase - WAVETABLE_MAX_VALUE_PHASE) >> 31) - ((uint32_t)(previousPhase - WAVETABLE_MAX_VALUE_PHASE) >> 31);

		phaseEventArray[i] = phaseWrapper;

		// TODO rewrite logic parsing function

		// store the current phase
		previousPhase = phase;
		previousPhaseEvent = phaseWrapper;

		// calculate the sample value
		phaseArray[i] = phase;
	}

	return phase;

}

int advancePhaseEnv(q31_t * incrementValues1, q31_t * incrementValues2, q31_t * triggerValues, q31_t * gateValues, int phase, int oscillatorActive, q31_t * phaseArray, q31_t * phaseEventArray) {


	static q31_t previousPhase;
	static q31_t previousPhaseEvent;
	q31_t phaseWrapper;

	for (int i = 0; i < BUFFER_SIZE; i++) {

		int increment = (*envStateMachine)(triggerValues[i], previousPhaseEvent, incrementValues1[i], incrementValues2[i]);

		phase = (phase + increment);// * (oscillatorActive);

		phaseWrapper = 0;

		// add wavetable length if phase < 0

		phaseWrapper += ((uint32_t)(phase) >> 31) * WAVETABLE_LENGTH;

		// subtract wavetable length if phase > wavetable length

		phaseWrapper -= ((uint32_t)(WAVETABLE_LENGTH - phase) >> 31) * WAVETABLE_LENGTH;

		// apply the wrapping
		// no effect if the phase is in bounds

		phase += phaseWrapper;

		// log a -1 if the max value index of the wavetable is traversed from the left
		// log a 1 if traversed from the right
		// do this by subtracting the sign bit of the last phase from the current phase, both less the max phase index
		// this adds cruft to the wrap indicators, but that is deterministic and can be parsed out

		phaseWrapper += ((uint32_t)(phase - WAVETABLE_MAX_VALUE_PHASE) >> 31) - ((uint32_t)(previousPhase - WAVETABLE_MAX_VALUE_PHASE) >> 31);

		phaseEventArray[i] = phaseWrapper;

		// TODO rewrite logic parsing function

		// store the current phase
		previousPhase = phase;
		previousPhaseEvent = phaseWrapper;

		// calculate the sample value
		phaseArray[i] = phase;
	}

	return phase;

}

int advancePhaseGate(q31_t * incrementValues1, q31_t * incrementValues2, q31_t * triggerValues, q31_t * gateValues, int phase, int oscillatorActive, q31_t * phaseArray, q31_t * phaseEventArray) {


	static q31_t previousPhase;
	static q31_t previousPhaseEvent;
	q31_t phaseWrapper;

	for (int i = 0; i < BUFFER_SIZE; i++) {

		int increment = (*gateStateMachine)(gateValues[i], previousPhaseEvent, incrementValues1[i], incrementValues2[i]);

		phase = (phase + increment);// * (oscillatorActive);

		phaseWrapper = 0;

		// add wavetable length if phase < 0

		phaseWrapper += ((uint32_t)(phase) >> 31) * WAVETABLE_LENGTH;

		// subtract wavetable length if phase > wavetable length

		phaseWrapper -= ((uint32_t)(WAVETABLE_LENGTH - phase) >> 31) * WAVETABLE_LENGTH;

		// apply the wrapping
		// no effect if the phase is in bounds

		phase += phaseWrapper;

		// log a -1 if the max value index of the wavetable is traversed from the left
		// log a 1 if traversed from the right
		// do this by subtracting the sign bit of the last phase from the current phase, both less the max phase index
		// this adds cruft to the wrap indicators, but that is deterministic and can be parsed out

		phaseWrapper += ((uint32_t)(phase - WAVETABLE_MAX_VALUE_PHASE) >> 31) - ((uint32_t)(previousPhase - WAVETABLE_MAX_VALUE_PHASE) >> 31);

		phaseEventArray[i] = phaseWrapper;

		// TODO rewrite logic parsing function

		// store the current phase
		previousPhase = phase;
		previousPhaseEvent = phaseWrapper;

		// calculate the sample value
		phaseArray[i] = phase;
	}

	return phase;

}

int advancePhasePendulum(q31_t * incrementValues1, q31_t * incrementValues2, q31_t * triggerValues, q31_t * gateValues, int phase, int oscillatorActive, q31_t * phaseArray, q31_t * phaseEventArray) {


	static q31_t previousPhase;
	static q31_t previousPhaseEvent;
	q31_t phaseWrapper;

	for (int i = 0; i < BUFFER_SIZE; i++) {

		int increment = (*pendulumStateMachine)(triggerValues[i], previousPhaseEvent, incrementValues1[i], incrementValues2[i]);

		phase = (phase + increment);// * (oscillatorActive);

		phaseWrapper = 0;

		// add wavetable length if phase < 0

		phaseWrapper += ((uint32_t)(phase) >> 31) * WAVETABLE_LENGTH;

		// subtract wavetable length if phase > wavetable length

		phaseWrapper -= ((uint32_t)(WAVETABLE_LENGTH - phase) >> 31) * WAVETABLE_LENGTH;

		// apply the wrapping
		// no effect if the phase is in bounds

		phase += phaseWrapper;

		// log a -1 if the max value index of the wavetable is traversed from the left
		// log a 1 if traversed from the right
		// do this by subtracting the sign bit of the last phase from the current phase, both less the max phase index
		// this adds cruft to the wrap indicators, but that is deterministic and can be parsed out

		phaseWrapper += ((uint32_t)(phase - WAVETABLE_MAX_VALUE_PHASE) >> 31) - ((uint32_t)(previousPhase - WAVETABLE_MAX_VALUE_PHASE) >> 31);

		phaseEventArray[i] = phaseWrapper;

		// TODO rewrite logic parsing function

		// store the current phase
		previousPhase = phase;
		previousPhaseEvent = phaseWrapper;

		// calculate the sample value
		phaseArray[i] = phase;

	}

	return phase;

}

// SLOW
//static inline void wrapPhaseAndLog(int * phaseValue, int * phaseWrapper, int * previousPhase, int * previousPhaseEvent, int bufferIndex, q31_t * phaseBuffer, q31_t * phaseEventBuffer) {
//
//	// start with a 0 for no event
//
//	*phaseWrapper = 0;
//
//	// add wavetable length if phase < 0
//
//	*phaseWrapper += ((uint32_t)(*phaseValue) >> 31) * WAVETABLE_LENGTH;
//
//	// subtract wavetable length if phase > wavetable length
//
//	*phaseWrapper -= ((uint32_t)(WAVETABLE_LENGTH - *phaseValue) >> 31) * WAVETABLE_LENGTH;
//
//	// apply the wrapping
//	// no effect if the phase is in bounds
//
//	*phaseValue += *phaseWrapper;
//
//	// log a -1 if the max value index of the wavetable is traversed from the left
//	// log a 1 if traversed from the right
//	// do this by subtracting the sign bit of the last phase from the current phase, both less the max phase index
//	// this adds cruft to the wrap indicators, but that is deterministic and can be parsed out
//
//	*phaseWrapper += ((uint32_t)(*phaseValue - WAVETABLE_MAX_VALUE_PHASE) >> 31) - ((uint32_t)(*previousPhase - WAVETABLE_MAX_VALUE_PHASE) >> 31);
//
//	phaseEventBuffer[bufferIndex] = *phaseWrapper;
//
//	// TODO rewrite logic parsing function
//
//	// store the current phase
//	*previousPhase = *phaseValue;
//	*previousPhaseEvent = *phaseWrapper;
//
//	// calculate the sample value
//	phaseBuffer[bufferIndex] = *phaseValue;
//
//
//}




