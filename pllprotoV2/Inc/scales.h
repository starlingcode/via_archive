#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"

typedef struct {
	const uint32_t integerPart;
	const uint32_t fractionalPart;
	const uint32_t fundamentalDivision;
} ScaleNote;

typedef struct {
	ScaleNote **grid;
	uint32_t t2Bitshift;
	uint32_t oneVoltOct;
} Scale;

Scale scaleGroup[16];

Scale harmSubharm;
Scale modal5prime;
Scale harmSubharmfullspan;
Scale modal5primefullspan;

static const ScaleNote *harmSubharmGrid[8];
static const ScaleNote *modal5primeGrid[8];
static const ScaleNote *harmSubharmfullspanGrid[8];
static const ScaleNote *modal5primefullspanGrid[8];


#define ratio9_8 {73728, 0, 8}
#define ratio16_120 {8738, 572662306, 15}
#define ratio1_64 {1024, 0, 64}
#define ratio112_8 {917504, 0, 1}
#define ratio2_7 {18724, 2454267026, 7}
#define ratio18_5 {235929, 2576980377, 5}
#define ratio256_15 {1118481, 286331153, 15}
#define ratio72_5 {943718, 1717986918, 5}
#define ratio9_128 {4608, 0, 128}
#define ratio3_256 {768, 0, 256}
#define ratio32_1 {2097152, 0, 1}
#define ratio32_7 {299593, 613566756, 7}
#define ratio40_3 {873813, 1431655765, 3}
#define ratio2_1 {131072, 0, 1}
#define ratio5_3 {109226, 2863311530, 3}
#define ratio7_1 {458752, 0, 1}
#define ratio512_15 {2236962, 572662306, 15}
#define ratio80_6 {873813, 1431655765, 3}
#define ratio36_8 {294912, 0, 2}
#define ratio3_8 {24576, 0, 8}
#define ratio2_64 {2048, 0, 32}
#define ratio8_20 {26214, 1717986918, 5}
#define ratio2_4 {32768, 0, 2}
#define ratio5_1 {327680, 0, 1}
#define ratio60_8 {491520, 0, 2}
#define ratio6_256 {1536, 0, 128}
#define ratio3_128 {1536, 0, 128}
#define ratio18_8 {147456, 0, 4}
#define ratio64_3 {1398101, 1431655765, 3}
#define ratio7_64 {7168, 0, 64}
#define ratio3_32 {6144, 0, 32}
#define ratio64_15 {279620, 1145324612, 15}
#define ratio3_7 {28086, 3681400539, 7}
#define ratio6_80 {4915, 858993459, 40}
#define ratio16_480 {2184, 2290649224, 30}
#define ratio6_112 {3510, 3681400539, 56}
#define ratio5_96 {3413, 1431655765, 96}
#define ratio1_40 {1638, 1717986918, 40}
#define ratio7_8 {57344, 0, 8}
#define ratio15_8 {122880, 0, 8}
#define ratio6_5 {78643, 858993459, 5}
#define ratio1_7 {9362, 1227133513, 7}
#define ratio96_7 {898779, 1840700269, 7}
#define ratio7_48 {9557, 1431655765, 48}
#define ratio50_18 {182044, 1908874353, 9}
#define ratio4_7 {37449, 613566756, 7}
#define ratio12_2 {393216, 0, 1}
#define ratio5_32 {10240, 0, 32}
#define ratio16_5 {209715, 858993459, 5}
#define ratio5_8 {40960, 0, 8}
#define ratio16_240 {4369, 286331153, 15}
#define ratio80_8 {655360, 0, 1}
#define ratio2_2 {65536, 0, 1}
#define ratio128_15 {559240, 2290649224, 15}
#define ratio2_192 {682, 2863311530, 96}
#define ratio4_3 {87381, 1431655765, 3}
#define ratio8_56 {9362, 1227133513, 7}
#define ratio7_6 {76458, 2863311530, 6}
#define ratio25_18 {91022, 954437176, 18}
#define ratio10_4 {163840, 0, 2}
#define ratio9_64 {9216, 0, 64}
#define ratio8_2 {262144, 0, 1}
#define ratio8_320 {1638, 1717986918, 40}
#define ratio200_18 {728177, 3340530119, 9}
#define ratio80_3 {1747626, 2863311531, 3}
#define ratio7_3 {152917, 1431655765, 3}
#define ratio48_8 {393216, 0, 1}
#define ratio32_15 {139810, 572662306, 15}
#define ratio1_2 {32768, 0, 2}
#define ratio4_2 {131072, 0, 1}
#define ratio2_16 {8192, 0, 8}
#define ratio48_7 {449389, 3067833782, 7}
#define ratio15_64 {15360, 0, 64}
#define ratio4_320 {819, 858993459, 80}
#define ratio8_8 {65536, 0, 1}
#define ratio40_4 {655360, 0, 1}
#define ratio36_5 {471859, 858993459, 5}
#define ratio5_192 {1706, 2863311530, 192}
#define ratio1_4 {16384, 0, 4}
#define ratio1_18 {3640, 3817748707, 18}
#define ratio80_7 {748982, 3681400539, 7}
#define ratio15_32 {30720, 0, 32}
#define ratio8_5 {104857, 2576980377, 5}
#define ratio5_256 {1280, 0, 256}
#define ratio5_6 {54613, 1431655765, 6}
#define ratio5_4 {81920, 0, 4}
#define ratio400_18 {1456355, 2386092942, 9}
#define ratio4_6 {43690, 2863311530, 3}
#define ratio1_48 {1365, 1431655765, 48}
#define ratio16_7 {149796, 2454267026, 7}
#define ratio25_72 {22755, 2386092942, 72}
#define ratio8_40 {13107, 858993459, 5}
#define ratio1_3 {21845, 1431655765, 3}
#define ratio6_10 {39321, 2576980377, 5}
#define ratio9_32 {18432, 0, 32}
#define ratio15_256 {3840, 0, 256}
#define ratio20_4 {327680, 0, 1}
#define ratio2_320 {409, 2576980377, 160}
#define ratio1_16 {4096, 0, 16}
#define ratio96_5 {1258291, 858993459, 5}
#define ratio9_20 {29491, 858993459, 20}
#define ratio3_512 {384, 0, 512}
#define ratio1_5 {13107, 858993459, 5}
#define ratio5_7 {46811, 1840700269, 7}
#define ratio6_40 {9830, 1717986918, 20}
#define ratio8_24 {21845, 1431655765, 3}
#define ratio25_36 {45511, 477218588, 36}
#define ratio8_3 {174762, 2863311530, 3}
#define ratio128_5 {1677721, 2576980378, 5}
#define ratio4_24 {10922, 2863311530, 6}
#define ratio8_7 {74898, 1227133513, 7}
#define ratio32_5 {419430, 1717986918, 5}
#define ratio16_1 {1048576, 0, 1}
#define ratio9_160 {3686, 1717986918, 160}
#define ratio3_2 {98304, 0, 2}
#define ratio5_128 {2560, 0, 128}
#define ratio7_96 {4778, 2863311530, 96}
#define ratio8_64 {8192, 0, 8}
#define ratio4_1 {262144, 0, 1}
#define ratio9_10 {58982, 1717986918, 10}
#define ratio7_512 {896, 0, 512}
#define ratio6_4 {98304, 0, 2}
#define ratio7_32 {14336, 0, 32}
#define ratio4_48 {5461, 1431655765, 12}
#define ratio4_8 {32768, 0, 2}
#define ratio5_512 {640, 0, 512}
#define ratio15_512 {1920, 0, 512}
#define ratio144_5 {1887436, 3435973837, 5}
#define ratio144_8 {1179648, 0, 1}
#define ratio2_24 {5461, 1431655765, 12}
#define ratio192_5 {2516582, 1717986918, 5}
#define ratio72_8 {589824, 0, 1}
#define ratio6_7 {56173, 3067833782, 7}
#define ratio16_3 {349525, 1431655765, 3}
#define ratio2_5 {26214, 1717986918, 5}
#define ratio240_8 {1966080, 0, 1}
#define ratio4_12 {21845, 1431655765, 3}
#define ratio7_128 {3584, 0, 128}
#define ratio100_18 {364088, 3817748707, 9}
#define ratio25_576 {2844, 1908874353, 576}
#define ratio4_192 {1365, 1431655765, 48}
#define ratio25_288 {5688, 3817748707, 288}
#define ratio20_3 {436906, 2863311530, 3}
#define ratio1_32 {2048, 0, 32}
#define ratio48_4 {786432, 0, 1}
#define ratio64_5 {838860, 3435973837, 5}
#define ratio3_80 {2457, 2576980377, 80}
#define ratio8_4 {131072, 0, 1}
#define ratio2_40 {3276, 3435973836, 20}
#define ratio5_64 {5120, 0, 64}
#define ratio7_16 {28672, 0, 16}
#define ratio1_8 {8192, 0, 8}
#define ratio6_16 {24576, 0, 8}
#define ratio3_4 {49152, 0, 4}
#define ratio112_6 {1223338, 2863311531, 3}
#define ratio120_8 {983040, 0, 1}
#define ratio288_8 {2359296, 0, 1}
#define ratio16_60 {17476, 1145324612, 15}
#define ratio5_2 {163840, 0, 2}
#define ratio1_56 {1170, 1227133513, 56}
#define ratio9_5 {117964, 3435973836, 5}
#define ratio3_16 {12288, 0, 16}
#define ratio1_1 {65536, 0, 1}
#define ratio7_4 {114688, 0, 4}
#define ratio3_5 {39321, 2576980377, 5}
#define ratio9_320 {1843, 858993459, 320}
#define ratio6_2 {196608, 0, 1}
#define ratio8_6 {87381, 1431655765, 3}
#define ratio9_80 {7372, 3435973836, 80}
#define ratio48_5 {629145, 2576980377, 5}
#define ratio7_5 {91750, 1717986918, 5}
#define ratio8_192 {2730, 2863311530, 24}
#define ratio16_2 {524288, 0, 1}
#define ratio6_1 {393216, 0, 1}
#define ratio4_96 {2730, 2863311530, 24}
#define ratio2_8 {16384, 0, 4}
#define ratio8_10 {52428, 3435973836, 5}
#define ratio9_40 {14745, 2576980377, 40}
#define ratio10_3 {218453, 1431655765, 3}
#define ratio5_24 {13653, 1431655765, 24}
#define ratio80_4 {1310720, 0, 1}
#define ratio4_40 {6553, 2576980377, 10}
#define ratio7_80 {5734, 1717986918, 80}
#define ratio8_80 {6553, 2576980377, 10}
#define ratio64_7 {599186, 1227133513, 7}
#define ratio25_144 {11377, 3340530119, 144}
#define ratio6_160 {2457, 2576980377, 80}
#define ratio24_2 {786432, 0, 1}
#define ratio16_30 {34952, 2290649224, 15}
#define ratio1_192 {341, 1431655765, 192}
#define ratio4_56 {4681, 613566756, 14}
#define ratio3_1 {196608, 0, 1}
#define ratio16_15 {69905, 286331153, 15}
#define ratio7_256 {1792, 0, 256}
#define ratio5_16 {20480, 0, 16}
#define ratio2_56 {2340, 2454267026, 28}
#define ratio1_6 {10922, 2863311530, 6}
#define ratio1_320 {204, 3435973836, 320}
#define ratio48_2 {1572864, 0, 1}
#define ratio9_16 {36864, 0, 16}
#define ratio24_5 {314572, 3435973836, 5}
#define ratio9_256 {2304, 0, 256}
#define ratio1_15 {4369, 286331153, 15}
#define ratio5_112 {2925, 3067833782, 112}
#define ratio4_5 {52428, 3435973836, 5}
#define ratio1_128 {512, 0, 128}
#define ratio5_48 {6826, 2863311530, 48}
#define ratio1_24 {2730, 2863311530, 24}
#define ratio15_16 {61440, 0, 16}
#define ratio6_20 {19660, 3435973836, 10}
#define ratio12_5 {157286, 1717986918, 5}
#define ratio32_3 {699050, 2863311530, 3}
#define ratio4_64 {4096, 0, 16}
#define ratio15_128 {7680, 0, 128}
#define ratio8_1 {524288, 0, 1}
#define ratio3_112 {1755, 1840700269, 112}
#define ratio7_2 {229376, 0, 2}
#define ratio8_160 {3276, 3435973836, 20}
#define ratio3_64 {3072, 0, 64}
#define ratio5_12 {27306, 2863311530, 12}
#define ratio1_256 {256, 0, 256}
#define ratio30_8 {245760, 0, 4}
#define ratio2_3 {43690, 2863311530, 3}



