#ifndef SEQUENCERS_INC_BOOLEAN_SEQUENCES_H_
#define SEQUENCERS_INC_BOOLEAN_SEQUENCES_H_

typedef struct {
	const uint32_t **patternBank;
	const uint32_t *lengths;
	const uint32_t numPatterns;
} booleanSequenceBank;

/////////////////////////
// Euclidean sequences //
/////////////////////////


static const uint32_t euclidean_divider_1_14[14] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; 

static const uint32_t euclidean_doubled_divider_2_6[6] = {1, 0, 0, 1, 0, 0}; 

static const uint32_t euclidean_doubled_divider_1_6[6] = {1, 0, 0, 0, 0, 0}; 

static const uint32_t euclidean_simple_8_8[8] = {1, 1, 1, 1, 1, 1, 1, 1}; 

static const uint32_t euclidean_simple_3_8[8] = {1, 0, 0, 1, 0, 0, 1, 0}; 

static const uint32_t euclidean_2vs3_3_5[5] = {1, 0, 1, 0, 1}; 

static const uint32_t euclidean_12vs16odd_14_24[24] = {1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0}; 

static const uint32_t euclidean_divider_1_7[7] = {1, 0, 0, 0, 0, 0, 0}; 

static const uint32_t euclidean_16vs32odd_7_32[32] = {1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0}; 

static const uint32_t euclidean_simple_2_8[8] = {1, 0, 0, 0, 1, 0, 0, 0}; 

static const uint32_t euclidean_2vs3_2_9[9] = {1, 0, 0, 0, 1, 0, 0, 0, 0}; 

static const uint32_t euclidean_divider_1_16[16] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; 

static const uint32_t euclidean_16vs32odd_11_16[16] = {1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1}; 

static const uint32_t euclidean_2vs3_3_6[6] = {1, 0, 1, 0, 1, 0}; 

static const uint32_t euclidean_16vs32odd_9_16[16] = {1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0}; 

static const uint32_t euclidean_12vs16odd_18_24[24] = {1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0}; 

static const uint32_t euclidean_divider_2_2[2] = {1, 1}; 

static const uint32_t euclidean_simple_7_16[16] = {1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0}; 

static const uint32_t euclidean_divider_1_4[4] = {1, 0, 0, 0}; 

static const uint32_t euclidean_doubled_divider_1_14[14] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; 

static const uint32_t euclidean_doubled_divider_2_2[2] = {1, 1}; 

static const uint32_t euclidean_divider_1_8[8] = {1, 0, 0, 0, 0, 0, 0, 0}; 

static const uint32_t euclidean_2vs3_3_8[8] = {1, 0, 0, 1, 0, 0, 1, 0}; 

static const uint32_t euclidean_12vs16odd_20_24[24] = {1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0}; 

static const uint32_t euclidean_simple_1_16[16] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; 

static const uint32_t euclidean_12vs16odd_6_24[24] = {1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0}; 

static const uint32_t euclidean_16vs32odd_9_32[32] = {1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0}; 

static const uint32_t euclidean_divider_1_2[2] = {1, 0}; 

static const uint32_t euclidean_2vs3_2_10[10] = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0}; 

static const uint32_t euclidean_divider_1_6[6] = {1, 0, 0, 0, 0, 0}; 

static const uint32_t euclidean_12vs16odd_12_24[24] = {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0}; 

static const uint32_t euclidean_2vs3_3_10[10] = {1, 0, 0, 1, 0, 0, 1, 0, 0, 0}; 

static const uint32_t euclidean_12vs16odd_5_24[24] = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0}; 

static const uint32_t euclidean_16vs32odd_7_16[16] = {1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0}; 

static const uint32_t euclidean_doubled_divider_2_3[3] = {1, 1, 0}; 

static const uint32_t euclidean_16vs32odd_15_16[16] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0}; 

static const uint32_t euclidean_doubled_divider_1_8[8] = {1, 0, 0, 0, 0, 0, 0, 0}; 

static const uint32_t euclidean_12vs16odd_22_24[24] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0}; 

static const uint32_t euclidean_16vs32odd_3_16[16] = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0}; 

static const uint32_t euclidean_doubled_divider_1_16[16] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; 

static const uint32_t euclidean_2vs3_3_7[7] = {1, 0, 1, 0, 1, 0, 0}; 

static const uint32_t euclidean_doubled_divider_2_8[8] = {1, 0, 0, 0, 1, 0, 0, 0}; 

static const uint32_t euclidean_simple_6_8[8] = {1, 1, 1, 0, 1, 1, 1, 0}; 

static const uint32_t euclidean_simple_2_16[16] = {1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0}; 

static const uint32_t euclidean_divider_1_5[5] = {1, 0, 0, 0, 0}; 

static const uint32_t euclidean_doubled_divider_1_12[12] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; 

static const uint32_t euclidean_2vs3_3_9[9] = {1, 0, 0, 1, 0, 0, 1, 0, 0}; 

static const uint32_t euclidean_12vs16odd_10_24[24] = {1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0}; 

static const uint32_t euclidean_12vs16odd_4_24[24] = {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0}; 

