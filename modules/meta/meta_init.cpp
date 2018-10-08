/*
 * meta_init.cpp
 *
 *  Created on: Sep 12, 2018
 *      Author: willmitchell
 */

#include "meta.hpp"

// eeprom storage array
//extern uint16_t VirtAddVarTab[NB_OF_VAR] = { 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7,
//		0x8, 0x9, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16 };

void ViaMeta::init() {

	initializeAuxOutputs();

	drumMode = &ViaMeta::drumModeOff;
	updateRGB = &ViaMeta::updateRGBSubaudio;
	calculateDac3 = &ViaMeta::calculateDac3Phasor;
	calculateLogicA = &ViaMeta::calculateLogicAReleaseGate;
	calculateSH = &ViaMeta::calculateSHMode1;

	metaController.parseControls = &MetaController::parseControlsDrum;
	metaController.generateIncrements = &MetaController::generateIncrementsDrum;
	metaController.incrementArbiter = &MetaController::noRetrigAttackState;
	metaController.loopHandler = &MetaController::handleLoopOn;

	drumEnvelope.incrementArbiter = &SimpleEnvelope::restingState;

	// initialize our touch sensors

	fillWavetableArray();
	initDrum();
	drumEnvelope.output = (uint32_t*) drumWrite;

	inputs.init(META_BUFFER_SIZE);
	outputs.init(META_BUFFER_SIZE);
	bufferSize = META_BUFFER_SIZE;

	metaUI.initialize();

	// switchWavetable(wavetableArray[0][0]);

	metaController.triggerSignal = 1;
	metaController.gateSignal = 0;
	metaController.freeze = 1;

	metaWavetable.morphMod = inputs.cv3Samples;
#ifdef BUILD_VIRTUAL
	metaWavetable.morphScale = (int16_t*) drumEnvelope.output;
	metaController.fm = (int16_t*) drumEnvelope.output;
#endif

}
