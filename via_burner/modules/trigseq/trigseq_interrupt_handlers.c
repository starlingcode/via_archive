#include "trigseq.h"

void trigseq_mainRisingEdgeCallback(trigseq_signal_set * signals) {

	dualEuclideanParameters *parameters = signals->parameters;

	dualEuclideanProcessClock(signals->controls, signals->inputs,
			signals->parameters);

	setLogicA(parameters->aOutput);
	setAuxLogic(parameters->logicOutput);

	// tricksy, sample only if sample and track mode is enabled
	uint32_t shASetting = (parameters->trackA | parameters->sampleA)  * parameters->aOutput;
	uint32_t shBSetting = (parameters->trackB | parameters->sampleB) * parameters->bOutput;
//
	signals->outputs->shA[0] = shASetting;
	signals->outputs->shB[0] = shBSetting;

// similar deal here
	if (runtimeDisplay) {
		setLEDA(parameters->sampleA | shASetting);
		setLEDB(parameters->sampleB | shBSetting);

		setLEDC(parameters->aOutput);
		setLEDD(parameters->bOutput);
	}

	parameters->outputAEvent = SOFT_GATE_HIGH * parameters->aOutput;
	parameters->outputBEvent = SOFT_GATE_HIGH * parameters->bOutput;

}

void trigseq_mainFallingEdgeCallback(trigseq_signal_set * signals) {

	dualEuclideanParameters *parameters = signals->parameters;

	parameters->aOutput = 0;
	parameters->bOutput = 0;
	parameters->logicOutput = 0;

	setLogicA(parameters->aOutput);
	setAuxLogic(parameters->logicOutput);

	signals->outputs->shA[0] = parameters->sampleA;
	signals->outputs->shB[0] = parameters->sampleA;

	// similar deal here
	if (runtimeDisplay) {
		setLEDA(parameters->sampleA);
		setLEDB(parameters->sampleB);

		setLEDC(parameters->aOutput);
		setLEDD(parameters->bOutput);
	}

	parameters->outputAEvent = SOFT_GATE_LOW * parameters->andA;
	parameters->outputBEvent = SOFT_GATE_LOW * parameters->andB;

}

void trigseq_auxRisingEdgeCallback(trigseq_signal_set * signals) {

	dualEuclideanParameters *parameters = signals->parameters;

	parameters->aCounter = 0;
	parameters->bCounter = 0;

	// process clock if there is a noticeable issue with resyncing?
	// this might have to talk to the main trigger in a slightly more elaborate way

}
void trigseq_auxFallingEdgeCallback(trigseq_signal_set * signals) {
	;
}

void trigseq_buttonPressedCallback(trigseq_signal_set * signals) {

	dualEuclideanParameters *parameters = signals->parameters;

	parameters->aCounter = 0;
	parameters->bCounter = 0;

}
void trigseq_buttonReleasedCallback(trigseq_signal_set * signals) {
	;
}

void trigseq_ioProcessCallback(trigseq_signal_set * signals) {
	;
}

void trigseq_halfTransferCallback(trigseq_signal_set * signals) {

	dualEuclideanParameters *parameters = signals->parameters;
	audioRateOutputs *outputs = signals->outputs;

	(*manageOutputA)(parameters->outputAEvent, 0, outputs);
	(*manageOutputB)(parameters->outputBEvent, 0, outputs);
	outputs->dac3Samples[0] = 2048 - (parameters->bOutput * 2048);

	parameters->outputAEvent = SOFT_GATE_EXECUTE;
	parameters->outputBEvent = SOFT_GATE_EXECUTE;

	setSH(outputs->shA[0], outputs->shB[0]);
	outputs->shA[0] += parameters->sampleA;
	outputs->shB[0] += parameters->sampleB;

}

void trigseq_transferCompleteCallback(trigseq_signal_set * signals) {

	dualEuclideanParameters *parameters = signals->parameters;
	audioRateOutputs *outputs = signals->outputs;

	(*manageOutputA)(parameters->outputAEvent, 1, outputs);
	(*manageOutputB)(parameters->outputBEvent, 1, outputs);
	outputs->dac3Samples[1] = 2048 - (parameters->bOutput * 2048);

	parameters->outputAEvent = SOFT_GATE_EXECUTE;
	parameters->outputBEvent = SOFT_GATE_EXECUTE;

	setSH(outputs->shA[0], outputs->shB[0]);
	if (parameters->sampleA) {
		outputs->shA[0] = 1;
	}
	if (parameters->sampleB) {
		outputs->shB[0] = 1;
	}

}

void trigseq_slowConversionCallback(trigseq_signal_set *signals) {

	controlRateInputs *controls = signals->controls;
	dualEuclideanParameters *parameters = signals->parameters;

	via_updateControlRateInputs(controls);
	// some controls should be parsed here
	if (runtimeDisplay) {
		updateRGBDisplay(4095 - !parameters->aOutput * parameters->andA * 4095,
				parameters->logicOutput * 1024,
				4095 - !parameters->bOutput * parameters->andB * 4095);
	}

}

