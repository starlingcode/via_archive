#include "main_state_machine.h"
#include "dsp.h"
#include "main.h"
#include "user_interface.h"
#include "via_rev5_hardware_io.h"

enum
{	NULL_SIG,     // Null signal, all state functions should ignore this signal and return their parent state or NONE if it's the top level state
	ENTRY_SIG,    // Entry signal, a state function should perform its entry actions (if any)
	EXIT_SIG,	  // Exit signal, a state function should pEntry signal, a state function should perform its entry actions (if any)erform its exit actions (if any)
	INIT_SIG,     // Just look to global value and initialize, return to default state.  For recalling (presets, memory)
	TIMEOUT_SIG,// timer timeout
	SENSOR_EVENT_SIG,  // Sensor state machine not busy, can be queried for events
	EXPAND_SW_ON_SIG,  // expander button depressed
	EXPAND_SW_OFF_SIG, // expander button released
	TSL_ERROR_SIG
};

int gateSignal;
int triggerSignal;
