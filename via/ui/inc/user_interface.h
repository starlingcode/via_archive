
#ifdef __cplusplus
extern "C" {
#endif

#ifndef USER_INTERFACE_H__
#define USER_INTERFACE_H__


#include "via_platform_binding.h"
#include "tsl_user.h"
#include "eeprom.h"

//TSL_TouchKey_T MyTKeys[6];
tsl_user_status_t tsl_status;

uint32_t eepromStatus;

#define UI_TIMER_RESET __HAL_TIM_SET_COUNTER(&htim7, 1);
#define UI_TIMER_DISABLE __HAL_TIM_DISABLE(&htim7);
#define UI_TIMER_ENABLE __HAL_TIM_ENABLE(&htim7);
#define UI_TIMER_SET_OVERFLOW(X) TIM7->ARR = X;
#define UI_TIMER_READ __HAL_TIM_GET_COUNTER(&htim7)

// how modes are arranged by size and location in modeStateBuffer (formatted for EEPROM storage).
#define BUTTON1_MASK 		0b00000000000000000000000000000111

#define BUTTON2_MASK 		0b00000000000000000000000000111000
#define BUTTON2_SHIFT		3

#define BUTTON3_MASK 		0b00000000000000000000000111000000
#define BUTTON3_SHIFT 		6

#define BUTTON4_MASK 		0b00000000000000000000111000000000
#define BUTTON4_SHIFT 		9

#define BUTTON5_MASK	 	0b00000000000000000111000000000000
#define BUTTON5_SHIFT	 	12

#define BUTTON6_MASK		0b00000000000000111000000000000000
#define BUTTON6_SHIFT		15

#define AUX_MODE1_MASK		0b00000000000111000000000000000000
#define AUX_MODE1_SHIFT		18

#define AUX_MODE2_MASK		0b00000000111000000000000000000000
#define AUX_MODE2_SHIFT		21

#define AUX_MODE3_MASK		0b00000111000000000000000000000000
#define AUX_MODE3_SHIFT		24

#define AUX_MODE4_MASK		0b00111000000000000000000000000000
#define AUX_MODE4_SHIFT		27

#define DEFAULTPRESET1 0b0000000000000000
#define DEFAULTPRESET2 0b0000000000000000
#define DEFAULTPRESET3 0b0000000000000000
#define DEFAULTPRESET4 0b0000000000000000
#define DEFAULTPRESET5 0b0000000000000000
#define DEFAULTPRESET6 0b0000000000000000

// holds the mode state as a EEPROM-formatted value.
uint32_t modeStateBuffer;

// this holds the read 16-bit EEPROM data while it gets shifted and recomposed into modeStateBuffer.
uint16_t EEPROMTemp;

// used by state machine to signal preset to be stored or recalled.
int presetNumber;

typedef struct {
	int r;
	int b;
	int g;
} rgb;

// shortcuts for commonly used colors as macro defines of rgb struct values
#define red {4095, 0, 0};
#define green {0, 4095, 0};
#define blue {0, 0, 4095};
#define orange {4095, 4095, 0};
#define magenta {4095, 0, 4095};
#define cyan {0, 4095, 4095};

uint32_t morphCal;
uint32_t t1Cal;
uint32_t t2Cal;

// initial setup of UI
void uiInitialize(void);
void uiLoadFromEEPROM(int);
void uiStoreToEEPROM(int);

// UI States
void (*ui_State)(int);

// dispatch a signal to current state
void uiDispatch(int);  // dispatch signal to state
void uiTransition(void (*func)(int));

// Main
void ui_default(int sig);
void ui_newMode(int sig);
void ui_newAuxMode(int sig);
void ui_error(int sig);

// Button menus
void ui_button4Menu(int sig);
void ui_button1Menu(int sig);
void ui_button2Menu(int sig);
void ui_button5Menu(int sig);
void ui_button3Menu(int sig);
void ui_button6Menu(int sig);
void ui_aux1Menu(int sig);
void ui_aux2Menu(int sig);
void ui_aux3Menu(int sig);
void ui_aux4Menu(int sig);

// Preset menus
void ui_presetMenu(int sig);
void ui_presetPressedMenu(int sig);
void ui_newPreset(int sig);
void ui_switchPreset(int sig);

// Factory reset
void ui_factoryReset(int sig);

void (*button1TapCallback)(void);
void (*button1HoldCallback)(void);
void (*button2TapCallback)(void);
void (*button2HoldCallback)(void);
void (*button3TapCallback)(void);
void (*button3HoldCallback)(void);
void (*button4TapCallback)(void);
void (*button4HoldCallback)(void);
void (*button5TapCallback)(void);
void (*button5HoldCallback)(void);
void (*button6TapCallback)(void);
void (*button6HoldCallback)(void);

void (*aux1TapCallback)(void);
void (*aux1HoldCallback)(void);
void (*aux2TapCallback)(void);
void (*aux2HoldCallback)(void);
void (*aux3TapCallback)(void);
void (*aux3HoldCallback)(void);
void (*aux4TapCallback)(void);
void (*aux4HoldCallback)(void);

void (*button1EnterMenuCallback)(void);
void (*button2EnterMenuCallback)(void);
void (*button3EnterMenuCallback)(void);
void (*button4EnterMenuCallback)(void);
void (*button5EnterMenuCallback)(void);
void (*button6EnterMenuCallback)(void);

void (*aux1EnterMenuCallback)(void);
void (*aux2EnterMenuCallback)(void);
void (*aux3EnterMenuCallback)(void);
void (*aux4EnterMenuCallback)(void);

void initializeUICallbacks(void);

int button1Mode;
int button2Mode;
int button3Mode;
int button4Mode;
int button5Mode;
int button6Mode;
int aux1Mode;
int aux2Mode;
int aux3Mode;
int aux4Mode;

// helper functions for the UI
void uiClearLEDs();
void uiSetLEDs(int);
void uiClearRGB();
void uiSetRGB(rgb);

void uiStaticLEDHandler();
void (*uiSetLEDA)();
void (*uiSetLEDB)();
void (*uiSetLEDC)();
void (*uiSetLEDD)();

void uiSetLEDAOn();
void uiSetLEDAOff();
void uiSetLEDBOn();
void uiSetLEDBOff();
void uiSetLEDCOn();
void uiSetLEDCOff();
void uiSetLEDDOn();
void uiSetLEDDOff();

int incrementModeAndStore(int, int, int);
int decrementModeAndStore(int, int, int);
static inline void uiResetTimerMenu(void) {
	UI_TIMER_RESET
	;
	UI_TIMER_SET_OVERFLOW(65535);
	UI_TIMER_ENABLE
	;
}

// TODO HALF ASSED
uint32_t runtimeDisplay;
#define SET_RUNTIME_DISPLAY runtimeDisplay = 1
#define CLEAR_RUNTIME_DISPLAY runtimeDisplay = 0
#define RUNTIME_DISPLAY runtimeDisplay

#ifdef __cplusplus
}
#endif

#endif /* USER_INTERFACE_H__*/

