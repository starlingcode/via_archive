#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"
#include "via_rev5_hardware_io.h"
#include "user_interface.h"
#include "led_display.h"
#include "dsp.h"
#include "main_state_machine.h"

/**
 *
 * S&H handling functions
 *
 */



/**
 *
 * ADC Averaging
 *
 */

void writeBuffer(buffer* buffer, int value) {
	buffer->buff[(buffer->writeIndex++) & 255] = value;
}

int readBuffer(buffer* buffer, int Xn) {
	return buffer->buff[(buffer->writeIndex + (~Xn)) & 255];
}

int handleCoversionSlow(controlRateInputs * inputs, uint32_t sequencingSignal) {

	// TODO apply SIMD instructions?

	static uint32_t knob1Sum;
	static uint32_t knob2Sum;
	static uint32_t knob3Sum;
	static uint32_t cv1Sum;
	static buffer knob1Buffer;
	static buffer knob2Buffer;
	static buffer knob3Buffer;
	static buffer cv1Buffer;

	switch (sequencingSignal) {
	case 1:
		// implement a running average on the control rate CV inputs
		knob1Sum = knob1 + knob1Sum - readBuffer(&knob1Buffer, 1023);
		knob2Sum = knob2 + knob2Sum - readBuffer(&knob2Buffer, 1023);

		// store the newest value in a ring buffer
		writeBuffer(&knob1Buffer, knob1);
		writeBuffer(&knob2Buffer, knob2);

		// write the averaged inputs to the holding struct
		inputs->knob1Value = knob1Sum >> 8;
		inputs->knob2Value = knob2Sum >> 8;

		break;

	case 2:
		// implement a running average on the control rate CV inputs
		knob3Sum = knob3 + knob3Sum - readBuffer(&knob3Buffer, 1023);
		cv1Sum = cv1 + cv1Sum - readBuffer(&cv1Buffer, 1023);

		// store the newest value in a ring buffer
		writeBuffer(&knob3Buffer, knob3);
		writeBuffer(&cv1Buffer, cv1);

		// write the averaged inputs to the holding struct
		inputs->knob3Value = knob3Sum >> 8;
		inputs->cv1Value = cv1Sum >> 8;

		break;

	case 3:
		// update the runtime display if the UI menu is not turned on
		if (RUNTIME_DISPLAY) {
			updateRGB(inputs, inputRead);
			(*displayButton1Mode)();
			(*displayButton4Mode)();
			(*displayButton3Mode)();
			(*displayButton1Mode)();
		}

		sequencingSignal = 0;

		break;

	}

	return sequencingSignal;

}




