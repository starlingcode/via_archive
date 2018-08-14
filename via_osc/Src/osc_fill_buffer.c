
#include "signals.h"
#include "via_rev5_hardware_io.h"
#include "../inc/osc_fill_buffer.h"
#include "../inc/osc_main_states.h"
#include "../inc/osc_modes.h"
#include "../inc/osc_tables.h"

extern int handleConversionSlow(controlRateInputs * controls, audioRateInputs * inputs, uint32_t sequencingSignal);

//void fillBuffer(viaSignals * signals) {
//
//	q31_t increment;
//	q31_t phaseMod;
//	q31_t morph;
//	q31_t pwm;
//	int phaseEvent;
//
//	// eventually,
//	// static struct viaStateInfoHolder viaStateInfo;
//
//	audioRateInputs * inputs = signals->inputs;
//	audioRateOutputs * outputs = signals->outputs;
//	softwareSignaling * softwareSignals = signals->softwareSignals;
//	controlRateInputs * controls = signals->controls;
//
//
//	(*prepareCV)(inputs, &controlRateInput, increment, phaseMod, morph, pwmBuffer);
//
//	incrementOscillator(incrementBuffer, phaseModBuffer, morphBuffer, pwmBuffer, inputs->hardSyncInput, inputs->reverseInput, outputs);
//
//	(*logicAndFilter)(phaseEvents, outputs);
//
//	slowConversionCounter = handleConversionSlow(controls, inputs, slowConversionCounter);
//}

void renderBuffer0(viaSignals * signals) {

	GPIOC->BRR = (uint32_t)GPIO_PIN_13;

	uint32_t increment = (((controls->timeBase1) * (cv2[0])));
	uint32_t pwm = controls->timeBase2;
	//uint32_t pwm = 2000;
	uint32_t pwmIndex = (pwm >> 7);
	uint32_t pwmFrac = (pwm & 0b00000000000000001111111) << 8;
	uint32_t * pwmTable1 = phaseModPWMTables[pwmIndex];
	uint32_t * pwmTable2 = phaseModPWMTables[pwmIndex + 1];
	uint32_t morph = controls->morphBase;
	uint32_t * buffer1 = dacBuffer1;
	uint32_t * buffer2 = dacBuffer2;
	uint32_t * buffer3 = dacBuffer3;


#define pwmPhaseFrac (phase & 0x3FFFFFF) >> 11
#define phaseFrac (result & 0xFFFF)

	uint32_t leftSample;
	uint32_t result;


	for (int i = 0; i < 8; i++) {

		// wraps at full scale uint32_t
		phase = (phase + increment);
		leftSample = phase >> 26;
		result = fix15_bilerp(pwmTable1[leftSample], pwmTable2[leftSample],
					pwmTable1[leftSample + 1], pwmTable2[leftSample + 1],
						pwmFrac, pwmPhaseFrac);
		buffer3[i] = result >> 13;
		leftSample = result >> 16;
		result = fast_15_16_bilerp(wavetable1[leftSample], wavetable2[leftSample],
					wavetable1[leftSample + 1], wavetable2[leftSample + 1],
						morph, phaseFrac);
		buffer1[i] = 4095 - result;
		buffer2[i] = result;
	}


	GPIOC->BSRR = (uint32_t)GPIO_PIN_13;


}

void renderBuffer1(controlRateInputs * controls) {

#define pwmPhaseFrac (phase & 0x3FFFFFF) >> 11
#define phaseFrac (result & 0xFFFF)

	GPIOC->BRR = (uint32_t)GPIO_PIN_13;

	uint32_t increment = (((controls->timeBase1) * (cv2[0])));
	int morph = controls->morphBase;
	uint32_t pwm = controls->timeBase2;
	uint32_t pwmIndex = (pwm >> 7);
	uint32_t pwmFrac = (pwm & 0b00000000000000001111111) << 8;
	uint32_t * pwmTable1 = phaseModPWMTables[pwmIndex];
	uint32_t * pwmTable2 = phaseModPWMTables[pwmIndex + 1];
	uint32_t * buffer1 = dacBuffer1;
	uint32_t * buffer2 = dacBuffer2;
	uint32_t * buffer3 = dacBuffer3;

	for (int i = 8; i < 16; i++) {

		uint32_t leftSample;
		uint32_t result;

		// wraps at full scale uint32_t
		phase = (phase + increment);
		leftSample = phase >> 26;
		result = fix15_bilerp(pwmTable1[leftSample], pwmTable2[leftSample],
					pwmTable1[leftSample + 1], pwmTable2[leftSample + 1],
						pwmFrac, pwmPhaseFrac);
		buffer3[i] = result >> 13;
		leftSample = result >> 16;
		result = fast_15_16_bilerp(wavetable1[leftSample], wavetable2[leftSample],
					wavetable1[leftSample + 1], wavetable2[leftSample + 1],
						morph, phaseFrac);
		buffer1[i] = 4095 - result;
		buffer2[i] = result;

	}
	GPIOC->BSRR = (uint32_t)GPIO_PIN_13;

}
