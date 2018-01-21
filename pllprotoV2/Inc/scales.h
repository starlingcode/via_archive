#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"

uint32_t scale[8][8];

/*
#define noteC1 			((1 << 20)/1) | (1 << 27)
#define noteCsharp1 	((16 << 20)/15) | (15 << 27)
#define noteD1 			((9 << 20)/8) | (8 << 27)
#define noteDsharp1 	((6 << 20)/5) | (5 << 27)
#define noteE1 			((5 << 20)/4) | (4 << 27)
#define noteF1 			((4 << 20)/3) | (3 << 27)
#define noteFsharp1 	((25 << 20)/18) | (18 << 27)
#define noteG1 			((3<< 20)/2) | (2 << 27)
#define noteGsharp1 	((8<< 20)/5) | (5 << 27)
#define noteA2 			((5 << 20)/3) | (3 << 27)
#define noteAsharp2 	((9 << 20)/5) | (5 << 27)
#define noteB2 			((15 << 20)/8) | (8 << 27)
#define noteC2 			((2 << 20)/1) | (1 << 27)
#define noteCsharp2 	((32 << 20)/15) | (15 << 27)
#define noteD2 			((18 << 20)/8) | (4 << 27)
#define noteDsharp2 	((12 << 20)/5) | (1 << 27)
#define noteE2 			((10 << 20)/4) | (2 << 27)
#define noteF2 			((8 << 20)/3) | (1 << 27)
#define noteFsharp2 	((50 << 20)/18) | (9 << 27)
#define noteG2 			((6<< 20)/2) | (1 << 27)
#define noteGsharp2 	((16<< 20)/5) | (5 << 27)
#define noteA3 			((10 << 20)/3) | (3 << 27)
#define noteAsharp3 	((18 << 20)/5) | (5 << 27)
#define noteB3 			((30 << 20)/8) | (4 << 27)
#define noteC3 			((4 << 20)/1) | (1 << 27)
#define noteCsharp3 	((64 << 20)/15) | (15 << 27)
#define noteD3 			((36 << 20)/8) | (2 << 27)
#define noteDsharp3 	((24 << 20)/5) | (5 << 27)
#define noteE3 			((20 << 20)/4) | (1 << 27)
#define noteF3 			((16 << 20)/3) | (3 << 27)
#define noteFsharp3 	((100 << 20)/18) | (9 << 27)
#define noteG3 			((12<< 20)/2) | (1 << 27)
#define noteGsharp3 	((32<< 20)/5) | (5 << 27)
#define noteA4 			((20 << 20)/3) | (3 << 27)
#define noteAsharp4 	((36 << 20)/5) | (5 << 27)
#define noteB4 			((60 << 20)/8) | (2 << 27)
#define noteC4 			((8 << 20)/1) | (1 << 27)



#define rhythm_16clock_1_16			((1 << 20)/1) | (1 << 27)
#define rhythm_16clock_1_8			((1 << 20)/2) | (1 << 27)
#define rhythm_16clock_3_16			((1 << 20)/3) | (3 << 27)
#define rhythm_16clock_1_4			((1 << 20)/4) | (1 << 27)
#define rhythm_16clock_5_16			((1 << 20)/5) | (5 << 27)
#define rhythm_16clock_3_8			((1 << 20)/6) | (3 << 27)
#define rhythm_16clock_7_16			((1 << 20)/7) | (7 << 27)
#define rhythm_16clock_1_2			((1 << 20)/8) | (1 << 27)
#define rhythm_16clock_9_16			((1 << 20)/9) | (9 << 27)
#define rhythm_16clock_5_8			((1 << 20)/10) | (5 << 27)
#define rhythm_16clock_11_16		((1 << 20)/11) | (11 << 27)
#define rhythm_16clock_3_4			((1 << 20)/12) | (3 << 27)
#define rhythm_16clock_13_16		((1 << 20)/13) | (13 << 27)
#define rhythm_16clock_7_8			((1 << 20)/14) | (7 << 27)
#define rhythm_16clock_15_16		((1 << 20)/15) | (15 << 27)

#define rhythm_16clock_1_12			((3 << 20)/4) | (1 << 27)
#define rhythm_16clock_1_6			((3 << 20)/8) | (1 << 27)
#define rhythm_16clock_5_12			((3 << 20)/20) | (3 << 27)
#define rhythm_16clock_7_12			((3 << 20)/28) | (1 << 27)
#define rhythm_16clock_2_3			((3 << 20)/32) | (5 << 27)
#define rhythm_16clock_5_6			((3 << 20)/40) | (5 << 27)
#define rhythm_16clock_11_12		((3 << 20)/44) | (11 << 27)

*/

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

 #define diatonicMinor7thsRow1 {noteC1, noteD1, noteDsharp1, noteF1 , noteG1 , noteGsharp1, noteAsharp2, noteC2}
 #define diatonicMinor7thsRow2 {noteC1, noteDsharp1, noteG1, noteAsharp2 , noteC2, noteDsharp2, noteG2, noteAsharp3 }
 #define diatonicMinor7thsRow3 {noteD1, noteF1, noteA2, noteC2 , noteD2, noteF2, noteA3, noteC3}
 #define diatonicMinor7thsRow4 {noteDsharp1, noteG1, noteAsharp2, noteD2, noteDsharp2 , noteG2, noteAsharp3, noteD3}
 #define diatonicMinor7thsRow5 {noteF1, noteGsharp1, noteC2, noteDsharp2, noteF2 , noteGsharp2, noteC3, noteDsharp3}
 #define diatonicMinor7thsRow6 {noteG1, noteAsharp2, noteD2, noteF2 , noteG2, noteAsharp3, noteD3, noteF3}
 #define diatonicMinor7thsRow7 {noteGsharp1, noteC2, noteDsharp2, noteG2 , noteGsharp2, noteC3, noteDsharp3, noteG3 }
 #define diatonicMinor7thsRow8 {noteAsharp2, noteD2, noteF2, noteA3 , noteAsharp3, noteD3, noteF3, noteA4 }

 #define diatonicMajor7thsRow1 {noteC1, noteD1, noteE1, noteF1 , noteG1 , noteA2, noteB2, noteC2}
 #define diatonicMajor7thsRow2 {noteC1, noteE1, noteG1, noteB2 , noteC2, noteE2, noteG2, noteB3 }
 #define diatonicMajor7thsRow3 {noteD1, noteF1, noteA2, noteC2 , noteD2, noteF2, noteA3, noteC3}
 #define diatonicMajor7thsRow4 {noteE1, noteG1, noteB2, noteD2, noteE2 , noteG2, noteB3, noteD3}
 #define diatonicMajor7thsRow5 {noteF1, noteA2, noteC2, noteE2, noteF2 , noteA3, noteC3, noteE3}
 #define diatonicMajor7thsRow6 {noteG1, noteB2, noteD2, noteF2 , noteG2, noteB3, noteD3, noteF3}
 #define diatonicMajor7thsRow7 {noteA2, noteC2, noteE2, noteG2 , noteA3, noteC3, noteE3, noteG3 }
 #define diatonicMajor7thsRow8 {noteB2, noteD2, noteF2, noteA3 , noteB3, noteD3, noteF3, noteA4 }

 #define rhythmsRow1 {rhythm_16clock_1_16, rhythm_16clock_1_8, rhythm_16clock_3_16, rhythm_16clock_1_4, rhythm_16clock_5_16, rhythm_16clock_3_8, rhythm_16clock_7_16, rhythm_16clock_1_2}
 #define rhythmsRow2 {rhythm_16clock_1_12, rhythm_16clock_1_16, rhythm_16clock_1_6, rhythm_16clock_1_8, rhythm_16clock_3_16, rhythm_16clock_1_6, rhythm_16clock_1_4, rhythm_16clock_1_2}
 #define rhythmsRow3 {rhythm_8clock_1_16, rhythm_8clock_1_8, rhythm_8clock_3_16, rhythm_8clock_1_4, rhythm_8clock_5_16, rhythm_8clock_3_8, rhythm_8clock_7_16, rhythm_8clock_1_2}
 #define rhythmsRow4 {rhythm_8clock_1_12, rhythm_8clock_1_16, rhythm_8clock_1_6, rhythm_8clock_1_8, rhythm_8clock_3_16, rhythm_8clock_1_6, rhythm_8clock_1_4, rhythm_8clock_1_6}
 #define rhythmsRow5 {rhythm_4clock_1_16, rhythm_4clock_1_8, rhythm_4clock_3_16, rhythm_4clock_1_4, rhythm_4clock_5_16, rhythm_4clock_3_8, rhythm_4clock_7_16, rhythm_4clock_1_2}
 #define rhythmsRow6 {rhythm_4clock_1_12, rhythm_4clock_1_16, rhythm_4clock_1_6, rhythm_4clock_1_8, rhythm_4clock_3_16, rhythm_4clock_1_6, rhythm_4clock_1_4, rhythm_4clock_1_6}
 #define rhythmsRow7 {rhythm_2clock_1_16, rhythm_2clock_1_8, rhythm_2clock_3_16, rhythm_2clock_1_4, rhythm_2clock_5_16, rhythm_2clock_3_8, rhythm_2clock_7_16, rhythm_2clock_1_2}
 #define rhythmsRow8 {rhythm_2clock_1_12, rhythm_2clock_1_16, rhythm_2clock_1_6, rhythm_2clock_1_8, rhythm_2clock_3_16, rhythm_2clock_1_6, rhythm_2clock_1_4, rhythm_2clock_1_6}

static const uint32_t diatonicMinor7ths[8][8] = {diatonicMinor7thsRow1, diatonicMinor7thsRow2,diatonicMinor7thsRow3,diatonicMinor7thsRow4,diatonicMinor7thsRow5,diatonicMinor7thsRow6,diatonicMinor7thsRow7,diatonicMinor7thsRow8};

static const uint32_t diatonicMajor7ths[8][8] = {diatonicMajor7thsRow1, diatonicMajor7thsRow2,diatonicMajor7thsRow3,diatonicMajor7thsRow4,diatonicMajor7thsRow5,diatonicMajor7thsRow6,diatonicMajor7thsRow7,diatonicMajor7thsRow8};

static const uint32_t rhythms[8][8] = {rhythmsRow1, rhythmsRow2,rhythmsRow3,rhythmsRow4,rhythmsRow5,rhythmsRow6,rhythmsRow7,rhythmsRow8};

