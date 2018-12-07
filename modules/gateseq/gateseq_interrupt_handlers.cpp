#include <gateseq.hpp>

void ViaGateseq::mainRisingEdgeCallback() {

	// notify the module of a rising edge

	simultaneousTrigFlag = 1;

	// enable the simultaneous reset handling

#ifdef BUILD_F373
	TIM18->CR1 = TIM_CR1_CEN;
#endif
#ifdef BUILD_VIRTUAL
	sequencer.virtualTimer4Enable = 1;
#endif

	// process the rising edge

	sequencer.processMainRisingEdge();

	// in VCVRack, set a "virtual interrupt" for the sequencer 1 timer

#ifdef BUILD_VIRTUAL
	if (sequencer.processSeq1) {
		auxTimer1InterruptCallback();
		sequencer.processSeq1 = 0;
	}
	sequencer.updateLogicOutput();

#endif

	// update the aux logic output for new seq2 value

	setAuxLogic(sequencer.logicOutput);

	// set the leds

	if (runtimeDisplay) {
		setLEDB(sequencer.sampleB | sequencer.shBSignal);
		setLEDD(sequencer.bOutput);
	}

	// send a gate signal, update the timing (move gate events out of sequencer class)

	sequencer.gateBEvent = SOFT_GATE_HIGH * sequencer.bOutput;

	if (softGateBOn) {
		gateController.attackTimeB = ((1 << 20) * 1439 / sequencer.periodCount) << 12;
	} else {
		gateController.attackTimeB = (1 << 27);
	}
	gateController.releaseTimeB = gateController.attackTimeB;

}

void ViaGateseq::mainFallingEdgeCallback() {

	sequencer.processMainFallingEdge();

	// update the logic mode per sequencer II state

	setAuxLogic(sequencer.logicOutput);

//	if (!sequencer.clockOn) {
//		setLogicA(sequencer.aOutput);
//		setAuxLogic(sequencer.logicOutput);
//		if (runtimeDisplay) {
//			setLEDA(sequencer.sampleA);
//			setLEDC(sequencer.aOutput);
//		}
//		sequencer.gateAEvent = SOFT_GATE_LOW * sequencer.andA;
//	}

	// similar deal as the rising edge

	sequencer.shBSignal = sequencer.sampleB;

	if (runtimeDisplay) {
		setLEDB(sequencer.sampleB);
		setLEDD(sequencer.bOutput);
	}

	sequencer.gateBEvent = SOFT_GATE_LOW * sequencer.andB;

}

void ViaGateseq::auxTimer1InterruptCallback() {

	sequencer.processInternalRisingEdge();

	setLogicA(sequencer.aOutput);
	setAuxLogic(sequencer.logicOutput);

	if (runtimeDisplay) {
		setLEDA(sequencer.sampleA | sequencer.shASignal);
		setLEDC(sequencer.aOutput);
	}

	sequencer.gateAEvent = SOFT_GATE_HIGH * sequencer.aOutput;

	// update the gate time

	if (softGateAOn) {
		gateController.attackTimeA = ((1 << 20) * 1439 / sequencer.clockPeriod) << 12;
	} else {
		gateController.attackTimeA = 1 << 27;
	}
	gateController.releaseTimeA = gateController.attackTimeA;

}

void ViaGateseq::auxTimer2InterruptCallback() {

	sequencer.processInternalFallingEdge();

	//if (sequencer.clockOn) {
		setLogicA(sequencer.aOutput);
		setAuxLogic(sequencer.logicOutput);
		if (runtimeDisplay) {
			setLEDA(sequencer.sampleA);
			setLEDC(sequencer.aOutput);
		}
		sequencer.gateAEvent = SOFT_GATE_LOW * sequencer.andA;
	//}

}

void ViaGateseq::auxTimer3InterruptCallback() {

	// signal a timeout

	simultaneousTrigFlag = 0;
#ifdef BUILD_F373
	TIM18->CR1 &= ~TIM_CR1_CEN;
	TIM18->CNT = 1;
#endif
#ifdef BUILD_VIRTUAL
	sequencer.virtualTimer4Enable = 0;
	sequencer.virtualTimer4Count = 1;
#endif

}

void ViaGateseq::auxRisingEdgeCallback() {

	if (simultaneousTrigFlag) {
		sequencer.skipClock = 1;
		sequencer.aCounter = 0;
		sequencer.bCounter = 0;
		sequencer.advanceSequencerA();
		sequencer.advanceSequencerB();
		sequencer.updateLogicOutput();
		setLogicA(sequencer.aOutput);
		setAuxLogic(sequencer.logicOutput);
		if (sequencer.sampleB) {
			sequencer.shBSignal = (!sequencer.bOutput);
		} else if (sequencer.trackB) {
			sequencer.shBSignal = (sequencer.bOutput);
		} else {
			sequencer.shBSignal = 0;
		}
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
			setLEDB(sequencer.sampleB | sequencer.shBSignal);
			setLEDC(sequencer.aOutput);
			setLEDD(sequencer.bOutput);
		}

		sequencer.gateAEvent = SOFT_GATE_HIGH * sequencer.aOutput;
		sequencer.gateBEvent = SOFT_GATE_HIGH * sequencer.bOutput;
	} else {
		sequencer.aCounter = 0;
		sequencer.bCounter = 0;
	}

}
void ViaGateseq::auxFallingEdgeCallback() {
	;
}

void ViaGateseq::buttonPressedCallback() {

	sequencer.aCounter = 0;
	sequencer.bCounter = 0;

	this->gateseqUI.dispatch(EXPAND_SW_ON_SIG);


}
void ViaGateseq::buttonReleasedCallback() {

	this->gateseqUI.dispatch(EXPAND_SW_OFF_SIG);

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

#ifdef BUILD_F373

	if (runtimeDisplay) {
		SET_BLUE_LED_ONOFF((outputs.dac2Samples[0] >> 11));
	}

#endif

}

