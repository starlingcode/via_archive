
#include "signals.h"
#include "via_rev5_hardware_io.h"
#include "../inc/osc_fill_buffer.h"
#include "../inc/osc_main_states.h"
#include "../inc/osc_modes.h"
#include "../inc/osc_tables.h"

extern int handleConversionSlow(controlRateInputs * controls, audioRateInputs * inputs, uint32_t sequencingSignal);

void fillBuffer(viaSignals * signals) {

	q31_t increment;
	q31_t phaseMod;
	q31_t morph;
	q31_t pwm;
	int phaseEvent;

	// eventually,
	// static struct viaStateInfoHolder viaStateInfo;

	audioRateInputs * inputs = signals->inputs;
	audioRateOutputs * outputs = signals->outputs;
	softwareSignaling * softwareSignals = signals->softwareSignals;
	controlRateInputs * controls = signals->controls;


	(*prepareCV)(inputs, &controlRateInput, increment, phaseMod, morph, pwmBuffer);

	incrementOscillator(incrementBuffer, phaseModBuffer, morphBuffer, pwmBuffer, inputs->hardSyncInput, inputs->reverseInput, outputs);

	(*logicAndFilter)(phaseEvents, outputs);

	slowConversionCounter = handleConversionSlow(controls, inputs, slowConversionCounter);
}

