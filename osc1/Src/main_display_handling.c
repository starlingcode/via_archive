#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"
#include "main_state_machine.h"

extern TIM_HandleTypeDef htim1;

extern struct parameters viaParams;
extern struct oscillator viaOsc;

/**
 *
 * Helper function for display handling
 *
 */

// wrapper for updating LED display
void updateRuntimeDisplay(void) {

	if (SAMPLE_A) {
		LEDA_ON;
	} else {
		LEDA_OFF;
	}

	if (SAMPLE_B) {
		LEDB_ON;
	} else {
		LEDB_OFF;
	}

//	if (LOGIC_A) {
//		LEDC_ON;
//	} else {
//		LEDC_OFF;
//	}

	if (LOGIC_B) {
		LEDD_ON;
	} else {
		LEDD_OFF;
	}

	if (viaOsc.phase < (256 << 16)) {
		//SET_BLUE_LED(output);
		SET_GREEN_LED(viaParams.morph);
	} else {
		//SET_RED_LED(output);
		SET_GREEN_LED(viaParams.morph);
	}

}
