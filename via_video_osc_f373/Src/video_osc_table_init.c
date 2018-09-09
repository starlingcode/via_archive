#include <video_osc.h>

//void loadPhaseDistTable(PhaseDistTable * table, uint32_t * tableRead);
//void loadWavetableWithDiff(Wavetable * table, uint32_t * tableRead);

void video_osc_fillWavetableArray(void) {
	video_osc_wavetableArray[0] = &tenor257;
	video_osc_wavetableArray[1] = &soprano257;
	video_osc_wavetableArray[2] = &impevens;
	video_osc_wavetableArray[3] = &linwavefold_257;
	video_osc_wavetableArray[4] = &skipSaw;
	video_osc_wavetableArray[5] = &sinwavefold_257;
	video_osc_wavetableArray[6] = &additive_tri_to_pulse;
	video_osc_wavetableArray[7] = &newBounce;
}

// declare functions to set the currently active tables
void video_osc_switchWavetable(Wavetable * table, video_osc_signal_set * signals) {
	loadWavetableWithDiff(table, video_osc_wavetableRead);
	signals->parameters->tableSize = table->numWaveforms - 1;
}

//// declare functions to set the currently active tables
void video_osc_initPhaseDist(void) {
	loadPhaseDistTable(&phaseDistPWM, video_osc_phaseDistRead);
}

