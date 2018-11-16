#include <gateseq.hpp>

void ViaGateseq::mainRisingEdgeCallback() {

	simultaneousTrigFlag = 1;
#ifdef BUILD_F373
	TIM18->CR1 = TIM_CR1_CEN;
#endif
#ifdef BUILD_VIRTUAL
	sequencer.virtualTimer4Enable = 1;
#endif

	sequencer.processClock();

#ifdef BUILD_VIRTUAL
	if (sequencer.skipClock) {
		auxTimer1InterruptCallback();
	}
	sequencer.updateLogicOutput();
#endif

	setAuxLogic(sequencer.logicOutput);

	if (sequencer.sampleB) {
		sequencer.shBSignal = (!sequencer.bOutput);
	} else if (sequencer.trackB) {
		sequencer.shBSignal = (sequencer.bOutput);
	} else {
		sequencer.shBSignal = 0;
	}

	// similar deal here
	if (runtimeDisplay) {
		setLEDB(sequencer.sampleB | sequencer.shBSignal);
		setLEDD(sequencer.bOutput);
	}

	sequencer.gateBEvent = SOFT_GATE_HIGH * sequencer.bOutput;

	if (softGateBOn) {
		gateController.attackTimeB = ((1 << 20) * 1439 / sequencer.periodCount) << 12;
	} else {
		gateController.attackTimeB = (1 << 27);
	}
	gateController.releaseTimeB = gateController.attackTimeB;

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

		uint32_t clockPeriod = sequencer.periodCount/sequencer.multiplier;
		
		if (sequencer.shuffledStep) {
			sequencer.shuffleDelay = fix16_mul(clockPeriod, sequencer.shuffle);
			sequencer.shuffledStep = 0;
		} else {
			sequencer.shuffleDelay = -fix16_mul(clockPeriod, sequencer.shuffle);
			sequencer.shuffledStep = 1;
		}
		clockPeriod += sequencer.shuffleDelay;

#ifdef BUILD_F373

		TIM2->ARR = clockPeriod;
		TIM17->ARR = clockPeriod >> 14;
		TIM17->CNT = 1;
		TIM17->CR1 = TIM_CR1_CEN;
#endif 
#ifdef BUILD_VIRTUAL
		sequencer.virtualTimer2Overflow = clockPeriod;
		sequencer.virtualTimer3Overflow = clockPeriod >> 1;
		sequencer.virtualTimer3Count = 0;
		sequencer.virtualTimer3Enable = 1;
#endif


		if (softGateAOn) {
			gateController.attackTimeA = ((1 << 20) * 1439 / clockPeriod) << 12;
		} else {
			gateController.attackTimeA = 1 << 27;
		}
		gateController.releaseTimeA = gateController.attackTimeA;

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

#ifdef BUILD_F373
		TIM17->CR1 &= ~TIM_CR1_CEN;
#endif
#ifdef BUILD_VIRTUAL
		sequencer.virtualTimer3Enable = 0;
#endif

}

void ViaGateseq::auxTimer3InterruptCallback() {

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

