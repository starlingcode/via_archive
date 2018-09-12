/*
 * oscillators.h
 *
 *  Created on: Aug 18, 2018
 *      Author: willmitchell
 */

#ifndef INC_OSCILLATORS_H_
#define INC_OSCILLATORS_H_

#include "via_platform_binding.h"
#include "tables.h"
#include "scales.h"

#define WAVETABLE_LENGTH 33554432
#define NEGATIVE_WAVETABLE_LENGTH -33554432 // wavetable length in 16 bit fixed point (512 << 16)
#define AT_B_PHASE 16777216 // wavetable midpoint in 16 bit fixed point (256 << 16)

// phase events
#define NO_EVENT 0
#define AT_A_FROM_RELEASE -WAVETABLE_LENGTH + 1
#define AT_A_FROM_ATTACK WAVETABLE_LENGTH - 1
#define AT_B_FROM_ATTACK -1
#define AT_B_FROM_RELEASE 1

/*
 *
 * Oscillators
 *
 */

// oversampled wavetable
// all controls read (maybe soon interpoated) per buffer

typedef struct {
	int16_t * fm;
	int16_t * pm;
	int16_t * pwm;
	int16_t * morphMod;
	int frequencyBase;
	int pmBase;
	int pwmBase;
	int morphBase;
	int syncInput;
	int reverseInput;
	int syncMode;
	int shOn;
	int tableSize;
} oversampledWavetableParameters;

void oversampledWavetableParseControls(controlRateInputs * controls,
		oversampledWavetableParameters * parameters);

uint32_t oversampledWavetableAdvance(
		oversampledWavetableParameters * parameters, audioRateOutputs * outputs,
		uint32_t * wavetable, uint32_t * phaseDistTable, uint32_t writePosition,
		uint32_t bufferSize);

void oversampledWavetableParsePhase(uint32_t phase,
		oversampledWavetableParameters * parameters, audioRateOutputs *output);

// single sample wavetable
// no buffering, looks to it's parameters each sample

typedef struct {

	// assigned per mode
	int16_t * fm;
	int16_t * pm;
	int16_t * pwm;
	int16_t * morphMod;
	int cv2Offset;
	uint32_t tableSize;

	// generated externally
	int phaseReset;
	int increment;
	int morphBase;

	// results
	int phase;
	int ghostPhase;
	int phaseEvent;
	int delta;

} singleSampleWavetableParameters;

void singleSampleWavetableParseControls(controlRateInputs * controls,
		singleSampleWavetableParameters * parameters);

uint32_t singleSampleWavetableAdvance(
		singleSampleWavetableParameters * parameters,
		uint32_t * wavetable, uint32_t * phaseDistTable);

// simplest wavetable, provide a phase and a morph

typedef struct {

	int morphBase;
	int16_t * morphMod;
	int16_t * morphScale;
	int phase;
	uint32_t tableSize;


	// results
	int delta;

} simpleWavetableParameters;

void simpleWavetableParseControls(controlRateInputs * controls, simpleWavetableParameters * parameters);
int simpleWavetableAdvance(simpleWavetableParameters * parameters, uint32_t * wavetable);

// cheap version of that with bilinear interpolation

typedef struct {

	int morphBase;
	int16_t * morphMod;
	int phase;
	uint32_t tableSize;

} cheapWavetableParameters;

void cheapWavetableParseControls(controlRateInputs * controls, cheapWavetableParameters * parameters);
int cheapWavetableAdvance(cheapWavetableParameters * parameters, uint32_t * wavetable);


/*
 *
 * Shared resources
 *
 */


// pll with multiplier

typedef struct {

	uint32_t periodCount;
	uint32_t pllNudge;

	uint32_t phaseSignal;
	uint32_t tapTempo;
	uint32_t pllReset;

	uint16_t * rootMod;
	uint32_t phaseOffset;
	uint32_t syncMode;
	Scale * scale;

	uint32_t fracMultiplier;
	uint32_t intMultiplier;
	uint32_t gcd;

	uint32_t increment;
	uint32_t phaseReset;
	uint32_t ratioChange;

} pllMultiplierParameters;

void pllMultiplierParseControls(controlRateInputs * controls, audioRateInputs * input,
		pllMultiplierParameters * parameters);

static inline void pllMultiplierMeasureFrequency(pllMultiplierParameters * parameters) {

	// store the length of the last period
	parameters->periodCount = TIM2->CNT;

	// reset the timer value
	TIM2->CNT = 0;

}

