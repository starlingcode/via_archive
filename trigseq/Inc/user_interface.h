#ifndef TEST_H__
#define TEST_H__

#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"
#include "eeprom.h"

uint32_t eepromStatus;

#define BUTTON1SENSOR MyTKeys[4].p_Data->StateId
#define BUTTON2SENSOR MyTKeys[5].p_Data->StateId
#define BUTTON3SENSOR MyTKeys[3].p_Data->StateId
#define BUTTON4SENSOR MyTKeys[2].p_Data->StateId
#define BUTTON5SENSOR MyTKeys[0].p_Data->StateId
#define BUTTON6SENSOR MyTKeys[1].p_Data->StateId

#define PRESSED TSL_STATEID_DETECT
#define RELEASED TSL_STATEID_RELEASE

#define UI_TIMER_RESET __HAL_TIM_SET_COUNTER(&htim4, 1);
#define UI_TIMER_DISABLE __HAL_TIM_DISABLE(&htim4);
#define UI_TIMER_ENABLE __HAL_TIM_ENABLE(&htim4);
#define UI_TIMER_SET_OVERFLOW(X) TIM4->ARR = X;
#define UI_TIMER_READ __HAL_TIM_GET_COUNTER(&htim4)

// how modes are arranged by size and location in modeStateBuffer (formatted for EEPROM storage).
#define SH_A_MASK 		0b00000000000000000000000000000000

#define SH_B_MASK 		0b00000000000000000000000011110000
#define SH_B_SHIFT		4

#define AND_A_MASK 		0b00000000000000000000111100000000
#define AND_A_SHIFT 	8

#define AND_B_MASK 		0b00000000000000001111000000000000
#define AND_B_SHIFT 	12

#define BANK_MASK	 	0b00000000000011110000000000000000
#define BANK_SHIFT	 	16

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

void uiChangeSHAMode(int mode);
void uiChangeSHBMode(int mode);
void uiChangeGrid(int mode);
void uiChangeAndAMode(int mode);
void uiChangeAndBMode(int mode);
void uiChangeAuxLogicMode(int mode);

// UI States
void (*State)(int);

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

#endif /* TEST_H__*/

