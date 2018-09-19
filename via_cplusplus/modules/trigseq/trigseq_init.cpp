#include <trigseq.hpp>

// eeprom storage array
extern uint16_t VirtAddVarTab[NB_OF_VAR] = { 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7,
		0x8, 0x9, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16 };

void ViaTrigseq::init(void) {

	initializeAuxOutputs();

	// initialize our touch sensors
	tsl_user_Init();
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

