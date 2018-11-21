# include "meta.hpp"


void ViaMeta::fillWavetableArray(void) {

	wavetableArray[0][0] = &trains;
	wavetableArray[0][1] = &waterphone;
	wavetableArray[0][2] = &vox;
	wavetableArray[0][3] = &csound_formants;
	wavetableArray[0][4] = &impevens;
	wavetableArray[0][5] = &sinwavefold_257;
	wavetableArray[0][6] = &linwavefold_257;
	wavetableArray[0][7] = &skipSaw;
	wavetableArray[1][0] = &testRMS;
	wavetableArray[1][1] = &gamma257;
	wavetableArray[1][2] = &bounce_257;
	wavetableArray[1][3] = &circular_257;
	wavetableArray[1][4] = &sharpExpoSym;
	wavetableArray[1][5] = &quintic_out2quintic_in257;
	wavetableArray[1][6] = &quintic_inout2quintic_outin257;
	wavetableArray[1][7] = &newBounce;
	wavetableArray[2][0] = &bounce_257;
	wavetableArray[2][1] = &exciteBike;
	wavetableArray[2][2] = &newBounce;
	wavetableArray[2][3] = &sawBend;
	wavetableArray[2][4] = &triOdd;
	wavetableArray[2][5] = &moogSquare;
	wavetableArray[2][6] = &algerian;
	wavetableArray[2][7] = &exciteBike;
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