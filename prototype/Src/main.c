/**
 ******************************************************************************
 * File Name          : main.c
 * Description        : Main program body
 ******************************************************************************
 ** This notice applies to any and all portions of this file
 * that are not between comment pairs USER CODE BEGIN and
 * USER CODE END. Other portions of this file, whether
 * inserted by the user or by software development tools
 * are owned by their respective copyright owners.
 *
 * COPYRIGHT(c) 2017 STMicroelectronics
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of STMicroelectronics nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************
 */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f3xx_hal.h"

/* USER CODE BEGIN Includes */

#include "tables.h"
#include "tsl_user.h"
#include "eeprom.h"

/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;
ADC_HandleTypeDef hadc2;
ADC_HandleTypeDef hadc3;
DMA_HandleTypeDef hdma_adc1;
DMA_HandleTypeDef hdma_adc2;
DMA_HandleTypeDef hdma_adc3;

DAC_HandleTypeDef hdac;

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim4;
TIM_HandleTypeDef htim6;
TIM_HandleTypeDef htim7;
TIM_HandleTypeDef htim8;
TIM_HandleTypeDef htim15;

TSC_HandleTypeDef htsc;

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

// this is part of the user code needed to run the STM32 touch sense library
tsl_user_status_t tsl_status;

// these variables are passed between our functions that read the touch sensors and change modes
uint32_t modeflag;
uint32_t detectOn;
uint32_t lastDetect;
uint32_t displayNewMode;

uint32_t holdState;

uint16_t VirtAddVarTab[NB_OF_VAR] = {0x5555};
uint16_t VarDataTab[NB_OF_VAR] = {0};
uint16_t VarValue,VarDataTmp;



// these variables are used to represent the number of entries in a given wavetable stored in the currently selected family
extern uint32_t span;
extern int spanx2;
extern int tableSizeCompensation;

// these variables are used to represent the number of wavetables in the currently selected family when performing our morph function
extern uint32_t morphBitShiftRight;
extern uint32_t morphBitShiftLeft;

// these logic flags are used to communicate state between the main loop and the interrupts

extern int incSign;



// here we initialize the "Family" structs for all of the wavetables that we will fill upon initialization
Family moog1;
Family moog2;
Family triFudge;
Family triOdd;
Family triFold;
Family bounce;
Family sineFold;
Family perlin;
Family sawBend;
Family exciteBike;
Family rand;
Family gauss;
Family gauss_noconform;
Family gauss_low;
Family gauss_low_noconform;
Family algerian;
Family gammaSym;
Family gammaAsym;
Family sharpExpoSym;
Family sharpExpoAsym;
Family sharpLinSym;
Family sharpLinAsym;
Family quartSym;
Family quartAsym;
Family superEllipse1Sym;
Family superEllipse1Asym;
Family moogShifted;
Family moogNormalized;
Family moogInverted;
Family moogImpossible;
Family moogSquare;
Family summingAdditiveClamp;
Family ascendingAdditiveClamp;
Family steps;
Family moogImpossibleTri;

extern Family currentFamily;

// The following large chunk of code declares our wavetables as 15 bit integers.
// Notice how several related wavetables are declared in each subsection.
// This forms the basis for our "morph", or bi-interpolation
//
//const uint16_t sineFoldCtr2[65] =
//{0,2116,4367,6748,9247,11853,14549,17315,20128,22964,25794,28590,31320,33954,36460,38805,40959,42892,44573,45978,47080,47860,48299,48381,48097,47440,46407,45000,43228,41100,38633,35847,32768,29688,26902,24435,22307,20535,19128,18095,17438,17154,17236,17675,18455,19557,20962,22643,24576,26730,29075,31581,34215,36945,39741,42571,45407,48220,50986,53682,56288,58787,61168,63419,65535};
//const uint16_t sineFoldCtr3[65] =
//{0,1816,3184,4149,4784,5183,5460,5738,6144,6801,7819,9290,11279,13820,16914,20523,24576,28964,33549,38169,42641,46775,50380,53275,55295,56307,56213,54956,52529,48977,44395,38928,32768,26607,21140,16558,13006,10579,9322,9228,10240,12260,15155,18760,22894,27366,31986,36571,40959,45012,48621,51715,54256,56245,57716,58734,59391,59797,60075,60352,60751,61386,62351,63719,65535};
//const uint16_t sineFoldCtr4[65] =
//{0,2313,5106,8231,11464,14535,17162,19089,20128,20184,19277,17552,15265,12771,10480,8821,8192,8909,11170,15017,20322,26788,33962,41278,48097,53776,57728,59482,58745,55434,49706,41950,32768,23585,15829,10101,6790,6053,7807,11759,17438,24257,31573,38747,45213,50518,54365,56626,57343,56714,55055,52764,50270,47983,46258,45351,45407,46446,48373,51000,54071,57304,60429,63222,65535};
//const uint16_t sineFoldCtr5[65] =
//{0,1624,2520,3018,3584,4710,6791,10025,14336,19367,24520,29062,32256,33514,32537,29398,24576,18906,13462,9385,7680,9029,13638,21163,30720,40996,50441,57511,60927,59915,54361,44883,32768,20652,11174,5620,4608,8024,15094,24539,34815,44372,51897,56506,57855,56150,52073,46629,40959,36137,32998,32021,33279,36473,41015,46168,51199,55510,58744,60825,61951,62517,63015,63911,65535};
//const uint16_t sineFoldCtr6[65] =
//{0,2499,5671,8913,11464,12688,12334,10687,8543,7021,7237,9949,15265,22520,30364,37066,40959,40920,36736,29267,20322,12273,7473,7638,13342,23768,36810,49507,58745,62032,58182,47699,32768,17836,7353,3503,6790,16028,28725,41767,52193,57897,58062,53262,45213,36268,28799,24615,24576,28469,35171,43015,50270,55586,58298,58514,56992,54848,53201,52847,54071,56622,59864,63036,65535};
//const uint16_t sineFoldCtr7[65] =
//{0,1447,2076,2843,4784,8441,13487,18728,22528,23502,21198,16458,11279,8160,9155,14986,24576,35239,43524,46441,42641,33091,20947,10593,6144,9914,21427,37361,52529,61604,61021,50371,32768,15164,4514,3931,13006,28174,44108,55621,59391,54942,44588,32444,22894,19094,22011,30296,40959,50549,56380,57375,54256,49077,44337,42033,43007,46807,52048,57094,60751,62692,63459,64088,65535};
//const uint16_t sineFoldCtr8[65] =
//{0,2666,5977,8565,9247,7954,6027,5634,8543,14936,22969,29435,31320,27491,19603,11646,8192,12111,22900,36531,47080,49473,42083,27867,13342,5723,9479,23942,43228,58669,62769,52873,32768,12662,2766,6866,22307,41593,56056,59812,52193,37668,23452,16062,18455,29004,42635,53424,57343,53889,45932,38044,34215,36100,42566,50599,56992,59901,59508,57581,56288,56970,59558,62869,65535};
//const uint16_t sineFoldCtr9[65] =
//{0,1292,1920,3684,7680,13060,17280,17836,14336,9323,7040,10691,19968,30629,36735,34381,24576,13258,8064,13602,28160,44101,52095,46829,30720,13098,4992,12418,32256,53477,63359,55182,32768,10353,2176,12058,33279,53117,60543,52437,34815,18706,13440,21434,37375,51933,57471,52277,40959,31154,28800,34906,45567,54844,58495,56212,51199,47699,48255,52475,57855,61851,63615,64243,65535};




