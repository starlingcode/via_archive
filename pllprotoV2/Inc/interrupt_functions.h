#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"

// wavetable size - 1 in fix16 and that number doubled
uint32_t span;
uint32_t spanx2;
int tableSizeCompensation;

//per family bit shift amounts to accomplish morph
uint32_t morphBitShiftRight;
uint32_t morphBitShiftLeft;

//import pointer to struct that contains our wavetable family info

//this is used for our 1v/oct and bonus expo envelope


//these are the variables used to generate the phase information that feeds our interpolations
int fixMorph;
int getMorph;

uint32_t attackInc;
uint32_t releaseInc;
uint32_t catchupInc;
uint32_t gateOnCount;
uint32_t periodCount;
int incSign;
int time1;
int time2;

int holdPosition;


//most recent value from our expo decay
int expoScale;

//lastest result of the biinterpolation between interp1 and interp2 (scaled in drum mode)
int out;


int myfix16_mul(int, int)  __attribute__((section("ccmram")));
int myfix24_mul(int, int)  __attribute__((section("ccmram")));
int myfix48_mul(uint32_t, uint32_t)  __attribute__((section("ccmram")));
int myfix16_lerp(int, int, uint16_t)  __attribute__((section("ccmram")));


// ADC variables and defines

#define time2Knob ADCReadings2[0]
#define morphKnob (ADCReadings2[1] & 0b11111111111111111111111111100000)
#define time1CV ADCReadings1[0]
#define time2CV (ADCReadings1[1] & 0b11111111111111111111111111111110)
#define morphCV (ADCReadings1[2] & 0b11111111111111111111111111000000)
#define time1Knob ADCReadings3[0]







void inputCapture(void)  __attribute__((section("ccmram")));
void dacISR(void)  __attribute__((section("ccmram")));
