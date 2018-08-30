/*
 * meta_interrupt_handlers.c
 *
 *  Created on: Aug 29, 2018
 *      Author: willmitchell
 */

#include "meta.h"

const int phaseModPWMTables[33][65] = {phaseModPWM_0, phaseModPWM_1, phaseModPWM_2, phaseModPWM_3, phaseModPWM_4, phaseModPWM_5, phaseModPWM_6, phaseModPWM_7, phaseModPWM_8, phaseModPWM_9, phaseModPWM_10, phaseModPWM_11, phaseModPWM_12, phaseModPWM_13, phaseModPWM_14, phaseModPWM_15, phaseModPWM_16, phaseModPWM_17, phaseModPWM_18, phaseModPWM_19, phaseModPWM_20, phaseModPWM_21, phaseModPWM_22, phaseModPWM_23, phaseModPWM_24, phaseModPWM_25, phaseModPWM_26, phaseModPWM_27, phaseModPWM_28, phaseModPWM_29, phaseModPWM_30, phaseModPWM_31, phaseModPWM_32};

void meta_mainRisingEdgeCallback(meta_signal_set * signals) {

	signals->meta_parameters->triggerSignal = 0;

}

void meta_mainFallingEdgeCallback(meta_signal_set * signals) {

	// gate signal

}

void meta_auxRisingEdgeCallback(meta_signal_set * signals) {

	// freeze input

}
void meta_auxFallingEdgeCallback(meta_signal_set * signals) {
	// dead
}

void meta_buttonPressedCallback(meta_signal_set * signals) {

	// manual trigger

}
void meta_buttonReleasedCallback(meta_signal_set * signals) {

	// manual gate

}

void meta_ioProcessCallback(meta_signal_set * signals) {

	// no need

}

void meta_halfTransferCallback(meta_signal_set * signals) {


	simpleWavetableParameters * wavetable_parameters = signals->wavetable_parameters;
	metaControllerParameters * meta_parameters = signals->meta_parameters;
	audioRateInputs * inputs = signals->inputs;
	audioRateOutputs * outputs = signals->outputs;

	(*metaControllerGenerateIncrements)(meta_parameters, signals->inputs);
	metaControllerAdvancePhase(meta_parameters);
	wavetable_parameters->phase = meta_parameters->phase;
	outputs->dac2Samples[0] = simpleWavetableAdvance(wavetable_parameters, meta_wavetableRead);
	outputs->dac1Samples[0] = 4095 - outputs->dac2Samples[0];
	(*meta_calculateDac3)(signals, 0);
	(*meta_calculateLogicA)(signals, 0);
	(*meta_calculateSH)(signals, 0);


}

void meta_transferCompleteCallback(meta_signal_set * signals) {

	simpleWavetableParameters * wavetable_parameters = signals->wavetable_parameters;
	metaControllerParameters * meta_parameters = signals->meta_parameters;
	audioRateInputs * inputs = signals->inputs;
	audioRateOutputs * outputs = signals->outputs;

	(*metaControllerGenerateIncrements)(meta_parameters, signals->inputs);
	metaControllerAdvancePhase(meta_parameters);
	wavetable_parameters->phase = meta_parameters->phase;
	outputs->dac2Samples[1] = simpleWavetableAdvance(wavetable_parameters, meta_wavetableRead);
	outputs->dac1Samples[1] = 4095 - outputs->dac2Samples[1];
	(*meta_calculateDac3)(signals, 1);
	(*meta_calculateLogicA)(signals, 1);
	(*meta_calculateSH)(signals, 1);

}

void meta_slowConversionCallback(meta_signal_set * signals) {

	controlRateInputs * controls = signals->controls;

	via_updateControlRateInputs(controls);
	simpleWavetableParseControls(controls, signals->wavetable_parameters);
	(*metaControllerParseControls)(controls, signals->meta_parameters);

	int sample = signals->outputs->dac2Samples[0];
	int lastPhaseValue = signals->meta_parameters->phase;
	SET_RED_LED(sample * (lastPhaseValue >> 24));
	SET_BLUE_LED(sample * (!(lastPhaseValue >> 24)));
	SET_GREEN_LED(__USAT((signals->inputs->cv3Samples[0] + controls->knob3Value - 2048), 12) * sample >> 12);

}


