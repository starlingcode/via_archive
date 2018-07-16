#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"
#include "main_state_machine.h"
#include "dsp.h"
#include "via_rev5_hardware_io.h"

/*
 *
 * FIR filter setup
 *
 */

// fir filter data structure
arm_fir_instance_q31 fir;

// declare filter coefficients
q31_t firCoefficients[NUM_TAPS] = FIR24TAPS5_12;

// declare state buffer of size (numTaps + blockSize - 1)
q31_t firState[BUFFER_SIZE + NUM_TAPS - 1];

// iir filter data structure
arm_biquad_casd_df1_inst_q31 biquad;

// declare filter coefficients (a set of 5 for each stage)
q31_t biquadCoefficients[NUM_STAGES * 5] = BIQUAD20K_8STAGE;

// Declare state buffer of size (numStages*4, 4 states per stage)
q31_t biquadState[NUM_STAGES*4];


void initializeFilter() {
	// initialize the FIR filter
	arm_fir_init_q31(&fir, NUM_TAPS, &firCoefficients[0], &firState[0], BUFFER_SIZE);
}

//void initializeFilter() {
//	// initialize the IIR filter (cascaded biquad filter)
//	arm_biquad_cascade_df1_init_q31(&biquad, NUM_STAGES, &biquadCoefficients[0], &biquadState[0], 0);
//}

/*
 *
 * Logic functions
 *
 */

// resampling management timers

extern TIM_HandleTypeDef htim16;
extern TIM_HandleTypeDef htim17;

void logicAHigh(void);
void logicALow(void);
void logicBHigh(void);
void logicBLow(void);
void shASample(void);
void shATrack(void);
void shBSample(void);
void shBTrack(void);
void resampleA(void);
void resampleB(void);

// assign a set of logic output function per the phase event at that sample
// SH on or off is wrapped up in this pair of functions

static inline void calculateLogicSHOn(uint32_t * phaseEvents, audioRateOutputs * output) {

	for (int i; i < BUFFER_SIZE; i++) {

		switch (phaseEvents[i]) {
			//no logic events
			case 0:
				output->shAHandler[i] = SH_A_SAMPLE_MASK;
				output->shBHandler[i] = SH_B_SAMPLE_MASK;
				output->logicAHandler[i] = GPIO_NOP;
				output->logicBHandler[i] = GPIO_NOP;
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
				output->logicBHandler[i] = BLOGIC_HIGH_MASK;
				output->auxLogicHandler[i] = GPIO_NOP;
				break;
			// at b handling
			case 1:
			case -1:
				output->shAHandler[i] = SH_A_TRACK_MASK;
				output->shBHandler[i] = SH_B_SAMPLE_MASK;
				output->logicAHandler[i] = GPIO_NOP;
				output->logicBHandler[i] = BLOGIC_LOW_MASK;
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
				output->logicBHandler[i] = GPIO_NOP;
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
				output->logicBHandler[i] = GPIO_NOP;
				output->auxLogicHandler[i] = GPIO_NOP;
				break;
			//dummy at b handling
			case -1:
			case 1:
				output->shAHandler[i] = SH_A_TRACK_MASK;
				output->shBHandler[i] = SH_A_TRACK_MASK;
				output->logicAHandler[i] = GPIO_NOP;
				output->logicBHandler[i] = GPIO_NOP;
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
//	arm_shift_q31(output->samples, 4, output->samples, BUFFER_SIZE);
//	arm_biquad_cascade_df1_fast_q31(&biquad, output->samples, output->samples, BUFFER_SIZE);
//	arm_shift_q31(output->samples, -20, output->samples, BUFFER_SIZE);
//  arm_fir_fast_q31(&fir, output->samples, output->samples, BUFFER_SIZE);

}

