#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"
#include "via_rev5_hardware_io.h"
#include "user_interface.h"
#include "dsp.h"
#include "trigseq_interrupt_handlers.h"



//////////////////////////
// s&h handling functions
//////////////////////////

void resampleA(void){
	SH_A_TRACK;
	__HAL_TIM_SET_COUNTER(&htim16, 0);
	__HAL_TIM_ENABLE(&htim16);
}
void resampleB(void){
	SH_B_TRACK;
	__HAL_TIM_SET_COUNTER(&htim17, 0);
	__HAL_TIM_ENABLE(&htim17);
}

////////////////////////////////////
// sequence logic handling functions
////////////////////////////////////

void handleAHigh(softwareSignaling * softwareSignals){
	ALOGIC_HIGH;
	if (RUNTIME_DISPLAY) {
		LEDC_ON;
	}
	if (softwareSignals->andA) {
		softwareSignals->dacAEvent = (DAC_GATE_HIGH);
	}
	if (softwareSignals->sampleA) {
		resampleA();
	}
}
void handleALow(softwareSignaling * softwareSignals){
	ALOGIC_LOW;
	if (RUNTIME_DISPLAY) {
		LEDC_OFF;
	}
	if (softwareSignals->andA) {
		softwareSignals->dacAEvent = (DAC_GATE_LOW);
	}
	if (softwareSignals->trackA) {
		SH_A_TRACK;
		if (RUNTIME_DISPLAY) {
			LEDA_OFF;
		}
	}
}

void handleBHigh(softwareSignaling * softwareSignals){

	//update dac
	WRITE_DAC3(4095);
	if (RUNTIME_DISPLAY) {
		LEDD_ON;
	}
	if (softwareSignals->andB) {
		softwareSignals->dacBEvent = (DAC_GATE_HIGH);
	}
	if (softwareSignals->sampleB) {
		resampleB();
	}
}
void handleBLow(softwareSignaling * softwareSignals){
	WRITE_DAC3(2048);
	if (RUNTIME_DISPLAY) {
		LEDD_OFF;
	}
	if (softwareSignals->andB) {
		softwareSignals->dacBEvent = (DAC_GATE_LOW);
	}
	if (softwareSignals->trackB) {
		SH_B_TRACK;
		if (RUNTIME_DISPLAY) {
			LEDB_OFF;
		}
	}
}

void handleAuxHigh(softwareSignaling * softwareSignals) {

	EXPAND_LOGIC_HIGH;

	if (RUNTIME_DISPLAY) {
		SET_GREEN_LED(1000);
	}
}

void handleAuxLow(softwareSignaling * softwareSignals) {

	EXPAND_LOGIC_LOW;

	if (RUNTIME_DISPLAY) {
		SET_GREEN_LED(0);
	}
}


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

void handleConversionSlow(controlRateInputs * controls) {

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

	static int sequencingSignal;

	switch (sequencingSignal) {
	case 1:
		// implement a running average on the control rate CV inputs
		knob1Sum = knob1 + knob1Sum - readBuffer(&knob1Buffer, 31);
		knob2Sum = knob2 + knob2Sum - readBuffer(&knob2Buffer, 31);

		// store the newest value in a ring buffer
		writeBuffer(&knob1Buffer, knob1);
		writeBuffer(&knob2Buffer, knob2);

		// write the averaged inputs to the holding struct
		controls->knob1Value = knob1Sum >> 5;
		controls->knob2Value = knob2Sum >> 5;

		break;

	case 16:
		// implement a running average on the control rate CV inputs
		knob3Sum = knob3 + knob3Sum - readBuffer(&knob3Buffer, 31);
		cv1Sum = cv1 + cv1Sum - readBuffer(&cv1Buffer, 3);

		// store the newest value in a ring buffer
		writeBuffer(&knob3Buffer, knob3);
		writeBuffer(&cv1Buffer, cv1);

		// write the averaged inputs to the holding struct
		controls->knob3Value = knob3Sum >> 5;
		controls->cv1Value = cv1Sum >> 2;

		break;

	case 32:
		sequencingSignal = 0;
		break;

	default:
		break;

	}

	sequencingSignal++;

}





