#include "scales.h"

#include "main.h"

#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"

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



 #define rhythm16clock_1_16			((1 << 20)/1) | (1 << 27)
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

const ScaleNote diatonicMinor7thsRow1[8] = {noteC1, noteD1, noteDsharp1, noteF1 , noteG1 , noteGsharp1, noteAsharp2, noteC2};
const ScaleNote diatonicMinor7thsRow2[8] = {noteC1, noteDsharp1, noteG1, noteAsharp2 , noteC2, noteDsharp2, noteG2, noteAsharp3 };
const ScaleNote diatonicMinor7thsRow3[8] = {noteD1, noteF1, noteA2, noteC2 , noteD2, noteF2, noteA3, noteC3};
const ScaleNote diatonicMinor7thsRow4[8] = {noteDsharp1, noteG1, noteAsharp2, noteD2, noteDsharp2 , noteG2, noteAsharp3, noteD3};
const ScaleNote diatonicMinor7thsRow5[8] = {noteF1, noteGsharp1, noteC2, noteDsharp2, noteF2 , noteGsharp2, noteC3, noteDsharp3};
const ScaleNote diatonicMinor7thsRow6[8] = {noteG1, noteAsharp2, noteD2, noteF2 , noteG2, noteAsharp3, noteD3, noteF3};
const ScaleNote diatonicMinor7thsRow7[8] = {noteGsharp1, noteC2, noteDsharp2, noteG2 , noteGsharp2, noteC3, noteDsharp3, noteG3 };
const ScaleNote diatonicMinor7thsRow8[8] = {noteAsharp2, noteD2, noteF2, noteA3 , noteAsharp3, noteD3, noteF3, noteA4 };

const ScaleNote diatonicMajor7thsRow1[8] = {noteC1, noteD1, noteE1, noteF1 , noteG1 , noteA2, noteB2, noteC2};
const ScaleNote diatonicMajor7thsRow2[8] = {noteC1, noteE1, noteG1, noteB2 , noteC2, noteE2, noteG2, noteB3 };
const ScaleNote diatonicMajor7thsRow3[8] = {noteD1, noteF1, noteA2, noteC2 , noteD2, noteF2, noteA3, noteC3};
const ScaleNote diatonicMajor7thsRow4[8] = {noteE1, noteG1, noteB2, noteD2, noteE2 , noteG2, noteB3, noteD3};
const ScaleNote diatonicMajor7thsRow5[8] = {noteF1, noteA2, noteC2, noteE2, noteF2 , noteA3, noteC3, noteE3};
const ScaleNote diatonicMajor7thsRow6[8] = {noteG1, noteB2, noteD2, noteF2 , noteG2, noteB3, noteD3, noteF3};
const ScaleNote diatonicMajor7thsRow7[8] = {noteA2, noteC2, noteE2, noteG2 , noteA3, noteC3, noteE3, noteG3 };
const ScaleNote diatonicMajor7thsRow8[8] = {noteB2, noteD2, noteF2, noteA3 , noteB3, noteD3, noteF3, noteA4 };

const ScaleNote rhythms1Row1[8] = {rhythm16clock_1_32_no_reset, rhythm16clock_1_24_no_reset, rhythm16clock_1_16_no_reset, rhythm16clock_1_8_no_reset, rhythm16clock_1_6_no_reset, rhythm16clock_3_16_no_reset, rhythm16clock_1_4_no_reset, rhythm16clock_5_16_no_reset};
const ScaleNote rhythms1Row2[8] = {rhythm16clock_1_8_no_reset, rhythm16clock_1_6_no_reset, rhythm16clock_3_16_no_reset, rhythm16clock_1_4_no_reset, rhythm16clock_5_16_no_reset, rhythm16clock_1_3_no_reset, rhythm16clock_3_8_no_reset, rhythm16clock_7_16_no_reset};
const ScaleNote rhythms1Row3[8] = {rhythm16clock_1_32_8_reset, rhythm16clock_1_24_8_reset, rhythm16clock_1_16_8_reset, rhythm16clock_1_8_8_reset, rhythm16clock_1_6_8_reset, rhythm16clock_3_16_8_reset, rhythm16clock_1_4_8_reset, rhythm16clock_5_16_8_reset};
const ScaleNote rhythms1Row4[8] = {rhythm16clock_1_8_8_reset, rhythm16clock_1_6_8_reset, rhythm16clock_3_16_8_reset, rhythm16clock_1_4_8_reset, rhythm16clock_5_16_8_reset, rhythm16clock_1_3_8_reset, rhythm16clock_3_8_8_reset, rhythm16clock_7_16_8_reset};
const ScaleNote rhythms1Row5[8] = {rhythm16clock_1_32_16_reset, rhythm16clock_1_24_16_reset, rhythm16clock_1_16_16_reset, rhythm16clock_1_8_16_reset, rhythm16clock_1_6_16_reset, rhythm16clock_3_16_16_reset, rhythm16clock_1_4_16_reset, rhythm16clock_5_16_16_reset};
const ScaleNote rhythms1Row6[8] = {rhythm16clock_1_8_16_reset, rhythm16clock_1_6_16_reset, rhythm16clock_3_16_16_reset, rhythm16clock_1_4_16_reset, rhythm16clock_5_16_16_reset, rhythm16clock_1_3_16_reset, rhythm16clock_3_8_16_reset, rhythm16clock_7_16_16_reset};
const ScaleNote rhythms1Row7[8] = {rhythm16clock_1_2_no_reset, rhythm16clock_9_16_no_reset, rhythm16clock_5_8_no_reset, rhythm16clock_11_16_no_reset, rhythm16clock_3_4_no_reset, rhythm16clock_13_16_no_reset, rhythm16clock_7_8_no_reset, rhythm16clock_15_16_no_reset};
const ScaleNote rhythms1Row8[8] = {rhythm16clock_1_2_16_reset, rhythm16clock_9_16_16_reset, rhythm16clock_5_8_16_reset, rhythm16clock_11_16_16_reset, rhythm16clock_3_4_16_reset, rhythm16clock_13_16_16_reset, rhythm16clock_7_8_16_reset, rhythm16clock_15_16_16_reset};

