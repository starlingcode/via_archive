#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"



typedef struct {
	const uint32_t **aPatternBank;
	const uint32_t **bPatternBank;
	const uint32_t *aLengths;
	const uint32_t *bLengths;
	const uint32_t aNumPatterns;
	const uint32_t bNumPatterns;
} pattern_bank;


pattern_bank *patternBanks[8];
pattern_bank *currentBank;


void initializePatterns(void);


static const uint32_t euclidean_simple_2_8[8] = {1, 0, 0, 0, 1, 0, 0, 0}; 

static const uint32_t euclidean_16vs32odd_9_16[16] = {1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0}; 

static const uint32_t euclidean_doubled_divider_1_8[8] = {1, 0, 0, 0, 0, 0, 0, 0}; 

static const uint32_t euclidean_2vs3_3_6[6] = {1, 0, 1, 0, 1, 0}; 

static const uint32_t euclidean_16vs32noprimes_10_16[16] = {1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0}; 

static const uint32_t euclidean_doubled_divider_2_4[4] = {1, 0, 1, 0}; 

static const uint32_t euclidean_simple_3_8[8] = {1, 0, 0, 1, 0, 0, 1, 0}; 

static const uint32_t euclidean_16vs32noprimes_14_16[16] = {1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0}; 

static const uint32_t euclidean_3_2multvs2_3mult_2_15[15] = {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0}; 

static const uint32_t euclidean_16vs32noprimes_15_32[32] = {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0}; 

static const uint32_t euclidean_12vs16odd_13_16[16] = {1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1}; 

static const uint32_t euclidean_16vs32noprimes_12_32[32] = {1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0}; 

static const uint32_t euclidean_16vs32noprimes_9_16[16] = {1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0}; 

static const uint32_t euclidean_doubled_divider_2_5[5] = {1, 0, 1, 0, 0}; 

static const uint32_t euclidean_2vs3_3_9[9] = {1, 0, 0, 1, 0, 0, 1, 0, 0}; 

static const uint32_t euclidean_16vs32noprimes_4_16[16] = {1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0}; 

static const uint32_t euclidean_16vs32noprimes_9_32[32] = {1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0}; 

static const uint32_t euclidean_12vs16odd_1_12[12] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; 

static const uint32_t euclidean_divider_1_5[5] = {1, 0, 0, 0, 0}; 

static const uint32_t euclidean_16vs32odd_5_32[32] = {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0}; 

static const uint32_t euclidean_doubled_divider_1_16[16] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; 

static const uint32_t euclidean_simple_1_16[16] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; 

static const uint32_t euclidean_2vs3_2_10[10] = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0}; 

static const uint32_t euclidean_simple_8_16[16] = {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0}; 

static const uint32_t euclidean_3_2multvs2_3mult_3_14[14] = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0}; 

static const uint32_t euclidean_3_2multvs2_3mult_3_12[12] = {1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0}; 

static const uint32_t euclidean_12vs16odd_4_12[12] = {1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0}; 

static const uint32_t euclidean_doubled_divider_1_2[2] = {1, 0}; 

static const uint32_t euclidean_12vs16odd_15_16[16] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0}; 

static const uint32_t euclidean_simple_4_16[16] = {1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0}; 

static const uint32_t euclidean_16vs32noprimes_15_16[16] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0}; 

static const uint32_t euclidean_2vs3_3_4[4] = {1, 1, 1, 0}; 

static const uint32_t euclidean_divider_1_10[10] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0}; 

static const uint32_t euclidean_16vs32noprimes_8_16[16] = {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0}; 

static const uint32_t euclidean_2vs3_2_8[8] = {1, 0, 0, 0, 1, 0, 0, 0}; 

static const uint32_t euclidean_16vs32odd_3_16[16] = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0}; 

static const uint32_t euclidean_divider_1_4[4] = {1, 0, 0, 0}; 

static const uint32_t euclidean_16vs32noprimes_8_32[32] = {1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0}; 

