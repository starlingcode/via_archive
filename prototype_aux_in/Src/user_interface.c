#include "tables.h"
#include "main.h"
#include "tsl_user.h"
#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"
#include "interrupt_functions.h"
#include "eeprom.h"
#include "int64.h"
#include "fsm.h"

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

// these variables are passed between globally to public functions
extern uint32_t modeFlag;

void changeMode(uint32_t);
void showMode(uint32_t);
void clearLEDs(void);
void switchFamily(void);
void loadSampleArray(Family);

uint32_t modeStateBuffer;  // replaces global modeStateBuffer

int sig;

struct rgb uiColor;

struct rgb red = {4095, 0, 0};
struct rgb green = {0, 4095, 0};
struct rgb blue = {0, 0, 4095};

void (*State)(int);
void uiInitialize(void);

// a pointer to these functions is the current state
void uidefault(int sig);

void uinewMode(int sig);
void uitrigMenu(int sig);
void uilogicAMenu(int sig);
void uilogicBMenu(int sig);
void uiSampleHoldMenu(int sig);
void uifamilyUpMenu(int sig);
void uifamilyDownMenu(int sig);
void uifreqMenu(int sig);
void uiloopMenu(int sig);
void uidrumTrigMenu(int sig);
void uinewLogicMode(int sig);

void uiSetFreq(void);
void uiSetPhaseFunctions(void);

void uiSetDrumMode(void);
void uiClearDrumMode(void);


void uiClearLEDs();
void uiSetLEDs(int digit);
void uiClearRGB();
void uiSetRGB(struct rgb);


//might change these to make them more targeted to specific needs.
static inline void uiTimerReset() { __HAL_TIM_SET_COUNTER(&htim4, 0); }
static inline void uiTimerDisable() { __HAL_TIM_DISABLE(&htim4); }
static inline void uiTimerEnable() { __HAL_TIM_ENABLE(&htim4); }
static inline int uiTimerRead() { return __HAL_TIM_GET_COUNTER(&htim4); }  // return needed?
static inline void uiTimerSet(int val) { __HAL_TIM_SET_COUNTER(&htim4, val); }

void uiDispatch(int sig) {(*State)(sig);}  // dispatch signal to state

// transition to new state
void uiTransition(void (*func)(int)) {
	uiDispatch(EXIT_SIG);
	State = func;
	uiDispatch(ENTRY_SIG);
}


// default runtime state,  handles launching menus on detect, and turning runtime  display back on upon entry.
void uidefault(int sig)
{
	switch (sig){

	case ENTRY_SIG:
		uiClearLEDs();
		uiClearRGB();
		uiTimerDisable();
		SET_DISPLAY_RUNTIME;
		break;

	case SENSOR_EVENT_SIG:

		if (FREQSENSOR == PRESSED){
			uiTransition(&uifreqMenu);

		} else if (SHSENSOR == PRESSED){
			uiTransition(&uiSampleHoldMenu);

		} else if (TRIGSENSOR == PRESSED){
			uiTransition(&uitrigMenu);

		} else if (LOOPSENSOR == PRESSED){
			uiTransition(&uiloopMenu);

		} else if (UPSENSOR == PRESSED){
			uiTransition(&uifamilyUpMenu);

		} else if (DOWNSENSOR == PRESSED){
			uiTransition(&uifamilyDownMenu);
		}
		break;

	case EXIT_SIG:
		RESET_DISPLAY_RUNTIME;
		uiClearLEDs();
		uiClearRGB();
		uiTimerReset();
		uiTimerEnable();
		break;
	}
}

// catches error states and gives display feedback
void uierror(int sig){
}




