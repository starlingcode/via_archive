/*
 * meta_init.c
 *
 *  Created on: Aug 29, 2018
 *      Author: willmitchell
 */


#include "meta.h"

// eeprom storage array
extern uint16_t VirtAddVarTab[NB_OF_VAR] = { 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7,
		0x8, 0x9, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16 };

void meta_init(meta_signal_set * signals) {

	signals->controls = &controlRateInput;
	signals->inputs = &audioRateInput;
	signals->outputs = &audioRateOutput;
	signals->wavetable_parameters = &meta_wavetableParameters;
	signals->meta_parameters = &metaParameters;

	metaControllerParseControls = metaControllerParseControlsAudio;
	metaControllerGenerateIncrements = metaControllerGenerateIncrementsAudio;
	metaControllerIncrementArbiter = noRetrigAttackState;
	metaControllerLoopHandler = handleLoopOn;
	meta_calculateDac3 = meta_calculateDac3Phasor;
	meta_calculateLogicA = meta_calculateLogicAGate;
	meta_calculateSH = meta_calculateSHMode1;


	meta_initializeUICallbacks();

	// initialize our touch sensors
	tsl_user_Init();
	uiInitialize();

	meta_fillWavetableArray();

	meta_switchWavetable(meta_wavetableArray[0][0], signals);

	signals->meta_parameters->triggerSignal = 1;
	signals->meta_parameters->gateSignal = 0;

	via_ioStreamInit(&audioRateInput, &audioRateOutput, META_BUFFER_SIZE);
	via_logicStreamInit(&audioRateInput, &audioRateOutput, META_BUFFER_SIZE);

	signals->wavetable_parameters->morphMod = signals->inputs->cv3Samples;


}
