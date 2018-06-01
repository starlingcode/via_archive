#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"
#include "main_state_machine.h"
#include "hardware_io.h"
#include "dsp.h"

/**
 *
 * Signal handlers, should probably move to hardware_io
 *
 */

void handleCoversionSlow(controlRateInputs * inputs) {

	static uint32_t knob1Sum;
	static uint32_t knob2Sum;
	static uint32_t knob3Sum;
	static uint32_t cv1Sum;
	static buffer knob1Buffer;
	static buffer knob2Buffer;
	static buffer knob3Buffer;
	static buffer cv1Buffer;

	// implement a running average on the control rate CV inputs
	knob1Sum = knob1 + knob1Sum - readBuffer(&knob1Buffer, 511);
	knob2Sum = knob2 + knob2Sum - readBuffer(&knob2Buffer, 511);
	knob3Sum = knob3 + knob3Sum - readBuffer(&knob3Buffer, 511);
	cv1Sum = cv1 + cv1Sum - readBuffer(&cv1Buffer, 15);

	writeBuffer(&knob1Buffer, knob1);
	writeBuffer(&knob2Buffer, knob2);
	writeBuffer(&knob3Buffer, knob3);
	writeBuffer(&cv1Buffer, cv1);

	// write the inputs to the holding struct
	inputs->knob1Value = knob1Sum >> 9;
	inputs->knob2Value = knob2Sum >> 9;
	inputs->knob3Value = knob3Sum >> 9;
	inputs->cv1Value = cv1Sum >> 4;

	// shoehorned into this timer for convenience
	if (RUNTIME_DISPLAY) {
		updateRGB(inputs, inputRead);
		(*displaySHMode)();
		(*displaySyncMode)();
		(*displayXCVMode)();
		(*displayMorphMode)();
	}

}

// wrap register address functions to be loaded into the logic struct (which is loaded into a playback buffer)
void holdLogic(void) {

}
void logicAHigh(void) {
	ALOGIC_HIGH;
}
void logicALow(void) {
	ALOGIC_LOW;
}
void logicBHigh(void) {
	BLOGIC_HIGH;
}
void logicBLow(void) {
	BLOGIC_LOW;
}
void shASample(void) {
	SH_A_SAMPLE;
}
void shATrack(void) {
	SH_A_TRACK;
}
void shBSample(void) {
	SH_B_SAMPLE;
}
void shBTrack(void) {
	SH_B_TRACK;
}

