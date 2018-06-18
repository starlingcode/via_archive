#ifndef TEST_H__
#define TEST_H__

#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"
#include "eeprom.h"

uint32_t eepromStatus;

#define UI_TIMER_RESET __HAL_TIM_SET_COUNTER(&htim7, 1);
#define UI_TIMER_DISABLE __HAL_TIM_DISABLE(&htim7);
#define UI_TIMER_ENABLE __HAL_TIM_ENABLE(&htim7);
#define UI_TIMER_SET_OVERFLOW(X) TIM7->ARR = X;
#define UI_TIMER_READ __HAL_TIM_GET_COUNTER(&htim7)

// how modes are arranged by size and location in modeStateBuffer (formatted for EEPROM storage).
#define SH_MASK 		0b00000000000000000000000000000000

#define SYNC_MASK 		0b00000000000000000000000011110000
#define SYNC_SHIFT		4

#define XCV_MASK 		0b00000000000000000000111100000000
#define XCV_SHIFT 		8

#define MORPH_MASK 		0b00000000000000001111000000000000
#define MORPH_SHIFT 	12

#define TABLE_MASK	 	0b00000000000011110000000000000000
#define TABLE_SHIFT	 	16

#define AUX_LOGIC_MASK	0b00000000111100000000000000000000
#define AUX_LOGIC_SHIFT	20



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

// helper functions for the UI
void uiClearLEDs();
void uiSetLEDs(int);
void uiClearRGB();
void uiSetRGB(rgb);

void handleSHModeChange(int);
void handleSHBModeChange(int);
void handleXModeChange(int);
void handleSyncModeChange(int);
void handleMorphModeChange(int);

// UI States
void (*ui_State)(int);

// dispatch a signal to current state
void uiDispatch(int);  // dispatch signal to state

// Main
void ui_default(int sig);
void ui_newMode(int sig);
void ui_error(int sig);

// Button menus
void ui_button4Menu(int sig);
void ui_button1Menu(int sig);
void ui_button2Menu(int sig);
void ui_button5Menu(int sig);
void ui_button3Menu(int sig);
void ui_button6Menu(int sig);
void ui_button6_3Menu(int sig);
void ui_button6SubMenu(int sig);

// Preset menus
void ui_presetMenu(int sig);
void ui_presetPressedMenu(int sig);
void ui_newPreset(int sig);
void ui_switchPreset(int sig);

// Factory reset
void ui_factoryReset(int sig);

// Mode enums and mode variables

enum shModes {none, decimate};
enum syncModes {hard, pendulum};
enum xModes {FM, PM};
enum morphModes {morphCV, pwmCV};


enum shModes shMode;
enum syncModes syncMode;
enum xModes xMode;
enum morphModes morphMode;

int familyIndicator;

// Flag word bit packing macros (stale from a different fimware)

uint32_t flagHolder;

#define TRIGGER_BUTTON 				flagHolder & 0b00000000000000000000000000000001
#define RUNTIME_DISPLAY 			flagHolder & 0b00000000000000000000000000000010
#define TRIGGER_HIGH 				flagHolder & 0b00000000000000000000000000000100
#define LOGIC_B 					flagHolder & 0b00000000000000000000000000001000
#define SAMPLE_A 					flagHolder & 0b00000000000000000000000000010000
#define SAMPLE_B 					flagHolder & 0b00000000000000000000000000100000
#define TRACK_A 					flagHolder & 0b00000000000000000000000001000000
#define TRACK_B 					flagHolder & 0b00000000000000000000000010000000

#define SET_TRIGGER_BUTTON	 		flagHolder |= 0b00000000000000000000000000000001
#define SET_RUNTIME_DISPLAY 		flagHolder |= 0b00000000000000000000000000000010
#define SET_TRIGGER_HIGH 			flagHolder |= 0b00000000000000000000000000000100
#define SET_LOGIC_B	 				flagHolder |= 0b00000000000000000000000000001000
#define SET_SAMPLE_A	 			flagHolder |= 0b00000000000000000000000000010000
#define SET_SAMPLE_B	 			flagHolder |= 0b00000000000000000000000000100000
#define SET_TRACK_A	 				flagHolder |= 0b00000000000000000000000001000000
#define SET_TRACK_B	 				flagHolder |= 0b00000000000000000000000010000000



#define CLEAR_TRIGGER_BUTTON 		flagHolder &= 0b11111111111111111111111111111110
#define CLEAR_RUNTIME_DISPLAY 		flagHolder &= 0b11111111111111111111111111111101
#define CLEAR_TRIGGER_HIGH	 		flagHolder &= 0b11111111111111111111111111111011
#define CLEAR_LOGIC_B	 			flagHolder &= 0b11111111111111111111111111110111
#define CLEAR_SAMPLE_A	 			flagHolder &= 0b11111111111111111111111111101111
#define CLEAR_SAMPLE_B	 			flagHolder &= 0b11111111111111111111111111011111
#define CLEAR_TRACK_A	 			flagHolder &= 0b11111111111111111111111110111111
#define CLEAR_TRACK_B	 			flagHolder &= 0b11111111111111111111111101111111




#endif /* TEST_H__*/

