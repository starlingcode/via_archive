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
const ScaleNote diatonicMinor7thsRow6[8] = {noteG1, noteAsharp2, noteD2, noteF2 , noteG2, noteAsharp3, noteD3, noteF_3};
const ScaleNote diatonicMinor7thsRow7[8] = {noteGsharp1, noteC2, noteDsharp2, noteG2 , noteGsharp2, noteC3, noteDsharp3, noteG3 };
const ScaleNote diatonicMinor7thsRow8[8] = {noteAsharp2, noteD2, noteF2, noteA3 , noteAsharp3, noteD3, noteF_3, noteA4 };

const ScaleNote diatonicMajor7thsRow1[8] = {noteC1, noteD1, noteE1, noteF1 , noteG1 , noteA2, noteB2, noteC2};
const ScaleNote diatonicMajor7thsRow2[8] = {noteC1, noteE1, noteG1, noteB2 , noteC2, noteE2, noteG2, noteB3 };
const ScaleNote diatonicMajor7thsRow3[8] = {noteD1, noteF1, noteA2, noteC2 , noteD2, noteF2, noteA3, noteC3};
const ScaleNote diatonicMajor7thsRow4[8] = {noteE1, noteG1, noteB2, noteD2, noteE2 , noteG2, noteB3, noteD3};
const ScaleNote diatonicMajor7thsRow5[8] = {noteF1, noteA2, noteC2, noteE2, noteF2 , noteA3, noteC3, noteE3};
const ScaleNote diatonicMajor7thsRow6[8] = {noteG1, noteB2, noteD2, noteF2 , noteG2, noteB3, noteD3, noteF_3};
const ScaleNote diatonicMajor7thsRow7[8] = {noteA2, noteC2, noteE2, noteG2 , noteA3, noteC3, noteE3, noteG3 };
const ScaleNote diatonicMajor7thsRow8[8] = {noteB2, noteD2, noteF2, noteA3 , noteB3, noteD3, noteF_3, noteA4 };

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

const ScaleNote pureRhythmsRow1[8] = {rhythm_pure1_16, rhythm_pure2_16, rhythm_pure3_16, rhythm_pure4_16, rhythm_pure5_16, rhythm_pure6_16, rhythm_pure7_16, rhythm_pure8_16};

const ScaleNote pureNotesRow1[8] = {note_pureA1, note_pureB1, note_pureC1, note_pureD1, note_pureE1, note_pureF1, note_pureG1, note_pureGsharp1};

const ScaleNote fullChromaticRow1[128] = {
		noteA_3, noteAsharp_3, noteB_3, noteC_3, noteCsharp_3, noteD_3, noteDsharp_3, noteE_3, noteF_3, noteFsharp_3, noteG_3, noteGsharp_3,
		noteA_2, noteAsharp_2, noteB_2, noteC_2, noteCsharp_2, noteD_2, noteDsharp_2, noteE_2, noteF_2, noteFsharp_2, noteG_2, noteGsharp_2,
		noteA_1, noteAsharp_1, noteB_1, noteC_1, noteCsharp_1, noteD_1, noteDsharp_1, noteE_1, noteF_1, noteFsharp_1, noteG_1, noteGsharp_1,
		noteA0, noteAsharp0, noteB0, noteC0, noteCsharp0, noteD0, noteDsharp0, noteE0, noteF0, noteFsharp0, noteG0, noteGsharp0,
		noteA1, noteAsharp1, noteB1, noteC1, noteCsharp1, noteD1, noteDsharp1, noteE1, noteF1, noteFsharp1, noteG1, noteGsharp1,
		noteA2, noteAsharp2, noteB2, noteC2, noteCsharp2, noteD2, noteDsharp2, noteE2, noteF2, noteFsharp2, noteG2, noteGsharp2,
		noteA3, noteAsharp3, noteB3, noteC3, noteCsharp3, noteD3, noteDsharp3, noteE3, noteF3, noteFsharp3, noteG3, noteGsharp3,
		noteA4, noteAsharp4, noteB4, noteC4, noteCsharp4, noteD4, noteDsharp4, noteE4, noteF4, noteFsharp4, noteG4, noteGsharp4,
		noteA5, noteAsharp5, noteB5, noteC5, noteCsharp5, noteD5, noteDsharp5, noteE5, noteF5, noteFsharp5, noteG5, noteGsharp5,
		noteA6, noteAsharp6, noteB6, noteC6, noteCsharp6, noteD6, noteDsharp6, noteE6, noteF6, noteFsharp6, noteG6, noteGsharp6,
		noteA7, noteAsharp7, noteB7, noteC7, noteCsharp7, noteD7, noteDsharp7, noteE7
};

