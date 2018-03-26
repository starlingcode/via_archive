#include "tables.h"
#include "main.h"
#include "tsl_user.h"

#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"

#include "interrupt_functions.h"

#include "eeprom.h"

#include "int64.h"


//uint32_t ee_status;

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;


// these enums contain our mode information
enum speedTypes speed; // {audio, env, seq}
enum loopTypes loop; // {noloop, looping}
enum trigModeTypes trigMode; // {noretrigger, hardsync, nongatedretrigger, gated, pendulum}
enum sampleHoldModeTypes sampleHoldMode; // {nosampleandhold, a, b, ab, antidecimate, decimate}
enum logicOutATypes logicOutA; // {triggerA, gateA, deltaA}
enum logicOutBTypes logicOutB; // {triggerB, gateB, deltaB}

extern uint16_t VirtAddVarTab[NB_OF_VAR];
extern uint16_t VarDataTab[NB_OF_VAR];






// these variables are passed between our functions that read the touch sensors and change modes
extern uint32_t modeflag;
extern uint32_t detectOn;
uint32_t lastDetect;
extern uint32_t displayNewMode;


void handleRelease(uint32_t);
void changeMode(uint32_t);
void showMode(uint32_t);
void familyRGB(void);
void clearLEDs(void);


void switchFamily(void);
void loadSampleArray(Family);

// these variables are used to represent the number of entries in a given wavetable stored in the currently selected family
// they are shared by tim6IRQ
extern uint32_t span;
extern int spanx2;
extern int tableSizeCompensation;

// these variables are used to represent the number of wavetables in the currently selected family when performing our morph function
extern uint32_t morphBitShiftRight;
extern uint32_t morphBitShiftLeft;


void readDetect(void) {

	//check to see if any of our touch sensors have gone into detect state

	if (MyTKeys[3].p_Data->StateId == TSL_STATEID_DETECT) {
		RESET_RGB_ON; //turn off the runtime display
		modeflag = 1; //indicate to the other mode change functions that we have pressed the speed button
		detectOn = 1; //indicate that a touch sensor was in detect state during this aquisition cycle
		clearLEDs(); //wipe the vestiges of our runtimme display
		__HAL_TIM_SET_COUNTER(&htim4, 0); //reset the timer that we use for mode change timeout
		showMode(speed); //show our currentm mode
	}
	if (MyTKeys[2].p_Data->StateId == TSL_STATEID_DETECT) {
		RESET_RGB_ON;
		modeflag = 2; //indicate to the other mode change functions that we have pressed the trigger mode button
		detectOn = 1;
		clearLEDs();
		__HAL_TIM_SET_COUNTER(&htim4, 0);
		showMode(trigMode);
	}
	if (MyTKeys[1].p_Data->StateId == TSL_STATEID_DETECT) {
		RESET_RGB_ON;
		modeflag = 3; //indicate to the other mode change functions that we have pressed the loop button
		detectOn = 1;
		clearLEDs();
		__HAL_TIM_SET_COUNTER(&htim4, 0);
		showMode(loop);
	}
	if (MyTKeys[4].p_Data->StateId == TSL_STATEID_DETECT) {
		RESET_RGB_ON;
		modeflag = 4; //indicate to the other mode change functions that we have pressed the sample and hold mode button
		detectOn = 1;
		clearLEDs();
		__HAL_TIM_SET_COUNTER(&htim4, 0);
		showMode(sampleHoldMode);
	}
	if (MyTKeys[5].p_Data->StateId == TSL_STATEID_DETECT) {
		RESET_RGB_ON;
		modeflag = 5; //indicate to the other mode change functions that we have pressed the family up button
		detectOn = 1;
		clearLEDs();
		__HAL_TIM_SET_COUNTER(&htim4, 0);
		showMode(familyIndicator);
	}
	if (MyTKeys[0].p_Data->StateId == TSL_STATEID_DETECT) {
		RESET_RGB_ON;
		modeflag = 6; //indicate to the other mode change functions that we have pressed the family down button
		detectOn = 1;
		clearLEDs();
		__HAL_TIM_SET_COUNTER(&htim4, 0);
		showMode(familyIndicator);
	}

}

