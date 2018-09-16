#include <trigseq.hpp>

void ViaTrigseq::mainRisingEdgeCallback() {

	sequencer.processClock();

	setLogicA(sequencer.aOutput);
	setAuxLogic(sequencer.logicOutput);

	// tricksy, sample only if sample and track mode is enabled
	uint32_t shASetting = (sequencer.trackA | sequencer.sampleA)  * sequencer.aOutput;
	uint32_t shBSetting = (sequencer.trackB | sequencer.sampleB) * sequencer.bOutput;

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

	system.outputs.dac1Samples[0] = gateController.updateGateA(sequencer.gateAEvent);
	system.outputs.dac2Samples[0] = gateController.updateGateB(sequencer.gateBEvent);
	system.outputs.dac3Samples[0] = 2048 - (sequencer.bOutput * 2048);


	sequencer.gateAEvent = SOFT_GATE_EXECUTE;
	sequencer.gateBEvent = SOFT_GATE_EXECUTE;

	setSH(sequencer.shASignal, sequencer.shBSignal);
	sequencer.shASignal += sequencer.sampleA;
	sequencer.shBSignal += sequencer.sampleB;

}

void ViaTrigseq::transferCompleteCallback() {

	system.outputs.dac1Samples[1] = gateController.updateGateA(sequencer.gateAEvent);
	system.outputs.dac2Samples[1] = gateController.updateGateB(sequencer.gateBEvent);
	system.outputs.dac3Samples[1] = 2048 - (sequencer.bOutput * 2048);

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

	system.controls.update();

	sequencer.parseControls(&system.controls, &system.inputs);
	if (runtimeDisplay) {
		updateRGBDisplay(system.outputs.dac1Samples[0],
				sequencer.logicOutput * 4095,
				system.outputs.dac2Samples[0]);
	}

}

