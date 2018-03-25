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
	.tableLength = 0,
	.familySize = 0,
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
	.tableLength = 0,
	.familySize = 0,
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

	familyArray[audio][0] = tenor257;
	familyArray[audio][1] = sawPWM;
	familyArray[audio][2] = impevens;
	familyArray[audio][3] = linwavefold_257;
	familyArray[audio][4] = skipSaw;
	familyArray[audio][5] = sinwavefold_257;
	familyArray[audio][6] = additive_tri_to_pulse;
	familyArray[audio][7] = newBounce;
	familyArray[env][0] = superEllipse1Sym;
	familyArray[env][1] = superEllipse1Asym;
	familyArray[env][2] = doubleLump2ndDegLinAtk;
	familyArray[env][3] = lump2ndDegLinAtk;
	familyArray[env][4] = steps;
	familyArray[env][5] = sawBendLinAtk;
	familyArray[env][6] = newBounce;
	familyArray[env][7] = threeBounceLinAtk;
	familyArray[seq][0] = skipSaw;
	familyArray[seq][1] = exciteBike;
	familyArray[seq][2] = newBounce;
	familyArray[seq][3] = sawBend;
	familyArray[seq][4] = triOdd;
	familyArray[seq][5] = moogSquare;
	familyArray[seq][6] = algerian;
	familyArray[seq][7] = exciteBike;

	currentFamily = familyArray[0][0];
	switchFamily();

}