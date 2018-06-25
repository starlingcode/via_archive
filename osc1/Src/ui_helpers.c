#include "main.h"
#include "tsl_user.h"
#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"
#include "user_interface.h"
#include "dsp.h"
#include "main_state_machine.h"

// RGB led timer
TIM_HandleTypeDef htim1;

/**
 *
 * Mode change helpers
 *
 */

void handleSHModeChange(int mode) {
	SH_A_TRACK;
	SH_B_TRACK;

	switch (mode) {
	case none:
		fillBuffer = &fillBufferSHOff;
		displaySHMode = &displaySH_Off;
		break;
	case decimate:
		fillBuffer = &fillBufferSHOn;
		displaySHMode = &displaySH_On;
		break;
	}

}

void handleXModeChange(int mode) {

	switch (mode) {
	case FM:
		if (morphMode == morphCV) {
			incrementOscillator = &incrementOscillatorFM_Morph;
		} else {
			incrementOscillator = &incrementOscillatorFM_PWM;
		}
		displayXCVMode = &displayXCV_FM;
		break;
	case PM:
		if (morphMode == morphCV) {
			incrementOscillator = &incrementOscillatorPM_Morph;
		} else {
			incrementOscillator = &incrementOscillatorPM_PWM;
		}
		displayXCVMode = &displayXCV_PM;
		break;
	}

}

// not yet implemented, switch between morph lookup and PWM
//void handleMorphModeChange(int mode) {
//
//}

void handleSyncModeChange(int mode) {
	// sync modes handled in IRQ handler
	if (syncMode == hard) {
		displaySyncMode = &displaySync_Hard;
	} else {
		displaySyncMode = &displaySync_Soft;
	}
}

void handleMorphModeChange(int mode) {

	switch (mode) {
	case morphCV:
		if (xMode == FM) {
			incrementOscillator = &incrementOscillatorFM_Morph;
		} else {
			incrementOscillator = &incrementOscillatorPM_Morph;
		}
		displayMorphMode = &displayMorph_Morph;
		break;
	case pwmCV:
		if (xMode == FM) {
			incrementOscillator = &incrementOscillatorFM_PWM;
		} else {
			incrementOscillator = &incrementOscillatorPM_PWM;
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
