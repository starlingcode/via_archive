#include "tables.h"
#include "main.h"
#include "tsl_user.h"

#include "scales.h"
#include "eeprom.h"

#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"

#include "interrupt_functions.h"


#include "int64.h"

int holdState;

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;


// these enums contain our mode information
enum pllTypes pll; // {none, true, catch, setCatch}
enum controlSchemes controlScheme; // {gateLength, knobCV}
enum scaleTypes scaleType; // {rhythms, pitches}
enum sampleHoldModeTypes sampleHoldMode; // {nosampleandhold, a, b, ab, antidecimate, decimate}
enum logicOutATypes logicOutA; // {triggerA, gateA, deltaA, ratioDeltaA, pllClock};
enum logicOutBTypes logicOutB; // {triggerB, gateB, deltaB, ratioDeltaB, pllClock};
enum autoDutyTypes autoDuty;

extern uint16_t VirtAddVarTab[NB_OF_VAR];
extern uint16_t VarDataTab[NB_OF_VAR];
// these logic flags are used to communicate state between the main controlScheme and the interrupts





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


void readDetect(void) {

	//check to see if any of our touch sensors have gone into detect state

	if (MyTKeys[3].p_Data->StateId == TSL_STATEID_DETECT) {
		RESET_RGB_ON; //turn off the runtime display
		modeflag = 1; //indicate to the other mode change functions that we have pressed the scaleType button
		detectOn = 1; //indicate that a touch sensor was in detect state during this aquisition cycle
		clearLEDs(); //wipe the vestiges of our runtimme display
		__HAL_TIM_SET_COUNTER(&htim4, 0); //reset the timer that we use for mode change timeout
		showMode(scaleType); //show our currentm mode
	}
	if (MyTKeys[2].p_Data->StateId == TSL_STATEID_DETECT) {
		RESET_RGB_ON;
		modeflag = 2; //indicate to the other mode change functions that we have pressed the trigger mode button
		detectOn = 1;
		clearLEDs();
		__HAL_TIM_SET_COUNTER(&htim4, 0);
		showMode(pll);
	}
	if (MyTKeys[1].p_Data->StateId == TSL_STATEID_DETECT) {
		RESET_RGB_ON;
		modeflag = 3; //indicate to the other mode change functions that we have pressed the controlScheme button
		detectOn = 1;
		clearLEDs();
		__HAL_TIM_SET_COUNTER(&htim4, 0);
		showMode(controlScheme);
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

		if (MyTKeys[4].p_Data->StateId == TSL_STATEID_DETECT) {
			SET_AUX_MENU;
			modeflag = 9; //indicate to the other mode change functions that we have pressed the logic b button
			detectOn = 1; //indicate that a touch sensor was in detect state during this aquisition cycle
			clearLEDs(); //wipe the vestiges of our runtime display
			__HAL_TIM_SET_COUNTER(&htim4, 0); //reset the timer that we use for mode change timeout
			showMode(autoDuty); //show our current mode
		}

		if (MyTKeys[2].p_Data->StateId == TSL_STATEID_RELEASE) {
			detectOn = 0;
			if (!(AUX_MENU)) {
				clearLEDs();
			}
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
			handleRelease(modeFlagHolder);
		}
		break;

	case 8:

		if (MyTKeys[1].p_Data->StateId == TSL_STATEID_RELEASE) {
			if (MyTKeys[2].p_Data->StateId == TSL_STATEID_RELEASE) {
				detectOn = 0;
			}
			clearLEDs();
			handleRelease(modeFlagHolder);
		}
		break;
	case 9:

		if (MyTKeys[4].p_Data->StateId == TSL_STATEID_RELEASE) {
			if (MyTKeys[2].p_Data->StateId == TSL_STATEID_RELEASE) {
				detectOn = 0;
			}
			clearLEDs();
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
			showMode(scaleType);
			break;
		case 2:
			showMode(pll);
			break;
		case 3:
			showMode(controlScheme);
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
		case 9:
			modeflag = 2;
			showMode(autoDuty);
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
		// toggle through our 3 scaleType modes
		scaleType = (scaleType + 1) % 5;
		switchScale(scaleType);
		holdState = (holdState & 0b1111111100111111) | (scaleType << 6);
	}
	else if (mode == 2) {

		pll = (pll + 1) % 3;
		holdState = (holdState & 0b1111111111000111) | (pll << 3);


	}
	else if (mode == 3) {

		controlScheme = (controlScheme + 1) % 4;
		holdState = (holdState & 0b1111111111111000) | controlScheme;

	}
	else if (mode == 4) {

		sampleHoldMode = (sampleHoldMode + 1) % 6;

		holdState = (holdState & 0b1111100011111111) | (sampleHoldMode << 8);

		SH_A_TRACK
		SH_B_TRACK

	}
	else if (mode == 5) {
		// increment our family pointer and swap in the correct family
		familyIndicator = (familyIndicator + 1) % 16;
		switchFamily();
		holdState = (holdState & 0b1000011111111111) | (familyIndicator << 11);
	}
	else if (mode == 6) {
		// wrap back to the end of the array of families if we go back from the first entry
		// otherwise same as above
		if (familyIndicator == 0) {
			familyIndicator = 15;
		} else {
			familyIndicator = (familyIndicator - 1);
		}

		switchFamily();
		holdState = (holdState & 0b1000011111111111) | (familyIndicator << 11);
	}	else if (mode == 7) {
		logicOutA = (logicOutA + 1) % 5;
		holdLogicOut = (holdLogicOut & 0b1111111111111000) | logicOutA;

		ee_status = EE_WriteVariable(VirtAddVarTab[1], holdLogicOut);
	    ee_status|= EE_ReadVariable(VirtAddVarTab[1],  &VarDataTab[1]);


		switch (logicOutA) {
		case 0:
			SET_GATEA;
			RESET_DELTAB;
			RESET_DELTAA;
			RESET_RATIO_DELTAA;
			RESET_PLL_DIVA;
			break;
		case 1:
			RESET_GATEA;
			SET_TRIGA;
			RESET_DELTAA;
			RESET_RATIO_DELTAA;
			RESET_PLL_DIVA;
			break;
		case 2:
			RESET_GATEA;
			RESET_TRIGA;
			SET_DELTAA;
			RESET_RATIO_DELTAA;
			RESET_PLL_DIVA;
			break;
		case 3:
			RESET_GATEA;
			RESET_TRIGA;
			RESET_DELTAA;
			SET_RATIO_DELTAA;
			RESET_PLL_DIVA;
			break;
		case 4:
			RESET_GATEA;
			RESET_TRIGA;
			RESET_DELTAA;
			RESET_RATIO_DELTAA;
			SET_PLL_DIVA;
			break;

		}



	}
	else if (mode == 8) {
		logicOutB = (logicOutB + 1) % 5;
		holdLogicOut = (holdLogicOut & 0b1111111111000111) | (logicOutB << 3);

		ee_status = EE_WriteVariable(VirtAddVarTab[1], holdLogicOut);
	    ee_status|= EE_ReadVariable(VirtAddVarTab[1],  &VarDataTab[1]);

		switch (logicOutB) {
		case 0:
			SET_GATEB;
			RESET_TRIGB;
			RESET_DELTAB;
			RESET_RATIO_DELTAB;
			RESET_PLL_DIVB;
			break;
		case 1:
			RESET_GATEB;
			SET_TRIGB;
			RESET_DELTAA;
			RESET_RATIO_DELTAB;
			RESET_PLL_DIVB;
			break;
		case 2:
			RESET_GATEB;
			RESET_TRIGB;
			SET_DELTAB;
			RESET_RATIO_DELTAB;
			RESET_PLL_DIVB;
			break;
		case 3:
			RESET_GATEB;
			RESET_TRIGB;
			RESET_DELTAB;
			SET_RATIO_DELTAB;
			RESET_PLL_DIVB;
			break;
		case 4:
			RESET_GATEB;
			RESET_TRIGB;
			RESET_DELTAB;
			RESET_RATIO_DELTAB;
			SET_PLL_DIVB;
			break;
		}
	} else if (mode == 9) {

		autoDuty = (autoDuty + 1) % 2;
		holdLogicOut = (holdLogicOut & 0b1111111111000111) | (autoDuty << 6);

		if (autoDuty == autoDutyOn) {
			RESET_AUTODUTY;
		} else {
			SET_AUTODUTY;
		}

		ee_status = EE_WriteVariable(VirtAddVarTab[1], holdLogicOut);
	    ee_status|= EE_ReadVariable(VirtAddVarTab[1],  &VarDataTab[1]);



	}

	ee_status = EE_WriteVariable(VirtAddVarTab[0], holdState);
    ee_status|= EE_ReadVariable(VirtAddVarTab[0],  &VarDataTab[0]);

}

void showMode(uint32_t currentmode) {

	// if we are switching families, show a color corresponding to that family
	if ((modeflag == 5) || modeflag == 6) {
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



	if (familyIndicator < 8) {
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 4095);
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);
	}
	else {
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 4095);
	}

	switch (familyIndicator % 8) {
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
		displayNewMode = 0; // a bit of logic used to make sure that we show the mode during the main controlScheme
	}
}




