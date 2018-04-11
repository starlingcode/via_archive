#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"

#include "interrupt_functions.h"
#include "main.h"

// this is an integer that compensates for wavetable size in our frequency calculation (defined on wavetable family change)
int tableSizeCompensation;

// wavetable size - 1 in fix16 and that number doubled
int span;
int spanx2;

// control signal averages
extern uint32_t morphCVAverage;
uint32_t t1KnobAverage;
uint32_t t2KnobAverage;
extern uint32_t morphKnobAverage;
uint32_t t1CVAverage;
uint32_t t2CVAverage;

// these arrays are filled with our ADC values using DMA (set up in main.c)
uint32_t ADCReadings1[4];
uint32_t ADCReadings2[2];
uint32_t ADCReadings3[2];

enum trigModeTypes trigMode;


// mode indicators, defined in functions found in user_interface.c
int expoTable[4095];

void getAverages(int) __attribute__((section("ccmram")));


int getPhaseOsc(int position) {

	// call a specific averaging function that allows higher frequency CV inputs
	getAverages(1);

	// calculate the product of the linar FM CV with a product of exponential lookup functions
	// the lookup functions are scaled with the CV input circuit to yield 1vOct at the T1 CV
	inc = fix16_mul(fix16_mul(fix16_mul((2100 - t2CVAverage) << 9, expoTable[4095 - t1CVAverage] >> 5), expoTable[t1KnobAverage] >> 4), expoTable[t2KnobAverage >> 4]) >> tableSizeCompensation;

	//this keeps us from asking the contour generator to jump all the way through the wavetable
	if (inc >= span) {
		inc = span;
	} else if (inc <= -span) {
		inc = -span;
	}

	// apply the approrpiate signage to our inc per the retrigger behavior
	// this is how we get the contour generator to run backwards
	inc = inc * incSign;
	// if trigmode is gated and we arent in Drum Mode
	if (trigMode > 2) {
		// we look to see if we are about to increment past the attack->release transition
		if ((GATE_ON) && (my_abs(inc) > my_abs(span - position))) {
			// if so, we set a logic flag that we have frozen the contour generator in this transition
			SET_HOLD_AT_B;
			//and we hold it in place
			inc = span - position;
		}
		//if any of the above changes, we indicate that we are no longer frozen
		else {
			RESET_HOLD_AT_B;
		}
	}

	// increment our phase pointer by the newly calculated increment value
	position = position + inc;

	// if we have incremented outside of our table, wrap back around to the other side and stop/reset if we are in LF 1 shot mode
	if (position >= spanx2) {
		position = position - spanx2;
	}
	// same as above but for when we are backtracking through the attack phase aka negative increment
	else if (position < 0) {
		position = position + spanx2;
	}
	return position;
}

int getPhaseDrum(int position) {

	// don't average for noisy character
	getAverages(0);

	// calculate the product of exponential lookup functions
	// the lookup functions are scaled with the CV input circuit to yield 1vOct at the T1 CV
	// T2 is omitted from this calculation and determines drum decay time
	inc = fix16_mul(
			fix16_mul(300000, expoTable[4095 - t1CVAverage] >> 6), expoTable[(t1KnobAverage >> 1) + 2047] >> 10) >> tableSizeCompensation;

	// scale with the drum envelope when specified by the trig control
	if (PITCH_ON) {inc = fix16_mul(drumModValue + 80000, inc);}

	inc = inc * incSign;

	//this keeps us from asking the contour generator to jump all the way through the wavetable
	if (inc >= span) {
		inc = span;
	} else if (inc <= -span) {
		inc = -span;
	}

	// increment our phase pointer by the newly calculated increment value
	position = position + inc;

	// if we have incremented outside of our table, wrap back around to the other side and stop/reset if we are in LF 1 shot mode
	if (position >= spanx2) {
		position = position - spanx2;
		if (LAST_CYCLE) {

			// this is the logic maintenance needed to properly put the contour generator to rest
			// this keeps behavior on the next trigger predictable
			out = 0;
			RESET_LAST_CYCLE;
			RESET_OSCILLATOR_ACTIVE;
			incSign = 1;
			position = 0;
			SET_PHASE_STATE;
			SH_A_TRACK;
			SH_B_TRACK;
			if (DISPLAY_RUNTIME) {
				LEDA_OFF;
				LEDB_OFF;
				LEDC_OFF;
				LEDD_OFF;
			}
		}
	}
	// same as above but for when we are backtracking through the attack phase aka negative increment
	else if (position < 0) {

		position = position + spanx2;

		if (LAST_CYCLE) {

			// same as above, we are putting our contour generator to rest
			out = 0;
			RESET_LAST_CYCLE;
			RESET_OSCILLATOR_ACTIVE;
			incSign = 1;
			position = 0;
			RESET_PHASE_STATE;
			SH_A_TRACK;
			SH_B_TRACK;
			if (DISPLAY_RUNTIME) {
				LEDA_OFF;
				LEDB_OFF;
				LEDC_OFF;
				LEDD_OFF;
			}
			//HAL_NVIC_SetPendingIRQ(EXTI15_10_IRQn);
		}
	}
	return position;
}

