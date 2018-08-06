#ifndef FILL_BUFFER
#define FILL_BUFFER

#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"
#include "signals.h"

typedef struct {
	q31_t incrementValue1;
	q31_t incrementValue2;
	q31_t phase;
	q31_t phaseEvent;
	q31_t dutyCycle;
	q31_t morph;
	int lastPhase;
	int delta;
	int oscillatorOn;
	uint32_t slowConversionCounter;
} viaStateVariableSet;


// assume a fixed wavetable length in samples, in this case 512

#define WAVETABLE_LENGTH 33554432
#define NEGATIVE_WAVETABLE_LENGTH -33554432 // wavetable length in 16 bit fixed point (512 << 16)
#define AT_B_PHASE 16777216 // wavetable midpoint in 16 bit fixed point (256 << 16)

// phase events defines generated in advancePhase

#define NO_EVENT 0
#define AT_A_FROM_RELEASE -WAVETABLE_LENGTH + 1
#define AT_A_FROM_ATTACK WAVETABLE_LENGTH - 1
#define AT_B_FROM_ATTACK -1
#define AT_B_FROM_RELEASE 1

void nextSample(controlRateInputs * controls, audioRateInputs * inputs, audioRateOutputs * outputs, softwareSignaling *);

void (*advancePhase)(audioRateInputs *, viaStateVariableSet *);

void advancePhaseRoot(audioRateInputs *, viaStateVariableSet *);
void advancePhasePM(audioRateInputs *, viaStateVariableSet *);
void advancePhaseFM(audioRateInputs *, viaStateVariableSet *);
void advancePhasePWM(audioRateInputs *, viaStateVariableSet *);

int (*getIncrement)(viaStateVariableSet *);

int getIncrementAttack(viaStateVariableSet *);
int getIncrementRelease(viaStateVariableSet *);

void calculateSample(controlRateInputs *, audioRateInputs *, viaStateVariableSet *, audioRateOutputs * output);

void (*calculateLogicA)(viaStateVariableSet *, audioRateOutputs * output);

void calculateLogicAGate(viaStateVariableSet *, audioRateOutputs * output);
void calculateLogicADelta(viaStateVariableSet *, audioRateOutputs * output);

void calculateDac3(viaStateVariableSet *, audioRateOutputs * output);

void calculateAuxLogic(viaStateVariableSet *, audioRateOutputs * output);

void (*calculateSH)(viaStateVariableSet *, audioRateOutputs * output);

void calculateSHMode1(viaStateVariableSet *, audioRateOutputs * output);
void calculateSHMode2(viaStateVariableSet *, audioRateOutputs * output);
void calculateSHMode3(viaStateVariableSet *, audioRateOutputs * output);

void (*updateRGB)(controlRateInputs *, audioRateInputs *, int, int);
void updateRGBAudio(controlRateInputs *, audioRateInputs *, int, int);
void updateRGBSubAudio(controlRateInputs *, audioRateInputs *, int, int);
void updateRGBTrigger(controlRateInputs *, audioRateInputs *, int, int);
void updateRGBBlank(controlRateInputs *, audioRateInputs *, int, int);

void generateFrequency(controlRateInputs * controls, audioRateInputs * inputs, softwareSignaling * softwareSignals);

#endif
