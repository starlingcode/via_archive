#include "main.h"
#include "tsl_user.h"
#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"
#include "eeprom.h"
#include "user_interface.h"
#include "hardware_io.h"
#include "patterns.h"

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim4;

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

enum {
	DAC_GATE_HIGH,
	DAC_GATE_LOW,
	DAC_EXECUTE,
};

enum shAModes shAMode;
enum shBModes shBMode;
enum andAModes andAMode;
enum andBModes andBMode;
int patternBankIndex;

// holds the mode state as a EEPROM-formatted value.
uint32_t modeStateBuffer;

// this holds the read 16-bit EEPROM data while it gets shifted and recomposed into modeStateBuffer.
uint16_t EEPROMTemp;

// used by state machine to signal preset to be stored or recalled.
int presetNumber;


struct rgb {
	int r;
	int b;
	int g;
};

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


// these could be rolled into smarter functions instead that do what we most often need?
// e.g. always reset then enable, or always set overflow then reset then enable?

static inline void uiTimerReset() { __HAL_TIM_SET_COUNTER(&htim4, 1); }
static inline void uiTimerDisable() { __HAL_TIM_DISABLE(&htim4); }
static inline void uiTimerEnable() { __HAL_TIM_ENABLE(&htim4); }
static inline int uiTimerRead() { return __HAL_TIM_GET_COUNTER(&htim4); }  // return needed?
static inline void uiTimerSetOverflow(int val) { TIM4->ARR = val; }

void uiStoreToEEPROM(int);
void uiLoadFromEEPROM(int);

// a pointer to these functions is the current state
void ui_default(int sig);
void ui_newMode(int sig);
void ui_button4Menu(int sig);
void ui_button4_3Menu(int sig);
void ui_button4_6Menu(int sig);
void ui_button1Menu(int sig);
void ui_button2Menu(int sig);
void ui_button5Menu(int sig);
void ui_button3Menu(int sig);
void ui_button6Menu(int sig);
void ui_button4SubMenu(int sig);
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

		if (BUTTON3SENSOR == PRESSED){
			uiTransition(&ui_button3Menu);

		} else if (BUTTON1SENSOR == PRESSED){
			uiTransition(&ui_button1Menu);

		} else if (BUTTON4SENSOR == PRESSED){
			uiTransition(&ui_button4Menu);

		} else if (BUTTON6SENSOR == PRESSED){
			uiTransition(&ui_button6Menu);

		} else if (BUTTON2SENSOR == PRESSED){
			uiTransition(&ui_button2Menu);

		} else if (BUTTON5SENSOR == PRESSED){
			uiTransition(&ui_button5Menu);
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
		CLEAR_RUNTIME_DISPLAY;
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

		if (BUTTON3SENSOR == PRESSED){
			uiTransition( &ui_button3Menu);

		} else if (BUTTON1SENSOR == PRESSED){
			uiTransition( &ui_button1Menu);

		} else if (BUTTON4SENSOR == PRESSED){
			uiTransition( &ui_button4Menu);

		} else if (BUTTON6SENSOR == PRESSED){
			uiTransition( &ui_button6Menu);

		} else if (BUTTON2SENSOR == PRESSED){
			uiTransition( &ui_button2Menu);

		} else if (BUTTON5SENSOR == PRESSED){
			uiTransition( &ui_button5Menu);
		}
		break;

	case EXIT_SIG:
		uiClearLEDs();
		uiClearRGB();
		break;
	}

}


