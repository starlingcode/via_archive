#include "scanner.hpp"


void ViaScanner::fillWavetableArray(void) {

	wavetableArray[0][0] = &wavetableSet.hyperbolic_shapers;
	wavetableArray[0][1] = &wavetableSet.tanh_res;
	wavetableArray[0][2] = &wavetableSet.newBounce;
	wavetableArray[0][3] = &wavetableSet.exciteBike;
	wavetableArray[0][4] = &wavetableSet.test_fm;
	wavetableArray[0][5] = &wavetableSet.sin_phase_shift;
	wavetableArray[0][6] = &wavetableSet.bitcrush;
	wavetableArray[0][7] = &wavetableSet.new_steps;
	wavetableArray[1][0] = &wavetableSet.circular_257;
	wavetableArray[1][1] = &wavetableSet.bessel;
	wavetableArray[1][2] = &wavetableSet.additive_tri_to_pulse;
	wavetableArray[1][3] = &wavetableSet.sawBend;
	wavetableArray[1][4] = &wavetableSet.moog5Square;
	wavetableArray[1][5] = &wavetableSet.triangle_comb;
	wavetableArray[1][6] = &wavetableSet.bitcrush;
	wavetableArray[1][7] = &wavetableSet.steps5;
}

constexpr Wavetable ScannerWavetableSet::exciteBike;
constexpr Wavetable ScannerWavetableSet::test_fm;
constexpr Wavetable ScannerWavetableSet::hyperbolic_shapers;
constexpr Wavetable ScannerWavetableSet::bitcrush;
constexpr Wavetable ScannerWavetableSet::moog5Square;
constexpr Wavetable ScannerWavetableSet::new_steps;
constexpr Wavetable ScannerWavetableSet::bessel;
constexpr Wavetable ScannerWavetableSet::circular_257;
constexpr Wavetable ScannerWavetableSet::sawBend;
constexpr Wavetable ScannerWavetableSet::steps5;
constexpr Wavetable ScannerWavetableSet::sin_phase_shift;
constexpr Wavetable ScannerWavetableSet::newBounce;
constexpr Wavetable ScannerWavetableSet::tanh_res;
constexpr Wavetable ScannerWavetableSet::triangle_comb;
constexpr Wavetable ScannerWavetableSet::additive_tri_to_pulse;

constexpr uint16_t ScannerWavetableSet::moog5SquareShiftAttackFamily[5][257];

constexpr uint16_t ScannerWavetableSet::moog5SquareShiftReleaseFamily[5][257];

constexpr uint16_t ScannerWavetableSet::sawBendAttackFamily[5][257];

constexpr uint16_t ScannerWavetableSet::sawBendReleaseFamily[5][257];

constexpr uint16_t ScannerWavetableSet::exciteBikeAttackFamily[9][257];

constexpr uint16_t ScannerWavetableSet::exciteBikeReleaseFamily[9][257];

constexpr uint16_t ScannerWavetableSet::steps5AttackFamily[5][257];

constexpr uint16_t ScannerWavetableSet::steps5ReleaseFamily[5][257];

constexpr uint16_t ScannerWavetableSet::additive_tri_to_pulseFamily[5][257];

constexpr uint16_t ScannerWavetableSet::newBounceFamily[5][257];

constexpr uint16_t ScannerWavetableSet::circular_257_slopes[4][257];

constexpr uint16_t ScannerWavetableSet::test_fm_attack[5][257];

constexpr uint16_t ScannerWavetableSet::test_fm_release[5][257];

constexpr uint16_t ScannerWavetableSet::triangle_comb_attack[5][257];

constexpr uint16_t ScannerWavetableSet::triangle_comb_release[5][257];

constexpr uint16_t ScannerWavetableSet::tanh_res_attack[5][257];

constexpr uint16_t ScannerWavetableSet::tanh_res_release[5][257];

constexpr uint16_t ScannerWavetableSet::hyperbolic_shapers_attack[5][257];

constexpr uint16_t ScannerWavetableSet::hyperbolic_shapers_release[5][257];

constexpr uint16_t ScannerWavetableSet::bitcrush_attack[5][257];

constexpr uint16_t ScannerWavetableSet::bitcrush_release[5][257];

constexpr uint16_t ScannerWavetableSet::new_steps_attack[5][257];

constexpr uint16_t ScannerWavetableSet::new_steps_release[5][257];

constexpr uint16_t ScannerWavetableSet::bessel_attack[5][257];

constexpr uint16_t ScannerWavetableSet::bessel_release[5][257];

constexpr uint16_t ScannerWavetableSet::sin_phase_shift_attack[5][257];

constexpr uint16_t ScannerWavetableSet::sin_phase_shift_release[5][257];


// declare functions to set the currently active tables
void ViaScanner::switchWavetableX(const Wavetable * table) {
	wavetableSet.loadWavetableWithDiff15BitSlope(table, (uint32_t *) wavetableXRead);
	scanner.xTableSize = table->numWaveforms - 1;
}

// declare functions to set the currently active tables
void ViaScanner::switchWavetableY(const Wavetable * table) {
	wavetableSet.loadWavetableWithDiff15BitSlope(table, (uint32_t *) wavetableYRead);
	scanner.yTableSize = table->numWaveforms - 1;
}