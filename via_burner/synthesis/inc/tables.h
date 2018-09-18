/*
 * tables.h
 *
 *  Created on: Aug 18, 2018
 *      Author: willmitchell
 */

#ifndef INC_TABLES_H_
#define INC_TABLES_H_

#include "sample_data.h"

/*
 *
 * Assign tables of slopes
 *
 */

static const uint16_t *allLinear[5] = {allLinear_Samples, allLinear_Samples, allLinear_Samples,
		allLinear_Samples, allLinear_Samples};

static const uint16_t *allExpo[5] = {sharpExpo, sharpExpo, sharpExpo,
		sharpExpo, sharpExpo};

static const uint16_t *skipsaw[5] = { skipsaw0, skipsaw1, skipsaw2, skipsaw3,
		skipsaw4 };

static const uint16_t *tenor257Atk[5] = { tenor257Atk0, tenor257Atk1,
		tenor257Atk2, tenor257Atk3, tenor257Atk4 };

static const uint16_t *bounce_257_slopes[5] = { bounce_257_slopes0,
		bounce_257_slopes1, bounce_257_slopes2, bounce_257_slopes3,
		bounce_257_slopes4 };

static const uint16_t *newBounceFamily[5] = { newBounceFamily0,
		newBounceFamily1, newBounceFamily2, newBounceFamily3, newBounceFamily4 };

static const uint16_t *additive_tri_to_pulseFamily[5] = {
		additive_tri_to_pulseFamily0, additive_tri_to_pulseFamily1,
		additive_tri_to_pulseFamily2, additive_tri_to_pulseFamily3,
		additive_tri_to_pulseFamily4 };

static const uint16_t *gamma257Attack[9] = { gamma257Attack0, gamma257Attack1,
		gamma257Attack2, gamma257Attack3, gamma257Attack4, gamma257Attack5,
		gamma257Attack6, gamma257Attack7, gamma257Attack8 };

static const uint16_t *algerianReleaseFamily[5] = { algerianReleaseFamily0,
		algerianReleaseFamily1, algerianReleaseFamily2, algerianReleaseFamily3,
		algerianReleaseFamily4 };

static const uint16_t *trioddReleaseFamily[9] = { trioddReleaseFamily0,
		trioddReleaseFamily1, trioddReleaseFamily2, trioddReleaseFamily3,
		trioddReleaseFamily4, trioddReleaseFamily5, trioddReleaseFamily6,
		trioddReleaseFamily7, trioddReleaseFamily8 };

static const uint16_t *quintic_out2quintic_in257_slopes[9] = {
		quintic_out2quintic_in257_slopes0, quintic_out2quintic_in257_slopes1,
		quintic_out2quintic_in257_slopes2, quintic_out2quintic_in257_slopes3,
		quintic_out2quintic_in257_slopes4, quintic_out2quintic_in257_slopes5,
		quintic_out2quintic_in257_slopes6, quintic_out2quintic_in257_slopes7,
		quintic_out2quintic_in257_slopes8 };

static const uint16_t *circular_257_slopes[5] = { circular_257_slopes0,
		circular_257_slopes1, circular_257_slopes2, circular_257_slopes3,
		circular_257_slopes4 };

static const uint16_t *quintic_outin2quintic_inout257_slopes[9] = {
		quintic_outin2quintic_inout257_slopes0,
		quintic_outin2quintic_inout257_slopes1,
		quintic_outin2quintic_inout257_slopes2,
		quintic_outin2quintic_inout257_slopes3,
		quintic_outin2quintic_inout257_slopes4,
		quintic_outin2quintic_inout257_slopes5,
		quintic_outin2quintic_inout257_slopes6,
		quintic_outin2quintic_inout257_slopes7,
		quintic_outin2quintic_inout257_slopes8 };

static const uint16_t *algerianAttackFamily[5] = { algerianAttackFamily0,
		algerianAttackFamily1, algerianAttackFamily2, algerianAttackFamily3,
		algerianAttackFamily4 };

static const uint16_t *impshort[9] = { impshort0, impshort1, impshort2,
		impshort3, impshort4, impshort5, impshort6, impshort7, impshort8 };

static const uint16_t *impshort_5[9] = { impshort0, impshort1, impshort2,
		impshort3, impshort4};

static const uint16_t *moogSquareShiftReleaseFamily[9] = {
		moogSquareShiftReleaseFamily0, moogSquareShiftReleaseFamily1,
		moogSquareShiftReleaseFamily2, moogSquareShiftReleaseFamily3,
		moogSquareShiftReleaseFamily4, moogSquareShiftReleaseFamily5,
		moogSquareShiftReleaseFamily6, moogSquareShiftReleaseFamily7,
		moogSquareShiftReleaseFamily8 };

static const uint16_t *moogSquareShiftAttackFamily[9] = {
		moogSquareShiftAttackFamily0, moogSquareShiftAttackFamily1,
		moogSquareShiftAttackFamily2, moogSquareShiftAttackFamily3,
		moogSquareShiftAttackFamily4, moogSquareShiftAttackFamily5,
		moogSquareShiftAttackFamily6, moogSquareShiftAttackFamily7,
		moogSquareShiftAttackFamily8 };

static const uint16_t *quintic_in2quintic_out257_slopes[9] = {
		quintic_in2quintic_out257_slopes0, quintic_in2quintic_out257_slopes1,
		quintic_in2quintic_out257_slopes2, quintic_in2quintic_out257_slopes3,
		quintic_in2quintic_out257_slopes4, quintic_in2quintic_out257_slopes5,
		quintic_in2quintic_out257_slopes6, quintic_in2quintic_out257_slopes7,
		quintic_in2quintic_out257_slopes8 };

static const uint16_t *testRMSRMSRls[5] = { testRMSRMSRls0, testRMSRMSRls1,
		testRMSRMSRls2, testRMSRMSRls3, testRMSRMSRls4 };

static const uint16_t *sawBendReleaseFamily[5] = { sawBendReleaseFamily0,
		sawBendReleaseFamily1, sawBendReleaseFamily2, sawBendReleaseFamily3,
		sawBendReleaseFamily4 };

static const uint16_t *sawBendAttackFamily[5] = { sawBendAttackFamily0,
		sawBendAttackFamily1, sawBendAttackFamily2, sawBendAttackFamily3,
		sawBendAttackFamily4 };

static const uint16_t *soprano257Rls[5] = { soprano257Rls0, soprano257Rls1,
		soprano257Rls2, soprano257Rls3, soprano257Rls4 };

static const uint16_t *linwavefold_257_Family[5] = { linwavefold_257_Family0,
		linwavefold_257_Family1, linwavefold_257_Family2,
		linwavefold_257_Family3, linwavefold_257_Family4 };

static const uint16_t *exciteBikeReleaseFamily[9] = { exciteBikeReleaseFamily0,
		exciteBikeReleaseFamily1, exciteBikeReleaseFamily2,
		exciteBikeReleaseFamily3, exciteBikeReleaseFamily4,
		exciteBikeReleaseFamily5, exciteBikeReleaseFamily6,
		exciteBikeReleaseFamily7, exciteBikeReleaseFamily8 };

static const uint16_t *testRMSRMSAtk[5] = { testRMSRMSAtk0, testRMSRMSAtk1,
		testRMSRMSAtk2, testRMSRMSAtk3, testRMSRMSAtk4 };

static const uint16_t *trioddAttackFamily[9] = { trioddAttackFamily0,
		trioddAttackFamily1, trioddAttackFamily2, trioddAttackFamily3,
		trioddAttackFamily4, trioddAttackFamily5, trioddAttackFamily6,
		trioddAttackFamily7, trioddAttackFamily8 };

static const uint16_t *sinwavefold_257_Family[9] = { sinwavefold_257_Family0,
		sinwavefold_257_Family1, sinwavefold_257_Family2,
		sinwavefold_257_Family3, sinwavefold_257_Family4,
		sinwavefold_257_Family5, sinwavefold_257_Family6,
		sinwavefold_257_Family7, sinwavefold_257_Family8 };

static const uint16_t *exciteBikeAttackFamily[9] = { exciteBikeAttackFamily0,
		exciteBikeAttackFamily1, exciteBikeAttackFamily2,
		exciteBikeAttackFamily3, exciteBikeAttackFamily4,
		exciteBikeAttackFamily5, exciteBikeAttackFamily6,
		exciteBikeAttackFamily7, exciteBikeAttackFamily8 };

static const uint16_t *soprano257Atk[5] = { soprano257Atk0, soprano257Atk1,
		soprano257Atk2, soprano257Atk3, soprano257Atk4 };

static const uint16_t *tenor257Rls[5] = { tenor257Rls0, tenor257Rls1,
		tenor257Rls2, tenor257Rls3, tenor257Rls4 };

static const uint16_t *quintic_inout2quintic_outin257_slopes[9] = {
		quintic_inout2quintic_outin257_slopes0,
		quintic_inout2quintic_outin257_slopes1,
		quintic_inout2quintic_outin257_slopes2,
		quintic_inout2quintic_outin257_slopes3,
		quintic_inout2quintic_outin257_slopes4,
		quintic_inout2quintic_outin257_slopes5,
		quintic_inout2quintic_outin257_slopes6,
		quintic_inout2quintic_outin257_slopes7,
		quintic_inout2quintic_outin257_slopes8 };

/*
 *
 * Link pairs of slope tables into families
 *
 */

//
typedef struct {
	const uint16_t **attackSlope;
	const uint16_t **releaseSlope;
	uint32_t slopeLength;
	uint32_t numWaveforms;
} Wavetable;

// helper function to load the above array

void loadTable(Wavetable * family);

static const Wavetable moogSquare = {
		.attackSlope = moogSquareShiftAttackFamily, .releaseSlope =
				moogSquareShiftReleaseFamily, .slopeLength = 256,
		.numWaveforms = 9 };

