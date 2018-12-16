/*
 * oscillators.h
 *
 *  Created on: Aug 18, 2018
 *      Author: willmitchell
 */

#ifndef INC_OSCILLATORS_HPP_
#define INC_OSCILLATORS_HPP_

#include <via_platform_binding.hpp>
#include "tables.hpp"
#include "scales.hpp"

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


class SyncWavetable {

	int32_t previousPhase = 0;
	int32_t previousPhaseMod = 0;

public:

	// assigned per mode
	int16_t * fm;
	int16_t * pm;
	int16_t * pwm;
	int16_t * morphMod;
	int32_t cv2Offset = 0;
	uint32_t tableSize = 0;

	// generated externally
	int32_t phaseReset = 1;
	int32_t increment = 0;
	int32_t morphBase = 0;

	// results
	int32_t phaseMod = 0;
	int32_t phase = 0;
	int32_t ghostPhase = 0;
	int32_t phaseEvent = 0;
	int32_t delta = 0;

	int32_t phaseOut[32];
	int32_t signalOut[32];

	int32_t oversamplingFactor = 3;
	int32_t bufferSize = 8;

	void parseControls(ViaControls * controls);

	inline int32_t incrementPhase(uint32_t * phaseDistTable);

	void oversample(uint32_t * wavetable,
			uint32_t * phaseDistTable);

	void spline(uint32_t * wavetable,
			uint32_t * phaseDistTable);

	void advance(uint32_t * wavetable,
			uint32_t * phaseDistTable) {
		if (increment > (1 << 22)) {
			oversample(wavetable, phaseDistTable);
		} else {
			spline(wavetable, phaseDistTable);
		}
	}


};





// simplest wavetable, provide a phase and a morph

class MetaWavetable {

public:

	int32_t morphBase = 0;
	int16_t * morphMod;
	int16_t * morphScale;
	int32_t phase = 0;
	uint32_t tableSize = 0;
	int32_t increment = 0;

	int32_t oversamplingFactor = 3;
	int32_t bufferSize = 8;

	// results
	int32_t delta = 0;

	int32_t phaseOut[32];
	int32_t signalOut[32];

	void parseControls(ViaControls * controls);

	void advance(uint32_t * wavetable) {
		if (oversamplingFactor) {
			advanceOversampled(wavetable);
		} else {
			advanceSingleSample(wavetable);
		}
	}

	void advanceSingleSample(uint32_t * wavetable);

	void advanceOversampled(uint32_t * wavetable);

};


// cheap version of that with bilinear interpolation

class CheapWavetable {

public:

	int32_t morphBase = 0;
	int16_t * morphMod;
	int32_t phase = 0;
	uint32_t tableSize = 0;

	void parseControls(ViaControls * controls);
	int32_t advance(uint32_t * wavetable);

};


/*
 *
 * Shared resources
 *
 */

// pll with multiplier

class PllController {

	uint32_t pllCounter;
	int32_t lastMultiplier;
	int32_t lastYIndex;

public:

	uint32_t virtualTimer;

	uint32_t periodCount = 100000;
	int32_t pllNudge = 0;
	buffer nudgeBuffer;
	int32_t nudgeSum = 0;

	uint32_t phaseSignal = 0;
	uint32_t phaseModSignal = 0;
	uint32_t tapTempo = 0;
	uint32_t pllReset = 0;

	int16_t * rootMod;
	uint32_t phaseOffset = 0;
	uint32_t syncMode = 0;
	Scale * scale;

	uint32_t fracMultiplier = 0;
	uint32_t intMultiplier = 0;
	uint32_t gcd = 0;

	uint32_t increment = 0;
	uint32_t phaseReset = 0;
	uint32_t ratioChange = 0;
	uint32_t yIndexChange = 0;

	int32_t lastRatioX = 1;
	int32_t ratioXTransitionPoint = 0;
	int32_t ratioXStable = 0;

	int32_t ratioXHysterisis(int32_t thisRatioX, int32_t control) {

		if (ratioXStable) {
			ratioXStable = ((lastRatioX - thisRatioX) == 0);
			ratioXTransitionPoint = control & 0b111111100000;
			lastRatioX = thisRatioX;
			return thisRatioX;
		} else {
			ratioXStable = abs(control - ratioXTransitionPoint) > 8;
			lastRatioX = ratioXStable ? thisRatioX : lastRatioX;
			return lastRatioX;
		}

	}

	int32_t lastRatioY = 1;
	int32_t ratioYTransitionPoint = 0;
	int32_t ratioYStable = 0;

	int32_t ratioYHysterisis(int32_t control, int32_t shiftAmount) {

		int32_t thisRatioY = control >> shiftAmount;

		if (ratioYStable) {
			ratioYStable = ((lastRatioY - thisRatioY) == 0);
			ratioYTransitionPoint = thisRatioY << shiftAmount;
			lastRatioY = thisRatioY;
			return thisRatioY;
		} else {
			ratioYStable = abs(control - ratioYTransitionPoint) > 8;
			lastRatioY = ratioYStable ? thisRatioY : lastRatioY;
			return lastRatioY;
		}

	}


