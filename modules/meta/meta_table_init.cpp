#include "meta.hpp"

void ViaMeta::fillWavetableArray(void) {

	wavetableArray[audio][0] = &tenor257;
	wavetableArray[audio][1] = &soprano257;
	wavetableArray[audio][2] = &impevens;
	wavetableArray[audio][3] = &linwavefold_257;
	wavetableArray[audio][4] = &skipSaw;
	wavetableArray[audio][5] = &sinwavefold_257;
	wavetableArray[audio][6] = &additive_tri_to_pulse;
	wavetableArray[audio][7] = &newBounce;
	wavetableArray[env][0] = &testRMS;
	wavetableArray[env][1] = &gamma257;
	wavetableArray[env][2] = &bounce_257;
	wavetableArray[env][3] = &circular_257;
	wavetableArray[env][4] = &quintic_outin2quintic_inout257;
	wavetableArray[env][5] = &quintic_out2quintic_in257;
	wavetableArray[env][6] = &quintic_inout2quintic_outin257;
	wavetableArray[env][7] = &quintic_in2quintic_out257;
	wavetableArray[seq][0] = &bounce_257;
	wavetableArray[seq][1] = &exciteBike;
	wavetableArray[seq][2] = &newBounce;
	wavetableArray[seq][3] = &sawBend;
	wavetableArray[seq][4] = &triOdd;
	wavetableArray[seq][5] = &moogSquare;
	wavetableArray[seq][6] = &algerian;
	wavetableArray[seq][7] = &exciteBike;

}

// declare functions to set the currently active tables
void ViaMeta::switchWavetable(const Wavetable * table) {
	loadWavetableWithDiff15Bit(table, (uint32_t *) wavetableRead);
	metaWavetable.tableSize = table->numWaveforms - 1;
}

// declare functions to set the currently active tables
void ViaMeta::initDrum(void) {
	loadSingleTable15Bit(&drum, (uint32_t *) wavetableReadDrum);
	for (int32_t i = 0; i < 4; i++) {
		drumFullScale[i] = 32767;
	}
}
