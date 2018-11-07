/*
 * meta_interrupt_handlers.cpp
 *
 *  Created on: Sep 12, 2018
 *      Author: willmitchell
 */


/*
 * meta_interrupt_handlers.c
 *
 *  Created on: Aug 29, 2018
 *      Author: willmitchell
 */

#include "meta.hpp"

const uint32_t phaseModPWMTables[33][65] = {phaseModPWM_0, phaseModPWM_1, phaseModPWM_2, phaseModPWM_3, phaseModPWM_4, phaseModPWM_5, phaseModPWM_6, phaseModPWM_7, phaseModPWM_8, phaseModPWM_9, phaseModPWM_10, phaseModPWM_11, phaseModPWM_12, phaseModPWM_13, phaseModPWM_14, phaseModPWM_15, phaseModPWM_16, phaseModPWM_17, phaseModPWM_18, phaseModPWM_19, phaseModPWM_20, phaseModPWM_21, phaseModPWM_22, phaseModPWM_23, phaseModPWM_24, phaseModPWM_25, phaseModPWM_26, phaseModPWM_27, phaseModPWM_28, phaseModPWM_29, phaseModPWM_30, phaseModPWM_31, phaseModPWM_32};

void ViaMeta::mainRisingEdgeCallback(void) {

	metaController.triggerSignal = 0;

	metaController.gateSignal = 1 * metaController.gateOn;

	drumEnvelope.trigger = 0;

	updateRGB = &ViaMeta::updateRGBBlink;

	TIM17->CR1 |= TIM_CR1_CEN;

}

void ViaMeta::mainFallingEdgeCallback(void) {

	metaController.gateSignal = 0;

}

void ViaMeta::auxRisingEdgeCallback(void) {

	metaController.freeze = 0;

}
void ViaMeta::auxFallingEdgeCallback(void)
{
	metaController.freeze = 1;

}

void ViaMeta::buttonPressedCallback(void) {

	metaController.triggerSignal = 0;

	metaController.gateSignal = 1 * metaController.gateOn;

	drumEnvelope.trigger = 0;

	this->metaUI.dispatch(EXPAND_SW_ON_SIG);

}
void ViaMeta::buttonReleasedCallback(void) {

	metaController.gateSignal = 0;

	this->metaUI.dispatch(EXPAND_SW_OFF_SIG);

}

void ViaMeta::ioProcessCallback(void) {

	// no need

}

void ViaMeta::halfTransferCallback(void) {

	setLogicOut(0, runtimeDisplay);

	metaController.generateIncrementsExternal(&inputs);
	metaController.advancePhase((uint32_t *) phaseModPWMTables);
	metaWavetable.phase = metaController.phaseBeforeIncrement;
	metaWavetable.increment = metaController.incrementUsed;
	metaWavetable.advance((uint32_t *) wavetableRead);
	(this->*outputStage)(0);
	//outputs.auxLogic[0] = EXPAND_LOGIC_LOW_MASK << (16 * metaWavetable.delta);
	outputs.auxLogic[0] = GPIO_NOP;
	(this->*calculateDac3)(0);
	(this->*calculateLogicA)(0);
	(this->*calculateSH)(0);
	metaController.triggerSignal = 1;

}

void ViaMeta::transferCompleteCallback(void) {

	setLogicOut(1, runtimeDisplay);

	metaController.generateIncrementsExternal(&inputs);
	metaController.advancePhase((uint32_t *) phaseModPWMTables);
	metaWavetable.phase = metaController.phaseBeforeIncrement;
	metaWavetable.increment = metaController.incrementUsed;
	metaWavetable.advance((uint32_t *) wavetableRead);
	(this->*outputStage)(META_BUFFER_SIZE);
	//outputs.auxLogic[1] = EXPAND_LOGIC_LOW_MASK << (16 * metaWavetable.delta);
	outputs.auxLogic[1] = GPIO_NOP;
	(this->*calculateDac3)(META_BUFFER_SIZE);
	(this->*calculateLogicA)(1);
	(this->*calculateSH)(1);
	metaController.triggerSignal = 1;

}

void ViaMeta::slowConversionCallback(void) {


	controls.update();
	metaWavetable.parseControls(&controls);
	metaController.parseControlsExternal(&controls, &inputs);
	drumEnvelope.parseControls(&controls, &inputs);

	(this->*updateRGB)();

}

void ViaMeta::auxTimer1InterruptCallback(void) {

	updateRGB = &ViaMeta::updateRGBBlank;

}

void ViaMeta::auxTimer2InterruptCallback(void) {

	updateRGB = currentRGBBehavior;

}