const ScaleNote fullChromaticRow2[128] = {
		noteA_3, noteA_3, noteB_3, noteC_3, noteC_3, noteD_3, noteD_3, noteE_3, noteF_3, noteF_3, noteG_3, noteG_3,
		noteA_2, noteA_2, noteB_2, noteC_2, noteC_2, noteD_2, noteD_2, noteE_2, noteF_2, noteF_2, noteG_2, noteG_2,
		noteA_1, noteA_1, noteB_1, noteC_1, noteC_1, noteD_1, noteD_1, noteE_1, noteF_1, noteF_1, noteG_1, noteG_1,
		noteA0, noteA0, noteB0, noteC0, noteC0, noteD0, noteD0, noteE0, noteF0, noteF0, noteG0, noteG0,
		noteA1, noteA1, noteB1, noteC1, noteC1, noteD1, noteD1, noteE1, noteF1, noteF1, noteG1, noteG1,
		noteA2, noteA2, noteB2, noteC2, noteC2, noteD2, noteD2, noteE2, noteF2, noteF2, noteG2, noteG2,
		noteA3, noteA3, noteB3, noteC3, noteC3, noteD3, noteD3, noteE3, noteF3, noteF3, noteG3, noteG3,
		noteA4, noteA4, noteB4, noteC4, noteC4, noteD4, noteD4, noteE4, noteF4, noteF4, noteG4, noteG4,
		noteA5, noteA5, noteB5, noteC5, noteC5, noteD5, noteD5, noteE5, noteF5, noteF5, noteG5, noteG5,
		noteA6, noteA6, noteB6, noteC6, noteC6, noteD6, noteD6, noteE6, noteF6, noteF6, noteG6, noteG6,
		noteA7, noteA7, noteB7, noteC7, noteC7, noteD7, noteD7, noteE7
};

const ScaleNote fullChromaticRow3[128] = {
		noteA_3, noteA_3, noteC_3, noteC_3, noteD_3, noteD_3, noteE_3, noteE_3, noteE_3, noteG_3, noteG_3, noteG_3,
		noteA_2, noteA_2, noteC_2, noteC_2, noteD_2, noteD_2, noteE_2, noteE_2, noteE_2, noteG_2, noteG_2, noteG_2,
		noteA_1, noteA_1, noteC_1, noteC_1, noteD_1, noteD_1, noteE_1, noteE_1, noteE_1, noteG_1, noteG_1, noteG_1,
		noteA0, noteA0, noteC0, noteC0, noteD0, noteD0, noteE0, noteE0, noteE0, noteG0, noteG0, noteG0,
		noteA1, noteA1, noteC1, noteC1, noteD1, noteD1, noteE1, noteE1, noteE1, noteG1, noteG1, noteG1,
		noteA2, noteA2, noteC2, noteC2, noteD2, noteD2, noteE2, noteE2, noteE2, noteG2, noteG2, noteG2,
		noteA3, noteA3, noteC3, noteC3, noteD3, noteD3, noteE3, noteE3, noteE3, noteG3, noteG3, noteG3,
		noteA4, noteA4, noteC4, noteC4, noteD4, noteD4, noteE4, noteE4, noteE4, noteG4, noteG4, noteG4,
		noteA5, noteA5, noteC5, noteC5, noteD5, noteD5, noteE5, noteE5, noteE5, noteG5, noteG5, noteG5,
		noteA6, noteA6, noteC6, noteC6, noteD6, noteD6, noteE6, noteE6, noteE6, noteG6, noteG6, noteG6,
		noteA7, noteA7, noteC7, noteC7, noteD7, noteD7, noteE7, noteE7
};

