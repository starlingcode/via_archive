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

#define ratio80_7 {748982, 3681400539, 7}
#define ratio5_1 {327680, 0, 1}
#define ratio7_256 {1792, 0, 256}
#define ratio7_80 {5734, 1717986918, 80}
#define ratio8_40 {13107, 858993459, 5}
#define ratio1_192 {341, 1431655765, 192}
#define ratio16_7 {149796, 2454267026, 7}
#define ratio8_320 {1638, 1717986918, 40}
#define ratio8_7 {74898, 1227133513, 7}
#define ratio3_512 {384, 0, 512}
#define ratio8_192 {2730, 2863311530, 24}
#define ratio4_192 {1365, 1431655765, 48}
#define ratio3_8 {24576, 0, 8}
#define ratio6_256 {1536, 0, 128}
#define ratio1_56 {1170, 1227133513, 56}
#define ratio3_5 {39321, 2576980377, 5}
#define ratio4_56 {4681, 613566756, 14}
#define ratio5_64 {5120, 0, 64}
#define ratio7_3 {152917, 1431655765, 3}
#define ratio1_128 {512, 0, 128}
#define ratio48_4 {786432, 0, 1}
#define ratio6_7 {56173, 3067833782, 7}
#define ratio7_1 {458752, 0, 1}
#define ratio1_64 {1024, 0, 64}
#define ratio48_8 {393216, 0, 1}
#define ratio80_8 {655360, 0, 1}
#define ratio8_24 {21845, 1431655765, 3}
#define ratio8_1 {524288, 0, 1}
#define ratio4_7 {37449, 613566756, 7}
#define ratio5_6 {54613, 1431655765, 6}
#define ratio7_96 {4778, 2863311530, 96}
#define ratio32_5 {419430, 1717986918, 5}
#define ratio1_8 {8192, 0, 8}
#define ratio32_7 {299593, 613566756, 7}
#define ratio8_64 {8192, 0, 8}
#define ratio8_6 {87381, 1431655765, 3}
#define ratio64_3 {1398101, 1431655765, 3}
#define ratio1_24 {2730, 2863311530, 24}
#define ratio2_192 {682, 2863311530, 96}
#define ratio2_64 {2048, 0, 32}
#define ratio1_256 {256, 0, 256}
#define ratio1_1 {65536, 0, 1}
#define ratio48_7 {449389, 3067833782, 7}
#define ratio6_112 {3510, 3681400539, 56}
#define ratio16_3 {349525, 1431655765, 3}
#define ratio112_6 {1223338, 2863311531, 3}
#define ratio2_16 {8192, 0, 8}
#define ratio64_5 {838860, 3435973837, 5}
#define ratio7_48 {9557, 1431655765, 48}
#define ratio96_5 {1258291, 858993459, 5}
#define ratio5_112 {2925, 3067833782, 112}
#define ratio7_64 {7168, 0, 64}
#define ratio8_3 {174762, 2863311530, 3}
#define ratio3_2 {98304, 0, 2}
#define ratio96_7 {898779, 1840700269, 7}
#define ratio1_16 {4096, 0, 16}
#define ratio5_7 {46811, 1840700269, 7}
#define ratio2_8 {16384, 0, 4}
#define ratio80_6 {873813, 1431655765, 3}
#define ratio3_128 {1536, 0, 128}
#define ratio2_56 {2340, 2454267026, 28}
#define ratio7_8 {57344, 0, 8}
#define ratio16_5 {209715, 858993459, 5}
#define ratio7_512 {896, 0, 512}
#define ratio4_8 {32768, 0, 2}
#define ratio6_5 {78643, 858993459, 5}
#define ratio6_80 {4915, 858993459, 40}
#define ratio5_3 {109226, 2863311530, 3}
#define ratio4_3 {87381, 1431655765, 3}
#define ratio4_5 {52428, 3435973836, 5}
#define ratio16_2 {524288, 0, 1}
#define ratio4_64 {4096, 0, 16}
#define ratio3_80 {2457, 2576980377, 80}
#define ratio7_128 {3584, 0, 128}
#define ratio4_320 {819, 858993459, 80}
#define ratio1_4 {16384, 0, 4}
#define ratio7_4 {114688, 0, 4}
#define ratio7_16 {28672, 0, 16}
#define ratio2_1 {131072, 0, 1}
#define ratio7_6 {76458, 2863311530, 6}
#define ratio5_2 {163840, 0, 2}
#define ratio5_96 {3413, 1431655765, 96}
#define ratio4_1 {262144, 0, 1}
#define ratio1_40 {1638, 1717986918, 40}
#define ratio8_2 {262144, 0, 1}
#define ratio32_3 {699050, 2863311530, 3}
#define ratio112_8 {917504, 0, 1}
#define ratio7_5 {91750, 1717986918, 5}
#define ratio1_6 {10922, 2863311530, 6}
#define ratio1_3 {21845, 1431655765, 3}
#define ratio5_4 {81920, 0, 4}
#define ratio6_16 {24576, 0, 8}
#define ratio5_256 {1280, 0, 256}
#define ratio7_32 {14336, 0, 32}
#define ratio3_256 {768, 0, 256}
#define ratio5_8 {40960, 0, 8}
#define ratio1_2 {32768, 0, 2}
#define ratio2_7 {18724, 2454267026, 7}
#define ratio2_24 {5461, 1431655765, 12}
#define ratio16_1 {1048576, 0, 1}
#define ratio64_7 {599186, 1227133513, 7}
#define ratio2_5 {26214, 1717986918, 5}
#define ratio32_1 {2097152, 0, 1}
#define ratio5_32 {10240, 0, 32}
#define ratio8_4 {131072, 0, 1}
#define ratio6_1 {393216, 0, 1}
#define ratio5_48 {6826, 2863311530, 48}
#define ratio1_5 {13107, 858993459, 5}
#define ratio2_3 {43690, 2863311530, 3}
#define ratio5_512 {640, 0, 512}
#define ratio4_24 {10922, 2863311530, 6}
#define ratio3_1 {196608, 0, 1}
#define ratio3_4 {49152, 0, 4}
#define ratio48_5 {629145, 2576980377, 5}
#define ratio80_4 {1310720, 0, 1}
#define ratio3_16 {12288, 0, 16}
#define ratio5_128 {2560, 0, 128}
#define ratio7_2 {229376, 0, 2}
#define ratio8_8 {65536, 0, 1}
#define ratio4_40 {6553, 2576980377, 10}
#define ratio8_5 {104857, 2576980377, 5}
#define ratio8_56 {9362, 1227133513, 7}
#define ratio3_7 {28086, 3681400539, 7}
#define ratio3_32 {6144, 0, 32}
#define ratio1_32 {2048, 0, 32}
#define ratio1_320 {204, 3435973836, 320}
#define ratio1_7 {9362, 1227133513, 7}
#define ratio2_320 {409, 2576980377, 160}
#define ratio3_112 {1755, 1840700269, 112}
#define ratio5_16 {20480, 0, 16}
#define ratio3_64 {3072, 0, 64}
#define ratio1_48 {1365, 1431655765, 48}
#define ratio2_40 {3276, 3435973836, 20}

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

static const ScaleNote *harmSubharmGrid[8] = {harmSubharm1, harmSubharm2, harmSubharm3, harmSubharm4, harmSubharm5, harmSubharm6, harmSubharm7, harmSubharm8};


