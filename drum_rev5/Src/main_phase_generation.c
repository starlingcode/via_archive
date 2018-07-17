#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"
#include "main_state_machine.h"
#include "tables.h"
#include "dsp.h"
#include "fill_buffer.h"

const uint32_t expoTable[4096] = expotable10oct;

// fill incrementValues 1 and 2 with the attack and release time increments, respectively

void getIncrementsAudio(q31_t * t2CV, controlRateInputs * controlInputs, q31_t * attackIncrements,  q31_t * releaseIncrements) {

	// t1 is coarse, t2 is fine, release time = attack time

	q31_t frequencyMultiplier = fix16_mul(expoTable[controlInputs->knob1Value] >> 3, expoTable[controlInputs->cv1Value] >> 2);
	arm_fill_q31(frequencyMultiplier, attackIncrements, BUFFER_SIZE);
	arm_fill_q31(frequencyMultiplier, releaseIncrements, BUFFER_SIZE);

}

void getIncrementsEnv(q31_t * t2CV, controlRateInputs * controlInputs, q31_t * attackIncrements,  q31_t * releaseIncrements) {

	// t1 is attack time (attackIncrements), t2 is release time (releaseIncrements)

	int attackTime = expoTable[(4095 - controlInputs->knob1Value) >> 1] >> 10;
	int releaseTime = expoTable[(4095 - controlInputs->knob2Value) >> 1] >> 10;

	arm_fill_q31(attackTime, attackIncrements, BUFFER_SIZE);
	arm_fill_q31(releaseTime, releaseIncrements, BUFFER_SIZE);


}


void getIncrementsSeq(q31_t * t2CV, controlRateInputs * controlInputs, q31_t * attackIncrements,  q31_t * releaseIncrements) {

	// t1 is cycle time, t2 is used to feed the duty cycle input for getSamples

	q31_t frequencyMultiplier = fix16_mul(expoTable[4095 - controlInputs->knob1Value] >> 6, expoTable[4095 - controlInputs->cv1Value] >> 6);
	arm_shift_q31(t2CV, 19, attackIncrements, BUFFER_SIZE);
	arm_scale_q31(attackIncrements, frequencyMultiplier, 0, attackIncrements, BUFFER_SIZE);
	arm_copy_q31(attackIncrements, releaseIncrements, BUFFER_SIZE);

}

void generateDrumEnv(q31_t time, q31_t * triggers, q31_t * drumEnv) {

	static int drumPhase;
	static int drumState;

	#define drumResting 0
	#define drumAttacking 1
	#define drumReleasing 2

	for (int i = 0; i < BUFFER_SIZE; i++) {
		switch (drumState) {
		case drumResting:
			// keep the drum envelope at 0
			drumEnv[i] = 0;
			// if there is a 0 in the trigger array (rising edge), set the drum state to attack
			drumState |= !triggers[i];
			break;
		case drumAttacking:
			// increment the drum envelope phase
			drumPhase += (65535 << 5);
			// extract the sign bit of drumPhase less the max valid interpolation index
			// the expression returns 0 if the phase has exceeded (4094 << 16) (max valid interpolation index), 1 otherwise
			// invert for a more useful value, aka 1 if overflow
			uint32_t endOfAttack = !((uint32_t)(drumPhase - (4094 << 16)) >> 31);
			// if 0, switch to release state
			drumState += endOfAttack;
			// funny way of clamping at 4094 by incrementing back to 4094 if greater than 4094
			drumPhase -= endOfAttack * (drumPhase - (4094 << 16));
			uint32_t envelopeSampleIndex = drumPhase >> 16;
			drumEnv[i] = fix16_lerp(expoTable[envelopeSampleIndex], expoTable[envelopeSampleIndex + 1], drumPhase & 0xFFFF) >> 16;
			break;
		case drumReleasing:
			// increment the drum envelope phase
				drumState -= !triggers[i];
				drumPhase -= expoTable[time] >> 8;
				// extract the sign bit of drumPhase less the max valid interpolation index
				// the expression returns 1 if the phase is negative, 0 otherwise
				// no need to invert
				uint32_t endOfRelease = ((uint32_t)(drumPhase) >> 31);
				// if 0, switch to resting state
				drumState -= endOfRelease * 2;
				// funny way of clamping at 0 by incrementing back to 4094 if greater than 4094
				drumPhase -= endOfRelease * (drumPhase);
				envelopeSampleIndex = drumPhase >> 16;
				drumEnv[i] = fix16_lerp(expoTable[envelopeSampleIndex], expoTable[envelopeSampleIndex + 1], drumPhase & 0xFFFF) >> 16;

			break;
		default:
			break;
		}
	}

}

