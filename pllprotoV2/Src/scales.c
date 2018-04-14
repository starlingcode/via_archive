#include "scales.h"
#include "main.h"
#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"



Scale harmSubharm = {
   .grid = harmSubharmGrid,
   .t2Bitshift = 8,
   .oneVoltOct = 1};

Scale harmSubharmfullspan = {
   .grid = harmSubharmfullspanGrid,
   .t2Bitshift = 8,
   .oneVoltOct = 0};

Scale modal5primefullspan = {
   .grid = modal5primefullspanGrid,
   .t2Bitshift = 8,
   .oneVoltOct = 0};

Scale harmFolded4 = {
   .grid = harmFolded4Grid,
   .t2Bitshift = 9,
   .oneVoltOct = 1};

Scale polyResets = {
   .grid = polyResetsGrid,
   .t2Bitshift = 7,
   .oneVoltOct = 0};

Scale pentamodal5prime = {
   .grid = pentamodal5primeGrid,
   .t2Bitshift = 8,
   .oneVoltOct = 1};

Scale triads = {
   .grid = triadsGrid,
   .t2Bitshift = 8,
   .oneVoltOct = 1};

Scale seventhTetradsMinimalProgression = {
   .grid = seventhTetradsMinimalProgressionGrid,
   .t2Bitshift = 7,
   .oneVoltOct = 1};

Scale seventhTetrads = {
   .grid = seventhTetradsGrid,
   .t2Bitshift = 7,
   .oneVoltOct = 1};

Scale rhythmDivisionsReset = {
   .grid = rhythmDivisionsResetGrid,
   .t2Bitshift = 8,
   .oneVoltOct = 0};

Scale modesOfLimitedTransposition = {
   .grid = modesOfLimitedTranspositionGrid,
   .t2Bitshift = 7,
   .oneVoltOct = 1};

Scale majMin9thPentStarling = {
   .grid = majMin9thPentStarlingGrid,
   .t2Bitshift = 7,
   .oneVoltOct = 1};

Scale Harm73_75 = {
   .grid = Harm73_75Grid,
   .t2Bitshift = 8,
   .oneVoltOct = 1};

Scale h73_75_BPwide = {
   .grid = h73_75_BPwideGrid,
   .t2Bitshift = 7,
   .oneVoltOct = 1};

Scale bohlenPeirce = {
   .grid = bohlenPeirceGrid,
   .t2Bitshift = 7,
   .oneVoltOct = 0};

Scale add9thSixthsusp4th = {
   .grid = add9thSixthsusp4thGrid,
   .t2Bitshift = 7,
   .oneVoltOct = 1};

void initializeScales() {
   scaleGroup[0] = harmSubharm;
   scaleGroup[1] = harmSubharmfullspan;
   scaleGroup[2] = modal5primefullspan;
   scaleGroup[3] = harmFolded4;
   scaleGroup[4] = polyResets;
   scaleGroup[5] = pentamodal5prime;
   scaleGroup[6] = triads;
   scaleGroup[7] = seventhTetradsMinimalProgression;
   scaleGroup[8] = seventhTetrads;
   scaleGroup[9] = rhythmDivisionsReset;
   scaleGroup[10] = modesOfLimitedTransposition;
   scaleGroup[11] = majMin9thPentStarling;
   scaleGroup[12] = Harm73_75;
   scaleGroup[13] = h73_75_BPwide;
   scaleGroup[14] = bohlenPeirce;
   scaleGroup[15] = add9thSixthsusp4th;
}
