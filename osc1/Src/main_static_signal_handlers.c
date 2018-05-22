#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"
#include "main_state_machine.h"
#include "hardware_io.h"

struct parameters viaParams;
extern struct oscillator viaOsc;

/**
 *
 * State machine signal parser
 *
 */

void parseSignal(int signal) {
	 switch (signal) {
		case MAIN_EXECUTE:
			break;
		case MAIN_RISING_EDGE:
			//handleRisingEdge();
			break;
		case MAIN_FALLING_EDGE:
			//handleFallingEdge();
			break;
		case MAIN_AUX_RISING_EDGE:
			handleAuxRisingEdge();
			break;
		case MAIN_AUX_FALLING_EDGE:
			//handleAuxFallingEdge();
			break;
		case MAIN_ADC1_CONV_COMPLETE:
			//handleADC1Conversion();
			break;
		case MAIN_ADC2_CONV_COMPLETE:
			//handleADC2Conversion();
			break;
		case MAIN_ADC3_CONV_COMPLETE:
			//handleADC3Conversion();
			break;
		case MAIN_AT_A:
			//handleAtA();
			break;
		case MAIN_AT_B:
			//handleAtB();
			break;
		case MAIN_TOWARDS_A:
			//handleTowardsA();
			break;
		case MAIN_TOWARDS_B:
			//handleTowardsB();
			break;
		case MAIN_DAC_TIMER_OVERRUN:
			handleDACTimerOverrun();
			break;
		case MAIN_UPDATE_DISPLAY:
			//updateRuntimeDisplay();
			break;
		default:
			break;
	 }
}

/**
 *
 * Signal handlers
 *
 */

// switch the main state to handle logic, which will cascade through all the necessary tasks to get ready for the next sample

void handleDACTimerOverrun(void) {
	main_State = &main_handleLogic;
}

// helper functions to average adc inputs and generate oscillator parameters
// use macros for the first and last samples in a 512 sample circular buffer
// DMA provides the circular buffer

void handleADC1Conversion(void) {

	static uint32_t cv1Sum;
	static uint32_t cv2Sum;
	static uint32_t cv3Sum;
	static buffer cv1Buffer;
	static buffer cv2Buffer;
	static buffer cv3Buffer;

	cv1Sum = cv1 + cv1Sum - readBuffer(&cv1Buffer, 511);
	cv2Sum = cv2 + cv2Sum - readBuffer(&cv2Buffer, 511);
	cv3Sum = cv3 + cv3Sum - readBuffer(&cv3Buffer, 511);

	writeBuffer(&cv1Buffer, cv1);
	writeBuffer(&cv2Buffer, cv2);
	writeBuffer(&cv3Buffer, cv3);

	viaParams.voltOct = cv1Sum >> 9;
	viaParams.xCV = cv2Sum >> 9;
	viaParams.morphCV = cv3Sum >> 9;

}

void handleADC2Conversion(void) {

	static uint32_t knob2Sum;
	static uint32_t knob3Sum;
	static buffer knob2Buffer;
	static buffer knob3Buffer;

	knob2Sum = knob2 + knob2Sum - readBuffer(&knob2Buffer, 511);
	knob3Sum = knob3 + knob3Sum - readBuffer(&knob3Buffer, 511);

	writeBuffer(&knob2Buffer, knob2);
	writeBuffer(&knob3Buffer, knob3);

	viaParams.finePitch = knob2Sum >> 9;
	viaParams.morph = knob3Sum >> 9;

}

void handleADC3Conversion(void) {

	static uint32_t knob1Sum;
	static buffer knob1Buffer;

	knob1Sum = knob1 + knob1Sum - readBuffer(&knob1Buffer, 511);

	writeBuffer(&knob1Buffer, knob1);

	viaParams.coarsePitch = knob1Sum >> 9;

}

void handleRisingEdge(void) {
	switch (syncMode) {

	case pendulum:
		viaParams.direction *= -1;
		break;

	case hard:
		viaOsc.phase = 0;
		break;

	case meta:
		familyIndicator = (familyIndicator + 1) % 8;
		switchFamily(familyIndicator);
		break;

	}
}

void handleAuxRisingEdge(void) {
	switch (auxSyncMode) {

	case auxPendulum:
//		viaParams.direction *= -1;
		break;

	case auxHard:
//		viaOsc.phase = 0;
		break;

	case auxMeta:
		if (familyIndicator == 0) {
			familyIndicator = 7;
		} else {
			familyIndicator --;
		}
		switchFamily(familyIndicator);
		break;

	}
}

void handleAtA() {

	// TODO replace with function pointers declared in UI

//	ALOGIC_HIGH;
//	SET_LOGIC_A;
	if (LOGIC_B) {
		BLOGIC_LOW;
		CLEAR_LOGIC_B;
	} else {
		BLOGIC_HIGH;
		SET_LOGIC_B;
	}

	if (shAMode == aDecimate) {
		resampleA();
		CLEAR_SAMPLE_A;
	} else if (shAMode == aHalfDecimate) {
		SH_A_SAMPLE;
		SET_SAMPLE_A;
	}

	if (shBMode == bHalfDecimate) {
		SH_B_TRACK;
		CLEAR_SAMPLE_B;
	}

}

void handleAtB() {

//	ALOGIC_LOW;
//	CLEAR_LOGIC_A;

	if (shBMode == bDecimate) {
		resampleB();
		CLEAR_SAMPLE_B;
	} else if (shBMode == bHalfDecimate) {
		SH_B_SAMPLE;
		SET_SAMPLE_B;
	}

	if (shAMode == aHalfDecimate) {
		SH_A_TRACK;
		CLEAR_SAMPLE_A;
	}
}

void handleTowardsA() {
	EXPAND_GATE_HIGH;
}

void handleTowardsB() {
	EXPAND_GATE_LOW;
}

