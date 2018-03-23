#include "scales.h"

#include "main.h"

#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"








Scale harmSubHarm =
				{.grid = harmSubharmGrid,
				.t2Bitshift = 9,
				.oneVoltOct = 1};

void initializeScales() {
	scaleGroup[0] =  harmSubHarm;
	scaleGroup[1] =  harmSubHarm;
	scaleGroup[2] =  harmSubHarm;
	scaleGroup[3] =  harmSubHarm;
	scaleGroup[4] =  harmSubHarm;
	scaleGroup[5] =  harmSubHarm;
	scaleGroup[6] =  harmSubHarm;
	scaleGroup[7] =  harmSubHarm;
	scaleGroup[8] =  harmSubHarm;
	scaleGroup[9] =  harmSubHarm;
	scaleGroup[10] =  harmSubHarm;
	scaleGroup[11] =  harmSubHarm;
	scaleGroup[12] =  harmSubHarm;
	scaleGroup[13] =  harmSubHarm;
	scaleGroup[14] =  harmSubHarm;
	scaleGroup[15] =  harmSubHarm;
}