int getPhaseSimpleEnv(int position) {

	// call function with longer moving averages for more noise reduction at the expense of CV bandwidth
	getAverages(2);

	//call the appropriate time calculation for the phase state and retriggering behavior
	if (position < span) {
		inc = (*attackTime)();
	}
	else {
		inc = (*releaseTime)();
	}

	// apply the approrpiate signage to our inc per the retrigger behavior
	// this is how we get the contour generator to run backwards
	inc = inc * incSign;
	// if trigmode is gated
	if (trigMode > 2) {
		// we look to see if we are about to increment past the attack->release transition
		if ((GATE_ON) && (my_abs(inc) > my_abs(span - position))) {
			// if so, we set a logic flag that we have frozen the contour generator in this transition
			SET_HOLD_AT_B;
			//and we hold it in place
			inc = span - position;
		}
		//if any of the above changes, we indicate that we are no longer frozen
		else {
			RESET_HOLD_AT_B;
		}
	}
	//this keeps us from asking the contour generator to jump all the way through the wavetable
	if (inc >= span) {
		inc = span;
	} else if (inc <= -span) {
		inc = -span;
	}

	// increment our phase pointer by the newly calculated increment value
	position = position + inc;

	// if we have incremented outside of our table, wrap back around to the other side and stop/reset if we are in LF 1 shot mode
	if (position >= spanx2) {

		position = position - spanx2;
		RESET_LAST_CYCLE;
		RESET_OSCILLATOR_ACTIVE;
		if (trigMode == pendulum)  {
			incSign = -1;
			position = spanx2;
			holdPosition = position;
		}
		else {
			incSign = 1;
			position = 0;
			holdPosition = position;
		}
		SET_PHASE_STATE;
		SH_A_TRACK;
		SH_B_TRACK;
		if (DISPLAY_RUNTIME) {
			LEDA_OFF;
			LEDB_OFF;
			LEDC_OFF;
			LEDD_OFF;
		}
	}
	// same as above but for when we are backtracking through the attack phase aka negative increment
	else if (position < 0) {

		position = position + spanx2;

		RESET_LAST_CYCLE;
		RESET_OSCILLATOR_ACTIVE;
		incSign = 1;
		position = 0;
		holdPosition = 0;
		RESET_PHASE_STATE;
		SH_A_TRACK;
		SH_B_TRACK;
		if (DISPLAY_RUNTIME) {
			LEDA_OFF;
			LEDB_OFF;
			LEDC_OFF;
			LEDD_OFF;
		}
	}
	return position;
}

int getPhaseSimpleLFO(int position) {

	getAverages(2);

	if (position < span) {
		inc = (*attackTime)();
	}
	else {
		inc = (*releaseTime)();
	}

	// apply the approrpiate signage to our inc per the retrigger behavior
	// this is how we get the contour generator to run backwards
	inc = inc * incSign;
	// if trigmode is gated and we arent in Drum Mode
	if (trigMode > 2) {
		// we look to see if we are about to increment past the attack->release transition
		if ((GATE_ON) && (my_abs(inc) > my_abs(span - position))) {
			// if so, we set a logic flag that we have frozen the contour generator in this transition
			SET_HOLD_AT_B;
			//and we hold it in place
			inc = span - position;
		}
		//if any of the above changes, we indicate that we are no longer frozen
		else {
			RESET_HOLD_AT_B;
		}
	}
	//this keeps us from asking the contour generator to jump all the way through the wavetable
	if (inc >= span) {
		inc = span;
	} else if (inc <= -span) {
		inc = -span;
	}

	// increment our phase pointer by the newly calculated increment value
	position = position + inc;

	// if we have incremented outside of our table, wrap back around to the other side and stop/reset if we are in LF 1 shot mode
	if (position >= spanx2) {

		position = position - spanx2;

	}
	// same as above but for when we are backtracking through the attack phase aka negative increment
	else if (position < 0) {
		position = position + spanx2;
	}
	return position;
}

