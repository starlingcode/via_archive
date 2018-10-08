/*
 * via_virtual_module.hpp
 *
 *  Created on: Sep 22, 2018
 *      Author: willmitchell
 */

#ifndef IO_INC_VIA_VIRTUAL_MODULE_HPP_
#define IO_INC_VIA_VIRTUAL_MODULE_HPP_

#include "dsp.hpp"
#include "via_virtual_system.hpp"
#include "via_global_signals.hpp"

class ViaModule {
public:

	uint32_t aLogicOutput = 0;
	uint32_t auxLogicOutput = 0;
	uint32_t shAOutput = 0;
	uint32_t shBOutput = 0;

	uint32_t redLevel = 0;
	uint32_t greenLevel = 0;
	uint32_t blueLevel = 0;

	uint32_t ledAOutput = 0;
	uint32_t ledBOutput = 0;
	uint32_t ledCOutput = 0;
	uint32_t ledDOutput = 0;

	int32_t button1Input = 0;
	int32_t button2Input = 0;
	int32_t button3Input = 0;
	int32_t button4Input = 0;
	int32_t button5Input = 0;
	int32_t button6Input = 0;



	ViaControls controls;

	int32_t bufferSize;
	ViaInputStreams inputs;
	ViaOutputStreams outputs;

	void ioStreamInit() {

		// // assign module IO streams to virtual hook
		// int

	}

	void initializeAuxOutputs(void) {

		// not needed

		// assign GPIO and LED to virtual module write location

//		aLogicOutput = &(GPIOC->BSRR);
//		auxLogicOutput = &(GPIOA->BSRR);
//		shAOutput = &(GPIOB->BSRR);
//		shBOutput = &(GPIOB->BSRR);
//
//		// tim3 channel 2
//		redLevel = &TIM3->CCR1 + 1;
//		// tim4 channel 4
//		greenLevel = &TIM4->CCR1 + 3;
//		// tim5 channel 1
//		blueLevel = &TIM5->CCR1;
//
//		ledAOutput = &(GPIOF->BSRR);
//		ledBOutput = &(GPIOC->BSRR);
//		ledCOutput = &(GPIOA->BSRR);
//		ledDOutput = &(GPIOB->BSRR);

	}

	rgb hueSpace[16] = {{4095, 0, 0}, {4095, 1228, 0}, {4095, 2457, 0}, {4095, 3685, 0}, {2047, 4095, 0}, {819, 4095, 0}, {0, 4095, 409}, {0, 4095, 1638}, {0, 4095, 4095}, {0, 2866, 4095}, {0, 1638, 4095}, {0, 409, 4095}, {2047, 0, 4095}, {3276, 0, 4095}, {4095, 0, 3685}, {4095, 0, 2456}};


	/*
	 *
	 * Logic output handling
	 *
	 */

	inline void setLogicA(int32_t high) {
		aLogicOutput = 1 + high;
	}

	inline void setAuxLogic(int32_t high) {
		auxLogicOutput = 1 + high;
	}

	inline void setSH(int32_t sampleA, int32_t sampleB) {

		shAOutput = 1 + sampleA;
		shBOutput = 1 + sampleB;


	}

	inline void setLEDA(int32_t on) {
		ledAOutput = 1 + on;
	}

	inline void setLEDB(int32_t on) {
		ledBOutput = 1 + on;
	}

	inline void setLEDC(int32_t on) {
		ledCOutput = 1 + on;
	}

	inline void setLEDD(int32_t on) {
		ledDOutput = 1 + on;
	}

	enum ViaVirtualGPIO {
		VIA_GPIO_NOP,
		VIA_GPIO_LOW,
		VIA_GPIO_HIGH
	};

	inline void setLogicOutputsLEDOn(uint32_t logicA, uint32_t auxLogic,
			uint32_t shA, uint32_t shB) {

		logicA = GET_ALOGIC_VIRTUAL_MASK(logicA);
		auxLogic = GET_EXPAND_LOGIC_VIRTUAL_MASK(auxLogic);
		shA = GET_SH_A_VIRTUAL_MASK(shA);
		shB = GET_SH_B_VIRTUAL_MASK(shB);

		setLEDA(shA - 1);
		setLEDB(shB - 1);
		setLEDC(logicA - 1);

		//combine the mask variables for a shared GPIO group with a bitwise or
		aLogicOutput = (logicA);

		auxLogicOutput = (auxLogic);

		shAOutput = (shA);

		shBOutput = (shB);

	}

