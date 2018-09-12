/*
 * trigseq.h
 *
 *  Created on: Aug 21, 2018
 *      Author: willmitchell
 */

#ifndef INC_TRIGSEQ_H_
#define INC_TRIGSEQ_H_

#include "user_interface.h"
#include "sequencers.h"
#include "via_platform_binding.h"

/*
 *
 * Signals
 *
 */

dualEuclideanParameters trigseqParameters;

typedef struct {
	audioRateOutputs * outputs;
	audioRateInputs * inputs;
	controlRateInputs * controls;
	dualEuclideanParameters * parameters;
} trigseq_signal_set;

trigseq_signal_set trigseq_signals;

#define TRIGSEQ_BUFFER_SIZE 1

/*
 *
 * Event handlers
 *
 */

void trigseq_init(trigseq_signal_set *);

void trigseq_mainRisingEdgeCallback(trigseq_signal_set *);
void trigseq_mainFallingEdgeCallback(trigseq_signal_set *);

void trigseq_auxRisingEdgeCallback(trigseq_signal_set *);
void trigseq_auxFallingEdgeCallback(trigseq_signal_set *);

void trigseq_buttonPressedCallback(trigseq_signal_set *);
void trigseq_buttonPressedCallback(trigseq_signal_set *);

void trigseq_ioProcessCallback(trigseq_signal_set *);
void trigseq_halfTransferCallback(trigseq_signal_set *);
void trigseq_transferCompleteCallback(trigseq_signal_set *);
void trigseq_slowConversionCallback(trigseq_signal_set *);

/*
 *
 * Modes
 *
 */

// Mode enums and mode variables
#define SH_A_MODE button1Mode
#define AND_A_MODE button2Mode
#define A_PATTERN_BANK button3Mode
#define SH_B_MODE button4Mode
#define AND_B_MODE button5Mode
#define B_PATTERN_BANK button6Mode

#define LOGIC_MODE aux2Mode

#define numButton1Modes 3
#define numButton2Modes 2
#define numButton3Modes 8
#define numButton4Modes 3
#define numButton5Modes 2
#define numButton6Modes 8
#define numAux1Modes 0
#define numAux2Modes 4
#define numAux3Modes 0
#define numAux4Modes 0

enum trigseq_button1Modes {
	aNoSH, aResample, aSampleTrack
};
enum trigseq_button2Modes {
	andAoff, andAon
};
enum trigseq_button3Modes {
	aPatternBankSelections
};
enum trigseq_button4Modes {
	bNoSH, bResample, bSampleTrack
};
enum trigseq_button5Modes {
	andBoff, andBon
};
enum trigseq_button6Modes {
	bPatternBankSelections
};
enum trigseq_aux1Modes {
	trigseq_aux1NotUsed
};
enum trigseq_aux2Modes {
	and, or, xor, nand
};
enum trigseq_aux3Modes {
	trigseq_aux3NotUsed
};
enum trigseq_aux4Modes {
	trigseq_aux4NotUsed
};
/*
 *
 * UI implementation
 *
 */

void trigseq_handleButton1ModeChange(int);
void trigseq_handleButton2ModeChange(int);
void trigseq_handleButton3ModeChange(int);
void trigseq_handleButton4ModeChange(int);
void trigseq_handleButton5ModeChange(int);
void trigseq_handleButton6ModeChange(int);
void trigseq_handleAux1ModeChange(int);
void trigseq_handleAux2ModeChange(int);
void trigseq_handleAux3ModeChange(int);
void trigseq_handleAux4ModeChange(int);

void trigseq_handleButton1Tap(void);
void trigseq_handleButton2Tap(void);
void trigseq_handleButton3Tap(void);
void trigseq_handleButton4Tap(void);
void trigseq_handleButton5Tap(void);
void trigseq_handleButton6Tap(void);
void trigseq_handleAux1Tap(void);
void trigseq_handleAux2Tap(void);
void trigseq_handleAux3Tap(void);
void trigseq_handleAux4Tap(void);

void trigseq_handleButton1EnterMenu(void);
void trigseq_handleButton2EnterMenu(void);
void trigseq_handleButton3EnterMenu(void);
void trigseq_handleButton4EnterMenu(void);
void trigseq_handleButton5EnterMenu(void);
void trigseq_handleButton6EnterMenu(void);
void trigseq_handleAux1EnterMenu(void);
void trigseq_handleAux2EnterMenu(void);
void trigseq_handleAux3EnterMenu(void);
void trigseq_handleAux4EnterMenu(void);

void trigseq_handleButton1Tap(void);
void trigseq_handleButton2Tap(void);
void trigseq_handleButton3Tap(void);
void trigseq_handleButton4Tap(void);
void trigseq_handleButton5Tap(void);
void trigseq_handleButton6Tap(void);
void trigseq_handleAux1Tap(void);
void trigseq_handleAux2Tap(void);
void trigseq_handleAux3Tap(void);
void trigseq_handleAux4Tap(void);

void trigseq_handleButton1Hold(void);
void trigseq_handleButton2Hold(void);
void trigseq_handleButton3Hold(void);
void trigseq_handleButton4Hold(void);
void trigseq_handleButton5Hold(void);
void trigseq_handleButton6Hold(void);
void trigseq_handleAux1Hold(void);
void trigseq_handleAux2Hold(void);
void trigseq_handleAux3Hold(void);
void trigseq_handleAux4Hold(void);

void trigseq_initializeUICallbacks(void);

/*
 *
 * Tables
 *
 */

dualBooleanSequence *trigseq_patternBank[8];

void trigseq_initializePatterns(void);

#endif /* INC_TRIGSEQ_H_ */
