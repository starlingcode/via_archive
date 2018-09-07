/*
 * led_display.h
 *
 *  Created on: Jun 26, 2018
 *      Author: willmitchell
 */

#ifndef LED_DISPLAY_H_
#define LED_DISPLAY_H_

#include "dsp.h"

typedef struct {
	int r;
	int b;
	int g;
} rgb;

// shortcuts for commonly used colors as macro defines of rgb struct values
#define red {4095, 0, 0};
#define green {0, 4095, 0};
#define blue {0, 0, 4095};
#define orange {4095, 4095, 0};
#define magenta {4095, 0, 4095};
#define cyan {0, 4095, 4095};


void (*displayButton1Mode)(void);
void (*displayButton3Mode)(void);
void (*displayButton4Mode)(void);
void (*displayButton6Mode)(void);

void displayButton1ModeOn(void);
void displayButton1ModeOff(void);

void displayButton3ModeOn(void);
void displayButton3ModeOff(void);

void displayButton4ModeOn(void);
void displayButton4ModeOff(void);

void displayButton6ModeOn(void);
void displayButton6ModeOff(void);

void updateRGB(controlRateInputs *, audioRateInputs *);



#endif /* LED_DISPLAY_H_ */