static const ScaleNote harmSubharm1[128] = {ratio1_320, ratio1_320, ratio1_320, ratio1_320, ratio1_256, ratio1_256, ratio1_256, ratio1_256, ratio1_192, ratio1_192, ratio1_192, ratio1_192, ratio1_192,
ratio1_192, ratio1_128, ratio1_128, ratio1_128, ratio1_128, ratio1_128, ratio1_128, ratio1_128, ratio1_128, ratio1_128, ratio1_64, ratio1_64,
ratio1_64, ratio1_64, ratio1_64, ratio1_64, ratio1_64, ratio1_64, ratio1_56, ratio1_56, ratio1_48, ratio1_48, ratio1_48, ratio1_40,
ratio1_40, ratio1_40, ratio1_40, ratio1_32, ratio1_32, ratio1_32, ratio1_32, ratio1_24, ratio1_24, ratio1_24, ratio1_24, ratio1_24,
ratio1_24, ratio1_16, ratio1_16, ratio1_16, ratio1_16, ratio1_16, ratio1_16, ratio1_16, ratio1_16, ratio1_16, ratio1_8, ratio1_8,
ratio1_8, ratio1_8, ratio1_8, ratio1_8, ratio1_8, ratio1_8, ratio1_7, ratio1_7, ratio1_6, ratio1_6, ratio1_6, ratio1_5,
ratio1_5, ratio1_5, ratio1_5, ratio1_4, ratio1_4, ratio1_4, ratio1_4, ratio1_3, ratio1_3, ratio1_3, ratio1_3, ratio1_3,
ratio1_3, ratio1_2, ratio1_2, ratio1_2, ratio1_2, ratio1_2, ratio1_2, ratio1_2, ratio1_2, ratio1_2, ratio1_1, ratio1_1,
ratio1_1, ratio1_1, ratio1_1, ratio8_8, ratio8_8, ratio8_8, ratio8_7, ratio8_7, ratio8_6, ratio8_6, ratio8_6, ratio8_5,
ratio8_5, ratio8_5, ratio8_5, ratio8_4, ratio8_4, ratio8_4, ratio8_4, ratio8_3, ratio8_3, ratio8_3, ratio8_3, ratio8_3,
ratio8_3, ratio8_2, ratio8_2, ratio8_2, ratio8_2, ratio8_2, ratio8_2};

static const ScaleNote harmSubharm2[128] = {ratio2_320, ratio2_320, ratio2_320, ratio2_320, ratio1_128, ratio1_128, ratio1_128, ratio1_128, ratio2_192, ratio2_192, ratio2_192, ratio2_192, ratio2_192,
ratio2_192, ratio1_64, ratio1_64, ratio1_64, ratio1_64, ratio1_64, ratio1_64, ratio1_64, ratio1_64, ratio1_64, ratio2_64, ratio2_64,
ratio2_64, ratio2_64, ratio2_64, ratio1_32, ratio1_32, ratio1_32, ratio2_56, ratio2_56, ratio1_24, ratio1_24, ratio1_24, ratio2_40,
ratio2_40, ratio2_40, ratio2_40, ratio1_16, ratio1_16, ratio1_16, ratio1_16, ratio2_24, ratio2_24, ratio2_24, ratio2_24, ratio2_24,
ratio2_24, ratio1_8, ratio1_8, ratio1_8, ratio1_8, ratio1_8, ratio1_8, ratio1_8, ratio1_8, ratio1_8, ratio2_8, ratio2_8,
ratio2_8, ratio2_8, ratio2_8, ratio1_4, ratio1_4, ratio1_4, ratio2_7, ratio2_7, ratio1_3, ratio1_3, ratio1_3, ratio2_5,
ratio2_5, ratio2_5, ratio2_5, ratio1_2, ratio1_2, ratio1_2, ratio1_2, ratio2_3, ratio2_3, ratio2_3, ratio2_3, ratio2_3,
ratio2_3, ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio2_1, ratio2_1,
ratio2_1, ratio2_1, ratio2_1, ratio8_4, ratio8_4, ratio8_4, ratio16_7, ratio16_7, ratio8_3, ratio8_3, ratio8_3, ratio16_5,
ratio16_5, ratio16_5, ratio16_5, ratio8_2, ratio8_2, ratio8_2, ratio8_2, ratio16_3, ratio16_3, ratio16_3, ratio16_3, ratio16_3,
ratio16_3, ratio8_1, ratio8_1, ratio8_1, ratio8_1, ratio8_1, ratio8_1};

static const ScaleNote harmSubharm3[128] = {ratio3_512, ratio3_512, ratio3_512, ratio3_512, ratio3_512, ratio3_512, ratio3_256, ratio3_256, ratio3_256, ratio3_256, ratio3_256, ratio3_256, ratio3_256,
ratio3_256, ratio3_256, ratio3_256, ratio3_128, ratio3_128, ratio3_128, ratio3_128, ratio3_128, ratio3_128, ratio3_128, ratio3_128, ratio3_128,
ratio3_128, ratio3_112, ratio3_112, ratio1_32, ratio1_32, ratio1_32, ratio3_80, ratio3_80, ratio3_80, ratio3_80, ratio3_64, ratio3_64,
ratio3_64, ratio3_64, ratio1_16, ratio1_16, ratio1_16, ratio1_16, ratio1_16, ratio3_32, ratio3_32, ratio3_32, ratio3_32, ratio3_32,
ratio3_32, ratio3_32, ratio3_32, ratio3_32, ratio3_32, ratio3_16, ratio3_16, ratio3_16, ratio3_16, ratio3_16, ratio3_16, ratio3_16,
ratio3_16, ratio3_16, ratio3_16, ratio3_8, ratio3_8, ratio3_8, ratio3_8, ratio3_8, ratio3_8, ratio3_8, ratio3_8, ratio3_8,
ratio3_8, ratio3_7, ratio3_7, ratio1_2, ratio1_2, ratio1_2, ratio3_5, ratio3_5, ratio3_5, ratio3_5, ratio3_4, ratio3_4,
ratio3_4, ratio3_4, ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio3_2, ratio3_2, ratio3_2, ratio3_2, ratio3_2,
ratio3_2, ratio3_2, ratio3_2, ratio3_2, ratio3_2, ratio3_1, ratio3_1, ratio3_1, ratio3_1, ratio3_1, ratio3_1, ratio3_1,
ratio3_1, ratio3_1, ratio3_1, ratio48_8, ratio48_8, ratio48_8, ratio48_8, ratio48_8, ratio48_8, ratio48_8, ratio48_8, ratio48_8,
ratio48_8, ratio48_7, ratio48_7, ratio16_2, ratio16_2, ratio16_2, ratio48_5};