const ScaleNote rhythms2Row1[8] = {rhythm4clock_1_32_no_reset, rhythm4clock_1_24_no_reset, rhythm4clock_1_16_no_reset, rhythm4clock_1_8_no_reset, rhythm4clock_1_6_no_reset, rhythm4clock_3_16_no_reset, rhythm4clock_1_4_no_reset, rhythm4clock_5_16_no_reset};
const ScaleNote rhythms2Row2[8] = {rhythm4clock_1_8_no_reset, rhythm4clock_1_6_no_reset, rhythm4clock_3_16_no_reset, rhythm4clock_1_4_no_reset, rhythm4clock_5_16_no_reset, rhythm4clock_1_3_no_reset, rhythm4clock_3_8_no_reset, rhythm4clock_7_16_no_reset};
const ScaleNote rhythms2Row3[8] = {rhythm4clock_1_32_8_reset, rhythm4clock_1_24_8_reset, rhythm4clock_1_16_8_reset, rhythm4clock_1_8_8_reset, rhythm4clock_1_6_8_reset, rhythm4clock_3_16_8_reset, rhythm4clock_1_4_8_reset, rhythm4clock_5_16_8_reset};
const ScaleNote rhythms2Row4[8] = {rhythm4clock_1_8_8_reset, rhythm4clock_1_6_8_reset, rhythm4clock_3_16_8_reset, rhythm4clock_1_4_8_reset, rhythm4clock_5_16_8_reset, rhythm4clock_1_3_8_reset, rhythm4clock_3_8_8_reset, rhythm4clock_7_16_8_reset};
const ScaleNote rhythms2Row5[8] = {rhythm16clock_1_32_no_reset, rhythm16clock_1_24_no_reset, rhythm16clock_1_16_no_reset, rhythm16clock_1_8_no_reset, rhythm16clock_1_6_no_reset, rhythm16clock_3_16_no_reset, rhythm16clock_1_4_no_reset, rhythm16clock_5_16_no_reset};
const ScaleNote rhythms2Row6[8] = {rhythm16clock_1_8_no_reset, rhythm16clock_1_6_no_reset, rhythm16clock_3_16_no_reset, rhythm16clock_1_4_no_reset, rhythm16clock_5_16_no_reset, rhythm16clock_1_3_no_reset, rhythm16clock_3_8_no_reset, rhythm16clock_7_16_no_reset};
const ScaleNote rhythms2Row7[8] = {rhythm16clock_1_32_8_reset, rhythm16clock_1_24_8_reset, rhythm16clock_1_16_8_reset, rhythm16clock_1_8_8_reset, rhythm16clock_1_6_8_reset, rhythm16clock_3_16_8_reset, rhythm16clock_1_4_8_reset, rhythm16clock_5_16_8_reset};
const ScaleNote rhythms2Row8[8] = {rhythm16clock_1_8_8_reset, rhythm16clock_1_6_8_reset, rhythm16clock_3_16_8_reset, rhythm16clock_1_4_8_reset, rhythm16clock_5_16_8_reset, rhythm16clock_1_3_8_reset, rhythm16clock_3_8_8_reset, rhythm16clock_7_16_8_reset};


ScaleNote *diatonicMinor7ths[8] = { diatonicMinor7thsRow1,
		diatonicMinor7thsRow2, diatonicMinor7thsRow3, diatonicMinor7thsRow4,
		diatonicMinor7thsRow5, diatonicMinor7thsRow6, diatonicMinor7thsRow7,
		diatonicMinor7thsRow8 };

ScaleNote *diatonicMajor7ths[8] = { diatonicMajor7thsRow1,
		diatonicMajor7thsRow2, diatonicMajor7thsRow3, diatonicMajor7thsRow4,
		diatonicMajor7thsRow5, diatonicMajor7thsRow6, diatonicMajor7thsRow7,
		diatonicMajor7thsRow8 };


ScaleNote *rhythms1[8] = { rhythms1Row1,
		rhythms1Row2, rhythms1Row3, rhythms1Row4,
		rhythms1Row5, rhythms1Row6, rhythms1Row7,
		rhythms1Row8 };


ScaleNote *rhythms2[8] = { rhythms2Row1,
		rhythms2Row2, rhythms2Row3, rhythms2Row4,
		rhythms2Row5, rhythms2Row6, rhythms2Row7,
		rhythms2Row8 };


//static const uint32_t rhythms[8][8] = {rhythmsRow1, rhythmsRow2,rhythmsRow3,rhythmsRow4,rhythmsRow5,rhythmsRow6,rhythmsRow7,rhythmsRow8};;

void switchScale(uint32_t scaleIndex) {
	ScaleNote evaluationHolder;

	switch (scaleIndex) {
	case 0:
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				// this just gets the appropriate samples and plops them into the global holding arrays
				evaluationHolder = diatonicMinor7ths[i][j];
				scale[i][j] = evaluationHolder;
			}
		}
		break;

	case 1:
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				// this just gets the appropriate samples and plops them into the global holding arrays
				evaluationHolder = diatonicMinor7ths[i][j];
				scale[i][j] = evaluationHolder;
			}
		}
		break;
	case 2:
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				// this just gets the appropriate samples and plops them into the global holding arrays
				evaluationHolder = diatonicMajor7ths[i][j];
				scale[i][j] = evaluationHolder;
			}
		}
		break;

	}
}

