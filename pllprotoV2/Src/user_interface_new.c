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
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;

// these enums contain our mode information
enum syncTypes syncMode; // {none, true, hardSync, catch}
enum controlSchemes controlScheme; // {gateLength, knobCV}
enum scaleTypes scaleType; // {rhythm, pitch, other}
enum sampleHoldModeTypes sampleHoldMode; // {nosampleandhold, a, b, ab, antidecimate, decimate}
enum logicOutATypes logicOutA; // {triggerA, gateA, deltaA, ratioDeltaA, pllClock};
enum logicOutBTypes logicOutB; // {triggerB, gateB, deltaB, ratioDeltaB, pllClock};
enum autoDutyTypes autoDuty; // {autoDutyOn, autoDutyOff};


extern uint16_t VirtAddVarTab[NB_OF_VAR];
extern uint16_t VarDataTab[NB_OF_VAR];

// holds the mode state as a EEPROM-formatted value.
uint32_t modeStateBuffer;

void switchFamily(void);

// variable that holds an address to current state function
void (*State)(int);

//used by state machine to signal preset to be stored or recalled.
int presetNumber;


// initial setup of UI
void uiInitialize(void);
void uiLoadFromEEPROM(int);
void uiStoreToEEPROM(int);

// helper functions for the UI
void uiClearLEDs();
void uiSetLEDs(int digit);
void uiClearRGB();
void uiSetRGB(struct rgb);

void uiSetPhaseFunctions(void);
void uiSetDrumMode(void);
void uiClearDrumMode(void);

