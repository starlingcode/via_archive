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
struct rgb orange = {4095, 4095, 0};
struct rgb magenta = {4095, 0, 4095};
struct rgb cyan = {0, 4095, 4095};

#define DOWNSENSOR MyTKeys[0].p_Data->StateId
#define XSENSOR MyTKeys[1].p_Data->StateId
#define SYNCSENSOR MyTKeys[2].p_Data->StateId
#define SCALESENSOR MyTKeys[3].p_Data->StateId
#define SHSENSOR MyTKeys[4].p_Data->StateId
#define UPSENSOR MyTKeys[5].p_Data->StateId

#define PRESSED TSL_STATEID_DETECT
#define RELEASED TSL_STATEID_RELEASE


// how modes are arranged by size and location in modeStateBuffer (formatted for EEPROM storage).

// up to 8 control types
#define XMASK 	  	  	0b0000000000000111

// up to 8 sync types
#define SYNCMASK 		0b0000000000111000
#define SYNCSHIFT 		3

// up to 16 scales per scaleType
#define SCALEMASK 		0b0000001111000000
#define SCALESHIFT		6

// up to 4 scaleTypes
#define SCALETYPEMASK	0b0000110000000000
#define SCALETYPESHIFT	10

// up to 8 sample & hold modes
#define SHMASK 			0x0b000000000000000111000000000000
#define SHSHIFT 		12

// up to 32 families
#define FAMILYMASK		0x0b000000000011111000000000000000
#define FAMILYSHIFT		15

// up to 8 logic A types
#define LOGICAMASK		0x0b000000011100000000000000000000
#define LOGICASHIFT		20

// up to 8 logic B types
#define LOGICBMASK		0x0b000011100000000000000000000000
#define LOGICBSHIFT		23

// 2 auto duty types
#define AUTODUTYMASK	0x0b000100000000000000000000000000
#define AUTODUTYSHIFT	26


#define DEFAULTPRESET1 0b0000000000000000
#define DEFAULTPRESET2 0b0000000000000000
#define DEFAULTPRESET3 0b0000000000000000
#define DEFAULTPRESET4 0b0000000000000000
#define DEFAULTPRESET5 0b0000000000000000
#define DEFAULTPRESET6 0b0000000000000000



