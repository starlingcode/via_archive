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
#include "fixmath.h"
#include "fix16.h"
#include "tables.h"

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

TSC_HandleTypeDef htsc;

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
__IO uint32_t uhTSCAcquisitionValue1;
__IO uint32_t uhTSCAcquisitionValue2;
__IO uint32_t uhTSCAcquisitionValue3;
int not1;
int not2;
int not3;
int modeflag;
int modechanged;
int pindownlastcycle;
int temp1 = 0;
int temp2 = 0;
int temp3 = 0;
int temp4 = 0;
extern uint16_t dacbuffer1[1];
extern uint16_t dacbuffer2[1];
Family moog1;
Family moog2;
Family triFudge;
Family triOdd;
Family triFold;
Family bounce;
Family sineFold;
Family perlin;


extern Family familyArray[8];
extern uint8_t familyIndicator;
enum speedTypes speed;
enum loopTypes loop;
enum trigModeTypes trigMode;
enum sampleHoldModeTypes sampleHoldMode;
int trig;
uint8_t lastAttackFlag;
uint8_t lastReleaseFlag;
uint8_t intoattackfroml;
uint8_t intoreleasefroml;
uint8_t intoattackfromr;
uint8_t intoreleasefromr;
uint8_t pintimer;
uint16_t sampleHoldTimer;
int benchmark;
int lastcount;
fix16_t out;
extern uint32_t ADCReadings[48];

//define our wavetable family as two arrays of 9 wavetables (defined in tables.h), one for attack, one for release





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
static void MX_TIM2_Init(void);
static void MX_TSC_Init(void);
static void MX_TIM3_Init(void);

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);
                                

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/
void ReadPins(uint8_t);
void ChangeMode(int);
void ShowMode(uint8_t);
void ClearRGB(void);
void ClearLEDs(void);
/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