static const uint32_t euclidean_12vs16odd_9_16[16] = {1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0}; 

static const uint32_t euclidean_divider_1_7[7] = {1, 0, 0, 0, 0, 0, 0}; 

static const uint32_t euclidean_doubled_divider_2_2[2] = {1, 1}; 

static const uint32_t euclidean_3_2multvs2_3mult_2_3[3] = {1, 1, 0}; 

static const uint32_t euclidean_3_2multvs2_3mult_3_16[16] = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0}; 

static const uint32_t euclidean_16vs32noprimes_6_32[32] = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0}; 

static const uint32_t euclidean_doubled_divider_1_14[14] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; 

static const uint32_t euclidean_12vs16odd_3_12[12] = {1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0}; 

static const uint32_t euclidean_3_2multvs2_3mult_3_8[8] = {1, 0, 0, 1, 0, 0, 1, 0}; 

static const uint32_t euclidean_divider_1_2[2] = {1, 0}; 

static const uint32_t euclidean_2vs3_3_8[8] = {1, 0, 0, 1, 0, 0, 1, 0}; 

static const uint32_t euclidean_16vs32odd_15_32[32] = {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0}; 

static const uint32_t euclidean_16vs32odd_13_16[16] = {1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1}; 

static const uint32_t euclidean_2vs3_2_3[3] = {1, 1, 0}; 

static const uint32_t euclidean_16vs32odd_1_32[32] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; 

static const uint32_t euclidean_simple_5_16[16] = {1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0}; 

static const uint32_t euclidean_3_2multvs2_3mult_3_4[4] = {1, 1, 1, 0}; 

static const uint32_t euclidean_16vs32noprimes_12_16[16] = {1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0}; 

static const uint32_t euclidean_12vs16odd_11_16[16] = {1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1}; 

static const uint32_t euclidean_simple_2_16[16] = {1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0}; 

static const uint32_t euclidean_12vs16odd_7_16[16] = {1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0}; 

static const uint32_t euclidean_16vs32odd_3_32[32] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0}; 

static const uint32_t euclidean_3_2multvs2_3mult_2_9[9] = {1, 0, 0, 0, 1, 0, 0, 0, 0}; 

static const uint32_t euclidean_12vs16odd_6_12[12] = {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0}; 

static const uint32_t euclidean_divider_1_3[3] = {1, 0, 0}; 

static const uint32_t euclidean_2vs3_2_6[6] = {1, 0, 0, 1, 0, 0}; 

static const uint32_t euclidean_3_2multvs2_3mult_3_24[24] = {1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0}; 

static const uint32_t euclidean_simple_3_16[16] = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0}; 

static const uint32_t euclidean_2vs3_3_7[7] = {1, 0, 1, 0, 1, 0, 0}; 

static const uint32_t euclidean_3_2multvs2_3mult_2_6[6] = {1, 0, 0, 1, 0, 0}; 

static const uint32_t euclidean_16vs32odd_7_16[16] = {1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0}; 

static const uint32_t euclidean_16vs32noprimes_14_32[32] = {1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0}; 

static const uint32_t euclidean_doubled_divider_1_12[12] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; 

static const uint32_t euclidean_12vs16odd_1_16[16] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; 

static const uint32_t euclidean_3_2multvs2_3mult_3_10[10] = {1, 0, 0, 1, 0, 0, 1, 0, 0, 0}; 

static const uint32_t euclidean_3_2multvs2_3mult_3_6[6] = {1, 0, 1, 0, 1, 0}; 

static const uint32_t euclidean_simple_8_8[8] = {1, 1, 1, 1, 1, 1, 1, 1}; 

static const uint32_t euclidean_divider_2_2[2] = {1, 1}; 

static const uint32_t euclidean_16vs32odd_9_32[32] = {1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0}; 

static const uint32_t euclidean_16vs32odd_11_32[32] = {1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0}; 

static const uint32_t euclidean_16vs32odd_7_32[32] = {1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0}; 

