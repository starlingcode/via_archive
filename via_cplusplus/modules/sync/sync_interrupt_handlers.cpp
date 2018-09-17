#include "sync.hpp"

const int phaseModPWMTables[33][65] = {phaseModPWM_0, phaseModPWM_1, phaseModPWM_2, phaseModPWM_3, phaseModPWM_4, phaseModPWM_5, phaseModPWM_6, phaseModPWM_7, phaseModPWM_8, phaseModPWM_9, phaseModPWM_10, phaseModPWM_11, phaseModPWM_12, phaseModPWM_13, phaseModPWM_14, phaseModPWM_15, phaseModPWM_16, phaseModPWM_17, phaseModPWM_18, phaseModPWM_19, phaseModPWM_20, phaseModPWM_21, phaseModPWM_22, phaseModPWM_23, phaseModPWM_24, phaseModPWM_25, phaseModPWM_26, phaseModPWM_27, phaseModPWM_28, phaseModPWM_29, phaseModPWM_30, phaseModPWM_31, phaseModPWM_32};

void ViaSync::mainRisingEdgeCallback(void) {

	pllController.measureFrequency();
	pllController.doPLL();
	pllController.generateFrequency();

	// should these be initialized to point to the same address?

	syncWavetable.increment = pllController.increment;
	syncWavetable.phaseReset = pllController.phaseReset;

	system.outputs.auxLogic[0] = GET_EXPAND_LOGIC_MASK(pllController.ratioChange);
	pllController.tapTempo = 0;

}

void ViaSync::mainFallingEdgeCallback(void) {

	pllController.ratioChange = 0;
	system.outputs.auxLogic[0] = GET_EXPAND_LOGIC_MASK(pllController.ratioChange);

}

void ViaSync::auxRisingEdgeCallback(void) {

	syncWavetable.phase = 0;

}
void ViaSync::auxFallingEdgeCallback(void) {
	;
}

void ViaSync::buttonPressedCallback(void) {

	if (pllController.tapTempo) {
		// store the length of the last period
		// average against the current length

		int tap = TIM2->CNT;

		writeBuffer(&tapStore, tap);
		tapSum += tap - readBuffer(&tapStore, 3);

		pllController.periodCount = tapSum >> 2;

		lastTap = tap;

		// reset the timer value
		TIM2->CNT = 0;

		pllController.doPLL();
		pllController.generateFrequency();

		// should these be initialized to point to the same address?

		syncWavetable.increment = pllController.increment;
		syncWavetable.phaseReset = pllController.phaseReset;

		system.outputs.auxLogic[0] = GET_EXPAND_LOGIC_MASK(pllController.ratioChange);

	} else {
		pllController.tapTempo = 1;
	}

}
void ViaSync::buttonReleasedCallback(void) {
	;
}

void ViaSync::ioProcessCallback(void) {
}

void ViaSync::halfTransferCallback(void) {

	system.setLogicOut(0, runtimeDisplay);


	system.outputs.dac2Samples[0] = __USAT(syncWavetable.advance((uint32_t *)wavetableRead, (uint32_t *) phaseModPWMTables), 12);
	system.outputs.dac1Samples[0] = 4095 - system.outputs.dac2Samples[0];
	(this->*calculateDac3)(0);
	(this->*calculateLogicA)(0);
	(this->*calculateSH)(0);

}

void ViaSync::transferCompleteCallback(void) {

	system.setLogicOut(0, runtimeDisplay);

	system.outputs.dac2Samples[1] = __USAT(syncWavetable.advance((uint32_t *)wavetableRead, (uint32_t *) phaseModPWMTables), 12);
	system.outputs.dac1Samples[1] = 4095 - system.outputs.dac2Samples[1];
	(this->*calculateDac3)(1);
	(this->*calculateLogicA)(0);
	(this->*calculateSH)(0);

}

void ViaSync::slowConversionCallback(void) {

	system.controls.update();
	syncWavetable.parseControls(&system.controls);
	pllController.parseControls(&system.controls, &system.inputs);

	if (pllController.tapTempo) {
		pllController.generateFrequency();
		syncWavetable.increment = pllController.increment;
	}

	int sample = system.outputs.dac1Samples[0];
	int lastPhaseValue = syncWavetable.ghostPhase;
	SET_RED_LED(sample * (lastPhaseValue >> 24));
	SET_BLUE_LED(sample * (!(lastPhaseValue >> 24)));
	SET_GREEN_LED(__USAT((system.inputs.cv3Samples[0] + system.controls.knob3Value - 2048), 12) * sample >> 12);

}

