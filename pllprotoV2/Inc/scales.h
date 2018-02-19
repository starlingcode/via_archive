#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"

typedef struct {
	uint32_t simplifiedRatio;
	uint32_t fundamentalDivision;

} ScaleNote;

ScaleNote scale[8][8];

ScaleNote *diatonicMinor7ths[8];
ScaleNote *diatonicMajor7ths[8];
ScaleNote *rhythms1[8];
ScaleNote *rhythms2[8];


#define rhythm_16clock_1_16			135266304
#define rhythm_16clock_1_8			134742016
#define rhythm_16clock_3_16			403002709
#define rhythm_16clock_1_4			134479872
#define rhythm_16clock_5_16			671298355
#define rhythm_16clock_3_8			402827946
#define rhythm_16clock_7_16			939673892
#define rhythm_16clock_1_2			134348800
#define rhythm_16clock_9_16			1208076060
#define rhythm_16clock_5_8			671193497
#define rhythm_16clock_11_16		1476490333
#define rhythm_16clock_3_4			402740565
#define rhythm_16clock_13_16		1744911123
#define rhythm_16clock_7_8			939598994
#define rhythm_16clock_15_16		2013335825

#define rhythm_16clock_1_12			135004160
#define rhythm_16clock_1_6			134610944
#define rhythm_16clock_5_12			402810470
#define rhythm_16clock_7_12			134330075
#define rhythm_16clock_2_3			671186944
#define rhythm_16clock_5_6			671167283
#define rhythm_16clock_11_12		1476466501

#define rhythm_8clock_1_16			136314880
#define rhythm_8clock_1_8			135266304
#define rhythm_8clock_3_16			403352234
#define rhythm_8clock_1_4			134742016
#define rhythm_8clock_5_16			671508070
#define rhythm_8clock_3_8			403002709
#define rhythm_8clock_7_16			939823689
#define rhythm_8clock_1_2			134479872
#define rhythm_8clock_9_16			1208192568
#define rhythm_8clock_5_8			671298355
#define rhythm_8clock_11_16			1476585658
#define rhythm_8clock_3_4			402827946
#define rhythm_8clock_13_16			1744991783
#define rhythm_8clock_7_8			939673892
#define rhythm_8clock_15_16			2013405730

#define rhythm_8clock_1_12			135790592
#define rhythm_8clock_1_6			135004160
#define rhythm_8clock_5_12			402967756
#define rhythm_8clock_7_12			134442422
#define rhythm_8clock_2_3			671285248
#define rhythm_8clock_5_6			671245926
#define rhythm_8clock_11_12			1476537995


#define rhythm_4clock_1_16			138412032
#define rhythm_4clock_1_8			136314880
#define rhythm_4clock_3_16			404051285
#define rhythm_4clock_1_4			135266304
#define rhythm_4clock_5_16			671927500
#define rhythm_4clock_3_8			403352234
#define rhythm_4clock_7_16			940123282
#define rhythm_4clock_1_2			134742016
#define rhythm_4clock_9_16			1208425585
#define rhythm_4clock_5_8			671508070
#define rhythm_4clock_11_16			1476776308
#define rhythm_4clock_3_4			403002709
#define rhythm_4clock_13_16			1745153102
#define rhythm_4clock_7_8			939823689
#define rhythm_4clock_15_16			2013545540

#define rhythm_4clock_1_12			137363456
#define rhythm_4clock_1_6			135790592
#define rhythm_4clock_5_12			403282329
#define rhythm_4clock_7_12			134667117
#define rhythm_4clock_2_3			671481856
#define rhythm_4clock_5_6			671403212
#define rhythm_4clock_11_12			1476680983

#define rhythm_2clock_1_16			142606336
#define rhythm_2clock_1_8			138412032
#define rhythm_2clock_3_16			405449386
#define rhythm_2clock_1_4			136314880
#define rhythm_2clock_5_16			672766361
#define rhythm_2clock_3_8			404051285
#define rhythm_2clock_7_16			940722468
#define rhythm_2clock_1_2			135266304
#define rhythm_2clock_9_16			1208891619
#define rhythm_2clock_5_8			671927500
#define rhythm_2clock_11_16			1477157608
#define rhythm_2clock_3_4			403352234
#define rhythm_2clock_13_16			1745475741
#define rhythm_2clock_7_8			940123282
#define rhythm_2clock_15_16			2013825160

