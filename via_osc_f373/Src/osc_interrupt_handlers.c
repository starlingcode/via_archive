#include "signals.h"
#include "user_interface.h"
#include "via_io_binding.h"

#include "../inc/osc_fill_buffer.h"
#include "../inc/osc_main_states.h"
#include "../inc/osc_modes.h"

void mainRisingEdgeCallback(viaSignals * signals) {

	softwareSignaling * softwareSignals = signals->softwareSignals;

	if (softwareSignals->syncMode == hard) {
		// this is reset to 1 at every with every new sample aquisition
		ALOGIC_HIGH;
		softwareSignals->syncInput = 0;
	} else {
		// toggle increment direction on rising and falling edges
		softwareSignals->reverseInput *= -1;
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
	audioRateOutputs * outputs = signals->outputs;
	//setLogicOutputsNoLEDs(outputs->logicAHandler, outputs->auxLogicHandler, outputs->shAHandler, outputs->shBHandler);
}

void halfTransferCallback(viaSignals * signals) {
	renderBuffer0(signals);
}

void transferCompleteCallback(viaSignals * signals) {
	renderBuffer1(signals);
}

void slowConversionCallback(viaSignals * signals) {
	updateControlRateInputs(signals->controls);
	parseControls(signals);
}