static const ScaleNote harmSubharm4[128] = {ratio4_320, ratio4_320, ratio4_320, ratio4_320, ratio1_64, ratio1_64, ratio1_64, ratio4_192, ratio4_192, ratio4_192, ratio4_192, ratio4_192, ratio4_192,
ratio2_64, ratio2_64, ratio2_64, ratio2_64, ratio2_64, ratio2_64, ratio2_64, ratio2_64, ratio2_64, ratio2_64, ratio4_64, ratio4_64,
ratio4_64, ratio4_64, ratio4_64, ratio1_16, ratio1_16, ratio1_16, ratio4_56, ratio4_56, ratio2_24, ratio2_24, ratio2_24, ratio4_40,
ratio4_40, ratio4_40, ratio4_40, ratio1_8, ratio1_8, ratio1_8, ratio4_24, ratio4_24, ratio4_24, ratio4_24, ratio4_24, ratio4_24,
ratio2_8, ratio2_8, ratio2_8, ratio2_8, ratio2_8, ratio2_8, ratio2_8, ratio2_8, ratio2_8, ratio2_8, ratio4_8, ratio4_8,
ratio4_8, ratio4_8, ratio4_8, ratio1_2, ratio1_2, ratio1_2, ratio4_7, ratio4_7, ratio2_3, ratio2_3, ratio2_3, ratio4_5,
ratio4_5, ratio4_5, ratio4_5, ratio1_1, ratio1_1, ratio1_1, ratio4_3, ratio4_3, ratio4_3, ratio4_3, ratio4_3, ratio4_3,
ratio2_1, ratio2_1, ratio2_1, ratio2_1, ratio2_1, ratio2_1, ratio2_1, ratio2_1, ratio2_1, ratio2_1, ratio4_1, ratio4_1,
ratio4_1, ratio4_1, ratio4_1, ratio8_2, ratio8_2, ratio8_2, ratio32_7, ratio32_7, ratio16_3, ratio16_3, ratio16_3, ratio32_5,
ratio32_5, ratio32_5, ratio32_5, ratio8_1, ratio8_1, ratio8_1, ratio32_3, ratio32_3, ratio32_3, ratio32_3, ratio32_3, ratio32_3,
ratio16_1, ratio16_1, ratio16_1, ratio16_1, ratio16_1, ratio16_1, ratio16_1};

static const ScaleNote harmSubharm5[128] = {ratio5_512, ratio5_512, ratio5_256, ratio5_256, ratio5_256, ratio5_256, ratio5_256, ratio5_256, ratio5_256, ratio5_256, ratio5_256, ratio5_256, ratio5_256,
ratio5_256, ratio5_256, ratio5_256, ratio5_128, ratio5_128, ratio5_128, ratio5_128, ratio5_128, ratio5_128, ratio5_128, ratio5_112, ratio5_112,
ratio5_96, ratio5_96, ratio5_96, ratio1_16, ratio1_16, ratio5_64, ratio5_64, ratio5_64, ratio5_64, ratio5_48, ratio5_48, ratio5_48,
ratio5_48, ratio5_48, ratio5_48, ratio5_32, ratio5_32, ratio5_32, ratio5_32, ratio5_32, ratio5_32, ratio5_32, ratio5_32, ratio5_32,
ratio5_32, ratio5_16, ratio5_16, ratio5_16, ratio5_16, ratio5_16, ratio5_16, ratio5_16, ratio5_16, ratio5_16, ratio5_16, ratio5_16,
ratio5_16, ratio5_16, ratio5_16, ratio5_8, ratio5_8, ratio5_8, ratio5_8, ratio5_8, ratio5_8, ratio5_8, ratio5_7, ratio5_7,
ratio5_6, ratio5_6, ratio5_6, ratio1_1, ratio1_1, ratio5_4, ratio5_4, ratio5_4, ratio5_4, ratio5_3, ratio5_3, ratio5_3,
ratio5_3, ratio5_3, ratio5_3, ratio5_2, ratio5_2, ratio5_2, ratio5_2, ratio5_2, ratio5_2, ratio5_2, ratio5_2, ratio5_2,
ratio5_2, ratio5_1, ratio5_1, ratio5_1, ratio5_1, ratio5_1, ratio5_1, ratio5_1, ratio5_1, ratio5_1, ratio5_1, ratio5_1,
ratio5_1, ratio5_1, ratio5_1, ratio80_8, ratio80_8, ratio80_8, ratio80_8, ratio80_8, ratio80_8, ratio80_8, ratio80_7, ratio80_7,
ratio80_6, ratio80_6, ratio80_6, ratio16_1, ratio16_1, ratio80_4, ratio80_4};

static const ScaleNote harmSubharm6[128] = {ratio3_256, ratio3_256, ratio3_256, ratio3_256, ratio3_256, ratio3_256, ratio6_256, ratio6_256, ratio6_256, ratio6_256, ratio6_256, ratio6_256, ratio6_256,
ratio6_256, ratio6_256, ratio6_256, ratio3_64, ratio3_64, ratio3_64, ratio3_64, ratio3_64, ratio3_64, ratio3_64, ratio3_64, ratio3_64,
ratio3_64, ratio6_112, ratio6_112, ratio1_16, ratio1_16, ratio6_80, ratio6_80, ratio6_80, ratio6_80, ratio3_32, ratio3_32, ratio3_32,
ratio3_32, ratio2_16, ratio2_16, ratio2_16, ratio2_16, ratio2_16, ratio2_16, ratio3_16, ratio3_16, ratio3_16, ratio3_16, ratio3_16,
ratio3_16, ratio3_16, ratio3_16, ratio3_16, ratio3_16, ratio6_16, ratio6_16, ratio6_16, ratio6_16, ratio6_16, ratio6_16, ratio6_16,
ratio6_16, ratio6_16, ratio6_16, ratio3_4, ratio3_4, ratio3_4, ratio3_4, ratio3_4, ratio3_4, ratio3_4, ratio3_4, ratio3_4,
ratio3_4, ratio6_7, ratio6_7, ratio1_1, ratio1_1, ratio6_5, ratio6_5, ratio6_5, ratio6_5, ratio3_2, ratio3_2, ratio3_2,
ratio3_2, ratio2_1, ratio2_1, ratio2_1, ratio2_1, ratio2_1, ratio2_1, ratio3_1, ratio3_1, ratio3_1, ratio3_1, ratio3_1,
ratio3_1, ratio3_1, ratio3_1, ratio3_1, ratio3_1, ratio6_1, ratio6_1, ratio6_1, ratio6_1, ratio6_1, ratio6_1, ratio6_1,
ratio6_1, ratio6_1, ratio6_1, ratio48_4, ratio48_4, ratio48_4, ratio48_4, ratio48_4, ratio48_4, ratio48_4, ratio48_4, ratio48_4,
ratio48_4, ratio96_7, ratio96_7, ratio16_1, ratio16_1, ratio96_5, ratio96_5};

static const ScaleNote harmSubharm7[128] = {ratio7_512, ratio7_512, ratio7_512, ratio7_512, ratio7_512, ratio7_512, ratio7_512, ratio7_512, ratio7_256, ratio7_256, ratio7_256, ratio7_256, ratio7_256,
ratio7_256, ratio7_256, ratio7_256, ratio7_128, ratio7_128, ratio7_128, ratio7_128, ratio7_128, ratio7_128, ratio7_128, ratio7_128, ratio7_128,
ratio7_128, ratio7_128, ratio7_128, ratio1_16, ratio1_16, ratio7_96, ratio7_96, ratio7_80, ratio7_80, ratio7_80, ratio7_80, ratio7_64,
ratio7_64, ratio7_64, ratio7_64, ratio7_48, ratio7_48, ratio7_48, ratio7_48, ratio7_48, ratio7_48, ratio7_32, ratio7_32, ratio7_32,
ratio7_32, ratio7_32, ratio7_32, ratio7_32, ratio7_32, ratio7_32, ratio7_32, ratio7_16, ratio7_16, ratio7_16, ratio7_16, ratio7_16,
ratio7_16, ratio7_16, ratio7_16, ratio7_8, ratio7_8, ratio7_8, ratio7_8, ratio7_8, ratio7_8, ratio7_8, ratio7_8, ratio7_8,
ratio7_8, ratio7_8, ratio7_8, ratio1_1, ratio1_1, ratio7_6, ratio7_6, ratio7_5, ratio7_5, ratio7_5, ratio7_5, ratio7_4,
ratio7_4, ratio7_4, ratio7_4, ratio7_3, ratio7_3, ratio7_3, ratio7_3, ratio7_3, ratio7_3, ratio7_2, ratio7_2, ratio7_2,
ratio7_2, ratio7_2, ratio7_2, ratio7_2, ratio7_2, ratio7_2, ratio7_2, ratio7_1, ratio7_1, ratio7_1, ratio7_1, ratio7_1,
ratio7_1, ratio7_1, ratio7_1, ratio112_8, ratio112_8, ratio112_8, ratio112_8, ratio112_8, ratio112_8, ratio112_8, ratio112_8, ratio112_8,
ratio112_8, ratio112_8, ratio112_8, ratio16_1, ratio16_1, ratio112_6, ratio112_6};

static const ScaleNote harmSubharm8[128] = {ratio8_320, ratio8_320, ratio8_320, ratio2_64, ratio2_64, ratio2_64, ratio2_64, ratio8_192, ratio8_192, ratio8_192, ratio8_192, ratio8_192, ratio8_192,
ratio4_64, ratio4_64, ratio4_64, ratio4_64, ratio4_64, ratio4_64, ratio4_64, ratio4_64, ratio4_64, ratio4_64, ratio8_64, ratio8_64,
ratio8_64, ratio8_64, ratio8_64, ratio1_8, ratio1_8, ratio8_56, ratio8_56, ratio4_24, ratio4_24, ratio4_24, ratio8_40, ratio8_40,
ratio8_40, ratio8_40, ratio2_8, ratio2_8, ratio2_8, ratio2_8, ratio8_24, ratio8_24, ratio8_24, ratio8_24, ratio8_24, ratio8_24,
ratio4_8, ratio4_8, ratio4_8, ratio4_8, ratio4_8, ratio4_8, ratio4_8, ratio4_8, ratio4_8, ratio4_8, ratio8_8, ratio8_8,
ratio8_8, ratio8_8, ratio8_8, ratio1_1, ratio1_1, ratio8_7, ratio8_7, ratio4_3, ratio4_3, ratio4_3, ratio8_5, ratio8_5,
ratio8_5, ratio8_5, ratio2_1, ratio2_1, ratio2_1, ratio2_1, ratio8_3, ratio8_3, ratio8_3, ratio8_3, ratio8_3, ratio8_3,
ratio4_1, ratio4_1, ratio4_1, ratio4_1, ratio4_1, ratio4_1, ratio4_1, ratio4_1, ratio4_1, ratio4_1, ratio8_1, ratio8_1,
ratio8_1, ratio8_1, ratio8_1, ratio8_1, ratio8_1, ratio64_7, ratio64_7, ratio32_3, ratio32_3, ratio32_3, ratio64_5, ratio64_5,
ratio64_5, ratio64_5, ratio16_1, ratio16_1, ratio16_1, ratio16_1, ratio64_3, ratio64_3, ratio64_3, ratio64_3, ratio64_3, ratio64_3,
ratio32_1, ratio32_1, ratio32_1, ratio32_1, ratio32_1, ratio32_1, ratio32_1};



