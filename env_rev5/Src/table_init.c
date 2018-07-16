#include "tables.h"
#include "main.h"
#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"
#include "modes.h"

// this sets the flags to be used in the interrupt and also fills the holding array on the heap
void switchAttackFamily(void) {

	currentAttackFamily = *attackArray[0][ATTACK_SHAPE];
	loadAttackSampleArray(&currentAttackFamily);


}

void switchReleaseFamily(void) {

	currentReleaseFamily = *releaseArray[0][RELEASE_SHAPE];
	loadReleaseSampleArray(&currentReleaseFamily);


}

// this shuttles the data from flash to ram and fills our holding array
void loadAttackSampleArray(Family *family) {

	uint32_t numSamples = family->tableLength;

	//for each table in the family
	for (int i = 0; i < family->familySize; i++) {
		//fill in the attack samples
		for (int j = 0;j < numSamples; j++) {
			fullTableHoldArray[i][2 + j] = *(*(family->attackFamily + i) + j);
		}
		//pad the end of the table with the first value in attack
		fullTableHoldArray[i][(numSamples << 1) + 2] = *(*(family->attackFamily + i) + 0);
		fullTableHoldArray[i][(numSamples << 1) + 3] = *(*(family->attackFamily + i) + 0);
		fullTableHoldArray[i][(numSamples << 1) + 4] = *(*(family->attackFamily + i) + 0);
	}

}

void loadReleaseSampleArray(Family *family) {

	uint32_t numSamples = family->tableLength;

	//for each table in the family
	for (int i = 0; i < family->familySize; i++) {
		//pad the start with the the "last sample" from release
		fullTableHoldArray[i][0] = *(*(family->releaseFamily + i) + 0);
		fullTableHoldArray[i][1] = *(*(family->releaseFamily + i) + 0);
		//fill in a full cycle's worth of samples
		//the release gets reversed
		//we drop the last sample from attack and the first from releas
		for (int j = 0;j < numSamples; j++) {
			fullTableHoldArray[i][2 + numSamples + j] = *(*(family->releaseFamily + i) + family->tableLength - j);
		}

	}

}