static const uint32_t euclidean_16vs32odd_1_16[16] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; 

static const uint32_t euclidean_16vs32odd_3_32[32] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0}; 

static const uint32_t euclidean_simple_1_8[8] = {1, 0, 0, 0, 0, 0, 0, 0}; 

static const uint32_t euclidean_doubled_divider_2_5[5] = {1, 0, 1, 0, 0}; 

static const uint32_t euclidean_16vs32odd_1_32[32] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; 

static const uint32_t euclidean_doubled_divider_1_4[4] = {1, 0, 0, 0}; 

static const uint32_t euclidean_16vs32odd_11_32[32] = {1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0}; 

static const uint32_t euclidean_simple_5_8[8] = {1, 0, 1, 1, 0, 1, 1, 0}; 

static const uint32_t euclidean_2vs3_2_5[5] = {1, 0, 1, 0, 0}; 

static const uint32_t euclidean_divider_1_10[10] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0}; 

static const uint32_t euclidean_simple_6_16[16] = {1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0}; 

static const uint32_t euclidean_2vs3_2_6[6] = {1, 0, 0, 1, 0, 0}; 

static const uint32_t euclidean_divider_1_3[3] = {1, 0, 0}; 

static const uint32_t euclidean_simple_8_16[16] = {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0}; 

static const uint32_t euclidean_simple_4_8[8] = {1, 0, 1, 0, 1, 0, 1, 0}; 

static const uint32_t euclidean_12vs16odd_8_24[24] = {1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0}; 

static const uint32_t euclidean_16vs32odd_15_32[32] = {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0}; 

static const uint32_t euclidean_12vs16odd_2_24[24] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; 

static const uint32_t euclidean_12vs16odd_1_24[24] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; 

static const uint32_t euclidean_12vs16odd_16_24[24] = {1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0}; 

static const uint32_t euclidean_16vs32odd_5_32[32] = {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0}; 

static const uint32_t euclidean_simple_3_16[16] = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0}; 

static const uint32_t euclidean_2vs3_2_8[8] = {1, 0, 0, 0, 1, 0, 0, 0}; 

static const uint32_t euclidean_doubled_divider_2_4[4] = {1, 0, 1, 0}; 

static const uint32_t euclidean_doubled_divider_1_10[10] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0}; 

static const uint32_t euclidean_16vs32odd_13_32[32] = {1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0}; 

static const uint32_t euclidean_12vs16odd_7_24[24] = {1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0}; 

static const uint32_t euclidean_16vs32odd_13_16[16] = {1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1}; 

static const uint32_t euclidean_2vs3_3_4[4] = {1, 1, 1, 0}; 

static const uint32_t euclidean_simple_4_16[16] = {1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0}; 

static const uint32_t euclidean_12vs16odd_24_24[24] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}; 

static const uint32_t euclidean_divider_1_12[12] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; 

static const uint32_t euclidean_16vs32odd_5_16[16] = {1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0}; 

static const uint32_t euclidean_2vs3_2_3[3] = {1, 1, 0}; 

static const uint32_t euclidean_2vs3_3_3[3] = {1, 1, 1}; 

static const uint32_t euclidean_simple_5_16[16] = {1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0}; 

static const uint32_t euclidean_12vs16odd_3_24[24] = {1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0}; 

static const uint32_t euclidean_2vs3_2_7[7] = {1, 0, 0, 1, 0, 0, 0}; 

static const uint32_t euclidean_simple_7_8[8] = {1, 1, 1, 1, 1, 1, 1, 0}; 

static const uint32_t euclidean_doubled_divider_1_2[2] = {1, 0}; 

static const uint32_t euclidean_2vs3_2_4[4] = {1, 0, 1, 0}; 

static const uint32_t euclidean_doubled_divider_2_7[7] = {1, 0, 0, 1, 0, 0, 0}; 




//////////////////////////////////////////////////////// 

// Banks 
//////////////////////////////////////////////////////// 

static const uint32_t *euclidean_simple[16] = {euclidean_simple_1_16, euclidean_simple_2_16, euclidean_simple_1_8, euclidean_simple_3_16, euclidean_simple_4_16, euclidean_simple_2_8, euclidean_simple_5_16, euclidean_simple_6_16, euclidean_simple_3_8, euclidean_simple_7_16, euclidean_simple_8_16, euclidean_simple_4_8, euclidean_simple_5_8, euclidean_simple_6_8, euclidean_simple_7_8, euclidean_simple_8_8}; 

static const uint32_t euclidean_simpleLengths[16] = {16, 16, 8, 16, 16, 8, 16, 16, 8, 16, 16, 8, 8, 8, 8, 8}; 

static const booleanSequenceBank euclidean_simple_bank = {
   .patternBank = euclidean_simple,
   .lengths = euclidean_simpleLengths,
   .numPatterns = 16};
//////////////////////////////////////////////////////// 

