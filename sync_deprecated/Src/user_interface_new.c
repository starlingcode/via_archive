#include "tables.h"
#include "main.h"
#include "tsl_user.h"
#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"
#include "interrupt_functions.h"
#include "eeprom.h"
#include "int64.h"
#include "user_interface.h"


uint32_t eepromStatus;

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim4;

enum
{	NULL_SIG,     // Null signal, all state functions should ignore this signal and return their parent state or NONE if it's the top level state
	ENTRY_SIG,    // Entry signal, a state function should perform its entry actions (if any)
	EXIT_SIG,	  // Exit signal, a state function should pEntry signal, a state function should perform its entry actions (if any)erform its exit actions (if any)
	INIT_SIG,     // Just look to global value and initialize, return to default state.  For recalling (presets, memory)
	TIMEOUT_SIG,  // timer timeout
	SENSOR_EVENT_SIG,  // Sensor state machine not busy, can be queried for events
	EXPAND_SW_ON_SIG,  // expander button depressed
	EXPAND_SW_OFF_SIG, // expander button released
	TSL_ERROR_SIG
};

// for eeprom storage
// virtual EEPROM addresses (store in flash, doesn't need to change)
static uint16_t VirtAddVarTab[NB_OF_VAR] = {0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16};
// holds the mode state as a EEPROM-formatted value.
uint32_t modeStateBuffer;
// this holds the read 16-bit EEPROM data while it gets shifted and reconstituted into modeStateBuffer.
uint16_t EEPROMTemp;

extern uint32_t morphCal;
extern uint32_t t1Cal;
extern uint32_t t2Cal;

uint32_t t1CVAverage;
uint32_t t2CVAverage;
uint32_t morphCVAverage;

//used by state machine to signal preset to be stored or recalled.
int presetNumber;

// currentScale * scaleType = our index in scales
int currentScale;

struct rgb orange = {4095, 4095, 0};
struct rgb magenta = {4095, 0, 4095};
struct rgb cyan = {0, 4095, 4095};
struct rgb red = {4095, 0, 0};
struct rgb green = {0, 4095, 0};
struct rgb blue = {0, 0, 4095};

// initial setup of UI
void uiLoadFromEEPROM(int);
void uiStoreToEEPROM(int);

// helper functions for the UI
void uiClearLEDs();
void uiSetLEDs(int digit);
void uiClearRGB();
void uiSetRGB(struct rgb);

static inline void uiTimerReset() { __HAL_TIM_SET_COUNTER(&htim4, 0); }
static inline void uiTimerDisable() { __HAL_TIM_DISABLE(&htim4); }
static inline void uiTimerEnable() { __HAL_TIM_ENABLE(&htim4); }
static inline int uiTimerRead() { return __HAL_TIM_GET_COUNTER(&htim4); }  // return needed?
static inline void uiTimerSetOverflow(int val) { TIM4->ARR = val; }

void uiStoreToEEPROM(int);
void uiLoadFromEEPROM(int);

// a pointer to these functions is the current state
void ui_default(int sig);
void ui_newMode(int sig);
void ui_syncMenu(int sig);
void ui_logicAMenu(int sig);
void ui_logicBMenu(int sig);
void ui_newLogicMode(int sig);
void ui_SampleHoldMenu(int sig);
void ui_familyUpMenu(int sig);
void ui_familyDownMenu(int sig);
void ui_scaleMenu(int sig);
void ui_scaleTypeUp(int sig);
void ui_scaleTypeDown(int sig);
void ui_xMenu(int sig);
void ui_autoDutyMenu(int sig);
void ui_error(int sig);
void ui_presetMenu(int sig);
void ui_switchPreset(int sig);
void ui_newPreset(int sig);
void ui_factoryReset(int sig);

void uiInitialize(void);

void uiDispatch(int sig) {(*State)(sig);}


