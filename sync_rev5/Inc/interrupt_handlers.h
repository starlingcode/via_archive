#ifndef INTERRUPT_HANDLERS
#define INTERRUPT_HANDLERS

#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"
#include "dsp.h"

void mainRisingEdgeCallback(controlRateInputs * controls, audioRateInputs * inputs, softwareSignaling * softwareSignals);
void mainFallingEdgeCallback(softwareSignaling * softwareSignals);

void auxRisingEdgeCallback(void);
void auxFallingEdgeCallback(void);

void buttonPressedCallback(void);
void buttonPressedCallback(void);

void ioProcessCallback(audioRateInputs * inputWrite, audioRateOutputs * outputRead);
void nextSampleCallback(void);


#endif