int getPhaseComplexEnv(int position) {
	int attackTransferHolder;
	int releaseTransferHolder;
	static int hysteresis;
	static buffer256 skewBuffer;
	static int skewSum;
	int skewAverage;


	getAverages(2);

	inc = incSign*calcTime1Seq();

	if (!(HOLD_AT_B)) {
		holdPosition = inc + holdPosition;
	}
	if (holdPosition >= spanx2) {

		holdPosition = holdPosition - spanx2;

		RESET_OSCILLATOR_ACTIVE;
		if (trigMode == pendulum && !(DRUM_MODE_ON))  {
			incSign = -1;
			position = spanx2;
			holdPosition = spanx2;
		}
		else {
			incSign = 1;
			position = 0;
			holdPosition = 0;
		}
		out = 0;
		SET_PHASE_STATE;
		SH_A_TRACK;
		SH_B_TRACK;
		if (DISPLAY_RUNTIME) {
			LEDA_OFF;
			LEDB_OFF;
			LEDC_OFF;
			LEDD_OFF;
		}
	}

	if (holdPosition < 0) {
		holdPosition = holdPosition + spanx2;

		RESET_OSCILLATOR_ACTIVE;
		incSign = 1;
		position = 0;
		holdPosition = 0;
		out = 0;
		RESET_PHASE_STATE;
		SH_A_TRACK;
		SH_B_TRACK;
		if (DISPLAY_RUNTIME) {
			LEDA_OFF;
			LEDB_OFF;
			LEDC_OFF;
			LEDD_OFF;
		}
	}

	//combine the T2 CV and knob analogous to the morph knob

	if ((4095 - t2CVAverage) >= 2047) {
		// this first does the aforementioned interpolation between the knob value and full scale then scales back the value according to frequency
		skewMod = fix16_lerp(t2KnobAverage, 4095, ((4095 - t2CVAverage) - 2048) << 4) + hysteresis;
	}
	else {
		// analogous to above except in this case, morphCV is less than halfway
		skewMod = fix16_lerp(0, t2KnobAverage, (4095 - t2CVAverage) << 4) + hysteresis;
	}

	//reduce the bit depth with hysteresis and then apply an extra average to

	if ((skewMod - (skewMod >> 6)) > 32) {hysteresis = -24;}
	else if ((skewMod - (skewMod >> 6)) < 32) {hysteresis = 24;}
	else {hysteresis = 0;}

	skewMod = skewMod & 0b11111111111111111111111111000000;
	skewSum = (skewSum + skewMod- readn256(&skewBuffer, 255));
	skewAverage = skewSum >> 8;
	write256(&skewBuffer, skewMod);

	if (holdPosition < (fix16_mul(spanx2, (4095 - skewAverage) << 4))) {
		attackTransferHolder = (65535 << 11)/(4095 - skewAverage); // 1/(T2*2)
		position = fix16_mul(holdPosition, attackTransferHolder);

	}
	else if (!(HOLD_AT_B)) {
		releaseTransferHolder = (65535 << 11)/(skewAverage); // 1/((1-T2)*2)
		position = fix16_mul(holdPosition, releaseTransferHolder) + spanx2 - fix16_mul(spanx2, releaseTransferHolder);

	}

	if ((GATE_ON) && ((my_abs(inc) > my_abs(span - position)) || (HOLD_AT_B))) {
		// if so, we set a logic flag that we have frozen the contour generator in this transition
		SET_HOLD_AT_B;
	}
	//if any of the above changes, we indicate that we are no longer frozen
	else {
		RESET_HOLD_AT_B;
	}


	// if we have incremented outside of our table, wrap back around to the other side and stop/reset if we are in LF 1 shot mode
	if (position >= spanx2) {
		position = position - spanx2;

		RESET_OSCILLATOR_ACTIVE;
		if (trigMode == pendulum && !(DRUM_MODE_ON))  {
			incSign = -1;
			position = spanx2;
			holdPosition = position;
		}
		else {
			incSign = 1;
			position = 0;
			holdPosition = position;
		}
		SET_PHASE_STATE;
		SH_A_TRACK;
		SH_B_TRACK;
		if (DISPLAY_RUNTIME) {
			LEDA_OFF;
			LEDB_OFF;
			LEDC_OFF;
			LEDD_OFF;
		}
	}
	// same as above but for when we are backtracking through the attack phase aka negative increment
	else if (position < 0) {

		position = position + spanx2;

		RESET_OSCILLATOR_ACTIVE;
		incSign = 1;
		position = 0;
		holdPosition = 0;
		RESET_PHASE_STATE;
		SH_A_TRACK;
		SH_B_TRACK;
		if (DISPLAY_RUNTIME) {
			LEDA_OFF;
			LEDB_OFF;
			LEDC_OFF;
			LEDD_OFF;
		}

	}
	return position;
}

