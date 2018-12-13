# include "sync.hpp"


void ViaSync::fillWavetableArray(void) {

	wavetableArray[	0][0] = &ascendingAdditiveClamp;
	wavetableArray[	0][1] = &linwavefold_257;
	wavetableArray[	0][2] = &newBounce;
	wavetableArray[	0][3] = &sharpExpoAsym;
	wavetableArray[	1][0] = &impevens;
	wavetableArray[	1][1] = &perlin;
	wavetableArray[	1][2] = &additive_tri_to_pulse;
	wavetableArray[	1][3] = &csound_formants;
	wavetableArray[	2][0] = &triOdd;
	wavetableArray[	2][1] = &moogSquare;
	wavetableArray[	2][2] = &test_fm;
	wavetableArray[	2][3] = &trains;
	wavetableArray[	3][0] = &sharpExpoAsym;
	wavetableArray[	3][1] = &gamma257;
	wavetableArray[	3][2] = &exciteBike;
	wavetableArray[	3][3] = &steps;
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

