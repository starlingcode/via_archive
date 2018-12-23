# include "meta.hpp"


void ViaMeta::fillWavetableArray(void) {

	wavetableArray[0][0] = &trains;
	wavetableArray[0][1] = &vox;
	wavetableArray[0][2] = &csound_formants;
	wavetableArray[0][3] = &perlin;
	wavetableArray[0][4] = &impevens;
	wavetableArray[0][5] = &additive_pairs;
	wavetableArray[0][6] = &linwavefold_257;
	wavetableArray[0][7] = &skipSaw;
	wavetableArray[1][0] = &gammaAsym;
	wavetableArray[1][1] = &sharpLinSym;
	wavetableArray[1][2] = &circular_257;
	wavetableArray[1][3] = &quintic_outinAsym;
	wavetableArray[1][4] = &doubleLump3rdDegLinAtk;
	wavetableArray[1][5] = &lump2ndDegLinAtk;
	wavetableArray[1][6] = &testRMS2;
	wavetableArray[1][7] = &testRMS;
	wavetableArray[2][0] = &bounce;
	wavetableArray[2][1] = &bounce_257;
	wavetableArray[2][2] = &sawBend;
	wavetableArray[2][3] = &exciteBike;
	wavetableArray[2][4] = &skipSaw;
	wavetableArray[2][5] = &euclidean_test;
	wavetableArray[2][6] = &newest_steps;
	wavetableArray[2][7] = &block_test;
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