// transition to new state
void uiTransition(void (*func)(int)) {
	uiDispatch(EXIT_SIG);
	State = func;
	uiDispatch(ENTRY_SIG);
}


// default runtime state,  handles launching menus on detect, and turning runtime  display back on upon entry.
void ui_default(int sig)
{
	switch (sig){

	case ENTRY_SIG:
		SET_RUNTIME_DISPLAY;
		uiClearLEDs();
		uiClearRGB();
		uiTimerReset();
		uiTimerDisable();
		break;

	case SENSOR_EVENT_SIG:

		if (SCALESENSOR == PRESSED){
			uiTransition(&ui_scaleMenu);

		} else if (SHSENSOR == PRESSED){
			uiTransition(&ui_SampleHoldMenu);

		} else if (SYNCSENSOR == PRESSED){
			uiTransition(&ui_syncMenu);

		} else if (XSENSOR == PRESSED){
			uiTransition(&ui_xMenu);

		} else if (UPSENSOR == PRESSED){
			uiTransition(&ui_familyUpMenu);

		} else if (DOWNSENSOR == PRESSED){
			uiTransition(&ui_familyDownMenu);
		}
		break;

	case EXPAND_SW_ON_SIG:
		uiTransition(&ui_presetMenu);
		break;

	case EXIT_SIG:
		uiClearLEDs();
		uiClearRGB();
		CLEAR_RUNTIME_DISPLAY;
		uiTimerReset();
		uiTimerEnable();
		break;
	}
}

// catches error states and gives display feedback
void ui_error(int sig){

	// not yet implemented

}


// newMode state is transitioned into after a mode change, writes to EEPROM and maintains mode display until timeout.
void ui_newMode(int sig)
{
	switch (sig)
	{
	case ENTRY_SIG:
		uiStoreToEEPROM(0);
		CLEAR_RUNTIME_DISPLAY;
		uiTimerReset();
		uiTimerSetOverflow(10000);
		uiTimerEnable();
		break;

	// once uiTimerRead() times out, clear display and return to default state
	case TIMEOUT_SIG:
		uiTransition(&ui_default);
		break;

	// in case of new events immediately jump to relevant menu
	case SENSOR_EVENT_SIG:

		if (SCALESENSOR == PRESSED){
			uiTransition( &ui_scaleMenu);

		} else if (SHSENSOR == PRESSED){
			uiTransition( &ui_SampleHoldMenu);

		} else if (SYNCSENSOR == PRESSED){
			uiTransition( &ui_syncMenu);

		} else if (XSENSOR == PRESSED){
			uiTransition( &ui_xMenu);

		} else if (UPSENSOR == PRESSED){
			uiTransition( &ui_familyUpMenu);

		} else if (DOWNSENSOR == PRESSED){
			uiTransition( &ui_familyDownMenu);
		}
		break;

	case EXPAND_SW_ON_SIG:
		uiTransition(&ui_presetMenu);
		break;

	case EXIT_SIG:
		CLEAR_RUNTIME_DISPLAY;
		uiClearLEDs();
		uiClearRGB();
		uiTimerReset();
		uiTimerEnable();
		break;
	}
}

void ui_syncMenu(int sig)
{
	switch (sig)
	{
	case ENTRY_SIG:

		uiTimerSetOverflow(65535);
		uiTimerReset();
		uiTimerEnable();
		uiSetLEDs(button4Mode);
		break;

	case SENSOR_EVENT_SIG:

		if (SYNCSENSOR == RELEASED){
			if(uiTimerRead() < 3000){
				button4Mode = (button4Mode + 1) % 3;
				modeStateBuffer = (modeStateBuffer & ~(SYNCMASK)) | (button4Mode << SYNCSHIFT);
				uiSetLEDs(button4Mode);
				uiTransition(&ui_newMode);
			} else {
				//no mode change
				uiTransition(&ui_default);
			}

		} else if (SCALESENSOR == PRESSED){
			// descend into submenu
			uiTransition(&ui_logicAMenu);

		} else if (XSENSOR == PRESSED){
			// descend into submenu
			uiTransition(&ui_logicBMenu);
		} else if (SHSENSOR == PRESSED){
			uiTransition(&ui_autoDutyMenu);
		}
		break;
	}
}