void readRelease(uint32_t modeFlagHolder) {

	// look for a change to release state on the button that was pressed (passed in with the function argument)

	switch (modeFlagHolder) {

	case 1:

		if (MyTKeys[3].p_Data->StateId == TSL_STATEID_RELEASE) {
			detectOn = 0; // indicate that we no longer have a touch sensor in detect state
			clearLEDs(); // clear the display that showed the current mode
			handleRelease(modeFlagHolder); //take the appropriate action per the button that had been pressed
		}
		break;

	case 2:

		if (MyTKeys[3].p_Data->StateId == TSL_STATEID_DETECT) {
			SET_AUX_MENU;
			modeflag = 7; //indicate to the other mode change functions that we have pressed the logic a button
			detectOn = 1; //indicate that a touch sensor was in detect state during this aquisition cycle
			clearLEDs(); //wipe the vestiges of our runtimme display
			__HAL_TIM_SET_COUNTER(&htim4, 0); //reset the timer that we use for mode change timeout
			showMode(logicOutA); //show our currentm mode
		}

		if (MyTKeys[1].p_Data->StateId == TSL_STATEID_DETECT) {
			SET_AUX_MENU;
			modeflag = 8; //indicate to the other mode change functions that we have pressed the logic b button
			detectOn = 1; //indicate that a touch sensor was in detect state during this aquisition cycle
			clearLEDs(); //wipe the vestiges of our runtime display
			__HAL_TIM_SET_COUNTER(&htim4, 0); //reset the timer that we use for mode change timeout
			showMode(logicOutB); //show our current mode
		}

		if (MyTKeys[2].p_Data->StateId == TSL_STATEID_RELEASE) {
			detectOn = 0;
			clearLEDs();
			handleRelease(modeFlagHolder);
		}
		break;

	case 3:

		if (MyTKeys[1].p_Data->StateId == TSL_STATEID_RELEASE) {
			detectOn = 0;
			clearLEDs();
			handleRelease(modeFlagHolder);
		}
		break;

	case 4:

		if (MyTKeys[4].p_Data->StateId == TSL_STATEID_RELEASE) {
			detectOn = 0;
			clearLEDs();
			handleRelease(modeFlagHolder);
		}
		break;

	case 5:

		if (MyTKeys[5].p_Data->StateId == TSL_STATEID_RELEASE) {
			detectOn = 0;
			clearLEDs();
			handleRelease(modeFlagHolder);
		}
		break;

	case 6:

		if (MyTKeys[0].p_Data->StateId == TSL_STATEID_RELEASE) {
			detectOn = 0;
			clearLEDs();
			handleRelease(modeFlagHolder);
		}
		break;

	case 7:

		if (MyTKeys[3].p_Data->StateId == TSL_STATEID_RELEASE) {
			if (MyTKeys[2].p_Data->StateId == TSL_STATEID_RELEASE) {
				detectOn = 0;
			}
			clearLEDs();
			RESET_AUX_MENU;
			handleRelease(modeFlagHolder);
		}
		break;

	case 8:

		if (MyTKeys[1].p_Data->StateId == TSL_STATEID_RELEASE) {
			if (MyTKeys[2].p_Data->StateId == TSL_STATEID_RELEASE) {
				detectOn = 0;
			}
			clearLEDs();
			RESET_AUX_MENU;
			handleRelease(modeFlagHolder);
		}
		break;

	}

}

