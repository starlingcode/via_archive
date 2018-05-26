#ifndef DSP_H
#define DSP_H

#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"
#define ARM_MATH_CM4
#include "arm_math.h"


#define BUFFER_SIZE 8

#define NUM_TAPS 24

#define FIR8TAPS1_24 {37653504, 103041591, 262708334, 424417055, 491842679, 424417055, 262708334, 103041591 , 37653504}

#define FIR16TAPS5_24 {-5268880, 20286907, 45192374, -47794798, -227426832, -51762506, 769600018, 1644657365, 1644657365, 769600018, -51762506, -227426832, -47794798, 45192374, 20286907, -5268880}

#define FIR24TAPS6_24 {1499280, 3097718, -6929872, -34955643, -49795015, -9487274, 49070362, 22354339, -80649134, -68021400, 179184179, 459216960, 459216960, 179184179, -68021400, -80649134, 22354339, 49070362, -9487274, -49795015, -34955643, -6929872, 3097718, 1499280}

#define FIR24TAPS5_12 {3016239, 5738308, -1679970, -18021039, -10780765, 37693189, 55436335, -41562717, -155240046, -30053218, 404571402, 824624103, 824624103, 404571402, -30053218, -155240046, -41562717, 55436335, 37693189, -10780765, -18021039, -1679970, 5738308, 3016239}

// IO buffers

// function pointers to handle the logic outs
// this type can be stored in a buffer cleanly
typedef struct {
	void (*shAHandler)(void);
	void (*shBHandler)(void);
	void (*logicAHandler)(void);
	void (*logicBHandler)(void);
	void (*auxLogicHandler)(void);
} logicState;

// store buffer pointers for the audio rate inputs and outputs
typedef struct {
	q31_t *samples;
	logicState *logicStates;
} audioRateOutputs;

// declare a struct to hold the current audio rate inputs
typedef struct {
	q31_t *xCV;
	q31_t *morphCV;
	q31_t *hardSyncInput;
	q31_t *reverseInput;
} audioRateInputs;

// allocate a pair of buffers for each member of the above structs

q31_t sampleBuffer1[BUFFER_SIZE];
q31_t sampleBuffer2[BUFFER_SIZE];

q31_t xCVBuffer1[BUFFER_SIZE];
q31_t xCVBuffer2[BUFFER_SIZE];

q31_t morphCVBuffer1[BUFFER_SIZE];
q31_t morphCVBuffer2[BUFFER_SIZE];

uint32_t hardSyncBuffer1[BUFFER_SIZE];
uint32_t hardSyncBuffer2[BUFFER_SIZE];

int reverseBuffer1[BUFFER_SIZE];
int reverseBuffer2[BUFFER_SIZE];

logicState logicStateBuffer1[BUFFER_SIZE];
logicState logicStateBuffer2[BUFFER_SIZE];

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

void (*fillBuffer)(void);

void fillBufferSHOn(void);
void fillBufferSHOff(void);

void handleCoversionSlow(controlRateInputs *);

// pointer to the function that calculates samples and phase events
void (*incrementOscillator)(audioRateInputs *, controlRateInputs *, audioRateOutputs *, uint32_t *, uint32_t);

void incrementOscillatorFM_Morph(audioRateInputs *, controlRateInputs *, audioRateOutputs *, uint32_t *, uint32_t);
void incrementOscillatorPM_Morph(audioRateInputs *, controlRateInputs *, audioRateOutputs *, uint32_t *, uint32_t);


// parse the phase events into logic outputs
void calculateLogicSHOn(uint32_t *, audioRateOutputs *, uint32_t);

// parse the phase events into logic outputs
void calculateLogicSHOff(uint32_t *, audioRateOutputs *, uint32_t);

// logic output helper functions
void logicInit(void);

void logicAHigh(void);
void logicALow(void);
void logicBHigh(void);
void logicBLow(void);
void shASample(void);
void shATrack(void);
void shBSample(void);
void shBTrack(void);
void holdLogic(void);

void initializeFilter();

void initializeDoubleBuffer();

#endif


