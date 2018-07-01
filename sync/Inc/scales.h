#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"



typedef struct {
	const uint32_t integerPart;
	const uint32_t fractionalPart;
	const uint32_t fundamentalDivision;
} ScaleNote;



typedef struct {
	ScaleNote ***grid;
	uint32_t t2Bitshift;
	uint32_t oneVoltOct;
} Scale;



Scale scaleGroup[16];



static const ScaleNote **integerRatiosGrid[8];
Scale integerRatios;
static const ScaleNote **pentamodal5primefullspanGrid[8];
Scale pentamodal5primefullspan;
static const ScaleNote **harmSubharmfullspanGrid[8];
Scale harmSubharmfullspan;
static const ScaleNote **modal5primefullspanGrid[8];
Scale modal5primefullspan;
static const ScaleNote **harmSubharmGrid[8];
Scale harmSubharm;
static const ScaleNote **harmFolded4Grid[4];
Scale harmFolded4;
static const ScaleNote **pentamodal5primeGrid[8];
Scale pentamodal5prime;
static const ScaleNote **triadsGrid[8];
Scale triads;
static const ScaleNote **seventhTetradsMinimalProgressionGrid[16];
Scale seventhTetradsMinimalProgression;
static const ScaleNote **seventhTetradsGrid[16];
Scale seventhTetrads;
static const ScaleNote **modesOfLimitedTranspositionGrid[16];
Scale modesOfLimitedTransposition;
static const ScaleNote **majMin9thPentStarlingGrid[16];
Scale majMin9thPentStarling;
static const ScaleNote **simpleRhythmsGrid[8];
Scale simpleRhythms;
static const ScaleNote **simpleRhythms16Grid[8];
Scale simpleRhythms16;
static const ScaleNote **rhythmDivisionsResetGrid[8];
Scale rhythmDivisionsReset;
static const ScaleNote **polyResetsGrid[16];
Scale polyResets;


static const ScaleNote ratio6_1_4 = {393216, 0, 4};
static const ScaleNote ratio4_5_5 = {52428, 3435973836, 5};
static const ScaleNote ratio7_5_11 = {91750, 1717986918, 11};
static const ScaleNote ratio3_4_13 = {49152, 0, 13};
static const ScaleNote ratio4_1_8 = {262144, 0, 8};
static const ScaleNote ratio9_160 = {3686, 1717986918, 160};
static const ScaleNote ratio1_3_14 = {21845, 1431655765, 14};
static const ScaleNote ratio7_8 = {57344, 0, 8};
static const ScaleNote ratio9_400 = {1474, 2405181685, 400};
static const ScaleNote ratio16_1_16 = {1048576, 0, 16};
static const ScaleNote ratio18_25 = {47185, 3951369912, 25};
static const ScaleNote ratio3_2_2 = {98304, 0, 2};
static const ScaleNote ratio1_13 = {5041, 991146299, 13};
static const ScaleNote ratio3_4_16 = {49152, 0, 16};
static const ScaleNote ratio16_3 = {349525, 1431655765, 3};
static const ScaleNote ratio25_576 = {2844, 1908874353, 576};
static const ScaleNote ratio2_1_2 = {131072, 0, 2};
static const ScaleNote ratio12_5 = {157286, 1717986918, 5};
static const ScaleNote ratio4_3_9 = {87381, 1431655765, 9};
static const ScaleNote ratio5_144 = {2275, 2386092942, 144};
static const ScaleNote ratio1_3_7 = {21845, 1431655765, 7};
static const ScaleNote ratio4_1 = {262144, 0, 1};
static const ScaleNote ratio6_1_6 = {393216, 0, 6};
static const ScaleNote ratio40_3 = {873813, 1431655765, 3};
static const ScaleNote ratio4_1_7 = {262144, 0, 7};
static const ScaleNote ratio6_5_13 = {78643, 858993459, 13};
static const ScaleNote ratio11_1 = {720896, 0, 1};
static const ScaleNote ratio1_1_14 = {65536, 0, 14};
static const ScaleNote ratio8_1 = {524288, 0, 1};
static const ScaleNote ratio1_4_7 = {16384, 0, 7};
static const ScaleNote ratio15_32 = {30720, 0, 32};
static const ScaleNote ratio5_2_2 = {163840, 0, 2};
static const ScaleNote ratio3_4_6 = {49152, 0, 6};
static const ScaleNote ratio1_1 = {65536, 0, 1};
static const ScaleNote ratio7_80 = {5734, 1717986918, 80};
static const ScaleNote ratio5_2_7 = {163840, 0, 7};
static const ScaleNote ratio18_5 = {235929, 2576980377, 5};
static const ScaleNote ratio1_12 = {5461, 1431655765, 12};
static const ScaleNote ratio4_5_15 = {52428, 3435973836, 15};
static const ScaleNote ratio25_288 = {5688, 3817748707, 288};
static const ScaleNote ratio9_8_8 = {73728, 0, 8};
static const ScaleNote ratio3_7 = {28086, 3681400539, 7};
static const ScaleNote ratio7_48 = {9557, 1431655765, 48};
static const ScaleNote ratio7_12 = {38229, 1431655765, 12};
static const ScaleNote ratio3_4_1 = {49152, 0, 1};
static const ScaleNote ratio5_3_1 = {109226, 2863311530, 1};
static const ScaleNote ratio3_2_6 = {98304, 0, 6};
static const ScaleNote ratio256_13 = {1290555, 330382100, 13};
static const ScaleNote ratio7_24 = {19114, 2863311530, 24};
static const ScaleNote ratio1_1_15 = {65536, 0, 15};
static const ScaleNote ratio15_1 = {983040, 0, 1};
static const ScaleNote ratio4_3_15 = {87381, 1431655765, 15};
static const ScaleNote ratio5_4_16 = {81920, 0, 16};
static const ScaleNote ratio64_7 = {599186, 1227133513, 7};
static const ScaleNote ratio15_7 = {140434, 1227133513, 7};
static const ScaleNote ratio6_1_1 = {393216, 0, 1};
static const ScaleNote ratio13_16 = {53248, 0, 16};
static const ScaleNote ratio3_2_14 = {98304, 0, 14};
static const ScaleNote ratio5_18 = {18204, 1908874353, 18};
static const ScaleNote ratio1_3 = {21845, 1431655765, 3};
static const ScaleNote ratio6_5_3 = {78643, 858993459, 3};
static const ScaleNote ratio7_32 = {14336, 0, 32};
static const ScaleNote ratio28_1 = {1835008, 0, 1};
static const ScaleNote ratio3_1_16 = {196608, 0, 16};
static const ScaleNote ratio7_4_1 = {114688, 0, 1};
static const ScaleNote ratio9_8_15 = {73728, 0, 15};
static const ScaleNote ratio7_4_13 = {114688, 0, 13};
static const ScaleNote ratio12_1_16 = {786432, 0, 16};
static const ScaleNote ratio15_128 = {7680, 0, 128};
static const ScaleNote ratio15_56 = {17554, 1227133513, 56};
static const ScaleNote ratio9_100 = {5898, 1030792151, 100};
static const ScaleNote ratio112_5 = {1468006, 1717986918, 5};
static const ScaleNote ratio7_5_7 = {91750, 1717986918, 7};
static const ScaleNote ratio16_15 = {69905, 286331153, 15};
static const ScaleNote ratio12_1_8 = {786432, 0, 8};
static const ScaleNote ratio15_28 = {35108, 2454267026, 28};
static const ScaleNote ratio3_1_4 = {196608, 0, 4};
static const ScaleNote ratio9_5 = {117964, 3435973836, 5};
static const ScaleNote ratio96_7 = {898779, 1840700269, 7};
static const ScaleNote ratio10_1_1 = {655360, 0, 1};
static const ScaleNote ratio5_3_14 = {109226, 2863311530, 14};
static const ScaleNote ratio4_3_5 = {87381, 1431655765, 5};
static const ScaleNote ratio9_8_10 = {73728, 0, 10};
static const ScaleNote ratio8_3_16 = {174762, 2863311530, 16};
static const ScaleNote ratio1_1_11 = {65536, 0, 11};
static const ScaleNote ratio15_448 = {2194, 1227133513, 448};
static const ScaleNote ratio5_2_10 = {163840, 0, 10};
static const ScaleNote ratio5_3_11 = {109226, 2863311530, 11};
static const ScaleNote ratio11_16 = {45056, 0, 16};
static const ScaleNote ratio8_1_4 = {524288, 0, 4};
static const ScaleNote ratio7_5_14 = {91750, 1717986918, 14};
static const ScaleNote ratio7_5_2 = {91750, 1717986918, 2};
static const ScaleNote ratio5_128 = {2560, 0, 128};
static const ScaleNote ratio128_3 = {2796202, 2863311530, 3};
static const ScaleNote ratio1_30 = {2184, 2290649224, 30};
static const ScaleNote ratio9_8_2 = {73728, 0, 2};
static const ScaleNote ratio5_2_5 = {163840, 0, 5};
static const ScaleNote ratio5_3_15 = {109226, 2863311530, 15};
static const ScaleNote ratio5_4_5 = {81920, 0, 5};
static const ScaleNote ratio32_1 = {2097152, 0, 1};
static const ScaleNote ratio1_1_5 = {65536, 0, 5};
static const ScaleNote ratio6_5_11 = {78643, 858993459, 11};
static const ScaleNote ratio80_9 = {582542, 954437177, 9};
static const ScaleNote ratio3_2_12 = {98304, 0, 12};
static const ScaleNote ratio9_80 = {7372, 3435973836, 80};
static const ScaleNote ratio32_7 = {299593, 613566756, 7};
static const ScaleNote ratio11_64 = {11264, 0, 64};
static const ScaleNote ratio12_1_1 = {786432, 0, 1};
static const ScaleNote ratio5_1_8 = {327680, 0, 8};
static const ScaleNote ratio9_8_11 = {73728, 0, 11};
static const ScaleNote ratio3_4_5 = {49152, 0, 5};
static const ScaleNote ratio5_9 = {36408, 3817748707, 9};
static const ScaleNote ratio4_3_1 = {87381, 1431655765, 1};
static const ScaleNote ratio6_5_5 = {78643, 858993459, 5};
static const ScaleNote ratio7_4_8 = {114688, 0, 8};
static const ScaleNote ratio7_4_9 = {114688, 0, 9};
static const ScaleNote ratio9_8_5 = {73728, 0, 5};
static const ScaleNote ratio320_9 = {2330168, 3817748708, 9};
static const ScaleNote ratio4_1_2 = {262144, 0, 2};
static const ScaleNote ratio8_1_8 = {524288, 0, 8};
static const ScaleNote ratio7_4 = {114688, 0, 4};
static const ScaleNote ratio4_5_3 = {52428, 3435973836, 3};
static const ScaleNote ratio3_2_1 = {98304, 0, 1};
static const ScaleNote ratio2_5 = {26214, 1717986918, 5};
static const ScaleNote ratio11_96 = {7509, 1431655765, 96};
static const ScaleNote ratio7_5_9 = {91750, 1717986918, 9};
static const ScaleNote ratio7_1 = {458752, 0, 1};
static const ScaleNote ratio7_4_3 = {114688, 0, 3};
static const ScaleNote ratio48_7 = {449389, 3067833782, 7};
static const ScaleNote ratio2_1_1 = {131072, 0, 1};
static const ScaleNote ratio9_8_6 = {73728, 0, 6};
static const ScaleNote ratio9_8_14 = {73728, 0, 14};
static const ScaleNote ratio7_4_10 = {114688, 0, 10};
static const ScaleNote ratio56_5 = {734003, 858993459, 5};
static const ScaleNote ratio30_7 = {280868, 2454267026, 7};
static const ScaleNote ratio1_8_16 = {8192, 0, 16};
static const ScaleNote ratio4_1_6 = {262144, 0, 6};
static const ScaleNote ratio4_5_6 = {52428, 3435973836, 6};
static const ScaleNote ratio7_4_2 = {114688, 0, 2};
static const ScaleNote ratio2_1_5 = {131072, 0, 5};
static const ScaleNote ratio15_256 = {3840, 0, 256};
static const ScaleNote ratio80_3 = {1747626, 2863311531, 3};
static const ScaleNote ratio5_4_1 = {81920, 0, 1};
static const ScaleNote ratio7_40 = {11468, 3435973836, 40};
static const ScaleNote ratio1_1_10 = {65536, 0, 10};
static const ScaleNote ratio40_7 = {374491, 1840700269, 7};
static const ScaleNote ratio5_2_13 = {163840, 0, 13};
static const ScaleNote ratio7_64 = {7168, 0, 64};
static const ScaleNote ratio40_1 = {2621440, 0, 1};
static const ScaleNote ratio3_56 = {3510, 3681400539, 56};
static const ScaleNote ratio1_4_15 = {16384, 0, 15};
static const ScaleNote ratio3_2_7 = {98304, 0, 7};
static const ScaleNote ratio3_2_15 = {98304, 0, 15};
static const ScaleNote ratio6_7 = {56173, 3067833782, 7};
static const ScaleNote ratio3_112 = {1755, 1840700269, 112};
static const ScaleNote ratio1_32 = {2048, 0, 32};
static const ScaleNote ratio1_128 = {512, 0, 128};
static const ScaleNote ratio5_2_11 = {163840, 0, 11};
static const ScaleNote ratio15_4 = {245760, 0, 4};
static const ScaleNote ratio6_5 = {78643, 858993459, 5};
static const ScaleNote ratio64_9 = {466033, 3340530119, 9};
static const ScaleNote ratio3_4_8 = {49152, 0, 8};
static const ScaleNote ratio3_1_8 = {196608, 0, 8};
static const ScaleNote ratio2_1_8 = {131072, 0, 8};
static const ScaleNote ratio7_5_6 = {91750, 1717986918, 6};
static const ScaleNote ratio144_25 = {377487, 1546188226, 25};
static const ScaleNote ratio5_2 = {163840, 0, 2};
static const ScaleNote ratio5_3_9 = {109226, 2863311530, 9};
static const ScaleNote ratio1_3_3 = {21845, 1431655765, 3};
static const ScaleNote ratio1_96 = {682, 2863311530, 96};
static const ScaleNote ratio7_10 = {45875, 858993459, 10};
static const ScaleNote ratio288_25 = {754974, 3092376453, 25};
static const ScaleNote ratio5_4_4 = {81920, 0, 4};
static const ScaleNote ratio1_1_9 = {65536, 0, 9};
static const ScaleNote ratio1_7 = {9362, 1227133513, 7};
static const ScaleNote ratio2_3_16 = {43690, 2863311530, 16};
static const ScaleNote ratio4_3_2 = {87381, 1431655765, 2};
static const ScaleNote ratio1_56 = {1170, 1227133513, 56};
static const ScaleNote ratio1_20 = {3276, 3435973836, 20};
static const ScaleNote ratio2_3_9 = {43690, 2863311530, 9};
static const ScaleNote ratio6_1_3 = {393216, 0, 3};
static const ScaleNote ratio6_5_7 = {78643, 858993459, 7};
static const ScaleNote ratio5_4_6 = {81920, 0, 6};
static const ScaleNote ratio5_4_14 = {81920, 0, 14};
static const ScaleNote ratio7_4_15 = {114688, 0, 15};
static const ScaleNote ratio1_1_1 = {65536, 0, 1};
static const ScaleNote ratio3_2_8 = {98304, 0, 8};
static const ScaleNote ratio10_1_2 = {655360, 0, 2};
static const ScaleNote ratio2_3_11 = {43690, 2863311530, 11};
static const ScaleNote ratio1_4_2 = {16384, 0, 2};
static const ScaleNote ratio6_1_8 = {393216, 0, 8};
static const ScaleNote ratio4_1_4 = {262144, 0, 4};
static const ScaleNote ratio8_1_2 = {524288, 0, 2};
static const ScaleNote ratio1_3_10 = {21845, 1431655765, 10};
static const ScaleNote ratio5_4_12 = {81920, 0, 12};
static const ScaleNote ratio5_7 = {46811, 1840700269, 7};
static const ScaleNote ratio9_50 = {11796, 2061584302, 50};
static const ScaleNote ratio16_1 = {1048576, 0, 1};
static const ScaleNote ratio3_5 = {39321, 2576980377, 5};
static const ScaleNote ratio24_5 = {314572, 3435973836, 5};
static const ScaleNote ratio128_15 = {559240, 2290649224, 15};
static const ScaleNote ratio9_8_16 = {73728, 0, 16};
static const ScaleNote ratio8_1_3 = {524288, 0, 3};
static const ScaleNote ratio1_3_13 = {21845, 1431655765, 13};
static const ScaleNote ratio3_8 = {24576, 0, 8};
static const ScaleNote ratio160_9 = {1165084, 1908874354, 9};
static const ScaleNote ratio7_5_12 = {91750, 1717986918, 12};
static const ScaleNote ratio5_64 = {5120, 0, 64};
static const ScaleNote ratio2_3_1 = {43690, 2863311530, 1};
static const ScaleNote ratio1_4_10 = {16384, 0, 10};
static const ScaleNote ratio5_2_12 = {163840, 0, 12};
static const ScaleNote ratio6_5_16 = {78643, 858993459, 16};
static const ScaleNote ratio1_4_9 = {16384, 0, 9};
static const ScaleNote ratio4_9 = {29127, 477218588, 9};
static const ScaleNote ratio11_256 = {2816, 0, 256};
static const ScaleNote ratio1_4_4 = {16384, 0, 4};
static const ScaleNote ratio1_9 = {7281, 3340530119, 9};
static const ScaleNote ratio3_1_2 = {196608, 0, 2};
static const ScaleNote ratio8_1_16 = {524288, 0, 16};
static const ScaleNote ratio112_3 = {2446677, 1431655766, 3};
static const ScaleNote ratio3_4_3 = {49152, 0, 3};
static const ScaleNote ratio9_4 = {147456, 0, 4};
static const ScaleNote ratio1_2_16 = {32768, 0, 16};
static const ScaleNote ratio64_11 = {381300, 1561806289, 11};
static const ScaleNote ratio1_28 = {2340, 2454267026, 28};
static const ScaleNote ratio5_6 = {54613, 1431655765, 6};
static const ScaleNote ratio5_512 = {640, 0, 512};
static const ScaleNote ratio4_5_14 = {52428, 3435973836, 14};
static const ScaleNote ratio15_112 = {8777, 613566756, 112};
static const ScaleNote ratio4_3_3 = {87381, 1431655765, 3};
static const ScaleNote ratio5_56 = {5851, 1840700269, 56};
static const ScaleNote ratio5_16 = {20480, 0, 16};
static const ScaleNote ratio5_1_6 = {327680, 0, 6};
static const ScaleNote ratio8_5 = {104857, 2576980377, 5};
static const ScaleNote ratio5_3_13 = {109226, 2863311530, 13};
static const ScaleNote ratio96_5 = {1258291, 858993459, 5};
static const ScaleNote ratio6_5_2 = {78643, 858993459, 2};
static const ScaleNote ratio2_1_3 = {131072, 0, 3};
static const ScaleNote ratio64_5 = {838860, 3435973837, 5};
static const ScaleNote ratio5_3_10 = {109226, 2863311530, 10};
static const ScaleNote ratio128_5 = {1677721, 2576980378, 5};
static const ScaleNote ratio5_4_13 = {81920, 0, 13};
static const ScaleNote ratio4_5 = {52428, 3435973836, 5};
static const ScaleNote ratio36_25 = {94371, 3607772528, 25};
static const ScaleNote ratio1_1_2 = {65536, 0, 2};
static const ScaleNote ratio5_12 = {27306, 2863311530, 12};
static const ScaleNote ratio1_36 = {1820, 1908874353, 36};
static const ScaleNote ratio12_1_3 = {786432, 0, 3};
static const ScaleNote ratio9_8_1 = {73728, 0, 1};
static const ScaleNote ratio3_2_5 = {98304, 0, 5};
static const ScaleNote ratio5_1_4 = {327680, 0, 4};
static const ScaleNote ratio1_192 = {341, 1431655765, 192};
static const ScaleNote ratio5_3_6 = {109226, 2863311530, 6};
static const ScaleNote ratio3_4_10 = {49152, 0, 10};
static const ScaleNote ratio200_9 = {1456355, 2386092942, 9};
static const ScaleNote ratio4_3_14 = {87381, 1431655765, 14};
static const ScaleNote ratio9_256 = {2304, 0, 256};
static const ScaleNote ratio20_7 = {187245, 3067833782, 7};
static const ScaleNote ratio24_1 = {1572864, 0, 1};
static const ScaleNote ratio104_3 = {2271914, 2863311530, 3};
static const ScaleNote ratio2_3_14 = {43690, 2863311530, 14};
static const ScaleNote ratio1_2 = {32768, 0, 2};
static const ScaleNote ratio7_5 = {91750, 1717986918, 5};
static const ScaleNote ratio7_2 = {229376, 0, 2};
static const ScaleNote ratio4_15 = {17476, 1145324612, 15};
static const ScaleNote ratio4_5_2 = {52428, 3435973836, 2};
static const ScaleNote ratio3_2_9 = {98304, 0, 9};
static const ScaleNote ratio5_3_2 = {109226, 2863311530, 2};
static const ScaleNote ratio6_5_6 = {78643, 858993459, 6};
static const ScaleNote ratio16_5 = {209715, 858993459, 5};
static const ScaleNote ratio1_3_11 = {21845, 1431655765, 11};
static const ScaleNote ratio5_8 = {40960, 0, 8};
static const ScaleNote ratio6_5_8 = {78643, 858993459, 8};
static const ScaleNote ratio128_9 = {932067, 2386092942, 9};
static const ScaleNote ratio5_192 = {1706, 2863311530, 192};
static const ScaleNote ratio11_24 = {30037, 1431655765, 24};
static const ScaleNote ratio3_2_11 = {98304, 0, 11};
static const ScaleNote ratio5_2_3 = {163840, 0, 3};
static const ScaleNote ratio1_6_16 = {10922, 2863311530, 16};
static const ScaleNote ratio3_4_9 = {49152, 0, 9};
static const ScaleNote ratio20_3 = {436906, 2863311530, 3};
static const ScaleNote ratio9_1 = {589824, 0, 1};
static const ScaleNote ratio10_1_3 = {655360, 0, 3};
static const ScaleNote ratio4_3_6 = {87381, 1431655765, 6};
static const ScaleNote ratio5_36 = {9102, 954437176, 36};
static const ScaleNote ratio4_5_11 = {52428, 3435973836, 11};
static const ScaleNote ratio5_1_5 = {327680, 0, 5};
static const ScaleNote ratio1_3_1 = {21845, 1431655765, 1};
static const ScaleNote ratio50_9 = {364088, 3817748707, 9};
static const ScaleNote ratio1_3_12 = {21845, 1431655765, 12};
static const ScaleNote ratio20_1 = {1310720, 0, 1};
static const ScaleNote ratio5_256 = {1280, 0, 256};
static const ScaleNote ratio9_8_13 = {73728, 0, 13};
static const ScaleNote ratio6_5_10 = {78643, 858993459, 10};
static const ScaleNote ratio9_40 = {14745, 2576980377, 40};
static const ScaleNote ratio1_4_11 = {16384, 0, 11};
static const ScaleNote ratio64_3 = {1398101, 1431655765, 3};
static const ScaleNote ratio13_256 = {3328, 0, 256};
static const ScaleNote ratio9_8_3 = {73728, 0, 3};
static const ScaleNote ratio5_4 = {81920, 0, 4};
static const ScaleNote ratio4_7 = {37449, 613566756, 7};
static const ScaleNote ratio3_1_3 = {196608, 0, 3};
static const ScaleNote ratio7_4_7 = {114688, 0, 7};
static const ScaleNote ratio2_7 = {18724, 2454267026, 7};
static const ScaleNote ratio5_4_10 = {81920, 0, 10};
static const ScaleNote ratio1_3_9 = {21845, 1431655765, 9};
static const ScaleNote ratio1_3_8 = {21845, 1431655765, 8};
static const ScaleNote ratio15_16 = {61440, 0, 16};
static const ScaleNote ratio15_224 = {4388, 2454267026, 224};
static const ScaleNote ratio100_9 = {728177, 3340530119, 9};
static const ScaleNote ratio30_1 = {1966080, 0, 1};
static const ScaleNote ratio32_3 = {699050, 2863311530, 3};
static const ScaleNote ratio2_3_7 = {43690, 2863311530, 7};
static const ScaleNote ratio1_3_16 = {21845, 1431655765, 16};
static const ScaleNote ratio5_3 = {109226, 2863311530, 3};
static const ScaleNote ratio10_1_6 = {655360, 0, 6};
static const ScaleNote ratio1_1_12 = {65536, 0, 12};
static const ScaleNote ratio4_5_13 = {52428, 3435973836, 13};
static const ScaleNote ratio1_14 = {4681, 613566756, 14};
static const ScaleNote ratio15_64 = {15360, 0, 64};
static const ScaleNote ratio5_2_8 = {163840, 0, 8};
static const ScaleNote ratio5_4_3 = {81920, 0, 3};
static const ScaleNote ratio15_2 = {491520, 0, 2};
static const ScaleNote ratio3_14 = {14043, 1840700269, 14};
static const ScaleNote ratio4_3_10 = {87381, 1431655765, 10};
static const ScaleNote ratio4_5_4 = {52428, 3435973836, 4};
static const ScaleNote ratio5_1_2 = {327680, 0, 2};
static const ScaleNote ratio32_15 = {139810, 572662306, 15};
static const ScaleNote ratio25_72 = {22755, 2386092942, 72};
static const ScaleNote ratio10_9 = {72817, 3340530119, 9};
static const ScaleNote ratio4_3_16 = {87381, 1431655765, 16};
static const ScaleNote ratio8_7 = {74898, 1227133513, 7};
static const ScaleNote ratio2_3_6 = {43690, 2863311530, 6};
static const ScaleNote ratio5_3_4 = {109226, 2863311530, 4};
static const ScaleNote ratio1_3_2 = {21845, 1431655765, 2};
static const ScaleNote ratio7_5_5 = {91750, 1717986918, 5};
static const ScaleNote ratio1_16 = {4096, 0, 16};
static const ScaleNote ratio7_4_6 = {114688, 0, 6};
static const ScaleNote ratio1_4_14 = {16384, 0, 14};
static const ScaleNote ratio5_48 = {6826, 2863311530, 48};
static const ScaleNote ratio240_7 = {2246948, 2454267026, 7};
static const ScaleNote ratio7_5_8 = {91750, 1717986918, 8};
static const ScaleNote ratio60_7 = {561737, 613566756, 7};
static const ScaleNote ratio4_5_16 = {52428, 3435973836, 16};
static const ScaleNote ratio1_11 = {5957, 3514064151, 11};
static const ScaleNote ratio6_1_7 = {393216, 0, 7};
static const ScaleNote ratio576_25 = {1509949, 1889785610, 25};
static const ScaleNote ratio5_4_8 = {81920, 0, 8};
static const ScaleNote ratio1_3_15 = {21845, 1431655765, 15};
static const ScaleNote ratio6_1_16 = {393216, 0, 16};
static const ScaleNote ratio3_28 = {7021, 3067833782, 28};
static const ScaleNote ratio5_96 = {3413, 1431655765, 96};
static const ScaleNote ratio3_160 = {1228, 3435973836, 160};
static const ScaleNote ratio6_5_4 = {78643, 858993459, 4};
static const ScaleNote ratio15_8 = {122880, 0, 8};
static const ScaleNote ratio1_1_8 = {65536, 0, 8};
static const ScaleNote ratio10_1_4 = {655360, 0, 4};
static const ScaleNote ratio1_4_6 = {16384, 0, 6};
static const ScaleNote ratio4_3 = {87381, 1431655765, 3};
static const ScaleNote ratio3_1_1 = {196608, 0, 1};
static const ScaleNote ratio7_5_15 = {91750, 1717986918, 15};
static const ScaleNote ratio4_5_10 = {52428, 3435973836, 10};
static const ScaleNote ratio144_5 = {1887436, 3435973837, 5};
static const ScaleNote ratio5_3_16 = {109226, 2863311530, 16};
static const ScaleNote ratio24_7 = {224694, 3681400539, 7};
static const ScaleNote ratio16_9 = {116508, 1908874353, 9};
static const ScaleNote ratio2_3_4 = {43690, 2863311530, 4};
static const ScaleNote ratio9_8_4 = {73728, 0, 4};
static const ScaleNote ratio8_1_7 = {524288, 0, 7};
static const ScaleNote ratio12_1_7 = {786432, 0, 7};
static const ScaleNote ratio5_1_7 = {327680, 0, 7};
static const ScaleNote ratio7_192 = {2389, 1431655765, 192};
static const ScaleNote ratio7_5_16 = {91750, 1717986918, 16};
static const ScaleNote ratio2_1_7 = {131072, 0, 7};
static const ScaleNote ratio2_3_13 = {43690, 2863311530, 13};
static const ScaleNote ratio5_2_9 = {163840, 0, 9};
static const ScaleNote ratio3_4_2 = {49152, 0, 2};
static const ScaleNote ratio2_3_12 = {43690, 2863311530, 12};
static const ScaleNote ratio26_3 = {567978, 2863311530, 3};
static const ScaleNote ratio6_5_14 = {78643, 858993459, 14};
static const ScaleNote ratio36_1 = {2359296, 0, 1};
static const ScaleNote ratio1_16_16 = {4096, 0, 16};
static const ScaleNote ratio7_4_12 = {114688, 0, 12};
static const ScaleNote ratio7_5_4 = {91750, 1717986918, 4};
static const ScaleNote ratio2_3_10 = {43690, 2863311530, 10};
static const ScaleNote ratio3_1_7 = {196608, 0, 7};
static const ScaleNote ratio5_32 = {10240, 0, 32};
static const ScaleNote ratio9_25 = {23592, 4123168604, 25};
static const ScaleNote ratio1_320 = {204, 3435973836, 320};
static const ScaleNote ratio32_5 = {419430, 1717986918, 5};
static const ScaleNote ratio22_3 = {480597, 1431655765, 3};
static const ScaleNote ratio120_7 = {1123474, 1227133513, 7};
static const ScaleNote ratio5_112 = {2925, 3067833782, 112};
static const ScaleNote ratio1_4_13 = {16384, 0, 13};
static const ScaleNote ratio5_2_16 = {163840, 0, 16};
static const ScaleNote ratio28_3 = {611669, 1431655765, 3};
static const ScaleNote ratio3_512 = {384, 0, 512};
static const ScaleNote ratio9_10 = {58982, 1717986918, 10};
static const ScaleNote ratio3_2_10 = {98304, 0, 10};
static const ScaleNote ratio9_8_12 = {73728, 0, 12};
static const ScaleNote ratio18_1 = {1179648, 0, 1};
static const ScaleNote ratio15_14 = {70217, 613566756, 14};
static const ScaleNote ratio4_5_1 = {52428, 3435973836, 1};
static const ScaleNote ratio8_9 = {58254, 954437176, 9};
static const ScaleNote ratio1_10 = {6553, 2576980377, 10};
static const ScaleNote ratio7_512 = {896, 0, 512};
static const ScaleNote ratio9_32 = {18432, 0, 32};
static const ScaleNote ratio3_8_16 = {24576, 0, 16};
static const ScaleNote ratio1_256 = {256, 0, 256};
static const ScaleNote ratio9_200 = {2949, 515396075, 200};
static const ScaleNote ratio12_7 = {112347, 1840700269, 7};
static const ScaleNote ratio1_24 = {2730, 2863311530, 24};
static const ScaleNote ratio88_3 = {1922389, 1431655765, 3};
static const ScaleNote ratio5_2_1 = {163840, 0, 1};
static const ScaleNote ratio3_128 = {1536, 0, 128};
static const ScaleNote ratio7_5_10 = {91750, 1717986918, 10};
static const ScaleNote ratio3_16_16 = {12288, 0, 16};
static const ScaleNote ratio5_3_12 = {109226, 2863311530, 12};
static const ScaleNote ratio9_20 = {29491, 858993459, 20};
static const ScaleNote ratio1_1_13 = {65536, 0, 13};
static const ScaleNote ratio14_5 = {183500, 3435973836, 5};
static const ScaleNote ratio9_8 = {73728, 0, 8};
static const ScaleNote ratio8_11 = {47662, 2342709434, 11};
static const ScaleNote ratio7_3 = {152917, 1431655765, 3};
static const ScaleNote ratio12_1_6 = {786432, 0, 6};
static const ScaleNote ratio2_1 = {131072, 0, 1};
static const ScaleNote ratio12_1_5 = {786432, 0, 5};
static const ScaleNote ratio5_28 = {11702, 3681400539, 28};
static const ScaleNote ratio25_18 = {91022, 954437176, 18};
static const ScaleNote ratio2_15 = {8738, 572662306, 15};
static const ScaleNote ratio8_3 = {174762, 2863311530, 3};
static const ScaleNote ratio5_24 = {13653, 1431655765, 24};
static const ScaleNote ratio192_5 = {2516582, 1717986918, 5};
static const ScaleNote ratio8_1_1 = {524288, 0, 1};
static const ScaleNote ratio4_3_4 = {87381, 1431655765, 4};
static const ScaleNote ratio3_20 = {9830, 1717986918, 20};
static const ScaleNote ratio9_128 = {4608, 0, 128};
static const ScaleNote ratio1_3_5 = {21845, 1431655765, 5};
static const ScaleNote ratio7_96 = {4778, 2863311530, 96};
static const ScaleNote ratio3_2_13 = {98304, 0, 13};
static const ScaleNote ratio13_1 = {851968, 0, 1};
static const ScaleNote ratio7_4_4 = {114688, 0, 4};
static const ScaleNote ratio3_16 = {12288, 0, 16};
static const ScaleNote ratio12_1_2 = {786432, 0, 2};
static const ScaleNote ratio7_6 = {76458, 2863311530, 6};
static const ScaleNote ratio1_40 = {1638, 1717986918, 40};
static const ScaleNote ratio4_5_8 = {52428, 3435973836, 8};
static const ScaleNote ratio7_4_14 = {114688, 0, 14};
static const ScaleNote ratio3_2_16 = {98304, 0, 16};
static const ScaleNote ratio6_1_5 = {393216, 0, 5};
static const ScaleNote ratio3_40 = {4915, 858993459, 40};
static const ScaleNote ratio3_1_6 = {196608, 0, 6};
static const ScaleNote ratio5_2_6 = {163840, 0, 6};
static const ScaleNote ratio2_9 = {14563, 2386092942, 9};
static const ScaleNote ratio7_256 = {1792, 0, 256};
static const ScaleNote ratio4_3_7 = {87381, 1431655765, 7};
static const ScaleNote ratio4_5_7 = {52428, 3435973836, 7};
static const ScaleNote ratio3_4_15 = {49152, 0, 15};
static const ScaleNote ratio3_64 = {3072, 0, 64};
static const ScaleNote ratio3_80 = {2457, 2576980377, 80};
static const ScaleNote ratio25_36 = {45511, 477218588, 36};
static const ScaleNote ratio2_1_6 = {131072, 0, 6};
static const ScaleNote ratio13_96 = {8874, 2863311530, 96};
static const ScaleNote ratio4_3_8 = {87381, 1431655765, 8};
static const ScaleNote ratio10_1_7 = {655360, 0, 7};
static const ScaleNote ratio5_4_11 = {81920, 0, 11};
static const ScaleNote ratio10_1_5 = {655360, 0, 5};
static const ScaleNote ratio3_2_4 = {98304, 0, 4};
static const ScaleNote ratio5_1 = {327680, 0, 1};
static const ScaleNote ratio7_4_11 = {114688, 0, 11};
static const ScaleNote ratio5_72 = {4551, 477218588, 72};
static const ScaleNote ratio9_320 = {1843, 858993459, 320};
static const ScaleNote ratio10_1 = {655360, 0, 1};
static const ScaleNote ratio8_15 = {34952, 2290649224, 15};
static const ScaleNote ratio4_3_11 = {87381, 1431655765, 11};
static const ScaleNote ratio80_7 = {748982, 3681400539, 7};
static const ScaleNote ratio6_5_12 = {78643, 858993459, 12};
static const ScaleNote ratio1_8 = {8192, 0, 8};
static const ScaleNote ratio1_4_3 = {16384, 0, 3};
static const ScaleNote ratio9_16 = {36864, 0, 16};
static const ScaleNote ratio28_5 = {367001, 2576980377, 5};
static const ScaleNote ratio16_3_16 = {349525, 1431655765, 16};
static const ScaleNote ratio7_160 = {2867, 858993459, 160};
static const ScaleNote ratio1_12_16 = {5461, 1431655765, 16};
static const ScaleNote ratio5_4_15 = {81920, 0, 15};
static const ScaleNote ratio1_3_4 = {21845, 1431655765, 4};
static const ScaleNote ratio3_4_12 = {49152, 0, 12};
static const ScaleNote ratio6_1 = {393216, 0, 1};
static const ScaleNote ratio13_24 = {35498, 2863311530, 24};
static const ScaleNote ratio11_6 = {120149, 1431655765, 6};
static const ScaleNote ratio6_5_15 = {78643, 858993459, 15};
static const ScaleNote ratio9_8_7 = {73728, 0, 7};
static const ScaleNote ratio1_1_6 = {65536, 0, 6};
static const ScaleNote ratio256_15 = {1118481, 286331153, 15};
static const ScaleNote ratio4_5_12 = {52428, 3435973836, 12};
static const ScaleNote ratio4_1_5 = {262144, 0, 5};
static const ScaleNote ratio72_5 = {943718, 1717986918, 5};
static const ScaleNote ratio9_2 = {294912, 0, 2};
static const ScaleNote ratio14_1 = {917504, 0, 1};
static const ScaleNote ratio3_4_11 = {49152, 0, 11};
static const ScaleNote ratio15_512 = {1920, 0, 512};
static const ScaleNote ratio2_3_8 = {43690, 2863311530, 8};
static const ScaleNote ratio3_10 = {19660, 3435973836, 10};
static const ScaleNote ratio2_3 = {43690, 2863311530, 3};
static const ScaleNote ratio11_384 = {1877, 1431655765, 384};
static const ScaleNote ratio32_9 = {233016, 3817748707, 9};
static const ScaleNote ratio9_64 = {9216, 0, 64};
static const ScaleNote ratio2_3_5 = {43690, 2863311530, 5};
static const ScaleNote ratio10_3 = {218453, 1431655765, 3};
static const ScaleNote ratio64_15 = {279620, 1145324612, 15};
static const ScaleNote ratio2_1_4 = {131072, 0, 4};
static const ScaleNote ratio1_4_1 = {16384, 0, 1};
static const ScaleNote ratio512_15 = {2236962, 572662306, 15};
static const ScaleNote ratio13_384 = {2218, 2863311530, 384};
static const ScaleNote ratio25_9 = {182044, 1908874353, 9};
static const ScaleNote ratio256_7 = {2396745, 613566756, 7};
static const ScaleNote ratio16_7 = {149796, 2454267026, 7};
static const ScaleNote ratio128_7 = {1198372, 2454267026, 7};
static const ScaleNote ratio1_18 = {3640, 3817748707, 18};
static const ScaleNote ratio7_5_1 = {91750, 1717986918, 1};
static const ScaleNote ratio9_8_9 = {73728, 0, 9};
static const ScaleNote ratio3_256 = {768, 0, 256};
static const ScaleNote ratio5_4_7 = {81920, 0, 7};
static const ScaleNote ratio36_5 = {471859, 858993459, 5};
static const ScaleNote ratio4_1_16 = {262144, 0, 16};
static const ScaleNote ratio3_4_7 = {49152, 0, 7};
static const ScaleNote ratio8_1_6 = {524288, 0, 6};
static const ScaleNote ratio1_4_16 = {16384, 0, 16};
static const ScaleNote ratio1_160 = {409, 2576980377, 160};
static const ScaleNote ratio256_9 = {1864135, 477218588, 9};
static const ScaleNote ratio1_1_3 = {65536, 0, 3};
static const ScaleNote ratio5_4_9 = {81920, 0, 9};
static const ScaleNote ratio1_4 = {16384, 0, 4};
static const ScaleNote ratio3_1_5 = {196608, 0, 5};
static const ScaleNote ratio5_1_1 = {327680, 0, 1};
static const ScaleNote ratio5_3_7 = {109226, 2863311530, 7};
static const ScaleNote ratio5_3_8 = {109226, 2863311530, 8};
static const ScaleNote ratio1_6 = {10922, 2863311530, 6};
static const ScaleNote ratio16_13 = {80659, 2973438897, 13};
static const ScaleNote ratio7_4_16 = {114688, 0, 16};
static const ScaleNote ratio3_1 = {196608, 0, 1};
static const ScaleNote ratio5_3_5 = {109226, 2863311530, 5};
static const ScaleNote ratio7_4_5 = {114688, 0, 5};
static const ScaleNote ratio7_5_13 = {91750, 1717986918, 13};
static const ScaleNote ratio25_144 = {11377, 3340530119, 144};
static const ScaleNote ratio192_7 = {1797558, 3681400539, 7};
static const ScaleNote ratio5_1_3 = {327680, 0, 3};
static const ScaleNote ratio3_32 = {6144, 0, 32};
static const ScaleNote ratio5_2_4 = {163840, 0, 4};
static const ScaleNote ratio1_1_7 = {65536, 0, 7};
static const ScaleNote ratio1_1_16 = {65536, 0, 16};
static const ScaleNote ratio5_2_15 = {163840, 0, 15};
static const ScaleNote ratio13_6 = {141994, 2863311530, 6};
static const ScaleNote ratio6_5_9 = {78643, 858993459, 9};
static const ScaleNote ratio1_64 = {1024, 0, 64};
static const ScaleNote ratio4_3_13 = {87381, 1431655765, 13};
static const ScaleNote ratio20_9 = {145635, 2386092942, 9};
static const ScaleNote ratio3_2 = {98304, 0, 2};
static const ScaleNote ratio14_3 = {305834, 2863311530, 3};
static const ScaleNote ratio3_4_4 = {49152, 0, 4};
static const ScaleNote ratio2_3_15 = {43690, 2863311530, 15};
static const ScaleNote ratio7_128 = {3584, 0, 128};
static const ScaleNote ratio2_3_2 = {43690, 2863311530, 2};
static const ScaleNote ratio7_5_3 = {91750, 1717986918, 3};
static const ScaleNote ratio10_7 = {93622, 3681400539, 7};
static const ScaleNote ratio2_3_3 = {43690, 2863311530, 3};
static const ScaleNote ratio6_1_2 = {393216, 0, 2};
static const ScaleNote ratio3_4_14 = {49152, 0, 14};
static const ScaleNote ratio7_20 = {22937, 2576980377, 20};
static const ScaleNote ratio72_25 = {188743, 2920577761, 25};
static const ScaleNote ratio160_7 = {1497965, 3067833783, 7};
static const ScaleNote ratio4_5_9 = {52428, 3435973836, 9};
static const ScaleNote ratio56_3 = {1223338, 2863311531, 3};
static const ScaleNote ratio5_14 = {23405, 3067833782, 14};
static const ScaleNote ratio1_15 = {4369, 286331153, 15};
static const ScaleNote ratio1_5 = {13107, 858993459, 5};
static const ScaleNote ratio6_5_1 = {78643, 858993459, 1};
static const ScaleNote ratio3_4 = {49152, 0, 4};
static const ScaleNote ratio2_1_16 = {131072, 0, 16};
static const ScaleNote ratio5_3_3 = {109226, 2863311530, 3};
static const ScaleNote ratio8_1_5 = {524288, 0, 5};
static const ScaleNote ratio5_2_14 = {163840, 0, 14};
static const ScaleNote ratio12_1_4 = {786432, 0, 4};
static const ScaleNote ratio4_3_12 = {87381, 1431655765, 12};
static const ScaleNote ratio1_48 = {1365, 1431655765, 48};
static const ScaleNote ratio1_80 = {819, 858993459, 80};
static const ScaleNote ratio1_4_12 = {16384, 0, 12};
static const ScaleNote ratio1_4_5 = {16384, 0, 5};
static const ScaleNote ratio48_5 = {629145, 2576980377, 5};
static const ScaleNote ratio40_9 = {291271, 477218588, 9};
static const ScaleNote ratio4_1_3 = {262144, 0, 3};
static const ScaleNote ratio12_1 = {786432, 0, 1};
static const ScaleNote ratio11_8 = {90112, 0, 8};
static const ScaleNote ratio1_1_4 = {65536, 0, 4};
static const ScaleNote ratio1_3_6 = {21845, 1431655765, 6};
static const ScaleNote ratio10_1_8 = {655360, 0, 8};
static const ScaleNote ratio5_4_2 = {81920, 0, 2};
static const ScaleNote ratio1_4_8 = {16384, 0, 8};
static const ScaleNote ratio4_1_1 = {262144, 0, 1};
static const ScaleNote ratio3_2_3 = {98304, 0, 3};
static const ScaleNote ratio7_16 = {28672, 0, 16};



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

