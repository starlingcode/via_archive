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
#define TRIG_MODE button4Mode
#define FREQ_MODE button3Mode
#define LOOP_MODE button6Mode
#define LOGIC_A_MODE aux2Mode
#define DRUM_MODE aux3Mode
#define DAC_3_MODE aux4Mode



#define numButton1Modes 6
#define numButton2Modes 8
#define numButton3Modes 3
#define numButton4Modes 5
#define numButton5Modes 8
#define numButton6Modes 2
#define numAux1Modes 0
#define numAux2Modes 2
#define numAux3Modes 6
#define numAux4Modes 2

enum button1Modes {nosampleandhold, a, b, ab, halfdecimate, decimate};
enum button2Modes {tables};
enum button3Modes {audio, env, seq};
enum button4Modes {noretrigger, hardsync, nongatedretrigger, gated, pendulum};
enum button5Modes {pairedWithButton2};
enum button6Modes {noloop, looping};
enum aux1Modes {aux1NotUsed};
enum aux2Modes {attackGate, releaseGate};
enum aux3Modes {pitchMorphAmp, morphAmp, amp, morph, pitch, pitchMorph};
enum aux4Modes {phasor, contour};

#endif /* SCANNER_MODES_H_ */
