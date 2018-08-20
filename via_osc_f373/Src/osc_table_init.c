#include "osc_tables.h"
#include "signals.h"

//void loadPhaseDistTable(uint32_t ** table, uint32_t ** tableRead);
void loadWavetableWithDiff(Wavetable * table, uint32_t ** tableRead);

void osc_fillWavetableArray(void) {
	wavetableArray[0] = &tenor257;
	wavetableArray[1] = &soprano257;
	wavetableArray[2] = &impevens;
	wavetableArray[3] = &linwavefold_257;
	wavetableArray[4] = &skipSaw;
	wavetableArray[5] = &sinwavefold_257;
	wavetableArray[6] = &additive_tri_to_pulse;
	wavetableArray[7] = &newBounce;
}

// declare functions to set the currently active tables
void osc_switchWavetable(Wavetable * table, viaSignals * signals) {
	loadWavetableWithDiff(table, &wavetableRead);
	signals->parameters->numTables = table->numTables - 1;
}

//// declare functions to set the currently active tables
//void osc_initPhaseDist(void) {
//	loadPhaseDistTable(&phaseDistPWM, &phaseDistRead);
//}

//void loadPhaseDistTable(uint32_t ** table, uint32_t ** tableRead) {
//	for (int i = 0; i < 33; i++) {
//		for (int j = 0; j < 65; j++) {
//			tableRead[i][j] = table[i][j];
//		}
//	}
//}

void loadWavetableWithDiff(Wavetable * table, uint32_t ** tableRead) {

	uint32_t numSamples = table->slopeLength;

	//for each table in the table
	for (int i = 0; i < table->numTables; i++) {
		//include the "last two" samples from release
		wavetableRead[i][0] = *(*(table->releaseSlope + i) + 0) >> 3;
		wavetableRead[i][1] = *(*(table->releaseSlope + i) + 0) >> 3;
		//fill in a full cycle's worth of samples
		//the release gets reversed
		//we drop the last sample from attack and the first from releas
		for (int j = 0;j < numSamples; j++) {
			wavetableRead[i][2 + j] = *(*(table->attackSlope + i) + j) >> 3;
			wavetableRead[i][2 + numSamples + j] = *(*(table->releaseSlope + i) + numSamples - j) >> 3;
		}
		//pad out the "first two" samples from attack
		wavetableRead[i][(numSamples << 1) + 2] = *(*(table->attackSlope + i) + 0) >> 3;
		wavetableRead[i][(numSamples << 1) + 3] = *(*(table->attackSlope + i) + 0) >> 3;
		wavetableRead[i][(numSamples << 1) + 4] = *(*(table->attackSlope + i) + 0) >> 3;
	}


	for (int i = 0; i < table->numTables - 1; i++) {
		for (int j = 0;j < (numSamples*2 + 5); j++) {
			wavetableRead[i][j] |= (wavetableRead[i+1][j] - wavetableRead[i][j]) << 16;
		}
	}

}
