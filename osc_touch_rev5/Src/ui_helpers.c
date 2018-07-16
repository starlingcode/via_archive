#include "main.h"
#include "tsl_user.h"
#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"
#include "user_interface.h"
#include "dsp.h"
#include "main_state_machine.h"
#include "via_rev5_hardware_io.h"

// RGB led timer
TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim4;
TIM_HandleTypeDef htim5;

/**
 *
 * Mode change helpers
 *
 */

void handleButton1ModeChange(int mode) {


	switch (mode) {
	case none:
		logicAndFilter = &logicAndFilterSHOff;
		displaySHMode = &displaySH_Off;
		break;
	case decimate:
		logicAndFilter = &logicAndFilterSHOn;
		displaySHMode = &displaySH_On;
		break;
	}

	SH_A_TRACK;
	SH_B_TRACK;

}

void handleButton3ModeChange(int mode) {

	switch (mode) {
	case FM:
		if (button6Mode == morphCV) {
			prepareCV = &prepareCV_FM_Morph;
		} else {
			prepareCV = &prepareCV_FM_PWM;
		}
		displayXCVMode = &displayXCV_FM;
		break;
	case PM:
		if (button6Mode == morphCV) {
			prepareCV = &prepareCV_PM_Morph;
		} else {
			prepareCV = &prepareCV_PM_PWM;
		}
		displayXCVMode = &displayXCV_PM;
		break;
	}

}

// not yet implemented, switch between morph lookup and PWM
//void handleMorphModeChange(int mode) {
//
//}

void handleButton4ModeChange(int mode) {
	// sync modes handled in IRQ handler
	if (button4Mode == hard) {
		displaySyncMode = &displaySync_Hard;
	} else {
		displaySyncMode = &displaySync_Soft;
	}
}

void handleButton6ModeChange(int mode) {

	switch (mode) {
	case morphCV:
		if (button3Mode == FM) {
			prepareCV = &prepareCV_FM_Morph;
		} else {
			prepareCV = &prepareCV_PM_Morph;
		}
		displayMorphMode = &displayMorph_Morph;
		break;
	case pwmCV:
		if (button3Mode == FM) {
			prepareCV = &prepareCV_FM_PWM;
		} else {
			prepareCV = &prepareCV_PM_PWM;
		}
		displayMorphMode = &displayMorph_PMW;
		break;
	}

}



/**
 *
 * LED display helpers
 *
 */

void uiSetRGB(rgb color){
	SET_RED_LED(color.r);
	SET_GREEN_LED(color.g);
	SET_BLUE_LED(color.b);
}

void uiClearRGB(){
	SET_RED_LED(0);
	SET_GREEN_LED(0);
	SET_BLUE_LED(0);
}

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

