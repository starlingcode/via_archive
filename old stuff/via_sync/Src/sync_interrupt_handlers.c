#include "sync_dsp.h"
#include "user_interface.h"
#include "via_rev5_hardware_io.h"
#include "sync_modes.h"
#include "sync_next_sample.h"

enum
{	NULL_SIG,     // Null signal, all state functions should ignore this signal and return their parent state or NONE if it's the top level state
	ENTRY_SIG,    // Entry signal, a state function should perform its entry actions (if any)
	EXIT_SIG,	  // Exit signal, a state function should pEntry signal, a state function should perform its entry actions (if any)erform its exit actions (if any)
	INIT_SIG,     // Just look to global value and initialize, return to default state.  For recalling (presets, memory)
	TIMEOUT_SIG,// timer timeout
	SENSOR_EVENT_SIG,  // Sensor state machine not busy, can be queried for events
	EXPAND_SW_ON_SIG,  // expander button depressed
	EXPAND_SW_OFF_SIG, // expander button released
	TSL_ERROR_SIG
};


void generateFrequency(controlRateInputs * controls, audioRateInputs * inputs, softwareSignaling * softwareSignals);

extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim16;
extern TIM_HandleTypeDef htim17;

void mainRisingEdgeCallback(osc_signal_set * signals) {

	// store the length of the last period
	signals->softwareSignals->periodCount = TIM2->CNT;

	// reset the timer value
	TIM2->CNT = 0;

	// generate increments from the timing reading
	generateFrequency(signals->controls, signals->inputs, signals->softwareSignals);

	signals->softwareSignals->tapTempo = 0;



}

void mainFallingEdgeCallback(softwareSignaling * softwareSignals) {

	EXPAND_LOGIC_LOW
}

void auxRisingEdgeCallback(osc_signal_set * signals) {
	// arbitrary big number guaranteed to be greater than the largest gcd value for the scales
	// see generateFrequency for implementation
	signals->softwareSignals->pllReset = 65535;
	// apply the pll if uncommented
	// generateFrequency(signals->controls, signals->inputs, signals->softwareSignals);
}
void auxFallingEdgeCallback(osc_signal_set * signals) {
	;
}

void buttonPressedCallback(osc_signal_set * signals) {

	static buffer tapStore;
	static int tapSum;

	uiDispatch(EXPAND_SW_ON_SIG);

	if (signals->softwareSignals->tapTempo) {
		// store the length of the last period

		int tap = __HAL_TIM_GET_COUNTER(&htim2);

		writeBuffer(&tapStore, tap);
		tapSum = tap + tapSum - readBuffer(&tapStore, 7);
		signals->softwareSignals->periodCount = tapSum >> 3;

		// reset the timer value
		__HAL_TIM_SET_COUNTER(&htim2, 0);

		// generate increments from the timing reading
		generateFrequency(signals->controls, signals->inputs, signals->softwareSignals);
	} else {
		signals->softwareSignals->tapTempo = 1;
	}

}
void buttonReleasedCallback(osc_signal_set * signals) {
	uiDispatch(EXPAND_SW_OFF_SIG);
}

void ioProcessCallback(osc_signal_set * signals) {

	audioRateOutputs* outputRead = signals->outputs;
	int outputSample =  signals->outputs->samples;

	WRITE_DAC1(4095 - outputSample);
	WRITE_DAC2(outputSample);
	WRITE_DAC3(__USAT(outputRead->dac3Sample, 12));


	// replace with one function using runtime display as a mask
	if (RUNTIME_DISPLAY) {
		setLogicOutputs(outputRead->logicAHandler, outputRead->auxLogicHandler, outputRead->shAHandler, outputRead->shBHandler);
	} else {
		setLogicOutputsNoLEDs(outputRead->logicAHandler, outputRead->auxLogicHandler, outputRead->shAHandler, outputRead->shBHandler);
	}

	audioRateInputs* inputWrite = signals->inputs;
	// store the x and morph CVs at sample rate
	inputWrite->cv2Input = __USAT(cv2, 12);
	inputWrite->cv3Input = __USAT(cv3, 12);


}
void generateSample(osc_signal_set * signals) {

	nextSample(signals->controls, signals->inputs, signals->outputs, signals->softwareSignals);

}
