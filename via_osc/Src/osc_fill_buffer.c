
#include "signals.h"
#include "via_rev5_hardware_io.h"
#include "../inc/osc_fill_buffer.h"
#include "../inc/osc_main_states.h"
#include "../inc/osc_modes.h"
#include "../inc/osc_tables.h"

extern int handleCoversionSlow(controlRateInputs * controls, audioRateInputs * inputs, uint32_t sequencingSignal);

void fillBuffer(viaSignals * signals) {

	q31_t incrementBuffer[BUFFER_SIZE];
	q31_t phaseModBuffer[BUFFER_SIZE];
	q31_t morphBuffer[BUFFER_SIZE];
	q31_t pwmBuffer[BUFFER_SIZE];
	int phaseEvents[BUFFER_SIZE];
	static uint32_t slowConversionCounter;

	// eventually,
	// static struct viaStateInfoHolder viaStateInfo;

	audioRateInputs * inputRead = signals->inputRead;
	audioRateOutputs * outputWrite = signals->outputWrite;
	softwareSignaling * softwareSignals = signals->softwareSignals;
	controlRateInputs * controls = signals->controls;


	(*prepareCV)(inputRead, &controlRateInput, incrementBuffer, phaseModBuffer, morphBuffer, pwmBuffer);

	incrementOscillator(incrementBuffer, phaseModBuffer, morphBuffer, pwmBuffer, inputRead->hardSyncInput, inputRead->reverseInput, outputWrite->samples, phaseEvents, outputWrite->dac3Samples);

	(*logicAndFilter)(phaseEvents, outputWrite);

	calculateDac3Samples(outputWrite->dac3Samples, phaseModBuffer, incrementBuffer);

	slowConversionCounter = handleCoversionSlow(controls, inputRead, slowConversionCounter);

	main_state = main_idle;

}

