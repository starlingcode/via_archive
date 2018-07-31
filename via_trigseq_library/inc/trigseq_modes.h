#ifndef MODES
#define MODES

// Mode enums and mode variables

#define SH_A_MODE button1Mode
#define AND_A_MODE button2Mode
#define A_PATTERN_BANK button3Mode
#define SH_B_MODE button4Mode
#define AND_B_MODE button5Mode
#define B_PATTERN_BANK button6Mode

#define AUX2_MODE_USED
#define LOGIC_MODE aux2Mode

#define numButton1Modes 3
#define numButton2Modes 2
#define numButton3Modes 8
#define numButton4Modes 3
#define numButton5Modes 2
#define numButton6Modes 8
#define numAux1Modes 0
#define numAux2Modes 4
#define numAux3Modes 0
#define numAux4Modes 0

enum button1Modes {aNoSH, aResample, aSampleTrack};
enum button2Modes {andAoff, andAon};
enum button3Modes {aPatternBankSelections};
enum button4Modes {bNoSH, bResample, bSampleTrack};
enum button5Modes {andBoff, andBon};
enum button6Modes {bPatternBankSelections};
enum aux1Modes {aux1NotUsed};
enum aux2Modes {and, or, xor, nand};
enum aux3Modes {aux3NotUsed};
enum aux4Modes {aux4NotUsed};

#endif
