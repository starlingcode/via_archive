#include "signals.h"
#include "user_interface.h"
#include "via_rev5_hardware_io.h"

#include "../inc/osc_fill_buffer.h"
#include "../inc/osc_main_states.h"
#include "../inc/osc_modes.h"

uint32_t transferComplete;

void mainRisingEdgeCallback(viaSignals * signals) {

	if (transferComplete) {
		renderBuffer1(signals);
		transferComplete = 0;
	}


}

void mainFallingEdgeCallback(viaSignals * signals) {

}

void auxRisingEdgeCallback(viaSignals * signals) {
	;
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
//	renderBuffer1(signals);
	DMA1_Channel5->CCR &= ~DMA_CCR_EN;
	DMA1_Channel5->CNDTR = 64;
	transferComplete = 1;
}

void slowConversionCallback(viaSignals * signals) {
	controlRateInputs * controls = signals->controls;
	calculateControls(controls);
}