	void parseControls(ViaControls * controls, ViaInputStreams * input);

	void measureFrequency(void) {

#ifdef BUILD_F373

		// store the length of the last period
		periodCount = TIM2->CNT;

		// reset the timer value
		TIM2->CNT = 0;
#endif

#ifdef BUILD_VIRTUAL

		periodCount = virtualTimer;
		virtualTimer = 0;

#endif

	}

	void doPLL(void);

	void generateFrequency(void);

};

// meta oscillator controller

class MetaController {

	int32_t previousGhostPhase = 0;
	int32_t previousPhase = 0;

public:

	int32_t timeBase1 = 0;
	int32_t timeBase2 = 0;
	int32_t dutyCycleBase = 0;
	int32_t triggerSignal = 0;
	int32_t gateSignal = 0;
	int32_t freeze = 0;
	int32_t gateOn = 0;
	uint32_t loopMode = 0;
	int32_t atB = 0;

	int32_t increment1 = 0;
	int32_t increment2 = 0;
	int32_t incrementUsed = 0;
	int32_t dutyCycle = 0;
	int32_t lastPhase = 0;
	int32_t oscillatorOn = 0;
	int16_t * fm;
	int32_t * expoFM;

	int32_t phase = 0;
	int32_t phaseBeforeIncrement;
	int32_t ghostPhase = 0;
	int32_t phaseEvent = 0;

	void parseControlsExternal(ViaControls * controls, ViaInputStreams * inputs);

	void (MetaController::*parseControls)(ViaControls * controls, ViaInputStreams * inputs);

	void parseControlsAudio(ViaControls * controls, ViaInputStreams * inputs);
	void parseControlsDrum(ViaControls * controls, ViaInputStreams * inputs);
	void parseControlsEnv(ViaControls * controls, ViaInputStreams * inputs);
	void parseControlsSeq(ViaControls * controls, ViaInputStreams * inputs);

	void generateIncrementsExternal(ViaInputStreams * inputs);

	void (MetaController::*generateIncrements)(ViaInputStreams * inputs);

	void generateIncrementsAudio(ViaInputStreams * inputs);
	void generateIncrementsDrum(ViaInputStreams * inputs);
	void generateIncrementsEnv(ViaInputStreams * inputs);
	void generateIncrementsSeq(ViaInputStreams * inputs);

	void advancePhaseExternal(uint32_t * phaseDistTable);

	int32_t (MetaController::*advancePhase)(uint32_t * phaseDistTable);
	int32_t advancePhasePWM(uint32_t * phaseDistTable);
	int32_t advancePhaseOversampled(uint32_t * phaseDistTable);


	int32_t (MetaController::*incrementArbiter)(void);

	int32_t noRetrigAttackState(void);
	int32_t noRetrigReleaseState(void);

	int32_t hardSyncAttackState(void);
	int32_t hardSyncReleaseState(void);

	int32_t envAttackState(void);
	int32_t envReleaseState(void);
	int32_t envRetriggerState(void);

	int32_t gateAttackState(void);
	int32_t gateReleaseReverseState(void);
	int32_t gatedState(void);
	int32_t gateReleaseState(void);
	int32_t gateRetriggerState(void);

	int32_t pendulumRestingState(void);
	int32_t pendulumForwardAttackState(void);
	int32_t pendulumForwardReleaseState(void);
	int32_t pendulumReverseAttackState(void);
	int32_t pendulumReverseReleaseState(void);

	int32_t stickyPendulumRestingState(void);
	int32_t stickyPendulumAtBState(void);
	int32_t stickyPendulumForwardAttackState(void);
	int32_t stickyPendulumForwardReleaseState(void);
	int32_t stickyPendulumReverseAttackState(void);
	int32_t stickyPendulumReverseReleaseState(void);

	void (MetaController::*loopHandler)(void);

	void handleLoopOff(void);
	void handleLoopOn(void);

};


// just the envelope

class SimpleEnvelope {

	int32_t previousPhase;

public:

	uint32_t attack = 100000;
	uint32_t release = 0;
	uint32_t increment = 0;
	uint32_t morph = 0;
	uint32_t phase = 0;
	int32_t phaseEvent = 0;
	uint32_t trigger;

	int32_t * output;

	void parseControls (ViaControls * controls, ViaInputStreams * inputs);
	void advance (ViaInputStreams * inputs, uint32_t * wavetable);

	int32_t (SimpleEnvelope::*incrementArbiter)(void);

	int32_t attackState(void);
	int32_t releaseState(void);
	int32_t retriggerState(void);
	int32_t restingState(void);

};

#endif /* INC_OSCILLATORS_HPP_ */