#define rhythm_2clock_1_12			140509184
#define rhythm_2clock_1_6			135790592
#define rhythm_2clock_5_12			403911475
#define rhythm_2clock_7_12			135116507
#define rhythm_2clock_2_3			671875072
#define rhythm_2clock_5_6			671717785
#define rhythm_2clock_11_12			1476966958

#define rhythm_1clock_1_16			150994944
#define rhythm_1clock_1_8			142606336
#define rhythm_1clock_3_16			408245589
#define rhythm_1clock_1_4			138412032
#define rhythm_1clock_5_16			674444083
#define rhythm_1clock_3_8			405449386
#define rhythm_1clock_7_16			941920841
#define rhythm_1clock_1_2			136314880
#define rhythm_1clock_9_16			1209823687
#define rhythm_1clock_5_8			672766361
#define rhythm_1clock_11_16			1477920209
#define rhythm_1clock_3_4			404051285
#define rhythm_1clock_13_16			1746121019
#define rhythm_1clock_7_8			940722468
#define rhythm_1clock_15_16			2014384401



/*
#define noteC1 			68157440
#define noteCsharp1 	1007751441
#define noteD1 			538050560
#define noteDsharp1 	336802611
#define noteE1 			269746176
#define noteF1 			202724693
#define noteFsharp1 	1209415907
#define noteG1 			135790592
#define noteGsharp1 	337222041
#define noteA2 			203074218
#define noteAsharp2 	337431756
#define noteB2 			538836992
#define noteC2 			69206016
#define noteCsharp2 	1008869922
#define noteD2 			270794752
#define noteDsharp2 	69625446
#define noteE2 			136839168
#define noteF2 			69905066
#define noteFsharp2 	606892487
#define noteG2 			70254592
#define noteGsharp2 	338899763
#define noteA3 			204821845
#define noteAsharp3 	339319193
#define noteB3 			272367616
#define noteC3 			71303168
#define noteCsharp3 	1011106884
#define noteD3 			138936320
#define noteDsharp3 	340577484
#define noteE3 			72351744
#define noteF3 			206918997
#define noteFsharp3 	609805198
#define noteG3 			73400320
#define noteGsharp3 	342255206
#define noteA4 			208317098
#define noteAsharp4 	343094067
#define noteB4 			142082048
#define noteC4 			75497472
/*

/*
static const uint32_t diatonicMinor7thsRow1[8] = {noteC1, noteD1, noteDsharp1, noteF1 , noteG1 , noteGsharp1, noteAsharp2, noteC2};
static const uint32_t diatonicMinor7thsRow2[8] = {noteC1, noteDsharp1, noteG1, noteAsharp2 , noteC2, noteDsharp2, noteG2, noteAsharp3 };
static const uint32_t diatonicMinor7thsRow3[8] = {noteD1, noteF1, noteA2, noteC2 , noteD2, noteF2, noteA3, noteC3};
static const uint32_t diatonicMinor7thsRow4[8] = {noteDsharp1, noteG1, noteAsharp2, noteD2, noteDsharp2 , noteG2, noteAsharp3, noteD3};
static const uint32_t diatonicMinor7thsRow5[8] = {noteF1, noteGsharp1, noteC2, noteDsharp2, noteF2 , noteGsharp2, noteC3, noteDsharp3};
static const uint32_t diatonicMinor7thsRow6[8] = {noteG1, noteAsharp2, noteD2, noteF2 , noteG2, noteAsharp3, noteD3, noteF3};
static const uint32_t diatonicMinor7thsRow7[8] = {noteGsharp1, noteC2, noteDsharp2, noteG2 , noteGsharp2, noteC3, noteDsharp3, noteG3 };
static const uint32_t diatonicMinor7thsRow8[8] = {noteAsharp2, noteD2, noteF2, noteA3 , noteAsharp3, noteD3, noteF3, noteA4 };

static const uint32_t diatonicMajor7thsRow1[8] = {noteC1, noteD1, noteE1, noteF1 , noteG1 , noteA2, noteB2, noteC2};
static const uint32_t diatonicMajor7thsRow2[8] = {noteC1, noteE1, noteG1, noteB2 , noteC2, noteE2, noteG2, noteB3 };
static const uint32_t diatonicMajor7thsRow3[8] = {noteD1, noteF1, noteA2, noteC2 , noteD2, noteF2, noteA3, noteC3};
static const uint32_t diatonicMajor7thsRow4[8] = {noteE1, noteG1, noteB2, noteD2, noteE2 , noteG2, noteB3, noteD3};
static const uint32_t diatonicMajor7thsRow5[8] = {noteF1, noteA2, noteC2, noteE2, noteF2 , noteA3, noteC3, noteE3};
static const uint32_t diatonicMajor7thsRow6[8] = {noteG1, noteB2, noteD2, noteF2 , noteG2, noteB3, noteD3, noteF3};
static const uint32_t diatonicMajor7thsRow7[8] = {noteA2, noteC2, noteE2, noteG2 , noteA3, noteC3, noteE3, noteG3 };
static const uint32_t diatonicMajor7thsRow8[8] = {noteB2, noteD2, noteF2, noteA3 , noteB3, noteD3, noteF3, noteA4 };
*/


