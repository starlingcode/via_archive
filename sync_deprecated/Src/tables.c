#include "tables.h"
#include "main.h"
#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"



Family moogSquare = {
	.attackFamily = moogSquareShiftAttackFamily,
	.releaseFamily = moogSquareShiftReleaseFamily,
	.tableLength = 64,
	.familySize = 9,
	.bandlimitOff = 0};


Family triOdd = {
	.attackFamily = trioddAttackFamily,
	.releaseFamily = trioddReleaseFamily,
	.tableLength = 64,
	.familySize = 9,
	.bandlimitOff = 0};


Family sawBend = {
	.attackFamily = sawBendAttackFamily,
	.releaseFamily = sawBendReleaseFamily,
	.tableLength = 4,
	.familySize = 5,
	.bandlimitOff = 0};


Family sawBendLinAtk = {
	.attackFamily = allLinear5_5,
	.releaseFamily = sawBendReleaseFamily,
	.tableLength = 4,
	.familySize = 5,
	.bandlimitOff = 0};


Family exciteBike = {
	.attackFamily = exciteBikeAttackFamily,
	.releaseFamily = exciteBikeReleaseFamily,
	.tableLength = 8,
	.familySize = 9,
	.bandlimitOff = 0};


Family algerian = {
	.attackFamily = algerianAttackFamily,
	.releaseFamily = algerianReleaseFamily,
	.tableLength = 64,
	.familySize = 5,
	.bandlimitOff = 0};


Family superEllipse1Sym = {
	.attackFamily = superEllipse1SymAttackFamily,
	.releaseFamily = superEllipse1SymReleaseFamily,
	.tableLength = 64,
	.familySize = 5,
	.bandlimitOff = 0};


Family superEllipse1Asym = {
	.attackFamily = superEllipse1AsymAttackFamily,
	.releaseFamily = superEllipse1AsymReleaseFamily,
	.tableLength = 64,
	.familySize = 5,
	.bandlimitOff = 0};


Family steps = {
	.attackFamily = stepsAttackFamily,
	.releaseFamily = stepsReleaseFamily,
	.tableLength = 64,
	.familySize = 9,
	.bandlimitOff = 0};


Family impevens = {
	.attackFamily = impshort,
	.releaseFamily = impshort,
	.tableLength = 128,
	.familySize = 9,
	.bandlimitOff = 0};


Family skipSaw = {
	.attackFamily = skipsaw,
	.releaseFamily = skipsaw,
	.tableLength = 64,
	.familySize = 5,
	.bandlimitOff = 0};


Family lump2ndDegLinAtk = {
	.attackFamily = allLinear129_5,
	.releaseFamily = lump2ndDeg,
	.tableLength = 128,
	.familySize = 5,
	.bandlimitOff = 0};


Family doubleLump2ndDegLinAtk = {
	.attackFamily = allLinear129_5,
	.releaseFamily = lump2ndDeg,
	.tableLength = 128,
	.familySize = 5,
	.bandlimitOff = 0};


Family threeBounceLinAtk = {
	.attackFamily = allLinear65_3,
	.releaseFamily = threeBounce,
	.tableLength = 64,
	.familySize = 3,
	.bandlimitOff = 0};


Family sawPWM = {
	.attackFamily = sawPWMAttackFamily,
	.releaseFamily = sawPWMReleaseFamily,
	.tableLength = 256,
	.familySize = 9,
	.bandlimitOff = 0};


Family tenor257 = {
	.attackFamily =  tenor257Atk,
	.releaseFamily =  tenor257Rls,
	.tableLength = 256,
	.familySize = 5,
	.bandlimitOff = 1};


Family linwavefold_257 = {
	.attackFamily = linwavefold_257_Family,
	.releaseFamily = linwavefold_257_Family,
	.tableLength = 256,
	.familySize = 5,
	.bandlimitOff = 0};


Family sinwavefold_257 = {
	.attackFamily = sinwavefold_257_Family,
	.releaseFamily = sinwavefold_257_Family,
	.tableLength = 256,
	.familySize = 9,
	.bandlimitOff = 0};


Family additive_tri_to_pulse = {
	.attackFamily = additive_tri_to_pulseFamily,
	.releaseFamily = additive_tri_to_pulseFamily,
	.tableLength = 256,
	.familySize = 5,
	.bandlimitOff = 0};


Family newBounce = {
	.attackFamily = newBounceFamily,
	.releaseFamily = newBounceFamily,
	.tableLength = 256,
	.familySize = 5,
	.bandlimitOff = 0};




void fillFamilyArray(void) {

	familyArray[rhythm][0] = superEllipse1Sym;
	familyArray[rhythm][1] = superEllipse1Asym;
	familyArray[rhythm][2] = doubleLump2ndDegLinAtk;
	familyArray[rhythm][3] = lump2ndDegLinAtk;
	familyArray[rhythm][4] = steps;
	familyArray[rhythm][5] = sawBendLinAtk;
	familyArray[rhythm][6] = newBounce;
	familyArray[rhythm][7] = threeBounceLinAtk;
	familyArray[arp][0] = tenor257;
	familyArray[arp][1] = sawPWM;
	familyArray[arp][2] = impevens;
	familyArray[arp][3] = linwavefold_257;
	familyArray[arp][4] = skipSaw;
	familyArray[arp][5] = sinwavefold_257;
	familyArray[arp][6] = additive_tri_to_pulse;
	familyArray[arp][7] = newBounce;
	familyArray[voltOct][0] = tenor257;
	familyArray[voltOct][1] = sawPWM;
	familyArray[voltOct][2] = impevens;
	familyArray[voltOct][3] = linwavefold_257;
	familyArray[voltOct][4] = skipSaw;
	familyArray[voltOct][5] = sinwavefold_257;
	familyArray[voltOct][6] = additive_tri_to_pulse;
	familyArray[voltOct][7] = newBounce;

	currentFamily = familyArray[scaleType][familyIndicator];
	switchFamily();

}
