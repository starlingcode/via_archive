/*
 * Calib.hpp
 *
 *  Created on: Sep 11, 2018
 *      Author: willmitchell
 */

#ifndef INC_Calib_HPP_
#define INC_Calib_HPP_

#include "user_interface.hpp"
#include <via_platform_binding.hpp>
#include <oscillators.hpp>

#ifdef __cplusplus
extern "C" {
#endif



#ifdef __cplusplus
}
#endif

#define CALIB_BUFFER_SIZE 8

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

void calibTouchLink (void *);

class ViaCalib : public ViaModule {

public:

	class ViaCalibUI: public ViaUI {

	public:

		ViaCalib& this_module;

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
		void aux2AltTapCallback(void) override;
		void aux2AltHoldCallback(void) override;
		void aux3TapCallback(void) override;
		void aux3HoldCallback(void) override;
		void aux4TapCallback(void) override;
		void aux4HoldCallback(void) override;

		void uiSetLEDs(int) override;

		void recallModuleState(void) override;

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
		void aux2AltEnterMenuCallback(void) override;
		void aux3EnterMenuCallback(void) override;
		void aux4EnterMenuCallback(void) override;

		void initialize(void) override;

		ViaCalibUI(ViaCalib& x): this_module(x) {
			linkUI((void *) &calibTouchLink, (void *) this);
		}

	};

	/*
	 *
	 * Tables
	 *
	 */

	void init(void);

	ViaCalibUI CalibUI;

	int32_t runtimeDisplay;

	/*
	 *
	 * Event Calib_handlers
	 *
	 */

	ViaCalib() : CalibUI(*this) {

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

	void auxTimer1InterruptCallback(void);
	void auxTimer2InterruptCallback(void);


	void ui_dispatch(int32_t sig) {
		this->CalibUI.dispatch(sig);
	};

};



#endif /* INC_Calib_HPP_ */