#define noteC1 {16777216, 1} // 1/1
#define noteCsharp1 {17895697, 15} // 16/15
#define noteD1 {18874368, 8} // 9/8
#define noteDsharp1 {20132659, 5} // 6/5
#define noteE1 {20971520, 4} // 5/4
#define noteF1 {22369621, 3} // 4/3
#define noteFsharp1 {23301689, 12} // 25/18
#define noteG1 {25165824, 2} // 3/2
#define noteGsharp1 {26843546, 5} // 8/5
#define noteA2 {27962026.7, 3} // 5/3
#define noteAsharp2 {30198989, 5} // 9/5
#define noteB2 {31457280, 8} // 15/8
#define noteC2 {33554432, 1} // 2/1
#define noteCsharp2 {35791394, 15} // 32/15
#define noteD2 {37748736, 4} // 18/4
#define noteDsharp2 {40265318, 1} // 12/1
#define noteE2 {41943040, 2} // 10/2
#define noteF2 {44739243, 1} // 8/1
#define noteFsharp2 {46603378, 9} // 50/9
#define noteG2 {50331648, 1} // 6/1
#define noteGsharp2 {53687091, 5} // 16/5
#define noteA3 {55924053, 3} // 10/3
#define noteAsharp3 {60397978, 5} // 18/5
#define noteB3 {62914560, 4} //30/8
#define noteC3 {67108864, 1} // 4/1
#define noteCsharp3 {71582788, 15} // 64/15
#define noteD3 {75497472, 2} // 36/8
#define noteDsharp3 {80530637, 5} // 24/5
#define noteE3 {83886080, 1} // 20/4
#define noteF3 {89478485, 3} // 16/3
#define noteFsharp3 {93206756, 9} // 200/18
#define noteG3 {100663296, 1} // 12/2
#define noteGsharp3 {107374182, 5} // 32/5
#define noteA4 {111848107, 3} // 20/3
#define noteAsharp4 {120795955, 5} // 36/5
#define noteB4 {125829120, 2} // 60/8
#define noteC4 {134217728, 1} // 8/1

