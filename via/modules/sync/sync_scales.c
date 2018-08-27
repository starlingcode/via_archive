
#include "sync.h"

void sync_initializeScales() {

   sync_scaleArray[0][0] = &integerRatios;
   sync_scaleArray[0][1] = &pentamodal5primefullspan;
   sync_scaleArray[0][2] = &harmSubharmfullspan;
   sync_scaleArray[0][3] = &modal5primefullspan;

   sync_scaleArray[1][0] = &harmSubharm;
   sync_scaleArray[1][1] = &harmFolded4;
   sync_scaleArray[1][2] = &pentamodal5prime;
   sync_scaleArray[1][3] = &triads;

   sync_scaleArray[2][0] = &seventhTetradsMinimalProgression;
   sync_scaleArray[2][1] = &seventhTetrads;
   sync_scaleArray[2][2] = &modesOfLimitedTransposition;
   sync_scaleArray[2][3] = &majMin9thPentStarling;

   sync_scaleArray[3][0] = &simpleRhythms;
   sync_scaleArray[3][1] = &simpleRhythms16;
   sync_scaleArray[3][2] = &rhythmDivisionsReset;
   sync_scaleArray[3][3] = &polyResets;

}

