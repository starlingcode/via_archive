#include <trigseq.hpp>

void ViaTrigseq::init(void) {

	initializeAuxOutputs();

	// initialize our touch sensors
	// move to hardware init?
	//tsl_user_Init();
	trigseqUI.initialize();

	initializePatterns();

	gateController.updateGateA(SOFT_GATE_HIGH);
	gateController.updateGateB(SOFT_GATE_HIGH);

	sequencer.currentABank = patternBank[0];
	sequencer.currentBBank = patternBank[0];

	sequencer.gateAEvent = SOFT_GATE_EXECUTE;
	sequencer.gateBEvent = SOFT_GATE_EXECUTE;

	inputs.init(TRIGSEQ_BUFFER_SIZE);
	outputs.init(TRIGSEQ_BUFFER_SIZE);
	bufferSize = TRIGSEQ_BUFFER_SIZE;

}