Family familyArray[16];
uint32_t familyIndicator;
extern Family currentFamily;

// these enums contain our mode information
enum speedTypes speed; // {audio, env, seq}
enum loopTypes loop; // {noloop, looping}
enum trigModeTypes trigMode; // {noretrigger, hardsync, nongatedretrigger, gated, pendulum}
enum sampleHoldModeTypes sampleHoldMode; // {nosampleandhold, a, b, ab, antidecimate, decimate}


// initialize the arrays that will be used by DMA to store our Knob and CV values
extern uint32_t ADCReadings1[4];
extern uint32_t ADCReadings2[2];
extern uint32_t ADCReadings3[1];

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_ADC1_Init(void);
static void MX_ADC2_Init(void);
static void MX_ADC3_Init(void);
static void MX_DAC_Init(void);
static void MX_TIM1_Init(void);
static void MX_TSC_Init(void);
static void MX_TIM2_Init(void);
static void MX_TIM6_Init(void);
static void MX_TIM7_Init(void);
static void MX_TIM8_Init(void);
static void MX_TIM4_Init(void);
static void MX_TIM3_Init(void);
static void MX_TIM15_Init(void);

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/
void readDetect(void);
void readRelease(uint32_t);
void handleRelease(uint32_t);
void changeMode(uint32_t);
void showMode(uint32_t);
void familyRGB(void);
void restoreDisplay(void);
void clearLEDs(void);
void restoreState(void);
//uint32_t saveState(void);
/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

