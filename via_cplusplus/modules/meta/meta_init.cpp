/*
 * meta_init.cpp
 *
 *  Created on: Sep 12, 2018
 *      Author: willmitchell
 */

#include "meta.hpp"

// eeprom storage array
extern uint16_t VirtAddVarTab[NB_OF_VAR] = { 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7,
		0x8, 0x9, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16 };

void ViaMeta::init() {

	signals.controls = &controlRateInput;
	signals.inputs = &audioRateInput;
	signals.outputs = &audioRateOutput;
	signals.wavetable_parameters = &meta_wavetableParameters;
	signals.meta_parameters = &metaParameters;
	signals.drum_parameters = &drumParameters;

	metaControllerParseControls = metaControllerParseControlsDrum;
	metaControllerGenerateIncrements = metaControllerGenerateIncrementsDrum;
	metaControllerIncrementArbiter = noRetrigAttackState;
	metaControllerLoopHandler = handleLoopOn;
	drumMode = &ViaMeta::drumModeOn;
	calculateDac3 = &ViaMeta::calculateDac3Phasor;
	calculateLogicA = &ViaMeta::calculateLogicAReleaseGate;
	calculateSH = &ViaMeta::calculateSHMode1;
	simpleEnvelopeIncrementArbiter = simpleEnvelopeRestingState;

	// initialize our touch sensors
	tsl_user_Init();
	metaUI.initialize();

	fillWavetableArray();

	switchWavetable(wavetableArray[0][0]);
	initDrum();
	signals.drum_parameters->output = (uint32_t*) drumWrite;

	signals.meta_parameters->triggerSignal = 1;
	signals.meta_parameters->gateSignal = 0;
	signals.meta_parameters->freeze = 1;

	via_ioStreamInit(&audioRateInput, &audioRateOutput, META_BUFFER_SIZE);
	via_logicStreamInit(&audioRateInput, &audioRateOutput, META_BUFFER_SIZE);

	signals.wavetable_parameters->morphMod = signals.inputs->cv3Samples;
	signals.wavetable_parameters->morphScale = (int16_t*) signals.drum_parameters->output;
	signals.meta_parameters->fm = (int16_t*) signals.drum_parameters->output;


}
