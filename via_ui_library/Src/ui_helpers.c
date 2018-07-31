#include "main.h"
#include "tsl_user.h"
#include "user_interface.h"
#include "via_rev5_hardware_io.h"

// RGB led timer
TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim4;
TIM_HandleTypeDef htim5;



int incrementModeAndStore(int mode, int mask, int numModes) {
	mode = (mode + 1) % numModes;
	modeStateBuffer = (modeStateBuffer & ~(mask)) | mode;
	return mode;
}

int decrementModeAndStore(int mode, int mask, int numModes) {
	mode = (mode - 1) % numModes;
	modeStateBuffer = (modeStateBuffer & ~(mask)) | mode;
	return mode;
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

void uiStaticLEDHandler() {
	(*uiSetLEDA)();
	(*uiSetLEDB)();
	(*uiSetLEDC)();
	(*uiSetLEDD)();
}

void uiSetLEDAOn() {
	LEDA_ON;
}
void uiSetLEDBOn() {
	LEDB_ON;
}
void uiSetLEDCOn() {
	LEDC_ON;
}
void uiSetLEDDOn() {
	LEDD_ON;
}

void uiSetLEDAOff() {
	LEDA_OFF;
}
void uiSetLEDBOff() {
	LEDB_OFF;
}
void uiSetLEDCOff() {
	LEDC_OFF;
}
void uiSetLEDDOff() {
	LEDD_OFF;
}

