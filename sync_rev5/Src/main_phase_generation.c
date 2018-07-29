#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"
#include "main_state_machine.h"
#include "tables.h"
#include "dsp.h"
#include "fill_buffer.h"


int getIncrementAttack(viaStateVariableSet * stateVariables) {
	if (stateVariables->phaseEvent) {
		getIncrement = getIncrementRelease;
		return stateVariables->incrementValue2;
	} else {
		return stateVariables->incrementValue1;
	}
}
int getIncrementRelease(viaStateVariableSet * stateVariables) {
	if (stateVariables->phaseEvent) {
		getIncrement = getIncrementAttack;
		return stateVariables->incrementValue1;
	} else {
		return stateVariables->incrementValue2;
	}
}

void advancePhaseRoot(audioRateInputs * inputs, viaStateVariableSet * stateVariables) {

	q31_t phase = stateVariables->phase;
	static q31_t previousPhase;

	int increment = (*getIncrement)(stateVariables);
	phase += increment;

	int phaseEventCalculator = 0;

	// add wavetable length if phase < 0

	phaseEventCalculator += ((uint32_t)(phase) >> 31) * WAVETABLE_LENGTH;

	// subtract wavetable length if phase > wavetable length

	phaseEventCalculator -= ((uint32_t)(WAVETABLE_LENGTH - phase) >> 31) * WAVETABLE_LENGTH;

	// apply the wrapping
	// no effect if the phase is in bounds

	phase += phaseEventCalculator;

	// log a -1 if the max value index of the wavetable is traversed from the left
	// log a 1 if traversed from the right
	// do this by subtracting the sign bit of the last phase from the current phase, both less the max phase index
	// this adds cruft to the wrap indicators, but that is deterministic and can be parsed out

	int atBIndicator = ((uint32_t)(phase - AT_B_PHASE) >> 31) - ((uint32_t)(previousPhase - AT_B_PHASE) >> 31);

	phaseEventCalculator += atBIndicator;

	stateVariables->phaseEvent = phaseEventCalculator;

	stateVariables->dutyCycle = 2048;

	// store the current phase
	previousPhase = phase;

	stateVariables->phase = phase;

}
void advancePhasePM(audioRateInputs * inputs, viaStateVariableSet * stateVariables) {

	q31_t phase = stateVariables->phase;
	static q31_t previousPhase;
	static q31_t lastCV;

	int increment = (*getIncrement)(stateVariables);
	q31_t cvInput = inputs->cv2Input;
	phase += increment + ((cvInput - lastCV) << 13);
	lastCV = cvInput;

	int phaseEventCalculator = 0;

	// add wavetable length if phase < 0

	phaseEventCalculator += ((uint32_t)(phase) >> 31) * WAVETABLE_LENGTH;

	// subtract wavetable length if phase > wavetable length

	phaseEventCalculator -= ((uint32_t)(WAVETABLE_LENGTH - phase) >> 31) * WAVETABLE_LENGTH;

	// apply the wrapping
	// no effect if the phase is in bounds

	phase += phaseEventCalculator;

	// log a -1 if the max value index of the wavetable is traversed from the left
	// log a 1 if traversed from the right
	// do this by subtracting the sign bit of the last phase from the current phase, both less the max phase index
	// this adds cruft to the wrap indicators, but that is deterministic and can be parsed out

	int atBIndicator = ((uint32_t)(phase - AT_B_PHASE) >> 31) - ((uint32_t)(previousPhase - AT_B_PHASE) >> 31);

	phaseEventCalculator += atBIndicator;

	stateVariables->phaseEvent = phaseEventCalculator;

	stateVariables->dutyCycle = 2048;

	// store the current phase
	previousPhase = phase;

	stateVariables->phase = phase;

}
void advancePhaseFM(audioRateInputs * inputs, viaStateVariableSet * stateVariables) {

	q31_t phase = stateVariables->phase;
	static q31_t previousPhase;

	int increment = stateVariables->incrementValue1;
	phase += fix16_mul(increment, inputs->cv2Input << 5);

	int phaseEventCalculator = 0;

	// add wavetable length if phase < 0

	phaseEventCalculator += ((uint32_t)(phase) >> 31) * WAVETABLE_LENGTH;

	// subtract wavetable length if phase > wavetable length

	phaseEventCalculator -= ((uint32_t)(WAVETABLE_LENGTH - phase) >> 31) * WAVETABLE_LENGTH;

	// apply the wrapping
	// no effect if the phase is in bounds

	phase += phaseEventCalculator;

	// log a -1 if the max value index of the wavetable is traversed from the left
	// log a 1 if traversed from the right
	// do this by subtracting the sign bit of the last phase from the current phase, both less the max phase index
	// this adds cruft to the wrap indicators, but that is deterministic and can be parsed out

	int atBIndicator = ((uint32_t)(phase - AT_B_PHASE) >> 31) - ((uint32_t)(previousPhase - AT_B_PHASE) >> 31);

	phaseEventCalculator += atBIndicator;

	stateVariables->phaseEvent = phaseEventCalculator;

	stateVariables->dutyCycle = 2048;

	// store the current phase
	previousPhase = phase;

	stateVariables->phase = phase;

}
void advancePhasePWM(audioRateInputs * inputs, viaStateVariableSet * stateVariables) {

	q31_t phase = stateVariables->phase;
	static q31_t previousPhase;

	int increment = stateVariables->incrementValue1;
	phase += increment;

	int phaseEventCalculator = 0;

	// add wavetable length if phase < 0

	phaseEventCalculator += ((uint32_t)(phase) >> 31) * WAVETABLE_LENGTH;

	// subtract wavetable length if phase > wavetable length

	phaseEventCalculator -= ((uint32_t)(WAVETABLE_LENGTH - phase) >> 31) * WAVETABLE_LENGTH;

	// apply the wrapping
	// no effect if the phase is in bounds

	phase += phaseEventCalculator;

	// log a -1 if the max value index of the wavetable is traversed from the left
	// log a 1 if traversed from the right
	// do this by subtracting the sign bit of the last phase from the current phase, both less the max phase index
	// this adds cruft to the wrap indicators, but that is deterministic and can be parsed out

	int atBIndicator = ((uint32_t)(phase - AT_B_PHASE) >> 31) - ((uint32_t)(previousPhase - AT_B_PHASE) >> 31);

	phaseEventCalculator += atBIndicator;

	stateVariables->phaseEvent = phaseEventCalculator;

	stateVariables->dutyCycle = inputs->cv2Input;

	// store the current phase
	previousPhase = phase;

	stateVariables->phase = phase;
}
