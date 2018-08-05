/*
 * scanner_modes.h
 *
 *  Created on: Aug 2, 2018
 *      Author: willmitchell
 */

#ifndef SCANNER_MODES_H_
#define SCANNER_MODES_H_


// Mode enums and mode variables

#define SH_MODE button1Mode
#define TABLE button2Mode
#define FM_PM_MODE button3Mode
#define SYNC_MODE button4Mode
#define MORPH_PWM_MODE button6Mode

#define AUX4_MODE_USED

#define numButton1Modes 2
#define numButton2Modes 8
#define numButton3Modes 2
#define numButton4Modes 2
#define numButton5Modes 8
#define numButton6Modes 2
#define numAux1Modes 0
#define numAux2Modes 0
#define numAux3Modes 0
#define numAux4Modes 0

enum button1Modes {none, decimate};
enum button2Modes {yTables};
enum button3Modes {FM, PM};
enum button4Modes {hard, pendulum};
enum button5Modes {pairedWithButton2};
enum button6Modes {morphCV, pwmCV};
enum aux1Modes {aux1NotUsed};
enum aux2Modes {aux2NotUsed};
enum aux3Modes {aux3NotUsed};
enum aux4Modes {aux4NotUsed};

#endif /* SCANNER_MODES_H_ */
