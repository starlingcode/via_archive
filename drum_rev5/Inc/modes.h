#ifndef MODES
#define MODES

// Mode enums and mode variables

#define SH_MODE button1Mode
#define TRIG_MODE button4Mode
#define FREQ_MODE button3Mode
#define LOOP_MODE button6Mode
#define LOGICA_MODE aux1Mode
#define LOGICB_MODE aux2Mode
#define DRUM_MODE aux3Mode

#define numButton1Modes 6
#define numButton4Modes 5
#define numButton3Modes 3
#define numButton6Modes 2
#define numAux1Modes 3
#define numAux2Modes 3
#define numAux3Modes 6

enum button1Modes {nosampleandhold, a, b, ab, halfdecimate, decimate};
enum button3Modes {audio, env, seq};
enum button4Modes {noretrigger, hardsync, nongatedretrigger, gated, pendulum};
enum button6Modes {noloop, looping};
enum aux1Modes {triggerA, gateA, deltaA};
enum aux2Modes {triggerB, gateB, deltaB};
enum aux3Modes {APM, AM, A, M, PM, P};

enum button1Modes button1Mode;
enum button4Modes button4Mode;
enum button3Modes button3Mode;
enum button6Modes button6Mode;
enum aux1Modes aux1Mode;
enum aux2Modes aux2Mode;
enum aux3Modes aux3Mode;

int familyIndicator;

#endif