void ui_logicAMenu(int sig)
{
	switch (sig)
	{
	case ENTRY_SIG:
		uiTimerReset();  // start count over for submenus
		uiSetLEDs(logicOutA);
		uiTimerSetOverflow(65535);
		break;

	case SENSOR_EVENT_SIG:

		if (SYNCSENSOR == RELEASED){
			uiTransition(&ui_default);

		} else if (SCALESENSOR == RELEASED){
			if(uiTimerRead() < 3000){
				logicOutA = (logicOutA + 1) % 5;
				modeStateBuffer = (modeStateBuffer & ~(LOGICAMASK)) | logicOutA << LOGICASHIFT;

				CLEAR_GATEA;
				CLEAR_TRIGA;
				CLEAR_DELTAA;
				CLEAR_RATIO_DELTAA;
				CLEAR_PLL_DIVA;

				switch (logicOutA) {
				case 0:
					SET_GATEA;
					break;
				case 1:
					SET_TRIGA;
					break;
				case 2:
					SET_DELTAA;
					break;
				case 3:
					SET_RATIO_DELTAA;
					break;
				case 4:
					SET_PLL_DIVA;
					break;
				}

				uiSetLEDs(logicOutA);
				uiTransition(&ui_newLogicMode);

			} else {
				uiTransition(&ui_default);  // fall all the way back to default instead of allowing a trig modechange
			}

		} else if (XSENSOR == PRESSED){
			uiTransition(&ui_logicBMenu);  // should we even allow this case?  more chances of bumped buttons?
		}
		break;

	case INIT_SIG:
		CLEAR_GATEA;
		CLEAR_TRIGA;
		CLEAR_DELTAA;
		CLEAR_RATIO_DELTAA;
		CLEAR_PLL_DIVA;

		switch (logicOutA) {
		case 0:
			SET_GATEA;
			break;
		case 1:
			SET_TRIGA;
			break;
		case 2:
			SET_DELTAA;
			break;
		case 3:
			SET_RATIO_DELTAA;
			break;
		case 4:
			SET_PLL_DIVA;
			break;
		}
	}
}

void ui_logicBMenu(int sig)
{
	switch (sig)
	{
	case ENTRY_SIG:
		uiTimerReset();  // start count over for submenus
		uiSetLEDs(logicOutB);
		uiTimerSetOverflow(65535);
		break;

	case SENSOR_EVENT_SIG:

		if (SYNCSENSOR == RELEASED){
			uiTransition(&ui_default);
			break;

		} else if (XSENSOR == RELEASED){
			if(uiTimerRead() < 3000){
				logicOutB = (logicOutB + 1) % 5;
				modeStateBuffer = (modeStateBuffer & ~(LOGICBMASK)) | (logicOutB << LOGICBSHIFT);
				CLEAR_GATEB;
				CLEAR_TRIGB;
				CLEAR_DELTAB;
				CLEAR_RATIO_DELTAB;
				CLEAR_PLL_DIVB;

				switch (logicOutB) {
				case 0:
					SET_GATEB;
					break;
				case 1:
					SET_TRIGB;
					break;
				case 2:
					SET_DELTAB;
					break;
				case 3:
					SET_RATIO_DELTAB;
					break;
				case 4:
					SET_PLL_DIVB;
					break;
				}

				uiSetLEDs(logicOutB);
				uiTransition(&ui_newLogicMode);

			} else {
				uiTransition(&ui_default);
				break;
			}

		} else if (SCALESENSOR == PRESSED){
			uiTransition(&ui_logicAMenu);  // don't make this transition maybe??
		}
		break;

	case INIT_SIG:
		CLEAR_GATEB;
		CLEAR_TRIGB;
		CLEAR_DELTAB;
		CLEAR_RATIO_DELTAB;
		CLEAR_PLL_DIVB;

		switch (logicOutB) {
		case 0:
			SET_GATEB;
			break;
		case 1:
			SET_TRIGB;
			break;
		case 2:
			SET_DELTAB;
			break;
		case 3:
			SET_RATIO_DELTAB;
			break;
		case 4:
			SET_PLL_DIVB;
			break;
		}
	}
}