// newMode state is transitioned into after a mode change, writes to EEPROM and maintains mode display until timeout.
void uinewMode(int sig)
{
	switch (sig)
	{
	case ENTRY_SIG:
		uiTimerReset();  // start count over
		eepromStatus = EE_WriteVariable(VirtAddVarTab[0], modeStateBuffer);
		eepromStatus |= EE_ReadVariable(VirtAddVarTab[0],  &VarDataTab[0]);
		break;

	// once uiTimerRead() times out, clear display and return to default state
	case TIMEOUT_SIG:
		if (uiTimerRead() > 10000)
		uiTransition(&uidefault);
		break;

	// in case of new events immediately jump to relevant menu
	case SENSOR_EVENT_SIG:

		if (FREQSENSOR == PRESSED){
			uiTransition( &uifreqMenu);

		} else if (SHSENSOR == PRESSED){
			uiTransition( &uiSampleHoldMenu);

		} else if (TRIGSENSOR == PRESSED){
			uiTransition( &uitrigMenu);

		} else if (LOOPSENSOR == PRESSED){
			uiTransition( &uiloopMenu);

		} else if (UPSENSOR == PRESSED){
			uiTransition( &uifamilyUpMenu);

		} else if (DOWNSENSOR == PRESSED){
			uiTransition( &uifamilyDownMenu);
		}
		break;
	case EXIT_SIG:
		RESET_DISPLAY_RUNTIME;
		uiClearLEDs();
		uiClearRGB();
		uiTimerReset();
		uiTimerEnable();
		break;
	}

}

void uitrigMenu(int sig)
{
	switch (sig)
	{
	case ENTRY_SIG:
		if (DRUM_MODE_ON){
			uiTransition(&uidrumTrigMenu);
		} else {
			uiSetLEDs(trigMode);
		}
		break;

	case SENSOR_EVENT_SIG:

		if (TRIGSENSOR == RELEASED){
			if(uiTimerRead() < 3000){
				trigMode = (trigMode + 1) % 6;
				// initialize some essential retrigger variables
				modeStateBuffer = (modeStateBuffer & 0b1111111111000111) | (trigMode << 3);
				incSign = 1;
				RESET_GATE_ON;
				// if drum mode is on, toggle through sets of modulation destinations
				uiClearLEDs();
				uiSetLEDs(trigMode);
				uiTransition(&uinewMode);
			} else {
				//no mode change
				uiTransition(&uidefault);
			}

		} else if (FREQSENSOR == PRESSED){
			// descend into submenu
			uiTransition(&uilogicAMenu);

		} else if (LOOPSENSOR == PRESSED){
			// descend into submenu
			uiTransition(&uilogicBMenu);
		}
		break;

	case INIT_SIG:
		// initialize some essential retrigger variables
		incSign = 1;
		RESET_GATE_ON;

	}
}



void uidrumTrigMenu(int sig) {
	switch (sig) {

	case ENTRY_SIG:
		uiSetLEDs(drumMode);
		break;

	case SENSOR_EVENT_SIG:

		if (TRIGSENSOR == RELEASED){
			if (uiTimerRead() < 3000) {
				drumMode = (drumMode + 1) % 6;
				uiClearLEDs();
				uiSetLEDs(drumMode);
				uiTransition(&uinewMode);
			} else {
				uiTransition(&uidefault);
			}

		} else if (FREQSENSOR == PRESSED){
			uiTransition(&uilogicAMenu);

		} else if (LOOPSENSOR == PRESSED){
			uiTransition(&uilogicBMenu);
		}
		break;

	// on exit we always set drum flags since it doesn't affect any other mode
	case EXIT_SIG:
		uiSetDrumMode();
	}

}


void uilogicAMenu(int sig)
{
	switch (sig)
	{
	case ENTRY_SIG:
		uiTimerReset();  // start count over for submenus
		uiSetLEDs(logicOutA);
		break;

	case SENSOR_EVENT_SIG:

		if (TRIGSENSOR == RELEASED){
			uiTransition(&uidefault);

		} else if (FREQSENSOR == RELEASED){
			if(uiTimerRead() < 3000){
				logicOutA = (logicOutA + 1) % 3;
				uiClearLEDs();
				uiSetLEDs(logicOutA);
				uiTransition(&uinewLogicMode);

			} else {
				uiTransition(&uidefault);  // fall all the way back to default instead of allowing a trig modechange
			}

		} else if (LOOPSENSOR == PRESSED){
			uiTransition(&uilogicBMenu);  // should we even allow this case?  more chances of bumped buttons?
		}
	}
}

