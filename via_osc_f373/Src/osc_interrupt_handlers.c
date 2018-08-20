#include "signals.h"
#include "user_interface.h"
#include "via_io_binding.h"
#include "osc_modes.h"
#include "osc_tables.h"
#include "oscillators.h"

uint32_t phaseDistRead[33][65] = {phaseDistPWM_0, phaseDistPWM_1, phaseDistPWM_2, phaseDistPWM_3, phaseDistPWM_4, phaseDistPWM_5, phaseDistPWM_6, phaseDistPWM_7, phaseDistPWM_8, phaseDistPWM_9, phaseDistPWM_10, phaseDistPWM_11, phaseDistPWM_12, phaseDistPWM_13, phaseDistPWM_14, phaseDistPWM_15, phaseDistPWM_16, phaseDistPWM_17, phaseDistPWM_18, phaseDistPWM_19, phaseDistPWM_20, phaseDistPWM_21, phaseDistPWM_22, phaseDistPWM_23, phaseDistPWM_24, phaseDistPWM_25, phaseDistPWM_26, phaseDistPWM_27, phaseDistPWM_28, phaseDistPWM_29, phaseDistPWM_30, phaseDistPWM_31, phaseDistPWM_32};

void mainRisingEdgeCallback(viaSignals * signals) {

	oversampledWavetableParameters * parameters = signals->parameters;

	if (parameters->syncMode == hard) {
		// this is reset to 1 at every with every new sample aquisition
		parameters->syncInput = 0;
	} else {
		// toggle increment direction on rising and falling edges
		parameters->reverseInput *= -1;
	}

}

void mainFallingEdgeCallback(viaSignals * signals) {

}

void auxRisingEdgeCallback(viaSignals * signals) {
	handleButton2Tap();
}
void auxFallingEdgeCallback(viaSignals * signals) {
	;
}

void buttonPressedCallback(viaSignals * signals) {
	;
}
void buttonReleasedCallback(viaSignals * signals) {
	;
}

void ioProcessCallback(viaSignals * signals) {
}

void halfTransferCallback(viaSignals * signals) {

	EXPAND_LOGIC_HIGH

	oversampledWavetableParameters * parameters = signals->parameters;
	audioRateOutputs * outputs = signals->outputs;

	uint32_t lastPhase = oversampledWavetableAdvance(parameters, outputs, wavetableRead, phaseDistRead, 0, OSC_BUFFER_SIZE);
	oversampledWavetableParsePhase(lastPhase, parameters, outputs);

	EXPAND_LOGIC_LOW;

}

void transferCompleteCallback(viaSignals * signals) {

	EXPAND_LOGIC_HIGH

	oversampledWavetableParameters * parameters = signals->parameters;
	audioRateOutputs * outputs = signals->outputs;

	uint32_t lastPhase = oversampledWavetableAdvance(parameters, outputs, wavetableRead, phaseDistRead, OSC_BUFFER_SIZE, OSC_BUFFER_SIZE);
	oversampledWavetableParsePhase(lastPhase, parameters, outputs);

	EXPAND_LOGIC_LOW;

}

void slowConversionCallback(viaSignals * signals) {

	oversampledWavetableParameters * parameters = signals->parameters;
	controlRateInputs * controls = signals->controls;

	updateControlRateInputs(controls);
	oversampledWavetableParseControls(controls, parameters);
	uint32_t displayFreq = __USAT(abs((((parameters->frequencyBase) * (-(int)parameters->fm[0] + 16383)) >> 4)) >> 10, 12);
	uint32_t redLevel = 4095 - displayFreq;
	uint32_t blueLevel = displayFreq;
	uint32_t greenLevel = __USAT(((parameters->morphBase << 4) - (int)parameters->morphMod[0]), 16) >> 6;
	updateRGBDisplay(redLevel, greenLevel, blueLevel);

}