const ScaleNote fullChromaticRow4[128] = {
		noteA_3, noteA_3, noteB_3, noteC_3, noteC_3, noteD_3, noteD_3, noteD_3, noteF_3, noteF_3, noteF_3, noteA_2,
		noteA_2, noteA_2, noteB_2, noteC_2, noteC_2, noteD_2, noteD_2, noteD_2, noteF_2, noteF_2, noteF_2, noteA_1,
		noteA_1, noteA_1, noteB_1, noteC_1, noteC_1, noteD_1, noteD_1, noteD_1, noteF_1, noteF_1, noteF_1, noteA0,
		noteA0, noteA0, noteB0, noteC0, noteC0, noteD0, noteD0, noteD0, noteF0, noteF0, noteF0, noteA1,
		noteA1, noteA1, noteB1, noteC1, noteC1, noteD1, noteD1, noteD1, noteF1, noteF1, noteF1, noteA2,
		noteA2, noteA2, noteB2, noteC2, noteC2, noteD2, noteD2, noteD2, noteF2, noteF2, noteF2, noteA3,
		noteA3, noteA3, noteB3, noteC3, noteC3, noteD3, noteD3, noteD3, noteF3, noteF3, noteF3, noteA4,
		noteA4, noteA4, noteB4, noteC4, noteC4, noteD4, noteD4, noteD4, noteF4, noteF4, noteF4, noteA5,
		noteA5, noteA5, noteB5, noteC5, noteC5, noteD5, noteD5, noteD5, noteF5, noteF5, noteF5, noteA6,
		noteA6, noteA6, noteB6, noteC6, noteC6, noteD6, noteD6, noteD6, noteF6, noteF6, noteF6, noteA7,
		noteA7, noteA7, noteB7, noteC7, noteC7, noteD7, noteD7, noteD7


};

const ScaleNote fullChromaticRow5[128] = {
		noteA_3, noteA_3, noteB_3, noteC_3, noteC_3, noteD_3, noteD_3, noteE_3, noteE_3, noteE_3, noteGsharp_3, noteGsharp_3,
		noteGsharp_3, noteGsharp_3, noteB_2, noteC_2, noteC_2, noteD_2, noteD_2, noteE_2, noteE_2, noteE_2, noteGsharp_2, noteGsharp_2,
		noteGsharp_2, noteGsharp_2, noteB_1, noteC_1, noteC_1, noteD_1, noteD_1, noteE_1, noteE_1, noteE_1, noteGsharp_1, noteGsharp_1,
		noteGsharp_1, noteGsharp_1, noteB0, noteC0, noteC0, noteD0, noteD0, noteE0, noteE0, noteE0, noteGsharp0, noteGsharp0,
		noteGsharp0, noteGsharp0, noteB1, noteC1, noteC1, noteD1, noteD1, noteE1, noteE1, noteE1, noteGsharp1, noteGsharp1,
		noteGsharp1, noteGsharp1, noteB2, noteC2, noteC2, noteD2, noteD2, noteE2, noteE2, noteE2, noteGsharp2, noteGsharp2,
		noteGsharp2, noteGsharp2, noteB3, noteC3, noteC3, noteD3, noteD3, noteE3, noteE3, noteE3, noteGsharp3, noteGsharp3,
		noteGsharp3, noteGsharp3, noteB4, noteC4, noteC4, noteD4, noteD4, noteE4, noteE4, noteE4, noteGsharp4, noteGsharp4,
		noteGsharp4, noteGsharp4, noteB5, noteC5, noteC5, noteD5, noteD5, noteE5, noteE5, noteE5, noteGsharp5, noteGsharp5,
		noteGsharp5, noteGsharp5, noteB6, noteC6, noteC6, noteD6, noteD6, noteE6, noteE6, noteE6, noteGsharp6, noteGsharp6,
		noteGsharp6, noteGsharp6, noteB7, noteC7, noteC7, noteD7, noteD7, noteE7
};

