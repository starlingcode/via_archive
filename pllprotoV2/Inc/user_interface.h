// dispatch a signal to current state
void uiDispatch(int sig) {(*State)(sig);}  // dispatch signal to state


/* signals used by the ui FSM */
enum
{	NULL_SIG,     // Null signal, all state functions should ignore this signal and return their parent state or NONE if it's the top level state
	ENTRY_SIG,    // Entry signal, a state function should perform its entry actions (if any)
	EXIT_SIG,	  // Exit signal, a state function should pEntry signal, a state function should perform its entry actions (if any)erform its exit actions (if any)
	INIT_SIG,     // Just look to global value and initialize, return to default state.  For recalling (presets, memory)
	TIMEOUT_SIG,  // timer timeout
	SENSOR_EVENT_SIG,  // Sensor state machine not busy, can be queried for events
	EXPAND_SW_ON_SIG,  // expander button depressed
	EXPAND_SW_OFF_SIG, // expander button released
	TSL_ERROR_SIG
};

struct rgb
{
	int r;	   		// 12-bit red amount RGB LED
	int g;	  		// 12-bit green amount RGB LED
	int b;	   		// 12-bit blue amount RGB LED
};


// shortcuts for commonly used colors!
struct rgb red = {4095, 0, 0};
struct rgb green = {0, 4095, 0};
struct rgb blue = {0, 0, 4095};

#define DOWNSENSOR MyTKeys[0].p_Data->StateId
#define XSENSOR MyTKeys[1].p_Data->StateId
#define SYNCSENSOR MyTKeys[2].p_Data->StateId
#define SCALESENSOR MyTKeys[3].p_Data->StateId
#define SHSENSOR MyTKeys[4].p_Data->StateId
#define UPSENSOR MyTKeys[5].p_Data->StateId

#define PRESSED TSL_STATEID_DETECT
#define RELEASED TSL_STATEID_RELEASE

/*
eepromStatus = EE_ReadVariable(VirtAddVarTab[0], &VarDataTab[0]);
holdState = VarDataTab[0];
eepromStatus = EE_ReadVariable(VirtAddVarTab[1], &VarDataTab[1]);
holdLogicOut = VarDataTab[1];
controlScheme = holdState & 0b0000000000000111;
scaleType = (holdState & 0b0000000011000000) >> 6;
syncMode = (holdState & 0b0000000000111000) >> 3;
sampleHoldMode = (holdState & 0b0000011100000000) >> 8;
familyIndicator = (holdState & 0b0111100000000000) >> 11;
logicOutA = holdLogicOut & 0b0000000000000111;
logicOutB = (holdLogicOut & 0b0000000000111000) >> 3;
*/

// how modes are arranged by size and location in modeStateBuffer (formatted for EEPROM storage).
#define XMASK 	    0b0000000000000111

#define SYNCMASK 	0b0000000000111000
#define SYNCSHIFT 	3

#define SCALEMASK 	0b0000000011000000
#define SCALESHIFT	6

#define SHMASK 		0x0b0000011100000000
#define SHSHIFT 	8

#define FAMILYMASK	0b0111100000000000
#define FAMILYSHIFT	11

#define LOGICAMASK	0b00000000000001110000000000000000
#define LOGICASHIFT	16

#define LOGICBMASK	0b00000000001110000000000000000000
#define LOGICBSHIFT	19
