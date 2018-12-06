#include "scanner.hpp"


void ViaScanner::fillWavetableArray(void) {

	wavetableArray[0] = &hyperbolic_shapers;
	wavetableArray[1] = &tanh_res;
	wavetableArray[2] = &newBounce;
	wavetableArray[3] = &bessel;
	wavetableArray[4] = &test_fm;
	wavetableArray[5] = &soprano257;
	wavetableArray[6] = &bitcrush;
	wavetableArray[7] = &new_steps;
}


// declare functions to set the currently active tables
void ViaScanner::switchWavetableX(const Wavetable * table) {
	loadWavetableWithDiff15BitSlope(table, (uint32_t *) wavetableXRead);
	scanner.xTableSize = table->numWaveforms - 1;
}

// declare functions to set the currently active tables
void ViaScanner::switchWavetableY(const Wavetable * table) {
	loadWavetableWithDiff15BitSlope(table, (uint32_t *) wavetableYRead);
	scanner.yTableSize = table->numWaveforms - 1;
}