int main(void) {

	/* USER CODE BEGIN 1 */
	uint32_t ee_status;
	/* USER CODE END 1 */

	/* MCU Configuration----------------------------------------------------------*/

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* USER CODE BEGIN Init */

	/* USER CODE END Init */

	/* Configure the system clock */
	SystemClock_Config();

	/* USER CODE BEGIN SysInit */

	/* USER CODE END SysInit */

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	MX_DMA_Init();
	MX_ADC1_Init();
	MX_ADC2_Init();
	MX_ADC3_Init();
	MX_DAC_Init();
	MX_TIM1_Init();
	MX_TSC_Init();
	MX_TIM2_Init();
	MX_TIM6_Init();
	MX_TIM7_Init();
	MX_TIM8_Init();
	MX_TIM4_Init();
	MX_TIM3_Init();
	MX_TIM15_Init();

	/* USER CODE BEGIN 2 */
	//define our wavetable family as two arrays of wavetables as defined above, one for attack, one for release

//	Family sineFoldCtr;
//
//	const uint16_t *sineFoldCtrAttackFamily[9] =
//	{sine, sineFoldCtr2, sineFoldCtr3,
//	sineFoldCtr4, sineFoldCtr5, sineFoldCtr6,
//	sineFoldCtr7, sineFoldCtr8, sineFoldCtr9};
//
//	const uint16_t *sineFoldCtrReleaseFamily[9] =
//	{sine, sineFoldCtr2, sineFoldCtr3,
//	sineFoldCtr4, sineFoldCtr5, sineFoldCtr6,
//	sineFoldCtr7, sineFoldCtr8, sineFoldCtr9};
//
//	sineFoldCtr.attackFamily = sineFoldCtrAttackFamily;
//	sineFoldCtr.releaseFamily = sineFoldCtrReleaseFamily;
//	sineFoldCtr.tableLength = 64;
//	sineFoldCtr.familySize = 9;

	// fill all the family structs stored above with the arrays of arrays that we just defined
	// "load them into the UI" by declaring a position for them in our "familyArray" index

	moogShifted.attackFamily = moogShiftedAttackFamily;
	moogShifted.releaseFamily = moogShiftedReleaseFamily;
	moogShifted.tableLength = 64;
	moogShifted.familySize = 9;


	moogNormalized.attackFamily = moogNormalizedAttackFamily;
	moogNormalized.releaseFamily = moogNormalizedReleaseFamily;
	moogNormalized.tableLength = 64;
	moogNormalized.familySize = 9;


	moogSquare.attackFamily = moogSquareShiftAttackFamily;
	moogSquare.releaseFamily = moogSquareShiftReleaseFamily;
	moogSquare.tableLength = 64;
	moogSquare.familySize = 9;


	moogInverted.attackFamily = moogInvertedAttackFamily;
	moogInverted.releaseFamily = moogInvertedReleaseFamily;
	moogInverted.tableLength = 64;
	moogInverted.familySize = 9;


	perlin.attackFamily = perlinAttackFamily;
	perlin.releaseFamily = perlinReleaseFamily;
	perlin.tableLength = 64;
	perlin.familySize = 9;


	sineFold.attackFamily = sinefoldAttackFamily;
	sineFold.releaseFamily = sinefoldReleaseFamily;
	sineFold.tableLength = 64;
	sineFold.familySize = 9;


	bounce.attackFamily = bounceAttackFamily;
	bounce.releaseFamily = bounceReleaseFamily;
	bounce.tableLength = 64;
	bounce.familySize = 9;


	triFold.attackFamily = trifoldAttackFamily;
	triFold.releaseFamily = trifoldReleaseFamily;
	triFold.tableLength = 64;
	triFold.familySize = 9;


	triOdd.attackFamily = trioddAttackFamily;
	triOdd.releaseFamily = trioddReleaseFamily;
	triOdd.tableLength = 64;
	triOdd.familySize = 9;


	triFudge.attackFamily = trifudgeAttackFamily;
	triFudge.releaseFamily = trifudgeReleaseFamily;
	triFudge.tableLength = 64;
	triFudge.familySize = 9;


	moog1.attackFamily = moog1AttackFamily;
	moog1.releaseFamily = moog1ReleaseFamily;
	moog1.tableLength = 64;
	moog1.familySize = 9;


	moog2.attackFamily = moog2AttackFamily;
	moog2.releaseFamily = moog2ReleaseFamily;
	moog2.tableLength = 64;
	moog2.familySize = 9;


	sawBend.attackFamily = sawBendAttackFamily;
	sawBend.releaseFamily = sawBendReleaseFamily;
	sawBend.tableLength = 4;
	sawBend.familySize = 5;


	exciteBike.attackFamily = exciteBikeAttackFamily;
	exciteBike.releaseFamily = exciteBikeReleaseFamily;
	exciteBike.tableLength = 8;
	exciteBike.familySize = 9;


	rand.attackFamily = randAttackFamily;
	rand.releaseFamily = randReleaseFamily;
	rand.tableLength = 8;
	rand.familySize = 33;


	gauss.attackFamily = gaussAttackFamily;
	gauss.releaseFamily = gaussReleaseFamily;
	gauss.tableLength = 8;
	gauss.familySize = 33;


	gauss_noconform.attackFamily = gauss_noconformAttackFamily;
	gauss_noconform.releaseFamily = gauss_noconformReleaseFamily;
	gauss_noconform.tableLength = 8;
	gauss_noconform.familySize = 33;


	gauss_low.attackFamily = gauss_lowAttackFamily;
	gauss_low.releaseFamily = gauss_lowReleaseFamily;
	gauss_low.tableLength = 8;
	gauss_low.familySize = 33;


	gauss_low_noconform.attackFamily = gauss_low_noconformAttackFamily;
	gauss_low_noconform.releaseFamily = gauss_low_noconformReleaseFamily;
	gauss_low_noconform.tableLength = 8;
	gauss_low_noconform.familySize = 33;


	algerian.attackFamily = algerianAttackFamily;
	algerian.releaseFamily = algerianReleaseFamily;
	algerian.tableLength = 64;
	algerian.familySize = 5;


	quartSym.attackFamily = quartSymAttackFamily;
	quartSym.releaseFamily = quartSymReleaseFamily;
	quartSym.tableLength = 64;
	quartSym.familySize = 9;


	quartAsym.attackFamily = quartAsymAttackFamily;
	quartAsym.releaseFamily = quartAsymReleaseFamily;
	quartAsym.tableLength = 64;
	quartAsym.familySize = 9;


	superEllipse1Sym.attackFamily = superEllipse1SymAttackFamily;
	superEllipse1Sym.releaseFamily = superEllipse1SymReleaseFamily;
	superEllipse1Sym.tableLength = 64;
	superEllipse1Sym.familySize = 5;


	superEllipse1Asym.attackFamily = superEllipse1AsymAttackFamily;
	superEllipse1Asym.releaseFamily = superEllipse1AsymReleaseFamily;
	superEllipse1Asym.tableLength = 64;
	superEllipse1Asym.familySize = 5;


	gammaSym.attackFamily = gammaSymAttackFamily;
	gammaSym.releaseFamily = gammaSymReleaseFamily;
	gammaSym.tableLength = 64;
	gammaSym.familySize = 9;


	gammaAsym.attackFamily = gammaAsymAttackFamily;
	gammaAsym.releaseFamily = gammaAsymReleaseFamily;
	gammaAsym.tableLength = 64;
	gammaAsym.familySize = 9;


	sharpExpoSym.attackFamily = sharpExpoSymAttackFamily;
	sharpExpoSym.releaseFamily = sharpExpoSymReleaseFamily;
	sharpExpoSym.tableLength = 64;
	sharpExpoSym.familySize = 9;


	sharpExpoAsym.attackFamily = sharpExpoAsymAttackFamily;
	sharpExpoAsym.releaseFamily = sharpExpoAsymReleaseFamily;
	sharpExpoAsym.tableLength = 64;
	sharpExpoAsym.familySize = 9;


	sharpLinSym.attackFamily = sharpLinSymAttackFamily;
	sharpLinSym.releaseFamily = sharpLinSymReleaseFamily;
	sharpLinSym.tableLength = 64;
	sharpLinSym.familySize = 9;

	sharpLinAsym.attackFamily = sharpLinAsymAttackFamily;
	sharpLinAsym.releaseFamily = sharpLinAsymReleaseFamily;
	sharpLinAsym.tableLength = 64;
	sharpLinAsym.familySize = 9;


	ascendingAdditiveClamp.attackFamily = ascendingAdditiveClampAttackFamily;
	ascendingAdditiveClamp.releaseFamily = ascendingAdditiveClampReleaseFamily;
	ascendingAdditiveClamp.tableLength = 64;
	ascendingAdditiveClamp.familySize = 9;


	summingAdditiveClamp.attackFamily = summingAdditiveClampAttackFamily;
	summingAdditiveClamp.releaseFamily = summingAdditiveClampReleaseFamily;
	summingAdditiveClamp.tableLength = 64;
	summingAdditiveClamp.familySize = 9;


	moogImpossibleTri.attackFamily = moogImpossibleTriAttackFamily;
	moogImpossibleTri.releaseFamily = moogImpossibleTriReleaseFamily;
	moogImpossibleTri.tableLength = 64;
	moogImpossibleTri.familySize = 9;


	steps.attackFamily = stepsAttackFamily;
	steps.releaseFamily = stepsReleaseFamily;
	steps.tableLength = 64;
	steps.familySize = 9;

	familyArray[0] = perlin;
	familyArray[1] = ascendingAdditiveClamp;
	familyArray[2] = bounce;
	familyArray[3] = sineFold;
	familyArray[4] = triFold;
	familyArray[5] = triOdd;
	familyArray[6] = moogSquare;
	familyArray[7] = moogInverted;
	familyArray[8] = moogImpossibleTri;
	familyArray[9] = algerian;
	familyArray[10] = exciteBike;
	familyArray[11] = sawBend;
	familyArray[12] = gauss_low;
	familyArray[13] = gauss_noconform;
	familyArray[14] = quartSym;
	familyArray[15] = quartAsym;






	// declare the initialization state
	span = familyArray[0].tableLength << 16;
	spanx2 = familyArray[0].tableLength << 17;
	currentFamily = familyArray[0];
	morphBitShiftRight = 9;
	morphBitShiftLeft = 7;




	SET_RGB_ON;
	SET_AMP_ON;
	SET_PITCH_ON;
	SET_MORPH_ON;
	SET_DRUM_MODE_ON;
	((*(volatile uint32_t *) DAC1_ADDR) = (4095));
	((*(volatile uint32_t *) DAC2_ADDR) = (0));


	// set the priority and enable an interrupt line to be used by our phase state change interrupt
	HAL_NVIC_SetPriority(EXTI15_10_IRQn, 1, 0);
	HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

	//initialize our ADCs and their respective DMA arrays
	HAL_ADC_Start_DMA(&hadc1, ADCReadings1, 4);
	HAL_ADC_Start_DMA(&hadc2, ADCReadings2, 2);
	HAL_ADC_Start_DMA(&hadc3, ADCReadings3, 1);

	//initialize the timer that is used to detect our triggers
	HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_1);

	//initialize the timer that is used for touch sensor press timeout
	HAL_TIM_Base_Start(&htim4);

	// intitialize the timer that runs the PWM for our RGB led
	HAL_TIM_Base_Start(&htim1);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);

	//initialize our dac
	HAL_DAC_Start(&hdac, DAC_CHANNEL_1);
	HAL_DAC_Start(&hdac, DAC_CHANNEL_2);

	// initialize our touch sensors
	tsl_user_Init();

	//enable our S&H resampling interrupts
	__HAL_TIM_ENABLE_IT(&htim7, TIM_IT_UPDATE);
	__HAL_TIM_ENABLE_IT(&htim8, TIM_IT_UPDATE);

	//enable our trigger interrupt
	__HAL_TIM_ENABLE_IT(&htim15, TIM_IT_UPDATE);

	//enable our drum envelope interrupt
	__HAL_TIM_ENABLE_IT(&htim3, TIM_IT_UPDATE);

	//start our DAC time base
	HAL_TIM_Base_Start_IT(&htim6);

	//initialize our sample and holds to track
	//we must do this after the resampling interrupts have been enabled
	SH_A_TRACK
	SH_B_TRACK
	attackTime = calcTime1Env;
	releaseTime = calcTime2Env;

	//HAL_FLASH_Unlock();

	//ee_status = EE_Init();
	//if( ee_status != EE_OK) {LEDC_ON}

	//restoreState();

	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1) {

		if ((GPIOA->IDR & GPIO_PIN_13) == (uint32_t) GPIO_PIN_RESET){
			if (!(TRIGGER_BUTTON)) {
				SET_TRIGGER_BUTTON;
				HAL_NVIC_SetPendingIRQ(TIM2_IRQn);
			}
		}
		else if (TRIGGER_BUTTON){
			RESET_TRIGGER_BUTTON;
			HAL_NVIC_SetPendingIRQ(TIM2_IRQn);
		}




		// run the state machine that gets us a reading on our touch sensors
		tsl_status = tsl_user_Exec();

		// if we have completed our touch sensor aquisitions
		if (tsl_status != TSL_USER_STATUS_BUSY) {

			// if no sensors were touched the last time we ran the state machine
			if (detectOn == 0) {
				// check to see if any are in detect state
				readDetect();
			} else {
				// check to see if we have released the sensor
				readRelease(modeflag);
			}

		}

		if (displayNewMode == 1) {
			//this turns our runtime display back on if we were just showing a mode change
			restoreDisplay();
		}

		/* USER CODE END WHILE */

		/* USER CODE BEGIN 3 */

	}
	/* USER CODE END 3 */

}

