#include <gateseq.hpp>

void ViaGateseq::initializePatterns() {
   patternBank[0] = &euclidean_simple;
   patternBank[1] = &euclidean_2vs3;
   patternBank[2] = &euclidean_3_2multvs2_3mult;
   patternBank[3] = &euclidean_12vs16odd;
   patternBank[4] = &euclidean_16vs32odd;
   patternBank[5] = &euclidean_16vs32noprimes;
   patternBank[6] = &euclidean_divider;
   patternBank[7] = &euclidean_doubled_divider;
}