static const Wavetable triOdd = { .attackSlope = trioddAttackFamily,
		.releaseSlope = trioddReleaseFamily, .slopeLength = 256, .numWaveforms =
				9 };

static const Wavetable sawBend = { .attackSlope = sawBendAttackFamily,
		.releaseSlope = sawBendReleaseFamily, .slopeLength = 256,
		.numWaveforms = 5 };

static const Wavetable exciteBike = { .attackSlope = exciteBikeAttackFamily,
		.releaseSlope = exciteBikeReleaseFamily, .slopeLength = 256,
		.numWaveforms = 9 };

static const Wavetable algerian = { .attackSlope = algerianAttackFamily,
		.releaseSlope = algerianReleaseFamily, .slopeLength = 256,
		.numWaveforms = 5 };

static const Wavetable impevens = { .attackSlope = impshort, .releaseSlope =
		impshort, .slopeLength = 256, .numWaveforms = 9 };

static const Wavetable imp_5 = { .attackSlope = impshort_5, .releaseSlope =
		impshort, .slopeLength = 256, .numWaveforms = 5 };

static const Wavetable skipSaw = { .attackSlope = skipsaw, .releaseSlope =
		skipsaw, .slopeLength = 256, .numWaveforms = 5 };

static const Wavetable tenor257 = { .attackSlope = tenor257Atk, .releaseSlope =
		tenor257Rls, .slopeLength = 256, .numWaveforms = 5 };

static const Wavetable linwavefold_257 = {
		.attackSlope = linwavefold_257_Family, .releaseSlope =
				linwavefold_257_Family, .slopeLength = 256, .numWaveforms = 5 };

static const Wavetable sinwavefold_257 = {
		.attackSlope = sinwavefold_257_Family, .releaseSlope =
				sinwavefold_257_Family, .slopeLength = 256, .numWaveforms = 9 };

static const Wavetable additive_tri_to_pulse = { .attackSlope =
		additive_tri_to_pulseFamily,
		.releaseSlope = additive_tri_to_pulseFamily, .slopeLength = 256,
		.numWaveforms = 5 };

static const Wavetable newBounce = { .attackSlope = newBounceFamily,
		.releaseSlope = newBounceFamily, .slopeLength = 256, .numWaveforms = 5 };

static const Wavetable soprano257 = { .attackSlope = soprano257Atk,
		.releaseSlope = soprano257Rls, .slopeLength = 256, .numWaveforms = 5 };

static const Wavetable testRMS = { .attackSlope = testRMSRMSAtk, .releaseSlope =
		testRMSRMSRls, .slopeLength = 256, .numWaveforms = 5 };

static const Wavetable gamma257 = { .attackSlope = gamma257Attack,
		.releaseSlope = gamma257Attack, .slopeLength = 256, .numWaveforms = 9 };

static const Wavetable bounce_257 =
		{ .attackSlope = bounce_257_slopes, .releaseSlope = bounce_257_slopes,
				.slopeLength = 256, .numWaveforms = 5 };

static const Wavetable circular_257 = { .attackSlope = circular_257_slopes,
		.releaseSlope = circular_257_slopes, .slopeLength = 256, .numWaveforms =
				5 };

static const Wavetable quintic_outin2quintic_inout257 = { .attackSlope =
		quintic_outin2quintic_inout257_slopes, .releaseSlope =
		quintic_outin2quintic_inout257_slopes, .slopeLength = 256,
		.numWaveforms = 9 };

static const Wavetable quintic_out2quintic_in257 =
		{ .attackSlope = quintic_out2quintic_in257_slopes, .releaseSlope =
				quintic_out2quintic_in257_slopes, .slopeLength = 256,
				.numWaveforms = 9 };

static const Wavetable quintic_inout2quintic_outin257 = { .attackSlope =
		quintic_inout2quintic_outin257_slopes, .releaseSlope =
		quintic_inout2quintic_outin257_slopes, .slopeLength = 256,
		.numWaveforms = 9 };

static const Wavetable quintic_in2quintic_out257 =
		{ .attackSlope = quintic_in2quintic_out257_slopes, .releaseSlope =
				quintic_in2quintic_out257_slopes, .slopeLength = 256,
				.numWaveforms = 9 };

static const Wavetable drum =
		{ .attackSlope = allLinear, .releaseSlope =
				allExpo, .slopeLength = 256,
				.numWaveforms = 5 };

// load each sample from flash to ram with bitshift by 3 and store in bottom halfword
// store difference between sample and corresponding sample in adjacent waveform in top halfword

static inline void loadWavetableWithDiff(Wavetable * table,
		uint32_t * tableRead) {

	uint32_t numSamples = table->slopeLength;

	//for each table in the table
	for (int i = 0; i < table->numWaveforms; i++) {
		//include the "last two" samples from release
		*((tableRead + 517 * i) + 0) = *(*(table->releaseSlope + i) + 0) >> 3;
		*((tableRead + 517 * i) + 1) = *(*(table->releaseSlope + i) + 0) >> 3;
		//fill in a full cycle's worth of samples
		//the release gets reversed
		//we drop the last sample from attack and the first from releas
		for (int j = 0; j < numSamples; j++) {
			*((tableRead + 517 * i) + 2 + j) = *(*(table->attackSlope + i) + j)
					>> 3;
			*((tableRead + 517 * i) + 2 + numSamples + j) =
					*(*(table->releaseSlope + i) + numSamples - j) >> 3;
		}
		//pad out the "first two" samples from attack
		*((tableRead + 517 * i) + (numSamples << 1) + 2) =
				*(*(table->attackSlope + i) + 0) >> 3;
		*((tableRead + 517 * i) + (numSamples << 1) + 3) =
				*(*(table->attackSlope + i) + 0) >> 3;
		*((tableRead + 517 * i) + (numSamples << 1) + 4) =
				*(*(table->attackSlope + i) + 0) >> 3;
	}

	for (int i = 0; i < table->numWaveforms - 1; i++) {
		for (int j = 0; j < (numSamples * 2 + 5); j++) {
			*((tableRead + 517 * i) + j) |= (*((tableRead + 517 * (i + 1)) + j)
					- *((tableRead + 517 * i) + j)) << 16;
		}
	}

}

static inline void loadWavetableWithDiff15Bit(Wavetable * table,
		uint32_t * tableRead) {

	uint32_t numSamples = table->slopeLength;

	//for each table in the table
	for (int i = 0; i < table->numWaveforms; i++) {
		//pad with duplicate samples
		*((tableRead + 517 * i) + 0) = *(*(table->releaseSlope + i) + 0);
		*((tableRead + 517 * i) + 1) = *(*(table->releaseSlope + i) + 0);
		//fill in a full cycle's worth of samples
		//the release gets reversed
		//we drop the last sample from attack and the first from releas
		for (int j = 0; j < numSamples; j++) {
			*((tableRead + 517 * i) + 2 + j) = *(*(table->attackSlope + i) + j);
			*((tableRead + 517 * i) + 2 + numSamples + j) =
					*(*(table->releaseSlope + i) + numSamples - j);
		}
		//pad with duplicate samples
		*((tableRead + 517 * i) + (numSamples << 1) + 2) =
				*(*(table->attackSlope + i) + 0);
		*((tableRead + 517 * i) + (numSamples << 1) + 3) =
				*(*(table->attackSlope + i) + 0);
		*((tableRead + 517 * i) + (numSamples << 1) + 4) =
				*(*(table->attackSlope + i) + 0);
	}

	for (int i = 0; i < table->numWaveforms - 1; i++) {
		for (int j = 0; j < (numSamples * 2 + 5); j++) {
			*((tableRead + 517 * i) + j) |= (*((tableRead + 517 * (i + 1)) + j)
					- *((tableRead + 517 * i) + j)) << 16;
		}
	}

}

static inline void loadSingleTable15Bit(Wavetable * table,
		uint32_t * tableRead) {

	uint32_t numSamples = table->slopeLength;

	//for each table in the table
	for (int i = 0; i < 1; i++) {
		//pad with duplicate samples
		*((tableRead + 517 * i) + 0) = *(*(table->releaseSlope + i) + 0);
		*((tableRead + 517 * i) + 1) = *(*(table->releaseSlope + i) + 0);
		//fill in a full cycle's worth of samples
		//the release gets reversed
		//we drop the last sample from attack and the first from releas
		for (int j = 0; j < numSamples; j++) {
			*((tableRead + 517 * i) + 2 + j) = *(*(table->attackSlope + i) + j);
			*((tableRead + 517 * i) + 2 + numSamples + j) =
					*(*(table->releaseSlope + i) + numSamples - j);
		}
		//pad with duplicate samples
		*((tableRead + 517 * i) + (numSamples << 1) + 2) =
				*(*(table->attackSlope + i) + 0);
		*((tableRead + 517 * i) + (numSamples << 1) + 3) =
				*(*(table->attackSlope + i) + 0);
		*((tableRead + 517 * i) + (numSamples << 1) + 4) =
				*(*(table->attackSlope + i) + 0);
	}

}

/*
 *
 * Link phase distortion waveforms into tables
 * Currently, phase distortion table size is fixed at 33 and waveform sample length 65
 *
 */

