#ifndef DSP_H
#define DSP_H

#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"
#define ARM_MATH_CM4
#include "arm_math.h"
#include "int64.h"

#define WAVETABLE_LENGTH 33554432
#define NEGATIVE_WAVETABLE_LENGTH -33554432 // wavetable length in 16 bit fixed point (512 << 16)
#define WAVETABLE_MAX_VALUE_PHASE 16777216 // wavetable midpoint in 16 bit fixed point (256 << 16)

#define BUFFER_SIZE 64

#define NUM_TAPS 24

#define FIR8TAPS1_24 {37653504, 103041591, 262708334, 424417055, 491842679, 424417055, 262708334, 103041591 , 37653504}

#define FIR16TAPS5_24 {-5268880, 20286907, 45192374, -47794798, -227426832, -51762506, 769600018, 1644657365, 1644657365, 769600018, -51762506, -227426832, -47794798, 45192374, 20286907, -5268880}

#define FIR24TAPS6_24 {1499280, 3097718, -6929872, -34955643, -49795015, -9487274, 49070362, 22354339, -80649134, -68021400, 179184179, 459216960, 459216960, 179184179, -68021400, -80649134, 22354339, 49070362, -9487274, -49795015, -34955643, -6929872, 3097718, 1499280}

#define FIR24TAPS5_12 {3016239, 5738308, -1679970, -18021039, -10780765, 37693189, 55436335, -41562717, -155240046, -30053218, 404571402, 824624103, 824624103, 404571402, -30053218, -155240046, -41562717, 55436335, 37693189, -10780765, -18021039, -1679970, 5738308, 3016239}

#define NUM_STAGES 4

#define BIQUAD20K_8STAGE {740135009, 1480270018, 740135009, 1373991412, 512806799, 40135009, 1480270018, 740135009, 1373991412, 512806799, 40135009, 1480270018, 740135009, 1373991412, 512806799, 40135009, 1480270018, 740135009, 1373991412, 512806799}

// Circular buffer

typedef struct {
    int buff[32];
    int writeIndex;
}buffer;

// IO buffers

// function pointers to handle the logic outs
// this type can be stored in a buffer cleanly

typedef void(*logicHandler)(void);

// store buffer pointers for the audio rate inputs and outputs

typedef struct {
	q31_t *samples;
	logicHandler *shAHandler;
	logicHandler *shBHandler;
	logicHandler *logicAHandler;
	logicHandler *logicBHandler;
	logicHandler *auxLogicHandler;
} audioRateOutputs;

// declare a struct to hold the current audio rate inputs

typedef struct {
	q31_t *t2CV;
	q31_t *morphCV;
	q31_t *hardSyncInput;
	q31_t *reverseInput;
} audioRateInputs;

// allocate a pair of buffers for each member of the above structs

q31_t sampleBuffer1[BUFFER_SIZE];
q31_t sampleBuffer2[BUFFER_SIZE];

logicHandler shABuffer1[BUFFER_SIZE];
logicHandler shABuffer2[BUFFER_SIZE];

logicHandler shBBuffer1[BUFFER_SIZE];
logicHandler shBBuffer2[BUFFER_SIZE];

logicHandler logicABuffer1[BUFFER_SIZE];
logicHandler logicABuffer2[BUFFER_SIZE];

logicHandler logicBBuffer1[BUFFER_SIZE];
logicHandler logicBBuffer2[BUFFER_SIZE];

logicHandler auxLogicBuffer1[BUFFER_SIZE];
logicHandler auxLogicBuffer2[BUFFER_SIZE];

q31_t t2CVBuffer1[BUFFER_SIZE];
q31_t t2CVBuffer2[BUFFER_SIZE];

q31_t morphCVBuffer1[BUFFER_SIZE];
q31_t morphCVBuffer2[BUFFER_SIZE];

uint32_t hardSyncBuffer1[BUFFER_SIZE];
uint32_t hardSyncBuffer2[BUFFER_SIZE];

int reverseBuffer1[BUFFER_SIZE];
int reverseBuffer2[BUFFER_SIZE];

// create a pair each of input and output structs
// create a pair of pointers for each for double buffering

audioRateOutputs output1;
audioRateOutputs output2;

audioRateOutputs *outputRead;
audioRateOutputs *outputWrite;

audioRateInputs input1;
audioRateInputs input2;

audioRateInputs *inputRead;
audioRateInputs *inputWrite;

typedef struct {
	q31_t knob1Value;
	q31_t knob2Value;
	q31_t knob3Value;
	q31_t cv1Value;
} controlRateInputs;

controlRateInputs controlRateInput;

int handleCoversionSlow(controlRateInputs *, uint32_t);

// Mode enums and mode variables