// special newMode which only accepts additional presses on FREQ or LOOP, and returns to newMode on TRIG release.
// for cycling through logicOut modes.  Does not time out.
void ui_newLogicMode(int sig)
{
	switch (sig)
	{
	case ENTRY_SIG:
		uiTimerReset();  // start count over
		uiStoreToEEPROM(0);  // store in preset 0 (current state)
		break;

	// once uiTimerRead() times out, clear display and return to default state

	case SENSOR_EVENT_SIG:
		// in case either logic mode sensors are pressed, jump to their menu
		if (SCALESENSOR == PRESSED){
			uiTransition(&ui_logicAMenu);

		} else if (XSENSOR == PRESSED){
			uiTransition(&ui_logicBMenu);
			// if sync sensor is released, jump out of menu to new mode display.
		}
		if (SHSENSOR == PRESSED){
			uiTransition(&ui_autoDutyMenu);
		}
		else if (SYNCSENSOR == RELEASED){
			uiTransition(&ui_newMode);
		}
		break;
	}
}

void ui_SampleHoldMenu(int sig)
{
	switch (sig)
	{
	case ENTRY_SIG:
		uiTimerSetOverflow(65535);
		uiSetLEDs(sampleHoldMode);
		break;

	case SENSOR_EVENT_SIG:
		if (SHSENSOR == RELEASED){
			if(uiTimerRead() < 3000){
				sampleHoldMode = (sampleHoldMode + 1) % 6;
				modeStateBuffer = (modeStateBuffer & ~(SHMASK)) | (sampleHoldMode << SHSHIFT);
				SH_A_TRACK;  // ensure that there's no carryover holding by forcing tracking
				SH_B_TRACK;
				uiSetLEDs(sampleHoldMode);
				uiTransition(&ui_newMode);
			} else {
				uiTransition(&ui_default);
			}
		}
		break;

	case INIT_SIG:
		SH_A_TRACK;
		SH_B_TRACK;
		break;
	}

}


void ui_familyUpMenu(int sig)
{
	switch (sig)
	{
	case ENTRY_SIG:
		uiTimerSetOverflow(65535);
		uiSetLEDs(familyIndicator);
		uiSetRGB(currentFamily.color);
		break;

	case SENSOR_EVENT_SIG:
		if (UPSENSOR == RELEASED){
			if(uiTimerRead() < 3000){
				familyIndicator = (familyIndicator + 1) % 8;
				switchFamily();
				modeStateBuffer = (modeStateBuffer & ~(FAMILYMASK)) | (familyIndicator << FAMILYSHIFT);
				uiSetLEDs(familyIndicator % 8);
				uiSetRGB(currentFamily.color);
				uiTransition( &ui_newMode);
			} else {
				uiTransition( &ui_default);
			}
		}
		break;
	}
}

void ui_familyDownMenu(int sig)
{
	switch (sig)
	{
	case ENTRY_SIG:
		uiTimerSetOverflow(65535);
		uiSetLEDs(familyIndicator);
		uiSetRGB(currentFamily.color);
		break;

	case SENSOR_EVENT_SIG:
		if (DOWNSENSOR == RELEASED){
			if(uiTimerRead() < 3000){
				if (familyIndicator == 0) {
					familyIndicator = 8;  // wrap around
				} else {
					familyIndicator--;
				}
				switchFamily();
				modeStateBuffer = (modeStateBuffer & ~(FAMILYMASK)) | (familyIndicator << FAMILYSHIFT);
				uiSetLEDs(familyIndicator % 8);
				uiSetRGB(currentFamily.color);
				uiTransition( &ui_newMode);
			} else {
				uiTransition(&ui_default);
			}
		}
		break;
	}
}

