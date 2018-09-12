#include "scanner.h"

void scanner_fillWavetableArray(void) {

	scanner_wavetableArray[0] = &tenor257;
	scanner_wavetableArray[1] = &soprano257;
	scanner_wavetableArray[2] = &algerian;
	scanner_wavetableArray[3] = &linwavefold_257;
	scanner_wavetableArray[4] = &skipSaw;
	scanner_wavetableArray[5] = &imp_5;
	scanner_wavetableArray[6] = &additive_tri_to_pulse;
	scanner_wavetableArray[7] = &newBounce;

}

// declare functions to set the currently active tables
void scanner_switchWavetableX(Wavetable * table, scanner_signal_set * signals) {
	loadWavetableWithDiff15Bit(table, scanner_wavetableXRead);
	signals->parameters->xTableSize = table->numWaveforms - 1;
}

// declare functions to set the currently active tables
void scanner_switchWavetableY(Wavetable * table, scanner_signal_set * signals) {
	loadWavetableWithDiff15Bit(table, scanner_wavetableYRead);
	signals->parameters->yTableSize = table->numWaveforms - 1;
}
