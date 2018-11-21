#include <gateseq.hpp>

void ViaGateseq::initializePatterns() {
   seq1PatternBank[0] = &sequencer1banknoclock_bank;
   seq1PatternBank[1] = &sequencer1banktriplet_bank;
   seq1PatternBank[2] = &sequencer1bankshuffle_bank;
   seq1PatternBank[3] = &sequencer1bankmultiplier_bank;
   seq2PatternBank[0] = &sequencer2bank1_bank;
   seq2PatternBank[1] = &sequencer2bank2_bank;
   seq2PatternBank[2] = &sequencer2bank3_bank;
   seq2PatternBank[3] = &sequencer2bank4_bank;
}
