#include "tables.h"
#include "main.h"
#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"
#include "modes.h"



const Family moogSquare = {
	.attackFamily = moogSquareShiftAttackFamily,
	.releaseFamily = moogSquareShiftReleaseFamily,
	.tableLength = 256,
	.familySize = 9};


const Family triOdd = {
	.attackFamily = trioddAttackFamily,
	.releaseFamily = trioddReleaseFamily,
	.tableLength = 256,
	.familySize = 9};


const Family sawBend = {
	.attackFamily = sawBendAttackFamily,
	.releaseFamily = sawBendReleaseFamily,
	.tableLength = 256,
	.familySize = 5};


const Family exciteBike = {
	.attackFamily = exciteBikeAttackFamily,
	.releaseFamily = exciteBikeReleaseFamily,
	.tableLength = 256,
	.familySize = 9};


const Family algerian = {
	.attackFamily = algerianAttackFamily,
	.releaseFamily = algerianReleaseFamily,
	.tableLength = 256,
	.familySize = 5};


const Family impevens = {
	.attackFamily = impshort,
	.releaseFamily = impshort,
	.tableLength = 256,
	.familySize = 9};


const Family skipSaw = {
	.attackFamily = skipsaw,
	.releaseFamily = skipsaw,
	.tableLength = 256,
	.familySize = 5};


const Family tenor257 = {
	.attackFamily = tenor257Atk,
	.releaseFamily = tenor257Rls,
	.tableLength = 256,
	.familySize = 5};


const Family linwavefold_257 = {
	.attackFamily = linwavefold_257_Family,
	.releaseFamily = linwavefold_257_Family,
	.tableLength = 256,
	.familySize = 5};


const Family sinwavefold_257 = {
	.attackFamily = sinwavefold_257_Family,
	.releaseFamily = sinwavefold_257_Family,
	.tableLength = 256,
	.familySize = 9};


const Family additive_tri_to_pulse = {
	.attackFamily = additive_tri_to_pulseFamily,
	.releaseFamily = additive_tri_to_pulseFamily,
	.tableLength = 256,
	.familySize = 5};


const Family newBounce = {
	.attackFamily = newBounceFamily,
	.releaseFamily = newBounceFamily,
	.tableLength = 256,
	.familySize = 5};


const Family soprano257 = {
	.attackFamily = soprano257Atk,
	.releaseFamily = soprano257Rls,
	.tableLength = 256,
	.familySize = 5};


const Family testRMS = {
	.attackFamily = testRMSRMSAtk,
	.releaseFamily = testRMSRMSRls,
	.tableLength = 256,
	.familySize = 5};


const Family gamma257 = {
	.attackFamily = gamma257Attack,
	.releaseFamily = gamma257Attack,
	.tableLength = 256,
	.familySize = 9};


const Family bounce_257 = {
	.attackFamily = bounce_257_slopes,
	.releaseFamily = bounce_257_slopes,
	.tableLength = 256,
	.familySize = 5};


const Family circular_257 = {
	.attackFamily = circular_257_slopes,
	.releaseFamily = circular_257_slopes,
	.tableLength = 256,
	.familySize = 5};


const Family quintic_outin2quintic_inout257 = {
	.attackFamily = quintic_outin2quintic_inout257_slopes,
	.releaseFamily = quintic_outin2quintic_inout257_slopes,
	.tableLength = 256,
	.familySize = 9};


const Family quintic_out2quintic_in257 = {
	.attackFamily = quintic_out2quintic_in257_slopes,
	.releaseFamily = quintic_out2quintic_in257_slopes,
	.tableLength = 256,
	.familySize = 9};


const Family quintic_inout2quintic_outin257 = {
	.attackFamily = quintic_inout2quintic_outin257_slopes,
	.releaseFamily = quintic_inout2quintic_outin257_slopes,
	.tableLength = 256,
	.familySize = 9};


const Family quintic_in2quintic_out257 = {
	.attackFamily = quintic_in2quintic_out257_slopes,
	.releaseFamily = quintic_in2quintic_out257_slopes,
	.tableLength = 256,
	.familySize = 9};




void fillFamilyArray(void) {


	attackArray[0][0] = &quintic_outin2quintic_inout257;
	attackArray[0][1] = &quintic_out2quintic_in257;
	attackArray[0][2] = &quintic_inout2quintic_outin257;
	attackArray[0][3] = &quintic_in2quintic_out257;

	releaseArray[0][0] = &testRMS;
	releaseArray[0][1] = &gamma257;
	releaseArray[0][2] = &bounce_257;
	releaseArray[0][3] = &circular_257;



	switchAttackFamily();
	switchReleaseFamily();

}