void ui_scaleMenu(int sig) {
	switch (sig) {

	case ENTRY_SIG:
		uiTimerSetOverflow(65535);
		uiTimerReset();
		uiTimerEnable();
		uiSetLEDs(currentScale);
		switch (scaleType){
		case rhythm:
			uiSetRGB(orange);
			break;
		case arp:
			uiSetRGB(magenta);
			break;
		case voltOct:
			uiSetRGB(cyan);
			break;
		}
		break;

		case SENSOR_EVENT_SIG:
			if(UPSENSOR == PRESSED){
				uiTransition(&ui_scaleTypeUp);
				break;
			}
			if(DOWNSENSOR == PRESSED){
				uiTransition(&ui_scaleTypeDown);
				break;
			}

			if(SCALESENSOR == RELEASED){
				if (uiTimerRead() < 3000) {
					currentScale = (currentScale + 1) % 4;
					modeStateBuffer = (modeStateBuffer & ~(SCALEMASK)) | (currentScale << SCALESHIFT);
					switchFamily();
					uiSetLEDs(currentScale);
					switch (scaleType){
					case rhythm:
						uiSetRGB(orange);
						break;
					case arp:
						uiSetRGB(magenta);
						break;
					case voltOct:
						uiSetRGB(cyan);
						break;
					}
					uiTransition(&ui_newMode);
				} else {
					uiTransition(&ui_default);
				}
			}
			break;

		case INIT_SIG:
			break;
	}
}

void ui_scaleTypeUp(int sig) {
	switch (sig) {

	case ENTRY_SIG:
		uiTimerReset();
		uiClearLEDs();
		uiTimerSetOverflow(65535);

		break;

	case SENSOR_EVENT_SIG:
		if(UPSENSOR == RELEASED){
			if (uiTimerRead() < 3000) {
				scaleType = (scaleType + 1) % 4;
				currentScale = 0;
				modeStateBuffer = (modeStateBuffer & ~(SCALETYPEMASK)) | (scaleType << SCALETYPESHIFT);
				modeStateBuffer = (modeStateBuffer & ~(SCALEMASK)) | (scaleType << SCALESHIFT);
				switch (scaleType){
				case rhythm:
					uiSetRGB(orange);
					break;
				case arp:
					uiSetRGB(magenta);
					break;
				case voltOct:
					uiSetRGB(cyan);
					break;
				}
				uiTransition(&ui_default);
				break;
			}
		}
		if(SCALESENSOR == RELEASED){
			uiTransition(&ui_default);
			break;
		}
		break;
	}
}

void ui_scaleTypeDown(int sig) {
	switch (sig) {

	case ENTRY_SIG:
		uiTimerReset();
		uiClearLEDs();
		uiTimerSetOverflow(65535);

		break;

	case SENSOR_EVENT_SIG:
		if(UPSENSOR == RELEASED){
			if (uiTimerRead() < 3000) {
				if (scaleType == 0){
					scaleType = 3;
				} else {
					scaleType--;
				}
				currentScale = 0;
				modeStateBuffer = (modeStateBuffer & ~(SCALETYPEMASK)) | (scaleType << SCALETYPESHIFT);
				modeStateBuffer = (modeStateBuffer & ~(SCALEMASK)) | (scaleType << SCALESHIFT);
				switch (scaleType){
				case rhythm:
					uiSetRGB(orange);
					break;
				case arp:
					uiSetRGB(magenta);
					break;
				case voltOct:
					uiSetRGB(cyan);
					break;
				}
				uiTransition(&ui_default);
				break;
			}
		}
		if(SCALESENSOR == RELEASED){
			uiTransition(&ui_default);
			break;
		}
		break;
	}
}


