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



static const ScaleNote **harmSubharmGrid[8];
Scale harmSubharm;
static const ScaleNote **modal5primeGrid[8];
Scale modal5prime;
static const ScaleNote **harmSubharmfullspanGrid[8];
Scale harmSubharmfullspan;
static const ScaleNote **modal5primefullspanGrid[8];
Scale modal5primefullspan;


static const ScaleNote ratio80_7 = {748982, 3681400539, 7};
static const ScaleNote ratio9_320 = {1843, 858993459, 320};
static const ScaleNote ratio3_32 = {6144, 0, 32};
static const ScaleNote ratio3_7 = {28086, 3681400539, 7};
static const ScaleNote ratio1_12 = {5461, 1431655765, 12};
static const ScaleNote ratio1_6 = {10922, 2863311530, 6};
static const ScaleNote ratio1_8 = {8192, 0, 8};
static const ScaleNote ratio9_40 = {14745, 2576980377, 40};
static const ScaleNote ratio4_15 = {17476, 1145324612, 15};
static const ScaleNote ratio1_160 = {409, 2576980377, 160};
static const ScaleNote ratio8_7 = {74898, 1227133513, 7};
static const ScaleNote ratio5_112 = {2925, 3067833782, 112};
static const ScaleNote ratio1_20 = {3276, 3435973836, 20};
static const ScaleNote ratio7_2 = {229376, 0, 2};
static const ScaleNote ratio5_8 = {40960, 0, 8};
static const ScaleNote ratio10_3 = {218453, 1431655765, 3};
static const ScaleNote ratio5_1 = {327680, 0, 1};
static const ScaleNote ratio24_5 = {314572, 3435973836, 5};
static const ScaleNote ratio40_1 = {2621440, 0, 1};
static const ScaleNote ratio9_5 = {117964, 3435973836, 5};
static const ScaleNote ratio3_80 = {2457, 2576980377, 80};
static const ScaleNote ratio3_512 = {384, 0, 512};
static const ScaleNote ratio25_576 = {2844, 1908874353, 576};
static const ScaleNote ratio10_1 = {655360, 0, 1};
static const ScaleNote ratio4_1 = {262144, 0, 1};
static const ScaleNote ratio1_3 = {21845, 1431655765, 3};
static const ScaleNote ratio9_16 = {36864, 0, 16};
static const ScaleNote ratio16_3 = {349525, 1431655765, 3};
static const ScaleNote ratio64_3 = {1398101, 1431655765, 3};
static const ScaleNote ratio1_128 = {512, 0, 128};
static const ScaleNote ratio32_1 = {2097152, 0, 1};
static const ScaleNote ratio25_18 = {91022, 954437176, 18};
static const ScaleNote ratio1_15 = {4369, 286331153, 15};
static const ScaleNote ratio15_512 = {1920, 0, 512};
static const ScaleNote ratio1_2 = {32768, 0, 2};
static const ScaleNote ratio3_56 = {3510, 3681400539, 56};
static const ScaleNote ratio1_320 = {204, 3435973836, 320};
static const ScaleNote ratio9_4 = {147456, 0, 4};
static const ScaleNote ratio7_4 = {114688, 0, 4};
static const ScaleNote ratio200_9 = {1456355, 2386092942, 9};
static const ScaleNote ratio3_256 = {768, 0, 256};
static const ScaleNote ratio5_6 = {54613, 1431655765, 6};
static const ScaleNote ratio3_64 = {3072, 0, 64};
static const ScaleNote ratio5_48 = {6826, 2863311530, 48};
static const ScaleNote ratio128_15 = {559240, 2290649224, 15};
static const ScaleNote ratio100_9 = {728177, 3340530119, 9};
static const ScaleNote ratio5_192 = {1706, 2863311530, 192};
static const ScaleNote ratio36_5 = {471859, 858993459, 5};
static const ScaleNote ratio1_64 = {1024, 0, 64};
static const ScaleNote ratio5_32 = {10240, 0, 32};
static const ScaleNote ratio7_3 = {152917, 1431655765, 3};
static const ScaleNote ratio5_7 = {46811, 1840700269, 7};
static const ScaleNote ratio15_256 = {3840, 0, 256};
static const ScaleNote ratio15_32 = {30720, 0, 32};
static const ScaleNote ratio7_256 = {1792, 0, 256};
static const ScaleNote ratio9_8 = {73728, 0, 8};
static const ScaleNote ratio14_1 = {917504, 0, 1};
static const ScaleNote ratio32_15 = {139810, 572662306, 15};
static const ScaleNote ratio72_5 = {943718, 1717986918, 5};
static const ScaleNote ratio1_96 = {682, 2863311530, 96};
static const ScaleNote ratio1_80 = {819, 858993459, 80};
static const ScaleNote ratio56_3 = {1223338, 2863311531, 3};
static const ScaleNote ratio16_5 = {209715, 858993459, 5};
static const ScaleNote ratio3_1 = {196608, 0, 1};
static const ScaleNote ratio24_1 = {1572864, 0, 1};
static const ScaleNote ratio64_7 = {599186, 1227133513, 7};
static const ScaleNote ratio48_7 = {449389, 3067833782, 7};
static const ScaleNote ratio9_20 = {29491, 858993459, 20};
static const ScaleNote ratio9_80 = {7372, 3435973836, 80};
static const ScaleNote ratio25_9 = {182044, 1908874353, 9};
static const ScaleNote ratio12_5 = {157286, 1717986918, 5};
static const ScaleNote ratio6_1 = {393216, 0, 1};
static const ScaleNote ratio64_5 = {838860, 3435973837, 5};
static const ScaleNote ratio9_256 = {2304, 0, 256};
static const ScaleNote ratio1_7 = {9362, 1227133513, 7};
static const ScaleNote ratio80_3 = {1747626, 2863311531, 3};
static const ScaleNote ratio16_7 = {149796, 2454267026, 7};
static const ScaleNote ratio1_1 = {65536, 0, 1};
static const ScaleNote ratio50_9 = {364088, 3817748707, 9};
static const ScaleNote ratio1_256 = {256, 0, 256};
static const ScaleNote ratio5_24 = {13653, 1431655765, 24};
static const ScaleNote ratio15_64 = {15360, 0, 64};
static const ScaleNote ratio7_512 = {896, 0, 512};
static const ScaleNote ratio1_28 = {2340, 2454267026, 28};
static const ScaleNote ratio3_2 = {98304, 0, 2};
static const ScaleNote ratio5_96 = {3413, 1431655765, 96};
static const ScaleNote ratio1_30 = {2184, 2290649224, 30};
static const ScaleNote ratio2_1 = {131072, 0, 1};
static const ScaleNote ratio9_2 = {294912, 0, 2};
static const ScaleNote ratio12_1 = {786432, 0, 1};
static const ScaleNote ratio2_7 = {18724, 2454267026, 7};
static const ScaleNote ratio5_128 = {2560, 0, 128};
static const ScaleNote ratio1_192 = {341, 1431655765, 192};
static const ScaleNote ratio512_15 = {2236962, 572662306, 15};
static const ScaleNote ratio144_5 = {1887436, 3435973837, 5};
static const ScaleNote ratio1_5 = {13107, 858993459, 5};
static const ScaleNote ratio5_512 = {640, 0, 512};
static const ScaleNote ratio7_128 = {3584, 0, 128};
static const ScaleNote ratio15_16 = {61440, 0, 16};
static const ScaleNote ratio18_5 = {235929, 2576980377, 5};
static const ScaleNote ratio6_5 = {78643, 858993459, 5};
static const ScaleNote ratio5_64 = {5120, 0, 64};
static const ScaleNote ratio1_48 = {1365, 1431655765, 48};
static const ScaleNote ratio7_1 = {458752, 0, 1};
static const ScaleNote ratio2_15 = {8738, 572662306, 15};
static const ScaleNote ratio16_1 = {1048576, 0, 1};
static const ScaleNote ratio7_32 = {14336, 0, 32};
static const ScaleNote ratio3_4 = {49152, 0, 4};
static const ScaleNote ratio5_3 = {109226, 2863311530, 3};
static const ScaleNote ratio7_8 = {57344, 0, 8};
static const ScaleNote ratio7_64 = {7168, 0, 64};
static const ScaleNote ratio9_160 = {3686, 1717986918, 160};
static const ScaleNote ratio6_7 = {56173, 3067833782, 7};
static const ScaleNote ratio15_2 = {491520, 0, 2};
static const ScaleNote ratio5_2 = {163840, 0, 2};
static const ScaleNote ratio3_112 = {1755, 1840700269, 112};
static const ScaleNote ratio128_5 = {1677721, 2576980378, 5};
static const ScaleNote ratio4_5 = {52428, 3435973836, 5};
static const ScaleNote ratio40_3 = {873813, 1431655765, 3};
static const ScaleNote ratio25_72 = {22755, 2386092942, 72};
static const ScaleNote ratio15_128 = {7680, 0, 128};
static const ScaleNote ratio8_1 = {524288, 0, 1};
static const ScaleNote ratio1_16 = {4096, 0, 16};
static const ScaleNote ratio15_8 = {122880, 0, 8};
static const ScaleNote ratio9_1 = {589824, 0, 1};
static const ScaleNote ratio2_5 = {26214, 1717986918, 5};
static const ScaleNote ratio4_3 = {87381, 1431655765, 3};
static const ScaleNote ratio9_10 = {58982, 1717986918, 10};
static const ScaleNote ratio36_1 = {2359296, 0, 1};
static const ScaleNote ratio3_20 = {9830, 1717986918, 20};
static const ScaleNote ratio256_15 = {1118481, 286331153, 15};
static const ScaleNote ratio7_80 = {5734, 1717986918, 80};
static const ScaleNote ratio20_3 = {436906, 2863311530, 3};
static const ScaleNote ratio15_4 = {245760, 0, 4};
static const ScaleNote ratio1_40 = {1638, 1717986918, 40};
static const ScaleNote ratio7_6 = {76458, 2863311530, 6};
static const ScaleNote ratio48_5 = {629145, 2576980377, 5};
static const ScaleNote ratio32_5 = {419430, 1717986918, 5};
static const ScaleNote ratio8_15 = {34952, 2290649224, 15};
static const ScaleNote ratio1_32 = {2048, 0, 32};
static const ScaleNote ratio96_5 = {1258291, 858993459, 5};
static const ScaleNote ratio1_18 = {3640, 3817748707, 18};
static const ScaleNote ratio3_10 = {19660, 3435973836, 10};
static const ScaleNote ratio16_15 = {69905, 286331153, 15};
static const ScaleNote ratio30_1 = {1966080, 0, 1};
static const ScaleNote ratio2_3 = {43690, 2863311530, 3};
static const ScaleNote ratio32_7 = {299593, 613566756, 7};
static const ScaleNote ratio7_5 = {91750, 1717986918, 5};
static const ScaleNote ratio3_16 = {12288, 0, 16};
static const ScaleNote ratio25_288 = {5688, 3817748707, 288};
static const ScaleNote ratio1_4 = {16384, 0, 4};
static const ScaleNote ratio18_1 = {1179648, 0, 1};
static const ScaleNote ratio1_14 = {4681, 613566756, 14};
static const ScaleNote ratio3_5 = {39321, 2576980377, 5};
static const ScaleNote ratio5_16 = {20480, 0, 16};
static const ScaleNote ratio64_15 = {279620, 1145324612, 15};
static const ScaleNote ratio96_7 = {898779, 1840700269, 7};
static const ScaleNote ratio4_7 = {37449, 613566756, 7};
static const ScaleNote ratio32_3 = {699050, 2863311530, 3};
static const ScaleNote ratio7_96 = {4778, 2863311530, 96};
static const ScaleNote ratio7_16 = {28672, 0, 16};
static const ScaleNote ratio192_5 = {2516582, 1717986918, 5};
static const ScaleNote ratio1_10 = {6553, 2576980377, 10};
static const ScaleNote ratio1_56 = {1170, 1227133513, 56};
static const ScaleNote ratio15_1 = {983040, 0, 1};
static const ScaleNote ratio5_4 = {81920, 0, 4};
static const ScaleNote ratio3_128 = {1536, 0, 128};
static const ScaleNote ratio5_256 = {1280, 0, 256};
static const ScaleNote ratio9_128 = {4608, 0, 128};
static const ScaleNote ratio20_1 = {1310720, 0, 1};
static const ScaleNote ratio5_12 = {27306, 2863311530, 12};
static const ScaleNote ratio3_40 = {4915, 858993459, 40};
static const ScaleNote ratio25_144 = {11377, 3340530119, 144};
static const ScaleNote ratio8_3 = {174762, 2863311530, 3};
static const ScaleNote ratio7_48 = {9557, 1431655765, 48};
static const ScaleNote ratio1_24 = {2730, 2863311530, 24};
static const ScaleNote ratio3_8 = {24576, 0, 8};
static const ScaleNote ratio9_64 = {9216, 0, 64};
static const ScaleNote ratio9_32 = {18432, 0, 32};
static const ScaleNote ratio25_36 = {45511, 477218588, 36};
static const ScaleNote ratio8_5 = {104857, 2576980377, 5};



