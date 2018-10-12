
#include "sync.hpp"

void ViaSync::init(void) {

	initializeAuxOutputs();

	fillWavetableArray();

	// switchWavetable(wavetableArray[0][0]);

	initializeScales();

	pllController.scale = (Scale *) scaleArray[0][0];

	calculateDac3 = &ViaSync::calculateDac3Phasor;
	calculateLogicA = &ViaSync::calculateLogicAGate;
	calculateSH = &ViaSync::calculateSHMode1;

	inputs.init(SYNC_BUFFER_SIZE);
	outputs.init(SYNC_BUFFER_SIZE);
	bufferSize = SYNC_BUFFER_SIZE;

	pllController.rootMod = inputs.cv2Samples;
	syncWavetable.fm = inputs.cv2VirtualGround;
	syncWavetable.pm = inputs.cv2VirtualGround;
	syncWavetable.pwm = inputs.cv2VirtualGround;

	for (int i = 0; i < 32; i++) {
		writeBuffer(&pllController.nudgeBuffer, 0);
	}

	syncWavetable.morphMod = inputs.cv3Samples;

	syncWavetable.phaseReset = 1;
	pllController.phaseReset = 1;

	syncWavetable.increment = 10000;

	syncUI.initialize();

}

