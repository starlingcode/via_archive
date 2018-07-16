#ifndef FILL_BUFFER
#define FILL_BUFFER

#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"
#include "dsp.h"

struct viaStateInfoHolder {
	q31_t incrementValues1[BUFFER_SIZE];
	q31_t incrementValues2[BUFFER_SIZE];
	q31_t phaseArray[BUFFER_SIZE];
	q31_t phaseEventArray[BUFFER_SIZE];
	int lastPhase;
	int oscillatorOn;
	uint32_t slowConversionCounter;
};


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

// TODO contain via state data in a struct and pass by reference

void (*getIncrements)(q31_t *, controlRateInputs *, q31_t *, q31_t *);

void getIncrementsAudio(q31_t *, controlRateInputs *, q31_t *, q31_t *);
void getIncrementsEnv(q31_t *, controlRateInputs *, q31_t *, q31_t *);
void getIncrementsSeq(q31_t *, controlRateInputs *, q31_t *, q31_t *);

int (*advancePhase)(q31_t *, q31_t *, q31_t *, q31_t *, int, int *, q31_t *, q31_t *);

int advancePhaseNoRetrig(q31_t *, q31_t *, q31_t *, q31_t *, int, int *, q31_t *, q31_t *);
int advancePhaseHardSync(q31_t *, q31_t *, q31_t *, q31_t *, int, int *, q31_t *, q31_t *);
int advancePhaseEnv(q31_t *, q31_t *, q31_t *, q31_t *, int, int *, q31_t *, q31_t *);
int advancePhaseGate(q31_t *, q31_t *, q31_t *, q31_t *, int, int *, q31_t *, q31_t *);
int advancePhasePendulum(q31_t *, q31_t *, q31_t *, q31_t *, int, int *, q31_t *, q31_t *);

int (*noRetrigStateMachine)(int, int, int, int);
int (*hardSyncStateMachine)(int, int, int, int);
int (*envStateMachine)(int, int, int, int);
int (*gateStateMachine)(int, int, int, int);
int (*pendulumStateMachine)(int, int, int, int, int);

int noRetrigAttackState(int, int, int, int);
int noRetrigReleaseState(int, int, int, int);

int hardSyncAttackState(int, int, int, int);
int hardSyncReleaseState(int, int, int, int);

int envAttackState(int, int, int, int);
int envReleaseState(int, int, int, int);
int envRetriggerState(int, int, int, int);

int gateAttackState(int, int, int, int);
int gateReleaseReverseState(int, int, int, int);
int gatedState(int, int, int, int);
int gateReleaseState(int, int, int, int);
int gateRetriggerState(int, int, int, int);

int pendulumRestingState(int, int, int, int, int);
int pendulumForwardAttackState(int, int, int, int, int);
int pendulumForwardReleaseState(int, int, int, int, int);
int pendulumReverseAttackState(int, int, int, int, int);
int pendulumReverseReleaseState(int, int, int, int, int);

int (*handleLoop)(q31_t, q31_t);

int handleLoopOff(q31_t, q31_t);
int handleLoopOn(q31_t, q31_t);

void (*getSamples)(q31_t *, int, q31_t *, q31_t *, q31_t *);

void getSamplesNoPWM(q31_t *, int, q31_t *, q31_t *, q31_t *);
void getSamplesPWM(q31_t *, int, q31_t *, q31_t *, q31_t *);

void (*calculateLogicA)(q31_t * phaseEvents, q31_t * triggers, int oscillatorOn, audioRateOutputs * output);

void calculateLogicAGate(q31_t * phaseEvents, q31_t * triggers, int oscillatorOn, audioRateOutputs * output);
void calculateLogicATrigger(q31_t * phaseEvents, q31_t * triggers, int oscillatorOn, audioRateOutputs * output);
void calculateLogicADelta(q31_t * phaseEvents, q31_t * triggers, int oscillatorOn, audioRateOutputs * output);

void (*calculateLogicB)(q31_t * phaseEvents, audioRateOutputs * output);

void calculateLogicBGate(q31_t * phaseEvents, audioRateOutputs * output);
void calculateLogicBTrigger(q31_t * phaseEvents, audioRateOutputs * output);
void calculateLogicBDelta(q31_t * phaseEvents, audioRateOutputs * output);

void calculateAuxLogic(q31_t * phaseEvents, audioRateOutputs * output);

void (*calculateSH)(q31_t * phaseEvents, audioRateOutputs * output);

void calculateSHMode1(q31_t * phaseEvents, audioRateOutputs * output);
void calculateSHMode2(q31_t * phaseEvents, audioRateOutputs * output);
void calculateSHMode3(q31_t * phaseEvents, audioRateOutputs * output);
void calculateSHMode4(q31_t * phaseEvents, audioRateOutputs * output);
void calculateSHMode5(q31_t * phaseEvents, audioRateOutputs * output);
void calculateSHMode6(q31_t * phaseEvents, audioRateOutputs * output);

#endif
