/*
 * scanner.hpp
 *
 *  Created on: Sep 17, 2018
 *      Author: willmitchell
 */

#ifndef INC_SCANNER_HPP_
#define INC_SCANNER_HPP_



#ifdef __cplusplus
extern "C" {
#endif

#include "user_interface.hpp"
#include <via_platform_binding.hpp>
#include <signal_processors.hpp>
#include <tables.hpp>

#ifdef __cplusplus
}
#endif

#define SCANNER_BUFFER_SIZE 8

/*
 *
 * Modes
 *
 */

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

void scannerTouchLink (void *);

class ViaScanner : public ViaModule {

	int32_t readIndex = 0;

public:

	class ViaScannerUI: public ViaUI {

	public:

		ViaScanner& this_module;

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

		void initialize(void);

		ViaScannerUI(ViaScanner& x): this_module(x) {
			linkUI((void *) &scannerTouchLink, (void *) this);
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
	const Wavetable * wavetableArray[8];

	// declare arrays to store the active tables
	uint32_t wavetableXRead[5][517];
	uint32_t wavetableYRead[5][517];

	void fillWavetableArray(void);

	// declare functions to set the currently active tables
	void switchWavetableX(const Wavetable *);
	void switchWavetableY(const Wavetable *);

	// phase distortion table is fixed
	void initPhaseDistTable(void);

	int32_t reverseBuffer[SCANNER_BUFFER_SIZE*2];

	int32_t reverseSignal = 1;

	/*
	 *
	 * Synthesis classes and init
	 *
	 */


	void init(void);

	ViaScannerUI scannerUI;

	int32_t runtimeDisplay;

	ThreeAxisScanner scanner;

	/*
	 *
	 * Event scanner_handlers
	 *
	 */

	ViaScanner() : scannerUI(*this) {
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
	void cv2HalfTransferCallback(void);
	void cv2TransferCompleteCallback(void);
	void cv3HalfTransferCallback(void);
	void cv3TransferCompleteCallback(void);
	void slowConversionCallback(void);

	void ui_dispatch(int32_t sig) {
		scannerUI.dispatch(sig);
	};

};



#endif /* INC_SCANNER_HPP_ */
