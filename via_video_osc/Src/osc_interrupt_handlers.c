#include "signals.h"
#include "user_interface.h"
#include "via_rev5_hardware_io.h"

#include "../inc/osc_fill_buffer.h"
#include "../inc/osc_main_states.h"
#include "../inc/osc_modes.h"

uint32_t transferComplete;

void mainRisingEdgeCallback(osc_signal_set * signals) {

	if (transferComplete) {
		renderBuffer1(signals);
		transferComplete = 0;
	}


}

void mainFallingEdgeCallback(osc_signal_set * signals) {

}

void auxRisingEdgeCallback(osc_signal_set * signals) {
	;
}
void auxFallingEdgeCallback(osc_signal_set * signals) {
	;
}

void buttonPressedCallback(osc_signal_set * signals) {
	;
}
void buttonReleasedCallback(osc_signal_set * signals) {
	;
}

void ioProcessCallback(osc_signal_set * signals) {
	audioRateOutputs * outputs = signals->outputs;
	//setLogicOutputsNoLEDs(outputs->logicAHandler, outputs->auxLogicHandler, outputs->shAHandler, outputs->shBHandler);
}

void halfTransferCallback(osc_signal_set * signals) {
	renderBuffer0(signals);
}

void transferCompleteCallback(osc_signal_set * signals) {
//	renderBuffer1(signals);
	DMA1_Channel5->CCR &= ~DMA_CCR_EN;
	DMA1_Channel5->CNDTR = 64;
	transferComplete = 1;
}

void slowConversionCallback(osc_signal_set * signals) {
	controlRateInputs * controls = signals->controls;
	parseControls(controls);
}
