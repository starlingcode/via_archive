typedef short Signal;
typedef struct Event Event;
typedef struct Hsm Hsm;



////state is stored as a pointer to the current state function
//typedef void (*State)(int const *);
//
//// Event base class
//struct Event
//{
//   Signal sig; // passed to state machine to message an event
//};
//
//// Finite State Machine base class
//struct Hsm
//{
//   State state__; // the current state
//};
//
//// inlined methods of Hsm class
//#define HsmConstructor(me_, init_) ((me_)->state__ = (State)(init_))
//#define HsmInit(me_, e_)     (*(me_)->state__)((me_), (e_))
//
////dispatches SIGnals to state machine
//#define HsmDispatch(me_, e_) (*(me_)->state__)((me_), (e_))

void uiDispatch(int);

// triggers optional exit and entry behavior for state transition out/in

/* signals used by the ui FSM */
enum
{	NULL_SIG,     // Null signal, all state functions should ignore this signal and return their parent state or NONE if it's the top level state
	ENTRY_SIG,    // Entry signal, a state function should perform its entry actions (if any)
	EXIT_SIG,	  // Exit signal, a state function should pEntry signal, a state function should perform its entry actions (if any)erform its exit actions (if any)
	INIT_SIG,     // Just look to global value and initialize, return to default state.  For recalling (presets, memory)
	TIMEOUT_SIG,  // timer timeout
	SENSOR_EVENT_SIG,  // Sensor state machine not busy, can be queried for events
	TSL_ERROR_SIG
};
