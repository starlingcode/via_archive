
void (*State)(int);

// dispatch a signal to current state
void uiDispatch(int);  // dispatch signal to state


uint32_t eepromStatus;


#define DOWNSENSOR MyTKeys[0].p_Data->StateId
#define LOOPSENSOR MyTKeys[1].p_Data->StateId
#define TRIGSENSOR MyTKeys[2].p_Data->StateId
#define FREQSENSOR MyTKeys[3].p_Data->StateId
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

#define DRUMMASK	0x70000
#define DRUMSHIFT	16

#define DEFAULTPRESET1 0b0000000000000000
#define DEFAULTPRESET2 0b0000000000000000
#define DEFAULTPRESET3 0b0000000000000000
#define DEFAULTPRESET4 0b0000000000000000
#define DEFAULTPRESET5 0b0000000000000000
#define DEFAULTPRESET6 0b0000000000000000