// use those increment values to calculate a phase array and phase event array
// see main_trigger_states.c for more

int advancePhaseNoRetrig(q31_t * attackIncrements, q31_t * releaseIncrements, q31_t * triggerValues, q31_t * gateValues, int phase, int * oscillatorActiveFlag, q31_t * phaseArray, q31_t * phaseEventArray) {

	static q31_t previousPhase;
	static q31_t previousPhaseEvent;
	q31_t phaseWrapper = 0;
	int oscillatorActive;

	oscillatorActive = *oscillatorActiveFlag;

	for (int i = 0; i < BUFFER_SIZE; i++) {

		int increment = (*noRetrigStateMachine)(triggerValues[i], previousPhaseEvent, attackIncrements[i], releaseIncrements[i]);

		phase = (phase + __SSAT(increment, 24)) * (oscillatorActive);

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

		phaseWrapper += ((uint32_t)(phase - AT_B_PHASE) >> 31) - ((uint32_t)(previousPhase - AT_B_PHASE) >> 31);

		phaseEventArray[i] = phaseWrapper * (oscillatorActive);

		// TODO rewrite logic parsing function

		// store the current phase
		previousPhase = phase;
		previousPhaseEvent = phaseWrapper;

		oscillatorActive = (*handleLoop)(previousPhaseEvent, triggerValues[i]);

		// calculate the sample value
		phaseArray[i] = phase;

	}

	*oscillatorActiveFlag  = oscillatorActive;
	return phase;

}

int advancePhaseHardSync(q31_t * attackIncrements, q31_t * releaseIncrements, q31_t * triggerValues, q31_t * gateValues, int phase, int * oscillatorActiveFlag, q31_t * phaseArray, q31_t * phaseEventArray) {


	static q31_t previousPhase;
	static q31_t previousPhaseEvent;
	q31_t phaseWrapper;
	int oscillatorActive;

	oscillatorActive = *oscillatorActiveFlag;

	for (int i = 0; i < BUFFER_SIZE; i++) {

		int increment = (*hardSyncStateMachine)(triggerValues[i], previousPhaseEvent, attackIncrements[i], releaseIncrements[i]);

		phase = (phase + __SSAT(increment, 24)) * triggerValues[i] * (oscillatorActive);

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

		phaseWrapper += ((uint32_t)(phase - AT_B_PHASE) >> 31) - ((uint32_t)(previousPhase - AT_B_PHASE) >> 31);

		phaseEventArray[i] = phaseWrapper * (oscillatorActive);

		// TODO rewrite logic parsing function

		// store the current phase
		previousPhase = phase;
		previousPhaseEvent = phaseWrapper;

		oscillatorActive = (*handleLoop)(previousPhaseEvent, triggerValues[i]);


		// calculate the sample value
		phaseArray[i] = phase;
	}

	*oscillatorActiveFlag  = oscillatorActive;
	return phase;

}

