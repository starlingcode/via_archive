#include "osc.h"

void osc_mainRisingEdgeCallback(osc_signal_set * signals) {

	oversampledWavetableParameters * parameters = signals->parameters;

	if (parameters->syncMode == hard) {
		// this is reset to 1 at every with every new sample aquisition
		parameters->syncInput = 0;
	} else {
		// toggle increment direction on rising and falling edges
		parameters->reverseInput *= -1;
	}

}

void osc_mainFallingEdgeCallback(osc_signal_set * signals) {

}

void osc_auxRisingEdgeCallback(osc_signal_set * signals) {
	osc_handleButton2Tap();
}
void osc_auxFallingEdgeCallback(osc_signal_set * signals) {
	;
}

void osc_buttonPressedCallback(osc_signal_set * signals) {
	;
}
void osc_buttonReleasedCallback(osc_signal_set * signals) {
	;
}

void osc_ioProcessCallback(osc_signal_set * signals) {
}

void osc_halfTransferCallback(osc_signal_set * signals) {

	EXPAND_LOGIC_HIGH

	oversampledWavetableParameters * parameters = signals->parameters;
	audioRateOutputs * outputs = signals->outputs;

	uint32_t lastPhase = oversampledWavetableAdvance(parameters, outputs,
			osc_wavetableRead, osc_phaseDistRead, 0, OSC_BUFFER_SIZE);
	oversampledWavetableParsePhase(lastPhase, parameters, outputs);

	EXPAND_LOGIC_LOW
	;

}

void osc_transferCompleteCallback(osc_signal_set * signals) {

	EXPAND_LOGIC_HIGH

	oversampledWavetableParameters * parameters = signals->parameters;
	audioRateOutputs * outputs = signals->outputs;

	uint32_t lastPhase = oversampledWavetableAdvance(parameters, outputs,
			osc_wavetableRead, osc_phaseDistRead, OSC_BUFFER_SIZE,
			OSC_BUFFER_SIZE);
	oversampledWavetableParsePhase(lastPhase, parameters, outputs);

	EXPAND_LOGIC_LOW
	;

}

void osc_slowConversionCallback(osc_signal_set * signals) {

	oversampledWavetableParameters * parameters = signals->parameters;
	controlRateInputs * controls = signals->controls;

	via_updateControlRateInputs(controls);
	oversampledWavetableParseControls(controls, parameters);

	// set LED display
	uint32_t displayFreq = __USAT(parameters->frequencyBase >> 10, 12);
	uint32_t blueLevel = displayFreq;
	uint32_t greenLevel = controls->linTouchValue >> 1;
	uint32_t redLevel = 4095 - controls->linTouchValue;
	updateRGBDisplay(redLevel, greenLevel, blueLevel);

}

