#include "int64.h"
#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"


#define ARM_MATH_CM4

#include "arm_math.h"

void (*dspTaskManager)(void);

int attackCoeffArray[5];
int releaseCoeffArray[5];

typedef struct {
    int buff[4096];
    int writeIndex;
}buffer;

static inline void writeBuffer(buffer* buffer, int value) {
	buffer->buff[(buffer->writeIndex++) & 4095] = value;
}

static inline int readBuffer(buffer* buffer, int Xn) {
	return buffer->buff[(buffer->writeIndex + (~Xn)) & 4095];
}

typedef struct {
    int buff[16];
    int writeIndex;
}shortbuffer;

static inline void writeShortBuffer(shortbuffer* buffer, int value) {
	buffer->buff[(buffer->writeIndex++) & 15] = value;
}

static inline int readShortBuffer(shortbuffer* buffer, int Xn) {
	return buffer->buff[(buffer->writeIndex + (~Xn)) & 15];
}

static inline int q31_mul(int in0, int in1) {
	// adapted from the fixmathlib library
	int64_t result = (uint64_t) in0 * in1;
	return result >> 31;
}

static inline int q24_mul(int in0, int in1) {
	// adapted from the fixmathlib library
	int64_t result = (uint64_t) in0 * in1;
	return result >> 24;
}

static inline int fix16_lerp(int in0, int in1, uint16_t inFract) {
	// taken from the fixmathlib library
	int64_t tempOut = int64_mul_i32_i32(in0, (((int32_t) 1 << 16) - inFract));
	tempOut = int64_add(tempOut, int64_mul_i32_i32(in1, inFract));
	tempOut = int64_shift(tempOut, -16);
	return (int) int64_lo(tempOut);
}

static inline q31_t q31Negate(q31_t in) {
	return in ^ 0x80000000; //toggle the uppermost bit
}

shortbuffer inputs;
shortbuffer outputs;

static inline uint32_t biquadFilter(int *coeffArray) {
	int64_t output = q31_mul(coeffArray[0] << 1, readShortBuffer(&inputs, 0));
	output += q31_mul(coeffArray[1] << 1, readShortBuffer(&inputs, 1));
	output += q31_mul(coeffArray[2] << 1, readShortBuffer(&inputs, 2));
	output -= q31_mul(coeffArray[3], readShortBuffer(&outputs, 0))*2;
	output -= q31_mul(coeffArray[4] << 1, readShortBuffer(&outputs, 1));
	return  output;
}

int peakDetect(void);

void calculateBiquadCoeffs(void);

void dspIdle(void);