#define rhythm16clock_1_32_no_reset {33554432, 1} // 2/1
#define rhythm16clock_1_24_no_reset {25165824, 2} // 3/2
#define rhythm16clock_1_16_no_reset {16777216, 1} // 1/1
#define rhythm16clock_1_12_no_reset {12582912, 4} // 3/4
#define rhythm16clock_1_8_no_reset {8388608, 2} // 1/2
#define rhythm16clock_1_6_no_reset {6291456, 8} // 3/8
#define rhythm16clock_3_16_no_reset {5592405, 3} // 1/3
#define rhythm16clock_1_4_no_reset {4194304, 4} // 1/4
#define rhythm16clock_5_16_no_reset {3355443, 5} // 1/5
#define rhythm16clock_1_3_no_reset {3145728, 7} // 3/16
#define rhythm16clock_3_8_no_reset {2796203, 6} // 1/6
#define rhythm16clock_7_16_no_reset {2396745, 7} // 1/7
#define rhythm16clock_1_2_no_reset {2097152, 8} // 1/8
#define rhythm16clock_9_16_no_reset {1864135, 9} // 1/9
#define rhythm16clock_5_8_no_reset {1677721, 10} // 1/10
#define rhythm16clock_11_16_no_reset {1677721, 11} // 1/11
#define rhythm16clock_3_4_no_reset {1525201, 12} // 1/12
#define rhythm16clock_13_16_no_reset {1290555, 13} // 1/13
#define rhythm16clock_7_8_no_reset {1198373, 14} // 1/14
#define rhythm16clock_15_16_no_reset {1118481, 15} // 1/15

#define rhythm16clock_1_32_8_reset {33554432, 8} // 2/1
#define rhythm16clock_1_24_8_reset {25165824, 8} // 3/2
#define rhythm16clock_1_16_8_reset {16777216, 8} // 1/1
#define rhythm16clock_1_12_8_reset {12582912, 8} // 3/4
#define rhythm16clock_1_8_8_reset {8388608, 8} // 1/2
#define rhythm16clock_1_6_8_reset {6291456, 8} // 3/8
#define rhythm16clock_3_16_8_reset {5592405, 8} // 1/3
#define rhythm16clock_1_4_8_reset {4194304, 8} // 1/4
#define rhythm16clock_5_16_8_reset {3355443, 8} // 1/5
#define rhythm16clock_1_3_8_reset {3145728, 8} // 3/16
#define rhythm16clock_3_8_8_reset {2796203, 8} // 1/6
#define rhythm16clock_7_16_8_reset {2396745, 8} // 1/7
#define rhythm16clock_1_2_8_reset {2097152, 8} // 1/8



#define rhythm16clock_1_32_16_reset {33554432, 16} // 2/1
#define rhythm16clock_1_24_16_reset {25165824, 16} // 3/2
#define rhythm16clock_1_16_16_reset {16777216, 16} // 1/1
#define rhythm16clock_1_12_16_reset {12582912, 16} // 3/4
#define rhythm16clock_1_8_16_reset {8388608, 16} // 1/2
#define rhythm16clock_1_6_16_reset {6291456, 16} // 3/8
#define rhythm16clock_3_16_16_reset {5592405, 16} // 1/3
#define rhythm16clock_1_4_16_reset {4194304, 16} // 1/4
#define rhythm16clock_5_16_16_reset {3355443, 16} // 1/5
#define rhythm16clock_1_3_16_reset {3145728, 16} // 3/16
#define rhythm16clock_3_8_16_reset {2796203, 16} // 1/6
#define rhythm16clock_7_16_16_reset {2396745, 16} // 1/7
#define rhythm16clock_1_2_16_reset {2097152, 16} // 1/8
#define rhythm16clock_9_16_16_reset {1864135, 16} // 1/9
#define rhythm16clock_5_8_16_reset {1677721, 16} // 1/10
#define rhythm16clock_11_16_16_reset {1677721, 16} // 1/11
#define rhythm16clock_3_4_16_reset {1525201, 16} // 1/12
#define rhythm16clock_13_16_16_reset {1290555, 16} // 1/13
#define rhythm16clock_7_8_16_reset {1198373, 16} // 1/14
#define rhythm16clock_15_16_16_reset {1118481, 16} // 1/15



