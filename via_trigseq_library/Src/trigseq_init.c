#include "tsl_user.h"
#include "eeprom.h"
#include "user_interface.h"
#include "dsp.h"
#include "trigseq_interrupt_handlers.h"
#include "trigseq_patterns.h"

// eeprom storage array
extern uint16_t VirtAddVarTab[NB_OF_VAR] = {0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16};

void trigseqInit(void) {

	// initialize our touch sensors
	tsl_user_Init();
	uiInitialize();

	manageADac = dacAHigh;
	manageBDac = dacBHigh;

	initializePatterns();

	softwareSignals.currentABank = patternBanks[0];
	softwareSignals.currentBBank = patternBanks[0];

}