/** System Clock Configuration
 */
void SystemClock_Config(void) {

	RCC_OscInitTypeDef RCC_OscInitStruct;
	RCC_ClkInitTypeDef RCC_ClkInitStruct;
	RCC_PeriphCLKInitTypeDef PeriphClkInit;

	/**Initializes the CPU, AHB and APB busses clocks
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL3;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}

	/**Initializes the CPU, AHB and APB busses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}

	PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_TIM1 | RCC_PERIPHCLK_TIM8
			| RCC_PERIPHCLK_ADC12 | RCC_PERIPHCLK_ADC34;
	PeriphClkInit.Adc12ClockSelection = RCC_ADC12PLLCLK_DIV8;
	PeriphClkInit.Adc34ClockSelection = RCC_ADC34PLLCLK_DIV16;
	PeriphClkInit.Tim1ClockSelection = RCC_TIM1CLK_HCLK;
	PeriphClkInit.Tim8ClockSelection = RCC_TIM8CLK_HCLK;
	if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}

	/**Configure the Systick interrupt time
	 */
	HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq() / 1000);

	/**Configure the Systick
	 */
	HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

	/* SysTick_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* ADC1 init function */
static void MX_ADC1_Init(void) {

	ADC_MultiModeTypeDef multimode;
	ADC_ChannelConfTypeDef sConfig;

	/**Common config
	 */
	hadc1.Instance = ADC1;
	hadc1.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV1;
	hadc1.Init.Resolution = ADC_RESOLUTION_12B;
	hadc1.Init.ScanConvMode = ADC_SCAN_ENABLE;
	hadc1.Init.ContinuousConvMode = ENABLE;
	hadc1.Init.DiscontinuousConvMode = DISABLE;
	hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
	hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
	hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
	hadc1.Init.NbrOfConversion = 4;
	hadc1.Init.DMAContinuousRequests = ENABLE;
	hadc1.Init.EOCSelection = ADC_EOC_SEQ_CONV;
	hadc1.Init.LowPowerAutoWait = DISABLE;
	hadc1.Init.Overrun = ADC_OVR_DATA_OVERWRITTEN;
	if (HAL_ADC_Init(&hadc1) != HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}

	/**Configure the ADC multi-mode
	 */
	multimode.Mode = ADC_MODE_INDEPENDENT;
	if (HAL_ADCEx_MultiModeConfigChannel(&hadc1, &multimode) != HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}

	/**Configure Regular Channel
	 */
	sConfig.Channel = ADC_CHANNEL_1;
	sConfig.Rank = 1;
	sConfig.SingleDiff = ADC_SINGLE_ENDED;
	sConfig.SamplingTime = ADC_SAMPLETIME_181CYCLES_5;
	sConfig.OffsetNumber = ADC_OFFSET_NONE;
	sConfig.Offset = 0;
	if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}

	/**Configure Regular Channel
	 */
	sConfig.Channel = ADC_CHANNEL_2;
	sConfig.Rank = 2;
	if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}

	/**Configure Regular Channel
	 */
	sConfig.Channel = ADC_CHANNEL_3;
	sConfig.Rank = 3;
	if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}

	/**Configure Regular Channel
	 */
	sConfig.Channel = ADC_CHANNEL_4;
	sConfig.Rank = 4;
	if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}

}

/* ADC2 init function */
static void MX_ADC2_Init(void) {

	ADC_ChannelConfTypeDef sConfig;

	/**Common config
	 */
	hadc2.Instance = ADC2;
	hadc2.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV1;
	hadc2.Init.Resolution = ADC_RESOLUTION_12B;
	hadc2.Init.ScanConvMode = ADC_SCAN_ENABLE;
	hadc2.Init.ContinuousConvMode = ENABLE;
	hadc2.Init.DiscontinuousConvMode = DISABLE;
	hadc2.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
	hadc2.Init.ExternalTrigConv = ADC_SOFTWARE_START;
	hadc2.Init.DataAlign = ADC_DATAALIGN_RIGHT;
	hadc2.Init.NbrOfConversion = 2;
	hadc2.Init.DMAContinuousRequests = ENABLE;
	hadc2.Init.EOCSelection = ADC_EOC_SEQ_CONV;
	hadc2.Init.LowPowerAutoWait = DISABLE;
	hadc2.Init.Overrun = ADC_OVR_DATA_OVERWRITTEN;
	if (HAL_ADC_Init(&hadc2) != HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}

	/**Configure Regular Channel
	 */
	sConfig.Channel = ADC_CHANNEL_3;
	sConfig.Rank = 1;
	sConfig.SingleDiff = ADC_SINGLE_ENDED;
	sConfig.SamplingTime = ADC_SAMPLETIME_61CYCLES_5;
	sConfig.OffsetNumber = ADC_OFFSET_NONE;
	sConfig.Offset = 0;
	if (HAL_ADC_ConfigChannel(&hadc2, &sConfig) != HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}

	/**Configure Regular Channel
	 */
	sConfig.Channel = ADC_CHANNEL_4;
	sConfig.Rank = 2;
	sConfig.OffsetNumber = ADC_OFFSET_1;
	if (HAL_ADC_ConfigChannel(&hadc2, &sConfig) != HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}

}

