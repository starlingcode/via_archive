#include "via_rev5_hardware_io.h"
#include "tsl_user.h"
#include "eeprom.h"
#include "user_interface.h"
#include "sync_dsp.h"
#include "sync_scales.h"
#include "sync_ui_implementation.h"
#include "sync_next_sample.h"
#include "sync_modes.h"

// eeprom storage array
extern uint16_t VirtAddVarTab[NB_OF_VAR] = {0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16};

void syncInit(void) {

	viaSignalInit();

	initializeUICallbacks();

	// initialize our touch sensors
	tsl_user_Init();
	uiInitialize();

	fillFamilyArray();

	GROUP_MODE = 0;
	SCALE_MODE = 0;

	familyIndicator = 2;

	switchFamily();


	getIncrement = getIncrementAttack;
	advancePhase = advancePhasePM;
	calculateSH = calculateSHMode1;
	calculateLogicA = calculateLogicAGate;
	updateRGB = updateRGBAudio;

	initializeScales();

	softwareSignals.scale = scaleArray[0][0];

	softwareSignals.gateOnCount = 10000;
	softwareSignals.periodCount = 10000;
	softwareSignals.phaseSignal = 0;
	softwareSignals.attackIncrement = 10000;

}
