# include "meta.hpp"


void ViaMeta::fillWavetableArray(void) {

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