void uilogicBMenu(int sig)
{
	switch (sig)
	{
	case ENTRY_SIG:
		uiTimerReset();  // start count over for submenus
		uiSetLEDs(logicOutB);
		break;

	case SENSOR_EVENT_SIG:

		if (TRIGSENSOR == RELEASED){
			uiTransition(&uidefault);

		} else if (LOOPSENSOR == RELEASED){
			if(uiTimerRead() < 3000){
				logicOutB = (logicOutB + 1) % 3;
				uiClearLEDs();
				uiSetLEDs(logicOutB);
				uiTransition(&uinewLogicMode);

			} else {
				uiTransition(&uidefault);
			}

		} else if (FREQSENSOR == PRESSED){
			uiTransition(&uilogicAMenu);
		}
	}
}

// special newMode which only accepts additional presses on FREQ or LOOP, and returns to newMode on TRIG release.
// for cycling through logicOut modes.  Does not time out.
void uinewLogicMode(int sig)
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
			uiTransition( &uilogicAMenu);

		} else if (LOOPSENSOR == PRESSED){
			uiTransition( &uilogicBMenu);

		} else if (TRIGSENSOR == RELEASED){
			uiTransition( &uinewMode);
		}

		break;
	}
}

void uiSampleHoldMenu(int sig)
{
	switch (sig)
	{
	case ENTRY_SIG:
		uiSetLEDs(sampleHoldMode);
		break;

	case SENSOR_EVENT_SIG:
		if (SHSENSOR == RELEASED){
			if(uiTimerRead() < 3000){
				sampleHoldMode = (sampleHoldMode + 1) % 6;
				modeStateBuffer = (modeStateBuffer & 0b1111111000111111) | (sampleHoldMode << 6);
				SH_A_TRACK;  // ensure that there's no carryover holding by forcing tracking
				SH_B_TRACK;
				uiClearLEDs();
				uiSetLEDs(sampleHoldMode);
				uiTransition(&uinewMode);
			} else {
				uiTransition(&uidefault);
			}
		}
		break;

	case INIT_SIG:
		SH_A_TRACK;
		SH_B_TRACK;
		break;
	}
}


void uifamilyUpMenu(int sig)
{
	switch (sig)
	{
	case ENTRY_SIG:
		uiSetLEDs(familyIndicator);
		uiSetRGB(currentFamily.color);
		break;

	case SENSOR_EVENT_SIG:
		if (UPSENSOR == RELEASED){
			if(uiTimerRead() < 3000){
				familyIndicator = (familyIndicator + 1) % 8;
				switchFamily();
				modeStateBuffer = (modeStateBuffer & 0b1111000111111111) | (familyIndicator << 9);
				uiClearLEDs();
				uiSetLEDs(familyIndicator);
				uiSetRGB(currentFamily.color);
				uiTransition( &uinewMode);
			} else {
				uiTransition( &uidefault);
			}
		}
		break;
	}
}

void uifamilyDownMenu(int sig)
{
	switch (sig)
	{
	case ENTRY_SIG:
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
				modeStateBuffer = (modeStateBuffer & 0b1111000111111111) | (familyIndicator << 9);
				uiClearLEDs();
				uiSetLEDs(familyIndicator);
				uiSetRGB(currentFamily.color);
				uiTransition( &uinewMode);
			} else {
				uiTransition(&uidefault);
			}
		}
		break;
	}
}

void uifreqMenu(int sig) {
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
		break;

	case SENSOR_EVENT_SIG:
		if(FREQSENSOR == RELEASED){
			if (uiTimerRead() < 3000) {
				speed = (speed + 1) % 3;
				modeStateBuffer = (modeStateBuffer & 0b1111111111111001) | (speed << 1);
				switchFamily();
				uiSetPhaseFunctions();
			}
			uiClearLEDs();
			uiSetLEDs(speed);
			uiTransition(&uinewMode);
		} else {
			uiTransition(&uidefault);
		}
		break;

	case INIT_SIG:
		//uiSetFreq();
		break;
	}
}