void ui_xMenu(int sig)
{
	switch (sig) {

	case ENTRY_SIG:
		uiTimerSetOverflow(65535);
		uiSetLEDs(controlScheme);
		break;

	case SENSOR_EVENT_SIG:
		// x sensor + scale, sync, & S+H initiate a factory reset (calibration and default presets)
		if (XSENSOR == RELEASED){
			if(uiTimerRead() < 3000){
				controlScheme = (controlScheme + 1) % 4;
				uiSetLEDs(controlScheme);
				uiTransition( &ui_newMode);
			} else {
				uiTransition(&ui_default);
			}

			if ((SCALESENSOR == PRESSED) && (SYNCSENSOR == PRESSED) && (SHSENSOR == PRESSED)){
				uiTransition(&ui_factoryReset);
			}
		}
		break;
	}
}

void ui_autoDutyMenu(int sig){
	switch (sig){
	case ENTRY_SIG:
		uiSetLEDs(autoDuty);
		uiTimerSetOverflow(65535);
		uiTimerReset();
		uiTimerEnable();
		break;

	case SENSOR_EVENT_SIG:
		if (SHSENSOR == RELEASED){
			if (uiTimerRead() < 3000){
				autoDuty = (autoDuty + 1) % 2;
				modeStateBuffer = (modeStateBuffer & ~(AUTODUTYMASK)) | (autoDuty << AUTODUTYSHIFT);
				if (autoDuty == autoDutyOn) {
						CLEAR_AUTODUTY;
					} else {
						SET_AUTODUTY;
					}
				uiSetLEDs(autoDuty);
				uiTransition(&ui_newLogicMode);
			} else {
				uiTransition(&ui_default);
			}
		}
		if (SYNCSENSOR == RELEASED){
			uiTransition(&ui_default);
		}
	}
}

void uiSetRGB(struct rgb color){
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, color.r);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, color.g);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, color.b);
}

void uiClearRGB(){
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);
}

// show a pattern corresponding to a mode 1-8
void uiSetLEDs(int digit){
	switch (digit){
	case 0:
		LEDA_ON;
		LEDB_OFF;
		LEDC_OFF;
		LEDD_OFF;
		break;
	case 1:
		LEDA_OFF;
		LEDB_OFF;
		LEDC_ON;
		LEDD_OFF;
		break;
	case 2:
		LEDA_OFF;
		LEDB_ON;
		LEDC_OFF;
		LEDD_OFF;
		break;
	case 3:
		LEDA_OFF;
		LEDB_OFF;
		LEDC_OFF;
		LEDD_ON;
		break;
	case 4:
		LEDA_ON;
		LEDB_OFF;
		LEDC_ON;
		LEDD_OFF;
		break;
	case 5:
		LEDA_OFF;
		LEDB_ON;
		LEDC_OFF;
		LEDD_ON;
		break;
	case 6:
		LEDA_ON;
		LEDB_ON;
		LEDC_OFF;
		LEDD_OFF;
		break;
	case 7:
		LEDA_OFF;
		LEDB_OFF;
		LEDC_ON;
		LEDD_ON;
		break;
	}
}

void uiClearLEDs(){
	LEDA_OFF;
	LEDB_OFF;
	LEDC_OFF;
	LEDD_OFF;
}

// initialization routine for the UI state machine
void uiInitialize(void)
{
	HAL_FLASH_Unlock();
	eepromStatus = EE_Init();
	HAL_Delay(500);  // init time
	if(eepromStatus != EE_OK) {LEDC_ON;}  // error handling, switch to UI error handling?
	//uiLoadFromEEPROM(0);  // load the most recently stored state from memory

	// load calibration values from virtual EEPROM
	//eepromStatus = EE_ReadVariable(VirtAddVarTab[7], &EEPROMTemp);
	//morphCal = EEPROMTemp >> 8;
	//t2Cal = EEPROMTemp & 0xFF00;
	//eepromStatus |= EE_ReadVariable(VirtAddVarTab[(position * 2) + 1], &EEPROMTemp);
	//t1Cal = EEPROMTemp;


	State = &ui_default;
	uiTransition( &ui_default);
}



