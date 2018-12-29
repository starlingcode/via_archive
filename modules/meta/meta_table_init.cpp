#include "meta.hpp"


void ViaMeta::fillWavetableArray(void) {

	wavetableArray[0][0] = &wavetableSet.impevens;
	wavetableArray[0][1] = &wavetableSet.additive_pairs;
	wavetableArray[0][2] = &wavetableSet.linwavefold_257;
	wavetableArray[0][3] = &wavetableSet.skipSaw;
	wavetableArray[0][4] = &wavetableSet.csound_formants;
	wavetableArray[0][5] = &wavetableSet.perlin;
	wavetableArray[0][6] = &wavetableSet.trains;
	wavetableArray[0][7] = &wavetableSet.vox;
	wavetableArray[1][0] = &wavetableSet.gammaAsym;
	wavetableArray[1][1] = &wavetableSet.sharpLinSym;
	wavetableArray[1][2] = &wavetableSet.circular_257;
	wavetableArray[1][3] = &wavetableSet.quintic_outinAsym;
	wavetableArray[1][4] = &wavetableSet.doubleLump3rdDegLinAtk;
	wavetableArray[1][5] = &wavetableSet.lump2ndDegLinAtk;
	wavetableArray[1][6] = &wavetableSet.testRMS2;
	wavetableArray[1][7] = &wavetableSet.testRMS;
	wavetableArray[2][0] = &wavetableSet.skipSaw;
	wavetableArray[2][1] = &wavetableSet.euclidean_test;
	wavetableArray[2][2] = &wavetableSet.bounce;
	wavetableArray[2][3] = &wavetableSet.bounce_257;
	wavetableArray[2][4] = &wavetableSet.sawBend;
	wavetableArray[2][5] = &wavetableSet.exciteBike;
	wavetableArray[2][6] = &wavetableSet.newest_steps;
	wavetableArray[2][7] = &wavetableSet.block_test;
}

constexpr Wavetable MetaWavetableSet::bounce;
constexpr Wavetable MetaWavetableSet::csound_formants;
constexpr Wavetable MetaWavetableSet::sawBend;
constexpr Wavetable MetaWavetableSet::doubleLump3rdDegLinAtk;
constexpr Wavetable MetaWavetableSet::sharpLinSym;
constexpr Wavetable MetaWavetableSet::lump2ndDegLinAtk;
constexpr Wavetable MetaWavetableSet::quintic_outinAsym;
constexpr Wavetable MetaWavetableSet::circular_257;
constexpr Wavetable MetaWavetableSet::drum;
constexpr Wavetable MetaWavetableSet::bounce_257;
constexpr Wavetable MetaWavetableSet::euclidean_test;
constexpr Wavetable MetaWavetableSet::exciteBike;
constexpr Wavetable MetaWavetableSet::testRMS;
constexpr Wavetable MetaWavetableSet::skipSaw;
constexpr Wavetable MetaWavetableSet::linwavefold_257;
constexpr Wavetable MetaWavetableSet::newest_steps;
constexpr Wavetable MetaWavetableSet::trains;
constexpr Wavetable MetaWavetableSet::vox;
constexpr Wavetable MetaWavetableSet::block_test;
constexpr Wavetable MetaWavetableSet::impevens;
constexpr Wavetable MetaWavetableSet::gammaAsym;
constexpr Wavetable MetaWavetableSet::testRMS2;
constexpr Wavetable MetaWavetableSet::perlin;
constexpr Wavetable MetaWavetableSet::additive_pairs;

constexpr uint16_t MetaWavetableSet::perlinAttackFamily[9][257];

constexpr uint16_t MetaWavetableSet::perlinReleaseFamily[9][257];

constexpr uint16_t MetaWavetableSet::bounceAttackFamily[9][257];

constexpr uint16_t MetaWavetableSet::bounceReleaseFamily[9][257];

constexpr uint16_t MetaWavetableSet::sawBendAttackFamily[5][257];

constexpr uint16_t MetaWavetableSet::sawBendReleaseFamily[5][257];

constexpr uint16_t MetaWavetableSet::exciteBikeAttackFamily[9][257];

constexpr uint16_t MetaWavetableSet::exciteBikeReleaseFamily[9][257];

constexpr uint16_t MetaWavetableSet::gammaAsymAttackFamily[9][257];

constexpr uint16_t MetaWavetableSet::gammaAsymReleaseFamily[9][257];

constexpr uint16_t MetaWavetableSet::sharpLinSymAttackFamily[9][257];

constexpr uint16_t MetaWavetableSet::sharpLinSymReleaseFamily[9][257];

constexpr uint16_t MetaWavetableSet::impshort[9][257];

constexpr uint16_t MetaWavetableSet::skipsaw[5][257];

constexpr uint16_t MetaWavetableSet::allLinear129_5[5][257];

constexpr uint16_t MetaWavetableSet::lump2ndDeg[5][257];

constexpr uint16_t MetaWavetableSet::lump3rdDeg[5][257];

constexpr uint16_t MetaWavetableSet::linwavefold_257_Family[5][257];

constexpr uint16_t MetaWavetableSet::testRMS_release[5][257];

constexpr uint16_t MetaWavetableSet::bounce_257_slopes[5][257];

constexpr uint16_t MetaWavetableSet::circular_257_slopes[4][257];

constexpr uint16_t MetaWavetableSet::quintic_outin2quintic_inout257_slopes[9][257];

constexpr uint16_t MetaWavetableSet::quintic_inout2quintic_outin257_slopes[9][257];

constexpr uint16_t MetaWavetableSet::trains_attack[9][257];

constexpr uint16_t MetaWavetableSet::trains_release[9][257];

constexpr uint16_t MetaWavetableSet::vox_attack[9][257];

constexpr uint16_t MetaWavetableSet::vox_release[9][257];

constexpr uint16_t MetaWavetableSet::csound_formants_attack[9][257];

constexpr uint16_t MetaWavetableSet::csound_formants_release[9][257];

constexpr uint16_t MetaWavetableSet::additive_pairs_slopes[9][257];

constexpr uint16_t MetaWavetableSet::testRMS2_release[5][257];

constexpr uint16_t MetaWavetableSet::euclidean_test_slopes[6][257];

constexpr uint16_t MetaWavetableSet::block_test_attack[9][257];

constexpr uint16_t MetaWavetableSet::block_test_release[9][257];

constexpr uint16_t MetaWavetableSet::newest_steps_attack[9][257];

constexpr uint16_t MetaWavetableSet::newest_steps_release[9][257];

constexpr uint16_t MetaWavetableSet::allLinear[1][257];

constexpr uint16_t MetaWavetableSet::allExpo[1][257];


// declare functions to set the currently active tables
void ViaMeta::switchWavetable(const Wavetable * table) {
	wavetableSet.loadWavetableWithDiff15Bit(table, (uint32_t *) wavetableRead);
	metaWavetable.tableSize = table->numWaveforms - 1;
}

// declare functions to set the currently active tables
void ViaMeta::initDrum(void) {
	wavetableSet.loadSingleTable15Bit(&wavetableSet.drum, (uint32_t *) wavetableReadDrum);
	for (int32_t i = 0; i < 4; i++) {
		drumFullScale[i] = 32767;
	}
}