const ScaleNote fullChromaticRow6[128] = {
		noteA_3, noteA_3, noteA_3, noteC_3, noteC_3, noteC_3, noteE_3, noteE_3, noteE_3, noteF_3, noteF_3, noteF_3,
		noteA_2, noteA_2, noteA_2, noteC_2, noteC_2, noteC_2, noteE_2, noteE_2, noteE_2, noteF_2, noteF_2, noteF_2,
		noteA_1, noteA_1, noteA_1, noteC_1, noteC_1, noteC_1, noteE_1, noteE_1, noteE_1, noteF_1, noteF_1, noteF_1,
		noteA0, noteA0, noteA0, noteC0, noteC0, noteC0, noteE0, noteE0, noteE0, noteF0, noteF0, noteF0,
		noteA1, noteA1, noteA1, noteC1, noteC1, noteC1, noteE1, noteE1, noteE1, noteF1, noteF1, noteF1,
		noteA2, noteA2, noteA2, noteC2, noteC2, noteC2, noteE2, noteE2, noteE2, noteF2, noteF2, noteF2,
		noteA3, noteA3, noteA3, noteC3, noteC3, noteC3, noteE3, noteE3, noteE3, noteF3, noteF3, noteF3,
		noteA4, noteA4, noteA4, noteC4, noteC4, noteC4, noteE4, noteE4, noteE4, noteF4, noteF4, noteF4,
		noteA5, noteA5, noteA5, noteC5, noteC5, noteC5, noteE5, noteE5, noteE5, noteF5, noteF5, noteF5,
		noteA6, noteA6, noteA6, noteC6, noteC6, noteC6, noteE6, noteE6, noteE6, noteF6, noteF6, noteF6,
		noteA7, noteA7, noteA7, noteC7, noteC7, noteC7, noteE7, noteE7
};

const ScaleNote fullChromaticRow7[128] = {
		noteB_3, noteB_3, noteB_3, noteB_3, noteD_3, noteD_3, noteE_3, noteE_3, noteE_3, noteG_3, noteG_3, noteG_3,
		noteB_2, noteB_2, noteB_2, noteB_2, noteD_2, noteD_2, noteE_2, noteE_2, noteE_2, noteG_2, noteG_2, noteG_2,
		noteB_1, noteB_1, noteB_1, noteB_1, noteD_1, noteD_1, noteE_1, noteE_1, noteE_1, noteG_1, noteG_1, noteG_1,
		noteB0, noteB0, noteB0, noteB0, noteD0, noteD0, noteE0, noteE0, noteE0, noteG0, noteG0, noteG0,
		noteB1, noteB1, noteB1, noteB1, noteD1, noteD1, noteE1, noteE1, noteE1, noteG1, noteG1, noteG1,
		noteB2, noteB2, noteB2, noteB2, noteD2, noteD2, noteE2, noteE2, noteE2, noteG2, noteG2, noteG2,
		noteB3, noteB3, noteB3, noteB3, noteD3, noteD3, noteE3, noteE3, noteE3, noteG3, noteG3, noteG3,
		noteB4, noteB4, noteB4, noteB4, noteD4, noteD4, noteE4, noteE4, noteE4, noteG4, noteG4, noteG4,
		noteB5, noteB5, noteB5, noteB5, noteD5, noteD5, noteE5, noteE5, noteE5, noteG5, noteG5, noteG5,
		noteB6, noteB6, noteB6, noteB6, noteD6, noteD6, noteE6, noteE6, noteE6, noteG6, noteG6, noteG6,
		noteB7, noteB7, noteB7, noteB7, noteD7, noteD7, noteE7, noteE7,
};

