#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"
#include "signal_processing.h"

	q31_t alpha;
	q31_t freq;
	q31_t cosCoefficient;
	int64_t gain;

void dspIdle(void) {

}

void calculateBiquadCoeffs(void) {

	//adapted from the musicDSP EQ cookbook
	//https://web.archive.org/web/20180108012523/http://www.musicdsp.org/files/Audio-EQ-Cookbook.txt

	#define Q31_UNITY 2147483647
	#define ALPHA_CONSTANT 1518729595 //1/(2*Q) in q31_t, Q of .707 (maximally flat butterworth response)

	freq = (knob1) << 18;

	cosCoefficient = arm_cos_q31(freq);

	alpha = q31_mul(arm_sin_q31(freq), ALPHA_CONSTANT);

	gain = int64_div_i64_i32((int64_t)1 << 61, (1<<30) + (alpha >> 1));

    //calculate and normalize the coefficients, dividing by 2 to keep the coefficients below 1
    attackCoeffArray[0] =  q31_mul((Q31_UNITY - cosCoefficient) >> 2, gain);
    attackCoeffArray[1] =   q31_mul((Q31_UNITY - cosCoefficient) >> 1, gain);
    attackCoeffArray[2] =  q31_mul((Q31_UNITY - cosCoefficient) >> 2, gain);
    attackCoeffArray[3] =  q31_mul(cosCoefficient, gain);
    attackCoeffArray[4] =   q31_mul((Q31_UNITY - alpha) >> 1, gain);

	freq = (knob2 + 50) << 7;

	cosCoefficient = arm_cos_q31(freq);

	alpha = q31_mul(arm_sin_q31(freq), ALPHA_CONSTANT);

	gain = int64_div_i64_i32((int64_t)1 << 61, (1<<30) + (alpha >> 1));

    //calculate and normalize the coefficients, dividing by 2 to keep the coefficients below 1
    releaseCoeffArray[0] =  q31_mul((Q31_UNITY - cosCoefficient) >> 2, gain);
    releaseCoeffArray[1] =   q31_mul((Q31_UNITY - cosCoefficient) >> 1, gain);
    releaseCoeffArray[2] =  q31_mul((Q31_UNITY - cosCoefficient) >> 2, gain);
    releaseCoeffArray[3] =  q31_mul(cosCoefficient, gain);
    releaseCoeffArray[4] =   q31_mul((Q31_UNITY - alpha) >> 1, gain);

    dspTaskManager = dspIdle;

}