static const ScaleNote chromatic5prime[128] = {ratio8_320, ratio5_192, ratio9_320, ratio15_512, ratio1_32, ratio16_480, ratio9_256, ratio6_160, ratio4_96, ratio25_576, ratio25_576, ratio3_64, ratio8_160,
ratio5_96, ratio9_160, ratio15_256, ratio1_16, ratio16_240, ratio9_128, ratio6_80, ratio4_48, ratio25_288, ratio25_288, ratio3_32, ratio8_80,
ratio5_48, ratio9_80, ratio15_128, ratio1_8, ratio16_120, ratio9_64, ratio6_40, ratio4_24, ratio25_144, ratio25_144, ratio3_16, ratio8_40,
ratio5_24, ratio9_40, ratio15_64, ratio1_4, ratio16_60, ratio9_32, ratio6_20, ratio4_12, ratio25_72, ratio25_72, ratio3_8, ratio8_20,
ratio5_12, ratio9_20, ratio15_32, ratio1_2, ratio16_30, ratio9_16, ratio6_10, ratio4_6, ratio25_36, ratio25_36, ratio3_4, ratio8_10,
ratio5_6, ratio9_10, ratio15_16, ratio1_1, ratio16_15, ratio9_8, ratio6_5, ratio4_3, ratio25_18, ratio25_18, ratio3_2, ratio8_5,
ratio5_3, ratio9_5, ratio15_8, ratio2_1, ratio32_15, ratio18_8, ratio12_5, ratio8_3, ratio50_18, ratio50_18, ratio6_2, ratio16_5,
ratio10_3, ratio18_5, ratio30_8, ratio4_1, ratio64_15, ratio36_8, ratio24_5, ratio16_3, ratio100_18, ratio100_18, ratio12_2, ratio32_5,
ratio20_3, ratio36_5, ratio60_8, ratio8_1, ratio128_15, ratio72_8, ratio48_5, ratio32_3, ratio200_18, ratio200_18, ratio24_2, ratio64_5,
ratio40_3, ratio72_5, ratio120_8, ratio16_1, ratio256_15, ratio144_8, ratio96_5, ratio64_3, ratio400_18, ratio400_18, ratio48_2, ratio128_5,
ratio80_3, ratio144_5, ratio240_8, ratio32_1, ratio512_15, ratio288_8, ratio192_5};

static const ScaleNote major5prime[128] = {ratio5_48, ratio15_128, ratio15_128, ratio15_128, ratio1_8, ratio1_8, ratio9_64, ratio9_64, ratio9_64, ratio9_64, ratio5_32, ratio4_24, ratio4_24,
ratio3_16, ratio3_16, ratio3_16, ratio3_16, ratio3_16, ratio3_16, ratio5_24, ratio5_24, ratio15_64, ratio15_64, ratio15_64, ratio1_4,
ratio1_4, ratio9_32, ratio9_32, ratio9_32, ratio9_32, ratio5_16, ratio4_12, ratio4_12, ratio3_8, ratio3_8, ratio3_8, ratio3_8,
ratio3_8, ratio3_8, ratio5_12, ratio5_12, ratio15_32, ratio15_32, ratio15_32, ratio1_2, ratio1_2, ratio9_16, ratio9_16, ratio9_16,
ratio9_16, ratio5_8, ratio4_6, ratio4_6, ratio3_4, ratio3_4, ratio3_4, ratio3_4, ratio3_4, ratio3_4, ratio5_6, ratio5_6,
ratio15_16, ratio15_16, ratio15_16, ratio1_1, ratio1_1, ratio9_8, ratio9_8, ratio9_8, ratio9_8, ratio5_4, ratio4_3, ratio4_3,
ratio3_2, ratio3_2, ratio3_2, ratio3_2, ratio3_2, ratio3_2, ratio5_3, ratio5_3, ratio15_8, ratio15_8, ratio15_8, ratio2_1,
ratio2_1, ratio18_8, ratio18_8, ratio18_8, ratio18_8, ratio10_4, ratio8_3, ratio8_3, ratio6_2, ratio6_2, ratio6_2, ratio6_2,
ratio6_2, ratio6_2, ratio10_3, ratio10_3, ratio30_8, ratio30_8, ratio30_8, ratio4_1, ratio4_1, ratio36_8, ratio36_8, ratio36_8,
ratio36_8, ratio20_4, ratio16_3, ratio16_3, ratio12_2, ratio12_2, ratio12_2, ratio12_2, ratio12_2, ratio12_2, ratio20_3, ratio20_3,
ratio60_8, ratio60_8, ratio60_8, ratio8_1, ratio8_1, ratio72_8, ratio72_8};

static const ScaleNote dorian5prime[128] = {ratio9_80, ratio1_8, ratio1_8, ratio9_64, ratio9_64, ratio9_64, ratio9_64, ratio5_32, ratio5_32, ratio5_32, ratio3_16, ratio3_16, ratio3_16,
ratio3_16, ratio3_16, ratio3_16, ratio3_16, ratio3_16, ratio5_24, ratio5_24, ratio9_40, ratio9_40, ratio1_4, ratio1_4, ratio9_32,
ratio9_32, ratio9_32, ratio9_32, ratio5_16, ratio5_16, ratio5_16, ratio3_8, ratio3_8, ratio3_8, ratio3_8, ratio3_8, ratio3_8,
ratio3_8, ratio3_8, ratio5_12, ratio5_12, ratio9_20, ratio9_20, ratio1_2, ratio1_2, ratio9_16, ratio9_16, ratio9_16, ratio9_16,
ratio5_8, ratio5_8, ratio5_8, ratio3_4, ratio3_4, ratio3_4, ratio3_4, ratio3_4, ratio3_4, ratio3_4, ratio3_4, ratio5_6,
ratio5_6, ratio9_10, ratio9_10, ratio1_1, ratio1_1, ratio9_8, ratio9_8, ratio9_8, ratio9_8, ratio5_4, ratio5_4, ratio5_4,
ratio3_2, ratio3_2, ratio3_2, ratio3_2, ratio3_2, ratio3_2, ratio3_2, ratio3_2, ratio5_3, ratio5_3, ratio9_5, ratio9_5,
ratio2_1, ratio2_1, ratio18_8, ratio18_8, ratio18_8, ratio18_8, ratio10_4, ratio10_4, ratio10_4, ratio6_2, ratio6_2, ratio6_2,
ratio6_2, ratio6_2, ratio6_2, ratio6_2, ratio6_2, ratio10_3, ratio10_3, ratio18_5, ratio18_5, ratio4_1, ratio4_1, ratio36_8,
ratio36_8, ratio36_8, ratio36_8, ratio20_4, ratio20_4, ratio20_4, ratio12_2, ratio12_2, ratio12_2, ratio12_2, ratio12_2, ratio12_2,
ratio12_2, ratio12_2, ratio20_3, ratio20_3, ratio36_5, ratio36_5, ratio8_1};

static const ScaleNote phrygian5prime[128] = {ratio4_48, ratio3_32, ratio3_32, ratio3_32, ratio8_80, ratio8_80, ratio9_80, ratio9_80, ratio9_80, ratio9_80, ratio1_8, ratio16_120, ratio16_120,
ratio6_40, ratio6_40, ratio6_40, ratio6_40, ratio4_24, ratio4_24, ratio3_16, ratio3_16, ratio3_16, ratio8_40, ratio8_40, ratio9_40,
ratio9_40, ratio9_40, ratio9_40, ratio1_4, ratio16_60, ratio16_60, ratio6_20, ratio6_20, ratio6_20, ratio6_20, ratio4_12, ratio4_12,
ratio3_8, ratio3_8, ratio3_8, ratio8_20, ratio8_20, ratio9_20, ratio9_20, ratio9_20, ratio9_20, ratio1_2, ratio16_30, ratio16_30,
ratio6_10, ratio6_10, ratio6_10, ratio6_10, ratio4_6, ratio4_6, ratio3_4, ratio3_4, ratio3_4, ratio8_10, ratio8_10, ratio9_10,
ratio9_10, ratio9_10, ratio9_10, ratio1_1, ratio16_15, ratio16_15, ratio6_5, ratio6_5, ratio6_5, ratio6_5, ratio4_3, ratio4_3,
ratio3_2, ratio3_2, ratio3_2, ratio8_5, ratio8_5, ratio9_5, ratio9_5, ratio9_5, ratio9_5, ratio2_1, ratio32_15, ratio32_15,
ratio12_5, ratio12_5, ratio12_5, ratio12_5, ratio8_3, ratio8_3, ratio6_2, ratio6_2, ratio6_2, ratio16_5, ratio16_5, ratio18_5,
ratio18_5, ratio18_5, ratio18_5, ratio4_1, ratio64_15, ratio64_15, ratio24_5, ratio24_5, ratio24_5, ratio24_5, ratio16_3, ratio16_3,
ratio12_2, ratio12_2, ratio12_2, ratio32_5, ratio32_5, ratio36_5, ratio36_5, ratio36_5, ratio36_5, ratio8_1, ratio128_15, ratio128_15,
ratio48_5, ratio48_5, ratio48_5, ratio48_5, ratio32_3, ratio32_3, ratio24_2};

