#include "main.h"
#include "tsl_user.h"
#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"
#include "user_interface.h"
#include "dsp.h"
#include "main_state_machine.h"
#include "modes.h"
#include "via_rev5_hardware_io.h"
#include "fill_buffer.h"

// RGB led timer
TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim4;
TIM_HandleTypeDef htim5;

/**
 *
 * Mode change helpers
 *
 */

void handleButton6ModeChange(int mode) {


	switch (mode) {
	case shANone:
		calculateSHA = calculateSHAMode1;
		break;
	case shAHalf:
		calculateSHA = calculateSHAMode2;
		break;
	case shAFull:
		calculateSHA = calculateSHAMode3;
		break;
	}

}

void handleButton2ModeChange(int mode) {

	switch (mode) {
	case noloop:
		handleLoop = handleLoopOff;
		break;
	case looping:
		handleLoop = handleLoopOn;
		break;
	}

}

void handleButton3ModeChange(int mode) {

	switchReleaseFamily();


}

void handleButton1ModeChange(int mode) {

	switchAttackFamily();


}

void handleButton5ModeChange(int mode) {

	switch (mode) {
	case noretrigger:
		advancePhase = advancePhaseNoRetrig;
		noRetrigStateMachine = noRetrigAttackState;
		break;
	case nongatedretrigger:
		advancePhase = advancePhaseEnv;
		envStateMachine = envAttackState;
		break;
	case gated:
		advancePhase = advancePhaseGate;
		gateStateMachine = gateAttackState;
		break;
	case pendulum:
		advancePhase = advancePhasePendulum;
		pendulumStateMachine = pendulumForwardAttackState;
		break;
	}

}

void handleButton4ModeChange(int mode) {


	switch (mode) {
	case shBNone:
		calculateSHB = calculateSHBMode1;
		break;
	case shAHalf:
		calculateSHB = calculateSHBMode2;
		break;
	case shAFull:
		calculateSHB = calculateSHBMode3;
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