int getPhaseComplexLFO(int position) {
	int attackTransferHolder;
	int releaseTransferHolder;
	static int hysteresis;
	static buffer256 skewBuffer;
	static int skewSum;
	int skewAverage;


		getAverages(2);

		inc = incSign*calcTime1Seq();

		if (!(HOLD_AT_B)) {
			holdPosition = inc + holdPosition;
		}
		if (holdPosition >= spanx2) {
			holdPosition = holdPosition - spanx2;
		}

		if (holdPosition < 0) {
			holdPosition = holdPosition + spanx2;
		}

		if ((4095 - t2CVAverage) >= 2047) {
			// this first does the aforementioned interpolation between the knob value and full scale then scales back the value according to frequency
			skewMod = fix16_lerp(t2KnobAverage, 4095, ((4095 - t2CVAverage) - 2048) << 4) + hysteresis;
		}
		else {
			// analogous to above except in this case, morphCV is less than halfway
			skewMod = fix16_lerp(0, t2KnobAverage, (4095 - t2CVAverage) << 4) + hysteresis;
		}

		if ((skewMod - (skewMod >> 6)) > 32) {hysteresis = -24;}
		else if ((skewMod - (skewMod >> 6)) < 32) {hysteresis = 24;}
		else {hysteresis = 0;}

		skewMod = skewMod & 0b11111111111111111111111111000000;
		skewSum = (skewSum + skewMod- readn256(&skewBuffer, 255));
		skewAverage = skewSum >> 8;
		write256(&skewBuffer, skewMod);

		if (holdPosition < (fix16_mul(spanx2, (4095 - skewAverage) << 4))) {
			attackTransferHolder = (65535 << 11)/(4095 - skewAverage); // 1/(T2*2)
			position = fix16_mul(holdPosition, attackTransferHolder);

		}
		else if (!(HOLD_AT_B)) {
			releaseTransferHolder = (65535 << 11)/(skewAverage); // 1/((1-T2)*2)
			position = fix16_mul(holdPosition, releaseTransferHolder) + spanx2 - fix16_mul(spanx2, releaseTransferHolder);

		}

		if ((GATE_ON) && ((my_abs(inc) > my_abs(span - position)) || (HOLD_AT_B))) {
			// if so, we set a logic flag that we have frozen the contour generator in this transition
			SET_HOLD_AT_B;
		}
		//if any of the above changes, we indicate that we are no longer frozen
		else {
			RESET_HOLD_AT_B;
		}

	// if we have incremented outside of our table, wrap back around to the other side and stop/reset if we are in LF 1 shot mode
	if (position >= spanx2) {
		position = position - spanx2;
	}
	// same as above but for when we are backtracking through the attack phase aka negative increment
	else if (position < 0) {
		position = position + spanx2;
	}
	return position;
}

// multiply our knobs with our CVs with the appropriate scaling per the current frequency mode

int calcTime1Env(void) {
	int time1 = ((expoTable[t1CVAverage] >> 13) * (expoTable[(4095 - t1KnobAverage)] >> 13)) >> (6 + tableSizeCompensation);
	return time1;
}

