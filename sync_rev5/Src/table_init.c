#include "tables.h"
#include "main.h"
#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"
#include "modes.h"

// this sets the flags to be used in the interrupt and also fills the holding array on the heap
void switchFamily(void) {

	currentFamily = familyArray[GROUP_MODE][TABLE_MODE];
	loadSampleArray(currentFamily);


}

// this shuttles the data from flash to ram and fills our holding array
void loadSampleArray(Family *family) {

	uint32_t numSamples = family->tableLength;

	//for each table in the family
	for (int i = 0; i < family->familySize; i++) {
		//include the "last two" samples from release
		fullTableHoldArray[i][0] = *(*(family->releaseFamily + i) + 0);
		fullTableHoldArray[i][1] = *(*(family->releaseFamily + i) + 0);
		//fill in a full cycle's worth of samples
		//the release gets reversed
		//we drop the last sample from attack and the first from releas
		for (int j = 0;j < numSamples; j++) {
			fullTableHoldArray[i][2 + j] = *(*(family->attackFamily + i) + j);
			fullTableHoldArray[i][2 + numSamples + j] = *(*(family->releaseFamily + i) + family->tableLength - j);
		}
		//pad out the "first two" samples from attack
		fullTableHoldArray[i][(numSamples << 1) + 2] = *(*(family->attackFamily + i) + 0);
		fullTableHoldArray[i][(numSamples << 1) + 3] = *(*(family->attackFamily + i) + 0);
		fullTableHoldArray[i][(numSamples << 1) + 4] = *(*(family->attackFamily + i) + 0);
	}

}