static const uint32_t euclidean_doubled_divider_2_7[7] = {1, 0, 0, 1, 0, 0, 0}; 

static const uint32_t euclidean_doubled_divider_1_6[6] = {1, 0, 0, 0, 0, 0}; 

static const uint32_t euclidean_simple_6_16[16] = {1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0}; 

static const uint32_t euclidean_16vs32noprimes_6_16[16] = {1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0}; 

static const uint32_t euclidean_16vs32odd_15_16[16] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0}; 

static const uint32_t euclidean_simple_7_16[16] = {1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0}; 

static const uint32_t euclidean_simple_1_8[8] = {1, 0, 0, 0, 0, 0, 0, 0}; 

static const uint32_t euclidean_12vs16odd_8_12[12] = {1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0}; 

static const uint32_t euclidean_2vs3_3_10[10] = {1, 0, 0, 1, 0, 0, 1, 0, 0, 0}; 

static const uint32_t euclidean_16vs32odd_5_16[16] = {1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0}; 

static const uint32_t euclidean_12vs16odd_3_16[16] = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0}; 

static const uint32_t euclidean_simple_5_8[8] = {1, 0, 1, 1, 0, 1, 1, 0}; 

static const uint32_t euclidean_divider_1_14[14] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; 

static const uint32_t euclidean_simple_7_8[8] = {1, 1, 1, 1, 1, 1, 1, 0}; 

static const uint32_t euclidean_divider_1_12[12] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; 

static const uint32_t euclidean_doubled_divider_1_4[4] = {1, 0, 0, 0}; 

static const uint32_t euclidean_16vs32odd_11_16[16] = {1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1}; 

static const uint32_t euclidean_doubled_divider_2_8[8] = {1, 0, 0, 0, 1, 0, 0, 0}; 

static const uint32_t euclidean_2vs3_2_9[9] = {1, 0, 0, 0, 1, 0, 0, 0, 0}; 

static const uint32_t euclidean_3_2multvs2_3mult_2_12[12] = {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0}; 

static const uint32_t euclidean_divider_1_16[16] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; 

static const uint32_t euclidean_3_2multvs2_3mult_2_24[24] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; 

static const uint32_t euclidean_divider_1_6[6] = {1, 0, 0, 0, 0, 0}; 

static const uint32_t euclidean_16vs32odd_13_32[32] = {1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0}; 

static const uint32_t euclidean_12vs16odd_7_12[12] = {1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0}; 

static const uint32_t euclidean_12vs16odd_5_12[12] = {1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0}; 

static const uint32_t euclidean_simple_4_8[8] = {1, 0, 1, 0, 1, 0, 1, 0}; 

static const uint32_t euclidean_2vs3_3_5[5] = {1, 0, 1, 0, 1}; 

static const uint32_t euclidean_2vs3_2_4[4] = {1, 0, 1, 0}; 

static const uint32_t euclidean_12vs16odd_5_16[16] = {1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0}; 

static const uint32_t euclidean_16vs32noprimes_10_32[32] = {1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0}; 

static const uint32_t euclidean_doubled_divider_1_10[10] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0}; 

static const uint32_t euclidean_3_2multvs2_3mult_2_21[21] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; 

static const uint32_t euclidean_divider_1_8[8] = {1, 0, 0, 0, 0, 0, 0, 0}; 

static const uint32_t euclidean_2vs3_3_3[3] = {1, 1, 1}; 

static const uint32_t euclidean_12vs16odd_2_12[12] = {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0}; 

static const uint32_t euclidean_16vs32odd_1_16[16] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; 

static const uint32_t euclidean_2vs3_2_7[7] = {1, 0, 0, 1, 0, 0, 0}; 

static const uint32_t euclidean_doubled_divider_2_3[3] = {1, 1, 0}; 

static const uint32_t euclidean_3_2multvs2_3mult_2_18[18] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0}; 

static const uint32_t euclidean_16vs32noprimes_4_32[32] = {1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0}; 

static const uint32_t euclidean_doubled_divider_2_6[6] = {1, 0, 0, 1, 0, 0}; 