static const ScaleNote lydian5prime[128] = {ratio25_288, ratio25_288, ratio25_288, ratio3_32, ratio3_32, ratio5_48, ratio5_48, ratio15_128, ratio15_128, ratio15_128, ratio1_8, ratio1_8, ratio9_64,
ratio9_64, ratio9_64, ratio9_64, ratio5_32, ratio5_32, ratio25_144, ratio25_144, ratio25_144, ratio3_16, ratio3_16, ratio5_24, ratio5_24,
ratio15_64, ratio15_64, ratio15_64, ratio1_4, ratio1_4, ratio9_32, ratio9_32, ratio9_32, ratio9_32, ratio5_16, ratio5_16, ratio25_72,
ratio25_72, ratio25_72, ratio3_8, ratio3_8, ratio5_12, ratio5_12, ratio15_32, ratio15_32, ratio15_32, ratio1_2, ratio1_2, ratio9_16,
ratio9_16, ratio9_16, ratio9_16, ratio5_8, ratio5_8, ratio25_36, ratio25_36, ratio25_36, ratio3_4, ratio3_4, ratio5_6, ratio5_6,
ratio15_16, ratio15_16, ratio15_16, ratio1_1, ratio1_1, ratio9_8, ratio9_8, ratio9_8, ratio9_8, ratio5_4, ratio5_4, ratio25_18,
ratio25_18, ratio25_18, ratio3_2, ratio3_2, ratio5_3, ratio5_3, ratio15_8, ratio15_8, ratio15_8, ratio2_1, ratio2_1, ratio18_8,
ratio18_8, ratio18_8, ratio18_8, ratio10_4, ratio10_4, ratio50_18, ratio50_18, ratio50_18, ratio6_2, ratio6_2, ratio10_3, ratio10_3,
ratio30_8, ratio30_8, ratio30_8, ratio4_1, ratio4_1, ratio36_8, ratio36_8, ratio36_8, ratio36_8, ratio20_4, ratio20_4, ratio100_18,
ratio100_18, ratio100_18, ratio12_2, ratio12_2, ratio20_3, ratio20_3, ratio60_8, ratio60_8, ratio60_8, ratio8_1, ratio8_1, ratio72_8,
ratio72_8, ratio72_8, ratio72_8, ratio40_4, ratio40_4, ratio200_18, ratio200_18};

static const ScaleNote mixolydian5prime[128] = {ratio3_32, ratio3_32, ratio3_32, ratio5_48, ratio5_48, ratio9_80, ratio9_80, ratio1_8, ratio1_8, ratio9_64, ratio9_64, ratio9_64, ratio9_64,
ratio5_32, ratio4_24, ratio4_24, ratio3_16, ratio3_16, ratio3_16, ratio3_16, ratio3_16, ratio3_16, ratio5_24, ratio5_24, ratio9_40,
ratio9_40, ratio1_4, ratio1_4, ratio9_32, ratio9_32, ratio9_32, ratio9_32, ratio5_16, ratio4_12, ratio4_12, ratio3_8, ratio3_8,
ratio3_8, ratio3_8, ratio3_8, ratio3_8, ratio5_12, ratio5_12, ratio9_20, ratio9_20, ratio1_2, ratio1_2, ratio9_16, ratio9_16,
ratio9_16, ratio9_16, ratio5_8, ratio4_6, ratio4_6, ratio3_4, ratio3_4, ratio3_4, ratio3_4, ratio3_4, ratio3_4, ratio5_6,
ratio5_6, ratio9_10, ratio9_10, ratio1_1, ratio1_1, ratio9_8, ratio9_8, ratio9_8, ratio9_8, ratio5_4, ratio4_3, ratio4_3,
ratio3_2, ratio3_2, ratio3_2, ratio3_2, ratio3_2, ratio3_2, ratio5_3, ratio5_3, ratio9_5, ratio9_5, ratio2_1, ratio2_1,
ratio18_8, ratio18_8, ratio18_8, ratio18_8, ratio10_4, ratio8_3, ratio8_3, ratio6_2, ratio6_2, ratio6_2, ratio6_2, ratio6_2,
ratio6_2, ratio10_3, ratio10_3, ratio18_5, ratio18_5, ratio4_1, ratio4_1, ratio36_8, ratio36_8, ratio36_8, ratio36_8, ratio20_4,
ratio16_3, ratio16_3, ratio12_2, ratio12_2, ratio12_2, ratio12_2, ratio12_2, ratio12_2, ratio20_3, ratio20_3, ratio36_5, ratio36_5,
ratio8_1, ratio8_1, ratio72_8, ratio72_8, ratio72_8, ratio72_8, ratio40_4};

static const ScaleNote aeolian5prime[128] = {ratio6_80, ratio6_80, ratio4_48, ratio4_48, ratio3_32, ratio3_32, ratio3_32, ratio8_80, ratio8_80, ratio9_80, ratio9_80, ratio9_80, ratio9_80,
ratio1_8, ratio1_8, ratio9_64, ratio9_64, ratio6_40, ratio6_40, ratio4_24, ratio4_24, ratio3_16, ratio3_16, ratio3_16, ratio8_40,
ratio8_40, ratio9_40, ratio9_40, ratio9_40, ratio9_40, ratio1_4, ratio1_4, ratio9_32, ratio9_32, ratio6_20, ratio6_20, ratio4_12,
ratio4_12, ratio3_8, ratio3_8, ratio3_8, ratio8_20, ratio8_20, ratio9_20, ratio9_20, ratio9_20, ratio9_20, ratio1_2, ratio1_2,
ratio9_16, ratio9_16, ratio6_10, ratio6_10, ratio4_6, ratio4_6, ratio3_4, ratio3_4, ratio3_4, ratio8_10, ratio8_10, ratio9_10,
ratio9_10, ratio9_10, ratio9_10, ratio1_1, ratio1_1, ratio9_8, ratio9_8, ratio6_5, ratio6_5, ratio4_3, ratio4_3, ratio3_2,
ratio3_2, ratio3_2, ratio8_5, ratio8_5, ratio9_5, ratio9_5, ratio9_5, ratio9_5, ratio2_1, ratio2_1, ratio18_8, ratio18_8,
ratio12_5, ratio12_5, ratio8_3, ratio8_3, ratio6_2, ratio6_2, ratio6_2, ratio16_5, ratio16_5, ratio18_5, ratio18_5, ratio18_5,
ratio18_5, ratio4_1, ratio4_1, ratio36_8, ratio36_8, ratio24_5, ratio24_5, ratio16_3, ratio16_3, ratio12_2, ratio12_2, ratio12_2,
ratio32_5, ratio32_5, ratio36_5, ratio36_5, ratio36_5, ratio36_5, ratio8_1, ratio8_1, ratio72_8, ratio72_8, ratio48_5, ratio48_5,
ratio32_3, ratio32_3, ratio24_2, ratio24_2, ratio24_2, ratio64_5, ratio64_5};

static const ScaleNote locrian5prime[128] = {ratio9_80, ratio9_80, ratio9_80, ratio9_80, ratio1_8, ratio16_120, ratio16_120, ratio6_40, ratio6_40, ratio6_40, ratio6_40, ratio4_24, ratio25_144,
ratio25_144, ratio8_40, ratio8_40, ratio8_40, ratio8_40, ratio8_40, ratio8_40, ratio9_40, ratio9_40, ratio9_40, ratio9_40, ratio1_4,
ratio16_60, ratio16_60, ratio6_20, ratio6_20, ratio6_20, ratio6_20, ratio4_12, ratio25_72, ratio25_72, ratio8_20, ratio8_20, ratio8_20,
ratio8_20, ratio8_20, ratio8_20, ratio9_20, ratio9_20, ratio9_20, ratio9_20, ratio1_2, ratio16_30, ratio16_30, ratio6_10, ratio6_10,
ratio6_10, ratio6_10, ratio4_6, ratio25_36, ratio25_36, ratio8_10, ratio8_10, ratio8_10, ratio8_10, ratio8_10, ratio8_10, ratio9_10,
ratio9_10, ratio9_10, ratio9_10, ratio1_1, ratio16_15, ratio16_15, ratio6_5, ratio6_5, ratio6_5, ratio6_5, ratio4_3, ratio25_18,
ratio25_18, ratio8_5, ratio8_5, ratio8_5, ratio8_5, ratio8_5, ratio8_5, ratio9_5, ratio9_5, ratio9_5, ratio9_5, ratio2_1,
ratio32_15, ratio32_15, ratio12_5, ratio12_5, ratio12_5, ratio12_5, ratio8_3, ratio50_18, ratio50_18, ratio16_5, ratio16_5, ratio16_5,
ratio16_5, ratio16_5, ratio16_5, ratio18_5, ratio18_5, ratio18_5, ratio18_5, ratio4_1, ratio64_15, ratio64_15, ratio24_5, ratio24_5,
ratio24_5, ratio24_5, ratio16_3, ratio100_18, ratio100_18, ratio32_5, ratio32_5, ratio32_5, ratio32_5, ratio32_5, ratio32_5, ratio36_5,
ratio36_5, ratio36_5, ratio36_5, ratio8_1, ratio128_15, ratio128_15, ratio48_5};



