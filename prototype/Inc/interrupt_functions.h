#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"



int calcTime1Env(void) __attribute__((section("ccmram")));
int calcTime2Env(void) __attribute__((section("ccmram")));
int calcTime1Seq(void) __attribute__((section("ccmram")));
int calcTime2Seq(void) __attribute__((section("ccmram")));

void sampHoldB(void) __attribute__((section("ccmram")));
void sampHoldA(void) __attribute__((section("ccmram")));


void dacISR(void) __attribute__((section("ccmram")));

int (*attackTime) (void);
int (*releaseTime) (void);

//these are the variables used to generate the phase information that feeds our interpolations
int fixMorph;
int morphBuffer[8];
int getMorph;

int time1;
int time2;

//most recent value from our expo decay
int expoScale;

volatile int position;
volatile int inc;
volatile int incSign;

uint32_t attackCount;



