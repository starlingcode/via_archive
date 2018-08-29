/*
 * meta.h
 *
 *  Created on: Aug 29, 2018
 *      Author: willmitchell
 */

#ifndef INC_META_H_
#define INC_META_H_


#include "via_platform_binding.h"
#include "user_interface.h"
#include "oscillators.h"


singleSampleWavetableParameters wavetableParameters;

pllMultiplierParameters pllParameters;

typedef struct {

	audioRateOutputs * outputs;
	audioRateInputs * inputs;
	controlRateInputs * controls;
	singleSampleWavetableParameters * wavetable_parameters;
	pllMultiplierParameters * pll_parameters;

} meta_signal_set;

meta_signal_set meta_signals;

#define SYNC_BUFFER_SIZE 1

/*
 *
 * Event handlers
 *
 */

void meta_init(meta_signal_set *);

void meta_mainRisingEdgeCallback(meta_signal_set *);
void meta_mainFallingEdgeCallback(meta_signal_set *);

void meta_auxRisingEdgeCallback(meta_signal_set *);
void meta_auxFallingEdgeCallback(meta_signal_set *);

void meta_buttonPressedCallback(meta_signal_set *);
void meta_buttonPressedCallback(meta_signal_set *);

void meta_ioProcessCallback(meta_signal_set *);
void meta_halfTransferCallback(meta_signal_set *);
void meta_transferCompleteCallback(meta_signal_set *);
void meta_slowConversionCallback(meta_signal_set *);

/*
 *
 * Modes
 *
 */

// Mode enums and mode variables

#define SH_MODE button1Mode
#define SCALE_MODE button2Mode
#define X_MODE button3Mode
#define SYNC_MODE button4Mode
#define GROUP_MODE button5Mode
#define TABLE_MODE button6Mode
#define QUADRATURE_MODE aux2Mode
#define LOGIC_A_MODE aux3Mode
#define TABLE_GROUP_MODE aux4Mode

#define numButton1Modes 3
#define numButton2Modes 4
#define numButton3Modes 4
#define numButton4Modes 3
#define numButton5Modes 4
#define numButton6Modes 4
#define numAux1Modes 0
#define numAux2Modes 2
#define numAux3Modes 4
#define numAux4Modes 2

enum meta_button1Modes {noSH, sampletrack, resample};
enum meta_button2Modes {scale1, scale2, scale3, scale4};
enum meta_button3Modes {root, pm, fm, pwm};
enum meta_button4Modes {nosync, true, hardsync};
enum meta_button5Modes {group1, group2, group3, group4};
enum meta_button6Modes {table1, table2, table3, table4};
enum meta_aux1Modes {meta_aux1NotUsed};
enum meta_aux2Modes {gate, delta};
enum meta_aux3Modes {noOffset, quarter, half, threeQuarters};
enum meta_aux4Modes {groupSpecific, global};


/*
 *
 * UI implementation
 *
 */

void meta_handleButton1ModeChange(int);
void meta_handleButton2ModeChange(int);
void meta_handleButton3ModeChange(int);
void meta_handleButton4ModeChange(int);
void meta_handleButton5ModeChange(int);
void meta_handleButton6ModeChange(int);
void meta_handleAux1ModeChange(int);
void meta_handleAux2ModeChange(int);
void meta_handleAux3ModeChange(int);
void meta_handleAux4ModeChange(int);

void meta_handleButton1Tap(void);
void meta_handleButton2Tap(void);
void meta_handleButton3Tap(void);
void meta_handleButton4Tap(void);
void meta_handleButton5Tap(void);
void meta_handleButton6Tap(void);
void meta_handleAux1Tap(void);
void meta_handleAux2Tap(void);
void meta_handleAux3Tap(void);
void meta_handleAux4Tap(void);

void meta_handleButton1EnterMenu(void);
void meta_handleButton2EnterMenu(void);
void meta_handleButton3EnterMenu(void);
void meta_handleButton4EnterMenu(void);
void meta_handleButton5EnterMenu(void);
void meta_handleButton6EnterMenu(void);
void meta_handleAux1EnterMenu(void);
void meta_handleAux2EnterMenu(void);
void meta_handleAux3EnterMenu(void);
void meta_handleAux4EnterMenu(void);

void meta_handleButton1Tap(void);
void meta_handleButton2Tap(void);
void meta_handleButton3Tap(void);
void meta_handleButton4Tap(void);
void meta_handleButton5Tap(void);
void meta_handleButton6Tap(void);
void meta_handleAux1Tap(void);
void meta_handleAux2Tap(void);
void meta_handleAux3Tap(void);
void meta_handleAux4Tap(void);

void meta_handleButton1Hold(void);
void meta_handleButton2Hold(void);
void meta_handleButton3Hold(void);
void meta_handleButton4Hold(void);
void meta_handleButton5Hold(void);
void meta_handleButton6Hold(void);
void meta_handleAux1Hold(void);
void meta_handleAux2Hold(void);
void meta_handleAux3Hold(void);
void meta_handleAux4Hold(void);

void meta_initializeUICallbacks(void);

/*
 *
 * Tables
 *
 */

// declare an array of pointers to wavetables (stored in flash)
Wavetable * meta_wavetableArray[3][8];

// declare arrays to store the active tables
uint32_t meta_wavetableRead[9][517];
//uint32_t meta_phaseDistRead[33][65];

// declare functions to set the currently active tables
void meta_switchWavetable(Wavetable *, meta_signal_set * signals);
void meta_switchWavetableGlobal(Wavetable *, meta_signal_set * signals);
// phase distortion table is fixed
void meta_initPhaseDistTable(void);
void meta_fillWavetableArray(void);

#endif /* INC_META_H_ */