void pllMultiplierDoPLL(pllMultiplierParameters * parameters);

void pllMultiplierGenerateFrequency(pllMultiplierParameters * parameters);


// meta oscillator controller

typedef struct {

	int timeBase1;
	int timeBase2;
	int dutyCycleBase;
	int triggerSignal;
	int gateSignal;
	int freeze;
	int gateOn;
	uint32_t loopMode;

	int increment1;
	int increment2;
	int dutyCycle;
	int lastPhase;
	int oscillatorOn;
	int16_t * fm;

	int phase;
	int ghostPhase;
	int phaseEvent;

} metaControllerParameters;

void (*metaControllerParseControls)(controlRateInputs * controls, audioRateInputs * inputs,
		metaControllerParameters * parameters);

void metaControllerParseControlsAudio(controlRateInputs * controls, audioRateInputs * inputs,
		metaControllerParameters * parameters);
void metaControllerParseControlsDrum(controlRateInputs * controls, audioRateInputs * inputs,
		metaControllerParameters * parameters);
void metaControllerParseControlsEnv(controlRateInputs * controls, audioRateInputs * inputs,
		metaControllerParameters * parameters);
void metaControllerParseControlsSeq(controlRateInputs * controls, audioRateInputs * inputs,
		metaControllerParameters * parameters);

void (*metaControllerGenerateIncrements)(metaControllerParameters * parameters, audioRateInputs * inputs);

void metaControllerGenerateIncrementsAudio(metaControllerParameters * parameters, audioRateInputs * inputs);
void metaControllerGenerateIncrementsDrum(metaControllerParameters * parameters, audioRateInputs * inputs);
void metaControllerGenerateIncrementsEnv(metaControllerParameters * parameters, audioRateInputs * inputs);
void metaControllerGenerateIncrementsSeq(metaControllerParameters * parameters, audioRateInputs * inputs);

int metaControllerAdvancePhase(metaControllerParameters * parameters, uint32_t * phaseDistTable);

int (*metaControllerIncrementArbiter)(metaControllerParameters * parameters);

int noRetrigAttackState(metaControllerParameters * parameters);
int noRetrigReleaseState(metaControllerParameters * parameters);

int hardSyncAttackState(metaControllerParameters * parameters);
int hardSyncReleaseState(metaControllerParameters * parameters);

int envAttackState(metaControllerParameters * parameters);
int envReleaseState(metaControllerParameters * parameters);
int envRetriggerState(metaControllerParameters * parameters);

int gateAttackState(metaControllerParameters * parameters);
int gateReleaseReverseState(metaControllerParameters * parameters);
int gatedState(metaControllerParameters * parameters);
int gateReleaseState(metaControllerParameters * parameters);
int gateRetriggerState(metaControllerParameters * parameters);

int pendulumRestingState(metaControllerParameters * parameters);
int pendulumForwardAttackState(metaControllerParameters * parameters);
int pendulumForwardReleaseState(metaControllerParameters * parameters);
int pendulumReverseAttackState(metaControllerParameters * parameters);
int pendulumReverseReleaseState(metaControllerParameters * parameters);

int (*metaControllerLoopHandler)(metaControllerParameters * parameters);

int handleLoopOff(metaControllerParameters * parameters);
int handleLoopOn(metaControllerParameters * parameters);

// just the envelope

typedef struct {

	uint32_t attack;
	uint32_t release;
	uint32_t increment;
	uint32_t morph;
	uint32_t phase;
	uint32_t phaseEvent;
	uint32_t trigger;

	uint32_t * output;

} simpleEnvelopeParameters;

void simpleEnvelopeParseControls (controlRateInputs * controls, audioRateInputs * inputs,
		simpleEnvelopeParameters * parameters);
void simpleEnvelopeAdvance (simpleEnvelopeParameters * parameters, audioRateInputs * inputs,
		uint32_t * wavetable);

int (*simpleEnvelopeIncrementArbiter)(simpleEnvelopeParameters * parameters);

int simpleEnvelopeAttackState(simpleEnvelopeParameters * parameters);
int simpleEnvelopeReleaseState(simpleEnvelopeParameters * parameters);
int simpleEnvelopeRetriggerState(simpleEnvelopeParameters * parameters);
int simpleEnvelopeRestingState(simpleEnvelopeParameters * parameters);



#endif /* INC_OSCILLATORS_H_ */
