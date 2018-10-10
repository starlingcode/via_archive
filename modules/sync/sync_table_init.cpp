# include "sync.hpp"


void ViaSync::fillWavetableArray(void) {

	wavetableArray[	0][0] = &tenor257;
	wavetableArray[	0][1] = &soprano257;
	wavetableArray[	0][2] = &impevens;
	wavetableArray[	0][3] = &linwavefold_257;
	wavetableArray[	1][0] = &skipSaw;
	wavetableArray[	1][1] = &sinwavefold_257;
	wavetableArray[	1][2] = &additive_tri_to_pulse;
	wavetableArray[	1][3] = &newBounce;
	wavetableArray[	2][0] = &triOdd;
	wavetableArray[	2][1] = &moogSquare;
	wavetableArray[	2][2] = &algerian;
	wavetableArray[	2][3] = &exciteBike;
	wavetableArray[	3][0] = &testRMS;
	wavetableArray[	3][1] = &gamma257;
	wavetableArray[	3][2] = &bounce_257;
	wavetableArray[	3][3] = &circular_257;
	wavetableArrayGlobal[0] = &linwavefold_257;
	wavetableArrayGlobal[1] = &sinwavefold_257;
	wavetableArrayGlobal[2] = &newBounce;
	wavetableArrayGlobal[3] = &skipSaw;
}


// declare functions to set the currently active tables
void ViaSync::switchWavetable(const Wavetable * table) {
	loadWavetableWithDiff(table, (uint32_t *) wavetableRead);
	syncWavetable.tableSize = table->numWaveforms - 1;
}

// declare functions to set the currently active tables
void ViaSync::switchWavetableGlobal(const Wavetable * table) {
	loadWavetableWithDiff(table, (uint32_t *) wavetableRead);
	syncWavetable.tableSize = table->numWaveforms - 1;
}

//// declare functions to set the currently active tables
//void ViaSync::initPhaseDistTable(void) {
//	loadPhaseDistTable(&phaseDistPWM, phaseDistRead);
//}