static const uint32_t * phaseDistPWMTable[33] = { phaseDistPWM_0,
		phaseDistPWM_1, phaseDistPWM_2, phaseDistPWM_3, phaseDistPWM_4,
		phaseDistPWM_5, phaseDistPWM_6, phaseDistPWM_7, phaseDistPWM_8,
		phaseDistPWM_9, phaseDistPWM_10, phaseDistPWM_11, phaseDistPWM_12,
		phaseDistPWM_13, phaseDistPWM_14, phaseDistPWM_15, phaseDistPWM_16,
		phaseDistPWM_17, phaseDistPWM_18, phaseDistPWM_19, phaseDistPWM_20,
		phaseDistPWM_21, phaseDistPWM_22, phaseDistPWM_23, phaseDistPWM_24,
		phaseDistPWM_25, phaseDistPWM_26, phaseDistPWM_27, phaseDistPWM_28,
		phaseDistPWM_29, phaseDistPWM_30, phaseDistPWM_31, phaseDistPWM_32 };

typedef struct {
	const uint32_t **lookupTable;
	uint32_t tableLength;
	uint32_t numWaveforms;
} PhaseDistTable;

static const PhaseDistTable phaseDistPWM = { .lookupTable = phaseDistPWMTable,
		.tableLength = 65, .numWaveforms = 33 };

static inline void loadPhaseDistTable(PhaseDistTable * table,
		uint32_t * tableRead) {
//	memcpy(tableRead, table->lookupTable, 33*65*sizeof(uint32_t));
	for (int i = 0; i < 33; i++) {
		for (int j = 0; j < 65; j++) {
			*((tableRead + i * 65) + j) = *(*(table->lookupTable + i) + j);
		}
	}
}

/*
 *
 * Expo lookup table for 1v/oct
 *
 */

