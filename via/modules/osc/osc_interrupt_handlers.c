
#include "osc.h"

void osc_mainRisingEdgeCallback(osc_signals * signals) {

	oversampledWavetableParameters * parameters = signals->parameters;

	if (parameters->syncMode == hard) {
		// this is reset to 1 at every with every new sample aquisition
		parameters->syncInput = 0;
	} else {
		// toggle increment direction on rising and falling edges
		parameters->reverseInput *= -1;
	}

}

void osc_mainFallingEdgeCallback(osc_signals * signals) {

}

void osc_auxRisingEdgeCallback(osc_signals * signals) {
	osc_handleButton2Tap();
}
void osc_auxFallingEdgeCallback(osc_signals * signals) {
	;
}

void osc_buttonPressedCallback(osc_signals * signals) {
	;
}
void osc_buttonReleasedCallback(osc_signals * signals) {
	;
}

void osc_ioProcessCallback(osc_signals * signals) {
}

void osc_halfTransferCallback(osc_signals * signals) {

	EXPAND_LOGIC_HIGH

	oversampledWavetableParameters * parameters = signals->parameters;
	audioRateOutputs * outputs = signals->outputs;

	uint32_t lastPhase = oversampledWavetableAdvance(parameters, outputs, osc_wavetableRead, osc_phaseDistRead, 0, OSC_BUFFER_SIZE);
	oversampledWavetableParsePhase(lastPhase, parameters, outputs);

	EXPAND_LOGIC_LOW;

}

void osc_transferCompleteCallback(osc_signals * signals) {

	EXPAND_LOGIC_HIGH

	oversampledWavetableParameters * parameters = signals->parameters;
	audioRateOutputs * outputs = signals->outputs;

	uint32_t lastPhase = oversampledWavetableAdvance(parameters, outputs, osc_wavetableRead, osc_phaseDistRead, OSC_BUFFER_SIZE, OSC_BUFFER_SIZE);
	oversampledWavetableParsePhase(lastPhase, parameters, outputs);

	EXPAND_LOGIC_LOW;

}

void osc_slowConversionCallback(osc_signals * signals) {

	oversampledWavetableParameters * parameters = signals->parameters;
	controlRateInputs * controls = signals->controls;

	via_updateControlRateInputs(controls);
	oversampledWavetableParseControls(controls, parameters);

	// set LED display
	uint32_t displayFreq = __USAT(abs((((parameters->frequencyBase) * (-(int)parameters->fm[0] + 16383)) >> 4)) >> 10, 12);
	uint32_t redLevel = 4095 - displayFreq;
	uint32_t blueLevel = displayFreq;
	uint32_t greenLevel = __USAT(((parameters->morphBase << 4) - (int)parameters->morphMod[0]), 16) >> 6;
	updateRGBDisplay(redLevel, greenLevel, blueLevel);

}

