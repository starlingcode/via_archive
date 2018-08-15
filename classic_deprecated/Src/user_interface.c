
#ifndef UI_HEADER
#define UI_HEADER

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

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;

// these enums contain our mode information
enum speedTypes speed; // {audio, env, seq}
enum loopTypes loop; // {noloop, looping}
enum trigModeTypes trigMode; // {noretrigger, hardsync, nongatedretrigger, gated, pendulum}
enum sampleHoldModeTypes sampleHoldMode; // {nosampleandhold, a, b, ab, antidecimate, decimate}
enum logicOutATypes logicOutA; // {triggerA, gateA, deltaA}
enum logicOutBTypes logicOutB; // {triggerB, gateB, deltaB}
enum drumModeTypes drumMode; // {APM, AM, A, M, PM, P}

uint32_t morphCVAverage;
uint32_t t1CVAverage;
uint32_t t2CVAverage;

extern uint16_t VirtAddVarTab[NB_OF_VAR];

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

// holds the mode state as a EEPROM-formatted value.
uint32_t modeStateBuffer;

// this holds the read 16-bit EEPROM data while it gets shifted and recomposed into modeStateBuffer.
uint16_t EEPROMTemp;

// used by state machine to signal preset to be stored or recalled.
int presetNumber;

// shortcuts for commonly used colors!
struct rgb red = {4095, 0, 0};
struct rgb green = {0, 4095, 0};
struct rgb blue = {0, 0, 4095};
struct rgb orange = {4095, 4095, 0};
struct rgb magenta = {4095, 0, 4095};
struct rgb cyan = {0, 4095, 4095};

uint32_t morphCal;
uint32_t t1Cal;
uint32_t t2Cal;

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


// these could be rolled into smarter functions instead that do what we most often need?
// e.g. always reset then enable, or always set overflow then reset then enable?

static inline void uiTimerReset() { __HAL_TIM_SET_COUNTER(&htim4, 1); }
static inline void uiTimerDisable() { __HAL_TIM_DISABLE(&htim4); }
static inline void uiTimerEnable() { __HAL_TIM_ENABLE(&htim4); }
static inline int uiTimerRead() { return __HAL_TIM_GET_COUNTER(&htim4); }  // return needed?
static inline void uiTimerSet(int val) { __HAL_TIM_SET_COUNTER(&htim4, val); }  // this is unused, will we ever need it?
static inline void uiTimerSetOverflow(int val) { TIM4->ARR = val; }

void uiStoreToEEPROM(int);
void uiLoadFromEEPROM(int);

// a pointer to these functions is the current state
void ui_default(int sig);
void ui_newMode(int sig);
void ui_trigMenu(int sig);
void ui_logicAMenu(int sig);
void ui_logicBMenu(int sig);
void ui_SampleHoldMenu(int sig);
void ui_familyUpMenu(int sig);
void ui_familyDownMenu(int sig);
void ui_freqMenu(int sig);
void ui_loopMenu(int sig);
void ui_drumTrigMenu(int sig);
void ui_newLogicMode(int sig);
void ui_error(int sig);
void ui_presetMenu(int sig);
void ui_presetPressedMenu(int sig);
void ui_newPreset(int sig);
void ui_switchPreset(int sig);
void ui_factoryReset(int sig);

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

		if (FREQSENSOR == PRESSED){
			uiTransition(&ui_freqMenu);

		} else if (SHSENSOR == PRESSED){
			uiTransition(&ui_SampleHoldMenu);

		} else if (TRIGSENSOR == PRESSED){
			uiTransition(&ui_trigMenu);

		} else if (LOOPSENSOR == PRESSED){
			uiTransition(&ui_loopMenu);

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
		CLEAR_RUNTIME_DISPLAY;
		uiClearLEDs();
		uiClearRGB();
		break;


	default:
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
		uiTimerReset();
		uiTimerSetOverflow(10000);
		uiTimerEnable();
		break;

	// once uiTimerRead() times out, clear display and return to default state
	case TIMEOUT_SIG:
		uiTransition(&ui_default);
		break;

	case EXPAND_SW_ON_SIG:
		uiTransition(&ui_presetMenu);
		break;

	// in case of new events immediately jump to relevant menu
	case SENSOR_EVENT_SIG:

		if (FREQSENSOR == PRESSED){
			uiTransition( &ui_freqMenu);

		} else if (SHSENSOR == PRESSED){
			uiTransition( &ui_SampleHoldMenu);

		} else if (TRIGSENSOR == PRESSED){
			uiTransition( &ui_trigMenu);

		} else if (LOOPSENSOR == PRESSED){
			uiTransition( &ui_loopMenu);

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
		break;
	}

}

