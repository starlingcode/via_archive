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

/*
 *
 * Oscillators
 *
 */

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

/*
 *
 * Shared resources
 *
 */

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
	int phaseEvent;
	int delta;

} singleSampleWavetableParameters;

void singleSampleWavetableParseControls(controlRateInputs * controls,
		singleSampleWavetableParameters * parameters);

uint32_t singleSampleWavetableAdvance(
		singleSampleWavetableParameters * parameters,
		uint32_t * wavetable, uint32_t * phaseDistTable);

/*
 *
 * Shared resources
 *
 */

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



#endif /* INC_OSCILLATORS_H_ */