/* ADC3 init function */
static void MX_ADC3_Init(void) {

	ADC_MultiModeTypeDef multimode;
	ADC_ChannelConfTypeDef sConfig;

	/**Common config
	 */
	hadc3.Instance = ADC3;
	hadc3.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV1;
	hadc3.Init.Resolution = ADC_RESOLUTION_12B;
	hadc3.Init.ScanConvMode = ADC_SCAN_DISABLE;
	hadc3.Init.ContinuousConvMode = ENABLE;
	hadc3.Init.DiscontinuousConvMode = DISABLE;
	hadc3.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
	hadc3.Init.ExternalTrigConv = ADC_SOFTWARE_START;
	hadc3.Init.DataAlign = ADC_DATAALIGN_RIGHT;
	hadc3.Init.NbrOfConversion = 1;
	hadc3.Init.DMAContinuousRequests = ENABLE;
	hadc3.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
	hadc3.Init.LowPowerAutoWait = DISABLE;
	hadc3.Init.Overrun = ADC_OVR_DATA_OVERWRITTEN;
	if (HAL_ADC_Init(&hadc3) != HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}

	/**Configure the ADC multi-mode
	 */
	multimode.Mode = ADC_MODE_INDEPENDENT;
	if (HAL_ADCEx_MultiModeConfigChannel(&hadc3, &multimode) != HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}

	/**Configure Regular Channel
	 */
	sConfig.Channel = ADC_CHANNEL_12;
	sConfig.Rank = 1;
	sConfig.SingleDiff = ADC_SINGLE_ENDED;
	sConfig.SamplingTime = ADC_SAMPLETIME_61CYCLES_5;
	sConfig.OffsetNumber = ADC_OFFSET_NONE;
	sConfig.Offset = 0;
	if (HAL_ADC_ConfigChannel(&hadc3, &sConfig) != HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}

}

/* DAC init function */
static void MX_DAC_Init(void) {

	DAC_ChannelConfTypeDef sConfig;

	/**DAC Initialization
	 */
	hdac.Instance = DAC;
	if (HAL_DAC_Init(&hdac) != HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}

	/**DAC channel OUT1 config
	 */
	sConfig.DAC_Trigger = DAC_TRIGGER_T6_TRGO;
	sConfig.DAC_OutputBuffer = DAC_OUTPUTBUFFER_DISABLE;
	if (HAL_DAC_ConfigChannel(&hdac, &sConfig, DAC_CHANNEL_1) != HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}

	/**DAC channel OUT2 config
	 */
	if (HAL_DAC_ConfigChannel(&hdac, &sConfig, DAC_CHANNEL_2) != HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}

}

/* TIM1 init function */
static void MX_TIM1_Init(void) {

	TIM_MasterConfigTypeDef sMasterConfig;
	TIM_OC_InitTypeDef sConfigOC;
	TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig;

	htim1.Instance = TIM1;
	htim1.Init.Prescaler = 1 - 1;
	htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim1.Init.Period = 4095;
	htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim1.Init.RepetitionCounter = 0;
	htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	if (HAL_TIM_PWM_Init(&htim1) != HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}

	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterOutputTrigger2 = TIM_TRGO2_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig)
			!= HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}

	sConfigOC.OCMode = TIM_OCMODE_PWM1;
	sConfigOC.Pulse = 0;
	sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
	sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
	if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_1)
			!= HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}

	if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_2)
			!= HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}

	if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_3)
			!= HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}

	sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
	sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
	sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
	sBreakDeadTimeConfig.DeadTime = 0;
	sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
	sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
	sBreakDeadTimeConfig.BreakFilter = 0;
	sBreakDeadTimeConfig.Break2State = TIM_BREAK2_DISABLE;
	sBreakDeadTimeConfig.Break2Polarity = TIM_BREAK2POLARITY_HIGH;
	sBreakDeadTimeConfig.Break2Filter = 0;
	sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
	if (HAL_TIMEx_ConfigBreakDeadTime(&htim1, &sBreakDeadTimeConfig)
			!= HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}

	HAL_TIM_MspPostInit(&htim1);

}

/* TIM2 init function */
static void MX_TIM2_Init(void) {

	TIM_MasterConfigTypeDef sMasterConfig;
	TIM_IC_InitTypeDef sConfigIC;

	htim2.Instance = TIM2;
	htim2.Init.Prescaler = 0;
	htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim2.Init.Period = 0;
	htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	if (HAL_TIM_IC_Init(&htim2) != HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}

	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig)
			!= HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}

	sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_BOTHEDGE;
	sConfigIC.ICSelection = TIM_ICSELECTION_DIRECTTI;
	sConfigIC.ICPrescaler = TIM_ICPSC_DIV1;
	sConfigIC.ICFilter = 0;
	if (HAL_TIM_IC_ConfigChannel(&htim2, &sConfigIC, TIM_CHANNEL_1) != HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}

}

/* TIM3 init function */
static void MX_TIM3_Init(void) {

	TIM_ClockConfigTypeDef sClockSourceConfig;
	TIM_MasterConfigTypeDef sMasterConfig;

	htim3.Instance = TIM3;
	htim3.Init.Prescaler = 10000 - 1;
	htim3.Init.CounterMode = TIM_COUNTERMODE_DOWN;
	htim3.Init.Period = 3840;
	htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	if (HAL_TIM_Base_Init(&htim3) != HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}

	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}

	sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig)
			!= HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}

}

/* TIM4 init function */
static void MX_TIM4_Init(void) {

	TIM_ClockConfigTypeDef sClockSourceConfig;
	TIM_MasterConfigTypeDef sMasterConfig;

	htim4.Instance = TIM4;
	htim4.Init.Prescaler = 10000;
	htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim4.Init.Period = 65535;
	htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	if (HAL_TIM_Base_Init(&htim4) != HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}

	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	if (HAL_TIM_ConfigClockSource(&htim4, &sClockSourceConfig) != HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}

	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig)
			!= HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}

}