static const uint32_t euclidean_simple_6_8[8] = {1, 1, 1, 0, 1, 1, 1, 0}; 

static const uint32_t euclidean_2vs3_2_5[5] = {1, 0, 1, 0, 0}; 




//////////////////////////////////////////////////////// 

static const uint32_t *euclidean_simple_a[8] = {euclidean_simple_1_16, euclidean_simple_2_16, euclidean_simple_3_16, euclidean_simple_4_16, euclidean_simple_5_16, euclidean_simple_6_16, euclidean_simple_7_16, euclidean_simple_8_16}; 

static const uint32_t *euclidean_simple_b[8] = {euclidean_simple_1_8, euclidean_simple_2_8, euclidean_simple_3_8, euclidean_simple_4_8, euclidean_simple_5_8, euclidean_simple_6_8, euclidean_simple_7_8, euclidean_simple_8_8}; 

static const uint32_t euclidean_simple_aLengths[8] = {16, 16, 16, 16, 16, 16, 16, 16}; 

static const uint32_t euclidean_simple_bLengths[8] = {8, 8, 8, 8, 8, 8, 8, 8}; 

static const pattern_bank euclidean_simple = {
   .aPatternBank = euclidean_simple_a,
   .bPatternBank = euclidean_simple_b,
   .aLengths = euclidean_simple_aLengths,
   .bLengths = euclidean_simple_bLengths,
   .aNumPatterns = 8,
   .bNumPatterns = 8};

//////////////////////////////////////////////////////// 

static const uint32_t *euclidean_2vs3_a[8] = {euclidean_2vs3_2_10, euclidean_2vs3_2_9, euclidean_2vs3_2_8, euclidean_2vs3_2_7, euclidean_2vs3_2_6, euclidean_2vs3_2_5, euclidean_2vs3_2_4, euclidean_2vs3_2_3}; 

static const uint32_t *euclidean_2vs3_b[8] = {euclidean_2vs3_3_10, euclidean_2vs3_3_9, euclidean_2vs3_3_8, euclidean_2vs3_3_7, euclidean_2vs3_3_6, euclidean_2vs3_3_5, euclidean_2vs3_3_4, euclidean_2vs3_3_3}; 

static const uint32_t euclidean_2vs3_aLengths[8] = {10, 9, 8, 7, 6, 5, 4, 3}; 

static const uint32_t euclidean_2vs3_bLengths[8] = {10, 9, 8, 7, 6, 5, 4, 3}; 

static const pattern_bank euclidean_2vs3 = {
   .aPatternBank = euclidean_2vs3_a,
   .bPatternBank = euclidean_2vs3_b,
   .aLengths = euclidean_2vs3_aLengths,
   .bLengths = euclidean_2vs3_bLengths,
   .aNumPatterns = 8,
   .bNumPatterns = 8};

//////////////////////////////////////////////////////// 

static const uint32_t *euclidean_3_2multvs2_3mult_a[8] = {euclidean_3_2multvs2_3mult_3_24, euclidean_3_2multvs2_3mult_3_16, euclidean_3_2multvs2_3mult_3_14, euclidean_3_2multvs2_3mult_3_12, euclidean_3_2multvs2_3mult_3_10, euclidean_3_2multvs2_3mult_3_8, euclidean_3_2multvs2_3mult_3_6, euclidean_3_2multvs2_3mult_3_4}; 

static const uint32_t *euclidean_3_2multvs2_3mult_b[8] = {euclidean_3_2multvs2_3mult_2_24, euclidean_3_2multvs2_3mult_2_21, euclidean_3_2multvs2_3mult_2_18, euclidean_3_2multvs2_3mult_2_15, euclidean_3_2multvs2_3mult_2_12, euclidean_3_2multvs2_3mult_2_9, euclidean_3_2multvs2_3mult_2_6, euclidean_3_2multvs2_3mult_2_3}; 

static const uint32_t euclidean_3_2multvs2_3mult_aLengths[8] = {24, 16, 14, 12, 10, 8, 6, 4}; 

