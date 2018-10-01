#ifndef INTERRUPT_HANDLERS
#define INTERRUPT_HANDLERS

#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"
#include "signals.h"


void syncInit(void);

void mainRisingEdgeCallback(osc_signals *);
void mainFallingEdgeCallback(osc_signals *);

void auxRisingEdgeCallback(osc_signals *);
void auxFallingEdgeCallback(osc_signals *);

void buttonPressedCallback(osc_signals *);
void buttonPressedCallback(osc_signals *);

// DMA handlers

void ioProcessCallback(osc_signals *);
void halfTransferCallback(osc_signals *);
void transferCompleteCallback(osc_signals *);
void slowConversionCallback(osc_signals *);



#endif
