#include "tables.h"
#include "main.h"
#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"

const Family moogSquare = {
	.attackFamily = moogSquareShiftAttackFamily,
	.releaseFamily = moogSquareShiftReleaseFamily,
	.tableLength = 64,
	.familySize = 9,
	.bandlimitOff = 0};


const Family triOdd = {
	.attackFamily = trioddAttackFamily,
	.releaseFamily = trioddReleaseFamily,
	.tableLength = 64,
	.familySize = 9,
	.bandlimitOff = 0};


const Family sawBend = {
	.attackFamily = sawBendAttackFamily,
	.releaseFamily = sawBendReleaseFamily,
	.tableLength = 4,
	.familySize = 5,
	.bandlimitOff = 0};


const Family sawBendLinAtk = {
	.attackFamily = allLinear5_5,
	.releaseFamily = sawBendReleaseFamily,
	.tableLength = 4,
	.familySize = 5,
	.bandlimitOff = 0};


const Family exciteBike = {
	.attackFamily = exciteBikeAttackFamily,
	.releaseFamily = exciteBikeReleaseFamily,
	.tableLength = 8,
	.familySize = 9,
	.bandlimitOff = 0};


const Family algerian = {
	.attackFamily = algerianAttackFamily,
	.releaseFamily = algerianReleaseFamily,
	.tableLength = 64,
	.familySize = 5,
	.bandlimitOff = 0};


const Family superEllipse1Sym = {
	.attackFamily = superEllipse1SymAttackFamily,
	.releaseFamily = superEllipse1SymReleaseFamily,
	.tableLength = 64,
	.familySize = 5,
	.bandlimitOff = 0};


const Family superEllipse1Asym = {
	.attackFamily = superEllipse1AsymAttackFamily,
	.releaseFamily = superEllipse1AsymReleaseFamily,
	.tableLength = 64,
	.familySize = 5,
	.bandlimitOff = 0};


const Family steps = {
	.attackFamily = stepsAttackFamily,
	.releaseFamily = stepsReleaseFamily,
	.tableLength = 64,
	.familySize = 9,
	.bandlimitOff = 0};


const Family impevens = {
	.attackFamily = impshort,
	.releaseFamily = impshort,
	.tableLength = 128,
	.familySize = 9,
	.bandlimitOff = 0};


const Family skipSaw = {
	.attackFamily = skipsaw,
	.releaseFamily = skipsaw,
	.tableLength = 64,
	.familySize = 5,
	.bandlimitOff = 0};


const Family lump2ndDegLinAtk = {
	.attackFamily = allLinear129_5,
	.releaseFamily = lump2ndDeg,
	.tableLength = 128,
	.familySize = 5,
	.bandlimitOff = 0};


const Family doubleLump2ndDegLinAtk = {
	.attackFamily = allLinear129_5,
	.releaseFamily = lump2ndDeg,
	.tableLength = 128,
	.familySize = 5,
	.bandlimitOff = 0};


const Family threeBounceLinAtk = {
	.attackFamily = allLinear65_3,
	.releaseFamily = threeBounce,
	.tableLength = 64,
	.familySize = 3,
	.bandlimitOff = 0};


const Family sawPWM = {
	.attackFamily = sawPWMAttackFamily,
	.releaseFamily = sawPWMReleaseFamily,
	.tableLength = 256,
	.familySize = 9,
	.bandlimitOff = 0};


const Family tenor257 = {
	.attackFamily = tenor257Atk,
	.releaseFamily = tenor257Rls,
	.tableLength = 256,
	.familySize = 5,
	.bandlimitOff = 1};


const Family linwavefold_257 = {
	.attackFamily = linwavefold_257_Family,
	.releaseFamily = linwavefold_257_Family,
	.tableLength = 256,
	.familySize = 5,
	.bandlimitOff = 0};


const Family sinwavefold_257 = {
	.attackFamily = sinwavefold_257_Family,
	.releaseFamily = sinwavefold_257_Family,
	.tableLength = 256,
	.familySize = 9,
	.bandlimitOff = 0};


const Family additive_tri_to_pulse = {
	.attackFamily = additive_tri_to_pulseFamily,
	.releaseFamily = additive_tri_to_pulseFamily,
	.tableLength = 256,
	.familySize = 5,
	.bandlimitOff = 0};


const Family newBounce = {
	.attackFamily = newBounceFamily,
	.releaseFamily = newBounceFamily,
	.tableLength = 256,
	.familySize = 5,
	.bandlimitOff = 0};




void fillFamilyArray(void) {

	familyArray[0] = &tenor257;
	familyArray[1] = &sawPWM;
	familyArray[2] = &sinwavefold_257;
	familyArray[3] = &linwavefold_257;
	familyArray[4] = &skipSaw;
	familyArray[5] = &sinwavefold_257;
	familyArray[6] = &additive_tri_to_pulse;
	familyArray[7] = &newBounce;

	currentFamily = *familyArray[0];
	switchFamily();

}

// this sets the flags to be used in the interrupt and also fills the holding array on the heap
void switchFamily(void) {

	currentFamily = *familyArray[familyIndicator];
	loadSampleArray(currentFamily);


}

// this shuttles the data from flash to ram and fills our holding array
void loadSampleArray(Family family) {

	uint32_t numSamples = family.tableLength;

	//for each table in the family
	for (int i = 0; i < 5; i++) {
		//include the "last two" samples from release
		fullTableHoldArray[i][0] = *(*(family.releaseFamily + i) + 0);
		fullTableHoldArray[i][1] = *(*(family.releaseFamily + i) + 0);
		//fill in a full cycle's worth of samples
		//the release gets reversed
		//we drop the last sample from attack and the first from releas
		for (int j = 0;j < numSamples; j++) {
			fullTableHoldArray[i][2 + j] = *(*(family.attackFamily + i) + j);
			fullTableHoldArray[i][2 + numSamples + j] = *(*(family.releaseFamily + i) + family.tableLength - j);
		}
		//pad out the "first two" samples from attack
		fullTableHoldArray[i][(numSamples << 1) + 2] = *(*(family.attackFamily + i) + 0);
		fullTableHoldArray[i][(numSamples << 1) + 3] = *(*(family.attackFamily + i) + 0);
		fullTableHoldArray[i][(numSamples << 1) + 4] = *(*(family.attackFamily + i) + 0);
	}

}