void handleRelease(uint32_t pinMode) {
	if (__HAL_TIM_GET_COUNTER(&htim4) < 3000) {
		// if we havent exceeded the mode change timeout, change the appropriate mode and then display the new mode
		// current value is probably too short
		changeMode(pinMode);
		switch (pinMode) {
		case 1:
			showMode(speed);
			break;
		case 2:
			showMode(trigMode);
			break;
		case 3:
			showMode(loop);
			break;
		case 4:
			showMode(sampleHoldMode);
			break;
		case 5:
			showMode(familyIndicator);
			break;
		case 6:
			showMode(familyIndicator);
			break;
		case 7:
			modeflag = 2;
			showMode(logicOutA);
			break;
		case 8:
			modeflag = 2;
			showMode(logicOutB);
			break;
		}
		displayNewMode = 1;
		__HAL_TIM_SET_COUNTER(&htim4, 0);
	} else {
		if (AUX_MENU) {
			modeflag = 2;
		}
		clearLEDs();
		SET_RGB_ON;
	}
}

void changeMode(uint32_t mode) {
	if (mode == 1) {
		// toggle through our 3 speed modes
		speed = (speed + 1) % 3;

		holdState = (holdState & 0b1111111111111001) | (speed << 1);

		switchFamily();

		if (speed == audio && loop == noloop) {
			//SET_CLEARBUFFER;
			//since this parameter can throw us into drum mode, initialize the proper modulation flags per trigger mode
			SET_DRUM_MODE_ON;
			TIM6->ARR = 750;
			switch (trigMode) {
			case 0:
				SET_AMP_ON;
				SET_PITCH_ON;
				SET_MORPH_ON;
				break;
			case 1:
				SET_AMP_ON;
				RESET_PITCH_ON;
				SET_MORPH_ON;
				break;
			case 2:
				SET_AMP_ON;
				RESET_PITCH_ON;
				RESET_MORPH_ON;
				break;
			case 3:
				RESET_AMP_ON;
				RESET_PITCH_ON;
				SET_MORPH_ON;
				break;
			case 4:
				RESET_AMP_ON;
				SET_PITCH_ON;
				SET_MORPH_ON;
				break;
			}
			// i believe this is a holdover from old code
			__HAL_TIM_ENABLE(&htim3);
		} else {
			// if we didnt just go into drum mode, make sure drum mode is off
			RESET_DRUM_MODE_ON;
			RESET_AMP_ON;
			RESET_PITCH_ON;
			RESET_MORPH_ON;


			// set the appropriate time calculation functions
			if (speed == env) {
				TIM6->ARR = 750;
				attackTime = calcTime1Env;
				releaseTime = calcTime2Env;
			} else if (speed == seq) {
				TIM6->ARR = 1000;
				attackTime = calcTime1Seq;
				releaseTime = calcTime2Seq;
			} else {
				TIM6->ARR = 750;
			}
		}
	}
	else if (mode == 2) {
		trigMode = (trigMode + 1) % 6;
		//initialize some essential retrigger variables

		holdState = (holdState & 0b1111111111000111) | (trigMode << 3);

		incSign = 1;
		RESET_GATE_ON;
		//if drum mode is on, toggle through sets of modulation destinations
		switch (trigMode) {
		case 0:
			SET_AMP_ON;
			SET_PITCH_ON;
			SET_MORPH_ON;
			break;
		case 1:
			SET_AMP_ON;
			RESET_PITCH_ON;
			SET_MORPH_ON;
			break;
		case 2:
			SET_AMP_ON;
			RESET_PITCH_ON;
			RESET_MORPH_ON;
			break;
		case 3:
			RESET_AMP_ON;
			RESET_PITCH_ON;
			SET_MORPH_ON;
			break;
		case 4:
			RESET_AMP_ON;
			SET_PITCH_ON;
			SET_MORPH_ON;
			break;

		case 5:
			RESET_AMP_ON;
			SET_PITCH_ON;
			RESET_MORPH_ON;
			break;

		}
	}
	else if (mode == 3) {
		loop = (loop + 1) % 2;

		holdState = (holdState & 0b1111111111111110) | loop;

		if (loop == noloop) {
			// signal to our oscillator that it should put itself to sleep
			SET_LAST_CYCLE;
			// switching to no loop when speed is at audio activates drum mode
			// this is about the same as what we do in the speed mode case above
			if (speed == audio) {
				SET_DRUM_MODE_ON;
				//TIM6->ARR = 750;
				switch (trigMode) {
				case 0:
					SET_AMP_ON;
					SET_PITCH_ON;
					SET_MORPH_ON;
					break;
				case 1:
					SET_AMP_ON;
					RESET_PITCH_ON;
					SET_MORPH_ON;
					break;
				case 2:
					SET_AMP_ON;
					RESET_PITCH_ON;
					RESET_MORPH_ON;
					break;
				case 3:
					RESET_AMP_ON;
					RESET_PITCH_ON;
					SET_MORPH_ON;
					break;
				case 4:
					RESET_AMP_ON;
					SET_PITCH_ON;
					SET_MORPH_ON;
					break;

				}
				__HAL_TIM_ENABLE(&htim3);
			} else {
				RESET_DRUM_MODE_ON;
				//TIM6->ARR = 500;
				RESET_AMP_ON;
				RESET_PITCH_ON;
				RESET_MORPH_ON;
			}
		} else {
			RESET_LAST_CYCLE;
			RESET_DRUM_MODE_ON;
			//TIM6->ARR = 500;
			RESET_AMP_ON;
			RESET_PITCH_ON;
			RESET_MORPH_ON;
			//set our oscillator active flag so enabling loop starts playback (not for ken!)
			SET_OSCILLATOR_ACTIVE;
		}

	}
	else if (mode == 4) {
		sampleHoldMode = (sampleHoldMode + 1) % 6;

		holdState = (holdState & 0b1111111000111111) | (sampleHoldMode << 6);

		SH_A_TRACK
		SH_B_TRACK

	}
	else if (mode == 5) {
		// increment our family pointer and swap in the correct family

		familyIndicator = (familyIndicator + 1) % 8;
		switchFamily();
		holdState = (holdState & 0b1111000111111111) | (familyIndicator << 9);
	}
	else if (mode == 6) {
		// wrap back to the end of the array of families if we go back from the first entry
		// otherwise same as above
		if (familyIndicator == 0) {
			familyIndicator = 7;
		} else {
			familyIndicator = (familyIndicator - 1);
		}
		switchFamily();
		holdState = (holdState & 0b1111000111111111) | (familyIndicator << 9);
	}
	else if (mode == 7) {
		logicOutA = (logicOutA + 1) % 3;
		holdState = (holdState & 0b1100111111111111) | (logicOutA << 13);;
		switch (logicOutA) {
		case 0:
			SET_GATEA;
			RESET_TRIGA;
			RESET_DELTAA;
			break;
		case 1:
			RESET_GATEA;
			SET_TRIGA;
			RESET_DELTAA;
			break;
		case 2:
			RESET_GATEA;
			RESET_TRIGA;
			SET_DELTAA;
			break;
		}


	}
	else if (mode == 8) {
		logicOutB = (logicOutB + 1) % 3;
		holdState = (holdState & 0b0011111111111111) | (logicOutB << 15);
		switch (logicOutB) {
		case 0:
			SET_GATEB;
			RESET_TRIGB;
			RESET_DELTAB;
			break;
		case 1:
			RESET_GATEB;
			SET_TRIGB;
			RESET_DELTAB;
			break;
		case 2:
			RESET_GATEB;
			RESET_TRIGB;
			SET_DELTAB;
			break;
		}

	}


	ee_status = EE_WriteVariable(VirtAddVarTab[0], holdState);
    ee_status|= EE_ReadVariable(VirtAddVarTab[0],  &VarDataTab[0]);

}