static const ScaleNote harmSubharmfullspan1[128] = {ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_1,
ratio1_1, ratio1_1, ratio1_1, ratio1_2, ratio1_2, ratio1_2, ratio1_2, ratio1_2, ratio1_2, ratio1_2, ratio1_2, ratio1_2,
ratio1_2, ratio1_2, ratio1_2, ratio1_2, ratio1_2, ratio1_2, ratio1_2, ratio1_3, ratio1_3, ratio1_3, ratio1_3, ratio1_3,
ratio1_3, ratio1_3, ratio1_3, ratio1_3, ratio1_3, ratio1_3, ratio1_3, ratio1_3, ratio1_3, ratio1_3, ratio1_3, ratio1_4,
ratio1_4, ratio1_4, ratio1_4, ratio1_4, ratio1_4, ratio1_4, ratio1_4, ratio1_4, ratio1_4, ratio1_4, ratio1_4, ratio1_4,
ratio1_4, ratio1_4, ratio1_4, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5,
ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_6, ratio1_6, ratio1_6, ratio1_6, ratio1_6,
ratio1_6, ratio1_6, ratio1_6, ratio1_6, ratio1_6, ratio1_6, ratio1_6, ratio1_6, ratio1_6, ratio1_6, ratio1_6, ratio1_7,
ratio1_7, ratio1_7, ratio1_7, ratio1_7, ratio1_7, ratio1_7, ratio1_7, ratio1_7, ratio1_7, ratio1_7, ratio1_7, ratio1_7,
ratio1_7, ratio1_7, ratio1_7, ratio1_8, ratio1_8, ratio1_8, ratio1_8, ratio1_8, ratio1_8, ratio1_8, ratio1_8, ratio1_8,
ratio1_8, ratio1_8, ratio1_8, ratio1_8, ratio1_8, ratio1_8, ratio1_8};

static const ScaleNote harmSubharmfullspan2[128] = {ratio2_1, ratio2_1, ratio2_1, ratio2_1, ratio2_1, ratio2_1, ratio2_1, ratio2_1, ratio2_1, ratio2_1, ratio2_1, ratio2_1, ratio2_1,
ratio2_1, ratio2_1, ratio2_1, ratio2_1, ratio2_1, ratio2_1, ratio2_1, ratio2_1, ratio2_1, ratio2_1, ratio2_1, ratio2_1,
ratio2_1, ratio2_1, ratio2_1, ratio2_1, ratio2_1, ratio2_1, ratio2_1, ratio2_3, ratio2_3, ratio2_3, ratio2_3, ratio2_3,
ratio2_3, ratio2_3, ratio2_3, ratio2_3, ratio2_3, ratio2_3, ratio2_3, ratio2_3, ratio2_3, ratio2_3, ratio2_3, ratio2_2,
ratio2_2, ratio2_2, ratio2_2, ratio2_2, ratio2_2, ratio2_2, ratio2_2, ratio2_2, ratio2_2, ratio2_2, ratio2_2, ratio2_2,
ratio2_2, ratio2_2, ratio2_2, ratio2_5, ratio2_5, ratio2_5, ratio2_5, ratio2_5, ratio2_5, ratio2_5, ratio2_5, ratio2_5,
ratio2_5, ratio2_5, ratio2_5, ratio2_5, ratio2_5, ratio2_5, ratio2_5, ratio2_3, ratio2_3, ratio2_3, ratio2_3, ratio2_3,
ratio2_3, ratio2_3, ratio2_3, ratio2_3, ratio2_3, ratio2_3, ratio2_3, ratio2_3, ratio2_3, ratio2_3, ratio2_3, ratio2_7,
ratio2_7, ratio2_7, ratio2_7, ratio2_7, ratio2_7, ratio2_7, ratio2_7, ratio2_7, ratio2_7, ratio2_7, ratio2_7, ratio2_7,
ratio2_7, ratio2_7, ratio2_7, ratio2_4, ratio2_4, ratio2_4, ratio2_4, ratio2_4, ratio2_4, ratio2_4, ratio2_4, ratio2_4,
ratio2_4, ratio2_4, ratio2_4, ratio2_4, ratio2_4, ratio2_4, ratio2_4};

static const ScaleNote harmSubharmfullspan3[128] = {ratio3_1, ratio3_1, ratio3_1, ratio3_1, ratio3_1, ratio3_1, ratio3_1, ratio3_1, ratio3_1, ratio3_1, ratio3_1, ratio3_1, ratio3_1,
ratio3_1, ratio3_1, ratio3_1, ratio3_2, ratio3_2, ratio3_2, ratio3_2, ratio3_2, ratio3_2, ratio3_2, ratio3_2, ratio3_2,
ratio3_2, ratio3_2, ratio3_2, ratio3_2, ratio3_2, ratio3_2, ratio3_2, ratio3_1, ratio3_1, ratio3_1, ratio3_1, ratio3_1,
ratio3_1, ratio3_1, ratio3_1, ratio3_1, ratio3_1, ratio3_1, ratio3_1, ratio3_1, ratio3_1, ratio3_1, ratio3_1, ratio3_4,
ratio3_4, ratio3_4, ratio3_4, ratio3_4, ratio3_4, ratio3_4, ratio3_4, ratio3_4, ratio3_4, ratio3_4, ratio3_4, ratio3_4,
ratio3_4, ratio3_4, ratio3_4, ratio3_5, ratio3_5, ratio3_5, ratio3_5, ratio3_5, ratio3_5, ratio3_5, ratio3_5, ratio3_5,
ratio3_5, ratio3_5, ratio3_5, ratio3_5, ratio3_5, ratio3_5, ratio3_5, ratio3_2, ratio3_2, ratio3_2, ratio3_2, ratio3_2,
ratio3_2, ratio3_2, ratio3_2, ratio3_2, ratio3_2, ratio3_2, ratio3_2, ratio3_2, ratio3_2, ratio3_2, ratio3_2, ratio3_7,
ratio3_7, ratio3_7, ratio3_7, ratio3_7, ratio3_7, ratio3_7, ratio3_7, ratio3_7, ratio3_7, ratio3_7, ratio3_7, ratio3_7,
ratio3_7, ratio3_7, ratio3_7, ratio3_8, ratio3_8, ratio3_8, ratio3_8, ratio3_8, ratio3_8, ratio3_8, ratio3_8, ratio3_8,
ratio3_8, ratio3_8, ratio3_8, ratio3_8, ratio3_8, ratio3_8, ratio3_8};

static const ScaleNote harmSubharmfullspan4[128] = {ratio4_1, ratio4_1, ratio4_1, ratio4_1, ratio4_1, ratio4_1, ratio4_1, ratio4_1, ratio4_1, ratio4_1, ratio4_1, ratio4_1, ratio4_1,
ratio4_1, ratio4_1, ratio4_1, ratio4_1, ratio4_1, ratio4_1, ratio4_1, ratio4_1, ratio4_1, ratio4_1, ratio4_1, ratio4_1,
ratio4_1, ratio4_1, ratio4_1, ratio4_1, ratio4_1, ratio4_1, ratio4_1, ratio4_3, ratio4_3, ratio4_3, ratio4_3, ratio4_3,
ratio4_3, ratio4_3, ratio4_3, ratio4_3, ratio4_3, ratio4_3, ratio4_3, ratio4_3, ratio4_3, ratio4_3, ratio4_3, ratio4_1,
ratio4_1, ratio4_1, ratio4_1, ratio4_1, ratio4_1, ratio4_1, ratio4_1, ratio4_1, ratio4_1, ratio4_1, ratio4_1, ratio4_1,
ratio4_1, ratio4_1, ratio4_1, ratio4_5, ratio4_5, ratio4_5, ratio4_5, ratio4_5, ratio4_5, ratio4_5, ratio4_5, ratio4_5,
ratio4_5, ratio4_5, ratio4_5, ratio4_5, ratio4_5, ratio4_5, ratio4_5, ratio4_3, ratio4_3, ratio4_3, ratio4_3, ratio4_3,
ratio4_3, ratio4_3, ratio4_3, ratio4_3, ratio4_3, ratio4_3, ratio4_3, ratio4_3, ratio4_3, ratio4_3, ratio4_3, ratio4_7,
ratio4_7, ratio4_7, ratio4_7, ratio4_7, ratio4_7, ratio4_7, ratio4_7, ratio4_7, ratio4_7, ratio4_7, ratio4_7, ratio4_7,
ratio4_7, ratio4_7, ratio4_7, ratio4_2, ratio4_2, ratio4_2, ratio4_2, ratio4_2, ratio4_2, ratio4_2, ratio4_2, ratio4_2,
ratio4_2, ratio4_2, ratio4_2, ratio4_2, ratio4_2, ratio4_2, ratio4_2};

static const ScaleNote harmSubharmfullspan5[128] = {ratio5_1, ratio5_1, ratio5_1, ratio5_1, ratio5_1, ratio5_1, ratio5_1, ratio5_1, ratio5_1, ratio5_1, ratio5_1, ratio5_1, ratio5_1,
ratio5_1, ratio5_1, ratio5_1, ratio5_2, ratio5_2, ratio5_2, ratio5_2, ratio5_2, ratio5_2, ratio5_2, ratio5_2, ratio5_2,
ratio5_2, ratio5_2, ratio5_2, ratio5_2, ratio5_2, ratio5_2, ratio5_2, ratio5_3, ratio5_3, ratio5_3, ratio5_3, ratio5_3,
ratio5_3, ratio5_3, ratio5_3, ratio5_3, ratio5_3, ratio5_3, ratio5_3, ratio5_3, ratio5_3, ratio5_3, ratio5_3, ratio5_4,
ratio5_4, ratio5_4, ratio5_4, ratio5_4, ratio5_4, ratio5_4, ratio5_4, ratio5_4, ratio5_4, ratio5_4, ratio5_4, ratio5_4,
ratio5_4, ratio5_4, ratio5_4, ratio5_1, ratio5_1, ratio5_1, ratio5_1, ratio5_1, ratio5_1, ratio5_1, ratio5_1, ratio5_1,
ratio5_1, ratio5_1, ratio5_1, ratio5_1, ratio5_1, ratio5_1, ratio5_1, ratio5_6, ratio5_6, ratio5_6, ratio5_6, ratio5_6,
ratio5_6, ratio5_6, ratio5_6, ratio5_6, ratio5_6, ratio5_6, ratio5_6, ratio5_6, ratio5_6, ratio5_6, ratio5_6, ratio5_7,
ratio5_7, ratio5_7, ratio5_7, ratio5_7, ratio5_7, ratio5_7, ratio5_7, ratio5_7, ratio5_7, ratio5_7, ratio5_7, ratio5_7,
ratio5_7, ratio5_7, ratio5_7, ratio5_8, ratio5_8, ratio5_8, ratio5_8, ratio5_8, ratio5_8, ratio5_8, ratio5_8, ratio5_8,
ratio5_8, ratio5_8, ratio5_8, ratio5_8, ratio5_8, ratio5_8, ratio5_8};

