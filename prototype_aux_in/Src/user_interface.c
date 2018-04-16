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
enum speedTypes speed; // {audio, env, seq}
enum loopTypes loop; // {noloop, looping}
enum trigModeTypes trigMode; // {noretrigger, hardsync, nongatedretrigger, gated, pendulum}
enum sampleHoldModeTypes sampleHoldMode; // {nosampleandhold, a, b, ab, antidecimate, decimate}
enum logicOutATypes logicOutA; // {triggerA, gateA, deltaA}
enum logicOutBTypes logicOutB; // {triggerB, gateB, deltaB}
enum drumModeTypes drumMode; // {APM, AM, A, M, PM, P}

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
		uiTimerReset();
		uiTimerEnable();
		break;
	}

}

void ui_trigMenu(int sig)
{
	switch (sig)
	{
	case ENTRY_SIG:

		if (TRIGGER_BUTTON){
			presetNumber = 2;
			uiTransition(&ui_presetMenu);
			break;
		}
		if (DRUM_MODE){
			uiTransition(&ui_drumTrigMenu);
		} else {
			uiSetLEDs(trigMode);
		}
		break;

	case SENSOR_EVENT_SIG:

		if (TRIGSENSOR == RELEASED){
			if(uiTimerRead() < 3000){
				trigMode = (trigMode + 1) % 6;
				// initialize some essential retrigger variables
				modeStateBuffer = (modeStateBuffer & !(TRIGMASK)) | (trigMode << TRIGSHIFT);
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
	}
}



void ui_drumTrigMenu(int sig) {
	switch (sig) {

	case ENTRY_SIG:
		uiSetLEDs(drumMode);
		break;

	case SENSOR_EVENT_SIG:

		if (TRIGSENSOR == RELEASED){
			if (uiTimerRead() < 3000) {
				drumMode = (drumMode + 1) % 6;
				modeStateBuffer = (modeStateBuffer & !(DRUMMASK)) | (drumMode << DRUMSHIFT);
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
		uiSetLEDs(logicOutA);
		break;

	case SENSOR_EVENT_SIG:

		if (TRIGSENSOR == RELEASED){
			uiTransition(&ui_default);

		} else if (FREQSENSOR == RELEASED){
			if(uiTimerRead() < 3000){
				logicOutA = (logicOutA + 1) % 3;

				modeStateBuffer = (modeStateBuffer & !(LOGICAMASK)) | (logicOutA << LOGICASHIFT);
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
		uiSetLEDs(logicOutB);
		break;

	case SENSOR_EVENT_SIG:

		if (TRIGSENSOR == RELEASED){
			uiTransition(&ui_default);

		} else if (LOOPSENSOR == RELEASED){
			if(uiTimerRead() < 3000){
				logicOutB = (logicOutB + 1) % 3;
				modeStateBuffer = (modeStateBuffer & !(LOGICBMASK)) | (logicOutB << LOGICBSHIFT);
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
		eepromStatus = EE_WriteVariable(VirtAddVarTab[0], modeStateBuffer);
		eepromStatus |= EE_ReadVariable(VirtAddVarTab[0],  &VarDataTab[0]);
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

void ui_freqMenu(int sig) {
	switch (sig) {

	case ENTRY_SIG:
		if (TRIGGER_BUTTON){
			presetNumber = 5;
			uiTransition(&ui_presetMenu);
			break;
		}
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
		if (TRIGGER_BUTTON){
			presetNumber = 6;
			uiTransition(&ui_presetMenu);
			break;
		}
		uiSetLEDs(sampleHoldMode);
		break;

	case SENSOR_EVENT_SIG:
		if (LOOPSENSOR == RELEASED){

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


void uiClearDrumMode(void){
	CLEAR_AMP_MOD;
	CLEAR_PITCH_MOD;
	CLEAR_MORPH_MOD;
}

// drumMenu just sets drum mode and passes through to newMode
void uiSetDrumMode(void)
{
	SET_DRUM_MODE;
	SET_LAST_CYCLE;
	getPhase = getPhaseDrum;
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

// initialization routine for the UI state machine
void uiInitialize()
{
	HAL_FLASH_Unlock();
	eepromStatus = EE_Init();
	//if(eepromStatus != EE_OK) {LEDC_ON;}  // error handling, switch to UI error handling?
	HAL_Delay(500);  // init time
	uiLoadFromEEPROM(0);  // load the most recently stored state from memory
	/*

	shoudln't be needed but left for reference

	eepromStatus = EE_ReadVariable(VirtAddVarTab[0], &VarDataTab[0]);
	CLEAR_DRUM_MODE;
	modeStateBuffer = VarDataTab[0];
	loop = modeStateBuffer & 0x01;
	speed = (modeStateBuffer & 0x06) >> 1;
	trigMode = (modeStateBuffer & 0x38) >> 3;
	sampleHoldMode = (modeStateBuffer & 0x1C0) >> 6;
	familyIndicator = (modeStateBuffer & 0xE00) >> 9;
	logicOutA = (modeStateBuffer & 0x3000) >> 12;
	logicOutB = (modeStateBuffer & 0xC000) >> 14;
	//drumTrigMode = NOTIMPLEMENTEDYET;

	fillFamilyArray();

	// ... initialization of ui attributes
	// call each menu to initialize, to make UI process the stored modes
	 // processs trig first so it skips possibility of DRUM_MODE_ON_ON
	ui_trigMenu(INIT_SIG);
	ui_loopMenu(INIT_SIG);
	ui_freqMenu(INIT_SIG);
	ui_SampleHoldMenu(INIT_SIG);
	ui_familyUpMenu(INIT_SIG);
	ui_familyDownMenu(INIT_SIG);
	ui_drumTrigMenu(EXIT_SIG);

	if (loop != noloop || speed != audio) {
		uiClearDrumMode();
	}

	// logic A and B don't need additional initialization beyond setting mode
	uiSetPhaseFunctions();
*/

	State = &ui_default;
	uiTransition( &ui_default);
}



void uiLoadFromEEPROM(int position) {
	CLEAR_DRUM_MODE;
	eepromStatus = EE_ReadVariable(VirtAddVarTab[position * 2], &VarDataTab[position * 2]);
	modeStateBuffer = VarDataTab[position * 2] | (VarDataTab[(position * 2) + 1] >> 16);
	loop = modeStateBuffer & LOOPMASK;
	speed = (modeStateBuffer & SPEEDMASK) >> SPEEDSHIFT;
	trigMode = (modeStateBuffer & TRIGMASK) >> TRIGSHIFT;
	sampleHoldMode = (modeStateBuffer & SHMASK) >> SHSHIFT;
	familyIndicator = (modeStateBuffer & FAMILYMASK) >> FAMILYSHIFT;
	logicOutA = (modeStateBuffer & LOGICAMASK) >> LOGICASHIFT;
	logicOutB = (modeStateBuffer & LOGICBMASK) >> LOGICBSHIFT;
	drumMode = (modeStateBuffer & DRUMMASK) >> DRUMSHIFT;

	fillFamilyArray();


	/* ... initialization of ui attributes */
	// call each menu to initialize, to make UI process the stored modes
	// process trig first so it skips possibility of DRUM_MODE
	// logic A and B don't need additional initialization beyond setting mode
	ui_trigMenu(INIT_SIG);
	ui_loopMenu(INIT_SIG);
	ui_freqMenu(INIT_SIG);
	ui_SampleHoldMenu(INIT_SIG);
	ui_switchFamily();
	if (loop = looping && speed == audio) {
		uiSetDrumMode();
	} else {
		uiClearDrumMode();
	}
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
			if (TRIGSENSOR == RELEASED){
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
			if (FREQSENSOR == RELEASED){
				uiLoadFromEEPROM(presetNumber);
			}
			break;
		case 6:
			if (LOOPSENSOR == RELEASED){
				uiLoadFromEEPROM(presetNumber);
			}
			break;

		case TIMER_TIMEOUT:
			uiStoreToEEPROM(presetNumber);
			uiTransition(&ui_newPreset);
			break;
		}
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