void showMode(uint32_t currentmode) {

	// if we are switching families, show a color corresponding to that family
	if (modeflag == 5 || modeflag == 6) {
		familyRGB();
	}

	else {
		switch (currentmode) {
		// represent a 4 bit number with our LEDs
		// NEEDS WORK
		case 0:
			LEDA_ON
			break;
		case 1:
			LEDC_ON
			break;
		case 2:
			LEDB_ON
			break;
		case 3:
			LEDD_ON
			break;
		case 4:
			LEDA_ON
			LEDC_ON
			break;
		case 5:
			LEDB_ON
			LEDD_ON
			break;
		}
	}


}

void familyRGB(void) {

	switch (speed) {
	case 0:
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 4095);
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);
		break;

	case 1:
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 4095);
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);
		break;

	case 2:
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 4095);
	}

	switch (familyIndicator) {
	case 0:
		LEDA_ON
		break;
	case 1:
		LEDC_ON
		break;
	case 2:
		LEDB_ON
		break;

	case 3:
		LEDD_ON
		break;
	case 4:
		LEDA_ON
		LEDC_ON
		break;
	case 5:
		LEDB_ON
		LEDD_ON
		break;
	case 6:
		LEDA_ON;
		LEDB_ON;
		break;
	case 7:
		LEDC_ON;
		LEDD_ON;
		break;

	}



}
void clearLEDs(void) {
	//pretty self explanatory

	LEDA_OFF
	LEDB_OFF
	LEDC_OFF
	LEDD_OFF

	//blank the LEDs
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);

}



