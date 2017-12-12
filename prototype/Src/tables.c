#include "tables.h"

#include "main.h"

#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"

// helper function to load the selected family to ram
void loadSampleArray(Family);

// we store our family stuct pointers here
Family familyArray[3][8];

// helpful variable we can use for the currently selected family struct
Family currentFamily;

// we need to have access to the speed flag in order to determine the correct family
enum speedTypes speed;

// these variables are used to represent the number of entries in a given wavetable stored in the currently selected family
// they are shared by tim6IRQ
extern uint32_t span;
extern int spanx2;
extern int tableSizeCompensation;

// these variables are used to represent the number of wavetables in the currently selected family when performing our morph function
extern uint32_t morphBitShiftRight;
extern uint32_t morphBitShiftLeft;

// fill our family structs with the arrays declared in the header
// length and size are declared here in accordance with the chosen arrays

Family moogShifted =
	{.attackFamily = moogShiftedAttackFamily,
	.releaseFamily = moogShiftedReleaseFamily,
	.tableLength = 64,
	.familySize = 9};

Family moogNormalized =
	{.attackFamily = moogNormalizedAttackFamily,
	.releaseFamily = moogNormalizedReleaseFamily,
	.tableLength = 64,
	.familySize = 9};

Family moogSquare =
	{.attackFamily = moogSquareShiftAttackFamily,
	.releaseFamily = moogSquareShiftReleaseFamily,
	.tableLength = 64,
	.familySize = 9};

Family moogInverted =
	{.attackFamily = moogInvertedAttackFamily,
	.releaseFamily = moogInvertedReleaseFamily,
	.tableLength = 64,
	.familySize = 9};

Family perlin =
	{.attackFamily = perlinAttackFamily,
	.releaseFamily = perlinReleaseFamily,
	.tableLength = 64,
	.familySize = 9};

Family sineFold =
	{.attackFamily = sinefoldAttackFamily,
	.releaseFamily = sinefoldReleaseFamily,
	.tableLength = 64,
	.familySize = 9};

Family bounce =
	{.attackFamily = bounceAttackFamily,
	.releaseFamily = bounceReleaseFamily,
	.tableLength = 64,
	.familySize = 9};

Family triodd =
	{.attackFamily = trioddAttackFamily,
	.releaseFamily = trioddReleaseFamily,
	.tableLength = 64,
	.familySize = 9};

Family triOdd =
	{.attackFamily = trioddAttackFamily,
	.releaseFamily = trioddReleaseFamily,
	.tableLength = 64,
	.familySize = 9};

Family triFudge =
	{.attackFamily = trifudgeAttackFamily,
	.releaseFamily = trifudgeReleaseFamily,
	.tableLength = 64,
	.familySize = 9};

Family moog1 =
	{.attackFamily = moog1AttackFamily,
	.releaseFamily = moog1ReleaseFamily,
	.tableLength = 64,
	.familySize = 9};

Family moog2 =
	{.attackFamily = moog2AttackFamily,
	.releaseFamily = moog2ReleaseFamily,
	.tableLength = 64,
	.familySize = 9};

Family sawBend =
	{.attackFamily = sawBendAttackFamily,
	.releaseFamily = sawBendReleaseFamily,
	.tableLength = 4,
	.familySize = 5};

Family exciteBike =
	{.attackFamily = exciteBikeAttackFamily,
	.releaseFamily = exciteBikeReleaseFamily,
	.tableLength = 8,
	.familySize = 9};

Family rand =
	{.attackFamily = randAttackFamily,
	.releaseFamily = randReleaseFamily,
	.tableLength = 8,
	.familySize = 33};

Family gauss =
	{.attackFamily = gaussAttackFamily,
	.releaseFamily = gaussReleaseFamily,
	.tableLength = 8,
	.familySize = 33};

Family gauss_noconform =
	{.attackFamily = gauss_noconformAttackFamily,
	.releaseFamily = gauss_noconformReleaseFamily,
	.tableLength = 8,
	.familySize = 33};

Family gauss_low =
	{.attackFamily = gauss_lowAttackFamily,
	.releaseFamily = gauss_lowReleaseFamily,
	.tableLength = 8,
	.familySize = 33};

Family gauss_low_noconform =
	{.attackFamily = gauss_low_noconformAttackFamily,
	.releaseFamily = gauss_low_noconformReleaseFamily,
	.tableLength = 8,
	.familySize = 33};

