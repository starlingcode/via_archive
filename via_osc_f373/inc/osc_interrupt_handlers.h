#ifndef INTERRUPT_HANDLERS
#define INTERRUPT_HANDLERS

#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"
#include "signals.h"


void oscInit(viaSignals *);

void mainRisingEdgeCallback(viaSignals *);
void mainFallingEdgeCallback(viaSignals *);

void auxRisingEdgeCallback(viaSignals *);
void auxFallingEdgeCallback(viaSignals *);

void buttonPressedCallback(viaSignals *);
void buttonPressedCallback(viaSignals *);

// DMA handlers

void ioProcessCallback(viaSignals *);
void halfTransferCallback(viaSignals *);
void transferCompleteCallback(viaSignals *);
void slowConversionCallback(viaSignals *);



#endif