#define expotable10oct {65536 , 65654 , 65773 , 65892 , 66011 , 66130 , 66250 , 66369 , 66489 , 66609 , 66730 , 66850 , 66971 , 67092 , 67213 , 67335 , 67456 , 67578 , 67700 , 67823 , 67945 , 68068 , 68191 , 68314 , 68438 , 68561 , 68685 , 68809 , 68933 , 69058 , 69183 , 69308 , 69433 , 69558 , 69684 , 69810 , 69936 , 70062 , 70189 , 70316 , 70443 , 70570 , 70698 , 70825 , 70953 , 71082 , 71210 , 71339 , 71468 , 71597 , 71726 , 71856 , 71985 , 72115 , 72246 , 72376 , 72507 , 72638 , 72769 , 72901 , 73032 , 73164 , 73297 , 73429 , 73562 , 73695 , 73828 , 73961 , 74095 , 74229 , 74363 , 74497 , 74632 , 74766 , 74902 , 75037 , 75172 , 75308 , 75444 , 75581 , 75717 , 75854 , 75991 , 76128 , 76266 , 76404 , 76542 , 76680 , 76819 , 76957 , 77096 , 77236 , 77375 , 77515 , 77655 , 77795 , 77936 , 78077 , 78218 , 78359 , 78501 , 78642 , 78785 , 78927 , 79069 , 79212 , 79355 , 79499 , 79642 , 79786 , 79930 , 80075 , 80220 , 80365 , 80510 , 80655 , 80801 , 80947 , 81093 , 81240 , 81386 , 81533 , 81681 , 81828 , 81976 , 82124 , 82273 , 82421 , 82570 , 82719 , 82869 , 83019 , 83169 , 83319 , 83469 , 83620 , 83771 , 83923 , 84074 , 84226 , 84378 , 84531 , 84683 , 84836 , 84990 , 85143 , 85297 , 85451 , 85606 , 85760 , 85915 , 86070 , 86226 , 86382 , 86538 , 86694 , 86851 , 87008 , 87165 , 87322 , 87480 , 87638 , 87796 , 87955 , 88114 , 88273 , 88433 , 88592 , 88752 , 88913 , 89073 , 89234 , 89396 , 89557 , 89719 , 89881 , 90043 , 90206 , 90369 , 90532 , 90696 , 90860 , 91024 , 91188 , 91353 , 91518 , 91684 , 91849 , 92015 , 92181 , 92348 , 92515 , 92682 , 92849 , 93017 , 93185 , 93354 , 93522 , 93691 , 93860 , 94030 , 94200 , 94370 , 94541 , 94711 , 94882 , 95054 , 95226 , 95398 , 95570 , 95743 , 95916 , 96089 , 96263 , 96437 , 96611 , 96785 , 96960 , 97135 , 97311 , 97487 , 97663 , 97839 , 98016 , 98193 , 98370 , 98548 , 98726 , 98905 , 99083 , 99262 , 99442 , 99621 , 99801 , 99982 , 100162 , 100343 , 100524 , 100706 , 100888 , 101070 , 101253 , 101436 , 101619 , 101803 , 101987 , 102171 , 102356 , 102540 , 102726 , 102911 , 103097 , 103283 , 103470 , 103657 , 103844 , 104032 , 104220 , 104408 , 104597 , 104786 , 104975 , 105165 , 105355 , 105545 , 105736 , 105927 , 106118 , 106310 , 106502 , 106694 , 106887 , 107080 , 107274 , 107468 , 107662 , 107856 , 108051 , 108246 , 108442 , 108638 , 108834 , 109031 , 109228 , 109425 , 109623 , 109821 , 110019 , 110218 , 110417 , 110617 , 110816 , 111017 , 111217 , 111418 , 111619 , 111821 , 112023 , 112226 , 112428 , 112631 , 112835 , 113039 , 113243 , 113448 , 113653 , 113858 , 114064 , 114270 , 114476 , 114683 , 114890 , 115098 , 115306 , 115514 , 115723 , 115932 , 116141 , 116351 , 116561 , 116772 , 116983 , 117194 , 117406 , 117618 , 117831 , 118043 , 118257 , 118470 , 118684 , 118899 , 119114 , 119329 , 119544 , 119760 , 119977 , 120194 , 120411 , 120628 , 120846 , 121065 , 121283 , 121502 , 121722 , 121942 , 122162 , 122383 , 122604 , 122825 , 123047 , 123270 , 123492 , 123715 , 123939 , 124163 , 124387 , 124612 , 124837 , 125063 , 125289 , 125515 , 125742 , 125969 , 126197 , 126425 , 126653 , 126882 , 127111 , 127341 , 127571 , 127801 , 128032 , 128263 , 128495 , 128727 , 128960 , 129193 , 129426 , 129660 , 129894 , 130129 , 130364 , 130600 , 130836 , 131072 , 131309 , 131546 , 131784 , 132022 , 132260 , 132499 , 132739 , 132978 , 133219 , 133459 , 133701 , 133942 , 134184 , 134427 , 134669 , 134913 , 135156 , 135401 , 135645 , 135890 , 136136 , 136382 , 136628 , 136875 , 137122 , 137370 , 137618 , 137867 , 138116 , 138366 , 138616 , 138866 , 139117 , 139368 , 139620 , 139872 , 140125 , 140378 , 140632 , 140886 , 141140 , 141395 , 141651 , 141907 , 142163 , 142420 , 142677 , 142935 , 143193 , 143452 , 143711 , 143971 , 144231 , 144491 , 144753 , 145014 , 145276 , 145539 , 145801 , 146065 , 146329 , 146593 , 146858 , 147123 , 147389 , 147655 , 147922 , 148189 , 148457 , 148725 , 148994 , 149263 , 149533 , 149803 , 150074 , 150345 , 150617 , 150889 , 151161 , 151434 , 151708 , 151982 , 152257 , 152532 , 152807 , 153083 , 153360 , 153637 , 153915 , 154193 , 154471 , 154750 , 155030 , 155310 , 155591 , 155872 , 156153 , 156436 , 156718 , 157001 , 157285 , 157569 , 157854 , 158139 , 158425 , 158711 , 158998 , 159285 , 159573 , 159861 , 160150 , 160439 , 160729 , 161019 , 161310 , 161602 , 161894 , 162186 , 162479 , 162773 , 163067 , 163361 , 163657 , 163952 , 164249 , 164545 , 164843 , 165140 , 165439 , 165738 , 166037 , 166337 , 166638 , 166939 , 167240 , 167542 , 167845 , 168148 , 168452 , 168756 , 169061 , 169367 , 169673 , 169979 , 170286 , 170594 , 170902 , 171211 , 171520 , 171830 , 172141 , 172452 , 172763 , 173075 , 173388 , 173701 , 174015 , 174330 , 174645 , 174960 , 175276 , 175593 , 175910 , 176228 , 176546 , 176865 , 177185 , 177505 , 177826 , 178147 , 178469 , 178791 , 179114 , 179438 , 179762 , 180087 , 180412 , 180738 , 181065 , 181392 , 181720 , 182048 , 182377 , 182706 , 183036 , 183367 , 183698 , 184030 , 184363 , 184696 , 185030 , 185364 , 185699 , 186034 , 186370 , 186707 , 187044 , 187382 , 187721 , 188060 , 188400 , 188740 , 189081 , 189423 , 189765 , 190108 , 190451 , 190795 , 191140 , 191485 , 191831 , 192178 , 192525 , 192873 , 193221 , 193571 , 193920 , 194271 , 194622 , 194973 , 195326 , 195678 , 196032 , 196386 , 196741 , 197096 , 197452 , 197809 , 198167 , 198525 , 198883 , 199243 , 199603 , 199963 , 200324 , 200686 , 201049 , 201412 , 201776 , 202141 , 202506 , 202872 , 203238 , 203605 , 203973 , 204342 , 204711 , 205081 , 205451 , 205823 , 206194 , 206567 , 206940 , 207314 , 207689 , 208064 , 208440 , 208816 , 209194 , 209572 , 209950 , 210329 , 210710 , 211090 , 211472 , 211854 , 212236 , 212620 , 213004 , 213389 , 213774 , 214161 , 214547 , 214935 , 215323 , 215712 , 216102 , 216493 , 216884 , 217276 , 217668 , 218061 , 218455 , 218850 , 219245 , 219642 , 220038 , 220436 , 220834 , 221233 , 221633 , 222033 , 222434 , 222836 , 223239 , 223642 , 224046 , 224451 , 224857 , 225263 , 225670 , 226078 , 226486 , 226895 , 227305 , 227716 , 228127 , 228539 , 228952 , 229366 , 229780 , 230195 , 230611 , 231028 , 231445 , 231864 , 232282 , 232702 , 233123 , 233544 , 233966 , 234388 , 234812 , 235236 , 235661 , 236087 , 236513 , 236941 , 237369 , 237798 , 238227 , 238658 , 239089 , 239521 , 239954 , 240387 , 240821 , 241257 , 241692 , 242129 , 242567 , 243005 , 243444 , 243884 , 244324 , 244766 , 245208 , 245651 , 246095 , 246539 , 246985 , 247431 , 247878 , 248326 , 248775 , 249224 , 249674 , 250125 , 250577 , 251030 , 251483 , 251938 , 252393 , 252849 , 253306 , 253763 , 254222 , 254681 , 255141 , 255602 , 256064 , 256527 , 256990 , 257455 , 257920 , 258386 , 258853 , 259320 , 259789 , 260258 , 260728 , 261199 , 261671 , 262144 , 262618 , 263092 , 263567 , 264044 , 264521 , 264999 , 265477 , 265957 , 266437 , 266919 , 267401 , 267884 , 268368 , 268853 , 269339 , 269825 , 270313 , 270801 , 271291 , 271781 , 272272 , 272764 , 273256 , 273750 , 274245 , 274740 , 275237 , 275734 , 276232 , 276731 , 277231 , 277732 , 278234 , 278736 , 279240 , 279744 , 280250 , 280756 , 281263 , 281772 , 282281 , 282791 , 283302 , 283813 , 284326 , 284840 , 285355 , 285870 , 286387 , 286904 , 287422 , 287942 , 288462 , 288983 , 289505 , 290028 , 290552 , 291077 , 291603 , 292130 , 292658 , 293186 , 293716 , 294247 , 294778 , 295311 , 295844 , 296379 , 296914 , 297451 , 297988 , 298527 , 299066 , 299606 , 300148 , 300690 , 301233 , 301777 , 302323 , 302869 , 303416 , 303964 , 304513 , 305064 , 305615 , 306167 , 306720 , 307274 , 307829 , 308385 , 308943 , 309501 , 310060 , 310620 , 311181 , 311744 , 312307 , 312871 , 313436 , 314003 , 314570 , 315138 , 315708 , 316278 , 316849 , 317422 , 317995 , 318570 , 319145 , 319722 , 320300 , 320878 , 321458 , 322039 , 322621 , 323204 , 323787 , 324372 , 324958 , 325546 , 326134 , 326723 , 327313 , 327905 , 328497 , 329091 , 329685 , 330281 , 330877 , 331475 , 332074 , 332674 , 333275 , 333877 , 334480 , 335085 , 335690 , 336297 , 336904 , 337513 , 338123 , 338734 , 339346 , 339959 , 340573 , 341188 , 341805 , 342422 , 343041 , 343661 , 344282 , 344904 , 345527 , 346151 , 346776 , 347403 , 348031 , 348659 , 349289 , 349920 , 350552 , 351186 , 351820 , 352456 , 353093 , 353731 , 354370 , 355010 , 355651 , 356294 , 356938 , 357583 , 358229 , 358876 , 359524 , 360174 , 360824 , 361476 , 362129 , 362784 , 363439 , 364096 , 364754 , 365413 , 366073 , 366734 , 367397 , 368060 , 368725 , 369392 , 370059 , 370728 , 371397 , 372068 , 372741 , 373414 , 374089 , 374765 , 375442 , 376120 , 376800 , 377480 , 378162 , 378845 , 379530 , 380216 , 380903 , 381591 , 382280 , 382971 , 383663 , 384356 , 385050 , 385746 , 386443 , 387141 , 387841 , 388541 , 389243 , 389947 , 390651 , 391357 , 392064 , 392772 , 393482 , 394193 , 394905 , 395618 , 396333 , 397049 , 397767 , 398485 , 399205 , 399926 , 400649 , 401373 , 402098 , 402824 , 403552 , 404281 , 405012 , 405743 , 406477 , 407211 , 407947 , 408684 , 409422 , 410162 , 410903 , 411645 , 412389 , 413134 , 413880 , 414628 , 415377 , 416128 , 416879 , 417633 , 418387 , 419143 , 419900 , 420659 , 421419 , 422180 , 422943 , 423707 , 424473 , 425240 , 426008 , 426778 , 427549 , 428321 , 429095 , 429870 , 430647 , 431425 , 432204 , 432985 , 433768 , 434551 , 435336 , 436123 , 436911 , 437700 , 438491 , 439283 , 440077 , 440872 , 441668 , 442466 , 443266 , 444067 , 444869 , 445673 , 446478 , 447285 , 448093 , 448902 , 449713 , 450526 , 451340 , 452155 , 452972 , 453790 , 454610 , 455432 , 456255 , 457079 , 457905 , 458732 , 459561 , 460391 , 461223 , 462056 , 462891 , 463727 , 464565 , 465404 , 466245 , 467087 , 467931 , 468777 , 469624 , 470472 , 471322 , 472174 , 473027 , 473881 , 474738 , 475595 , 476455 , 477315 , 478178 , 479042 , 479907 , 480774 , 481643 , 482513 , 483385 , 484258 , 485133 , 486010 , 486888 , 487767 , 488649 , 489531 , 490416 , 491302 , 492189 , 493079 , 493970 , 494862 , 495756 , 496652 , 497549 , 498448 , 499349 , 500251 , 501154 , 502060 , 502967 , 503876 , 504786 , 505698 , 506612 , 507527 , 508444 , 509363 , 510283 , 511205 , 512128 , 513054 , 513981 , 514909 , 515839 , 516771 , 517705 , 518640 , 519577 , 520516 , 521457 , 522399 , 523342 , 524288 , 525235 , 526184 , 527135 , 528087 , 529041 , 529997 , 530955 , 531914 , 532875 , 533838 , 534802 , 535768 , 536736 , 537706 , 538678 , 539651 , 540626 , 541603 , 542581 , 543561 , 544543 , 545527 , 546513 , 547500 , 548489 , 549480 , 550473 , 551468 , 552464 , 553462 , 554462 , 555464 , 556467 , 557473 , 558480 , 559489 , 560500 , 561512 , 562527 , 563543 , 564561 , 565581 , 566603 , 567627 , 568652 , 569680 , 570709 , 571740 , 572773 , 573808 , 574845 , 575883 , 576924 , 577966 , 579010 , 580056 , 581104 , 582154 , 583206 , 584260 , 585315 , 586373 , 587432 , 588493 , 589557 , 590622 , 591689 , 592758 , 593829 , 594902 , 595976 , 597053 , 598132 , 599213 , 600295 , 601380 , 602466 , 603555 , 604645 , 605738 , 606832 , 607928 , 609027 , 610127 , 611229 , 612334 , 613440 , 614548 , 615659 , 616771 , 617885 , 619001 , 620120 , 621240 , 622363 , 623487 , 624614 , 625742 , 626873 , 628005 , 629140 , 630276 , 631415 , 632556 , 633699 , 634844 , 635991 , 637140 , 638291 , 639444 , 640599 , 641757 , 642916 , 644078 , 645241 , 646407 , 647575 , 648745 , 649917 , 651091 , 652268 , 653446 , 654627 , 655809 , 656994 , 658181 , 659370 , 660561 , 661755 , 662951 , 664148 , 665348 , 666550 , 667755 , 668961 , 670170 , 671380 , 672593 , 673809 , 675026 , 676246 , 677467 , 678691 , 679917 , 681146 , 682376 , 683609 , 684844 , 686082 , 687321 , 688563 , 689807 , 691053 , 692302 , 693553 , 694806 , 696061 , 697319 , 698578 , 699841 , 701105 , 702372 , 703641 , 704912 , 706185 , 707461 , 708739 , 710020 , 711303 , 712588 , 713875 , 715165 , 716457 , 717752 , 719048 , 720347 , 721649 , 722953 , 724259 , 725567 , 726878 , 728191 , 729507 , 730825 , 732145 , 733468 , 734793 , 736121 , 737451 , 738783 , 740118 , 741455 , 742795 , 744137 , 745481 , 746828 , 748177 , 749529 , 750883 , 752240 , 753599 , 754961 , 756324 , 757691 , 759060 , 760431 , 761805 , 763182 , 764560 , 765942 , 767326 , 768712 , 770101 , 771492 , 772886 , 774282 , 775681 , 777083 , 778487 , 779893 , 781302 , 782714 , 784128 , 785544 , 786964 , 788386 , 789810 , 791237 , 792666 , 794098 , 795533 , 796971 , 798410 , 799853 , 801298 , 802746 , 804196 , 805649 , 807104 , 808563 , 810024 , 811487 , 812953 , 814422 , 815893 , 817367 , 818844 , 820323 , 821806 , 823290 , 824778 , 826268 , 827761 , 829256 , 830754 , 832255 , 833759 , 835265 , 836774 , 838286 , 839801 , 841318 , 842838 , 844361 , 845886 , 847415 , 848946 , 850479 , 852016 , 853555 , 855097 , 856642 , 858190 , 859741 , 861294 , 862850 , 864409 , 865970 , 867535 , 869102 , 870673 , 872246 , 873822 , 875400 , 876982 , 878566 , 880154 , 881744 , 883337 , 884933 , 886532 , 888133 , 889738 , 891345 , 892956 , 894569 , 896185 , 897804 , 899426 , 901052 , 902679 , 904310 , 905944 , 907581 , 909221 , 910863 , 912509 , 914158 , 915809 , 917464 , 919121 , 920782 , 922446 , 924112 , 925782 , 927454 , 929130 , 930809 , 932490 , 934175 , 935863 , 937554 , 939247 , 940944 , 942645 , 944347 , 946054 , 947763 , 949475 , 951191 , 952909 , 954631 , 956356 , 958083 , 959814 , 961548 , 963286 , 965026 , 966770 , 968516 , 970266 , 972019 , 973775 , 975534 , 977297 , 979063 , 980832 , 982604 , 984379 , 986157 , 987939 , 989724 , 991512 , 993303 , 995098 , 996896 , 998697 , 1000501 , 1002309 , 1004120 , 1005934 , 1007751 , 1009572 , 1011396 , 1013223 , 1015054 , 1016888 , 1018725 , 1020566 , 1022410 , 1024257 , 1026107 , 1027961 , 1029818 , 1031679 , 1033543 , 1035410 , 1037281 , 1039155 , 1041032 , 1042913 , 1044797 , 1046685 , 1048576 , 1050470 , 1052369 , 1054270 , 1056174 , 1058083 , 1059994 , 1061909 , 1063828 , 1065750 , 1067675 , 1069605 , 1071537 , 1073473 , 1075412 , 1077355 , 1079302 , 1081252 , 1083205 , 1085162 , 1087123 , 1089087 , 1091054 , 1093026 , 1095000 , 1096979 , 1098961 , 1100946 , 1102935 , 1104928 , 1106924 , 1108924 , 1110928 , 1112935 , 1114945 , 1116960 , 1118978 , 1120999 , 1123025 , 1125054 , 1127086 , 1129123 , 1131163 , 1133206 , 1135254 , 1137305 , 1139359 , 1141418 , 1143480 , 1145546 , 1147616 , 1149689 , 1151766 , 1153847 , 1155932 , 1158020 , 1160113 , 1162209 , 1164308 , 1166412 , 1168519 , 1170630 , 1172746 , 1174864 , 1176987 , 1179113 , 1181244 , 1183378 , 1185516 , 1187658 , 1189803 , 1191953 , 1194106 , 1196264 , 1198425 , 1200590 , 1202759 , 1204933 , 1207109 , 1209290 , 1211475 , 1213664 , 1215857 , 1218053 , 1220254 , 1222459 , 1224667 , 1226880 , 1229096 , 1231317 , 1233542 , 1235770 , 1238003 , 1240240 , 1242480 , 1244725 , 1246974 , 1249227 , 1251484 , 1253745 , 1256010 , 1258280 , 1260553 , 1262830 , 1265112 , 1267397 , 1269687 , 1271981 , 1274279 , 1276581 , 1278888 , 1281198 , 1283513 , 1285832 , 1288155 , 1290482 , 1292814 , 1295150 , 1297490 , 1299834 , 1302182 , 1304535 , 1306892 , 1309253 , 1311618 , 1313988 , 1316362 , 1318740 , 1321123 , 1323510 , 1325901 , 1328297 , 1330696 , 1333100 , 1335509 , 1337922 , 1340339 , 1342761 , 1345187 , 1347617 , 1350052 , 1352491 , 1354934 , 1357383 , 1359835 , 1362292 , 1364753 , 1367219 , 1369689 , 1372164 , 1374643 , 1377126 , 1379614 , 1382107 , 1384604 , 1387105 , 1389611 , 1392122 , 1394637 , 1397157 , 1399681 , 1402210 , 1404743 , 1407281 , 1409824 , 1412371 , 1414922 , 1417479 , 1420040 , 1422605 , 1425176 , 1427751 , 1430330 , 1432914 , 1435503 , 1438097 , 1440695 , 1443298 , 1445905 , 1448518 , 1451135 , 1453756 , 1456383 , 1459014 , 1461650 , 1464291 , 1466937 , 1469587 , 1472242 , 1474902 , 1477566 , 1480236 , 1482910 , 1485589 , 1488274 , 1490963 , 1493656 , 1496355 , 1499058 , 1501766 , 1504480 , 1507198 , 1509921 , 1512649 , 1515382 , 1518120 , 1520863 , 1523610 , 1526363 , 1529121 , 1531883 , 1534651 , 1537424 , 1540201 , 1542984 , 1545772 , 1548565 , 1551362 , 1554165 , 1556973 , 1559786 , 1562604 , 1565427 , 1568255 , 1571089 , 1573927 , 1576771 , 1579620 , 1582474 , 1585333 , 1588197 , 1591066 , 1593941 , 1596821 , 1599706 , 1602596 , 1605491 , 1608392 , 1611298 , 1614209 , 1617125 , 1620047 , 1622974 , 1625906 , 1628843 , 1631787 , 1634735 , 1637688 , 1640647 , 1643611 , 1646580 , 1649556 , 1652536 , 1655521 , 1658513 , 1661509 , 1664511 , 1667518 , 1670531 , 1673549 , 1676573 , 1679602 , 1682636 , 1685676 , 1688722 , 1691772 , 1694829 , 1697891 , 1700959 , 1704032 , 1707111 , 1710195 , 1713285 , 1716380 , 1719481 , 1722588 , 1725700 , 1728817 , 1731941 , 1735070 , 1738205 , 1741345 , 1744491 , 1747643 , 1750801 , 1753964 , 1757133 , 1760308 , 1763488 , 1766674 , 1769866 , 1773063 , 1776266 , 1779476 , 1782691 , 1785911 , 1789138 , 1792371 , 1795609 , 1798853 , 1802103 , 1805359 , 1808621 , 1811888 , 1815162 , 1818441 , 1821727 , 1825018 , 1828315 , 1831618 , 1834927 , 1838243 , 1841564 , 1844891 , 1848224 , 1851563 , 1854908 , 1858260 , 1861617 , 1864980 , 1868350 , 1871726 , 1875107 , 1878495 , 1881889 , 1885289 , 1888695 , 1892107 , 1895526 , 1898951 , 1902381 , 1905818 , 1909262 , 1912711 , 1916167 , 1919629 , 1923097 , 1926571 , 1930052 , 1933539 , 1937032 , 1940532 , 1944038 , 1947550 , 1951069 , 1954594 , 1958125 , 1961663 , 1965207 , 1968758 , 1972315 , 1975878 , 1979448 , 1983024 , 1986607 , 1990196 , 1993792 , 1997394 , 2001003 , 2004618 , 2008240 , 2011868 , 2015503 , 2019144 , 2022792 , 2026447 , 2030108 , 2033776 , 2037450 , 2041131 , 2044819 , 2048514 , 2052214 , 2055922 , 2059637 , 2063358 , 2067085 , 2070820 , 2074562 , 2078309 , 2082065 , 2085826 , 2089594 , 2093370 , 2097152 , 2100941 , 2104737 , 2108539 , 2112349 , 2116166 , 2119989 , 2123819 , 2127656 , 2131500 , 2135351 , 2139209 , 2143074 , 2146945 , 2150825 , 2154710 , 2158603 , 2162504 , 2166410 , 2170324 , 2174246 , 2178174 , 2182109 , 2186052 , 2190001 , 2193957 , 2197922 , 2201892 , 2205870 , 2209856 , 2213849 , 2217848 , 2221856 , 2225870 , 2229891 , 2233920 , 2237956 , 2241999 , 2246050 , 2250108 , 2254173 , 2258246 , 2262325 , 2266413 , 2270508 , 2274610 , 2278719 , 2282836 , 2286961 , 2291092 , 2295232 , 2299379 , 2303533 , 2307695 , 2311864 , 2316041 , 2320225 , 2324417 , 2328616 , 2332824 , 2337039 , 2341261 , 2345491 , 2349728 , 2353973 , 2358227 , 2362487 , 2366755 , 2371032 , 2375315 , 2379606 , 2383906 , 2388213 , 2392528 , 2396851 , 2401181 , 2405519 , 2409865 , 2414219 , 2418580 , 2422951 , 2427328 , 2431713 , 2436107 , 2440508 , 2444917 , 2449335 , 2453760 , 2458193 , 2462634 , 2467083 , 2471540 , 2476006 , 2480479 , 2484961 , 2489451 , 2493948 , 2498454 , 2502968 , 2507490 , 2512020 , 2516559 , 2521106 , 2525660 , 2530224 , 2534795 , 2539374 , 2543963 , 2548559 , 2553163 , 2557776 , 2562397 , 2567026 , 2571665 , 2576311 , 2580965 , 2585628 , 2590300 , 2594979 , 2599668 , 2604365 , 2609070 , 2613784 , 2618506 , 2623237 , 2627977 , 2632724 , 2637481 , 2642246 , 2647020 , 2651802 , 2656594 , 2661393 , 2666201 , 2671019 , 2675844 , 2680678 , 2685522 , 2690374 , 2695234 , 2700104 , 2704982 , 2709869 , 2714765 , 2719670 , 2724583 , 2729506 , 2734437 , 2739377 , 2744327 , 2749285 , 2754252 , 2759229 , 2764213 , 2769207 , 2774211 , 2779223 , 2784244 , 2789275 , 2794314 , 2799362 , 2804420 , 2809487 , 2814562 , 2819648 , 2824742 , 2829845 , 2834958 , 2840080 , 2845211 , 2850352 , 2855501 , 2860660 , 2865829 , 2871006 , 2876193 , 2881390 , 2886596 , 2891810 , 2897036 , 2902270 , 2907513 , 2912766 , 2918029 , 2923300 , 2928582 , 2933873 , 2939173 , 2944484 , 2949804 , 2955133 , 2960473 , 2965821 , 2971179 , 2976548 , 2981925 , 2987312 , 2992710 , 2998117 , 3003533 , 3008960 , 3014396 , 3019842 , 3025298 , 3030764 , 3036239 , 3041726 , 3047221 , 3052726 , 3058242 , 3063767 , 3069302 , 3074848 , 3080403 , 3085968 , 3091544 , 3097129 , 3102724 , 3108331 , 3113946 , 3119572 , 3125209 , 3130855 , 3136511 , 3142178 , 3147855 , 3153542 , 3159240 , 3164947 , 3170665 , 3176394 , 3182133 , 3187881 , 3193642 , 3199411 , 3205191 , 3210983 , 3216784 , 3222595 , 3228418 , 3234251 , 3240094 , 3245948 , 3251812 , 3257687 , 3263573 , 3269469 , 3275376 , 3281294 , 3287222 , 3293161 , 3299111 , 3305072 , 3311042 , 3317025 , 3323018 , 3329021 , 3335036 , 3341061 , 3347097 , 3353145 , 3359203 , 3365272 , 3371352 , 3377443 , 3383545 , 3389659 , 3395782 , 3401917 , 3408064 , 3414221 , 3420389 , 3426570 , 3432760 , 3438962 , 3445175 , 3451400 , 3457635 , 3463882 , 3470140 , 3476409 , 3482691 , 3488983 , 3495286 , 3501602 , 3507928 , 3514265 , 3520615 , 3526975 , 3533347 , 3539732 , 3546126 , 3552533 , 3558952 , 3565382 , 3571823 , 3578277 , 3584741 , 3591217 , 3597706 , 3604206 , 3610717 , 3617242 , 3623777 , 3630323 , 3636883 , 3643453 , 3650035 , 3656631 , 3663237 , 3669855 , 3676486 , 3683128 , 3689782 , 3696449 , 3703127 , 3709817 , 3716520 , 3723234 , 3729961 , 3736701 , 3743451 , 3750214 , 3756991 , 3763778 , 3770577 , 3777391 , 3784215 , 3791051 , 3797901 , 3804763 , 3811636 , 3818524 , 3825422 , 3832333 , 3839258 , 3846194 , 3853142 , 3860105 , 3867078 , 3874065 , 3881065 , 3888076 , 3895100 , 3902138 , 3909188 , 3916250 , 3923327 , 3930415 , 3937515 , 3944630 , 3951756 , 3958895 , 3966049 , 3973214 , 3980392 , 3987584 , 3994788 , 4002005 , 4009236 , 4016479 , 4023736 , 4031006 , 4038288 , 4045584 , 4052894 , 4060216 , 4067551 , 4074901 , 4082263 , 4089638 , 4097027 , 4104429 , 4111844 , 4119274 , 4126715 , 4134171 , 4141641 , 4149123 , 4156619 , 4164130 , 4171652 , 4179189 , 4186740 , 4194304 , 4201882 , 4209474 , 4217079 , 4224697 , 4232331 , 4239977 , 4247637 , 4255312 , 4263000 , 4270701 , 4278418 , 4286148 , 4293891 , 4301650 , 4309421 , 4317206 , 4325007 , 4332821 , 4340648 , 4348491 , 4356347 , 4364218 , 4372103 , 4380002 , 4387915 , 4395843 , 4403785 , 4411741 , 4419712 , 4427697 , 4435696 , 4443711 , 4451739 , 4459781 , 4467840 , 4475912 , 4483998 , 4492100 , 4500215 , 4508345 , 4516492 , 4524651 , 4532825 , 4541016 , 4549219 , 4557438 , 4565673 , 4573921 , 4582184 , 4590464 , 4598757 , 4607065 , 4615390 , 4623728 , 4632081 , 4640451 , 4648834 , 4657233 , 4665648 , 4674077 , 4682521 , 4690982 , 4699457 , 4707947 , 4716454 , 4724974 , 4733510 , 4742064 , 4750631 , 4759213 , 4767812 , 4776426 , 4785055 , 4793701 , 4802361 , 4811037 , 4819731 , 4828438 , 4837161 , 4845901 , 4854656 , 4863426 , 4872214 , 4881016 , 4889834 , 4898670 , 4907520 , 4916385 , 4925269 , 4934167 , 4943081 , 4952013 , 4960959 , 4969921 , 4978902 , 4987896 , 4996907 , 5005937 , 5014980 , 5024040 , 5033118 , 5042211 , 5051320 , 5060448 , 5069590 , 5078748 , 5087925 , 5097117 , 5106326 , 5115552 , 5124794 , 5134052 , 5143329 , 5152621 , 5161930 , 5171257 , 5180599 , 5189959 , 5199336 , 5208729 , 5218139 , 5227568 , 5237012 , 5246473 , 5255953 , 5265449 , 5274961 , 5284493 , 5294040 , 5303604 , 5313187 , 5322786 , 5332402 , 5342037 , 5351688 , 5361356 , 5371044 , 5380747 , 5390468 , 5400208 , 5409964 , 5419738 , 5429531 , 5439340 , 5449166 , 5459012 , 5468875 , 5478755 , 5488654 , 5498570 , 5508504 , 5518457 , 5528427 , 5538414 , 5548422 , 5558446 , 5568487 , 5578549 , 5588627 , 5598724 , 5608840 , 5618973 , 5629124 , 5639296 , 5649484 , 5659690 , 5669916 , 5680160 , 5690421 , 5700704 , 5711002 , 5721320 , 5731658 , 5742013 , 5752386 , 5762780 , 5773191 , 5783621 , 5794071 , 5804539 , 5815025 , 5825533 , 5836057 , 5846600 , 5857165 , 5867746 , 5878347 , 5888969 , 5899608 , 5910266 , 5920945 , 5931642 , 5942358 , 5953095 , 5963850 , 5974624 , 5985420 , 5996233 , 6007066 , 6017920 , 6028792 , 6039684 , 6050597 , 6061528 , 6072479 , 6083451 , 6094441 , 6105452 , 6116484 , 6127534 , 6138604 , 6149696 , 6160805 , 6171936 , 6183088 , 6194258 , 6205449 , 6216661 , 6227892 , 6239144 , 6250417 , 6261709 , 6273021 , 6284356 , 6295710 , 6307083 , 6318480 , 6329895 , 6341330 , 6352788 , 6364265 , 6375763 , 6387283 , 6398823 , 6410383 , 6421966 , 6433568 , 6445190 , 6456836 , 6468501 , 6480187 , 6491896 , 6503625 , 6515374 , 6527147 , 6538939 , 6550752 , 6562589 , 6574444 , 6586322 , 6598223 , 6610143 , 6622085 , 6634050 , 6646035 , 6658042 , 6670073 , 6682123 , 6694195 , 6706290 , 6718406 , 6730543 , 6742705 , 6754886 , 6767090 , 6779317 , 6791565 , 6803834 , 6816128 , 6828442 , 6840778 , 6853139 , 6865520 , 6877923 , 6890351 , 6902799 , 6915270 , 6927765 , 6940281 , 6952819 , 6965382 , 6977966 , 6990572 , 7003203 , 7015855 , 7028530 , 7041230 , 7053951 , 7066694 , 7079463 , 7092253 , 7105066 , 7117904 , 7130763 , 7143645 , 7156554 , 7169482 , 7182435 , 7195413 , 7208412 , 7221435 , 7234483 , 7247553 , 7260646 , 7273766 , 7286907 , 7300071 , 7313262 , 7326474 , 7339710 , 7352972 , 7366256 , 7379564 , 7392898 , 7406254 , 7419634 , 7433041 , 7446469 , 7459922 , 7473401 , 7486903 , 7500428 , 7513981 , 7527556 , 7541155 , 7554781 , 7568430 , 7582103 , 7595803 , 7609525 , 7623273 , 7637047 , 7650844 , 7664666 , 7678516 , 7692388 , 7706285 , 7720209 , 7734157 , 7748129 , 7762129 , 7776152 , 7790201 , 7804277 , 7818376 , 7832501 , 7846653 , 7860829 , 7875030 , 7889260 , 7903513 , 7917791 , 7932098 , 7946428 , 7960784 , 7975168 , 7989576 , 8004010 , 8018473 , 8032959 , 8047471 , 8062012 , 8076577 , 8091168 , 8105788 , 8120432 , 8135102 , 8149802 , 8164525 , 8179275 , 8194054 , 8208858 , 8223688 , 8238547 , 8253431 , 8268342 , 8283282 , 8298246 , 8313238 , 8328259 , 8343305 , 8358378 , 8373481 , 8388608 , 8403764 , 8418948 , 8434158 , 8449394 , 8464662 , 8479954 , 8495274 , 8510624 , 8526000 , 8541402 , 8556836 , 8572296 , 8587782 , 8603300 , 8618842 , 8634412 , 8650014 , 8665642 , 8681296 , 8696982 , 8712694 , 8728436 , 8744206 , 8760004 , 8775830 , 8791686 , 8807570 , 8823482 , 8839424 , 8855394 , 8871392 , 8887422 , 8903478 , 8919562 , 8935680 , 8951824 , 8967996 , 8984200 , 9000430 , 9016690 , 9032984 , 9049302 , 9065650 , 9082032 , 9098438 , 9114876 , 9131346 , 9147842 , 9164368 , 9180928 , 9197514 , 9214130 , 9230780 , 9247456 , 9264162 , 9280902 , 9297668 , 9314466 , 9331296 , 9348154 , 9365042 , 9381964 , 9398914 , 9415894 , 9432908 , 9449948 , 9467020 , 9484128 , 9501262 , 9518426 , 9535624 , 9552852 , 9570110 , 9587402 , 9604722 , 9622074 , 9639462 , 9656876 , 9674322 , 9691802 , 9709312 , 9726852 , 9744428 , 9762032 , 9779668 , 9797340 , 9815040 , 9832770 , 9850538 , 9868334 , 9886162 , 9904026 , 9921918 , 9939842 , 9957804 , 9975792 , 9993814 , 10011874 , 10029960 , 10048080 , 10066236 , 10084422 , 10102640 , 10120896 , 10139180 , 10157496 , 10175850 , 10194234 , 10212652 , 10231104 , 10249588 , 10268104 , 10286658 , 10305242 , 10323860 , 10342514 , 10361198 , 10379918 , 10398672 , 10417458 , 10436278 , 10455136 , 10474024 , 10492946 , 10511906 , 10530898 , 10549922 , 10568986 , 10588080 , 10607208 , 10626374 , 10645572 , 10664804 , 10684074 , 10703376 , 10722712 , 10742088 , 10761494 , 10780936 , 10800416 , 10819928 , 10839476 , 10859062 , 10878680 , 10898332 , 10918024 , 10937750 , 10957510 , 10977308 , 10997140 , 11017008 , 11036914 , 11056854 , 11076828 , 11096844 , 11116892 , 11136974 , 11157098 , 11177254 , 11197448 , 11217680 , 11237946 , 11258248 , 11278592 , 11298968 , 11319380 , 11339832 , 11360320 , 11380842 , 11401408 , 11422004 , 11442640 , 11463316 , 11484026 , 11504772 , 11525560 , 11546382 , 11567242 , 11588142 , 11609078 , 11630050 , 11651066 , 11672114 , 11693200 , 11714330 , 11735492 , 11756694 , 11777938 , 11799216 , 11820532 , 11841890 , 11863284 , 11884716 , 11906190 , 11927700 , 11949248 , 11970840 , 11992466 , 12014132 , 12035840 , 12057584 , 12079368 , 12101194 , 12123056 , 12144958 , 12166902 , 12188882 , 12210904 , 12232968 , 12255068 , 12277208 , 12299392 , 12321610 , 12343872 , 12366176 , 12388516 , 12410898 , 12433322 , 12455784 , 12478288 , 12500834 , 12523418 , 12546042 , 12568712 , 12591420 , 12614166 , 12636960 , 12659790 , 12682660 , 12705576 , 12728530 , 12751526 , 12774566 , 12797646 , 12820766 , 12843932 , 12867136 , 12890380 , 12913672 , 12937002 , 12960374 , 12983792 , 13007250 , 13030748 , 13054294 , 13077878 , 13101504 , 13125178 , 13148888 , 13172644 , 13196446 , 13220286 , 13244170 , 13268100 , 13292070 , 13316084 , 13340146 , 13364246 , 13388390 , 13412580 , 13436812 , 13461086 , 13485410 , 13509772 , 13534180 , 13558634 , 13583130 , 13607668 , 13632256 , 13656884 , 13681556 , 13706278 , 13731040 , 13755846 , 13780702 , 13805598 , 13830540 , 13855530 , 13880562 , 13905638 , 13930764 , 13955932 , 13981144 , 14006406 , 14031710 , 14057060 , 14082460 , 14107902 , 14133388 , 14158926 , 14184506 , 14210132 , 14235808 , 14261526 , 14287290 , 14313108 , 14338964 , 14364870 , 14390826 , 14416824 , 14442870 , 14468966 , 14495106 , 14521292 , 14547532 , 14573814 , 14600142 , 14626524 , 14652948 , 14679420 , 14705944 , 14732512 , 14759128 , 14785796 , 14812508 , 14839268 , 14866082 , 14892938 , 14919844 , 14946802 , 14973806 , 15000856 , 15027962 , 15055112 , 15082310 , 15109562 , 15136860 , 15164206 , 15191606 , 15219050 , 15246546 , 15274094 , 15301688 , 15329332 , 15357032 , 15384776 , 15412570 , 15440418 , 15468314 , 15496258 , 15524258 , 15552304 , 15580402 , 15608554 , 15636752 , 15665002 , 15693306 , 15721658 , 15750060 , 15778520 , 15807026 , 15835582 , 15864196 , 15892856 , 15921568 , 15950336 , 15979152 , 16008020 , 16036946 , 16065918 , 16094942 , 16124024 , 16153154 , 16182336 , 16211576 , 16240864 , 16270204 , 16299604 , 16329050 , 16358550 , 16388108 , 16417716 , 16447376 , 16477094 , 16506862 , 16536684 , 16566564 , 16596492 , 16626476 , 16656518 , 16686610 , 16716756 , 16746962 , 16777216 , 16807532 , 16837890 , 16868314 , 16898794 , 16929318 , 16959908 , 16990554 , 17021242 , 17051998 , 17082810 , 17113666 , 17144590 , 17175568 , 17206592 , 17237682 , 17268830 , 17300022 , 17331282 , 17362598 , 17393960 , 17425388 , 17456874 , 17488406 , 17520006 , 17551664 , 17583366 , 17615138 , 17646968 , 17678842 , 17710788 , 17742790 , 17774838 , 17806956 , 17839130 , 17871352 , 17903646 , 17935996 , 17968392 , 18000860 , 18033386 , 18065960 , 18098602 , 18131306 , 18164056 , 18196876 , 18229756 , 18262684 , 18295684 , 18328742 , 18361850 , 18395028 , 18428266 , 18461552 , 18494910 , 18528330 , 18561796 , 18595336 , 18628936 , 18662586 , 18696308 , 18730090 , 18763922 , 18797826 , 18831792 , 18865808 , 18899896 , 18934048 , 18968246 , 19002522 , 19036858 , 19071242 , 19105702 , 19140226 , 19174798 , 19209444 , 19244154 , 19278914 , 19313750 , 19348648 , 19383598 , 19418622 , 19453710 , 19488848 , 19524064 , 19559342 , 19594672 , 19630078 , 19665548 , 19701068 , 19736666 , 19772330 , 19808044 , 19843834 , 19879690 , 19915598 , 19951584 , 19987636 , 20023738 , 20059920 , 20096166 , 20132466 , 20168844 , 20205286 , 20241782 , 20278358 , 20315000 , 20351694 , 20388468 , 20425308 , 20462202 , 20499174 , 20536216 , 20573308 , 20610484 , 20647724 , 20685020 , 20722396 , 20759840 , 20797338 , 20834916 , 20872564 , 20910266 , 20948048 , 20985900 , 21023806 , 21061794 , 21099852 , 21137962 , 21176158 , 21214422 , 21252740 , 21291142 , 21329614 , 21368140 , 21406750 , 21445432 , 21484168 , 21522988 , 21561878 , 21600824 , 21639856 , 21678956 , 21718114 , 21757358 , 21796672 , 21836042 , 21875498 , 21915024 , 21954610 , 21994280 , 22034022 , 22073820 , 22113706 , 22153664 , 22193680 , 22233782 , 22273956 , 22314188 , 22354508 , 22394902 , 22435352 , 22475892 , 22516504 , 22557174 , 22597934 , 22638766 , 22679658 , 22720638 , 22761692 , 22802806 , 22844008 , 22885286 , 22926622 , 22968050 , 23009550 , 23051112 , 23092764 , 23134490 , 23176278 , 23218156 , 23260108 , 23302122 , 23344228 , 23386408 , 23428650 , 23470984 , 23513394 , 23555866 , 23598430 , 23641070 , 23683772 , 23726566 , 23769438 , 23812372 , 23855400 , 23898504 , 23941672 , 23984932 , 24028270 , 24071672 , 24115168 , 24158742 , 24202378 , 24246110 , 24289922 , 24333796 , 24377764 , 24421814 , 24465926 , 24510134 , 24554422 , 24598772 , 24643220 , 24687750 , 24732342 , 24777032 , 24821802 , 24866636 , 24911568 , 24956582 , 25001660 , 25046836 , 25092094 , 25137416 , 25182838 , 25228340 , 25273910 , 25319578 , 25365328 , 25411144 , 25457060 , 25503060 , 25549124 , 25595290 , 25641538 , 25687854 , 25734270 , 25780770 , 25827336 , 25874004 , 25920756 , 25967576 , 26014498 , 26061504 , 26108578 , 26155754 , 26203014 , 26250344 , 26297776 , 26345294 , 26392882 , 26440572 , 26488348 , 26536192 , 26584140 , 26632176 , 26680280 , 26728490 , 26776786 , 26825152 , 26873624 , 26922182 , 26970810 , 27019544 , 27068366 , 27117258 , 27166258 , 27215344 , 27264502 , 27313768 , 27363122 , 27412546 , 27462078 , 27511700 , 27561394 , 27611196 , 27661086 , 27711050 , 27761122 , 27811284 , 27861518 , 27911862 , 27962296 , 28012804 , 28063420 , 28114128 , 28164910 , 28215802 , 28266786 , 28317842 , 28369010 , 28420272 , 28471606 , 28523052 , 28574590 , 28626204 , 28677928 , 28729748 , 28781642 , 28833648 , 28885748 , 28937922 , 28990212 , 29042594 , 29095052 , 29147626 , 29200292 , 29253036 , 29305894 , 29358848 , 29411876 , 29465022 , 29518262 , 29571580 , 29625014 , 29678544 , 29732152 , 29785874 , 29839696 , 29893594 , 29947610 , 30001722 , 30055914 , 30110222 , 30164628 , 30219114 , 30273718 , 30328420 , 30383200 , 30438100 , 30493100 , 30548178 , 30603376 , 30658674 , 30714052 , 30769550 , 30825148 , 30880826 , 30936626 , 30992526 , 31048506 , 31104608 , 31160812 , 31217096 , 31273504 , 31330012 , 31386602 , 31443316 , 31500130 , 31557028 , 31614050 , 31671174 , 31728380 , 31785710 , 31843144 , 31900662 , 31958304 , 32016050 , 32073880 , 32131834 , 32189894 , 32248038 , 32306306 , 32364682 , 32423140 , 32481726 , 32540418 , 32599196 , 32658100 , 32717110 , 32776206 , 32835430 , 32894760 , 32954178 , 33013722 , 33073376 , 33133116 , 33192984 , 33252962 , 33313024 , 33373218 , 33433522 , 33493912 , 33554432 , 33615064 , 33675780 , 33736628 , 33797588 , 33858636 , 33919816 , 33981108 , 34042484 , 34103996 , 34165620 , 34227332 , 34289180 , 34351136 , 34413184 , 34475364 , 34537660 , 34600044 , 34662564 , 34725196 , 34787920 , 34850776 , 34913748 , 34976812 , 35040012 , 35103328 , 35166732 , 35230276 , 35293936 , 35357684 , 35421576 , 35485580 , 35549676 , 35613912 , 35678260 , 35742704 , 35807292 , 35871992 , 35936784 , 36001720 , 36066772 , 36131920 , 36197204 , 36262612 , 36328112 , 36393752 , 36459512 , 36525368 , 36591368 , 36657484 , 36723700 , 36790056 , 36856532 , 36923104 , 36989820 , 37056660 , 37123592 , 37190672 , 37257872 , 37325172 , 37392616 , 37460180 , 37527844 , 37595652 , 37663584 , 37731616 , 37799792 , 37868096 , 37936492 , 38005044 , 38073716 , 38142484 , 38211404 , 38280452 , 38349596 , 38418888 , 38488308 , 38557828 , 38627500 , 38697296 , 38767196 , 38837244 , 38907420 , 38977696 , 39048128 , 39118684 , 39189344 , 39260156 , 39331096 , 39402136 , 39473332 , 39544660 , 39616088 , 39687668 , 39759380 , 39831196 , 39903168 , 39975272 , 40047476 , 40119840 , 40192332 , 40264932 , 40337688 , 40410572 , 40483564 , 40556716 , 40630000 , 40703388 , 40776936 , 40850616 , 40924404 , 40998348 , 41072432 , 41146616 , 41220968 , 41295448 , 41370040 , 41444792 , 41519680 , 41594676 , 41669832 , 41745128 , 41820532 , 41896096 , 41971800 , 42047612 , 42123588 , 42199704 , 42275924 , 42352316 , 42428844 , 42505480 , 42582284 , 42659228 , 42736280 , 42813500 , 42890864 , 42968336 , 43045976 , 43123756 , 43201648 , 43279712 , 43357912 , 43436228 , 43514716 , 43593344 , 43672084 , 43750996 , 43830048 , 43909220 , 43988560 , 44068044 , 44147640 , 44227412 , 44307328 , 44387360 , 44467564 , 44547912 , 44628376 , 44709016 , 44789804 , 44870704 , 44951784 , 45033008 , 45114348 , 45195868 , 45277532 , 45359316 , 45441276 , 45523384 , 45605612 , 45688016 , 45770572 , 45853244 , 45936100 , 46019100 , 46102224 , 46185528 , 46268980 , 46352556 , 46436312 , 46520216 , 46604244 , 46688456 , 46772816 , 46857300 , 46941968 , 47026788 , 47111732 , 47196860 , 47282140 , 47367544 , 47453132 , 47538876 , 47624744 , 47710800 , 47797008 , 47883344 , 47969864 , 48056540 , 48143344 , 48230336 , 48317484 , 48404756 , 48492220 , 48579844 , 48667592 , 48755528 , 48843628 , 48931852 , 49020268 , 49108844 , 49197544 , 49286440 , 49375500 , 49464684 , 49554064 , 49643604 , 49733272 , 49823136 , 49913164 , 50003320 , 50093672 , 50184188 , 50274832 , 50365676 , 50456680 , 50547820 , 50639156 , 50730656 , 50822288 , 50914120 , 51006120 , 51098248 , 51190580 , 51283076 , 51375708 , 51468540 , 51561540 , 51654672 , 51748008 , 51841512 , 51935152 , 52028996 , 52123008 , 52217156 , 52311508 , 52406028 , 52500688 , 52595552 , 52690588 , 52785764 , 52881144 , 52976696 , 53072384 , 53168280 , 53264352 , 53360560 , 53456980 , 53553572 , 53650304 , 53747248 , 53844364 , 53941620 , 54039088 , 54136732 , 54234516 , 54332516 , 54430688 , 54529004 , 54627536 , 54726244 , 54825092 , 54924156 , 55023400 , 55122788 , 55222392 , 55322172 , 55422100 , 55522244 , 55622568 , 55723036 , 55823724 , 55924592 , 56025608 , 56126840 , 56228256 , 56329820 , 56431604 , 56533572 , 56635684 , 56738020 , 56840544 , 56943212 , 57046104 , 57149180 , 57252408 , 57355856 , 57459496 , 57563284 , 57667296 , 57771496 , 57875844 , 57980424 , 58085188 , 58190104 , 58295252 , 58400584 , 58506072 , 58611788 , 58717696 , 58823752 , 58930044 , 59036524 , 59143160 , 59250028 , 59357088 , 59464304 , 59571748 , 59679392 , 59787188 , 59895220 , 60003444 , 60111828 , 60220444 , 60329256 , 60438228 , 60547436 , 60656840 , 60766400 , 60876200 , 60986200 , 61096356 , 61206752 , 61317348 , 61428104 , 61539100 , 61650296 , 61761652 , 61873252 , 61985052 , 62097012 , 62209216 , 62321624 , 62434192 , 62547008 , 62660024 , 62773204 , 62886632 , 63000260 , 63114056 , 63228100 , 63342348 , 63456760 , 63571420 , 63686288 , 63801324 , 63916608 , 64032100 , 64147760 , 64263668 , 64379788 , 64496076 , 64612612 , 64729364 , 64846280 , 64963452 , 65080836 , 65198392 , 65316200 , 65434220 , 65552412 , 65670860 , 65789520 , 65908356 , 66027444 , 66146752 , 66266232 , 66385968 , 66505924 , 66626048 , 66746436 , 66867044 , 66987824 , 67108864 , 67230128 , 67351560 , 67473256 , 67595176 , 67717272 , 67839632 , 67962216 , 68084968 , 68207992 , 68331240 , 68454664 , 68578360 , 68702272 , 68826368 , 68950728 , 69075320 , 69200088 , 69325128 , 69450392 , 69575840 , 69701552 , 69827496 , 69953624 , 70080024 , 70206656 , 70333464 , 70460552 , 70587872 , 70715368 , 70843152 , 70971160 , 71099352 , 71227824 , 71356520 , 71485408 , 71614584 , 71743984 , 71873568 , 72003440 , 72133544 , 72263840 , 72394408 , 72525224 , 72656224 , 72787504 , 72919024 , 73050736 , 73182736 , 73314968 , 73447400 , 73580112 , 73713064 , 73846208 , 73979640 , 74113320 , 74247184 , 74381344 , 74515744 , 74650344 , 74785232 , 74920360 , 75055688 , 75191304 , 75327168 , 75463232 , 75599584 , 75736192 , 75872984 , 76010088 , 76147432 , 76284968 , 76422808 , 76560904 , 76699192 , 76837776 , 76976616 , 77115656 , 77255000 , 77394592 , 77534392 , 77674488 , 77814840 , 77955392 , 78096256 , 78237368 , 78378688 , 78520312 , 78662192 , 78804272 , 78946664 , 79089320 , 79232176 , 79375336 , 79518760 , 79662392 , 79806336 , 79950544 , 80094952 , 80239680 , 80384664 , 80529864 , 80675376 , 80821144 , 80967128 , 81113432 , 81260000 , 81406776 , 81553872 , 81701232 , 81848808 , 81996696 , 82144864 , 82293232 , 82441936 , 82590896 , 82740080 , 82889584 , 83039360 , 83189352 , 83339664 , 83490256 , 83641064 , 83792192 , 83943600 , 84095224 , 84247176 , 84399408 , 84551848 , 84704632 , 84857688 , 85010960 , 85164568 , 85318456 , 85472560 , 85627000 , 85781728 , 85936672 , 86091952 , 86247512 , 86403296 , 86559424 , 86715824 , 86872456 , 87029432 , 87186688 , 87344168 , 87501992 , 87660096 , 87818440 , 87977120 , 88136088 , 88295280 , 88454824 , 88614656 , 88774720 , 88935128 , 89095824 , 89256752 , 89418032 , 89579608 , 89741408 , 89903568 , 90066016 , 90228696 , 90391736 , 90555064 , 90718632 , 90882552 , 91046768 , 91211224 , 91376032 , 91541144 , 91706488 , 91872200 , 92038200 , 92204448 , 92371056 , 92537960 , 92705112 , 92872624 , 93040432 , 93208488 , 93376912 , 93545632 , 93714600 , 93883936 , 94053576 , 94223464 , 94393720 , 94564280 , 94735088 , 94906264 , 95077752 , 95249488 , 95421600 , 95594016 , 95766688 , 95939728 , 96113080 , 96286688 , 96460672 , 96634968 , 96809512 , 96984440 , 97159688 , 97335184 , 97511056 , 97687256 , 97863704 , 98040536 , 98217688 , 98395088 , 98572880 , 98751000 , 98929368 , 99108128 , 99287208 , 99466544 , 99646272 , 99826328 , 100006640 , 100187344 , 100368376 , 100549664 , 100731352 , 100913360 , 101095640 , 101278312 , 101461312 , 101644576 , 101828240 , 102012240 , 102196496 , 102381160 , 102566152 , 102751416 , 102937080 , 103123080 , 103309344 , 103496016 , 103683024 , 103870304 , 104057992 , 104246016 , 104434312 , 104623016 , 104812056 , 105001376 , 105191104 , 105381176 , 105571528 , 105762288 , 105953392 , 106144768 , 106336560}

static const uint32_t expoTable[4096] = expotable10oct;

#endif /* INC_TABLES_H_ */