
#include "signals.h"
#include "via_rev5_hardware_io.h"
#include "../inc/osc_fill_buffer.h"
#include "../inc/osc_main_states.h"
#include "../inc/osc_modes.h"
#include "../inc/osc_tables.h"
#include "osc_pwm_tables.h"

// expo scaling for 1voct
const uint32_t expoTable[4096] = expotable10oct;
q31_t phaseModPWMTables[33][65] = {phaseModPWM_0, phaseModPWM_1, phaseModPWM_2, phaseModPWM_3, phaseModPWM_4, phaseModPWM_5, phaseModPWM_6, phaseModPWM_7, phaseModPWM_8, phaseModPWM_9, phaseModPWM_10, phaseModPWM_11, phaseModPWM_12, phaseModPWM_13, phaseModPWM_14, phaseModPWM_15, phaseModPWM_16, phaseModPWM_17, phaseModPWM_18, phaseModPWM_19, phaseModPWM_20, phaseModPWM_21, phaseModPWM_22, phaseModPWM_23, phaseModPWM_24, phaseModPWM_25, phaseModPWM_26, phaseModPWM_27, phaseModPWM_28, phaseModPWM_29, phaseModPWM_30, phaseModPWM_31, phaseModPWM_32, phaseModPWM_32};
//q31_t phaseModPWMTables[16][65] = {phaseModPWM_0, phaseModPWM_2, phaseModPWM_4, phaseModPWM_6, phaseModPWM_8, phaseModPWM_10, phaseModPWM_12, phaseModPWM_14, phaseModPWM_16, phaseModPWM_18, phaseModPWM_20, phaseModPWM_22, phaseModPWM_24, phaseModPWM_26, phaseModPWM_28, phaseModPWM_30, phaseModPWM_32};

q31_t fullScale[16] = {4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095};

void writeBuffer(buffer* buffer, int value) {
	buffer->buff[(buffer->writeIndex++) & 31] = value;
}

int readBuffer(buffer* buffer, int Xn) {
	return buffer->buff[(buffer->writeIndex + (~Xn)) & 31];
}


void parseControls(controlRateInputs * controls) {

	// TODO apply SIMD instructions?

	static uint32_t knob1Sum;
	static uint32_t knob2Sum;
	static uint32_t knob3Sum;
	static uint32_t cv1Sum;
	static buffer knob1Buffer;
	static buffer knob2Buffer;
	static buffer knob3Buffer;
	static buffer cv1Buffer;
	uint32_t knob1Value;
	uint32_t knob2Value;
	uint32_t knob3Value;
	uint32_t cv1Value;

	// implement a running average on the control rate CV controls
	knob1Sum = knob1 + knob1Sum - readBuffer(&knob1Buffer, 31);
	knob2Sum = knob2 + knob2Sum - readBuffer(&knob2Buffer, 31);

	// store the newest value in a ring buffer
	writeBuffer(&knob1Buffer, knob1);
	writeBuffer(&knob2Buffer, knob2);

	// write the averaged controls to the holding struct
	knob1Value = knob1Sum >> 5;
	knob2Value = knob2Sum >> 5;

	// implement a running average on the control rate CV controls
	knob3Sum = knob3 + knob3Sum - readBuffer(&knob3Buffer, 31);
	cv1Sum = cv1 + cv1Sum - readBuffer(&cv1Buffer, 31);

	// store the newest value in a ring buffer
	writeBuffer(&knob3Buffer, knob3);
	writeBuffer(&cv1Buffer, cv1);

	// write the averaged controls to the holding struct
	knob3Value = knob3Sum >> 5;
	cv1Value = cv1Sum >> 5;

	controls->frequency = fix16_mul(expoTable[cv1Value] >> 6, fix16_mul(expoTable[knob1Value], expoTable[knob2Value >> 4])) >> 10;
	controls->morph = knob3Value;

}


uint32_t phase;

