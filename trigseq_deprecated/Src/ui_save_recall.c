#include "main.h"
#include "tsl_user.h"
#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"
#include "eeprom.h"
#include "user_interface.h"
#include "hardware_io.h"
#include "patterns.h"

// UI timer
TIM_HandleTypeDef htim4;

uint16_t VirtAddVarTab[NB_OF_VAR];

enum
{	NULL_SIG,     // Null signal, all state functions should ignore this signal and return their parent state or NONE if it's the top level state
	ENTRY_SIG,    // Entry signal, a state function should perform its entry actions (if any)
	EXIT_SIG,	  // Exit signal, a state function should pEntry signal, a state function should perform its entry actions (if any)erform its exit actions (if any)
	INIT_SIG,     // Just look to global value and initialize, return to default state.  For recalling (presets, memory)
	TIMEOUT_SIG,// timer timeout
	SENSOR_EVENT_SIG,  // Sensor state machine not busy, can be queried for events
	EXPAND_SW_ON_SIG,  // expander button depressed
	EXPAND_SW_OFF_SIG, // expander button released
	TSL_ERROR_SIG
};

enum {
	DAC_GATE_HIGH,
	DAC_GATE_LOW,
	DAC_EXECUTE,
};

/**
 *
 * Initialization routine for the UI state machine
 * Initialize the eeprom and read the last saved mode set
 * Initialize those modes
 * Set the UI state default
 *
 */

void uiInitialize()
{
	initializePatterns();

	HAL_FLASH_Unlock();
	eepromStatus = EE_Init();

	// error handling
	if(eepromStatus != EE_OK) {
		uiSetLEDs(3);
		uiTransition(&ui_error);
	}

	HAL_Delay(500);  // init time
	//uiLoadFromEEPROM(0);  // load the most recently stored state from memory


	shAMode = modeStateBuffer & SH_A_MASK;
	shBMode = (modeStateBuffer & SH_B_MASK) >> SH_B_SHIFT;
	andAMode = (modeStateBuffer & AND_A_MASK) >> AND_A_SHIFT;
	andBMode = (modeStateBuffer & AND_A_MASK) >> AND_B_SHIFT;
	patternBankIndex = (modeStateBuffer & BANK_MASK) >> BANK_SHIFT;

	/* ... initialization of ui attributes */
	// call each menu to initialize, to make UI process the stored modes

	currentBank = patternBanks[patternBankIndex];
	handleALow();
	handleBLow();

	// load calibration values from virtual EEPROM
//	eepromStatus = EE_ReadVariable(VirtAddVarTab[7], &EEPROMTemp);
//	cv3Cal = EEPROMTemp >> 8;
//	cv2Cal = EEPROMTemp & 0xFF00;
//	eepromStatus |= EE_ReadVariable(VirtAddVarTab[(position * 2) + 1], &EEPROMTemp);
//	cv1Cal = EEPROMTemp;

	State = &ui_default;
	uiTransition( &ui_default);
}


// there may be a clever way to do this without EEPROMTemp but i think the different typing may make that unnecessarily difficult.
void uiLoadFromEEPROM(int position) {

	eepromStatus = EE_ReadVariable(VirtAddVarTab[position * 2], &EEPROMTemp);
	modeStateBuffer = EEPROMTemp;  // load bottom 16 bits
	eepromStatus |= EE_ReadVariable(VirtAddVarTab[(position * 2) + 1], &EEPROMTemp);
	modeStateBuffer |= EEPROMTemp << 16;  // load 16 upper bits

	if (eepromStatus != HAL_OK){
		uiSetLEDs(2);
		uiTransition(&ui_error);
	}

}

// writes 2 16-bit values representing modeState to EEPROM per position,  1 runtime + 6 presets + calibration word
void uiStoreToEEPROM(int position){
	// store lower 16 bits
	eepromStatus = EE_WriteVariable(VirtAddVarTab[position * 2], (uint16_t)modeStateBuffer);
	eepromStatus |= EE_WriteVariable(VirtAddVarTab[(position * 2) + 1], (uint16_t)(modeStateBuffer >> 16));  // make sure i'm shifting in the right direction here!!

	if (eepromStatus != HAL_OK){
		uiSetLEDs(1);
		uiTransition(&ui_error);
	}
}

// calibration and default preset initialization
void ui_factoryReset(int sig){
	static uint16_t tempData;
	switch (sig){
	case ENTRY_SIG:
		UI_TIMER_RESET;
		UI_TIMER_SET_OVERFLOW(1000);
		UI_TIMER_ENABLE;
		// disable any DAC writes here?
		// maximize length of averaging?
		modeStateBuffer = DEFAULTPRESET1;
		uiStoreToEEPROM(1);
		modeStateBuffer = DEFAULTPRESET2;
		uiStoreToEEPROM(2);
		modeStateBuffer = DEFAULTPRESET3;
		uiStoreToEEPROM(3);
		modeStateBuffer = DEFAULTPRESET4;
		uiStoreToEEPROM(4);
		modeStateBuffer = DEFAULTPRESET5;
		uiStoreToEEPROM(5);
		modeStateBuffer = DEFAULTPRESET6;
		uiStoreToEEPROM(6);
		uiLoadFromEEPROM(1);
		break;

	case TIMEOUT_SIG:
	    //tempData = (cv3Average - 2048) << 8 | ((cv2Average - 2048) & 0xFFFFFF00);
		//eepromStatus = EE_WriteVariable(VirtAddVarTab[7], tempData);
		//eepromStatus |= EE_WriteVariable(VirtAddVarTab[15], (uint16_t)cv1Average - 2048);  // make sure i'm shifting in the right direction here!!
		if (eepromStatus != EE_OK){
			uiSetLEDs(4);
			uiTransition(&ui_error);
		} else {
			uiTransition(&ui_default);
		}
	}
}


