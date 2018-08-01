#ifndef INTERRUPT_HANDLERS
#define INTERRUPT_HANDLERS

#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"
#include "dsp.h"

void trigseqInit(void);

// main handlers

void mainRisingEdgeCallback(controlRateInputs *, audioRateInputs *, softwareSignaling *);
void mainFallingEdgeCallback(softwareSignaling *);

void auxRisingEdgeCallback(softwareSignaling *);
void auxFallingEdgeCallback(softwareSignaling *);

void buttonPressedCallback(softwareSignaling *);
void buttonPressedCallback(softwareSignaling *);

void ioProcessCallback(audioRateInputs *, controlRateInputs *, audioRateOutputs *);
void nextSampleCallback(softwareSignaling *, audioRateOutputs *);

// helper functions

void (*manageADac)(softwareSignaling *, audioRateOutputs *);
void (*manageBDac)(softwareSignaling *, audioRateOutputs *);

void dacAHigh(softwareSignaling *, audioRateOutputs *);
void dacALow(softwareSignaling *, audioRateOutputs *);

void dacARise(softwareSignaling *, audioRateOutputs *);
void dacAFall(softwareSignaling *, audioRateOutputs *);

void dacBHigh(softwareSignaling *, audioRateOutputs *);
void dacBLow(softwareSignaling *, audioRateOutputs *);

void dacBRise(softwareSignaling *, audioRateOutputs *);
void dacBFall(softwareSignaling *, audioRateOutputs *);

void handleAHigh(softwareSignaling *);
void handleALow(softwareSignaling *);

void handleBHigh(softwareSignaling *);
void handleBLow(softwareSignaling *);

void handleAuxHigh(softwareSignaling *);
void handleAuxLow(softwareSignaling *);

void processClock(controlRateInputs *, audioRateInputs *, softwareSignaling *);

void doLogic(softwareSignaling *);
void handleFallingEdge(softwareSignaling *);

void resampleA(void);
void resampleB(void);


#endif
