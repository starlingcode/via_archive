#include "sync.h"

const int phaseModPWMTables[33][65] = {phaseModPWM_0, phaseModPWM_1, phaseModPWM_2, phaseModPWM_3, phaseModPWM_4, phaseModPWM_5, phaseModPWM_6, phaseModPWM_7, phaseModPWM_8, phaseModPWM_9, phaseModPWM_10, phaseModPWM_11, phaseModPWM_12, phaseModPWM_13, phaseModPWM_14, phaseModPWM_15, phaseModPWM_16, phaseModPWM_17, phaseModPWM_18, phaseModPWM_19, phaseModPWM_20, phaseModPWM_21, phaseModPWM_22, phaseModPWM_23, phaseModPWM_24, phaseModPWM_25, phaseModPWM_26, phaseModPWM_27, phaseModPWM_28, phaseModPWM_29, phaseModPWM_30, phaseModPWM_31, phaseModPWM_32};

void sync_mainRisingEdgeCallback(sync_signal_set * signals) {

	pllMultiplierParameters * pll_parameters = signals->pll_parameters;

	pllMultiplierMeasureFrequency(pll_parameters);
	pllMultiplierDoPLL(pll_parameters);
	pllMultiplierGenerateFrequency(pll_parameters);

	singleSampleWavetableParameters * wavetable_parameters = signals->wavetable_parameters;

	// should these be initialized to point to the same address?

	wavetable_parameters->increment = pll_parameters->increment;
	wavetable_parameters->phaseReset = pll_parameters->phaseReset;


}

void sync_mainFallingEdgeCallback(sync_signal_set * signals) {



}

void sync_auxRisingEdgeCallback(sync_signal_set * signals) {
	sync_handleButton2Tap();
}
void sync_auxFallingEdgeCallback(sync_signal_set * signals) {
	;
}

void sync_buttonPressedCallback(sync_signal_set * signals) {
	;
}
void sync_buttonReleasedCallback(sync_signal_set * signals) {
	;
}

void sync_ioProcessCallback(sync_signal_set * signals) {
}

void sync_halfTransferCallback(sync_signal_set * signals) {


	singleSampleWavetableParameters * parameters = signals->wavetable_parameters;
	audioRateOutputs * outputs = signals->outputs;

	outputs->dac2Samples[0] = __USAT(singleSampleWavetableAdvance(parameters,
			sync_wavetableRead, phaseModPWMTables), 12);
	outputs->dac1Samples[0] = 4095 - outputs->dac2Samples[0];
	outputs->dac3Samples[0] = parameters->ghostPhase >> 13;
//	uint32_t ghostPhase = parameters->ghostPhase >> 12;
//	if (ghostPhase >> 12) {
//		outputs->dac3Samples[0] = 8191 - ghostPhase;
//	} else {
//		outputs->dac3Samples[0] = ghostPhase;
//	}



}

void sync_transferCompleteCallback(sync_signal_set * signals) {


	singleSampleWavetableParameters * parameters = signals->wavetable_parameters;
	audioRateOutputs * outputs = signals->outputs;

	outputs->dac2Samples[1] = __USAT(singleSampleWavetableAdvance(parameters,
			sync_wavetableRead, phaseModPWMTables), 12);
	outputs->dac1Samples[1] = 4095 - outputs->dac2Samples[1];
	outputs->dac3Samples[1] = parameters->ghostPhase >> 13;
//	if (ghostPhase >> 12) {
//		outputs->dac3Samples[1] = 8191 - ghostPhase;
//	} else {
//		outputs->dac3Samples[1] = ghostPhase;
//	}




}

void sync_slowConversionCallback(sync_signal_set * signals) {

	controlRateInputs * controls = signals->controls;

	via_updateControlRateInputs(controls);
	singleSampleWavetableParseControls(controls, signals->wavetable_parameters);
	pllMultiplierParseControls(controls, signals->inputs, signals->pll_parameters);

	int sample = signals->outputs->dac1Samples[0];
	int lastPhaseValue = signals->wavetable_parameters->ghostPhase;
	SET_RED_LED(sample * (lastPhaseValue >> 24));
	SET_BLUE_LED(sample * (!(lastPhaseValue >> 24)));
	SET_GREEN_LED(__USAT((signals->inputs->cv3Samples[0] + controls->knob3Value - 2048), 12) * sample >> 12);

}

