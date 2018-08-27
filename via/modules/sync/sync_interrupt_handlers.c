#include "sync.h"

const int phaseModPWMTables[33][65] = {phaseModPWM_0, phaseModPWM_1, phaseModPWM_2, phaseModPWM_3, phaseModPWM_4, phaseModPWM_5, phaseModPWM_6, phaseModPWM_7, phaseModPWM_8, phaseModPWM_9, phaseModPWM_10, phaseModPWM_11, phaseModPWM_12, phaseModPWM_13, phaseModPWM_14, phaseModPWM_15, phaseModPWM_16, phaseModPWM_17, phaseModPWM_18, phaseModPWM_19, phaseModPWM_20, phaseModPWM_21, phaseModPWM_22, phaseModPWM_23, phaseModPWM_24, phaseModPWM_25, phaseModPWM_26, phaseModPWM_27, phaseModPWM_28, phaseModPWM_29, phaseModPWM_30, phaseModPWM_31, phaseModPWM_32};


// needs to be reworked to actually be the sync module

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

	EXPAND_LOGIC_HIGH

	singleSampleWavetableParameters * parameters = signals->wavetable_parameters;
	audioRateOutputs * outputs = signals->outputs;

	outputs->dac3Samples[0] = __USAT(singleSampleWavetableAdvance(parameters,
			sync_wavetableRead, phaseModPWMTables), 12);

	EXPAND_LOGIC_LOW
	;

}

void sync_transferCompleteCallback(sync_signal_set * signals) {

	EXPAND_LOGIC_HIGH

	singleSampleWavetableParameters * parameters = signals->wavetable_parameters;
	audioRateOutputs * outputs = signals->outputs;

	outputs->dac3Samples[1] = __USAT(singleSampleWavetableAdvance(parameters,
			sync_wavetableRead, phaseModPWMTables), 12);

	EXPAND_LOGIC_LOW
	;

}

void sync_slowConversionCallback(sync_signal_set * signals) {

	controlRateInputs * controls = signals->controls;

	via_updateControlRateInputs(controls);
	singleSampleWavetableParseControls(controls, signals->wavetable_parameters);
	pllMultiplierParseControls(controls, signals->inputs, signals->pll_parameters);

//	// set LED display
//	uint32_t displayFreq = __USAT(
//			abs(
//					(((parameters->frequencyBase)
//							* (-(int )parameters->fm[0] + 16383)) >> 4)) >> 10,
//			12);
//	uint32_t redLevel = 4095 - displayFreq;
//	uint32_t blueLevel = displayFreq;
//	uint32_t greenLevel =
//			__USAT(
//					((parameters->morphBase << 4)
//							- (int )parameters->morphMod[0]), 16)
//					>> 6;
//	updateRGBDisplay(redLevel, greenLevel, blueLevel);

}