void restoreDisplay() {
	if (__HAL_TIM_GET_COUNTER(&htim4) > 10000) {
		clearLEDs(); // get rid of our last mode display
		SET_RGB_ON; // turn on the runtime display
		displayNewMode = 0; // a bit of logic used to make sure that we show the mode during the main loop
	}
}

// this sets the flags to be used in the interrupt and also fills the holding array on the heap

void switchFamily(void) {
	currentFamily = familyArray[speed][familyIndicator];

	currentFamily = familyArray[speed][familyIndicator];
	loadSampleArray(currentFamily);

	if (currentFamily.bandlimitOff) {
		RESET_BANDLIMIT;
	} else {
		SET_BANDLIMIT;
	}

	span = (currentFamily.tableLength) << 16;
	spanx2 = (currentFamily.tableLength) << 17;
	switch (currentFamily.familySize) {
	// these are values that properly allow us to select a family and interpolation fraction for our morph
	case 3:
		morphBitShiftRight = 11;
		morphBitShiftLeft = 5;
		break;

	case 5:
		morphBitShiftRight = 10;
		morphBitShiftLeft = 6;
		break;

	case 9:
		morphBitShiftRight = 9;
		morphBitShiftLeft = 7;
		break;

	case 17:
		morphBitShiftRight = 8;
		morphBitShiftLeft = 8;
		break;

	case 33:
		morphBitShiftRight = 7;
		morphBitShiftLeft = 9;
		break;

	}
	switch (currentFamily.tableLength) {
	// these are values that properly allow us to select a family and interpolation fraction for our morph
	case 4:
		tableSizeCompensation = 6;
		break;

	case 8:
		tableSizeCompensation = 5;
		break;

	case 16:
		tableSizeCompensation = 4;
		break;

	case 32:
		tableSizeCompensation = 3;
		break;

	case 64:
		tableSizeCompensation = 2;
		break;

	case 128:
		tableSizeCompensation = 1;

	case 256:
		tableSizeCompensation = 0;

	}
}

//this actually shuttles the data from flash to ram and fills our holding array

void loadSampleArray(Family family) {

	uint16_t **currentFamilyPointer;

	for (int i = 0; i < family.familySize; i++) {
		for (int j = 0; j <= family.tableLength; j++) {
			// this just gets the appropriate samples and plops them into the global holding arrays
			currentFamilyPointer = family.attackFamily + i;
			attackHoldArray[i][j] = *(*(currentFamilyPointer) + j);

			currentFamilyPointer = family.releaseFamily + i;
			releaseHoldArray[i][j] = *(*(currentFamilyPointer) + j);
		}
	}
}