static const ScaleNote harmSubharmfullspan6[128] = {ratio6_1, ratio6_1, ratio6_1, ratio6_1, ratio6_1, ratio6_1, ratio6_1, ratio6_1, ratio6_1, ratio6_1, ratio6_1, ratio6_1, ratio6_1,
ratio6_1, ratio6_1, ratio6_1, ratio6_1, ratio6_1, ratio6_1, ratio6_1, ratio6_1, ratio6_1, ratio6_1, ratio6_1, ratio6_1,
ratio6_1, ratio6_1, ratio6_1, ratio6_1, ratio6_1, ratio6_1, ratio6_1, ratio6_1, ratio6_1, ratio6_1, ratio6_1, ratio6_1,
ratio6_1, ratio6_1, ratio6_1, ratio6_1, ratio6_1, ratio6_1, ratio6_1, ratio6_1, ratio6_1, ratio6_1, ratio6_1, ratio6_2,
ratio6_2, ratio6_2, ratio6_2, ratio6_2, ratio6_2, ratio6_2, ratio6_2, ratio6_2, ratio6_2, ratio6_2, ratio6_2, ratio6_2,
ratio6_2, ratio6_2, ratio6_2, ratio6_5, ratio6_5, ratio6_5, ratio6_5, ratio6_5, ratio6_5, ratio6_5, ratio6_5, ratio6_5,
ratio6_5, ratio6_5, ratio6_5, ratio6_5, ratio6_5, ratio6_5, ratio6_5, ratio6_1, ratio6_1, ratio6_1, ratio6_1, ratio6_1,
ratio6_1, ratio6_1, ratio6_1, ratio6_1, ratio6_1, ratio6_1, ratio6_1, ratio6_1, ratio6_1, ratio6_1, ratio6_1, ratio6_7,
ratio6_7, ratio6_7, ratio6_7, ratio6_7, ratio6_7, ratio6_7, ratio6_7, ratio6_7, ratio6_7, ratio6_7, ratio6_7, ratio6_7,
ratio6_7, ratio6_7, ratio6_7, ratio6_4, ratio6_4, ratio6_4, ratio6_4, ratio6_4, ratio6_4, ratio6_4, ratio6_4, ratio6_4,
ratio6_4, ratio6_4, ratio6_4, ratio6_4, ratio6_4, ratio6_4, ratio6_4};

static const ScaleNote harmSubharmfullspan7[128] = {ratio7_1, ratio7_1, ratio7_1, ratio7_1, ratio7_1, ratio7_1, ratio7_1, ratio7_1, ratio7_1, ratio7_1, ratio7_1, ratio7_1, ratio7_1,
ratio7_1, ratio7_1, ratio7_1, ratio7_2, ratio7_2, ratio7_2, ratio7_2, ratio7_2, ratio7_2, ratio7_2, ratio7_2, ratio7_2,
ratio7_2, ratio7_2, ratio7_2, ratio7_2, ratio7_2, ratio7_2, ratio7_2, ratio7_3, ratio7_3, ratio7_3, ratio7_3, ratio7_3,
ratio7_3, ratio7_3, ratio7_3, ratio7_3, ratio7_3, ratio7_3, ratio7_3, ratio7_3, ratio7_3, ratio7_3, ratio7_3, ratio7_4,
ratio7_4, ratio7_4, ratio7_4, ratio7_4, ratio7_4, ratio7_4, ratio7_4, ratio7_4, ratio7_4, ratio7_4, ratio7_4, ratio7_4,
ratio7_4, ratio7_4, ratio7_4, ratio7_5, ratio7_5, ratio7_5, ratio7_5, ratio7_5, ratio7_5, ratio7_5, ratio7_5, ratio7_5,
ratio7_5, ratio7_5, ratio7_5, ratio7_5, ratio7_5, ratio7_5, ratio7_5, ratio7_6, ratio7_6, ratio7_6, ratio7_6, ratio7_6,
ratio7_6, ratio7_6, ratio7_6, ratio7_6, ratio7_6, ratio7_6, ratio7_6, ratio7_6, ratio7_6, ratio7_6, ratio7_6, ratio7_1,
ratio7_1, ratio7_1, ratio7_1, ratio7_1, ratio7_1, ratio7_1, ratio7_1, ratio7_1, ratio7_1, ratio7_1, ratio7_1, ratio7_1,
ratio7_1, ratio7_1, ratio7_1, ratio7_8, ratio7_8, ratio7_8, ratio7_8, ratio7_8, ratio7_8, ratio7_8, ratio7_8, ratio7_8,
ratio7_8, ratio7_8, ratio7_8, ratio7_8, ratio7_8, ratio7_8, ratio7_8};

static const ScaleNote harmSubharmfullspan8[128] = {ratio8_1, ratio8_1, ratio8_1, ratio8_1, ratio8_1, ratio8_1, ratio8_1, ratio8_1, ratio8_1, ratio8_1, ratio8_1, ratio8_1, ratio8_1,
ratio8_1, ratio8_1, ratio8_1, ratio8_1, ratio8_1, ratio8_1, ratio8_1, ratio8_1, ratio8_1, ratio8_1, ratio8_1, ratio8_1,
ratio8_1, ratio8_1, ratio8_1, ratio8_1, ratio8_1, ratio8_1, ratio8_1, ratio8_3, ratio8_3, ratio8_3, ratio8_3, ratio8_3,
ratio8_3, ratio8_3, ratio8_3, ratio8_3, ratio8_3, ratio8_3, ratio8_3, ratio8_3, ratio8_3, ratio8_3, ratio8_3, ratio8_1,
ratio8_1, ratio8_1, ratio8_1, ratio8_1, ratio8_1, ratio8_1, ratio8_1, ratio8_1, ratio8_1, ratio8_1, ratio8_1, ratio8_1,
ratio8_1, ratio8_1, ratio8_1, ratio8_5, ratio8_5, ratio8_5, ratio8_5, ratio8_5, ratio8_5, ratio8_5, ratio8_5, ratio8_5,
ratio8_5, ratio8_5, ratio8_5, ratio8_5, ratio8_5, ratio8_5, ratio8_5, ratio8_3, ratio8_3, ratio8_3, ratio8_3, ratio8_3,
ratio8_3, ratio8_3, ratio8_3, ratio8_3, ratio8_3, ratio8_3, ratio8_3, ratio8_3, ratio8_3, ratio8_3, ratio8_3, ratio8_7,
ratio8_7, ratio8_7, ratio8_7, ratio8_7, ratio8_7, ratio8_7, ratio8_7, ratio8_7, ratio8_7, ratio8_7, ratio8_7, ratio8_7,
ratio8_7, ratio8_7, ratio8_7, ratio8_1, ratio8_1, ratio8_1, ratio8_1, ratio8_1, ratio8_1, ratio8_1, ratio8_1, ratio8_1,
ratio8_1, ratio8_1, ratio8_1, ratio8_1, ratio8_1, ratio8_1, ratio8_1};



static const ScaleNote chromatic5primefullspan[128] = {ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_15, ratio1_15,
ratio1_15, ratio1_15, ratio1_15, ratio1_15, ratio1_15, ratio1_15, ratio1_15, ratio1_15, ratio1_15, ratio1_8, ratio1_8, ratio1_8,
ratio1_8, ratio1_8, ratio1_8, ratio1_8, ratio1_8, ratio1_8, ratio1_8, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5,
ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_4, ratio1_4, ratio1_4, ratio1_4, ratio1_4, ratio1_4,
ratio1_4, ratio1_4, ratio1_4, ratio1_4, ratio1_4, ratio1_3, ratio1_3, ratio1_3, ratio1_3, ratio1_3, ratio1_3, ratio1_3,
ratio1_3, ratio1_3, ratio1_3, ratio1_18, ratio1_18, ratio1_18, ratio1_18, ratio1_18, ratio1_18, ratio1_18, ratio1_18, ratio1_18,
ratio1_18, ratio1_18, ratio1_2, ratio1_2, ratio1_2, ratio1_2, ratio1_2, ratio1_2, ratio1_2, ratio1_2, ratio1_2, ratio1_2,
ratio1_2, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_3,
ratio1_3, ratio1_3, ratio1_3, ratio1_3, ratio1_3, ratio1_3, ratio1_3, ratio1_3, ratio1_3, ratio1_3, ratio1_5, ratio1_5,
ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_8, ratio1_8, ratio1_8,
ratio1_8, ratio1_8, ratio1_8, ratio1_8, ratio1_8, ratio1_8, ratio1_8};

static const ScaleNote major5primefullspan[128] = {ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_1,
ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_8, ratio1_8, ratio1_8,
ratio1_8, ratio1_8, ratio1_8, ratio1_8, ratio1_8, ratio1_8, ratio1_8, ratio1_8, ratio1_8, ratio1_8, ratio1_8, ratio1_8,
ratio1_8, ratio1_8, ratio1_8, ratio1_8, ratio1_8, ratio1_8, ratio1_4, ratio1_4, ratio1_4, ratio1_4, ratio1_4, ratio1_4,
ratio1_4, ratio1_4, ratio1_4, ratio1_4, ratio1_4, ratio1_3, ratio1_3, ratio1_3, ratio1_3, ratio1_3, ratio1_3, ratio1_3,
ratio1_3, ratio1_3, ratio1_3, ratio1_3, ratio1_3, ratio1_3, ratio1_3, ratio1_3, ratio1_3, ratio1_3, ratio1_3, ratio1_3,
ratio1_3, ratio1_3, ratio1_2, ratio1_2, ratio1_2, ratio1_2, ratio1_2, ratio1_2, ratio1_2, ratio1_2, ratio1_2, ratio1_2,
ratio1_2, ratio1_2, ratio1_2, ratio1_2, ratio1_2, ratio1_2, ratio1_2, ratio1_2, ratio1_2, ratio1_2, ratio1_2, ratio1_3,
ratio1_3, ratio1_3, ratio1_3, ratio1_3, ratio1_3, ratio1_3, ratio1_3, ratio1_3, ratio1_3, ratio1_3, ratio1_3, ratio1_3,
ratio1_3, ratio1_3, ratio1_3, ratio1_3, ratio1_3, ratio1_3, ratio1_3, ratio1_3, ratio1_3, ratio1_8, ratio1_8, ratio1_8,
ratio1_8, ratio1_8, ratio1_8, ratio1_8, ratio1_8, ratio1_8, ratio1_8};