enum button1Modes {nosampleandhold, a, b, ab, antidecimate, decimate};
enum button3Modes {audio, env, seq};
enum button4Modes {noretrigger, hardsync, nongatedretrigger, gated, pendulum, pendulum2};
enum button6Modes {noloop, looping};
enum aux1Modes {triggerA, gateA, deltaA};
enum aux2Modes {triggerB, gateB, deltaB};
enum aux3Modes {APM, AM, A, M, PM, P};

enum button1Modes button1Mode;
enum button4Modes button4Mode;
enum button3Modes button3Mode;
enum button6Modes button6Mode;
enum aux1Modes aux1Mode;
enum aux2Modes aux2Mode;
enum aux3Modes aux3Mode;

int familyIndicator;

// function calling subfunctions to fill the sample buffer

void fillBuffer(void);

// pointer to the function that calculates samples and phase events

void (*getIncrements)(q31_t *, controlRateInputs *, q31_t *, int, int, int, q31_t *);

void getIncrementsAudio(q31_t *, controlRateInputs *, q31_t *, int, int, int, q31_t *);
void getIncrementsSimple(q31_t *, controlRateInputs *, q31_t *, int, int, int, q31_t *);
void getIncrementsComplex(q31_t *, controlRateInputs *, q31_t *, int, int, int, q31_t *);

int (*advancePhase)(q31_t *, q31_t *, int, int, q31_t *, q31_t *);

int advancePhaseLoopNoGate(q31_t *, q31_t *, int, int, q31_t *, q31_t *);
int advancePhaseLoopGate(q31_t *, q31_t *, int, int, q31_t *, q31_t *);
int advancePhaseNoLoopNoGate(q31_t *, q31_t *, int, int, q31_t *, q31_t *);
int advancePhaseNoLoopGate(q31_t *, q31_t *, int, int, q31_t *, q31_t *);

void (*getSamples)(q31_t *, int, q31_t *, q31_t *);

void getSamplesNoPWM(q31_t *, int, q31_t *, q31_t *);
void getSamplesPWM(q31_t *, int, q31_t *, q31_t *);

void (*calculateLogicA)(int *, logicHandler *);

void calculateLogicAGate(int *, logicHandler *);
void calculateLogicATrigger(int *, logicHandler *);
void calculateLogicADelta(int *, logicHandler *);

void (*calculateLogicB)(int *, logicHandler *);

void calculateLogicAGate(int *, logicHandler *);
void calculateLogicATrigger(int *, logicHandler *);
void calculateLogicADelta(int *, logicHandler *);

void calculateAuxLogic(int *, logicHandler *);

void (*calculateSHA)(int *, logicHandler *);

void calculateSHAMode1(int *, logicHandler *);
void calculateSHAMode2(int *, logicHandler *);
void calculateSHAMode3(int *, logicHandler *);
void calculateSHAMode4(int *, logicHandler *);
void calculateSHAMode5(int *, logicHandler *);
void calculateSHAMode6(int *, logicHandler *);

void (*calculateSHB)(int *, logicHandler *);

void calculateSHBMode1(int *, logicHandler *);
void calculateSHBMode2(int *, logicHandler *);
void calculateSHBMode3(int *, logicHandler *);
void calculateSHBMode4(int *, logicHandler *);
void calculateSHBMode5(int *, logicHandler *);
void calculateSHBMode6(int *, logicHandler *);

// initialization functions

void initializeFilter(void);
void initialializeVirtualGround(void);
void initializeDoubleBuffer(void);


// fixed point math functions

static inline int fix16_mul(int in0, int in1) {

	int lsb;
	  int msb;

	  // multiply the inputs, store the top 32 bits in msb and bottom in lsb

	  __asm ("SMULL %[result_1], %[result_2], %[input_1], %[input_2]"
	    : [result_1] "=r" (lsb), [result_2] "=r" (msb)
	    : [input_1] "r" (in0), [input_2] "r" (in1)
	  );

	  // reconstruct the result with a left shift by 16
	  // pack the bottom halfword of msb into the top halfword of the result
	  // top halfword of lsb goes into the bottom halfword of the result

	  return __ROR(__PKHBT(msb, lsb, 0), 16);

}

// doubting such an optimization would work here
// probaby not needed (called once per sample)

static inline int fix24_mul(int in0, int in1) {
	int64_t result = (uint64_t) in0 * in1;
	return result >> 24;
}


static inline int fix16_lerp(q31_t in0, q31_t in1, int frac) {
	return in0 + fix16_mul(in1 - in0, frac);

}

// this is a decent improvement over the above for the case of 16 bit interpolation points
// no need to cast a 16bit by 16bit multiplication to 64 bit

static inline int fast_16_16_mul(int in0, int in1) {
	return (in0 * in1) >> 16;
}

static inline int fast_16_16_lerp(int in0, int in1, int frac) {
	return in0 + fast_16_16_mul(in1 - in0, frac);
}

// twos complement absolute value

static inline int abs(int n) {
  int mask = n >> 31;
  return ((n + mask) ^ mask);
}



#endif


