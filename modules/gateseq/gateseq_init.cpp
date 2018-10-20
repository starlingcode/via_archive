#include <gateseq.hpp>

void ViaGateseq::init(void) {

	initializeAuxOutputs();

	initializePatterns();

	gateController.updateGateA(SOFT_GATE_HIGH);
	gateController.updateGateB(SOFT_GATE_HIGH);

	sequencer.currentABank = seq1PatternBank[0];
	sequencer.currentBBank = seq2PatternBank[0];

	sequencer.gateAEvent = SOFT_GATE_EXECUTE;
	sequencer.gateBEvent = SOFT_GATE_EXECUTE;

	inputs.init(TRIGSEQ_BUFFER_SIZE);
	outputs.init(TRIGSEQ_BUFFER_SIZE);
	bufferSize = TRIGSEQ_BUFFER_SIZE;

	gateseqUI.initialize();

}
