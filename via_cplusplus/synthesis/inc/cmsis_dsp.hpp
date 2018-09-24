/*
 * dsp.h
 *
 *  Created on: Aug 18, 2018
 *      Author: willmitchell
 */

#ifndef INC_CMSIS_DSP_HPP_
#define INC_CMSIS_DSP_HPP_

#ifdef BUILD_F373

extern "C" {

// link to system defines for cmsis library functions
#include "stm32f3xx.h"

// link to cmsis header with platform definition
#define ARM_MATH_CM4
#define ARM_MATH_DSP
#include "arm_math.h"

}

#define VIA_SCALE_Q31 arm_scale_q31
#define VIA_OFFSET_Q31 arm_offset_q31
#define VIA_SHIFT_Q31 arm_shift_q31

#endif

#ifdef BUILD_VIRTUAL

#include <stdint.h>

typedef int32_t q31_t;
typedef int64_t q63_t;

// perhaps this is where you go to macro-town, and assign macros to the buffer functions

#define VIA_SCALE_Q31 not_arm_scale_q31
#define VIA_OFFSET_Q31 not_arm_offset_q31
#define VIA_SHIFT_Q31 not_arm_shift_q31

void not_arm_scale_q31(q31_t *, int32_t, int32_t, q31_t *, uint32_t);
void not_arm_offset_q31(q31_t *, int32_t, q31_t *, uint32_t);
void not_arm_shift_q31(q31_t *, int32_t, q31_t *, uint32_t);

#endif



#endif /* INC_CMSIS_DSP_HPP_ */
