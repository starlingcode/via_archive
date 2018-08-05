
#include "signals.h"
#include "via_rev5_hardware_io.h"

#include "../inc/meta_fill_buffer.h"
#include "../inc/meta_main_states.h"
#include "../inc/meta_modes.h"
#include "../inc/meta_tables.h"

extern int handleCoversionSlow(q31_t lastSample, int lastPhaseValue, controlRateInputs * controls, audioRateInputs * inputBuffer, uint32_t sequencingSignal);

void fillBuffer(viaSignals * signals) {

	static q31_t incrementValues1[BUFFER_SIZE];
	static q31_t incrementValues2[BUFFER_SIZE];
	static q31_t phaseArray[BUFFER_SIZE];
	static q31_t phaseEventArray[BUFFER_SIZE];
	static q31_t drumEnvelope[BUFFER_SIZE];
	static int lastPhase;
	static int oscillatorOn;
	static uint32_t slowConversionCounter;

	// eventually,
	// static struct viaStateInfoHolder viaStateInfo;

	audioRateInputs * inputRead = signals->inputRead;
	audioRateOutputs * outputWrite = signals->outputWrite;
	softwareSignaling * softwareSignals = signals->softwareSignals;
	controlRateInputs * controls = signals->controls;

	// profiling pin a logic out high
	GPIOC->BRR = (uint32_t)GPIO_PIN_13;

	(*getIncrements)(inputRead->cv2Input, &controlRateInput, incrementValues1, incrementValues2);

	lastPhase = (*advancePhase)(incrementValues1, incrementValues2, inputRead->triggerInput, inputRead->gateInput, lastPhase, &oscillatorOn, phaseArray, phaseEventArray);

	arm_offset_q31(inputRead->cv3Input, controlRateInput.knob3Value - 2048, inputRead->cv3Input, BUFFER_SIZE);
	arm_scale_q31(inputRead->cv3Input, ((1<<28) - 1) * (softwareSignals->currentFamily->familySize - 1), 0, inputRead->cv3Input, BUFFER_SIZE);

	(*getSamples)(phaseArray, __USAT(inputRead->cv2Input[0] + controlRateInput.knob2Value - 2048, 12), inputRead->cv3Input, outputWrite->samples, outputWrite->auxLogicHandler);

	(*calculateSH)(phaseEventArray, outputWrite);

	(*calculateLogicA)(phaseEventArray, inputRead->triggerInput, oscillatorOn, outputWrite);

	//calculateDac3Samples(outputWrite->dac3Samples, phaseModBuffer, incrementBuffer);

	slowConversionCounter = handleCoversionSlow(outputWrite->samples[BUFFER_SIZE - 1], lastPhase, controls, inputRead, slowConversionCounter);

	main_state = main_idle;

}

