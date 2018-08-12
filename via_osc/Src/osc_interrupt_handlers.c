#include "signals.h"
#include "user_interface.h"
#include "via_rev5_hardware_io.h"

#include "../inc/osc_fill_buffer.h"
#include "../inc/osc_main_states.h"
#include "../inc/osc_modes.h"

void mainRisingEdgeCallback(viaSignals * signals) {

	audioRateInputs * inputs = signals->inputs;

	if (signals->softwareSignals->syncMode == hard) {
		// this is reset to 1 at every with every new sample aquisition
		ALOGIC_HIGH;
		inputs->mainLogicInput = 0;
	} else {
		// toggle increment direction on rising and falling edges
		inputs->mainLogicInput *= -1;
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

	setLogicOutputsNoLEDs(outputs->logicAHandler, outputs->auxLogicHandler, outputs->shAHandler, outputs->shBHandler);

}
void nextSampleCallback(viaSignals * signals) {



	// handled with fillBuffer

}
