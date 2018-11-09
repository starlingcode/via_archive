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
	knob1Sum = knob1 + knob1Sum - readLongBuffer(&knob1Buffer, 63);
	knob2Sum = knob2 + knob2Sum - readLongBuffer(&knob2Buffer, 63);
	knob3Sum = knob3 + knob3Sum - readLongBuffer(&knob3Buffer, 63);

	// write the averaged controls to the holding struct
	cv1Value = cv1Sum >> 3;
	knob1Value = knob1Sum >> 6;
	knob2Value = knob2Sum >> 6;
	knob3Value = knob3Sum >> 6;

	// store the newest value in a ring buffer
	writeBuffer(&cv1Buffer, cv1);
	writeLongBuffer(&knob1Buffer, knob1);
	writeLongBuffer(&knob2Buffer, knob2);
	writeLongBuffer(&knob3Buffer, knob3);

}


