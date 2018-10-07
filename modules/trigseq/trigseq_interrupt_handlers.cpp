#include <trigseq.hpp>

void ViaTrigseq::mainRisingEdgeCallback() {

	sequencer.processClock();

	setLogicA(sequencer.aOutput);
	setAuxLogic(sequencer.logicOutput);

	// tricksy, sample only if sample and track mode is enabled
	uint32_t shASetting;
	uint32_t shBSetting;

	if (sequencer.sampleA) {
		shASetting = (!sequencer.aOutput);
	} else if (sequencer.trackA) {
		shASetting = (sequencer.aOutput);
	} else {
		shASetting = 0;
	}

	if (sequencer.sampleB) {
		shBSetting = (!sequencer.bOutput);
	} else if (sequencer.trackB) {
		shBSetting = (sequencer.bOutput);
	} else {
		shBSetting = 0;
	}

	sequencer.shASignal = shASetting;
	sequencer.shBSignal = shBSetting;

	// similar deal here
	if (runtimeDisplay) {
		setLEDA(sequencer.sampleA | shASetting);
		setLEDB(sequencer.sampleB | shBSetting);

		setLEDC(sequencer.aOutput);
		setLEDD(sequencer.bOutput);
	}

	sequencer.gateAEvent = SOFT_GATE_HIGH * sequencer.aOutput;
	sequencer.gateBEvent = SOFT_GATE_HIGH * sequencer.bOutput;

}

void ViaTrigseq::mainFallingEdgeCallback() {

	sequencer.aOutput = 0;
	sequencer.bOutput = 0;
	sequencer.logicOutput = 0;

	setLogicA(sequencer.aOutput);
	setAuxLogic(sequencer.logicOutput);

	sequencer.shASignal = sequencer.sampleA;
	sequencer.shBSignal = sequencer.sampleB;

	// similar deal here
	if (runtimeDisplay) {
		setLEDA(sequencer.sampleA);
		setLEDB(sequencer.sampleB);

		setLEDC(sequencer.aOutput);
		setLEDD(sequencer.bOutput);
	}

	sequencer.gateAEvent = SOFT_GATE_LOW * sequencer.andA;
	sequencer.gateBEvent = SOFT_GATE_LOW * sequencer.andB;

}

void ViaTrigseq::auxRisingEdgeCallback() {

	sequencer.aCounter = 0;
	sequencer.bCounter = 0;

	// process clock if there is a noticeable issue with resyncing?
	// this might have to talk to the main trigger in a slightly more elaborate way

}
void ViaTrigseq::auxFallingEdgeCallback() {
	;
}

void ViaTrigseq::buttonPressedCallback() {

	sequencer.aCounter = 0;
	sequencer.bCounter = 0;

}
void ViaTrigseq::buttonReleasedCallback() {
	;
}

void ViaTrigseq::ioProcessCallback() {
	;
}

void ViaTrigseq::halfTransferCallback() {

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

void ViaTrigseq::transferCompleteCallback() {

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

void ViaTrigseq::slowConversionCallback() {

	controls.update();

	sequencer.parseControls(&controls, &inputs);

	updateRGBDisplay(outputs.dac1Samples[0],
			sequencer.logicOutput * 4095,
			outputs.dac2Samples[0], runtimeDisplay);

}

