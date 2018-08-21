#include "osc.h"


//void loadPhaseDistTable(PhaseDistTable * table, uint32_t * tableRead);
//void loadWavetableWithDiff(Wavetable * table, uint32_t * tableRead);

void osc_fillWavetableArray(void) {
	osc_wavetableArray[0] = &tenor257;
	osc_wavetableArray[1] = &soprano257;
	osc_wavetableArray[2] = &impevens;
	osc_wavetableArray[3] = &linwavefold_257;
	osc_wavetableArray[4] = &skipSaw;
	osc_wavetableArray[5] = &sinwavefold_257;
	osc_wavetableArray[6] = &additive_tri_to_pulse;
	osc_wavetableArray[7] = &newBounce;
}

// declare functions to set the currently active tables
void osc_switchWavetable(Wavetable * table, osc_signals * signals) {
	loadWavetableWithDiff(table, osc_wavetableRead);
	signals->parameters->tableSize = table->numWaveforms - 1;
}

//// declare functions to set the currently active tables
void osc_initPhaseDist(void) {
	loadPhaseDistTable(&phaseDistPWM, osc_phaseDistRead);
}