static const ScaleNote * const integerRatios2[128] = {&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, 
&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, 
&ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, 
&ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, 
&ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, 
&ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, 
&ratio5_2, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, 
&ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio7_2, &ratio7_2, &ratio7_2, &ratio7_2, &ratio7_2, 
&ratio7_2, &ratio7_2, &ratio7_2, &ratio7_2, &ratio7_2, &ratio7_2, &ratio7_2, &ratio7_2, &ratio7_2, &ratio7_2, &ratio7_2, &ratio7_2, 
&ratio7_2, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, 
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

static const ScaleNote * const integerRatios4[128] = {&ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, 
&ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_1, &ratio1_1, &ratio1_1, 
&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, 
&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, 
&ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, 
&ratio5_4, &ratio5_4, &ratio5_4, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, 
&ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, 
&ratio3_2, &ratio7_4, &ratio7_4, &ratio7_4, &ratio7_4, &ratio7_4, &ratio7_4, &ratio7_4, &ratio7_4, &ratio7_4, &ratio7_4, &ratio7_4, 
&ratio7_4, &ratio7_4, &ratio7_4, &ratio7_4, &ratio7_4, &ratio7_4, &ratio7_4, &ratio7_4, &ratio7_4, &ratio7_4, &ratio2_1, &ratio2_1, 
&ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, 
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



static const ScaleNote * const majpenta5primefullspan[128] = {&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, 
&ratio1_1, &ratio1_1, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, 
&ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, 
&ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, 
&ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, 
&ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio2_1, 
&ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, 
&ratio2_1, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, 
&ratio9_4, &ratio9_4, &ratio9_4, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, 
&ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, 
&ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1}; 

static const ScaleNote * const maj2min75primefullspan[128] = {&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, 
&ratio1_1, &ratio1_1, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, 
&ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, 
&ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, 
&ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, 
&ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio2_1, 
&ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, 
&ratio2_1, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, 
&ratio9_4, &ratio9_4, &ratio9_4, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, 
&ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio10_3, &ratio10_3, &ratio10_3, &ratio10_3, &ratio10_3, &ratio10_3, &ratio10_3, 
&ratio10_3, &ratio10_3, &ratio10_3, &ratio10_3, &ratio10_3, &ratio10_3, &ratio10_3}; 

static const ScaleNote * const maj3dom75primefullspan[128] = {&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, 
&ratio1_1, &ratio1_1, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, 
&ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, 
&ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, 
&ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, 
&ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio2_1, 
&ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, 
&ratio2_1, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, 
&ratio9_4, &ratio9_4, &ratio9_4, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, 
&ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio16_5, &ratio16_5, &ratio16_5, &ratio16_5, &ratio16_5, &ratio16_5, &ratio16_5, 
&ratio16_5, &ratio16_5, &ratio16_5, &ratio16_5, &ratio16_5, &ratio16_5, &ratio16_5}; 

static const ScaleNote * const subdompenta5primefullspan[128] = {&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, 
&ratio1_1, &ratio1_1, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, 
&ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, 
&ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, 
&ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, 
&ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio2_1, 
&ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, 
&ratio2_1, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, 
&ratio9_4, &ratio9_4, &ratio9_4, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, 
&ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, 
&ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1}; 

static const ScaleNote * const dompenta5primefullspan[128] = {&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, 
&ratio1_1, &ratio1_1, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, 
&ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, 
&ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, 
&ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, 
&ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio2_1, 
&ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, 
&ratio2_1, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, 
&ratio9_4, &ratio9_4, &ratio9_4, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, 
&ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, 
&ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1}; 

static const ScaleNote * const relmin75primefullspan[128] = {&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, 
&ratio1_1, &ratio1_1, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, 
&ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, 
&ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, 
&ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, 
&ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio2_1, 
&ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, 
&ratio2_1, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, 
&ratio5_2, &ratio5_2, &ratio5_2, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, 
&ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, 
&ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2}; 

static const ScaleNote * const dim75primefullspan[128] = {&ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, 
&ratio9_8, &ratio9_8, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, 
&ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, 
&ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, 
&ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, 
&ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio2_1, 
&ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, 
&ratio2_1, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, 
&ratio8_3, &ratio8_3, &ratio8_3, &ratio16_5, &ratio16_5, &ratio16_5, &ratio16_5, &ratio16_5, &ratio16_5, &ratio16_5, &ratio16_5, &ratio16_5, 
&ratio16_5, &ratio16_5, &ratio16_5, &ratio16_5, &ratio16_5, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, 
&ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2}; 

static const ScaleNote * const majmaj75primefullspan[128] = {&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, 
&ratio1_1, &ratio1_1, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, 
&ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, 
&ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, 
&ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, 
&ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio2_1, 
&ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, 
&ratio2_1, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, 
&ratio5_2, &ratio5_2, &ratio5_2, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, 
&ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio15_4, &ratio15_4, &ratio15_4, &ratio15_4, &ratio15_4, &ratio15_4, &ratio15_4, 
&ratio15_4, &ratio15_4, &ratio15_4, &ratio15_4, &ratio15_4, &ratio15_4, &ratio15_4}; 



static const ScaleNote * const harmSubharmfullspan1[128] = {&ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, 
&ratio1_8, &ratio1_8, &ratio1_8, &ratio1_7, &ratio1_7, &ratio1_7, &ratio1_7, &ratio1_7, &ratio1_7, &ratio1_7, &ratio1_7, &ratio1_7, 
&ratio1_7, &ratio1_7, &ratio1_7, &ratio1_7, &ratio1_7, &ratio1_7, &ratio1_7, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, 
&ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_5, 
&ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, 
&ratio1_5, &ratio1_5, &ratio1_5, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, 
&ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, 
&ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_2, 
&ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, 
&ratio1_2, &ratio1_2, &ratio1_2, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, 
&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1}; 

static const ScaleNote * const harmSubharmfullspan2[128] = {&ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, 
&ratio1_4, &ratio1_4, &ratio1_4, &ratio2_7, &ratio2_7, &ratio2_7, &ratio2_7, &ratio2_7, &ratio2_7, &ratio2_7, &ratio2_7, &ratio2_7, 
&ratio2_7, &ratio2_7, &ratio2_7, &ratio2_7, &ratio2_7, &ratio2_7, &ratio2_7, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, 
&ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio2_5, 
&ratio2_5, &ratio2_5, &ratio2_5, &ratio2_5, &ratio2_5, &ratio2_5, &ratio2_5, &ratio2_5, &ratio2_5, &ratio2_5, &ratio2_5, &ratio2_5, 
&ratio2_5, &ratio2_5, &ratio2_5, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, 
&ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, 
&ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio1_1, 
&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, 
&ratio1_1, &ratio1_1, &ratio1_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, 
&ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1}; 

static const ScaleNote * const harmSubharmfullspan3[128] = {&ratio3_8, &ratio3_8, &ratio3_8, &ratio3_8, &ratio3_8, &ratio3_8, &ratio3_8, &ratio3_8, &ratio3_8, &ratio3_8, &ratio3_8, &ratio3_8, &ratio3_8, 
&ratio3_8, &ratio3_8, &ratio3_8, &ratio3_7, &ratio3_7, &ratio3_7, &ratio3_7, &ratio3_7, &ratio3_7, &ratio3_7, &ratio3_7, &ratio3_7, 
&ratio3_7, &ratio3_7, &ratio3_7, &ratio3_7, &ratio3_7, &ratio3_7, &ratio3_7, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, 
&ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio3_5, 
&ratio3_5, &ratio3_5, &ratio3_5, &ratio3_5, &ratio3_5, &ratio3_5, &ratio3_5, &ratio3_5, &ratio3_5, &ratio3_5, &ratio3_5, &ratio3_5, 
&ratio3_5, &ratio3_5, &ratio3_5, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, 
&ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, 
&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio3_2, 
&ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, 
&ratio3_2, &ratio3_2, &ratio3_2, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, 
&ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1}; 

static const ScaleNote * const harmSubharmfullspan4[128] = {&ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, 
&ratio1_2, &ratio1_2, &ratio1_2, &ratio4_7, &ratio4_7, &ratio4_7, &ratio4_7, &ratio4_7, &ratio4_7, &ratio4_7, &ratio4_7, &ratio4_7, 
&ratio4_7, &ratio4_7, &ratio4_7, &ratio4_7, &ratio4_7, &ratio4_7, &ratio4_7, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, 
&ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio4_5, 
&ratio4_5, &ratio4_5, &ratio4_5, &ratio4_5, &ratio4_5, &ratio4_5, &ratio4_5, &ratio4_5, &ratio4_5, &ratio4_5, &ratio4_5, &ratio4_5, 
&ratio4_5, &ratio4_5, &ratio4_5, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, 
&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, 
&ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio2_1, 
&ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, 
&ratio2_1, &ratio2_1, &ratio2_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, 
&ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1}; 

static const ScaleNote * const harmSubharmfullspan5[128] = {&ratio5_8, &ratio5_8, &ratio5_8, &ratio5_8, &ratio5_8, &ratio5_8, &ratio5_8, &ratio5_8, &ratio5_8, &ratio5_8, &ratio5_8, &ratio5_8, &ratio5_8, 
&ratio5_8, &ratio5_8, &ratio5_8, &ratio5_7, &ratio5_7, &ratio5_7, &ratio5_7, &ratio5_7, &ratio5_7, &ratio5_7, &ratio5_7, &ratio5_7, 
&ratio5_7, &ratio5_7, &ratio5_7, &ratio5_7, &ratio5_7, &ratio5_7, &ratio5_7, &ratio5_6, &ratio5_6, &ratio5_6, &ratio5_6, &ratio5_6, 
&ratio5_6, &ratio5_6, &ratio5_6, &ratio5_6, &ratio5_6, &ratio5_6, &ratio5_6, &ratio5_6, &ratio5_6, &ratio5_6, &ratio5_6, &ratio1_1, 
&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, 
&ratio1_1, &ratio1_1, &ratio1_1, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, 
&ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, 
&ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_2, 
&ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, 
&ratio5_2, &ratio5_2, &ratio5_2, &ratio5_1, &ratio5_1, &ratio5_1, &ratio5_1, &ratio5_1, &ratio5_1, &ratio5_1, &ratio5_1, &ratio5_1, 
&ratio5_1, &ratio5_1, &ratio5_1, &ratio5_1, &ratio5_1, &ratio5_1, &ratio5_1}; 

static const ScaleNote * const harmSubharmfullspan6[128] = {&ratio3_4, &ratio3_4, &ratio3_4, &ratio3_4, &ratio3_4, &ratio3_4, &ratio3_4, &ratio3_4, &ratio3_4, &ratio3_4, &ratio3_4, &ratio3_4, &ratio3_4, 
&ratio3_4, &ratio3_4, &ratio3_4, &ratio6_7, &ratio6_7, &ratio6_7, &ratio6_7, &ratio6_7, &ratio6_7, &ratio6_7, &ratio6_7, &ratio6_7, 
&ratio6_7, &ratio6_7, &ratio6_7, &ratio6_7, &ratio6_7, &ratio6_7, &ratio6_7, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, 
&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio6_5, 
&ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, 
&ratio6_5, &ratio6_5, &ratio6_5, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, 
&ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, 
&ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio3_1, 
&ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, 
&ratio3_1, &ratio3_1, &ratio3_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, 
&ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1}; 

static const ScaleNote * const harmSubharmfullspan7[128] = {&ratio7_8, &ratio7_8, &ratio7_8, &ratio7_8, &ratio7_8, &ratio7_8, &ratio7_8, &ratio7_8, &ratio7_8, &ratio7_8, &ratio7_8, &ratio7_8, &ratio7_8, 
&ratio7_8, &ratio7_8, &ratio7_8, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, 
&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio7_6, &ratio7_6, &ratio7_6, &ratio7_6, &ratio7_6, 
&ratio7_6, &ratio7_6, &ratio7_6, &ratio7_6, &ratio7_6, &ratio7_6, &ratio7_6, &ratio7_6, &ratio7_6, &ratio7_6, &ratio7_6, &ratio7_5, 
&ratio7_5, &ratio7_5, &ratio7_5, &ratio7_5, &ratio7_5, &ratio7_5, &ratio7_5, &ratio7_5, &ratio7_5, &ratio7_5, &ratio7_5, &ratio7_5, 
&ratio7_5, &ratio7_5, &ratio7_5, &ratio7_4, &ratio7_4, &ratio7_4, &ratio7_4, &ratio7_4, &ratio7_4, &ratio7_4, &ratio7_4, &ratio7_4, 
&ratio7_4, &ratio7_4, &ratio7_4, &ratio7_4, &ratio7_4, &ratio7_4, &ratio7_4, &ratio7_3, &ratio7_3, &ratio7_3, &ratio7_3, &ratio7_3, 
&ratio7_3, &ratio7_3, &ratio7_3, &ratio7_3, &ratio7_3, &ratio7_3, &ratio7_3, &ratio7_3, &ratio7_3, &ratio7_3, &ratio7_3, &ratio7_2, 
&ratio7_2, &ratio7_2, &ratio7_2, &ratio7_2, &ratio7_2, &ratio7_2, &ratio7_2, &ratio7_2, &ratio7_2, &ratio7_2, &ratio7_2, &ratio7_2, 
&ratio7_2, &ratio7_2, &ratio7_2, &ratio7_1, &ratio7_1, &ratio7_1, &ratio7_1, &ratio7_1, &ratio7_1, &ratio7_1, &ratio7_1, &ratio7_1, 
&ratio7_1, &ratio7_1, &ratio7_1, &ratio7_1, &ratio7_1, &ratio7_1, &ratio7_1}; 

static const ScaleNote * const harmSubharmfullspan8[128] = {&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, 
&ratio1_1, &ratio1_1, &ratio1_1, &ratio8_7, &ratio8_7, &ratio8_7, &ratio8_7, &ratio8_7, &ratio8_7, &ratio8_7, &ratio8_7, &ratio8_7, 
&ratio8_7, &ratio8_7, &ratio8_7, &ratio8_7, &ratio8_7, &ratio8_7, &ratio8_7, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, 
&ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio8_5, 
&ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, 
&ratio8_5, &ratio8_5, &ratio8_5, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, 
&ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, 
&ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio4_1, 
&ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, 
&ratio4_1, &ratio4_1, &ratio4_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, 
&ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1}; 



static const ScaleNote * const dominant5primefullspan[128] = {&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, 
&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, 
&ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, 
&ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, 
&ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, 
&ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, 
&ratio4_3, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, 
&ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, 
&ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, 
&ratio5_3, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, 
&ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5}; 

static const ScaleNote * const major5primefullspan[128] = {&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, 
&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, 
&ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, 
&ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, 
&ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, 
&ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, 
&ratio4_3, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, 
&ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, 
&ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, 
&ratio5_3, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, 
&ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8}; 

static const ScaleNote * const dorian5primefullspan[128] = {&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, 
&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio9_8, &ratio9_8, &ratio9_8, 
&ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, 
&ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, 
&ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, 
&ratio5_4, &ratio5_4, &ratio5_4, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, 
&ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, 
&ratio3_2, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, 
&ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio9_5, &ratio9_5, 
&ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, 
&ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5}; 

static const ScaleNote * const phrygian5primefullspan[128] = {&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, 
&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio16_15, &ratio16_15, &ratio16_15, &ratio16_15, &ratio16_15, &ratio16_15, 
&ratio16_15, &ratio16_15, &ratio16_15, &ratio16_15, &ratio16_15, &ratio16_15, &ratio16_15, &ratio16_15, &ratio16_15, &ratio16_15, &ratio16_15, &ratio16_15, 
&ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, 
&ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, 
&ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, 
&ratio4_3, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, 
&ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, 
&ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, 
&ratio8_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, 
&ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5}; 

static const ScaleNote * const lydian5primefullspan[128] = {&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, 
&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, 
&ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, 
&ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, 
&ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio25_18, &ratio25_18, &ratio25_18, &ratio25_18, &ratio25_18, &ratio25_18, 
&ratio25_18, &ratio25_18, &ratio25_18, &ratio25_18, &ratio25_18, &ratio25_18, &ratio25_18, &ratio25_18, &ratio25_18, &ratio25_18, &ratio25_18, &ratio25_18, 
&ratio25_18, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, 
&ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, 
&ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, 
&ratio5_2, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, 
&ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8}; 

static const ScaleNote * const mixolydian5primefullspan[128] = {&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, 
&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, 
&ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, 
&ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, 
&ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, 
&ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, 
&ratio4_3, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, 
&ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, 
&ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, 
&ratio5_3, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, 
&ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5}; 

static const ScaleNote * const aeolian5primefullspan[128] = {&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, 
&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, 
&ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, &ratio9_8, 
&ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, 
&ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, 
&ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, 
&ratio4_3, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, 
&ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, 
&ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, 
&ratio8_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, 
&ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5}; 

static const ScaleNote * const locrian5primefullspan[128] = {&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, 
&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio16_15, &ratio16_15, &ratio16_15, &ratio16_15, &ratio16_15, &ratio16_15, 
&ratio16_15, &ratio16_15, &ratio16_15, &ratio16_15, &ratio16_15, &ratio16_15, &ratio16_15, &ratio16_15, &ratio16_15, &ratio16_15, &ratio16_15, &ratio16_15, 
&ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, 
&ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, 
&ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, 
&ratio4_3, &ratio25_18, &ratio25_18, &ratio25_18, &ratio25_18, &ratio25_18, &ratio25_18, &ratio25_18, &ratio25_18, &ratio25_18, &ratio25_18, &ratio25_18, 
&ratio25_18, &ratio25_18, &ratio25_18, &ratio25_18, &ratio25_18, &ratio25_18, &ratio25_18, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, 
&ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, 
&ratio8_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, 
&ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5}; 



static const ScaleNote * const harmSubharm1[128] = {&ratio1_320, &ratio1_320, &ratio1_320, &ratio1_320, &ratio1_256, &ratio1_256, &ratio1_256, &ratio1_256, &ratio1_192, &ratio1_192, &ratio1_192, &ratio1_192, &ratio1_192, 
&ratio1_192, &ratio1_128, &ratio1_128, &ratio1_128, &ratio1_128, &ratio1_128, &ratio1_128, &ratio1_128, &ratio1_128, &ratio1_128, &ratio1_64, &ratio1_64, 
&ratio1_64, &ratio1_64, &ratio1_64, &ratio1_64, &ratio1_64, &ratio1_64, &ratio1_56, &ratio1_56, &ratio1_48, &ratio1_48, &ratio1_48, &ratio1_40, 
&ratio1_40, &ratio1_40, &ratio1_40, &ratio1_32, &ratio1_32, &ratio1_32, &ratio1_32, &ratio1_24, &ratio1_24, &ratio1_24, &ratio1_24, &ratio1_24, 
&ratio1_24, &ratio1_16, &ratio1_16, &ratio1_16, &ratio1_16, &ratio1_16, &ratio1_16, &ratio1_16, &ratio1_16, &ratio1_16, &ratio1_8, &ratio1_8, 
&ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_7, &ratio1_7, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_5, 
&ratio1_5, &ratio1_5, &ratio1_5, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, 
&ratio1_3, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_1, &ratio1_1, 
&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio8_7, &ratio8_7, &ratio4_3, &ratio4_3, &ratio4_3, &ratio8_5, 
&ratio8_5, &ratio8_5, &ratio8_5, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, 
&ratio8_3, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1}; 

static const ScaleNote * const harmSubharm2[128] = {&ratio1_160, &ratio1_160, &ratio1_160, &ratio1_160, &ratio1_128, &ratio1_128, &ratio1_128, &ratio1_128, &ratio1_96, &ratio1_96, &ratio1_96, &ratio1_96, &ratio1_96, 
&ratio1_96, &ratio1_64, &ratio1_64, &ratio1_64, &ratio1_64, &ratio1_64, &ratio1_64, &ratio1_64, &ratio1_64, &ratio1_64, &ratio1_32, &ratio1_32, 
&ratio1_32, &ratio1_32, &ratio1_32, &ratio1_32, &ratio1_32, &ratio1_32, &ratio1_28, &ratio1_28, &ratio1_24, &ratio1_24, &ratio1_24, &ratio1_20, 
&ratio1_20, &ratio1_20, &ratio1_20, &ratio1_16, &ratio1_16, &ratio1_16, &ratio1_16, &ratio1_12, &ratio1_12, &ratio1_12, &ratio1_12, &ratio1_12, 
&ratio1_12, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_4, &ratio1_4, 
&ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio2_7, &ratio2_7, &ratio1_3, &ratio1_3, &ratio1_3, &ratio2_5, 
&ratio2_5, &ratio2_5, &ratio2_5, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, 
&ratio2_3, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio2_1, &ratio2_1, 
&ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio16_7, &ratio16_7, &ratio8_3, &ratio8_3, &ratio8_3, &ratio16_5, 
&ratio16_5, &ratio16_5, &ratio16_5, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio16_3, &ratio16_3, &ratio16_3, &ratio16_3, &ratio16_3, 
&ratio16_3, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1}; 

static const ScaleNote * const harmSubharm3[128] = {&ratio3_512, &ratio3_512, &ratio3_512, &ratio3_512, &ratio3_512, &ratio3_512, &ratio3_256, &ratio3_256, &ratio3_256, &ratio3_256, &ratio3_256, &ratio3_256, &ratio3_256, 
&ratio3_256, &ratio3_256, &ratio3_256, &ratio3_128, &ratio3_128, &ratio3_128, &ratio3_128, &ratio3_128, &ratio3_128, &ratio3_128, &ratio3_128, &ratio3_128, 
&ratio3_128, &ratio3_112, &ratio3_112, &ratio1_32, &ratio1_32, &ratio1_32, &ratio3_80, &ratio3_80, &ratio3_80, &ratio3_80, &ratio3_64, &ratio3_64, 
&ratio3_64, &ratio3_64, &ratio1_16, &ratio1_16, &ratio1_16, &ratio1_16, &ratio1_16, &ratio3_32, &ratio3_32, &ratio3_32, &ratio3_32, &ratio3_32, 
&ratio3_32, &ratio3_32, &ratio3_32, &ratio3_32, &ratio3_32, &ratio3_16, &ratio3_16, &ratio3_16, &ratio3_16, &ratio3_16, &ratio3_16, &ratio3_16, 
&ratio3_16, &ratio3_16, &ratio3_16, &ratio3_8, &ratio3_8, &ratio3_8, &ratio3_8, &ratio3_8, &ratio3_8, &ratio3_8, &ratio3_8, &ratio3_8, 
&ratio3_8, &ratio3_7, &ratio3_7, &ratio1_2, &ratio1_2, &ratio1_2, &ratio3_5, &ratio3_5, &ratio3_5, &ratio3_5, &ratio3_4, &ratio3_4, 
&ratio3_4, &ratio3_4, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, 
&ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, 
&ratio3_1, &ratio3_1, &ratio3_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, 
&ratio6_1, &ratio48_7, &ratio48_7, &ratio8_1, &ratio8_1, &ratio8_1, &ratio48_5}; 

static const ScaleNote * const harmSubharm4[128] = {&ratio1_80, &ratio1_80, &ratio1_80, &ratio1_80, &ratio1_64, &ratio1_64, &ratio1_64, &ratio1_48, &ratio1_48, &ratio1_48, &ratio1_48, &ratio1_48, &ratio1_48, 
&ratio1_32, &ratio1_32, &ratio1_32, &ratio1_32, &ratio1_32, &ratio1_32, &ratio1_32, &ratio1_32, &ratio1_32, &ratio1_32, &ratio1_16, &ratio1_16, 
&ratio1_16, &ratio1_16, &ratio1_16, &ratio1_16, &ratio1_16, &ratio1_16, &ratio1_14, &ratio1_14, &ratio1_12, &ratio1_12, &ratio1_12, &ratio1_10, 
&ratio1_10, &ratio1_10, &ratio1_10, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, 
&ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_2, &ratio1_2, 
&ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio4_7, &ratio4_7, &ratio2_3, &ratio2_3, &ratio2_3, &ratio4_5, 
&ratio4_5, &ratio4_5, &ratio4_5, &ratio1_1, &ratio1_1, &ratio1_1, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, 
&ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio4_1, &ratio4_1, 
&ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio32_7, &ratio32_7, &ratio16_3, &ratio16_3, &ratio16_3, &ratio32_5, 
&ratio32_5, &ratio32_5, &ratio32_5, &ratio8_1, &ratio8_1, &ratio8_1, &ratio32_3, &ratio32_3, &ratio32_3, &ratio32_3, &ratio32_3, &ratio32_3, 
&ratio16_1, &ratio16_1, &ratio16_1, &ratio16_1, &ratio16_1, &ratio16_1, &ratio16_1}; 

static const ScaleNote * const harmSubharm5[128] = {&ratio5_512, &ratio5_512, &ratio5_256, &ratio5_256, &ratio5_256, &ratio5_256, &ratio5_256, &ratio5_256, &ratio5_256, &ratio5_256, &ratio5_256, &ratio5_256, &ratio5_256, 
&ratio5_256, &ratio5_256, &ratio5_256, &ratio5_128, &ratio5_128, &ratio5_128, &ratio5_128, &ratio5_128, &ratio5_128, &ratio5_128, &ratio5_112, &ratio5_112, 
&ratio5_96, &ratio5_96, &ratio5_96, &ratio1_16, &ratio1_16, &ratio5_64, &ratio5_64, &ratio5_64, &ratio5_64, &ratio5_48, &ratio5_48, &ratio5_48, 
&ratio5_48, &ratio5_48, &ratio5_48, &ratio5_32, &ratio5_32, &ratio5_32, &ratio5_32, &ratio5_32, &ratio5_32, &ratio5_32, &ratio5_32, &ratio5_32, 
&ratio5_32, &ratio5_16, &ratio5_16, &ratio5_16, &ratio5_16, &ratio5_16, &ratio5_16, &ratio5_16, &ratio5_16, &ratio5_16, &ratio5_16, &ratio5_16, 
&ratio5_16, &ratio5_16, &ratio5_16, &ratio5_8, &ratio5_8, &ratio5_8, &ratio5_8, &ratio5_8, &ratio5_8, &ratio5_8, &ratio5_7, &ratio5_7, 
&ratio5_6, &ratio5_6, &ratio5_6, &ratio1_1, &ratio1_1, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_3, &ratio5_3, &ratio5_3, 
&ratio5_3, &ratio5_3, &ratio5_3, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, 
&ratio5_2, &ratio5_1, &ratio5_1, &ratio5_1, &ratio5_1, &ratio5_1, &ratio5_1, &ratio5_1, &ratio5_1, &ratio5_1, &ratio5_1, &ratio5_1, 
&ratio5_1, &ratio5_1, &ratio5_1, &ratio10_1, &ratio10_1, &ratio10_1, &ratio10_1, &ratio10_1, &ratio10_1, &ratio10_1, &ratio80_7, &ratio80_7, 
&ratio40_3, &ratio40_3, &ratio40_3, &ratio16_1, &ratio16_1, &ratio20_1, &ratio20_1}; 

static const ScaleNote * const harmSubharm6[128] = {&ratio3_256, &ratio3_256, &ratio3_256, &ratio3_256, &ratio3_256, &ratio3_256, &ratio3_128, &ratio3_128, &ratio3_128, &ratio3_128, &ratio3_128, &ratio3_128, &ratio3_128, 
&ratio3_128, &ratio3_128, &ratio3_128, &ratio3_64, &ratio3_64, &ratio3_64, &ratio3_64, &ratio3_64, &ratio3_64, &ratio3_64, &ratio3_64, &ratio3_64, 
&ratio3_64, &ratio3_56, &ratio3_56, &ratio1_16, &ratio1_16, &ratio3_40, &ratio3_40, &ratio3_40, &ratio3_40, &ratio3_32, &ratio3_32, &ratio3_32, 
&ratio3_32, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio3_16, &ratio3_16, &ratio3_16, &ratio3_16, &ratio3_16, 
&ratio3_16, &ratio3_16, &ratio3_16, &ratio3_16, &ratio3_16, &ratio3_8, &ratio3_8, &ratio3_8, &ratio3_8, &ratio3_8, &ratio3_8, &ratio3_8, 
&ratio3_8, &ratio3_8, &ratio3_8, &ratio3_4, &ratio3_4, &ratio3_4, &ratio3_4, &ratio3_4, &ratio3_4, &ratio3_4, &ratio3_4, &ratio3_4, 
&ratio3_4, &ratio6_7, &ratio6_7, &ratio1_1, &ratio1_1, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio3_2, &ratio3_2, &ratio3_2, 
&ratio3_2, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, 
&ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, 
&ratio6_1, &ratio6_1, &ratio6_1, &ratio12_1, &ratio12_1, &ratio12_1, &ratio12_1, &ratio12_1, &ratio12_1, &ratio12_1, &ratio12_1, &ratio12_1, 
&ratio12_1, &ratio96_7, &ratio96_7, &ratio16_1, &ratio16_1, &ratio96_5, &ratio96_5}; 

static const ScaleNote * const harmSubharm7[128] = {&ratio7_512, &ratio7_512, &ratio7_512, &ratio7_512, &ratio7_512, &ratio7_512, &ratio7_512, &ratio7_512, &ratio7_256, &ratio7_256, &ratio7_256, &ratio7_256, &ratio7_256, 
&ratio7_256, &ratio7_256, &ratio7_256, &ratio7_128, &ratio7_128, &ratio7_128, &ratio7_128, &ratio7_128, &ratio7_128, &ratio7_128, &ratio7_128, &ratio7_128, 
&ratio7_128, &ratio7_128, &ratio7_128, &ratio1_16, &ratio1_16, &ratio7_96, &ratio7_96, &ratio7_80, &ratio7_80, &ratio7_80, &ratio7_80, &ratio7_64, 
&ratio7_64, &ratio7_64, &ratio7_64, &ratio7_48, &ratio7_48, &ratio7_48, &ratio7_48, &ratio7_48, &ratio7_48, &ratio7_32, &ratio7_32, &ratio7_32, 
&ratio7_32, &ratio7_32, &ratio7_32, &ratio7_32, &ratio7_32, &ratio7_32, &ratio7_32, &ratio7_16, &ratio7_16, &ratio7_16, &ratio7_16, &ratio7_16, 
&ratio7_16, &ratio7_16, &ratio7_16, &ratio7_8, &ratio7_8, &ratio7_8, &ratio7_8, &ratio7_8, &ratio7_8, &ratio7_8, &ratio7_8, &ratio7_8, 
&ratio7_8, &ratio7_8, &ratio7_8, &ratio1_1, &ratio1_1, &ratio7_6, &ratio7_6, &ratio7_5, &ratio7_5, &ratio7_5, &ratio7_5, &ratio7_4, 
&ratio7_4, &ratio7_4, &ratio7_4, &ratio7_3, &ratio7_3, &ratio7_3, &ratio7_3, &ratio7_3, &ratio7_3, &ratio7_2, &ratio7_2, &ratio7_2, 
&ratio7_2, &ratio7_2, &ratio7_2, &ratio7_2, &ratio7_2, &ratio7_2, &ratio7_2, &ratio7_1, &ratio7_1, &ratio7_1, &ratio7_1, &ratio7_1, 
&ratio7_1, &ratio7_1, &ratio7_1, &ratio14_1, &ratio14_1, &ratio14_1, &ratio14_1, &ratio14_1, &ratio14_1, &ratio14_1, &ratio14_1, &ratio14_1, 
&ratio14_1, &ratio14_1, &ratio14_1, &ratio16_1, &ratio16_1, &ratio56_3, &ratio56_3}; 

static const ScaleNote * const harmSubharm8[128] = {&ratio1_40, &ratio1_40, &ratio1_40, &ratio1_32, &ratio1_32, &ratio1_32, &ratio1_32, &ratio1_24, &ratio1_24, &ratio1_24, &ratio1_24, &ratio1_24, &ratio1_24, 
&ratio1_16, &ratio1_16, &ratio1_16, &ratio1_16, &ratio1_16, &ratio1_16, &ratio1_16, &ratio1_16, &ratio1_16, &ratio1_16, &ratio1_8, &ratio1_8, 
&ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_7, &ratio1_7, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_5, &ratio1_5, 
&ratio1_5, &ratio1_5, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, 
&ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_1, &ratio1_1, 
&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio8_7, &ratio8_7, &ratio4_3, &ratio4_3, &ratio4_3, &ratio8_5, &ratio8_5, 
&ratio8_5, &ratio8_5, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, 
&ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio8_1, &ratio8_1, 
&ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio64_7, &ratio64_7, &ratio32_3, &ratio32_3, &ratio32_3, &ratio64_5, &ratio64_5, 
&ratio64_5, &ratio64_5, &ratio16_1, &ratio16_1, &ratio16_1, &ratio16_1, &ratio64_3, &ratio64_3, &ratio64_3, &ratio64_3, &ratio64_3, &ratio64_3, 
&ratio32_1, &ratio32_1, &ratio32_1, &ratio32_1, &ratio32_1, &ratio32_1, &ratio32_1}; 



static const ScaleNote * const harmFolded8_2oct[128] = {&ratio3_128, &ratio7_256, &ratio7_256, &ratio1_32, &ratio1_32, &ratio1_32, &ratio1_28, &ratio1_28, &ratio1_24, &ratio1_24, &ratio3_64, &ratio3_64, &ratio1_20, 
&ratio1_20, &ratio1_20, &ratio1_20, &ratio1_16, &ratio1_16, &ratio5_64, &ratio5_64, &ratio1_12, &ratio1_12, &ratio3_32, &ratio3_32, &ratio3_32, 
&ratio7_64, &ratio7_64, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_7, &ratio1_7, &ratio1_6, &ratio1_6, &ratio3_16, &ratio3_16, &ratio1_5, 
&ratio1_5, &ratio1_5, &ratio1_5, &ratio1_4, &ratio1_4, &ratio5_16, &ratio5_16, &ratio1_3, &ratio1_3, &ratio3_8, &ratio3_8, &ratio3_8, 
&ratio7_16, &ratio7_16, &ratio1_2, &ratio1_2, &ratio1_2, &ratio4_7, &ratio4_7, &ratio2_3, &ratio2_3, &ratio3_4, &ratio3_4, &ratio4_5, 
&ratio4_5, &ratio4_5, &ratio4_5, &ratio1_1, &ratio1_1, &ratio5_4, &ratio5_4, &ratio4_3, &ratio4_3, &ratio3_2, &ratio3_2, &ratio3_2, 
&ratio7_4, &ratio7_4, &ratio2_1, &ratio2_1, &ratio2_1, &ratio16_7, &ratio16_7, &ratio8_3, &ratio8_3, &ratio3_1, &ratio3_1, &ratio16_5, 
&ratio16_5, &ratio16_5, &ratio16_5, &ratio4_1, &ratio4_1, &ratio5_1, &ratio5_1, &ratio16_3, &ratio16_3, &ratio6_1, &ratio6_1, &ratio6_1, 
&ratio7_1, &ratio7_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio64_7, &ratio64_7, &ratio32_3, &ratio32_3, &ratio12_1, &ratio12_1, &ratio64_5, 
&ratio64_5, &ratio64_5, &ratio64_5, &ratio16_1, &ratio16_1, &ratio20_1, &ratio20_1, &ratio64_3, &ratio64_3, &ratio24_1, &ratio24_1, &ratio24_1, 
&ratio28_1, &ratio28_1, &ratio32_1, &ratio32_1, &ratio32_1, &ratio256_7, &ratio256_7}; 

static const ScaleNote * const harmFolded12_2oct[128] = {&ratio1_32, &ratio1_32, &ratio1_32, &ratio1_32, &ratio9_256, &ratio5_128, &ratio1_24, &ratio1_24, &ratio3_64, &ratio3_64, &ratio3_64, &ratio3_64, &ratio3_64, 
&ratio3_64, &ratio1_16, &ratio1_16, &ratio5_64, &ratio5_64, &ratio1_12, &ratio1_12, &ratio3_32, &ratio3_32, &ratio1_10, &ratio1_9, &ratio1_9, 
&ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio9_64, &ratio5_32, &ratio1_6, &ratio1_6, &ratio3_16, &ratio3_16, &ratio3_16, &ratio3_16, 
&ratio3_16, &ratio3_16, &ratio1_4, &ratio1_4, &ratio5_16, &ratio5_16, &ratio1_3, &ratio1_3, &ratio3_8, &ratio3_8, &ratio2_5, &ratio4_9, 
&ratio4_9, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio9_16, &ratio5_8, &ratio2_3, &ratio2_3, &ratio3_4, &ratio3_4, &ratio3_4, 
&ratio3_4, &ratio3_4, &ratio3_4, &ratio1_1, &ratio1_1, &ratio5_4, &ratio5_4, &ratio4_3, &ratio4_3, &ratio3_2, &ratio3_2, &ratio8_5, 
&ratio16_9, &ratio16_9, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio9_4, &ratio5_2, &ratio8_3, &ratio8_3, &ratio3_1, &ratio3_1, 
&ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio4_1, &ratio4_1, &ratio5_1, &ratio5_1, &ratio16_3, &ratio16_3, &ratio6_1, &ratio6_1, 
&ratio32_5, &ratio64_9, &ratio64_9, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio9_1, &ratio10_1, &ratio32_3, &ratio32_3, &ratio12_1, 
&ratio12_1, &ratio12_1, &ratio12_1, &ratio12_1, &ratio12_1, &ratio16_1, &ratio16_1, &ratio20_1, &ratio20_1, &ratio64_3, &ratio64_3, &ratio24_1, 
&ratio24_1, &ratio128_5, &ratio256_9, &ratio256_9, &ratio32_1, &ratio32_1, &ratio32_1}; 

static const ScaleNote * const HarmFolded12_3oct[128] = {&ratio1_40, &ratio1_40, &ratio1_40, &ratio1_32, &ratio1_32, &ratio1_32, &ratio1_32, &ratio1_24, &ratio1_24, &ratio1_24, &ratio3_64, &ratio3_64, &ratio3_64, 
&ratio3_64, &ratio1_16, &ratio1_16, &ratio1_16, &ratio1_16, &ratio5_64, &ratio5_64, &ratio1_12, &ratio1_12, &ratio1_11, &ratio3_32, &ratio1_10, 
&ratio7_64, &ratio1_9, &ratio1_9, &ratio1_8, &ratio1_8, &ratio9_64, &ratio5_32, &ratio1_6, &ratio11_64, &ratio11_64, &ratio3_16, &ratio1_5, 
&ratio1_5, &ratio1_5, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_3, &ratio1_3, &ratio1_3, &ratio3_8, &ratio3_8, &ratio3_8, 
&ratio3_8, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio5_8, &ratio5_8, &ratio2_3, &ratio2_3, &ratio8_11, &ratio3_4, &ratio4_5, 
&ratio7_8, &ratio8_9, &ratio8_9, &ratio1_1, &ratio1_1, &ratio9_8, &ratio5_4, &ratio4_3, &ratio11_8, &ratio11_8, &ratio3_2, &ratio8_5, 
&ratio8_5, &ratio8_5, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio8_3, &ratio8_3, &ratio8_3, &ratio3_1, &ratio3_1, &ratio3_1, 
&ratio3_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio5_1, &ratio5_1, &ratio16_3, &ratio16_3, &ratio64_11, &ratio6_1, &ratio32_5, 
&ratio7_1, &ratio64_9, &ratio64_9, &ratio8_1, &ratio8_1, &ratio9_1, &ratio10_1, &ratio32_3, &ratio11_1, &ratio11_1, &ratio12_1, &ratio64_5, 
&ratio64_5, &ratio64_5, &ratio16_1, &ratio16_1, &ratio16_1, &ratio16_1, &ratio64_3, &ratio64_3, &ratio64_3, &ratio24_1, &ratio24_1, &ratio24_1, 
&ratio24_1, &ratio32_1, &ratio32_1, &ratio32_1, &ratio32_1, &ratio40_1, &ratio40_1}; 

static const ScaleNote * const HarmFolded16_4oct[128] = {&ratio3_128, &ratio7_256, &ratio7_256, &ratio1_32, &ratio1_32, &ratio1_32, &ratio9_256, &ratio5_128, &ratio5_128, &ratio11_256, &ratio11_256, &ratio3_64, &ratio13_256, 
&ratio7_128, &ratio15_256, &ratio15_256, &ratio1_16, &ratio1_15, &ratio1_14, &ratio1_13, &ratio1_13, &ratio1_13, &ratio1_10, &ratio1_10, &ratio1_10, 
&ratio1_9, &ratio1_9, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_7, &ratio1_7, &ratio1_6, &ratio1_6, &ratio3_16, &ratio3_16, &ratio1_5, 
&ratio1_5, &ratio1_5, &ratio1_4, &ratio1_4, &ratio1_4, &ratio5_16, &ratio5_16, &ratio1_3, &ratio1_3, &ratio3_8, &ratio3_8, &ratio3_8, 
&ratio7_16, &ratio7_16, &ratio1_2, &ratio1_2, &ratio1_2, &ratio9_16, &ratio5_8, &ratio5_8, &ratio11_16, &ratio11_16, &ratio3_4, &ratio13_16, 
&ratio7_8, &ratio15_16, &ratio15_16, &ratio1_1, &ratio16_15, &ratio8_7, &ratio16_13, &ratio16_13, &ratio16_13, &ratio8_5, &ratio8_5, &ratio8_5, 
&ratio16_9, &ratio16_9, &ratio2_1, &ratio2_1, &ratio2_1, &ratio16_7, &ratio16_7, &ratio8_3, &ratio8_3, &ratio3_1, &ratio3_1, &ratio16_5, 
&ratio16_5, &ratio16_5, &ratio4_1, &ratio4_1, &ratio4_1, &ratio5_1, &ratio5_1, &ratio16_3, &ratio16_3, &ratio6_1, &ratio6_1, &ratio6_1, 
&ratio7_1, &ratio7_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio9_1, &ratio10_1, &ratio10_1, &ratio11_1, &ratio11_1, &ratio12_1, &ratio13_1, 
&ratio14_1, &ratio15_1, &ratio15_1, &ratio16_1, &ratio256_15, &ratio128_7, &ratio256_13, &ratio256_13, &ratio256_13, &ratio128_5, &ratio128_5, &ratio128_5, 
&ratio256_9, &ratio256_9, &ratio32_1, &ratio32_1, &ratio32_1, &ratio256_7, &ratio256_7}; 



static const ScaleNote * const majpenta5prime[128] = {&ratio5_192, &ratio5_192, &ratio5_192, &ratio5_192, &ratio1_32, &ratio1_32, &ratio9_256, &ratio5_128, &ratio5_128, &ratio5_128, &ratio3_64, &ratio3_64, &ratio5_96, 
&ratio5_96, &ratio5_96, &ratio5_96, &ratio1_16, &ratio1_16, &ratio9_128, &ratio5_64, &ratio5_64, &ratio5_64, &ratio3_32, &ratio3_32, &ratio5_48, 
&ratio5_48, &ratio5_48, &ratio5_48, &ratio1_8, &ratio1_8, &ratio9_64, &ratio5_32, &ratio5_32, &ratio5_32, &ratio3_16, &ratio3_16, &ratio5_24, 
&ratio5_24, &ratio5_24, &ratio5_24, &ratio1_4, &ratio1_4, &ratio9_32, &ratio5_16, &ratio5_16, &ratio5_16, &ratio3_8, &ratio3_8, &ratio5_12, 
&ratio5_12, &ratio5_12, &ratio5_12, &ratio1_2, &ratio1_2, &ratio9_16, &ratio5_8, &ratio5_8, &ratio5_8, &ratio3_4, &ratio3_4, &ratio5_6, 
&ratio5_6, &ratio5_6, &ratio5_6, &ratio1_1, &ratio1_1, &ratio9_8, &ratio5_4, &ratio5_4, &ratio5_4, &ratio3_2, &ratio3_2, &ratio5_3, 
&ratio5_3, &ratio5_3, &ratio5_3, &ratio2_1, &ratio2_1, &ratio9_4, &ratio5_2, &ratio5_2, &ratio5_2, &ratio3_1, &ratio3_1, &ratio10_3, 
&ratio10_3, &ratio10_3, &ratio10_3, &ratio4_1, &ratio4_1, &ratio9_2, &ratio5_1, &ratio5_1, &ratio5_1, &ratio6_1, &ratio6_1, &ratio20_3, 
&ratio20_3, &ratio20_3, &ratio20_3, &ratio8_1, &ratio8_1, &ratio9_1, &ratio10_1, &ratio10_1, &ratio10_1, &ratio12_1, &ratio12_1, &ratio40_3, 
&ratio40_3, &ratio40_3, &ratio40_3, &ratio16_1, &ratio16_1, &ratio18_1, &ratio20_1, &ratio20_1, &ratio20_1, &ratio24_1, &ratio24_1, &ratio80_3, 
&ratio80_3, &ratio80_3, &ratio80_3, &ratio32_1, &ratio32_1, &ratio36_1, &ratio40_1}; 

static const ScaleNote * const maj2min75prime[128] = {&ratio5_192, &ratio5_192, &ratio15_512, &ratio15_512, &ratio1_32, &ratio1_32, &ratio9_256, &ratio9_256, &ratio1_24, &ratio1_24, &ratio1_24, &ratio5_96, &ratio5_96, 
&ratio5_96, &ratio15_256, &ratio15_256, &ratio1_16, &ratio1_16, &ratio9_128, &ratio9_128, &ratio1_12, &ratio1_12, &ratio1_12, &ratio5_48, &ratio5_48, 
&ratio5_48, &ratio15_128, &ratio15_128, &ratio1_8, &ratio1_8, &ratio9_64, &ratio9_64, &ratio1_6, &ratio1_6, &ratio1_6, &ratio5_24, &ratio5_24, 
&ratio5_24, &ratio15_64, &ratio15_64, &ratio1_4, &ratio1_4, &ratio9_32, &ratio9_32, &ratio1_3, &ratio1_3, &ratio1_3, &ratio5_12, &ratio5_12, 
&ratio5_12, &ratio15_32, &ratio15_32, &ratio1_2, &ratio1_2, &ratio9_16, &ratio9_16, &ratio2_3, &ratio2_3, &ratio2_3, &ratio5_6, &ratio5_6, 
&ratio5_6, &ratio15_16, &ratio15_16, &ratio1_1, &ratio1_1, &ratio9_8, &ratio9_8, &ratio4_3, &ratio4_3, &ratio4_3, &ratio5_3, &ratio5_3, 
&ratio5_3, &ratio15_8, &ratio15_8, &ratio2_1, &ratio2_1, &ratio9_4, &ratio9_4, &ratio8_3, &ratio8_3, &ratio8_3, &ratio10_3, &ratio10_3, 
&ratio10_3, &ratio15_4, &ratio15_4, &ratio4_1, &ratio4_1, &ratio9_2, &ratio9_2, &ratio16_3, &ratio16_3, &ratio16_3, &ratio20_3, &ratio20_3, 
&ratio20_3, &ratio15_2, &ratio15_2, &ratio8_1, &ratio8_1, &ratio9_1, &ratio9_1, &ratio32_3, &ratio32_3, &ratio32_3, &ratio40_3, &ratio40_3, 
&ratio40_3, &ratio15_1, &ratio15_1, &ratio16_1, &ratio16_1, &ratio18_1, &ratio18_1, &ratio64_3, &ratio64_3, &ratio64_3, &ratio80_3, &ratio80_3, 
&ratio80_3, &ratio30_1, &ratio30_1, &ratio32_1, &ratio32_1, &ratio36_1, &ratio36_1}; 

static const ScaleNote * const maj3dom75prime[128] = {&ratio1_40, &ratio1_40, &ratio15_512, &ratio15_512, &ratio1_32, &ratio1_32, &ratio9_256, &ratio5_128, &ratio5_128, &ratio5_128, &ratio1_20, &ratio1_20, &ratio1_20, 
&ratio1_20, &ratio15_256, &ratio15_256, &ratio1_16, &ratio1_16, &ratio9_128, &ratio5_64, &ratio5_64, &ratio5_64, &ratio1_10, &ratio1_10, &ratio1_10, 
&ratio1_10, &ratio15_128, &ratio15_128, &ratio1_8, &ratio1_8, &ratio9_64, &ratio5_32, &ratio5_32, &ratio5_32, &ratio1_5, &ratio1_5, &ratio1_5, 
&ratio1_5, &ratio15_64, &ratio15_64, &ratio1_4, &ratio1_4, &ratio9_32, &ratio5_16, &ratio5_16, &ratio5_16, &ratio2_5, &ratio2_5, &ratio2_5, 
&ratio2_5, &ratio15_32, &ratio15_32, &ratio1_2, &ratio1_2, &ratio9_16, &ratio5_8, &ratio5_8, &ratio5_8, &ratio4_5, &ratio4_5, &ratio4_5, 
&ratio4_5, &ratio15_16, &ratio15_16, &ratio1_1, &ratio1_1, &ratio9_8, &ratio5_4, &ratio5_4, &ratio5_4, &ratio8_5, &ratio8_5, &ratio8_5, 
&ratio8_5, &ratio15_8, &ratio15_8, &ratio2_1, &ratio2_1, &ratio9_4, &ratio5_2, &ratio5_2, &ratio5_2, &ratio16_5, &ratio16_5, &ratio16_5, 
&ratio16_5, &ratio15_4, &ratio15_4, &ratio4_1, &ratio4_1, &ratio9_2, &ratio5_1, &ratio5_1, &ratio5_1, &ratio32_5, &ratio32_5, &ratio32_5, 
&ratio32_5, &ratio15_2, &ratio15_2, &ratio8_1, &ratio8_1, &ratio9_1, &ratio10_1, &ratio10_1, &ratio10_1, &ratio64_5, &ratio64_5, &ratio64_5, 
&ratio64_5, &ratio15_1, &ratio15_1, &ratio16_1, &ratio16_1, &ratio18_1, &ratio20_1, &ratio20_1, &ratio20_1, &ratio128_5, &ratio128_5, &ratio128_5, 
&ratio128_5, &ratio30_1, &ratio30_1, &ratio32_1, &ratio32_1, &ratio36_1, &ratio40_1}; 

static const ScaleNote * const subdompenta5prime[128] = {&ratio5_192, &ratio5_192, &ratio5_192, &ratio5_192, &ratio1_32, &ratio1_32, &ratio9_256, &ratio9_256, &ratio1_24, &ratio1_24, &ratio3_64, &ratio3_64, &ratio5_96, 
&ratio5_96, &ratio5_96, &ratio5_96, &ratio1_16, &ratio1_16, &ratio9_128, &ratio9_128, &ratio1_12, &ratio1_12, &ratio3_32, &ratio3_32, &ratio5_48, 
&ratio5_48, &ratio5_48, &ratio5_48, &ratio1_8, &ratio1_8, &ratio9_64, &ratio9_64, &ratio1_6, &ratio1_6, &ratio3_16, &ratio3_16, &ratio5_24, 
&ratio5_24, &ratio5_24, &ratio5_24, &ratio1_4, &ratio1_4, &ratio9_32, &ratio9_32, &ratio1_3, &ratio1_3, &ratio3_8, &ratio3_8, &ratio5_12, 
&ratio5_12, &ratio5_12, &ratio5_12, &ratio1_2, &ratio1_2, &ratio9_16, &ratio9_16, &ratio2_3, &ratio2_3, &ratio3_4, &ratio3_4, &ratio5_6, 
&ratio5_6, &ratio5_6, &ratio5_6, &ratio1_1, &ratio1_1, &ratio9_8, &ratio9_8, &ratio4_3, &ratio4_3, &ratio3_2, &ratio3_2, &ratio5_3, 
&ratio5_3, &ratio5_3, &ratio5_3, &ratio2_1, &ratio2_1, &ratio9_4, &ratio9_4, &ratio8_3, &ratio8_3, &ratio3_1, &ratio3_1, &ratio10_3, 
&ratio10_3, &ratio10_3, &ratio10_3, &ratio4_1, &ratio4_1, &ratio9_2, &ratio9_2, &ratio16_3, &ratio16_3, &ratio6_1, &ratio6_1, &ratio20_3, 
&ratio20_3, &ratio20_3, &ratio20_3, &ratio8_1, &ratio8_1, &ratio9_1, &ratio9_1, &ratio32_3, &ratio32_3, &ratio12_1, &ratio12_1, &ratio40_3, 
&ratio40_3, &ratio40_3, &ratio40_3, &ratio16_1, &ratio16_1, &ratio18_1, &ratio18_1, &ratio64_3, &ratio64_3, &ratio24_1, &ratio24_1, &ratio80_3, 
&ratio80_3, &ratio80_3, &ratio80_3, &ratio32_1, &ratio32_1, &ratio36_1, &ratio36_1}; 

static const ScaleNote * const dompenta5prime[128] = {&ratio3_128, &ratio15_512, &ratio15_512, &ratio15_512, &ratio1_32, &ratio1_32, &ratio9_256, &ratio9_256, &ratio1_24, &ratio1_24, &ratio3_64, &ratio3_64, &ratio3_64, 
&ratio15_256, &ratio15_256, &ratio15_256, &ratio1_16, &ratio1_16, &ratio9_128, &ratio9_128, &ratio1_12, &ratio1_12, &ratio3_32, &ratio3_32, &ratio3_32, 
&ratio15_128, &ratio15_128, &ratio15_128, &ratio1_8, &ratio1_8, &ratio9_64, &ratio9_64, &ratio1_6, &ratio1_6, &ratio3_16, &ratio3_16, &ratio3_16, 
&ratio15_64, &ratio15_64, &ratio15_64, &ratio1_4, &ratio1_4, &ratio9_32, &ratio9_32, &ratio1_3, &ratio1_3, &ratio3_8, &ratio3_8, &ratio3_8, 
&ratio15_32, &ratio15_32, &ratio15_32, &ratio1_2, &ratio1_2, &ratio9_16, &ratio9_16, &ratio2_3, &ratio2_3, &ratio3_4, &ratio3_4, &ratio3_4, 
&ratio15_16, &ratio15_16, &ratio15_16, &ratio1_1, &ratio1_1, &ratio9_8, &ratio9_8, &ratio4_3, &ratio4_3, &ratio3_2, &ratio3_2, &ratio3_2, 
&ratio15_8, &ratio15_8, &ratio15_8, &ratio2_1, &ratio2_1, &ratio9_4, &ratio9_4, &ratio8_3, &ratio8_3, &ratio3_1, &ratio3_1, &ratio3_1, 
&ratio15_4, &ratio15_4, &ratio15_4, &ratio4_1, &ratio4_1, &ratio9_2, &ratio9_2, &ratio16_3, &ratio16_3, &ratio6_1, &ratio6_1, &ratio6_1, 
&ratio15_2, &ratio15_2, &ratio15_2, &ratio8_1, &ratio8_1, &ratio9_1, &ratio9_1, &ratio32_3, &ratio32_3, &ratio12_1, &ratio12_1, &ratio12_1, 
&ratio15_1, &ratio15_1, &ratio15_1, &ratio16_1, &ratio16_1, &ratio18_1, &ratio18_1, &ratio64_3, &ratio64_3, &ratio24_1, &ratio24_1, &ratio24_1, 
&ratio30_1, &ratio30_1, &ratio30_1, &ratio32_1, &ratio32_1, &ratio36_1, &ratio36_1}; 

static const ScaleNote * const relmin75prime[128] = {&ratio3_64, &ratio3_64, &ratio3_64, &ratio3_64, &ratio3_64, &ratio15_256, &ratio15_256, &ratio15_256, &ratio1_16, &ratio1_16, &ratio5_64, &ratio5_64, &ratio5_64, 
&ratio5_64, &ratio3_32, &ratio3_32, &ratio3_32, &ratio3_32, &ratio3_32, &ratio15_128, &ratio15_128, &ratio15_128, &ratio1_8, &ratio1_8, &ratio5_32, 
&ratio5_32, &ratio5_32, &ratio5_32, &ratio3_16, &ratio3_16, &ratio3_16, &ratio3_16, &ratio3_16, &ratio15_64, &ratio15_64, &ratio15_64, &ratio1_4, 
&ratio1_4, &ratio5_16, &ratio5_16, &ratio5_16, &ratio5_16, &ratio3_8, &ratio3_8, &ratio3_8, &ratio3_8, &ratio3_8, &ratio15_32, &ratio15_32, 
&ratio15_32, &ratio1_2, &ratio1_2, &ratio5_8, &ratio5_8, &ratio5_8, &ratio5_8, &ratio3_4, &ratio3_4, &ratio3_4, &ratio3_4, &ratio3_4, 
&ratio15_16, &ratio15_16, &ratio15_16, &ratio1_1, &ratio1_1, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio3_2, &ratio3_2, &ratio3_2, 
&ratio3_2, &ratio3_2, &ratio15_8, &ratio15_8, &ratio15_8, &ratio2_1, &ratio2_1, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio3_1, 
&ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio15_4, &ratio15_4, &ratio15_4, &ratio4_1, &ratio4_1, &ratio5_1, &ratio5_1, &ratio5_1, 
&ratio5_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio15_2, &ratio15_2, &ratio15_2, &ratio8_1, &ratio8_1, &ratio10_1, 
&ratio10_1, &ratio10_1, &ratio10_1, &ratio12_1, &ratio12_1, &ratio12_1, &ratio12_1, &ratio12_1, &ratio15_1, &ratio15_1, &ratio15_1, &ratio16_1, 
&ratio16_1, &ratio20_1, &ratio20_1, &ratio20_1, &ratio20_1, &ratio24_1, &ratio24_1}; 

static const ScaleNote * const dim75prime[128] = {&ratio1_40, &ratio1_40, &ratio15_512, &ratio15_512, &ratio9_256, &ratio9_256, &ratio9_256, &ratio5_128, &ratio1_24, &ratio1_24, &ratio1_24, &ratio1_20, &ratio1_20, 
&ratio1_20, &ratio15_256, &ratio15_256, &ratio9_128, &ratio9_128, &ratio9_128, &ratio5_64, &ratio1_12, &ratio1_12, &ratio1_12, &ratio1_10, &ratio1_10, 
&ratio1_10, &ratio15_128, &ratio15_128, &ratio9_64, &ratio9_64, &ratio9_64, &ratio5_32, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_5, &ratio1_5, 
&ratio1_5, &ratio15_64, &ratio15_64, &ratio9_32, &ratio9_32, &ratio9_32, &ratio5_16, &ratio1_3, &ratio1_3, &ratio1_3, &ratio2_5, &ratio2_5, 
&ratio2_5, &ratio15_32, &ratio15_32, &ratio9_16, &ratio9_16, &ratio9_16, &ratio5_8, &ratio2_3, &ratio2_3, &ratio2_3, &ratio4_5, &ratio4_5, 
&ratio4_5, &ratio15_16, &ratio15_16, &ratio9_8, &ratio9_8, &ratio9_8, &ratio5_4, &ratio4_3, &ratio4_3, &ratio4_3, &ratio8_5, &ratio8_5, 
&ratio8_5, &ratio15_8, &ratio15_8, &ratio9_4, &ratio9_4, &ratio9_4, &ratio5_2, &ratio8_3, &ratio8_3, &ratio8_3, &ratio16_5, &ratio16_5, 
&ratio16_5, &ratio15_4, &ratio15_4, &ratio9_2, &ratio9_2, &ratio9_2, &ratio5_1, &ratio16_3, &ratio16_3, &ratio16_3, &ratio32_5, &ratio32_5, 
&ratio32_5, &ratio15_2, &ratio15_2, &ratio9_1, &ratio9_1, &ratio9_1, &ratio10_1, &ratio32_3, &ratio32_3, &ratio32_3, &ratio64_5, &ratio64_5, 
&ratio64_5, &ratio15_1, &ratio15_1, &ratio18_1, &ratio18_1, &ratio18_1, &ratio20_1, &ratio64_3, &ratio64_3, &ratio64_3, &ratio128_5, &ratio128_5, 
&ratio128_5, &ratio30_1, &ratio30_1, &ratio36_1, &ratio36_1, &ratio36_1, &ratio40_1}; 

static const ScaleNote * const majmaj75prime[128] = {&ratio3_128, &ratio15_512, &ratio15_512, &ratio15_512, &ratio1_32, &ratio1_32, &ratio5_128, &ratio5_128, &ratio5_128, &ratio5_128, &ratio3_64, &ratio3_64, &ratio3_64, 
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



static const ScaleNote * const majTriad[128] = {&ratio3_128, &ratio3_128, &ratio3_128, &ratio3_128, &ratio1_32, &ratio1_32, &ratio5_128, &ratio5_128, &ratio5_128, &ratio5_128, &ratio3_64, &ratio3_64, &ratio3_64, 
&ratio3_64, &ratio3_64, &ratio3_64, &ratio1_16, &ratio1_16, &ratio5_64, &ratio5_64, &ratio5_64, &ratio5_64, &ratio3_32, &ratio3_32, &ratio3_32, 
&ratio3_32, &ratio3_32, &ratio3_32, &ratio1_8, &ratio1_8, &ratio5_32, &ratio5_32, &ratio5_32, &ratio5_32, &ratio3_16, &ratio3_16, &ratio3_16, 
&ratio3_16, &ratio3_16, &ratio3_16, &ratio1_4, &ratio1_4, &ratio5_16, &ratio5_16, &ratio5_16, &ratio5_16, &ratio3_8, &ratio3_8, &ratio3_8, 
&ratio3_8, &ratio3_8, &ratio3_8, &ratio1_2, &ratio1_2, &ratio5_8, &ratio5_8, &ratio5_8, &ratio5_8, &ratio3_4, &ratio3_4, &ratio3_4, 
&ratio3_4, &ratio3_4, &ratio3_4, &ratio1_1, &ratio1_1, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio3_2, &ratio3_2, &ratio3_2, 
&ratio3_2, &ratio3_2, &ratio3_2, &ratio2_1, &ratio2_1, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio3_1, &ratio3_1, &ratio3_1, 
&ratio3_1, &ratio3_1, &ratio3_1, &ratio4_1, &ratio4_1, &ratio5_1, &ratio5_1, &ratio5_1, &ratio5_1, &ratio6_1, &ratio6_1, &ratio6_1, 
&ratio6_1, &ratio6_1, &ratio6_1, &ratio8_1, &ratio8_1, &ratio10_1, &ratio10_1, &ratio10_1, &ratio10_1, &ratio12_1, &ratio12_1, &ratio12_1, 
&ratio12_1, &ratio12_1, &ratio12_1, &ratio16_1, &ratio16_1, &ratio20_1, &ratio20_1, &ratio20_1, &ratio20_1, &ratio24_1, &ratio24_1, &ratio24_1, 
&ratio24_1, &ratio24_1, &ratio24_1, &ratio32_1, &ratio32_1, &ratio40_1, &ratio40_1}; 

static const ScaleNote * const majTriad1stInv[128] = {&ratio1_40, &ratio1_40, &ratio1_40, &ratio1_40, &ratio1_32, &ratio1_32, &ratio3_80, &ratio3_80, &ratio3_80, &ratio3_80, &ratio1_20, &ratio1_20, &ratio1_20, 
&ratio1_20, &ratio1_20, &ratio1_20, &ratio1_16, &ratio1_16, &ratio3_40, &ratio3_40, &ratio3_40, &ratio3_40, &ratio1_10, &ratio1_10, &ratio1_10, 
&ratio1_10, &ratio1_10, &ratio1_10, &ratio1_8, &ratio1_8, &ratio3_20, &ratio3_20, &ratio3_20, &ratio3_20, &ratio1_5, &ratio1_5, &ratio1_5, 
&ratio1_5, &ratio1_5, &ratio1_5, &ratio1_4, &ratio1_4, &ratio3_10, &ratio3_10, &ratio3_10, &ratio3_10, &ratio2_5, &ratio2_5, &ratio2_5, 
&ratio2_5, &ratio2_5, &ratio2_5, &ratio1_2, &ratio1_2, &ratio3_5, &ratio3_5, &ratio3_5, &ratio3_5, &ratio4_5, &ratio4_5, &ratio4_5, 
&ratio4_5, &ratio4_5, &ratio4_5, &ratio1_1, &ratio1_1, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio8_5, &ratio8_5, &ratio8_5, 
&ratio8_5, &ratio8_5, &ratio8_5, &ratio2_1, &ratio2_1, &ratio12_5, &ratio12_5, &ratio12_5, &ratio12_5, &ratio16_5, &ratio16_5, &ratio16_5, 
&ratio16_5, &ratio16_5, &ratio16_5, &ratio4_1, &ratio4_1, &ratio24_5, &ratio24_5, &ratio24_5, &ratio24_5, &ratio32_5, &ratio32_5, &ratio32_5, 
&ratio32_5, &ratio32_5, &ratio32_5, &ratio8_1, &ratio8_1, &ratio48_5, &ratio48_5, &ratio48_5, &ratio48_5, &ratio64_5, &ratio64_5, &ratio64_5, 
&ratio64_5, &ratio64_5, &ratio64_5, &ratio16_1, &ratio16_1, &ratio96_5, &ratio96_5, &ratio96_5, &ratio96_5, &ratio128_5, &ratio128_5, &ratio128_5, 
&ratio128_5, &ratio128_5, &ratio128_5, &ratio32_1, &ratio32_1, &ratio192_5, &ratio192_5}; 

static const ScaleNote * const majTriad2ndInv[128] = {&ratio5_192, &ratio5_192, &ratio5_192, &ratio5_192, &ratio1_32, &ratio1_32, &ratio1_32, &ratio1_24, &ratio1_24, &ratio1_24, &ratio1_24, &ratio5_96, &ratio5_96, 
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

static const ScaleNote * const minTriad[128] = {&ratio3_128, &ratio3_128, &ratio3_128, &ratio3_128, &ratio1_32, &ratio1_32, &ratio3_80, &ratio3_80, &ratio3_80, &ratio3_80, &ratio3_64, &ratio3_64, &ratio3_64, 
&ratio3_64, &ratio3_64, &ratio3_64, &ratio1_16, &ratio1_16, &ratio3_40, &ratio3_40, &ratio3_40, &ratio3_40, &ratio3_32, &ratio3_32, &ratio3_32, 
&ratio3_32, &ratio3_32, &ratio3_32, &ratio1_8, &ratio1_8, &ratio3_20, &ratio3_20, &ratio3_20, &ratio3_20, &ratio3_16, &ratio3_16, &ratio3_16, 
&ratio3_16, &ratio3_16, &ratio3_16, &ratio1_4, &ratio1_4, &ratio3_10, &ratio3_10, &ratio3_10, &ratio3_10, &ratio3_8, &ratio3_8, &ratio3_8, 
&ratio3_8, &ratio3_8, &ratio3_8, &ratio1_2, &ratio1_2, &ratio3_5, &ratio3_5, &ratio3_5, &ratio3_5, &ratio3_4, &ratio3_4, &ratio3_4, 
&ratio3_4, &ratio3_4, &ratio3_4, &ratio1_1, &ratio1_1, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio3_2, &ratio3_2, &ratio3_2, 
&ratio3_2, &ratio3_2, &ratio3_2, &ratio2_1, &ratio2_1, &ratio12_5, &ratio12_5, &ratio12_5, &ratio12_5, &ratio3_1, &ratio3_1, &ratio3_1, 
&ratio3_1, &ratio3_1, &ratio3_1, &ratio4_1, &ratio4_1, &ratio24_5, &ratio24_5, &ratio24_5, &ratio24_5, &ratio6_1, &ratio6_1, &ratio6_1, 
&ratio6_1, &ratio6_1, &ratio6_1, &ratio8_1, &ratio8_1, &ratio48_5, &ratio48_5, &ratio48_5, &ratio48_5, &ratio12_1, &ratio12_1, &ratio12_1, 
&ratio12_1, &ratio12_1, &ratio12_1, &ratio16_1, &ratio16_1, &ratio96_5, &ratio96_5, &ratio96_5, &ratio96_5, &ratio24_1, &ratio24_1, &ratio24_1, 
&ratio24_1, &ratio24_1, &ratio24_1, &ratio32_1, &ratio32_1, &ratio192_5, &ratio192_5}; 

static const ScaleNote * const minTriad2ndInv[128] = {&ratio1_40, &ratio1_40, &ratio1_40, &ratio1_40, &ratio1_32, &ratio1_32, &ratio1_32, &ratio1_24, &ratio1_24, &ratio1_24, &ratio1_24, &ratio1_20, &ratio1_20, 
&ratio1_20, &ratio1_20, &ratio1_20, &ratio1_16, &ratio1_16, &ratio1_16, &ratio1_12, &ratio1_12, &ratio1_12, &ratio1_12, &ratio1_10, &ratio1_10, 
&ratio1_10, &ratio1_10, &ratio1_10, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_5, &ratio1_5, 
&ratio1_5, &ratio1_5, &ratio1_5, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio2_5, &ratio2_5, 
&ratio2_5, &ratio2_5, &ratio2_5, &ratio1_2, &ratio1_2, &ratio1_2, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio4_5, &ratio4_5, 
&ratio4_5, &ratio4_5, &ratio4_5, &ratio1_1, &ratio1_1, &ratio1_1, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio8_5, &ratio8_5, 
&ratio8_5, &ratio8_5, &ratio8_5, &ratio2_1, &ratio2_1, &ratio2_1, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio16_5, &ratio16_5, 
&ratio16_5, &ratio16_5, &ratio16_5, &ratio4_1, &ratio4_1, &ratio4_1, &ratio16_3, &ratio16_3, &ratio16_3, &ratio16_3, &ratio32_5, &ratio32_5, 
&ratio32_5, &ratio32_5, &ratio32_5, &ratio8_1, &ratio8_1, &ratio8_1, &ratio32_3, &ratio32_3, &ratio32_3, &ratio32_3, &ratio64_5, &ratio64_5, 
&ratio64_5, &ratio64_5, &ratio64_5, &ratio16_1, &ratio16_1, &ratio16_1, &ratio64_3, &ratio64_3, &ratio64_3, &ratio64_3, &ratio128_5, &ratio128_5, 
&ratio128_5, &ratio128_5, &ratio128_5, &ratio32_1, &ratio32_1, &ratio32_1, &ratio128_3}; 

static const ScaleNote * const MinTriad1stInv[128] = {&ratio5_192, &ratio5_192, &ratio5_192, &ratio5_192, &ratio1_32, &ratio1_32, &ratio5_128, &ratio5_128, &ratio5_128, &ratio5_128, &ratio5_96, &ratio5_96, &ratio5_96, 
&ratio5_96, &ratio5_96, &ratio5_96, &ratio1_16, &ratio1_16, &ratio5_64, &ratio5_64, &ratio5_64, &ratio5_64, &ratio5_48, &ratio5_48, &ratio5_48, 
&ratio5_48, &ratio5_48, &ratio5_48, &ratio1_8, &ratio1_8, &ratio5_32, &ratio5_32, &ratio5_32, &ratio5_32, &ratio5_24, &ratio5_24, &ratio5_24, 
&ratio5_24, &ratio5_24, &ratio5_24, &ratio1_4, &ratio1_4, &ratio5_16, &ratio5_16, &ratio5_16, &ratio5_16, &ratio5_12, &ratio5_12, &ratio5_12, 
&ratio5_12, &ratio5_12, &ratio5_12, &ratio1_2, &ratio1_2, &ratio5_8, &ratio5_8, &ratio5_8, &ratio5_8, &ratio5_6, &ratio5_6, &ratio5_6, 
&ratio5_6, &ratio5_6, &ratio5_6, &ratio1_1, &ratio1_1, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_3, &ratio5_3, &ratio5_3, 
&ratio5_3, &ratio5_3, &ratio5_3, &ratio2_1, &ratio2_1, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio10_3, &ratio10_3, &ratio10_3, 
&ratio10_3, &ratio10_3, &ratio10_3, &ratio4_1, &ratio4_1, &ratio5_1, &ratio5_1, &ratio5_1, &ratio5_1, &ratio20_3, &ratio20_3, &ratio20_3, 
&ratio20_3, &ratio20_3, &ratio20_3, &ratio8_1, &ratio8_1, &ratio10_1, &ratio10_1, &ratio10_1, &ratio10_1, &ratio40_3, &ratio40_3, &ratio40_3, 
&ratio40_3, &ratio40_3, &ratio40_3, &ratio16_1, &ratio16_1, &ratio20_1, &ratio20_1, &ratio20_1, &ratio20_1, &ratio80_3, &ratio80_3, &ratio80_3, 
&ratio80_3, &ratio80_3, &ratio80_3, &ratio32_1, &ratio32_1, &ratio40_1, &ratio40_1}; 

static const ScaleNote * const quartalTriad[128] = {&ratio1_48, &ratio1_48, &ratio1_48, &ratio1_48, &ratio1_32, &ratio1_32, &ratio9_256, &ratio9_256, &ratio1_24, &ratio1_24, &ratio1_24, &ratio1_24, &ratio1_24, 
&ratio1_24, &ratio1_24, &ratio1_24, &ratio1_16, &ratio1_16, &ratio9_128, &ratio9_128, &ratio1_12, &ratio1_12, &ratio1_12, &ratio1_12, &ratio1_12, 
&ratio1_12, &ratio1_12, &ratio1_12, &ratio1_8, &ratio1_8, &ratio9_64, &ratio9_64, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, 
&ratio1_6, &ratio1_6, &ratio1_6, &ratio1_4, &ratio1_4, &ratio9_32, &ratio9_32, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, 
&ratio1_3, &ratio1_3, &ratio1_3, &ratio1_2, &ratio1_2, &ratio9_16, &ratio9_16, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, 
&ratio2_3, &ratio2_3, &ratio2_3, &ratio1_1, &ratio1_1, &ratio9_8, &ratio9_8, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, 
&ratio4_3, &ratio4_3, &ratio4_3, &ratio2_1, &ratio2_1, &ratio9_4, &ratio9_4, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, 
&ratio8_3, &ratio8_3, &ratio8_3, &ratio4_1, &ratio4_1, &ratio9_2, &ratio9_2, &ratio16_3, &ratio16_3, &ratio16_3, &ratio16_3, &ratio16_3, 
&ratio16_3, &ratio16_3, &ratio16_3, &ratio8_1, &ratio8_1, &ratio9_1, &ratio9_1, &ratio32_3, &ratio32_3, &ratio32_3, &ratio32_3, &ratio32_3, 
&ratio32_3, &ratio32_3, &ratio32_3, &ratio16_1, &ratio16_1, &ratio18_1, &ratio18_1, &ratio64_3, &ratio64_3, &ratio64_3, &ratio64_3, &ratio64_3, 
&ratio64_3, &ratio64_3, &ratio64_3, &ratio32_1, &ratio32_1, &ratio36_1, &ratio36_1}; 

static const ScaleNote * const quartalTriad1stInv[128] = {&ratio1_36, &ratio1_36, &ratio1_36, &ratio1_36, &ratio1_32, &ratio1_32, &ratio1_32, &ratio1_24, &ratio1_24, &ratio1_24, &ratio1_24, &ratio1_18, &ratio1_18, 
&ratio1_18, &ratio1_18, &ratio1_18, &ratio1_16, &ratio1_16, &ratio1_16, &ratio1_12, &ratio1_12, &ratio1_12, &ratio1_12, &ratio1_9, &ratio1_9, 
&ratio1_9, &ratio1_9, &ratio1_9, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, &ratio2_9, &ratio2_9, 
&ratio2_9, &ratio2_9, &ratio2_9, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio4_9, &ratio4_9, 
&ratio4_9, &ratio4_9, &ratio4_9, &ratio1_2, &ratio1_2, &ratio1_2, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio8_9, &ratio8_9, 
&ratio8_9, &ratio8_9, &ratio8_9, &ratio1_1, &ratio1_1, &ratio1_1, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio16_9, &ratio16_9, 
&ratio16_9, &ratio16_9, &ratio16_9, &ratio2_1, &ratio2_1, &ratio2_1, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio32_9, &ratio32_9, 
&ratio32_9, &ratio32_9, &ratio32_9, &ratio4_1, &ratio4_1, &ratio4_1, &ratio16_3, &ratio16_3, &ratio16_3, &ratio16_3, &ratio64_9, &ratio64_9, 
&ratio64_9, &ratio64_9, &ratio64_9, &ratio8_1, &ratio8_1, &ratio8_1, &ratio32_3, &ratio32_3, &ratio32_3, &ratio32_3, &ratio128_9, &ratio128_9, 
&ratio128_9, &ratio128_9, &ratio128_9, &ratio16_1, &ratio16_1, &ratio16_1, &ratio64_3, &ratio64_3, &ratio64_3, &ratio64_3, &ratio256_9, &ratio256_9, 
&ratio256_9, &ratio256_9, &ratio256_9, &ratio32_1, &ratio32_1, &ratio32_1, &ratio128_3}; 



static const ScaleNote * const subDom7thRotate[128] = {&ratio5_192, &ratio5_192, &ratio5_192, &ratio5_192, &ratio1_32, &ratio1_32, &ratio9_256, &ratio9_256, &ratio25_576, &ratio25_576, &ratio25_576, &ratio5_96, &ratio5_96, 
&ratio5_96, &ratio5_96, &ratio5_96, &ratio1_16, &ratio1_16, &ratio9_128, &ratio9_128, &ratio25_288, &ratio25_288, &ratio25_288, &ratio5_48, &ratio5_48, 
&ratio5_48, &ratio5_48, &ratio5_48, &ratio1_8, &ratio1_8, &ratio9_64, &ratio9_64, &ratio25_144, &ratio25_144, &ratio25_144, &ratio5_24, &ratio5_24, 
&ratio5_24, &ratio5_24, &ratio5_24, &ratio1_4, &ratio1_4, &ratio9_32, &ratio9_32, &ratio25_72, &ratio25_72, &ratio25_72, &ratio5_12, &ratio5_12, 
&ratio5_12, &ratio5_12, &ratio5_12, &ratio1_2, &ratio1_2, &ratio9_16, &ratio9_16, &ratio25_36, &ratio25_36, &ratio25_36, &ratio5_6, &ratio5_6, 
&ratio5_6, &ratio5_6, &ratio5_6, &ratio1_1, &ratio1_1, &ratio9_8, &ratio9_8, &ratio25_18, &ratio25_18, &ratio25_18, &ratio5_3, &ratio5_3, 
&ratio5_3, &ratio5_3, &ratio5_3, &ratio2_1, &ratio2_1, &ratio9_4, &ratio9_4, &ratio25_9, &ratio25_9, &ratio25_9, &ratio10_3, &ratio10_3, 
&ratio10_3, &ratio10_3, &ratio10_3, &ratio4_1, &ratio4_1, &ratio9_2, &ratio9_2, &ratio50_9, &ratio50_9, &ratio50_9, &ratio20_3, &ratio20_3, 
&ratio20_3, &ratio20_3, &ratio20_3, &ratio8_1, &ratio8_1, &ratio9_1, &ratio9_1, &ratio100_9, &ratio100_9, &ratio100_9, &ratio40_3, &ratio40_3, 
&ratio40_3, &ratio40_3, &ratio40_3, &ratio16_1, &ratio16_1, &ratio18_1, &ratio18_1, &ratio200_9, &ratio200_9, &ratio200_9, &ratio80_3, &ratio80_3, 
&ratio80_3, &ratio80_3, &ratio80_3, &ratio32_1, &ratio32_1, &ratio36_1, &ratio36_1}; 

static const ScaleNote * const min7th[128] = {&ratio3_128, &ratio3_128, &ratio3_128, &ratio3_128, &ratio1_32, &ratio1_32, &ratio9_256, &ratio3_80, &ratio3_80, &ratio3_80, &ratio3_64, &ratio3_64, &ratio3_64, 
&ratio3_64, &ratio3_64, &ratio3_64, &ratio1_16, &ratio1_16, &ratio9_128, &ratio3_40, &ratio3_40, &ratio3_40, &ratio3_32, &ratio3_32, &ratio3_32, 
&ratio3_32, &ratio3_32, &ratio3_32, &ratio1_8, &ratio1_8, &ratio9_64, &ratio3_20, &ratio3_20, &ratio3_20, &ratio3_16, &ratio3_16, &ratio3_16, 
&ratio3_16, &ratio3_16, &ratio3_16, &ratio1_4, &ratio1_4, &ratio9_32, &ratio3_10, &ratio3_10, &ratio3_10, &ratio3_8, &ratio3_8, &ratio3_8, 
&ratio3_8, &ratio3_8, &ratio3_8, &ratio1_2, &ratio1_2, &ratio9_16, &ratio3_5, &ratio3_5, &ratio3_5, &ratio3_4, &ratio3_4, &ratio3_4, 
&ratio3_4, &ratio3_4, &ratio3_4, &ratio1_1, &ratio1_1, &ratio9_8, &ratio6_5, &ratio6_5, &ratio6_5, &ratio3_2, &ratio3_2, &ratio3_2, 
&ratio3_2, &ratio3_2, &ratio3_2, &ratio2_1, &ratio2_1, &ratio9_4, &ratio12_5, &ratio12_5, &ratio12_5, &ratio3_1, &ratio3_1, &ratio3_1, 
&ratio3_1, &ratio3_1, &ratio3_1, &ratio4_1, &ratio4_1, &ratio9_2, &ratio24_5, &ratio24_5, &ratio24_5, &ratio6_1, &ratio6_1, &ratio6_1, 
&ratio6_1, &ratio6_1, &ratio6_1, &ratio8_1, &ratio8_1, &ratio9_1, &ratio48_5, &ratio48_5, &ratio48_5, &ratio12_1, &ratio12_1, &ratio12_1, 
&ratio12_1, &ratio12_1, &ratio12_1, &ratio16_1, &ratio16_1, &ratio18_1, &ratio96_5, &ratio96_5, &ratio96_5, &ratio24_1, &ratio24_1, &ratio24_1, 
&ratio24_1, &ratio24_1, &ratio24_1, &ratio32_1, &ratio32_1, &ratio36_1, &ratio192_5}; 

static const ScaleNote * const dom7thRotate[128] = {&ratio5_192, &ratio5_192, &ratio5_192, &ratio5_192, &ratio1_32, &ratio1_32, &ratio3_80, &ratio3_80, &ratio3_80, &ratio3_80, &ratio3_64, &ratio3_64, &ratio5_96, 
&ratio5_96, &ratio5_96, &ratio5_96, &ratio1_16, &ratio1_16, &ratio3_40, &ratio3_40, &ratio3_40, &ratio3_40, &ratio3_32, &ratio3_32, &ratio5_48, 
&ratio5_48, &ratio5_48, &ratio5_48, &ratio1_8, &ratio1_8, &ratio3_20, &ratio3_20, &ratio3_20, &ratio3_20, &ratio3_16, &ratio3_16, &ratio5_24, 
&ratio5_24, &ratio5_24, &ratio5_24, &ratio1_4, &ratio1_4, &ratio3_10, &ratio3_10, &ratio3_10, &ratio3_10, &ratio3_8, &ratio3_8, &ratio5_12, 
&ratio5_12, &ratio5_12, &ratio5_12, &ratio1_2, &ratio1_2, &ratio3_5, &ratio3_5, &ratio3_5, &ratio3_5, &ratio3_4, &ratio3_4, &ratio5_6, 
&ratio5_6, &ratio5_6, &ratio5_6, &ratio1_1, &ratio1_1, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio3_2, &ratio3_2, &ratio5_3, 
&ratio5_3, &ratio5_3, &ratio5_3, &ratio2_1, &ratio2_1, &ratio12_5, &ratio12_5, &ratio12_5, &ratio12_5, &ratio3_1, &ratio3_1, &ratio10_3, 
&ratio10_3, &ratio10_3, &ratio10_3, &ratio4_1, &ratio4_1, &ratio24_5, &ratio24_5, &ratio24_5, &ratio24_5, &ratio6_1, &ratio6_1, &ratio20_3, 
&ratio20_3, &ratio20_3, &ratio20_3, &ratio8_1, &ratio8_1, &ratio48_5, &ratio48_5, &ratio48_5, &ratio48_5, &ratio12_1, &ratio12_1, &ratio40_3, 
&ratio40_3, &ratio40_3, &ratio40_3, &ratio16_1, &ratio16_1, &ratio96_5, &ratio96_5, &ratio96_5, &ratio96_5, &ratio24_1, &ratio24_1, &ratio80_3, 
&ratio80_3, &ratio80_3, &ratio80_3, &ratio32_1, &ratio32_1, &ratio192_5, &ratio192_5}; 

static const ScaleNote * const min7th2ndInv[128] = {&ratio1_40, &ratio1_40, &ratio1_40, &ratio1_40, &ratio1_32, &ratio1_32, &ratio3_80, &ratio3_80, &ratio3_80, &ratio3_80, &ratio3_64, &ratio3_64, &ratio1_20, 
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

static const ScaleNote * const maj7th1stInv[128] = {&ratio1_40, &ratio1_40, &ratio1_40, &ratio1_40, &ratio1_32, &ratio1_32, &ratio5_128, &ratio5_128, &ratio5_128, &ratio5_128, &ratio3_64, &ratio3_64, &ratio1_20, 
&ratio1_20, &ratio1_20, &ratio1_20, &ratio1_16, &ratio1_16, &ratio5_64, &ratio5_64, &ratio5_64, &ratio5_64, &ratio3_32, &ratio3_32, &ratio1_10, 
&ratio1_10, &ratio1_10, &ratio1_10, &ratio1_8, &ratio1_8, &ratio5_32, &ratio5_32, &ratio5_32, &ratio5_32, &ratio3_16, &ratio3_16, &ratio1_5, 
&ratio1_5, &ratio1_5, &ratio1_5, &ratio1_4, &ratio1_4, &ratio5_16, &ratio5_16, &ratio5_16, &ratio5_16, &ratio3_8, &ratio3_8, &ratio2_5, 
&ratio2_5, &ratio2_5, &ratio2_5, &ratio1_2, &ratio1_2, &ratio5_8, &ratio5_8, &ratio5_8, &ratio5_8, &ratio3_4, &ratio3_4, &ratio4_5, 
&ratio4_5, &ratio4_5, &ratio4_5, &ratio1_1, &ratio1_1, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio3_2, &ratio3_2, &ratio8_5, 
&ratio8_5, &ratio8_5, &ratio8_5, &ratio2_1, &ratio2_1, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio3_1, &ratio3_1, &ratio16_5, 
&ratio16_5, &ratio16_5, &ratio16_5, &ratio4_1, &ratio4_1, &ratio5_1, &ratio5_1, &ratio5_1, &ratio5_1, &ratio6_1, &ratio6_1, &ratio32_5, 
&ratio32_5, &ratio32_5, &ratio32_5, &ratio8_1, &ratio8_1, &ratio10_1, &ratio10_1, &ratio10_1, &ratio10_1, &ratio12_1, &ratio12_1, &ratio64_5, 
&ratio64_5, &ratio64_5, &ratio64_5, &ratio16_1, &ratio16_1, &ratio20_1, &ratio20_1, &ratio20_1, &ratio20_1, &ratio24_1, &ratio24_1, &ratio128_5, 
&ratio128_5, &ratio128_5, &ratio128_5, &ratio32_1, &ratio32_1, &ratio40_1, &ratio40_1}; 

static const ScaleNote * const maj7th[128] = {&ratio3_128, &ratio15_512, &ratio15_512, &ratio15_512, &ratio1_32, &ratio1_32, &ratio5_128, &ratio5_128, &ratio5_128, &ratio5_128, &ratio3_64, &ratio3_64, &ratio3_64, 
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

static const ScaleNote * const dom7th[128] = {&ratio3_128, &ratio9_320, &ratio9_320, &ratio9_320, &ratio1_32, &ratio1_32, &ratio5_128, &ratio5_128, &ratio5_128, &ratio5_128, &ratio3_64, &ratio3_64, &ratio3_64, 
&ratio9_160, &ratio9_160, &ratio9_160, &ratio1_16, &ratio1_16, &ratio5_64, &ratio5_64, &ratio5_64, &ratio5_64, &ratio3_32, &ratio3_32, &ratio3_32, 
&ratio9_80, &ratio9_80, &ratio9_80, &ratio1_8, &ratio1_8, &ratio5_32, &ratio5_32, &ratio5_32, &ratio5_32, &ratio3_16, &ratio3_16, &ratio3_16, 
&ratio9_40, &ratio9_40, &ratio9_40, &ratio1_4, &ratio1_4, &ratio5_16, &ratio5_16, &ratio5_16, &ratio5_16, &ratio3_8, &ratio3_8, &ratio3_8, 
&ratio9_20, &ratio9_20, &ratio9_20, &ratio1_2, &ratio1_2, &ratio5_8, &ratio5_8, &ratio5_8, &ratio5_8, &ratio3_4, &ratio3_4, &ratio3_4, 
&ratio9_10, &ratio9_10, &ratio9_10, &ratio1_1, &ratio1_1, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio3_2, &ratio3_2, &ratio3_2, 
&ratio9_5, &ratio9_5, &ratio9_5, &ratio2_1, &ratio2_1, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio3_1, &ratio3_1, &ratio3_1, 
&ratio18_5, &ratio18_5, &ratio18_5, &ratio4_1, &ratio4_1, &ratio5_1, &ratio5_1, &ratio5_1, &ratio5_1, &ratio6_1, &ratio6_1, &ratio6_1, 
&ratio36_5, &ratio36_5, &ratio36_5, &ratio8_1, &ratio8_1, &ratio10_1, &ratio10_1, &ratio10_1, &ratio10_1, &ratio12_1, &ratio12_1, &ratio12_1, 
&ratio72_5, &ratio72_5, &ratio72_5, &ratio16_1, &ratio16_1, &ratio20_1, &ratio20_1, &ratio20_1, &ratio20_1, &ratio24_1, &ratio24_1, &ratio24_1, 
&ratio144_5, &ratio144_5, &ratio144_5, &ratio32_1, &ratio32_1, &ratio40_1, &ratio40_1}; 

static const ScaleNote * const harmDom7th[128] = {&ratio3_128, &ratio7_256, &ratio7_256, &ratio7_256, &ratio1_32, &ratio1_32, &ratio5_128, &ratio5_128, &ratio5_128, &ratio5_128, &ratio3_64, &ratio3_64, &ratio3_64, 
&ratio7_128, &ratio7_128, &ratio7_128, &ratio1_16, &ratio1_16, &ratio5_64, &ratio5_64, &ratio5_64, &ratio5_64, &ratio3_32, &ratio3_32, &ratio3_32, 
&ratio7_64, &ratio7_64, &ratio7_64, &ratio1_8, &ratio1_8, &ratio5_32, &ratio5_32, &ratio5_32, &ratio5_32, &ratio3_16, &ratio3_16, &ratio3_16, 
&ratio7_32, &ratio7_32, &ratio7_32, &ratio1_4, &ratio1_4, &ratio5_16, &ratio5_16, &ratio5_16, &ratio5_16, &ratio3_8, &ratio3_8, &ratio3_8, 
&ratio7_16, &ratio7_16, &ratio7_16, &ratio1_2, &ratio1_2, &ratio5_8, &ratio5_8, &ratio5_8, &ratio5_8, &ratio3_4, &ratio3_4, &ratio3_4, 
&ratio7_8, &ratio7_8, &ratio7_8, &ratio1_1, &ratio1_1, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio3_2, &ratio3_2, &ratio3_2, 
&ratio7_4, &ratio7_4, &ratio7_4, &ratio2_1, &ratio2_1, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio3_1, &ratio3_1, &ratio3_1, 
&ratio7_2, &ratio7_2, &ratio7_2, &ratio4_1, &ratio4_1, &ratio5_1, &ratio5_1, &ratio5_1, &ratio5_1, &ratio6_1, &ratio6_1, &ratio6_1, 
&ratio7_1, &ratio7_1, &ratio7_1, &ratio8_1, &ratio8_1, &ratio10_1, &ratio10_1, &ratio10_1, &ratio10_1, &ratio12_1, &ratio12_1, &ratio12_1, 
&ratio14_1, &ratio14_1, &ratio14_1, &ratio16_1, &ratio16_1, &ratio20_1, &ratio20_1, &ratio20_1, &ratio20_1, &ratio24_1, &ratio24_1, &ratio24_1, 
&ratio28_1, &ratio28_1, &ratio28_1, &ratio32_1, &ratio32_1, &ratio40_1, &ratio40_1}; 

static const ScaleNote * const min7th1stInv[128] = {&ratio5_192, &ratio5_192, &ratio5_192, &ratio5_192, &ratio1_32, &ratio1_32, &ratio5_128, &ratio5_128, &ratio5_128, &ratio5_128, &ratio3_64, &ratio3_64, &ratio5_96, 
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

static const ScaleNote * const maj7th2ndInv[128] = {&ratio5_192, &ratio5_192, &ratio5_192, &ratio5_192, &ratio1_32, &ratio1_32, &ratio5_128, &ratio5_128, &ratio1_24, &ratio1_24, &ratio1_24, &ratio5_96, &ratio5_96, 
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

static const ScaleNote * const harmDom7th2ndInv[128] = {&ratio5_192, &ratio5_192, &ratio5_192, &ratio5_192, &ratio1_32, &ratio1_32, &ratio7_192, &ratio7_192, &ratio1_24, &ratio1_24, &ratio1_24, &ratio5_96, &ratio5_96, 
&ratio5_96, &ratio5_96, &ratio5_96, &ratio1_16, &ratio1_16, &ratio7_96, &ratio7_96, &ratio1_12, &ratio1_12, &ratio1_12, &ratio5_48, &ratio5_48, 
&ratio5_48, &ratio5_48, &ratio5_48, &ratio1_8, &ratio1_8, &ratio7_48, &ratio7_48, &ratio1_6, &ratio1_6, &ratio1_6, &ratio5_24, &ratio5_24, 
&ratio5_24, &ratio5_24, &ratio5_24, &ratio1_4, &ratio1_4, &ratio7_24, &ratio7_24, &ratio1_3, &ratio1_3, &ratio1_3, &ratio5_12, &ratio5_12, 
&ratio5_12, &ratio5_12, &ratio5_12, &ratio1_2, &ratio1_2, &ratio7_12, &ratio7_12, &ratio2_3, &ratio2_3, &ratio2_3, &ratio5_6, &ratio5_6, 
&ratio5_6, &ratio5_6, &ratio5_6, &ratio1_1, &ratio1_1, &ratio7_6, &ratio7_6, &ratio4_3, &ratio4_3, &ratio4_3, &ratio5_3, &ratio5_3, 
&ratio5_3, &ratio5_3, &ratio5_3, &ratio2_1, &ratio2_1, &ratio7_3, &ratio7_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio10_3, &ratio10_3, 
&ratio10_3, &ratio10_3, &ratio10_3, &ratio4_1, &ratio4_1, &ratio14_3, &ratio14_3, &ratio16_3, &ratio16_3, &ratio16_3, &ratio20_3, &ratio20_3, 
&ratio20_3, &ratio20_3, &ratio20_3, &ratio8_1, &ratio8_1, &ratio28_3, &ratio28_3, &ratio32_3, &ratio32_3, &ratio32_3, &ratio40_3, &ratio40_3, 
&ratio40_3, &ratio40_3, &ratio40_3, &ratio16_1, &ratio16_1, &ratio56_3, &ratio56_3, &ratio64_3, &ratio64_3, &ratio64_3, &ratio80_3, &ratio80_3, 
&ratio80_3, &ratio80_3, &ratio80_3, &ratio32_1, &ratio32_1, &ratio112_3, &ratio112_3}; 

static const ScaleNote * const min7th3rdInv[128] = {&ratio5_192, &ratio5_192, &ratio5_192, &ratio5_192, &ratio1_32, &ratio5_144, &ratio5_144, &ratio1_24, &ratio1_24, &ratio1_24, &ratio1_24, &ratio5_96, &ratio5_96, 
&ratio5_96, &ratio5_96, &ratio5_96, &ratio1_16, &ratio5_72, &ratio5_72, &ratio1_12, &ratio1_12, &ratio1_12, &ratio1_12, &ratio5_48, &ratio5_48, 
&ratio5_48, &ratio5_48, &ratio5_48, &ratio1_8, &ratio5_36, &ratio5_36, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, &ratio5_24, &ratio5_24, 
&ratio5_24, &ratio5_24, &ratio5_24, &ratio1_4, &ratio5_18, &ratio5_18, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio5_12, &ratio5_12, 
&ratio5_12, &ratio5_12, &ratio5_12, &ratio1_2, &ratio5_9, &ratio5_9, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio5_6, &ratio5_6, 
&ratio5_6, &ratio5_6, &ratio5_6, &ratio1_1, &ratio10_9, &ratio10_9, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio5_3, &ratio5_3, 
&ratio5_3, &ratio5_3, &ratio5_3, &ratio2_1, &ratio20_9, &ratio20_9, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio10_3, &ratio10_3, 
&ratio10_3, &ratio10_3, &ratio10_3, &ratio4_1, &ratio40_9, &ratio40_9, &ratio16_3, &ratio16_3, &ratio16_3, &ratio16_3, &ratio20_3, &ratio20_3, 
&ratio20_3, &ratio20_3, &ratio20_3, &ratio8_1, &ratio80_9, &ratio80_9, &ratio32_3, &ratio32_3, &ratio32_3, &ratio32_3, &ratio40_3, &ratio40_3, 
&ratio40_3, &ratio40_3, &ratio40_3, &ratio16_1, &ratio160_9, &ratio160_9, &ratio64_3, &ratio64_3, &ratio64_3, &ratio64_3, &ratio80_3, &ratio80_3, 
&ratio80_3, &ratio80_3, &ratio80_3, &ratio32_1, &ratio320_9, &ratio320_9, &ratio128_3}; 

static const ScaleNote * const maj7th3rdInv[128] = {&ratio1_40, &ratio1_40, &ratio1_40, &ratio1_40, &ratio1_32, &ratio1_30, &ratio1_30, &ratio1_24, &ratio1_24, &ratio1_24, &ratio1_24, &ratio1_20, &ratio1_20, 
&ratio1_20, &ratio1_20, &ratio1_20, &ratio1_16, &ratio1_15, &ratio1_15, &ratio1_12, &ratio1_12, &ratio1_12, &ratio1_12, &ratio1_10, &ratio1_10, 
&ratio1_10, &ratio1_10, &ratio1_10, &ratio1_8, &ratio2_15, &ratio2_15, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_5, &ratio1_5, 
&ratio1_5, &ratio1_5, &ratio1_5, &ratio1_4, &ratio4_15, &ratio4_15, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio2_5, &ratio2_5, 
&ratio2_5, &ratio2_5, &ratio2_5, &ratio1_2, &ratio8_15, &ratio8_15, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio4_5, &ratio4_5, 
&ratio4_5, &ratio4_5, &ratio4_5, &ratio1_1, &ratio16_15, &ratio16_15, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio8_5, &ratio8_5, 
&ratio8_5, &ratio8_5, &ratio8_5, &ratio2_1, &ratio32_15, &ratio32_15, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio16_5, &ratio16_5, 
&ratio16_5, &ratio16_5, &ratio16_5, &ratio4_1, &ratio64_15, &ratio64_15, &ratio16_3, &ratio16_3, &ratio16_3, &ratio16_3, &ratio32_5, &ratio32_5, 
&ratio32_5, &ratio32_5, &ratio32_5, &ratio8_1, &ratio128_15, &ratio128_15, &ratio32_3, &ratio32_3, &ratio32_3, &ratio32_3, &ratio64_5, &ratio64_5, 
&ratio64_5, &ratio64_5, &ratio64_5, &ratio16_1, &ratio256_15, &ratio256_15, &ratio64_3, &ratio64_3, &ratio64_3, &ratio64_3, &ratio128_5, &ratio128_5, 
&ratio128_5, &ratio128_5, &ratio128_5, &ratio32_1, &ratio512_15, &ratio512_15, &ratio128_3}; 

static const ScaleNote * const harmDom7th1stInv[128] = {&ratio1_40, &ratio1_40, &ratio1_40, &ratio1_40, &ratio1_32, &ratio1_32, &ratio3_80, &ratio3_80, &ratio3_80, &ratio7_160, &ratio7_160, &ratio1_20, &ratio1_20, 
&ratio1_20, &ratio1_20, &ratio1_20, &ratio1_16, &ratio1_16, &ratio3_40, &ratio3_40, &ratio3_40, &ratio7_80, &ratio7_80, &ratio1_10, &ratio1_10, 
&ratio1_10, &ratio1_10, &ratio1_10, &ratio1_8, &ratio1_8, &ratio3_20, &ratio3_20, &ratio3_20, &ratio7_40, &ratio7_40, &ratio1_5, &ratio1_5, 
&ratio1_5, &ratio1_5, &ratio1_5, &ratio1_4, &ratio1_4, &ratio3_10, &ratio3_10, &ratio3_10, &ratio7_20, &ratio7_20, &ratio2_5, &ratio2_5, 
&ratio2_5, &ratio2_5, &ratio2_5, &ratio1_2, &ratio1_2, &ratio3_5, &ratio3_5, &ratio3_5, &ratio7_10, &ratio7_10, &ratio4_5, &ratio4_5, 
&ratio4_5, &ratio4_5, &ratio4_5, &ratio1_1, &ratio1_1, &ratio6_5, &ratio6_5, &ratio6_5, &ratio7_5, &ratio7_5, &ratio8_5, &ratio8_5, 
&ratio8_5, &ratio8_5, &ratio8_5, &ratio2_1, &ratio2_1, &ratio12_5, &ratio12_5, &ratio12_5, &ratio14_5, &ratio14_5, &ratio16_5, &ratio16_5, 
&ratio16_5, &ratio16_5, &ratio16_5, &ratio4_1, &ratio4_1, &ratio24_5, &ratio24_5, &ratio24_5, &ratio28_5, &ratio28_5, &ratio32_5, &ratio32_5, 
&ratio32_5, &ratio32_5, &ratio32_5, &ratio8_1, &ratio8_1, &ratio48_5, &ratio48_5, &ratio48_5, &ratio56_5, &ratio56_5, &ratio64_5, &ratio64_5, 
&ratio64_5, &ratio64_5, &ratio64_5, &ratio16_1, &ratio16_1, &ratio96_5, &ratio96_5, &ratio96_5, &ratio112_5, &ratio112_5, &ratio128_5, &ratio128_5, 
&ratio128_5, &ratio128_5, &ratio128_5, &ratio32_1, &ratio32_1, &ratio192_5, &ratio192_5}; 

static const ScaleNote * const subDom7th[128] = {&ratio9_400, &ratio9_320, &ratio9_320, &ratio9_320, &ratio1_32, &ratio1_32, &ratio3_80, &ratio3_80, &ratio3_80, &ratio9_200, &ratio9_200, &ratio9_200, &ratio9_200, 
&ratio9_160, &ratio9_160, &ratio9_160, &ratio1_16, &ratio1_16, &ratio3_40, &ratio3_40, &ratio3_40, &ratio9_100, &ratio9_100, &ratio9_100, &ratio9_100, 
&ratio9_80, &ratio9_80, &ratio9_80, &ratio1_8, &ratio1_8, &ratio3_20, &ratio3_20, &ratio3_20, &ratio9_50, &ratio9_50, &ratio9_50, &ratio9_50, 
&ratio9_40, &ratio9_40, &ratio9_40, &ratio1_4, &ratio1_4, &ratio3_10, &ratio3_10, &ratio3_10, &ratio9_25, &ratio9_25, &ratio9_25, &ratio9_25, 
&ratio9_20, &ratio9_20, &ratio9_20, &ratio1_2, &ratio1_2, &ratio3_5, &ratio3_5, &ratio3_5, &ratio18_25, &ratio18_25, &ratio18_25, &ratio18_25, 
&ratio9_10, &ratio9_10, &ratio9_10, &ratio1_1, &ratio1_1, &ratio6_5, &ratio6_5, &ratio6_5, &ratio36_25, &ratio36_25, &ratio36_25, &ratio36_25, 
&ratio9_5, &ratio9_5, &ratio9_5, &ratio2_1, &ratio2_1, &ratio12_5, &ratio12_5, &ratio12_5, &ratio72_25, &ratio72_25, &ratio72_25, &ratio72_25, 
&ratio18_5, &ratio18_5, &ratio18_5, &ratio4_1, &ratio4_1, &ratio24_5, &ratio24_5, &ratio24_5, &ratio144_25, &ratio144_25, &ratio144_25, &ratio144_25, 
&ratio36_5, &ratio36_5, &ratio36_5, &ratio8_1, &ratio8_1, &ratio48_5, &ratio48_5, &ratio48_5, &ratio288_25, &ratio288_25, &ratio288_25, &ratio288_25, 
&ratio72_5, &ratio72_5, &ratio72_5, &ratio16_1, &ratio16_1, &ratio96_5, &ratio96_5, &ratio96_5, &ratio576_25, &ratio576_25, &ratio576_25, &ratio576_25, 
&ratio144_5, &ratio144_5, &ratio144_5, &ratio32_1, &ratio32_1, &ratio192_5, &ratio192_5}; 

static const ScaleNote * const harmDom7th3rdInv[128] = {&ratio3_112, &ratio3_112, &ratio3_112, &ratio3_112, &ratio1_32, &ratio1_32, &ratio1_28, &ratio1_28, &ratio1_28, &ratio5_112, &ratio5_112, &ratio5_112, &ratio3_56, 
&ratio3_56, &ratio3_56, &ratio3_56, &ratio1_16, &ratio1_16, &ratio1_14, &ratio1_14, &ratio1_14, &ratio5_56, &ratio5_56, &ratio5_56, &ratio3_28, 
&ratio3_28, &ratio3_28, &ratio3_28, &ratio1_8, &ratio1_8, &ratio1_7, &ratio1_7, &ratio1_7, &ratio5_28, &ratio5_28, &ratio5_28, &ratio3_14, 
&ratio3_14, &ratio3_14, &ratio3_14, &ratio1_4, &ratio1_4, &ratio2_7, &ratio2_7, &ratio2_7, &ratio5_14, &ratio5_14, &ratio5_14, &ratio3_7, 
&ratio3_7, &ratio3_7, &ratio3_7, &ratio1_2, &ratio1_2, &ratio4_7, &ratio4_7, &ratio4_7, &ratio5_7, &ratio5_7, &ratio5_7, &ratio6_7, 
&ratio6_7, &ratio6_7, &ratio6_7, &ratio1_1, &ratio1_1, &ratio8_7, &ratio8_7, &ratio8_7, &ratio10_7, &ratio10_7, &ratio10_7, &ratio12_7, 
&ratio12_7, &ratio12_7, &ratio12_7, &ratio2_1, &ratio2_1, &ratio16_7, &ratio16_7, &ratio16_7, &ratio20_7, &ratio20_7, &ratio20_7, &ratio24_7, 
&ratio24_7, &ratio24_7, &ratio24_7, &ratio4_1, &ratio4_1, &ratio32_7, &ratio32_7, &ratio32_7, &ratio40_7, &ratio40_7, &ratio40_7, &ratio48_7, 
&ratio48_7, &ratio48_7, &ratio48_7, &ratio8_1, &ratio8_1, &ratio64_7, &ratio64_7, &ratio64_7, &ratio80_7, &ratio80_7, &ratio80_7, &ratio96_7, 
&ratio96_7, &ratio96_7, &ratio96_7, &ratio16_1, &ratio16_1, &ratio128_7, &ratio128_7, &ratio128_7, &ratio160_7, &ratio160_7, &ratio160_7, &ratio192_7, 
&ratio192_7, &ratio192_7, &ratio192_7, &ratio32_1, &ratio32_1, &ratio256_7, &ratio256_7}; 





static const ScaleNote * const messiaenOctatonic1[128] = {&ratio5_192, &ratio7_256, &ratio7_256, &ratio7_256, &ratio1_32, &ratio15_448, &ratio15_448, &ratio3_80, &ratio5_128, &ratio7_160, &ratio7_160, &ratio3_64, &ratio5_96, 
&ratio7_128, &ratio7_128, &ratio7_128, &ratio1_16, &ratio15_224, &ratio15_224, &ratio3_40, &ratio5_64, &ratio7_80, &ratio7_80, &ratio3_32, &ratio5_48, 
&ratio7_64, &ratio7_64, &ratio7_64, &ratio1_8, &ratio15_112, &ratio15_112, &ratio3_20, &ratio5_32, &ratio7_40, &ratio7_40, &ratio3_16, &ratio5_24, 
&ratio7_32, &ratio7_32, &ratio7_32, &ratio1_4, &ratio15_56, &ratio15_56, &ratio3_10, &ratio5_16, &ratio7_20, &ratio7_20, &ratio3_8, &ratio5_12, 
&ratio7_16, &ratio7_16, &ratio7_16, &ratio1_2, &ratio15_28, &ratio15_28, &ratio3_5, &ratio5_8, &ratio7_10, &ratio7_10, &ratio3_4, &ratio5_6, 
&ratio7_8, &ratio7_8, &ratio7_8, &ratio1_1, &ratio15_14, &ratio15_14, &ratio6_5, &ratio5_4, &ratio7_5, &ratio7_5, &ratio3_2, &ratio5_3, 
&ratio7_4, &ratio7_4, &ratio7_4, &ratio2_1, &ratio15_7, &ratio15_7, &ratio12_5, &ratio5_2, &ratio14_5, &ratio14_5, &ratio3_1, &ratio10_3, 
&ratio7_2, &ratio7_2, &ratio7_2, &ratio4_1, &ratio30_7, &ratio30_7, &ratio24_5, &ratio5_1, &ratio28_5, &ratio28_5, &ratio6_1, &ratio20_3, 
&ratio7_1, &ratio7_1, &ratio7_1, &ratio8_1, &ratio60_7, &ratio60_7, &ratio48_5, &ratio10_1, &ratio56_5, &ratio56_5, &ratio12_1, &ratio40_3, 
&ratio14_1, &ratio14_1, &ratio14_1, &ratio16_1, &ratio120_7, &ratio120_7, &ratio96_5, &ratio20_1, &ratio112_5, &ratio112_5, &ratio24_1, &ratio80_3, 
&ratio28_1, &ratio28_1, &ratio28_1, &ratio32_1, &ratio240_7, &ratio240_7, &ratio192_5}; 

static const ScaleNote * const messiaenOctatonic2[128] = {&ratio1_40, &ratio5_192, &ratio15_512, &ratio15_512, &ratio1_32, &ratio1_32, &ratio1_28, &ratio3_80, &ratio1_24, &ratio7_160, &ratio7_160, &ratio1_20, &ratio1_20, 
&ratio5_96, &ratio15_256, &ratio15_256, &ratio1_16, &ratio1_16, &ratio1_14, &ratio3_40, &ratio1_12, &ratio7_80, &ratio7_80, &ratio1_10, &ratio1_10, 
&ratio5_48, &ratio15_128, &ratio15_128, &ratio1_8, &ratio1_8, &ratio1_7, &ratio3_20, &ratio1_6, &ratio7_40, &ratio7_40, &ratio1_5, &ratio1_5, 
&ratio5_24, &ratio15_64, &ratio15_64, &ratio1_4, &ratio1_4, &ratio2_7, &ratio3_10, &ratio1_3, &ratio7_20, &ratio7_20, &ratio2_5, &ratio2_5, 
&ratio5_12, &ratio15_32, &ratio15_32, &ratio1_2, &ratio1_2, &ratio4_7, &ratio3_5, &ratio2_3, &ratio7_10, &ratio7_10, &ratio4_5, &ratio4_5, 
&ratio5_6, &ratio15_16, &ratio15_16, &ratio1_1, &ratio1_1, &ratio8_7, &ratio6_5, &ratio4_3, &ratio7_5, &ratio7_5, &ratio8_5, &ratio8_5, 
&ratio5_3, &ratio15_8, &ratio15_8, &ratio2_1, &ratio2_1, &ratio16_7, &ratio12_5, &ratio8_3, &ratio14_5, &ratio14_5, &ratio16_5, &ratio16_5, 
&ratio10_3, &ratio15_4, &ratio15_4, &ratio4_1, &ratio4_1, &ratio32_7, &ratio24_5, &ratio16_3, &ratio28_5, &ratio28_5, &ratio32_5, &ratio32_5, 
&ratio20_3, &ratio15_2, &ratio15_2, &ratio8_1, &ratio8_1, &ratio64_7, &ratio48_5, &ratio32_3, &ratio56_5, &ratio56_5, &ratio64_5, &ratio64_5, 
&ratio40_3, &ratio15_1, &ratio15_1, &ratio16_1, &ratio16_1, &ratio128_7, &ratio96_5, &ratio64_3, &ratio112_5, &ratio112_5, &ratio128_5, &ratio128_5, 
&ratio80_3, &ratio30_1, &ratio30_1, &ratio32_1, &ratio32_1, &ratio256_7, &ratio192_5}; 

static const ScaleNote * const messiaenModeIII1[128] = {&ratio1_40, &ratio7_256, &ratio7_256, &ratio7_256, &ratio1_32, &ratio15_448, &ratio1_28, &ratio5_128, &ratio1_24, &ratio7_160, &ratio7_160, &ratio1_20, &ratio1_20, 
&ratio7_128, &ratio7_128, &ratio7_128, &ratio1_16, &ratio15_224, &ratio1_14, &ratio5_64, &ratio1_12, &ratio7_80, &ratio7_80, &ratio1_10, &ratio1_10, 
&ratio7_64, &ratio7_64, &ratio7_64, &ratio1_8, &ratio15_112, &ratio1_7, &ratio5_32, &ratio1_6, &ratio7_40, &ratio7_40, &ratio1_5, &ratio1_5, 
&ratio7_32, &ratio7_32, &ratio7_32, &ratio1_4, &ratio15_56, &ratio2_7, &ratio5_16, &ratio1_3, &ratio7_20, &ratio7_20, &ratio2_5, &ratio2_5, 
&ratio7_16, &ratio7_16, &ratio7_16, &ratio1_2, &ratio15_28, &ratio4_7, &ratio5_8, &ratio2_3, &ratio7_10, &ratio7_10, &ratio4_5, &ratio4_5, 
&ratio7_8, &ratio7_8, &ratio7_8, &ratio1_1, &ratio15_14, &ratio8_7, &ratio5_4, &ratio4_3, &ratio7_5, &ratio7_5, &ratio8_5, &ratio8_5, 
&ratio7_4, &ratio7_4, &ratio7_4, &ratio2_1, &ratio15_7, &ratio16_7, &ratio5_2, &ratio8_3, &ratio14_5, &ratio14_5, &ratio16_5, &ratio16_5, 
&ratio7_2, &ratio7_2, &ratio7_2, &ratio4_1, &ratio30_7, &ratio32_7, &ratio5_1, &ratio16_3, &ratio28_5, &ratio28_5, &ratio32_5, &ratio32_5, 
&ratio7_1, &ratio7_1, &ratio7_1, &ratio8_1, &ratio60_7, &ratio64_7, &ratio10_1, &ratio32_3, &ratio56_5, &ratio56_5, &ratio64_5, &ratio64_5, 
&ratio14_1, &ratio14_1, &ratio14_1, &ratio16_1, &ratio120_7, &ratio128_7, &ratio20_1, &ratio64_3, &ratio112_5, &ratio112_5, &ratio128_5, &ratio128_5, 
&ratio28_1, &ratio28_1, &ratio28_1, &ratio32_1, &ratio240_7, &ratio256_7, &ratio40_1}; 

static const ScaleNote * const messiaenModeIII2[128] = {&ratio1_40, &ratio5_192, &ratio15_512, &ratio15_512, &ratio1_32, &ratio15_448, &ratio15_448, &ratio3_80, &ratio1_24, &ratio1_24, &ratio3_64, &ratio3_64, &ratio1_20, 
&ratio5_96, &ratio15_256, &ratio15_256, &ratio1_16, &ratio15_224, &ratio15_224, &ratio3_40, &ratio1_12, &ratio1_12, &ratio3_32, &ratio3_32, &ratio1_10, 
&ratio5_48, &ratio15_128, &ratio15_128, &ratio1_8, &ratio15_112, &ratio15_112, &ratio3_20, &ratio1_6, &ratio1_6, &ratio3_16, &ratio3_16, &ratio1_5, 
&ratio5_24, &ratio15_64, &ratio15_64, &ratio1_4, &ratio15_56, &ratio15_56, &ratio3_10, &ratio1_3, &ratio1_3, &ratio3_8, &ratio3_8, &ratio2_5, 
&ratio5_12, &ratio15_32, &ratio15_32, &ratio1_2, &ratio15_28, &ratio15_28, &ratio3_5, &ratio2_3, &ratio2_3, &ratio3_4, &ratio3_4, &ratio4_5, 
&ratio5_6, &ratio15_16, &ratio15_16, &ratio1_1, &ratio15_14, &ratio15_14, &ratio6_5, &ratio4_3, &ratio4_3, &ratio3_2, &ratio3_2, &ratio8_5, 
&ratio5_3, &ratio15_8, &ratio15_8, &ratio2_1, &ratio15_7, &ratio15_7, &ratio12_5, &ratio8_3, &ratio8_3, &ratio3_1, &ratio3_1, &ratio16_5, 
&ratio10_3, &ratio15_4, &ratio15_4, &ratio4_1, &ratio30_7, &ratio30_7, &ratio24_5, &ratio16_3, &ratio16_3, &ratio6_1, &ratio6_1, &ratio32_5, 
&ratio20_3, &ratio15_2, &ratio15_2, &ratio8_1, &ratio60_7, &ratio60_7, &ratio48_5, &ratio32_3, &ratio32_3, &ratio12_1, &ratio12_1, &ratio64_5, 
&ratio40_3, &ratio15_1, &ratio15_1, &ratio16_1, &ratio120_7, &ratio120_7, &ratio96_5, &ratio64_3, &ratio64_3, &ratio24_1, &ratio24_1, &ratio128_5, 
&ratio80_3, &ratio30_1, &ratio30_1, &ratio32_1, &ratio240_7, &ratio240_7, &ratio192_5}; 

static const ScaleNote * const messiaenModeIII3[128] = {&ratio1_40, &ratio7_256, &ratio15_512, &ratio15_512, &ratio1_32, &ratio1_32, &ratio1_28, &ratio3_80, &ratio5_128, &ratio7_160, &ratio7_160, &ratio3_64, &ratio1_20, 
&ratio7_128, &ratio15_256, &ratio15_256, &ratio1_16, &ratio1_16, &ratio1_14, &ratio3_40, &ratio5_64, &ratio7_80, &ratio7_80, &ratio3_32, &ratio1_10, 
&ratio7_64, &ratio15_128, &ratio15_128, &ratio1_8, &ratio1_8, &ratio1_7, &ratio3_20, &ratio5_32, &ratio7_40, &ratio7_40, &ratio3_16, &ratio1_5, 
&ratio7_32, &ratio15_64, &ratio15_64, &ratio1_4, &ratio1_4, &ratio2_7, &ratio3_10, &ratio5_16, &ratio7_20, &ratio7_20, &ratio3_8, &ratio2_5, 
&ratio7_16, &ratio15_32, &ratio15_32, &ratio1_2, &ratio1_2, &ratio4_7, &ratio3_5, &ratio5_8, &ratio7_10, &ratio7_10, &ratio3_4, &ratio4_5, 
&ratio7_8, &ratio15_16, &ratio15_16, &ratio1_1, &ratio1_1, &ratio8_7, &ratio6_5, &ratio5_4, &ratio7_5, &ratio7_5, &ratio3_2, &ratio8_5, 
&ratio7_4, &ratio15_8, &ratio15_8, &ratio2_1, &ratio2_1, &ratio16_7, &ratio12_5, &ratio5_2, &ratio14_5, &ratio14_5, &ratio3_1, &ratio16_5, 
&ratio7_2, &ratio15_4, &ratio15_4, &ratio4_1, &ratio4_1, &ratio32_7, &ratio24_5, &ratio5_1, &ratio28_5, &ratio28_5, &ratio6_1, &ratio32_5, 
&ratio7_1, &ratio15_2, &ratio15_2, &ratio8_1, &ratio8_1, &ratio64_7, &ratio48_5, &ratio10_1, &ratio56_5, &ratio56_5, &ratio12_1, &ratio64_5, 
&ratio14_1, &ratio15_1, &ratio15_1, &ratio16_1, &ratio16_1, &ratio128_7, &ratio96_5, &ratio20_1, &ratio112_5, &ratio112_5, &ratio24_1, &ratio128_5, 
&ratio28_1, &ratio30_1, &ratio30_1, &ratio32_1, &ratio32_1, &ratio256_7, &ratio192_5}; 

static const ScaleNote * const messiaenModeIV1[128] = {&ratio1_40, &ratio5_192, &ratio5_192, &ratio5_192, &ratio1_32, &ratio15_448, &ratio1_28, &ratio3_80, &ratio3_80, &ratio7_160, &ratio7_160, &ratio3_64, &ratio1_20, 
&ratio5_96, &ratio5_96, &ratio5_96, &ratio1_16, &ratio15_224, &ratio1_14, &ratio3_40, &ratio3_40, &ratio7_80, &ratio7_80, &ratio3_32, &ratio1_10, 
&ratio5_48, &ratio5_48, &ratio5_48, &ratio1_8, &ratio15_112, &ratio1_7, &ratio3_20, &ratio3_20, &ratio7_40, &ratio7_40, &ratio3_16, &ratio1_5, 
&ratio5_24, &ratio5_24, &ratio5_24, &ratio1_4, &ratio15_56, &ratio2_7, &ratio3_10, &ratio3_10, &ratio7_20, &ratio7_20, &ratio3_8, &ratio2_5, 
&ratio5_12, &ratio5_12, &ratio5_12, &ratio1_2, &ratio15_28, &ratio4_7, &ratio3_5, &ratio3_5, &ratio7_10, &ratio7_10, &ratio3_4, &ratio4_5, 
&ratio5_6, &ratio5_6, &ratio5_6, &ratio1_1, &ratio15_14, &ratio8_7, &ratio6_5, &ratio6_5, &ratio7_5, &ratio7_5, &ratio3_2, &ratio8_5, 
&ratio5_3, &ratio5_3, &ratio5_3, &ratio2_1, &ratio15_7, &ratio16_7, &ratio12_5, &ratio12_5, &ratio14_5, &ratio14_5, &ratio3_1, &ratio16_5, 
&ratio10_3, &ratio10_3, &ratio10_3, &ratio4_1, &ratio30_7, &ratio32_7, &ratio24_5, &ratio24_5, &ratio28_5, &ratio28_5, &ratio6_1, &ratio32_5, 
&ratio20_3, &ratio20_3, &ratio20_3, &ratio8_1, &ratio60_7, &ratio64_7, &ratio48_5, &ratio48_5, &ratio56_5, &ratio56_5, &ratio12_1, &ratio64_5, 
&ratio40_3, &ratio40_3, &ratio40_3, &ratio16_1, &ratio120_7, &ratio128_7, &ratio96_5, &ratio96_5, &ratio112_5, &ratio112_5, &ratio24_1, &ratio128_5, 
&ratio80_3, &ratio80_3, &ratio80_3, &ratio32_1, &ratio240_7, &ratio256_7, &ratio192_5}; 

static const ScaleNote * const messiaenModeIV2[128] = {&ratio1_40, &ratio1_40, &ratio15_512, &ratio15_512, &ratio1_32, &ratio15_448, &ratio1_28, &ratio1_28, &ratio1_24, &ratio7_160, &ratio7_160, &ratio3_64, &ratio1_20, 
&ratio1_20, &ratio15_256, &ratio15_256, &ratio1_16, &ratio15_224, &ratio1_14, &ratio1_14, &ratio1_12, &ratio7_80, &ratio7_80, &ratio3_32, &ratio1_10, 
&ratio1_10, &ratio15_128, &ratio15_128, &ratio1_8, &ratio15_112, &ratio1_7, &ratio1_7, &ratio1_6, &ratio7_40, &ratio7_40, &ratio3_16, &ratio1_5, 
&ratio1_5, &ratio15_64, &ratio15_64, &ratio1_4, &ratio15_56, &ratio2_7, &ratio2_7, &ratio1_3, &ratio7_20, &ratio7_20, &ratio3_8, &ratio2_5, 
&ratio2_5, &ratio15_32, &ratio15_32, &ratio1_2, &ratio15_28, &ratio4_7, &ratio4_7, &ratio2_3, &ratio7_10, &ratio7_10, &ratio3_4, &ratio4_5, 
&ratio4_5, &ratio15_16, &ratio15_16, &ratio1_1, &ratio15_14, &ratio8_7, &ratio8_7, &ratio4_3, &ratio7_5, &ratio7_5, &ratio3_2, &ratio8_5, 
&ratio8_5, &ratio15_8, &ratio15_8, &ratio2_1, &ratio15_7, &ratio16_7, &ratio16_7, &ratio8_3, &ratio14_5, &ratio14_5, &ratio3_1, &ratio16_5, 
&ratio16_5, &ratio15_4, &ratio15_4, &ratio4_1, &ratio30_7, &ratio32_7, &ratio32_7, &ratio16_3, &ratio28_5, &ratio28_5, &ratio6_1, &ratio32_5, 
&ratio32_5, &ratio15_2, &ratio15_2, &ratio8_1, &ratio60_7, &ratio64_7, &ratio64_7, &ratio32_3, &ratio56_5, &ratio56_5, &ratio12_1, &ratio64_5, 
&ratio64_5, &ratio15_1, &ratio15_1, &ratio16_1, &ratio120_7, &ratio128_7, &ratio128_7, &ratio64_3, &ratio112_5, &ratio112_5, &ratio24_1, &ratio128_5, 
&ratio128_5, &ratio30_1, &ratio30_1, &ratio32_1, &ratio240_7, &ratio256_7, &ratio256_7}; 

static const ScaleNote * const messiaenModeIV3[128] = {&ratio3_128, &ratio7_256, &ratio15_512, &ratio15_512, &ratio1_32, &ratio15_448, &ratio15_448, &ratio5_128, &ratio1_24, &ratio7_160, &ratio7_160, &ratio3_64, &ratio3_64, 
&ratio7_128, &ratio15_256, &ratio15_256, &ratio1_16, &ratio15_224, &ratio15_224, &ratio5_64, &ratio1_12, &ratio7_80, &ratio7_80, &ratio3_32, &ratio3_32, 
&ratio7_64, &ratio15_128, &ratio15_128, &ratio1_8, &ratio15_112, &ratio15_112, &ratio5_32, &ratio1_6, &ratio7_40, &ratio7_40, &ratio3_16, &ratio3_16, 
&ratio7_32, &ratio15_64, &ratio15_64, &ratio1_4, &ratio15_56, &ratio15_56, &ratio5_16, &ratio1_3, &ratio7_20, &ratio7_20, &ratio3_8, &ratio3_8, 
&ratio7_16, &ratio15_32, &ratio15_32, &ratio1_2, &ratio15_28, &ratio15_28, &ratio5_8, &ratio2_3, &ratio7_10, &ratio7_10, &ratio3_4, &ratio3_4, 
&ratio7_8, &ratio15_16, &ratio15_16, &ratio1_1, &ratio15_14, &ratio15_14, &ratio5_4, &ratio4_3, &ratio7_5, &ratio7_5, &ratio3_2, &ratio3_2, 
&ratio7_4, &ratio15_8, &ratio15_8, &ratio2_1, &ratio15_7, &ratio15_7, &ratio5_2, &ratio8_3, &ratio14_5, &ratio14_5, &ratio3_1, &ratio3_1, 
&ratio7_2, &ratio15_4, &ratio15_4, &ratio4_1, &ratio30_7, &ratio30_7, &ratio5_1, &ratio16_3, &ratio28_5, &ratio28_5, &ratio6_1, &ratio6_1, 
&ratio7_1, &ratio15_2, &ratio15_2, &ratio8_1, &ratio60_7, &ratio60_7, &ratio10_1, &ratio32_3, &ratio56_5, &ratio56_5, &ratio12_1, &ratio12_1, 
&ratio14_1, &ratio15_1, &ratio15_1, &ratio16_1, &ratio120_7, &ratio120_7, &ratio20_1, &ratio64_3, &ratio112_5, &ratio112_5, &ratio24_1, &ratio24_1, 
&ratio28_1, &ratio30_1, &ratio30_1, &ratio32_1, &ratio240_7, &ratio240_7, &ratio40_1}; 

static const ScaleNote * const messiaenModeIV4[128] = {&ratio5_192, &ratio7_256, &ratio15_512, &ratio15_512, &ratio1_32, &ratio1_32, &ratio3_80, &ratio3_80, &ratio1_24, &ratio7_160, &ratio7_160, &ratio5_96, &ratio5_96, 
&ratio7_128, &ratio15_256, &ratio15_256, &ratio1_16, &ratio1_16, &ratio3_40, &ratio3_40, &ratio1_12, &ratio7_80, &ratio7_80, &ratio5_48, &ratio5_48, 
&ratio7_64, &ratio15_128, &ratio15_128, &ratio1_8, &ratio1_8, &ratio3_20, &ratio3_20, &ratio1_6, &ratio7_40, &ratio7_40, &ratio5_24, &ratio5_24, 
&ratio7_32, &ratio15_64, &ratio15_64, &ratio1_4, &ratio1_4, &ratio3_10, &ratio3_10, &ratio1_3, &ratio7_20, &ratio7_20, &ratio5_12, &ratio5_12, 
&ratio7_16, &ratio15_32, &ratio15_32, &ratio1_2, &ratio1_2, &ratio3_5, &ratio3_5, &ratio2_3, &ratio7_10, &ratio7_10, &ratio5_6, &ratio5_6, 
&ratio7_8, &ratio15_16, &ratio15_16, &ratio1_1, &ratio1_1, &ratio6_5, &ratio6_5, &ratio4_3, &ratio7_5, &ratio7_5, &ratio5_3, &ratio5_3, 
&ratio7_4, &ratio15_8, &ratio15_8, &ratio2_1, &ratio2_1, &ratio12_5, &ratio12_5, &ratio8_3, &ratio14_5, &ratio14_5, &ratio10_3, &ratio10_3, 
&ratio7_2, &ratio15_4, &ratio15_4, &ratio4_1, &ratio4_1, &ratio24_5, &ratio24_5, &ratio16_3, &ratio28_5, &ratio28_5, &ratio20_3, &ratio20_3, 
&ratio7_1, &ratio15_2, &ratio15_2, &ratio8_1, &ratio8_1, &ratio48_5, &ratio48_5, &ratio32_3, &ratio56_5, &ratio56_5, &ratio40_3, &ratio40_3, 
&ratio14_1, &ratio15_1, &ratio15_1, &ratio16_1, &ratio16_1, &ratio96_5, &ratio96_5, &ratio64_3, &ratio112_5, &ratio112_5, &ratio80_3, &ratio80_3, 
&ratio28_1, &ratio30_1, &ratio30_1, &ratio32_1, &ratio32_1, &ratio192_5, &ratio192_5}; 

static const ScaleNote * const messiaenModeV1[128] = {&ratio1_40, &ratio1_40, &ratio1_40, &ratio1_40, &ratio1_32, &ratio15_448, &ratio1_28, &ratio1_28, &ratio7_160, &ratio7_160, &ratio7_160, &ratio3_64, &ratio1_20, 
&ratio1_20, &ratio1_20, &ratio1_20, &ratio1_16, &ratio15_224, &ratio1_14, &ratio1_14, &ratio7_80, &ratio7_80, &ratio7_80, &ratio3_32, &ratio1_10, 
&ratio1_10, &ratio1_10, &ratio1_10, &ratio1_8, &ratio15_112, &ratio1_7, &ratio1_7, &ratio7_40, &ratio7_40, &ratio7_40, &ratio3_16, &ratio1_5, 
&ratio1_5, &ratio1_5, &ratio1_5, &ratio1_4, &ratio15_56, &ratio2_7, &ratio2_7, &ratio7_20, &ratio7_20, &ratio7_20, &ratio3_8, &ratio2_5, 
&ratio2_5, &ratio2_5, &ratio2_5, &ratio1_2, &ratio15_28, &ratio4_7, &ratio4_7, &ratio7_10, &ratio7_10, &ratio7_10, &ratio3_4, &ratio4_5, 
&ratio4_5, &ratio4_5, &ratio4_5, &ratio1_1, &ratio15_14, &ratio8_7, &ratio8_7, &ratio7_5, &ratio7_5, &ratio7_5, &ratio3_2, &ratio8_5, 
&ratio8_5, &ratio8_5, &ratio8_5, &ratio2_1, &ratio15_7, &ratio16_7, &ratio16_7, &ratio14_5, &ratio14_5, &ratio14_5, &ratio3_1, &ratio16_5, 
&ratio16_5, &ratio16_5, &ratio16_5, &ratio4_1, &ratio30_7, &ratio32_7, &ratio32_7, &ratio28_5, &ratio28_5, &ratio28_5, &ratio6_1, &ratio32_5, 
&ratio32_5, &ratio32_5, &ratio32_5, &ratio8_1, &ratio60_7, &ratio64_7, &ratio64_7, &ratio56_5, &ratio56_5, &ratio56_5, &ratio12_1, &ratio64_5, 
&ratio64_5, &ratio64_5, &ratio64_5, &ratio16_1, &ratio120_7, &ratio128_7, &ratio128_7, &ratio112_5, &ratio112_5, &ratio112_5, &ratio24_1, &ratio128_5, 
&ratio128_5, &ratio128_5, &ratio128_5, &ratio32_1, &ratio240_7, &ratio256_7, &ratio256_7}; 

static const ScaleNote * const messiaenModeV2[128] = {&ratio3_128, &ratio15_512, &ratio15_512, &ratio15_512, &ratio1_32, &ratio15_448, &ratio15_448, &ratio1_24, &ratio1_24, &ratio7_160, &ratio7_160, &ratio3_64, &ratio3_64, 
&ratio15_256, &ratio15_256, &ratio15_256, &ratio1_16, &ratio15_224, &ratio15_224, &ratio1_12, &ratio1_12, &ratio7_80, &ratio7_80, &ratio3_32, &ratio3_32, 
&ratio15_128, &ratio15_128, &ratio15_128, &ratio1_8, &ratio15_112, &ratio15_112, &ratio1_6, &ratio1_6, &ratio7_40, &ratio7_40, &ratio3_16, &ratio3_16, 
&ratio15_64, &ratio15_64, &ratio15_64, &ratio1_4, &ratio15_56, &ratio15_56, &ratio1_3, &ratio1_3, &ratio7_20, &ratio7_20, &ratio3_8, &ratio3_8, 
&ratio15_32, &ratio15_32, &ratio15_32, &ratio1_2, &ratio15_28, &ratio15_28, &ratio2_3, &ratio2_3, &ratio7_10, &ratio7_10, &ratio3_4, &ratio3_4, 
&ratio15_16, &ratio15_16, &ratio15_16, &ratio1_1, &ratio15_14, &ratio15_14, &ratio4_3, &ratio4_3, &ratio7_5, &ratio7_5, &ratio3_2, &ratio3_2, 
&ratio15_8, &ratio15_8, &ratio15_8, &ratio2_1, &ratio15_7, &ratio15_7, &ratio8_3, &ratio8_3, &ratio14_5, &ratio14_5, &ratio3_1, &ratio3_1, 
&ratio15_4, &ratio15_4, &ratio15_4, &ratio4_1, &ratio30_7, &ratio30_7, &ratio16_3, &ratio16_3, &ratio28_5, &ratio28_5, &ratio6_1, &ratio6_1, 
&ratio15_2, &ratio15_2, &ratio15_2, &ratio8_1, &ratio60_7, &ratio60_7, &ratio32_3, &ratio32_3, &ratio56_5, &ratio56_5, &ratio12_1, &ratio12_1, 
&ratio15_1, &ratio15_1, &ratio15_1, &ratio16_1, &ratio120_7, &ratio120_7, &ratio64_3, &ratio64_3, &ratio112_5, &ratio112_5, &ratio24_1, &ratio24_1, 
&ratio30_1, &ratio30_1, &ratio30_1, &ratio32_1, &ratio240_7, &ratio240_7, &ratio128_3}; 

static const ScaleNote * const messiaenModeV3[128] = {&ratio7_256, &ratio7_256, &ratio15_512, &ratio15_512, &ratio1_32, &ratio1_32, &ratio5_128, &ratio5_128, &ratio1_24, &ratio7_160, &ratio7_160, &ratio7_160, &ratio7_128, 
&ratio7_128, &ratio15_256, &ratio15_256, &ratio1_16, &ratio1_16, &ratio5_64, &ratio5_64, &ratio1_12, &ratio7_80, &ratio7_80, &ratio7_80, &ratio7_64, 
&ratio7_64, &ratio15_128, &ratio15_128, &ratio1_8, &ratio1_8, &ratio5_32, &ratio5_32, &ratio1_6, &ratio7_40, &ratio7_40, &ratio7_40, &ratio7_32, 
&ratio7_32, &ratio15_64, &ratio15_64, &ratio1_4, &ratio1_4, &ratio5_16, &ratio5_16, &ratio1_3, &ratio7_20, &ratio7_20, &ratio7_20, &ratio7_16, 
&ratio7_16, &ratio15_32, &ratio15_32, &ratio1_2, &ratio1_2, &ratio5_8, &ratio5_8, &ratio2_3, &ratio7_10, &ratio7_10, &ratio7_10, &ratio7_8, 
&ratio7_8, &ratio15_16, &ratio15_16, &ratio1_1, &ratio1_1, &ratio5_4, &ratio5_4, &ratio4_3, &ratio7_5, &ratio7_5, &ratio7_5, &ratio7_4, 
&ratio7_4, &ratio15_8, &ratio15_8, &ratio2_1, &ratio2_1, &ratio5_2, &ratio5_2, &ratio8_3, &ratio14_5, &ratio14_5, &ratio14_5, &ratio7_2, 
&ratio7_2, &ratio15_4, &ratio15_4, &ratio4_1, &ratio4_1, &ratio5_1, &ratio5_1, &ratio16_3, &ratio28_5, &ratio28_5, &ratio28_5, &ratio7_1, 
&ratio7_1, &ratio15_2, &ratio15_2, &ratio8_1, &ratio8_1, &ratio10_1, &ratio10_1, &ratio32_3, &ratio56_5, &ratio56_5, &ratio56_5, &ratio14_1, 
&ratio14_1, &ratio15_1, &ratio15_1, &ratio16_1, &ratio16_1, &ratio20_1, &ratio20_1, &ratio64_3, &ratio112_5, &ratio112_5, &ratio112_5, &ratio28_1, 
&ratio28_1, &ratio30_1, &ratio30_1, &ratio32_1, &ratio32_1, &ratio40_1, &ratio40_1}; 

static const ScaleNote * const messiaenModeVI1[128] = {&ratio5_192, &ratio5_192, &ratio15_512, &ratio15_512, &ratio1_32, &ratio15_448, &ratio15_448, &ratio3_80, &ratio1_24, &ratio7_160, &ratio7_160, &ratio3_64, &ratio5_96, 
&ratio5_96, &ratio15_256, &ratio15_256, &ratio1_16, &ratio15_224, &ratio15_224, &ratio3_40, &ratio1_12, &ratio7_80, &ratio7_80, &ratio3_32, &ratio5_48, 
&ratio5_48, &ratio15_128, &ratio15_128, &ratio1_8, &ratio15_112, &ratio15_112, &ratio3_20, &ratio1_6, &ratio7_40, &ratio7_40, &ratio3_16, &ratio5_24, 
&ratio5_24, &ratio15_64, &ratio15_64, &ratio1_4, &ratio15_56, &ratio15_56, &ratio3_10, &ratio1_3, &ratio7_20, &ratio7_20, &ratio3_8, &ratio5_12, 
&ratio5_12, &ratio15_32, &ratio15_32, &ratio1_2, &ratio15_28, &ratio15_28, &ratio3_5, &ratio2_3, &ratio7_10, &ratio7_10, &ratio3_4, &ratio5_6, 
&ratio5_6, &ratio15_16, &ratio15_16, &ratio1_1, &ratio15_14, &ratio15_14, &ratio6_5, &ratio4_3, &ratio7_5, &ratio7_5, &ratio3_2, &ratio5_3, 
&ratio5_3, &ratio15_8, &ratio15_8, &ratio2_1, &ratio15_7, &ratio15_7, &ratio12_5, &ratio8_3, &ratio14_5, &ratio14_5, &ratio3_1, &ratio10_3, 
&ratio10_3, &ratio15_4, &ratio15_4, &ratio4_1, &ratio30_7, &ratio30_7, &ratio24_5, &ratio16_3, &ratio28_5, &ratio28_5, &ratio6_1, &ratio20_3, 
&ratio20_3, &ratio15_2, &ratio15_2, &ratio8_1, &ratio60_7, &ratio60_7, &ratio48_5, &ratio32_3, &ratio56_5, &ratio56_5, &ratio12_1, &ratio40_3, 
&ratio40_3, &ratio15_1, &ratio15_1, &ratio16_1, &ratio120_7, &ratio120_7, &ratio96_5, &ratio64_3, &ratio112_5, &ratio112_5, &ratio24_1, &ratio80_3, 
&ratio80_3, &ratio30_1, &ratio30_1, &ratio32_1, &ratio240_7, &ratio240_7, &ratio192_5}; 

static const ScaleNote * const messiaenModeVI2[128] = {&ratio1_40, &ratio7_256, &ratio15_512, &ratio15_512, &ratio1_32, &ratio1_32, &ratio1_28, &ratio5_128, &ratio1_24, &ratio7_160, &ratio7_160, &ratio1_20, &ratio1_20, 
&ratio7_128, &ratio15_256, &ratio15_256, &ratio1_16, &ratio1_16, &ratio1_14, &ratio5_64, &ratio1_12, &ratio7_80, &ratio7_80, &ratio1_10, &ratio1_10, 
&ratio7_64, &ratio15_128, &ratio15_128, &ratio1_8, &ratio1_8, &ratio1_7, &ratio5_32, &ratio1_6, &ratio7_40, &ratio7_40, &ratio1_5, &ratio1_5, 
&ratio7_32, &ratio15_64, &ratio15_64, &ratio1_4, &ratio1_4, &ratio2_7, &ratio5_16, &ratio1_3, &ratio7_20, &ratio7_20, &ratio2_5, &ratio2_5, 
&ratio7_16, &ratio15_32, &ratio15_32, &ratio1_2, &ratio1_2, &ratio4_7, &ratio5_8, &ratio2_3, &ratio7_10, &ratio7_10, &ratio4_5, &ratio4_5, 
&ratio7_8, &ratio15_16, &ratio15_16, &ratio1_1, &ratio1_1, &ratio8_7, &ratio5_4, &ratio4_3, &ratio7_5, &ratio7_5, &ratio8_5, &ratio8_5, 
&ratio7_4, &ratio15_8, &ratio15_8, &ratio2_1, &ratio2_1, &ratio16_7, &ratio5_2, &ratio8_3, &ratio14_5, &ratio14_5, &ratio16_5, &ratio16_5, 
&ratio7_2, &ratio15_4, &ratio15_4, &ratio4_1, &ratio4_1, &ratio32_7, &ratio5_1, &ratio16_3, &ratio28_5, &ratio28_5, &ratio32_5, &ratio32_5, 
&ratio7_1, &ratio15_2, &ratio15_2, &ratio8_1, &ratio8_1, &ratio64_7, &ratio10_1, &ratio32_3, &ratio56_5, &ratio56_5, &ratio64_5, &ratio64_5, 
&ratio14_1, &ratio15_1, &ratio15_1, &ratio16_1, &ratio16_1, &ratio128_7, &ratio20_1, &ratio64_3, &ratio112_5, &ratio112_5, &ratio128_5, &ratio128_5, 
&ratio28_1, &ratio30_1, &ratio30_1, &ratio32_1, &ratio32_1, &ratio256_7, &ratio40_1}; 

static const ScaleNote * const messiaenModeVI3[128] = {&ratio1_40, &ratio7_256, &ratio7_256, &ratio7_256, &ratio1_32, &ratio1_32, &ratio1_28, &ratio3_80, &ratio5_128, &ratio7_160, &ratio7_160, &ratio1_20, &ratio1_20, 
&ratio7_128, &ratio7_128, &ratio7_128, &ratio1_16, &ratio1_16, &ratio1_14, &ratio3_40, &ratio5_64, &ratio7_80, &ratio7_80, &ratio1_10, &ratio1_10, 
&ratio7_64, &ratio7_64, &ratio7_64, &ratio1_8, &ratio1_8, &ratio1_7, &ratio3_20, &ratio5_32, &ratio7_40, &ratio7_40, &ratio1_5, &ratio1_5, 
&ratio7_32, &ratio7_32, &ratio7_32, &ratio1_4, &ratio1_4, &ratio2_7, &ratio3_10, &ratio5_16, &ratio7_20, &ratio7_20, &ratio2_5, &ratio2_5, 
&ratio7_16, &ratio7_16, &ratio7_16, &ratio1_2, &ratio1_2, &ratio4_7, &ratio3_5, &ratio5_8, &ratio7_10, &ratio7_10, &ratio4_5, &ratio4_5, 
&ratio7_8, &ratio7_8, &ratio7_8, &ratio1_1, &ratio1_1, &ratio8_7, &ratio6_5, &ratio5_4, &ratio7_5, &ratio7_5, &ratio8_5, &ratio8_5, 
&ratio7_4, &ratio7_4, &ratio7_4, &ratio2_1, &ratio2_1, &ratio16_7, &ratio12_5, &ratio5_2, &ratio14_5, &ratio14_5, &ratio16_5, &ratio16_5, 
&ratio7_2, &ratio7_2, &ratio7_2, &ratio4_1, &ratio4_1, &ratio32_7, &ratio24_5, &ratio5_1, &ratio28_5, &ratio28_5, &ratio32_5, &ratio32_5, 
&ratio7_1, &ratio7_1, &ratio7_1, &ratio8_1, &ratio8_1, &ratio64_7, &ratio48_5, &ratio10_1, &ratio56_5, &ratio56_5, &ratio64_5, &ratio64_5, 
&ratio14_1, &ratio14_1, &ratio14_1, &ratio16_1, &ratio16_1, &ratio128_7, &ratio96_5, &ratio20_1, &ratio112_5, &ratio112_5, &ratio128_5, &ratio128_5, 
&ratio28_1, &ratio28_1, &ratio28_1, &ratio32_1, &ratio32_1, &ratio256_7, &ratio192_5}; 

static const ScaleNote * const messiaenModeVI4[128] = {&ratio1_40, &ratio7_256, &ratio7_256, &ratio7_256, &ratio1_32, &ratio15_448, &ratio1_28, &ratio5_128, &ratio5_128, &ratio7_160, &ratio7_160, &ratio3_64, &ratio1_20, 
&ratio7_128, &ratio7_128, &ratio7_128, &ratio1_16, &ratio15_224, &ratio1_14, &ratio5_64, &ratio5_64, &ratio7_80, &ratio7_80, &ratio3_32, &ratio1_10, 
&ratio7_64, &ratio7_64, &ratio7_64, &ratio1_8, &ratio15_112, &ratio1_7, &ratio5_32, &ratio5_32, &ratio7_40, &ratio7_40, &ratio3_16, &ratio1_5, 
&ratio7_32, &ratio7_32, &ratio7_32, &ratio1_4, &ratio15_56, &ratio2_7, &ratio5_16, &ratio5_16, &ratio7_20, &ratio7_20, &ratio3_8, &ratio2_5, 
&ratio7_16, &ratio7_16, &ratio7_16, &ratio1_2, &ratio15_28, &ratio4_7, &ratio5_8, &ratio5_8, &ratio7_10, &ratio7_10, &ratio3_4, &ratio4_5, 
&ratio7_8, &ratio7_8, &ratio7_8, &ratio1_1, &ratio15_14, &ratio8_7, &ratio5_4, &ratio5_4, &ratio7_5, &ratio7_5, &ratio3_2, &ratio8_5, 
&ratio7_4, &ratio7_4, &ratio7_4, &ratio2_1, &ratio15_7, &ratio16_7, &ratio5_2, &ratio5_2, &ratio14_5, &ratio14_5, &ratio3_1, &ratio16_5, 
&ratio7_2, &ratio7_2, &ratio7_2, &ratio4_1, &ratio30_7, &ratio32_7, &ratio5_1, &ratio5_1, &ratio28_5, &ratio28_5, &ratio6_1, &ratio32_5, 
&ratio7_1, &ratio7_1, &ratio7_1, &ratio8_1, &ratio60_7, &ratio64_7, &ratio10_1, &ratio10_1, &ratio56_5, &ratio56_5, &ratio12_1, &ratio64_5, 
&ratio14_1, &ratio14_1, &ratio14_1, &ratio16_1, &ratio120_7, &ratio128_7, &ratio20_1, &ratio20_1, &ratio112_5, &ratio112_5, &ratio24_1, &ratio128_5, 
&ratio28_1, &ratio28_1, &ratio28_1, &ratio32_1, &ratio240_7, &ratio256_7, &ratio40_1}; 



static const ScaleNote * const maj9thPent[128] = {&ratio3_128, &ratio15_512, &ratio15_512, &ratio15_512, &ratio15_512, &ratio9_256, &ratio9_256, &ratio9_256, &ratio9_256, &ratio9_256, &ratio9_256, &ratio9_256, &ratio9_256, 
&ratio9_256, &ratio9_256, &ratio9_256, &ratio1_16, &ratio1_16, &ratio5_64, &ratio5_64, &ratio5_64, &ratio5_64, &ratio3_32, &ratio3_32, &ratio3_32, 
&ratio15_128, &ratio15_128, &ratio15_128, &ratio15_128, &ratio9_64, &ratio9_64, &ratio9_64, &ratio9_64, &ratio9_64, &ratio9_64, &ratio9_64, &ratio9_64, 
&ratio9_64, &ratio9_64, &ratio9_64, &ratio1_4, &ratio1_4, &ratio5_16, &ratio5_16, &ratio5_16, &ratio5_16, &ratio3_8, &ratio3_8, &ratio3_8, 
&ratio15_32, &ratio15_32, &ratio15_32, &ratio15_32, &ratio9_16, &ratio9_16, &ratio9_16, &ratio9_16, &ratio9_16, &ratio9_16, &ratio9_16, &ratio9_16, 
&ratio9_16, &ratio9_16, &ratio9_16, &ratio1_1, &ratio1_1, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio3_2, &ratio3_2, &ratio3_2, 
&ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, 
&ratio9_4, &ratio9_4, &ratio9_4, &ratio4_1, &ratio4_1, &ratio5_1, &ratio5_1, &ratio5_1, &ratio5_1, &ratio6_1, &ratio6_1, &ratio6_1, 
&ratio15_2, &ratio15_2, &ratio15_2, &ratio15_2, &ratio9_1, &ratio9_1, &ratio9_1, &ratio9_1, &ratio9_1, &ratio9_1, &ratio9_1, &ratio9_1, 
&ratio9_1, &ratio9_1, &ratio9_1, &ratio16_1, &ratio16_1, &ratio20_1, &ratio20_1, &ratio20_1, &ratio20_1, &ratio24_1, &ratio24_1, &ratio24_1, 
&ratio30_1, &ratio30_1, &ratio30_1, &ratio30_1, &ratio36_1, &ratio36_1, &ratio36_1}; 

static const ScaleNote * const min9thPent[128] = {&ratio3_128, &ratio9_320, &ratio9_320, &ratio9_320, &ratio9_320, &ratio9_256, &ratio9_256, &ratio9_256, &ratio9_256, &ratio9_256, &ratio9_256, &ratio9_256, &ratio9_256, 
&ratio9_256, &ratio9_256, &ratio9_256, &ratio1_16, &ratio1_16, &ratio3_40, &ratio3_40, &ratio3_40, &ratio3_40, &ratio3_32, &ratio3_32, &ratio3_32, 
&ratio9_80, &ratio9_80, &ratio9_80, &ratio9_80, &ratio9_64, &ratio9_64, &ratio9_64, &ratio9_64, &ratio9_64, &ratio9_64, &ratio9_64, &ratio9_64, 
&ratio9_64, &ratio9_64, &ratio9_64, &ratio1_4, &ratio1_4, &ratio3_10, &ratio3_10, &ratio3_10, &ratio3_10, &ratio3_8, &ratio3_8, &ratio3_8, 
&ratio9_20, &ratio9_20, &ratio9_20, &ratio9_20, &ratio9_16, &ratio9_16, &ratio9_16, &ratio9_16, &ratio9_16, &ratio9_16, &ratio9_16, &ratio9_16, 
&ratio9_16, &ratio9_16, &ratio9_16, &ratio1_1, &ratio1_1, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio3_2, &ratio3_2, &ratio3_2, 
&ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, &ratio9_4, 
&ratio9_4, &ratio9_4, &ratio9_4, &ratio4_1, &ratio4_1, &ratio24_5, &ratio24_5, &ratio24_5, &ratio24_5, &ratio6_1, &ratio6_1, &ratio6_1, 
&ratio36_5, &ratio36_5, &ratio36_5, &ratio36_5, &ratio9_1, &ratio9_1, &ratio9_1, &ratio9_1, &ratio9_1, &ratio9_1, &ratio9_1, &ratio9_1, 
&ratio9_1, &ratio9_1, &ratio9_1, &ratio16_1, &ratio16_1, &ratio96_5, &ratio96_5, &ratio96_5, &ratio96_5, &ratio24_1, &ratio24_1, &ratio24_1, 
&ratio144_5, &ratio144_5, &ratio144_5, &ratio144_5, &ratio36_1, &ratio36_1, &ratio36_1}; 

static const ScaleNote * const maj9thPent1stInv[128] = {&ratio3_128, &ratio9_320, &ratio9_320, &ratio9_320, &ratio9_320, &ratio9_320, &ratio9_320, &ratio9_320, &ratio1_20, &ratio1_20, &ratio1_20, &ratio1_20, &ratio1_20, 
&ratio1_20, &ratio1_20, &ratio1_20, &ratio1_16, &ratio1_16, &ratio3_40, &ratio3_40, &ratio3_40, &ratio3_40, &ratio3_32, &ratio3_32, &ratio3_32, 
&ratio9_80, &ratio9_80, &ratio9_80, &ratio9_80, &ratio9_80, &ratio9_80, &ratio9_80, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, 
&ratio1_5, &ratio1_5, &ratio1_5, &ratio1_4, &ratio1_4, &ratio3_10, &ratio3_10, &ratio3_10, &ratio3_10, &ratio3_8, &ratio3_8, &ratio3_8, 
&ratio9_20, &ratio9_20, &ratio9_20, &ratio9_20, &ratio9_20, &ratio9_20, &ratio9_20, &ratio4_5, &ratio4_5, &ratio4_5, &ratio4_5, &ratio4_5, 
&ratio4_5, &ratio4_5, &ratio4_5, &ratio1_1, &ratio1_1, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio3_2, &ratio3_2, &ratio3_2, 
&ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio9_5, &ratio16_5, &ratio16_5, &ratio16_5, &ratio16_5, &ratio16_5, 
&ratio16_5, &ratio16_5, &ratio16_5, &ratio4_1, &ratio4_1, &ratio24_5, &ratio24_5, &ratio24_5, &ratio24_5, &ratio6_1, &ratio6_1, &ratio6_1, 
&ratio36_5, &ratio36_5, &ratio36_5, &ratio36_5, &ratio36_5, &ratio36_5, &ratio36_5, &ratio64_5, &ratio64_5, &ratio64_5, &ratio64_5, &ratio64_5, 
&ratio64_5, &ratio64_5, &ratio64_5, &ratio16_1, &ratio16_1, &ratio96_5, &ratio96_5, &ratio96_5, &ratio96_5, &ratio24_1, &ratio24_1, &ratio24_1, 
&ratio144_5, &ratio144_5, &ratio144_5, &ratio144_5, &ratio144_5, &ratio144_5, &ratio144_5}; 

static const ScaleNote * const min9thPent1stInv[128] = {&ratio3_128, &ratio15_512, &ratio15_512, &ratio15_512, &ratio15_512, &ratio15_512, &ratio15_512, &ratio15_512, &ratio5_96, &ratio5_96, &ratio5_96, &ratio5_96, &ratio5_96, 
&ratio5_96, &ratio5_96, &ratio5_96, &ratio1_16, &ratio1_16, &ratio5_64, &ratio5_64, &ratio5_64, &ratio5_64, &ratio3_32, &ratio3_32, &ratio3_32, 
&ratio15_128, &ratio15_128, &ratio15_128, &ratio15_128, &ratio15_128, &ratio15_128, &ratio15_128, &ratio5_24, &ratio5_24, &ratio5_24, &ratio5_24, &ratio5_24, 
&ratio5_24, &ratio5_24, &ratio5_24, &ratio1_4, &ratio1_4, &ratio5_16, &ratio5_16, &ratio5_16, &ratio5_16, &ratio3_8, &ratio3_8, &ratio3_8, 
&ratio15_32, &ratio15_32, &ratio15_32, &ratio15_32, &ratio15_32, &ratio15_32, &ratio15_32, &ratio5_6, &ratio5_6, &ratio5_6, &ratio5_6, &ratio5_6, 
&ratio5_6, &ratio5_6, &ratio5_6, &ratio1_1, &ratio1_1, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio3_2, &ratio3_2, &ratio3_2, 
&ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio15_8, &ratio10_3, &ratio10_3, &ratio10_3, &ratio10_3, &ratio10_3, 
&ratio10_3, &ratio10_3, &ratio10_3, &ratio4_1, &ratio4_1, &ratio5_1, &ratio5_1, &ratio5_1, &ratio5_1, &ratio6_1, &ratio6_1, &ratio6_1, 
&ratio15_2, &ratio15_2, &ratio15_2, &ratio15_2, &ratio15_2, &ratio15_2, &ratio15_2, &ratio40_3, &ratio40_3, &ratio40_3, &ratio40_3, &ratio40_3, 
&ratio40_3, &ratio40_3, &ratio40_3, &ratio16_1, &ratio16_1, &ratio20_1, &ratio20_1, &ratio20_1, &ratio20_1, &ratio24_1, &ratio24_1, &ratio24_1, 
&ratio30_1, &ratio30_1, &ratio30_1, &ratio30_1, &ratio30_1, &ratio30_1, &ratio30_1}; 

static const ScaleNote * const maj9thPent2ndInv[128] = {&ratio3_128, &ratio3_128, &ratio3_128, &ratio3_128, &ratio1_24, &ratio1_24, &ratio1_24, &ratio1_24, &ratio1_24, &ratio1_24, &ratio1_24, &ratio5_96, &ratio5_96, 
&ratio5_96, &ratio5_96, &ratio5_96, &ratio1_16, &ratio1_16, &ratio5_64, &ratio5_64, &ratio5_64, &ratio5_64, &ratio3_32, &ratio3_32, &ratio3_32, 
&ratio3_32, &ratio3_32, &ratio3_32, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, &ratio5_24, &ratio5_24, 
&ratio5_24, &ratio5_24, &ratio5_24, &ratio1_4, &ratio1_4, &ratio5_16, &ratio5_16, &ratio5_16, &ratio5_16, &ratio3_8, &ratio3_8, &ratio3_8, 
&ratio3_8, &ratio3_8, &ratio3_8, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio5_6, &ratio5_6, 
&ratio5_6, &ratio5_6, &ratio5_6, &ratio1_1, &ratio1_1, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio3_2, &ratio3_2, &ratio3_2, 
&ratio3_2, &ratio3_2, &ratio3_2, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio10_3, &ratio10_3, 
&ratio10_3, &ratio10_3, &ratio10_3, &ratio4_1, &ratio4_1, &ratio5_1, &ratio5_1, &ratio5_1, &ratio5_1, &ratio6_1, &ratio6_1, &ratio6_1, 
&ratio6_1, &ratio6_1, &ratio6_1, &ratio32_3, &ratio32_3, &ratio32_3, &ratio32_3, &ratio32_3, &ratio32_3, &ratio32_3, &ratio40_3, &ratio40_3, 
&ratio40_3, &ratio40_3, &ratio40_3, &ratio16_1, &ratio16_1, &ratio20_1, &ratio20_1, &ratio20_1, &ratio20_1, &ratio24_1, &ratio24_1, &ratio24_1, 
&ratio24_1, &ratio24_1, &ratio24_1, &ratio128_3, &ratio128_3, &ratio128_3, &ratio128_3}; 

static const ScaleNote * const min9thPent2ndInv[128] = {&ratio3_128, &ratio3_128, &ratio3_128, &ratio3_128, &ratio1_24, &ratio1_24, &ratio1_24, &ratio1_24, &ratio1_24, &ratio1_24, &ratio1_24, &ratio1_20, &ratio1_20, 
&ratio1_20, &ratio1_20, &ratio1_20, &ratio1_16, &ratio1_16, &ratio3_40, &ratio3_40, &ratio3_40, &ratio3_40, &ratio3_32, &ratio3_32, &ratio3_32, 
&ratio3_32, &ratio3_32, &ratio3_32, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_5, &ratio1_5, 
&ratio1_5, &ratio1_5, &ratio1_5, &ratio1_4, &ratio1_4, &ratio3_10, &ratio3_10, &ratio3_10, &ratio3_10, &ratio3_8, &ratio3_8, &ratio3_8, 
&ratio3_8, &ratio3_8, &ratio3_8, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio4_5, &ratio4_5, 
&ratio4_5, &ratio4_5, &ratio4_5, &ratio1_1, &ratio1_1, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio3_2, &ratio3_2, &ratio3_2, 
&ratio3_2, &ratio3_2, &ratio3_2, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio16_5, &ratio16_5, 
&ratio16_5, &ratio16_5, &ratio16_5, &ratio4_1, &ratio4_1, &ratio24_5, &ratio24_5, &ratio24_5, &ratio24_5, &ratio6_1, &ratio6_1, &ratio6_1, 
&ratio6_1, &ratio6_1, &ratio6_1, &ratio32_3, &ratio32_3, &ratio32_3, &ratio32_3, &ratio32_3, &ratio32_3, &ratio32_3, &ratio64_5, &ratio64_5, 
&ratio64_5, &ratio64_5, &ratio64_5, &ratio16_1, &ratio16_1, &ratio96_5, &ratio96_5, &ratio96_5, &ratio96_5, &ratio24_1, &ratio24_1, &ratio24_1, 
&ratio24_1, &ratio24_1, &ratio24_1, &ratio128_3, &ratio128_3, &ratio128_3, &ratio128_3}; 

static const ScaleNote * const maj9thPent3rdInv[128] = {&ratio3_160, &ratio1_30, &ratio1_30, &ratio1_30, &ratio1_30, &ratio1_30, &ratio1_30, &ratio1_24, &ratio1_24, &ratio1_24, &ratio1_24, &ratio1_20, &ratio1_20, 
&ratio1_20, &ratio1_20, &ratio1_20, &ratio1_16, &ratio1_16, &ratio3_40, &ratio3_40, &ratio3_40, &ratio3_40, &ratio3_40, &ratio3_40, &ratio3_40, 
&ratio2_15, &ratio2_15, &ratio2_15, &ratio2_15, &ratio2_15, &ratio2_15, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_5, &ratio1_5, 
&ratio1_5, &ratio1_5, &ratio1_5, &ratio1_4, &ratio1_4, &ratio3_10, &ratio3_10, &ratio3_10, &ratio3_10, &ratio3_10, &ratio3_10, &ratio3_10, 
&ratio8_15, &ratio8_15, &ratio8_15, &ratio8_15, &ratio8_15, &ratio8_15, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio4_5, &ratio4_5, 
&ratio4_5, &ratio4_5, &ratio4_5, &ratio1_1, &ratio1_1, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, 
&ratio32_15, &ratio32_15, &ratio32_15, &ratio32_15, &ratio32_15, &ratio32_15, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio16_5, &ratio16_5, 
&ratio16_5, &ratio16_5, &ratio16_5, &ratio4_1, &ratio4_1, &ratio24_5, &ratio24_5, &ratio24_5, &ratio24_5, &ratio24_5, &ratio24_5, &ratio24_5, 
&ratio128_15, &ratio128_15, &ratio128_15, &ratio128_15, &ratio128_15, &ratio128_15, &ratio32_3, &ratio32_3, &ratio32_3, &ratio32_3, &ratio64_5, &ratio64_5, 
&ratio64_5, &ratio64_5, &ratio64_5, &ratio16_1, &ratio16_1, &ratio96_5, &ratio96_5, &ratio96_5, &ratio96_5, &ratio96_5, &ratio96_5, &ratio96_5, 
&ratio512_15, &ratio512_15, &ratio512_15, &ratio512_15, &ratio512_15, &ratio512_15, &ratio128_3}; 

static const ScaleNote * const Min9thPent3rdInv[128] = {&ratio5_256, &ratio5_144, &ratio5_144, &ratio5_144, &ratio5_144, &ratio5_144, &ratio5_144, &ratio1_24, &ratio1_24, &ratio1_24, &ratio1_24, &ratio5_96, &ratio5_96, 
&ratio5_96, &ratio5_96, &ratio5_96, &ratio1_16, &ratio1_16, &ratio5_64, &ratio5_64, &ratio5_64, &ratio5_64, &ratio5_64, &ratio5_64, &ratio5_64, 
&ratio5_36, &ratio5_36, &ratio5_36, &ratio5_36, &ratio5_36, &ratio5_36, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, &ratio5_24, &ratio5_24, 
&ratio5_24, &ratio5_24, &ratio5_24, &ratio1_4, &ratio1_4, &ratio5_16, &ratio5_16, &ratio5_16, &ratio5_16, &ratio5_16, &ratio5_16, &ratio5_16, 
&ratio5_9, &ratio5_9, &ratio5_9, &ratio5_9, &ratio5_9, &ratio5_9, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio5_6, &ratio5_6, 
&ratio5_6, &ratio5_6, &ratio5_6, &ratio1_1, &ratio1_1, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, 
&ratio20_9, &ratio20_9, &ratio20_9, &ratio20_9, &ratio20_9, &ratio20_9, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio10_3, &ratio10_3, 
&ratio10_3, &ratio10_3, &ratio10_3, &ratio4_1, &ratio4_1, &ratio5_1, &ratio5_1, &ratio5_1, &ratio5_1, &ratio5_1, &ratio5_1, &ratio5_1, 
&ratio80_9, &ratio80_9, &ratio80_9, &ratio80_9, &ratio80_9, &ratio80_9, &ratio32_3, &ratio32_3, &ratio32_3, &ratio32_3, &ratio40_3, &ratio40_3, 
&ratio40_3, &ratio40_3, &ratio40_3, &ratio16_1, &ratio16_1, &ratio20_1, &ratio20_1, &ratio20_1, &ratio20_1, &ratio20_1, &ratio20_1, &ratio20_1, 
&ratio320_9, &ratio320_9, &ratio320_9, &ratio320_9, &ratio320_9, &ratio320_9, &ratio128_3}; 

static const ScaleNote * const Maj9thPent4thInv[128] = {&ratio1_36, &ratio1_36, &ratio1_36, &ratio1_36, &ratio5_144, &ratio5_144, &ratio5_144, &ratio1_24, &ratio1_24, &ratio1_24, &ratio1_24, &ratio5_96, &ratio5_96, 
&ratio5_96, &ratio5_96, &ratio5_96, &ratio1_16, &ratio1_16, &ratio1_16, &ratio1_16, &ratio1_16, &ratio1_9, &ratio1_9, &ratio1_9, &ratio1_9, 
&ratio1_9, &ratio1_9, &ratio1_9, &ratio5_36, &ratio5_36, &ratio5_36, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, &ratio5_24, &ratio5_24, 
&ratio5_24, &ratio5_24, &ratio5_24, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio4_9, &ratio4_9, &ratio4_9, &ratio4_9, 
&ratio4_9, &ratio4_9, &ratio4_9, &ratio5_9, &ratio5_9, &ratio5_9, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio5_6, &ratio5_6, 
&ratio5_6, &ratio5_6, &ratio5_6, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio16_9, &ratio16_9, &ratio16_9, &ratio16_9, 
&ratio16_9, &ratio16_9, &ratio16_9, &ratio20_9, &ratio20_9, &ratio20_9, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio10_3, &ratio10_3, 
&ratio10_3, &ratio10_3, &ratio10_3, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio64_9, &ratio64_9, &ratio64_9, &ratio64_9, 
&ratio64_9, &ratio64_9, &ratio64_9, &ratio80_9, &ratio80_9, &ratio80_9, &ratio32_3, &ratio32_3, &ratio32_3, &ratio32_3, &ratio40_3, &ratio40_3, 
&ratio40_3, &ratio40_3, &ratio40_3, &ratio16_1, &ratio16_1, &ratio16_1, &ratio16_1, &ratio16_1, &ratio256_9, &ratio256_9, &ratio256_9, &ratio256_9, 
&ratio256_9, &ratio256_9, &ratio256_9, &ratio320_9, &ratio320_9, &ratio320_9, &ratio128_3}; 

static const ScaleNote * const Min9thPent4thInv[128] = {&ratio1_36, &ratio1_36, &ratio1_36, &ratio1_36, &ratio1_30, &ratio1_30, &ratio1_30, &ratio1_24, &ratio1_24, &ratio1_24, &ratio1_24, &ratio1_20, &ratio1_20, 
&ratio1_20, &ratio1_20, &ratio1_20, &ratio1_16, &ratio1_16, &ratio1_16, &ratio1_16, &ratio1_16, &ratio1_9, &ratio1_9, &ratio1_9, &ratio1_9, 
&ratio1_9, &ratio1_9, &ratio1_9, &ratio2_15, &ratio2_15, &ratio2_15, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_5, &ratio1_5, 
&ratio1_5, &ratio1_5, &ratio1_5, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio4_9, &ratio4_9, &ratio4_9, &ratio4_9, 
&ratio4_9, &ratio4_9, &ratio4_9, &ratio8_15, &ratio8_15, &ratio8_15, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio4_5, &ratio4_5, 
&ratio4_5, &ratio4_5, &ratio4_5, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio16_9, &ratio16_9, &ratio16_9, &ratio16_9, 
&ratio16_9, &ratio16_9, &ratio16_9, &ratio32_15, &ratio32_15, &ratio32_15, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio16_5, &ratio16_5, 
&ratio16_5, &ratio16_5, &ratio16_5, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio64_9, &ratio64_9, &ratio64_9, &ratio64_9, 
&ratio64_9, &ratio64_9, &ratio64_9, &ratio128_15, &ratio128_15, &ratio128_15, &ratio32_3, &ratio32_3, &ratio32_3, &ratio32_3, &ratio64_5, &ratio64_5, 
&ratio64_5, &ratio64_5, &ratio64_5, &ratio16_1, &ratio16_1, &ratio16_1, &ratio16_1, &ratio16_1, &ratio256_9, &ratio256_9, &ratio256_9, &ratio256_9, 
&ratio256_9, &ratio256_9, &ratio256_9, &ratio512_15, &ratio512_15, &ratio512_15, &ratio128_3}; 

static const ScaleNote * const starling[128] = {&ratio3_128, &ratio9_320, &ratio9_320, &ratio9_320, &ratio1_32, &ratio1_32, &ratio9_256, &ratio5_128, &ratio5_128, &ratio5_128, &ratio3_64, &ratio3_64, &ratio3_64, 
&ratio9_160, &ratio9_160, &ratio9_160, &ratio1_16, &ratio1_16, &ratio9_128, &ratio5_64, &ratio5_64, &ratio5_64, &ratio3_32, &ratio3_32, &ratio3_32, 
&ratio9_80, &ratio9_80, &ratio9_80, &ratio1_8, &ratio1_8, &ratio9_64, &ratio5_32, &ratio5_32, &ratio5_32, &ratio3_16, &ratio3_16, &ratio3_16, 
&ratio9_40, &ratio9_40, &ratio9_40, &ratio1_4, &ratio1_4, &ratio9_32, &ratio5_16, &ratio5_16, &ratio5_16, &ratio3_8, &ratio3_8, &ratio3_8, 
&ratio9_20, &ratio9_20, &ratio9_20, &ratio1_2, &ratio1_2, &ratio9_16, &ratio5_8, &ratio5_8, &ratio5_8, &ratio3_4, &ratio3_4, &ratio3_4, 
&ratio9_10, &ratio9_10, &ratio9_10, &ratio1_1, &ratio1_1, &ratio9_8, &ratio5_4, &ratio5_4, &ratio5_4, &ratio3_2, &ratio3_2, &ratio3_2, 
&ratio9_5, &ratio9_5, &ratio9_5, &ratio2_1, &ratio2_1, &ratio9_4, &ratio5_2, &ratio5_2, &ratio5_2, &ratio3_1, &ratio3_1, &ratio3_1, 
&ratio18_5, &ratio18_5, &ratio18_5, &ratio4_1, &ratio4_1, &ratio9_2, &ratio5_1, &ratio5_1, &ratio5_1, &ratio6_1, &ratio6_1, &ratio6_1, 
&ratio36_5, &ratio36_5, &ratio36_5, &ratio8_1, &ratio8_1, &ratio9_1, &ratio10_1, &ratio10_1, &ratio10_1, &ratio12_1, &ratio12_1, &ratio12_1, 
&ratio72_5, &ratio72_5, &ratio72_5, &ratio16_1, &ratio16_1, &ratio18_1, &ratio20_1, &ratio20_1, &ratio20_1, &ratio24_1, &ratio24_1, &ratio24_1, 
&ratio144_5, &ratio144_5, &ratio144_5, &ratio32_1, &ratio32_1, &ratio36_1, &ratio40_1}; 

static const ScaleNote * const starling1stInv[128] = {&ratio1_40, &ratio1_36, &ratio1_36, &ratio1_36, &ratio1_32, &ratio5_144, &ratio5_144, &ratio1_24, &ratio1_24, &ratio1_24, &ratio1_24, &ratio1_20, &ratio1_20, 
&ratio1_18, &ratio1_18, &ratio1_18, &ratio1_16, &ratio5_72, &ratio5_72, &ratio1_12, &ratio1_12, &ratio1_12, &ratio1_12, &ratio1_10, &ratio1_10, 
&ratio1_9, &ratio1_9, &ratio1_9, &ratio1_8, &ratio5_36, &ratio5_36, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_5, &ratio1_5, 
&ratio2_9, &ratio2_9, &ratio2_9, &ratio1_4, &ratio5_18, &ratio5_18, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio2_5, &ratio2_5, 
&ratio4_9, &ratio4_9, &ratio4_9, &ratio1_2, &ratio5_9, &ratio5_9, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio4_5, &ratio4_5, 
&ratio8_9, &ratio8_9, &ratio8_9, &ratio1_1, &ratio10_9, &ratio10_9, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio8_5, &ratio8_5, 
&ratio16_9, &ratio16_9, &ratio16_9, &ratio2_1, &ratio20_9, &ratio20_9, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio16_5, &ratio16_5, 
&ratio32_9, &ratio32_9, &ratio32_9, &ratio4_1, &ratio40_9, &ratio40_9, &ratio16_3, &ratio16_3, &ratio16_3, &ratio16_3, &ratio32_5, &ratio32_5, 
&ratio64_9, &ratio64_9, &ratio64_9, &ratio8_1, &ratio80_9, &ratio80_9, &ratio32_3, &ratio32_3, &ratio32_3, &ratio32_3, &ratio64_5, &ratio64_5, 
&ratio128_9, &ratio128_9, &ratio128_9, &ratio16_1, &ratio160_9, &ratio160_9, &ratio64_3, &ratio64_3, &ratio64_3, &ratio64_3, &ratio128_5, &ratio128_5, 
&ratio256_9, &ratio256_9, &ratio256_9, &ratio32_1, &ratio320_9, &ratio320_9, &ratio128_3}; 

static const ScaleNote * const starling2ndInv[128] = {&ratio1_40, &ratio1_40, &ratio9_320, &ratio9_320, &ratio1_32, &ratio1_32, &ratio3_80, &ratio3_80, &ratio3_80, &ratio9_200, &ratio9_200, &ratio9_200, &ratio1_20, 
&ratio1_20, &ratio9_160, &ratio9_160, &ratio1_16, &ratio1_16, &ratio3_40, &ratio3_40, &ratio3_40, &ratio9_100, &ratio9_100, &ratio9_100, &ratio1_10, 
&ratio1_10, &ratio9_80, &ratio9_80, &ratio1_8, &ratio1_8, &ratio3_20, &ratio3_20, &ratio3_20, &ratio9_50, &ratio9_50, &ratio9_50, &ratio1_5, 
&ratio1_5, &ratio9_40, &ratio9_40, &ratio1_4, &ratio1_4, &ratio3_10, &ratio3_10, &ratio3_10, &ratio9_25, &ratio9_25, &ratio9_25, &ratio2_5, 
&ratio2_5, &ratio9_20, &ratio9_20, &ratio1_2, &ratio1_2, &ratio3_5, &ratio3_5, &ratio3_5, &ratio18_25, &ratio18_25, &ratio18_25, &ratio4_5, 
&ratio4_5, &ratio9_10, &ratio9_10, &ratio1_1, &ratio1_1, &ratio6_5, &ratio6_5, &ratio6_5, &ratio36_25, &ratio36_25, &ratio36_25, &ratio8_5, 
&ratio8_5, &ratio9_5, &ratio9_5, &ratio2_1, &ratio2_1, &ratio12_5, &ratio12_5, &ratio12_5, &ratio72_25, &ratio72_25, &ratio72_25, &ratio16_5, 
&ratio16_5, &ratio18_5, &ratio18_5, &ratio4_1, &ratio4_1, &ratio24_5, &ratio24_5, &ratio24_5, &ratio144_25, &ratio144_25, &ratio144_25, &ratio32_5, 
&ratio32_5, &ratio36_5, &ratio36_5, &ratio8_1, &ratio8_1, &ratio48_5, &ratio48_5, &ratio48_5, &ratio288_25, &ratio288_25, &ratio288_25, &ratio64_5, 
&ratio64_5, &ratio72_5, &ratio72_5, &ratio16_1, &ratio16_1, &ratio96_5, &ratio96_5, &ratio96_5, &ratio576_25, &ratio576_25, &ratio576_25, &ratio128_5, 
&ratio128_5, &ratio144_5, &ratio144_5, &ratio32_1, &ratio32_1, &ratio192_5, &ratio192_5}; 

static const ScaleNote * const starling3rdInv[128] = {&ratio5_192, &ratio5_192, &ratio5_192, &ratio5_192, &ratio1_32, &ratio1_32, &ratio3_80, &ratio3_80, &ratio1_24, &ratio1_24, &ratio3_64, &ratio3_64, &ratio5_96, 
&ratio5_96, &ratio5_96, &ratio5_96, &ratio1_16, &ratio1_16, &ratio3_40, &ratio3_40, &ratio1_12, &ratio1_12, &ratio3_32, &ratio3_32, &ratio5_48, 
&ratio5_48, &ratio5_48, &ratio5_48, &ratio1_8, &ratio1_8, &ratio3_20, &ratio3_20, &ratio1_6, &ratio1_6, &ratio3_16, &ratio3_16, &ratio5_24, 
&ratio5_24, &ratio5_24, &ratio5_24, &ratio1_4, &ratio1_4, &ratio3_10, &ratio3_10, &ratio1_3, &ratio1_3, &ratio3_8, &ratio3_8, &ratio5_12, 
&ratio5_12, &ratio5_12, &ratio5_12, &ratio1_2, &ratio1_2, &ratio3_5, &ratio3_5, &ratio2_3, &ratio2_3, &ratio3_4, &ratio3_4, &ratio5_6, 
&ratio5_6, &ratio5_6, &ratio5_6, &ratio1_1, &ratio1_1, &ratio6_5, &ratio6_5, &ratio4_3, &ratio4_3, &ratio3_2, &ratio3_2, &ratio5_3, 
&ratio5_3, &ratio5_3, &ratio5_3, &ratio2_1, &ratio2_1, &ratio12_5, &ratio12_5, &ratio8_3, &ratio8_3, &ratio3_1, &ratio3_1, &ratio10_3, 
&ratio10_3, &ratio10_3, &ratio10_3, &ratio4_1, &ratio4_1, &ratio24_5, &ratio24_5, &ratio16_3, &ratio16_3, &ratio6_1, &ratio6_1, &ratio20_3, 
&ratio20_3, &ratio20_3, &ratio20_3, &ratio8_1, &ratio8_1, &ratio48_5, &ratio48_5, &ratio32_3, &ratio32_3, &ratio12_1, &ratio12_1, &ratio40_3, 
&ratio40_3, &ratio40_3, &ratio40_3, &ratio16_1, &ratio16_1, &ratio96_5, &ratio96_5, &ratio64_3, &ratio64_3, &ratio24_1, &ratio24_1, &ratio80_3, 
&ratio80_3, &ratio80_3, &ratio80_3, &ratio32_1, &ratio32_1, &ratio192_5, &ratio192_5}; 

static const ScaleNote * const Starling4thInv[128] = {&ratio5_192, &ratio1_36, &ratio1_36, &ratio1_36, &ratio1_30, &ratio1_30, &ratio1_30, &ratio1_30, &ratio1_30, &ratio1_30, &ratio1_30, &ratio1_30, &ratio1_30, 
&ratio1_30, &ratio1_30, &ratio1_30, &ratio1_16, &ratio1_16, &ratio1_16, &ratio25_288, &ratio25_288, &ratio25_288, &ratio25_288, &ratio5_48, &ratio5_48, 
&ratio1_9, &ratio1_9, &ratio1_9, &ratio2_15, &ratio2_15, &ratio2_15, &ratio2_15, &ratio2_15, &ratio2_15, &ratio2_15, &ratio2_15, &ratio2_15, 
&ratio2_15, &ratio2_15, &ratio2_15, &ratio1_4, &ratio1_4, &ratio1_4, &ratio25_72, &ratio25_72, &ratio25_72, &ratio25_72, &ratio5_12, &ratio5_12, 
&ratio4_9, &ratio4_9, &ratio4_9, &ratio8_15, &ratio8_15, &ratio8_15, &ratio8_15, &ratio8_15, &ratio8_15, &ratio8_15, &ratio8_15, &ratio8_15, 
&ratio8_15, &ratio8_15, &ratio8_15, &ratio1_1, &ratio1_1, &ratio1_1, &ratio25_18, &ratio25_18, &ratio25_18, &ratio25_18, &ratio5_3, &ratio5_3, 
&ratio16_9, &ratio16_9, &ratio16_9, &ratio32_15, &ratio32_15, &ratio32_15, &ratio32_15, &ratio32_15, &ratio32_15, &ratio32_15, &ratio32_15, &ratio32_15, 
&ratio32_15, &ratio32_15, &ratio32_15, &ratio4_1, &ratio4_1, &ratio4_1, &ratio50_9, &ratio50_9, &ratio50_9, &ratio50_9, &ratio20_3, &ratio20_3, 
&ratio64_9, &ratio64_9, &ratio64_9, &ratio128_15, &ratio128_15, &ratio128_15, &ratio128_15, &ratio128_15, &ratio128_15, &ratio128_15, &ratio128_15, &ratio128_15, 
&ratio128_15, &ratio128_15, &ratio128_15, &ratio16_1, &ratio16_1, &ratio16_1, &ratio200_9, &ratio200_9, &ratio200_9, &ratio200_9, &ratio80_3, &ratio80_3, 
&ratio256_9, &ratio256_9, &ratio256_9, &ratio512_15, &ratio512_15, &ratio512_15, &ratio512_15}; 

static const ScaleNote * const tridecimalSubminor9th[128] = {&ratio3_128, &ratio11_384, &ratio11_384, &ratio11_384, &ratio13_384, &ratio13_384, &ratio13_384, &ratio13_384, &ratio13_384, &ratio13_384, &ratio13_384, &ratio13_384, &ratio13_384, 
&ratio13_384, &ratio13_384, &ratio13_384, &ratio1_16, &ratio1_16, &ratio7_96, &ratio7_96, &ratio7_96, &ratio3_32, &ratio3_32, &ratio3_32, &ratio3_32, 
&ratio11_96, &ratio11_96, &ratio11_96, &ratio13_96, &ratio13_96, &ratio13_96, &ratio13_96, &ratio13_96, &ratio13_96, &ratio13_96, &ratio13_96, &ratio13_96, 
&ratio13_96, &ratio13_96, &ratio13_96, &ratio1_4, &ratio1_4, &ratio7_24, &ratio7_24, &ratio7_24, &ratio3_8, &ratio3_8, &ratio3_8, &ratio3_8, 
&ratio11_24, &ratio11_24, &ratio11_24, &ratio13_24, &ratio13_24, &ratio13_24, &ratio13_24, &ratio13_24, &ratio13_24, &ratio13_24, &ratio13_24, &ratio13_24, 
&ratio13_24, &ratio13_24, &ratio13_24, &ratio1_1, &ratio1_1, &ratio7_6, &ratio7_6, &ratio7_6, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, 
&ratio11_6, &ratio11_6, &ratio11_6, &ratio13_6, &ratio13_6, &ratio13_6, &ratio13_6, &ratio13_6, &ratio13_6, &ratio13_6, &ratio13_6, &ratio13_6, 
&ratio13_6, &ratio13_6, &ratio13_6, &ratio4_1, &ratio4_1, &ratio14_3, &ratio14_3, &ratio14_3, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, 
&ratio22_3, &ratio22_3, &ratio22_3, &ratio26_3, &ratio26_3, &ratio26_3, &ratio26_3, &ratio26_3, &ratio26_3, &ratio26_3, &ratio26_3, &ratio26_3, 
&ratio26_3, &ratio26_3, &ratio26_3, &ratio16_1, &ratio16_1, &ratio56_3, &ratio56_3, &ratio56_3, &ratio24_1, &ratio24_1, &ratio24_1, &ratio24_1, 
&ratio88_3, &ratio88_3, &ratio88_3, &ratio104_3, &ratio104_3, &ratio104_3, &ratio104_3}; 



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






static const ScaleNote **integerRatiosGrid[8] = {integerRatios1, integerRatios2, integerRatios3, integerRatios4, integerRatios5, integerRatios6, integerRatios7, integerRatios8}; 

static const ScaleNote **pentamodal5primefullspanGrid[8] = {majpenta5primefullspan, maj2min75primefullspan, maj3dom75primefullspan, subdompenta5primefullspan, dompenta5primefullspan, relmin75primefullspan, dim75primefullspan, majmaj75primefullspan}; 

static const ScaleNote **harmSubharmfullspanGrid[8] = {harmSubharmfullspan1, harmSubharmfullspan2, harmSubharmfullspan3, harmSubharmfullspan4, harmSubharmfullspan5, harmSubharmfullspan6, harmSubharmfullspan7, harmSubharmfullspan8}; 

static const ScaleNote **modal5primefullspanGrid[8] = {dominant5primefullspan, major5primefullspan, dorian5primefullspan, phrygian5primefullspan, lydian5primefullspan, mixolydian5primefullspan, aeolian5primefullspan, locrian5primefullspan}; 

static const ScaleNote **harmSubharmGrid[8] = {harmSubharm1, harmSubharm2, harmSubharm3, harmSubharm4, harmSubharm5, harmSubharm6, harmSubharm7, harmSubharm8}; 

static const ScaleNote **harmFolded4Grid[4] = {harmFolded8_2oct, harmFolded12_2oct, HarmFolded12_3oct, HarmFolded16_4oct}; 

static const ScaleNote **pentamodal5primeGrid[8] = {majpenta5prime, maj2min75prime, maj3dom75prime, subdompenta5prime, dompenta5prime, relmin75prime, dim75prime, majmaj75prime}; 

static const ScaleNote **triadsGrid[8] = {majTriad, majTriad1stInv, majTriad2ndInv, minTriad, minTriad2ndInv, MinTriad1stInv, quartalTriad, quartalTriad1stInv}; 

static const ScaleNote **seventhTetradsMinimalProgressionGrid[16] = {subDom7thRotate, min7th, dom7thRotate, min7th2ndInv, maj7th1stInv, maj7th, dom7th, harmDom7th, min7th1stInv, maj7th2ndInv, harmDom7th2ndInv, min7th3rdInv, maj7th3rdInv, harmDom7th1stInv, subDom7th, harmDom7th3rdInv}; 

static const ScaleNote **seventhTetradsGrid[16] = {maj7th, maj7th2ndInv, maj7th1stInv, maj7th3rdInv, min7th, min7th2ndInv, min7th1stInv, min7th3rdInv, harmDom7th, harmDom7th1stInv, harmDom7th2ndInv, harmDom7th3rdInv, dom7th, subDom7th, dom7thRotate, subDom7thRotate}; 

static const ScaleNote **modesOfLimitedTranspositionGrid[16] = {messiaenOctatonic1, messiaenOctatonic2, messiaenModeIII1, messiaenModeIII2, messiaenModeIII3, messiaenModeIV1, messiaenModeIV2, messiaenModeIV3, messiaenModeIV4, messiaenModeV1, messiaenModeV2, messiaenModeV3, messiaenModeVI1, messiaenModeVI2, messiaenModeVI3, messiaenModeVI4}; 

static const ScaleNote **majMin9thPentStarlingGrid[16] = {maj9thPent, min9thPent, maj9thPent1stInv, min9thPent1stInv, maj9thPent2ndInv, min9thPent2ndInv, maj9thPent3rdInv, Min9thPent3rdInv, Maj9thPent4thInv, Min9thPent4thInv, starling, starling1stInv, starling2ndInv, starling3rdInv, Starling4thInv, tridecimalSubminor9th}; 

static const ScaleNote **simpleRhythmsGrid[8] = {simpleRhythms1, simpleRhythms2, simpleRhythms3, simpleRhythms4, simpleRhythms5, simpleRhythms6, simpleRhythms7, simpleRhythms8}; 

static const ScaleNote **simpleRhythms16Grid[8] = {SimpleRhythms1_16, SimpleRhythms2_16, SimpleRhythms3_16, SimpleRhythms4_16, SimpleRhythms5_16, SimpleRhythms6_16, SimpleRhythms7_16, SimpleRhythms8_16}; 

static const ScaleNote **rhythmDivisionsResetGrid[8] = {rhythmDivisionsReset1, rhythmDivisionsReset2, rhythmDivisionsReset3, rhythmDivisionsReset4, rhythmDivisionsReset5, rhythmDivisionsReset6, rhythmDivisionsReset7, rhythmDivisionsReset8}; 

static const ScaleNote **polyResetsGrid[16] = {polyResets1, polyResets2, polyResets3, polyResets4, polyResets5, polyResets6, polyResets7, polyResets8, polyResets9, polyResets10, polyResets11, polyResets12, polyResets13, polyResets14, polyResets15, polyResets16}; 