void renderBuffer0(viaSignals * signals) {

	//EXPAND_LOGIC_HIGH

	// get signal class pointers
	softwareSignaling * softwareSignals = signals->softwareSignals;
	controlRateInputs * controls = signals->controls;
	audioRateInputs * inputs = signals->inputs;
	audioRateOutputs * outputs = signals->outputs;

	// calculate buffer rate parameters
	uint32_t increment = (((controls->frequency) * (-(int)inputs->fm[0] + 16383)) >> 6) * inputs->reverseInput;

	uint32_t pwm = inputs->pwm[0] + 32768;
	uint32_t pwmIndex = (pwm >> 11);
	uint32_t pwmFrac = (pwm & 0x7FF) << 4;
	uint32_t * pwmTable1 = phaseModPWMTables[pwmIndex];
	uint32_t * pwmTable2 = phaseModPWMTables[pwmIndex + 1];

	// scale morph to table size in 16.16 fixed point
	uint32_t morph = __USAT(((controls->morph << 4) - (int)inputs->morphMod[0]), 16) * softwareSignals->morphMultiplier;
	uint32_t morphIndex = morph >> 16;
	uint32_t morphFrac = morph & 0xFFFF;
	q31_t * wavetable1 = fullTableHoldArray[morphIndex] + 2;
	//q31_t * wavetable2 = fullTableHoldArray[morphIndex + 1] + 2;

	static uint32_t lastPhaseMod;
	uint32_t phaseMod = inputs->pm[0];
	phase += (phaseMod - lastPhaseMod) << 12;
	lastPhaseMod = phaseMod;

	phase *= inputs->syncInput;
	inputs->syncInput = 1;
	phase *= inputs->syncInput;
	inputs->syncInput = 1;

	uint32_t * buffer1 = outputs->dac1Samples;
	uint32_t * buffer2 = outputs->dac2Samples;
	uint32_t * buffer3 = outputs->dac3Samples;

	uint32_t leftSample;
	uint32_t result;

	uint32_t writeIndex = 0;
	uint32_t samplesRemaining = BUFFER_SIZE;

	while (samplesRemaining) {
		// phase pointer wraps at 32 bits
		phase = (phase + increment);
		// treat the msb of phase as a 6.15 (tablesize.interpolationbits) fixed point number
		// divide by right shifting phase size (32 bits) less table size (6 bits) to find the nearest sample to the left
		leftSample = phase >> 26;
		// extract the less significant bits as fractional phase
#define pwmPhaseFrac (phase & 0x3FFFFFF) >> 11
		// use this with the precalculated pwm to perform bilinear interpolation
		// this accomplishes the
		result = fix15_bilerp(pwmTable1[leftSample], pwmTable2[leftSample],
					pwmTable1[leftSample + 1], pwmTable2[leftSample + 1],
						pwmFrac, pwmPhaseFrac);
		// output of phase distortion is a 9.16 (tablesize.interpolationbits) fixed point number
		// scale to 12 bits for saw out
		buffer3[writeIndex] = (result) >> 13;
		// get the actual wavetable output sample as above
		// but with the appropriate scaling as phase is now 25 bits and table length is 9 bits
		leftSample = result >> 16;
#define phaseFrac (result & 0xFFFF)
//		buffer2[writeIndex] = fast_15_16_bilerp(wavetable1[leftSample], wavetable2[leftSample],
//										wavetable1[leftSample + 1], wavetable2[leftSample + 1],
//											morphFrac, phaseFrac);
		buffer2[writeIndex] = fast_15_16_bilerp_prediff(wavetable1[leftSample], wavetable1[leftSample + 1],
													morphFrac, phaseFrac);
		buffer1[writeIndex] = 4095 - buffer2[writeIndex];

		writeIndex++;
		samplesRemaining--;
	}

	GPIOA->BSRR = (uint32_t)GPIO_PIN_12 << (16 * (buffer1[0] - buffer1[BUFFER_SIZE] >> 31));

	static uint32_t lastHemisphere;
	uint32_t phaseHemisphere = (result >> 24);
	uint32_t transition = (phaseHemisphere ^ lastHemisphere);
	uint32_t atB = transition & (phaseHemisphere);
	uint32_t atA = transition & !atB;
	lastHemisphere = phaseHemisphere;

	GPIOC->BSRR = (uint32_t)GPIO_PIN_13 << (16 * phaseHemisphere);

	GPIOB->BSRR = ((uint32_t)GPIO_PIN_9 << (16 * phaseHemisphere)) | ((uint32_t)GPIO_PIN_8 << (16 * !phaseHemisphere));

	//EXPAND_LOGIC_LOW;



}

