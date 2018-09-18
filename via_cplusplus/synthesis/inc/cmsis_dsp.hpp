/*
 * dsp.h
 *
 *  Created on: Aug 18, 2018
 *      Author: willmitchell
 */

#ifndef INC_CMSIS_DSP_HPP_
#define INC_CMSIS_DSP_HPP_

extern "C" {

// link to system defines for cmsis library functions
#include "stm32f3xx.h"

// link to cmsis header with platform definition
#define ARM_MATH_CM4
#define ARM_MATH_DSP
#include "arm_math.h"

}

#endif /* INC_CMSIS_DSP_HPP_ */
