/*
 * meta_interrupt_handlers.cpp
 *
 *  Created on: Sep 12, 2018
 *      Author: willmitchell
 */


/*
 * meta_interrupt_handlers.c
 *
 *  Created on: Aug 29, 2018
 *      Author: willmitchell
 */

#include "calib.hpp"

constexpr int32_t Sine::big_sine[4097];

void ViaCalib::mainRisingEdgeCallback(void) {
	setLEDA(1);
	setLEDB(1);
}

void ViaCalib::mainFallingEdgeCallback(void) {
	setLEDA(0);
	setLEDB(0);
}

void ViaCalib::auxRisingEdgeCallback(void) {
	setLEDC(1);
	setLEDD(1);
}
void ViaCalib::auxFallingEdgeCallback(void) {
	setLEDC(0);
	setLEDD(0);
}

void ViaCalib::buttonPressedCallback(void) {

	if (!calibrateCVs) {
		calibrateCVs = 1;
	} else if (!calibrateDAC3) {
		dac3Offset = abs((int32_t)(2048 + cv1Read - controls.cv1Value));
		encodeCalibrationPacket(cv2Read, cv3Read, cv1Read, dac3Offset);
		setLEDA(1);
		setLEDB(1);
		setLEDC(1);
		setLEDD(1);
		calibrateDAC3 = 1;
	} else {
		calibUI.storeToEEPROM(7, calibrationPacket);
		writeOptionBytes(0, 0);
	}

}
void ViaCalib::buttonReleasedCallback(void) {


}

void ViaCalib::ioProcessCallback(void) {

	// no need

}

void ViaCalib::halfTransferCallback(void) {

	if (calibrateCVs) {
		if (cvCalibCounter < 64) {
			cv1Sum += controls.cv1Value;
			int32_t cv2Sample = inputs.cv2Samples[0];
			cv2Sum += cv2Sample;
			int32_t cv3Sample = inputs.cv3Samples[0];
			cv3Sum += cv3Sample;
			cvCalibCounter ++;
		} else if (cvCalibCounter == 64) {
			cv1Read = (cv1Sum >> 6) - 2048;
			cv2Read = cv2Sum >> 6;
			cv3Read = cv3Sum >> 6;
			cvCalibCounter ++;
		} else {
			setGreenLED(4095);
		}
	} else if (!checkTouch) {

		int32_t sample;

		for (int i = 0; i < 8; i++) {
			sinePhase += sineFreq;
			sample = oscillator.evaluate(sinePhase) >> 3;

			outputs.dac1Samples[i] = 4095 - sample;
			outputs.dac2Samples[i] = sample;
			outputs.dac3Samples[i] = dac3Output;
		}

	}

}

void ViaCalib::transferCompleteCallback(void) {

	 if (!calibrateCVs && !checkTouch) {

			int32_t sample;

			for (int i = 8; i < 16; i++) {
				sinePhase += sineFreq;
				sample = oscillator.evaluate(sinePhase) >> 3;
				outputs.dac1Samples[i] = 4095 - sample;
				outputs.dac2Samples[i] = sample;
				outputs.dac3Samples[i] = dac3Output;
			}

		}

}

void ViaCalib::slowConversionCallback(void) {

	if (!calibrateCVs && !checkTouch) {

		int32_t cv1Change = (int32_t)((4095 - controls.controlRateInputs[0]) - controls.cv1Value);

		if (!cv1Stable) {

			errorSum += cv1Change - readBuffer(&errorBuffer, 31);
			writeBuffer(&errorBuffer, cv1Change);
			cv1Change = errorSum >> 5;

			if (abs(cv1Change) < 1) {
				cv1Counter = 0;
				cv1Stable = 1;
				thisCV1 = controls.cv1Value;
				int32_t error = abs(thisCV1 - lastCV1) % 384;
				setLEDA(0);
				if ((error < 3) || (error > 381)) {
					setGreenLED(1024);
					setRedLED(0);
					setBlueLED(0);
				} else if (error > 256) {
					setBlueLED(((384 - error) << 3) + 300);
					setRedLED(0);
					setGreenLED(0);
				} else if (error < 128) {
					setBlueLED(0);
					setRedLED((error << 3) + 300);
					setGreenLED(0);
				}
			}
		} else if ((cv1Change > 50)) {
			setLEDA(1);
			cv1Stable = 0;
			lastCV1 = controls.cv1Value;
			errorSum += cv1Change - readBuffer(&errorBuffer, 31);
			writeBuffer(&errorBuffer, cv1Change);
		} else {
			errorSum += 0 - readBuffer(&errorBuffer, 31);
			writeBuffer(&errorBuffer, 0);
		}

		sineFreq = expo.convert(controls.cv1Value) >> 1;

		dac3Increment = controls.knob1 << 9;
		dac3Range = controls.knob2 >> 9;
		dac3Base = (controls.knob3 >> 9) - 4;

		dac3Phasor += dac3Increment;

		uint32_t state = (dac3Phasor >> 31) * (dac3Increment != 0);

		int32_t octaveOffset = __SSAT(dac3Base + dac3Range*state, 3);

		dac3Output = 2048 - octaveOffset * 384;

		outputs.logicA[0] = GET_ALOGIC_MASK(state);
		outputs.auxLogic[0] = GET_EXPAND_LOGIC_MASK(state);
		outputs.shA[0] = GET_SH_A_MASK(state);
		outputs.shB[0] = GET_SH_B_MASK(state);

		setLogicOut(0, 0);

		int32_t cv2Sample = inputs.cv2Samples[0];
		int32_t cv3Sample = inputs.cv3Samples[0];

		if (cv2Sample < -10000) {
			setRedLED(2048);
		}

		if (cv3Sample < -10000) {
			setBlueLED(2048);
		}

	} else {
		dac3Output = 2048;
	}

	controls.update();

}

void ViaCalib::auxTimer1InterruptCallback(void) {


}

void ViaCalib::auxTimer2InterruptCallback(void) {


}




