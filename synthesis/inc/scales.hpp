/*
 * scales.h
 *
 *  Created on: Aug 18, 2018
 *      Author: willmitchell
 */

#ifndef INC_SCALES_HPP_
#define INC_SCALES_HPP_


/// Data structure for a note in a scale as represented by a precalculated ratio of integers. Generated with (link).
typedef struct {
    /// Top 32 bits of a 64 bit precalculated ratio.
	const uint32_t integerPart;
	/// Bottom 32 bits of a 64 bit precalculated ratio.
	const uint32_t fractionalPart;
	/// GCD of the numerator and denominator.
	const uint32_t fundamentalDivision;
} ScaleNote;


/// Data structure for a grid of scale notes. Generated with (link).
typedef struct {
    /// An array of scales (an array of pointers to notes).
	const ScaleNote* const** grid;
	/// 12 - log2(number of scales) used to scale a control to an lookup index.
	const uint32_t t2Bitshift;
	/// Use 1v_oct control parsing if 1.
	const uint32_t oneVoltOct;
} Scale;



static const ScaleNote ratio27_1 = {1769472, 0, 1};
static const ScaleNote ratio1_4_10 = {16384, 0, 10};
static const ScaleNote ratio10_3 = {218453, 1431655765, 3};
static const ScaleNote ratio7_2 = {229376, 0, 2};
static const ScaleNote ratio12_1 = {786432, 0, 1};
static const ScaleNote ratio4_3_3 = {87381, 1431655765, 3};
static const ScaleNote ratio4_5_6 = {52428, 3435973836, 6};
static const ScaleNote ratio19_128 = {9728, 0, 128};
static const ScaleNote ratio13_512 = {1664, 0, 512};
static const ScaleNote ratio2_3_14 = {43690, 2863311530, 14};
static const ScaleNote ratio1_2_16 = {32768, 0, 16};
static const ScaleNote ratio5_2 = {163840, 0, 2};
static const ScaleNote ratio1_3_11 = {21845, 1431655765, 11};
static const ScaleNote ratio9_8_5 = {73728, 0, 5};
static const ScaleNote ratio5_4_15 = {81920, 0, 15};
static const ScaleNote ratio4_5_7 = {52428, 3435973836, 7};
static const ScaleNote ratio6_5_7 = {78643, 858993459, 7};
static const ScaleNote ratio3_2_11 = {98304, 0, 11};
static const ScaleNote ratio17_15 = {74274, 572662306, 15};
static const ScaleNote ratio19_32 = {38912, 0, 32};
static const ScaleNote ratio19_8 = {155648, 0, 8};
static const ScaleNote ratio3_1_1 = {196608, 0, 1};
static const ScaleNote ratio25_63 = {26006, 1499829849, 63};
static const ScaleNote ratio225_49 = {300930, 2629571814, 49};
static const ScaleNote ratio1_1_7 = {65536, 0, 7};
static const ScaleNote ratio6_5_9 = {78643, 858993459, 9};
static const ScaleNote ratio19_1 = {1245184, 0, 1};
static const ScaleNote ratio567_25 = {1486356, 2061584302, 25};
static const ScaleNote ratio2_1_7 = {131072, 0, 7};
static const ScaleNote ratio1_25 = {2621, 1889785610, 25};
static const ScaleNote ratio7_4_5 = {114688, 0, 5};
static const ScaleNote ratio5_192 = {1706, 2863311530, 192};
static const ScaleNote ratio3_2 = {98304, 0, 2};
static const ScaleNote ratio75_7 = {702171, 1840700269, 7};
static const ScaleNote ratio2_3_15 = {43690, 2863311530, 15};
static const ScaleNote ratio7_5_10 = {91750, 1717986918, 10};
static const ScaleNote ratio4_3_15 = {87381, 1431655765, 15};
static const ScaleNote ratio1_36 = {1820, 1908874353, 36};
static const ScaleNote ratio9_320 = {1843, 858993459, 320};
static const ScaleNote ratio5_3_6 = {109226, 2863311530, 6};
static const ScaleNote ratio36_7 = {337042, 1227133513, 7};
static const ScaleNote ratio4_1_2 = {262144, 0, 2};
static const ScaleNote ratio5_1_2 = {327680, 0, 2};
static const ScaleNote ratio11_112 = {6436, 2454267026, 112};
static const ScaleNote ratio5_3_12 = {109226, 2863311530, 12};
static const ScaleNote ratio5_144 = {2275, 2386092942, 144};
static const ScaleNote ratio5_48 = {6826, 2863311530, 48};
static const ScaleNote ratio7_40 = {11468, 3435973836, 40};
static const ScaleNote ratio4_5_14 = {52428, 3435973836, 14};
static const ScaleNote ratio160_7 = {1497965, 3067833783, 7};
static const ScaleNote ratio17_8 = {139264, 0, 8};
static const ScaleNote ratio5_4_7 = {81920, 0, 7};
static const ScaleNote ratio7_20 = {22937, 2576980377, 20};
static const ScaleNote ratio192_7 = {1797558, 3681400539, 7};
static const ScaleNote ratio7_1 = {458752, 0, 1};
static const ScaleNote ratio112_5 = {1468006, 1717986918, 5};
static const ScaleNote ratio13_2 = {425984, 0, 2};
static const ScaleNote ratio88_7 = {823881, 613566756, 7};
static const ScaleNote ratio7_5_8 = {91750, 1717986918, 8};
static const ScaleNote ratio3_2_14 = {98304, 0, 14};
static const ScaleNote ratio1_2 = {32768, 0, 2};
static const ScaleNote ratio7_11 = {41704, 3123612578, 11};
static const ScaleNote ratio13_64 = {13312, 0, 64};
static const ScaleNote ratio3_4_2 = {49152, 0, 2};
static const ScaleNote ratio7_5_4 = {91750, 1717986918, 4};
static const ScaleNote ratio5_3 = {109226, 2863311530, 3};
static const ScaleNote ratio25_49 = {33436, 3155486176, 49};
static const ScaleNote ratio2_3_12 = {43690, 2863311530, 12};
static const ScaleNote ratio7_4_2 = {114688, 0, 2};
static const ScaleNote ratio7_4_6 = {114688, 0, 6};
static const ScaleNote ratio32_5 = {419430, 1717986918, 5};
static const ScaleNote ratio34_1 = {2228224, 0, 1};
static const ScaleNote ratio7_5_13 = {91750, 1717986918, 13};
static const ScaleNote ratio64_9 = {466033, 3340530119, 9};
static const ScaleNote ratio1_7 = {9362, 1227133513, 7};
static const ScaleNote ratio3_4_11 = {49152, 0, 11};
static const ScaleNote ratio176_7 = {1647762, 1227133513, 7};
static const ScaleNote ratio4_3_13 = {87381, 1431655765, 13};
static const ScaleNote ratio1_18 = {3640, 3817748707, 18};
static const ScaleNote ratio189_5 = {2477260, 3435973836, 5};
static const ScaleNote ratio5_2_1 = {163840, 0, 1};
static const ScaleNote ratio40_3 = {873813, 1431655765, 3};
static const ScaleNote ratio17_64 = {17408, 0, 64};
static const ScaleNote ratio2_1_5 = {131072, 0, 5};
static const ScaleNote ratio6_5_8 = {78643, 858993459, 8};
static const ScaleNote ratio4_3_4 = {87381, 1431655765, 4};
static const ScaleNote ratio5_3_9 = {109226, 2863311530, 9};
static const ScaleNote ratio9_8_1 = {73728, 0, 1};
static const ScaleNote ratio5_2_5 = {163840, 0, 5};
static const ScaleNote ratio4_1_6 = {262144, 0, 6};
static const ScaleNote ratio4_1_7 = {262144, 0, 7};
static const ScaleNote ratio3_20 = {9830, 1717986918, 20};
static const ScaleNote ratio15_7 = {140434, 1227133513, 7};
static const ScaleNote ratio5_3_5 = {109226, 2863311530, 5};
static const ScaleNote ratio5_4_13 = {81920, 0, 13};
static const ScaleNote ratio4_3 = {87381, 1431655765, 3};
static const ScaleNote ratio15_8 = {122880, 0, 8};
static const ScaleNote ratio3_2_9 = {98304, 0, 9};
static const ScaleNote ratio3_4_4 = {49152, 0, 4};
static const ScaleNote ratio21_25 = {55050, 1030792151, 25};
static const ScaleNote ratio48_7 = {449389, 3067833782, 7};
static const ScaleNote ratio1_12 = {5461, 1431655765, 12};
static const ScaleNote ratio192_5 = {2516582, 1717986918, 5};
static const ScaleNote ratio4_1_8 = {262144, 0, 8};
static const ScaleNote ratio1_4_8 = {16384, 0, 8};
static const ScaleNote ratio12_1_8 = {786432, 0, 8};
static const ScaleNote ratio3_2_13 = {98304, 0, 13};
static const ScaleNote ratio3_128 = {1536, 0, 128};
static const ScaleNote ratio5_24 = {13653, 1431655765, 24};
static const ScaleNote ratio5_128 = {2560, 0, 128};
static const ScaleNote ratio8_1_8 = {524288, 0, 8};
static const ScaleNote ratio1_4_15 = {16384, 0, 15};
static const ScaleNote ratio64_5 = {838860, 3435973837, 5};
static const ScaleNote ratio1_1_12 = {65536, 0, 12};
static const ScaleNote ratio27_5 = {353894, 1717986918, 5};
static const ScaleNote ratio1_17 = {3855, 252645135, 17};
static const ScaleNote ratio15_512 = {1920, 0, 512};
static const ScaleNote ratio81_25 = {212336, 2748779069, 25};
static const ScaleNote ratio44_7 = {411940, 2454267026, 7};
static const ScaleNote ratio5_4_8 = {81920, 0, 8};
static const ScaleNote ratio5_4_9 = {81920, 0, 9};
static const ScaleNote ratio11_4 = {180224, 0, 4};
static const ScaleNote ratio1_21 = {3120, 3272356035, 21};
static const ScaleNote ratio15_17 = {57825, 3789677025, 17};
static const ScaleNote ratio72_7 = {674084, 2454267026, 7};
static const ScaleNote ratio7_8 = {57344, 0, 8};
static const ScaleNote ratio18_5 = {235929, 2576980377, 5};
static const ScaleNote ratio5_2_3 = {163840, 0, 3};
static const ScaleNote ratio30_1 = {1966080, 0, 1};
static const ScaleNote ratio6_1_2 = {393216, 0, 2};
static const ScaleNote ratio11_8 = {90112, 0, 8};
static const ScaleNote ratio19_256 = {4864, 0, 256};
static const ScaleNote ratio4_5_4 = {52428, 3435973836, 4};
static const ScaleNote ratio9_8_2 = {73728, 0, 2};
static const ScaleNote ratio5_3_8 = {109226, 2863311530, 8};
static const ScaleNote ratio5_16 = {20480, 0, 16};
static const ScaleNote ratio8_1 = {524288, 0, 1};
static const ScaleNote ratio9_8_14 = {73728, 0, 14};
static const ScaleNote ratio18_7 = {168521, 613566756, 7};
static const ScaleNote ratio7_4_9 = {114688, 0, 9};
static const ScaleNote ratio2_1_4 = {131072, 0, 4};
static const ScaleNote ratio6_5_14 = {78643, 858993459, 14};
static const ScaleNote ratio4_3_11 = {87381, 1431655765, 11};
static const ScaleNote ratio3_2_12 = {98304, 0, 12};
static const ScaleNote ratio40_7 = {374491, 1840700269, 7};
static const ScaleNote ratio8_1_7 = {524288, 0, 7};
static const ScaleNote ratio11_224 = {3218, 1227133513, 224};
static const ScaleNote ratio2_3_7 = {43690, 2863311530, 7};
static const ScaleNote ratio1_4_9 = {16384, 0, 9};
static const ScaleNote ratio25_147 = {11145, 2483484490, 147};
static const ScaleNote ratio11_2 = {360448, 0, 2};
static const ScaleNote ratio3_1_16 = {196608, 0, 16};
static const ScaleNote ratio144_7 = {1348169, 613566757, 7};
static const ScaleNote ratio17_16 = {69632, 0, 16};
static const ScaleNote ratio7_4_7 = {114688, 0, 7};
static const ScaleNote ratio4_5_2 = {52428, 3435973836, 2};
static const ScaleNote ratio12_1_7 = {786432, 0, 7};
static const ScaleNote ratio8_1_6 = {524288, 0, 6};
static const ScaleNote ratio7_5_14 = {91750, 1717986918, 14};
static const ScaleNote ratio3_56 = {3510, 3681400539, 56};
static const ScaleNote ratio19_64 = {19456, 0, 64};
static const ScaleNote ratio5_72 = {4551, 477218588, 72};
static const ScaleNote ratio7_4_13 = {114688, 0, 13};
static const ScaleNote ratio17_3 = {371370, 2863311530, 3};
static const ScaleNote ratio25_9 = {182044, 1908874353, 9};
static const ScaleNote ratio3_40 = {4915, 858993459, 40};
static const ScaleNote ratio2_1_2 = {131072, 0, 2};
static const ScaleNote ratio5_4_14 = {81920, 0, 14};
static const ScaleNote ratio13_16 = {53248, 0, 16};
static const ScaleNote ratio5_36 = {9102, 954437176, 36};
static const ScaleNote ratio10_1_3 = {655360, 0, 3};
static const ScaleNote ratio9_8_4 = {73728, 0, 4};
static const ScaleNote ratio7_3 = {152917, 1431655765, 3};
static const ScaleNote ratio1_5 = {13107, 858993459, 5};
static const ScaleNote ratio441_25 = {1156055, 171798692, 25};
static const ScaleNote ratio1_14 = {4681, 613566756, 14};
static const ScaleNote ratio6_5_10 = {78643, 858993459, 10};
static const ScaleNote ratio5_3_3 = {109226, 2863311530, 3};
static const ScaleNote ratio11_64 = {11264, 0, 64};
static const ScaleNote ratio1_1_3 = {65536, 0, 3};
static const ScaleNote ratio17_32 = {34816, 0, 32};
static const ScaleNote ratio15_16 = {61440, 0, 16};
static const ScaleNote ratio27_8 = {221184, 0, 8};
static const ScaleNote ratio9_7 = {84260, 2454267026, 7};
static const ScaleNote ratio5_17 = {19275, 1263225675, 17};
static const ScaleNote ratio13_128 = {6656, 0, 128};
static const ScaleNote ratio3_4_1 = {49152, 0, 1};
static const ScaleNote ratio9_2 = {294912, 0, 2};
static const ScaleNote ratio1_4_5 = {16384, 0, 5};
static const ScaleNote ratio1_1_10 = {65536, 0, 10};
static const ScaleNote ratio13_15 = {56797, 3722304989, 15};
static const ScaleNote ratio19_2 = {622592, 0, 2};
static const ScaleNote ratio27_64 = {27648, 0, 64};
static const ScaleNote ratio5_2_14 = {163840, 0, 14};
static const ScaleNote ratio21_5 = {275251, 858993459, 5};
static const ScaleNote ratio3_4_6 = {49152, 0, 6};
static const ScaleNote ratio1_1_13 = {65536, 0, 13};
static const ScaleNote ratio15_13 = {75618, 1982292598, 13};
static const ScaleNote ratio9_8_6 = {73728, 0, 6};
static const ScaleNote ratio32_3 = {699050, 2863311530, 3};
static const ScaleNote ratio9_8_10 = {73728, 0, 10};
static const ScaleNote ratio1_1_15 = {65536, 0, 15};
static const ScaleNote ratio1_4_14 = {16384, 0, 14};
static const ScaleNote ratio5_4_1 = {81920, 0, 1};
static const ScaleNote ratio5_108 = {3034, 318145725, 108};
static const ScaleNote ratio1_6_16 = {10922, 2863311530, 16};
static const ScaleNote ratio9_40 = {14745, 2576980377, 40};
static const ScaleNote ratio19_16 = {77824, 0, 16};
static const ScaleNote ratio7_15 = {30583, 2004318071, 15};
static const ScaleNote ratio3_8_16 = {24576, 0, 16};
static const ScaleNote ratio2_3_3 = {43690, 2863311530, 3};
static const ScaleNote ratio27_7 = {252781, 3067833782, 7};
static const ScaleNote ratio16_1_16 = {1048576, 0, 16};
static const ScaleNote ratio80_3 = {1747626, 2863311531, 3};
static const ScaleNote ratio1_3_5 = {21845, 1431655765, 5};
static const ScaleNote ratio27_512 = {3456, 0, 512};
static const ScaleNote ratio2_7 = {18724, 2454267026, 7};
static const ScaleNote ratio4_5_3 = {52428, 3435973836, 3};
static const ScaleNote ratio3_4 = {49152, 0, 4};
static const ScaleNote ratio27_1024 = {1728, 0, 1024};
static const ScaleNote ratio11_28 = {25746, 1227133513, 28};
static const ScaleNote ratio3_16 = {12288, 0, 16};
static const ScaleNote ratio8_1_16 = {524288, 0, 16};
static const ScaleNote ratio1_3_7 = {21845, 1431655765, 7};
static const ScaleNote ratio27_256 = {6912, 0, 256};
static const ScaleNote ratio25_81 = {20227, 689315738, 81};
static const ScaleNote ratio4_3_9 = {87381, 1431655765, 9};
static const ScaleNote ratio27_4 = {442368, 0, 4};
static const ScaleNote ratio5_3_15 = {109226, 2863311530, 15};
static const ScaleNote ratio3_4_12 = {49152, 0, 12};
static const ScaleNote ratio14_5 = {183500, 3435973836, 5};
static const ScaleNote ratio9_8_12 = {73728, 0, 12};
static const ScaleNote ratio243_25 = {637009, 3951369912, 25};
static const ScaleNote ratio17_13 = {85700, 3964585196, 13};
static const ScaleNote ratio1_16 = {4096, 0, 16};
static const ScaleNote ratio15_64 = {15360, 0, 64};
static const ScaleNote ratio9_4 = {147456, 0, 4};
static const ScaleNote ratio10_1_5 = {655360, 0, 5};
static const ScaleNote ratio4_3_14 = {87381, 1431655765, 14};
static const ScaleNote ratio135_7 = {1263908, 2454267026, 7};
static const ScaleNote ratio4_3_8 = {87381, 1431655765, 8};
static const ScaleNote ratio27_2 = {884736, 0, 2};
static const ScaleNote ratio3_2_10 = {98304, 0, 10};
static const ScaleNote ratio10_1_7 = {655360, 0, 7};
static const ScaleNote ratio4_3_1 = {87381, 1431655765, 1};
static const ScaleNote ratio2_3_6 = {43690, 2863311530, 6};
static const ScaleNote ratio49_225 = {14272, 1221679586, 225};
static const ScaleNote ratio1_13 = {5041, 991146299, 13};
static const ScaleNote ratio49_25 = {128450, 2405181685, 25};
static const ScaleNote ratio25_729 = {2247, 1985464991, 729};
static const ScaleNote ratio12_1_6 = {786432, 0, 6};
static const ScaleNote ratio4_3_7 = {87381, 1431655765, 7};
static const ScaleNote ratio5_3_10 = {109226, 2863311530, 10};
static const ScaleNote ratio4_3_12 = {87381, 1431655765, 12};
static const ScaleNote ratio7_5_1 = {91750, 1717986918, 1};
static const ScaleNote ratio4_1_16 = {262144, 0, 16};
static const ScaleNote ratio128_3 = {2796202, 2863311530, 3};
static const ScaleNote ratio1_3_4 = {21845, 1431655765, 4};
static const ScaleNote ratio63_25 = {165150, 3092376453, 25};
static const ScaleNote ratio7_4_10 = {114688, 0, 10};
static const ScaleNote ratio6_5_2 = {78643, 858993459, 2};
static const ScaleNote ratio3_2_5 = {98304, 0, 5};
static const ScaleNote ratio4_5_5 = {52428, 3435973836, 5};
static const ScaleNote ratio7_5_11 = {91750, 1717986918, 11};
static const ScaleNote ratio3_112 = {1755, 1840700269, 112};
static const ScaleNote ratio1_4_12 = {16384, 0, 12};
static const ScaleNote ratio13_11 = {77451, 2733161006, 11};
static const ScaleNote ratio135_4 = {2211840, 0, 4};
static const ScaleNote ratio9_20 = {29491, 858993459, 20};
static const ScaleNote ratio25_1 = {1638400, 0, 1};
static const ScaleNote ratio5_28 = {11702, 3681400539, 28};
static const ScaleNote ratio2_9 = {14563, 2386092942, 9};
static const ScaleNote ratio32_9 = {233016, 3817748707, 9};
static const ScaleNote ratio3_28 = {7021, 3067833782, 28};
static const ScaleNote ratio8_3 = {174762, 2863311530, 3};
static const ScaleNote ratio5_4_2 = {81920, 0, 2};
static const ScaleNote ratio3_4_9 = {49152, 0, 9};
static const ScaleNote ratio5_3_16 = {109226, 2863311530, 16};
static const ScaleNote ratio3_4_16 = {49152, 0, 16};
static const ScaleNote ratio5_3_11 = {109226, 2863311530, 11};
static const ScaleNote ratio1_4_7 = {16384, 0, 7};
static const ScaleNote ratio6_5 = {78643, 858993459, 5};
static const ScaleNote ratio10_1 = {655360, 0, 1};
static const ScaleNote ratio8_1_4 = {524288, 0, 4};
static const ScaleNote ratio3_2_2 = {98304, 0, 2};
static const ScaleNote ratio4_5_16 = {52428, 3435973836, 16};
static const ScaleNote ratio25_441 = {3715, 827828163, 441};
static const ScaleNote ratio7_5_7 = {91750, 1717986918, 7};
static const ScaleNote ratio5_2_11 = {163840, 0, 11};
static const ScaleNote ratio13_5 = {170393, 2576980377, 5};
static const ScaleNote ratio36_25 = {94371, 3607772528, 25};
static const ScaleNote ratio10_1_1 = {655360, 0, 1};
static const ScaleNote ratio5_8 = {40960, 0, 8};
static const ScaleNote ratio5_14 = {23405, 3067833782, 14};
static const ScaleNote ratio8_1_3 = {524288, 0, 3};
static const ScaleNote ratio7_5_2 = {91750, 1717986918, 2};
static const ScaleNote ratio3_2_16 = {98304, 0, 16};
static const ScaleNote ratio8_1_2 = {524288, 0, 2};
static const ScaleNote ratio7_4_4 = {114688, 0, 4};
static const ScaleNote ratio1_3_16 = {21845, 1431655765, 16};
static const ScaleNote ratio5_6 = {54613, 1431655765, 6};
static const ScaleNote ratio15_128 = {7680, 0, 128};
static const ScaleNote ratio2_1_1 = {131072, 0, 1};
static const ScaleNote ratio4_5_10 = {52428, 3435973836, 10};
static const ScaleNote ratio25_567 = {2889, 2552740703, 567};
static const ScaleNote ratio4_3_10 = {87381, 1431655765, 10};
static const ScaleNote ratio25_7 = {234057, 613566756, 7};
static const ScaleNote ratio7_81 = {5663, 2598190092, 81};
static const ScaleNote ratio11_32 = {22528, 0, 32};
static const ScaleNote ratio320_9 = {2330168, 3817748708, 9};
static const ScaleNote ratio3_5 = {39321, 2576980377, 5};
static const ScaleNote ratio15_2 = {491520, 0, 2};
static const ScaleNote ratio20_7 = {187245, 3067833782, 7};
static const ScaleNote ratio5_4_16 = {81920, 0, 16};
static const ScaleNote ratio32_1 = {2097152, 0, 1};
static const ScaleNote ratio7_6 = {76458, 2863311530, 6};
static const ScaleNote ratio9_56 = {10532, 2454267026, 56};
static const ScaleNote ratio17_4 = {278528, 0, 4};
static const ScaleNote ratio1_3_15 = {21845, 1431655765, 15};
static const ScaleNote ratio2_3_9 = {43690, 2863311530, 9};
static const ScaleNote ratio6_5_16 = {78643, 858993459, 16};
static const ScaleNote ratio5_4_3 = {81920, 0, 3};
static const ScaleNote ratio1_40 = {1638, 1717986918, 40};
static const ScaleNote ratio96_7 = {898779, 1840700269, 7};
static const ScaleNote ratio10_7 = {93622, 3681400539, 7};
static const ScaleNote ratio6_5_6 = {78643, 858993459, 6};
static const ScaleNote ratio2_3_8 = {43690, 2863311530, 8};
static const ScaleNote ratio5_112 = {2925, 3067833782, 112};
static const ScaleNote ratio5_1_8 = {327680, 0, 8};
static const ScaleNote ratio38_1 = {2490368, 0, 1};
static const ScaleNote ratio7_4_1 = {114688, 0, 1};
static const ScaleNote ratio5_3_7 = {109226, 2863311530, 7};
static const ScaleNote ratio5_18 = {18204, 1908874353, 18};
static const ScaleNote ratio147_25 = {385351, 2920577761, 25};
static const ScaleNote ratio15_1 = {983040, 0, 1};
static const ScaleNote ratio11_1 = {720896, 0, 1};
static const ScaleNote ratio7_5_16 = {91750, 1717986918, 16};
static const ScaleNote ratio7_243 = {1887, 3729374894, 243};
static const ScaleNote ratio17_512 = {2176, 0, 512};
static const ScaleNote ratio4_5 = {52428, 3435973836, 5};
static const ScaleNote ratio7_27 = {16990, 3499602981, 27};
static const ScaleNote ratio3_4_7 = {49152, 0, 7};
static const ScaleNote ratio1_1_6 = {65536, 0, 6};
static const ScaleNote ratio11_128 = {5632, 0, 128};
static const ScaleNote ratio17_128 = {8704, 0, 128};
static const ScaleNote ratio25_18 = {91022, 954437176, 18};
static const ScaleNote ratio11_3 = {240298, 2863311530, 3};
static const ScaleNote ratio27_16 = {110592, 0, 16};
static const ScaleNote ratio48_5 = {629145, 2576980377, 5};
static const ScaleNote ratio49_75 = {42816, 3665038759, 75};
static const ScaleNote ratio7_5 = {91750, 1717986918, 5};
static const ScaleNote ratio14_1 = {917504, 0, 1};
static const ScaleNote ratio5_1_4 = {327680, 0, 4};
static const ScaleNote ratio7_4_8 = {114688, 0, 8};
static const ScaleNote ratio5_81 = {4045, 1855850066, 81};
static const ScaleNote ratio1_3_2 = {21845, 1431655765, 2};
static const ScaleNote ratio9_16 = {36864, 0, 16};
static const ScaleNote ratio2_3_10 = {43690, 2863311530, 10};
static const ScaleNote ratio1_1_5 = {65536, 0, 5};
static const ScaleNote ratio5_4_11 = {81920, 0, 11};
static const ScaleNote ratio8_5 = {104857, 2576980377, 5};
static const ScaleNote ratio675_49 = {902791, 3593748145, 49};
static const ScaleNote ratio5_4_10 = {81920, 0, 10};
static const ScaleNote ratio1_4_4 = {16384, 0, 4};
static const ScaleNote ratio6_7 = {56173, 3067833782, 7};
static const ScaleNote ratio5_1_6 = {327680, 0, 6};
static const ScaleNote ratio1_1_16 = {65536, 0, 16};
static const ScaleNote ratio26_1 = {1703936, 0, 1};
static const ScaleNote ratio4_1_1 = {262144, 0, 1};
static const ScaleNote ratio81_5 = {1061683, 858993459, 5};
static const ScaleNote ratio25_243 = {6742, 1661427678, 243};
static const ScaleNote ratio3_14 = {14043, 1840700269, 14};
static const ScaleNote ratio1_3_9 = {21845, 1431655765, 9};
static const ScaleNote ratio12_1_2 = {786432, 0, 2};
static const ScaleNote ratio49_2025 = {1585, 3476272295, 2025};
static const ScaleNote ratio13_256 = {3328, 0, 256};
static const ScaleNote ratio16_3_16 = {349525, 1431655765, 16};
static const ScaleNote ratio12_1_16 = {786432, 0, 16};
static const ScaleNote ratio20_3 = {436906, 2863311530, 3};
static const ScaleNote ratio7_5_12 = {91750, 1717986918, 12};
static const ScaleNote ratio63_5 = {825753, 2576980377, 5};
static const ScaleNote ratio3_4_13 = {49152, 0, 13};
static const ScaleNote ratio1_32 = {2048, 0, 32};
static const ScaleNote ratio12_1_5 = {786432, 0, 5};
static const ScaleNote ratio6_5_5 = {78643, 858993459, 5};
static const ScaleNote ratio6_1_7 = {393216, 0, 7};
static const ScaleNote ratio7_4_12 = {114688, 0, 12};
static const ScaleNote ratio6_5_3 = {78643, 858993459, 3};
static const ScaleNote ratio1_9 = {7281, 3340530119, 9};
static const ScaleNote ratio5_64 = {5120, 0, 64};
static const ScaleNote ratio9_5 = {117964, 3435973836, 5};
static const ScaleNote ratio6_1_8 = {393216, 0, 8};
static const ScaleNote ratio1_3_14 = {21845, 1431655765, 14};
static const ScaleNote ratio4_1_5 = {262144, 0, 5};
static const ScaleNote ratio7_80 = {5734, 1717986918, 80};
static const ScaleNote ratio9_8_11 = {73728, 0, 11};
static const ScaleNote ratio7_5_5 = {91750, 1717986918, 5};
static const ScaleNote ratio9_80 = {7372, 3435973836, 80};
static const ScaleNote ratio128_5 = {1677721, 2576980378, 5};
static const ScaleNote ratio7_4_3 = {114688, 0, 3};
static const ScaleNote ratio7_13 = {35288, 2643056797, 13};
static const ScaleNote ratio11_17 = {42405, 2779096485, 17};
static const ScaleNote ratio5_27 = {12136, 1272582902, 27};
static const ScaleNote ratio6_5_15 = {78643, 858993459, 15};
static const ScaleNote ratio6_1_16 = {393216, 0, 16};
static const ScaleNote ratio3_32 = {6144, 0, 32};
static const ScaleNote ratio5_3_4 = {109226, 2863311530, 4};
static const ScaleNote ratio5_2_13 = {163840, 0, 13};
static const ScaleNote ratio5_7 = {46811, 1840700269, 7};
static const ScaleNote ratio2_3 = {43690, 2863311530, 3};
static const ScaleNote ratio5_2_6 = {163840, 0, 6};
static const ScaleNote ratio21_1 = {1376256, 0, 1};
static const ScaleNote ratio8_9 = {58254, 954437176, 9};
static const ScaleNote ratio9_13 = {45371, 330382099, 13};
static const ScaleNote ratio6_5_11 = {78643, 858993459, 11};
static const ScaleNote ratio9_112 = {5266, 1227133513, 112};
static const ScaleNote ratio7_128 = {3584, 0, 128};
static const ScaleNote ratio13_4 = {212992, 0, 4};
static const ScaleNote ratio3_17 = {11565, 757935405, 17};
static const ScaleNote ratio72_25 = {188743, 2920577761, 25};
static const ScaleNote ratio4_1_4 = {262144, 0, 4};
static const ScaleNote ratio4_3_2 = {87381, 1431655765, 2};
static const ScaleNote ratio3_2_4 = {98304, 0, 4};
static const ScaleNote ratio8_3_16 = {174762, 2863311530, 16};
static const ScaleNote ratio9_128 = {4608, 0, 128};
static const ScaleNote ratio5_2_10 = {163840, 0, 10};
static const ScaleNote ratio9_8 = {73728, 0, 8};
static const ScaleNote ratio17_1 = {1114112, 0, 1};
static const ScaleNote ratio9_11 = {53620, 1561806289, 11};
static const ScaleNote ratio11_5 = {144179, 858993459, 5};
static const ScaleNote ratio17_11 = {101282, 3904515723, 11};
static const ScaleNote ratio9_160 = {3686, 1717986918, 160};
static const ScaleNote ratio2_3_5 = {43690, 2863311530, 5};
static const ScaleNote ratio8_1_1 = {524288, 0, 1};
static const ScaleNote ratio2_3_11 = {43690, 2863311530, 11};
static const ScaleNote ratio7_5_15 = {91750, 1717986918, 15};
static const ScaleNote ratio1_4_6 = {16384, 0, 6};
static const ScaleNote ratio12_7 = {112347, 1840700269, 7};
static const ScaleNote ratio6_1_6 = {393216, 0, 6};
static const ScaleNote ratio9_8_9 = {73728, 0, 9};
static const ScaleNote ratio2_3_16 = {43690, 2863311530, 16};
static const ScaleNote ratio2_5 = {26214, 1717986918, 5};
static const ScaleNote ratio7_17 = {26985, 1768515945, 17};
static const ScaleNote ratio3_2_3 = {98304, 0, 3};
static const ScaleNote ratio7_160 = {2867, 858993459, 160};
static const ScaleNote ratio9_14 = {42130, 1227133513, 14};
static const ScaleNote ratio1_6 = {10922, 2863311530, 6};
static const ScaleNote ratio12_5 = {157286, 1717986918, 5};
static const ScaleNote ratio4_5_8 = {52428, 3435973836, 8};
static const ScaleNote ratio1_20 = {3276, 3435973836, 20};
static const ScaleNote ratio3_1_7 = {196608, 0, 7};
static const ScaleNote ratio6_5_4 = {78643, 858993459, 4};
static const ScaleNote ratio6_1_3 = {393216, 0, 3};
static const ScaleNote ratio5_1 = {327680, 0, 1};
static const ScaleNote ratio17_7 = {159158, 3681400539, 7};
static const ScaleNote ratio7_9 = {50972, 1908874353, 9};
static const ScaleNote ratio3_10 = {19660, 3435973836, 10};
static const ScaleNote ratio24_5 = {314572, 3435973836, 5};
static const ScaleNote ratio5_2_15 = {163840, 0, 15};
static const ScaleNote ratio3_80 = {2457, 2576980377, 80};
static const ScaleNote ratio28_1 = {1835008, 0, 1};
static const ScaleNote ratio3_4_3 = {49152, 0, 3};
static const ScaleNote ratio12_1_3 = {786432, 0, 3};
static const ScaleNote ratio9_8_15 = {73728, 0, 15};
static const ScaleNote ratio3_8 = {24576, 0, 8};
static const ScaleNote ratio9_32 = {18432, 0, 32};
static const ScaleNote ratio45_7 = {421302, 3681400539, 7};
static const ScaleNote ratio11_56 = {12873, 613566756, 56};
static const ScaleNote ratio3_11 = {17873, 1952257861, 11};
static const ScaleNote ratio6_1_5 = {393216, 0, 5};
static const ScaleNote ratio64_3 = {1398101, 1431655765, 3};
static const ScaleNote ratio1_16_16 = {4096, 0, 16};
static const ScaleNote ratio3_64 = {3072, 0, 64};
static const ScaleNote ratio7_4 = {114688, 0, 4};
static const ScaleNote ratio9_17 = {34695, 2273806215, 17};
static const ScaleNote ratio3_2_6 = {98304, 0, 6};
static const ScaleNote ratio9_10 = {58982, 1717986918, 10};
static const ScaleNote ratio5_3_13 = {109226, 2863311530, 13};
static const ScaleNote ratio189_25 = {495452, 687194767, 25};
static const ScaleNote ratio15_4 = {245760, 0, 4};
static const ScaleNote ratio7_225 = {2038, 3855926194, 225};
static const ScaleNote ratio9_64 = {9216, 0, 64};
static const ScaleNote ratio1_1_9 = {65536, 0, 9};
static const ScaleNote ratio3_1 = {196608, 0, 1};
static const ScaleNote ratio5_9 = {36408, 3817748707, 9};
static const ScaleNote ratio6_1 = {393216, 0, 1};
static const ScaleNote ratio13_3 = {283989, 1431655765, 3};
static const ScaleNote ratio2_1_3 = {131072, 0, 3};
static const ScaleNote ratio3_4_10 = {49152, 0, 10};
static const ScaleNote ratio1_4_2 = {16384, 0, 2};
static const ScaleNote ratio3_4_8 = {49152, 0, 8};
static const ScaleNote ratio5_12 = {27306, 2863311530, 12};
static const ScaleNote ratio22_1 = {1441792, 0, 1};
static const ScaleNote ratio36_5 = {471859, 858993459, 5};
static const ScaleNote ratio1_1_11 = {65536, 0, 11};
static const ScaleNote ratio1_1_14 = {65536, 0, 14};
static const ScaleNote ratio9_8_16 = {73728, 0, 16};
static const ScaleNote ratio2_1_8 = {131072, 0, 8};
static const ScaleNote ratio4_1 = {262144, 0, 1};
static const ScaleNote ratio13_1 = {851968, 0, 1};
static const ScaleNote ratio1_10 = {6553, 2576980377, 10};
static const ScaleNote ratio1_15 = {4369, 286331153, 15};
static const ScaleNote ratio9_28 = {21065, 613566756, 28};
static const ScaleNote ratio144_5 = {1887436, 3435973837, 5};
static const ScaleNote ratio7_4_11 = {114688, 0, 11};
static const ScaleNote ratio1_3_12 = {21845, 1431655765, 12};
static const ScaleNote ratio4_7 = {37449, 613566756, 7};
static const ScaleNote ratio18_1 = {1179648, 0, 1};
static const ScaleNote ratio1_27 = {2427, 1113510039, 27};
static const ScaleNote ratio27_32 = {55296, 0, 32};
static const ScaleNote ratio1_4_1 = {16384, 0, 1};
static const ScaleNote ratio17_2 = {557056, 0, 2};
static const ScaleNote ratio1_3_10 = {21845, 1431655765, 10};
static const ScaleNote ratio3_2_8 = {98304, 0, 8};
static const ScaleNote ratio225_7 = {2106514, 1227133514, 7};
static const ScaleNote ratio160_9 = {1165084, 1908874354, 9};
static const ScaleNote ratio75_49 = {100310, 876523937, 49};
static const ScaleNote ratio19_512 = {2432, 0, 512};
static const ScaleNote ratio3_13 = {15123, 2973438897, 13};
static const ScaleNote ratio16_9 = {116508, 1908874353, 9};
static const ScaleNote ratio80_9 = {582542, 954437177, 9};
static const ScaleNote ratio45_4 = {737280, 0, 4};
static const ScaleNote ratio4_5_12 = {52428, 3435973836, 12};
static const ScaleNote ratio2_1_6 = {131072, 0, 6};
static const ScaleNote ratio11_9 = {80099, 2386092942, 9};
static const ScaleNote ratio25_3 = {546133, 1431655765, 3};
static const ScaleNote ratio1_4_13 = {16384, 0, 13};
static const ScaleNote ratio3_7 = {28086, 3681400539, 7};
static const ScaleNote ratio5_189 = {1733, 3249631340, 189};
static const ScaleNote ratio22_7 = {205970, 1227133513, 7};
static const ScaleNote ratio8_1_5 = {524288, 0, 5};
static const ScaleNote ratio15_32 = {30720, 0, 32};
static const ScaleNote ratio9_8_8 = {73728, 0, 8};
static const ScaleNote ratio1_3_3 = {21845, 1431655765, 3};
static const ScaleNote ratio2_3_4 = {43690, 2863311530, 4};
static const ScaleNote ratio1_8 = {8192, 0, 8};
static const ScaleNote ratio17_256 = {4352, 0, 256};
static const ScaleNote ratio7_4_16 = {114688, 0, 16};
static const ScaleNote ratio7_5_9 = {91750, 1717986918, 9};
static const ScaleNote ratio1_1_4 = {65536, 0, 4};
static const ScaleNote ratio4_5_9 = {52428, 3435973836, 9};
static const ScaleNote ratio27_25 = {70778, 3779571220, 25};
static const ScaleNote ratio24_7 = {224694, 3681400539, 7};
static const ScaleNote ratio1_12_16 = {5461, 1431655765, 16};
static const ScaleNote ratio72_5 = {943718, 1717986918, 5};
static const ScaleNote ratio36_1 = {2359296, 0, 1};
static const ScaleNote ratio2_3_1 = {43690, 2863311530, 1};
static const ScaleNote ratio3_4_15 = {49152, 0, 15};
static const ScaleNote ratio9_25 = {23592, 4123168604, 25};
static const ScaleNote ratio5_21 = {15603, 3476878287, 21};
static const ScaleNote ratio6_5_12 = {78643, 858993459, 12};
static const ScaleNote ratio5_2_16 = {163840, 0, 16};
static const ScaleNote ratio16_3 = {349525, 1431655765, 3};
static const ScaleNote ratio1_1_2 = {65536, 0, 2};
static const ScaleNote ratio7_256 = {1792, 0, 256};
static const ScaleNote ratio5_1_5 = {327680, 0, 5};
static const ScaleNote ratio9_8_3 = {73728, 0, 3};
static const ScaleNote ratio4_3_5 = {87381, 1431655765, 5};
static const ScaleNote ratio7_5_6 = {91750, 1717986918, 6};
static const ScaleNote ratio11_7 = {102985, 613566756, 7};
static const ScaleNote ratio11_13 = {55453, 2312674697, 13};
static const ScaleNote ratio1_24 = {2730, 2863311530, 24};
static const ScaleNote ratio5_32 = {10240, 0, 32};
static const ScaleNote ratio128_9 = {932067, 2386092942, 9};
static const ScaleNote ratio10_1_6 = {655360, 0, 6};
static const ScaleNote ratio1_1_8 = {65536, 0, 8};
static const ScaleNote ratio5_4_12 = {81920, 0, 12};
static const ScaleNote ratio5_11 = {29789, 390451572, 11};
static const ScaleNote ratio40_1 = {2621440, 0, 1};
static const ScaleNote ratio25_21 = {78019, 204522252, 21};
static const ScaleNote ratio11_16 = {45056, 0, 16};
static const ScaleNote ratio40_9 = {291271, 477218588, 9};
static const ScaleNote ratio5_56 = {5851, 1840700269, 56};
static const ScaleNote ratio1_1_1 = {65536, 0, 1};
static const ScaleNote ratio96_5 = {1258291, 858993459, 5};
static const ScaleNote ratio3_4_14 = {49152, 0, 14};
static const ScaleNote ratio9_1 = {589824, 0, 1};
static const ScaleNote ratio7_4_15 = {114688, 0, 15};
static const ScaleNote ratio4_5_1 = {52428, 3435973836, 1};
static const ScaleNote ratio25_27 = {60681, 2067947216, 27};
static const ScaleNote ratio256_9 = {1864135, 477218588, 9};
static const ScaleNote ratio4_3_6 = {87381, 1431655765, 6};
static const ScaleNote ratio3_1_4 = {196608, 0, 4};
static const ScaleNote ratio3_16_16 = {12288, 0, 16};
static const ScaleNote ratio4_3_16 = {87381, 1431655765, 16};
static const ScaleNote ratio1_4_16 = {16384, 0, 16};
static const ScaleNote ratio3_2_1 = {98304, 0, 1};
static const ScaleNote ratio3_1_2 = {196608, 0, 2};
static const ScaleNote ratio3_2_7 = {98304, 0, 7};
static const ScaleNote ratio1_48 = {1365, 1431655765, 48};
static const ScaleNote ratio13_8 = {106496, 0, 8};
static const ScaleNote ratio81_7 = {758345, 613566756, 7};
static const ScaleNote ratio5_96 = {3413, 1431655765, 96};
static const ScaleNote ratio10_1_2 = {655360, 0, 2};
static const ScaleNote ratio28_5 = {367001, 2576980377, 5};
static const ScaleNote ratio3_1_5 = {196608, 0, 5};
static const ScaleNote ratio15_11 = {89367, 1171354717, 11};
static const ScaleNote ratio7_75 = {6116, 2977843991, 75};
static const ScaleNote ratio9_8_7 = {73728, 0, 7};
static const ScaleNote ratio4_1_3 = {262144, 0, 3};
static const ScaleNote ratio9_8_13 = {73728, 0, 13};
static const ScaleNote ratio3_1_6 = {196608, 0, 6};
static const ScaleNote ratio5_13 = {25206, 660764199, 13};
static const ScaleNote ratio2_1 = {131072, 0, 1};
static const ScaleNote ratio2_3_2 = {43690, 2863311530, 2};
static const ScaleNote ratio1_3_8 = {21845, 1431655765, 8};
static const ScaleNote ratio12_1_1 = {786432, 0, 1};
static const ScaleNote ratio20_1 = {1310720, 0, 1};
static const ScaleNote ratio7_135 = {3398, 699920596, 135};
static const ScaleNote ratio7_45 = {10194, 2099761789, 45};
static const ScaleNote ratio5_2_8 = {163840, 0, 8};
static const ScaleNote ratio16_1 = {1048576, 0, 1};
static const ScaleNote ratio5_4_4 = {81920, 0, 4};
static const ScaleNote ratio11_256 = {2816, 0, 256};
static const ScaleNote ratio16_5 = {209715, 858993459, 5};
static const ScaleNote ratio4_5_15 = {52428, 3435973836, 15};
static const ScaleNote ratio5_3_2 = {109226, 2863311530, 2};
static const ScaleNote ratio4_5_13 = {52428, 3435973836, 13};
static const ScaleNote ratio7_4_14 = {114688, 0, 14};
static const ScaleNote ratio17_5 = {222822, 1717986918, 5};
static const ScaleNote ratio5_2_9 = {163840, 0, 9};
static const ScaleNote ratio1_3_6 = {21845, 1431655765, 6};
static const ScaleNote ratio243_7 = {2275035, 1840700270, 7};
static const ScaleNote ratio12_1_4 = {786432, 0, 4};
static const ScaleNote ratio5_2_7 = {163840, 0, 7};
static const ScaleNote ratio7_5_3 = {91750, 1717986918, 3};
static const ScaleNote ratio5_4 = {81920, 0, 4};
static const ScaleNote ratio13_7 = {121709, 3067833782, 7};
static const ScaleNote ratio5_2_2 = {163840, 0, 2};
static const ScaleNote ratio49_675 = {4757, 1838882294, 675};
static const ScaleNote ratio2_3_13 = {43690, 2863311530, 13};
static const ScaleNote ratio7_25 = {18350, 343597383, 25};
static const ScaleNote ratio5_4_6 = {81920, 0, 6};
static const ScaleNote ratio20_9 = {145635, 2386092942, 9};
static const ScaleNote ratio5_1_1 = {327680, 0, 1};
static const ScaleNote ratio45_1 = {2949120, 0, 1};
static const ScaleNote ratio5_1_7 = {327680, 0, 7};
static const ScaleNote ratio3_4_5 = {49152, 0, 5};
static const ScaleNote ratio11_15 = {48059, 3149642683, 15};
static const ScaleNote ratio1_4_3 = {16384, 0, 3};
static const ScaleNote ratio729_25 = {1911029, 3264175145, 25};
static const ScaleNote ratio17_9 = {123790, 954437176, 9};
static const ScaleNote ratio1_3_1 = {21845, 1431655765, 1};
static const ScaleNote ratio25_189 = {8668, 3363254813, 189};
static const ScaleNote ratio13_9 = {94663, 477218588, 9};
static const ScaleNote ratio1_4_11 = {16384, 0, 11};
static const ScaleNote ratio5_63 = {5201, 1158959429, 63};
static const ScaleNote ratio3_2_15 = {98304, 0, 15};
static const ScaleNote ratio7_64 = {7168, 0, 64};
static const ScaleNote ratio3_1_3 = {196608, 0, 3};
static const ScaleNote ratio9_224 = {2633, 613566756, 224};
static const ScaleNote ratio10_1_8 = {655360, 0, 8};
static const ScaleNote ratio5_2_12 = {163840, 0, 12};
static const ScaleNote ratio9_256 = {2304, 0, 256};
static const ScaleNote ratio6_1_1 = {393216, 0, 1};
static const ScaleNote ratio7_32 = {14336, 0, 32};
static const ScaleNote ratio7_10 = {45875, 858993459, 10};
static const ScaleNote ratio13_17 = {50115, 3284386755, 17};
static const ScaleNote ratio11_14 = {51492, 2454267026, 14};
static const ScaleNote ratio1_11 = {5957, 3514064151, 11};
static const ScaleNote ratio8_7 = {74898, 1227133513, 7};
static const ScaleNote ratio2025_49 = {2708375, 2191309844, 49};
static const ScaleNote ratio4_9 = {29127, 477218588, 9};
static const ScaleNote ratio5_4_5 = {81920, 0, 5};
static const ScaleNote ratio1_3 = {21845, 1431655765, 3};
static const ScaleNote ratio5_3_1 = {109226, 2863311530, 1};
static const ScaleNote ratio5_3_14 = {109226, 2863311530, 14};
static const ScaleNote ratio6_1_4 = {393216, 0, 4};
static const ScaleNote ratio4_5_11 = {52428, 3435973836, 11};
static const ScaleNote ratio1_4 = {16384, 0, 4};
static const ScaleNote ratio27_128 = {13824, 0, 128};
static const ScaleNote ratio10_9 = {72817, 3340530119, 9};
static const ScaleNote ratio13_32 = {26624, 0, 32};
static const ScaleNote ratio56_5 = {734003, 858993459, 5};
static const ScaleNote ratio7_16 = {28672, 0, 16};
static const ScaleNote ratio5_2_4 = {163840, 0, 4};
static const ScaleNote ratio2_1_16 = {131072, 0, 16};
static const ScaleNote ratio24_1 = {1572864, 0, 1};
static const ScaleNote ratio80_7 = {748982, 3681400539, 7};
static const ScaleNote ratio15_256 = {3840, 0, 256};
static const ScaleNote ratio3_1_8 = {196608, 0, 8};
static const ScaleNote ratio6_5_13 = {78643, 858993459, 13};
static const ScaleNote ratio10_1_4 = {655360, 0, 4};
static const ScaleNote ratio19_4 = {311296, 0, 4};
static const ScaleNote ratio5_1_3 = {327680, 0, 3};
static const ScaleNote ratio1_3_13 = {21845, 1431655765, 13};
static const ScaleNote ratio3_25 = {7864, 1374389534, 25};
static const ScaleNote ratio6_5_1 = {78643, 858993459, 1};
static const ScaleNote ratio1_8_16 = {8192, 0, 16};
static const ScaleNote ratio1_1 = {65536, 0, 1};



static const ScaleNote * const integerRatios1[128] = {&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, 
&ratio1_1, &ratio1_1, &ratio1_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, 
&ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, 
&ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio4_1, 
&ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, 
&ratio4_1, &ratio4_1, &ratio4_1, &ratio5_1, &ratio5_1, &ratio5_1, &ratio5_1, &ratio5_1, &ratio5_1, &ratio5_1, &ratio5_1, &ratio5_1, 
&ratio5_1, &ratio5_1, &ratio5_1, &ratio5_1, &ratio5_1, &ratio5_1, &ratio5_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, 
&ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio7_1, 
&ratio7_1, &ratio7_1, &ratio7_1, &ratio7_1, &ratio7_1, &ratio7_1, &ratio7_1, &ratio7_1, &ratio7_1, &ratio7_1, &ratio7_1, &ratio7_1, 
&ratio7_1, &ratio7_1, &ratio7_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, 
&ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1}; 

static const ScaleNote * const integerRatios2[128] = {&ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, 
&ratio1_2, &ratio1_2, &ratio1_2, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, 
&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, 
&ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio2_1, 
&ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, 
&ratio2_1, &ratio2_1, &ratio2_1, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, 
&ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, 
&ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio7_2, 
&ratio7_2, &ratio7_2, &ratio7_2, &ratio7_2, &ratio7_2, &ratio7_2, &ratio7_2, &ratio7_2, &ratio7_2, &ratio7_2, &ratio7_2, &ratio7_2, 
&ratio7_2, &ratio7_2, &ratio7_2, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, 
&ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1}; 

static const ScaleNote * const integerRatios3[128] = {&ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, 
&ratio1_3, &ratio1_3, &ratio1_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, 
&ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, 
&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio4_3, 
&ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, 
&ratio4_3, &ratio4_3, &ratio4_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, 
&ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, 
&ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio7_3, 
&ratio7_3, &ratio7_3, &ratio7_3, &ratio7_3, &ratio7_3, &ratio7_3, &ratio7_3, &ratio7_3, &ratio7_3, &ratio7_3, &ratio7_3, &ratio7_3, 
&ratio7_3, &ratio7_3, &ratio7_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, 
&ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3}; 

static const ScaleNote * const integerRatios4[128] = {&ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, 
&ratio1_4, &ratio1_4, &ratio1_4, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, 
&ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio3_4, &ratio3_4, &ratio3_4, &ratio3_4, &ratio3_4, 
&ratio3_4, &ratio3_4, &ratio3_4, &ratio3_4, &ratio3_4, &ratio3_4, &ratio3_4, &ratio3_4, &ratio3_4, &ratio3_4, &ratio3_4, &ratio1_1, 
&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, 
&ratio1_1, &ratio1_1, &ratio1_1, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, 
&ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, 
&ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio7_4, 
&ratio7_4, &ratio7_4, &ratio7_4, &ratio7_4, &ratio7_4, &ratio7_4, &ratio7_4, &ratio7_4, &ratio7_4, &ratio7_4, &ratio7_4, &ratio7_4, 
&ratio7_4, &ratio7_4, &ratio7_4, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, 
&ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1}; 

static const ScaleNote * const integerRatios5[128] = {&ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, 
&ratio1_5, &ratio1_5, &ratio1_5, &ratio2_5, &ratio2_5, &ratio2_5, &ratio2_5, &ratio2_5, &ratio2_5, &ratio2_5, &ratio2_5, &ratio2_5, 
&ratio2_5, &ratio2_5, &ratio2_5, &ratio2_5, &ratio2_5, &ratio2_5, &ratio2_5, &ratio3_5, &ratio3_5, &ratio3_5, &ratio3_5, &ratio3_5, 
&ratio3_5, &ratio3_5, &ratio3_5, &ratio3_5, &ratio3_5, &ratio3_5, &ratio3_5, &ratio3_5, &ratio3_5, &ratio3_5, &ratio3_5, &ratio4_5, 
&ratio4_5, &ratio4_5, &ratio4_5, &ratio4_5, &ratio4_5, &ratio4_5, &ratio4_5, &ratio4_5, &ratio4_5, &ratio4_5, &ratio4_5, &ratio4_5, 
&ratio4_5, &ratio4_5, &ratio4_5, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, 
&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, 
&ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio7_5, 
&ratio7_5, &ratio7_5, &ratio7_5, &ratio7_5, &ratio7_5, &ratio7_5, &ratio7_5, &ratio7_5, &ratio7_5, &ratio7_5, &ratio7_5, &ratio7_5, 
&ratio7_5, &ratio7_5, &ratio7_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, 
&ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5}; 

static const ScaleNote * const integerRatios6[128] = {&ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, 
&ratio1_6, &ratio1_6, &ratio1_6, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, 
&ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, 
&ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio2_3, 
&ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, 
&ratio2_3, &ratio2_3, &ratio2_3, &ratio5_6, &ratio5_6, &ratio5_6, &ratio5_6, &ratio5_6, &ratio5_6, &ratio5_6, &ratio5_6, &ratio5_6, 
&ratio5_6, &ratio5_6, &ratio5_6, &ratio5_6, &ratio5_6, &ratio5_6, &ratio5_6, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, 
&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio7_6, 
&ratio7_6, &ratio7_6, &ratio7_6, &ratio7_6, &ratio7_6, &ratio7_6, &ratio7_6, &ratio7_6, &ratio7_6, &ratio7_6, &ratio7_6, &ratio7_6, 
&ratio7_6, &ratio7_6, &ratio7_6, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, 
&ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3}; 

static const ScaleNote * const integerRatios7[128] = {&ratio1_7, &ratio1_7, &ratio1_7, &ratio1_7, &ratio1_7, &ratio1_7, &ratio1_7, &ratio1_7, &ratio1_7, &ratio1_7, &ratio1_7, &ratio1_7, &ratio1_7, 
&ratio1_7, &ratio1_7, &ratio1_7, &ratio2_7, &ratio2_7, &ratio2_7, &ratio2_7, &ratio2_7, &ratio2_7, &ratio2_7, &ratio2_7, &ratio2_7, 
&ratio2_7, &ratio2_7, &ratio2_7, &ratio2_7, &ratio2_7, &ratio2_7, &ratio2_7, &ratio3_7, &ratio3_7, &ratio3_7, &ratio3_7, &ratio3_7, 
&ratio3_7, &ratio3_7, &ratio3_7, &ratio3_7, &ratio3_7, &ratio3_7, &ratio3_7, &ratio3_7, &ratio3_7, &ratio3_7, &ratio3_7, &ratio4_7, 
&ratio4_7, &ratio4_7, &ratio4_7, &ratio4_7, &ratio4_7, &ratio4_7, &ratio4_7, &ratio4_7, &ratio4_7, &ratio4_7, &ratio4_7, &ratio4_7, 
&ratio4_7, &ratio4_7, &ratio4_7, &ratio5_7, &ratio5_7, &ratio5_7, &ratio5_7, &ratio5_7, &ratio5_7, &ratio5_7, &ratio5_7, &ratio5_7, 
&ratio5_7, &ratio5_7, &ratio5_7, &ratio5_7, &ratio5_7, &ratio5_7, &ratio5_7, &ratio6_7, &ratio6_7, &ratio6_7, &ratio6_7, &ratio6_7, 
&ratio6_7, &ratio6_7, &ratio6_7, &ratio6_7, &ratio6_7, &ratio6_7, &ratio6_7, &ratio6_7, &ratio6_7, &ratio6_7, &ratio6_7, &ratio1_1, 
&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, 
&ratio1_1, &ratio1_1, &ratio1_1, &ratio8_7, &ratio8_7, &ratio8_7, &ratio8_7, &ratio8_7, &ratio8_7, &ratio8_7, &ratio8_7, &ratio8_7, 
&ratio8_7, &ratio8_7, &ratio8_7, &ratio8_7, &ratio8_7, &ratio8_7, &ratio8_7}; 

static const ScaleNote * const integerRatios8[128] = {&ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, 
&ratio1_8, &ratio1_8, &ratio1_8, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, 
&ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio3_8, &ratio3_8, &ratio3_8, &ratio3_8, &ratio3_8, 
&ratio3_8, &ratio3_8, &ratio3_8, &ratio3_8, &ratio3_8, &ratio3_8, &ratio3_8, &ratio3_8, &ratio3_8, &ratio3_8, &ratio3_8, &ratio1_2, 
&ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, 
&ratio1_2, &ratio1_2, &ratio1_2, &ratio5_8, &ratio5_8, &ratio5_8, &ratio5_8, &ratio5_8, &ratio5_8, &ratio5_8, &ratio5_8, &ratio5_8, 
&ratio5_8, &ratio5_8, &ratio5_8, &ratio5_8, &ratio5_8, &ratio5_8, &ratio5_8, &ratio3_4, &ratio3_4, &ratio3_4, &ratio3_4, &ratio3_4, 
&ratio3_4, &ratio3_4, &ratio3_4, &ratio3_4, &ratio3_4, &ratio3_4, &ratio3_4, &ratio3_4, &ratio3_4, &ratio3_4, &ratio3_4, &ratio7_8, 
&ratio7_8, &ratio7_8, &ratio7_8, &ratio7_8, &ratio7_8, &ratio7_8, &ratio7_8, &ratio7_8, &ratio7_8, &ratio7_8, &ratio7_8, &ratio7_8, 
&ratio7_8, &ratio7_8, &ratio7_8, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, 
&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1}; 



static const ScaleNote * const even_integers0[128] = {&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, 
&ratio1_1, &ratio1_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, 
&ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, 
&ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, 
&ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, 
&ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio10_1, 
&ratio10_1, &ratio10_1, &ratio10_1, &ratio10_1, &ratio10_1, &ratio10_1, &ratio10_1, &ratio10_1, &ratio10_1, &ratio10_1, &ratio10_1, &ratio10_1, 
&ratio10_1, &ratio12_1, &ratio12_1, &ratio12_1, &ratio12_1, &ratio12_1, &ratio12_1, &ratio12_1, &ratio12_1, &ratio12_1, &ratio12_1, &ratio12_1, 
&ratio12_1, &ratio12_1, &ratio12_1, &ratio14_1, &ratio14_1, &ratio14_1, &ratio14_1, &ratio14_1, &ratio14_1, &ratio14_1, &ratio14_1, &ratio14_1, 
&ratio14_1, &ratio14_1, &ratio14_1, &ratio14_1, &ratio14_1, &ratio16_1, &ratio16_1, &ratio16_1, &ratio16_1, &ratio16_1, &ratio16_1, &ratio16_1, 
&ratio16_1, &ratio16_1, &ratio16_1, &ratio16_1, &ratio16_1, &ratio16_1, &ratio16_1}; 

static const ScaleNote * const even_integers1[128] = {&ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, 
&ratio1_2, &ratio1_2, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, 
&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, 
&ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, 
&ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, 
&ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio5_1, 
&ratio5_1, &ratio5_1, &ratio5_1, &ratio5_1, &ratio5_1, &ratio5_1, &ratio5_1, &ratio5_1, &ratio5_1, &ratio5_1, &ratio5_1, &ratio5_1, 
&ratio5_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, 
&ratio6_1, &ratio6_1, &ratio6_1, &ratio7_1, &ratio7_1, &ratio7_1, &ratio7_1, &ratio7_1, &ratio7_1, &ratio7_1, &ratio7_1, &ratio7_1, 
&ratio7_1, &ratio7_1, &ratio7_1, &ratio7_1, &ratio7_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, 
&ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1}; 

static const ScaleNote * const even_integers2[128] = {&ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, 
&ratio1_4, &ratio1_4, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, 
&ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, 
&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, 
&ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, 
&ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio5_2, 
&ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, 
&ratio5_2, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, 
&ratio3_1, &ratio3_1, &ratio3_1, &ratio7_2, &ratio7_2, &ratio7_2, &ratio7_2, &ratio7_2, &ratio7_2, &ratio7_2, &ratio7_2, &ratio7_2, 
&ratio7_2, &ratio7_2, &ratio7_2, &ratio7_2, &ratio7_2, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, 
&ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1}; 

static const ScaleNote * const even_integers3[128] = {&ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, 
&ratio1_6, &ratio1_6, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, 
&ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, 
&ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, 
&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, 
&ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio5_3, 
&ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, 
&ratio5_3, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, 
&ratio2_1, &ratio2_1, &ratio2_1, &ratio7_3, &ratio7_3, &ratio7_3, &ratio7_3, &ratio7_3, &ratio7_3, &ratio7_3, &ratio7_3, &ratio7_3, 
&ratio7_3, &ratio7_3, &ratio7_3, &ratio7_3, &ratio7_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, 
&ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3}; 

static const ScaleNote * const even_integers4[128] = {&ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, 
&ratio1_8, &ratio1_8, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, 
&ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, 
&ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio3_4, &ratio3_4, &ratio3_4, &ratio3_4, &ratio3_4, &ratio3_4, 
&ratio3_4, &ratio3_4, &ratio3_4, &ratio3_4, &ratio3_4, &ratio3_4, &ratio3_4, &ratio3_4, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, 
&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio5_4, 
&ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, 
&ratio5_4, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, 
&ratio3_2, &ratio3_2, &ratio3_2, &ratio7_4, &ratio7_4, &ratio7_4, &ratio7_4, &ratio7_4, &ratio7_4, &ratio7_4, &ratio7_4, &ratio7_4, 
&ratio7_4, &ratio7_4, &ratio7_4, &ratio7_4, &ratio7_4, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, 
&ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1}; 

static const ScaleNote * const even_integers5[128] = {&ratio1_10, &ratio1_10, &ratio1_10, &ratio1_10, &ratio1_10, &ratio1_10, &ratio1_10, &ratio1_10, &ratio1_10, &ratio1_10, &ratio1_10, &ratio1_10, &ratio1_10, 
&ratio1_10, &ratio1_10, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, 
&ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio2_5, &ratio2_5, &ratio2_5, &ratio2_5, &ratio2_5, &ratio2_5, &ratio2_5, &ratio2_5, 
&ratio2_5, &ratio2_5, &ratio2_5, &ratio2_5, &ratio2_5, &ratio2_5, &ratio3_5, &ratio3_5, &ratio3_5, &ratio3_5, &ratio3_5, &ratio3_5, 
&ratio3_5, &ratio3_5, &ratio3_5, &ratio3_5, &ratio3_5, &ratio3_5, &ratio3_5, &ratio3_5, &ratio4_5, &ratio4_5, &ratio4_5, &ratio4_5, 
&ratio4_5, &ratio4_5, &ratio4_5, &ratio4_5, &ratio4_5, &ratio4_5, &ratio4_5, &ratio4_5, &ratio4_5, &ratio4_5, &ratio4_5, &ratio1_1, 
&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, 
&ratio1_1, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, 
&ratio6_5, &ratio6_5, &ratio6_5, &ratio7_5, &ratio7_5, &ratio7_5, &ratio7_5, &ratio7_5, &ratio7_5, &ratio7_5, &ratio7_5, &ratio7_5, 
&ratio7_5, &ratio7_5, &ratio7_5, &ratio7_5, &ratio7_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, 
&ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5}; 

static const ScaleNote * const even_integers6[128] = {&ratio1_12, &ratio1_12, &ratio1_12, &ratio1_12, &ratio1_12, &ratio1_12, &ratio1_12, &ratio1_12, &ratio1_12, &ratio1_12, &ratio1_12, &ratio1_12, &ratio1_12, 
&ratio1_12, &ratio1_12, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, 
&ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, 
&ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, 
&ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, 
&ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio5_6, 
&ratio5_6, &ratio5_6, &ratio5_6, &ratio5_6, &ratio5_6, &ratio5_6, &ratio5_6, &ratio5_6, &ratio5_6, &ratio5_6, &ratio5_6, &ratio5_6, 
&ratio5_6, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, 
&ratio1_1, &ratio1_1, &ratio1_1, &ratio7_6, &ratio7_6, &ratio7_6, &ratio7_6, &ratio7_6, &ratio7_6, &ratio7_6, &ratio7_6, &ratio7_6, 
&ratio7_6, &ratio7_6, &ratio7_6, &ratio7_6, &ratio7_6, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, 
&ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3}; 

static const ScaleNote * const even_integers7[128] = {&ratio1_14, &ratio1_14, &ratio1_14, &ratio1_14, &ratio1_14, &ratio1_14, &ratio1_14, &ratio1_14, &ratio1_14, &ratio1_14, &ratio1_14, &ratio1_14, &ratio1_14, 
&ratio1_14, &ratio1_14, &ratio1_7, &ratio1_7, &ratio1_7, &ratio1_7, &ratio1_7, &ratio1_7, &ratio1_7, &ratio1_7, &ratio1_7, &ratio1_7, 
&ratio1_7, &ratio1_7, &ratio1_7, &ratio1_7, &ratio2_7, &ratio2_7, &ratio2_7, &ratio2_7, &ratio2_7, &ratio2_7, &ratio2_7, &ratio2_7, 
&ratio2_7, &ratio2_7, &ratio2_7, &ratio2_7, &ratio2_7, &ratio2_7, &ratio3_7, &ratio3_7, &ratio3_7, &ratio3_7, &ratio3_7, &ratio3_7, 
&ratio3_7, &ratio3_7, &ratio3_7, &ratio3_7, &ratio3_7, &ratio3_7, &ratio3_7, &ratio3_7, &ratio4_7, &ratio4_7, &ratio4_7, &ratio4_7, 
&ratio4_7, &ratio4_7, &ratio4_7, &ratio4_7, &ratio4_7, &ratio4_7, &ratio4_7, &ratio4_7, &ratio4_7, &ratio4_7, &ratio4_7, &ratio5_7, 
&ratio5_7, &ratio5_7, &ratio5_7, &ratio5_7, &ratio5_7, &ratio5_7, &ratio5_7, &ratio5_7, &ratio5_7, &ratio5_7, &ratio5_7, &ratio5_7, 
&ratio5_7, &ratio6_7, &ratio6_7, &ratio6_7, &ratio6_7, &ratio6_7, &ratio6_7, &ratio6_7, &ratio6_7, &ratio6_7, &ratio6_7, &ratio6_7, 
&ratio6_7, &ratio6_7, &ratio6_7, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, 
&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio8_7, &ratio8_7, &ratio8_7, &ratio8_7, &ratio8_7, &ratio8_7, &ratio8_7, 
&ratio8_7, &ratio8_7, &ratio8_7, &ratio8_7, &ratio8_7, &ratio8_7, &ratio8_7}; 

static const ScaleNote * const even_integers8[128] = {&ratio1_16, &ratio1_16, &ratio1_16, &ratio1_16, &ratio1_16, &ratio1_16, &ratio1_16, &ratio1_16, &ratio1_16, &ratio1_16, &ratio1_16, &ratio1_16, &ratio1_16, 
&ratio1_16, &ratio1_16, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, 
&ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, 
&ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio3_8, &ratio3_8, &ratio3_8, &ratio3_8, &ratio3_8, &ratio3_8, 
&ratio3_8, &ratio3_8, &ratio3_8, &ratio3_8, &ratio3_8, &ratio3_8, &ratio3_8, &ratio3_8, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, 
&ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio5_8, 
&ratio5_8, &ratio5_8, &ratio5_8, &ratio5_8, &ratio5_8, &ratio5_8, &ratio5_8, &ratio5_8, &ratio5_8, &ratio5_8, &ratio5_8, &ratio5_8, 
&ratio5_8, &ratio3_4, &ratio3_4, &ratio3_4, &ratio3_4, &ratio3_4, &ratio3_4, &ratio3_4, &ratio3_4, &ratio3_4, &ratio3_4, &ratio3_4, 
&ratio3_4, &ratio3_4, &ratio3_4, &ratio7_8, &ratio7_8, &ratio7_8, &ratio7_8, &ratio7_8, &ratio7_8, &ratio7_8, &ratio7_8, &ratio7_8, 
&ratio7_8, &ratio7_8, &ratio7_8, &ratio7_8, &ratio7_8, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, 
&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1}; 



static const ScaleNote * const rhythm_integers0[128] = {&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, 
&ratio1_1, &ratio1_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, 
&ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, 
&ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, 
&ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, 
&ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio9_1, 
&ratio9_1, &ratio9_1, &ratio9_1, &ratio9_1, &ratio9_1, &ratio9_1, &ratio9_1, &ratio9_1, &ratio9_1, &ratio9_1, &ratio9_1, &ratio9_1, 
&ratio9_1, &ratio12_1, &ratio12_1, &ratio12_1, &ratio12_1, &ratio12_1, &ratio12_1, &ratio12_1, &ratio12_1, &ratio12_1, &ratio12_1, &ratio12_1, 
&ratio12_1, &ratio12_1, &ratio12_1, &ratio16_1, &ratio16_1, &ratio16_1, &ratio16_1, &ratio16_1, &ratio16_1, &ratio16_1, &ratio16_1, &ratio16_1, 
&ratio16_1, &ratio16_1, &ratio16_1, &ratio16_1, &ratio16_1, &ratio24_1, &ratio24_1, &ratio24_1, &ratio24_1, &ratio24_1, &ratio24_1, &ratio24_1, 
&ratio24_1, &ratio24_1, &ratio24_1, &ratio24_1, &ratio24_1, &ratio24_1, &ratio24_1}; 

static const ScaleNote * const rhythm_integers1[128] = {&ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, 
&ratio1_2, &ratio1_2, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, 
&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, 
&ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, 
&ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, 
&ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio9_2, 
&ratio9_2, &ratio9_2, &ratio9_2, &ratio9_2, &ratio9_2, &ratio9_2, &ratio9_2, &ratio9_2, &ratio9_2, &ratio9_2, &ratio9_2, &ratio9_2, 
&ratio9_2, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, 
&ratio6_1, &ratio6_1, &ratio6_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, 
&ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio12_1, &ratio12_1, &ratio12_1, &ratio12_1, &ratio12_1, &ratio12_1, &ratio12_1, 
&ratio12_1, &ratio12_1, &ratio12_1, &ratio12_1, &ratio12_1, &ratio12_1, &ratio12_1}; 

static const ScaleNote * const rhythm_integers2[128] = {&ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, 
&ratio1_3, &ratio1_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, 
&ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, 
&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, 
&ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, 
&ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio3_1, 
&ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, 
&ratio3_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, 
&ratio4_1, &ratio4_1, &ratio4_1, &ratio16_3, &ratio16_3, &ratio16_3, &ratio16_3, &ratio16_3, &ratio16_3, &ratio16_3, &ratio16_3, &ratio16_3, 
&ratio16_3, &ratio16_3, &ratio16_3, &ratio16_3, &ratio16_3, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, 
&ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1}; 

static const ScaleNote * const rhythm_integers3[128] = {&ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, 
&ratio1_4, &ratio1_4, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, 
&ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio3_4, &ratio3_4, &ratio3_4, &ratio3_4, &ratio3_4, &ratio3_4, &ratio3_4, &ratio3_4, 
&ratio3_4, &ratio3_4, &ratio3_4, &ratio3_4, &ratio3_4, &ratio3_4, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, 
&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, 
&ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio9_4, 
&ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, 
&ratio9_4, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, 
&ratio3_1, &ratio3_1, &ratio3_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, 
&ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, 
&ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1}; 

static const ScaleNote * const rhythm_integers4[128] = {&ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, 
&ratio1_6, &ratio1_6, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, 
&ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, 
&ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, 
&ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, 
&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio3_2, 
&ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, 
&ratio3_2, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, 
&ratio2_1, &ratio2_1, &ratio2_1, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, 
&ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, 
&ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1}; 

static const ScaleNote * const rhythm_integers5[128] = {&ratio1_9, &ratio1_9, &ratio1_9, &ratio1_9, &ratio1_9, &ratio1_9, &ratio1_9, &ratio1_9, &ratio1_9, &ratio1_9, &ratio1_9, &ratio1_9, &ratio1_9, 
&ratio1_9, &ratio1_9, &ratio2_9, &ratio2_9, &ratio2_9, &ratio2_9, &ratio2_9, &ratio2_9, &ratio2_9, &ratio2_9, &ratio2_9, &ratio2_9, 
&ratio2_9, &ratio2_9, &ratio2_9, &ratio2_9, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, 
&ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio4_9, &ratio4_9, &ratio4_9, &ratio4_9, &ratio4_9, &ratio4_9, 
&ratio4_9, &ratio4_9, &ratio4_9, &ratio4_9, &ratio4_9, &ratio4_9, &ratio4_9, &ratio4_9, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, 
&ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio1_1, 
&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, 
&ratio1_1, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, 
&ratio4_3, &ratio4_3, &ratio4_3, &ratio16_9, &ratio16_9, &ratio16_9, &ratio16_9, &ratio16_9, &ratio16_9, &ratio16_9, &ratio16_9, &ratio16_9, 
&ratio16_9, &ratio16_9, &ratio16_9, &ratio16_9, &ratio16_9, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, 
&ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3}; 

static const ScaleNote * const rhythm_integers6[128] = {&ratio1_12, &ratio1_12, &ratio1_12, &ratio1_12, &ratio1_12, &ratio1_12, &ratio1_12, &ratio1_12, &ratio1_12, &ratio1_12, &ratio1_12, &ratio1_12, &ratio1_12, 
&ratio1_12, &ratio1_12, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, 
&ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, 
&ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, 
&ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, 
&ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio3_4, 
&ratio3_4, &ratio3_4, &ratio3_4, &ratio3_4, &ratio3_4, &ratio3_4, &ratio3_4, &ratio3_4, &ratio3_4, &ratio3_4, &ratio3_4, &ratio3_4, 
&ratio3_4, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, 
&ratio1_1, &ratio1_1, &ratio1_1, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, 
&ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, 
&ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1}; 

static const ScaleNote * const rhythm_integers7[128] = {&ratio1_16, &ratio1_16, &ratio1_16, &ratio1_16, &ratio1_16, &ratio1_16, &ratio1_16, &ratio1_16, &ratio1_16, &ratio1_16, &ratio1_16, &ratio1_16, &ratio1_16, 
&ratio1_16, &ratio1_16, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, 
&ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio3_16, &ratio3_16, &ratio3_16, &ratio3_16, &ratio3_16, &ratio3_16, &ratio3_16, &ratio3_16, 
&ratio3_16, &ratio3_16, &ratio3_16, &ratio3_16, &ratio3_16, &ratio3_16, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, 
&ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio3_8, &ratio3_8, &ratio3_8, &ratio3_8, 
&ratio3_8, &ratio3_8, &ratio3_8, &ratio3_8, &ratio3_8, &ratio3_8, &ratio3_8, &ratio3_8, &ratio3_8, &ratio3_8, &ratio3_8, &ratio9_16, 
&ratio9_16, &ratio9_16, &ratio9_16, &ratio9_16, &ratio9_16, &ratio9_16, &ratio9_16, &ratio9_16, &ratio9_16, &ratio9_16, &ratio9_16, &ratio9_16, 
&ratio9_16, &ratio3_4, &ratio3_4, &ratio3_4, &ratio3_4, &ratio3_4, &ratio3_4, &ratio3_4, &ratio3_4, &ratio3_4, &ratio3_4, &ratio3_4, 
&ratio3_4, &ratio3_4, &ratio3_4, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, 
&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, 
&ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2}; 

static const ScaleNote * const rhythm_integers8[128] = {&ratio1_24, &ratio1_24, &ratio1_24, &ratio1_24, &ratio1_24, &ratio1_24, &ratio1_24, &ratio1_24, &ratio1_24, &ratio1_24, &ratio1_24, &ratio1_24, &ratio1_24, 
&ratio1_24, &ratio1_24, &ratio1_12, &ratio1_12, &ratio1_12, &ratio1_12, &ratio1_12, &ratio1_12, &ratio1_12, &ratio1_12, &ratio1_12, &ratio1_12, 
&ratio1_12, &ratio1_12, &ratio1_12, &ratio1_12, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, 
&ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, 
&ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, 
&ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio3_8, 
&ratio3_8, &ratio3_8, &ratio3_8, &ratio3_8, &ratio3_8, &ratio3_8, &ratio3_8, &ratio3_8, &ratio3_8, &ratio3_8, &ratio3_8, &ratio3_8, 
&ratio3_8, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, 
&ratio1_2, &ratio1_2, &ratio1_2, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, 
&ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, 
&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1}; 



static const ScaleNote * const odd_integers0[128] = {&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, 
&ratio1_1, &ratio1_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, 
&ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio5_1, &ratio5_1, &ratio5_1, &ratio5_1, &ratio5_1, &ratio5_1, &ratio5_1, &ratio5_1, 
&ratio5_1, &ratio5_1, &ratio5_1, &ratio5_1, &ratio5_1, &ratio5_1, &ratio7_1, &ratio7_1, &ratio7_1, &ratio7_1, &ratio7_1, &ratio7_1, 
&ratio7_1, &ratio7_1, &ratio7_1, &ratio7_1, &ratio7_1, &ratio7_1, &ratio7_1, &ratio7_1, &ratio9_1, &ratio9_1, &ratio9_1, &ratio9_1, 
&ratio9_1, &ratio9_1, &ratio9_1, &ratio9_1, &ratio9_1, &ratio9_1, &ratio9_1, &ratio9_1, &ratio9_1, &ratio9_1, &ratio9_1, &ratio11_1, 
&ratio11_1, &ratio11_1, &ratio11_1, &ratio11_1, &ratio11_1, &ratio11_1, &ratio11_1, &ratio11_1, &ratio11_1, &ratio11_1, &ratio11_1, &ratio11_1, 
&ratio11_1, &ratio13_1, &ratio13_1, &ratio13_1, &ratio13_1, &ratio13_1, &ratio13_1, &ratio13_1, &ratio13_1, &ratio13_1, &ratio13_1, &ratio13_1, 
&ratio13_1, &ratio13_1, &ratio13_1, &ratio15_1, &ratio15_1, &ratio15_1, &ratio15_1, &ratio15_1, &ratio15_1, &ratio15_1, &ratio15_1, &ratio15_1, 
&ratio15_1, &ratio15_1, &ratio15_1, &ratio15_1, &ratio15_1, &ratio17_1, &ratio17_1, &ratio17_1, &ratio17_1, &ratio17_1, &ratio17_1, &ratio17_1, 
&ratio17_1, &ratio17_1, &ratio17_1, &ratio17_1, &ratio17_1, &ratio17_1, &ratio17_1}; 

static const ScaleNote * const odd_integers1[128] = {&ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, 
&ratio1_3, &ratio1_3, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, 
&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, 
&ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio7_3, &ratio7_3, &ratio7_3, &ratio7_3, &ratio7_3, &ratio7_3, 
&ratio7_3, &ratio7_3, &ratio7_3, &ratio7_3, &ratio7_3, &ratio7_3, &ratio7_3, &ratio7_3, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, 
&ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio11_3, 
&ratio11_3, &ratio11_3, &ratio11_3, &ratio11_3, &ratio11_3, &ratio11_3, &ratio11_3, &ratio11_3, &ratio11_3, &ratio11_3, &ratio11_3, &ratio11_3, 
&ratio11_3, &ratio13_3, &ratio13_3, &ratio13_3, &ratio13_3, &ratio13_3, &ratio13_3, &ratio13_3, &ratio13_3, &ratio13_3, &ratio13_3, &ratio13_3, 
&ratio13_3, &ratio13_3, &ratio13_3, &ratio5_1, &ratio5_1, &ratio5_1, &ratio5_1, &ratio5_1, &ratio5_1, &ratio5_1, &ratio5_1, &ratio5_1, 
&ratio5_1, &ratio5_1, &ratio5_1, &ratio5_1, &ratio5_1, &ratio17_3, &ratio17_3, &ratio17_3, &ratio17_3, &ratio17_3, &ratio17_3, &ratio17_3, 
&ratio17_3, &ratio17_3, &ratio17_3, &ratio17_3, &ratio17_3, &ratio17_3, &ratio17_3}; 

static const ScaleNote * const odd_integers2[128] = {&ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, 
&ratio1_5, &ratio1_5, &ratio3_5, &ratio3_5, &ratio3_5, &ratio3_5, &ratio3_5, &ratio3_5, &ratio3_5, &ratio3_5, &ratio3_5, &ratio3_5, 
&ratio3_5, &ratio3_5, &ratio3_5, &ratio3_5, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, 
&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio7_5, &ratio7_5, &ratio7_5, &ratio7_5, &ratio7_5, &ratio7_5, 
&ratio7_5, &ratio7_5, &ratio7_5, &ratio7_5, &ratio7_5, &ratio7_5, &ratio7_5, &ratio7_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, 
&ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio11_5, 
&ratio11_5, &ratio11_5, &ratio11_5, &ratio11_5, &ratio11_5, &ratio11_5, &ratio11_5, &ratio11_5, &ratio11_5, &ratio11_5, &ratio11_5, &ratio11_5, 
&ratio11_5, &ratio13_5, &ratio13_5, &ratio13_5, &ratio13_5, &ratio13_5, &ratio13_5, &ratio13_5, &ratio13_5, &ratio13_5, &ratio13_5, &ratio13_5, 
&ratio13_5, &ratio13_5, &ratio13_5, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, 
&ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio17_5, &ratio17_5, &ratio17_5, &ratio17_5, &ratio17_5, &ratio17_5, &ratio17_5, 
&ratio17_5, &ratio17_5, &ratio17_5, &ratio17_5, &ratio17_5, &ratio17_5, &ratio17_5}; 

static const ScaleNote * const odd_integers3[128] = {&ratio1_7, &ratio1_7, &ratio1_7, &ratio1_7, &ratio1_7, &ratio1_7, &ratio1_7, &ratio1_7, &ratio1_7, &ratio1_7, &ratio1_7, &ratio1_7, &ratio1_7, 
&ratio1_7, &ratio1_7, &ratio3_7, &ratio3_7, &ratio3_7, &ratio3_7, &ratio3_7, &ratio3_7, &ratio3_7, &ratio3_7, &ratio3_7, &ratio3_7, 
&ratio3_7, &ratio3_7, &ratio3_7, &ratio3_7, &ratio5_7, &ratio5_7, &ratio5_7, &ratio5_7, &ratio5_7, &ratio5_7, &ratio5_7, &ratio5_7, 
&ratio5_7, &ratio5_7, &ratio5_7, &ratio5_7, &ratio5_7, &ratio5_7, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, 
&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio9_7, &ratio9_7, &ratio9_7, &ratio9_7, 
&ratio9_7, &ratio9_7, &ratio9_7, &ratio9_7, &ratio9_7, &ratio9_7, &ratio9_7, &ratio9_7, &ratio9_7, &ratio9_7, &ratio9_7, &ratio11_7, 
&ratio11_7, &ratio11_7, &ratio11_7, &ratio11_7, &ratio11_7, &ratio11_7, &ratio11_7, &ratio11_7, &ratio11_7, &ratio11_7, &ratio11_7, &ratio11_7, 
&ratio11_7, &ratio13_7, &ratio13_7, &ratio13_7, &ratio13_7, &ratio13_7, &ratio13_7, &ratio13_7, &ratio13_7, &ratio13_7, &ratio13_7, &ratio13_7, 
&ratio13_7, &ratio13_7, &ratio13_7, &ratio15_7, &ratio15_7, &ratio15_7, &ratio15_7, &ratio15_7, &ratio15_7, &ratio15_7, &ratio15_7, &ratio15_7, 
&ratio15_7, &ratio15_7, &ratio15_7, &ratio15_7, &ratio15_7, &ratio17_7, &ratio17_7, &ratio17_7, &ratio17_7, &ratio17_7, &ratio17_7, &ratio17_7, 
&ratio17_7, &ratio17_7, &ratio17_7, &ratio17_7, &ratio17_7, &ratio17_7, &ratio17_7}; 

static const ScaleNote * const odd_integers4[128] = {&ratio1_9, &ratio1_9, &ratio1_9, &ratio1_9, &ratio1_9, &ratio1_9, &ratio1_9, &ratio1_9, &ratio1_9, &ratio1_9, &ratio1_9, &ratio1_9, &ratio1_9, 
&ratio1_9, &ratio1_9, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, 
&ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio5_9, &ratio5_9, &ratio5_9, &ratio5_9, &ratio5_9, &ratio5_9, &ratio5_9, &ratio5_9, 
&ratio5_9, &ratio5_9, &ratio5_9, &ratio5_9, &ratio5_9, &ratio5_9, &ratio7_9, &ratio7_9, &ratio7_9, &ratio7_9, &ratio7_9, &ratio7_9, 
&ratio7_9, &ratio7_9, &ratio7_9, &ratio7_9, &ratio7_9, &ratio7_9, &ratio7_9, &ratio7_9, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, 
&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio11_9, 
&ratio11_9, &ratio11_9, &ratio11_9, &ratio11_9, &ratio11_9, &ratio11_9, &ratio11_9, &ratio11_9, &ratio11_9, &ratio11_9, &ratio11_9, &ratio11_9, 
&ratio11_9, &ratio13_9, &ratio13_9, &ratio13_9, &ratio13_9, &ratio13_9, &ratio13_9, &ratio13_9, &ratio13_9, &ratio13_9, &ratio13_9, &ratio13_9, 
&ratio13_9, &ratio13_9, &ratio13_9, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, 
&ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio17_9, &ratio17_9, &ratio17_9, &ratio17_9, &ratio17_9, &ratio17_9, &ratio17_9, 
&ratio17_9, &ratio17_9, &ratio17_9, &ratio17_9, &ratio17_9, &ratio17_9, &ratio17_9}; 

static const ScaleNote * const odd_integers5[128] = {&ratio1_11, &ratio1_11, &ratio1_11, &ratio1_11, &ratio1_11, &ratio1_11, &ratio1_11, &ratio1_11, &ratio1_11, &ratio1_11, &ratio1_11, &ratio1_11, &ratio1_11, 
&ratio1_11, &ratio1_11, &ratio3_11, &ratio3_11, &ratio3_11, &ratio3_11, &ratio3_11, &ratio3_11, &ratio3_11, &ratio3_11, &ratio3_11, &ratio3_11, 
&ratio3_11, &ratio3_11, &ratio3_11, &ratio3_11, &ratio5_11, &ratio5_11, &ratio5_11, &ratio5_11, &ratio5_11, &ratio5_11, &ratio5_11, &ratio5_11, 
&ratio5_11, &ratio5_11, &ratio5_11, &ratio5_11, &ratio5_11, &ratio5_11, &ratio7_11, &ratio7_11, &ratio7_11, &ratio7_11, &ratio7_11, &ratio7_11, 
&ratio7_11, &ratio7_11, &ratio7_11, &ratio7_11, &ratio7_11, &ratio7_11, &ratio7_11, &ratio7_11, &ratio9_11, &ratio9_11, &ratio9_11, &ratio9_11, 
&ratio9_11, &ratio9_11, &ratio9_11, &ratio9_11, &ratio9_11, &ratio9_11, &ratio9_11, &ratio9_11, &ratio9_11, &ratio9_11, &ratio9_11, &ratio1_1, 
&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, 
&ratio1_1, &ratio13_11, &ratio13_11, &ratio13_11, &ratio13_11, &ratio13_11, &ratio13_11, &ratio13_11, &ratio13_11, &ratio13_11, &ratio13_11, &ratio13_11, 
&ratio13_11, &ratio13_11, &ratio13_11, &ratio15_11, &ratio15_11, &ratio15_11, &ratio15_11, &ratio15_11, &ratio15_11, &ratio15_11, &ratio15_11, &ratio15_11, 
&ratio15_11, &ratio15_11, &ratio15_11, &ratio15_11, &ratio15_11, &ratio17_11, &ratio17_11, &ratio17_11, &ratio17_11, &ratio17_11, &ratio17_11, &ratio17_11, 
&ratio17_11, &ratio17_11, &ratio17_11, &ratio17_11, &ratio17_11, &ratio17_11, &ratio17_11}; 

static const ScaleNote * const odd_integers6[128] = {&ratio1_13, &ratio1_13, &ratio1_13, &ratio1_13, &ratio1_13, &ratio1_13, &ratio1_13, &ratio1_13, &ratio1_13, &ratio1_13, &ratio1_13, &ratio1_13, &ratio1_13, 
&ratio1_13, &ratio1_13, &ratio3_13, &ratio3_13, &ratio3_13, &ratio3_13, &ratio3_13, &ratio3_13, &ratio3_13, &ratio3_13, &ratio3_13, &ratio3_13, 
&ratio3_13, &ratio3_13, &ratio3_13, &ratio3_13, &ratio5_13, &ratio5_13, &ratio5_13, &ratio5_13, &ratio5_13, &ratio5_13, &ratio5_13, &ratio5_13, 
&ratio5_13, &ratio5_13, &ratio5_13, &ratio5_13, &ratio5_13, &ratio5_13, &ratio7_13, &ratio7_13, &ratio7_13, &ratio7_13, &ratio7_13, &ratio7_13, 
&ratio7_13, &ratio7_13, &ratio7_13, &ratio7_13, &ratio7_13, &ratio7_13, &ratio7_13, &ratio7_13, &ratio9_13, &ratio9_13, &ratio9_13, &ratio9_13, 
&ratio9_13, &ratio9_13, &ratio9_13, &ratio9_13, &ratio9_13, &ratio9_13, &ratio9_13, &ratio9_13, &ratio9_13, &ratio9_13, &ratio9_13, &ratio11_13, 
&ratio11_13, &ratio11_13, &ratio11_13, &ratio11_13, &ratio11_13, &ratio11_13, &ratio11_13, &ratio11_13, &ratio11_13, &ratio11_13, &ratio11_13, &ratio11_13, 
&ratio11_13, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, 
&ratio1_1, &ratio1_1, &ratio1_1, &ratio15_13, &ratio15_13, &ratio15_13, &ratio15_13, &ratio15_13, &ratio15_13, &ratio15_13, &ratio15_13, &ratio15_13, 
&ratio15_13, &ratio15_13, &ratio15_13, &ratio15_13, &ratio15_13, &ratio17_13, &ratio17_13, &ratio17_13, &ratio17_13, &ratio17_13, &ratio17_13, &ratio17_13, 
&ratio17_13, &ratio17_13, &ratio17_13, &ratio17_13, &ratio17_13, &ratio17_13, &ratio17_13}; 

static const ScaleNote * const odd_integers7[128] = {&ratio1_15, &ratio1_15, &ratio1_15, &ratio1_15, &ratio1_15, &ratio1_15, &ratio1_15, &ratio1_15, &ratio1_15, &ratio1_15, &ratio1_15, &ratio1_15, &ratio1_15, 
&ratio1_15, &ratio1_15, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, 
&ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, 
&ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio7_15, &ratio7_15, &ratio7_15, &ratio7_15, &ratio7_15, &ratio7_15, 
&ratio7_15, &ratio7_15, &ratio7_15, &ratio7_15, &ratio7_15, &ratio7_15, &ratio7_15, &ratio7_15, &ratio3_5, &ratio3_5, &ratio3_5, &ratio3_5, 
&ratio3_5, &ratio3_5, &ratio3_5, &ratio3_5, &ratio3_5, &ratio3_5, &ratio3_5, &ratio3_5, &ratio3_5, &ratio3_5, &ratio3_5, &ratio11_15, 
&ratio11_15, &ratio11_15, &ratio11_15, &ratio11_15, &ratio11_15, &ratio11_15, &ratio11_15, &ratio11_15, &ratio11_15, &ratio11_15, &ratio11_15, &ratio11_15, 
&ratio11_15, &ratio13_15, &ratio13_15, &ratio13_15, &ratio13_15, &ratio13_15, &ratio13_15, &ratio13_15, &ratio13_15, &ratio13_15, &ratio13_15, &ratio13_15, 
&ratio13_15, &ratio13_15, &ratio13_15, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, 
&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio17_15, &ratio17_15, &ratio17_15, &ratio17_15, &ratio17_15, &ratio17_15, &ratio17_15, 
&ratio17_15, &ratio17_15, &ratio17_15, &ratio17_15, &ratio17_15, &ratio17_15, &ratio17_15}; 

static const ScaleNote * const odd_integers8[128] = {&ratio1_17, &ratio1_17, &ratio1_17, &ratio1_17, &ratio1_17, &ratio1_17, &ratio1_17, &ratio1_17, &ratio1_17, &ratio1_17, &ratio1_17, &ratio1_17, &ratio1_17, 
&ratio1_17, &ratio1_17, &ratio3_17, &ratio3_17, &ratio3_17, &ratio3_17, &ratio3_17, &ratio3_17, &ratio3_17, &ratio3_17, &ratio3_17, &ratio3_17, 
&ratio3_17, &ratio3_17, &ratio3_17, &ratio3_17, &ratio5_17, &ratio5_17, &ratio5_17, &ratio5_17, &ratio5_17, &ratio5_17, &ratio5_17, &ratio5_17, 
&ratio5_17, &ratio5_17, &ratio5_17, &ratio5_17, &ratio5_17, &ratio5_17, &ratio7_17, &ratio7_17, &ratio7_17, &ratio7_17, &ratio7_17, &ratio7_17, 
&ratio7_17, &ratio7_17, &ratio7_17, &ratio7_17, &ratio7_17, &ratio7_17, &ratio7_17, &ratio7_17, &ratio9_17, &ratio9_17, &ratio9_17, &ratio9_17, 
&ratio9_17, &ratio9_17, &ratio9_17, &ratio9_17, &ratio9_17, &ratio9_17, &ratio9_17, &ratio9_17, &ratio9_17, &ratio9_17, &ratio9_17, &ratio11_17, 
&ratio11_17, &ratio11_17, &ratio11_17, &ratio11_17, &ratio11_17, &ratio11_17, &ratio11_17, &ratio11_17, &ratio11_17, &ratio11_17, &ratio11_17, &ratio11_17, 
&ratio11_17, &ratio13_17, &ratio13_17, &ratio13_17, &ratio13_17, &ratio13_17, &ratio13_17, &ratio13_17, &ratio13_17, &ratio13_17, &ratio13_17, &ratio13_17, 
&ratio13_17, &ratio13_17, &ratio13_17, &ratio15_17, &ratio15_17, &ratio15_17, &ratio15_17, &ratio15_17, &ratio15_17, &ratio15_17, &ratio15_17, &ratio15_17, 
&ratio15_17, &ratio15_17, &ratio15_17, &ratio15_17, &ratio15_17, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, 
&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1}; 



static const ScaleNote * const modal_tetradsainversion_walk[128] = {&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, 
&ratio5_4, &ratio5_4, &ratio5_4, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio15_8, 
&ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, 
&ratio5_4, &ratio5_4, &ratio5_4, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio15_8, 
&ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, 
&ratio2_1, &ratio2_1, &ratio2_1, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio15_8, 
&ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, 
&ratio2_1, &ratio2_1, &ratio2_1, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio15_8, 
&ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, 
&ratio2_1, &ratio2_1, &ratio2_1, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio3_1, 
&ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1}; 

static const ScaleNote * const modal_tetradsbinversion_walk[128] = {&ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, 
&ratio4_3, &ratio4_3, &ratio4_3, &ratio27_16, &ratio27_16, &ratio27_16, &ratio27_16, &ratio27_16, &ratio27_16, &ratio27_16, &ratio27_16, &ratio2_1, 
&ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, 
&ratio4_3, &ratio4_3, &ratio4_3, &ratio27_16, &ratio27_16, &ratio27_16, &ratio27_16, &ratio27_16, &ratio27_16, &ratio27_16, &ratio27_16, &ratio2_1, 
&ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, 
&ratio9_4, &ratio9_4, &ratio9_4, &ratio27_16, &ratio27_16, &ratio27_16, &ratio27_16, &ratio27_16, &ratio27_16, &ratio27_16, &ratio27_16, &ratio2_1, 
&ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, 
&ratio9_4, &ratio9_4, &ratio9_4, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio2_1, 
&ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, 
&ratio9_4, &ratio9_4, &ratio9_4, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio27_8, 
&ratio27_8, &ratio27_8, &ratio27_8, &ratio27_8, &ratio27_8, &ratio27_8, &ratio27_8}; 

static const ScaleNote * const modal_tetradinversion_walk[128] = {&ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, 
&ratio3_2, &ratio3_2, &ratio3_2, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio9_4, 
&ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, 
&ratio3_2, &ratio3_2, &ratio3_2, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio9_4, 
&ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, 
&ratio5_2, &ratio5_2, &ratio5_2, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio9_4, 
&ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, 
&ratio5_2, &ratio5_2, &ratio5_2, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio9_4, 
&ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, 
&ratio5_2, &ratio5_2, &ratio5_2, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio15_4, 
&ratio15_4, &ratio15_4, &ratio15_4, &ratio15_4, &ratio15_4, &ratio15_4, &ratio15_4}; 

static const ScaleNote * const modal_tetradsdinversion_walk[128] = {&ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio27_16, &ratio27_16, &ratio27_16, &ratio27_16, &ratio27_16, 
&ratio27_16, &ratio27_16, &ratio27_16, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio5_2, 
&ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio27_16, &ratio27_16, &ratio27_16, &ratio27_16, &ratio27_16, 
&ratio27_16, &ratio27_16, &ratio27_16, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio5_2, 
&ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, 
&ratio8_3, &ratio8_3, &ratio8_3, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio5_2, 
&ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, 
&ratio8_3, &ratio8_3, &ratio8_3, &ratio27_8, &ratio27_8, &ratio27_8, &ratio27_8, &ratio27_8, &ratio27_8, &ratio27_8, &ratio27_8, &ratio5_2, 
&ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, 
&ratio8_3, &ratio8_3, &ratio8_3, &ratio27_8, &ratio27_8, &ratio27_8, &ratio27_8, &ratio27_8, &ratio27_8, &ratio27_8, &ratio27_8, &ratio4_1, 
&ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1}; 

static const ScaleNote * const modal_tetradseinversion_walk[128] = {&ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, 
&ratio15_8, &ratio15_8, &ratio15_8, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio8_3, 
&ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, 
&ratio15_8, &ratio15_8, &ratio15_8, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio8_3, 
&ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, 
&ratio3_1, &ratio3_1, &ratio3_1, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio8_3, 
&ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, 
&ratio3_1, &ratio3_1, &ratio3_1, &ratio15_4, &ratio15_4, &ratio15_4, &ratio15_4, &ratio15_4, &ratio15_4, &ratio15_4, &ratio15_4, &ratio8_3, 
&ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, 
&ratio3_1, &ratio3_1, &ratio3_1, &ratio15_4, &ratio15_4, &ratio15_4, &ratio15_4, &ratio15_4, &ratio15_4, &ratio15_4, &ratio15_4, &ratio9_2, 
&ratio9_2, &ratio9_2, &ratio9_2, &ratio9_2, &ratio9_2, &ratio9_2, &ratio9_2}; 

static const ScaleNote * const modal_tetradsfinversion_walk[128] = {&ratio27_16, &ratio27_16, &ratio27_16, &ratio27_16, &ratio27_16, &ratio27_16, &ratio27_16, &ratio27_16, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, 
&ratio2_1, &ratio2_1, &ratio2_1, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio3_1, 
&ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, 
&ratio2_1, &ratio2_1, &ratio2_1, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio3_1, 
&ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio27_8, &ratio27_8, &ratio27_8, &ratio27_8, &ratio27_8, 
&ratio27_8, &ratio27_8, &ratio27_8, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio3_1, 
&ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio27_8, &ratio27_8, &ratio27_8, &ratio27_8, &ratio27_8, 
&ratio27_8, &ratio27_8, &ratio27_8, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio3_1, 
&ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio27_8, &ratio27_8, &ratio27_8, &ratio27_8, &ratio27_8, 
&ratio27_8, &ratio27_8, &ratio27_8, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio5_1, 
&ratio5_1, &ratio5_1, &ratio5_1, &ratio5_1, &ratio5_1, &ratio5_1, &ratio5_1}; 

static const ScaleNote * const modal_tetradsginversion_walk[128] = {&ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, 
&ratio9_4, &ratio9_4, &ratio9_4, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio27_8, 
&ratio27_8, &ratio27_8, &ratio27_8, &ratio27_8, &ratio27_8, &ratio27_8, &ratio27_8, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, 
&ratio9_4, &ratio9_4, &ratio9_4, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio27_8, 
&ratio27_8, &ratio27_8, &ratio27_8, &ratio27_8, &ratio27_8, &ratio27_8, &ratio27_8, &ratio15_4, &ratio15_4, &ratio15_4, &ratio15_4, &ratio15_4, 
&ratio15_4, &ratio15_4, &ratio15_4, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio27_8, 
&ratio27_8, &ratio27_8, &ratio27_8, &ratio27_8, &ratio27_8, &ratio27_8, &ratio27_8, &ratio15_4, &ratio15_4, &ratio15_4, &ratio15_4, &ratio15_4, 
&ratio15_4, &ratio15_4, &ratio15_4, &ratio9_2, &ratio9_2, &ratio9_2, &ratio9_2, &ratio9_2, &ratio9_2, &ratio9_2, &ratio9_2, &ratio27_8, 
&ratio27_8, &ratio27_8, &ratio27_8, &ratio27_8, &ratio27_8, &ratio27_8, &ratio27_8, &ratio15_4, &ratio15_4, &ratio15_4, &ratio15_4, &ratio15_4, 
&ratio15_4, &ratio15_4, &ratio15_4, &ratio9_2, &ratio9_2, &ratio9_2, &ratio9_2, &ratio9_2, &ratio9_2, &ratio9_2, &ratio9_2, &ratio16_3, 
&ratio16_3, &ratio16_3, &ratio16_3, &ratio16_3, &ratio16_3, &ratio16_3, &ratio16_3}; 

static const ScaleNote * const modal_tetradshinversion_walk[128] = {&ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, 
&ratio5_2, &ratio5_2, &ratio5_2, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio18_5, 
&ratio18_5, &ratio18_5, &ratio18_5, &ratio18_5, &ratio18_5, &ratio18_5, &ratio18_5, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, 
&ratio5_2, &ratio5_2, &ratio5_2, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio18_5, 
&ratio18_5, &ratio18_5, &ratio18_5, &ratio18_5, &ratio18_5, &ratio18_5, &ratio18_5, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, 
&ratio4_1, &ratio4_1, &ratio4_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio18_5, 
&ratio18_5, &ratio18_5, &ratio18_5, &ratio18_5, &ratio18_5, &ratio18_5, &ratio18_5, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, 
&ratio4_1, &ratio4_1, &ratio4_1, &ratio5_1, &ratio5_1, &ratio5_1, &ratio5_1, &ratio5_1, &ratio5_1, &ratio5_1, &ratio5_1, &ratio18_5, 
&ratio18_5, &ratio18_5, &ratio18_5, &ratio18_5, &ratio18_5, &ratio18_5, &ratio18_5, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, 
&ratio4_1, &ratio4_1, &ratio4_1, &ratio5_1, &ratio5_1, &ratio5_1, &ratio5_1, &ratio5_1, &ratio5_1, &ratio5_1, &ratio5_1, &ratio6_1, 
&ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1}; 



static const ScaleNote * const a_maj7thinversion_walk[128] = {&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, 
&ratio5_4, &ratio5_4, &ratio5_4, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio15_8, 
&ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, 
&ratio5_4, &ratio5_4, &ratio5_4, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio15_8, 
&ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, 
&ratio2_1, &ratio2_1, &ratio2_1, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio15_8, 
&ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, 
&ratio2_1, &ratio2_1, &ratio2_1, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio15_8, 
&ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, 
&ratio2_1, &ratio2_1, &ratio2_1, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio3_1, 
&ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1}; 

static const ScaleNote * const a_maj7th2ndIninversion_walk[128] = {&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, 
&ratio5_4, &ratio5_4, &ratio5_4, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio5_3, 
&ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, 
&ratio5_4, &ratio5_4, &ratio5_4, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio5_3, 
&ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, 
&ratio2_1, &ratio2_1, &ratio2_1, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio5_3, 
&ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, 
&ratio2_1, &ratio2_1, &ratio2_1, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_3, 
&ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, 
&ratio2_1, &ratio2_1, &ratio2_1, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio8_3, 
&ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3}; 

static const ScaleNote * const b_dom7thinversion_walk[128] = {&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, 
&ratio5_4, &ratio5_4, &ratio5_4, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio9_5, 
&ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, 
&ratio5_4, &ratio5_4, &ratio5_4, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio9_5, 
&ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, 
&ratio2_1, &ratio2_1, &ratio2_1, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio9_5, 
&ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, 
&ratio2_1, &ratio2_1, &ratio2_1, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio9_5, 
&ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, 
&ratio2_1, &ratio2_1, &ratio2_1, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio3_1, 
&ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1}; 

static const ScaleNote * const b_dom7thRotateinversion_walk[128] = {&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, 
&ratio6_5, &ratio6_5, &ratio6_5, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio5_3, 
&ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, 
&ratio6_5, &ratio6_5, &ratio6_5, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio5_3, 
&ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, 
&ratio2_1, &ratio2_1, &ratio2_1, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio5_3, 
&ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, 
&ratio2_1, &ratio2_1, &ratio2_1, &ratio12_5, &ratio12_5, &ratio12_5, &ratio12_5, &ratio12_5, &ratio12_5, &ratio12_5, &ratio12_5, &ratio5_3, 
&ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, 
&ratio2_1, &ratio2_1, &ratio2_1, &ratio12_5, &ratio12_5, &ratio12_5, &ratio12_5, &ratio12_5, &ratio12_5, &ratio12_5, &ratio12_5, &ratio3_1, 
&ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1}; 

static const ScaleNote * const c_subDom7thinversion_walk[128] = {&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, 
&ratio6_5, &ratio6_5, &ratio6_5, &ratio36_25, &ratio36_25, &ratio36_25, &ratio36_25, &ratio36_25, &ratio36_25, &ratio36_25, &ratio36_25, &ratio9_5, 
&ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, 
&ratio6_5, &ratio6_5, &ratio6_5, &ratio36_25, &ratio36_25, &ratio36_25, &ratio36_25, &ratio36_25, &ratio36_25, &ratio36_25, &ratio36_25, &ratio9_5, 
&ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, 
&ratio2_1, &ratio2_1, &ratio2_1, &ratio36_25, &ratio36_25, &ratio36_25, &ratio36_25, &ratio36_25, &ratio36_25, &ratio36_25, &ratio36_25, &ratio9_5, 
&ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, 
&ratio2_1, &ratio2_1, &ratio2_1, &ratio12_5, &ratio12_5, &ratio12_5, &ratio12_5, &ratio12_5, &ratio12_5, &ratio12_5, &ratio12_5, &ratio9_5, 
&ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, 
&ratio2_1, &ratio2_1, &ratio2_1, &ratio12_5, &ratio12_5, &ratio12_5, &ratio12_5, &ratio12_5, &ratio12_5, &ratio12_5, &ratio12_5, &ratio72_25, 
&ratio72_25, &ratio72_25, &ratio72_25, &ratio72_25, &ratio72_25, &ratio72_25, &ratio72_25}; 

static const ScaleNote * const c_subDom7thRotateinversion_walk[128] = {&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, 
&ratio9_8, &ratio9_8, &ratio9_8, &ratio25_18, &ratio25_18, &ratio25_18, &ratio25_18, &ratio25_18, &ratio25_18, &ratio25_18, &ratio25_18, &ratio5_3, 
&ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, 
&ratio9_8, &ratio9_8, &ratio9_8, &ratio25_18, &ratio25_18, &ratio25_18, &ratio25_18, &ratio25_18, &ratio25_18, &ratio25_18, &ratio25_18, &ratio5_3, 
&ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, 
&ratio2_1, &ratio2_1, &ratio2_1, &ratio25_18, &ratio25_18, &ratio25_18, &ratio25_18, &ratio25_18, &ratio25_18, &ratio25_18, &ratio25_18, &ratio5_3, 
&ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, 
&ratio2_1, &ratio2_1, &ratio2_1, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio5_3, 
&ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, 
&ratio2_1, &ratio2_1, &ratio2_1, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio25_9, 
&ratio25_9, &ratio25_9, &ratio25_9, &ratio25_9, &ratio25_9, &ratio25_9, &ratio25_9}; 

static const ScaleNote * const min7thinversion_walk[128] = {&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, 
&ratio9_8, &ratio9_8, &ratio9_8, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio3_2, 
&ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, 
&ratio9_8, &ratio9_8, &ratio9_8, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio3_2, 
&ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, 
&ratio2_1, &ratio2_1, &ratio2_1, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio3_2, 
&ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, 
&ratio2_1, &ratio2_1, &ratio2_1, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio3_2, 
&ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, 
&ratio2_1, &ratio2_1, &ratio2_1, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio12_5, 
&ratio12_5, &ratio12_5, &ratio12_5, &ratio12_5, &ratio12_5, &ratio12_5, &ratio12_5}; 

static const ScaleNote * const min7th2ndIninversion_walk[128] = {&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, 
&ratio6_5, &ratio6_5, &ratio6_5, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio8_5, 
&ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, 
&ratio6_5, &ratio6_5, &ratio6_5, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio8_5, 
&ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, 
&ratio2_1, &ratio2_1, &ratio2_1, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio8_5, 
&ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, 
&ratio2_1, &ratio2_1, &ratio2_1, &ratio12_5, &ratio12_5, &ratio12_5, &ratio12_5, &ratio12_5, &ratio12_5, &ratio12_5, &ratio12_5, &ratio8_5, 
&ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, 
&ratio2_1, &ratio2_1, &ratio2_1, &ratio12_5, &ratio12_5, &ratio12_5, &ratio12_5, &ratio12_5, &ratio12_5, &ratio12_5, &ratio12_5, &ratio3_1, 
&ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1}; 



static const ScaleNote * const impressionista_vs_impressionistb[128] = {&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, 
&ratio6_5, &ratio6_5, &ratio6_5, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio8_5, 
&ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, 
&ratio2_1, &ratio2_1, &ratio2_1, &ratio12_5, &ratio12_5, &ratio12_5, &ratio12_5, &ratio12_5, &ratio12_5, &ratio12_5, &ratio12_5, &ratio3_1, 
&ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio15_4, &ratio15_4, &ratio15_4, &ratio15_4, &ratio15_4, 
&ratio15_4, &ratio15_4, &ratio15_4, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio18_5, 
&ratio18_5, &ratio18_5, &ratio18_5, &ratio18_5, &ratio18_5, &ratio18_5, &ratio18_5, &ratio12_5, &ratio12_5, &ratio12_5, &ratio12_5, &ratio12_5, 
&ratio12_5, &ratio12_5, &ratio12_5, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio8_5, 
&ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, 
&ratio3_2, &ratio3_2, &ratio3_2, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio1_1, 
&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1}; 

static const ScaleNote * const impressionist_vs_impressionistd[128] = {&ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, 
&ratio4_3, &ratio4_3, &ratio4_3, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio8_5, 
&ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, 
&ratio2_1, &ratio2_1, &ratio2_1, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio16_5, 
&ratio16_5, &ratio16_5, &ratio16_5, &ratio16_5, &ratio16_5, &ratio16_5, &ratio16_5, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, 
&ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio16_5, 
&ratio16_5, &ratio16_5, &ratio16_5, &ratio16_5, &ratio16_5, &ratio16_5, &ratio16_5, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, 
&ratio9_4, &ratio9_4, &ratio9_4, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio8_5, 
&ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, 
&ratio3_2, &ratio3_2, &ratio3_2, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio9_8, 
&ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8}; 

static const ScaleNote * const impressioniste_vs_impressionistf[128] = {&ratio17_16, &ratio17_16, &ratio17_16, &ratio17_16, &ratio17_16, &ratio17_16, &ratio17_16, &ratio17_16, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, 
&ratio5_4, &ratio5_4, &ratio5_4, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio9_5, 
&ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio17_8, &ratio17_8, &ratio17_8, &ratio17_8, &ratio17_8, 
&ratio17_8, &ratio17_8, &ratio17_8, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio3_1, 
&ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio18_5, &ratio18_5, &ratio18_5, &ratio18_5, &ratio18_5, 
&ratio18_5, &ratio18_5, &ratio18_5, &ratio18_5, &ratio18_5, &ratio18_5, &ratio18_5, &ratio18_5, &ratio18_5, &ratio18_5, &ratio18_5, &ratio3_1, 
&ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, 
&ratio5_2, &ratio5_2, &ratio5_2, &ratio17_8, &ratio17_8, &ratio17_8, &ratio17_8, &ratio17_8, &ratio17_8, &ratio17_8, &ratio17_8, &ratio9_5, 
&ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, 
&ratio3_2, &ratio3_2, &ratio3_2, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio17_16, 
&ratio17_16, &ratio17_16, &ratio17_16, &ratio17_16, &ratio17_16, &ratio17_16, &ratio17_16}; 

static const ScaleNote * const impressionistg_vs_impressionisth[128] = {&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, 
&ratio9_8, &ratio9_8, &ratio9_8, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio9_5, 
&ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, 
&ratio9_4, &ratio9_4, &ratio9_4, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio18_5, 
&ratio18_5, &ratio18_5, &ratio18_5, &ratio18_5, &ratio18_5, &ratio18_5, &ratio18_5, &ratio9_2, &ratio9_2, &ratio9_2, &ratio9_2, &ratio9_2, 
&ratio9_2, &ratio9_2, &ratio9_2, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio18_5, 
&ratio18_5, &ratio18_5, &ratio18_5, &ratio18_5, &ratio18_5, &ratio18_5, &ratio18_5, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, 
&ratio3_1, &ratio3_1, &ratio3_1, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_5, 
&ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, 
&ratio3_2, &ratio3_2, &ratio3_2, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, 
&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1}; 

static const ScaleNote * const impressionisti_vs_impressionistj[128] = {&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio17_16, &ratio17_16, &ratio17_16, &ratio17_16, &ratio17_16, 
&ratio17_16, &ratio17_16, &ratio17_16, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio8_5, 
&ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio17_8, &ratio17_8, &ratio17_8, &ratio17_8, &ratio17_8, 
&ratio17_8, &ratio17_8, &ratio17_8, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio16_5, 
&ratio16_5, &ratio16_5, &ratio16_5, &ratio16_5, &ratio16_5, &ratio16_5, &ratio16_5, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, 
&ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio16_5, 
&ratio16_5, &ratio16_5, &ratio16_5, &ratio16_5, &ratio16_5, &ratio16_5, &ratio16_5, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, 
&ratio8_3, &ratio8_3, &ratio8_3, &ratio17_8, &ratio17_8, &ratio17_8, &ratio17_8, &ratio17_8, &ratio17_8, &ratio17_8, &ratio17_8, &ratio9_5, 
&ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, 
&ratio8_5, &ratio8_5, &ratio8_5, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio17_16, 
&ratio17_16, &ratio17_16, &ratio17_16, &ratio17_16, &ratio17_16, &ratio17_16, &ratio17_16}; 

static const ScaleNote * const impressionistk_vs_impressionistl[128] = {&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, 
&ratio4_3, &ratio4_3, &ratio4_3, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio8_5, 
&ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, 
&ratio2_1, &ratio2_1, &ratio2_1, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio16_5, 
&ratio16_5, &ratio16_5, &ratio16_5, &ratio16_5, &ratio16_5, &ratio16_5, &ratio16_5, &ratio9_2, &ratio9_2, &ratio9_2, &ratio9_2, &ratio9_2, 
&ratio9_2, &ratio9_2, &ratio9_2, &ratio9_2, &ratio9_2, &ratio9_2, &ratio9_2, &ratio9_2, &ratio9_2, &ratio9_2, &ratio9_2, &ratio16_5, 
&ratio16_5, &ratio16_5, &ratio16_5, &ratio16_5, &ratio16_5, &ratio16_5, &ratio16_5, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, 
&ratio8_3, &ratio8_3, &ratio8_3, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio8_5, 
&ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, 
&ratio3_2, &ratio3_2, &ratio3_2, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio1_1, 
&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1}; 

static const ScaleNote * const impressionistm_vs_impressionistn[128] = {&ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, 
&ratio4_3, &ratio4_3, &ratio4_3, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio15_8, 
&ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, 
&ratio9_4, &ratio9_4, &ratio9_4, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio16_5, 
&ratio16_5, &ratio16_5, &ratio16_5, &ratio16_5, &ratio16_5, &ratio16_5, &ratio16_5, &ratio15_4, &ratio15_4, &ratio15_4, &ratio15_4, &ratio15_4, 
&ratio15_4, &ratio15_4, &ratio15_4, &ratio15_4, &ratio15_4, &ratio15_4, &ratio15_4, &ratio15_4, &ratio15_4, &ratio15_4, &ratio15_4, &ratio16_5, 
&ratio16_5, &ratio16_5, &ratio16_5, &ratio16_5, &ratio16_5, &ratio16_5, &ratio16_5, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, 
&ratio8_3, &ratio8_3, &ratio8_3, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio15_8, 
&ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, 
&ratio8_5, &ratio8_5, &ratio8_5, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio9_8, 
&ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8}; 

static const ScaleNote * const impressionisto_vs_impressionistp[128] = {&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, 
&ratio6_5, &ratio6_5, &ratio6_5, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio15_8, 
&ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, 
&ratio2_1, &ratio2_1, &ratio2_1, &ratio12_5, &ratio12_5, &ratio12_5, &ratio12_5, &ratio12_5, &ratio12_5, &ratio12_5, &ratio12_5, &ratio3_1, 
&ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, 
&ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio3_1, 
&ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio12_5, &ratio12_5, &ratio12_5, &ratio12_5, &ratio12_5, 
&ratio12_5, &ratio12_5, &ratio12_5, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio15_8, 
&ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, 
&ratio3_2, &ratio3_2, &ratio3_2, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio1_1, 
&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1}; 



static const ScaleNote * const bohlenPeirceAScale_vs_bohlenPeirceBlueLambda[128] = {&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio27_25, &ratio27_25, &ratio27_25, &ratio27_25, &ratio27_25, &ratio27_25, &ratio25_21, 
&ratio25_21, &ratio25_21, &ratio25_21, &ratio25_21, &ratio25_21, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio9_7, 
&ratio9_7, &ratio9_7, &ratio9_7, &ratio9_7, &ratio9_7, &ratio7_5, &ratio7_5, &ratio7_5, &ratio7_5, &ratio7_5, &ratio75_49, &ratio75_49, 
&ratio75_49, &ratio75_49, &ratio75_49, &ratio75_49, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio49_25, &ratio49_25, 
&ratio49_25, &ratio49_25, &ratio49_25, &ratio49_25, &ratio15_7, &ratio15_7, &ratio15_7, &ratio15_7, &ratio15_7, &ratio15_7, &ratio7_3, &ratio7_3, 
&ratio7_3, &ratio7_3, &ratio7_3, &ratio63_25, &ratio63_25, &ratio63_25, &ratio63_25, &ratio63_25, &ratio63_25, &ratio25_9, &ratio25_9, &ratio25_9, 
&ratio25_9, &ratio25_9, &ratio25_9, &ratio25_9, &ratio25_9, &ratio25_9, &ratio25_9, &ratio25_9, &ratio25_9, &ratio7_3, &ratio7_3, &ratio7_3, 
&ratio7_3, &ratio7_3, &ratio7_3, &ratio49_25, &ratio49_25, &ratio49_25, &ratio49_25, &ratio49_25, &ratio49_25, &ratio9_5, &ratio9_5, &ratio9_5, 
&ratio9_5, &ratio9_5, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio7_5, &ratio7_5, &ratio7_5, &ratio7_5, 
&ratio7_5, &ratio7_5, &ratio9_7, &ratio9_7, &ratio9_7, &ratio9_7, &ratio9_7, &ratio9_7, &ratio25_21, &ratio25_21, &ratio25_21, &ratio25_21, 
&ratio25_21, &ratio25_21, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1}; 

static const ScaleNote * const bohlenPeirceBlueLambda2_vs_bohlenPeirceDurI[128] = {&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio25_21, &ratio25_21, &ratio25_21, &ratio25_21, &ratio25_21, 
&ratio25_21, &ratio25_21, &ratio9_7, &ratio9_7, &ratio9_7, &ratio9_7, &ratio9_7, &ratio9_7, &ratio9_7, &ratio7_5, &ratio7_5, &ratio7_5, 
&ratio7_5, &ratio7_5, &ratio7_5, &ratio7_5, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio9_5, 
&ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio49_25, &ratio49_25, &ratio49_25, &ratio49_25, &ratio49_25, &ratio49_25, 
&ratio49_25, &ratio7_3, &ratio7_3, &ratio7_3, &ratio7_3, &ratio7_3, &ratio7_3, &ratio7_3, &ratio25_9, &ratio25_9, &ratio25_9, &ratio25_9, 
&ratio25_9, &ratio25_9, &ratio25_9, &ratio63_25, &ratio63_25, &ratio63_25, &ratio63_25, &ratio63_25, &ratio63_25, &ratio63_25, &ratio63_25, &ratio7_3, 
&ratio7_3, &ratio7_3, &ratio7_3, &ratio7_3, &ratio7_3, &ratio7_3, &ratio49_25, &ratio49_25, &ratio49_25, &ratio49_25, &ratio49_25, &ratio49_25, 
&ratio49_25, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, 
&ratio5_3, &ratio5_3, &ratio5_3, &ratio7_5, &ratio7_5, &ratio7_5, &ratio7_5, &ratio7_5, &ratio7_5, &ratio7_5, &ratio9_7, &ratio9_7, 
&ratio9_7, &ratio9_7, &ratio9_7, &ratio9_7, &ratio9_7, &ratio27_25, &ratio27_25, &ratio27_25, &ratio27_25, &ratio27_25, &ratio27_25, &ratio27_25, 
&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1}; 

static const ScaleNote * const bohlenPeirceDurII_vs_bohlenPeirceGamma[128] = {&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio25_21, &ratio25_21, &ratio25_21, &ratio25_21, &ratio25_21, 
&ratio25_21, &ratio25_21, &ratio9_7, &ratio9_7, &ratio9_7, &ratio9_7, &ratio9_7, &ratio9_7, &ratio9_7, &ratio7_5, &ratio7_5, &ratio7_5, 
&ratio7_5, &ratio7_5, &ratio7_5, &ratio7_5, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio9_5, 
&ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio15_7, &ratio15_7, &ratio15_7, &ratio15_7, &ratio15_7, &ratio15_7, 
&ratio15_7, &ratio7_3, &ratio7_3, &ratio7_3, &ratio7_3, &ratio7_3, &ratio7_3, &ratio7_3, &ratio63_25, &ratio63_25, &ratio63_25, &ratio63_25, 
&ratio63_25, &ratio63_25, &ratio63_25, &ratio25_9, &ratio25_9, &ratio25_9, &ratio25_9, &ratio25_9, &ratio25_9, &ratio25_9, &ratio25_9, &ratio7_3, 
&ratio7_3, &ratio7_3, &ratio7_3, &ratio7_3, &ratio7_3, &ratio7_3, &ratio49_25, &ratio49_25, &ratio49_25, &ratio49_25, &ratio49_25, &ratio49_25, 
&ratio49_25, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, 
&ratio5_3, &ratio5_3, &ratio5_3, &ratio7_5, &ratio7_5, &ratio7_5, &ratio7_5, &ratio7_5, &ratio7_5, &ratio7_5, &ratio9_7, &ratio9_7, 
&ratio9_7, &ratio9_7, &ratio9_7, &ratio9_7, &ratio9_7, &ratio27_25, &ratio27_25, &ratio27_25, &ratio27_25, &ratio27_25, &ratio27_25, &ratio27_25, 
&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1}; 

static const ScaleNote * const bohlenPeirceGLambda_vs_bohlenPeirceHarmoni[128] = {&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio25_21, &ratio25_21, &ratio25_21, &ratio25_21, &ratio25_21, 
&ratio25_21, &ratio25_21, &ratio9_7, &ratio9_7, &ratio9_7, &ratio9_7, &ratio9_7, &ratio9_7, &ratio9_7, &ratio7_5, &ratio7_5, &ratio7_5, 
&ratio7_5, &ratio7_5, &ratio7_5, &ratio7_5, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio9_5, 
&ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio15_7, &ratio15_7, &ratio15_7, &ratio15_7, &ratio15_7, &ratio15_7, 
&ratio15_7, &ratio7_3, &ratio7_3, &ratio7_3, &ratio7_3, &ratio7_3, &ratio7_3, &ratio7_3, &ratio63_25, &ratio63_25, &ratio63_25, &ratio63_25, 
&ratio63_25, &ratio63_25, &ratio63_25, &ratio63_25, &ratio63_25, &ratio63_25, &ratio63_25, &ratio63_25, &ratio63_25, &ratio63_25, &ratio63_25, &ratio7_3, 
&ratio7_3, &ratio7_3, &ratio7_3, &ratio7_3, &ratio7_3, &ratio7_3, &ratio15_7, &ratio15_7, &ratio15_7, &ratio15_7, &ratio15_7, &ratio15_7, 
&ratio15_7, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, 
&ratio5_3, &ratio5_3, &ratio5_3, &ratio7_5, &ratio7_5, &ratio7_5, &ratio7_5, &ratio7_5, &ratio7_5, &ratio7_5, &ratio9_7, &ratio9_7, 
&ratio9_7, &ratio9_7, &ratio9_7, &ratio9_7, &ratio9_7, &ratio27_25, &ratio27_25, &ratio27_25, &ratio27_25, &ratio27_25, &ratio27_25, &ratio27_25, 
&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1}; 

static const ScaleNote * const bohlenPeirceHPentatoni_vs_bohlenPeirceMollI[128] = {&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio9_7, &ratio9_7, &ratio9_7, 
&ratio9_7, &ratio9_7, &ratio9_7, &ratio9_7, &ratio9_7, &ratio9_7, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, 
&ratio5_3, &ratio5_3, &ratio5_3, &ratio15_7, &ratio15_7, &ratio15_7, &ratio15_7, &ratio15_7, &ratio15_7, &ratio15_7, &ratio15_7, &ratio15_7, 
&ratio25_9, &ratio25_9, &ratio25_9, &ratio25_9, &ratio25_9, &ratio25_9, &ratio25_9, &ratio25_9, &ratio25_9, &ratio25_9, &ratio25_9, &ratio25_9, 
&ratio25_9, &ratio25_9, &ratio25_9, &ratio25_9, &ratio25_9, &ratio25_9, &ratio7_3, &ratio7_3, &ratio7_3, &ratio7_3, &ratio7_3, &ratio7_3, 
&ratio7_3, &ratio7_3, &ratio7_3, &ratio15_7, &ratio15_7, &ratio15_7, &ratio15_7, &ratio15_7, &ratio15_7, &ratio15_7, &ratio15_7, &ratio15_7, 
&ratio15_7, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio5_3, &ratio5_3, 
&ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio75_49, &ratio75_49, &ratio75_49, &ratio75_49, &ratio75_49, 
&ratio75_49, &ratio75_49, &ratio75_49, &ratio75_49, &ratio9_7, &ratio9_7, &ratio9_7, &ratio9_7, &ratio9_7, &ratio9_7, &ratio9_7, &ratio9_7, 
&ratio9_7, &ratio25_21, &ratio25_21, &ratio25_21, &ratio25_21, &ratio25_21, &ratio25_21, &ratio25_21, &ratio25_21, &ratio25_21, &ratio1_1, &ratio1_1, 
&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1}; 

static const ScaleNote * const bohlenPeirceMollII_vs_bohlenPeirceProoijenMaj[128] = {&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio27_25, &ratio27_25, &ratio27_25, &ratio27_25, &ratio27_25, 
&ratio27_25, &ratio27_25, &ratio27_25, &ratio9_7, &ratio9_7, &ratio9_7, &ratio9_7, &ratio9_7, &ratio9_7, &ratio9_7, &ratio9_7, &ratio7_5, 
&ratio7_5, &ratio7_5, &ratio7_5, &ratio7_5, &ratio7_5, &ratio7_5, &ratio7_5, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, 
&ratio5_3, &ratio5_3, &ratio5_3, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio15_7, 
&ratio15_7, &ratio15_7, &ratio15_7, &ratio15_7, &ratio15_7, &ratio15_7, &ratio15_7, &ratio7_3, &ratio7_3, &ratio7_3, &ratio7_3, &ratio7_3, 
&ratio7_3, &ratio7_3, &ratio7_3, &ratio25_9, &ratio25_9, &ratio25_9, &ratio25_9, &ratio25_9, &ratio25_9, &ratio25_9, &ratio25_9, &ratio25_9, 
&ratio25_9, &ratio25_9, &ratio25_9, &ratio25_9, &ratio25_9, &ratio25_9, &ratio25_9, &ratio7_3, &ratio7_3, &ratio7_3, &ratio7_3, &ratio7_3, 
&ratio7_3, &ratio7_3, &ratio7_3, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio5_3, 
&ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio7_5, &ratio7_5, &ratio7_5, &ratio7_5, &ratio7_5, 
&ratio7_5, &ratio7_5, &ratio7_5, &ratio9_7, &ratio9_7, &ratio9_7, &ratio9_7, &ratio9_7, &ratio9_7, &ratio9_7, &ratio9_7, &ratio1_1, 
&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1}; 

static const ScaleNote * const bohlenPeirceProoijenMin_vs_bohlenPeirceWalkerA[128] = {&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio25_21, &ratio25_21, &ratio25_21, &ratio25_21, &ratio25_21, 
&ratio25_21, &ratio25_21, &ratio25_21, &ratio9_7, &ratio9_7, &ratio9_7, &ratio9_7, &ratio9_7, &ratio9_7, &ratio9_7, &ratio9_7, &ratio5_3, 
&ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, 
&ratio9_5, &ratio9_5, &ratio9_5, &ratio15_7, &ratio15_7, &ratio15_7, &ratio15_7, &ratio15_7, &ratio15_7, &ratio15_7, &ratio15_7, &ratio25_9, 
&ratio25_9, &ratio25_9, &ratio25_9, &ratio25_9, &ratio25_9, &ratio25_9, &ratio25_9, &ratio63_25, &ratio63_25, &ratio63_25, &ratio63_25, &ratio63_25, 
&ratio63_25, &ratio63_25, &ratio63_25, &ratio7_3, &ratio7_3, &ratio7_3, &ratio7_3, &ratio7_3, &ratio7_3, &ratio7_3, &ratio7_3, &ratio49_25, 
&ratio49_25, &ratio49_25, &ratio49_25, &ratio49_25, &ratio49_25, &ratio49_25, &ratio49_25, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, 
&ratio9_5, &ratio9_5, &ratio9_5, &ratio75_49, &ratio75_49, &ratio75_49, &ratio75_49, &ratio75_49, &ratio75_49, &ratio75_49, &ratio75_49, &ratio7_5, 
&ratio7_5, &ratio7_5, &ratio7_5, &ratio7_5, &ratio7_5, &ratio7_5, &ratio7_5, &ratio25_21, &ratio25_21, &ratio25_21, &ratio25_21, &ratio25_21, 
&ratio25_21, &ratio25_21, &ratio25_21, &ratio27_25, &ratio27_25, &ratio27_25, &ratio27_25, &ratio27_25, &ratio27_25, &ratio27_25, &ratio27_25, &ratio1_1, 
&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1}; 

static const ScaleNote * const bohlenPeirceWalkerB_vs_bohlenPeirceWalkerI[128] = {&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio27_25, &ratio27_25, &ratio27_25, &ratio27_25, &ratio27_25, 
&ratio27_25, &ratio27_25, &ratio9_7, &ratio9_7, &ratio9_7, &ratio9_7, &ratio9_7, &ratio9_7, &ratio9_7, &ratio7_5, &ratio7_5, &ratio7_5, 
&ratio7_5, &ratio7_5, &ratio7_5, &ratio7_5, &ratio75_49, &ratio75_49, &ratio75_49, &ratio75_49, &ratio75_49, &ratio75_49, &ratio75_49, &ratio9_5, 
&ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio49_25, &ratio49_25, &ratio49_25, &ratio49_25, &ratio49_25, &ratio49_25, 
&ratio49_25, &ratio7_3, &ratio7_3, &ratio7_3, &ratio7_3, &ratio7_3, &ratio7_3, &ratio7_3, &ratio63_25, &ratio63_25, &ratio63_25, &ratio63_25, 
&ratio63_25, &ratio63_25, &ratio63_25, &ratio25_9, &ratio25_9, &ratio25_9, &ratio25_9, &ratio25_9, &ratio25_9, &ratio25_9, &ratio25_9, &ratio63_25, 
&ratio63_25, &ratio63_25, &ratio63_25, &ratio63_25, &ratio63_25, &ratio63_25, &ratio15_7, &ratio15_7, &ratio15_7, &ratio15_7, &ratio15_7, &ratio15_7, 
&ratio15_7, &ratio49_25, &ratio49_25, &ratio49_25, &ratio49_25, &ratio49_25, &ratio49_25, &ratio49_25, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, 
&ratio5_3, &ratio5_3, &ratio5_3, &ratio75_49, &ratio75_49, &ratio75_49, &ratio75_49, &ratio75_49, &ratio75_49, &ratio75_49, &ratio9_7, &ratio9_7, 
&ratio9_7, &ratio9_7, &ratio9_7, &ratio9_7, &ratio9_7, &ratio25_21, &ratio25_21, &ratio25_21, &ratio25_21, &ratio25_21, &ratio25_21, &ratio25_21, 
&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1}; 



static const ScaleNote * const modesofroota[128] = {&ratio3_128, &ratio27_1024, &ratio15_512, &ratio15_512, &ratio1_32, &ratio1_32, &ratio9_256, &ratio5_128, &ratio1_24, &ratio1_24, &ratio3_64, &ratio3_64, &ratio3_64, 
&ratio27_512, &ratio15_256, &ratio15_256, &ratio1_16, &ratio1_16, &ratio9_128, &ratio5_64, &ratio1_12, &ratio1_12, &ratio3_32, &ratio3_32, &ratio3_32, 
&ratio27_256, &ratio15_128, &ratio15_128, &ratio1_8, &ratio1_8, &ratio9_64, &ratio5_32, &ratio1_6, &ratio1_6, &ratio3_16, &ratio3_16, &ratio3_16, 
&ratio27_128, &ratio15_64, &ratio15_64, &ratio1_4, &ratio1_4, &ratio9_32, &ratio5_16, &ratio1_3, &ratio1_3, &ratio3_8, &ratio3_8, &ratio3_8, 
&ratio27_64, &ratio15_32, &ratio15_32, &ratio1_2, &ratio1_2, &ratio9_16, &ratio5_8, &ratio2_3, &ratio2_3, &ratio3_4, &ratio3_4, &ratio3_4, 
&ratio27_32, &ratio15_16, &ratio15_16, &ratio1_1, &ratio1_1, &ratio9_8, &ratio5_4, &ratio4_3, &ratio4_3, &ratio3_2, &ratio3_2, &ratio3_2, 
&ratio27_16, &ratio15_8, &ratio15_8, &ratio2_1, &ratio2_1, &ratio9_4, &ratio5_2, &ratio8_3, &ratio8_3, &ratio3_1, &ratio3_1, &ratio3_1, 
&ratio27_8, &ratio15_4, &ratio15_4, &ratio4_1, &ratio4_1, &ratio9_2, &ratio5_1, &ratio16_3, &ratio16_3, &ratio6_1, &ratio6_1, &ratio6_1, 
&ratio27_4, &ratio15_2, &ratio15_2, &ratio8_1, &ratio8_1, &ratio9_1, &ratio10_1, &ratio32_3, &ratio32_3, &ratio12_1, &ratio12_1, &ratio12_1, 
&ratio27_2, &ratio15_1, &ratio15_1, &ratio16_1, &ratio16_1, &ratio18_1, &ratio20_1, &ratio64_3, &ratio64_3, &ratio24_1, &ratio24_1, &ratio24_1, 
&ratio27_1, &ratio30_1, &ratio30_1, &ratio32_1, &ratio32_1, &ratio36_1, &ratio40_1}; 

static const ScaleNote * const modesofrootb[128] = {&ratio3_128, &ratio27_1024, &ratio9_320, &ratio9_320, &ratio1_32, &ratio1_32, &ratio9_256, &ratio19_512, &ratio1_24, &ratio1_24, &ratio3_64, &ratio3_64, &ratio3_64, 
&ratio27_512, &ratio9_160, &ratio9_160, &ratio1_16, &ratio1_16, &ratio9_128, &ratio19_256, &ratio1_12, &ratio1_12, &ratio3_32, &ratio3_32, &ratio3_32, 
&ratio27_256, &ratio9_80, &ratio9_80, &ratio1_8, &ratio1_8, &ratio9_64, &ratio19_128, &ratio1_6, &ratio1_6, &ratio3_16, &ratio3_16, &ratio3_16, 
&ratio27_128, &ratio9_40, &ratio9_40, &ratio1_4, &ratio1_4, &ratio9_32, &ratio19_64, &ratio1_3, &ratio1_3, &ratio3_8, &ratio3_8, &ratio3_8, 
&ratio27_64, &ratio9_20, &ratio9_20, &ratio1_2, &ratio1_2, &ratio9_16, &ratio19_32, &ratio2_3, &ratio2_3, &ratio3_4, &ratio3_4, &ratio3_4, 
&ratio27_32, &ratio9_10, &ratio9_10, &ratio1_1, &ratio1_1, &ratio9_8, &ratio19_16, &ratio4_3, &ratio4_3, &ratio3_2, &ratio3_2, &ratio3_2, 
&ratio27_16, &ratio9_5, &ratio9_5, &ratio2_1, &ratio2_1, &ratio9_4, &ratio19_8, &ratio8_3, &ratio8_3, &ratio3_1, &ratio3_1, &ratio3_1, 
&ratio27_8, &ratio18_5, &ratio18_5, &ratio4_1, &ratio4_1, &ratio9_2, &ratio19_4, &ratio16_3, &ratio16_3, &ratio6_1, &ratio6_1, &ratio6_1, 
&ratio27_4, &ratio36_5, &ratio36_5, &ratio8_1, &ratio8_1, &ratio9_1, &ratio19_2, &ratio32_3, &ratio32_3, &ratio12_1, &ratio12_1, &ratio12_1, 
&ratio27_2, &ratio72_5, &ratio72_5, &ratio16_1, &ratio16_1, &ratio18_1, &ratio19_1, &ratio64_3, &ratio64_3, &ratio24_1, &ratio24_1, &ratio24_1, 
&ratio27_1, &ratio144_5, &ratio144_5, &ratio32_1, &ratio32_1, &ratio36_1, &ratio38_1}; 

static const ScaleNote * const modesofrootc[128] = {&ratio1_40, &ratio1_40, &ratio9_320, &ratio9_320, &ratio1_32, &ratio17_512, &ratio19_512, &ratio19_512, &ratio1_24, &ratio1_24, &ratio3_64, &ratio3_64, &ratio1_20, 
&ratio1_20, &ratio9_160, &ratio9_160, &ratio1_16, &ratio17_256, &ratio19_256, &ratio19_256, &ratio1_12, &ratio1_12, &ratio3_32, &ratio3_32, &ratio1_10, 
&ratio1_10, &ratio9_80, &ratio9_80, &ratio1_8, &ratio17_128, &ratio19_128, &ratio19_128, &ratio1_6, &ratio1_6, &ratio3_16, &ratio3_16, &ratio1_5, 
&ratio1_5, &ratio9_40, &ratio9_40, &ratio1_4, &ratio17_64, &ratio19_64, &ratio19_64, &ratio1_3, &ratio1_3, &ratio3_8, &ratio3_8, &ratio2_5, 
&ratio2_5, &ratio9_20, &ratio9_20, &ratio1_2, &ratio17_32, &ratio19_32, &ratio19_32, &ratio2_3, &ratio2_3, &ratio3_4, &ratio3_4, &ratio4_5, 
&ratio4_5, &ratio9_10, &ratio9_10, &ratio1_1, &ratio17_16, &ratio19_16, &ratio19_16, &ratio4_3, &ratio4_3, &ratio3_2, &ratio3_2, &ratio8_5, 
&ratio8_5, &ratio9_5, &ratio9_5, &ratio2_1, &ratio17_8, &ratio19_8, &ratio19_8, &ratio8_3, &ratio8_3, &ratio3_1, &ratio3_1, &ratio16_5, 
&ratio16_5, &ratio18_5, &ratio18_5, &ratio4_1, &ratio17_4, &ratio19_4, &ratio19_4, &ratio16_3, &ratio16_3, &ratio6_1, &ratio6_1, &ratio32_5, 
&ratio32_5, &ratio36_5, &ratio36_5, &ratio8_1, &ratio17_2, &ratio19_2, &ratio19_2, &ratio32_3, &ratio32_3, &ratio12_1, &ratio12_1, &ratio64_5, 
&ratio64_5, &ratio72_5, &ratio72_5, &ratio16_1, &ratio17_1, &ratio19_1, &ratio19_1, &ratio64_3, &ratio64_3, &ratio24_1, &ratio24_1, &ratio128_5, 
&ratio128_5, &ratio144_5, &ratio144_5, &ratio32_1, &ratio34_1, &ratio38_1, &ratio38_1}; 

static const ScaleNote * const modesofrootd[128] = {&ratio3_128, &ratio27_1024, &ratio15_512, &ratio15_512, &ratio1_32, &ratio1_32, &ratio9_256, &ratio5_128, &ratio5_128, &ratio7_160, &ratio7_160, &ratio3_64, &ratio3_64, 
&ratio27_512, &ratio15_256, &ratio15_256, &ratio1_16, &ratio1_16, &ratio9_128, &ratio5_64, &ratio5_64, &ratio7_80, &ratio7_80, &ratio3_32, &ratio3_32, 
&ratio27_256, &ratio15_128, &ratio15_128, &ratio1_8, &ratio1_8, &ratio9_64, &ratio5_32, &ratio5_32, &ratio7_40, &ratio7_40, &ratio3_16, &ratio3_16, 
&ratio27_128, &ratio15_64, &ratio15_64, &ratio1_4, &ratio1_4, &ratio9_32, &ratio5_16, &ratio5_16, &ratio7_20, &ratio7_20, &ratio3_8, &ratio3_8, 
&ratio27_64, &ratio15_32, &ratio15_32, &ratio1_2, &ratio1_2, &ratio9_16, &ratio5_8, &ratio5_8, &ratio7_10, &ratio7_10, &ratio3_4, &ratio3_4, 
&ratio27_32, &ratio15_16, &ratio15_16, &ratio1_1, &ratio1_1, &ratio9_8, &ratio5_4, &ratio5_4, &ratio7_5, &ratio7_5, &ratio3_2, &ratio3_2, 
&ratio27_16, &ratio15_8, &ratio15_8, &ratio2_1, &ratio2_1, &ratio9_4, &ratio5_2, &ratio5_2, &ratio14_5, &ratio14_5, &ratio3_1, &ratio3_1, 
&ratio27_8, &ratio15_4, &ratio15_4, &ratio4_1, &ratio4_1, &ratio9_2, &ratio5_1, &ratio5_1, &ratio28_5, &ratio28_5, &ratio6_1, &ratio6_1, 
&ratio27_4, &ratio15_2, &ratio15_2, &ratio8_1, &ratio8_1, &ratio9_1, &ratio10_1, &ratio10_1, &ratio56_5, &ratio56_5, &ratio12_1, &ratio12_1, 
&ratio27_2, &ratio15_1, &ratio15_1, &ratio16_1, &ratio16_1, &ratio18_1, &ratio20_1, &ratio20_1, &ratio112_5, &ratio112_5, &ratio24_1, &ratio24_1, 
&ratio27_1, &ratio30_1, &ratio30_1, &ratio32_1, &ratio32_1, &ratio36_1, &ratio40_1}; 

static const ScaleNote * const modesofroote[128] = {&ratio3_128, &ratio27_1024, &ratio9_320, &ratio9_320, &ratio1_32, &ratio1_32, &ratio9_256, &ratio5_128, &ratio1_24, &ratio1_24, &ratio3_64, &ratio3_64, &ratio3_64, 
&ratio27_512, &ratio9_160, &ratio9_160, &ratio1_16, &ratio1_16, &ratio9_128, &ratio5_64, &ratio1_12, &ratio1_12, &ratio3_32, &ratio3_32, &ratio3_32, 
&ratio27_256, &ratio9_80, &ratio9_80, &ratio1_8, &ratio1_8, &ratio9_64, &ratio5_32, &ratio1_6, &ratio1_6, &ratio3_16, &ratio3_16, &ratio3_16, 
&ratio27_128, &ratio9_40, &ratio9_40, &ratio1_4, &ratio1_4, &ratio9_32, &ratio5_16, &ratio1_3, &ratio1_3, &ratio3_8, &ratio3_8, &ratio3_8, 
&ratio27_64, &ratio9_20, &ratio9_20, &ratio1_2, &ratio1_2, &ratio9_16, &ratio5_8, &ratio2_3, &ratio2_3, &ratio3_4, &ratio3_4, &ratio3_4, 
&ratio27_32, &ratio9_10, &ratio9_10, &ratio1_1, &ratio1_1, &ratio9_8, &ratio5_4, &ratio4_3, &ratio4_3, &ratio3_2, &ratio3_2, &ratio3_2, 
&ratio27_16, &ratio9_5, &ratio9_5, &ratio2_1, &ratio2_1, &ratio9_4, &ratio5_2, &ratio8_3, &ratio8_3, &ratio3_1, &ratio3_1, &ratio3_1, 
&ratio27_8, &ratio18_5, &ratio18_5, &ratio4_1, &ratio4_1, &ratio9_2, &ratio5_1, &ratio16_3, &ratio16_3, &ratio6_1, &ratio6_1, &ratio6_1, 
&ratio27_4, &ratio36_5, &ratio36_5, &ratio8_1, &ratio8_1, &ratio9_1, &ratio10_1, &ratio32_3, &ratio32_3, &ratio12_1, &ratio12_1, &ratio12_1, 
&ratio27_2, &ratio72_5, &ratio72_5, &ratio16_1, &ratio16_1, &ratio18_1, &ratio20_1, &ratio64_3, &ratio64_3, &ratio24_1, &ratio24_1, &ratio24_1, 
&ratio27_1, &ratio144_5, &ratio144_5, &ratio32_1, &ratio32_1, &ratio36_1, &ratio40_1}; 

static const ScaleNote * const modesofrootf[128] = {&ratio1_40, &ratio1_40, &ratio9_320, &ratio9_320, &ratio1_32, &ratio1_32, &ratio9_256, &ratio19_512, &ratio1_24, &ratio1_24, &ratio3_64, &ratio3_64, &ratio1_20, 
&ratio1_20, &ratio9_160, &ratio9_160, &ratio1_16, &ratio1_16, &ratio9_128, &ratio19_256, &ratio1_12, &ratio1_12, &ratio3_32, &ratio3_32, &ratio1_10, 
&ratio1_10, &ratio9_80, &ratio9_80, &ratio1_8, &ratio1_8, &ratio9_64, &ratio19_128, &ratio1_6, &ratio1_6, &ratio3_16, &ratio3_16, &ratio1_5, 
&ratio1_5, &ratio9_40, &ratio9_40, &ratio1_4, &ratio1_4, &ratio9_32, &ratio19_64, &ratio1_3, &ratio1_3, &ratio3_8, &ratio3_8, &ratio2_5, 
&ratio2_5, &ratio9_20, &ratio9_20, &ratio1_2, &ratio1_2, &ratio9_16, &ratio19_32, &ratio2_3, &ratio2_3, &ratio3_4, &ratio3_4, &ratio4_5, 
&ratio4_5, &ratio9_10, &ratio9_10, &ratio1_1, &ratio1_1, &ratio9_8, &ratio19_16, &ratio4_3, &ratio4_3, &ratio3_2, &ratio3_2, &ratio8_5, 
&ratio8_5, &ratio9_5, &ratio9_5, &ratio2_1, &ratio2_1, &ratio9_4, &ratio19_8, &ratio8_3, &ratio8_3, &ratio3_1, &ratio3_1, &ratio16_5, 
&ratio16_5, &ratio18_5, &ratio18_5, &ratio4_1, &ratio4_1, &ratio9_2, &ratio19_4, &ratio16_3, &ratio16_3, &ratio6_1, &ratio6_1, &ratio32_5, 
&ratio32_5, &ratio36_5, &ratio36_5, &ratio8_1, &ratio8_1, &ratio9_1, &ratio19_2, &ratio32_3, &ratio32_3, &ratio12_1, &ratio12_1, &ratio64_5, 
&ratio64_5, &ratio72_5, &ratio72_5, &ratio16_1, &ratio16_1, &ratio18_1, &ratio19_1, &ratio64_3, &ratio64_3, &ratio24_1, &ratio24_1, &ratio128_5, 
&ratio128_5, &ratio144_5, &ratio144_5, &ratio32_1, &ratio32_1, &ratio36_1, &ratio38_1}; 

static const ScaleNote * const modesofrootg[128] = {&ratio1_40, &ratio1_40, &ratio9_320, &ratio9_320, &ratio1_32, &ratio17_512, &ratio19_512, &ratio19_512, &ratio1_24, &ratio7_160, &ratio7_160, &ratio1_20, &ratio1_20, 
&ratio1_20, &ratio9_160, &ratio9_160, &ratio1_16, &ratio17_256, &ratio19_256, &ratio19_256, &ratio1_12, &ratio7_80, &ratio7_80, &ratio1_10, &ratio1_10, 
&ratio1_10, &ratio9_80, &ratio9_80, &ratio1_8, &ratio17_128, &ratio19_128, &ratio19_128, &ratio1_6, &ratio7_40, &ratio7_40, &ratio1_5, &ratio1_5, 
&ratio1_5, &ratio9_40, &ratio9_40, &ratio1_4, &ratio17_64, &ratio19_64, &ratio19_64, &ratio1_3, &ratio7_20, &ratio7_20, &ratio2_5, &ratio2_5, 
&ratio2_5, &ratio9_20, &ratio9_20, &ratio1_2, &ratio17_32, &ratio19_32, &ratio19_32, &ratio2_3, &ratio7_10, &ratio7_10, &ratio4_5, &ratio4_5, 
&ratio4_5, &ratio9_10, &ratio9_10, &ratio1_1, &ratio17_16, &ratio19_16, &ratio19_16, &ratio4_3, &ratio7_5, &ratio7_5, &ratio8_5, &ratio8_5, 
&ratio8_5, &ratio9_5, &ratio9_5, &ratio2_1, &ratio17_8, &ratio19_8, &ratio19_8, &ratio8_3, &ratio14_5, &ratio14_5, &ratio16_5, &ratio16_5, 
&ratio16_5, &ratio18_5, &ratio18_5, &ratio4_1, &ratio17_4, &ratio19_4, &ratio19_4, &ratio16_3, &ratio28_5, &ratio28_5, &ratio32_5, &ratio32_5, 
&ratio32_5, &ratio36_5, &ratio36_5, &ratio8_1, &ratio17_2, &ratio19_2, &ratio19_2, &ratio32_3, &ratio56_5, &ratio56_5, &ratio64_5, &ratio64_5, 
&ratio64_5, &ratio72_5, &ratio72_5, &ratio16_1, &ratio17_1, &ratio19_1, &ratio19_1, &ratio64_3, &ratio112_5, &ratio112_5, &ratio128_5, &ratio128_5, 
&ratio128_5, &ratio144_5, &ratio144_5, &ratio32_1, &ratio34_1, &ratio38_1, &ratio38_1}; 

static const ScaleNote * const modesofrooth[128] = {&ratio1_40, &ratio1_40, &ratio9_320, &ratio9_320, &ratio1_32, &ratio1_32, &ratio9_256, &ratio5_128, &ratio5_128, &ratio7_160, &ratio7_160, &ratio1_20, &ratio1_20, 
&ratio1_20, &ratio9_160, &ratio9_160, &ratio1_16, &ratio1_16, &ratio9_128, &ratio5_64, &ratio5_64, &ratio7_80, &ratio7_80, &ratio1_10, &ratio1_10, 
&ratio1_10, &ratio9_80, &ratio9_80, &ratio1_8, &ratio1_8, &ratio9_64, &ratio5_32, &ratio5_32, &ratio7_40, &ratio7_40, &ratio1_5, &ratio1_5, 
&ratio1_5, &ratio9_40, &ratio9_40, &ratio1_4, &ratio1_4, &ratio9_32, &ratio5_16, &ratio5_16, &ratio7_20, &ratio7_20, &ratio2_5, &ratio2_5, 
&ratio2_5, &ratio9_20, &ratio9_20, &ratio1_2, &ratio1_2, &ratio9_16, &ratio5_8, &ratio5_8, &ratio7_10, &ratio7_10, &ratio4_5, &ratio4_5, 
&ratio4_5, &ratio9_10, &ratio9_10, &ratio1_1, &ratio1_1, &ratio9_8, &ratio5_4, &ratio5_4, &ratio7_5, &ratio7_5, &ratio8_5, &ratio8_5, 
&ratio8_5, &ratio9_5, &ratio9_5, &ratio2_1, &ratio2_1, &ratio9_4, &ratio5_2, &ratio5_2, &ratio14_5, &ratio14_5, &ratio16_5, &ratio16_5, 
&ratio16_5, &ratio18_5, &ratio18_5, &ratio4_1, &ratio4_1, &ratio9_2, &ratio5_1, &ratio5_1, &ratio28_5, &ratio28_5, &ratio32_5, &ratio32_5, 
&ratio32_5, &ratio36_5, &ratio36_5, &ratio8_1, &ratio8_1, &ratio9_1, &ratio10_1, &ratio10_1, &ratio56_5, &ratio56_5, &ratio64_5, &ratio64_5, 
&ratio64_5, &ratio72_5, &ratio72_5, &ratio16_1, &ratio16_1, &ratio18_1, &ratio20_1, &ratio20_1, &ratio112_5, &ratio112_5, &ratio128_5, &ratio128_5, 
&ratio128_5, &ratio144_5, &ratio144_5, &ratio32_1, &ratio32_1, &ratio36_1, &ratio40_1}; 



static const ScaleNote * const tetrad_inversionsa[128] = {&ratio3_128, &ratio15_512, &ratio15_512, &ratio15_512, &ratio1_32, &ratio1_32, &ratio5_128, &ratio5_128, &ratio5_128, &ratio5_128, &ratio3_64, &ratio3_64, &ratio3_64, 
&ratio15_256, &ratio15_256, &ratio15_256, &ratio1_16, &ratio1_16, &ratio5_64, &ratio5_64, &ratio5_64, &ratio5_64, &ratio3_32, &ratio3_32, &ratio3_32, 
&ratio15_128, &ratio15_128, &ratio15_128, &ratio1_8, &ratio1_8, &ratio5_32, &ratio5_32, &ratio5_32, &ratio5_32, &ratio3_16, &ratio3_16, &ratio3_16, 
&ratio15_64, &ratio15_64, &ratio15_64, &ratio1_4, &ratio1_4, &ratio5_16, &ratio5_16, &ratio5_16, &ratio5_16, &ratio3_8, &ratio3_8, &ratio3_8, 
&ratio15_32, &ratio15_32, &ratio15_32, &ratio1_2, &ratio1_2, &ratio5_8, &ratio5_8, &ratio5_8, &ratio5_8, &ratio3_4, &ratio3_4, &ratio3_4, 
&ratio15_16, &ratio15_16, &ratio15_16, &ratio1_1, &ratio1_1, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio3_2, &ratio3_2, &ratio3_2, 
&ratio15_8, &ratio15_8, &ratio15_8, &ratio2_1, &ratio2_1, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio3_1, &ratio3_1, &ratio3_1, 
&ratio15_4, &ratio15_4, &ratio15_4, &ratio4_1, &ratio4_1, &ratio5_1, &ratio5_1, &ratio5_1, &ratio5_1, &ratio6_1, &ratio6_1, &ratio6_1, 
&ratio15_2, &ratio15_2, &ratio15_2, &ratio8_1, &ratio8_1, &ratio10_1, &ratio10_1, &ratio10_1, &ratio10_1, &ratio12_1, &ratio12_1, &ratio12_1, 
&ratio15_1, &ratio15_1, &ratio15_1, &ratio16_1, &ratio16_1, &ratio20_1, &ratio20_1, &ratio20_1, &ratio20_1, &ratio24_1, &ratio24_1, &ratio24_1, 
&ratio30_1, &ratio30_1, &ratio30_1, &ratio32_1, &ratio32_1, &ratio40_1, &ratio40_1}; 

static const ScaleNote * const tetrad_inversionsb[128] = {&ratio5_192, &ratio5_192, &ratio5_192, &ratio5_192, &ratio1_32, &ratio1_32, &ratio5_128, &ratio5_128, &ratio1_24, &ratio1_24, &ratio1_24, &ratio5_96, &ratio5_96, 
&ratio5_96, &ratio5_96, &ratio5_96, &ratio1_16, &ratio1_16, &ratio5_64, &ratio5_64, &ratio1_12, &ratio1_12, &ratio1_12, &ratio5_48, &ratio5_48, 
&ratio5_48, &ratio5_48, &ratio5_48, &ratio1_8, &ratio1_8, &ratio5_32, &ratio5_32, &ratio1_6, &ratio1_6, &ratio1_6, &ratio5_24, &ratio5_24, 
&ratio5_24, &ratio5_24, &ratio5_24, &ratio1_4, &ratio1_4, &ratio5_16, &ratio5_16, &ratio1_3, &ratio1_3, &ratio1_3, &ratio5_12, &ratio5_12, 
&ratio5_12, &ratio5_12, &ratio5_12, &ratio1_2, &ratio1_2, &ratio5_8, &ratio5_8, &ratio2_3, &ratio2_3, &ratio2_3, &ratio5_6, &ratio5_6, 
&ratio5_6, &ratio5_6, &ratio5_6, &ratio1_1, &ratio1_1, &ratio5_4, &ratio5_4, &ratio4_3, &ratio4_3, &ratio4_3, &ratio5_3, &ratio5_3, 
&ratio5_3, &ratio5_3, &ratio5_3, &ratio2_1, &ratio2_1, &ratio5_2, &ratio5_2, &ratio8_3, &ratio8_3, &ratio8_3, &ratio10_3, &ratio10_3, 
&ratio10_3, &ratio10_3, &ratio10_3, &ratio4_1, &ratio4_1, &ratio5_1, &ratio5_1, &ratio16_3, &ratio16_3, &ratio16_3, &ratio20_3, &ratio20_3, 
&ratio20_3, &ratio20_3, &ratio20_3, &ratio8_1, &ratio8_1, &ratio10_1, &ratio10_1, &ratio32_3, &ratio32_3, &ratio32_3, &ratio40_3, &ratio40_3, 
&ratio40_3, &ratio40_3, &ratio40_3, &ratio16_1, &ratio16_1, &ratio20_1, &ratio20_1, &ratio64_3, &ratio64_3, &ratio64_3, &ratio80_3, &ratio80_3, 
&ratio80_3, &ratio80_3, &ratio80_3, &ratio32_1, &ratio32_1, &ratio40_1, &ratio40_1}; 

static const ScaleNote * const tetrad_inversionsc[128] = {&ratio1_40, &ratio1_40, &ratio1_40, &ratio1_40, &ratio1_32, &ratio1_32, &ratio3_80, &ratio3_80, &ratio3_80, &ratio3_80, &ratio3_64, &ratio3_64, &ratio1_20, 
&ratio1_20, &ratio1_20, &ratio1_20, &ratio1_16, &ratio1_16, &ratio3_40, &ratio3_40, &ratio3_40, &ratio3_40, &ratio3_32, &ratio3_32, &ratio1_10, 
&ratio1_10, &ratio1_10, &ratio1_10, &ratio1_8, &ratio1_8, &ratio3_20, &ratio3_20, &ratio3_20, &ratio3_20, &ratio3_16, &ratio3_16, &ratio1_5, 
&ratio1_5, &ratio1_5, &ratio1_5, &ratio1_4, &ratio1_4, &ratio3_10, &ratio3_10, &ratio3_10, &ratio3_10, &ratio3_8, &ratio3_8, &ratio2_5, 
&ratio2_5, &ratio2_5, &ratio2_5, &ratio1_2, &ratio1_2, &ratio3_5, &ratio3_5, &ratio3_5, &ratio3_5, &ratio3_4, &ratio3_4, &ratio4_5, 
&ratio4_5, &ratio4_5, &ratio4_5, &ratio1_1, &ratio1_1, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio3_2, &ratio3_2, &ratio8_5, 
&ratio8_5, &ratio8_5, &ratio8_5, &ratio2_1, &ratio2_1, &ratio12_5, &ratio12_5, &ratio12_5, &ratio12_5, &ratio3_1, &ratio3_1, &ratio16_5, 
&ratio16_5, &ratio16_5, &ratio16_5, &ratio4_1, &ratio4_1, &ratio24_5, &ratio24_5, &ratio24_5, &ratio24_5, &ratio6_1, &ratio6_1, &ratio32_5, 
&ratio32_5, &ratio32_5, &ratio32_5, &ratio8_1, &ratio8_1, &ratio48_5, &ratio48_5, &ratio48_5, &ratio48_5, &ratio12_1, &ratio12_1, &ratio64_5, 
&ratio64_5, &ratio64_5, &ratio64_5, &ratio16_1, &ratio16_1, &ratio96_5, &ratio96_5, &ratio96_5, &ratio96_5, &ratio24_1, &ratio24_1, &ratio128_5, 
&ratio128_5, &ratio128_5, &ratio128_5, &ratio32_1, &ratio32_1, &ratio192_5, &ratio192_5}; 

static const ScaleNote * const tetrad_inversionsd[128] = {&ratio1_40, &ratio1_40, &ratio1_40, &ratio1_32, &ratio1_32, &ratio1_32, &ratio1_32, &ratio1_24, &ratio1_24, &ratio1_24, &ratio1_24, &ratio1_20, &ratio1_20, 
&ratio1_20, &ratio1_20, &ratio1_16, &ratio1_16, &ratio1_16, &ratio1_16, &ratio1_12, &ratio1_12, &ratio1_12, &ratio1_12, &ratio1_10, &ratio1_10, 
&ratio1_10, &ratio1_10, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_5, &ratio1_5, 
&ratio1_5, &ratio1_5, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio2_5, &ratio2_5, 
&ratio2_5, &ratio2_5, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio4_5, &ratio4_5, 
&ratio4_5, &ratio4_5, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio8_5, &ratio8_5, 
&ratio8_5, &ratio8_5, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio16_5, &ratio16_5, 
&ratio16_5, &ratio16_5, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio16_3, &ratio16_3, &ratio16_3, &ratio16_3, &ratio32_5, &ratio32_5, 
&ratio32_5, &ratio32_5, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio32_3, &ratio32_3, &ratio32_3, &ratio32_3, &ratio64_5, &ratio64_5, 
&ratio64_5, &ratio64_5, &ratio16_1, &ratio16_1, &ratio16_1, &ratio16_1, &ratio64_3, &ratio64_3, &ratio64_3, &ratio64_3, &ratio128_5, &ratio128_5, 
&ratio128_5, &ratio128_5, &ratio32_1, &ratio32_1, &ratio32_1, &ratio32_1, &ratio128_3}; 

static const ScaleNote * const tetrad_inversionse[128] = {&ratio3_128, &ratio9_320, &ratio9_320, &ratio9_320, &ratio1_32, &ratio1_32, &ratio3_80, &ratio3_80, &ratio3_80, &ratio3_80, &ratio3_64, &ratio3_64, &ratio3_64, 
&ratio9_160, &ratio9_160, &ratio9_160, &ratio1_16, &ratio1_16, &ratio3_40, &ratio3_40, &ratio3_40, &ratio3_40, &ratio3_32, &ratio3_32, &ratio3_32, 
&ratio9_80, &ratio9_80, &ratio9_80, &ratio1_8, &ratio1_8, &ratio3_20, &ratio3_20, &ratio3_20, &ratio3_20, &ratio3_16, &ratio3_16, &ratio3_16, 
&ratio9_40, &ratio9_40, &ratio9_40, &ratio1_4, &ratio1_4, &ratio3_10, &ratio3_10, &ratio3_10, &ratio3_10, &ratio3_8, &ratio3_8, &ratio3_8, 
&ratio9_20, &ratio9_20, &ratio9_20, &ratio1_2, &ratio1_2, &ratio3_5, &ratio3_5, &ratio3_5, &ratio3_5, &ratio3_4, &ratio3_4, &ratio3_4, 
&ratio9_10, &ratio9_10, &ratio9_10, &ratio1_1, &ratio1_1, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio3_2, &ratio3_2, &ratio3_2, 
&ratio9_5, &ratio9_5, &ratio9_5, &ratio2_1, &ratio2_1, &ratio12_5, &ratio12_5, &ratio12_5, &ratio12_5, &ratio3_1, &ratio3_1, &ratio3_1, 
&ratio18_5, &ratio18_5, &ratio18_5, &ratio4_1, &ratio4_1, &ratio24_5, &ratio24_5, &ratio24_5, &ratio24_5, &ratio6_1, &ratio6_1, &ratio6_1, 
&ratio36_5, &ratio36_5, &ratio36_5, &ratio8_1, &ratio8_1, &ratio48_5, &ratio48_5, &ratio48_5, &ratio48_5, &ratio12_1, &ratio12_1, &ratio12_1, 
&ratio72_5, &ratio72_5, &ratio72_5, &ratio16_1, &ratio16_1, &ratio96_5, &ratio96_5, &ratio96_5, &ratio96_5, &ratio24_1, &ratio24_1, &ratio24_1, 
&ratio144_5, &ratio144_5, &ratio144_5, &ratio32_1, &ratio32_1, &ratio192_5, &ratio192_5}; 

static const ScaleNote * const tetrad_inversionsf[128] = {&ratio1_40, &ratio1_40, &ratio1_40, &ratio1_40, &ratio1_32, &ratio1_32, &ratio3_80, &ratio3_80, &ratio1_24, &ratio1_24, &ratio1_24, &ratio1_20, &ratio1_20, 
&ratio1_20, &ratio1_20, &ratio1_20, &ratio1_16, &ratio1_16, &ratio3_40, &ratio3_40, &ratio1_12, &ratio1_12, &ratio1_12, &ratio1_10, &ratio1_10, 
&ratio1_10, &ratio1_10, &ratio1_10, &ratio1_8, &ratio1_8, &ratio3_20, &ratio3_20, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_5, &ratio1_5, 
&ratio1_5, &ratio1_5, &ratio1_5, &ratio1_4, &ratio1_4, &ratio3_10, &ratio3_10, &ratio1_3, &ratio1_3, &ratio1_3, &ratio2_5, &ratio2_5, 
&ratio2_5, &ratio2_5, &ratio2_5, &ratio1_2, &ratio1_2, &ratio3_5, &ratio3_5, &ratio2_3, &ratio2_3, &ratio2_3, &ratio4_5, &ratio4_5, 
&ratio4_5, &ratio4_5, &ratio4_5, &ratio1_1, &ratio1_1, &ratio6_5, &ratio6_5, &ratio4_3, &ratio4_3, &ratio4_3, &ratio8_5, &ratio8_5, 
&ratio8_5, &ratio8_5, &ratio8_5, &ratio2_1, &ratio2_1, &ratio12_5, &ratio12_5, &ratio8_3, &ratio8_3, &ratio8_3, &ratio16_5, &ratio16_5, 
&ratio16_5, &ratio16_5, &ratio16_5, &ratio4_1, &ratio4_1, &ratio24_5, &ratio24_5, &ratio16_3, &ratio16_3, &ratio16_3, &ratio32_5, &ratio32_5, 
&ratio32_5, &ratio32_5, &ratio32_5, &ratio8_1, &ratio8_1, &ratio48_5, &ratio48_5, &ratio32_3, &ratio32_3, &ratio32_3, &ratio64_5, &ratio64_5, 
&ratio64_5, &ratio64_5, &ratio64_5, &ratio16_1, &ratio16_1, &ratio96_5, &ratio96_5, &ratio64_3, &ratio64_3, &ratio64_3, &ratio128_5, &ratio128_5, 
&ratio128_5, &ratio128_5, &ratio128_5, &ratio32_1, &ratio32_1, &ratio192_5, &ratio192_5}; 

static const ScaleNote * const tetrad_inversionsg[128] = {&ratio5_192, &ratio5_192, &ratio5_192, &ratio5_192, &ratio1_32, &ratio1_32, &ratio5_128, &ratio5_128, &ratio5_128, &ratio5_128, &ratio3_64, &ratio3_64, &ratio5_96, 
&ratio5_96, &ratio5_96, &ratio5_96, &ratio1_16, &ratio1_16, &ratio5_64, &ratio5_64, &ratio5_64, &ratio5_64, &ratio3_32, &ratio3_32, &ratio5_48, 
&ratio5_48, &ratio5_48, &ratio5_48, &ratio1_8, &ratio1_8, &ratio5_32, &ratio5_32, &ratio5_32, &ratio5_32, &ratio3_16, &ratio3_16, &ratio5_24, 
&ratio5_24, &ratio5_24, &ratio5_24, &ratio1_4, &ratio1_4, &ratio5_16, &ratio5_16, &ratio5_16, &ratio5_16, &ratio3_8, &ratio3_8, &ratio5_12, 
&ratio5_12, &ratio5_12, &ratio5_12, &ratio1_2, &ratio1_2, &ratio5_8, &ratio5_8, &ratio5_8, &ratio5_8, &ratio3_4, &ratio3_4, &ratio5_6, 
&ratio5_6, &ratio5_6, &ratio5_6, &ratio1_1, &ratio1_1, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio3_2, &ratio3_2, &ratio5_3, 
&ratio5_3, &ratio5_3, &ratio5_3, &ratio2_1, &ratio2_1, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio3_1, &ratio3_1, &ratio10_3, 
&ratio10_3, &ratio10_3, &ratio10_3, &ratio4_1, &ratio4_1, &ratio5_1, &ratio5_1, &ratio5_1, &ratio5_1, &ratio6_1, &ratio6_1, &ratio20_3, 
&ratio20_3, &ratio20_3, &ratio20_3, &ratio8_1, &ratio8_1, &ratio10_1, &ratio10_1, &ratio10_1, &ratio10_1, &ratio12_1, &ratio12_1, &ratio40_3, 
&ratio40_3, &ratio40_3, &ratio40_3, &ratio16_1, &ratio16_1, &ratio20_1, &ratio20_1, &ratio20_1, &ratio20_1, &ratio24_1, &ratio24_1, &ratio80_3, 
&ratio80_3, &ratio80_3, &ratio80_3, &ratio32_1, &ratio32_1, &ratio40_1, &ratio40_1}; 

static const ScaleNote * const tetrad_inversionsh[128] = {&ratio5_192, &ratio5_192, &ratio5_192, &ratio1_32, &ratio1_32, &ratio1_32, &ratio1_32, &ratio1_24, &ratio1_24, &ratio1_24, &ratio1_24, &ratio5_96, &ratio5_96, 
&ratio5_96, &ratio5_96, &ratio1_16, &ratio1_16, &ratio1_16, &ratio1_16, &ratio1_12, &ratio1_12, &ratio1_12, &ratio1_12, &ratio5_48, &ratio5_48, 
&ratio5_48, &ratio5_48, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, &ratio5_24, &ratio5_24, 
&ratio5_24, &ratio5_24, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio5_12, &ratio5_12, 
&ratio5_12, &ratio5_12, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio5_6, &ratio5_6, 
&ratio5_6, &ratio5_6, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio5_3, &ratio5_3, 
&ratio5_3, &ratio5_3, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio10_3, &ratio10_3, 
&ratio10_3, &ratio10_3, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio16_3, &ratio16_3, &ratio16_3, &ratio16_3, &ratio20_3, &ratio20_3, 
&ratio20_3, &ratio20_3, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio32_3, &ratio32_3, &ratio32_3, &ratio32_3, &ratio40_3, &ratio40_3, 
&ratio40_3, &ratio40_3, &ratio16_1, &ratio16_1, &ratio16_1, &ratio16_1, &ratio64_3, &ratio64_3, &ratio64_3, &ratio64_3, &ratio80_3, &ratio80_3, 
&ratio80_3, &ratio80_3, &ratio32_1, &ratio32_1, &ratio32_1, &ratio32_1, &ratio128_3}; 

static const ScaleNote * const tetrad_inversionsi[128] = {&ratio5_192, &ratio5_192, &ratio5_192, &ratio5_192, &ratio1_32, &ratio1_32, &ratio1_32, &ratio1_24, &ratio1_24, &ratio1_24, &ratio3_64, &ratio3_64, &ratio5_96, 
&ratio5_96, &ratio5_96, &ratio5_96, &ratio1_16, &ratio1_16, &ratio1_16, &ratio1_12, &ratio1_12, &ratio1_12, &ratio3_32, &ratio3_32, &ratio5_48, 
&ratio5_48, &ratio5_48, &ratio5_48, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_6, &ratio1_6, &ratio1_6, &ratio3_16, &ratio3_16, &ratio5_24, 
&ratio5_24, &ratio5_24, &ratio5_24, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_3, &ratio1_3, &ratio1_3, &ratio3_8, &ratio3_8, &ratio5_12, 
&ratio5_12, &ratio5_12, &ratio5_12, &ratio1_2, &ratio1_2, &ratio1_2, &ratio2_3, &ratio2_3, &ratio2_3, &ratio3_4, &ratio3_4, &ratio5_6, 
&ratio5_6, &ratio5_6, &ratio5_6, &ratio1_1, &ratio1_1, &ratio1_1, &ratio4_3, &ratio4_3, &ratio4_3, &ratio3_2, &ratio3_2, &ratio5_3, 
&ratio5_3, &ratio5_3, &ratio5_3, &ratio2_1, &ratio2_1, &ratio2_1, &ratio8_3, &ratio8_3, &ratio8_3, &ratio3_1, &ratio3_1, &ratio10_3, 
&ratio10_3, &ratio10_3, &ratio10_3, &ratio4_1, &ratio4_1, &ratio4_1, &ratio16_3, &ratio16_3, &ratio16_3, &ratio6_1, &ratio6_1, &ratio20_3, 
&ratio20_3, &ratio20_3, &ratio20_3, &ratio8_1, &ratio8_1, &ratio8_1, &ratio32_3, &ratio32_3, &ratio32_3, &ratio12_1, &ratio12_1, &ratio40_3, 
&ratio40_3, &ratio40_3, &ratio40_3, &ratio16_1, &ratio16_1, &ratio16_1, &ratio64_3, &ratio64_3, &ratio64_3, &ratio24_1, &ratio24_1, &ratio80_3, 
&ratio80_3, &ratio80_3, &ratio80_3, &ratio32_1, &ratio32_1, &ratio32_1, &ratio128_3}; 

static const ScaleNote * const tetrad_inversionsj[128] = {&ratio1_36, &ratio1_36, &ratio1_36, &ratio1_36, &ratio1_32, &ratio5_144, &ratio5_144, &ratio1_24, &ratio1_24, &ratio1_24, &ratio1_24, &ratio1_18, &ratio1_18, 
&ratio1_18, &ratio1_18, &ratio1_18, &ratio1_16, &ratio5_72, &ratio5_72, &ratio1_12, &ratio1_12, &ratio1_12, &ratio1_12, &ratio1_9, &ratio1_9, 
&ratio1_9, &ratio1_9, &ratio1_9, &ratio1_8, &ratio5_36, &ratio5_36, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, &ratio2_9, &ratio2_9, 
&ratio2_9, &ratio2_9, &ratio2_9, &ratio1_4, &ratio5_18, &ratio5_18, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio4_9, &ratio4_9, 
&ratio4_9, &ratio4_9, &ratio4_9, &ratio1_2, &ratio5_9, &ratio5_9, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio8_9, &ratio8_9, 
&ratio8_9, &ratio8_9, &ratio8_9, &ratio1_1, &ratio10_9, &ratio10_9, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio16_9, &ratio16_9, 
&ratio16_9, &ratio16_9, &ratio16_9, &ratio2_1, &ratio20_9, &ratio20_9, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio32_9, &ratio32_9, 
&ratio32_9, &ratio32_9, &ratio32_9, &ratio4_1, &ratio40_9, &ratio40_9, &ratio16_3, &ratio16_3, &ratio16_3, &ratio16_3, &ratio64_9, &ratio64_9, 
&ratio64_9, &ratio64_9, &ratio64_9, &ratio8_1, &ratio80_9, &ratio80_9, &ratio32_3, &ratio32_3, &ratio32_3, &ratio32_3, &ratio128_9, &ratio128_9, 
&ratio128_9, &ratio128_9, &ratio128_9, &ratio16_1, &ratio160_9, &ratio160_9, &ratio64_3, &ratio64_3, &ratio64_3, &ratio64_3, &ratio256_9, &ratio256_9, 
&ratio256_9, &ratio256_9, &ratio256_9, &ratio32_1, &ratio320_9, &ratio320_9, &ratio128_3}; 

static const ScaleNote * const tetrad_inversionsk[128] = {&ratio3_128, &ratio3_128, &ratio3_128, &ratio3_128, &ratio1_32, &ratio1_32, &ratio9_256, &ratio5_128, &ratio5_128, &ratio5_128, &ratio3_64, &ratio3_64, &ratio3_64, 
&ratio3_64, &ratio3_64, &ratio3_64, &ratio1_16, &ratio1_16, &ratio9_128, &ratio5_64, &ratio5_64, &ratio5_64, &ratio3_32, &ratio3_32, &ratio3_32, 
&ratio3_32, &ratio3_32, &ratio3_32, &ratio1_8, &ratio1_8, &ratio9_64, &ratio5_32, &ratio5_32, &ratio5_32, &ratio3_16, &ratio3_16, &ratio3_16, 
&ratio3_16, &ratio3_16, &ratio3_16, &ratio1_4, &ratio1_4, &ratio9_32, &ratio5_16, &ratio5_16, &ratio5_16, &ratio3_8, &ratio3_8, &ratio3_8, 
&ratio3_8, &ratio3_8, &ratio3_8, &ratio1_2, &ratio1_2, &ratio9_16, &ratio5_8, &ratio5_8, &ratio5_8, &ratio3_4, &ratio3_4, &ratio3_4, 
&ratio3_4, &ratio3_4, &ratio3_4, &ratio1_1, &ratio1_1, &ratio9_8, &ratio5_4, &ratio5_4, &ratio5_4, &ratio3_2, &ratio3_2, &ratio3_2, 
&ratio3_2, &ratio3_2, &ratio3_2, &ratio2_1, &ratio2_1, &ratio9_4, &ratio5_2, &ratio5_2, &ratio5_2, &ratio3_1, &ratio3_1, &ratio3_1, 
&ratio3_1, &ratio3_1, &ratio3_1, &ratio4_1, &ratio4_1, &ratio9_2, &ratio5_1, &ratio5_1, &ratio5_1, &ratio6_1, &ratio6_1, &ratio6_1, 
&ratio6_1, &ratio6_1, &ratio6_1, &ratio8_1, &ratio8_1, &ratio9_1, &ratio10_1, &ratio10_1, &ratio10_1, &ratio12_1, &ratio12_1, &ratio12_1, 
&ratio12_1, &ratio12_1, &ratio12_1, &ratio16_1, &ratio16_1, &ratio18_1, &ratio20_1, &ratio20_1, &ratio20_1, &ratio24_1, &ratio24_1, &ratio24_1, 
&ratio24_1, &ratio24_1, &ratio24_1, &ratio32_1, &ratio32_1, &ratio36_1, &ratio40_1}; 

static const ScaleNote * const tetrad_inversionsl[128] = {&ratio1_40, &ratio1_40, &ratio9_320, &ratio9_320, &ratio1_32, &ratio1_32, &ratio1_32, &ratio1_32, &ratio1_32, &ratio1_20, &ratio1_20, &ratio1_20, &ratio1_20, 
&ratio1_20, &ratio9_160, &ratio9_160, &ratio1_16, &ratio1_16, &ratio1_16, &ratio1_16, &ratio1_16, &ratio1_10, &ratio1_10, &ratio1_10, &ratio1_10, 
&ratio1_10, &ratio9_80, &ratio9_80, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, 
&ratio1_5, &ratio9_40, &ratio9_40, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio2_5, &ratio2_5, &ratio2_5, &ratio2_5, 
&ratio2_5, &ratio9_20, &ratio9_20, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio4_5, &ratio4_5, &ratio4_5, &ratio4_5, 
&ratio4_5, &ratio9_10, &ratio9_10, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, 
&ratio8_5, &ratio9_5, &ratio9_5, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio16_5, &ratio16_5, &ratio16_5, &ratio16_5, 
&ratio16_5, &ratio18_5, &ratio18_5, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio32_5, &ratio32_5, &ratio32_5, &ratio32_5, 
&ratio32_5, &ratio36_5, &ratio36_5, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio64_5, &ratio64_5, &ratio64_5, &ratio64_5, 
&ratio64_5, &ratio72_5, &ratio72_5, &ratio16_1, &ratio16_1, &ratio16_1, &ratio16_1, &ratio16_1, &ratio128_5, &ratio128_5, &ratio128_5, &ratio128_5, 
&ratio128_5, &ratio144_5, &ratio144_5, &ratio32_1, &ratio32_1, &ratio32_1, &ratio32_1}; 

static const ScaleNote * const tetrad_inversionsm[128] = {&ratio3_128, &ratio3_128, &ratio3_128, &ratio3_128, &ratio1_32, &ratio1_32, &ratio9_256, &ratio5_128, &ratio5_128, &ratio5_128, &ratio3_64, &ratio3_64, &ratio3_64, 
&ratio3_64, &ratio3_64, &ratio3_64, &ratio1_16, &ratio1_16, &ratio9_128, &ratio5_64, &ratio5_64, &ratio5_64, &ratio3_32, &ratio3_32, &ratio3_32, 
&ratio3_32, &ratio3_32, &ratio3_32, &ratio1_8, &ratio1_8, &ratio9_64, &ratio5_32, &ratio5_32, &ratio5_32, &ratio3_16, &ratio3_16, &ratio3_16, 
&ratio3_16, &ratio3_16, &ratio3_16, &ratio1_4, &ratio1_4, &ratio9_32, &ratio5_16, &ratio5_16, &ratio5_16, &ratio3_8, &ratio3_8, &ratio3_8, 
&ratio3_8, &ratio3_8, &ratio3_8, &ratio1_2, &ratio1_2, &ratio9_16, &ratio5_8, &ratio5_8, &ratio5_8, &ratio3_4, &ratio3_4, &ratio3_4, 
&ratio3_4, &ratio3_4, &ratio3_4, &ratio1_1, &ratio1_1, &ratio9_8, &ratio5_4, &ratio5_4, &ratio5_4, &ratio3_2, &ratio3_2, &ratio3_2, 
&ratio3_2, &ratio3_2, &ratio3_2, &ratio2_1, &ratio2_1, &ratio9_4, &ratio5_2, &ratio5_2, &ratio5_2, &ratio3_1, &ratio3_1, &ratio3_1, 
&ratio3_1, &ratio3_1, &ratio3_1, &ratio4_1, &ratio4_1, &ratio9_2, &ratio5_1, &ratio5_1, &ratio5_1, &ratio6_1, &ratio6_1, &ratio6_1, 
&ratio6_1, &ratio6_1, &ratio6_1, &ratio8_1, &ratio8_1, &ratio9_1, &ratio10_1, &ratio10_1, &ratio10_1, &ratio12_1, &ratio12_1, &ratio12_1, 
&ratio12_1, &ratio12_1, &ratio12_1, &ratio16_1, &ratio16_1, &ratio18_1, &ratio20_1, &ratio20_1, &ratio20_1, &ratio24_1, &ratio24_1, &ratio24_1, 
&ratio24_1, &ratio24_1, &ratio24_1, &ratio32_1, &ratio32_1, &ratio36_1, &ratio40_1}; 

static const ScaleNote * const tetrad_inversionsn[128] = {&ratio5_192, &ratio5_192, &ratio5_192, &ratio5_192, &ratio1_32, &ratio1_32, &ratio1_32, &ratio1_24, &ratio1_24, &ratio1_24, &ratio3_64, &ratio3_64, &ratio5_96, 
&ratio5_96, &ratio5_96, &ratio5_96, &ratio1_16, &ratio1_16, &ratio1_16, &ratio1_12, &ratio1_12, &ratio1_12, &ratio3_32, &ratio3_32, &ratio5_48, 
&ratio5_48, &ratio5_48, &ratio5_48, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_6, &ratio1_6, &ratio1_6, &ratio3_16, &ratio3_16, &ratio5_24, 
&ratio5_24, &ratio5_24, &ratio5_24, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_3, &ratio1_3, &ratio1_3, &ratio3_8, &ratio3_8, &ratio5_12, 
&ratio5_12, &ratio5_12, &ratio5_12, &ratio1_2, &ratio1_2, &ratio1_2, &ratio2_3, &ratio2_3, &ratio2_3, &ratio3_4, &ratio3_4, &ratio5_6, 
&ratio5_6, &ratio5_6, &ratio5_6, &ratio1_1, &ratio1_1, &ratio1_1, &ratio4_3, &ratio4_3, &ratio4_3, &ratio3_2, &ratio3_2, &ratio5_3, 
&ratio5_3, &ratio5_3, &ratio5_3, &ratio2_1, &ratio2_1, &ratio2_1, &ratio8_3, &ratio8_3, &ratio8_3, &ratio3_1, &ratio3_1, &ratio10_3, 
&ratio10_3, &ratio10_3, &ratio10_3, &ratio4_1, &ratio4_1, &ratio4_1, &ratio16_3, &ratio16_3, &ratio16_3, &ratio6_1, &ratio6_1, &ratio20_3, 
&ratio20_3, &ratio20_3, &ratio20_3, &ratio8_1, &ratio8_1, &ratio8_1, &ratio32_3, &ratio32_3, &ratio32_3, &ratio12_1, &ratio12_1, &ratio40_3, 
&ratio40_3, &ratio40_3, &ratio40_3, &ratio16_1, &ratio16_1, &ratio16_1, &ratio64_3, &ratio64_3, &ratio64_3, &ratio24_1, &ratio24_1, &ratio80_3, 
&ratio80_3, &ratio80_3, &ratio80_3, &ratio32_1, &ratio32_1, &ratio32_1, &ratio128_3}; 

static const ScaleNote * const tetrad_inversionso[128] = {&ratio1_40, &ratio1_40, &ratio9_320, &ratio9_320, &ratio1_32, &ratio1_32, &ratio3_80, &ratio3_80, &ratio3_80, &ratio3_80, &ratio1_20, &ratio1_20, &ratio1_20, 
&ratio1_20, &ratio9_160, &ratio9_160, &ratio1_16, &ratio1_16, &ratio3_40, &ratio3_40, &ratio3_40, &ratio3_40, &ratio1_10, &ratio1_10, &ratio1_10, 
&ratio1_10, &ratio9_80, &ratio9_80, &ratio1_8, &ratio1_8, &ratio3_20, &ratio3_20, &ratio3_20, &ratio3_20, &ratio1_5, &ratio1_5, &ratio1_5, 
&ratio1_5, &ratio9_40, &ratio9_40, &ratio1_4, &ratio1_4, &ratio3_10, &ratio3_10, &ratio3_10, &ratio3_10, &ratio2_5, &ratio2_5, &ratio2_5, 
&ratio2_5, &ratio9_20, &ratio9_20, &ratio1_2, &ratio1_2, &ratio3_5, &ratio3_5, &ratio3_5, &ratio3_5, &ratio4_5, &ratio4_5, &ratio4_5, 
&ratio4_5, &ratio9_10, &ratio9_10, &ratio1_1, &ratio1_1, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio8_5, &ratio8_5, &ratio8_5, 
&ratio8_5, &ratio9_5, &ratio9_5, &ratio2_1, &ratio2_1, &ratio12_5, &ratio12_5, &ratio12_5, &ratio12_5, &ratio16_5, &ratio16_5, &ratio16_5, 
&ratio16_5, &ratio18_5, &ratio18_5, &ratio4_1, &ratio4_1, &ratio24_5, &ratio24_5, &ratio24_5, &ratio24_5, &ratio32_5, &ratio32_5, &ratio32_5, 
&ratio32_5, &ratio36_5, &ratio36_5, &ratio8_1, &ratio8_1, &ratio48_5, &ratio48_5, &ratio48_5, &ratio48_5, &ratio64_5, &ratio64_5, &ratio64_5, 
&ratio64_5, &ratio72_5, &ratio72_5, &ratio16_1, &ratio16_1, &ratio96_5, &ratio96_5, &ratio96_5, &ratio96_5, &ratio128_5, &ratio128_5, &ratio128_5, 
&ratio128_5, &ratio144_5, &ratio144_5, &ratio32_1, &ratio32_1, &ratio192_5, &ratio192_5}; 

static const ScaleNote * const tetrad_inversionsp[128] = {&ratio1_48, &ratio1_32, &ratio1_32, &ratio1_32, &ratio1_32, &ratio5_144, &ratio5_144, &ratio1_24, &ratio1_24, &ratio1_24, &ratio1_24, &ratio1_24, &ratio1_24, 
&ratio1_16, &ratio1_16, &ratio1_16, &ratio1_16, &ratio5_72, &ratio5_72, &ratio1_12, &ratio1_12, &ratio1_12, &ratio1_12, &ratio1_12, &ratio1_12, 
&ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio5_36, &ratio5_36, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, 
&ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio5_18, &ratio5_18, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, 
&ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio5_9, &ratio5_9, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, 
&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio10_9, &ratio10_9, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, 
&ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio20_9, &ratio20_9, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, 
&ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio40_9, &ratio40_9, &ratio16_3, &ratio16_3, &ratio16_3, &ratio16_3, &ratio16_3, &ratio16_3, 
&ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio80_9, &ratio80_9, &ratio32_3, &ratio32_3, &ratio32_3, &ratio32_3, &ratio32_3, &ratio32_3, 
&ratio16_1, &ratio16_1, &ratio16_1, &ratio16_1, &ratio160_9, &ratio160_9, &ratio64_3, &ratio64_3, &ratio64_3, &ratio64_3, &ratio64_3, &ratio64_3, 
&ratio32_1, &ratio32_1, &ratio32_1, &ratio32_1, &ratio320_9, &ratio320_9, &ratio128_3}; 



static const ScaleNote * const harmonic_entropyA[128] = {&ratio3_128, &ratio3_128, &ratio3_128, &ratio3_128, &ratio1_32, &ratio1_32, &ratio1_32, &ratio1_32, &ratio3_64, &ratio3_64, &ratio3_64, &ratio3_64, &ratio3_64, 
&ratio3_64, &ratio3_64, &ratio3_64, &ratio1_16, &ratio1_16, &ratio1_16, &ratio1_16, &ratio3_32, &ratio3_32, &ratio3_32, &ratio3_32, &ratio3_32, 
&ratio3_32, &ratio3_32, &ratio3_32, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio3_16, &ratio3_16, &ratio3_16, &ratio3_16, &ratio3_16, 
&ratio3_16, &ratio3_16, &ratio3_16, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio3_8, &ratio3_8, &ratio3_8, &ratio3_8, &ratio3_8, 
&ratio3_8, &ratio3_8, &ratio3_8, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio3_4, &ratio3_4, &ratio3_4, &ratio3_4, &ratio3_4, 
&ratio3_4, &ratio3_4, &ratio3_4, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, 
&ratio3_2, &ratio3_2, &ratio3_2, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, 
&ratio3_1, &ratio3_1, &ratio3_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, 
&ratio6_1, &ratio6_1, &ratio6_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio12_1, &ratio12_1, &ratio12_1, &ratio12_1, &ratio12_1, 
&ratio12_1, &ratio12_1, &ratio12_1, &ratio16_1, &ratio16_1, &ratio16_1, &ratio16_1, &ratio24_1, &ratio24_1, &ratio24_1, &ratio24_1, &ratio24_1, 
&ratio24_1, &ratio24_1, &ratio24_1, &ratio32_1, &ratio32_1, &ratio32_1, &ratio32_1}; 

static const ScaleNote * const harmonic_entropyB[128] = {&ratio5_192, &ratio5_192, &ratio5_192, &ratio5_192, &ratio1_32, &ratio1_32, &ratio1_32, &ratio1_24, &ratio1_24, &ratio1_24, &ratio3_64, &ratio3_64, &ratio5_96, 
&ratio5_96, &ratio5_96, &ratio5_96, &ratio1_16, &ratio1_16, &ratio1_16, &ratio1_12, &ratio1_12, &ratio1_12, &ratio3_32, &ratio3_32, &ratio5_48, 
&ratio5_48, &ratio5_48, &ratio5_48, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_6, &ratio1_6, &ratio1_6, &ratio3_16, &ratio3_16, &ratio5_24, 
&ratio5_24, &ratio5_24, &ratio5_24, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_3, &ratio1_3, &ratio1_3, &ratio3_8, &ratio3_8, &ratio5_12, 
&ratio5_12, &ratio5_12, &ratio5_12, &ratio1_2, &ratio1_2, &ratio1_2, &ratio2_3, &ratio2_3, &ratio2_3, &ratio3_4, &ratio3_4, &ratio5_6, 
&ratio5_6, &ratio5_6, &ratio5_6, &ratio1_1, &ratio1_1, &ratio1_1, &ratio4_3, &ratio4_3, &ratio4_3, &ratio3_2, &ratio3_2, &ratio5_3, 
&ratio5_3, &ratio5_3, &ratio5_3, &ratio2_1, &ratio2_1, &ratio2_1, &ratio8_3, &ratio8_3, &ratio8_3, &ratio3_1, &ratio3_1, &ratio10_3, 
&ratio10_3, &ratio10_3, &ratio10_3, &ratio4_1, &ratio4_1, &ratio4_1, &ratio16_3, &ratio16_3, &ratio16_3, &ratio6_1, &ratio6_1, &ratio20_3, 
&ratio20_3, &ratio20_3, &ratio20_3, &ratio8_1, &ratio8_1, &ratio8_1, &ratio32_3, &ratio32_3, &ratio32_3, &ratio12_1, &ratio12_1, &ratio40_3, 
&ratio40_3, &ratio40_3, &ratio40_3, &ratio16_1, &ratio16_1, &ratio16_1, &ratio64_3, &ratio64_3, &ratio64_3, &ratio24_1, &ratio24_1, &ratio80_3, 
&ratio80_3, &ratio80_3, &ratio80_3, &ratio32_1, &ratio32_1, &ratio32_1, &ratio128_3}; 

static const ScaleNote * const harmonic_entropyC[128] = {&ratio5_192, &ratio7_256, &ratio7_256, &ratio7_256, &ratio1_32, &ratio1_32, &ratio5_128, &ratio5_128, &ratio1_24, &ratio1_24, &ratio3_64, &ratio3_64, &ratio5_96, 
&ratio7_128, &ratio7_128, &ratio7_128, &ratio1_16, &ratio1_16, &ratio5_64, &ratio5_64, &ratio1_12, &ratio1_12, &ratio3_32, &ratio3_32, &ratio5_48, 
&ratio7_64, &ratio7_64, &ratio7_64, &ratio1_8, &ratio1_8, &ratio5_32, &ratio5_32, &ratio1_6, &ratio1_6, &ratio3_16, &ratio3_16, &ratio5_24, 
&ratio7_32, &ratio7_32, &ratio7_32, &ratio1_4, &ratio1_4, &ratio5_16, &ratio5_16, &ratio1_3, &ratio1_3, &ratio3_8, &ratio3_8, &ratio5_12, 
&ratio7_16, &ratio7_16, &ratio7_16, &ratio1_2, &ratio1_2, &ratio5_8, &ratio5_8, &ratio2_3, &ratio2_3, &ratio3_4, &ratio3_4, &ratio5_6, 
&ratio7_8, &ratio7_8, &ratio7_8, &ratio1_1, &ratio1_1, &ratio5_4, &ratio5_4, &ratio4_3, &ratio4_3, &ratio3_2, &ratio3_2, &ratio5_3, 
&ratio7_4, &ratio7_4, &ratio7_4, &ratio2_1, &ratio2_1, &ratio5_2, &ratio5_2, &ratio8_3, &ratio8_3, &ratio3_1, &ratio3_1, &ratio10_3, 
&ratio7_2, &ratio7_2, &ratio7_2, &ratio4_1, &ratio4_1, &ratio5_1, &ratio5_1, &ratio16_3, &ratio16_3, &ratio6_1, &ratio6_1, &ratio20_3, 
&ratio7_1, &ratio7_1, &ratio7_1, &ratio8_1, &ratio8_1, &ratio10_1, &ratio10_1, &ratio32_3, &ratio32_3, &ratio12_1, &ratio12_1, &ratio40_3, 
&ratio14_1, &ratio14_1, &ratio14_1, &ratio16_1, &ratio16_1, &ratio20_1, &ratio20_1, &ratio64_3, &ratio64_3, &ratio24_1, &ratio24_1, &ratio80_3, 
&ratio28_1, &ratio28_1, &ratio28_1, &ratio32_1, &ratio32_1, &ratio40_1, &ratio40_1}; 

static const ScaleNote * const harmonic_entropyD[128] = {&ratio1_40, &ratio7_256, &ratio9_320, &ratio9_320, &ratio1_32, &ratio1_32, &ratio3_80, &ratio3_80, &ratio1_24, &ratio7_160, &ratio7_160, &ratio3_64, &ratio1_20, 
&ratio7_128, &ratio9_160, &ratio9_160, &ratio1_16, &ratio1_16, &ratio3_40, &ratio3_40, &ratio1_12, &ratio7_80, &ratio7_80, &ratio3_32, &ratio1_10, 
&ratio7_64, &ratio9_80, &ratio9_80, &ratio1_8, &ratio1_8, &ratio3_20, &ratio3_20, &ratio1_6, &ratio7_40, &ratio7_40, &ratio3_16, &ratio1_5, 
&ratio7_32, &ratio9_40, &ratio9_40, &ratio1_4, &ratio1_4, &ratio3_10, &ratio3_10, &ratio1_3, &ratio7_20, &ratio7_20, &ratio3_8, &ratio2_5, 
&ratio7_16, &ratio9_20, &ratio9_20, &ratio1_2, &ratio1_2, &ratio3_5, &ratio3_5, &ratio2_3, &ratio7_10, &ratio7_10, &ratio3_4, &ratio4_5, 
&ratio7_8, &ratio9_10, &ratio9_10, &ratio1_1, &ratio1_1, &ratio6_5, &ratio6_5, &ratio4_3, &ratio7_5, &ratio7_5, &ratio3_2, &ratio8_5, 
&ratio7_4, &ratio9_5, &ratio9_5, &ratio2_1, &ratio2_1, &ratio12_5, &ratio12_5, &ratio8_3, &ratio14_5, &ratio14_5, &ratio3_1, &ratio16_5, 
&ratio7_2, &ratio18_5, &ratio18_5, &ratio4_1, &ratio4_1, &ratio24_5, &ratio24_5, &ratio16_3, &ratio28_5, &ratio28_5, &ratio6_1, &ratio32_5, 
&ratio7_1, &ratio36_5, &ratio36_5, &ratio8_1, &ratio8_1, &ratio48_5, &ratio48_5, &ratio32_3, &ratio56_5, &ratio56_5, &ratio12_1, &ratio64_5, 
&ratio14_1, &ratio72_5, &ratio72_5, &ratio16_1, &ratio16_1, &ratio96_5, &ratio96_5, &ratio64_3, &ratio112_5, &ratio112_5, &ratio24_1, &ratio128_5, 
&ratio28_1, &ratio144_5, &ratio144_5, &ratio32_1, &ratio32_1, &ratio192_5, &ratio192_5}; 

static const ScaleNote * const harmonic_entropyE[128] = {&ratio13_512, &ratio3_112, &ratio9_320, &ratio9_320, &ratio1_32, &ratio1_32, &ratio3_80, &ratio3_80, &ratio9_224, &ratio11_256, &ratio5_112, &ratio11_224, &ratio13_256, 
&ratio3_56, &ratio9_160, &ratio9_160, &ratio1_16, &ratio1_16, &ratio3_40, &ratio3_40, &ratio9_112, &ratio11_128, &ratio5_56, &ratio11_112, &ratio13_128, 
&ratio3_28, &ratio9_80, &ratio9_80, &ratio1_8, &ratio1_8, &ratio3_20, &ratio3_20, &ratio9_56, &ratio11_64, &ratio5_28, &ratio11_56, &ratio13_64, 
&ratio3_14, &ratio9_40, &ratio9_40, &ratio1_4, &ratio1_4, &ratio3_10, &ratio3_10, &ratio9_28, &ratio11_32, &ratio5_14, &ratio11_28, &ratio13_32, 
&ratio3_7, &ratio9_20, &ratio9_20, &ratio1_2, &ratio1_2, &ratio3_5, &ratio3_5, &ratio9_14, &ratio11_16, &ratio5_7, &ratio11_14, &ratio13_16, 
&ratio6_7, &ratio9_10, &ratio9_10, &ratio1_1, &ratio1_1, &ratio6_5, &ratio6_5, &ratio9_7, &ratio11_8, &ratio10_7, &ratio11_7, &ratio13_8, 
&ratio12_7, &ratio9_5, &ratio9_5, &ratio2_1, &ratio2_1, &ratio12_5, &ratio12_5, &ratio18_7, &ratio11_4, &ratio20_7, &ratio22_7, &ratio13_4, 
&ratio24_7, &ratio18_5, &ratio18_5, &ratio4_1, &ratio4_1, &ratio24_5, &ratio24_5, &ratio36_7, &ratio11_2, &ratio40_7, &ratio44_7, &ratio13_2, 
&ratio48_7, &ratio36_5, &ratio36_5, &ratio8_1, &ratio8_1, &ratio48_5, &ratio48_5, &ratio72_7, &ratio11_1, &ratio80_7, &ratio88_7, &ratio13_1, 
&ratio96_7, &ratio72_5, &ratio72_5, &ratio16_1, &ratio16_1, &ratio96_5, &ratio96_5, &ratio144_7, &ratio22_1, &ratio160_7, &ratio176_7, &ratio26_1, 
&ratio192_7, &ratio144_5, &ratio144_5, &ratio32_1, &ratio32_1, &ratio192_5, &ratio192_5}; 

static const ScaleNote * const harmonic_entropyF[128] = {&ratio1_40, &ratio7_256, &ratio7_256, &ratio7_256, &ratio1_32, &ratio1_32, &ratio5_128, &ratio5_128, &ratio5_128, &ratio7_160, &ratio7_160, &ratio1_20, &ratio1_20, 
&ratio7_128, &ratio7_128, &ratio7_128, &ratio1_16, &ratio1_16, &ratio5_64, &ratio5_64, &ratio5_64, &ratio7_80, &ratio7_80, &ratio1_10, &ratio1_10, 
&ratio7_64, &ratio7_64, &ratio7_64, &ratio1_8, &ratio1_8, &ratio5_32, &ratio5_32, &ratio5_32, &ratio7_40, &ratio7_40, &ratio1_5, &ratio1_5, 
&ratio7_32, &ratio7_32, &ratio7_32, &ratio1_4, &ratio1_4, &ratio5_16, &ratio5_16, &ratio5_16, &ratio7_20, &ratio7_20, &ratio2_5, &ratio2_5, 
&ratio7_16, &ratio7_16, &ratio7_16, &ratio1_2, &ratio1_2, &ratio5_8, &ratio5_8, &ratio5_8, &ratio7_10, &ratio7_10, &ratio4_5, &ratio4_5, 
&ratio7_8, &ratio7_8, &ratio7_8, &ratio1_1, &ratio1_1, &ratio5_4, &ratio5_4, &ratio5_4, &ratio7_5, &ratio7_5, &ratio8_5, &ratio8_5, 
&ratio7_4, &ratio7_4, &ratio7_4, &ratio2_1, &ratio2_1, &ratio5_2, &ratio5_2, &ratio5_2, &ratio14_5, &ratio14_5, &ratio16_5, &ratio16_5, 
&ratio7_2, &ratio7_2, &ratio7_2, &ratio4_1, &ratio4_1, &ratio5_1, &ratio5_1, &ratio5_1, &ratio28_5, &ratio28_5, &ratio32_5, &ratio32_5, 
&ratio7_1, &ratio7_1, &ratio7_1, &ratio8_1, &ratio8_1, &ratio10_1, &ratio10_1, &ratio10_1, &ratio56_5, &ratio56_5, &ratio64_5, &ratio64_5, 
&ratio14_1, &ratio14_1, &ratio14_1, &ratio16_1, &ratio16_1, &ratio20_1, &ratio20_1, &ratio20_1, &ratio112_5, &ratio112_5, &ratio128_5, &ratio128_5, 
&ratio28_1, &ratio28_1, &ratio28_1, &ratio32_1, &ratio32_1, &ratio40_1, &ratio40_1}; 

static const ScaleNote * const harmonic_entropyG[128] = {&ratio5_192, &ratio5_192, &ratio5_192, &ratio5_192, &ratio1_32, &ratio1_32, &ratio1_32, &ratio1_24, &ratio1_24, &ratio1_24, &ratio1_24, &ratio5_96, &ratio5_96, 
&ratio5_96, &ratio5_96, &ratio5_96, &ratio1_16, &ratio1_16, &ratio1_16, &ratio1_12, &ratio1_12, &ratio1_12, &ratio1_12, &ratio5_48, &ratio5_48, 
&ratio5_48, &ratio5_48, &ratio5_48, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, &ratio5_24, &ratio5_24, 
&ratio5_24, &ratio5_24, &ratio5_24, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio5_12, &ratio5_12, 
&ratio5_12, &ratio5_12, &ratio5_12, &ratio1_2, &ratio1_2, &ratio1_2, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio5_6, &ratio5_6, 
&ratio5_6, &ratio5_6, &ratio5_6, &ratio1_1, &ratio1_1, &ratio1_1, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio5_3, &ratio5_3, 
&ratio5_3, &ratio5_3, &ratio5_3, &ratio2_1, &ratio2_1, &ratio2_1, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio10_3, &ratio10_3, 
&ratio10_3, &ratio10_3, &ratio10_3, &ratio4_1, &ratio4_1, &ratio4_1, &ratio16_3, &ratio16_3, &ratio16_3, &ratio16_3, &ratio20_3, &ratio20_3, 
&ratio20_3, &ratio20_3, &ratio20_3, &ratio8_1, &ratio8_1, &ratio8_1, &ratio32_3, &ratio32_3, &ratio32_3, &ratio32_3, &ratio40_3, &ratio40_3, 
&ratio40_3, &ratio40_3, &ratio40_3, &ratio16_1, &ratio16_1, &ratio16_1, &ratio64_3, &ratio64_3, &ratio64_3, &ratio64_3, &ratio80_3, &ratio80_3, 
&ratio80_3, &ratio80_3, &ratio80_3, &ratio32_1, &ratio32_1, &ratio32_1, &ratio128_3}; 

static const ScaleNote * const harmonic_entropyH[128] = {&ratio3_128, &ratio3_128, &ratio3_128, &ratio3_128, &ratio1_32, &ratio1_32, &ratio1_32, &ratio1_24, &ratio1_24, &ratio1_24, &ratio3_64, &ratio3_64, &ratio3_64, 
&ratio3_64, &ratio3_64, &ratio3_64, &ratio1_16, &ratio1_16, &ratio1_16, &ratio1_12, &ratio1_12, &ratio1_12, &ratio3_32, &ratio3_32, &ratio3_32, 
&ratio3_32, &ratio3_32, &ratio3_32, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_6, &ratio1_6, &ratio1_6, &ratio3_16, &ratio3_16, &ratio3_16, 
&ratio3_16, &ratio3_16, &ratio3_16, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_3, &ratio1_3, &ratio1_3, &ratio3_8, &ratio3_8, &ratio3_8, 
&ratio3_8, &ratio3_8, &ratio3_8, &ratio1_2, &ratio1_2, &ratio1_2, &ratio2_3, &ratio2_3, &ratio2_3, &ratio3_4, &ratio3_4, &ratio3_4, 
&ratio3_4, &ratio3_4, &ratio3_4, &ratio1_1, &ratio1_1, &ratio1_1, &ratio4_3, &ratio4_3, &ratio4_3, &ratio3_2, &ratio3_2, &ratio3_2, 
&ratio3_2, &ratio3_2, &ratio3_2, &ratio2_1, &ratio2_1, &ratio2_1, &ratio8_3, &ratio8_3, &ratio8_3, &ratio3_1, &ratio3_1, &ratio3_1, 
&ratio3_1, &ratio3_1, &ratio3_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio16_3, &ratio16_3, &ratio16_3, &ratio6_1, &ratio6_1, &ratio6_1, 
&ratio6_1, &ratio6_1, &ratio6_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio32_3, &ratio32_3, &ratio32_3, &ratio12_1, &ratio12_1, &ratio12_1, 
&ratio12_1, &ratio12_1, &ratio12_1, &ratio16_1, &ratio16_1, &ratio16_1, &ratio64_3, &ratio64_3, &ratio64_3, &ratio24_1, &ratio24_1, &ratio24_1, 
&ratio24_1, &ratio24_1, &ratio24_1, &ratio32_1, &ratio32_1, &ratio32_1, &ratio128_3}; 



static const ScaleNote * const bohlenPeirceAScalevoct[128] = {&ratio49_2025, &ratio5_189, &ratio5_189, &ratio7_243, &ratio7_243, &ratio7_225, &ratio7_225, &ratio1_27, &ratio1_25, &ratio1_21, &ratio7_135, &ratio7_135, &ratio5_108, 
&ratio5_108, &ratio5_108, &ratio5_108, &ratio5_108, &ratio1_15, &ratio1_15, &ratio49_675, &ratio5_63, &ratio5_63, &ratio7_81, &ratio7_81, &ratio7_75, 
&ratio7_75, &ratio1_9, &ratio3_25, &ratio1_7, &ratio7_45, &ratio7_45, &ratio5_36, &ratio5_36, &ratio5_36, &ratio5_36, &ratio5_36, &ratio1_5, 
&ratio1_5, &ratio49_225, &ratio5_21, &ratio5_21, &ratio7_27, &ratio7_27, &ratio7_25, &ratio7_25, &ratio1_3, &ratio9_25, &ratio3_7, &ratio7_15, 
&ratio7_15, &ratio5_12, &ratio5_12, &ratio5_12, &ratio5_12, &ratio5_12, &ratio3_5, &ratio3_5, &ratio49_75, &ratio5_7, &ratio5_7, &ratio7_9, 
&ratio7_9, &ratio21_25, &ratio21_25, &ratio1_1, &ratio27_25, &ratio9_7, &ratio7_5, &ratio7_5, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, 
&ratio5_4, &ratio9_5, &ratio9_5, &ratio49_25, &ratio15_7, &ratio15_7, &ratio7_3, &ratio7_3, &ratio63_25, &ratio63_25, &ratio3_1, &ratio81_25, 
&ratio27_7, &ratio21_5, &ratio21_5, &ratio15_4, &ratio15_4, &ratio15_4, &ratio15_4, &ratio15_4, &ratio27_5, &ratio27_5, &ratio147_25, &ratio45_7, 
&ratio45_7, &ratio7_1, &ratio7_1, &ratio189_25, &ratio189_25, &ratio9_1, &ratio243_25, &ratio81_7, &ratio63_5, &ratio63_5, &ratio45_4, &ratio45_4, 
&ratio45_4, &ratio45_4, &ratio45_4, &ratio81_5, &ratio81_5, &ratio441_25, &ratio135_7, &ratio135_7, &ratio21_1, &ratio21_1, &ratio567_25, &ratio567_25, 
&ratio27_1, &ratio729_25, &ratio243_7, &ratio189_5, &ratio189_5, &ratio135_4, &ratio135_4}; 

static const ScaleNote * const bohlenPeirceBlueLambdavoct[128] = {&ratio7_243, &ratio7_243, &ratio7_243, &ratio7_243, &ratio25_729, &ratio25_729, &ratio25_729, &ratio1_27, &ratio25_567, &ratio1_21, &ratio7_135, &ratio7_135, &ratio7_135, 
&ratio5_81, &ratio1_15, &ratio1_15, &ratio49_675, &ratio49_675, &ratio49_675, &ratio7_81, &ratio7_81, &ratio7_81, &ratio7_81, &ratio25_243, &ratio25_243, 
&ratio25_243, &ratio1_9, &ratio25_189, &ratio1_7, &ratio7_45, &ratio7_45, &ratio7_45, &ratio5_27, &ratio1_5, &ratio1_5, &ratio49_225, &ratio49_225, 
&ratio49_225, &ratio7_27, &ratio7_27, &ratio7_27, &ratio7_27, &ratio25_81, &ratio25_81, &ratio25_81, &ratio1_3, &ratio25_63, &ratio3_7, &ratio7_15, 
&ratio7_15, &ratio7_15, &ratio5_9, &ratio3_5, &ratio3_5, &ratio49_75, &ratio49_75, &ratio49_75, &ratio7_9, &ratio7_9, &ratio7_9, &ratio7_9, 
&ratio25_27, &ratio25_27, &ratio25_27, &ratio1_1, &ratio25_21, &ratio9_7, &ratio7_5, &ratio7_5, &ratio7_5, &ratio5_3, &ratio9_5, &ratio9_5, 
&ratio49_25, &ratio49_25, &ratio49_25, &ratio7_3, &ratio7_3, &ratio7_3, &ratio7_3, &ratio25_9, &ratio25_9, &ratio25_9, &ratio3_1, &ratio25_7, 
&ratio27_7, &ratio21_5, &ratio21_5, &ratio21_5, &ratio5_1, &ratio27_5, &ratio27_5, &ratio147_25, &ratio147_25, &ratio147_25, &ratio7_1, &ratio7_1, 
&ratio7_1, &ratio7_1, &ratio25_3, &ratio25_3, &ratio25_3, &ratio9_1, &ratio75_7, &ratio81_7, &ratio63_5, &ratio63_5, &ratio63_5, &ratio15_1, 
&ratio81_5, &ratio81_5, &ratio441_25, &ratio441_25, &ratio441_25, &ratio21_1, &ratio21_1, &ratio21_1, &ratio21_1, &ratio25_1, &ratio25_1, &ratio25_1, 
&ratio27_1, &ratio225_7, &ratio243_7, &ratio189_5, &ratio189_5, &ratio189_5, &ratio45_1}; 

static const ScaleNote * const bohlenPeirceDurIvoct[128] = {&ratio7_243, &ratio7_243, &ratio7_225, &ratio7_225, &ratio7_225, &ratio7_225, &ratio7_225, &ratio1_27, &ratio1_25, &ratio1_21, &ratio7_135, &ratio7_135, &ratio7_135, 
&ratio5_81, &ratio1_15, &ratio1_15, &ratio49_675, &ratio49_675, &ratio49_675, &ratio7_81, &ratio7_81, &ratio7_75, &ratio7_75, &ratio7_75, &ratio7_75, 
&ratio7_75, &ratio1_9, &ratio3_25, &ratio1_7, &ratio7_45, &ratio7_45, &ratio7_45, &ratio5_27, &ratio1_5, &ratio1_5, &ratio49_225, &ratio49_225, 
&ratio49_225, &ratio7_27, &ratio7_27, &ratio7_25, &ratio7_25, &ratio7_25, &ratio7_25, &ratio7_25, &ratio1_3, &ratio9_25, &ratio3_7, &ratio7_15, 
&ratio7_15, &ratio7_15, &ratio5_9, &ratio3_5, &ratio3_5, &ratio49_75, &ratio49_75, &ratio49_75, &ratio7_9, &ratio7_9, &ratio21_25, &ratio21_25, 
&ratio21_25, &ratio21_25, &ratio21_25, &ratio1_1, &ratio27_25, &ratio9_7, &ratio7_5, &ratio7_5, &ratio7_5, &ratio5_3, &ratio9_5, &ratio9_5, 
&ratio49_25, &ratio49_25, &ratio49_25, &ratio7_3, &ratio7_3, &ratio63_25, &ratio63_25, &ratio63_25, &ratio63_25, &ratio63_25, &ratio3_1, &ratio81_25, 
&ratio27_7, &ratio21_5, &ratio21_5, &ratio21_5, &ratio5_1, &ratio27_5, &ratio27_5, &ratio147_25, &ratio147_25, &ratio147_25, &ratio7_1, &ratio7_1, 
&ratio189_25, &ratio189_25, &ratio189_25, &ratio189_25, &ratio189_25, &ratio9_1, &ratio243_25, &ratio81_7, &ratio63_5, &ratio63_5, &ratio63_5, &ratio15_1, 
&ratio81_5, &ratio81_5, &ratio441_25, &ratio441_25, &ratio441_25, &ratio21_1, &ratio21_1, &ratio567_25, &ratio567_25, &ratio567_25, &ratio567_25, &ratio567_25, 
&ratio27_1, &ratio729_25, &ratio243_7, &ratio189_5, &ratio189_5, &ratio189_5, &ratio45_1}; 

static const ScaleNote * const bohlenPeirceGammavoct[128] = {&ratio7_243, &ratio7_243, &ratio7_243, &ratio7_243, &ratio25_729, &ratio25_729, &ratio25_729, &ratio1_27, &ratio1_25, &ratio1_21, &ratio7_135, &ratio7_135, &ratio7_135, 
&ratio5_81, &ratio1_15, &ratio1_15, &ratio49_675, &ratio49_675, &ratio49_675, &ratio7_81, &ratio7_81, &ratio7_81, &ratio7_81, &ratio25_243, &ratio25_243, 
&ratio25_243, &ratio1_9, &ratio3_25, &ratio1_7, &ratio7_45, &ratio7_45, &ratio7_45, &ratio5_27, &ratio1_5, &ratio1_5, &ratio49_225, &ratio49_225, 
&ratio49_225, &ratio7_27, &ratio7_27, &ratio7_27, &ratio7_27, &ratio25_81, &ratio25_81, &ratio25_81, &ratio1_3, &ratio9_25, &ratio3_7, &ratio7_15, 
&ratio7_15, &ratio7_15, &ratio5_9, &ratio3_5, &ratio3_5, &ratio49_75, &ratio49_75, &ratio49_75, &ratio7_9, &ratio7_9, &ratio7_9, &ratio7_9, 
&ratio25_27, &ratio25_27, &ratio25_27, &ratio1_1, &ratio27_25, &ratio9_7, &ratio7_5, &ratio7_5, &ratio7_5, &ratio5_3, &ratio9_5, &ratio9_5, 
&ratio49_25, &ratio49_25, &ratio49_25, &ratio7_3, &ratio7_3, &ratio7_3, &ratio7_3, &ratio25_9, &ratio25_9, &ratio25_9, &ratio3_1, &ratio81_25, 
&ratio27_7, &ratio21_5, &ratio21_5, &ratio21_5, &ratio5_1, &ratio27_5, &ratio27_5, &ratio147_25, &ratio147_25, &ratio147_25, &ratio7_1, &ratio7_1, 
&ratio7_1, &ratio7_1, &ratio25_3, &ratio25_3, &ratio25_3, &ratio9_1, &ratio243_25, &ratio81_7, &ratio63_5, &ratio63_5, &ratio63_5, &ratio15_1, 
&ratio81_5, &ratio81_5, &ratio441_25, &ratio441_25, &ratio441_25, &ratio21_1, &ratio21_1, &ratio21_1, &ratio21_1, &ratio25_1, &ratio25_1, &ratio25_1, 
&ratio27_1, &ratio729_25, &ratio243_7, &ratio189_5, &ratio189_5, &ratio189_5, &ratio45_1}; 

static const ScaleNote * const bohlenPeirceHarmonicvoct[128] = {&ratio7_243, &ratio7_243, &ratio7_225, &ratio7_225, &ratio7_225, &ratio7_225, &ratio7_225, &ratio1_27, &ratio1_25, &ratio1_21, &ratio7_135, &ratio7_135, &ratio7_135, 
&ratio5_81, &ratio1_15, &ratio1_15, &ratio1_15, &ratio5_63, &ratio5_63, &ratio7_81, &ratio7_81, &ratio7_75, &ratio7_75, &ratio7_75, &ratio7_75, 
&ratio7_75, &ratio1_9, &ratio3_25, &ratio1_7, &ratio7_45, &ratio7_45, &ratio7_45, &ratio5_27, &ratio1_5, &ratio1_5, &ratio1_5, &ratio5_21, 
&ratio5_21, &ratio7_27, &ratio7_27, &ratio7_25, &ratio7_25, &ratio7_25, &ratio7_25, &ratio7_25, &ratio1_3, &ratio9_25, &ratio3_7, &ratio7_15, 
&ratio7_15, &ratio7_15, &ratio5_9, &ratio3_5, &ratio3_5, &ratio3_5, &ratio5_7, &ratio5_7, &ratio7_9, &ratio7_9, &ratio21_25, &ratio21_25, 
&ratio21_25, &ratio21_25, &ratio21_25, &ratio1_1, &ratio27_25, &ratio9_7, &ratio7_5, &ratio7_5, &ratio7_5, &ratio5_3, &ratio9_5, &ratio9_5, 
&ratio9_5, &ratio15_7, &ratio15_7, &ratio7_3, &ratio7_3, &ratio63_25, &ratio63_25, &ratio63_25, &ratio63_25, &ratio63_25, &ratio3_1, &ratio81_25, 
&ratio27_7, &ratio21_5, &ratio21_5, &ratio21_5, &ratio5_1, &ratio27_5, &ratio27_5, &ratio27_5, &ratio45_7, &ratio45_7, &ratio7_1, &ratio7_1, 
&ratio189_25, &ratio189_25, &ratio189_25, &ratio189_25, &ratio189_25, &ratio9_1, &ratio243_25, &ratio81_7, &ratio63_5, &ratio63_5, &ratio63_5, &ratio15_1, 
&ratio81_5, &ratio81_5, &ratio81_5, &ratio135_7, &ratio135_7, &ratio21_1, &ratio21_1, &ratio567_25, &ratio567_25, &ratio567_25, &ratio567_25, &ratio567_25, 
&ratio27_1, &ratio729_25, &ratio243_7, &ratio189_5, &ratio189_5, &ratio189_5, &ratio45_1}; 

static const ScaleNote * const bohlenPeirceMollIvoct[128] = {&ratio7_243, &ratio7_243, &ratio7_243, &ratio7_243, &ratio25_729, &ratio25_729, &ratio25_729, &ratio1_27, &ratio25_567, &ratio1_21, &ratio1_21, &ratio1_21, &ratio25_441, 
&ratio5_81, &ratio1_15, &ratio1_15, &ratio1_15, &ratio5_63, &ratio5_63, &ratio7_81, &ratio7_81, &ratio7_81, &ratio7_81, &ratio25_243, &ratio25_243, 
&ratio25_243, &ratio1_9, &ratio25_189, &ratio1_7, &ratio1_7, &ratio1_7, &ratio25_147, &ratio5_27, &ratio1_5, &ratio1_5, &ratio1_5, &ratio5_21, 
&ratio5_21, &ratio7_27, &ratio7_27, &ratio7_27, &ratio7_27, &ratio25_81, &ratio25_81, &ratio25_81, &ratio1_3, &ratio25_63, &ratio3_7, &ratio3_7, 
&ratio3_7, &ratio25_49, &ratio5_9, &ratio3_5, &ratio3_5, &ratio3_5, &ratio5_7, &ratio5_7, &ratio7_9, &ratio7_9, &ratio7_9, &ratio7_9, 
&ratio25_27, &ratio25_27, &ratio25_27, &ratio1_1, &ratio25_21, &ratio9_7, &ratio9_7, &ratio9_7, &ratio75_49, &ratio5_3, &ratio9_5, &ratio9_5, 
&ratio9_5, &ratio15_7, &ratio15_7, &ratio7_3, &ratio7_3, &ratio7_3, &ratio7_3, &ratio25_9, &ratio25_9, &ratio25_9, &ratio3_1, &ratio25_7, 
&ratio27_7, &ratio27_7, &ratio27_7, &ratio225_49, &ratio5_1, &ratio27_5, &ratio27_5, &ratio27_5, &ratio45_7, &ratio45_7, &ratio7_1, &ratio7_1, 
&ratio7_1, &ratio7_1, &ratio25_3, &ratio25_3, &ratio25_3, &ratio9_1, &ratio75_7, &ratio81_7, &ratio81_7, &ratio81_7, &ratio675_49, &ratio15_1, 
&ratio81_5, &ratio81_5, &ratio81_5, &ratio135_7, &ratio135_7, &ratio21_1, &ratio21_1, &ratio21_1, &ratio21_1, &ratio25_1, &ratio25_1, &ratio25_1, 
&ratio27_1, &ratio225_7, &ratio243_7, &ratio243_7, &ratio243_7, &ratio2025_49, &ratio45_1}; 

static const ScaleNote * const bohlenPeirceProoijenMinvoct[128] = {&ratio5_189, &ratio5_189, &ratio5_189, &ratio5_189, &ratio25_729, &ratio25_729, &ratio25_729, &ratio1_27, &ratio25_567, &ratio1_21, &ratio1_21, &ratio1_21, &ratio1_21, 
&ratio5_81, &ratio1_15, &ratio1_15, &ratio1_15, &ratio5_63, &ratio5_63, &ratio5_63, &ratio5_63, &ratio5_63, &ratio5_63, &ratio25_243, &ratio25_243, 
&ratio25_243, &ratio1_9, &ratio25_189, &ratio1_7, &ratio1_7, &ratio1_7, &ratio1_7, &ratio5_27, &ratio1_5, &ratio1_5, &ratio1_5, &ratio5_21, 
&ratio5_21, &ratio5_21, &ratio5_21, &ratio5_21, &ratio5_21, &ratio25_81, &ratio25_81, &ratio25_81, &ratio1_3, &ratio25_63, &ratio3_7, &ratio3_7, 
&ratio3_7, &ratio3_7, &ratio5_9, &ratio3_5, &ratio3_5, &ratio3_5, &ratio5_7, &ratio5_7, &ratio5_7, &ratio5_7, &ratio5_7, &ratio5_7, 
&ratio25_27, &ratio25_27, &ratio25_27, &ratio1_1, &ratio25_21, &ratio9_7, &ratio9_7, &ratio9_7, &ratio9_7, &ratio5_3, &ratio9_5, &ratio9_5, 
&ratio9_5, &ratio15_7, &ratio15_7, &ratio15_7, &ratio15_7, &ratio15_7, &ratio15_7, &ratio25_9, &ratio25_9, &ratio25_9, &ratio3_1, &ratio25_7, 
&ratio27_7, &ratio27_7, &ratio27_7, &ratio27_7, &ratio5_1, &ratio27_5, &ratio27_5, &ratio27_5, &ratio45_7, &ratio45_7, &ratio45_7, &ratio45_7, 
&ratio45_7, &ratio45_7, &ratio25_3, &ratio25_3, &ratio25_3, &ratio9_1, &ratio75_7, &ratio81_7, &ratio81_7, &ratio81_7, &ratio81_7, &ratio15_1, 
&ratio81_5, &ratio81_5, &ratio81_5, &ratio135_7, &ratio135_7, &ratio135_7, &ratio135_7, &ratio135_7, &ratio135_7, &ratio25_1, &ratio25_1, &ratio25_1, 
&ratio27_1, &ratio225_7, &ratio243_7, &ratio243_7, &ratio243_7, &ratio243_7, &ratio45_1}; 

static const ScaleNote * const bohlenPeirceWalkerBvoct[128] = {&ratio7_243, &ratio7_243, &ratio7_225, &ratio7_225, &ratio7_225, &ratio7_225, &ratio7_225, &ratio1_27, &ratio1_25, &ratio1_21, &ratio7_135, &ratio7_135, &ratio25_441, 
&ratio25_441, &ratio1_15, &ratio1_15, &ratio49_675, &ratio49_675, &ratio49_675, &ratio7_81, &ratio7_81, &ratio7_75, &ratio7_75, &ratio7_75, &ratio7_75, 
&ratio7_75, &ratio1_9, &ratio3_25, &ratio1_7, &ratio7_45, &ratio7_45, &ratio25_147, &ratio25_147, &ratio1_5, &ratio1_5, &ratio49_225, &ratio49_225, 
&ratio49_225, &ratio7_27, &ratio7_27, &ratio7_25, &ratio7_25, &ratio7_25, &ratio7_25, &ratio7_25, &ratio1_3, &ratio9_25, &ratio3_7, &ratio7_15, 
&ratio7_15, &ratio25_49, &ratio25_49, &ratio3_5, &ratio3_5, &ratio49_75, &ratio49_75, &ratio49_75, &ratio7_9, &ratio7_9, &ratio21_25, &ratio21_25, 
&ratio21_25, &ratio21_25, &ratio21_25, &ratio1_1, &ratio27_25, &ratio9_7, &ratio7_5, &ratio7_5, &ratio75_49, &ratio75_49, &ratio9_5, &ratio9_5, 
&ratio49_25, &ratio49_25, &ratio49_25, &ratio7_3, &ratio7_3, &ratio63_25, &ratio63_25, &ratio63_25, &ratio63_25, &ratio63_25, &ratio3_1, &ratio81_25, 
&ratio27_7, &ratio21_5, &ratio21_5, &ratio225_49, &ratio225_49, &ratio27_5, &ratio27_5, &ratio147_25, &ratio147_25, &ratio147_25, &ratio7_1, &ratio7_1, 
&ratio189_25, &ratio189_25, &ratio189_25, &ratio189_25, &ratio189_25, &ratio9_1, &ratio243_25, &ratio81_7, &ratio63_5, &ratio63_5, &ratio675_49, &ratio675_49, 
&ratio81_5, &ratio81_5, &ratio441_25, &ratio441_25, &ratio441_25, &ratio21_1, &ratio21_1, &ratio567_25, &ratio567_25, &ratio567_25, &ratio567_25, &ratio567_25, 
&ratio27_1, &ratio729_25, &ratio243_7, &ratio189_5, &ratio189_5, &ratio2025_49, &ratio2025_49}; 



static const ScaleNote * const simpleRhythms1[128] = {&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, 
&ratio1_1, &ratio1_1, &ratio1_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, 
&ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, 
&ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio4_1, 
&ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, 
&ratio4_1, &ratio4_1, &ratio4_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, 
&ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, 
&ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio12_1, 
&ratio12_1, &ratio12_1, &ratio12_1, &ratio12_1, &ratio12_1, &ratio12_1, &ratio12_1, &ratio12_1, &ratio12_1, &ratio12_1, &ratio12_1, &ratio12_1, 
&ratio12_1, &ratio12_1, &ratio12_1, &ratio16_1, &ratio16_1, &ratio16_1, &ratio16_1, &ratio16_1, &ratio16_1, &ratio16_1, &ratio16_1, &ratio16_1, 
&ratio16_1, &ratio16_1, &ratio16_1, &ratio16_1, &ratio16_1, &ratio16_1, &ratio16_1}; 

static const ScaleNote * const simpleRhythms2[128] = {&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, 
&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, 
&ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, 
&ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, 
&ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, 
&ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, 
&ratio3_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, 
&ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, 
&ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, 
&ratio6_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, 
&ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1}; 

static const ScaleNote * const simpleRhythms3[128] = {&ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, 
&ratio1_3, &ratio1_3, &ratio1_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, 
&ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, 
&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio4_3, 
&ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, 
&ratio4_3, &ratio4_3, &ratio4_3, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, 
&ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, 
&ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio4_1, 
&ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, 
&ratio4_1, &ratio4_1, &ratio4_1, &ratio16_3, &ratio16_3, &ratio16_3, &ratio16_3, &ratio16_3, &ratio16_3, &ratio16_3, &ratio16_3, &ratio16_3, 
&ratio16_3, &ratio16_3, &ratio16_3, &ratio16_3, &ratio16_3, &ratio16_3, &ratio16_3}; 

static const ScaleNote * const simpleRhythms4[128] = {&ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, 
&ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_1, &ratio1_1, &ratio1_1, 
&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, 
&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, 
&ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, 
&ratio3_2, &ratio3_2, &ratio3_2, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, 
&ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, 
&ratio2_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, 
&ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio4_1, &ratio4_1, 
&ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, 
&ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1}; 

static const ScaleNote * const simpleRhythms5[128] = {&ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, 
&ratio1_6, &ratio1_6, &ratio1_6, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, 
&ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, 
&ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio2_3, 
&ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, 
&ratio2_3, &ratio2_3, &ratio2_3, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, 
&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, 
&ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio2_1, 
&ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, 
&ratio2_1, &ratio2_1, &ratio2_1, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, 
&ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3}; 

static const ScaleNote * const simpleRhythms6[128] = {&ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, 
&ratio1_8, &ratio1_8, &ratio1_8, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, 
&ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio3_8, &ratio3_8, &ratio3_8, &ratio3_8, &ratio3_8, 
&ratio3_8, &ratio3_8, &ratio3_8, &ratio3_8, &ratio3_8, &ratio3_8, &ratio3_8, &ratio3_8, &ratio3_8, &ratio3_8, &ratio3_8, &ratio1_2, 
&ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, 
&ratio1_2, &ratio1_2, &ratio1_2, &ratio3_4, &ratio3_4, &ratio3_4, &ratio3_4, &ratio3_4, &ratio3_4, &ratio3_4, &ratio3_4, &ratio3_4, 
&ratio3_4, &ratio3_4, &ratio3_4, &ratio3_4, &ratio3_4, &ratio3_4, &ratio3_4, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, 
&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio3_2, 
&ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, 
&ratio3_2, &ratio3_2, &ratio3_2, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, 
&ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1}; 

static const ScaleNote * const simpleRhythms7[128] = {&ratio1_12, &ratio1_12, &ratio1_12, &ratio1_12, &ratio1_12, &ratio1_12, &ratio1_12, &ratio1_12, &ratio1_12, &ratio1_12, &ratio1_12, &ratio1_12, &ratio1_12, 
&ratio1_12, &ratio1_12, &ratio1_12, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, 
&ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, 
&ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_3, 
&ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, 
&ratio1_3, &ratio1_3, &ratio1_3, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, 
&ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, 
&ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio1_1, 
&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, 
&ratio1_1, &ratio1_1, &ratio1_1, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, 
&ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3}; 

static const ScaleNote * const simpleRhythms8[128] = {&ratio1_16, &ratio1_16, &ratio1_16, &ratio1_16, &ratio1_16, &ratio1_16, &ratio1_16, &ratio1_16, &ratio1_16, &ratio1_16, &ratio1_16, &ratio1_16, &ratio1_16, 
&ratio1_16, &ratio1_16, &ratio1_16, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, 
&ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio3_16, &ratio3_16, &ratio3_16, &ratio3_16, &ratio3_16, 
&ratio3_16, &ratio3_16, &ratio3_16, &ratio3_16, &ratio3_16, &ratio3_16, &ratio3_16, &ratio3_16, &ratio3_16, &ratio3_16, &ratio3_16, &ratio1_4, 
&ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, 
&ratio1_4, &ratio1_4, &ratio1_4, &ratio3_8, &ratio3_8, &ratio3_8, &ratio3_8, &ratio3_8, &ratio3_8, &ratio3_8, &ratio3_8, &ratio3_8, 
&ratio3_8, &ratio3_8, &ratio3_8, &ratio3_8, &ratio3_8, &ratio3_8, &ratio3_8, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, 
&ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio3_4, 
&ratio3_4, &ratio3_4, &ratio3_4, &ratio3_4, &ratio3_4, &ratio3_4, &ratio3_4, &ratio3_4, &ratio3_4, &ratio3_4, &ratio3_4, &ratio3_4, 
&ratio3_4, &ratio3_4, &ratio3_4, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, 
&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1}; 



static const ScaleNote * const SimpleRhythms1_16[128] = {&ratio1_1_16, &ratio1_1_16, &ratio1_1_16, &ratio1_1_16, &ratio1_1_16, &ratio1_1_16, &ratio1_1_16, &ratio1_1_16, &ratio1_1_16, &ratio1_1_16, &ratio1_1_16, &ratio1_1_16, &ratio1_1_16, 
&ratio1_1_16, &ratio1_1_16, &ratio1_1_16, &ratio2_1_16, &ratio2_1_16, &ratio2_1_16, &ratio2_1_16, &ratio2_1_16, &ratio2_1_16, &ratio2_1_16, &ratio2_1_16, &ratio2_1_16, 
&ratio2_1_16, &ratio2_1_16, &ratio2_1_16, &ratio2_1_16, &ratio2_1_16, &ratio2_1_16, &ratio2_1_16, &ratio3_1_16, &ratio3_1_16, &ratio3_1_16, &ratio3_1_16, &ratio3_1_16, 
&ratio3_1_16, &ratio3_1_16, &ratio3_1_16, &ratio3_1_16, &ratio3_1_16, &ratio3_1_16, &ratio3_1_16, &ratio3_1_16, &ratio3_1_16, &ratio3_1_16, &ratio3_1_16, &ratio4_1_16, 
&ratio4_1_16, &ratio4_1_16, &ratio4_1_16, &ratio4_1_16, &ratio4_1_16, &ratio4_1_16, &ratio4_1_16, &ratio4_1_16, &ratio4_1_16, &ratio4_1_16, &ratio4_1_16, &ratio4_1_16, 
&ratio4_1_16, &ratio4_1_16, &ratio4_1_16, &ratio6_1_16, &ratio6_1_16, &ratio6_1_16, &ratio6_1_16, &ratio6_1_16, &ratio6_1_16, &ratio6_1_16, &ratio6_1_16, &ratio6_1_16, 
&ratio6_1_16, &ratio6_1_16, &ratio6_1_16, &ratio6_1_16, &ratio6_1_16, &ratio6_1_16, &ratio6_1_16, &ratio8_1_16, &ratio8_1_16, &ratio8_1_16, &ratio8_1_16, &ratio8_1_16, 
&ratio8_1_16, &ratio8_1_16, &ratio8_1_16, &ratio8_1_16, &ratio8_1_16, &ratio8_1_16, &ratio8_1_16, &ratio8_1_16, &ratio8_1_16, &ratio8_1_16, &ratio8_1_16, &ratio12_1_16, 
&ratio12_1_16, &ratio12_1_16, &ratio12_1_16, &ratio12_1_16, &ratio12_1_16, &ratio12_1_16, &ratio12_1_16, &ratio12_1_16, &ratio12_1_16, &ratio12_1_16, &ratio12_1_16, &ratio12_1_16, 
&ratio12_1_16, &ratio12_1_16, &ratio12_1_16, &ratio16_1_16, &ratio16_1_16, &ratio16_1_16, &ratio16_1_16, &ratio16_1_16, &ratio16_1_16, &ratio16_1_16, &ratio16_1_16, &ratio16_1_16, 
&ratio16_1_16, &ratio16_1_16, &ratio16_1_16, &ratio16_1_16, &ratio16_1_16, &ratio16_1_16, &ratio16_1_16}; 

static const ScaleNote * const SimpleRhythms2_16[128] = {&ratio1_2_16, &ratio1_2_16, &ratio1_2_16, &ratio1_2_16, &ratio1_2_16, &ratio1_2_16, &ratio1_2_16, &ratio1_2_16, &ratio1_2_16, &ratio1_2_16, &ratio1_2_16, &ratio1_2_16, &ratio1_2_16, 
&ratio1_2_16, &ratio1_2_16, &ratio1_2_16, &ratio1_1_16, &ratio1_1_16, &ratio1_1_16, &ratio1_1_16, &ratio1_1_16, &ratio1_1_16, &ratio1_1_16, &ratio1_1_16, &ratio1_1_16, 
&ratio1_1_16, &ratio1_1_16, &ratio1_1_16, &ratio1_1_16, &ratio1_1_16, &ratio1_1_16, &ratio1_1_16, &ratio3_2_16, &ratio3_2_16, &ratio3_2_16, &ratio3_2_16, &ratio3_2_16, 
&ratio3_2_16, &ratio3_2_16, &ratio3_2_16, &ratio3_2_16, &ratio3_2_16, &ratio3_2_16, &ratio3_2_16, &ratio3_2_16, &ratio3_2_16, &ratio3_2_16, &ratio3_2_16, &ratio2_1_16, 
&ratio2_1_16, &ratio2_1_16, &ratio2_1_16, &ratio2_1_16, &ratio2_1_16, &ratio2_1_16, &ratio2_1_16, &ratio2_1_16, &ratio2_1_16, &ratio2_1_16, &ratio2_1_16, &ratio2_1_16, 
&ratio2_1_16, &ratio2_1_16, &ratio2_1_16, &ratio3_1_16, &ratio3_1_16, &ratio3_1_16, &ratio3_1_16, &ratio3_1_16, &ratio3_1_16, &ratio3_1_16, &ratio3_1_16, &ratio3_1_16, 
&ratio3_1_16, &ratio3_1_16, &ratio3_1_16, &ratio3_1_16, &ratio3_1_16, &ratio3_1_16, &ratio3_1_16, &ratio4_1_16, &ratio4_1_16, &ratio4_1_16, &ratio4_1_16, &ratio4_1_16, 
&ratio4_1_16, &ratio4_1_16, &ratio4_1_16, &ratio4_1_16, &ratio4_1_16, &ratio4_1_16, &ratio4_1_16, &ratio4_1_16, &ratio4_1_16, &ratio4_1_16, &ratio4_1_16, &ratio6_1_16, 
&ratio6_1_16, &ratio6_1_16, &ratio6_1_16, &ratio6_1_16, &ratio6_1_16, &ratio6_1_16, &ratio6_1_16, &ratio6_1_16, &ratio6_1_16, &ratio6_1_16, &ratio6_1_16, &ratio6_1_16, 
&ratio6_1_16, &ratio6_1_16, &ratio6_1_16, &ratio8_1_16, &ratio8_1_16, &ratio8_1_16, &ratio8_1_16, &ratio8_1_16, &ratio8_1_16, &ratio8_1_16, &ratio8_1_16, &ratio8_1_16, 
&ratio8_1_16, &ratio8_1_16, &ratio8_1_16, &ratio8_1_16, &ratio8_1_16, &ratio8_1_16, &ratio8_1_16}; 

static const ScaleNote * const SimpleRhythms3_16[128] = {&ratio1_3_16, &ratio1_3_16, &ratio1_3_16, &ratio1_3_16, &ratio1_3_16, &ratio1_3_16, &ratio1_3_16, &ratio1_3_16, &ratio1_3_16, &ratio1_3_16, &ratio1_3_16, &ratio1_3_16, &ratio1_3_16, 
&ratio1_3_16, &ratio1_3_16, &ratio1_3_16, &ratio2_3_16, &ratio2_3_16, &ratio2_3_16, &ratio2_3_16, &ratio2_3_16, &ratio2_3_16, &ratio2_3_16, &ratio2_3_16, &ratio2_3_16, 
&ratio2_3_16, &ratio2_3_16, &ratio2_3_16, &ratio2_3_16, &ratio2_3_16, &ratio2_3_16, &ratio2_3_16, &ratio1_1_16, &ratio1_1_16, &ratio1_1_16, &ratio1_1_16, &ratio1_1_16, 
&ratio1_1_16, &ratio1_1_16, &ratio1_1_16, &ratio1_1_16, &ratio1_1_16, &ratio1_1_16, &ratio1_1_16, &ratio1_1_16, &ratio1_1_16, &ratio1_1_16, &ratio1_1_16, &ratio4_3_16, 
&ratio4_3_16, &ratio4_3_16, &ratio4_3_16, &ratio4_3_16, &ratio4_3_16, &ratio4_3_16, &ratio4_3_16, &ratio4_3_16, &ratio4_3_16, &ratio4_3_16, &ratio4_3_16, &ratio4_3_16, 
&ratio4_3_16, &ratio4_3_16, &ratio4_3_16, &ratio2_1_16, &ratio2_1_16, &ratio2_1_16, &ratio2_1_16, &ratio2_1_16, &ratio2_1_16, &ratio2_1_16, &ratio2_1_16, &ratio2_1_16, 
&ratio2_1_16, &ratio2_1_16, &ratio2_1_16, &ratio2_1_16, &ratio2_1_16, &ratio2_1_16, &ratio2_1_16, &ratio8_3_16, &ratio8_3_16, &ratio8_3_16, &ratio8_3_16, &ratio8_3_16, 
&ratio8_3_16, &ratio8_3_16, &ratio8_3_16, &ratio8_3_16, &ratio8_3_16, &ratio8_3_16, &ratio8_3_16, &ratio8_3_16, &ratio8_3_16, &ratio8_3_16, &ratio8_3_16, &ratio4_1_16, 
&ratio4_1_16, &ratio4_1_16, &ratio4_1_16, &ratio4_1_16, &ratio4_1_16, &ratio4_1_16, &ratio4_1_16, &ratio4_1_16, &ratio4_1_16, &ratio4_1_16, &ratio4_1_16, &ratio4_1_16, 
&ratio4_1_16, &ratio4_1_16, &ratio4_1_16, &ratio16_3_16, &ratio16_3_16, &ratio16_3_16, &ratio16_3_16, &ratio16_3_16, &ratio16_3_16, &ratio16_3_16, &ratio16_3_16, &ratio16_3_16, 
&ratio16_3_16, &ratio16_3_16, &ratio16_3_16, &ratio16_3_16, &ratio16_3_16, &ratio16_3_16, &ratio16_3_16}; 

static const ScaleNote * const SimpleRhythms4_16[128] = {&ratio1_4_16, &ratio1_4_16, &ratio1_4_16, &ratio1_4_16, &ratio1_4_16, &ratio1_4_16, &ratio1_4_16, &ratio1_4_16, &ratio1_4_16, &ratio1_4_16, &ratio1_4_16, &ratio1_4_16, &ratio1_4_16, 
&ratio1_4_16, &ratio1_4_16, &ratio1_4_16, &ratio1_2_16, &ratio1_2_16, &ratio1_2_16, &ratio1_2_16, &ratio1_2_16, &ratio1_2_16, &ratio1_2_16, &ratio1_2_16, &ratio1_2_16, 
&ratio1_2_16, &ratio1_2_16, &ratio1_2_16, &ratio1_2_16, &ratio1_2_16, &ratio1_2_16, &ratio1_2_16, &ratio3_4_16, &ratio3_4_16, &ratio3_4_16, &ratio3_4_16, &ratio3_4_16, 
&ratio3_4_16, &ratio3_4_16, &ratio3_4_16, &ratio3_4_16, &ratio3_4_16, &ratio3_4_16, &ratio3_4_16, &ratio3_4_16, &ratio3_4_16, &ratio3_4_16, &ratio3_4_16, &ratio1_1_16, 
&ratio1_1_16, &ratio1_1_16, &ratio1_1_16, &ratio1_1_16, &ratio1_1_16, &ratio1_1_16, &ratio1_1_16, &ratio1_1_16, &ratio1_1_16, &ratio1_1_16, &ratio1_1_16, &ratio1_1_16, 
&ratio1_1_16, &ratio1_1_16, &ratio1_1_16, &ratio3_2_16, &ratio3_2_16, &ratio3_2_16, &ratio3_2_16, &ratio3_2_16, &ratio3_2_16, &ratio3_2_16, &ratio3_2_16, &ratio3_2_16, 
&ratio3_2_16, &ratio3_2_16, &ratio3_2_16, &ratio3_2_16, &ratio3_2_16, &ratio3_2_16, &ratio3_2_16, &ratio2_1_16, &ratio2_1_16, &ratio2_1_16, &ratio2_1_16, &ratio2_1_16, 
&ratio2_1_16, &ratio2_1_16, &ratio2_1_16, &ratio2_1_16, &ratio2_1_16, &ratio2_1_16, &ratio2_1_16, &ratio2_1_16, &ratio2_1_16, &ratio2_1_16, &ratio2_1_16, &ratio3_1_16, 
&ratio3_1_16, &ratio3_1_16, &ratio3_1_16, &ratio3_1_16, &ratio3_1_16, &ratio3_1_16, &ratio3_1_16, &ratio3_1_16, &ratio3_1_16, &ratio3_1_16, &ratio3_1_16, &ratio3_1_16, 
&ratio3_1_16, &ratio3_1_16, &ratio3_1_16, &ratio4_1_16, &ratio4_1_16, &ratio4_1_16, &ratio4_1_16, &ratio4_1_16, &ratio4_1_16, &ratio4_1_16, &ratio4_1_16, &ratio4_1_16, 
&ratio4_1_16, &ratio4_1_16, &ratio4_1_16, &ratio4_1_16, &ratio4_1_16, &ratio4_1_16, &ratio4_1_16}; 

static const ScaleNote * const SimpleRhythms5_16[128] = {&ratio1_6_16, &ratio1_6_16, &ratio1_6_16, &ratio1_6_16, &ratio1_6_16, &ratio1_6_16, &ratio1_6_16, &ratio1_6_16, &ratio1_6_16, &ratio1_6_16, &ratio1_6_16, &ratio1_6_16, &ratio1_6_16, 
&ratio1_6_16, &ratio1_6_16, &ratio1_6_16, &ratio1_3_16, &ratio1_3_16, &ratio1_3_16, &ratio1_3_16, &ratio1_3_16, &ratio1_3_16, &ratio1_3_16, &ratio1_3_16, &ratio1_3_16, 
&ratio1_3_16, &ratio1_3_16, &ratio1_3_16, &ratio1_3_16, &ratio1_3_16, &ratio1_3_16, &ratio1_3_16, &ratio1_2_16, &ratio1_2_16, &ratio1_2_16, &ratio1_2_16, &ratio1_2_16, 
&ratio1_2_16, &ratio1_2_16, &ratio1_2_16, &ratio1_2_16, &ratio1_2_16, &ratio1_2_16, &ratio1_2_16, &ratio1_2_16, &ratio1_2_16, &ratio1_2_16, &ratio1_2_16, &ratio2_3_16, 
&ratio2_3_16, &ratio2_3_16, &ratio2_3_16, &ratio2_3_16, &ratio2_3_16, &ratio2_3_16, &ratio2_3_16, &ratio2_3_16, &ratio2_3_16, &ratio2_3_16, &ratio2_3_16, &ratio2_3_16, 
&ratio2_3_16, &ratio2_3_16, &ratio2_3_16, &ratio1_1_16, &ratio1_1_16, &ratio1_1_16, &ratio1_1_16, &ratio1_1_16, &ratio1_1_16, &ratio1_1_16, &ratio1_1_16, &ratio1_1_16, 
&ratio1_1_16, &ratio1_1_16, &ratio1_1_16, &ratio1_1_16, &ratio1_1_16, &ratio1_1_16, &ratio1_1_16, &ratio4_3_16, &ratio4_3_16, &ratio4_3_16, &ratio4_3_16, &ratio4_3_16, 
&ratio4_3_16, &ratio4_3_16, &ratio4_3_16, &ratio4_3_16, &ratio4_3_16, &ratio4_3_16, &ratio4_3_16, &ratio4_3_16, &ratio4_3_16, &ratio4_3_16, &ratio4_3_16, &ratio2_1_16, 
&ratio2_1_16, &ratio2_1_16, &ratio2_1_16, &ratio2_1_16, &ratio2_1_16, &ratio2_1_16, &ratio2_1_16, &ratio2_1_16, &ratio2_1_16, &ratio2_1_16, &ratio2_1_16, &ratio2_1_16, 
&ratio2_1_16, &ratio2_1_16, &ratio2_1_16, &ratio8_3_16, &ratio8_3_16, &ratio8_3_16, &ratio8_3_16, &ratio8_3_16, &ratio8_3_16, &ratio8_3_16, &ratio8_3_16, &ratio8_3_16, 
&ratio8_3_16, &ratio8_3_16, &ratio8_3_16, &ratio8_3_16, &ratio8_3_16, &ratio8_3_16, &ratio8_3_16}; 

static const ScaleNote * const SimpleRhythms6_16[128] = {&ratio1_8_16, &ratio1_8_16, &ratio1_8_16, &ratio1_8_16, &ratio1_8_16, &ratio1_8_16, &ratio1_8_16, &ratio1_8_16, &ratio1_8_16, &ratio1_8_16, &ratio1_8_16, &ratio1_8_16, &ratio1_8_16, 
&ratio1_8_16, &ratio1_8_16, &ratio1_8_16, &ratio1_4_16, &ratio1_4_16, &ratio1_4_16, &ratio1_4_16, &ratio1_4_16, &ratio1_4_16, &ratio1_4_16, &ratio1_4_16, &ratio1_4_16, 
&ratio1_4_16, &ratio1_4_16, &ratio1_4_16, &ratio1_4_16, &ratio1_4_16, &ratio1_4_16, &ratio1_4_16, &ratio3_8_16, &ratio3_8_16, &ratio3_8_16, &ratio3_8_16, &ratio3_8_16, 
&ratio3_8_16, &ratio3_8_16, &ratio3_8_16, &ratio3_8_16, &ratio3_8_16, &ratio3_8_16, &ratio3_8_16, &ratio3_8_16, &ratio3_8_16, &ratio3_8_16, &ratio3_8_16, &ratio1_2_16, 
&ratio1_2_16, &ratio1_2_16, &ratio1_2_16, &ratio1_2_16, &ratio1_2_16, &ratio1_2_16, &ratio1_2_16, &ratio1_2_16, &ratio1_2_16, &ratio1_2_16, &ratio1_2_16, &ratio1_2_16, 
&ratio1_2_16, &ratio1_2_16, &ratio1_2_16, &ratio3_4_16, &ratio3_4_16, &ratio3_4_16, &ratio3_4_16, &ratio3_4_16, &ratio3_4_16, &ratio3_4_16, &ratio3_4_16, &ratio3_4_16, 
&ratio3_4_16, &ratio3_4_16, &ratio3_4_16, &ratio3_4_16, &ratio3_4_16, &ratio3_4_16, &ratio3_4_16, &ratio1_1_16, &ratio1_1_16, &ratio1_1_16, &ratio1_1_16, &ratio1_1_16, 
&ratio1_1_16, &ratio1_1_16, &ratio1_1_16, &ratio1_1_16, &ratio1_1_16, &ratio1_1_16, &ratio1_1_16, &ratio1_1_16, &ratio1_1_16, &ratio1_1_16, &ratio1_1_16, &ratio3_2_16, 
&ratio3_2_16, &ratio3_2_16, &ratio3_2_16, &ratio3_2_16, &ratio3_2_16, &ratio3_2_16, &ratio3_2_16, &ratio3_2_16, &ratio3_2_16, &ratio3_2_16, &ratio3_2_16, &ratio3_2_16, 
&ratio3_2_16, &ratio3_2_16, &ratio3_2_16, &ratio2_1_16, &ratio2_1_16, &ratio2_1_16, &ratio2_1_16, &ratio2_1_16, &ratio2_1_16, &ratio2_1_16, &ratio2_1_16, &ratio2_1_16, 
&ratio2_1_16, &ratio2_1_16, &ratio2_1_16, &ratio2_1_16, &ratio2_1_16, &ratio2_1_16, &ratio2_1_16}; 

static const ScaleNote * const SimpleRhythms7_16[128] = {&ratio1_12_16, &ratio1_12_16, &ratio1_12_16, &ratio1_12_16, &ratio1_12_16, &ratio1_12_16, &ratio1_12_16, &ratio1_12_16, &ratio1_12_16, &ratio1_12_16, &ratio1_12_16, &ratio1_12_16, &ratio1_12_16, 
&ratio1_12_16, &ratio1_12_16, &ratio1_12_16, &ratio1_6_16, &ratio1_6_16, &ratio1_6_16, &ratio1_6_16, &ratio1_6_16, &ratio1_6_16, &ratio1_6_16, &ratio1_6_16, &ratio1_6_16, 
&ratio1_6_16, &ratio1_6_16, &ratio1_6_16, &ratio1_6_16, &ratio1_6_16, &ratio1_6_16, &ratio1_6_16, &ratio1_4_16, &ratio1_4_16, &ratio1_4_16, &ratio1_4_16, &ratio1_4_16, 
&ratio1_4_16, &ratio1_4_16, &ratio1_4_16, &ratio1_4_16, &ratio1_4_16, &ratio1_4_16, &ratio1_4_16, &ratio1_4_16, &ratio1_4_16, &ratio1_4_16, &ratio1_4_16, &ratio1_3_16, 
&ratio1_3_16, &ratio1_3_16, &ratio1_3_16, &ratio1_3_16, &ratio1_3_16, &ratio1_3_16, &ratio1_3_16, &ratio1_3_16, &ratio1_3_16, &ratio1_3_16, &ratio1_3_16, &ratio1_3_16, 
&ratio1_3_16, &ratio1_3_16, &ratio1_3_16, &ratio1_2_16, &ratio1_2_16, &ratio1_2_16, &ratio1_2_16, &ratio1_2_16, &ratio1_2_16, &ratio1_2_16, &ratio1_2_16, &ratio1_2_16, 
&ratio1_2_16, &ratio1_2_16, &ratio1_2_16, &ratio1_2_16, &ratio1_2_16, &ratio1_2_16, &ratio1_2_16, &ratio2_3_16, &ratio2_3_16, &ratio2_3_16, &ratio2_3_16, &ratio2_3_16, 
&ratio2_3_16, &ratio2_3_16, &ratio2_3_16, &ratio2_3_16, &ratio2_3_16, &ratio2_3_16, &ratio2_3_16, &ratio2_3_16, &ratio2_3_16, &ratio2_3_16, &ratio2_3_16, &ratio1_1_16, 
&ratio1_1_16, &ratio1_1_16, &ratio1_1_16, &ratio1_1_16, &ratio1_1_16, &ratio1_1_16, &ratio1_1_16, &ratio1_1_16, &ratio1_1_16, &ratio1_1_16, &ratio1_1_16, &ratio1_1_16, 
&ratio1_1_16, &ratio1_1_16, &ratio1_1_16, &ratio4_3_16, &ratio4_3_16, &ratio4_3_16, &ratio4_3_16, &ratio4_3_16, &ratio4_3_16, &ratio4_3_16, &ratio4_3_16, &ratio4_3_16, 
&ratio4_3_16, &ratio4_3_16, &ratio4_3_16, &ratio4_3_16, &ratio4_3_16, &ratio4_3_16, &ratio4_3_16}; 

static const ScaleNote * const SimpleRhythms8_16[128] = {&ratio1_16_16, &ratio1_16_16, &ratio1_16_16, &ratio1_16_16, &ratio1_16_16, &ratio1_16_16, &ratio1_16_16, &ratio1_16_16, &ratio1_16_16, &ratio1_16_16, &ratio1_16_16, &ratio1_16_16, &ratio1_16_16, 
&ratio1_16_16, &ratio1_16_16, &ratio1_16_16, &ratio1_8_16, &ratio1_8_16, &ratio1_8_16, &ratio1_8_16, &ratio1_8_16, &ratio1_8_16, &ratio1_8_16, &ratio1_8_16, &ratio1_8_16, 
&ratio1_8_16, &ratio1_8_16, &ratio1_8_16, &ratio1_8_16, &ratio1_8_16, &ratio1_8_16, &ratio1_8_16, &ratio3_16_16, &ratio3_16_16, &ratio3_16_16, &ratio3_16_16, &ratio3_16_16, 
&ratio3_16_16, &ratio3_16_16, &ratio3_16_16, &ratio3_16_16, &ratio3_16_16, &ratio3_16_16, &ratio3_16_16, &ratio3_16_16, &ratio3_16_16, &ratio3_16_16, &ratio3_16_16, &ratio1_4_16, 
&ratio1_4_16, &ratio1_4_16, &ratio1_4_16, &ratio1_4_16, &ratio1_4_16, &ratio1_4_16, &ratio1_4_16, &ratio1_4_16, &ratio1_4_16, &ratio1_4_16, &ratio1_4_16, &ratio1_4_16, 
&ratio1_4_16, &ratio1_4_16, &ratio1_4_16, &ratio3_8_16, &ratio3_8_16, &ratio3_8_16, &ratio3_8_16, &ratio3_8_16, &ratio3_8_16, &ratio3_8_16, &ratio3_8_16, &ratio3_8_16, 
&ratio3_8_16, &ratio3_8_16, &ratio3_8_16, &ratio3_8_16, &ratio3_8_16, &ratio3_8_16, &ratio3_8_16, &ratio1_2_16, &ratio1_2_16, &ratio1_2_16, &ratio1_2_16, &ratio1_2_16, 
&ratio1_2_16, &ratio1_2_16, &ratio1_2_16, &ratio1_2_16, &ratio1_2_16, &ratio1_2_16, &ratio1_2_16, &ratio1_2_16, &ratio1_2_16, &ratio1_2_16, &ratio1_2_16, &ratio3_4_16, 
&ratio3_4_16, &ratio3_4_16, &ratio3_4_16, &ratio3_4_16, &ratio3_4_16, &ratio3_4_16, &ratio3_4_16, &ratio3_4_16, &ratio3_4_16, &ratio3_4_16, &ratio3_4_16, &ratio3_4_16, 
&ratio3_4_16, &ratio3_4_16, &ratio3_4_16, &ratio1_1_16, &ratio1_1_16, &ratio1_1_16, &ratio1_1_16, &ratio1_1_16, &ratio1_1_16, &ratio1_1_16, &ratio1_1_16, &ratio1_1_16, 
&ratio1_1_16, &ratio1_1_16, &ratio1_1_16, &ratio1_1_16, &ratio1_1_16, &ratio1_1_16, &ratio1_1_16}; 



static const ScaleNote * const rhythmDivisionsReset1[128] = {&ratio2_1_1, &ratio2_1_1, &ratio2_1_1, &ratio2_1_1, &ratio2_1_1, &ratio2_1_1, &ratio2_1_1, &ratio2_1_1, &ratio2_1_1, &ratio2_1_1, &ratio2_1_1, &ratio2_1_1, &ratio2_1_1, 
&ratio2_1_1, &ratio2_1_1, &ratio2_1_1, &ratio3_1_1, &ratio3_1_1, &ratio3_1_1, &ratio3_1_1, &ratio3_1_1, &ratio3_1_1, &ratio3_1_1, &ratio3_1_1, &ratio3_1_1, 
&ratio3_1_1, &ratio3_1_1, &ratio3_1_1, &ratio3_1_1, &ratio3_1_1, &ratio3_1_1, &ratio3_1_1, &ratio4_1_1, &ratio4_1_1, &ratio4_1_1, &ratio4_1_1, &ratio4_1_1, 
&ratio4_1_1, &ratio4_1_1, &ratio4_1_1, &ratio4_1_1, &ratio4_1_1, &ratio4_1_1, &ratio4_1_1, &ratio4_1_1, &ratio4_1_1, &ratio4_1_1, &ratio4_1_1, &ratio5_1_1, 
&ratio5_1_1, &ratio5_1_1, &ratio5_1_1, &ratio5_1_1, &ratio5_1_1, &ratio5_1_1, &ratio5_1_1, &ratio5_1_1, &ratio5_1_1, &ratio5_1_1, &ratio5_1_1, &ratio5_1_1, 
&ratio5_1_1, &ratio5_1_1, &ratio5_1_1, &ratio6_1_1, &ratio6_1_1, &ratio6_1_1, &ratio6_1_1, &ratio6_1_1, &ratio6_1_1, &ratio6_1_1, &ratio6_1_1, &ratio6_1_1, 
&ratio6_1_1, &ratio6_1_1, &ratio6_1_1, &ratio6_1_1, &ratio6_1_1, &ratio6_1_1, &ratio6_1_1, &ratio8_1_1, &ratio8_1_1, &ratio8_1_1, &ratio8_1_1, &ratio8_1_1, 
&ratio8_1_1, &ratio8_1_1, &ratio8_1_1, &ratio8_1_1, &ratio8_1_1, &ratio8_1_1, &ratio8_1_1, &ratio8_1_1, &ratio8_1_1, &ratio8_1_1, &ratio8_1_1, &ratio10_1_1, 
&ratio10_1_1, &ratio10_1_1, &ratio10_1_1, &ratio10_1_1, &ratio10_1_1, &ratio10_1_1, &ratio10_1_1, &ratio10_1_1, &ratio10_1_1, &ratio10_1_1, &ratio10_1_1, &ratio10_1_1, 
&ratio10_1_1, &ratio10_1_1, &ratio10_1_1, &ratio12_1_1, &ratio12_1_1, &ratio12_1_1, &ratio12_1_1, &ratio12_1_1, &ratio12_1_1, &ratio12_1_1, &ratio12_1_1, &ratio12_1_1, 
&ratio12_1_1, &ratio12_1_1, &ratio12_1_1, &ratio12_1_1, &ratio12_1_1, &ratio12_1_1, &ratio12_1_1}; 

static const ScaleNote * const rhythmDivisionsReset2[128] = {&ratio2_1_2, &ratio2_1_2, &ratio2_1_2, &ratio2_1_2, &ratio2_1_2, &ratio2_1_2, &ratio2_1_2, &ratio2_1_2, &ratio2_1_2, &ratio2_1_2, &ratio2_1_2, &ratio2_1_2, &ratio2_1_2, 
&ratio2_1_2, &ratio2_1_2, &ratio2_1_2, &ratio3_1_2, &ratio3_1_2, &ratio3_1_2, &ratio3_1_2, &ratio3_1_2, &ratio3_1_2, &ratio3_1_2, &ratio3_1_2, &ratio3_1_2, 
&ratio3_1_2, &ratio3_1_2, &ratio3_1_2, &ratio3_1_2, &ratio3_1_2, &ratio3_1_2, &ratio3_1_2, &ratio4_1_2, &ratio4_1_2, &ratio4_1_2, &ratio4_1_2, &ratio4_1_2, 
&ratio4_1_2, &ratio4_1_2, &ratio4_1_2, &ratio4_1_2, &ratio4_1_2, &ratio4_1_2, &ratio4_1_2, &ratio4_1_2, &ratio4_1_2, &ratio4_1_2, &ratio4_1_2, &ratio5_1_2, 
&ratio5_1_2, &ratio5_1_2, &ratio5_1_2, &ratio5_1_2, &ratio5_1_2, &ratio5_1_2, &ratio5_1_2, &ratio5_1_2, &ratio5_1_2, &ratio5_1_2, &ratio5_1_2, &ratio5_1_2, 
&ratio5_1_2, &ratio5_1_2, &ratio5_1_2, &ratio6_1_2, &ratio6_1_2, &ratio6_1_2, &ratio6_1_2, &ratio6_1_2, &ratio6_1_2, &ratio6_1_2, &ratio6_1_2, &ratio6_1_2, 
&ratio6_1_2, &ratio6_1_2, &ratio6_1_2, &ratio6_1_2, &ratio6_1_2, &ratio6_1_2, &ratio6_1_2, &ratio8_1_2, &ratio8_1_2, &ratio8_1_2, &ratio8_1_2, &ratio8_1_2, 
&ratio8_1_2, &ratio8_1_2, &ratio8_1_2, &ratio8_1_2, &ratio8_1_2, &ratio8_1_2, &ratio8_1_2, &ratio8_1_2, &ratio8_1_2, &ratio8_1_2, &ratio8_1_2, &ratio10_1_2, 
&ratio10_1_2, &ratio10_1_2, &ratio10_1_2, &ratio10_1_2, &ratio10_1_2, &ratio10_1_2, &ratio10_1_2, &ratio10_1_2, &ratio10_1_2, &ratio10_1_2, &ratio10_1_2, &ratio10_1_2, 
&ratio10_1_2, &ratio10_1_2, &ratio10_1_2, &ratio12_1_2, &ratio12_1_2, &ratio12_1_2, &ratio12_1_2, &ratio12_1_2, &ratio12_1_2, &ratio12_1_2, &ratio12_1_2, &ratio12_1_2, 
&ratio12_1_2, &ratio12_1_2, &ratio12_1_2, &ratio12_1_2, &ratio12_1_2, &ratio12_1_2, &ratio12_1_2}; 

static const ScaleNote * const rhythmDivisionsReset3[128] = {&ratio2_1_3, &ratio2_1_3, &ratio2_1_3, &ratio2_1_3, &ratio2_1_3, &ratio2_1_3, &ratio2_1_3, &ratio2_1_3, &ratio2_1_3, &ratio2_1_3, &ratio2_1_3, &ratio2_1_3, &ratio2_1_3, 
&ratio2_1_3, &ratio2_1_3, &ratio2_1_3, &ratio3_1_3, &ratio3_1_3, &ratio3_1_3, &ratio3_1_3, &ratio3_1_3, &ratio3_1_3, &ratio3_1_3, &ratio3_1_3, &ratio3_1_3, 
&ratio3_1_3, &ratio3_1_3, &ratio3_1_3, &ratio3_1_3, &ratio3_1_3, &ratio3_1_3, &ratio3_1_3, &ratio4_1_3, &ratio4_1_3, &ratio4_1_3, &ratio4_1_3, &ratio4_1_3, 
&ratio4_1_3, &ratio4_1_3, &ratio4_1_3, &ratio4_1_3, &ratio4_1_3, &ratio4_1_3, &ratio4_1_3, &ratio4_1_3, &ratio4_1_3, &ratio4_1_3, &ratio4_1_3, &ratio5_1_3, 
&ratio5_1_3, &ratio5_1_3, &ratio5_1_3, &ratio5_1_3, &ratio5_1_3, &ratio5_1_3, &ratio5_1_3, &ratio5_1_3, &ratio5_1_3, &ratio5_1_3, &ratio5_1_3, &ratio5_1_3, 
&ratio5_1_3, &ratio5_1_3, &ratio5_1_3, &ratio6_1_3, &ratio6_1_3, &ratio6_1_3, &ratio6_1_3, &ratio6_1_3, &ratio6_1_3, &ratio6_1_3, &ratio6_1_3, &ratio6_1_3, 
&ratio6_1_3, &ratio6_1_3, &ratio6_1_3, &ratio6_1_3, &ratio6_1_3, &ratio6_1_3, &ratio6_1_3, &ratio8_1_3, &ratio8_1_3, &ratio8_1_3, &ratio8_1_3, &ratio8_1_3, 
&ratio8_1_3, &ratio8_1_3, &ratio8_1_3, &ratio8_1_3, &ratio8_1_3, &ratio8_1_3, &ratio8_1_3, &ratio8_1_3, &ratio8_1_3, &ratio8_1_3, &ratio8_1_3, &ratio10_1_3, 
&ratio10_1_3, &ratio10_1_3, &ratio10_1_3, &ratio10_1_3, &ratio10_1_3, &ratio10_1_3, &ratio10_1_3, &ratio10_1_3, &ratio10_1_3, &ratio10_1_3, &ratio10_1_3, &ratio10_1_3, 
&ratio10_1_3, &ratio10_1_3, &ratio10_1_3, &ratio12_1_3, &ratio12_1_3, &ratio12_1_3, &ratio12_1_3, &ratio12_1_3, &ratio12_1_3, &ratio12_1_3, &ratio12_1_3, &ratio12_1_3, 
&ratio12_1_3, &ratio12_1_3, &ratio12_1_3, &ratio12_1_3, &ratio12_1_3, &ratio12_1_3, &ratio12_1_3}; 

static const ScaleNote * const rhythmDivisionsReset4[128] = {&ratio2_1_4, &ratio2_1_4, &ratio2_1_4, &ratio2_1_4, &ratio2_1_4, &ratio2_1_4, &ratio2_1_4, &ratio2_1_4, &ratio2_1_4, &ratio2_1_4, &ratio2_1_4, &ratio2_1_4, &ratio2_1_4, 
&ratio2_1_4, &ratio2_1_4, &ratio2_1_4, &ratio3_1_4, &ratio3_1_4, &ratio3_1_4, &ratio3_1_4, &ratio3_1_4, &ratio3_1_4, &ratio3_1_4, &ratio3_1_4, &ratio3_1_4, 
&ratio3_1_4, &ratio3_1_4, &ratio3_1_4, &ratio3_1_4, &ratio3_1_4, &ratio3_1_4, &ratio3_1_4, &ratio4_1_4, &ratio4_1_4, &ratio4_1_4, &ratio4_1_4, &ratio4_1_4, 
&ratio4_1_4, &ratio4_1_4, &ratio4_1_4, &ratio4_1_4, &ratio4_1_4, &ratio4_1_4, &ratio4_1_4, &ratio4_1_4, &ratio4_1_4, &ratio4_1_4, &ratio4_1_4, &ratio5_1_4, 
&ratio5_1_4, &ratio5_1_4, &ratio5_1_4, &ratio5_1_4, &ratio5_1_4, &ratio5_1_4, &ratio5_1_4, &ratio5_1_4, &ratio5_1_4, &ratio5_1_4, &ratio5_1_4, &ratio5_1_4, 
&ratio5_1_4, &ratio5_1_4, &ratio5_1_4, &ratio6_1_4, &ratio6_1_4, &ratio6_1_4, &ratio6_1_4, &ratio6_1_4, &ratio6_1_4, &ratio6_1_4, &ratio6_1_4, &ratio6_1_4, 
&ratio6_1_4, &ratio6_1_4, &ratio6_1_4, &ratio6_1_4, &ratio6_1_4, &ratio6_1_4, &ratio6_1_4, &ratio8_1_4, &ratio8_1_4, &ratio8_1_4, &ratio8_1_4, &ratio8_1_4, 
&ratio8_1_4, &ratio8_1_4, &ratio8_1_4, &ratio8_1_4, &ratio8_1_4, &ratio8_1_4, &ratio8_1_4, &ratio8_1_4, &ratio8_1_4, &ratio8_1_4, &ratio8_1_4, &ratio10_1_4, 
&ratio10_1_4, &ratio10_1_4, &ratio10_1_4, &ratio10_1_4, &ratio10_1_4, &ratio10_1_4, &ratio10_1_4, &ratio10_1_4, &ratio10_1_4, &ratio10_1_4, &ratio10_1_4, &ratio10_1_4, 
&ratio10_1_4, &ratio10_1_4, &ratio10_1_4, &ratio12_1_4, &ratio12_1_4, &ratio12_1_4, &ratio12_1_4, &ratio12_1_4, &ratio12_1_4, &ratio12_1_4, &ratio12_1_4, &ratio12_1_4, 
&ratio12_1_4, &ratio12_1_4, &ratio12_1_4, &ratio12_1_4, &ratio12_1_4, &ratio12_1_4, &ratio12_1_4}; 

static const ScaleNote * const rhythmDivisionsReset5[128] = {&ratio2_1_5, &ratio2_1_5, &ratio2_1_5, &ratio2_1_5, &ratio2_1_5, &ratio2_1_5, &ratio2_1_5, &ratio2_1_5, &ratio2_1_5, &ratio2_1_5, &ratio2_1_5, &ratio2_1_5, &ratio2_1_5, 
&ratio2_1_5, &ratio2_1_5, &ratio2_1_5, &ratio3_1_5, &ratio3_1_5, &ratio3_1_5, &ratio3_1_5, &ratio3_1_5, &ratio3_1_5, &ratio3_1_5, &ratio3_1_5, &ratio3_1_5, 
&ratio3_1_5, &ratio3_1_5, &ratio3_1_5, &ratio3_1_5, &ratio3_1_5, &ratio3_1_5, &ratio3_1_5, &ratio4_1_5, &ratio4_1_5, &ratio4_1_5, &ratio4_1_5, &ratio4_1_5, 
&ratio4_1_5, &ratio4_1_5, &ratio4_1_5, &ratio4_1_5, &ratio4_1_5, &ratio4_1_5, &ratio4_1_5, &ratio4_1_5, &ratio4_1_5, &ratio4_1_5, &ratio4_1_5, &ratio5_1_5, 
&ratio5_1_5, &ratio5_1_5, &ratio5_1_5, &ratio5_1_5, &ratio5_1_5, &ratio5_1_5, &ratio5_1_5, &ratio5_1_5, &ratio5_1_5, &ratio5_1_5, &ratio5_1_5, &ratio5_1_5, 
&ratio5_1_5, &ratio5_1_5, &ratio5_1_5, &ratio6_1_5, &ratio6_1_5, &ratio6_1_5, &ratio6_1_5, &ratio6_1_5, &ratio6_1_5, &ratio6_1_5, &ratio6_1_5, &ratio6_1_5, 
&ratio6_1_5, &ratio6_1_5, &ratio6_1_5, &ratio6_1_5, &ratio6_1_5, &ratio6_1_5, &ratio6_1_5, &ratio8_1_5, &ratio8_1_5, &ratio8_1_5, &ratio8_1_5, &ratio8_1_5, 
&ratio8_1_5, &ratio8_1_5, &ratio8_1_5, &ratio8_1_5, &ratio8_1_5, &ratio8_1_5, &ratio8_1_5, &ratio8_1_5, &ratio8_1_5, &ratio8_1_5, &ratio8_1_5, &ratio10_1_5, 
&ratio10_1_5, &ratio10_1_5, &ratio10_1_5, &ratio10_1_5, &ratio10_1_5, &ratio10_1_5, &ratio10_1_5, &ratio10_1_5, &ratio10_1_5, &ratio10_1_5, &ratio10_1_5, &ratio10_1_5, 
&ratio10_1_5, &ratio10_1_5, &ratio10_1_5, &ratio12_1_5, &ratio12_1_5, &ratio12_1_5, &ratio12_1_5, &ratio12_1_5, &ratio12_1_5, &ratio12_1_5, &ratio12_1_5, &ratio12_1_5, 
&ratio12_1_5, &ratio12_1_5, &ratio12_1_5, &ratio12_1_5, &ratio12_1_5, &ratio12_1_5, &ratio12_1_5}; 

static const ScaleNote * const rhythmDivisionsReset6[128] = {&ratio2_1_6, &ratio2_1_6, &ratio2_1_6, &ratio2_1_6, &ratio2_1_6, &ratio2_1_6, &ratio2_1_6, &ratio2_1_6, &ratio2_1_6, &ratio2_1_6, &ratio2_1_6, &ratio2_1_6, &ratio2_1_6, 
&ratio2_1_6, &ratio2_1_6, &ratio2_1_6, &ratio3_1_6, &ratio3_1_6, &ratio3_1_6, &ratio3_1_6, &ratio3_1_6, &ratio3_1_6, &ratio3_1_6, &ratio3_1_6, &ratio3_1_6, 
&ratio3_1_6, &ratio3_1_6, &ratio3_1_6, &ratio3_1_6, &ratio3_1_6, &ratio3_1_6, &ratio3_1_6, &ratio4_1_6, &ratio4_1_6, &ratio4_1_6, &ratio4_1_6, &ratio4_1_6, 
&ratio4_1_6, &ratio4_1_6, &ratio4_1_6, &ratio4_1_6, &ratio4_1_6, &ratio4_1_6, &ratio4_1_6, &ratio4_1_6, &ratio4_1_6, &ratio4_1_6, &ratio4_1_6, &ratio5_1_6, 
&ratio5_1_6, &ratio5_1_6, &ratio5_1_6, &ratio5_1_6, &ratio5_1_6, &ratio5_1_6, &ratio5_1_6, &ratio5_1_6, &ratio5_1_6, &ratio5_1_6, &ratio5_1_6, &ratio5_1_6, 
&ratio5_1_6, &ratio5_1_6, &ratio5_1_6, &ratio6_1_6, &ratio6_1_6, &ratio6_1_6, &ratio6_1_6, &ratio6_1_6, &ratio6_1_6, &ratio6_1_6, &ratio6_1_6, &ratio6_1_6, 
&ratio6_1_6, &ratio6_1_6, &ratio6_1_6, &ratio6_1_6, &ratio6_1_6, &ratio6_1_6, &ratio6_1_6, &ratio8_1_6, &ratio8_1_6, &ratio8_1_6, &ratio8_1_6, &ratio8_1_6, 
&ratio8_1_6, &ratio8_1_6, &ratio8_1_6, &ratio8_1_6, &ratio8_1_6, &ratio8_1_6, &ratio8_1_6, &ratio8_1_6, &ratio8_1_6, &ratio8_1_6, &ratio8_1_6, &ratio10_1_6, 
&ratio10_1_6, &ratio10_1_6, &ratio10_1_6, &ratio10_1_6, &ratio10_1_6, &ratio10_1_6, &ratio10_1_6, &ratio10_1_6, &ratio10_1_6, &ratio10_1_6, &ratio10_1_6, &ratio10_1_6, 
&ratio10_1_6, &ratio10_1_6, &ratio10_1_6, &ratio12_1_6, &ratio12_1_6, &ratio12_1_6, &ratio12_1_6, &ratio12_1_6, &ratio12_1_6, &ratio12_1_6, &ratio12_1_6, &ratio12_1_6, 
&ratio12_1_6, &ratio12_1_6, &ratio12_1_6, &ratio12_1_6, &ratio12_1_6, &ratio12_1_6, &ratio12_1_6}; 

static const ScaleNote * const rhythmDivisionsReset7[128] = {&ratio2_1_7, &ratio2_1_7, &ratio2_1_7, &ratio2_1_7, &ratio2_1_7, &ratio2_1_7, &ratio2_1_7, &ratio2_1_7, &ratio2_1_7, &ratio2_1_7, &ratio2_1_7, &ratio2_1_7, &ratio2_1_7, 
&ratio2_1_7, &ratio2_1_7, &ratio2_1_7, &ratio3_1_7, &ratio3_1_7, &ratio3_1_7, &ratio3_1_7, &ratio3_1_7, &ratio3_1_7, &ratio3_1_7, &ratio3_1_7, &ratio3_1_7, 
&ratio3_1_7, &ratio3_1_7, &ratio3_1_7, &ratio3_1_7, &ratio3_1_7, &ratio3_1_7, &ratio3_1_7, &ratio4_1_7, &ratio4_1_7, &ratio4_1_7, &ratio4_1_7, &ratio4_1_7, 
&ratio4_1_7, &ratio4_1_7, &ratio4_1_7, &ratio4_1_7, &ratio4_1_7, &ratio4_1_7, &ratio4_1_7, &ratio4_1_7, &ratio4_1_7, &ratio4_1_7, &ratio4_1_7, &ratio5_1_7, 
&ratio5_1_7, &ratio5_1_7, &ratio5_1_7, &ratio5_1_7, &ratio5_1_7, &ratio5_1_7, &ratio5_1_7, &ratio5_1_7, &ratio5_1_7, &ratio5_1_7, &ratio5_1_7, &ratio5_1_7, 
&ratio5_1_7, &ratio5_1_7, &ratio5_1_7, &ratio6_1_7, &ratio6_1_7, &ratio6_1_7, &ratio6_1_7, &ratio6_1_7, &ratio6_1_7, &ratio6_1_7, &ratio6_1_7, &ratio6_1_7, 
&ratio6_1_7, &ratio6_1_7, &ratio6_1_7, &ratio6_1_7, &ratio6_1_7, &ratio6_1_7, &ratio6_1_7, &ratio8_1_7, &ratio8_1_7, &ratio8_1_7, &ratio8_1_7, &ratio8_1_7, 
&ratio8_1_7, &ratio8_1_7, &ratio8_1_7, &ratio8_1_7, &ratio8_1_7, &ratio8_1_7, &ratio8_1_7, &ratio8_1_7, &ratio8_1_7, &ratio8_1_7, &ratio8_1_7, &ratio10_1_7, 
&ratio10_1_7, &ratio10_1_7, &ratio10_1_7, &ratio10_1_7, &ratio10_1_7, &ratio10_1_7, &ratio10_1_7, &ratio10_1_7, &ratio10_1_7, &ratio10_1_7, &ratio10_1_7, &ratio10_1_7, 
&ratio10_1_7, &ratio10_1_7, &ratio10_1_7, &ratio12_1_7, &ratio12_1_7, &ratio12_1_7, &ratio12_1_7, &ratio12_1_7, &ratio12_1_7, &ratio12_1_7, &ratio12_1_7, &ratio12_1_7, 
&ratio12_1_7, &ratio12_1_7, &ratio12_1_7, &ratio12_1_7, &ratio12_1_7, &ratio12_1_7, &ratio12_1_7}; 

static const ScaleNote * const rhythmDivisionsReset8[128] = {&ratio2_1_8, &ratio2_1_8, &ratio2_1_8, &ratio2_1_8, &ratio2_1_8, &ratio2_1_8, &ratio2_1_8, &ratio2_1_8, &ratio2_1_8, &ratio2_1_8, &ratio2_1_8, &ratio2_1_8, &ratio2_1_8, 
&ratio2_1_8, &ratio2_1_8, &ratio2_1_8, &ratio3_1_8, &ratio3_1_8, &ratio3_1_8, &ratio3_1_8, &ratio3_1_8, &ratio3_1_8, &ratio3_1_8, &ratio3_1_8, &ratio3_1_8, 
&ratio3_1_8, &ratio3_1_8, &ratio3_1_8, &ratio3_1_8, &ratio3_1_8, &ratio3_1_8, &ratio3_1_8, &ratio4_1_8, &ratio4_1_8, &ratio4_1_8, &ratio4_1_8, &ratio4_1_8, 
&ratio4_1_8, &ratio4_1_8, &ratio4_1_8, &ratio4_1_8, &ratio4_1_8, &ratio4_1_8, &ratio4_1_8, &ratio4_1_8, &ratio4_1_8, &ratio4_1_8, &ratio4_1_8, &ratio5_1_8, 
&ratio5_1_8, &ratio5_1_8, &ratio5_1_8, &ratio5_1_8, &ratio5_1_8, &ratio5_1_8, &ratio5_1_8, &ratio5_1_8, &ratio5_1_8, &ratio5_1_8, &ratio5_1_8, &ratio5_1_8, 
&ratio5_1_8, &ratio5_1_8, &ratio5_1_8, &ratio6_1_8, &ratio6_1_8, &ratio6_1_8, &ratio6_1_8, &ratio6_1_8, &ratio6_1_8, &ratio6_1_8, &ratio6_1_8, &ratio6_1_8, 
&ratio6_1_8, &ratio6_1_8, &ratio6_1_8, &ratio6_1_8, &ratio6_1_8, &ratio6_1_8, &ratio6_1_8, &ratio8_1_8, &ratio8_1_8, &ratio8_1_8, &ratio8_1_8, &ratio8_1_8, 
&ratio8_1_8, &ratio8_1_8, &ratio8_1_8, &ratio8_1_8, &ratio8_1_8, &ratio8_1_8, &ratio8_1_8, &ratio8_1_8, &ratio8_1_8, &ratio8_1_8, &ratio8_1_8, &ratio10_1_8, 
&ratio10_1_8, &ratio10_1_8, &ratio10_1_8, &ratio10_1_8, &ratio10_1_8, &ratio10_1_8, &ratio10_1_8, &ratio10_1_8, &ratio10_1_8, &ratio10_1_8, &ratio10_1_8, &ratio10_1_8, 
&ratio10_1_8, &ratio10_1_8, &ratio10_1_8, &ratio12_1_8, &ratio12_1_8, &ratio12_1_8, &ratio12_1_8, &ratio12_1_8, &ratio12_1_8, &ratio12_1_8, &ratio12_1_8, &ratio12_1_8, 
&ratio12_1_8, &ratio12_1_8, &ratio12_1_8, &ratio12_1_8, &ratio12_1_8, &ratio12_1_8, &ratio12_1_8}; 



static const ScaleNote * const polyResets1[128] = {&ratio1_4_1, &ratio1_4_1, &ratio1_4_1, &ratio1_4_1, &ratio1_4_1, &ratio1_4_1, &ratio1_4_1, &ratio1_4_1, &ratio1_3_1, &ratio1_3_1, &ratio1_3_1, &ratio1_3_1, &ratio1_3_1, 
&ratio1_3_1, &ratio1_3_1, &ratio1_3_1, &ratio1_3_1, &ratio1_3_1, &ratio1_3_1, &ratio1_3_1, &ratio1_3_1, &ratio1_3_1, &ratio1_3_1, &ratio1_3_1, &ratio2_3_1, 
&ratio2_3_1, &ratio2_3_1, &ratio2_3_1, &ratio2_3_1, &ratio2_3_1, &ratio2_3_1, &ratio2_3_1, &ratio3_4_1, &ratio3_4_1, &ratio3_4_1, &ratio3_4_1, &ratio3_4_1, 
&ratio3_4_1, &ratio3_4_1, &ratio3_4_1, &ratio4_5_1, &ratio4_5_1, &ratio4_5_1, &ratio4_5_1, &ratio4_5_1, &ratio4_5_1, &ratio4_5_1, &ratio4_5_1, &ratio1_1_1, 
&ratio1_1_1, &ratio1_1_1, &ratio1_1_1, &ratio1_1_1, &ratio1_1_1, &ratio1_1_1, &ratio1_1_1, &ratio9_8_1, &ratio9_8_1, &ratio9_8_1, &ratio9_8_1, &ratio9_8_1, 
&ratio9_8_1, &ratio9_8_1, &ratio9_8_1, &ratio6_5_1, &ratio6_5_1, &ratio6_5_1, &ratio6_5_1, &ratio6_5_1, &ratio6_5_1, &ratio6_5_1, &ratio6_5_1, &ratio5_4_1, 
&ratio5_4_1, &ratio5_4_1, &ratio5_4_1, &ratio5_4_1, &ratio5_4_1, &ratio5_4_1, &ratio5_4_1, &ratio4_3_1, &ratio4_3_1, &ratio4_3_1, &ratio4_3_1, &ratio4_3_1, 
&ratio4_3_1, &ratio4_3_1, &ratio4_3_1, &ratio7_5_1, &ratio7_5_1, &ratio7_5_1, &ratio7_5_1, &ratio7_5_1, &ratio7_5_1, &ratio7_5_1, &ratio7_5_1, &ratio3_2_1, 
&ratio3_2_1, &ratio3_2_1, &ratio3_2_1, &ratio3_2_1, &ratio3_2_1, &ratio3_2_1, &ratio3_2_1, &ratio5_3_1, &ratio5_3_1, &ratio5_3_1, &ratio5_3_1, &ratio5_3_1, 
&ratio5_3_1, &ratio5_3_1, &ratio5_3_1, &ratio7_4_1, &ratio7_4_1, &ratio7_4_1, &ratio7_4_1, &ratio7_4_1, &ratio7_4_1, &ratio7_4_1, &ratio7_4_1, &ratio5_2_1, 
&ratio5_2_1, &ratio5_2_1, &ratio5_2_1, &ratio5_2_1, &ratio5_2_1, &ratio5_2_1, &ratio5_2_1}; 

static const ScaleNote * const polyResets10[128] = {&ratio1_4_10, &ratio1_4_10, &ratio1_4_10, &ratio1_4_10, &ratio1_4_10, &ratio1_4_10, &ratio1_4_10, &ratio1_4_10, &ratio1_3_10, &ratio1_3_10, &ratio1_3_10, &ratio1_3_10, &ratio1_3_10, 
&ratio1_3_10, &ratio1_3_10, &ratio1_3_10, &ratio1_3_10, &ratio1_3_10, &ratio1_3_10, &ratio1_3_10, &ratio1_3_10, &ratio1_3_10, &ratio1_3_10, &ratio1_3_10, &ratio2_3_10, 
&ratio2_3_10, &ratio2_3_10, &ratio2_3_10, &ratio2_3_10, &ratio2_3_10, &ratio2_3_10, &ratio2_3_10, &ratio3_4_10, &ratio3_4_10, &ratio3_4_10, &ratio3_4_10, &ratio3_4_10, 
&ratio3_4_10, &ratio3_4_10, &ratio3_4_10, &ratio4_5_10, &ratio4_5_10, &ratio4_5_10, &ratio4_5_10, &ratio4_5_10, &ratio4_5_10, &ratio4_5_10, &ratio4_5_10, &ratio1_1_10, 
&ratio1_1_10, &ratio1_1_10, &ratio1_1_10, &ratio1_1_10, &ratio1_1_10, &ratio1_1_10, &ratio1_1_10, &ratio9_8_10, &ratio9_8_10, &ratio9_8_10, &ratio9_8_10, &ratio9_8_10, 
&ratio9_8_10, &ratio9_8_10, &ratio9_8_10, &ratio6_5_10, &ratio6_5_10, &ratio6_5_10, &ratio6_5_10, &ratio6_5_10, &ratio6_5_10, &ratio6_5_10, &ratio6_5_10, &ratio5_4_10, 
&ratio5_4_10, &ratio5_4_10, &ratio5_4_10, &ratio5_4_10, &ratio5_4_10, &ratio5_4_10, &ratio5_4_10, &ratio4_3_10, &ratio4_3_10, &ratio4_3_10, &ratio4_3_10, &ratio4_3_10, 
&ratio4_3_10, &ratio4_3_10, &ratio4_3_10, &ratio7_5_10, &ratio7_5_10, &ratio7_5_10, &ratio7_5_10, &ratio7_5_10, &ratio7_5_10, &ratio7_5_10, &ratio7_5_10, &ratio3_2_10, 
&ratio3_2_10, &ratio3_2_10, &ratio3_2_10, &ratio3_2_10, &ratio3_2_10, &ratio3_2_10, &ratio3_2_10, &ratio5_3_10, &ratio5_3_10, &ratio5_3_10, &ratio5_3_10, &ratio5_3_10, 
&ratio5_3_10, &ratio5_3_10, &ratio5_3_10, &ratio7_4_10, &ratio7_4_10, &ratio7_4_10, &ratio7_4_10, &ratio7_4_10, &ratio7_4_10, &ratio7_4_10, &ratio7_4_10, &ratio5_2_10, 
&ratio5_2_10, &ratio5_2_10, &ratio5_2_10, &ratio5_2_10, &ratio5_2_10, &ratio5_2_10, &ratio5_2_10}; 

static const ScaleNote * const polyResets11[128] = {&ratio1_4_11, &ratio1_4_11, &ratio1_4_11, &ratio1_4_11, &ratio1_4_11, &ratio1_4_11, &ratio1_4_11, &ratio1_4_11, &ratio1_3_11, &ratio1_3_11, &ratio1_3_11, &ratio1_3_11, &ratio1_3_11, 
&ratio1_3_11, &ratio1_3_11, &ratio1_3_11, &ratio1_3_11, &ratio1_3_11, &ratio1_3_11, &ratio1_3_11, &ratio1_3_11, &ratio1_3_11, &ratio1_3_11, &ratio1_3_11, &ratio2_3_11, 
&ratio2_3_11, &ratio2_3_11, &ratio2_3_11, &ratio2_3_11, &ratio2_3_11, &ratio2_3_11, &ratio2_3_11, &ratio3_4_11, &ratio3_4_11, &ratio3_4_11, &ratio3_4_11, &ratio3_4_11, 
&ratio3_4_11, &ratio3_4_11, &ratio3_4_11, &ratio4_5_11, &ratio4_5_11, &ratio4_5_11, &ratio4_5_11, &ratio4_5_11, &ratio4_5_11, &ratio4_5_11, &ratio4_5_11, &ratio1_1_11, 
&ratio1_1_11, &ratio1_1_11, &ratio1_1_11, &ratio1_1_11, &ratio1_1_11, &ratio1_1_11, &ratio1_1_11, &ratio9_8_11, &ratio9_8_11, &ratio9_8_11, &ratio9_8_11, &ratio9_8_11, 
&ratio9_8_11, &ratio9_8_11, &ratio9_8_11, &ratio6_5_11, &ratio6_5_11, &ratio6_5_11, &ratio6_5_11, &ratio6_5_11, &ratio6_5_11, &ratio6_5_11, &ratio6_5_11, &ratio5_4_11, 
&ratio5_4_11, &ratio5_4_11, &ratio5_4_11, &ratio5_4_11, &ratio5_4_11, &ratio5_4_11, &ratio5_4_11, &ratio4_3_11, &ratio4_3_11, &ratio4_3_11, &ratio4_3_11, &ratio4_3_11, 
&ratio4_3_11, &ratio4_3_11, &ratio4_3_11, &ratio7_5_11, &ratio7_5_11, &ratio7_5_11, &ratio7_5_11, &ratio7_5_11, &ratio7_5_11, &ratio7_5_11, &ratio7_5_11, &ratio3_2_11, 
&ratio3_2_11, &ratio3_2_11, &ratio3_2_11, &ratio3_2_11, &ratio3_2_11, &ratio3_2_11, &ratio3_2_11, &ratio5_3_11, &ratio5_3_11, &ratio5_3_11, &ratio5_3_11, &ratio5_3_11, 
&ratio5_3_11, &ratio5_3_11, &ratio5_3_11, &ratio7_4_11, &ratio7_4_11, &ratio7_4_11, &ratio7_4_11, &ratio7_4_11, &ratio7_4_11, &ratio7_4_11, &ratio7_4_11, &ratio5_2_11, 
&ratio5_2_11, &ratio5_2_11, &ratio5_2_11, &ratio5_2_11, &ratio5_2_11, &ratio5_2_11, &ratio5_2_11}; 

static const ScaleNote * const polyResets12[128] = {&ratio1_4_12, &ratio1_4_12, &ratio1_4_12, &ratio1_4_12, &ratio1_4_12, &ratio1_4_12, &ratio1_4_12, &ratio1_4_12, &ratio1_3_12, &ratio1_3_12, &ratio1_3_12, &ratio1_3_12, &ratio1_3_12, 
&ratio1_3_12, &ratio1_3_12, &ratio1_3_12, &ratio1_3_12, &ratio1_3_12, &ratio1_3_12, &ratio1_3_12, &ratio1_3_12, &ratio1_3_12, &ratio1_3_12, &ratio1_3_12, &ratio2_3_12, 
&ratio2_3_12, &ratio2_3_12, &ratio2_3_12, &ratio2_3_12, &ratio2_3_12, &ratio2_3_12, &ratio2_3_12, &ratio3_4_12, &ratio3_4_12, &ratio3_4_12, &ratio3_4_12, &ratio3_4_12, 
&ratio3_4_12, &ratio3_4_12, &ratio3_4_12, &ratio4_5_12, &ratio4_5_12, &ratio4_5_12, &ratio4_5_12, &ratio4_5_12, &ratio4_5_12, &ratio4_5_12, &ratio4_5_12, &ratio1_1_12, 
&ratio1_1_12, &ratio1_1_12, &ratio1_1_12, &ratio1_1_12, &ratio1_1_12, &ratio1_1_12, &ratio1_1_12, &ratio9_8_12, &ratio9_8_12, &ratio9_8_12, &ratio9_8_12, &ratio9_8_12, 
&ratio9_8_12, &ratio9_8_12, &ratio9_8_12, &ratio6_5_12, &ratio6_5_12, &ratio6_5_12, &ratio6_5_12, &ratio6_5_12, &ratio6_5_12, &ratio6_5_12, &ratio6_5_12, &ratio5_4_12, 
&ratio5_4_12, &ratio5_4_12, &ratio5_4_12, &ratio5_4_12, &ratio5_4_12, &ratio5_4_12, &ratio5_4_12, &ratio4_3_12, &ratio4_3_12, &ratio4_3_12, &ratio4_3_12, &ratio4_3_12, 
&ratio4_3_12, &ratio4_3_12, &ratio4_3_12, &ratio7_5_12, &ratio7_5_12, &ratio7_5_12, &ratio7_5_12, &ratio7_5_12, &ratio7_5_12, &ratio7_5_12, &ratio7_5_12, &ratio3_2_12, 
&ratio3_2_12, &ratio3_2_12, &ratio3_2_12, &ratio3_2_12, &ratio3_2_12, &ratio3_2_12, &ratio3_2_12, &ratio5_3_12, &ratio5_3_12, &ratio5_3_12, &ratio5_3_12, &ratio5_3_12, 
&ratio5_3_12, &ratio5_3_12, &ratio5_3_12, &ratio7_4_12, &ratio7_4_12, &ratio7_4_12, &ratio7_4_12, &ratio7_4_12, &ratio7_4_12, &ratio7_4_12, &ratio7_4_12, &ratio5_2_12, 
&ratio5_2_12, &ratio5_2_12, &ratio5_2_12, &ratio5_2_12, &ratio5_2_12, &ratio5_2_12, &ratio5_2_12}; 

static const ScaleNote * const polyResets13[128] = {&ratio1_4_13, &ratio1_4_13, &ratio1_4_13, &ratio1_4_13, &ratio1_4_13, &ratio1_4_13, &ratio1_4_13, &ratio1_4_13, &ratio1_3_13, &ratio1_3_13, &ratio1_3_13, &ratio1_3_13, &ratio1_3_13, 
&ratio1_3_13, &ratio1_3_13, &ratio1_3_13, &ratio1_3_13, &ratio1_3_13, &ratio1_3_13, &ratio1_3_13, &ratio1_3_13, &ratio1_3_13, &ratio1_3_13, &ratio1_3_13, &ratio2_3_13, 
&ratio2_3_13, &ratio2_3_13, &ratio2_3_13, &ratio2_3_13, &ratio2_3_13, &ratio2_3_13, &ratio2_3_13, &ratio3_4_13, &ratio3_4_13, &ratio3_4_13, &ratio3_4_13, &ratio3_4_13, 
&ratio3_4_13, &ratio3_4_13, &ratio3_4_13, &ratio4_5_13, &ratio4_5_13, &ratio4_5_13, &ratio4_5_13, &ratio4_5_13, &ratio4_5_13, &ratio4_5_13, &ratio4_5_13, &ratio1_1_13, 
&ratio1_1_13, &ratio1_1_13, &ratio1_1_13, &ratio1_1_13, &ratio1_1_13, &ratio1_1_13, &ratio1_1_13, &ratio9_8_13, &ratio9_8_13, &ratio9_8_13, &ratio9_8_13, &ratio9_8_13, 
&ratio9_8_13, &ratio9_8_13, &ratio9_8_13, &ratio6_5_13, &ratio6_5_13, &ratio6_5_13, &ratio6_5_13, &ratio6_5_13, &ratio6_5_13, &ratio6_5_13, &ratio6_5_13, &ratio5_4_13, 
&ratio5_4_13, &ratio5_4_13, &ratio5_4_13, &ratio5_4_13, &ratio5_4_13, &ratio5_4_13, &ratio5_4_13, &ratio4_3_13, &ratio4_3_13, &ratio4_3_13, &ratio4_3_13, &ratio4_3_13, 
&ratio4_3_13, &ratio4_3_13, &ratio4_3_13, &ratio7_5_13, &ratio7_5_13, &ratio7_5_13, &ratio7_5_13, &ratio7_5_13, &ratio7_5_13, &ratio7_5_13, &ratio7_5_13, &ratio3_2_13, 
&ratio3_2_13, &ratio3_2_13, &ratio3_2_13, &ratio3_2_13, &ratio3_2_13, &ratio3_2_13, &ratio3_2_13, &ratio5_3_13, &ratio5_3_13, &ratio5_3_13, &ratio5_3_13, &ratio5_3_13, 
&ratio5_3_13, &ratio5_3_13, &ratio5_3_13, &ratio7_4_13, &ratio7_4_13, &ratio7_4_13, &ratio7_4_13, &ratio7_4_13, &ratio7_4_13, &ratio7_4_13, &ratio7_4_13, &ratio5_2_13, 
&ratio5_2_13, &ratio5_2_13, &ratio5_2_13, &ratio5_2_13, &ratio5_2_13, &ratio5_2_13, &ratio5_2_13}; 

static const ScaleNote * const polyResets14[128] = {&ratio1_4_14, &ratio1_4_14, &ratio1_4_14, &ratio1_4_14, &ratio1_4_14, &ratio1_4_14, &ratio1_4_14, &ratio1_4_14, &ratio1_3_14, &ratio1_3_14, &ratio1_3_14, &ratio1_3_14, &ratio1_3_14, 
&ratio1_3_14, &ratio1_3_14, &ratio1_3_14, &ratio1_3_14, &ratio1_3_14, &ratio1_3_14, &ratio1_3_14, &ratio1_3_14, &ratio1_3_14, &ratio1_3_14, &ratio1_3_14, &ratio2_3_14, 
&ratio2_3_14, &ratio2_3_14, &ratio2_3_14, &ratio2_3_14, &ratio2_3_14, &ratio2_3_14, &ratio2_3_14, &ratio3_4_14, &ratio3_4_14, &ratio3_4_14, &ratio3_4_14, &ratio3_4_14, 
&ratio3_4_14, &ratio3_4_14, &ratio3_4_14, &ratio4_5_14, &ratio4_5_14, &ratio4_5_14, &ratio4_5_14, &ratio4_5_14, &ratio4_5_14, &ratio4_5_14, &ratio4_5_14, &ratio1_1_14, 
&ratio1_1_14, &ratio1_1_14, &ratio1_1_14, &ratio1_1_14, &ratio1_1_14, &ratio1_1_14, &ratio1_1_14, &ratio9_8_14, &ratio9_8_14, &ratio9_8_14, &ratio9_8_14, &ratio9_8_14, 
&ratio9_8_14, &ratio9_8_14, &ratio9_8_14, &ratio6_5_14, &ratio6_5_14, &ratio6_5_14, &ratio6_5_14, &ratio6_5_14, &ratio6_5_14, &ratio6_5_14, &ratio6_5_14, &ratio5_4_14, 
&ratio5_4_14, &ratio5_4_14, &ratio5_4_14, &ratio5_4_14, &ratio5_4_14, &ratio5_4_14, &ratio5_4_14, &ratio4_3_14, &ratio4_3_14, &ratio4_3_14, &ratio4_3_14, &ratio4_3_14, 
&ratio4_3_14, &ratio4_3_14, &ratio4_3_14, &ratio7_5_14, &ratio7_5_14, &ratio7_5_14, &ratio7_5_14, &ratio7_5_14, &ratio7_5_14, &ratio7_5_14, &ratio7_5_14, &ratio3_2_14, 
&ratio3_2_14, &ratio3_2_14, &ratio3_2_14, &ratio3_2_14, &ratio3_2_14, &ratio3_2_14, &ratio3_2_14, &ratio5_3_14, &ratio5_3_14, &ratio5_3_14, &ratio5_3_14, &ratio5_3_14, 
&ratio5_3_14, &ratio5_3_14, &ratio5_3_14, &ratio7_4_14, &ratio7_4_14, &ratio7_4_14, &ratio7_4_14, &ratio7_4_14, &ratio7_4_14, &ratio7_4_14, &ratio7_4_14, &ratio5_2_14, 
&ratio5_2_14, &ratio5_2_14, &ratio5_2_14, &ratio5_2_14, &ratio5_2_14, &ratio5_2_14, &ratio5_2_14}; 

static const ScaleNote * const polyResets15[128] = {&ratio1_4_15, &ratio1_4_15, &ratio1_4_15, &ratio1_4_15, &ratio1_4_15, &ratio1_4_15, &ratio1_4_15, &ratio1_4_15, &ratio1_3_15, &ratio1_3_15, &ratio1_3_15, &ratio1_3_15, &ratio1_3_15, 
&ratio1_3_15, &ratio1_3_15, &ratio1_3_15, &ratio1_3_15, &ratio1_3_15, &ratio1_3_15, &ratio1_3_15, &ratio1_3_15, &ratio1_3_15, &ratio1_3_15, &ratio1_3_15, &ratio2_3_15, 
&ratio2_3_15, &ratio2_3_15, &ratio2_3_15, &ratio2_3_15, &ratio2_3_15, &ratio2_3_15, &ratio2_3_15, &ratio3_4_15, &ratio3_4_15, &ratio3_4_15, &ratio3_4_15, &ratio3_4_15, 
&ratio3_4_15, &ratio3_4_15, &ratio3_4_15, &ratio4_5_15, &ratio4_5_15, &ratio4_5_15, &ratio4_5_15, &ratio4_5_15, &ratio4_5_15, &ratio4_5_15, &ratio4_5_15, &ratio1_1_15, 
&ratio1_1_15, &ratio1_1_15, &ratio1_1_15, &ratio1_1_15, &ratio1_1_15, &ratio1_1_15, &ratio1_1_15, &ratio9_8_15, &ratio9_8_15, &ratio9_8_15, &ratio9_8_15, &ratio9_8_15, 
&ratio9_8_15, &ratio9_8_15, &ratio9_8_15, &ratio6_5_15, &ratio6_5_15, &ratio6_5_15, &ratio6_5_15, &ratio6_5_15, &ratio6_5_15, &ratio6_5_15, &ratio6_5_15, &ratio5_4_15, 
&ratio5_4_15, &ratio5_4_15, &ratio5_4_15, &ratio5_4_15, &ratio5_4_15, &ratio5_4_15, &ratio5_4_15, &ratio4_3_15, &ratio4_3_15, &ratio4_3_15, &ratio4_3_15, &ratio4_3_15, 
&ratio4_3_15, &ratio4_3_15, &ratio4_3_15, &ratio7_5_15, &ratio7_5_15, &ratio7_5_15, &ratio7_5_15, &ratio7_5_15, &ratio7_5_15, &ratio7_5_15, &ratio7_5_15, &ratio3_2_15, 
&ratio3_2_15, &ratio3_2_15, &ratio3_2_15, &ratio3_2_15, &ratio3_2_15, &ratio3_2_15, &ratio3_2_15, &ratio5_3_15, &ratio5_3_15, &ratio5_3_15, &ratio5_3_15, &ratio5_3_15, 
&ratio5_3_15, &ratio5_3_15, &ratio5_3_15, &ratio7_4_15, &ratio7_4_15, &ratio7_4_15, &ratio7_4_15, &ratio7_4_15, &ratio7_4_15, &ratio7_4_15, &ratio7_4_15, &ratio5_2_15, 
&ratio5_2_15, &ratio5_2_15, &ratio5_2_15, &ratio5_2_15, &ratio5_2_15, &ratio5_2_15, &ratio5_2_15}; 

static const ScaleNote * const polyResets16[128] = {&ratio1_4_16, &ratio1_4_16, &ratio1_4_16, &ratio1_4_16, &ratio1_4_16, &ratio1_4_16, &ratio1_4_16, &ratio1_4_16, &ratio1_3_16, &ratio1_3_16, &ratio1_3_16, &ratio1_3_16, &ratio1_3_16, 
&ratio1_3_16, &ratio1_3_16, &ratio1_3_16, &ratio1_3_16, &ratio1_3_16, &ratio1_3_16, &ratio1_3_16, &ratio1_3_16, &ratio1_3_16, &ratio1_3_16, &ratio1_3_16, &ratio2_3_16, 
&ratio2_3_16, &ratio2_3_16, &ratio2_3_16, &ratio2_3_16, &ratio2_3_16, &ratio2_3_16, &ratio2_3_16, &ratio3_4_16, &ratio3_4_16, &ratio3_4_16, &ratio3_4_16, &ratio3_4_16, 
&ratio3_4_16, &ratio3_4_16, &ratio3_4_16, &ratio4_5_16, &ratio4_5_16, &ratio4_5_16, &ratio4_5_16, &ratio4_5_16, &ratio4_5_16, &ratio4_5_16, &ratio4_5_16, &ratio1_1_16, 
&ratio1_1_16, &ratio1_1_16, &ratio1_1_16, &ratio1_1_16, &ratio1_1_16, &ratio1_1_16, &ratio1_1_16, &ratio9_8_16, &ratio9_8_16, &ratio9_8_16, &ratio9_8_16, &ratio9_8_16, 
&ratio9_8_16, &ratio9_8_16, &ratio9_8_16, &ratio6_5_16, &ratio6_5_16, &ratio6_5_16, &ratio6_5_16, &ratio6_5_16, &ratio6_5_16, &ratio6_5_16, &ratio6_5_16, &ratio5_4_16, 
&ratio5_4_16, &ratio5_4_16, &ratio5_4_16, &ratio5_4_16, &ratio5_4_16, &ratio5_4_16, &ratio5_4_16, &ratio4_3_16, &ratio4_3_16, &ratio4_3_16, &ratio4_3_16, &ratio4_3_16, 
&ratio4_3_16, &ratio4_3_16, &ratio4_3_16, &ratio7_5_16, &ratio7_5_16, &ratio7_5_16, &ratio7_5_16, &ratio7_5_16, &ratio7_5_16, &ratio7_5_16, &ratio7_5_16, &ratio3_2_16, 
&ratio3_2_16, &ratio3_2_16, &ratio3_2_16, &ratio3_2_16, &ratio3_2_16, &ratio3_2_16, &ratio3_2_16, &ratio5_3_16, &ratio5_3_16, &ratio5_3_16, &ratio5_3_16, &ratio5_3_16, 
&ratio5_3_16, &ratio5_3_16, &ratio5_3_16, &ratio7_4_16, &ratio7_4_16, &ratio7_4_16, &ratio7_4_16, &ratio7_4_16, &ratio7_4_16, &ratio7_4_16, &ratio7_4_16, &ratio5_2_16, 
&ratio5_2_16, &ratio5_2_16, &ratio5_2_16, &ratio5_2_16, &ratio5_2_16, &ratio5_2_16, &ratio5_2_16}; 

static const ScaleNote * const polyResets2[128] = {&ratio1_4_2, &ratio1_4_2, &ratio1_4_2, &ratio1_4_2, &ratio1_4_2, &ratio1_4_2, &ratio1_4_2, &ratio1_4_2, &ratio1_3_2, &ratio1_3_2, &ratio1_3_2, &ratio1_3_2, &ratio1_3_2, 
&ratio1_3_2, &ratio1_3_2, &ratio1_3_2, &ratio1_3_2, &ratio1_3_2, &ratio1_3_2, &ratio1_3_2, &ratio1_3_2, &ratio1_3_2, &ratio1_3_2, &ratio1_3_2, &ratio2_3_2, 
&ratio2_3_2, &ratio2_3_2, &ratio2_3_2, &ratio2_3_2, &ratio2_3_2, &ratio2_3_2, &ratio2_3_2, &ratio3_4_2, &ratio3_4_2, &ratio3_4_2, &ratio3_4_2, &ratio3_4_2, 
&ratio3_4_2, &ratio3_4_2, &ratio3_4_2, &ratio4_5_2, &ratio4_5_2, &ratio4_5_2, &ratio4_5_2, &ratio4_5_2, &ratio4_5_2, &ratio4_5_2, &ratio4_5_2, &ratio1_1_2, 
&ratio1_1_2, &ratio1_1_2, &ratio1_1_2, &ratio1_1_2, &ratio1_1_2, &ratio1_1_2, &ratio1_1_2, &ratio9_8_2, &ratio9_8_2, &ratio9_8_2, &ratio9_8_2, &ratio9_8_2, 
&ratio9_8_2, &ratio9_8_2, &ratio9_8_2, &ratio6_5_2, &ratio6_5_2, &ratio6_5_2, &ratio6_5_2, &ratio6_5_2, &ratio6_5_2, &ratio6_5_2, &ratio6_5_2, &ratio5_4_2, 
&ratio5_4_2, &ratio5_4_2, &ratio5_4_2, &ratio5_4_2, &ratio5_4_2, &ratio5_4_2, &ratio5_4_2, &ratio4_3_2, &ratio4_3_2, &ratio4_3_2, &ratio4_3_2, &ratio4_3_2, 
&ratio4_3_2, &ratio4_3_2, &ratio4_3_2, &ratio7_5_2, &ratio7_5_2, &ratio7_5_2, &ratio7_5_2, &ratio7_5_2, &ratio7_5_2, &ratio7_5_2, &ratio7_5_2, &ratio3_2_2, 
&ratio3_2_2, &ratio3_2_2, &ratio3_2_2, &ratio3_2_2, &ratio3_2_2, &ratio3_2_2, &ratio3_2_2, &ratio5_3_2, &ratio5_3_2, &ratio5_3_2, &ratio5_3_2, &ratio5_3_2, 
&ratio5_3_2, &ratio5_3_2, &ratio5_3_2, &ratio7_4_2, &ratio7_4_2, &ratio7_4_2, &ratio7_4_2, &ratio7_4_2, &ratio7_4_2, &ratio7_4_2, &ratio7_4_2, &ratio5_2_2, 
&ratio5_2_2, &ratio5_2_2, &ratio5_2_2, &ratio5_2_2, &ratio5_2_2, &ratio5_2_2, &ratio5_2_2}; 

static const ScaleNote * const polyResets3[128] = {&ratio1_4_3, &ratio1_4_3, &ratio1_4_3, &ratio1_4_3, &ratio1_4_3, &ratio1_4_3, &ratio1_4_3, &ratio1_4_3, &ratio1_3_3, &ratio1_3_3, &ratio1_3_3, &ratio1_3_3, &ratio1_3_3, 
&ratio1_3_3, &ratio1_3_3, &ratio1_3_3, &ratio1_3_3, &ratio1_3_3, &ratio1_3_3, &ratio1_3_3, &ratio1_3_3, &ratio1_3_3, &ratio1_3_3, &ratio1_3_3, &ratio2_3_3, 
&ratio2_3_3, &ratio2_3_3, &ratio2_3_3, &ratio2_3_3, &ratio2_3_3, &ratio2_3_3, &ratio2_3_3, &ratio3_4_3, &ratio3_4_3, &ratio3_4_3, &ratio3_4_3, &ratio3_4_3, 
&ratio3_4_3, &ratio3_4_3, &ratio3_4_3, &ratio4_5_3, &ratio4_5_3, &ratio4_5_3, &ratio4_5_3, &ratio4_5_3, &ratio4_5_3, &ratio4_5_3, &ratio4_5_3, &ratio1_1_3, 
&ratio1_1_3, &ratio1_1_3, &ratio1_1_3, &ratio1_1_3, &ratio1_1_3, &ratio1_1_3, &ratio1_1_3, &ratio9_8_3, &ratio9_8_3, &ratio9_8_3, &ratio9_8_3, &ratio9_8_3, 
&ratio9_8_3, &ratio9_8_3, &ratio9_8_3, &ratio6_5_3, &ratio6_5_3, &ratio6_5_3, &ratio6_5_3, &ratio6_5_3, &ratio6_5_3, &ratio6_5_3, &ratio6_5_3, &ratio5_4_3, 
&ratio5_4_3, &ratio5_4_3, &ratio5_4_3, &ratio5_4_3, &ratio5_4_3, &ratio5_4_3, &ratio5_4_3, &ratio4_3_3, &ratio4_3_3, &ratio4_3_3, &ratio4_3_3, &ratio4_3_3, 
&ratio4_3_3, &ratio4_3_3, &ratio4_3_3, &ratio7_5_3, &ratio7_5_3, &ratio7_5_3, &ratio7_5_3, &ratio7_5_3, &ratio7_5_3, &ratio7_5_3, &ratio7_5_3, &ratio3_2_3, 
&ratio3_2_3, &ratio3_2_3, &ratio3_2_3, &ratio3_2_3, &ratio3_2_3, &ratio3_2_3, &ratio3_2_3, &ratio5_3_3, &ratio5_3_3, &ratio5_3_3, &ratio5_3_3, &ratio5_3_3, 
&ratio5_3_3, &ratio5_3_3, &ratio5_3_3, &ratio7_4_3, &ratio7_4_3, &ratio7_4_3, &ratio7_4_3, &ratio7_4_3, &ratio7_4_3, &ratio7_4_3, &ratio7_4_3, &ratio5_2_3, 
&ratio5_2_3, &ratio5_2_3, &ratio5_2_3, &ratio5_2_3, &ratio5_2_3, &ratio5_2_3, &ratio5_2_3}; 

static const ScaleNote * const polyResets4[128] = {&ratio1_4_4, &ratio1_4_4, &ratio1_4_4, &ratio1_4_4, &ratio1_4_4, &ratio1_4_4, &ratio1_4_4, &ratio1_4_4, &ratio1_3_4, &ratio1_3_4, &ratio1_3_4, &ratio1_3_4, &ratio1_3_4, 
&ratio1_3_4, &ratio1_3_4, &ratio1_3_4, &ratio1_3_4, &ratio1_3_4, &ratio1_3_4, &ratio1_3_4, &ratio1_3_4, &ratio1_3_4, &ratio1_3_4, &ratio1_3_4, &ratio2_3_4, 
&ratio2_3_4, &ratio2_3_4, &ratio2_3_4, &ratio2_3_4, &ratio2_3_4, &ratio2_3_4, &ratio2_3_4, &ratio3_4_4, &ratio3_4_4, &ratio3_4_4, &ratio3_4_4, &ratio3_4_4, 
&ratio3_4_4, &ratio3_4_4, &ratio3_4_4, &ratio4_5_4, &ratio4_5_4, &ratio4_5_4, &ratio4_5_4, &ratio4_5_4, &ratio4_5_4, &ratio4_5_4, &ratio4_5_4, &ratio1_1_4, 
&ratio1_1_4, &ratio1_1_4, &ratio1_1_4, &ratio1_1_4, &ratio1_1_4, &ratio1_1_4, &ratio1_1_4, &ratio9_8_4, &ratio9_8_4, &ratio9_8_4, &ratio9_8_4, &ratio9_8_4, 
&ratio9_8_4, &ratio9_8_4, &ratio9_8_4, &ratio6_5_4, &ratio6_5_4, &ratio6_5_4, &ratio6_5_4, &ratio6_5_4, &ratio6_5_4, &ratio6_5_4, &ratio6_5_4, &ratio5_4_4, 
&ratio5_4_4, &ratio5_4_4, &ratio5_4_4, &ratio5_4_4, &ratio5_4_4, &ratio5_4_4, &ratio5_4_4, &ratio4_3_4, &ratio4_3_4, &ratio4_3_4, &ratio4_3_4, &ratio4_3_4, 
&ratio4_3_4, &ratio4_3_4, &ratio4_3_4, &ratio7_5_4, &ratio7_5_4, &ratio7_5_4, &ratio7_5_4, &ratio7_5_4, &ratio7_5_4, &ratio7_5_4, &ratio7_5_4, &ratio3_2_4, 
&ratio3_2_4, &ratio3_2_4, &ratio3_2_4, &ratio3_2_4, &ratio3_2_4, &ratio3_2_4, &ratio3_2_4, &ratio5_3_4, &ratio5_3_4, &ratio5_3_4, &ratio5_3_4, &ratio5_3_4, 
&ratio5_3_4, &ratio5_3_4, &ratio5_3_4, &ratio7_4_4, &ratio7_4_4, &ratio7_4_4, &ratio7_4_4, &ratio7_4_4, &ratio7_4_4, &ratio7_4_4, &ratio7_4_4, &ratio5_2_4, 
&ratio5_2_4, &ratio5_2_4, &ratio5_2_4, &ratio5_2_4, &ratio5_2_4, &ratio5_2_4, &ratio5_2_4}; 

static const ScaleNote * const polyResets5[128] = {&ratio1_4_5, &ratio1_4_5, &ratio1_4_5, &ratio1_4_5, &ratio1_4_5, &ratio1_4_5, &ratio1_4_5, &ratio1_4_5, &ratio1_3_5, &ratio1_3_5, &ratio1_3_5, &ratio1_3_5, &ratio1_3_5, 
&ratio1_3_5, &ratio1_3_5, &ratio1_3_5, &ratio1_3_5, &ratio1_3_5, &ratio1_3_5, &ratio1_3_5, &ratio1_3_5, &ratio1_3_5, &ratio1_3_5, &ratio1_3_5, &ratio2_3_5, 
&ratio2_3_5, &ratio2_3_5, &ratio2_3_5, &ratio2_3_5, &ratio2_3_5, &ratio2_3_5, &ratio2_3_5, &ratio3_4_5, &ratio3_4_5, &ratio3_4_5, &ratio3_4_5, &ratio3_4_5, 
&ratio3_4_5, &ratio3_4_5, &ratio3_4_5, &ratio4_5_5, &ratio4_5_5, &ratio4_5_5, &ratio4_5_5, &ratio4_5_5, &ratio4_5_5, &ratio4_5_5, &ratio4_5_5, &ratio1_1_5, 
&ratio1_1_5, &ratio1_1_5, &ratio1_1_5, &ratio1_1_5, &ratio1_1_5, &ratio1_1_5, &ratio1_1_5, &ratio9_8_5, &ratio9_8_5, &ratio9_8_5, &ratio9_8_5, &ratio9_8_5, 
&ratio9_8_5, &ratio9_8_5, &ratio9_8_5, &ratio6_5_5, &ratio6_5_5, &ratio6_5_5, &ratio6_5_5, &ratio6_5_5, &ratio6_5_5, &ratio6_5_5, &ratio6_5_5, &ratio5_4_5, 
&ratio5_4_5, &ratio5_4_5, &ratio5_4_5, &ratio5_4_5, &ratio5_4_5, &ratio5_4_5, &ratio5_4_5, &ratio4_3_5, &ratio4_3_5, &ratio4_3_5, &ratio4_3_5, &ratio4_3_5, 
&ratio4_3_5, &ratio4_3_5, &ratio4_3_5, &ratio7_5_5, &ratio7_5_5, &ratio7_5_5, &ratio7_5_5, &ratio7_5_5, &ratio7_5_5, &ratio7_5_5, &ratio7_5_5, &ratio3_2_5, 
&ratio3_2_5, &ratio3_2_5, &ratio3_2_5, &ratio3_2_5, &ratio3_2_5, &ratio3_2_5, &ratio3_2_5, &ratio5_3_5, &ratio5_3_5, &ratio5_3_5, &ratio5_3_5, &ratio5_3_5, 
&ratio5_3_5, &ratio5_3_5, &ratio5_3_5, &ratio7_4_5, &ratio7_4_5, &ratio7_4_5, &ratio7_4_5, &ratio7_4_5, &ratio7_4_5, &ratio7_4_5, &ratio7_4_5, &ratio5_2_5, 
&ratio5_2_5, &ratio5_2_5, &ratio5_2_5, &ratio5_2_5, &ratio5_2_5, &ratio5_2_5, &ratio5_2_5}; 

static const ScaleNote * const polyResets6[128] = {&ratio1_4_6, &ratio1_4_6, &ratio1_4_6, &ratio1_4_6, &ratio1_4_6, &ratio1_4_6, &ratio1_4_6, &ratio1_4_6, &ratio1_3_6, &ratio1_3_6, &ratio1_3_6, &ratio1_3_6, &ratio1_3_6, 
&ratio1_3_6, &ratio1_3_6, &ratio1_3_6, &ratio1_3_6, &ratio1_3_6, &ratio1_3_6, &ratio1_3_6, &ratio1_3_6, &ratio1_3_6, &ratio1_3_6, &ratio1_3_6, &ratio2_3_6, 
&ratio2_3_6, &ratio2_3_6, &ratio2_3_6, &ratio2_3_6, &ratio2_3_6, &ratio2_3_6, &ratio2_3_6, &ratio3_4_6, &ratio3_4_6, &ratio3_4_6, &ratio3_4_6, &ratio3_4_6, 
&ratio3_4_6, &ratio3_4_6, &ratio3_4_6, &ratio4_5_6, &ratio4_5_6, &ratio4_5_6, &ratio4_5_6, &ratio4_5_6, &ratio4_5_6, &ratio4_5_6, &ratio4_5_6, &ratio1_1_6, 
&ratio1_1_6, &ratio1_1_6, &ratio1_1_6, &ratio1_1_6, &ratio1_1_6, &ratio1_1_6, &ratio1_1_6, &ratio9_8_6, &ratio9_8_6, &ratio9_8_6, &ratio9_8_6, &ratio9_8_6, 
&ratio9_8_6, &ratio9_8_6, &ratio9_8_6, &ratio6_5_6, &ratio6_5_6, &ratio6_5_6, &ratio6_5_6, &ratio6_5_6, &ratio6_5_6, &ratio6_5_6, &ratio6_5_6, &ratio5_4_6, 
&ratio5_4_6, &ratio5_4_6, &ratio5_4_6, &ratio5_4_6, &ratio5_4_6, &ratio5_4_6, &ratio5_4_6, &ratio4_3_6, &ratio4_3_6, &ratio4_3_6, &ratio4_3_6, &ratio4_3_6, 
&ratio4_3_6, &ratio4_3_6, &ratio4_3_6, &ratio7_5_6, &ratio7_5_6, &ratio7_5_6, &ratio7_5_6, &ratio7_5_6, &ratio7_5_6, &ratio7_5_6, &ratio7_5_6, &ratio3_2_6, 
&ratio3_2_6, &ratio3_2_6, &ratio3_2_6, &ratio3_2_6, &ratio3_2_6, &ratio3_2_6, &ratio3_2_6, &ratio5_3_6, &ratio5_3_6, &ratio5_3_6, &ratio5_3_6, &ratio5_3_6, 
&ratio5_3_6, &ratio5_3_6, &ratio5_3_6, &ratio7_4_6, &ratio7_4_6, &ratio7_4_6, &ratio7_4_6, &ratio7_4_6, &ratio7_4_6, &ratio7_4_6, &ratio7_4_6, &ratio5_2_6, 
&ratio5_2_6, &ratio5_2_6, &ratio5_2_6, &ratio5_2_6, &ratio5_2_6, &ratio5_2_6, &ratio5_2_6}; 

static const ScaleNote * const polyResets7[128] = {&ratio1_4_7, &ratio1_4_7, &ratio1_4_7, &ratio1_4_7, &ratio1_4_7, &ratio1_4_7, &ratio1_4_7, &ratio1_4_7, &ratio1_3_7, &ratio1_3_7, &ratio1_3_7, &ratio1_3_7, &ratio1_3_7, 
&ratio1_3_7, &ratio1_3_7, &ratio1_3_7, &ratio1_3_7, &ratio1_3_7, &ratio1_3_7, &ratio1_3_7, &ratio1_3_7, &ratio1_3_7, &ratio1_3_7, &ratio1_3_7, &ratio2_3_7, 
&ratio2_3_7, &ratio2_3_7, &ratio2_3_7, &ratio2_3_7, &ratio2_3_7, &ratio2_3_7, &ratio2_3_7, &ratio3_4_7, &ratio3_4_7, &ratio3_4_7, &ratio3_4_7, &ratio3_4_7, 
&ratio3_4_7, &ratio3_4_7, &ratio3_4_7, &ratio4_5_7, &ratio4_5_7, &ratio4_5_7, &ratio4_5_7, &ratio4_5_7, &ratio4_5_7, &ratio4_5_7, &ratio4_5_7, &ratio1_1_7, 
&ratio1_1_7, &ratio1_1_7, &ratio1_1_7, &ratio1_1_7, &ratio1_1_7, &ratio1_1_7, &ratio1_1_7, &ratio9_8_7, &ratio9_8_7, &ratio9_8_7, &ratio9_8_7, &ratio9_8_7, 
&ratio9_8_7, &ratio9_8_7, &ratio9_8_7, &ratio6_5_7, &ratio6_5_7, &ratio6_5_7, &ratio6_5_7, &ratio6_5_7, &ratio6_5_7, &ratio6_5_7, &ratio6_5_7, &ratio5_4_7, 
&ratio5_4_7, &ratio5_4_7, &ratio5_4_7, &ratio5_4_7, &ratio5_4_7, &ratio5_4_7, &ratio5_4_7, &ratio4_3_7, &ratio4_3_7, &ratio4_3_7, &ratio4_3_7, &ratio4_3_7, 
&ratio4_3_7, &ratio4_3_7, &ratio4_3_7, &ratio7_5_7, &ratio7_5_7, &ratio7_5_7, &ratio7_5_7, &ratio7_5_7, &ratio7_5_7, &ratio7_5_7, &ratio7_5_7, &ratio3_2_7, 
&ratio3_2_7, &ratio3_2_7, &ratio3_2_7, &ratio3_2_7, &ratio3_2_7, &ratio3_2_7, &ratio3_2_7, &ratio5_3_7, &ratio5_3_7, &ratio5_3_7, &ratio5_3_7, &ratio5_3_7, 
&ratio5_3_7, &ratio5_3_7, &ratio5_3_7, &ratio7_4_7, &ratio7_4_7, &ratio7_4_7, &ratio7_4_7, &ratio7_4_7, &ratio7_4_7, &ratio7_4_7, &ratio7_4_7, &ratio5_2_7, 
&ratio5_2_7, &ratio5_2_7, &ratio5_2_7, &ratio5_2_7, &ratio5_2_7, &ratio5_2_7, &ratio5_2_7}; 

static const ScaleNote * const polyResets8[128] = {&ratio1_4_8, &ratio1_4_8, &ratio1_4_8, &ratio1_4_8, &ratio1_4_8, &ratio1_4_8, &ratio1_4_8, &ratio1_4_8, &ratio1_3_8, &ratio1_3_8, &ratio1_3_8, &ratio1_3_8, &ratio1_3_8, 
&ratio1_3_8, &ratio1_3_8, &ratio1_3_8, &ratio1_3_8, &ratio1_3_8, &ratio1_3_8, &ratio1_3_8, &ratio1_3_8, &ratio1_3_8, &ratio1_3_8, &ratio1_3_8, &ratio2_3_8, 
&ratio2_3_8, &ratio2_3_8, &ratio2_3_8, &ratio2_3_8, &ratio2_3_8, &ratio2_3_8, &ratio2_3_8, &ratio3_4_8, &ratio3_4_8, &ratio3_4_8, &ratio3_4_8, &ratio3_4_8, 
&ratio3_4_8, &ratio3_4_8, &ratio3_4_8, &ratio4_5_8, &ratio4_5_8, &ratio4_5_8, &ratio4_5_8, &ratio4_5_8, &ratio4_5_8, &ratio4_5_8, &ratio4_5_8, &ratio1_1_8, 
&ratio1_1_8, &ratio1_1_8, &ratio1_1_8, &ratio1_1_8, &ratio1_1_8, &ratio1_1_8, &ratio1_1_8, &ratio9_8_8, &ratio9_8_8, &ratio9_8_8, &ratio9_8_8, &ratio9_8_8, 
&ratio9_8_8, &ratio9_8_8, &ratio9_8_8, &ratio6_5_8, &ratio6_5_8, &ratio6_5_8, &ratio6_5_8, &ratio6_5_8, &ratio6_5_8, &ratio6_5_8, &ratio6_5_8, &ratio5_4_8, 
&ratio5_4_8, &ratio5_4_8, &ratio5_4_8, &ratio5_4_8, &ratio5_4_8, &ratio5_4_8, &ratio5_4_8, &ratio4_3_8, &ratio4_3_8, &ratio4_3_8, &ratio4_3_8, &ratio4_3_8, 
&ratio4_3_8, &ratio4_3_8, &ratio4_3_8, &ratio7_5_8, &ratio7_5_8, &ratio7_5_8, &ratio7_5_8, &ratio7_5_8, &ratio7_5_8, &ratio7_5_8, &ratio7_5_8, &ratio3_2_8, 
&ratio3_2_8, &ratio3_2_8, &ratio3_2_8, &ratio3_2_8, &ratio3_2_8, &ratio3_2_8, &ratio3_2_8, &ratio5_3_8, &ratio5_3_8, &ratio5_3_8, &ratio5_3_8, &ratio5_3_8, 
&ratio5_3_8, &ratio5_3_8, &ratio5_3_8, &ratio7_4_8, &ratio7_4_8, &ratio7_4_8, &ratio7_4_8, &ratio7_4_8, &ratio7_4_8, &ratio7_4_8, &ratio7_4_8, &ratio5_2_8, 
&ratio5_2_8, &ratio5_2_8, &ratio5_2_8, &ratio5_2_8, &ratio5_2_8, &ratio5_2_8, &ratio5_2_8}; 

static const ScaleNote * const polyResets9[128] = {&ratio1_4_9, &ratio1_4_9, &ratio1_4_9, &ratio1_4_9, &ratio1_4_9, &ratio1_4_9, &ratio1_4_9, &ratio1_4_9, &ratio1_3_9, &ratio1_3_9, &ratio1_3_9, &ratio1_3_9, &ratio1_3_9, 
&ratio1_3_9, &ratio1_3_9, &ratio1_3_9, &ratio1_3_9, &ratio1_3_9, &ratio1_3_9, &ratio1_3_9, &ratio1_3_9, &ratio1_3_9, &ratio1_3_9, &ratio1_3_9, &ratio2_3_9, 
&ratio2_3_9, &ratio2_3_9, &ratio2_3_9, &ratio2_3_9, &ratio2_3_9, &ratio2_3_9, &ratio2_3_9, &ratio3_4_9, &ratio3_4_9, &ratio3_4_9, &ratio3_4_9, &ratio3_4_9, 
&ratio3_4_9, &ratio3_4_9, &ratio3_4_9, &ratio4_5_9, &ratio4_5_9, &ratio4_5_9, &ratio4_5_9, &ratio4_5_9, &ratio4_5_9, &ratio4_5_9, &ratio4_5_9, &ratio1_1_9, 
&ratio1_1_9, &ratio1_1_9, &ratio1_1_9, &ratio1_1_9, &ratio1_1_9, &ratio1_1_9, &ratio1_1_9, &ratio9_8_9, &ratio9_8_9, &ratio9_8_9, &ratio9_8_9, &ratio9_8_9, 
&ratio9_8_9, &ratio9_8_9, &ratio9_8_9, &ratio6_5_9, &ratio6_5_9, &ratio6_5_9, &ratio6_5_9, &ratio6_5_9, &ratio6_5_9, &ratio6_5_9, &ratio6_5_9, &ratio5_4_9, 
&ratio5_4_9, &ratio5_4_9, &ratio5_4_9, &ratio5_4_9, &ratio5_4_9, &ratio5_4_9, &ratio5_4_9, &ratio4_3_9, &ratio4_3_9, &ratio4_3_9, &ratio4_3_9, &ratio4_3_9, 
&ratio4_3_9, &ratio4_3_9, &ratio4_3_9, &ratio7_5_9, &ratio7_5_9, &ratio7_5_9, &ratio7_5_9, &ratio7_5_9, &ratio7_5_9, &ratio7_5_9, &ratio7_5_9, &ratio3_2_9, 
&ratio3_2_9, &ratio3_2_9, &ratio3_2_9, &ratio3_2_9, &ratio3_2_9, &ratio3_2_9, &ratio3_2_9, &ratio5_3_9, &ratio5_3_9, &ratio5_3_9, &ratio5_3_9, &ratio5_3_9, 
&ratio5_3_9, &ratio5_3_9, &ratio5_3_9, &ratio7_4_9, &ratio7_4_9, &ratio7_4_9, &ratio7_4_9, &ratio7_4_9, &ratio7_4_9, &ratio7_4_9, &ratio7_4_9, &ratio5_2_9, 
&ratio5_2_9, &ratio5_2_9, &ratio5_2_9, &ratio5_2_9, &ratio5_2_9, &ratio5_2_9, &ratio5_2_9}; 






static const ScaleNote* const*integerRatiosGrid[8] = {integerRatios1, integerRatios2, integerRatios3, integerRatios4, integerRatios5, integerRatios6, integerRatios7, integerRatios8}; 

static const ScaleNote* const*even_integersGrid[9] = {even_integers0, even_integers1, even_integers2, even_integers3, even_integers4, even_integers5, even_integers6, even_integers7, even_integers8}; 

static const ScaleNote* const*rhythm_integersGrid[9] = {rhythm_integers0, rhythm_integers1, rhythm_integers2, rhythm_integers3, rhythm_integers4, rhythm_integers5, rhythm_integers6, rhythm_integers7, rhythm_integers8}; 

static const ScaleNote* const*odd_integersGrid[9] = {odd_integers0, odd_integers1, odd_integers2, odd_integers3, odd_integers4, odd_integers5, odd_integers6, odd_integers7, odd_integers8}; 

static const ScaleNote* const*modal_tetradsGrid[8] = {modal_tetradsainversion_walk, modal_tetradsbinversion_walk, modal_tetradinversion_walk, modal_tetradsdinversion_walk, modal_tetradseinversion_walk, modal_tetradsfinversion_walk, modal_tetradsginversion_walk, modal_tetradshinversion_walk}; 

static const ScaleNote* const*seventhTetradsMinimalProgressionGrid[8] = {a_maj7thinversion_walk, a_maj7th2ndIninversion_walk, b_dom7thinversion_walk, b_dom7thRotateinversion_walk, c_subDom7thinversion_walk, c_subDom7thRotateinversion_walk, min7thinversion_walk, min7th2ndIninversion_walk}; 

static const ScaleNote* const*impressionistGrid[8] = {impressionista_vs_impressionistb, impressionist_vs_impressionistd, impressioniste_vs_impressionistf, impressionistg_vs_impressionisth, impressionisti_vs_impressionistj, impressionistk_vs_impressionistl, impressionistm_vs_impressionistn, impressionisto_vs_impressionistp}; 

static const ScaleNote* const*bohlenPeirceGrid[8] = {bohlenPeirceAScale_vs_bohlenPeirceBlueLambda, bohlenPeirceBlueLambda2_vs_bohlenPeirceDurI, bohlenPeirceDurII_vs_bohlenPeirceGamma, bohlenPeirceGLambda_vs_bohlenPeirceHarmoni, bohlenPeirceHPentatoni_vs_bohlenPeirceMollI, bohlenPeirceMollII_vs_bohlenPeirceProoijenMaj, bohlenPeirceProoijenMin_vs_bohlenPeirceWalkerA, bohlenPeirceWalkerB_vs_bohlenPeirceWalkerI}; 

static const ScaleNote* const*modesofrootGrid[8] = {modesofroota, modesofrootb, modesofrootc, modesofrootd, modesofroote, modesofrootf, modesofrootg, modesofrooth}; 

static const ScaleNote* const*tetrad_inversionsGrid[16] = {tetrad_inversionsa, tetrad_inversionsb, tetrad_inversionsc, tetrad_inversionsd, tetrad_inversionse, tetrad_inversionsf, tetrad_inversionsg, tetrad_inversionsh, tetrad_inversionsi, tetrad_inversionsj, tetrad_inversionsk, tetrad_inversionsl, tetrad_inversionsm, tetrad_inversionsn, tetrad_inversionso, tetrad_inversionsp}; 

static const ScaleNote* const*harmonic_entropyGrid[8] = {harmonic_entropyA, harmonic_entropyB, harmonic_entropyC, harmonic_entropyD, harmonic_entropyE, harmonic_entropyF, harmonic_entropyG, harmonic_entropyH}; 

static const ScaleNote* const*bohlenPeircevoctGrid[8] = {bohlenPeirceAScalevoct, bohlenPeirceBlueLambdavoct, bohlenPeirceDurIvoct, bohlenPeirceGammavoct, bohlenPeirceHarmonicvoct, bohlenPeirceMollIvoct, bohlenPeirceProoijenMinvoct, bohlenPeirceWalkerBvoct}; 

static const ScaleNote* const*simpleRhythmsGrid[8] = {simpleRhythms1, simpleRhythms2, simpleRhythms3, simpleRhythms4, simpleRhythms5, simpleRhythms6, simpleRhythms7, simpleRhythms8}; 

static const ScaleNote* const*simpleRhythms16Grid[8] = {SimpleRhythms1_16, SimpleRhythms2_16, SimpleRhythms3_16, SimpleRhythms4_16, SimpleRhythms5_16, SimpleRhythms6_16, SimpleRhythms7_16, SimpleRhythms8_16}; 

static const ScaleNote* const*rhythmDivisionsResetGrid[8] = {rhythmDivisionsReset1, rhythmDivisionsReset2, rhythmDivisionsReset3, rhythmDivisionsReset4, rhythmDivisionsReset5, rhythmDivisionsReset6, rhythmDivisionsReset7, rhythmDivisionsReset8}; 

static const ScaleNote* const*polyResetsGrid[16] = {polyResets1, polyResets10, polyResets11, polyResets12, polyResets13, polyResets14, polyResets15, polyResets16, polyResets2, polyResets3, polyResets4, polyResets5, polyResets6, polyResets7, polyResets8, polyResets9}; 




static const Scale integerRatios = {
   .grid = integerRatiosGrid,
   .t2Bitshift = 9,
   .oneVoltOct = 0};

static const Scale even_integers = {
   .grid = even_integersGrid,
   .t2Bitshift = 9,
   .oneVoltOct = 0};

static const Scale rhythm_integers = {
   .grid = rhythm_integersGrid,
   .t2Bitshift = 9,
   .oneVoltOct = 0};

static const Scale odd_integers = {
   .grid = odd_integersGrid,
   .t2Bitshift = 9,
   .oneVoltOct = 0};

static const Scale modal_tetrads = {
   .grid = modal_tetradsGrid,
   .t2Bitshift = 9,
   .oneVoltOct = 0};

static const Scale seventhTetradsMinimalProgression = {
   .grid = seventhTetradsMinimalProgressionGrid,
   .t2Bitshift = 9,
   .oneVoltOct = 0};

static const Scale impressionist = {
   .grid = impressionistGrid,
   .t2Bitshift = 9,
   .oneVoltOct = 0};

static const Scale bohlenPeirce = {
   .grid = bohlenPeirceGrid,
   .t2Bitshift = 9,
   .oneVoltOct = 0};

static const Scale modesofroot = {
   .grid = modesofrootGrid,
   .t2Bitshift = 9,
   .oneVoltOct = 1};

static const Scale tetrad_inversions = {
   .grid = tetrad_inversionsGrid,
   .t2Bitshift = 8,
   .oneVoltOct = 1};

static const Scale harmonic_entropy = {
   .grid = harmonic_entropyGrid,
   .t2Bitshift = 9,
   .oneVoltOct = 1};

static const Scale bohlenPeircevoct = {
   .grid = bohlenPeircevoctGrid,
   .t2Bitshift = 9,
   .oneVoltOct = 0};

static const Scale simpleRhythms = {
   .grid = simpleRhythmsGrid,
   .t2Bitshift = 9,
   .oneVoltOct = 0};

static const Scale simpleRhythms16 = {
   .grid = simpleRhythms16Grid,
   .t2Bitshift = 9,
   .oneVoltOct = 0};

static const Scale rhythmDivisionsReset = {
   .grid = rhythmDivisionsResetGrid,
   .t2Bitshift = 9,
   .oneVoltOct = 0};

static const Scale polyResets = {
   .grid = polyResetsGrid,
   .t2Bitshift = 8,
   .oneVoltOct = 0};

#endif /* INC_SCALES_HPP_ */