#define rhythm4clock_1_32_no_reset {33554432 << 2, 1} // 2/1
#define rhythm4clock_1_24_no_reset {25165824 << 2, 2} // 3/2
#define rhythm4clock_1_16_no_reset {16777216 << 2, 1} // 1/1
#define rhythm4clock_1_12_no_reset {12582912 << 2, 4} // 3/4
#define rhythm4clock_1_8_no_reset {8388608 << 2, 2} // 1/2
#define rhythm4clock_1_6_no_reset {6291456 << 2, 8} // 3/8
#define rhythm4clock_3_16_no_reset {5592405 << 2, 3} // 1/3
#define rhythm4clock_1_4_no_reset {4194304 << 2, 4} // 1/4
#define rhythm4clock_5_16_no_reset {3355443 << 2, 5} // 1/5
#define rhythm4clock_1_3_no_reset {3145728 << 2, 7} // 3/16
#define rhythm4clock_3_8_no_reset {2796203 << 2, 6} // 1/6
#define rhythm4clock_7_16_no_reset {2396745 << 2, 7} // 1/7
#define rhythm4clock_1_2_no_reset {2097152 << 2, 8} // 1/8
#define rhythm4clock_9_16_no_reset {1864135 << 2, 9} // 1/9
#define rhythm4clock_5_8_no_reset {1677721 << 2, 10} // 1/10
#define rhythm4clock_11_16_no_reset {1677721 << 2, 11} // 1/11
#define rhythm4clock_3_4_no_reset {1525201 << 2, 12} // 1/12
#define rhythm4clock_13_16_no_reset {1290555 << 2, 13} // 1/13
#define rhythm4clock_7_8_no_reset {1198373 << 2, 14} // 1/14
#define rhythm4clock_15_16_no_reset {1118481 << 2, 15} // 1/15

#define rhythm4clock_1_32_8_reset {33554432 << 2, 2} // 2/1
#define rhythm4clock_1_24_8_reset {25165824 << 2, 2} // 3/2
#define rhythm4clock_1_16_8_reset {16777216 << 2, 2} // 1/1
#define rhythm4clock_1_12_8_reset {12582912 << 2, 2} // 3/4
#define rhythm4clock_1_8_8_reset {8388608 << 2, 2} // 1/2
#define rhythm4clock_1_6_8_reset {6291456 << 2, 2} // 3/8
#define rhythm4clock_3_16_8_reset {5592405 << 2, 2} // 1/3
#define rhythm4clock_1_4_8_reset {4194304 << 2, 2} // 1/4
#define rhythm4clock_5_16_8_reset {3355443 << 2, 2} // 1/5
#define rhythm4clock_1_3_8_reset {3145728 << 2, 2} // 3/16
#define rhythm4clock_3_8_8_reset {2796203 << 2, 2} // 1/6
#define rhythm4clock_7_16_8_reset {2396745 << 2, 2} // 1/7
#define rhythm4clock_1_2_8_reset {2097152 << 2, 2} // 1/8



#define rhythm4clock_1_32_16_reset {33554432 << 2, 4} // 2/1
#define rhythm4clock_1_24_16_reset {25165824 << 2, 4} // 3/2
#define rhythm4clock_1_16_16_reset {16777216 << 2, 4} // 1/1
#define rhythm4clock_1_12_16_reset {12582912 << 2, 4} // 3/4
#define rhythm4clock_1_8_16_reset {8388608 << 2, 4} // 1/2
#define rhythm4clock_1_6_16_reset {6291456 << 2, 4} // 3/8
#define rhythm4clock_3_16_16_reset {5592405 << 2, 4} // 1/3
#define rhythm4clock_1_4_16_reset {4194304 << 2, 4} // 1/4
#define rhythm4clock_5_16_16_reset {3355443 << 2, 4} // 1/5
#define rhythm4clock_1_3_16_reset {3145728 << 2, 4} // 3/16
#define rhythm4clock_3_8_16_reset {2796203 << 2, 4} // 1/6
#define rhythm4clock_7_16_16_reset {2396745 << 2, 4} // 1/7
#define rhythm4clock_1_2_16_reset {2097152 << 2, 4} // 1/8
#define rhythm4clock_9_16_16_reset {1864135 << 2, 4} // 1/9
#define rhythm4clock_5_8_16_reset {1677721 << 2, 4} // 1/10
#define rhythm4clock_11_16_16_reset {1677721 << 2, 4} // 1/11
#define rhythm4clock_3_4_16_reset {1525201 << 2, 4} // 1/12
#define rhythm4clock_13_16_16_reset {1290555 << 2, 4} // 1/13
#define rhythm4clock_7_8_16_reset {1198373 << 2, 4} // 1/14
#define rhythm4clock_15_16_16_reset {1118481 << 2, 4} // 1/15