/* TIM6 init function */
static void MX_TIM6_Init(void) {

	TIM_MasterConfigTypeDef sMasterConfig;

	htim6.Instance = TIM6;
	htim6.Init.Prescaler = 1 - 1;
	htim6.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim6.Init.Period = 1200;
	htim6.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	if (HAL_TIM_Base_Init(&htim6) != HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}

	sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim6, &sMasterConfig)
			!= HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}

}

/* TIM7 init function */
static void MX_TIM7_Init(void) {

	TIM_MasterConfigTypeDef sMasterConfig;

	htim7.Instance = TIM7;
	htim7.Init.Prescaler = 1;
	htim7.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim7.Init.Period = 5000;
	htim7.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	if (HAL_TIM_Base_Init(&htim7) != HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}

	sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim7, &sMasterConfig)
			!= HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}

}

/* TIM8 init function */
static void MX_TIM8_Init(void) {

	TIM_ClockConfigTypeDef sClockSourceConfig;
	TIM_MasterConfigTypeDef sMasterConfig;

	htim8.Instance = TIM8;
	htim8.Init.Prescaler = 1 - 1;
	htim8.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim8.Init.Period = 5000;
	htim8.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim8.Init.RepetitionCounter = 0;
	htim8.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	if (HAL_TIM_Base_Init(&htim8) != HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}

	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	if (HAL_TIM_ConfigClockSource(&htim8, &sClockSourceConfig) != HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}

	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterOutputTrigger2 = TIM_TRGO2_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim8, &sMasterConfig)
			!= HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}

}

/* TIM15 init function */
static void MX_TIM15_Init(void) {

	TIM_ClockConfigTypeDef sClockSourceConfig;
	TIM_MasterConfigTypeDef sMasterConfig;

	htim15.Instance = TIM15;
	htim15.Init.Prescaler = 1 - 1;
	htim15.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim15.Init.Period = 6000;
	htim15.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim15.Init.RepetitionCounter = 0;
	htim15.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	if (HAL_TIM_Base_Init(&htim15) != HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}

	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	if (HAL_TIM_ConfigClockSource(&htim15, &sClockSourceConfig) != HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}

	sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim15, &sMasterConfig)
			!= HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}

}

/* TSC init function */
static void MX_TSC_Init(void) {

	/**Configure the TSC peripheral
	 */
	htsc.Instance = TSC;
	htsc.Init.CTPulseHighLength = TSC_CTPH_2CYCLES;
	htsc.Init.CTPulseLowLength = TSC_CTPL_2CYCLES;
	htsc.Init.SpreadSpectrum = DISABLE;
	htsc.Init.SpreadSpectrumDeviation = 1;
	htsc.Init.SpreadSpectrumPrescaler = TSC_SS_PRESC_DIV1;
	htsc.Init.PulseGeneratorPrescaler = TSC_PG_PRESC_DIV32;
	htsc.Init.MaxCountValue = TSC_MCV_16383;
	htsc.Init.IODefaultMode = TSC_IODEF_IN_FLOAT;
	htsc.Init.SynchroPinPolarity = TSC_SYNC_POLARITY_FALLING;
	htsc.Init.AcquisitionMode = TSC_ACQ_MODE_NORMAL;
	htsc.Init.MaxCountInterrupt = DISABLE;
	htsc.Init.ChannelIOs = TSC_GROUP5_IO1 | TSC_GROUP5_IO2 | TSC_GROUP5_IO3
			| TSC_GROUP6_IO2 | TSC_GROUP6_IO3 | TSC_GROUP6_IO4;
	htsc.Init.ShieldIOs = TSC_GROUP3_IO4;
	htsc.Init.SamplingIOs = TSC_GROUP3_IO3 | TSC_GROUP5_IO4 | TSC_GROUP6_IO1;
	if (HAL_TSC_Init(&htsc) != HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}

}

/** 
 * Enable DMA controller clock
 */
