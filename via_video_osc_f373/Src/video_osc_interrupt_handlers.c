#include <video_osc.h>

uint32_t transferComplete;

void video_osc_mainRisingEdgeCallback(video_osc_signal_set * signals) {

	if (transferComplete) {
		EXPAND_LOGIC_HIGH
		oversampledWavetableAdvance1(signals->parameters,
				signals->outputs, video_osc_wavetableRead, VIDEO_OSC_BUFFER_SIZE,
				VIDEO_OSC_BUFFER_SIZE);
		EXPAND_LOGIC_LOW
		transferComplete = 0;
	}
}

void video_osc_mainFallingEdgeCallback(video_osc_signal_set * signals) {

}

void video_osc_auxRisingEdgeCallback(video_osc_signal_set * signals) {
	video_osc_handleButton2Tap();
}
void video_osc_auxFallingEdgeCallback(video_osc_signal_set * signals) {
	;
}

void video_osc_buttonPressedCallback(video_osc_signal_set * signals) {
	;
}
void video_osc_buttonReleasedCallback(video_osc_signal_set * signals) {
	;
}

void video_osc_ioProcessCallback(video_osc_signal_set * signals) {
}

void video_osc_halfTransferCallback(video_osc_signal_set * signals) {

	EXPAND_LOGIC_HIGH

	oversampledWavetableParameters * parameters = signals->parameters;
	audioRateOutputs * outputs = signals->outputs;

	//via_setLogicOut(outputs, 0, runtimeDisplay);
	oversampledWavetableAdvance0(parameters, outputs,
			video_osc_wavetableRead, 0, VIDEO_OSC_BUFFER_SIZE);
	//oversampledWavetableParsePhase(lastPhase, parameters, outputs);

	EXPAND_LOGIC_LOW

}

void video_osc_transferCompleteCallback(video_osc_signal_set * signals) {

	DMA1_Channel5->CCR &= ~DMA_CCR_EN;
	DMA1_Channel5->CNDTR = 64;
	transferComplete = 1;

	//EXPAND_LOGIC_HIGH

//	oversampledWavetableParameters * parameters = signals->parameters;
//	audioRateOutputs * outputs = signals->outputs;

	//via_setLogicOut(outputs, 0, runtimeDisplay);
//	uint32_t lastPhase = oversampledWavetableAdvance1(parameters, outputs,
//			video_osc_wavetableRead, VIDEO_OSC_BUFFER_SIZE,
//			VIDEO_OSC_BUFFER_SIZE);
	//oversampledWavetableParsePhase(lastPhase, parameters, outputs);

	//EXPAND_LOGIC_LOW


}

void video_osc_slowConversionCallback(video_osc_signal_set * signals) {

	oversampledWavetableParameters * parameters = signals->parameters;
	controlRateInputs * controls = signals->controls;

	via_updateControlRateInputs(controls);
	oversampledWavetableParseControls(controls, parameters);

	// set LED display
	uint32_t displayFreq = __USAT(parameters->frequencyBase1 >> 6, 12);
	uint32_t blueLevel = displayFreq;
	uint32_t greenLevel = controls->linTouchValue >> 1;
	uint32_t redLevel = 4095 - controls->linTouchValue;
	updateRGBDisplay(redLevel, greenLevel, blueLevel);

}