void uiloopMenu(int sig)
{
	switch (sig) {

	case ENTRY_SIG:
		uiSetLEDs(sampleHoldMode);
		break;

	case SENSOR_EVENT_SIG:
		if (LOOPSENSOR == RELEASED){

			if(uiTimerRead() < 3000){

				loop = (loop + 1) % 2;
				modeStateBuffer = (modeStateBuffer & 0b1111111111111110) | loop;
				if (loop == noloop) {
					SET_LAST_CYCLE;
				}
				else {
					RESET_DRUM_MODE_ON;
					RESET_LAST_CYCLE;
					SET_OSCILLATOR_ACTIVE;
				}
				uiClearLEDs();
				uiSetLEDs(loop);
				uiSetPhaseFunctions();
				uiTransition( &uinewMode);
			} else {
				uiTransition(&uidefault);
			}
		}
		break;
	}
}



// drumMenu just sets drum mode and passes through to newMode
void uiSetDrumMode(void)
{
	SET_DRUM_MODE_ON;
	SET_LAST_CYCLE;
	getPhase = getPhaseDrum;
	__HAL_TIM_ENABLE(&htim3);
	switch (drumMode) {
	case APM:
		SET_AMP_ON;
		SET_PITCH_ON;
		SET_MORPH_ON;
		break;
	case AM:
		SET_AMP_ON;
		RESET_PITCH_ON;
		SET_MORPH_ON;
		break;
	case A:
		SET_AMP_ON;
		RESET_PITCH_ON;
		RESET_MORPH_ON;
		break;
	case M:
		RESET_AMP_ON;
		RESET_PITCH_ON;
		SET_MORPH_ON;
		break;
	case PM:
		RESET_AMP_ON;
		SET_PITCH_ON;
		SET_MORPH_ON;
		break;
	case P:
		RESET_AMP_ON;
		SET_PITCH_ON;
		RESET_MORPH_ON;
		break;
	default:
		break;
	}
}

void uiSetPhaseFunctions(void) {
	switch (speed) {
	// set the appropriate time calculation functions
	case env:
		RESET_DRUM_MODE_ON;
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
			RESET_DRUM_MODE_ON;
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

void uiClearRGB(struct rgb color){
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);
}

// show a pattern corresponding to a mode 1-8
void uiSetLEDs(int digit){
	RESET_DISPLAY_RUNTIME;
	switch (digit){
	case 0:
		LEDA_ON;
		break;
	case 1:
		LEDC_ON;
		break;
	case 2:
		LEDB_ON;
		break;
	case 3:
		LEDD_ON;
		break;
	case 4:
		LEDA_ON;
		LEDC_ON;
		break;
	case 5:
		LEDB_ON;
		LEDD_ON;
		break;
	case 6:
		LEDA_ON;
		LEDB_ON;
		break;
	case 7:
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
	eepromStatus = EE_ReadVariable(VirtAddVarTab[0], &VarDataTab[0]);
	RESET_DRUM_MODE_ON;
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

	/* ... initialization of ui attributes */
	// call each menu to initialize, to make UI process the stored modes
	 // processs trig first so it skips possibility of DRUM_MODE_ON_ON
	uitrigMenu(INIT_SIG);
	uiloopMenu(INIT_SIG);
	uifreqMenu(INIT_SIG);
	uiSampleHoldMenu(INIT_SIG);
	uifamilyUpMenu(INIT_SIG);
	uifamilyDownMenu(INIT_SIG);
	uidrumTrigMenu(EXIT_SIG);
	// logic A and B don't need additional initialization beyond setting mode
	uiSetPhaseFunctions();

	State = &uidefault;
	uiTransition( &uidefault);
}

