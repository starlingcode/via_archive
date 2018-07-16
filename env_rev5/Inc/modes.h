#ifndef MODES
#define MODES

// Mode enums and mode variables

#define ATTACK_SHAPE button1Mode
#define LOOP_MODE button2Mode
#define RELEASE_SHAPE button3Mode
#define SHA_MODE button6Mode
#define TRIG_MODE button5Mode
#define SHB_MODE button4Mode

#define numButton1Modes 4
#define numButton5Modes 5
#define numButton4Modes 3
#define numButton3Modes 4
#define numButton2Modes 2
#define numButton6Modes 3

enum button1Modes {attackA, attackB, attackWildcard1, attackWildcard2};
enum button2Modes {noloop, looping};
enum button3Modes {releaseA, releaseB, releaseWildcard1, releaseWildcard2};
enum button6Modes {shANone, shAHalf, shAFull};
enum button5Modes {noretrigger, hardsync, nongatedretrigger, gated, pendulum};
enum button4Modes {shBNone, shBHalf, shBFull};

enum button1Modes button1Mode;
enum button2Modes button2Mode;
enum button3Modes button3Mode;
enum button4Modes button4Mode;
enum button5Modes button5Mode;
enum button6Modes button6Mode;



#endif
