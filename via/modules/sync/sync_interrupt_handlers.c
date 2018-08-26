#include "sync.h"

// needs to be reworked to actually be the sync module

void sync_mainRisingEdgeCallback(sync_signal_set * signals) {

	oversampledWavetableParameters * parameters = signals->parameters;

	if (parameters->syncMode == hard) {
		// this is reset to 1 at every with every new sample aquisition
		parameters->syncInput = 0;
	} else {
		// toggle increment direction on rising and falling edges
		parameters->reverseInput *= -1;
	}

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

	oversampledWavetableParameters * parameters = signals->parameters;
	audioRateOutputs * outputs = signals->outputs;

	uint32_t lastPhase = oversampledWavetableAdvance(parameters, outputs,
			sync_wavetableRead, sync_phaseDistRead, 0, SYNC_BUFFER_SIZE);
	oversampledWavetableParsePhase(lastPhase, parameters, outputs);

	EXPAND_LOGIC_LOW
	;

}

void sync_transferCompleteCallback(sync_signal_set * signals) {

	EXPAND_LOGIC_HIGH

	oversampledWavetableParameters * parameters = signals->parameters;
	audioRateOutputs * outputs = signals->outputs;

	uint32_t lastPhase = oversampledWavetableAdvance(parameters, outputs,
			sync_wavetableRead, sync_phaseDistRead, SYNC_BUFFER_SIZE,
			SYNC_BUFFER_SIZE);
	oversampledWavetableParsePhase(lastPhase, parameters, outputs);

	EXPAND_LOGIC_LOW
	;

}

void sync_slowConversionCallback(sync_signal_set * signals) {

	oversampledWavetableParameters * parameters = signals->parameters;
	controlRateInputs * controls = signals->controls;

	via_updateControlRateInputs(controls);
	oversampledWavetableParseControls(controls, parameters);

	// set LED display
	uint32_t displayFreq = __USAT(
			abs(
					(((parameters->frequencyBase)
							* (-(int )parameters->fm[0] + 16383)) >> 4)) >> 10,
			12);
	uint32_t redLevel = 4095 - displayFreq;
	uint32_t blueLevel = displayFreq;
	uint32_t greenLevel =
			__USAT(
					((parameters->morphBase << 4)
							- (int )parameters->morphMod[0]), 16)
					>> 6;
	updateRGBDisplay(redLevel, greenLevel, blueLevel);

}

