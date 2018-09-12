/*
 * meta.hpp
 *
 *  Created on: Sep 11, 2018
 *      Author: willmitchell
 */

#ifndef INC_META_HPP_
#define INC_META_HPP_

#include "../../ui/inc/user_interface.hpp"
#include "via_platform_binding.h"
#include "oscillators.h"

typedef struct {

	audioRateOutputs * outputs;
	audioRateInputs * inputs;
	controlRateInputs * controls;
	simpleWavetableParameters * wavetable_parameters;
	metaControllerParameters * meta_parameters;
	simpleEnvelopeParameters * drum_parameters;

} meta_signal_set;

#define META_BUFFER_SIZE 1

/*
 *
 * Modes
 *
 */

// Mode enums and mode variables

#define SH_MODE button1Mode
#define TABLE button2Mode
#define TRIG_MODE button4Mode
#define FREQ_MODE button3Mode
#define LOOP_MODE button6Mode
#define LOGIC_A_MODE aux2Mode
#define DRUM_MODE aux3Mode
#define DAC_3_MODE aux4Mode


#define numButton1Modes 6
#define numButton2Modes 8
#define numButton3Modes 3
#define numButton4Modes 5
#define numButton5Modes 8
#define numButton6Modes 2
#define numAux1Modes 0
#define numAux2Modes 2
#define numAux3Modes 4
#define numAux4Modes 2

enum meta_button1Modes {nosampleandhold, a, b, ab, halfdecimate, meta_decimate};
enum meta_button2Modes {tables};
enum meta_button3Modes {audio, env, seq};
enum meta_button4Modes {noretrigger, meta_hardsync, nongatedretrigger, gated, meta_pendulum};
enum meta_button5Modes {pairedWithButton2};
enum meta_button6Modes {noloop, looping};
enum meta_aux1Modes {aux1NotUsed};
enum meta_aux2Modes {releaseGate, attackGate};
enum meta_aux3Modes {pitchMorphAmp, morphAmp, pitchAmp, amp};
enum meta_aux4Modes {phasor, contour};


class ViaMeta {

public:

	/*
	 *
	 * UI implementation
	 *
	 */

	class ViaMetaUI: public ViaUI {

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

		void button1TapCallback(void);
		void button1HoldCallback(void);
		void button2TapCallback(void);
		void button2HoldCallback(void);
		void button3TapCallback(void);
		void button3HoldCallback(void);
		void button4TapCallback(void);
		void button4HoldCallback(void);
		void button5TapCallback(void);
		void button5HoldCallback(void);
		void button6TapCallback(void);
		void button6HoldCallback(void);

		void aux1TapCallback(void);
		void aux1HoldCallback(void);
		void aux2TapCallback(void);
		void aux2HoldCallback(void);
		void aux3TapCallback(void);
		void aux3HoldCallback(void);
		void aux4TapCallback(void);
		void aux4HoldCallback(void);

		void defaultEnterMenuCallback(void);
		void newModeEnterMenuCallback(void);
		void newAuxModeEnterMenuCallback(void);
		void presetEnterMenuCallback(void);

		void button1EnterMenuCallback(void);
		void button2EnterMenuCallback(void);
		void button3EnterMenuCallback(void);
		void button4EnterMenuCallback(void);
		void button5EnterMenuCallback(void);
		void button6EnterMenuCallback(void);

		void aux1EnterMenuCallback(void);
		void aux2EnterMenuCallback(void);
		void aux3EnterMenuCallback(void);
		void aux4EnterMenuCallback(void);

	};

	meta_signal_set signals;

	simpleWavetableParameters meta_wavetableParameters;
	metaControllerParameters metaParameters;
	simpleEnvelopeParameters drumParameters;

	/*
	 *
	 * Event meta_handlers
	 *
	 */

	void init(void);

	void mainRisingEdgeCallback(void);
	void mainFallingEdgeCallback(void);

	void auxRisingEdgeCallback(void);
	void auxFallingEdgeCallback(void);

	void buttonPressedCallback(void);
	void buttonReleasedCallback(void);

	void ioProcessCallback(void);
	void halfTransferCallback(void);
	void transferCompleteCallback(void);
	void slowConversionCallback(void);


	/*
	 *
	 * Tables
	 *
	 */

	// declare an array of pointers to wavetables (stored in flash)
	Wavetable * wavetableArray[3][8];

	// declare arrays to store the active tables
	uint32_t wavetableRead[9][517];
	uint32_t wavetableReadDrum[517];

	//uint32_t meta_phaseDistRead[33][65];

	// declare functions to set the currently active tables
	void switchWavetable(Wavetable *);
	// phase distortion table is fixed
	void initPhaseDistTable(void);
	void fillWavetableArray(void);
	void initDrum(void);
	int16_t drumWrite[4];
	int16_t drumFullScale[4];

	/*
	 *
	 * Mode functions
	 *
	 */

	void (ViaMeta::*drumMode)(int writeIndex);

	void drumModeOff(int writeIndex);
	void drumModeOn(int writeIndex);

	uint16_t virtualFM[2];
	uint16_t virtualMorph[2];

	void (ViaMeta::*calculateDac3)(int writeIndex);

	void calculateDac3Phasor(int writeIndex);
	void calculateDac3Contour(int writeIndex);

	void (ViaMeta::*calculateLogicA)(int writeIndex);

	void calculateLogicAReleaseGate(int writeIndex);
	void calculateLogicAAttackGate(int writeIndex);

	void (ViaMeta::*calculateSH)(int writeIndex);
	// No S&H
	void calculateSHMode1(int writeIndex);
	// Sample A from A to B
	void calculateSHMode2(int writeIndex);
	// Resample B at A
	void calculateSHMode3(int writeIndex);
	// Sample A from A to B and resample B at A
	void calculateSHMode4(int writeIndex);
	// Half Decimate (Sample A from A to B sample B from B to A
	void calculateSHMode5(int writeIndex);
	// Decimate (Resample A at B, resample B at A
	void calculateSHMode6(int writeIndex);

} metaModule;


#endif /* INC_META_HPP_ */