static inline void uiTimerReset() { __HAL_TIM_SET_COUNTER(&htim4, 0); }
static inline void uiTimerDisable() { __HAL_TIM_DISABLE(&htim4); }
static inline void uiTimerEnable() { __HAL_TIM_ENABLE(&htim4); }
static inline int uiTimerRead() { return __HAL_TIM_GET_COUNTER(&htim4); }  // return needed?
static inline void uiTimerSet(int val) { __HAL_TIM_SET_COUNTER(&htim4, val); }

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
void ui_xMenu(int sig);
void ui_error(int sig);
void ui_presetMenu(int sig);
void ui_newPreset(int sig);


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
		CLEAR_RUNTIME_DISPLAY;
		uiClearLEDs();
		uiClearRGB();
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

	case EXIT_SIG:
		uiClearLEDs();
		uiClearRGB();
		SET_RUNTIME_DISPLAY;
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
		uiTimerReset();  // start count over
		uiStoreToEEPROM(0);
		break;

	// once uiTimerRead() times out, clear display and return to default state
	case TIMEOUT_SIG:
		if (uiTimerRead() > 10000)
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

		if (TRIGGER_BUTTON){
			presetNumber = 2;
			uiTransition(&ui_presetMenu);
			break;
		}
			uiSetLEDs(syncMode);
		}
		break;

	case SENSOR_EVENT_SIG:

		if (SYNCSENSOR == RELEASED){
			if(uiTimerRead() < 3000){
				syncMode = (syncMode + 1) % 3;
				//modeStateBuffer = (holdState & 0b1111111111000111) | (syncMode << 3);
				modeStateBuffer = (holdState & !(SYNCFLAG)) | (syncMode << SYNCSHIFT);
				// if drum mode is on, toggle through sets of modulation destinations
				uiSetLEDs(syncMode);
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
		break;

	case SENSOR_EVENT_SIG:

		if (SYNCSENSOR == RELEASED){
			uiTransition(&ui_default);

		} else if (SCALESENSOR == RELEASED){
			if(uiTimerRead() < 3000){
				logicOutA = (logicOutA + 1) % 5;
				//holdLogicOut = (holdLogicOut & 0b1111111111111000) | logicOutA;
				modeStateBuffer = (modeStateBuffer & !(LOGICAMASK) | logicOutA << LOGICASHIFT);

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
					CLEAR_RATIO_DELTAA;
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
			CLEAR_RATIO_DELTAA;
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
		break;

	case SENSOR_EVENT_SIG:

		if (SYNCSENSOR == RELEASED){
			uiTransition(&ui_default);
			break;

		} else if (XSENSOR == RELEASED){
			if(uiTimerRead() < 3000){
				logicOutB = (logicOutB + 1) % 5;
				modeStateBuffer = (modeStateBuffer & !(LOGICBMASK)) | (logicOutB << LOGICBSHIFT);
				//holdLogicOut = (holdLogicOut & 0b1111111111000111) | (logicOutB << 3);
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
					CLEAR_RATIO_DELTAB;
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
			CLEAR_RATIO_DELTAB;
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

		if (SCALESENSOR == PRESSED){
			uiTransition( &ui_logicAMenu);

		} else if (XSENSOR == PRESSED){
			uiTransition( &ui_logicBMenu);

		} else if (SYNCSENSOR == RELEASED){
			uiTransition( &ui_newMode);
		}

		break;
	}
}

void ui_SampleHoldMenu(int sig)
{
	switch (sig)
	{
	case ENTRY_SIG:
		if (TRIGGER_BUTTON){
			presetNumber = 1
			uiTransition(&ui_presetMenu);
			break;
		}
		uiSetLEDs(sampleHoldMode);
		break;

	case SENSOR_EVENT_SIG:
		if (SHSENSOR == RELEASED){
			if(uiTimerRead() < 3000){
				sampleHoldMode = (sampleHoldMode + 1) % 6;
				modeStateBuffer = (modeStateBuffer & !(SHMASK)) | (sampleHoldMode << SHSHIFT);
				SH_A_TRACK;  // ensure that there's no carryover holding by forcing tracking
				SH_B_TRACK;
\				uiSetLEDs(sampleHoldMode);
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
		if (TRIGGER_BUTTON){
			presetNumber = 3;
			uiTransition(&ui_presetMenu);
			break;
		}
		uiSetLEDs(familyIndicator);
		uiSetRGB(currentFamily.color);
		break;

	case SENSOR_EVENT_SIG:
		if (UPSENSOR == RELEASED){
			if(uiTimerRead() < 3000){
				familyIndicator = (familyIndicator + 1) % 8;
				switchFamily();
				modeStateBuffer = (modeStateBuffer & !(FAMILYMASK)) | (familyIndicator << TRIGSHIFT);
				uiSetLEDs(familyIndicator);
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
		if (TRIGGER_BUTTON){
			presetNumber = 4;
			uiTransition(&ui_presetMenu);
			break;
		}
		uiSetLEDs(familyIndicator);
		uiSetRGB(currentFamily.color);
		break;

	case SENSOR_EVENT_SIG:
		if (DOWNSENSOR == RELEASED){
			if(uiTimerRead() < 3000){
				if (familyIndicator == 0) {
					familyIndicator = 7;  // wrap around
				} else {
					familyIndicator--;
				}
				switchFamily();
				modeStateBuffer = (modeStateBuffer & !(FAMILYMASK)) | (familyIndicator << TRIGSHIFT);
				uiSetLEDs(familyIndicator);
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
		if (TRIGGER_BUTTON){
			presetNumber = 5;
			uiTransition(&ui_presetMenu);
			break;
		}
		uiSetLEDs(scale);
		switch (scale){
		case rhythm:
			uiSetRGB(red);
			break;
		case pitch:
			uiSetRGB(green);
			break;
		case other:
			uiSetRGB(blue);
			break;
		}
		break;

	case SENSOR_EVENT_SIG:
		if(SCALESENSOR == RELEASED){
			if (uiTimerRead() < 3000) {
				speed = (speed + 1) % 3;
				modeStateBuffer = (modeStateBuffer & 0b1111111111111001) | (speed << 1);
				switchFamily();
				uiSetPhaseFunctions();
				uiSetLEDs(scale);
				switch (speed){
				case audio:
					uiSetRGB(red);
					break;
				case env:
					uiSetRGB(green);
					break;
				case seq:
					uiSetRGB(blue);
					break;
				}
				uiTransition(&ui_newMode);
			} else {
				uiTransition(&ui_default);
			}
		}
		break;

	case INIT_SIG:
		switchFamily();
		uiSetPhaseFunctions();
		break;
	}
}


void ui_xMenu(int sig)
{
	switch (sig) {

	case ENTRY_SIG:
		if (TRIGGER_BUTTON){
			presetNumber = 6;
			uiTransition(&ui_presetMenu);
			break;
		}
		uiSetLEDs(sampleHoldMode);
		break;

	case SENSOR_EVENT_SIG:
		if (XSENSOR == RELEASED){

			if(uiTimerRead() < 3000){
				loop = (loop + 1) % 2;
				modeStateBuffer = (modeStateBuffer & !(LOOPMASK)) | loop;

				if (loop == noloop) {
					SET_LAST_CYCLE;
				}
				else {
					CLEAR_DRUM_MODE;
					CLEAR_LAST_CYCLE;
					SET_OSCILLATOR_ACTIVE;
				}
				uiClearLEDs();
				uiSetLEDs(loop);
				uiSetPhaseFunctions();
				uiTransition( &ui_newMode);
			} else {
				uiTransition(&ui_default);
			}
		}
		break;

	case INIT_SIG:
		if (loop == noloop) {
			SET_LAST_CYCLE;
		}
		else {
			CLEAR_DRUM_MODE;
			CLEAR_LAST_CYCLE;
			SET_OSCILLATOR_ACTIVE;
		}
		break;
	}
}

void ui_autoDutyMenu(int sig){
	switch (sig){
	case ENTRY_SIG:
		uiSetLEDs(autoDuty);
		break;

	case SENSOR_EVENT_SIG:
		if (SHSENSOR == RELEASED){
			if (uiTimerRead() < 3000){
				autoDuty = (autoDuty + 1) % 2;
				modeStateBuffer = (modeStateBuffer & !(AUTODUTYMASK) | (autoDuty << AUTODUTYSHIFT);
				if (autoDuty == autoDutyOn) {
						CLEAR_AUTODUTY;
					} else {
						SET_AUTODUTY;
					}
				uiSetLEDs(autoDuty);
				uiTransition(&ui_newMode);
			} else {
				uiTransition(&ui_syncMenu);
			}
		}
		if (SYNCSENSOR == RELEASED){
			uiTransition(&ui_default);
		}
	}
}


void uiSetPhaseFunctions(void) {
	switch (speed) {
	// set the appropriate time calculation functions
	case env:
		CLEAR_DRUM_MODE;
		TIM6->ARR = 750;
		attackTime = calcTime1Env;
		releaseTime = calcTime2Env;
		if (loop) {
			getPhase = getPhaseSimpleLFO;
		} else {
			getPhase = getPhaseSimpleEnv;
		}
		break;

	case seq:
		TIM6->ARR = 1000;
		attackTime = calcTime1Seq;
		releaseTime = calcTime2Seq;
		if (loop) {
			getPhase = getPhaseComplexLFO;
		} else {
			getPhase = getPhaseComplexEnv;
		}
		break;

	case audio:
		if (loop == noloop) {
			TIM6->ARR = 750;
			uiSetDrumMode();
		} else {
			getPhase = getPhaseOsc;
			CLEAR_DRUM_MODE;
			TIM6->ARR = 750;
		}
		break;
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
eepromStatus = EE_ReadVariable(VirtAddVarTab[0], &VarDataTab[0]);
holdState = VarDataTab[0];
eepromStatus = EE_ReadVariable(VirtAddVarTab[1], &VarDataTab[1]);
holdLogicOut = VarDataTab[1];



// initialization routine for the UI state machine
void uiInitialize()
{
	HAL_FLASH_Unlock();
	eepromStatus = EE_Init();
	//if(eepromStatus != EE_OK) {LEDC_ON;}  // error handling, switch to UI error handling?
	HAL_Delay(500);  // init time
	uiLoadFromEEPROM(0);  // load the most recently stored state from memory




	State = &ui_default;
	uiTransition( &ui_default);
}



void uiLoadFromEEPROM(int position) {

	eepromStatus = EE_ReadVariable(VirtAddVarTab[position * 2], &VarDataTab[position * 2]);
	modeStateBuffer = VarDataTab[position * 2] | (VarDataTab[(position * 2) + 1] >> 16);
	controlScheme = modeStateBuffer & !(XMASK);
	scaleType = (modeStateBuffer & !(SCALEMASK)) >> SCALESHIFT;
	syncMode = (modeStateBuffer & !(SYNCMASK)) >> SYNCSHIFT;
	sampleHoldMode = (modeStateBuffer & !(SHMASK)) >> SHSHIFT;
	familyIndicator = (modeStateBuffer & !(FAMILYMASK)) >> FAMILYSHIFT;
	logicOutA = modeStateBuffer & !(LOGICAMASK) >> LOGICASHIFT;
	logicOutB = (modeStateBuffer & !(LOGICAMASK)) >> LOGICASHIFT;

	fillFamilyArray();

	/* ... initialization of ui attributes */
	// call each menu to initialize, to make UI process the stored modes
	// process trig first so it skips possibility of DRUM_MODE
	// logic A and B don't need additional initialization beyond setting mode
	ui_pllMenu(INIT_SIG);
	ui_xMenu(INIT_SIG);
	ui_scaleMenu(INIT_SIG);
	ui_SampleHoldMenu(INIT_SIG);
	ui_autoDutyMenu(INIT_SIG);
	switchFamily();
	ui_logicAMenu(INIT_SIG);
	ui_logicBMenu(INIT_SIG);
	uiSetPhaseFunctions();

}

// writes 2 16-bit values representing modeState to EEPROM per position,  1 runtime + 6 presets + calibration word
void uiStoreToEEPROM(int position){

	eepromStatus = EE_WriteVariable(VirtAddVarTab[position * 2], (uint16_t)modeStateBuffer);
	eepromStatus |= EE_ReadVariable(VirtAddVarTab[position * 2],  &VarDataTab[position * 2]);

	eepromStatus = EE_WriteVariable(VirtAddVarTab[(position * 2) + 1], (uint16_t)modeStateBuffer >> 16);
	eepromStatus |= EE_ReadVariable(VirtAddVarTab[(position * 2) + 1],  &VarDataTab[0]);
}

// watches for released sensor buttons while TRIG_BUTTON is down.  Loads or stores preset accordingly.
void ui_presetMenu(int sig){
	switch (sig){
	case ENTRY_SIG:
		uiTimerSet(30000);
		uiTimerReset();
		break;

	case SENSOR_EVENT_SIG:
		switch(presetNumber){
		case 1:
			if (SHSENSOR == RELEASED){
				loadFromEEPROM(presetNumber);
			}
			break;
		case 2:
			if (SYNCSENSOR == RELEASED){
				uiLoadFromEEPROM(presetNumber);
			}
			break;
		case 3:
			if (UPSENSOR == RELEASED){
				uiLoadFromEEPROM(presetNumber);
			}
			break;
		case 4:
			if (DOWNSENSOR == RELEASED){
				uiLoadFromEEPROM(presetNumber);
			}
			break;
		case 5:
			if (SCALESENSOR == RELEASED){
				uiLoadFromEEPROM(presetNumber);
			}
			break;
		case 6:
			if (XSENSOR == RELEASED){
				uiLoadFromEEPROM(presetNumber);
			}
			break;

		case TIMER_TIMEOUT:
			uiStoreToEEPROM(presetNumber);
			uiTransition(&ui_newPreset);
			break;
		}
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
		uiTimerSet(500);
		uiTimerReset();
		break;

	case TIMER_TIMEOUT:
		if (flashCounter < 16){
			uiTimerReset();
			uiSetLEDs(flashCounter % 4);
		} else {
			flashCounter = 0;
			uiTransition(&ui_default);
		}
	}
}
