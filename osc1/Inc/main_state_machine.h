#ifndef MAIN_STATE_MACHINE
#define MAIN_STATE_MACHINE


#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"

struct parameters {

	int coarsePitch;
	int finePitch;
	int voltOct;
	int xCV;
	int morph;
	int morphCV;
	int direction;

};



struct oscillator {

	int increment;
	int phase;

};

//declare output separately to be passed to the interrupt
int output;

/**
 *
 * Main oscillator state machine
 *
 */

enum mainSignal {

	MAIN_EXECUTE,
	MAIN_RISING_EDGE,
	MAIN_FALLING_EDGE,
	MAIN_AUX_RISING_EDGE,
	MAIN_AUX_FALLING_EDGE,
	MAIN_ADC1_CONV_COMPLETE,
	MAIN_ADC2_CONV_COMPLETE,
	MAIN_ADC3_CONV_COMPLETE,
	MAIN_AT_A,
	MAIN_AT_B,
	MAIN_TOWARDS_A,
	MAIN_TOWARDS_B,
	MAIN_DAC_TIMER_OVERRUN,
	MAIN_UPDATE_DISPLAY,

};

// main state machine
void (*main_State)(int);

// the idea here is to figure out a way to queue up requests to send signals (tasks) to the state machine
// requests are generated in the interrupt code
// requesting a task links it to the end of the task queue
// pushing a task adds it to the front of the queue

struct task {
	int signal;
	struct task *next;
};

typedef struct task Task;

Task *firstTask;
Task *lastTask;

Task nullTask;

Task taskQueue[128];

uint32_t queuePosition;

// dispatch task at front of queue to state machine
void mainDispatch(void);

// create a new task to be placed in the queue
Task* mainCreateTask(int, Task*);

// add a task to the end of the queue
void mainRequest(int);

// push a task to front of the queue
void mainPush(int);

/**
 *
 * States
 *
 */

// update logic outs then switch to led display state
void main_handleLogic(int);

// get next sample(s) then switch to ui handling state
void main_fillBuffer(int);

// execute the touch sensor state machine and expander button
void main_handleUI(int);

/**
 *
 * Main state machine helper functions
 *
 */

// parse the incoming signal to the correct handler function
void parseSignal(int);

// helper functions to parse hardware inputs and generate oscillator parameters


void handleADC1Conversion(void);
void handleADC2Conversion(void);
void handleADC3Conversion(void);
void handleDACTimerOverrun(void);

void handleRisingEdge(void);
void handleFallingEdge(void);
void handleAuxRisingEdge(void);
void handleAuxFallingEdge(void);

// wrapper for logic handling
void setLogicOutputs(void);

// wrapper for updating LED display
void updateRuntimeDisplay(void);

// wrappers for functions to fill sample buffer (separated to be later rolled into DSP loop)
uint32_t incrementOscillator(void);

// wrapper for implementing the UI
void implementUI(void);

#endif




