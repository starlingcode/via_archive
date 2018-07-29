
#include "scales.h"
#include "main.h"
#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"



Scale integerRatios = {
   .grid = integerRatiosGrid,
   .t2Bitshift = 9,
   .oneVoltOct = 0};

Scale pentamodal5primefullspan = {
   .grid = pentamodal5primefullspanGrid,
   .t2Bitshift = 9,
   .oneVoltOct = 0};

Scale harmSubharmfullspan = {
   .grid = harmSubharmfullspanGrid,
   .t2Bitshift = 9,
   .oneVoltOct = 0};

Scale modal5primefullspan = {
   .grid = modal5primefullspanGrid,
   .t2Bitshift = 9,
   .oneVoltOct = 0};

Scale harmSubharm = {
   .grid = harmSubharmGrid,
   .t2Bitshift = 9,
   .oneVoltOct = 1};

Scale harmFolded4 = {
   .grid = harmFolded4Grid,
   .t2Bitshift = 10,
   .oneVoltOct = 1};

Scale pentamodal5prime = {
   .grid = pentamodal5primeGrid,
   .t2Bitshift = 9,
   .oneVoltOct = 1};

Scale triads = {
   .grid = triadsGrid,
   .t2Bitshift = 9,
   .oneVoltOct = 1};

Scale seventhTetradsMinimalProgression = {
   .grid = seventhTetradsMinimalProgressionGrid,
   .t2Bitshift = 8,
   .oneVoltOct = 1};

Scale seventhTetrads = {
   .grid = seventhTetradsGrid,
   .t2Bitshift = 8,
   .oneVoltOct = 1};

Scale modesOfLimitedTransposition = {
   .grid = modesOfLimitedTranspositionGrid,
   .t2Bitshift = 8,
   .oneVoltOct = 1};

Scale majMin9thPentStarling = {
   .grid = majMin9thPentStarlingGrid,
   .t2Bitshift = 8,
   .oneVoltOct = 1};

Scale simpleRhythms = {
   .grid = simpleRhythmsGrid,
   .t2Bitshift = 9,
   .oneVoltOct = 0};

Scale simpleRhythms16 = {
   .grid = simpleRhythms16Grid,
   .t2Bitshift = 9,
   .oneVoltOct = 0};

Scale rhythmDivisionsReset = {
   .grid = rhythmDivisionsResetGrid,
   .t2Bitshift = 9,
   .oneVoltOct = 0};

Scale polyResets = {
   .grid = polyResetsGrid,
   .t2Bitshift = 8,
   .oneVoltOct = 0};

void initializeScales() {
   scaleArray[0] = integerRatios;
   scaleArray[1] = pentamodal5primefullspan;
   scaleArray[2] = harmSubharmfullspan;
   scaleArray[3] = modal5primefullspan;
   scaleArray[4] = harmSubharm;
   scaleArray[5] = harmFolded4;
   scaleArray[6] = pentamodal5prime;
   scaleArray[7] = triads;
   scaleArray[8] = seventhTetradsMinimalProgression;
   scaleArray[9] = seventhTetrads;
   scaleArray[10] = modesOfLimitedTransposition;
   scaleArray[11] = majMin9thPentStarling;
   scaleArray[12] = simpleRhythms;
   scaleArray[13] = simpleRhythms16;
   scaleArray[14] = rhythmDivisionsReset;
   scaleArray[15] = polyResets;
}

//void initializeScales() {
//   scaleGroup[0] = pentamodal5prime;
//   scaleGroup[1] = pentamodal5prime;
//   scaleGroup[2] = pentamodal5prime;
//   scaleGroup[3] = pentamodal5prime;
//   scaleGroup[4] = harmSubharm;
//   scaleGroup[5] = harmFolded4;
//   scaleGroup[6] = pentamodal5prime;
//   scaleGroup[7] = triads;
//   scaleGroup[8] = seventhTetradsMinimalProgression;
//   scaleGroup[9] = seventhTetrads;
//   scaleGroup[10] = modesOfLimitedTransposition;
//   scaleGroup[11] = majMin9thPentStarling;
//   scaleGroup[12] = simpleRhythms;
//   scaleGroup[13] = simpleRhythms16;
//   scaleGroup[14] = rhythmDivisionsReset;
//   scaleGroup[15] = polyResets;
//}