static const ScaleNote dorian5primefullspan[128] = {ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_1,
ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_8, ratio1_8, ratio1_8,
ratio1_8, ratio1_8, ratio1_8, ratio1_8, ratio1_8, ratio1_8, ratio1_8, ratio1_8, ratio1_8, ratio1_8, ratio1_8, ratio1_8,
ratio1_8, ratio1_8, ratio1_8, ratio1_8, ratio1_8, ratio1_8, ratio1_4, ratio1_4, ratio1_4, ratio1_4, ratio1_4, ratio1_4,
ratio1_4, ratio1_4, ratio1_4, ratio1_4, ratio1_4, ratio1_4, ratio1_4, ratio1_4, ratio1_4, ratio1_4, ratio1_4, ratio1_4,
ratio1_4, ratio1_4, ratio1_4, ratio1_4, ratio1_4, ratio1_4, ratio1_4, ratio1_4, ratio1_4, ratio1_4, ratio1_4, ratio1_4,
ratio1_4, ratio1_4, ratio1_2, ratio1_2, ratio1_2, ratio1_2, ratio1_2, ratio1_2, ratio1_2, ratio1_2, ratio1_2, ratio1_2,
ratio1_2, ratio1_2, ratio1_2, ratio1_2, ratio1_2, ratio1_2, ratio1_2, ratio1_2, ratio1_2, ratio1_2, ratio1_2, ratio1_3,
ratio1_3, ratio1_3, ratio1_3, ratio1_3, ratio1_3, ratio1_3, ratio1_3, ratio1_3, ratio1_3, ratio1_3, ratio1_5, ratio1_5,
ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5,
ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5};

static const ScaleNote phrygian5primefullspan[128] = {ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_15, ratio1_15,
ratio1_15, ratio1_15, ratio1_15, ratio1_15, ratio1_15, ratio1_15, ratio1_15, ratio1_15, ratio1_15, ratio1_15, ratio1_15, ratio1_15,
ratio1_15, ratio1_15, ratio1_15, ratio1_15, ratio1_15, ratio1_15, ratio1_15, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5,
ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5,
ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_3, ratio1_3, ratio1_3, ratio1_3, ratio1_3, ratio1_3, ratio1_3,
ratio1_3, ratio1_3, ratio1_3, ratio1_3, ratio1_3, ratio1_3, ratio1_3, ratio1_3, ratio1_3, ratio1_3, ratio1_3, ratio1_3,
ratio1_3, ratio1_3, ratio1_2, ratio1_2, ratio1_2, ratio1_2, ratio1_2, ratio1_2, ratio1_2, ratio1_2, ratio1_2, ratio1_2,
ratio1_2, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5,
ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5,
ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5,
ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5};

static const ScaleNote lydian5primefullspan[128] = {ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_1,
ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_8, ratio1_8, ratio1_8,
ratio1_8, ratio1_8, ratio1_8, ratio1_8, ratio1_8, ratio1_8, ratio1_8, ratio1_8, ratio1_8, ratio1_8, ratio1_8, ratio1_8,
ratio1_8, ratio1_8, ratio1_8, ratio1_8, ratio1_8, ratio1_8, ratio1_4, ratio1_4, ratio1_4, ratio1_4, ratio1_4, ratio1_4,
ratio1_4, ratio1_4, ratio1_4, ratio1_4, ratio1_4, ratio1_4, ratio1_4, ratio1_4, ratio1_4, ratio1_4, ratio1_4, ratio1_4,
ratio1_4, ratio1_4, ratio1_4, ratio1_18, ratio1_18, ratio1_18, ratio1_18, ratio1_18, ratio1_18, ratio1_18, ratio1_18, ratio1_18,
ratio1_18, ratio1_18, ratio1_2, ratio1_2, ratio1_2, ratio1_2, ratio1_2, ratio1_2, ratio1_2, ratio1_2, ratio1_2, ratio1_2,
ratio1_2, ratio1_2, ratio1_2, ratio1_2, ratio1_2, ratio1_2, ratio1_2, ratio1_2, ratio1_2, ratio1_2, ratio1_2, ratio1_3,
ratio1_3, ratio1_3, ratio1_3, ratio1_3, ratio1_3, ratio1_3, ratio1_3, ratio1_3, ratio1_3, ratio1_3, ratio1_3, ratio1_3,
ratio1_3, ratio1_3, ratio1_3, ratio1_3, ratio1_3, ratio1_3, ratio1_3, ratio1_3, ratio1_3, ratio1_8, ratio1_8, ratio1_8,
ratio1_8, ratio1_8, ratio1_8, ratio1_8, ratio1_8, ratio1_8, ratio1_8};

static const ScaleNote mixolydian5primefullspan[128] = {ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_1,
ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_8, ratio1_8, ratio1_8,
ratio1_8, ratio1_8, ratio1_8, ratio1_8, ratio1_8, ratio1_8, ratio1_8, ratio1_8, ratio1_8, ratio1_8, ratio1_8, ratio1_8,
ratio1_8, ratio1_8, ratio1_8, ratio1_8, ratio1_8, ratio1_8, ratio1_4, ratio1_4, ratio1_4, ratio1_4, ratio1_4, ratio1_4,
ratio1_4, ratio1_4, ratio1_4, ratio1_4, ratio1_4, ratio1_3, ratio1_3, ratio1_3, ratio1_3, ratio1_3, ratio1_3, ratio1_3,
ratio1_3, ratio1_3, ratio1_3, ratio1_3, ratio1_3, ratio1_3, ratio1_3, ratio1_3, ratio1_3, ratio1_3, ratio1_3, ratio1_3,
ratio1_3, ratio1_3, ratio1_2, ratio1_2, ratio1_2, ratio1_2, ratio1_2, ratio1_2, ratio1_2, ratio1_2, ratio1_2, ratio1_2,
ratio1_2, ratio1_2, ratio1_2, ratio1_2, ratio1_2, ratio1_2, ratio1_2, ratio1_2, ratio1_2, ratio1_2, ratio1_2, ratio1_3,
ratio1_3, ratio1_3, ratio1_3, ratio1_3, ratio1_3, ratio1_3, ratio1_3, ratio1_3, ratio1_3, ratio1_3, ratio1_5, ratio1_5,
ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5,
ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5};

static const ScaleNote aeolian5primefullspan[128] = {ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_1,
ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_8, ratio1_8, ratio1_8,
ratio1_8, ratio1_8, ratio1_8, ratio1_8, ratio1_8, ratio1_8, ratio1_8, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5,
ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5,
ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_3, ratio1_3, ratio1_3, ratio1_3, ratio1_3, ratio1_3, ratio1_3,
ratio1_3, ratio1_3, ratio1_3, ratio1_3, ratio1_3, ratio1_3, ratio1_3, ratio1_3, ratio1_3, ratio1_3, ratio1_3, ratio1_3,
ratio1_3, ratio1_3, ratio1_2, ratio1_2, ratio1_2, ratio1_2, ratio1_2, ratio1_2, ratio1_2, ratio1_2, ratio1_2, ratio1_2,
ratio1_2, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5,
ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5,
ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5,
ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5};

static const ScaleNote locrian5primefullspan[128] = {ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_1, ratio1_15, ratio1_15,
ratio1_15, ratio1_15, ratio1_15, ratio1_15, ratio1_15, ratio1_15, ratio1_15, ratio1_15, ratio1_15, ratio1_15, ratio1_15, ratio1_15,
ratio1_15, ratio1_15, ratio1_15, ratio1_15, ratio1_15, ratio1_15, ratio1_15, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5,
ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5,
ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_3, ratio1_3, ratio1_3, ratio1_3, ratio1_3, ratio1_3, ratio1_3,
ratio1_3, ratio1_3, ratio1_3, ratio1_18, ratio1_18, ratio1_18, ratio1_18, ratio1_18, ratio1_18, ratio1_18, ratio1_18, ratio1_18,
ratio1_18, ratio1_18, ratio1_18, ratio1_18, ratio1_18, ratio1_18, ratio1_18, ratio1_18, ratio1_18, ratio1_18, ratio1_18, ratio1_18,
ratio1_18, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5,
ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5,
ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5,
ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5, ratio1_5};






static const ScaleNote *harmSubharmGrid[8] = {harmSubharm1, harmSubharm2, harmSubharm3, harmSubharm4, harmSubharm5, harmSubharm6, harmSubharm7, harmSubharm8};

static const ScaleNote *modal5primeGrid[8] = {chromatic5prime, major5prime, dorian5prime, phrygian5prime, lydian5prime, mixolydian5prime, aeolian5prime, locrian5prime};

static const ScaleNote *harmSubharmfullspanGrid[8] = {harmSubharmfullspan1, harmSubharmfullspan2, harmSubharmfullspan3, harmSubharmfullspan4, harmSubharmfullspan5, harmSubharmfullspan6, harmSubharmfullspan7, harmSubharmfullspan8};

static const ScaleNote *modal5primefullspanGrid[8] = {chromatic5primefullspan, major5primefullspan, dorian5primefullspan, phrygian5primefullspan, lydian5primefullspan, mixolydian5primefullspan, aeolian5primefullspan, locrian5primefullspan};
