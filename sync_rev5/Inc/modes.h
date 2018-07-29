#ifndef MODES
#define MODES

// Mode enums and mode variables

#define SH_MODE button1Mode
#define SCALE_MODE button2Mode
#define X_MODE button3Mode
#define SYNC_MODE button4Mode
#define GROUP_MODE button5Mode
#define TABLE_MODE button6Mode
#define TABLE_GROUP_MODE aux1Mode


#define numButton1Modes 3
#define numButton2Modes 4
#define numButton3Modes 4
#define numButton4Modes 3
#define numButton5Modes 4
#define numButton6Modes 4
#define numAux1Modes 2
#define numAux2Modes 0
#define numAux3Modes 0

enum button1Modes {noSH, sampletrack, resample};
enum button2Modes {scale1, scale2, scale3, scale4};
enum button3Modes {root, pm, fm, pwm};
enum button4Modes {nosync, true, hardsync};
enum button5Modes {group1, group2, group3, group4};
enum button6Modes {table1, table2, table3, table4};
enum aux1Modes {groupSpecific, global};
//enum aux2Modes {};
//enum aux3Modes {};
//enum aux4Modes {};

enum button1Modes button1Mode;
enum button2Modes button2Mode;
enum button4Modes button3Mode;
enum button3Modes button4Mode;
enum button5Modes button5Mode;
enum button6Modes button6Mode;
enum aux1Modes aux1Mode;
//enum aux2Modes aux2Mode;
//enum aux3Modes aux3Mode;
//enum aux4Modes aux4Mode;

int familyIndicator;

#endif
