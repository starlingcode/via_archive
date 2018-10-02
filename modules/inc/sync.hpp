/*
 * sync.hpp
 *
 *  Created on: Sep 16, 2018
 *      Author: willmitchell
 */

#ifndef INC_SYNC_HPP_
#define INC_SYNC_HPP_



#ifdef __cplusplus
extern "C" {
#endif

#include "user_interface.hpp"
#include <via_platform_binding.hpp>
#include <oscillators.hpp>

#ifdef __cplusplus
}
#endif

#define SYNC_BUFFER_SIZE 1

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
#define LOGIC_A_MODE aux1Mode
#define QUADRATURE_MODE aux2Mode
#define AUX_OUT_MODE aux3Mode
#define TABLE_GROUP_MODE aux4Mode

#define numButton1Modes 3
#define numButton2Modes 4
#define numButton3Modes 4
#define numButton4Modes 3
#define numButton5Modes 4
#define numButton6Modes 4
#define numAux1Modes 2
#define numAux2Modes 2
#define numAux3Modes 4
#define numAux4Modes 2

enum sync_button1Modes {noSH, sampletrack, resample};
enum sync_button2Modes {scale1, scale2, scale3, scale4};
enum sync_button3Modes {root, pm, fm, pwm};
enum sync_button4Modes {nosync, truePLL, hardsync};
enum sync_button5Modes {group1, group2, group3, group4};
enum sync_button6Modes {table1, table2, table3, table4};
enum sync_aux1Modes {sync_gate, sync_delta};
enum sync_aux2Modes {sync_phasor, sync_contour};
enum sync_aux3Modes {noOffset, quarter, half, threeQuarters};
enum sync_aux4Modes {groupSpecific, global};

void syncTouchLink (void *);

class ViaSync : public ViaModule {

public:

	class ViaSyncUI: public ViaUI {

	public:

		ViaSync& this_module;

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

		ViaSyncUI(ViaSync& x): this_module(x) {
			linkUI((void *) &syncTouchLink, (void *) this);
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
	const Wavetable * wavetableArray[4][4];
	const Wavetable * wavetableArrayGlobal[4];

	// declare arrays to store the active tables
	uint32_t wavetableRead[9][517];
	//uint32_t sync_phaseDistRead[33][65];

	// declare functions to set the currently active tables
	void switchWavetable(const Wavetable *);
	void switchWavetableGlobal(const Wavetable *);
	// phase distortion table is fixed
	void initPhaseDistTable(void);
	void fillWavetableArray(void);


	const Scale * scaleArray[4][4];

	const Scale * scale;

	void initializeScales(void);

	/*
	 *
	 * Mode functions
	 *
	 */

	uint16_t virtualFM[2];
	uint16_t virtualMorph[2];

	void (ViaSync::*calculateDac3)(int32_t writeIndex);

	void calculateDac3Phasor(int32_t writeIndex);
	void calculateDac3Contour(int32_t writeIndex);

	void (ViaSync::*calculateLogicA)(int32_t writeIndex);

	void calculateLogicAGate(int32_t writeIndex);
	void calculateLogicADelta(int32_t writeIndex);

	void (ViaSync::*calculateSH)(int32_t writeIndex);
	// No S&H
	void calculateSHMode1(int32_t writeIndex);
	// Track and hold
	void calculateSHMode2(int32_t writeIndex);
	// Decimate
	void calculateSHMode3(int32_t writeIndex);

	void init(void);

	ViaSyncUI syncUI;

	int32_t runtimeDisplay;

	SingleSampleWavetable syncWavetable;
	PllController pllController;

	// average tap tempo
	int32_t lastTap = 0;
	buffer tapStore;
	int32_t tapSum = 0;

	/*
	 *
	 * Event meta_handlers
	 *
	 */

	ViaSync() : syncUI(*this) {
		init();
		for (int32_t i = 0; i < 32; i++) {
			writeBuffer(&tapStore, 0);
		}
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
		syncUI.dispatch(sig);
	};

	void incrementVirtualTimer(void) {
		pllController.virtualTimer++;
	}

};


#endif /* INC_SYNC_HPP_ */