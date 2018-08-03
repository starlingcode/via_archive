/*
 * scanner_modes.h
 *
 *  Created on: Aug 2, 2018
 *      Author: willmitchell
 */

#ifndef SCANNER_MODES_H_
#define SCANNER_MODES_H_


// Mode enums and mode variables

#define X_TABLE button1Mode
#define Y_TABLE button2Mode
#define SYNC_MODE button4Mode
#define TERRAIN_MODE button6Mode

#define AUX4_MODE_USED

#define numButton1Modes 8
#define numButton2Modes 8
#define numButton3Modes 8
#define numButton4Modes 2
#define numButton5Modes 8
#define numButton6Modes 4
#define numAux1Modes 0
#define numAux2Modes 0
#define numAux3Modes
#define numAux4Modes 2

enum button1Modes {xTables};
enum button2Modes {yTables};
enum button3Modes {pairedWithButton1};
enum button4Modes {hardsync, reverse};
enum button5Modes {pairedWithButton2};
enum button6Modes {sum, subtract, product, PM};
enum aux1Modes {aux1NotUsed};
enum aux2Modes {aux2NotUsed};
enum aux3Modes {aux3NotUsed};
enum aux4Modes {aux4NotUsed};

#endif /* SCANNER_MODES_H_ */
