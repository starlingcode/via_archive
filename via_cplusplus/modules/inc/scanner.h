/*
 * scanner.h
 *
 *  Created on: Aug 21, 2018
 *      Author: willmitchell
 */

#ifndef INC_SCANNER_H_
#define INC_SCANNER_H_

#include "user_interface.h"
#include "via_platform_binding.h"
#include "signal_processors.h"
#include "tables.h"

/*
 *
 * Signals
 *
 */

typedef struct {
	audioRateOutputs * outputs;
	audioRateInputs * inputs;
	controlRateInputs * controls;
	threeAxisScannerParameters * parameters;
} scanner_signal_set;

threeAxisScannerParameters scannerParameters;
scanner_signal_set scanner_signals;

#define SCANNER_BUFFER_SIZE 8

/*
 *
 * Event handlers
 *
 */

void scanner_init(scanner_signal_set *);

void scanner_mainRisingEdgeCallback(scanner_signal_set *);
void scanner_mainFallingEdgeCallback(scanner_signal_set *);

void scanner_auxRisingEdgeCallback(scanner_signal_set *);
void scanner_auxFallingEdgeCallback(scanner_signal_set *);

void scanner_buttonPressedCallback(scanner_signal_set *);
void scanner_buttonPressedCallback(scanner_signal_set *);

void scanner_ioProcessCallback(scanner_signal_set *);
void scanner_halfTransferCallback(scanner_signal_set *);
void scanner_transferCompleteCallback(scanner_signal_set *);
void scanner_slowConversionCallback(scanner_signal_set *);

/*
 *
 * Modes
 *
 */

#define X_TABLE button4Mode
#define Y_TABLE button2Mode
#define SYNC_MODE button1Mode
#define TERRAIN button3Mode

#define numButton1Modes 2
#define numButton2Modes 8
#define numButton3Modes 4
#define numButton4Modes 8
#define numButton5Modes 8
#define numButton6Modes 8
#define numAux1Modes 0
#define numAux2Modes 0
#define numAux3Modes 3
#define numAux4Modes 2

enum button1Modes {
	reverse, hardsync
};
enum button2Modes {
	yTables
};
enum button3Modes {
	sum, subtract, product, phaseMod
};
enum button4Modes {
	xTables
};
enum button5Modes {
	pairedWithButton2
};
enum button6Modes {
	pairedWithButton3
};
enum aux1Modes {
	aux1NotUsed
};
enum aux2Modes {
	aux2NotUsed
};
enum aux3Modes {
	aux3NotUsed
};
enum aux4Modes {
	aux4NotUsed
};

/*
 *
 * UI implementation
 *
 */

void scanner_handleButton1ModeChange(int);
void scanner_handleButton2ModeChange(int);
void scanner_handleButton3ModeChange(int);
void scanner_handleButton4ModeChange(int);
void scanner_handleButton5ModeChange(int);
void scanner_handleButton6ModeChange(int);
void scanner_handleAux1ModeChange(int);
void scanner_handleAux2ModeChange(int);
void scanner_handleAux3ModeChange(int);
void scanner_handleAux4ModeChange(int);

void scanner_handleButton1Tap(void);
void scanner_handleButton2Tap(void);
void scanner_handleButton3Tap(void);
void scanner_handleButton4Tap(void);
void scanner_handleButton5Tap(void);
void scanner_handleButton6Tap(void);
void scanner_handleAux1Tap(void);
void scanner_handleAux2Tap(void);
void scanner_handleAux3Tap(void);
void scanner_handleAux4Tap(void);

void scanner_handleButton1EnterMenu(void);
void scanner_handleButton2EnterMenu(void);
void scanner_handleButton3EnterMenu(void);
void scanner_handleButton4EnterMenu(void);
void scanner_handleButton5EnterMenu(void);
void scanner_handleButton6EnterMenu(void);
void scanner_handleAux1EnterMenu(void);
void scanner_handleAux2EnterMenu(void);
void scanner_handleAux3EnterMenu(void);
void scanner_handleAux4EnterMenu(void);

void scanner_handleButton1Tap(void);
void scanner_handleButton2Tap(void);
void scanner_handleButton3Tap(void);
void scanner_handleButton4Tap(void);
void scanner_handleButton5Tap(void);
void scanner_handleButton6Tap(void);
void scanner_handleAux1Tap(void);
void scanner_handleAux2Tap(void);
void scanner_handleAux3Tap(void);
void scanner_handleAux4Tap(void);

void scanner_handleButton1Hold(void);
void scanner_handleButton2Hold(void);
void scanner_handleButton3Hold(void);
void scanner_handleButton4Hold(void);
void scanner_handleButton5Hold(void);
void scanner_handleButton6Hold(void);
void scanner_handleAux1Hold(void);
void scanner_handleAux2Hold(void);
void scanner_handleAux3Hold(void);
void scanner_handleAux4Hold(void);

void scanner_initializeUICallbacks(void);

/*
 *
 * Tables
 *
 */

// declare an array of pointers to wavetables (stored in flash)
const Wavetable * scanner_wavetableArray[8];

// declare arrays to store the active tables
uint32_t scanner_wavetableXRead[5][517];
uint32_t scanner_wavetableYRead[5][517];

void scanner_fillWavetableArray(void);

// declare functions to set the currently active tables
void scanner_switchWavetableX(Wavetable *, scanner_signal_set * signals);
void scanner_switchWavetableY(Wavetable *, scanner_signal_set * signals);

// phase distortion table is fixed
void scanner_initPhaseDistTable(void);

int scanner_reverseBuffer[SCANNER_BUFFER_SIZE*2];
int scanner_reverseSignal;

#endif /* INC_SCANNER_H_ */