static const ScaleNote *harmSubharm1[128] = {&ratio1_320, &ratio1_320, &ratio1_320, &ratio1_320, &ratio1_256, &ratio1_256, &ratio1_256, &ratio1_256, &ratio1_192, &ratio1_192, &ratio1_192, &ratio1_192, &ratio1_192, 
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

static const ScaleNote *harmSubharm2[128] = {&ratio1_160, &ratio1_160, &ratio1_160, &ratio1_160, &ratio1_128, &ratio1_128, &ratio1_128, &ratio1_128, &ratio1_96, &ratio1_96, &ratio1_96, &ratio1_96, &ratio1_96, 
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

static const ScaleNote *harmSubharm3[128] = {&ratio3_512, &ratio3_512, &ratio3_512, &ratio3_512, &ratio3_512, &ratio3_512, &ratio3_256, &ratio3_256, &ratio3_256, &ratio3_256, &ratio3_256, &ratio3_256, &ratio3_256, 
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

static const ScaleNote *harmSubharm4[128] = {&ratio1_80, &ratio1_80, &ratio1_80, &ratio1_80, &ratio1_64, &ratio1_64, &ratio1_64, &ratio1_48, &ratio1_48, &ratio1_48, &ratio1_48, &ratio1_48, &ratio1_48, 
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

static const ScaleNote *harmSubharm5[128] = {&ratio5_512, &ratio5_512, &ratio5_256, &ratio5_256, &ratio5_256, &ratio5_256, &ratio5_256, &ratio5_256, &ratio5_256, &ratio5_256, &ratio5_256, &ratio5_256, &ratio5_256, 
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

static const ScaleNote *harmSubharm6[128] = {&ratio3_256, &ratio3_256, &ratio3_256, &ratio3_256, &ratio3_256, &ratio3_256, &ratio3_128, &ratio3_128, &ratio3_128, &ratio3_128, &ratio3_128, &ratio3_128, &ratio3_128, 
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

static const ScaleNote *harmSubharm7[128] = {&ratio7_512, &ratio7_512, &ratio7_512, &ratio7_512, &ratio7_512, &ratio7_512, &ratio7_512, &ratio7_512, &ratio7_256, &ratio7_256, &ratio7_256, &ratio7_256, &ratio7_256, 
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

static const ScaleNote *harmSubharm8[128] = {&ratio1_40, &ratio1_40, &ratio1_40, &ratio1_32, &ratio1_32, &ratio1_32, &ratio1_32, &ratio1_24, &ratio1_24, &ratio1_24, &ratio1_24, &ratio1_24, &ratio1_24, 
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



static const ScaleNote *chromatic5prime[128] = {&ratio1_40, &ratio5_192, &ratio9_320, &ratio15_512, &ratio1_32, &ratio1_30, &ratio9_256, &ratio3_80, &ratio1_24, &ratio25_576, &ratio25_576, &ratio3_64, &ratio1_20, 
&ratio5_96, &ratio9_160, &ratio15_256, &ratio1_16, &ratio1_15, &ratio9_128, &ratio3_40, &ratio1_12, &ratio25_288, &ratio25_288, &ratio3_32, &ratio1_10, 
&ratio5_48, &ratio9_80, &ratio15_128, &ratio1_8, &ratio2_15, &ratio9_64, &ratio3_20, &ratio1_6, &ratio25_144, &ratio25_144, &ratio3_16, &ratio1_5, 
&ratio5_24, &ratio9_40, &ratio15_64, &ratio1_4, &ratio4_15, &ratio9_32, &ratio3_10, &ratio1_3, &ratio25_72, &ratio25_72, &ratio3_8, &ratio2_5, 
&ratio5_12, &ratio9_20, &ratio15_32, &ratio1_2, &ratio8_15, &ratio9_16, &ratio3_5, &ratio2_3, &ratio25_36, &ratio25_36, &ratio3_4, &ratio4_5, 
&ratio5_6, &ratio9_10, &ratio15_16, &ratio1_1, &ratio16_15, &ratio9_8, &ratio6_5, &ratio4_3, &ratio25_18, &ratio25_18, &ratio3_2, &ratio8_5, 
&ratio5_3, &ratio9_5, &ratio15_8, &ratio2_1, &ratio32_15, &ratio9_4, &ratio12_5, &ratio8_3, &ratio25_9, &ratio25_9, &ratio3_1, &ratio16_5, 
&ratio10_3, &ratio18_5, &ratio15_4, &ratio4_1, &ratio64_15, &ratio9_2, &ratio24_5, &ratio16_3, &ratio50_9, &ratio50_9, &ratio6_1, &ratio32_5, 
&ratio20_3, &ratio36_5, &ratio15_2, &ratio8_1, &ratio128_15, &ratio9_1, &ratio48_5, &ratio32_3, &ratio100_9, &ratio100_9, &ratio12_1, &ratio64_5, 
&ratio40_3, &ratio72_5, &ratio15_1, &ratio16_1, &ratio256_15, &ratio18_1, &ratio96_5, &ratio64_3, &ratio200_9, &ratio200_9, &ratio24_1, &ratio128_5, 
&ratio80_3, &ratio144_5, &ratio30_1, &ratio32_1, &ratio512_15, &ratio36_1, &ratio192_5}; 

static const ScaleNote *major5prime[128] = {&ratio5_192, &ratio5_192, &ratio15_512, &ratio15_512, &ratio1_32, &ratio1_32, &ratio9_256, &ratio5_128, &ratio1_24, &ratio1_24, &ratio3_64, &ratio3_64, &ratio5_96, 
&ratio5_96, &ratio15_256, &ratio15_256, &ratio1_16, &ratio1_16, &ratio9_128, &ratio5_64, &ratio1_12, &ratio1_12, &ratio3_32, &ratio3_32, &ratio5_48, 
&ratio5_48, &ratio15_128, &ratio15_128, &ratio1_8, &ratio1_8, &ratio9_64, &ratio5_32, &ratio1_6, &ratio1_6, &ratio3_16, &ratio3_16, &ratio5_24, 
&ratio5_24, &ratio15_64, &ratio15_64, &ratio1_4, &ratio1_4, &ratio9_32, &ratio5_16, &ratio1_3, &ratio1_3, &ratio3_8, &ratio3_8, &ratio5_12, 
&ratio5_12, &ratio15_32, &ratio15_32, &ratio1_2, &ratio1_2, &ratio9_16, &ratio5_8, &ratio2_3, &ratio2_3, &ratio3_4, &ratio3_4, &ratio5_6, 
&ratio5_6, &ratio15_16, &ratio15_16, &ratio1_1, &ratio1_1, &ratio9_8, &ratio5_4, &ratio4_3, &ratio4_3, &ratio3_2, &ratio3_2, &ratio5_3, 
&ratio5_3, &ratio15_8, &ratio15_8, &ratio2_1, &ratio2_1, &ratio9_4, &ratio5_2, &ratio8_3, &ratio8_3, &ratio3_1, &ratio3_1, &ratio10_3, 
&ratio10_3, &ratio15_4, &ratio15_4, &ratio4_1, &ratio4_1, &ratio9_2, &ratio5_1, &ratio16_3, &ratio16_3, &ratio6_1, &ratio6_1, &ratio20_3, 
&ratio20_3, &ratio15_2, &ratio15_2, &ratio8_1, &ratio8_1, &ratio9_1, &ratio10_1, &ratio32_3, &ratio32_3, &ratio12_1, &ratio12_1, &ratio40_3, 
&ratio40_3, &ratio15_1, &ratio15_1, &ratio16_1, &ratio16_1, &ratio18_1, &ratio20_1, &ratio64_3, &ratio64_3, &ratio24_1, &ratio24_1, &ratio80_3, 
&ratio80_3, &ratio30_1, &ratio30_1, &ratio32_1, &ratio32_1, &ratio36_1, &ratio40_1}; 

static const ScaleNote *dorian5prime[128] = {&ratio5_192, &ratio5_192, &ratio9_320, &ratio9_320, &ratio1_32, &ratio1_32, &ratio9_256, &ratio5_128, &ratio5_128, &ratio5_128, &ratio3_64, &ratio3_64, &ratio5_96, 
&ratio5_96, &ratio9_160, &ratio9_160, &ratio1_16, &ratio1_16, &ratio9_128, &ratio5_64, &ratio5_64, &ratio5_64, &ratio3_32, &ratio3_32, &ratio5_48, 
&ratio5_48, &ratio9_80, &ratio9_80, &ratio1_8, &ratio1_8, &ratio9_64, &ratio5_32, &ratio5_32, &ratio5_32, &ratio3_16, &ratio3_16, &ratio5_24, 
&ratio5_24, &ratio9_40, &ratio9_40, &ratio1_4, &ratio1_4, &ratio9_32, &ratio5_16, &ratio5_16, &ratio5_16, &ratio3_8, &ratio3_8, &ratio5_12, 
&ratio5_12, &ratio9_20, &ratio9_20, &ratio1_2, &ratio1_2, &ratio9_16, &ratio5_8, &ratio5_8, &ratio5_8, &ratio3_4, &ratio3_4, &ratio5_6, 
&ratio5_6, &ratio9_10, &ratio9_10, &ratio1_1, &ratio1_1, &ratio9_8, &ratio5_4, &ratio5_4, &ratio5_4, &ratio3_2, &ratio3_2, &ratio5_3, 
&ratio5_3, &ratio9_5, &ratio9_5, &ratio2_1, &ratio2_1, &ratio9_4, &ratio5_2, &ratio5_2, &ratio5_2, &ratio3_1, &ratio3_1, &ratio10_3, 
&ratio10_3, &ratio18_5, &ratio18_5, &ratio4_1, &ratio4_1, &ratio9_2, &ratio5_1, &ratio5_1, &ratio5_1, &ratio6_1, &ratio6_1, &ratio20_3, 
&ratio20_3, &ratio36_5, &ratio36_5, &ratio8_1, &ratio8_1, &ratio9_1, &ratio10_1, &ratio10_1, &ratio10_1, &ratio12_1, &ratio12_1, &ratio40_3, 
&ratio40_3, &ratio72_5, &ratio72_5, &ratio16_1, &ratio16_1, &ratio18_1, &ratio20_1, &ratio20_1, &ratio20_1, &ratio24_1, &ratio24_1, &ratio80_3, 
&ratio80_3, &ratio144_5, &ratio144_5, &ratio32_1, &ratio32_1, &ratio36_1, &ratio40_1}; 

static const ScaleNote *phrygian5prime[128] = {&ratio1_40, &ratio1_40, &ratio9_320, &ratio9_320, &ratio1_32, &ratio1_30, &ratio1_30, &ratio3_80, &ratio1_24, &ratio1_24, &ratio3_64, &ratio3_64, &ratio1_20, 
&ratio1_20, &ratio9_160, &ratio9_160, &ratio1_16, &ratio1_15, &ratio1_15, &ratio3_40, &ratio1_12, &ratio1_12, &ratio3_32, &ratio3_32, &ratio1_10, 
&ratio1_10, &ratio9_80, &ratio9_80, &ratio1_8, &ratio2_15, &ratio2_15, &ratio3_20, &ratio1_6, &ratio1_6, &ratio3_16, &ratio3_16, &ratio1_5, 
&ratio1_5, &ratio9_40, &ratio9_40, &ratio1_4, &ratio4_15, &ratio4_15, &ratio3_10, &ratio1_3, &ratio1_3, &ratio3_8, &ratio3_8, &ratio2_5, 
&ratio2_5, &ratio9_20, &ratio9_20, &ratio1_2, &ratio8_15, &ratio8_15, &ratio3_5, &ratio2_3, &ratio2_3, &ratio3_4, &ratio3_4, &ratio4_5, 
&ratio4_5, &ratio9_10, &ratio9_10, &ratio1_1, &ratio16_15, &ratio16_15, &ratio6_5, &ratio4_3, &ratio4_3, &ratio3_2, &ratio3_2, &ratio8_5, 
&ratio8_5, &ratio9_5, &ratio9_5, &ratio2_1, &ratio32_15, &ratio32_15, &ratio12_5, &ratio8_3, &ratio8_3, &ratio3_1, &ratio3_1, &ratio16_5, 
&ratio16_5, &ratio18_5, &ratio18_5, &ratio4_1, &ratio64_15, &ratio64_15, &ratio24_5, &ratio16_3, &ratio16_3, &ratio6_1, &ratio6_1, &ratio32_5, 
&ratio32_5, &ratio36_5, &ratio36_5, &ratio8_1, &ratio128_15, &ratio128_15, &ratio48_5, &ratio32_3, &ratio32_3, &ratio12_1, &ratio12_1, &ratio64_5, 
&ratio64_5, &ratio72_5, &ratio72_5, &ratio16_1, &ratio256_15, &ratio256_15, &ratio96_5, &ratio64_3, &ratio64_3, &ratio24_1, &ratio24_1, &ratio128_5, 
&ratio128_5, &ratio144_5, &ratio144_5, &ratio32_1, &ratio512_15, &ratio512_15, &ratio192_5}; 

static const ScaleNote *lydian5prime[128] = {&ratio5_192, &ratio5_192, &ratio15_512, &ratio15_512, &ratio1_32, &ratio1_32, &ratio9_256, &ratio5_128, &ratio5_128, &ratio25_576, &ratio25_576, &ratio3_64, &ratio5_96, 
&ratio5_96, &ratio15_256, &ratio15_256, &ratio1_16, &ratio1_16, &ratio9_128, &ratio5_64, &ratio5_64, &ratio25_288, &ratio25_288, &ratio3_32, &ratio5_48, 
&ratio5_48, &ratio15_128, &ratio15_128, &ratio1_8, &ratio1_8, &ratio9_64, &ratio5_32, &ratio5_32, &ratio25_144, &ratio25_144, &ratio3_16, &ratio5_24, 
&ratio5_24, &ratio15_64, &ratio15_64, &ratio1_4, &ratio1_4, &ratio9_32, &ratio5_16, &ratio5_16, &ratio25_72, &ratio25_72, &ratio3_8, &ratio5_12, 
&ratio5_12, &ratio15_32, &ratio15_32, &ratio1_2, &ratio1_2, &ratio9_16, &ratio5_8, &ratio5_8, &ratio25_36, &ratio25_36, &ratio3_4, &ratio5_6, 
&ratio5_6, &ratio15_16, &ratio15_16, &ratio1_1, &ratio1_1, &ratio9_8, &ratio5_4, &ratio5_4, &ratio25_18, &ratio25_18, &ratio3_2, &ratio5_3, 
&ratio5_3, &ratio15_8, &ratio15_8, &ratio2_1, &ratio2_1, &ratio9_4, &ratio5_2, &ratio5_2, &ratio25_9, &ratio25_9, &ratio3_1, &ratio10_3, 
&ratio10_3, &ratio15_4, &ratio15_4, &ratio4_1, &ratio4_1, &ratio9_2, &ratio5_1, &ratio5_1, &ratio50_9, &ratio50_9, &ratio6_1, &ratio20_3, 
&ratio20_3, &ratio15_2, &ratio15_2, &ratio8_1, &ratio8_1, &ratio9_1, &ratio10_1, &ratio10_1, &ratio100_9, &ratio100_9, &ratio12_1, &ratio40_3, 
&ratio40_3, &ratio15_1, &ratio15_1, &ratio16_1, &ratio16_1, &ratio18_1, &ratio20_1, &ratio20_1, &ratio200_9, &ratio200_9, &ratio24_1, &ratio80_3, 
&ratio80_3, &ratio30_1, &ratio30_1, &ratio32_1, &ratio32_1, &ratio36_1, &ratio40_1}; 

static const ScaleNote *mixolydian5prime[128] = {&ratio5_192, &ratio5_192, &ratio9_320, &ratio9_320, &ratio1_32, &ratio1_32, &ratio9_256, &ratio5_128, &ratio1_24, &ratio1_24, &ratio3_64, &ratio3_64, &ratio5_96, 
&ratio5_96, &ratio9_160, &ratio9_160, &ratio1_16, &ratio1_16, &ratio9_128, &ratio5_64, &ratio1_12, &ratio1_12, &ratio3_32, &ratio3_32, &ratio5_48, 
&ratio5_48, &ratio9_80, &ratio9_80, &ratio1_8, &ratio1_8, &ratio9_64, &ratio5_32, &ratio1_6, &ratio1_6, &ratio3_16, &ratio3_16, &ratio5_24, 
&ratio5_24, &ratio9_40, &ratio9_40, &ratio1_4, &ratio1_4, &ratio9_32, &ratio5_16, &ratio1_3, &ratio1_3, &ratio3_8, &ratio3_8, &ratio5_12, 
&ratio5_12, &ratio9_20, &ratio9_20, &ratio1_2, &ratio1_2, &ratio9_16, &ratio5_8, &ratio2_3, &ratio2_3, &ratio3_4, &ratio3_4, &ratio5_6, 
&ratio5_6, &ratio9_10, &ratio9_10, &ratio1_1, &ratio1_1, &ratio9_8, &ratio5_4, &ratio4_3, &ratio4_3, &ratio3_2, &ratio3_2, &ratio5_3, 
&ratio5_3, &ratio9_5, &ratio9_5, &ratio2_1, &ratio2_1, &ratio9_4, &ratio5_2, &ratio8_3, &ratio8_3, &ratio3_1, &ratio3_1, &ratio10_3, 
&ratio10_3, &ratio18_5, &ratio18_5, &ratio4_1, &ratio4_1, &ratio9_2, &ratio5_1, &ratio16_3, &ratio16_3, &ratio6_1, &ratio6_1, &ratio20_3, 
&ratio20_3, &ratio36_5, &ratio36_5, &ratio8_1, &ratio8_1, &ratio9_1, &ratio10_1, &ratio32_3, &ratio32_3, &ratio12_1, &ratio12_1, &ratio40_3, 
&ratio40_3, &ratio72_5, &ratio72_5, &ratio16_1, &ratio16_1, &ratio18_1, &ratio20_1, &ratio64_3, &ratio64_3, &ratio24_1, &ratio24_1, &ratio80_3, 
&ratio80_3, &ratio144_5, &ratio144_5, &ratio32_1, &ratio32_1, &ratio36_1, &ratio40_1}; 

static const ScaleNote *aeolian5prime[128] = {&ratio1_40, &ratio1_40, &ratio9_320, &ratio9_320, &ratio1_32, &ratio1_32, &ratio9_256, &ratio3_80, &ratio1_24, &ratio1_24, &ratio3_64, &ratio3_64, &ratio1_20, 
&ratio1_20, &ratio9_160, &ratio9_160, &ratio1_16, &ratio1_16, &ratio9_128, &ratio3_40, &ratio1_12, &ratio1_12, &ratio3_32, &ratio3_32, &ratio1_10, 
&ratio1_10, &ratio9_80, &ratio9_80, &ratio1_8, &ratio1_8, &ratio9_64, &ratio3_20, &ratio1_6, &ratio1_6, &ratio3_16, &ratio3_16, &ratio1_5, 
&ratio1_5, &ratio9_40, &ratio9_40, &ratio1_4, &ratio1_4, &ratio9_32, &ratio3_10, &ratio1_3, &ratio1_3, &ratio3_8, &ratio3_8, &ratio2_5, 
&ratio2_5, &ratio9_20, &ratio9_20, &ratio1_2, &ratio1_2, &ratio9_16, &ratio3_5, &ratio2_3, &ratio2_3, &ratio3_4, &ratio3_4, &ratio4_5, 
&ratio4_5, &ratio9_10, &ratio9_10, &ratio1_1, &ratio1_1, &ratio9_8, &ratio6_5, &ratio4_3, &ratio4_3, &ratio3_2, &ratio3_2, &ratio8_5, 
&ratio8_5, &ratio9_5, &ratio9_5, &ratio2_1, &ratio2_1, &ratio9_4, &ratio12_5, &ratio8_3, &ratio8_3, &ratio3_1, &ratio3_1, &ratio16_5, 
&ratio16_5, &ratio18_5, &ratio18_5, &ratio4_1, &ratio4_1, &ratio9_2, &ratio24_5, &ratio16_3, &ratio16_3, &ratio6_1, &ratio6_1, &ratio32_5, 
&ratio32_5, &ratio36_5, &ratio36_5, &ratio8_1, &ratio8_1, &ratio9_1, &ratio48_5, &ratio32_3, &ratio32_3, &ratio12_1, &ratio12_1, &ratio64_5, 
&ratio64_5, &ratio72_5, &ratio72_5, &ratio16_1, &ratio16_1, &ratio18_1, &ratio96_5, &ratio64_3, &ratio64_3, &ratio24_1, &ratio24_1, &ratio128_5, 
&ratio128_5, &ratio144_5, &ratio144_5, &ratio32_1, &ratio32_1, &ratio36_1, &ratio192_5}; 

static const ScaleNote *locrian5prime[128] = {&ratio1_40, &ratio1_40, &ratio9_320, &ratio9_320, &ratio1_32, &ratio1_30, &ratio1_30, &ratio3_80, &ratio1_24, &ratio25_576, &ratio25_576, &ratio1_20, &ratio1_20, 
&ratio1_20, &ratio9_160, &ratio9_160, &ratio1_16, &ratio1_15, &ratio1_15, &ratio3_40, &ratio1_12, &ratio25_288, &ratio25_288, &ratio1_10, &ratio1_10, 
&ratio1_10, &ratio9_80, &ratio9_80, &ratio1_8, &ratio2_15, &ratio2_15, &ratio3_20, &ratio1_6, &ratio25_144, &ratio25_144, &ratio1_5, &ratio1_5, 
&ratio1_5, &ratio9_40, &ratio9_40, &ratio1_4, &ratio4_15, &ratio4_15, &ratio3_10, &ratio1_3, &ratio25_72, &ratio25_72, &ratio2_5, &ratio2_5, 
&ratio2_5, &ratio9_20, &ratio9_20, &ratio1_2, &ratio8_15, &ratio8_15, &ratio3_5, &ratio2_3, &ratio25_36, &ratio25_36, &ratio4_5, &ratio4_5, 
&ratio4_5, &ratio9_10, &ratio9_10, &ratio1_1, &ratio16_15, &ratio16_15, &ratio6_5, &ratio4_3, &ratio25_18, &ratio25_18, &ratio8_5, &ratio8_5, 
&ratio8_5, &ratio9_5, &ratio9_5, &ratio2_1, &ratio32_15, &ratio32_15, &ratio12_5, &ratio8_3, &ratio25_9, &ratio25_9, &ratio16_5, &ratio16_5, 
&ratio16_5, &ratio18_5, &ratio18_5, &ratio4_1, &ratio64_15, &ratio64_15, &ratio24_5, &ratio16_3, &ratio50_9, &ratio50_9, &ratio32_5, &ratio32_5, 
&ratio32_5, &ratio36_5, &ratio36_5, &ratio8_1, &ratio128_15, &ratio128_15, &ratio48_5, &ratio32_3, &ratio100_9, &ratio100_9, &ratio64_5, &ratio64_5, 
&ratio64_5, &ratio72_5, &ratio72_5, &ratio16_1, &ratio256_15, &ratio256_15, &ratio96_5, &ratio64_3, &ratio200_9, &ratio200_9, &ratio128_5, &ratio128_5, 
&ratio128_5, &ratio144_5, &ratio144_5, &ratio32_1, &ratio512_15, &ratio512_15, &ratio192_5}; 



static const ScaleNote *harmSubharmfullspan1[128] = {&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, 
&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, 
&ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, 
&ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_4, 
&ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, 
&ratio1_4, &ratio1_4, &ratio1_4, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, 
&ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, 
&ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_6, &ratio1_7, 
&ratio1_7, &ratio1_7, &ratio1_7, &ratio1_7, &ratio1_7, &ratio1_7, &ratio1_7, &ratio1_7, &ratio1_7, &ratio1_7, &ratio1_7, &ratio1_7, 
&ratio1_7, &ratio1_7, &ratio1_7, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, 
&ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8}; 

static const ScaleNote *harmSubharmfullspan2[128] = {&ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, 
&ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, 
&ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, 
&ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio1_1, 
&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, 
&ratio1_1, &ratio1_1, &ratio1_1, &ratio2_5, &ratio2_5, &ratio2_5, &ratio2_5, &ratio2_5, &ratio2_5, &ratio2_5, &ratio2_5, &ratio2_5, 
&ratio2_5, &ratio2_5, &ratio2_5, &ratio2_5, &ratio2_5, &ratio2_5, &ratio2_5, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, 
&ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_3, &ratio2_7, 
&ratio2_7, &ratio2_7, &ratio2_7, &ratio2_7, &ratio2_7, &ratio2_7, &ratio2_7, &ratio2_7, &ratio2_7, &ratio2_7, &ratio2_7, &ratio2_7, 
&ratio2_7, &ratio2_7, &ratio2_7, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, 
&ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2}; 

static const ScaleNote *harmSubharmfullspan3[128] = {&ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, 
&ratio3_1, &ratio3_1, &ratio3_1, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, 
&ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, 
&ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_4, 
&ratio3_4, &ratio3_4, &ratio3_4, &ratio3_4, &ratio3_4, &ratio3_4, &ratio3_4, &ratio3_4, &ratio3_4, &ratio3_4, &ratio3_4, &ratio3_4, 
&ratio3_4, &ratio3_4, &ratio3_4, &ratio3_5, &ratio3_5, &ratio3_5, &ratio3_5, &ratio3_5, &ratio3_5, &ratio3_5, &ratio3_5, &ratio3_5, 
&ratio3_5, &ratio3_5, &ratio3_5, &ratio3_5, &ratio3_5, &ratio3_5, &ratio3_5, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, 
&ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_7, 
&ratio3_7, &ratio3_7, &ratio3_7, &ratio3_7, &ratio3_7, &ratio3_7, &ratio3_7, &ratio3_7, &ratio3_7, &ratio3_7, &ratio3_7, &ratio3_7, 
&ratio3_7, &ratio3_7, &ratio3_7, &ratio3_8, &ratio3_8, &ratio3_8, &ratio3_8, &ratio3_8, &ratio3_8, &ratio3_8, &ratio3_8, &ratio3_8, 
&ratio3_8, &ratio3_8, &ratio3_8, &ratio3_8, &ratio3_8, &ratio3_8, &ratio3_8}; 

static const ScaleNote *harmSubharmfullspan4[128] = {&ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, 
&ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, 
&ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, 
&ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_1, 
&ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, &ratio4_1, 
&ratio4_1, &ratio4_1, &ratio4_1, &ratio4_5, &ratio4_5, &ratio4_5, &ratio4_5, &ratio4_5, &ratio4_5, &ratio4_5, &ratio4_5, &ratio4_5, 
&ratio4_5, &ratio4_5, &ratio4_5, &ratio4_5, &ratio4_5, &ratio4_5, &ratio4_5, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, 
&ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_3, &ratio4_7, 
&ratio4_7, &ratio4_7, &ratio4_7, &ratio4_7, &ratio4_7, &ratio4_7, &ratio4_7, &ratio4_7, &ratio4_7, &ratio4_7, &ratio4_7, &ratio4_7, 
&ratio4_7, &ratio4_7, &ratio4_7, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, 
&ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1, &ratio2_1}; 

static const ScaleNote *harmSubharmfullspan5[128] = {&ratio5_1, &ratio5_1, &ratio5_1, &ratio5_1, &ratio5_1, &ratio5_1, &ratio5_1, &ratio5_1, &ratio5_1, &ratio5_1, &ratio5_1, &ratio5_1, &ratio5_1, 
&ratio5_1, &ratio5_1, &ratio5_1, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, 
&ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_2, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, 
&ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_3, &ratio5_4, 
&ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, &ratio5_4, 
&ratio5_4, &ratio5_4, &ratio5_4, &ratio5_1, &ratio5_1, &ratio5_1, &ratio5_1, &ratio5_1, &ratio5_1, &ratio5_1, &ratio5_1, &ratio5_1, 
&ratio5_1, &ratio5_1, &ratio5_1, &ratio5_1, &ratio5_1, &ratio5_1, &ratio5_1, &ratio5_6, &ratio5_6, &ratio5_6, &ratio5_6, &ratio5_6, 
&ratio5_6, &ratio5_6, &ratio5_6, &ratio5_6, &ratio5_6, &ratio5_6, &ratio5_6, &ratio5_6, &ratio5_6, &ratio5_6, &ratio5_6, &ratio5_7, 
&ratio5_7, &ratio5_7, &ratio5_7, &ratio5_7, &ratio5_7, &ratio5_7, &ratio5_7, &ratio5_7, &ratio5_7, &ratio5_7, &ratio5_7, &ratio5_7, 
&ratio5_7, &ratio5_7, &ratio5_7, &ratio5_8, &ratio5_8, &ratio5_8, &ratio5_8, &ratio5_8, &ratio5_8, &ratio5_8, &ratio5_8, &ratio5_8, 
&ratio5_8, &ratio5_8, &ratio5_8, &ratio5_8, &ratio5_8, &ratio5_8, &ratio5_8}; 

static const ScaleNote *harmSubharmfullspan6[128] = {&ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, 
&ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, 
&ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, 
&ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio3_1, 
&ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, &ratio3_1, 
&ratio3_1, &ratio3_1, &ratio3_1, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, 
&ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_5, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, 
&ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_1, &ratio6_7, 
&ratio6_7, &ratio6_7, &ratio6_7, &ratio6_7, &ratio6_7, &ratio6_7, &ratio6_7, &ratio6_7, &ratio6_7, &ratio6_7, &ratio6_7, &ratio6_7, 
&ratio6_7, &ratio6_7, &ratio6_7, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, 
&ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2, &ratio3_2}; 

static const ScaleNote *harmSubharmfullspan7[128] = {&ratio7_1, &ratio7_1, &ratio7_1, &ratio7_1, &ratio7_1, &ratio7_1, &ratio7_1, &ratio7_1, &ratio7_1, &ratio7_1, &ratio7_1, &ratio7_1, &ratio7_1, 
&ratio7_1, &ratio7_1, &ratio7_1, &ratio7_2, &ratio7_2, &ratio7_2, &ratio7_2, &ratio7_2, &ratio7_2, &ratio7_2, &ratio7_2, &ratio7_2, 
&ratio7_2, &ratio7_2, &ratio7_2, &ratio7_2, &ratio7_2, &ratio7_2, &ratio7_2, &ratio7_3, &ratio7_3, &ratio7_3, &ratio7_3, &ratio7_3, 
&ratio7_3, &ratio7_3, &ratio7_3, &ratio7_3, &ratio7_3, &ratio7_3, &ratio7_3, &ratio7_3, &ratio7_3, &ratio7_3, &ratio7_3, &ratio7_4, 
&ratio7_4, &ratio7_4, &ratio7_4, &ratio7_4, &ratio7_4, &ratio7_4, &ratio7_4, &ratio7_4, &ratio7_4, &ratio7_4, &ratio7_4, &ratio7_4, 
&ratio7_4, &ratio7_4, &ratio7_4, &ratio7_5, &ratio7_5, &ratio7_5, &ratio7_5, &ratio7_5, &ratio7_5, &ratio7_5, &ratio7_5, &ratio7_5, 
&ratio7_5, &ratio7_5, &ratio7_5, &ratio7_5, &ratio7_5, &ratio7_5, &ratio7_5, &ratio7_6, &ratio7_6, &ratio7_6, &ratio7_6, &ratio7_6, 
&ratio7_6, &ratio7_6, &ratio7_6, &ratio7_6, &ratio7_6, &ratio7_6, &ratio7_6, &ratio7_6, &ratio7_6, &ratio7_6, &ratio7_6, &ratio7_1, 
&ratio7_1, &ratio7_1, &ratio7_1, &ratio7_1, &ratio7_1, &ratio7_1, &ratio7_1, &ratio7_1, &ratio7_1, &ratio7_1, &ratio7_1, &ratio7_1, 
&ratio7_1, &ratio7_1, &ratio7_1, &ratio7_8, &ratio7_8, &ratio7_8, &ratio7_8, &ratio7_8, &ratio7_8, &ratio7_8, &ratio7_8, &ratio7_8, 
&ratio7_8, &ratio7_8, &ratio7_8, &ratio7_8, &ratio7_8, &ratio7_8, &ratio7_8}; 

static const ScaleNote *harmSubharmfullspan8[128] = {&ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, 
&ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, 
&ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, 
&ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_1, 
&ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, 
&ratio8_1, &ratio8_1, &ratio8_1, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, 
&ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_5, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, 
&ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_3, &ratio8_7, 
&ratio8_7, &ratio8_7, &ratio8_7, &ratio8_7, &ratio8_7, &ratio8_7, &ratio8_7, &ratio8_7, &ratio8_7, &ratio8_7, &ratio8_7, &ratio8_7, 
&ratio8_7, &ratio8_7, &ratio8_7, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, 
&ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1, &ratio8_1}; 



static const ScaleNote *dominant5primefullspan[128] = {&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, 
&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, 
&ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, 
&ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, 
&ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, 
&ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, 
&ratio1_3, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, 
&ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, 
&ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, 
&ratio1_3, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, 
&ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5}; 

static const ScaleNote *major5primefullspan[128] = {&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, 
&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, 
&ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, 
&ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, 
&ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, 
&ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, 
&ratio1_3, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, 
&ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, 
&ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, 
&ratio1_3, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, 
&ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8}; 

static const ScaleNote *dorian5primefullspan[128] = {&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, 
&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_8, &ratio1_8, &ratio1_8, 
&ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, 
&ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, 
&ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, 
&ratio1_4, &ratio1_4, &ratio1_4, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, 
&ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, 
&ratio1_2, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, 
&ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_5, &ratio1_5, 
&ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, 
&ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5}; 

static const ScaleNote *phrygian5primefullspan[128] = {&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, 
&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_15, &ratio1_15, &ratio1_15, &ratio1_15, &ratio1_15, &ratio1_15, &ratio1_15, &ratio1_15, &ratio1_15, 
&ratio1_15, &ratio1_15, &ratio1_15, &ratio1_15, &ratio1_15, &ratio1_15, &ratio1_15, &ratio1_15, &ratio1_15, &ratio1_15, &ratio1_15, &ratio1_15, 
&ratio1_15, &ratio1_15, &ratio1_15, &ratio1_15, &ratio1_15, &ratio1_15, &ratio1_15, &ratio1_15, &ratio1_15, &ratio1_15, &ratio1_15, &ratio1_5, 
&ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, 
&ratio1_5, &ratio1_5, &ratio1_5, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, 
&ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, 
&ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_5, 
&ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, 
&ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, 
&ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5}; 

static const ScaleNote *lydian5primefullspan[128] = {&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, 
&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, 
&ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, 
&ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, 
&ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_18, &ratio1_18, &ratio1_18, &ratio1_18, &ratio1_18, &ratio1_18, 
&ratio1_18, &ratio1_18, &ratio1_18, &ratio1_18, &ratio1_18, &ratio1_18, &ratio1_18, &ratio1_18, &ratio1_18, &ratio1_18, &ratio1_18, &ratio1_18, 
&ratio1_18, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, 
&ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, 
&ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, 
&ratio1_3, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, 
&ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8}; 

static const ScaleNote *mixolydian5primefullspan[128] = {&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, 
&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, 
&ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, 
&ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, 
&ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_4, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, 
&ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, 
&ratio1_3, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, 
&ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, 
&ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, 
&ratio1_3, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, 
&ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5}; 

static const ScaleNote *aeolian5primefullspan[128] = {&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, 
&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, 
&ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, &ratio1_8, 
&ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, 
&ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, 
&ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, 
&ratio1_3, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, 
&ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_2, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, 
&ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, 
&ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, 
&ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5}; 

static const ScaleNote *locrian5primefullspan[128] = {&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, 
&ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_1, &ratio1_15, &ratio1_15, &ratio1_15, &ratio1_15, &ratio1_15, &ratio1_15, 
&ratio1_15, &ratio1_15, &ratio1_15, &ratio1_15, &ratio1_15, &ratio1_15, &ratio1_15, &ratio1_15, &ratio1_15, &ratio1_15, &ratio1_15, &ratio1_15, 
&ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, 
&ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, 
&ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, &ratio1_3, 
&ratio1_3, &ratio1_18, &ratio1_18, &ratio1_18, &ratio1_18, &ratio1_18, &ratio1_18, &ratio1_18, &ratio1_18, &ratio1_18, &ratio1_18, &ratio1_18, 
&ratio1_18, &ratio1_18, &ratio1_18, &ratio1_18, &ratio1_18, &ratio1_18, &ratio1_18, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, 
&ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, 
&ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, 
&ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5, &ratio1_5}; 






static const ScaleNote **harmSubharmGrid[8] = {harmSubharm1, harmSubharm2, harmSubharm3, harmSubharm4, harmSubharm5, harmSubharm6, harmSubharm7, harmSubharm8}; 

static const ScaleNote **modal5primeGrid[8] = {chromatic5prime, major5prime, dorian5prime, phrygian5prime, lydian5prime, mixolydian5prime, aeolian5prime, locrian5prime}; 

static const ScaleNote **harmSubharmfullspanGrid[8] = {harmSubharmfullspan1, harmSubharmfullspan2, harmSubharmfullspan3, harmSubharmfullspan4, harmSubharmfullspan5, harmSubharmfullspan6, harmSubharmfullspan7, harmSubharmfullspan8}; 

static const ScaleNote **modal5primefullspanGrid[8] = {dominant5primefullspan, major5primefullspan, dorian5primefullspan, phrygian5primefullspan, lydian5primefullspan, mixolydian5primefullspan, aeolian5primefullspan, locrian5primefullspan}; 




