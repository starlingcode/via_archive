#include "scanner.hpp"


void ViaScanner::fillWavetableArray(void) {

	wavetableArray[0] = &tenor257;
	wavetableArray[1] = &soprano257;
	wavetableArray[2] = &algerian;
	wavetableArray[3] = &linwavefold_257;
	wavetableArray[4] = &skipSaw;
	wavetableArray[5] = &imp_5;
	wavetableArray[6] = &test_fm;
	wavetableArray[7] = &newBounce;
}


// declare functions to set the currently active tables
void ViaScanner::switchWavetableX(const Wavetable * table) {
	loadWavetableWithDiff15Bit(table, (uint32_t *) wavetableXRead);
	scanner.xTableSize = table->numWaveforms - 1;
}

// declare functions to set the currently active tables
void ViaScanner::switchWavetableY(const Wavetable * table) {
	loadWavetableWithDiff15Bit(table, (uint32_t *) wavetableYRead);
	scanner.yTableSize = table->numWaveforms - 1;
}