void ui_trigMenu(int sig)
{
	switch (sig)
	{
	case ENTRY_SIG:

//		if (TRIGGER_BUTTON){
//			presetNumber = 2;
//			uiTransition(&ui_presetMenu);
//			break;
//		}
		if (loop == noloop && speed == audio){
			uiTransition(&ui_drumTrigMenu);
		} else {
			uiSetLEDs(trigMode);
			uiTimerReset();
			uiTimerSetOverflow(65535);
			uiTimerEnable();
		}
		break;

	case SENSOR_EVENT_SIG:

		if (TRIGSENSOR == RELEASED){
			if(uiTimerRead() < 3000){
				trigMode = (trigMode + 1) % 6;
				// initialize some essential retrigger variables
				modeStateBuffer = (modeStateBuffer & ~(TRIGMASK)) | (trigMode << TRIGSHIFT);
				incSign = 1;
				CLEAR_GATE;
				// if drum mode is on, toggle through sets of modulation destinations
				uiSetLEDs(trigMode);
				uiTransition(&ui_newMode);
			} else {
				//no mode change
				uiTransition(&ui_default);
			}

		} else if (FREQSENSOR == PRESSED){
			// descend into submenu
			uiTransition(&ui_logicAMenu);

		} else if (LOOPSENSOR == PRESSED){
			// descend into submenu
			uiTransition(&ui_logicBMenu);
		}
		break;

	case INIT_SIG:
		// initialize some essential retrigger variables
		incSign = 1;
		CLEAR_GATE;
		break;

	default:
		break;
	}

}



void ui_drumTrigMenu(int sig) {
	switch (sig) {

	case ENTRY_SIG:
		uiSetLEDs(drumMode);
		uiTimerReset();
		uiTimerSetOverflow(65535);
		uiTimerEnable();
		break;

	case SENSOR_EVENT_SIG:

		if (TRIGSENSOR == RELEASED){
			if (uiTimerRead() < 3000) {
				drumMode = (drumMode + 1) % 6;
				modeStateBuffer = (modeStateBuffer & ~(DRUMMASK)) | (drumMode << DRUMSHIFT);
				uiSetLEDs(drumMode);
				uiTransition(&ui_newMode);
			} else {
				uiTransition(&ui_default);
			}

		} else if (FREQSENSOR == PRESSED){
			uiTransition(&ui_logicAMenu);

		} else if (LOOPSENSOR == PRESSED){
			uiTransition(&ui_logicBMenu);
		}
		break;

	// on exit we always set drum flags since it doesn't affect any other mode
	case EXIT_SIG:
		uiSetDrumMode();
		break;
	}
}


void ui_logicAMenu(int sig)
{
	switch (sig)
	{
	case ENTRY_SIG:
		uiTimerReset();  // start count over for submenus
		uiTimerSetOverflow(65535);
		uiTimerEnable();
		uiSetLEDs(logicOutA);

		break;

	case SENSOR_EVENT_SIG:

		if (TRIGSENSOR == RELEASED){
			uiTransition(&ui_default);

		} else if (FREQSENSOR == RELEASED){
			if(uiTimerRead() < 3000){
				logicOutA = (logicOutA + 1) % 3;

				modeStateBuffer = (modeStateBuffer & ~(LOGICAMASK)) | (logicOutA << LOGICASHIFT);
				uiSetLEDs(logicOutA);
				uiTransition(&ui_newLogicMode);

			} else {
				uiTransition(&ui_default);  // fall all the way back to default instead of allowing a trig modechange
			}

		} else if (LOOPSENSOR == PRESSED){
			uiTransition(&ui_logicBMenu);  // should we even allow this case?  more chances of bumped buttons?
		}
	}
}

