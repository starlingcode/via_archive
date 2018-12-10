#include "scanner.hpp"


void ViaScanner::fillWavetableArray(void) {

	wavetableArray[0][0] = &hyperbolic_shapers;
	wavetableArray[0][1] = &tanh_res;
	wavetableArray[0][2] = &newBounce;
	wavetableArray[0][3] = &exciteBike;
	wavetableArray[0][4] = &test_fm;
	wavetableArray[0][5] = &sin_phase_shift;
	wavetableArray[0][6] = &bitcrush;
	wavetableArray[0][7] = &new_steps;
	wavetableArray[1][0] = &circular_257;
	wavetableArray[1][1] = &bessel;
	wavetableArray[1][2] = &additive_tri_to_pulse;
	wavetableArray[1][3] = &sawBend;
	wavetableArray[1][4] = &moog5Square;
	wavetableArray[1][5] = &triangle_comb;
	wavetableArray[1][6] = &bitcrush;
	wavetableArray[1][7] = &steps5;
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