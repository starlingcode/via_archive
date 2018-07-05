#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"
#include "via_rev5_hardware_io.h"
#include "user_interface.h"
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
	buffer->buff[(buffer->writeIndex++) & 31] = value;
}

int readBuffer(buffer* buffer, int Xn) {
	return buffer->buff[(buffer->writeIndex + (~Xn)) & 31];
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

	static int pwmCounter;

	switch (sequencingSignal) {
	case 1:
		// implement a running average on the control rate CV inputs
		knob1Sum = knob1 + knob1Sum - readBuffer(&knob1Buffer, 31);
		knob2Sum = knob2 + knob2Sum - readBuffer(&knob2Buffer, 31);

		// store the newest value in a ring buffer
		writeBuffer(&knob1Buffer, knob1);
		writeBuffer(&knob2Buffer, knob2);

		// write the averaged inputs to the holding struct
		inputs->knob1Value = knob1Sum >> 5;
		inputs->knob2Value = knob2Sum >> 5;

		break;

	case 2:
		// implement a running average on the control rate CV inputs
		knob3Sum = knob3 + knob3Sum - readBuffer(&knob3Buffer, 31);
		cv1Sum = cv1 + cv1Sum - readBuffer(&cv1Buffer, 7);

		// store the newest value in a ring buffer
		writeBuffer(&knob3Buffer, knob3);
		writeBuffer(&cv1Buffer, cv1);

		// write the averaged inputs to the holding struct
		inputs->knob3Value = knob3Sum >> 5;
		inputs->cv1Value = cv1Sum >> 3;

		break;

	case 3:
		// update the runtime display if the UI menu is not turned on
		if (RUNTIME_DISPLAY) {
			updateRGB(inputs, inputRead);
		}

		sequencingSignal = 0;

		break;

	}

	return sequencingSignal;

}




