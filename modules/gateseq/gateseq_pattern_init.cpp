#include <gateseq.hpp>

void ViaGateseq::initializePatterns() {
   seq1PatternBank[0] = &euclidean_simple_bank;
   seq1PatternBank[1] = &euclidean_12vs16odd_bank;
   seq1PatternBank[2] = &euclidean_16vs32odd_bank;
   seq1PatternBank[3] = &euclidean_divider_bank;
   seq2PatternBank[0] = &euclidean_simple_bank;
   seq2PatternBank[1] = &euclidean_2vs3_bank;
   seq2PatternBank[2] = &euclidean_16vs32odd_bank;
   seq2PatternBank[3] = &euclidean_doubled_divider_bank;
}