void uiLoadFromEEPROM(int position) {
	eepromStatus = EE_ReadVariable(VirtAddVarTab[position * 2], &EEPROMTemp);
	modeStateBuffer = EEPROMTemp;  // load bottom 16 bits
	eepromStatus |= EE_ReadVariable(VirtAddVarTab[(position * 2) + 1], &EEPROMTemp);
	modeStateBuffer |= EEPROMTemp << 16;  // load 16 upper bits
	if (eepromStatus != HAL_OK){
		uiSetLEDs(2);
		uiTransition(&ui_error);
	}
	controlScheme = modeStateBuffer & (XMASK);
	currentScale = (modeStateBuffer & (SCALEMASK)) >> SCALESHIFT;
	scaleType = (modeStateBuffer & (SCALETYPEMASK)) >> SCALETYPESHIFT;
	button4Mode = (modeStateBuffer & (SYNCMASK)) >> SYNCSHIFT;
	sampleHoldMode = (modeStateBuffer & (SHMASK)) >> SHSHIFT;
	familyIndicator = (modeStateBuffer & (FAMILYMASK)) >> FAMILYSHIFT;
	logicOutA = modeStateBuffer & (LOGICAMASK) >> LOGICASHIFT;
	logicOutB = (modeStateBuffer & (LOGICBMASK)) >> LOGICBSHIFT;
	autoDuty = (modeStateBuffer & (AUTODUTYMASK)) >> AUTODUTYSHIFT;


	loadSampleArray();

	/* ... initialization of ui attributes */
	// process the stored modes

	SH_A_TRACK;
	SH_B_TRACK;
	switchFamily();
	if (autoDuty == autoDutyOn) {
		CLEAR_AUTODUTY;
	} else {
		SET_AUTODUTY;
	}
}


// writes 2 16-bit values representing modeState to EEPROM per position,  1 runtime + 6 presets + calibration word
void uiStoreToEEPROM(int position){
	// store lower 16 bits
	eepromStatus = EE_WriteVariable(VirtAddVarTab[position * 2], (uint16_t)modeStateBuffer);
	eepromStatus |= EE_WriteVariable(VirtAddVarTab[(position * 2) + 1], (uint16_t)(modeStateBuffer >> 16));  // make sure i'm shifting in the right direction here!!
	modeStateBuffer |= EEPROMTemp << 16;  //write upper 16 bits
	if (eepromStatus != HAL_OK){
		uiSetLEDs(1);
		uiTransition(&ui_error);
	}
}

// watches for released sensor buttons while TRIG_BUTTON is down.  Loads or stores preset accordingly.
void ui_presetPressedMenu(int sig){
	switch (sig){
	case ENTRY_SIG:
		uiTimerReset();
		uiTimerSetOverflow(10000);
		uiTimerEnable();
		break;

	case SENSOR_EVENT_SIG:
		switch(presetNumber){
		case 1:
			if (SHSENSOR == RELEASED){
				uiLoadFromEEPROM(presetNumber);
				uiTransition(&ui_switchPreset);
			}
			break;
		case 2:
			if (SYNCSENSOR == RELEASED){
				uiLoadFromEEPROM(presetNumber);
				uiTransition(&ui_switchPreset);
			}
			break;
		case 3:
			if (UPSENSOR == RELEASED){
				uiLoadFromEEPROM(presetNumber);
				uiTransition(&ui_switchPreset);
			}
			break;
		case 4:
			if (DOWNSENSOR == RELEASED){
				uiLoadFromEEPROM(presetNumber);
				uiTransition(&ui_switchPreset);
			}
			break;
		case 5:
			if (SCALESENSOR == RELEASED){
				uiLoadFromEEPROM(presetNumber);
				uiTransition(&ui_switchPreset);
			}
			break;
		case 6:
			if (XSENSOR == RELEASED){
				uiLoadFromEEPROM(presetNumber);
				uiTransition(&ui_switchPreset);
			}
			break;
		}
		break;

	case TIMEOUT_SIG:
		uiStoreToEEPROM(presetNumber);
		uiTransition(&ui_newPreset);
		break;


	// if trig button is released, exit menu
	case EXPAND_SW_OFF_SIG:
		uiTransition(&ui_default);
		break;

	case EXIT_SIG:
		break;
	}
}