static const uint32_t *euclidean_12vs16odd[16] = {euclidean_12vs16odd_1_24, euclidean_12vs16odd_2_24, euclidean_12vs16odd_3_24, euclidean_12vs16odd_4_24, euclidean_12vs16odd_5_24, euclidean_12vs16odd_6_24, euclidean_12vs16odd_7_24, euclidean_12vs16odd_8_24, euclidean_12vs16odd_10_24, euclidean_12vs16odd_12_24, euclidean_12vs16odd_14_24, euclidean_12vs16odd_16_24, euclidean_12vs16odd_18_24, euclidean_12vs16odd_20_24, euclidean_12vs16odd_22_24, euclidean_12vs16odd_24_24}; 

static const uint32_t euclidean_12vs16oddLengths[16] = {24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24}; 

static const booleanSequenceBank euclidean_12vs16odd_bank = {
   .patternBank = euclidean_12vs16odd,
   .lengths = euclidean_12vs16oddLengths,
   .numPatterns = 16};
//////////////////////////////////////////////////////// 

static const uint32_t *euclidean_16vs32odd[16] = {euclidean_16vs32odd_1_32, euclidean_16vs32odd_1_16, euclidean_16vs32odd_3_32, euclidean_16vs32odd_5_32, euclidean_16vs32odd_3_16, euclidean_16vs32odd_7_32, euclidean_16vs32odd_9_32, euclidean_16vs32odd_5_16, euclidean_16vs32odd_11_32, euclidean_16vs32odd_13_32, euclidean_16vs32odd_7_16, euclidean_16vs32odd_15_32, euclidean_16vs32odd_9_16, euclidean_16vs32odd_11_16, euclidean_16vs32odd_13_16, euclidean_16vs32odd_15_16}; 

static const uint32_t euclidean_16vs32oddLengths[16] = {32, 16, 32, 32, 16, 32, 32, 16, 32, 32, 16, 32, 16, 16, 16, 16}; 

static const booleanSequenceBank euclidean_16vs32odd_bank = {
   .patternBank = euclidean_16vs32odd,
   .lengths = euclidean_16vs32oddLengths,
   .numPatterns = 16};
//////////////////////////////////////////////////////// 

static const uint32_t *euclidean_divider[16] = {euclidean_divider_1_16, euclidean_divider_1_14, euclidean_divider_1_12, euclidean_divider_1_10, euclidean_divider_1_8, euclidean_divider_1_8, euclidean_divider_1_7, euclidean_divider_1_6, euclidean_divider_1_6, euclidean_divider_1_5, euclidean_divider_1_4, euclidean_divider_1_4, euclidean_divider_1_3, euclidean_divider_1_2, euclidean_divider_1_2, euclidean_divider_2_2}; 

static const uint32_t euclidean_dividerLengths[16] = {16, 14, 12, 10, 8, 8, 7, 6, 6, 5, 4, 4, 3, 2, 2, 2}; 

static const booleanSequenceBank euclidean_divider_bank = {
   .patternBank = euclidean_divider,
   .lengths = euclidean_dividerLengths,
   .numPatterns = 16};
//////////////////////////////////////////////////////// 

static const uint32_t *euclidean_2vs3[16] = {euclidean_2vs3_2_10, euclidean_2vs3_2_9, euclidean_2vs3_2_8, euclidean_2vs3_2_7, euclidean_2vs3_3_10, euclidean_2vs3_2_6, euclidean_2vs3_3_9, euclidean_2vs3_3_8, euclidean_2vs3_2_5, euclidean_2vs3_3_7, euclidean_2vs3_2_4, euclidean_2vs3_3_6, euclidean_2vs3_3_5, euclidean_2vs3_2_3, euclidean_2vs3_3_4, euclidean_2vs3_3_3}; 

static const uint32_t euclidean_2vs3Lengths[16] = {10, 9, 8, 7, 10, 6, 9, 8, 5, 7, 4, 6, 5, 3, 4, 3}; 

static const booleanSequenceBank euclidean_2vs3_bank = {
   .patternBank = euclidean_2vs3,
   .lengths = euclidean_2vs3Lengths,
   .numPatterns = 16};
//////////////////////////////////////////////////////// 

static const uint32_t *euclidean_doubled_divider[16] = {euclidean_doubled_divider_1_16, euclidean_doubled_divider_1_14, euclidean_doubled_divider_1_12, euclidean_doubled_divider_1_10, euclidean_doubled_divider_1_8, euclidean_doubled_divider_1_6, euclidean_doubled_divider_2_8, euclidean_doubled_divider_1_4, euclidean_doubled_divider_2_7, euclidean_doubled_divider_2_6, euclidean_doubled_divider_2_5, euclidean_doubled_divider_1_2, euclidean_doubled_divider_2_4, euclidean_doubled_divider_1_2, euclidean_doubled_divider_2_3, euclidean_doubled_divider_2_2}; 

static const uint32_t euclidean_doubled_dividerLengths[16] = {16, 14, 12, 10, 8, 6, 8, 4, 7, 6, 5, 2, 4, 2, 3, 2}; 

static const booleanSequenceBank euclidean_doubled_divider_bank = {
   .patternBank = euclidean_doubled_divider,
   .lengths = euclidean_doubled_dividerLengths,
   .numPatterns = 16};
//////////////////////////////////////////////////////// 

#endif