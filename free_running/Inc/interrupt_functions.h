#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"

#include "int64.h"

int calcTime1Env(void) __attribute__((section("ccmram")));
int calcTime2Env(void) __attribute__((section("ccmram")));
int calcTime1Seq(void) __attribute__((section("ccmram")));
int calcTime2Seq(void) __attribute__((section("ccmram")));

void sampHoldB(void) __attribute__((section("ccmram")));
void sampHoldA(void) __attribute__((section("ccmram")));

static inline int fix16_mul(int, int) __attribute__((section("ccmram")));
static inline int fix24_mul(int, int) __attribute__((section("ccmram")));
static inline int my_abs(int) __attribute__((section("ccmram")));
static inline fix16_lerp(int, int, uint16_t) __attribute__((section("ccmram")));

void dacISR(void)  __attribute__((section("ccmram")));
int getPhaseOsc(int position) __attribute__((section("ccmram")));
int getPhaseDrum(int position) __attribute__((section("ccmram")));
int getPhaseSimpleEnv(int position) __attribute__((section("ccmram")));
int getPhaseSimpleLFO(int position) __attribute__((section("ccmram")));
int getPhaseComplexEnv(int position) __attribute__((section("ccmram")));
int getPhaseComplexLFO(int position) __attribute__((section("ccmram")));

int (*getPhase) (int);

int (*attackTime) (void);
int (*releaseTime) (void);

//these are the variables used to generate the phase information that feeds our interpolations
int fixMorph;
uint32_t skewMod;

//most recent value from our expo decay
int drumModValue;

int position;
int inc;
int incSign;

int attackCount;

int out;

int holdPosition;

//our 16 bit fixed point multiply and linear interpolate functions
static inline int fix16_mul(int in0, int in1) {
	// taken from the fixmathlib library
	int64_t result = (uint64_t) in0 * in1;
	return result >> 16;
}

static inline int fix24_mul(int in0, int in1) {
	// taken from the fixmathlib library
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

static inline int my_abs(int in) {
	int sign= (in>>31);
	return (in^sign) - sign;
}

// helper functions to maintain and read from a circular buffer
static inline void write512(buffer512* buffer, int value) {
	buffer->buff[(buffer->writeIndex++) & 511] = value;
}

static inline int readn512(buffer512* buffer, int Xn) {
	return buffer->buff[(buffer->writeIndex + (~Xn)) & 511];
}

static inline void write256(buffer256* buffer, int value) {
	buffer->buff[(buffer->writeIndex++) & 255] = value;
}

static inline int readn256(buffer256* buffer, int Xn) {
	return buffer->buff[(buffer->writeIndex + (~Xn)) & 255];
}

static inline void write32(buffer32* buffer, int value) {
	buffer->buff[(buffer->writeIndex++) & 31] = value;
}

static inline int readn32(buffer32* buffer, int Xn) {
	return buffer->buff[(buffer->writeIndex + (~Xn)) & 31];
}


