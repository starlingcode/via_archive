/*
 * via_global_signals.cpp
 *
 *  Created on: Sep 14, 2018
 *      Author: willmitchell
 */

#include "via_global_signals.hpp"

void ViaControls::update(void) {

	// implement a running average on the control rate CV controls
	cv1Sum = cv1 + cv1Sum - readBuffer(&cv1Buffer, 7);
	knob1Sum = knob1 + knob1Sum - readBuffer(&knob1Buffer, 31);
	knob2Sum = knob2 + knob2Sum - readBuffer(&knob2Buffer, 31);
	knob3Sum = knob3 + knob3Sum - readBuffer(&knob3Buffer, 31);

	// write the averaged controls to the holding struct
	cv1Value = cv1Sum >> 3;
	knob1Value = knob1Sum >> 5;
	knob2Value = knob2Sum >> 5;
	knob3Value = knob3Sum >> 5;

	// store the newest value in a ring buffer
	writeBuffer(&cv1Buffer, cv1);
	writeBuffer(&knob1Buffer, knob1);
	writeBuffer(&knob2Buffer, knob2);
	writeBuffer(&knob3Buffer, knob3);

}


