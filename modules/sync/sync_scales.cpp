
#include "sync.hpp"

void ViaSync::initializeScales() {
   scaleArray[0][0] = &integerRatios;
   scaleArray[0][1] = &even_integers;
   scaleArray[0][2] = &rhythm_integers;
   scaleArray[0][3] = &odd_integers;
   scaleArray[1][0] = &majMin9thPentStarling;
   scaleArray[1][1] = &seventhTetradsMinimalProgression;
   scaleArray[1][2] = &impressionist;
   scaleArray[1][3] = &bohlenPeirce;
   scaleArray[2][0] = &pentamodal5prime;
   scaleArray[2][1] = &add9thSixthsusp4th;
   scaleArray[2][2] = &harm73_75;
   scaleArray[2][3] = &h73_75_BPwide;
   scaleArray[3][0] = &simpleRhythms;
   scaleArray[3][1] = &simpleRhythms16;
   scaleArray[3][2] = &rhythmDivisionsReset;
   scaleArray[3][3] = &polyResets;
}