int main(void)
{

  /* USER CODE BEGIN 1 */

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
  MX_TIM2_Init();
  MX_TSC_Init();
  MX_TIM3_Init();

  /* USER CODE BEGIN 2 */
  //define our wavetable family as two arrays of 9 wavetables (defined in tables.h), one for attack, one for release


    const uint16_t perlinAttackFamily[9][65] = {perlin6_1, perlin6_2, perlin6_3, perlin6_4, perlin6_5, perlin6_6, perlin6_7, perlin6_8, perlin6_8};
    const uint16_t perlinReleaseFamily[9][65] = {perlin6_1, perlin6_2, perlin6_3, perlin6_4, perlin6_5, perlin6_6, perlin6_7, perlin6_8, perlin6_8};
    const uint16_t sinefoldAttackFamily[9][65] = {sinefold_ctr_1, sinefold_ctr_2, sinefold_ctr_3, sinefold_ctr_4, sinefold_ctr_5, sinefold_ctr_6, sinefold_ctr_7, sinefold_ctr_8, sinefold_ctr_9};
    const uint16_t sinefoldReleaseFamily[9][65] = {sinefold_ctr_1, sinefold_ctr_2, sinefold_ctr_3, sinefold_ctr_4, sinefold_ctr_5, sinefold_ctr_6, sinefold_ctr_7, sinefold_ctr_8, sinefold_ctr_9};
    const uint16_t bounceAttackFamily[9][65] = {bounce1, bounce2, bounce3, bounce4, bounce5, bounce6, bounce7, bounce8};
    const uint16_t bounceReleaseFamily[9][65] = {bounce1, bounce2, bounce3, bounce4, bounce5, bounce6, bounce7, bounce8};
    const uint16_t trifoldAttackFamily[9][65] = {trifold_1, trifold_2, trifold_3, trifold_4, trifold_5, trifold_6, trifold_7, trifold_8, trifold_9};
    const uint16_t trifoldReleaseFamily[9][65] = {trifold_1, trifold_2, trifold_3, trifold_4, trifold_5, trifold_6, trifold_7, trifold_8, trifold_9};
    const uint16_t trioddAttackFamily[9][65] = {triodd_1, triodd_2, triodd_3, triodd_4, triodd_5, triodd_6, triodd_7, triodd_8, triodd_9};
    const uint16_t trioddReleaseFamily[9][65] = {triodd_1, triodd_2, triodd_3, triodd_4, triodd_5, triodd_6, triodd_7, triodd_8, triodd_9};
    const uint16_t trifudgeAttackFamily[9][65] = {trifudge_1, trifudge_2, trifudge_3, trifudge_4, trifudge_5, trifudge_6, trifudge_7, trifudge_8, trifudge_9};
    const uint16_t trifudgeReleaseFamily[9][65] = {trifudge_1, trifudge_2, trifudge_3, trifudge_4, trifudge_5, trifudge_6, trifudge_7, trifudge_8, trifudge_9};
    const uint16_t moog1AttackFamily[9][65] = {moog1attack, moog2attack, moog3attack, moog5attack, moog6attack, moog7attack, moog8attack, moog9attack, moog9attack};
    const uint16_t moog1ReleaseFamily[9][65] = {moog1release, moog2release, moog3release, moog5release, moog6release, moog7release, moog8release, moog9release, moog9release};
    const uint16_t moog2AttackFamily[9][65] = {moog1attack2, moog2attack2, moog3attack2, moog4attack2, moog5attack2, moog6attack2, moog7attack2, moog8attack2, moog9attack2};
    const uint16_t moog2ReleaseFamily[9][65] = {moog1release2, moog2release2, moog3release2, moog4release2, moog5release2, moog6release2, moog7release2, moog8release2, moog9release2};

    perlin.attackFamily = perlinAttackFamily;
    perlin.releaseFamily = &perlinReleaseFamily[0][0];
    perlin.tableLength = 65;
    perlin.familySize = 9;
    familyArray[0] = perlin;

    sineFold.attackFamily = &sinefoldAttackFamily[0][0];
    sineFold.releaseFamily= &sinefoldReleaseFamily[0][0];
    sineFold.tableLength = 65;
    sineFold.familySize = 9;
    familyArray[1] = sineFold;

    bounce.attackFamily= &bounceAttackFamily[0][0];
    bounce.releaseFamily = &bounceReleaseFamily[0][0];
    bounce.tableLength = 65;
    bounce.familySize = 9;
    familyArray[2] = bounce;

    triFold.attackFamily = &trifoldAttackFamily[0][0];
    triFold.releaseFamily = &trifoldReleaseFamily[0][0];
    triFold.tableLength = 65;
    triFold.familySize = 9;
    familyArray[3] = triFold;

    triOdd.attackFamily = &trioddAttackFamily[0][0];
    triOdd.releaseFamily = &trioddReleaseFamily[0][0];
    triOdd.tableLength = 65;
    triOdd.familySize = 9;
    familyArray[4] = triOdd;

    triFudge.attackFamily = &trifudgeAttackFamily[0][0];
    triFudge.releaseFamily = &trifudgeReleaseFamily[0][0];
    triFudge.tableLength = 65;
    triFudge.familySize = 9;
    familyArray[5] = triFudge;

    moog1.attackFamily = &moog1AttackFamily[0][0];
    moog1.releaseFamily = &moog1ReleaseFamily[0][0];
    moog1.tableLength = 65;
    moog1.familySize = 9;
    familyArray[6] = moog1;

    moog2.attackFamily = &moog2AttackFamily[0][0];
    moog2.releaseFamily = &moog2ReleaseFamily[0][0];
    moog2.tableLength = 65;
    moog2.familySize = 9;
    familyArray[7] = moog2;




    HAL_ADC_Start_DMA(&hadc1, ADCReadings, 6);
      HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_1);
      HAL_TIM_Base_Start_IT(&htim3);
      HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
      HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
      HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
      HAL_DAC_Start(&hdac, DAC_CHANNEL_1);
      HAL_DAC_Start(&hdac, DAC_CHANNEL_2);
      HAL_DAC_Start_DMA(&hdac, DAC_CHANNEL_1, (uint32_t*)dacbuffer1, 1, DAC_ALIGN_12B_R);
      HAL_DAC_Start_DMA(&hdac, DAC_CHANNEL_2, (uint32_t*)dacbuffer2, 1, DAC_ALIGN_12B_R);



  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	 	 pintimer = (pintimer + 1) % 6;
	 	 //ReadPins(pintimer);
	 	 if (pindownlastcycle > modechanged) {ChangeMode(modeflag);}
	 	 if (pindownlastcycle > modechanged) {
	 			 if (modeflag == 1) {
	 				 for (int i = 0; i < 10000; i++) {ShowMode(speed);}
	 				 ClearLEDs();
	 			 }
	 			 else if (modeflag == 2) {
	 				 for (int i = 0; i < 10000; i++) {ShowMode(trigMode);}
	 				 ClearLEDs();}
	 			 else if (modeflag == 3) {
	 				 for (int i = 0; i < 10000; i++) {ShowMode(loop);}
	 				 ClearLEDs();}
	 			 else if (modeflag == 4) {
	 				 for (int i = 0; i < 10000; i++) {ShowMode(sampleHoldMode);}
	 				 ClearLEDs();}
	 	}

	 	 if (lastAttackFlag > 0 && modechanged == 0) {
	 		 __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, out);
	 		 __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);} //sets the PWM duty cycle (Capture Compare Value)
	 	 if (lastReleaseFlag > 0 && modechanged == 0) {
	 		 __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, out);
	 		 __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
	 	 } //sets the PWM duty cycle (Capture Compare Value)
	 	 if (modechanged == 0) {__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, ADCReadings[5]);} //sets the PWM duty cycle (Capture Compare Value)



	 	 //ProcessSensors(); /*Initiates acquisition, sets uhTSCAcquisitionValue1, uhTSCAcquisitionValue2, and
	     	//				uhTSCAcquisitionValue3 if acquisition successful*/
	 	 //SetFlags(); /*Sets flag1, flag2, or flag3 per the unique value combos indicating a touch in the corresponding
	      //	 	 	 zone*/
	      //


  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */

  }
  /* USER CODE END 3 */

}