Family algerian =
	{.attackFamily = algerianAttackFamily,
	.releaseFamily = algerianReleaseFamily,
	.tableLength = 64,
	.familySize = 5};

Family quartSym =
	{.attackFamily = quartSymAttackFamily,
	.releaseFamily = quartSymReleaseFamily,
	.tableLength = 64,
	.familySize = 9};

Family quartAsym =
	{.attackFamily = quartAsymAttackFamily,
	.releaseFamily = quartAsymReleaseFamily,
	.tableLength = 64,
	.familySize = 9};

Family superEllipse1Sym =
	{.attackFamily = superEllipse1SymAttackFamily,
	.releaseFamily = superEllipse1SymReleaseFamily,
	.tableLength = 64,
	.familySize = 5};

Family superEllipse1Asym =
	{.attackFamily = superEllipse1AsymAttackFamily,
	.releaseFamily = superEllipse1AsymReleaseFamily,
	.tableLength = 64,
	.familySize = 5};

Family gammaSym =
	{.attackFamily = gammaSymAttackFamily,
	.releaseFamily = gammaSymReleaseFamily,
	.tableLength = 64,
	.familySize = 9};

Family gammaAsym =
	{.attackFamily = gammaAsymAttackFamily,
	.releaseFamily = gammaAsymReleaseFamily,
	.tableLength = 64,
	.familySize = 9};

Family sharpExpoSym =
	{.attackFamily = sharpExpoSymAttackFamily,
	.releaseFamily = sharpExpoSymReleaseFamily,
	.tableLength = 64,
	.familySize = 9};

Family sharpExpoAsym =
	{.attackFamily = sharpExpoAsymAttackFamily,
	.releaseFamily = sharpExpoAsymReleaseFamily,
	.tableLength = 64,
	.familySize = 9};

Family sharpLinSym =
	{.attackFamily = sharpLinSymAttackFamily,
	.releaseFamily = sharpLinSymReleaseFamily,
	.tableLength = 64,
	.familySize = 9};

Family sharpLinAsym =
	{.attackFamily = sharpLinAsymAttackFamily,
	.releaseFamily = sharpLinAsymReleaseFamily,
	.tableLength = 64,
	.familySize = 9};

Family ascendingAdditiveClamp =
	{.attackFamily = ascendingAdditiveClampAttackFamily,
	.releaseFamily = ascendingAdditiveClampReleaseFamily,
	.tableLength = 64,
	.familySize = 9};

Family summingAdditiveClamp =
	{.attackFamily = summingAdditiveClampAttackFamily,
	.releaseFamily = summingAdditiveClampReleaseFamily,
	.tableLength = 64,
	.familySize = 9};

Family moogImpossibleTri =
	{.attackFamily = moogImpossibleTriAttackFamily,
	.releaseFamily = moogImpossibleTriReleaseFamily,
	.tableLength = 64,
	.familySize = 9};

Family steps =
	{.attackFamily = stepsAttackFamily,
	.releaseFamily = stepsReleaseFamily,
	.tableLength = 64,
	.familySize = 9};

Family additive16Circular =
	{.attackFamily = additive_16_circular1AttackFamily,
	.releaseFamily = additive_16_circular1ReleaseFamily,
	.tableLength = 128,
	.familySize = 9};

Family perlin130_1 =
	{.attackFamily = perlin130_1_noskewAttackFamily,
	.releaseFamily = perlin130_1_noskewReleaseFamily,
	.tableLength = 128,
	.familySize = 9};

Family perlin130_2 =
	{.attackFamily = perlin130_2_noskewAttackFamily,
	.releaseFamily = perlin130_2_noskewReleaseFamily,
	.tableLength = 128,
	.familySize = 9};

Family perlin130_3 =
	{.attackFamily = perlin130_3_noskewAttackFamily,
	.releaseFamily = perlin130_3_noskewReleaseFamily,
	.tableLength = 128,
	.familySize = 9};

Family perlin130_4 =
	{.attackFamily = perlin130_4_noskewAttackFamily,
	.releaseFamily = perlin130_4_noskewReleaseFamily,
	.tableLength = 128,
	.familySize = 9};

Family perlin130_5 =
	{.attackFamily = perlin130_5_noskewAttackFamily,
	.releaseFamily = perlin130_5_noskewReleaseFamily,
	.tableLength = 128,
	.familySize = 9};

