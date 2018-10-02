/*
 * trigseq.h
 *
 *  Created on: Aug 21, 2018
 *      Author: willmitchell
 */

#ifndef INC_TRIGSEQ_HPP_
#define INC_TRIGSEQ_HPP_

#ifdef __cplusplus
extern "C" {
#endif

#include "sequencers.hpp"
#include <via_platform_binding.hpp>
#include <user_interface.hpp>

#ifdef __cplusplus
}
#endif

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
	_and, _or, _xor, _sr
};
enum trigseq_aux3Modes {
	trigseq_aux3NotUsed
};
enum trigseq_aux4Modes {
	trigseq_aux4NotUsed
};

#define TRIGSEQ_BUFFER_SIZE 1

void trigseqTouchLink (void *);

class ViaTrigseq : public ViaModule {

public:

	class ViaTrigseqUI: public ViaUI {

	public:

		ViaTrigseq& this_module;

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

		ViaTrigseqUI(ViaTrigseq& x): this_module(x) {
			linkUI((void *) &trigseqTouchLink, (void *) this);
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

	const dualBooleanSequence *patternBank[8];

	void initializePatterns(void);

	/*
	 *
	 * Mode functions
	 *
	 */

	void init(void);

	ViaTrigseqUI trigseqUI;

	int32_t runtimeDisplay;

	DualEuclidean sequencer;

	SoftGate gateController;

	/*
	 *
	 * Event meta_handlers
	 *
	 */

	ViaTrigseq() : trigseqUI(*this) {
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
		trigseqUI.dispatch(sig);
	};

};

#endif /* INC_TRIGSEQ_HPP_ */
