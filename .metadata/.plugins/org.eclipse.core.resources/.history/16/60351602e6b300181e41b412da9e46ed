
#include "signals.h"
#include "via_rev5_hardware_io.h"
#include "../inc/osc_fill_buffer.h"
#include "../inc/osc_main_states.h"
#include "../inc/osc_modes.h"
#include "../inc/osc_tables.h"
#include "osc_pwm_tables.h"

// expo scaling for 1voct
const uint32_t expoTable[4096] = expotable10oct;
q31_t phaseModPWMTables[33][65] = {phaseModPWM_0, phaseModPWM_1, phaseModPWM_2, phaseModPWM_3, phaseModPWM_4, phaseModPWM_5, phaseModPWM_6, phaseModPWM_7, phaseModPWM_8, phaseModPWM_9, phaseModPWM_10, phaseModPWM_11, phaseModPWM_12, phaseModPWM_13, phaseModPWM_14, phaseModPWM_15, phaseModPWM_16, phaseModPWM_17, phaseModPWM_18, phaseModPWM_19, phaseModPWM_20, phaseModPWM_21, phaseModPWM_22, phaseModPWM_23, phaseModPWM_24, phaseModPWM_25, phaseModPWM_26, phaseModPWM_27, phaseModPWM_28, phaseModPWM_29, phaseModPWM_30, phaseModPWM_31, phaseModPWM_32};


void writeBuffer(buffer* buffer, int value) {
	buffer->buff[(buffer->writeIndex++) & 31] = value;
}

int readBuffer(buffer* buffer, int Xn) {
	return buffer->buff[(buffer->writeIndex + (~Xn)) & 31];
}


void calculateControls(controlRateInputs * controls) {

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

//	GPIOC->BRR = (uint32_t)GPIO_PIN_13;

	// get signal class pointers
	softwareSignaling * softwareSignals = signals->softwareSignals;
	controlRateInputs * controls = signals->controls;
	audioRateInputs * inputs = signals->inputs;
	audioRateOutputs * outputs = signals->outputs;

	// calculate buffer rate parameters
	uint32_t increment = (((controls->frequency) * ((int)inputs->fm[0] + 16383)) >> 4) * inputs->reverseInput;

	uint32_t pwm = (inputs->pwm[0] >> 4) + 2048;
	uint32_t pwmIndex = (pwm >> 7);
	uint32_t pwmFrac = (pwm & 0b00000000000000001111111) << 8;
	uint32_t * pwmTable1 = phaseModPWMTables[pwmIndex];
	uint32_t * pwmTable2 = phaseModPWMTables[pwmIndex + 1];

	// scale morph to table size in 16.16 fixed point
	uint32_t morph = __USAT(((controls->morph << 4) - inputs->morphMod[0]), 16) << 2;
	uint32_t morphIndex = morph >> 16;
	uint32_t morphFrac = morph & 0xFFFF;
	q31_t * wavetable1 = fullTableHoldArray[morphIndex];
	q31_t * wavetable2 = fullTableHoldArray[morphIndex + 1];

	uint32_t * buffer1 = outputs->dac1Samples;
	uint32_t * buffer2 = outputs->dac2Samples;
	uint32_t * buffer3 = outputs->dac3Samples;

	phase = ((int) inputs->pm[0]) << 16;

// only calculated once per sample so no need to store but ugly to inline
#define pwmPhaseFrac (phase & 0x3FFFFFF) >> 11
#define phaseFrac (result & 0xFFFF)

	uint32_t leftSample;
	uint32_t result;

	for (int i = 0; i < BUFFER_SIZE; i++) {
		// phase pointer wraps at 32 bits
		phase = (phase + increment);
		result = phase >> 7;
		leftSample = result >> 16;
#define phaseFrac (result & 0xFFFF)
		result = fast_15_16_bilerp(wavetable1[leftSample], wavetable2[leftSample],
					wavetable1[leftSample + 1], wavetable2[leftSample + 1],
						morphFrac, phaseFrac);
		buffer3[i] = (result >> 1) + 2048;
	}


//	GPIOC->BSRR = (uint32_t)GPIO_PIN_13;


}

void renderBuffer1(viaSignals * signals) {

//	GPIOC->BRR = (uint32_t)GPIO_PIN_13;

	// get signal class pointers
	softwareSignaling * softwareSignals = signals->softwareSignals;
	controlRateInputs * controls = signals->controls;
	audioRateInputs * inputs = signals->inputs;
	audioRateOutputs * outputs = signals->outputs;

	// calculate buffer rate parameters
	uint32_t increment = (((controls->frequency) * ((int)inputs->fm[0] + 16383)) >> 4) * inputs->reverseInput;

	// scale morph to table size in 16.16 fixed point
	uint32_t morph = __USAT(((controls->morph << 4) - inputs->morphMod[0]), 16) << 2;
	uint32_t morphIndex = morph >> 16;
	uint32_t morphFrac = morph & 0xFFFF;
	q31_t * wavetable1 = fullTableHoldArray[morphIndex];
	q31_t * wavetable2 = fullTableHoldArray[morphIndex + 1];

	uint32_t * buffer1 = outputs->dac1Samples;
	uint32_t * buffer2 = outputs->dac2Samples;
	uint32_t * buffer3 = outputs->dac3Samples;

#define pwmPhaseFrac (phase & 0x3FFFFFF) >> 11
#define phaseFrac (result & 0xFFFF)

	uint32_t leftSample;
	uint32_t result;

	for (int i = BUFFER_SIZE; i < BUFFER_SIZE*2; i++) {
		// phase pointer wraps at 32 bits
		phase = (phase + increment);
		result = phase >> 7;
		leftSample = result >> 16;
#define phaseFrac (result & 0xFFFF)
		result = fast_15_16_bilerp(wavetable1[leftSample], wavetable2[leftSample],
					wavetable1[leftSample + 1], wavetable2[leftSample + 1],
						morphFrac, phaseFrac);
		// write crossfader attenuation values
//		buffer1[i] = 4095 - result;
		buffer3[i] = (result >> 1) + 2048;
	}
//	GPIOC->BSRR = (uint32_t)GPIO_PIN_13;

}
