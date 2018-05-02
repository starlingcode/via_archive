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



static const uint32_t euclidean_simple_1_8[8] = {1, 0, 0, 0, 0, 0, 0, 0}; 

static const uint32_t euclidean_simple_3_16[16] = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0}; 

static const uint32_t euclidean_simple_8_8[8] = {1, 1, 1, 1, 1, 1, 1, 1}; 

static const uint32_t euclidean_simple_2_8[8] = {1, 0, 0, 0, 1, 0, 0, 0}; 

static const uint32_t euclidean_simple_5_16[16] = {1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0}; 

static const uint32_t euclidean_simple_3_8[8] = {1, 0, 0, 1, 0, 0, 1, 0}; 

static const uint32_t euclidean_simple_4_8[8] = {1, 0, 1, 0, 1, 0, 1, 0}; 

static const uint32_t euclidean_simple_7_16[16] = {1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0}; 

static const uint32_t euclidean_simple_8_16[16] = {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0}; 

static const uint32_t euclidean_simple_1_16[16] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; 

static const uint32_t euclidean_simple_7_8[8] = {1, 1, 1, 1, 1, 1, 1, 0}; 

static const uint32_t euclidean_simple_2_16[16] = {1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0}; 

static const uint32_t euclidean_simple_5_8[8] = {1, 0, 1, 1, 0, 1, 1, 0}; 

static const uint32_t euclidean_simple_6_8[8] = {1, 1, 1, 0, 1, 1, 1, 0}; 

static const uint32_t euclidean_simple_6_16[16] = {1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0}; 

static const uint32_t euclidean_simple_4_16[16] = {1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0}; 




static const uint32_t *euclidean_simple_a[8] = {euclidean_simple_1_16, euclidean_simple_2_16, euclidean_simple_3_16, euclidean_simple_4_16, euclidean_simple_5_16, euclidean_simple_6_16, euclidean_simple_7_16, euclidean_simple_8_16}; 

static const uint32_t *euclidean_simple_b[8] = {euclidean_simple_1_8, euclidean_simple_2_8, euclidean_simple_3_8, euclidean_simple_4_8, euclidean_simple_5_8, euclidean_simple_6_8, euclidean_simple_7_8, euclidean_simple_8_8}; 

static const uint32_t euclidean_simple_aLengths[8] = {16, 16, 16, 16, 16, 16, 16, 16}; 

static const uint32_t euclidean_simple_bLengths[8] = {8, 8, 8, 8, 8, 8, 8, 8}; 

static const pattern_bank euclidean_simple = {
   .aPatternBank = euclidean_simple_a,
   .bPatternBank = euclidean_simple_b,
   .aLengths = euclidean_simple_aLength,
   .bLengths = euclidean_simple_bLengths,
   .aNumPatterns = 8,
   .bNumPatterns = 8};

