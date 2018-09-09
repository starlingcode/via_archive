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
} video_osc_signal_set;

video_osc_signal_set video_osc_signals;

#define VIDEO_OSC_BUFFER_SIZE 32

/*
 *
 * Event handlers
 *
 */

void video_osc_init(video_osc_signal_set *);

void video_osc_mainRisingEdgeCallback(video_osc_signal_set *);
void video_osc_mainFallingEdgeCallback(video_osc_signal_set *);

void video_osc_auxRisingEdgeCallback(video_osc_signal_set *);
void video_osc_auxFallingEdgeCallback(video_osc_signal_set *);

void video_osc_buttonPressedCallback(video_osc_signal_set *);
void video_osc_buttonPressedCallback(video_osc_signal_set *);

void video_osc_ioProcessCallback(video_osc_signal_set *);
void video_osc_halfTransferCallback(video_osc_signal_set *);
void video_osc_transferCompleteCallback(video_osc_signal_set *);
void video_osc_slowConversionCallback(video_osc_signal_set *);

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

enum video_osc_button1Modes {
	none, decimate
};
enum video_osc_button2Modes {
	yTables
};
enum video_osc_button3Modes {
	FM, PM
};
enum video_osc_button4Modes {
	hard, pendulum
};
enum video_osc_button5Modes {
	video_osc_pairedWithButton2
};
enum video_osc_button6Modes {
	morphCV, pwmCV
};
enum video_osc_aux1Modes {
	video_osc_aux1NotUsed
};
enum video_osc_aux2Modes {
	video_osc_aux2NotUsed
};
enum video_osc_aux3Modes {
	video_osc_aux3NotUsed
};
enum video_osc_aux4Modes {
	video_osc_aux4NotUsed
};

/*
 *
 * UI implementation
 *
 */

void video_osc_handleButton1ModeChange(int);
void video_osc_handleButton2ModeChange(int);
void video_osc_handleButton3ModeChange(int);
void video_osc_handleButton4ModeChange(int);
void video_osc_handleButton5ModeChange(int);
void video_osc_handleButton6ModeChange(int);
void video_osc_handleAux1ModeChange(int);
void video_osc_handleAux2ModeChange(int);
void video_osc_handleAux3ModeChange(int);
void video_osc_handleAux4ModeChange(int);

void video_osc_handleButton1Tap(void);
void video_osc_handleButton2Tap(void);
void video_osc_handleButton3Tap(void);
void video_osc_handleButton4Tap(void);
void video_osc_handleButton5Tap(void);
void video_osc_handleButton6Tap(void);
void video_osc_handleAux1Tap(void);
void video_osc_handleAux2Tap(void);
void video_osc_handleAux3Tap(void);
void video_osc_handleAux4Tap(void);

void video_osc_handleButton1EnterMenu(void);
void video_osc_handleButton2EnterMenu(void);
void video_osc_handleButton3EnterMenu(void);
void video_osc_handleButton4EnterMenu(void);
void video_osc_handleButton5EnterMenu(void);
void video_osc_handleButton6EnterMenu(void);
void video_osc_handleAux1EnterMenu(void);
void video_osc_handleAux2EnterMenu(void);
void video_osc_handleAux3EnterMenu(void);
void video_osc_handleAux4EnterMenu(void);

void video_osc_handleButton1Tap(void);
void video_osc_handleButton2Tap(void);
void video_osc_handleButton3Tap(void);
void video_osc_handleButton4Tap(void);
void video_osc_handleButton5Tap(void);
void video_osc_handleButton6Tap(void);
void video_osc_handleAux1Tap(void);
void video_osc_handleAux2Tap(void);
void video_osc_handleAux3Tap(void);
void video_osc_handleAux4Tap(void);

void video_osc_handleButton1Hold(void);
void video_osc_handleButton2Hold(void);
void video_osc_handleButton3Hold(void);
void video_osc_handleButton4Hold(void);
void video_osc_handleButton5Hold(void);
void video_osc_handleButton6Hold(void);
void video_osc_handleAux1Hold(void);
void video_osc_handleAux2Hold(void);
void video_osc_handleAux3Hold(void);
void video_osc_handleAux4Hold(void);

void video_osc_initializeUICallbacks(void);

/*
 *
 * Tables
 *
 */

// declare an array of pointers to wavetables (stored in flash)
Wavetable * video_osc_wavetableArray[8];

// declare arrays to store the active tables
uint32_t video_osc_wavetableRead[9][517];
uint32_t video_osc_phaseDistRead[33][65];

// declare functions to set the currently active tables
void video_osc_switchWavetable(Wavetable *, video_osc_signal_set * signals);
// phase distortion table is fixed
void video_osc_initPhaseDistTable(void);
void video_osc_fillWavetableArray(void);

#endif /* INC_OSC_H_ */
