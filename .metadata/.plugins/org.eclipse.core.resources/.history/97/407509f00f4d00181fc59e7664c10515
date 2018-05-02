#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"



typedef struct {
	const uint32_t *data;
	const uint32_t length;
} pattern;


typedef struct {
	const pattern *aPatternBank;
	const pattern *bPatternBank;
	const uint32_t aLength;
	const uint32_t bLength;
} pattern_bank;



static const pattern euclidean_simple_3_8[8] = {{1, 0, 0, 1, 0, 0, 1, 0}, 8}; 

static const pattern euclidean_simple_8_16[16] = {{1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0}, 16}; 

static const pattern euclidean_simple_8_8[8] = {{1, 1, 1, 1, 1, 1, 1, 1}, 8}; 

static const pattern euclidean_simple_6_8[8] = {{1, 1, 1, 0, 1, 1, 1, 0}, 8}; 

static const pattern euclidean_simple_4_16[16] = {{1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0}, 16}; 

static const pattern euclidean_simple_4_8[8] = {{1, 0, 1, 0, 1, 0, 1, 0}, 8}; 

static const pattern euclidean_simple_5_8[8] = {{1, 0, 1, 1, 0, 1, 1, 0}, 8}; 

static const pattern euclidean_simple_6_16[16] = {{1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0}, 16}; 

static const pattern euclidean_simple_7_16[16] = {{1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0}, 16}; 

static const pattern euclidean_simple_2_16[16] = {{1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0}, 16}; 

static const pattern euclidean_simple_5_16[16] = {{1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0}, 16}; 

static const pattern euclidean_simple_3_16[16] = {{1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0}, 16}; 

static const pattern euclidean_simple_1_16[16] = {{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 16}; 

static const pattern euclidean_simple_7_8[8] = {{1, 1, 1, 1, 1, 1, 1, 0}, 8}; 

static const pattern euclidean_simple_1_8[8] = {{1, 0, 0, 0, 0, 0, 0, 0}, 8}; 

static const pattern euclidean_simple_2_8[8] = {{1, 0, 0, 0, 1, 0, 0, 0}, 8}; 




static const uint32_t *euclidean_simple_a[8] = {euclidean_simple_1_16, euclidean_simple_2_16, euclidean_simple_3_16, euclidean_simple_4_16, euclidean_simple_5_16, euclidean_simple_6_16, euclidean_simple_7_16, euclidean_simple_8_16}; 

static const uint32_t *euclidean_simple_b[8] = {euclidean_simple_1_8, euclidean_simple_2_8, euclidean_simple_3_8, euclidean_simple_4_8, euclidean_simple_5_8, euclidean_simple_6_8, euclidean_simple_7_8, euclidean_simple_8_8}; 

static const pattern_bank euclidean_simple = {
   .aPatternBank = euclidean_simple_a,
   .bPatternBank = euclidean_simple_b,
   .aLength = 8,
   .bLength = 8};

