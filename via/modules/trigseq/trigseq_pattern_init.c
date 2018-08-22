
#include "trigseq.h"


void trigseq_initializePatterns() {
	trigseq_patternBank[0] = &euclidean_simple;
	trigseq_patternBank[1] = &euclidean_2vs3;
	trigseq_patternBank[2] = &euclidean_3_2multvs2_3mult;
	trigseq_patternBank[3] = &euclidean_12vs16odd;
	trigseq_patternBank[4] = &euclidean_16vs32odd;
	trigseq_patternBank[5] = &euclidean_16vs32noprimes;
	trigseq_patternBank[6] = &euclidean_divider;
	trigseq_patternBank[7] = &euclidean_doubled_divider;
}