static void MX_DMA_Init(void) {
	/* DMA controller clock enable */
	__HAL_RCC_DMA2_CLK_ENABLE()
	;
	__HAL_RCC_DMA1_CLK_ENABLE()
	;

	/* DMA interrupt init */
	/* DMA1_Channel1_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(DMA1_Channel1_IRQn, 1, 1);
	HAL_NVIC_EnableIRQ(DMA1_Channel1_IRQn);
	/* DMA2_Channel1_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(DMA2_Channel1_IRQn, 2, 0);
	HAL_NVIC_EnableIRQ(DMA2_Channel1_IRQn);
	/* DMA2_Channel5_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(DMA2_Channel5_IRQn, 1, 0);
	HAL_NVIC_EnableIRQ(DMA2_Channel5_IRQn);

}

/** Configure pins as 
 * Analog
 * Input
 * Output
 * EVENT_OUT
 * EXTI
 */
static void MX_GPIO_Init(void) {

	GPIO_InitTypeDef GPIO_InitStruct;

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOC_CLK_ENABLE()
	;
	__HAL_RCC_GPIOF_CLK_ENABLE()
	;
	__HAL_RCC_GPIOA_CLK_ENABLE()
	;
	__HAL_RCC_GPIOB_CLK_ENABLE()
	;

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOC, EOA_Pin | ATTACK_GATE_Pin | EOR_Pin,
			GPIO_PIN_RESET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOB,
			C_LED_Pin | D_LED_Pin | B_LED_Pin | S_H_A_Pin | S_H_B_Pin,
			GPIO_PIN_RESET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11 | GPIO_PIN_12, GPIO_PIN_RESET);

	/*Configure GPIO pins : EOA_Pin ATTACK_GATE_Pin EOR_Pin */
	GPIO_InitStruct.Pin = EOA_Pin | ATTACK_GATE_Pin | EOR_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	/*Configure GPIO pins : C_LED_Pin D_LED_Pin B_LED_Pin S_H_A_Pin
	 S_H_B_Pin */
	GPIO_InitStruct.Pin = C_LED_Pin | D_LED_Pin | B_LED_Pin | S_H_A_Pin
			| S_H_B_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	/*Configure GPIO pins : PA11 PA12 */
	GPIO_InitStruct.Pin = GPIO_PIN_11 | GPIO_PIN_12;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

void readDetect(void) {

	//check to see if any of our touch sensors have gone into detect state

	if (MyTKeys[3].p_Data->StateId == TSL_STATEID_DETECT) {
		RESET_RGB_ON; //turn off the runtime display
		modeflag = 1; //indicate to the other mode change functions that we have pressed the speed button
		detectOn = 1; //indicate that a touch sensor was in detect state during this aquisition cycle
		clearLEDs(); //wipe the vestiges of our runtimme display
		__HAL_TIM_SET_COUNTER(&htim4, 0); //reset the timer that we use for mode change timeout
		showMode(speed); //show our currentm mode
	}
	if (MyTKeys[2].p_Data->StateId == TSL_STATEID_DETECT) {
		RESET_RGB_ON;
		modeflag = 2; //indicate to the other mode change functions that we have pressed the trigger mode button
		detectOn = 1;
		clearLEDs();
		__HAL_TIM_SET_COUNTER(&htim4, 0);
		showMode(trigMode);
	}
	if (MyTKeys[1].p_Data->StateId == TSL_STATEID_DETECT) {
		RESET_RGB_ON;
		modeflag = 3; //indicate to the other mode change functions that we have pressed the loop button
		detectOn = 1;
		clearLEDs();
		__HAL_TIM_SET_COUNTER(&htim4, 0);
		showMode(loop);
	}
	if (MyTKeys[4].p_Data->StateId == TSL_STATEID_DETECT) {
		RESET_RGB_ON;
		modeflag = 4; //indicate to the other mode change functions that we have pressed the sample and hold mode button
		detectOn = 1;
		clearLEDs();
		__HAL_TIM_SET_COUNTER(&htim4, 0);
		showMode(sampleHoldMode);
	}
	if (MyTKeys[5].p_Data->StateId == TSL_STATEID_DETECT) {
		RESET_RGB_ON;
		modeflag = 5; //indicate to the other mode change functions that we have pressed the family up button
		detectOn = 1;
		clearLEDs();
		__HAL_TIM_SET_COUNTER(&htim4, 0);
		showMode(familyIndicator);
	}
	if (MyTKeys[0].p_Data->StateId == TSL_STATEID_DETECT) {
		RESET_RGB_ON;
		modeflag = 6; //indicate to the other mode change functions that we have pressed the family down button
		detectOn = 1;
		clearLEDs();
		__HAL_TIM_SET_COUNTER(&htim4, 0);
		showMode(familyIndicator);
	}

}

void readRelease(uint32_t modeFlagHolder) {

	// look for a change to release state on the button that was pressed (passed in with the function argument)

	switch (modeFlagHolder) {

	case 1:

		if (MyTKeys[3].p_Data->StateId == TSL_STATEID_RELEASE) {
			detectOn = 0; // indicate that we no longer have a touch sensor in detect state
			clearLEDs(); // clear the display that showed the current mode
			handleRelease(modeFlagHolder); //take the appropriate action per the button that had been pressed
		}
		break;

	case 2:

		if (MyTKeys[2].p_Data->StateId == TSL_STATEID_RELEASE) {
			detectOn = 0;
			clearLEDs();
			handleRelease(modeFlagHolder);
		}
		break;

	case 3:

		if (MyTKeys[1].p_Data->StateId == TSL_STATEID_RELEASE) {
			detectOn = 0;
			clearLEDs();
			handleRelease(modeFlagHolder);
		}
		break;

	case 4:

		if (MyTKeys[4].p_Data->StateId == TSL_STATEID_RELEASE) {
			detectOn = 0;
			clearLEDs();
			handleRelease(modeFlagHolder);
		}
		break;

	case 5:

		if (MyTKeys[5].p_Data->StateId == TSL_STATEID_RELEASE) {
			detectOn = 0;
			clearLEDs();
			handleRelease(modeFlagHolder);
		}
		break;

	case 6:

		if (MyTKeys[0].p_Data->StateId == TSL_STATEID_RELEASE) {
			detectOn = 0;
			clearLEDs();
			handleRelease(modeFlagHolder);
		}
		break;

	}

}

void handleRelease(uint32_t pinMode) {
	if (__HAL_TIM_GET_COUNTER(&htim4) < 3000) {
		// if we havent exceeded the mode change timeout, change the appropriate mode and then display the new mode
		// current value is probably too short
		changeMode(pinMode);
		switch (pinMode) {
		case 1:
			showMode(speed);
			break;
		case 2:
			showMode(trigMode);
			break;
		case 3:
			showMode(loop);
			break;
		case 4:
			showMode(sampleHoldMode);
			break;
		case 5:
			showMode(familyIndicator);
			break;
		case 6:
			showMode(familyIndicator);
			break;
		}
		displayNewMode = 1;
		__HAL_TIM_SET_COUNTER(&htim4, 0);
	} else {
		clearLEDs();
		SET_RGB_ON;
	}
}

void changeMode(uint32_t mode) {
	if (mode == 1) {
		// toggle through our 3 speed modes
		speed = (speed + 1) % 3;

		holdState |= speed << 1;

		if (speed == audio && loop == noloop) {
			//since this parameter can throw us into drum mode, initialize the proper modulation flags per trigger mode
			SET_DRUM_MODE_ON;
			switch (trigMode) {
			case 0:
				SET_AMP_ON;
				SET_PITCH_ON;
				SET_MORPH_ON;
				break;
			case 1:
				SET_AMP_ON;
				RESET_PITCH_ON;
				SET_MORPH_ON;
				break;
			case 2:
				SET_AMP_ON;
				RESET_PITCH_ON;
				RESET_MORPH_ON;
				break;
			case 3:
				RESET_AMP_ON;
				RESET_PITCH_ON;
				SET_MORPH_ON;
				break;
			case 4:
				RESET_AMP_ON;
				SET_PITCH_ON;
				SET_MORPH_ON;
				break;
			}
			// i believe this is a holdover from old code
			__HAL_TIM_ENABLE(&htim3);
		} else {
			// if we didnt just go into drum mode, make sure drum mode is off
			RESET_DRUM_MODE_ON;
			RESET_AMP_ON;
			RESET_PITCH_ON;
			RESET_MORPH_ON;

			// set the appropriate time calculation functions
			if (speed == env) {
				attackTime = calcTime1Env;
				releaseTime = calcTime2Env;
			}
			if (speed == seq) {
				attackTime = calcTime1Seq;
				releaseTime = calcTime2Seq;
			}
		}
	}
	else if (mode == 2) {
		trigMode = (trigMode + 1) % 5;
		//initialize some essential retrigger variables

		holdState |= trigMode << 3;

		incSign = 1;
		RESET_GATE_ON;
		//if drum mode is on, toggle through sets of modulation destinations
		switch (trigMode) {
		case 0:
			SET_AMP_ON;
			SET_PITCH_ON;
			SET_MORPH_ON;
			break;
		case 1:
			SET_AMP_ON;
			RESET_PITCH_ON;
			SET_MORPH_ON;
			break;
		case 2:
			SET_AMP_ON;
			RESET_PITCH_ON;
			RESET_MORPH_ON;
			break;
		case 3:
			RESET_AMP_ON;
			RESET_PITCH_ON;
			SET_MORPH_ON;
			break;
		case 4:
			RESET_AMP_ON;
			SET_PITCH_ON;
			SET_MORPH_ON;
			break;

		}
	}
	else if (mode == 3) {
		loop = (loop + 1) % 2;

		holdState |= loop;

		if (loop == noloop) {
			// signal to our oscillator that it should put itself to sleep
			SET_LAST_CYCLE;
			// switching to no loop when speed is at audio activates drum mode
			// this is about the same as what we do in the speed mode case above
			if (speed == audio) {
				SET_DRUM_MODE_ON;
				switch (trigMode) {
				case 0:
					SET_AMP_ON;
					SET_PITCH_ON;
					SET_MORPH_ON;
					break;
				case 1:
					SET_AMP_ON;
					RESET_PITCH_ON;
					SET_MORPH_ON;
					break;
				case 2:
					SET_AMP_ON;
					RESET_PITCH_ON;
					RESET_MORPH_ON;
					break;
				case 3:
					RESET_AMP_ON;
					RESET_PITCH_ON;
					SET_MORPH_ON;
					break;
				case 4:
					RESET_AMP_ON;
					SET_PITCH_ON;
					SET_MORPH_ON;
					break;

				}
				__HAL_TIM_ENABLE(&htim3);
			} else {
				RESET_DRUM_MODE_ON;
				RESET_AMP_ON;
				RESET_PITCH_ON;
				RESET_MORPH_ON;
			}
		} else {
			RESET_LAST_CYCLE;
			RESET_DRUM_MODE_ON;
			RESET_AMP_ON;
			RESET_PITCH_ON;
			RESET_MORPH_ON;
			//set our oscillator active flag so enabling loop starts playback
			SET_OSCILLATOR_ACTIVE;
		}

	}
	if (mode == 4) {
		sampleHoldMode = (sampleHoldMode + 1) % 6;

		holdState |= sampleHoldMode << 6;
		// track both inputs when we turn off the sample and hold behavior
		if (sampleHoldMode == 0) {
			SH_A_TRACK
			SH_B_TRACK
		} else if (sampleHoldMode == b) {
			// make sure we let go of A when switching out of A sample mode
			SH_A_TRACK
		}
	}
	if (mode == 5) {
		// switch our family pointer and load the appropriate playback constants
		// TO DO: SHIFT INC ACCORDING TO WAVETABLE SIZE
		familyIndicator = (familyIndicator + 1) % 16;
		currentFamily = familyArray[familyIndicator];

		holdState |= familyIndicator << 9;

		span = (familyArray[familyIndicator].tableLength) << 16;
		spanx2 = (familyArray[familyIndicator].tableLength) << 17;
		switch (familyArray[familyIndicator].familySize) {
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
		switch (familyArray[familyIndicator].tableLength) {
		// these are values that properly allow us to select a family and interpolation fraction for our morph
		case 4:
			tableSizeCompensation = 4;
			break;

		case 8:
			tableSizeCompensation = 3;
			break;

		case 16:
			tableSizeCompensation = 2;
			break;

		case 32:
			tableSizeCompensation = 1;
			break;

		case 64:
			tableSizeCompensation = 0;
			break;

		}
	}
	if (mode == 6) {
		// wrap back to the end of the array of families if we go back from the first entry
		// otherwise same as above
		if (familyIndicator == 0) {
			familyIndicator = 15;
		} else
			familyIndicator = (familyIndicator - 1);

		holdState |= familyIndicator << 9;

		currentFamily = familyArray[familyIndicator];
		span = (familyArray[familyIndicator].tableLength) << 16;
		spanx2 = (familyArray[familyIndicator].tableLength) << 17;
		switch (familyArray[familyIndicator].familySize) {

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
		switch (familyArray[familyIndicator].tableLength) {
		// these are values that properly allow us to select a family and interpolation fraction for our morph
		case 4:
			tableSizeCompensation = 4;
			break;

		case 8:
			tableSizeCompensation = 3;
			break;

		case 16:
			tableSizeCompensation = 2;
			break;

		case 32:
			tableSizeCompensation = 1;
			break;

		case 64:
			tableSizeCompensation = 0;
			break;

		}
	}
}

void showMode(uint32_t currentmode) {

	// if we are switching families, show a color corresponding to that family
	if (currentmode == familyIndicator) {
		familyRGB();
	}

	else {
		switch (currentmode) {
		// represent a 4 bit number with our LEDs
		// NEEDS WORK
		case 0:
			LEDA_ON
			break;
		case 1:
			LEDB_ON
			break;
		case 2:
			LEDC_ON
			break;
		case 3:
			LEDD_ON
			break;
		case 4:
			LEDA_ON
			LEDB_ON
			break;
		case 5:
			LEDC_ON
			LEDD_ON
			break;
		}
	}

}

void familyRGB(void) {

	switch (familyIndicator) {
	case 0:
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 4095);
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);
		break;
	case 1:
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 1000);
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 4000);
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 1000);
		break;
	case 2:
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 2000);
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 3000);
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);
		break;
	case 3:
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 3000);
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 2000);
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 1000);
		break;
	case 4:
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 4000);
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 1000);
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);
		break;
	case 5:
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 4095);
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);
		break;
	case 6:
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 4000);
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 1000);
		break;
	case 7:
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 3000);
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 2000);
		break;
	case 8:
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 2000);
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 3000);
		break;
	case 9:
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 1000);
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 4000);
		break;
	case 10:
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 4095);
		break;
	case 11:
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 1000);
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 4000);
		break;
	case 12:
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 2000);
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 3000);
		break;
	case 13:
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 3000);
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 2000);
		break;
	case 14:
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 4000);
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 1000);
		break;
	case 15:
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 4000);
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 4000);
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 4000);
		break;
	default:
		break;
	}


}
void clearLEDs(void) {
	//pretty self explanatory

	LEDA_OFF
	LEDB_OFF
	LEDC_OFF
	LEDD_OFF

	//blank the LEDs
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);

}

