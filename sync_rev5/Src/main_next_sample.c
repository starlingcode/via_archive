#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"
#include "main_state_machine.h"
#include "fill_buffer.h"
#include "via_rev5_hardware_io.h"

extern void handleCoversionSlow(viaStateVariableSet *, controlRateInputs *, audioRateInputs *, audioRateOutputs * outputs);

void nextSample(controlRateInputs * controls, audioRateInputs * inputs, audioRateOutputs * outputs, softwareSignaling * softwareSignals) {



	static viaStateVariableSet viaStateVariables;

	viaStateVariables.incrementValue1 = softwareSignals->attackIncrement;
	viaStateVariables.incrementValue2 = softwareSignals->releaseIncrement;

	viaStateVariables.phase = softwareSignals->phaseSignal;

	(*advancePhase)(inputs, &viaStateVariables);

	viaStateVariables.morph = __USAT(4095 - inputs->cv3Input - 2048 + controls->knob3Value, 12) << softwareSignals->morphShift;

	calculateSample(controls, inputs, &viaStateVariables, outputs);

	calculateLogicA(&viaStateVariables, outputs);

	calculateDac3(&viaStateVariables, outputs);

	(*calculateSH)(&viaStateVariables, outputs);

	softwareSignals->phaseSignal = viaStateVariables.phase;

	viaStateVariables.slowConversionCounter += 1;

	handleCoversionSlow(&viaStateVariables, controls, inputs, outputs);



}
