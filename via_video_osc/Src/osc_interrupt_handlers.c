#include "signals.h"
#include "user_interface.h"
#include "via_rev5_hardware_io.h"

#include "../inc/osc_fill_buffer.h"
#include "../inc/osc_main_states.h"
#include "../inc/osc_modes.h"

uint32_t transferComplete;

void mainRisingEdgeCallback(osc_signals * signals) {

	if (transferComplete) {
		renderBuffer1(signals);
		transferComplete = 0;
	}


}

void mainFallingEdgeCallback(osc_signals * signals) {

}

void auxRisingEdgeCallback(osc_signals * signals) {
	;
}
void auxFallingEdgeCallback(osc_signals * signals) {
	;
}

void buttonPressedCallback(osc_signals * signals) {
	;
}
void buttonReleasedCallback(osc_signals * signals) {
	;
}

void ioProcessCallback(osc_signals * signals) {
	audioRateOutputs * outputs = signals->outputs;
	//setLogicOutputsNoLEDs(outputs->logicAHandler, outputs->auxLogicHandler, outputs->shAHandler, outputs->shBHandler);
}

void halfTransferCallback(osc_signals * signals) {
	renderBuffer0(signals);
}

void transferCompleteCallback(osc_signals * signals) {
//	renderBuffer1(signals);
	DMA1_Channel5->CCR &= ~DMA_CCR_EN;
	DMA1_Channel5->CNDTR = 64;
	transferComplete = 1;
}

void slowConversionCallback(osc_signals * signals) {
	controlRateInputs * controls = signals->controls;
	parseControls(controls);
}
