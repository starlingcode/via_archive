/*
 * sync.h
 *
 *  Created on: Aug 26, 2018
 *      Author: willmitchell
 */

#ifndef INC_SYNC_H_
#define INC_SYNC_H_

#include "via_platform_binding.h"
#include "oscillators.h"


singleSampleWavetableParameters syncParameters;

typedef struct {
	audioRateOutputs * outputs;
	audioRateInputs * inputs;
	controlRateInputs * controls;
	singleSampleWavetableParameters * parameters;
} sync_signal_set;

sync_signal_set sync_signals;

#define SYNC_BUFFER_SIZE 1

/*
 *
 * Event handlers
 *
 */

void sync_init(sync_signal_set *);

void sync_mainRisingEdgeCallback(sync_signal_set *);
void sync_mainFallingEdgeCallback(sync_signal_set *);

void sync_auxRisingEdgeCallback(sync_signal_set *);
void sync_auxFallingEdgeCallback(sync_signal_set *);

void sync_buttonPressedCallback(sync_signal_set *);
void sync_buttonPressedCallback(sync_signal_set *);

void sync_ioProcessCallback(sync_signal_set *);
void sync_halfTransferCallback(sync_signal_set *);
void sync_transferCompleteCallback(sync_signal_set *);
void sync_slowConversionCallback(sync_signal_set *);

/*
 *
 * Modes
 *
 */

#define SH_MODE button1Mode
#define TABLE button2Mode
#define FM_PM_MODE button3Mode
#define SYNC_MODE button4Mode
#define MORPH_PWM_MODE button6Mode

#define AUX4_MODE_USED

#define numButton1Modes 2
#define numButton2Modes 8
#define numButton3Modes 2
#define numButton4Modes 2
#define numButton5Modes 8
#define numButton6Modes 2
#define numAux1Modes 0
#define numAux2Modes 0
#define numAux3Modes 0
#define numAux4Modes 0

enum sync_button1Modes {
	none, decimate
};
enum sync_button2Modes {
	yTables
};
enum sync_button3Modes {
	FM, PM
};
enum sync_button4Modes {
	hard, pendulum
};
enum sync_button5Modes {
	sync_pairedWithButton2
};
enum sync_button6Modes {
	morphCV, pwmCV
};
enum sync_aux1Modes {
	sync_aux1NotUsed
};
enum sync_aux2Modes {
	sync_aux2NotUsed
};
enum sync_aux3Modes {
	sync_aux3NotUsed
};
enum sync_aux4Modes {
	sync_aux4NotUsed
};

/*
 *
 * UI implementation
 *
 */

void sync_handleButton1ModeChange(int);
void sync_handleButton2ModeChange(int);
void sync_handleButton3ModeChange(int);
void sync_handleButton4ModeChange(int);
void sync_handleButton5ModeChange(int);
void sync_handleButton6ModeChange(int);
void sync_handleAux1ModeChange(int);
void sync_handleAux2ModeChange(int);
void sync_handleAux3ModeChange(int);
void sync_handleAux4ModeChange(int);

void sync_handleButton1Tap(void);
void sync_handleButton2Tap(void);
void sync_handleButton3Tap(void);
void sync_handleButton4Tap(void);
void sync_handleButton5Tap(void);
void sync_handleButton6Tap(void);
void sync_handleAux1Tap(void);
void sync_handleAux2Tap(void);
void sync_handleAux3Tap(void);
void sync_handleAux4Tap(void);

void sync_handleButton1EnterMenu(void);
void sync_handleButton2EnterMenu(void);
void sync_handleButton3EnterMenu(void);
void sync_handleButton4EnterMenu(void);
void sync_handleButton5EnterMenu(void);
void sync_handleButton6EnterMenu(void);
void sync_handleAux1EnterMenu(void);
void sync_handleAux2EnterMenu(void);
void sync_handleAux3EnterMenu(void);
void sync_handleAux4EnterMenu(void);

void sync_handleButton1Tap(void);
void sync_handleButton2Tap(void);
void sync_handleButton3Tap(void);
void sync_handleButton4Tap(void);
void sync_handleButton5Tap(void);
void sync_handleButton6Tap(void);
void sync_handleAux1Tap(void);
void sync_handleAux2Tap(void);
void sync_handleAux3Tap(void);
void sync_handleAux4Tap(void);

void sync_handleButton1Hold(void);
void sync_handleButton2Hold(void);
void sync_handleButton3Hold(void);
void sync_handleButton4Hold(void);
void sync_handleButton5Hold(void);
void sync_handleButton6Hold(void);
void sync_handleAux1Hold(void);
void sync_handleAux2Hold(void);
void sync_handleAux3Hold(void);
void sync_handleAux4Hold(void);

void sync_initializeUICallbacks(void);

/*
 *
 * Tables
 *
 */

// declare an array of pointers to wavetables (stored in flash)
Wavetable * sync_wavetableArray[8];

// declare arrays to store the active tables
uint32_t sync_wavetableRead[9][517];
uint32_t sync_phaseDistRead[33][65];

// declare functions to set the currently active tables
void sync_switchWavetable(Wavetable *, sync_signal_set * signals);
// phase distortion table is fixed
void sync_initPhaseDistTable(void);
void sync_fillWavetableArray(void);


#endif /* INC_SYNC_H_ */
