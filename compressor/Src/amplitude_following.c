
#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"
#include "signal_processing.h"

int peakDetect(void) {

	static buffer delayLine;
	static buffer knobBuffer;
	static int runningSum;
	static int knobSum;
	int output;
	static int slewedAverage;
	int knobAverage;
	int gainReduction;
	int filterOut;
	int average;

	knobSum = knob3 + knobSum - readBuffer(&knobBuffer, 4095);
	knobAverage = knobSum >> 12;
	writeBuffer(&knobBuffer, knob3);

	if (cv2 > 2048) {
		writeBuffer(&delayLine, cv2);
		runningSum = cv2 + runningSum - readBuffer(&delayLine, 512);
	} else {
		writeBuffer(&delayLine, 4095 - cv2);
		runningSum = (4095 - cv2) + runningSum - readBuffer(&delayLine, 512);
	}

	average = runningSum;

	if (slewedAverage <= average) {
		slewedAverage += (knob1 >> 4) + 1;
		if (slewedAverage > average) {
			slewedAverage = average;
		}
	} else {
		slewedAverage -= (knob2 >> 4) + 1;
		if (slewedAverage < average) {
			slewedAverage = average;
		}
	}

	filterOut = slewedAverage >> 9;

	if (filterOut > (2048 + (knobAverage >> 1))) {
		gainReduction = (filterOut - (2048 + (knobAverage >> 1))) << 2;
		if (gainReduction > 4095) {
			gainReduction = 4095;
		}
		output = 4095 - gainReduction;
	} else {
		output = 4095;
	}

	return output;
}