const ScaleNote fullChromaticRow8[128] = {
		noteB_3, noteB_3, noteB_3, noteB_3, noteD_3, noteD_3, noteE_3, noteE_3, noteE_3, noteF_3, noteF_3, noteG_3,
		noteB_2, noteB_2, noteB_2, noteB_2, noteD_2, noteD_2, noteE_2, noteE_2, noteE_2, noteF_2, noteF_2, noteG_2,
		noteB_1, noteB_1, noteB_1, noteB_1, noteD_1, noteD_1, noteE_1, noteE_1, noteE_1, noteF_1, noteF_1, noteG_1,
		noteB0, noteB0, noteB0, noteB0, noteD0, noteD0, noteE0, noteE0, noteE0, noteF0, noteF0, noteG0,
		noteB1, noteB1, noteB1, noteB1, noteD1, noteD1, noteE1, noteE1, noteE1, noteF1, noteF1, noteG1,
		noteB2, noteB2, noteB2, noteB2, noteD2, noteD2, noteE2, noteE2, noteE2, noteF2, noteF2, noteG2,
		noteB3, noteB3, noteB3, noteB3, noteD3, noteD3, noteE3, noteE3, noteE3, noteF3, noteF3, noteG3,
		noteB4, noteB4, noteB4, noteB4, noteD4, noteD4, noteE4, noteE4, noteE4, noteF4, noteF4, noteG4,
		noteB5, noteB5, noteB5, noteB5, noteD5, noteD5, noteE5, noteE5, noteE5, noteF5, noteF5, noteG5,
		noteB6, noteB6, noteB6, noteB6, noteD6, noteD6, noteE6, noteE6, noteE6, noteF6, noteF6, noteG6,
		noteB7, noteB7, noteB7, noteB7, noteD7, noteD7, noteE7, noteE7,
};

const ScaleNote fullChromaticRow9[128] = {
		noteAsharp_3, noteAsharp_3, noteB_3, noteB_3, noteB_3, noteDsharp_3, noteDsharp_3, noteDsharp_3, noteDsharp_3, noteFsharp_3, noteFsharp_3, noteG_3,
		noteAsharp_2, noteAsharp_2, noteB_2, noteB_2, noteB_2, noteDsharp_2, noteDsharp_2, noteDsharp_2, noteDsharp_2, noteFsharp_2, noteFsharp_2, noteG_2,
		noteAsharp_1, noteAsharp_1, noteB_1, noteB_1, noteB_1, noteDsharp_1, noteDsharp_1, noteDsharp_1, noteDsharp_1, noteFsharp_1, noteFsharp_1, noteG_1,
		noteAsharp0, noteAsharp0, noteB0, noteB0, noteB0, noteDsharp0, noteDsharp0, noteDsharp0, noteDsharp0, noteFsharp0, noteFsharp0, noteG0,
		noteAsharp1, noteAsharp1, noteB1, noteB1, noteB1, noteDsharp1, noteDsharp1, noteDsharp1, noteDsharp1, noteFsharp1, noteFsharp1, noteG1,
		noteAsharp2, noteAsharp2, noteB2, noteB2, noteB2, noteDsharp2, noteDsharp2, noteDsharp2, noteDsharp2, noteFsharp2, noteFsharp2, noteG2,
		noteAsharp3, noteAsharp3, noteB3, noteB3, noteB3, noteDsharp3, noteDsharp3, noteDsharp3, noteDsharp3, noteFsharp3, noteFsharp3, noteG3,
		noteAsharp4, noteAsharp4, noteB4, noteB4, noteB4, noteDsharp4, noteDsharp4, noteDsharp4, noteDsharp4, noteFsharp4, noteFsharp4, noteG4,
		noteAsharp5, noteAsharp5, noteB5, noteB5, noteB5, noteDsharp5, noteDsharp5, noteDsharp5, noteDsharp5, noteFsharp5, noteFsharp5, noteG5,
		noteAsharp6, noteAsharp6, noteB6, noteB6, noteB6, noteDsharp6, noteDsharp6, noteDsharp6, noteDsharp6, noteFsharp6, noteFsharp6, noteG6,
		noteAsharp7, noteAsharp7, noteB7, noteB7, noteB7, noteDsharp7, noteDsharp7, noteDsharp7
};

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

ScaleNote *fullChromatic[8] = {
		fullChromaticRow2, fullChromaticRow3, fullChromaticRow4,
		fullChromaticRow5, fullChromaticRow6, fullChromaticRow7,
		fullChromaticRow8, fullChromaticRow9 };

ScaleNote *pureRhythms[8] = {
		pureRhythmsRow1, pureRhythmsRow1, pureRhythmsRow1,
		pureRhythmsRow1, pureRhythmsRow1, pureRhythmsRow1,
		pureRhythmsRow1, pureRhythmsRow1 };

ScaleNote *pureNotes[8] = {
		pureNotesRow1, pureNotesRow1, pureNotesRow1,
		pureNotesRow1, pureNotesRow1, pureNotesRow1,
		pureNotesRow1, pureNotesRow1 };


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

