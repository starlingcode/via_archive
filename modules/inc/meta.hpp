/*
 * meta.hpp
 *
 *  Created on: Sep 11, 2018
 *      Author: willmitchell
 */

#ifndef INC_META_HPP_
#define INC_META_HPP_

#include "user_interface.hpp"
#include <via_platform_binding.hpp>
#include <oscillators.hpp>

#ifdef __cplusplus
extern "C" {
#endif



#ifdef __cplusplus
}
#endif

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

void metaTouchLink (void *);

class ViaMeta : public ViaModule {

public:

	class ViaMetaUI: public ViaUI {

	public:

		ViaMeta& this_module;

		void button1TapCallback(void) override;
		void button1HoldCallback(void) override;
		void button2TapCallback(void) override;
		void button2HoldCallback(void) override;
		void button3TapCallback(void) override;
		void button3HoldCallback(void) override;
		void button4TapCallback(void) override;
		void button4HoldCallback(void) override;
		void button5TapCallback(void) override;
		void button5HoldCallback(void) override;
		void button6TapCallback(void) override;
		void button6HoldCallback(void) override;

		void aux1TapCallback(void) override;
		void aux1HoldCallback(void) override;
		void aux2TapCallback(void) override;
		void aux2HoldCallback(void) override;
		void aux3TapCallback(void) override;
		void aux3HoldCallback(void) override;
		void aux4TapCallback(void) override;
		void aux4HoldCallback(void) override;

		void defaultEnterMenuCallback(void) override;
		void newModeEnterMenuCallback(void) override;
		void newAuxModeEnterMenuCallback(void) override;
		void presetEnterMenuCallback(void) override;

		void button1EnterMenuCallback(void) override;
		void button2EnterMenuCallback(void) override;
		void button3EnterMenuCallback(void) override;
		void button4EnterMenuCallback(void) override;
		void button5EnterMenuCallback(void) override;
		void button6EnterMenuCallback(void) override;

		void aux1EnterMenuCallback(void) override;
		void aux2EnterMenuCallback(void) override;
		void aux3EnterMenuCallback(void) override;
		void aux4EnterMenuCallback(void) override;

		void initialize(void) override;

		ViaMetaUI(ViaMeta& x): this_module(x) {
			linkUI((void *) &metaTouchLink, (void *) this);
		}

	};

	void handleButton1ModeChange(int32_t);
	void handleButton2ModeChange(int32_t);
	void handleButton3ModeChange(int32_t);
	void handleButton4ModeChange(int32_t);
	void handleButton5ModeChange(int32_t);
	void handleButton6ModeChange(int32_t);
	void handleAux1ModeChange(int32_t);
	void handleAux2ModeChange(int32_t);
	void handleAux3ModeChange(int32_t);
	void handleAux4ModeChange(int32_t);

	/*
	 *
	 * Tables
	 *
	 */

	// declare an array of pointers to wavetables (stored in flash)
	const Wavetable * wavetableArray[3][8];

	// declare arrays to store the active tables
	uint32_t wavetableRead[9][517];
	uint32_t wavetableReadDrum[517];

	//uint32_t meta_phaseDistRead[33][65];

	// declare functions to set the currently active tables
	void switchWavetable(const Wavetable *);
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

	void (ViaMeta::*drumMode)(int32_t writeIndex);

	void drumModeOff(int32_t writeIndex);
	void drumModeOn(int32_t writeIndex);

	uint16_t virtualFM[2];
	uint16_t virtualMorph[2];

	void (ViaMeta::*calculateDac3)(int32_t writeIndex);

	void calculateDac3Phasor(int32_t writeIndex);
	void calculateDac3Contour(int32_t writeIndex);
	void calculateDac3PhasorEnv(int32_t writeIndex);
	void calculateDac3ContourEnv(int32_t writeIndex);

	void (ViaMeta::*calculateLogicA)(int32_t writeIndex);

	void calculateLogicAReleaseGate(int32_t writeIndex);
	void calculateLogicAAttackGate(int32_t writeIndex);

	void (ViaMeta::*calculateSH)(int32_t writeIndex);
	// No S&H
	void calculateSHMode1(int32_t writeIndex);
	// Sample A from A to B
	void calculateSHMode2(int32_t writeIndex);
	// Resample B at A
	void calculateSHMode3(int32_t writeIndex);
	// Sample A from A to B and resample B at A
	void calculateSHMode4(int32_t writeIndex);
	// Half Decimate (Sample A from A to B sample B from B to A
	void calculateSHMode5(int32_t writeIndex);
	// Decimate (Resample A at B, resample B at A
	void calculateSHMode6(int32_t writeIndex);

	void init(void);

	ViaMetaUI metaUI;

	int32_t runtimeDisplay;

	SimpleWavetable metaWavetable;
	MetaController metaController;
	SimpleEnvelope drumEnvelope;

	/*
	 *
	 * Event meta_handlers
	 *
	 */

	ViaMeta() : metaUI(*this) {

		init();
	}

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

	void ui_dispatch(int32_t sig) {
		this->metaUI.dispatch(sig);
	};

};



#endif /* INC_META_HPP_ */