void renderBuffer1(viaSignals * signals) {

	//EXPAND_LOGIC_HIGH

	// get signal class pointers
	softwareSignaling * softwareSignals = signals->softwareSignals;
	controlRateInputs * controls = signals->controls;
	audioRateInputs * inputs = signals->inputs;
	audioRateOutputs * outputs = signals->outputs;

	// calculate buffer rate parameters
	uint32_t increment = (((controls->frequency) * (-(int)inputs->fm[0] + 16383)) >> 6) * inputs->reverseInput;

	uint32_t pwm = inputs->pwm[0] + 32768;
	uint32_t pwmIndex = (pwm >> 11);
	uint32_t pwmFrac = (pwm & 0x7FF) << 4;
	uint32_t * pwmTable1 = phaseModPWMTables[pwmIndex];
	uint32_t * pwmTable2 = phaseModPWMTables[pwmIndex + 1];

	// scale morph to table size in 16.16 fixed point
	uint32_t morph = __USAT(((controls->morph << 4) - (int)inputs->morphMod[0]), 16) * softwareSignals->morphMultiplier;
	uint32_t morphIndex = morph >> 16;
	uint32_t morphFrac = morph & 0xFFFF;
	q31_t * wavetable1 = fullTableHoldArray[morphIndex] + 2;
	//q31_t * wavetable2 = fullTableHoldArray[morphIndex + 1] + 2;

	static uint32_t lastPhaseMod;
	uint32_t phaseMod = inputs->pm[0];
	phase += (phaseMod - lastPhaseMod) << 12;
	lastPhaseMod = phaseMod;

	phase *= inputs->syncInput;
	inputs->syncInput = 1;
	phase *= inputs->syncInput;
	inputs->syncInput = 1;

	uint32_t * buffer1 = outputs->dac1Samples;
	uint32_t * buffer2 = outputs->dac2Samples;
	uint32_t * buffer3 = outputs->dac3Samples;

	uint32_t leftSample;
	uint32_t result;

	uint32_t writeIndex = BUFFER_SIZE;
	uint32_t samplesRemaining = BUFFER_SIZE;

	while (samplesRemaining) {
		// phase pointer wraps at 32 bits
		phase = (phase + increment);
		// treat the msb of phase as a 6.15 (tablesize.interpolationbits) fixed point number
		// divide by right shifting phase size (32 bits) less table size (6 bits) to find the nearest sample to the left
		leftSample = phase >> 26;
		// extract the less significant bits as fractional phase
#define pwmPhaseFrac (phase & 0x3FFFFFF) >> 11
		// use this with the precalculated pwm to perform bilinear interpolation
		// this accomplishes the
		result = fix15_bilerp(pwmTable1[leftSample], pwmTable2[leftSample],
					pwmTable1[leftSample + 1], pwmTable2[leftSample + 1],
						pwmFrac, pwmPhaseFrac);
		// output of phase distortion is a 9.16 (tablesize.interpolationbits) fixed point number
		// scale to 12 bits for saw out
		buffer3[writeIndex] = (result) >> 13;
		// get the actual wavetable output sample as above
		// but with the appropriate scaling as phase is now 25 bits and table length is 9 bits
		leftSample = result >> 16;
#define phaseFrac (result & 0xFFFF)
//		buffer2[writeIndex] = fast_15_16_bilerp(wavetable1[leftSample], wavetable2[leftSample],
//										wavetable1[leftSample + 1], wavetable2[leftSample + 1],
//											morphFrac, phaseFrac);
		buffer2[writeIndex] = fast_15_16_bilerp_prediff(wavetable1[leftSample], wavetable1[leftSample + 1],
													morphFrac, phaseFrac);
		buffer1[writeIndex] = 4095 - buffer2[writeIndex];

		writeIndex++;
		samplesRemaining--;
	}

	GPIOA->BSRR = (uint32_t)GPIO_PIN_12 << (16 * (buffer1[0] - buffer1[BUFFER_SIZE] >> 31));

	static uint32_t lastHemisphere;
	uint32_t phaseHemisphere = (result >> 24);
	uint32_t transition = (phaseHemisphere ^ lastHemisphere);
	uint32_t atB = transition & (phaseHemisphere);
	uint32_t atA = transition & !atB;
	lastHemisphere = phaseHemisphere;

	GPIOC->BSRR = (uint32_t)GPIO_PIN_13 << (16 * phaseHemisphere);

	GPIOB->BSRR = ((uint32_t)GPIO_PIN_9 << (16 * phaseHemisphere)) | ((uint32_t)GPIO_PIN_8 << (16 * !phaseHemisphere));



	//EXPAND_LOGIC_LOW;





}
