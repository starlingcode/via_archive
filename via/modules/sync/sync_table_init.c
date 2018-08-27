#include "sync.h"

//void loadPhaseDistTable(PhaseDistTable * table, uint32_t * tableRead);
//void loadWavetableWithDiff(Wavetable * table, uint32_t * tableRead);

void sync_fillWavetableArray(void) {

	sync_wavetableArray[0][0] = &tenor257;
	sync_wavetableArray[0][1] = &soprano257;
	sync_wavetableArray[0][2] = &impevens;
	sync_wavetableArray[0][3] = &linwavefold_257;

	sync_wavetableArray[1][0] = &skipSaw;
	sync_wavetableArray[1][1] = &sinwavefold_257;
	sync_wavetableArray[1][2] = &additive_tri_to_pulse;
	sync_wavetableArray[1][3] = &newBounce;

	sync_wavetableArray[2][0] = &triOdd;
	sync_wavetableArray[2][1] = &moogSquare;
	sync_wavetableArray[2][2] = &algerian;
	sync_wavetableArray[2][3] = &exciteBike;

	sync_wavetableArray[3][0] = &testRMS;
	sync_wavetableArray[3][1] = &gamma257;
	sync_wavetableArray[3][2] = &bounce_257;
	sync_wavetableArray[3][3] = &circular_257;

	sync_wavetableArrayGlobal[0] = &linwavefold_257;
	sync_wavetableArrayGlobal[1] = &sinwavefold_257;
	sync_wavetableArrayGlobal[2] = &newBounce;
	sync_wavetableArrayGlobal[3] = &skipSaw;

}

// declare functions to set the currently active tables
void sync_switchWavetable(Wavetable * table, sync_signal_set * signals) {
	loadWavetableWithDiff(table, sync_wavetableRead);
	signals->wavetable_parameters->tableSize = table->numWaveforms - 1;
}

// declare functions to set the currently active tables
void sync_switchWavetableGlobal(Wavetable * table, sync_signal_set * signals) {
	loadWavetableWithDiff(table, sync_wavetableRead);
	signals->wavetable_parameters->tableSize = table->numWaveforms - 1;
}

//// declare functions to set the currently active tables
//void sync_initPhaseDistTable(void) {
//	loadPhaseDistTable(&phaseDistPWM, sync_phaseDistRead);
//}

