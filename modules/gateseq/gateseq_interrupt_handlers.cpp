#include <gateseq.hpp>

void ViaGateseq::mainRisingEdgeCallback() {

	sequencer.processClock();

	//setLogicA(1);
	setAuxLogic(sequencer.logicOutput);

//	if (sequencer.sampleA) {
//		sequencer.shASignal = (!sequencer.aOutput);
//	} else if (sequencer.trackA) {
//		sequencer.shASignal = (sequencer.aOutput);
//	} else {
//		sequencer.shASignal = 0;
//	}

	if (sequencer.sampleB) {
		sequencer.shBSignal = (!sequencer.bOutput);
	} else if (sequencer.trackB) {
		sequencer.shBSignal = (sequencer.bOutput);
	} else {
		sequencer.shBSignal = 0;
	}

	// similar deal here
	if (runtimeDisplay) {
		//setLEDA(sequencer.sampleA | sequencer.shASignal);
		setLEDB(sequencer.sampleB | sequencer.shBSignal);

		//setLEDC(sequencer.aOutput);
		setLEDD(sequencer.bOutput);
	}

	//sequencer.gateAEvent = SOFT_GATE_HIGH * sequencer.aOutput;
	sequencer.gateBEvent = SOFT_GATE_HIGH * sequencer.bOutput;

}

void ViaGateseq::mainFallingEdgeCallback() {

	sequencer.bOutput = 0;
	sequencer.updateLogicOutput();

	setAuxLogic(sequencer.logicOutput);

	sequencer.shBSignal = sequencer.sampleB;

	// similar deal here
	if (runtimeDisplay) {
		setLEDB(sequencer.sampleB);
		setLEDD(sequencer.bOutput);
	}

	sequencer.gateBEvent = SOFT_GATE_LOW * sequencer.andB;

}

void ViaGateseq::auxTimer1InterruptCallback() {

		// test
		// setLogicA(1);
		sequencer.virtualGateHigh = 1;

		sequencer.advanceSequencerA();
		sequencer.updateLogicOutput();
		setLogicA(sequencer.aOutput);
		setAuxLogic(sequencer.logicOutput);

		if (sequencer.sampleA) {
			sequencer.shASignal = (!sequencer.aOutput);
		} else if (sequencer.trackA) {
			sequencer.shASignal = (sequencer.aOutput);
		} else {
			sequencer.shASignal = 0;
		}

		// similar deal here
		if (runtimeDisplay) {
			setLEDA(sequencer.sampleA | sequencer.shASignal);
			setLEDC(sequencer.aOutput);
		}

		sequencer.gateAEvent = SOFT_GATE_HIGH * sequencer.aOutput;

		TIM2->ARR = sequencer.periodCount/sequencer.multiplier;
		TIM17->ARR = TIM2->ARR >> 13;
		TIM17->CNT = 1;
		TIM17->CR1 = TIM_CR1_CEN;


}

void ViaGateseq::auxTimer2InterruptCallback() {

		sequencer.virtualGateHigh = 0;

		sequencer.aOutput = 0;
		setLogicA(sequencer.aOutput);
		sequencer.updateLogicOutput();
		setAuxLogic(sequencer.logicOutput);
		sequencer.shASignal = sequencer.sampleA;
		// similar deal here
		if (runtimeDisplay) {
			setLEDA(sequencer.sampleA);
			setLEDC(sequencer.aOutput);
		}
		sequencer.gateAEvent = SOFT_GATE_LOW * sequencer.andA;

		TIM17->CR1 &= ~TIM_CR1_CEN;

}

void ViaGateseq::auxRisingEdgeCallback() {

	sequencer.aCounter = 0;
	sequencer.bCounter = 0;

	// process clock if there is a noticeable issue with resyncing?
	// this might have to talk to the main trigger in a slightly more elaborate way

}
void ViaGateseq::auxFallingEdgeCallback() {
	;
}

void ViaGateseq::buttonPressedCallback() {

	sequencer.aCounter = 0;
	sequencer.bCounter = 0;

}
void ViaGateseq::buttonReleasedCallback() {
	;
}

void ViaGateseq::ioProcessCallback() {
	;
}

void ViaGateseq::halfTransferCallback() {

	outputs.dac1Samples[0] = gateController.updateGateA(sequencer.gateAEvent);
	outputs.dac2Samples[0] = gateController.updateGateB(sequencer.gateBEvent);
	outputs.dac3Samples[0] = 2048 - (sequencer.bOutput * 2048);


	sequencer.gateAEvent = SOFT_GATE_EXECUTE;
	sequencer.gateBEvent = SOFT_GATE_EXECUTE;

	setSH(sequencer.shASignal, sequencer.shBSignal);
	if (sequencer.sampleA) {
		sequencer.shASignal = 1;
	}
	if (sequencer.sampleB) {
		sequencer.shBSignal = 1;
	}

}

void ViaGateseq::transferCompleteCallback() {

	outputs.dac1Samples[1] = gateController.updateGateA(sequencer.gateAEvent);
	outputs.dac2Samples[1] = gateController.updateGateB(sequencer.gateBEvent);
	outputs.dac3Samples[1] = 2048 - (sequencer.bOutput * 2048);

	sequencer.gateAEvent = SOFT_GATE_EXECUTE;
	sequencer.gateBEvent = SOFT_GATE_EXECUTE;

	setSH(sequencer.shASignal, sequencer.shBSignal);
	if (sequencer.sampleA) {
		sequencer.shASignal = 1;
	}
	if (sequencer.sampleB) {
		sequencer.shBSignal = 1;
	}

}

void ViaGateseq::slowConversionCallback() {

	controls.update();

	sequencer.parseControls(&controls, &inputs);

	updateRGBDisplay(outputs.dac1Samples[0],
			sequencer.logicOutput * 4095,
			outputs.dac2Samples[0], runtimeDisplay);

	if (runtimeDisplay) {
		SET_BLUE_LED_ONOFF(outputs.dac2Samples[0] >> 11);
	}

}