void ui_button1Menu(int sig)
{
	switch (sig)
	{
	case ENTRY_SIG:
		uiTimerReset();
		uiTimerSetOverflow(65535);
		uiTimerEnable();
		uiSetLEDs(shAMode);
		break;

	case SENSOR_EVENT_SIG:
		if (BUTTON1SENSOR == RELEASED){
			if(uiTimerRead() < 3000){
				shAMode = (shAMode + 1) % 3;
				modeStateBuffer = (modeStateBuffer & ~(SH_A_MASK)) | shAMode;
				switch (shAMode) {
					case aSHOff:
						CLEAR_SAMPLE_A;
						CLEAR_TRACK_A;
						SH_A_TRACK;
						break;
					case aResample:
						SET_SAMPLE_A;
						CLEAR_TRACK_A;
						break;
					case aSampleTrack:
						SET_SAMPLE_A;
						SET_TRACK_A;
						break;
					default:
						break;
				}
				uiSetLEDs(shAMode);
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

void ui_button4Menu(int sig)
{
	switch (sig)
	{
	case ENTRY_SIG:
		uiTimerReset();
		uiTimerSetOverflow(65535);
		uiTimerEnable();
		uiSetLEDs(shBMode);

		break;

	case SENSOR_EVENT_SIG:

		if (BUTTON4SENSOR == RELEASED){
			if(uiTimerRead() < 3000){
				shBMode = (shBMode + 1) % 3;
				// initialize some essential retrigger variables
				modeStateBuffer = (modeStateBuffer & ~(SH_B_MASK)) | (andAMode << SH_B_SHIFT);
				switch (shBMode) {
					case bSHOff:
						CLEAR_SAMPLE_B;
						CLEAR_TRACK_B;
						SH_B_TRACK;
						break;
					case bResample:
						SET_SAMPLE_B;
						CLEAR_TRACK_B;
						break;
					case bSampleTrack:
						SET_SAMPLE_B;
						SET_TRACK_B;
						break;
					default:
						break;
				}
				uiSetLEDs(shBMode);
				uiTransition(&ui_newMode);
			} else {
				//no mode change
				uiTransition(&ui_default);
			}

		}
		break;

	case INIT_SIG:
		break;

	default:
		break;
	}

}


void ui_button2Menu(int sig)
{
	switch (sig)
	{
	case ENTRY_SIG:

		uiTimerReset();
		uiTimerSetOverflow(65535);
		uiTimerEnable();
		uiSetLEDs(patternBankIndex);
		break;

	case SENSOR_EVENT_SIG:
		if (BUTTON2SENSOR == RELEASED){
			if(uiTimerRead() < 3000){
				patternBankIndex = (patternBankIndex + 1) % 8;
				modeStateBuffer = (modeStateBuffer & ~(BANK_MASK)) | (patternBankIndex << BANK_SHIFT);
				currentBank = patternBanks[patternBankIndex];
				uiSetLEDs(patternBankIndex);
				uiTransition( &ui_newMode);
			} else {
				uiTransition( &ui_default);
			}
		}
		break;
	}
}

void ui_button5Menu(int sig)
{
	switch (sig)
	{
	case ENTRY_SIG:
		uiTimerReset();
		uiTimerSetOverflow(65535);
		uiTimerEnable();
		uiSetLEDs(patternBankIndex);
		break;

	case SENSOR_EVENT_SIG:
		if (BUTTON5SENSOR == RELEASED){
			if(uiTimerRead() < 3000){
				if (patternBankIndex == 0) {
					patternBankIndex = 7;  // wrap around
				} else {
					patternBankIndex--;
				}
				modeStateBuffer = (modeStateBuffer & ~(BANK_MASK)) | (patternBankIndex << BANK_SHIFT);
				currentBank = patternBanks[patternBankIndex];
				uiSetLEDs(patternBankIndex);
				uiTransition( &ui_newMode);
			} else {
				uiTransition(&ui_default);
			}
		}
		break;
	}
}

void ui_button3Menu(int sig) {
	switch (sig) {

	case ENTRY_SIG:
		uiSetLEDs(andAMode);
		uiTimerReset();
		uiTimerSetOverflow(65535);
		uiTimerEnable();
		break;

	case SENSOR_EVENT_SIG:
		if(BUTTON3SENSOR == RELEASED){
			if (uiTimerRead() < 3000) {
				andAMode = (andAMode + 1) % 2;
				modeStateBuffer = AND_A_MASK | (andAMode << AND_A_MASK);
				if (andAMode != 0) {
					SET_AND_A;
				} else {
					CLEAR_AND_A;
					manageADac(DAC_GATE_HIGH);
				}
				uiSetLEDs(andAMode);
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


void ui_button6Menu(int sig)
{
	switch (sig) {

	case ENTRY_SIG:
		uiTimerReset();
		uiTimerSetOverflow(65535);
		uiTimerEnable();
		uiSetLEDs(andBMode);
		break;

	case SENSOR_EVENT_SIG:
		if (BUTTON6SENSOR == RELEASED){

			if(uiTimerRead() < 3000){
				andBMode = (andBMode + 1) % 2;
				modeStateBuffer = (modeStateBuffer & ~(AND_B_MASK)) | (andBMode << AND_B_SHIFT);
				if (andBMode != 0) {
					SET_AND_B;
				} else {
					CLEAR_AND_B;
					manageBDac(DAC_GATE_HIGH);
				}
				uiClearLEDs();
				uiSetLEDs(andBMode);
				uiTransition( &ui_newMode);
			} else {
				uiTransition(&ui_default);
			}

			if ((BUTTON4SENSOR == PRESSED) && (BUTTON1SENSOR == PRESSED) && (BUTTON3SENSOR == PRESSED)){
				uiTransition(&ui_factoryReset);
			}
		}
		break;

	case INIT_SIG:
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
	initializePatterns();

	HAL_FLASH_Unlock();
	eepromStatus = EE_Init();

	// error handling
	if(eepromStatus != EE_OK) {
		uiSetLEDs(3);
		uiTransition(&ui_error);
	}

	HAL_Delay(500);  // init time
	uiLoadFromEEPROM(0);  // load the most recently stored state from memory



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

	shAMode = modeStateBuffer & SH_A_MASK;
	shBMode = (modeStateBuffer & SH_B_MASK) >> SH_B_SHIFT;
	andAMode = (modeStateBuffer & AND_A_MASK) >> AND_A_SHIFT;
	andBMode = (modeStateBuffer & AND_A_MASK) >> AND_B_SHIFT;
	patternBankIndex = (modeStateBuffer & BANK_MASK) >> BANK_SHIFT;



	/* ... initialization of ui attributes */
	// call each menu to initialize, to make UI process the stored modes

	currentBank = patternBanks[patternBankIndex];


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
			if (BUTTON1SENSOR == RELEASED){
				uiLoadFromEEPROM(presetNumber);
				uiTransition(&ui_switchPreset);
			}
			break;
		case 2:
			if (BUTTON4SENSOR == RELEASED){
				uiLoadFromEEPROM(presetNumber);
				uiTransition(&ui_switchPreset);
			}
			break;
		case 3:
			if (BUTTON2SENSOR == RELEASED){
				uiLoadFromEEPROM(presetNumber);
				uiTransition(&ui_switchPreset);
			}
			break;
		case 4:
			if (BUTTON5SENSOR == RELEASED){
				uiLoadFromEEPROM(presetNumber);
				uiTransition(&ui_switchPreset);
			}
			break;
		case 5:
			if (BUTTON3SENSOR == RELEASED){
				uiLoadFromEEPROM(presetNumber);
				uiTransition(&ui_switchPreset);
			}
			break;
		case 6:
			if (BUTTON6SENSOR == RELEASED){
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

		if (BUTTON3SENSOR == PRESSED){
			uiTransition(&ui_presetPressedMenu);
			presetNumber = 3;
		} else if (BUTTON1SENSOR == PRESSED){
			uiTransition(&ui_presetPressedMenu);
			presetNumber = 1;
		} else if (BUTTON4SENSOR == PRESSED){
			uiTransition(&ui_presetPressedMenu);
			presetNumber = 4;
		} else if (BUTTON6SENSOR == PRESSED){
			uiTransition(&ui_presetPressedMenu);
			presetNumber = 6;
		} else if (BUTTON2SENSOR == PRESSED){
			uiTransition(&ui_presetPressedMenu);
			presetNumber = 2;
		} else if (BUTTON5SENSOR == PRESSED){
			uiTransition(&ui_presetPressedMenu);
			presetNumber = 5;
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


