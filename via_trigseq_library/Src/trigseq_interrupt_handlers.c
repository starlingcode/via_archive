#include "dsp.h"
#include "main.h"
#include "user_interface.h"
#include "via_rev5_hardware_io.h"
#include "trigseq_modes.h"
#include "trigseq_interrupt_handlers.h"

extern void handleCoversionSlow(controlRateInputs *);

void mainRisingEdgeCallback(controlRateInputs * controls, audioRateInputs * inputs, softwareSignaling * softwareSignals) {

	processClock(controls, inputs, softwareSignals);

}

void mainFallingEdgeCallback(softwareSignaling * softwareSignals) {

	handleFallingEdge(softwareSignals);

}

void auxRisingEdgeCallback(softwareSignaling * softwareSignals) {

	softwareSignals->aCounter = 0;
	softwareSignals->bCounter = 0;

}
void auxFallingEdgeCallback(softwareSignaling * softwareSignals) {
	// do nothing
}

void buttonPressedCallback(softwareSignaling * softwareSignals) {

	softwareSignals->aCounter = 0;
	softwareSignals->bCounter = 0;

}
void buttonReleasedCallback(softwareSignaling * softwareSignals) {
	// do nothing
}

void ioProcessCallback(audioRateInputs * inputWrite, controlRateInputs * controls, audioRateOutputs * outputRead) {

	WRITE_DAC1(outputRead->aLevel);
	WRITE_DAC2(outputRead->bLevel);

	// store the x and morph CVs at sample rate
	inputWrite->cv2Input = __USAT(cv2, 12);
	inputWrite->cv3Input = __USAT(cv3, 12);

	handleCoversionSlow(controls);

}
void nextSampleCallback(softwareSignaling * softwareSignals, audioRateOutputs * outputRead) {

	(*manageADac)(softwareSignals, outputRead);
	(*manageBDac)(softwareSignals, outputRead);

	softwareSignals->dacAEvent = DAC_EXECUTE;
	softwareSignals->dacBEvent = DAC_EXECUTE;

}