/** System Clock Configuration
*/
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInit;

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL16;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_TIM1|RCC_PERIPHCLK_ADC12
                              |RCC_PERIPHCLK_ADC34;
  PeriphClkInit.Adc12ClockSelection = RCC_ADC12PLLCLK_DIV1;
  PeriphClkInit.Adc34ClockSelection = RCC_ADC34PLLCLK_DIV1;
  PeriphClkInit.Tim1ClockSelection = RCC_TIM1CLK_HCLK;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* ADC1 init function */
static void MX_ADC1_Init(void)
{

  ADC_MultiModeTypeDef multimode;
  ADC_ChannelConfTypeDef sConfig;

    /**Common config 
    */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV1;
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  hadc1.Init.DMAContinuousRequests = DISABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  hadc1.Init.LowPowerAutoWait = DISABLE;
  hadc1.Init.Overrun = ADC_OVR_DATA_OVERWRITTEN;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the ADC multi-mode 
    */
  multimode.Mode = ADC_MODE_INDEPENDENT;
  if (HAL_ADCEx_MultiModeConfigChannel(&hadc1, &multimode) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure Regular Channel 
    */
  sConfig.Channel = ADC_CHANNEL_1;
  sConfig.Rank = 1;
  sConfig.SingleDiff = ADC_SINGLE_ENDED;
  sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
  sConfig.OffsetNumber = ADC_OFFSET_NONE;
  sConfig.Offset = 0;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/* ADC2 init function */
static void MX_ADC2_Init(void)
{

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
  hadc2.Init.NbrOfConversion = 4;
  hadc2.Init.DMAContinuousRequests = ENABLE;
  hadc2.Init.EOCSelection = ADC_EOC_SEQ_CONV;
  hadc2.Init.LowPowerAutoWait = DISABLE;
  hadc2.Init.Overrun = ADC_OVR_DATA_OVERWRITTEN;
  if (HAL_ADC_Init(&hadc2) != HAL_OK)
  {
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
  if (HAL_ADC_ConfigChannel(&hadc2, &sConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure Regular Channel 
    */
  sConfig.Rank = 2;
  if (HAL_ADC_ConfigChannel(&hadc2, &sConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure Regular Channel 
    */
  sConfig.Rank = 3;
  if (HAL_ADC_ConfigChannel(&hadc2, &sConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure Regular Channel 
    */
  sConfig.Rank = 4;
  if (HAL_ADC_ConfigChannel(&hadc2, &sConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/* ADC3 init function */
static void MX_ADC3_Init(void)
{

  ADC_MultiModeTypeDef multimode;
  ADC_ChannelConfTypeDef sConfig;

    /**Common config 
    */
  hadc3.Instance = ADC3;
  hadc3.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV1;
  hadc3.Init.Resolution = ADC_RESOLUTION_12B;
  hadc3.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc3.Init.ContinuousConvMode = DISABLE;
  hadc3.Init.DiscontinuousConvMode = DISABLE;
  hadc3.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc3.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc3.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc3.Init.NbrOfConversion = 1;
  hadc3.Init.DMAContinuousRequests = DISABLE;
  hadc3.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  hadc3.Init.LowPowerAutoWait = DISABLE;
  hadc3.Init.Overrun = ADC_OVR_DATA_OVERWRITTEN;
  if (HAL_ADC_Init(&hadc3) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the ADC multi-mode 
    */
  multimode.Mode = ADC_MODE_INDEPENDENT;
  if (HAL_ADCEx_MultiModeConfigChannel(&hadc3, &multimode) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure Regular Channel 
    */
  sConfig.Channel = ADC_CHANNEL_12;
  sConfig.Rank = 1;
  sConfig.SingleDiff = ADC_SINGLE_ENDED;
  sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
  sConfig.OffsetNumber = ADC_OFFSET_NONE;
  sConfig.Offset = 0;
  if (HAL_ADC_ConfigChannel(&hadc3, &sConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/* DAC init function */
static void MX_DAC_Init(void)
{

  DAC_ChannelConfTypeDef sConfig;

    /**DAC Initialization 
    */
  hdac.Instance = DAC;
  if (HAL_DAC_Init(&hdac) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**DAC channel OUT1 config 
    */
  sConfig.DAC_Trigger = DAC_TRIGGER_T3_TRGO;
  sConfig.DAC_OutputBuffer = DAC_OUTPUTBUFFER_ENABLE;
  if (HAL_DAC_ConfigChannel(&hdac, &sConfig, DAC_CHANNEL_1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  __HAL_REMAPTRIGGER_ENABLE(HAL_REMAPTRIGGER_DAC1_TRIG);

    /**DAC channel OUT2 config 
    */
  if (HAL_DAC_ConfigChannel(&hdac, &sConfig, DAC_CHANNEL_2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/* TIM1 init function */
static void MX_TIM1_Init(void)
{

  TIM_MasterConfigTypeDef sMasterConfig;
  TIM_OC_InitTypeDef sConfigOC;
  TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig;

  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 0;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 0;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_PWM_Init(&htim1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterOutputTrigger2 = TIM_TRGO2_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
  {
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
  if (HAL_TIMEx_ConfigBreakDeadTime(&htim1, &sBreakDeadTimeConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  HAL_TIM_MspPostInit(&htim1);

}

/* TIM2 init function */
static void MX_TIM2_Init(void)
{

  TIM_SlaveConfigTypeDef sSlaveConfig;
  TIM_MasterConfigTypeDef sMasterConfig;

  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 0;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 0;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sSlaveConfig.SlaveMode = TIM_SLAVEMODE_EXTERNAL1;
  sSlaveConfig.InputTrigger = TIM_TS_TI1FP1;
  sSlaveConfig.TriggerPolarity = TIM_TRIGGERPOLARITY_RISING;
  sSlaveConfig.TriggerFilter = 0;
  if (HAL_TIM_SlaveConfigSynchronization(&htim2, &sSlaveConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/* TIM3 init function */
static void MX_TIM3_Init(void)
{

  TIM_ClockConfigTypeDef sClockSourceConfig;
  TIM_MasterConfigTypeDef sMasterConfig;

  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 1-1;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 1000;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/* TSC init function */
static void MX_TSC_Init(void)
{

    /**Configure the TSC peripheral 
    */
  htsc.Instance = TSC;
  htsc.Init.CTPulseHighLength = TSC_CTPH_2CYCLES;
  htsc.Init.CTPulseLowLength = TSC_CTPL_2CYCLES;
  htsc.Init.SpreadSpectrum = DISABLE;
  htsc.Init.SpreadSpectrumDeviation = 1;
  htsc.Init.SpreadSpectrumPrescaler = TSC_SS_PRESC_DIV1;
  htsc.Init.PulseGeneratorPrescaler = TSC_PG_PRESC_DIV64;
  htsc.Init.MaxCountValue = TSC_MCV_255;
  htsc.Init.IODefaultMode = TSC_IODEF_OUT_PP_LOW;
  htsc.Init.SynchroPinPolarity = TSC_SYNC_POLARITY_FALLING;
  htsc.Init.AcquisitionMode = TSC_ACQ_MODE_NORMAL;
  htsc.Init.MaxCountInterrupt = DISABLE;
  htsc.Init.ChannelIOs = TSC_GROUP5_IO1|TSC_GROUP5_IO2|TSC_GROUP5_IO3|TSC_GROUP6_IO2
                    |TSC_GROUP6_IO3|TSC_GROUP6_IO4;
  htsc.Init.ShieldIOs = TSC_GROUP3_IO4;
  htsc.Init.SamplingIOs = TSC_GROUP3_IO3|TSC_GROUP5_IO4|TSC_GROUP6_IO1;
  if (HAL_TSC_Init(&htsc) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/** 
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void) 
{
  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();
  __HAL_RCC_DMA2_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Channel1_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel1_IRQn, 1, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel1_IRQn);
  /* DMA2_Channel1_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA2_Channel1_IRQn, 1, 0);
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
static void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, EOA_Pin|ATTACK_GATE_Pin|EOR_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOF, RELEASE_GATE_Pin|A_LED_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, C_LED_Pin|D_LED_Pin|B_LED_Pin|S_H_A_Pin 
                          |S_H_B_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : EOA_Pin ATTACK_GATE_Pin EOR_Pin */
  GPIO_InitStruct.Pin = EOA_Pin|ATTACK_GATE_Pin|EOR_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : RELEASE_GATE_Pin A_LED_Pin */
  GPIO_InitStruct.Pin = RELEASE_GATE_Pin|A_LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

  /*Configure GPIO pins : C_LED_Pin D_LED_Pin B_LED_Pin S_H_A_Pin 
                           S_H_B_Pin */
  GPIO_InitStruct.Pin = C_LED_Pin|D_LED_Pin|B_LED_Pin|S_H_A_Pin 
                          |S_H_B_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */


void ReadPins(uint8_t pin){
	pindownlastcycle = modechanged;
	if (pin == 0) {
	    if (HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_8) == GPIO_PIN_RESET) {
	    	modeflag = 1;
	    	modechanged = 1;
	    	ClearRGB();
	    	ShowMode(speed);
	    }
	    else {
	    	if (modeflag == 1) {modechanged = 0;}
	    }
	}
	if (pin == 1) {
	    if (HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_9) == GPIO_PIN_RESET) {
	    	modeflag = 2;
	    	modechanged = 1;
	    	ClearRGB();
	    	ShowMode(trigMode);
	    }
	    else {
	    	if (modeflag == 2) {modechanged = 0;}
	    }
	}
	if (pin == 2) {
	    if (HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_10) == GPIO_PIN_RESET) {
	    	modeflag = 3;
	    	modechanged = 1;
	    	ClearRGB();
	    	ShowMode(loop);
	    }
	    else {
	    	if (modeflag == 3) {modechanged = 0;}
	    }
	}
	if (pin == 3) {
	    if (HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_11) == GPIO_PIN_RESET) {
	    	modeflag = 4;
	    	modechanged = 1;
	    	ClearRGB();
	    	ShowMode(sampleHoldMode);
	    }
	    else {
	    	if (modeflag == 4) {modechanged = 0;}
	    }
	}
	if (pin == 4) {
	    if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_13) == GPIO_PIN_RESET) {
	    	modeflag = 5;
	    	modechanged = 1;
	    	ClearRGB();
	    	ShowMode(familyIndicator);
	    }
	    else {
	    	if (modeflag == 4) {modechanged = 0;}
	    }
	}
}

void ChangeMode(int mode) {
		if (mode == 1) {
			speed = (speed + 1) % 2;
		}
		if (mode == 2) {
			trigMode = (trigMode + 1) % 5;
		}
		if (mode == 3) {
			loop = (loop + 1) % 2;
		}
		if (mode == 4) {
			sampleHoldMode = (sampleHoldMode + 1) % 6;
		}
		if (mode == 5) {
			familyIndicator = (familyIndicator + 1) % 8;
		}
}

void ShowMode(uint8_t currentmode) {
	if (currentmode == 1) {
		HAL_GPIO_WritePin(GPIOF, GPIO_PIN_12, GPIO_PIN_SET);
		return;
	}
	if (currentmode == 2) {
		HAL_GPIO_WritePin(GPIOF, GPIO_PIN_12, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);
		return;
	}
	if (currentmode == 3) {
		HAL_GPIO_WritePin(GPIOF, GPIO_PIN_12, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_SET);
		return;

	}
	if (currentmode == 4) {
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_SET);
		return;

	}
	if (currentmode == 5) {
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);
		return;

	}
	if (currentmode == 6) {
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_SET);
		return;

	}
	if (currentmode == 7) {
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_SET);
		return;

	}
	/*
	if (lastAttackFlag > 0) {
			 __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, out);
			 __HAL_TIM_SET_COMPARE(&htim17, TIM_CHANNEL_1, 0);} //sets the PWM duty cycle (Capture Compare Value)
	if (lastReleaseFlag > 0) {
			 __HAL_TIM_SET_COMPARE(&htim17, TIM_CHANNEL_1, out);
			 __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 0);
		 } //sets the PWM duty cycle (Capture Compare Value)
		 __HAL_TIM_SET_COMPARE(&htim16, TIM_CHANNEL_1, ADCReadings[5]); //sets*/
}

void ClearRGB(void) {
	//HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_RESET);
	//HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_RESET);
	//HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_RESET);
	 __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
	 __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);
	 __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);
}
void ClearLEDs(void) {
	HAL_GPIO_WritePin(GPIOF, GPIO_PIN_12, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);
}







/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void _Error_Handler(char * file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1) 
  {
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
