#ifndef VIA_UI_IMPLEMENTATION_H
#define VIA_UI_IMPLEMENTATION_H

#include "user_interface.h"
#include "signals.h"

void handleButton1ModeChange(int);
void handleButton2ModeChange(int);
void handleButton3ModeChange(int);
void handleButton4ModeChange(int);
void handleButton5ModeChange(int);
void handleButton6ModeChange(int);
void handleAux1ModeChange(int);
void handleAux2ModeChange(int);
void handleAux3ModeChange(int);
void handleAux4ModeChange(int);


void handleButton1Tap(void);
void handleButton2Tap(void);
void handleButton3Tap(void);
void handleButton4Tap(void);
void handleButton5Tap(void);
void handleButton6Tap(void);
void handleAux1Tap(void);
void handleAux2Tap(void);
void handleAux3Tap(void);
void handleAux4Tap(void);

void handleButton1EnterMenu(void);
void handleButton2EnterMenu(void);
void handleButton3EnterMenu(void);
void handleButton4EnterMenu(void);
void handleButton5EnterMenu(void);
void handleButton6EnterMenu(void);
void handleAux1EnterMenu(void);
void handleAux2EnterMenu(void);
void handleAux3EnterMenu(void);
void handleAux4EnterMenu(void);

void handleButton1Tap(void);
void handleButton2Tap(void);
void handleButton3Tap(void);
void handleButton4Tap(void);
void handleButton5Tap(void);
void handleButton6Tap(void);
void handleAux1Tap(void);
void handleAux2Tap(void);
void handleAux3Tap(void);
void handleAux4Tap(void);

void handleButton1Hold(void);
void handleButton2Hold(void);
void handleButton3Hold(void);
void handleButton4Hold(void);
void handleButton5Hold(void);
void handleButton6Hold(void);
void handleAux1Hold(void);
void handleAux2Hold(void);
void handleAux3Hold(void);
void handleAux4Hold(void);

void (*updateRGB)(controlRateInputs *, audioRateInputs *, int, int);
void updateRGBAudio(controlRateInputs *, audioRateInputs *, int, int);
void updateRGBSubAudio(controlRateInputs *, audioRateInputs *, int, int);
void updateRGBTrigger(controlRateInputs *, audioRateInputs *, int, int);
void updateRGBBlank(controlRateInputs *, audioRateInputs *, int, int);

#endif