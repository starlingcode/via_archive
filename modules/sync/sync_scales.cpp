
#include "sync.hpp"

void ViaSync::initializeScales() {
   scaleArray[0][0] = &integerRatios;
   scaleArray[0][1] = &pentamodal5primefullspan;
   scaleArray[0][2] = &harmSubharmfullspan;
   scaleArray[0][3] = &modal5primefullspan;
   scaleArray[1][0] = &harmSubharm;
   scaleArray[1][1] = &harmFolded4;
   scaleArray[1][2] = &pentamodal5prime;
   scaleArray[1][3] = &triads;
   scaleArray[2][0] = &seventhTetradsMinimalProgression;
   scaleArray[2][1] = &seventhTetrads;
   scaleArray[2][2] = &modesOfLimitedTransposition;
   scaleArray[2][3] = &majMin9thPentStarling;
   scaleArray[3][0] = &simpleRhythms;
   scaleArray[3][1] = &simpleRhythms16;
   scaleArray[3][2] = &rhythmDivisionsReset;
   scaleArray[3][3] = &polyResets;
}
