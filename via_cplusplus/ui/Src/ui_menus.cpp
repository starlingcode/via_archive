/*
 * ViaUI::menus.cpp
 *
 *  Created on: Sep 11, 2018
 *      Author: willmitchell
 */

#include "user_interface.hpp"

// UI timer
TIM_HandleTypeDef htim7;

void ViaUI::button1Menu(int sig) {
	switch (sig) {
	case ENTRY_SIG:
		button1EnterMenuCallback();

		break;

	case SENSOR_EVENT_SIG:
		if (BUTTON1SENSOR== RELEASED) {
			if(timerRead() < 3000) {
				button1TapCallback();
			} else {
				button1HoldCallback();
			}
		}
		break;
	}
}

void ViaUI::button2Menu(int sig) {
	switch (sig) {
	case ENTRY_SIG:
		button2EnterMenuCallback();

		break;

	case SENSOR_EVENT_SIG:
		if (BUTTON2SENSOR== RELEASED) {
			if(timerRead() < 3000) {
				button2TapCallback();
			} else {
				button2HoldCallback();
			}
		}
		break;
	}
}

void ViaUI::button3Menu(int sig) {
	switch (sig) {

	case ENTRY_SIG:
		button3EnterMenuCallback();
		break;

	case SENSOR_EVENT_SIG:
		if (BUTTON3SENSOR== RELEASED) {
			if(timerRead() < 3000) {
				button3TapCallback();
			} else {
				button3HoldCallback();
			}
		}
		break;

		case INIT_SIG:
		break;
	}
}

void ViaUI::button4Menu(int sig) {
	switch (sig) {
	case ENTRY_SIG:
		button4EnterMenuCallback();

		break;

	case SENSOR_EVENT_SIG:

		if (BUTTON4SENSOR== RELEASED) {
			if(timerRead() < 3000) {
				button4TapCallback();
			} else {
				button4HoldCallback();
			}
		}
		break;

		case INIT_SIG:
		break;

		default:
		break;
	}

}

void ViaUI::button5Menu(int sig) {
	switch (sig) {
	case ENTRY_SIG:
		button5EnterMenuCallback();
		break;

	case SENSOR_EVENT_SIG:

		// Check for entry into an aux mode
		if (BUTTON1SENSOR== PRESSED) {
			transition(&ViaUI::aux1Menu);
		} else if (BUTTON3SENSOR == PRESSED) {
			transition(&ViaUI::aux2Menu);
		} else if (BUTTON4SENSOR == PRESSED) {
			transition(&ViaUI::aux3Menu);
		} else if (BUTTON6SENSOR == PRESSED) {
			transition(&ViaUI::aux4Menu);
		} else if (BUTTON5SENSOR == RELEASED) {
			if(timerRead() < 3000) {
				button5TapCallback();
			} else {
				button5HoldCallback();
			}
		}
		break;
	}
}

void ViaUI::button6Menu(int sig) {
	switch (sig) {

	case ENTRY_SIG:
		button6EnterMenuCallback();
		break;

	case SENSOR_EVENT_SIG:
		if (BUTTON6SENSOR== RELEASED) {
			if(timerRead() < 3000) {
				button6TapCallback();
			} else {
				button6HoldCallback();
			}
		}
		break;

		case INIT_SIG:
		break;
	}
}

void ViaUI::aux1Menu(int sig) {
	switch (sig) {

	case ENTRY_SIG:
		aux1EnterMenuCallback();
		break;

	case SENSOR_EVENT_SIG:
		if (BUTTON1SENSOR== RELEASED) {
			if(timerRead() < 3000) {
				aux1TapCallback();
			} else {
				aux1HoldCallback();
			}
		}
		break;

		case INIT_SIG:
		break;
	}
}

void ViaUI::aux2Menu(int sig) {
	switch (sig) {

	case ENTRY_SIG:
		aux2EnterMenuCallback();
		break;

	case SENSOR_EVENT_SIG:
		if (BUTTON3SENSOR== RELEASED) {
			if(timerRead() < 3000) {
				aux2TapCallback();
			} else {
				aux2HoldCallback();
			}
		}
		break;

		case INIT_SIG:
		break;
	}
}

void ViaUI::aux3Menu(int sig) {
	switch (sig) {

	case ENTRY_SIG:
		aux3EnterMenuCallback();
		break;

	case SENSOR_EVENT_SIG:
		if (BUTTON4SENSOR== RELEASED) {
			if(timerRead() < 3000) {
				aux3TapCallback();
			} else {
				aux3HoldCallback();
			}
		}
		break;

		case INIT_SIG:
		break;
	}
}

void ViaUI::aux4Menu(int sig) {
	switch (sig) {

	case ENTRY_SIG:
		aux4EnterMenuCallback();
		break;

	case SENSOR_EVENT_SIG:
		if (BUTTON6SENSOR== RELEASED) {
			if(timerRead() < 3000) {
				aux4TapCallback();
			} else {
				aux4HoldCallback();
			}
		}
		break;

		case INIT_SIG:
		break;
	}
}