static const uint32_t euclidean_3_2multvs2_3mult_bLengths[8] = {24, 21, 18, 15, 12, 9, 6, 3}; 

static const pattern_bank euclidean_3_2multvs2_3mult = {
   .aPatternBank = euclidean_3_2multvs2_3mult_a,
   .bPatternBank = euclidean_3_2multvs2_3mult_b,
   .aLengths = euclidean_3_2multvs2_3mult_aLengths,
   .bLengths = euclidean_3_2multvs2_3mult_bLengths,
   .aNumPatterns = 8,
   .bNumPatterns = 8};

//////////////////////////////////////////////////////// 

static const uint32_t *euclidean_12vs16odd_a[8] = {euclidean_12vs16odd_1_12, euclidean_12vs16odd_2_12, euclidean_12vs16odd_3_12, euclidean_12vs16odd_4_12, euclidean_12vs16odd_5_12, euclidean_12vs16odd_6_12, euclidean_12vs16odd_7_12, euclidean_12vs16odd_8_12}; 

static const uint32_t *euclidean_12vs16odd_b[8] = {euclidean_12vs16odd_1_16, euclidean_12vs16odd_3_16, euclidean_12vs16odd_5_16, euclidean_12vs16odd_7_16, euclidean_12vs16odd_9_16, euclidean_12vs16odd_11_16, euclidean_12vs16odd_13_16, euclidean_12vs16odd_15_16}; 

static const uint32_t euclidean_12vs16odd_aLengths[8] = {12, 12, 12, 12, 12, 12, 12, 12}; 

static const uint32_t euclidean_12vs16odd_bLengths[8] = {16, 16, 16, 16, 16, 16, 16, 16}; 

static const pattern_bank euclidean_12vs16odd = {
   .aPatternBank = euclidean_12vs16odd_a,
   .bPatternBank = euclidean_12vs16odd_b,
   .aLengths = euclidean_12vs16odd_aLengths,
   .bLengths = euclidean_12vs16odd_bLengths,
   .aNumPatterns = 8,
   .bNumPatterns = 8};

//////////////////////////////////////////////////////// 

static const uint32_t *euclidean_16vs32odd_a[8] = {euclidean_16vs32odd_1_16, euclidean_16vs32odd_3_16, euclidean_16vs32odd_5_16, euclidean_16vs32odd_7_16, euclidean_16vs32odd_9_16, euclidean_16vs32odd_11_16, euclidean_16vs32odd_13_16, euclidean_16vs32odd_15_16}; 

static const uint32_t *euclidean_16vs32odd_b[8] = {euclidean_16vs32odd_1_32, euclidean_16vs32odd_3_32, euclidean_16vs32odd_5_32, euclidean_16vs32odd_7_32, euclidean_16vs32odd_9_32, euclidean_16vs32odd_11_32, euclidean_16vs32odd_13_32, euclidean_16vs32odd_15_32}; 

static const uint32_t euclidean_16vs32odd_aLengths[8] = {16, 16, 16, 16, 16, 16, 16, 16}; 

static const uint32_t euclidean_16vs32odd_bLengths[8] = {32, 32, 32, 32, 32, 32, 32, 32}; 

static const pattern_bank euclidean_16vs32odd = {
   .aPatternBank = euclidean_16vs32odd_a,
   .bPatternBank = euclidean_16vs32odd_b,
   .aLengths = euclidean_16vs32odd_aLengths,
   .bLengths = euclidean_16vs32odd_bLengths,
   .aNumPatterns = 8,
   .bNumPatterns = 8};

//////////////////////////////////////////////////////// 

static const uint32_t *euclidean_16vs32noprimes_a[8] = {euclidean_16vs32noprimes_4_16, euclidean_16vs32noprimes_6_16, euclidean_16vs32noprimes_8_16, euclidean_16vs32noprimes_9_16, euclidean_16vs32noprimes_10_16, euclidean_16vs32noprimes_12_16, euclidean_16vs32noprimes_14_16, euclidean_16vs32noprimes_15_16}; 

