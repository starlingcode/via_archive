#ifndef INTERRUPT_HANDLERS
#define INTERRUPT_HANDLERS

#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"
#include "signals.h"

void syncInit(void);

void mainRisingEdgeCallback(signals *);
void mainFallingEdgeCallback(signals *);

void auxRisingEdgeCallback(signals *);
void auxFallingEdgeCallback(signals *);

void buttonPressedCallback(signals *);
void buttonPressedCallback(signals *);

void ioProcessCallback(signals *);
void generateSample(signals *);


#endif