void ui_logicBMenu(int sig)
{
	switch (sig)
	{
	case ENTRY_SIG:
		uiTimerReset();  // start count over for submenus
		uiTimerSetOverflow(65535);
		uiTimerEnable();
		uiSetLEDs(logicOutB);
		break;

	case SENSOR_EVENT_SIG:

		if (TRIGSENSOR == RELEASED){
			uiTransition(&ui_default);

		} else if (LOOPSENSOR == RELEASED){
			if(uiTimerRead() < 3000){
				logicOutB = (logicOutB + 1) % 3;
				modeStateBuffer = (modeStateBuffer & ~(LOGICBMASK)) | (logicOutB << LOGICBSHIFT);
				uiSetLEDs(logicOutB);
				uiTransition(&ui_newLogicMode);

			} else {
				uiTransition(&ui_default);
			}

		} else if (FREQSENSOR == PRESSED){
			uiTransition(&ui_logicAMenu);  // don't make this transition maybe??
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
		uiTimerDisable();
		uiStoreToEEPROM(0);  // store in preset 0 (current state)
		break;

	// once uiTimerRead() times out, clear display and return to default state

	case SENSOR_EVENT_SIG:

		if (FREQSENSOR == PRESSED){
			uiTransition( &ui_logicAMenu);

		} else if (LOOPSENSOR == PRESSED){
			uiTransition( &ui_logicBMenu);

		} else if (TRIGSENSOR == RELEASED){
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
//		if (TRIGGER_BUTTON){
//			presetNumber = 1;
//			uiTransition(&ui_presetMenu);
//			break;
//		}
		uiTimerReset();
		uiTimerSetOverflow(65535);
		uiTimerEnable();
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

		uiTimerReset();
		uiTimerSetOverflow(65535);
		uiTimerEnable();
		uiSetLEDs(familyIndicator);
		uiSetRGB(currentFamily.color);
		break;

	case SENSOR_EVENT_SIG:
		if (UPSENSOR == RELEASED){
			if(uiTimerRead() < 3000){
				familyIndicator = (familyIndicator + 1) % 8;
				switchFamily();
				modeStateBuffer = (modeStateBuffer & ~(FAMILYMASK)) | (familyIndicator << FAMILYSHIFT);
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
//		if (TRIGGER_BUTTON){
//			presetNumber = 4;
//			uiTransition(&ui_presetMenu);
//			break;
//		}
		uiTimerReset();
		uiTimerSetOverflow(65535);
		uiTimerEnable();
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
				modeStateBuffer = (modeStateBuffer & ~(FAMILYMASK)) | (familyIndicator << FAMILYSHIFT);
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

void ui_freqMenu(int sig) {
	switch (sig) {

	case ENTRY_SIG:
		uiSetLEDs(speed);
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
		uiTimerReset();
		uiTimerSetOverflow(65535);
		uiTimerEnable();
		break;

	case SENSOR_EVENT_SIG:
		if(FREQSENSOR == RELEASED){
			if (uiTimerRead() < 3000) {
				speed = (speed + 1) % 3;
				modeStateBuffer = (modeStateBuffer & 0b1111111111111001) | (speed << 1);
				switchFamily();
				uiSetPhaseFunctions();
				uiSetLEDs(speed);
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


void ui_loopMenu(int sig)
{
	switch (sig) {

	case ENTRY_SIG:
		uiTimerReset();
		uiTimerSetOverflow(65535);
		uiTimerEnable();
		uiSetLEDs(loop);
		break;

	case SENSOR_EVENT_SIG:
		if (LOOPSENSOR == RELEASED){

			if(uiTimerRead() < 3000){
				loop = (loop + 1) % 2;
				modeStateBuffer = (modeStateBuffer & ~(LOOPMASK)) | loop;

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

			if ((TRIGSENSOR == PRESSED) && (SHSENSOR == PRESSED) && (FREQSENSOR == PRESSED)){
				uiTransition(&ui_factoryReset);
			}
		}
		break;

	case INIT_SIG:
		if (loop == noloop) {
			SET_LAST_CYCLE;
			CLEAR_OSCILLATOR_ACTIVE;
		}
		else {
			CLEAR_DRUM_MODE;
			CLEAR_LAST_CYCLE;
			SET_OSCILLATOR_ACTIVE;
		}
		break;
	}
}


void uiClearDrumMode(void){
	CLEAR_AMP_MOD;
	CLEAR_PITCH_MOD;
	CLEAR_MORPH_MOD;
	CLEAR_DRUM_MODE;
}

// drumMenu just sets drum mode and passes through to newMode
void uiSetDrumMode(void)
{
	SET_DRUM_SAFETY;
	SET_DRUM_MODE;
	getPhase = getPhaseDrum;
	SET_LAST_CYCLE;
	__HAL_TIM_ENABLE(&htim3);
	switch (drumMode) {
	case APM:
		SET_AMP_MOD;
		SET_PITCH_MOD;
		SET_MORPH_MOD;
		break;
	case AM:
		SET_AMP_MOD;
		CLEAR_PITCH_MOD;
		SET_MORPH_MOD;
		break;
	case A:
		SET_AMP_MOD;
		CLEAR_PITCH_MOD;
		CLEAR_MORPH_MOD;
		break;
	case M:
		CLEAR_AMP_MOD;
		CLEAR_PITCH_MOD;
		SET_MORPH_MOD;
		break;
	case PM:
		CLEAR_AMP_MOD;
		SET_PITCH_MOD;
		SET_MORPH_MOD;
		break;
	case P:
		CLEAR_AMP_MOD;
		SET_PITCH_MOD;
		CLEAR_MORPH_MOD;
		break;
	}
	CLEAR_DRUM_SAFETY;
}

void uiSetPhaseFunctions(void) {
	switch (speed) {
	// set the appropriate time calculation functions
	case env:
		uiClearDrumMode();
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
		//releaseTime = calcTime2Seq;
		if (loop) {
			getPhase = getPhaseComplexLFO;
		} else {
			getPhase = getPhaseComplexEnv;
		}
		break;

	case audio:
		if (loop == noloop) {
			uiSetDrumMode();
			TIM6->ARR = 750;
		} else {
			getPhase = getPhaseOsc;
			uiClearDrumMode();
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

// initialization routine for the UI state machine
void uiInitialize()
{
	HAL_FLASH_Unlock();
	eepromStatus = EE_Init();

	// error handling
	if(eepromStatus != EE_OK) {
		uiSetLEDs(3);
		uiTransition(&ui_error);
	}

	HAL_Delay(500);  // init time
	//uiLoadFromEEPROM(0);  // load the most recently stored state from memory

	eepromStatus = EE_ReadVariable(VirtAddVarTab[7], &EEPROMTemp);
	morphCal = EEPROMTemp >> 8;
	t2Cal = EEPROMTemp & 0xFF00;
	eepromStatus |= EE_ReadVariable(VirtAddVarTab[(position * 2) + 1], &EEPROMTemp);
	t1Cal = EEPROMTemp;

	SH_A_TRACK;
	SH_B_TRACK;

	incSign = 1;

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


	loop = modeStateBuffer & LOOPMASK;
	speed = (modeStateBuffer & SPEEDMASK) >> SPEEDSHIFT;
	trigMode = (modeStateBuffer & TRIGMASK) >> TRIGSHIFT;
	sampleHoldMode = (modeStateBuffer & SHMASK) >> SHSHIFT;
	familyIndicator = (modeStateBuffer & FAMILYMASK) >> FAMILYSHIFT;
	logicOutA = (modeStateBuffer & LOGICAMASK) >> LOGICASHIFT;
	logicOutB = (modeStateBuffer & LOGICBMASK) >> LOGICBSHIFT;
	drumMode = (modeStateBuffer & DRUMMASK) >> DRUMSHIFT;
	fillFamilyArray();
	switchFamily();

	/* ... initialization of ui attributes */
	// call each menu to initialize, to make UI process the stored modes
	// process trig first so it skips possibility of DRUM_MODE
	// logic A and B don't need additional initialization beyond setting mode
	ui_trigMenu(INIT_SIG);
	ui_loopMenu(INIT_SIG);
	ui_freqMenu(INIT_SIG);
	ui_SampleHoldMenu(INIT_SIG);
}

// writes 2 16-bit values representing modeState to EEPROM per position,  1 runtime + 6 presets + calibration word
void uiStoreToEEPROM(int position){
	// store lower 16 bits
	eepromStatus = EE_WriteVariable(VirtAddVarTab[position * 2], (uint16_t)modeStateBuffer);
	eepromStatus |= EE_WriteVariable(VirtAddVarTab[(position * 2) + 1], (uint16_t)modeStateBuffer >> 16);  // make sure i'm shifting in the right direction here!!

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
			if (TRIGSENSOR == RELEASED){
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
			if (FREQSENSOR == RELEASED){
				uiLoadFromEEPROM(presetNumber);
				uiTransition(&ui_switchPreset);
			}
			break;
		case 6:
			if (LOOPSENSOR == RELEASED){
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
			if (TRIGGER_BUTTON) {
				uiTransition(&ui_presetMenu);
			} else {
				uiTransition(&ui_default);
			}
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

		if (FREQSENSOR == PRESSED){
			uiTransition(&ui_presetPressedMenu);
			presetNumber = 5;
		} else if (SHSENSOR == PRESSED){
			uiTransition(&ui_presetPressedMenu);
			presetNumber = 1;
		} else if (TRIGSENSOR == PRESSED){
			uiTransition(&ui_presetPressedMenu);
			presetNumber = 2;
		} else if (LOOPSENSOR == PRESSED){
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

#endif