int calcTime2Env(void) {
	int time2 = ((expoTable[t2CVAverage] >> 13) * (expoTable[(4095 - t2KnobAverage)] >> 11)) >> (8 + tableSizeCompensation);
	return time2;
}

int calcTime1Seq(void) {
	int time1 = ((expoTable[t1CVAverage] >> 13) * (expoTable[(4095 - t1KnobAverage)] >> 13)) >> (8 + tableSizeCompensation);
	return time1;
}

int calcTime2Seq(void) {
	int time2 = ((expoTable[t2CVAverage] >> 13) * (expoTable[(4095 - t2KnobAverage)] >> 13)) >> (8 + tableSizeCompensation);
	return time2;
}

// noise at the morph CV is noise in the contour generator signal

void getAverages(int speedFlag) {

	static buffer256 t1KnobBuffer;
	static buffer256 t2KnobBuffer;
	static buffer256 t1CVBuffer;
	static buffer256 t2CVBuffer;
	static buffer256 morphKnobBuffer;
	static buffer256 morphCVBuffer;
	static uint32_t t1KnobSum;
	static uint32_t t2KnobSum;
	static uint32_t morphKnobSum;
	static uint32_t morphCVSum;
	static uint32_t t1CVSum;
	static uint32_t t2CVSum;
	static uint32_t t1KnobSumAudio;
	static uint32_t t2KnobSumAudio;
	static uint32_t morphKnobSumAudio;
	static uint32_t morphCVSumAudio;
	static uint32_t t1CVSumAudio;
	static uint32_t t2CVSumAudio;

	t1KnobSum = (t1KnobSum + time1Knob- readn256(&t1KnobBuffer, 255));
	t2KnobSum = (t2KnobSum + time2Knob- readn256(&t2KnobBuffer, 255));
	morphKnobSum = (morphKnobSum + morphKnob- readn256(&morphKnobBuffer, 255));
	morphCVSum = (morphCVSum + morphCV- readn256(&morphCVBuffer, 255));
	t1CVSum = (t1CVSum + time1CV- readn256(&t1CVBuffer, 255));
	t2CVSum = (t2CVSum + time2CV- readn256(&t2CVBuffer, 255));
	t1KnobSumAudio = (t1KnobSumAudio + time1Knob- readn256(&t1KnobBuffer, 255));
	t2KnobSumAudio = (t2KnobSumAudio + time2Knob- readn256(&t2KnobBuffer, 255));
	morphKnobSumAudio = (morphKnobSumAudio + morphKnob- readn256(&morphKnobBuffer, 255));
	morphCVSumAudio = (morphCVSumAudio + morphCV- readn256(&morphCVBuffer, 255));
	t1CVSumAudio = (t1CVSumAudio + time1CV- readn256(&t1CVBuffer, 255));
	t2CVSumAudio = (t2CVSumAudio + time2CV- readn256(&t2CVBuffer, 15));

	switch (speedFlag) {
	case 0:
		t1KnobAverage = time1Knob;
		t2KnobAverage = time2Knob;
		morphKnobAverage = morphKnob;
		t1CVAverage = time1CV;
		t2CVAverage = time1CV;
		morphCVAverage = morphCV << 5;
		break;
	case 1:
		t1KnobAverage = t1KnobSumAudio >> 8;
		t2KnobAverage = t2KnobSumAudio >> 8;
		morphKnobAverage = morphKnobSumAudio >> 8;
		t1CVAverage = t1CVSumAudio >> 8;
		t2CVAverage = t2CVSumAudio >> 4;
		morphCVAverage = morphCVSumAudio >> 3;
		break;
	case 2:
		t1KnobAverage = t1KnobSum >> 8;
		t2KnobAverage = t2KnobSum >> 8;
		morphKnobAverage = morphKnobSum >> 8;
		t1CVAverage = t1CVSum >> 8;
		t2CVAverage = t2CVSum >> 8;
		morphCVAverage = morphCVSum >> 3;
	break;
	default: break;
	}

	write256(&morphCVBuffer, morphCV);
	write256(&t1CVBuffer, time1CV);
	write256(&t2CVBuffer, time2CV);
	write256(&t1KnobBuffer, time1Knob);
	write256(&t2KnobBuffer, time2Knob);
	write256(&morphKnobBuffer, morphKnob);
}

