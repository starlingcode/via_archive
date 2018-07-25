#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"
#include "main_state_machine.h"
#include "fill_buffer.h"
#include "via_rev5_hardware_io.h"

extern void handleCoversionSlow(viaStateVariableSet *, controlRateInputs *, audioRateInputs *, audioRateOutputs * outputs);

void nextSample(controlRateInputs * controls, audioRateInputs * inputs, audioRateOutputs * outputs, softwareSignaling * softwareSignals) {

	ALOGIC_HIGH;

	static viaStateVariableSet viaStateVariables;

	viaStateVariables.incrementValue1 = softwareSignals->attackIncrement;
	viaStateVariables.incrementValue2 = softwareSignals->releaseIncrement;

//	viaStateVariables.incrementValue1 = 1000;
//	viaStateVariables.incrementValue2 = 1000;

	(*advancePhase)(inputs, &viaStateVariables);

	calculateSample(controls, inputs, &viaStateVariables, outputs);

//	calculateLogicA(&viaStateVariables, outputs);

//	calculateDac3(&viaStateVariables, outputs);
//
//	calculateAuxLogic(&viaStateVariables, outputs);

//	(*calculateSH)(&viaStateVariables, outputs);

	viaStateVariables.slowConversionCounter += 1;

	handleCoversionSlow(&viaStateVariables, controls, inputs, outputs);

	ALOGIC_LOW;



}