void restoreDisplay() {
	if (__HAL_TIM_GET_COUNTER(&htim4) > 5000) {
		clearLEDs(); // get rid of our last mode display
		SET_RGB_ON; // turn on the runtime display
		displayNewMode = 0; // a bit of logic used to make sure that we show the mode during the main loop
	}
}

void restoreState(){
	//holdState = EE_ReadVariable(virtAddrVarTab, &varDataTab);
	loop = holdState & 0x01;
	speed = (holdState & 0x06) >> 1;
	trigMode = (holdState & 0x38) >> 3;
	sampleHoldMode = (holdState & 0x1C0) >> 6;
	familyIndicator = (holdState & 0xE00) >> 9;
}

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @param  None
 * @retval None
 */
void _Error_Handler(char * file, int line) {
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	while (1) {
	}
	/* USER CODE END Error_Handler_Debug */
}

#ifdef USE_FULL_ASSERT

/**
 * @brief Reports the name of the source file and the source line number
 * where the assert_param error has occurred.
 * @param file: pointer to the source file name
 * @param line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t* file, uint32_t line)
{
	/* USER CODE BEGIN 6 */
	/* User can add his own implementation to report the file name and line number,
	 ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
	/* USER CODE END 6 */

}

#endif

/**
 * @}
 */

/**
 * @}
 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