	inline void setLogicOutputsLEDOff(uint32_t logicA, uint32_t auxLogic,
			uint32_t shA, uint32_t shB) {

		logicA = GET_ALOGIC_VIRTUAL_MASK(logicA);
		auxLogic = GET_EXPAND_LOGIC_VIRTUAL_MASK(auxLogic);
		shA = GET_SH_A_VIRTUAL_MASK(shA);
		shB = GET_SH_B_VIRTUAL_MASK(shB);

		//combine the mask variables for a shared GPIO group with a bitwise or
		aLogicOutput = (logicA);

		auxLogicOutput = (auxLogic);

		shAOutput = (shA | shB);

	}

	inline void setLogicOut(int32_t writeIndex, int32_t runtimeDisplay) {

		int32_t logicA = outputs.logicA[writeIndex];
		int32_t auxLogic = outputs.auxLogic[writeIndex];
		int32_t shA = outputs.shA[writeIndex];
		int32_t shB = outputs.shB[writeIndex];

		if (runtimeDisplay) {
			setLogicOutputsLEDOn(logicA, auxLogic, shA, shB);
		} else {
			setLogicOutputsLEDOff(logicA, auxLogic, shA, shB);
		}

	}

	inline void setLogicOutBoolean(int32_t writeIndex, int32_t runtimeDisplay) {

		int32_t logicA = GET_ALOGIC_MASK(outputs.logicA[writeIndex]);
		int32_t auxLogic = GET_EXPAND_LOGIC_MASK(outputs.auxLogic[writeIndex]);
		int32_t shA = GET_SH_A_MASK(outputs.shA[writeIndex]);
		int32_t shB = GET_SH_B_MASK(outputs.shB[writeIndex]);

		if (runtimeDisplay) {
			setLogicOutputsLEDOn(logicA, auxLogic, shA, shB);
		} else {
			setLogicOutputsLEDOff(logicA, auxLogic, shA, shB);
		}

	}

	/*
	 *
	 * LED handling
	 *
	 */

	inline void setRedLED(int32_t level) {
		redLevel = level;
	}

	inline void setGreenLED(int32_t level) {
		greenLevel = level;
	}

	inline void setBlueLED(int32_t level) {
		blueLevel = level;
	}

	inline void updateRGBDisplay(int32_t red, int32_t green, int32_t blue, int32_t runtimeDisplay) {
		if (runtimeDisplay) {
			setRedLED(red);
			setGreenLED(green);
			setBlueLED(blue);
		}
	}

	void setRGB(rgb color) {
		setRedLED(color.r);
		setGreenLED(color.g);
		setBlueLED(color.b);
	}

	void setRGBScaled(rgb color, int32_t scale) {
		setRedLED((color.r * scale) >> 12);
		setGreenLED((color.g * scale) >> 12);
		setBlueLED((color.b * scale) >> 12);
	}

	void clearRGB() {
		setRedLED(0);
		setGreenLED(0);
		setBlueLED(0);
	}

	void setLEDs(int32_t digit) {
		switch (digit) {
		case 0:
			setLEDA(1);
			setLEDB(0);
			setLEDC(0);
			setLEDD(0);
			break;
		case 1:
			setLEDA(0);
			setLEDB(0);
			setLEDC(1);
			setLEDD(0);
			break;
		case 2:
			setLEDA(0);
			setLEDB(1);
			setLEDC(0);
			setLEDD(0);
			break;
		case 3:
			setLEDA(0);
			setLEDB(0);
			setLEDC(0);
			setLEDD(1);
			break;
		case 4:
			setLEDA(1);
			setLEDB(0);
			setLEDC(1);
			setLEDD(0);
			break;
		case 5:
			setLEDA(0);
			setLEDB(1);
			setLEDC(0);
			setLEDD(1);
			break;
		case 6:
			setLEDA(1);
			setLEDB(1);
			setLEDC(0);
			setLEDD(0);
			break;
		case 7:
			setLEDA(0);
			setLEDB(0);
			setLEDC(1);
			setLEDD(1);
			break;
		}
	}

	void clearLEDs() {
		setLEDA(0);
		setLEDB(0);
		setLEDC(0);
		setLEDD(0);
	}

};


#endif /* IO_INC_VIA_VIRTUAL_MODULE_HPP_ */