Family imp33 =
	{.attackFamily = imp,
	.releaseFamily = imp,
	.tableLength = 64,
	.familySize = 33};

Family impevens =
	{.attackFamily = impshort,
	.releaseFamily = impshort,
	.tableLength = 64,
	.familySize = 17};

Family tenor129 =
	{.attackFamily = tenor129AttackFamily,
	.releaseFamily = tenor129ReleaseFamily,
	.tableLength = 128,
	.familySize = 5};

Family tenor64 =
	{.attackFamily = tenor64AttackFamily,
	.releaseFamily = tenor64ReleaseFamily,
	.tableLength = 128,
	.familySize = 5};

Family tenor32 =
	{.attackFamily = tenor32AttackFamily,
	.releaseFamily = tenor32ReleaseFamily,
	.tableLength = 128,
	.familySize = 5};

Family tenor16 =
	{.attackFamily = tenor16AttackFamily,
	.releaseFamily = tenor16ReleaseFamily,
	.tableLength = 128,
	.familySize = 5};

// specify the family in our family bank per speed

void fillFamilyArray(void) {

	familyArray[audio][0] = impevens;
	familyArray[audio][1] = ascendingAdditiveClamp;
	familyArray[audio][2] = perlin130_1;
	familyArray[audio][3] = tenor64;
	familyArray[audio][4] = perlin130_5;
	familyArray[audio][5] = triOdd;
	familyArray[audio][6] = moogImpossibleTri;
	familyArray[audio][7] = moogSquare;

	familyArray[env][0] = sawBend;
	familyArray[env][1] = bounce;
	familyArray[env][2] = quartSym;
	familyArray[env][3] = quartAsym;
	familyArray[env][4] = superEllipse1Sym;
	familyArray[env][5] = superEllipse1Asym;
	familyArray[env][6] = impevens;
	familyArray[env][7] = exciteBike;

	familyArray[seq][0] = steps;
	familyArray[seq][1] = triOdd;
	familyArray[seq][2] = bounce;
	familyArray[seq][3] = sawBend;
	familyArray[seq][4] = gammaSym;
	familyArray[seq][5] = gammaAsym;
	familyArray[seq][6] = perlin130_5;
	familyArray[seq][7] = summingAdditiveClamp;

	currentFamily = familyArray[0][0];
	switchFamily();

}

// this sets the flags to be used in the interrupt and also fills the holding array on the heap

void switchFamily(void) {
	currentFamily = familyArray[speed][familyIndicator];

	holdState |= familyIndicator << 9;

	currentFamily = familyArray[speed][familyIndicator];
	loadSampleArray(currentFamily);

	span = (currentFamily.tableLength) << 16;
	spanx2 = (currentFamily.tableLength) << 17;
	switch (currentFamily.familySize) {
	// these are values that properly allow us to select a family and interpolation fraction for our morph
	case 5:
		morphBitShiftRight = 10;
		morphBitShiftLeft = 6;
		break;

	case 9:
		morphBitShiftRight = 9;
		morphBitShiftLeft = 7;
		break;

	case 17:
		morphBitShiftRight = 8;
		morphBitShiftLeft = 8;
		break;

	case 33:
		morphBitShiftRight = 7;
		morphBitShiftLeft = 9;
		break;

	}
	switch (currentFamily.tableLength) {
	// these are values that properly allow us to select a family and interpolation fraction for our morph
	case 4:
		tableSizeCompensation = 5;
		break;

	case 8:
		tableSizeCompensation = 4;
		break;

	case 16:
		tableSizeCompensation = 3;
		break;

	case 32:
		tableSizeCompensation = 2;
		break;

	case 64:
		tableSizeCompensation = 1;
		break;

	case 128:
		tableSizeCompensation = 0;

	}
}

//this actually shuttles the data from flash to ram and fills our holding array

void loadSampleArray(Family family) {

	uint16_t **currentFamilyPointer;

	for (int i = 0; i < family.familySize; i++) {
		for (int j = 0; j <= family.tableLength; j++) {
			// this just gets the appropriate samples and plops them into the global holding arrays
			currentFamilyPointer = family.attackFamily + i;
			attackHoldArray[i][j] = *(*(currentFamilyPointer) + j);

			currentFamilyPointer = family.releaseFamily + i;
			releaseHoldArray[i][j] = *(*(currentFamilyPointer) + j);
		}
	}
}

