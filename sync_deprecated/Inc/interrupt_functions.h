#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"
#include "int64.h"


typedef struct {
    int buff[1024];
    int writeIndex;
} buffer;

// wavetable size - 1 in fix16 and that number doubled
uint32_t span;
uint32_t spanx2;
int tableSizeCompensation;

//per family bit shift amounts to accomplish morph
uint32_t morphBitShiftRight;
uint32_t morphBitShiftLeft;

//these are the variables used to generate the phase information that feeds our interpolations
int fixMorph;
int getMorph;

uint32_t attackInc;
uint32_t releaseInc;
uint32_t catchupInc;
uint32_t gateOnCount;
uint32_t periodCount;
int incSign;
int time1;
int time2;

int holdPosition;

//lastest result of the biinterpolation between interp1 and interp2 (scaled in drum mode)
int out;


// ADC variables and defines

#define time2Knob (ADCReadings2[0] & 0b11111111111111111111111111100000)
#define morphKnob (ADCReadings2[1] & 0b11111111111111111111111111100000)
#define time1CV (ADCReadings1[0] & 0b111111111111111111111111100000)
#define time2CV (ADCReadings1[1] & 0b11111111111111111111111111111111)
#define morphCV (ADCReadings1[2] & 0b1111111111111111111111111100000)
#define time1Knob (ADCReadings3[0] & 0b1111111111111111111111111100000)

static inline int fix16_mul(int, int) __attribute__((section("ccmram")));
static inline int fix24_mul(int, int) __attribute__((section("ccmram")));
static inline int my_abs(int) __attribute__((section("ccmram")));
static inline fix16_lerp(int, int, uint16_t) __attribute__((section("ccmram")));
static inline int fix48_mul(uint32_t in0, uint32_t in1) __attribute__((section("ccmram")));
static inline void write(buffer* buffer, int value);
static inline int readn(buffer* buffer, int Xn);

void inputCapture(void)  __attribute__((section("ccmram")));
void tapTempo(void) __attribute__((section("ccmram")));
void generateFrequency(void) __attribute__((section("ccmram")));
void dacISR(void)  __attribute__((section("ccmram")));
void getPhase(void)  __attribute__((section("ccmram")));
void getAverages(void)  __attribute__((section("ccmram")));

//our 16 bit fixed point multiply and linear interpolate functions
static inline int fix16_mul(int in0, int in1) {
	// taken from fixmathlib
	int64_t result = (uint64_t) in0 * in1;
	return result >> 16;
}

static inline int fix24_mul(int in0, int in1) {
	// taken from fixmathlib
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

static inline int fix48_mul(uint32_t in0, uint32_t in1) {
	// taken from the fixmathlib library
	int64_t result = (uint64_t) in0 * in1;
	return result >> 48;
}

static inline void write(buffer* buffer, int value) {
	buffer->buff[(buffer->writeIndex++) & BUFF_SIZE_MASK] = value;
}

static inline int readn(buffer* buffer, int Xn) {
	return buffer->buff[(buffer->writeIndex + (~Xn)) & BUFF_SIZE_MASK];
}

