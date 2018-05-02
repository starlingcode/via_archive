#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"
#include "int64.h"

void doLogic(void);
void handleFallingEdge(void);

uint32_t aCounter;
uint32_t bCounter;

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
