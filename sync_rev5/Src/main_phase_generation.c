#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"
#include "main_state_machine.h"
#include "tables.h"
#include "dsp.h"
#include "fill_buffer.h"
#include "pwm_tables.h"

const q31_t phaseModPWMTables[33][65] = {phaseModPWM_0, phaseModPWM_1, phaseModPWM_2, phaseModPWM_3, phaseModPWM_4, phaseModPWM_5, phaseModPWM_6, phaseModPWM_7, phaseModPWM_8, phaseModPWM_9, phaseModPWM_10, phaseModPWM_11, phaseModPWM_12, phaseModPWM_13, phaseModPWM_14, phaseModPWM_15, phaseModPWM_16, phaseModPWM_17, phaseModPWM_18, phaseModPWM_19, phaseModPWM_20, phaseModPWM_21, phaseModPWM_22, phaseModPWM_23, phaseModPWM_24, phaseModPWM_25, phaseModPWM_26, phaseModPWM_27, phaseModPWM_28, phaseModPWM_29, phaseModPWM_30, phaseModPWM_31, phaseModPWM_32};

static inline int calculatePWMPhase(int, uint32_t);

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

	// TODO rewrite logic parsing function

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
	phase += increment + (cvInput - lastCV) << 8;
	lastCV = inputs->cv2Input;

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

	// TODO rewrite logic parsing function

	// store the current phase
	previousPhase = phase;

	stateVariables->phase = phase;

}
void advancePhaseFM(audioRateInputs * inputs, viaStateVariableSet * stateVariables) {

	q31_t phase = stateVariables->phase;
	static q31_t previousPhase;

	int increment = (*getIncrement)(stateVariables);
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

	// TODO rewrite logic parsing function

	// store the current phase
	previousPhase = phase;

	stateVariables->phase = phase;

}
void advancePhasePWM(audioRateInputs * inputs, viaStateVariableSet * stateVariables) {

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

	// TODO rewrite logic parsing function

	// store the current phase
	previousPhase = phase;

	// shift 12 bit cv left by 9 so max value is 32 in 16 bit (sigh)
	phase = calculatePWMPhase(phase, inputs->cv2Input << 9);

	stateVariables->phase = phase;
}

static inline int calculatePWMPhase(int phaseIn, uint32_t pwm) {

	#define phaseIndex (phaseIn >> 19)
	#define phaseFrac (phaseIn & 0b0000000000001111111111111111111) >> 3
	#define pwmIndex (pwm >> 16)
	#define pwmFrac (pwm & 0b00000000000000001111111111111111)
	uint32_t sampleA_0 = phaseModPWMTables[pwmIndex][phaseIndex];
	uint32_t sampleA_1 = phaseModPWMTables[pwmIndex][phaseIndex + 1];
	uint32_t sampleB_0 = phaseModPWMTables[pwmIndex + 1][phaseIndex];
	uint32_t sampleB_1 = phaseModPWMTables[pwmIndex + 1][phaseIndex + 1];

	int interp0 = fix16_lerp(sampleA_0, sampleA_1, phaseFrac);
	int interp1 = fix16_lerp(sampleB_0, sampleB_1, phaseFrac);

	return fix16_lerp(interp0, interp1, pwmFrac);

}
