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

// how modes are arranged by size and location in modeStateBuffer (formatted for EEPROM storage).
#define LOOPMASK 	0x01

#define SPEEDMASK 	0x06
#define SPEEDSHIFT	1

#define TRIGMASK 	0x38
#define TRIGSHIFT 	3

#define SHMASK 		0x1C0
#define SHSHIFT 	6

#define FAMILYMASK	0xE00
#define FAMILYSHIFT	9

#define LOGICAMASK	0x3000
#define LOGICASHIFT	12

#define LOGICBMASK	0xC000
#define LOGICBSHIFT	14

#define DRUMMASK	0x30000
#define DRUMSHIFT	16