static const uint32_t *euclidean_16vs32noprimes_b[8] = {euclidean_16vs32noprimes_4_32, euclidean_16vs32noprimes_6_32, euclidean_16vs32noprimes_8_32, euclidean_16vs32noprimes_9_32, euclidean_16vs32noprimes_10_32, euclidean_16vs32noprimes_12_32, euclidean_16vs32noprimes_14_32, euclidean_16vs32noprimes_15_32}; 

static const uint32_t euclidean_16vs32noprimes_aLengths[8] = {16, 16, 16, 16, 16, 16, 16, 16}; 

static const uint32_t euclidean_16vs32noprimes_bLengths[8] = {32, 32, 32, 32, 32, 32, 32, 32}; 

static const pattern_bank euclidean_16vs32noprimes = {
   .aPatternBank = euclidean_16vs32noprimes_a,
   .bPatternBank = euclidean_16vs32noprimes_b,
   .aLengths = euclidean_16vs32noprimes_aLengths,
   .bLengths = euclidean_16vs32noprimes_bLengths,
   .aNumPatterns = 8,
   .bNumPatterns = 8};

//////////////////////////////////////////////////////// 

static const uint32_t *euclidean_divider_a[8] = {euclidean_divider_1_8, euclidean_divider_1_7, euclidean_divider_1_6, euclidean_divider_1_5, euclidean_divider_1_4, euclidean_divider_1_3, euclidean_divider_1_2, euclidean_divider_2_2}; 

static const uint32_t *euclidean_divider_b[8] = {euclidean_divider_1_16, euclidean_divider_1_14, euclidean_divider_1_12, euclidean_divider_1_10, euclidean_divider_1_8, euclidean_divider_1_6, euclidean_divider_1_4, euclidean_divider_1_2}; 

static const uint32_t euclidean_divider_aLengths[8] = {8, 7, 6, 5, 4, 3, 2, 2}; 

static const uint32_t euclidean_divider_bLengths[8] = {16, 14, 12, 10, 8, 6, 4, 2}; 

static const pattern_bank euclidean_divider = {
   .aPatternBank = euclidean_divider_a,
   .bPatternBank = euclidean_divider_b,
   .aLengths = euclidean_divider_aLengths,
   .bLengths = euclidean_divider_bLengths,
   .aNumPatterns = 8,
   .bNumPatterns = 8};

//////////////////////////////////////////////////////// 

static const uint32_t *euclidean_doubled_divider_a[8] = {euclidean_doubled_divider_2_8, euclidean_doubled_divider_2_7, euclidean_doubled_divider_2_6, euclidean_doubled_divider_2_5, euclidean_doubled_divider_1_2, euclidean_doubled_divider_2_4, euclidean_doubled_divider_2_3, euclidean_doubled_divider_2_2}; 

static const uint32_t *euclidean_doubled_divider_b[8] = {euclidean_doubled_divider_1_16, euclidean_doubled_divider_1_14, euclidean_doubled_divider_1_12, euclidean_doubled_divider_1_10, euclidean_doubled_divider_1_8, euclidean_doubled_divider_1_6, euclidean_doubled_divider_1_4, euclidean_doubled_divider_1_2}; 

static const uint32_t euclidean_doubled_divider_aLengths[8] = {8, 7, 6, 5, 2, 4, 3, 2}; 

static const uint32_t euclidean_doubled_divider_bLengths[8] = {16, 14, 12, 10, 8, 6, 4, 2}; 

static const pattern_bank euclidean_doubled_divider = {
   .aPatternBank = euclidean_doubled_divider_a,
   .bPatternBank = euclidean_doubled_divider_b,
   .aLengths = euclidean_doubled_divider_aLengths,
   .bLengths = euclidean_doubled_divider_bLengths,
   .aNumPatterns = 8,
   .bNumPatterns = 8};

//////////////////////////////////////////////////////// 

