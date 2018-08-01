#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"
#include "patterns.h"


void initializePatterns() {
   patternBanks[0] = &euclidean_simple;
   patternBanks[1] = &euclidean_2vs3;
   patternBanks[2] = &euclidean_3_2multvs2_3mult;
   patternBanks[3] = &euclidean_12vs16odd;
   patternBanks[4] = &euclidean_16vs32odd;
   patternBanks[5] = &euclidean_16vs32noprimes;
   patternBanks[6] = &euclidean_divider;
   patternBanks[7] = &euclidean_doubled_divider;
}
