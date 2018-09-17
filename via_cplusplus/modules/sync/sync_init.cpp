
#include "sync.hpp"

// eeprom storage array
extern uint16_t VirtAddVarTab[NB_OF_VAR] = { 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7,
		0x8, 0x9, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16 };

void ViaSync::init(void) {


	// initialize our touch sensors
	tsl_user_Init();
	syncUI.initialize();

	fillWavetableArray();

	switchWavetable(wavetableArray[0][0]);

	initializeScales();

	pllController.scale = (Scale *) scaleArray[0][0];

	calculateDac3 = &ViaSync::calculateDac3Phasor;
	calculateLogicA = &ViaSync::calculateLogicAGate;
	calculateSH = &ViaSync::calculateSHMode1;

	system.inputs.init(SYNC_BUFFER_SIZE);
	system.outputs.init(SYNC_BUFFER_SIZE);
	system.bufferSize = SYNC_BUFFER_SIZE;
	system.ioStreamInit();

	pllController.rootMod = system.inputs.cv2Samples;
	syncWavetable.fm = system.inputs.cv2VirtualGround;
	syncWavetable.pm = system.inputs.cv2VirtualGround;
	syncWavetable.pwm = system.inputs.cv2VirtualGround;

	syncWavetable.morphMod = system.inputs.cv3Samples;

	syncWavetable.phaseReset = 1;
	pllController.phaseReset = 1;

	syncWavetable.increment = 10000;


}

