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
extern arm_fir_instance_q31 fir;

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