// displays the new preset was stored by flashing through an LED pattern
void ui_newPreset(int sig){
	static int flashCounter = 0;
	switch (sig){
	case ENTRY_SIG:
		uiTimerReset();
		uiTimerSetOverflow(500);
		uiTimerEnable();
		break;

	case TIMEOUT_SIG:
		if (flashCounter < 16){
			uiTimerEnable();
			flashCounter++;
			uiSetLEDs(flashCounter % 4);
		} else {
			flashCounter = 0;
			uiTransition(&ui_default);
		}
	}
}

void ui_switchPreset(int sig){
	static int flashCounter = 0;
	switch (sig){
	case ENTRY_SIG:
		uiTimerReset();
		uiTimerSetOverflow(500);
		uiTimerEnable();
		break;

	case TIMEOUT_SIG:
		if (flashCounter < 4){
			uiTimerEnable();
			flashCounter++;
			uiSetLEDs(flashCounter % 4);
		} else {
			flashCounter = 0;
			uiTransition(&ui_presetMenu);
		}
	}
}

void ui_presetMenu(int sig)
{
	switch (sig){

	case ENTRY_SIG:
		SET_RUNTIME_DISPLAY;
		uiClearLEDs();
		uiClearRGB();
		uiTimerReset();
		uiTimerDisable();
		break;

	case SENSOR_EVENT_SIG:

		if (SCALESENSOR == PRESSED){
			uiTransition(&ui_presetPressedMenu);
			presetNumber = 5;
		} else if (SHSENSOR == PRESSED){
			uiTransition(&ui_presetPressedMenu);
			presetNumber = 1;
		} else if (SYNCSENSOR == PRESSED){
			uiTransition(&ui_presetPressedMenu);
			presetNumber = 2;
		} else if (XSENSOR == PRESSED){
			uiTransition(&ui_presetPressedMenu);
			presetNumber = 6;
		} else if (UPSENSOR == PRESSED){
			uiTransition(&ui_presetPressedMenu);
			presetNumber = 3;
		} else if (DOWNSENSOR == PRESSED){
			uiTransition(&ui_presetPressedMenu);
			presetNumber = 4;
		}
		break;

	case EXPAND_SW_OFF_SIG:
		uiTransition(&ui_default);
		break;

	case EXIT_SIG:
		CLEAR_RUNTIME_DISPLAY;
		uiClearLEDs();
		uiClearRGB();
		break;

	default:
		break;
	}
}


// calibration and default preset initialization
void ui_factoryReset(int sig){
	static uint16_t tempData;
	switch (sig){
	case ENTRY_SIG:
		uiTimerReset();
		uiTimerSetOverflow(1000);
		uiTimerEnable();
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
	    tempData = (morphCVAverage - 2048) << 8 | ((t2CVAverage - 2048) & 0xFFFFFF00);
		eepromStatus = EE_WriteVariable(VirtAddVarTab[7], tempData);
		eepromStatus |= EE_WriteVariable(VirtAddVarTab[15], (uint16_t)t1CVAverage - 2048);  // make sure i'm shifting in the right direction here!!
		if (eepromStatus != EE_OK){
			uiSetLEDs(4);
			uiTransition(&ui_error);
		} else {
			uiTransition(&ui_default);
		}
	}
}

