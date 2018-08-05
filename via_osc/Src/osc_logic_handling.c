#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"
#include "osc_main_states.h"
#include "osc_dsp.h"
#include "signals.h"
#include "via_rev5_hardware_io.h"


/*
 *
 * Logic functions
 *
 */



// assign a set of logic output function per the phase event at that sample
// SH on or off is wrapped up in this pair of functions

static inline void calculateLogicSHOn(uint32_t * phaseEvents, audioRateOutputs * output) {

	for (int i = 0; i < BUFFER_SIZE; i++) {

		switch (phaseEvents[i]) {
			//no logic events
			case 0:
				output->shAHandler[i] = SH_A_SAMPLE_MASK;
				output->shBHandler[i] = SH_B_SAMPLE_MASK;
				output->logicAHandler[i] = GPIO_NOP;
				output->auxLogicHandler[i] = GPIO_NOP;
				break;
			// at a handling
			case WAVETABLE_LENGTH + 1:
			case WAVETABLE_LENGTH - 1:
			case NEGATIVE_WAVETABLE_LENGTH + 1:
			case NEGATIVE_WAVETABLE_LENGTH - 1:
				output->shAHandler[i] = SH_A_SAMPLE_MASK;
				output->shBHandler[i] = SH_B_TRACK_MASK;
				output->logicAHandler[i] = GPIO_NOP;
				output->auxLogicHandler[i] = GPIO_NOP;
				break;
			// at b handling
			case 1:
			case -1:
				output->shAHandler[i] = SH_A_TRACK_MASK;
				output->shBHandler[i] = SH_B_SAMPLE_MASK;
				output->logicAHandler[i] = GPIO_NOP;
				output->auxLogicHandler[i] = GPIO_NOP;
				break;
			default:
				break;
		}

	}

}

static inline void calculateLogicSHOff(uint32_t * phase, audioRateOutputs * output) {

	for (int i; i < BUFFER_SIZE; i++) {

		switch (phase[i]) {
			//no logic events
			case 0:
				output->shAHandler[i] = SH_A_TRACK_MASK;
				output->shBHandler[i] = SH_A_TRACK_MASK;
				output->logicAHandler[i] = GPIO_NOP;
				output->auxLogicHandler[i] = GPIO_NOP;
				break;
			//dummy at a handling
			case WAVETABLE_LENGTH + 1:
			case WAVETABLE_LENGTH - 1:
			case NEGATIVE_WAVETABLE_LENGTH + 1:
			case NEGATIVE_WAVETABLE_LENGTH - 1:
				output->shAHandler[i] = SH_A_TRACK_MASK;
				output->shBHandler[i] = SH_A_TRACK_MASK;
				output->logicAHandler[i] = GPIO_NOP;
				output->auxLogicHandler[i] = GPIO_NOP;
				break;
			//dummy at b handling
			case -1:
			case 1:
				output->shAHandler[i] = SH_A_TRACK_MASK;
				output->shBHandler[i] = SH_A_TRACK_MASK;
				output->logicAHandler[i] = GPIO_NOP;
				output->auxLogicHandler[i]= GPIO_NOP;
				break;
			default:
				break;
		}

	}

}


void logicAndFilterSHOn(uint32_t * phaseEvents, audioRateOutputs * output) {
	calculateLogicSHOn(phaseEvents, output);
}
void logicAndFilterSHOff(uint32_t * phaseEvents, audioRateOutputs * output) {
	calculateLogicSHOff(phaseEvents, output);
}

