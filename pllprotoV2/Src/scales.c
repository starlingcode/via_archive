#include "scales.h"
#include "main.h"
#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"



Scale harmSubharm = {
   .grid = harmSubharmGrid,
   .t2Bitshift = 9,
   .oneVoltOct = 1};

Scale modal5prime = {
   .grid = modal5primeGrid,
   .t2Bitshift = 9,
   .oneVoltOct = 1};

Scale harmSubharmfullspan = {
   .grid = harmSubharmfullspanGrid,
   .t2Bitshift = 9,
   .oneVoltOct = 0};

Scale modal5primefullspan = {
   .grid = modal5primefullspanGrid,
   .t2Bitshift = 9,
   .oneVoltOct = 0};

void initializeScales() {
   scaleGroup[0] = harmSubharm;
   scaleGroup[1] = modal5prime;
   scaleGroup[2] = harmSubharmfullspan;
   scaleGroup[3] = modal5primefullspan;
   scaleGroup[4] = harmSubharm;
   scaleGroup[5] = modal5prime;
   scaleGroup[6] = harmSubharmfullspan;
   scaleGroup[7] = modal5primefullspan;
   scaleGroup[8] = harmSubharm;
   scaleGroup[9] = modal5prime;
   scaleGroup[10] = harmSubharmfullspan;
   scaleGroup[11] = modal5primefullspan;
   scaleGroup[12] = harmSubharm;
   scaleGroup[13] = modal5prime;
   scaleGroup[14] = harmSubharmfullspan;
   scaleGroup[15] = modal5primefullspan;
}
