/*
 * osc.h
 *
 *  Created on: Aug 21, 2018
 *      Author: willmitchell
 */

#ifndef INC_OSC_H_
#define INC_OSC_H_

#include "oscillators.h"
#include "via_platform_binding.h"
#include "user_interface.h"

/*
 *
 * Signals
 *
 */

oversampledWavetableParameters oscParameters;

typedef struct {
	audioRateOutputs * outputs;
	audioRateInputs * inputs;
	controlRateInputs * controls;
	oversampledWavetableParameters * parameters;
} osc_signal_set;

osc_signal_set osc_signals;

#define OSC_BUFFER_SIZE 16

/*
 *
 * Event handlers
 *
 */

void osc_init(osc_signal_set *);

void osc_mainRisingEdgeCallback(osc_signal_set *);
void osc_mainFallingEdgeCallback(osc_signal_set *);

void osc_auxRisingEdgeCallback(osc_signal_set *);
void osc_auxFallingEdgeCallback(osc_signal_set *);

void osc_buttonPressedCallback(osc_signal_set *);
void osc_buttonPressedCallback(osc_signal_set *);

void osc_ioProcessCallback(osc_signal_set *);
void osc_halfTransferCallback(osc_signal_set *);
void osc_transferCompleteCallback(osc_signal_set *);
void osc_slowConversionCallback(osc_signal_set *);

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

enum osc_button1Modes {
	none, decimate
};
enum osc_button2Modes {
	yTables
};
enum osc_button3Modes {
	FM, PM
};
enum osc_button4Modes {
	hard, pendulum
};
enum osc_button5Modes {
	osc_pairedWithButton2
};
enum osc_button6Modes {
	morphCV, pwmCV
};
enum osc_aux1Modes {
	osc_aux1NotUsed
};
enum osc_aux2Modes {
	osc_aux2NotUsed
};
enum osc_aux3Modes {
	osc_aux3NotUsed
};
enum osc_aux4Modes {
	osc_aux4NotUsed
};

/*
 *
 * UI implementation
 *
 */

void osc_handleButton1ModeChange(int);
void osc_handleButton2ModeChange(int);
void osc_handleButton3ModeChange(int);
void osc_handleButton4ModeChange(int);
void osc_handleButton5ModeChange(int);
void osc_handleButton6ModeChange(int);
void osc_handleAux1ModeChange(int);
void osc_handleAux2ModeChange(int);
void osc_handleAux3ModeChange(int);
void osc_handleAux4ModeChange(int);

void osc_handleButton1Tap(void);
void osc_handleButton2Tap(void);
void osc_handleButton3Tap(void);
void osc_handleButton4Tap(void);
void osc_handleButton5Tap(void);
void osc_handleButton6Tap(void);
void osc_handleAux1Tap(void);
void osc_handleAux2Tap(void);
void osc_handleAux3Tap(void);
void osc_handleAux4Tap(void);

void osc_handleButton1EnterMenu(void);
void osc_handleButton2EnterMenu(void);
void osc_handleButton3EnterMenu(void);
void osc_handleButton4EnterMenu(void);
void osc_handleButton5EnterMenu(void);
void osc_handleButton6EnterMenu(void);
void osc_handleAux1EnterMenu(void);
void osc_handleAux2EnterMenu(void);
void osc_handleAux3EnterMenu(void);
void osc_handleAux4EnterMenu(void);

void osc_handleButton1Tap(void);
void osc_handleButton2Tap(void);
void osc_handleButton3Tap(void);
void osc_handleButton4Tap(void);
void osc_handleButton5Tap(void);
void osc_handleButton6Tap(void);
void osc_handleAux1Tap(void);
void osc_handleAux2Tap(void);
void osc_handleAux3Tap(void);
void osc_handleAux4Tap(void);

void osc_handleButton1Hold(void);
void osc_handleButton2Hold(void);
void osc_handleButton3Hold(void);
void osc_handleButton4Hold(void);
void osc_handleButton5Hold(void);
void osc_handleButton6Hold(void);
void osc_handleAux1Hold(void);
void osc_handleAux2Hold(void);
void osc_handleAux3Hold(void);
void osc_handleAux4Hold(void);

void osc_initializeUICallbacks(void);

/*
 *
 * Tables
 *
 */

// declare an array of pointers to wavetables (stored in flash)
Wavetable * osc_wavetableArray[8];

// declare arrays to store the active tables
uint32_t osc_wavetableRead[9][517];
uint32_t osc_phaseDistRead[33][65];

// declare functions to set the currently active tables
void osc_switchWavetable(Wavetable *, osc_signal_set * signals);
// phase distortion table is fixed
void osc_initPhaseDistTable(void);
void osc_fillWavetableArray(void);

#endif /* INC_OSC_H_ */
