#include "scales.h"

#include "main.h"

#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"

void switchScale(uint32_t scaleIndex) {
	uint32_t evaluationHolder;

	switch (scaleIndex) {
	case 0:
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				// this just gets the appropriate samples and plops them into the global holding arrays
				evaluationHolder = rhythms[i][j];
				scale[i][j] = evaluationHolder;
			}
		}
		break;

	case 1:
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				// this just gets the appropriate samples and plops them into the global holding arrays
				evaluationHolder = diatonicMinor7ths[i][j];
				scale[i][j] = evaluationHolder;
			}
		}
		break;
	case 2:
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				// this just gets the appropriate samples and plops them into the global holding arrays
				evaluationHolder = diatonicMajor7ths[i][j];
				scale[i][j] = evaluationHolder;
			}
		}
		break;

	}
}