int advancePhaseEnv(q31_t * attackIncrements, q31_t * releaseIncrements, q31_t * triggerValues, q31_t * gateValues, int phase, int * oscillatorActiveFlag, q31_t * phaseArray, q31_t * phaseEventArray) {


	static q31_t previousPhase;
	static q31_t previousPhaseEvent;
	q31_t phaseWrapper;
	int oscillatorActive;

	oscillatorActive = *oscillatorActiveFlag;

	for (int i = 0; i < BUFFER_SIZE; i++) {

		int increment = (*envStateMachine)(triggerValues[i], previousPhaseEvent, attackIncrements[i], releaseIncrements[i]);

		phase = (phase + __SSAT(increment, 24)) * (oscillatorActive);

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

		phaseWrapper += ((uint32_t)(phase - AT_B_PHASE) >> 31) - ((uint32_t)(previousPhase - AT_B_PHASE) >> 31);

		phaseEventArray[i] = phaseWrapper;

		// TODO rewrite logic parsing function

		// store the current phase
		previousPhase = phase;
		previousPhaseEvent = phaseWrapper;

		oscillatorActive = (*handleLoop)(previousPhaseEvent, triggerValues[i]);

		// calculate the sample value
		phaseArray[i] = phase;
	}

	*oscillatorActiveFlag  = oscillatorActive;
	return phase;

}

int advancePhaseGate(q31_t * attackIncrements, q31_t * releaseIncrements, q31_t * triggerValues, q31_t * gateValues, int phase, int * oscillatorActiveFlag, q31_t * phaseArray, q31_t * phaseEventArray) {


	static q31_t previousPhase;
	static q31_t previousPhaseEvent;
	q31_t phaseWrapper;
	int oscillatorActive;

	oscillatorActive = *oscillatorActiveFlag;

	for (int i = 0; i < BUFFER_SIZE; i++) {

		int increment = (*gateStateMachine)(gateValues[i], previousPhaseEvent, attackIncrements[i], releaseIncrements[i]);

		phase = (phase + __SSAT(increment, 24)) * (oscillatorActive);

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

		int atBIndicator = ((uint32_t)(phase - AT_B_PHASE) >> 31) - ((uint32_t)(previousPhase - AT_B_PHASE) >> 31);

		phaseWrapper += atBIndicator;

		// stick the position to WAVETABLE AT_B_PHASE
		phase += (AT_B_PHASE - phase) * (abs(atBIndicator) & gateValues[i]);

		phaseEventArray[i] = phaseWrapper;

		// TODO rewrite logic parsing function

		// store the current phase
		previousPhase = phase;
		previousPhaseEvent = phaseWrapper;

		oscillatorActive = (*handleLoop)(previousPhaseEvent, triggerValues[i]);


		// calculate the sample value
		phaseArray[i] = phase;
	}

	*oscillatorActiveFlag  = oscillatorActive;
	return phase;

}

int advancePhasePendulum(q31_t * attackIncrements, q31_t * releaseIncrements, q31_t * triggerValues, q31_t * gateValues, int phase, int * oscillatorActiveFlag, q31_t * phaseArray, q31_t * phaseEventArray) {


	static q31_t previousPhase;
	static q31_t previousPhaseEvent;
	q31_t phaseWrapper;
	int oscillatorActive;
	static int oscillatorActiveLastSample;

	oscillatorActive = *oscillatorActiveFlag;


	for (int i = 0; i < BUFFER_SIZE; i++) {

		int increment = (*pendulumStateMachine)(triggerValues[i], previousPhaseEvent, oscillatorActiveLastSample, attackIncrements[i], releaseIncrements[i]);

		phase = (phase + __SSAT(increment, 24)) * (oscillatorActive);

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

		phaseWrapper += ((uint32_t)(phase - AT_B_PHASE) >> 31) - ((uint32_t)(previousPhase - AT_B_PHASE) >> 31);

		phaseEventArray[i] = phaseWrapper;

		// TODO rewrite logic parsing function

		// store the current phase
		previousPhase = phase;
		previousPhaseEvent = phaseWrapper;

		oscillatorActiveLastSample = oscillatorActive;

		oscillatorActive = (*handleLoop)(previousPhaseEvent, triggerValues[i]);


		// calculate the sample value
		phaseArray[i] = phase;

	}

	*oscillatorActiveFlag  = oscillatorActive;
	return phase;

}

int handleLoopOn(q31_t phaseEvents, q31_t trigger) {
	return 1;
}

int handleLoopOff(q31_t phaseEvents, q31_t trigger) {

	static int oscillatorActiveState;

	oscillatorActiveState |= !trigger;

	oscillatorActiveState &= !(abs(phaseEvents) >> 24);

	return oscillatorActiveState;


}

