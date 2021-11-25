/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "fatfs.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
//#include "epd1in54.h"
//#include "epdif.h"
//#include "epdpaint.h"
//#include "imagedata.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "fatfs_sd.h"
#include "sd_card.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;
ADC_HandleTypeDef hadc2;
ADC_HandleTypeDef hadc3;
DMA_HandleTypeDef hdma_adc1;
DMA_HandleTypeDef hdma_adc2;
DMA_HandleTypeDef hdma_adc3;

DAC_HandleTypeDef hdac;
DMA_HandleTypeDef hdma_dac1;
DMA_HandleTypeDef hdma_dac2;

I2C_HandleTypeDef hi2c2;

SPI_HandleTypeDef hspi1;
SPI_HandleTypeDef hspi3;
SPI_HandleTypeDef hspi4;
DMA_HandleTypeDef hdma_spi4_rx;
DMA_HandleTypeDef hdma_spi4_tx;

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim4;
TIM_HandleTypeDef htim5;
TIM_HandleTypeDef htim6;
TIM_HandleTypeDef htim7;
TIM_HandleTypeDef htim8;

UART_HandleTypeDef huart3;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM8_Init(void);
static void MX_DMA_Init(void);
static void MX_DAC_Init(void);
static void MX_TIM6_Init(void);
static void MX_USART3_UART_Init(void);
static void MX_ADC2_Init(void);
static void MX_SPI1_Init(void);
static void MX_SPI3_Init(void);
static void MX_TIM2_Init(void);
static void MX_TIM4_Init(void);
static void MX_TIM1_Init(void);
static void MX_ADC1_Init(void);
static void MX_TIM5_Init(void);
static void MX_ADC3_Init(void);
static void MX_I2C2_Init(void);
static void MX_SPI4_Init(void);
static void MX_TIM7_Init(void);
static void MX_TIM3_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */


void HAL_ADC_ConvHalfCpltCallback(ADC_HandleTypeDef* hadc) {

	inputBuffer_position = HALF_BLOCK;
	if(hadc->Instance == ADC3){

				emg_peak_detection();
		ecg_heartrate();
	}
}
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc) {

	inputBuffer_position = FULL_BLOCK;
	if(hadc->Instance == ADC3){
				emg_peak_detection();
		ecg_heartrate();
	}
}


/* DAC CHANNEL FUnktions */

bool Init_complete = false;
////DAC_CHANNEL_1
//void HAL_DAC_ConvHalfCpltCallbackCh1(DAC_HandleTypeDef* hdac) {
//
//	outputBuffer_position = HALF_BLOCK;
//	if (Init_complete){
//		Signal_Synthesis(&signals1, 1);
//	}
//	else
//		Init_complete = initRamp();
//}
//
//void HAL_DAC_ConvCpltCallbackCh1(DAC_HandleTypeDef* hdac) {
//	outputBuffer_position = FULL_BLOCK;
//	if (Init_complete){
//		Signal_Synthesis(&signals1, 1);
//	}
//	else
//		Init_complete = initRamp();
//}

// DAC_CHANNEL_2
void HAL_DACEx_ConvHalfCpltCallbackCh2(DAC_HandleTypeDef* hdac) {
	outputBuffer_position = HALF_BLOCK;
	//Signal_Synthesis(&signals2, 2);
	if (Init_complete){
		Signal_Synthesis(&signals1, 1);
	}
	else
		Init_complete = initRamp();
}

void HAL_DACEx_ConvCpltCallbackCh2(DAC_HandleTypeDef* hdac) {
	outputBuffer_position = FULL_BLOCK;
	//Signal_Synthesis(&signals2, 2);
	if (Init_complete){
		Signal_Synthesis(&signals1, 1);
	}
	else
		Init_complete = initRamp();
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

	//	// you have to edit the startup_stm32fxxx.s file and set a big enough heap size
	//	unsigned char* frame_buffer = (unsigned char*)malloc(EPD_WIDTH * EPD_HEIGHT / 8);

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

	MX_DMA_Init();

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM8_Init();
  MX_DMA_Init();
  MX_DAC_Init();
  MX_TIM6_Init();
  MX_USART3_UART_Init();
  MX_ADC2_Init();
  MX_SPI1_Init();
  MX_SPI3_Init();
  MX_TIM2_Init();
  MX_TIM4_Init();
  MX_FATFS_Init();
  MX_TIM1_Init();
  MX_ADC1_Init();
  MX_TIM5_Init();
  MX_ADC3_Init();
  MX_I2C2_Init();
  MX_SPI4_Init();
  MX_TIM7_Init();
  MX_TIM3_Init();
  /* USER CODE BEGIN 2 */

	//--------------------------------------------------	SD CARD
	/*char* textfile_list;	// find textfiles on sd card
	sd_card_mount(huart3);
	textfile_list = find_text_file(huart3);
	sd_card_unmount(huart3);
	send_uart(textfile_list, huart3);
	send_uart("\n\n\r", huart3);*/

	/*sd_card_mount(huart3);
	sd_card_free_space(huart3);
	//sd_card_write_newfile("test.txt", "0,2,4", huart3);
	//sd_card_write_appendfile("ir.txt", "93,94", huart3);
	sd_card_read("test.txt", huart3);
	//sd_card_remove_file("ir.txt", huart3);
	sd_card_unmount(huart3);*/
	//--------------------------------------------------
	printf("***Bodysynthesizer*** \r\n");

	/* INIT FUNCTIONS************************
	 *
	 */
	printf("Begin Init\r\n");
	if(Signal_Synthesis_Init(htim8, hdac) != HAL_OK) {
		printf("Signal Synthesis init failed\n");
		//exit(EXIT_FAILURE);	// #include <stdlib.h>
	}

	effects_init();

	if(Filters_Init() == FILTER_FAIL) {
		printf("Filters init failed\n");
	}
	//SetupLowpass(&EQ_BAND1_I, 200, 0.707);

	if(Tremolo_Init(&Tremolo) == TREMOLO_FAIL) {
		printf("Tremolo init failed\n");
	}

	if(Distortion_Init() == DISTORTION_FAIL) {
		printf("Distortion init failed\n");
	}

	//ADSR_Linear_Init(&envelope);
	if(ADSR_Init() == ADSR_FAIL) {
		printf("ADSR init failed\n");
	}

	keyboard_init(&hadc1, &htim5);

	//Drummachine
	Drum_Computer_Init();

	//Gyros SPI
	spiC_Init(&hspi4, &htim7);

	//EMG init
	emg_init(&hadc3,&htim1);
	ecg_init();

	// WahWah Init
	WahWah_Init(&WahWah);

	// Interface Init
	II_init();

	// Display Init (should be done after the rest is initialized)
	if(Display_Init(&Display) == DISPLAY_FAIL)
		printf("Display init failed\n");

	printf("End Init\r\n");

	/* START FUNCTIONS ******************** */
	printf("Begin Start Functions\r\n");

	// Start Display
	frame_buffer = (unsigned char*)malloc(EPD_WIDTH * EPD_HEIGHT / 8);
	Display_Start(&epd, &paint, frame_buffer);	// https://github.com/soonuse/epd-library-stm32

	// Start DAC-DMA
	printf("start DAC\r\n");
//		HAL_DAC_Start_DMA(&hdac, DAC_CHANNEL_1, (uint32_t*)calculate_vector1 ,BLOCKSIZE, DAC_ALIGN_12B_R);
	HAL_DAC_Start_DMA(&hdac, DAC_CHANNEL_2, (uint32_t*)calculate_vector1 ,BLOCKSIZE, DAC_ALIGN_12B_R);

	// Start Timer and ADC-DMA for the keyboard (ADC1)
	keyboard_start_read();

	// Start Timer and ADC-DMA for the joystick and the potentiometer (ADC2)
	SetTimerSettings(&htim6, 500);	// Timer 6 default: 2000 Hz
	printf("start Button ADC\r\n");
	HAL_TIM_Base_Start(&htim6);
	HAL_ADC_Start_DMA(&hadc2, (uint32_t*)Display.ADC2inputs, 4);

	// Start Timer and ADC-DMA for the EMG-sensor (ADC3)
	emg_start_read();

	//Start Interface
	II_startInterface(&htim3);

	printf("End Start Functions\r\n");

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

	//	Display.Tremolo_Rate = 0.125;
	//	Display.Tremolo_Depth = 0.8;
	//	Display.Tremolo_ONOFF = true;

	//			NewSignal(&signals1,NOISE,'C',0,15);
	//NewSignal(&signals1,NOISE,'C',0);
	//	NewSignal(&signals1,NOISE,'C',0,1);
	// CEG Full Range for Wah
	//		NewSignal(&signals1,SIN, 'C',0,16);
	//	NewSignal(&signals1,SIN, 'E',0,17);
	//	NewSignal(&signals1,SIN, 'G',0,18);
	//	NewSignal(&signals1,SIN, 'C',1,8);
	//	NewSignal(&signals1,SIN, 'E',1,9);
	//	NewSignal(&signals1,SIN, 'G',1,10);
	//	NewSignal(&signals1,SIN, 'C',2,11);
	//	NewSignal(&signals1,SIN, 'E',2,12);
	//	NewSignal(&signals1,SIN, 'G',2,13);
	//		NewSignal(&signals1,SIN, 'C',4,14);
	//	NewSignal(&signals1,SIN, 'E',4,15);
	//		NewSignal(&signals1,SIN, 'G',4,16);
	//		NewSignal(&signals1,SIN, 'G',4,17);
	//	NewSignal(&signals1,SIN, 'E',5,18);
	//	NewSignal(&signals1,SIN, 'G',5,19);


	//NewSignal(&signals1,SIN, 'G',3);
	//NewSignal(&signals1,SIN, 'G',4);
	//	NewSignal(&signals2,SIN, 'C',1);
	//NewSignal(&signals2,SIN, 'C',2);
	//NewSignal(&signals2,SIN, 'C',3);
	//	NewSignal(&signals1,SIN, 'C', 2, 1);

	//effects_add(EQ, 0);
	//effects_add(DIST_S, 0);
	//	Display.Distortion_ONOFF = true;
	//	Display.Distortion_Gain = 8;

	//	// Kick
	//		timing_DS1[0] = 1;
	//		timing_DS1[1] = 0;
	//		timing_DS1[2] = 0;
	//		timing_DS1[3] = 0;
	//		timing_DS1[4] = 1;
	//		timing_DS1[5] = 0;
	//		timing_DS1[6] = 0;
	//		timing_DS1[7] = 0;
	//
	//		// Hihat
	//		timing_DS2[0] = 0;
	//		timing_DS2[1] = 0;
	//		timing_DS2[2] = 1;
	//		timing_DS2[3] = 0;
	//		timing_DS2[4] = 0;
	//		timing_DS2[5] = 0;
	//		timing_DS2[6] = 1;
	//		timing_DS2[7] = 0;
	//
	//		// Clap
	//		timing_DS3[0] = 0;
	//		timing_DS3[1] = 0;
	//		timing_DS3[2] = 0;
	//		timing_DS3[3] = 0;
	//		timing_DS3[4] = 1;
	//		timing_DS3[5] = 0;
	//		timing_DS3[6] = 0;
	//		timing_DS3[7] = 0;
	//
	//	//	// LowTom
	//		timing_DS4[0] = 0;
	//		timing_DS4[1] = 0;
	//		timing_DS4[2] = 1;
	//		timing_DS4[3] = 1;
	//		timing_DS4[4] = 0;
	//		timing_DS4[5] = 0;
	//		timing_DS4[6] = 0;
	//		timing_DS4[7] = 1;

	//		Display.Voices_Note[0] = 'C';
	//		Display.Voices_Octave[0] = 2;
	//		Display.Voices_ONOFF[0] = true;
	//	Display.Voice_Note_Sources[0] = EKG;
	//	Display.Voice_Note_Sources[0] = GYRO_FB;
	//	Display.Voice_Note_Sources[0] = POTI;
	//	Display.Voice_Note_Sources[0] = EMG;
	//	Display.PlaySingleSample_ONOFF = true;
	//	Display.Drumfilter_ONOFF = true;
	//		Display.Drumcomputer_ONOFF = true;
	//	Display.Sequencer_ONOFF = true;
	//	Display.WahWah_ONOFF = true;
	//	Display.Distortion_ONOFF = true;
	//	Display.Distortion_Gain = 8;
	//	Display.Distortion_Sources = GYRO_LR;
	//			Display.Tremolo_ONOFF = true;
	//		Display.Tremolo_Sources[0] = GYRO_FB;
	//	Display.Tremolo_Sources[1] = GYRO_LR;
	//		Display.Tremolo_Depth = 0.5;
	//		Display.Tremolo_Rate = 4;

	//	tim5_counter = 0;
	//	time = HAL_GetTick();

	while(1) {

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

		/* USER CODE END WHILE */
	}


	return 0;
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 216;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_USART3|RCC_PERIPHCLK_I2C2;
  PeriphClkInitStruct.Usart3ClockSelection = RCC_USART3CLKSOURCE_PCLK1;
  PeriphClkInitStruct.I2c2ClockSelection = RCC_I2C2CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */
  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV8;
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1.Init.ScanConvMode = ADC_SCAN_ENABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_RISING;
  hadc1.Init.ExternalTrigConv = ADC_EXTERNALTRIGCONV_T5_TRGO;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  hadc1.Init.DMAContinuousRequests = ENABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SEQ_CONV;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_12;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_15CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

/**
  * @brief ADC2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC2_Init(void)
{

  /* USER CODE BEGIN ADC2_Init 0 */

  /* USER CODE END ADC2_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC2_Init 1 */

  /* USER CODE END ADC2_Init 1 */
  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
  */
  hadc2.Instance = ADC2;
  hadc2.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV8;
  hadc2.Init.Resolution = ADC_RESOLUTION_12B;
  hadc2.Init.ScanConvMode = ADC_SCAN_ENABLE;
  hadc2.Init.ContinuousConvMode = DISABLE;
  hadc2.Init.DiscontinuousConvMode = DISABLE;
  hadc2.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_RISING;
  hadc2.Init.ExternalTrigConv = ADC_EXTERNALTRIGCONV_T6_TRGO;
  hadc2.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc2.Init.NbrOfConversion = 4;
  hadc2.Init.DMAContinuousRequests = ENABLE;
  hadc2.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  if (HAL_ADC_Init(&hadc2) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_6;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_15CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc2, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_8;
  sConfig.Rank = ADC_REGULAR_RANK_2;
  if (HAL_ADC_ConfigChannel(&hadc2, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_10;
  sConfig.Rank = ADC_REGULAR_RANK_3;
  if (HAL_ADC_ConfigChannel(&hadc2, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_13;
  sConfig.Rank = ADC_REGULAR_RANK_4;
  if (HAL_ADC_ConfigChannel(&hadc2, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC2_Init 2 */

  /* USER CODE END ADC2_Init 2 */

}

/**
  * @brief ADC3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC3_Init(void)
{

  /* USER CODE BEGIN ADC3_Init 0 */

  /* USER CODE END ADC3_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC3_Init 1 */

  /* USER CODE END ADC3_Init 1 */
  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
  */
  hadc3.Instance = ADC3;
  hadc3.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV8;
  hadc3.Init.Resolution = ADC_RESOLUTION_12B;
  hadc3.Init.ScanConvMode = ADC_SCAN_ENABLE;
  hadc3.Init.ContinuousConvMode = DISABLE;
  hadc3.Init.DiscontinuousConvMode = DISABLE;
  hadc3.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_RISING;
  hadc3.Init.ExternalTrigConv = ADC_EXTERNALTRIGCONV_T1_TRGO;
  hadc3.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc3.Init.NbrOfConversion = 2;
  hadc3.Init.DMAContinuousRequests = ENABLE;
  hadc3.Init.EOCSelection = ADC_EOC_SEQ_CONV;
  if (HAL_ADC_Init(&hadc3) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_4;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_15CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc3, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_5;
  sConfig.Rank = ADC_REGULAR_RANK_2;
  if (HAL_ADC_ConfigChannel(&hadc3, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC3_Init 2 */

  /* USER CODE END ADC3_Init 2 */

}

/**
  * @brief DAC Initialization Function
  * @param None
  * @retval None
  */
static void MX_DAC_Init(void)
{

  /* USER CODE BEGIN DAC_Init 0 */

  /* USER CODE END DAC_Init 0 */

  DAC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN DAC_Init 1 */

  /* USER CODE END DAC_Init 1 */
  /** DAC Initialization
  */
  hdac.Instance = DAC;
  if (HAL_DAC_Init(&hdac) != HAL_OK)
  {
    Error_Handler();
  }
  /** DAC channel OUT1 config
  */
  sConfig.DAC_Trigger = DAC_TRIGGER_T8_TRGO;
  sConfig.DAC_OutputBuffer = DAC_OUTPUTBUFFER_ENABLE;
  if (HAL_DAC_ConfigChannel(&hdac, &sConfig, DAC_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /** DAC channel OUT2 config
  */
  if (HAL_DAC_ConfigChannel(&hdac, &sConfig, DAC_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN DAC_Init 2 */

  /* USER CODE END DAC_Init 2 */

}

/**
  * @brief I2C2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C2_Init(void)
{

  /* USER CODE BEGIN I2C2_Init 0 */

  /* USER CODE END I2C2_Init 0 */

  /* USER CODE BEGIN I2C2_Init 1 */

  /* USER CODE END I2C2_Init 1 */
  hi2c2.Instance = I2C2;
  hi2c2.Init.Timing = 0x20404768;
  hi2c2.Init.OwnAddress1 = 0;
  hi2c2.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c2.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c2.Init.OwnAddress2 = 0;
  hi2c2.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c2.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c2.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c2) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c2, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c2, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C2_Init 2 */

  /* USER CODE END I2C2_Init 2 */

}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 7;
  hspi1.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  hspi1.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief SPI3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI3_Init(void)
{

  /* USER CODE BEGIN SPI3_Init 0 */

  /* USER CODE END SPI3_Init 0 */

  /* USER CODE BEGIN SPI3_Init 1 */

  /* USER CODE END SPI3_Init 1 */
  /* SPI3 parameter configuration*/
  hspi3.Instance = SPI3;
  hspi3.Init.Mode = SPI_MODE_MASTER;
  hspi3.Init.Direction = SPI_DIRECTION_2LINES;
  hspi3.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi3.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi3.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi3.Init.NSS = SPI_NSS_SOFT;
  hspi3.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_32;
  hspi3.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi3.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi3.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi3.Init.CRCPolynomial = 7;
  hspi3.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  hspi3.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
  if (HAL_SPI_Init(&hspi3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI3_Init 2 */

  /* USER CODE END SPI3_Init 2 */

}

/**
  * @brief SPI4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI4_Init(void)
{

  /* USER CODE BEGIN SPI4_Init 0 */

  /* USER CODE END SPI4_Init 0 */

  /* USER CODE BEGIN SPI4_Init 1 */

  /* USER CODE END SPI4_Init 1 */
  /* SPI4 parameter configuration*/
  hspi4.Instance = SPI4;
  hspi4.Init.Mode = SPI_MODE_MASTER;
  hspi4.Init.Direction = SPI_DIRECTION_2LINES;
  hspi4.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi4.Init.CLKPolarity = SPI_POLARITY_HIGH;
  hspi4.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi4.Init.NSS = SPI_NSS_SOFT;
  hspi4.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;
  hspi4.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi4.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi4.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi4.Init.CRCPolynomial = 7;
  hspi4.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  hspi4.Init.NSSPMode = SPI_NSS_PULSE_DISABLE;
  if (HAL_SPI_Init(&hspi4) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI4_Init 2 */

  /* USER CODE END SPI4_Init 2 */

}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 215;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 10000;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
  sMasterConfig.MasterOutputTrigger2 = TIM_TRGO2_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */

}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 4;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 59999;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 0;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 65535;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */

}

/**
  * @brief TIM4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM4_Init(void)
{

  /* USER CODE BEGIN TIM4_Init 0 */

  /* USER CODE END TIM4_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM4_Init 1 */

  /* USER CODE END TIM4_Init 1 */
  htim4.Instance = TIM4;
  htim4.Init.Prescaler = 4;
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim4.Init.Period = 59999;
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim4) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim4, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM4_Init 2 */

  /* USER CODE END TIM4_Init 2 */

}

/**
  * @brief TIM5 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM5_Init(void)
{

  /* USER CODE BEGIN TIM5_Init 0 */

  /* USER CODE END TIM5_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM5_Init 1 */

  /* USER CODE END TIM5_Init 1 */
  htim5.Instance = TIM5;
  htim5.Init.Prescaler = 0;
  htim5.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim5.Init.Period = 53999;
  htim5.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim5.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_Base_Init(&htim5) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim5, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim5, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM5_Init 2 */

  /* USER CODE END TIM5_Init 2 */

}

/**
  * @brief TIM6 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM6_Init(void)
{

  /* USER CODE BEGIN TIM6_Init 0 */

  /* USER CODE END TIM6_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM6_Init 1 */

  /* USER CODE END TIM6_Init 1 */
  htim6.Instance = TIM6;
  htim6.Init.Prescaler = 0;
  htim6.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim6.Init.Period = 53999;
  htim6.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_Base_Init(&htim6) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim6, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM6_Init 2 */

  /* USER CODE END TIM6_Init 2 */

}

/**
  * @brief TIM7 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM7_Init(void)
{

  /* USER CODE BEGIN TIM7_Init 0 */

  /* USER CODE END TIM7_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM7_Init 1 */

  /* USER CODE END TIM7_Init 1 */
  htim7.Instance = TIM7;
  htim7.Init.Prescaler = 0;
  htim7.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim7.Init.Period = 65535;
  htim7.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_Base_Init(&htim7) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim7, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM7_Init 2 */

  /* USER CODE END TIM7_Init 2 */

}

/**
  * @brief TIM8 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM8_Init(void)
{

  /* USER CODE BEGIN TIM8_Init 0 */

  /* USER CODE END TIM8_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};
  TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

  /* USER CODE BEGIN TIM8_Init 1 */

  /* USER CODE END TIM8_Init 1 */
  htim8.Instance = TIM8;
  htim8.Init.Prescaler = 0;
  htim8.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim8.Init.Period = 10800;
  htim8.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim8.Init.RepetitionCounter = 0;
  htim8.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_Base_Init(&htim8) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim8, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim8) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
  sMasterConfig.MasterOutputTrigger2 = TIM_TRGO2_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim8, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
  if (HAL_TIM_PWM_ConfigChannel(&htim8, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
  {
    Error_Handler();
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
  if (HAL_TIMEx_ConfigBreakDeadTime(&htim8, &sBreakDeadTimeConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM8_Init 2 */

  /* USER CODE END TIM8_Init 2 */

}

/**
  * @brief USART3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 115200;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  huart3.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart3.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */

  /* USER CODE END USART3_Init 2 */

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
  /* DMA1_Stream5_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Stream5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Stream5_IRQn);
  /* DMA1_Stream6_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Stream6_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Stream6_IRQn);
  /* DMA2_Stream0_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA2_Stream0_IRQn, 1, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream0_IRQn);
  /* DMA2_Stream1_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA2_Stream1_IRQn, 1, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream1_IRQn);
  /* DMA2_Stream2_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA2_Stream2_IRQn, 2, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream2_IRQn);
  /* DMA2_Stream3_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA2_Stream3_IRQn, 1, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream3_IRQn);
  /* DMA2_Stream4_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA2_Stream4_IRQn, 1, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream4_IRQn);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOF, SD_CS_Pin|DISP_RST_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(DISP_DC_GPIO_Port, DISP_DC_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, Red_User_LED_Pin|Blue_User_LED_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(DISP_CS_GPIO_Port, DISP_CS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : ENTER_USER_Pin BACK_Pin */
  GPIO_InitStruct.Pin = ENTER_USER_Pin|BACK_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : SD_CS_Pin DISP_RST_Pin */
  GPIO_InitStruct.Pin = SD_CS_Pin|DISP_RST_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

  /*Configure GPIO pin : DISP_DC_Pin */
  GPIO_InitStruct.Pin = DISP_DC_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(DISP_DC_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PA2 */
  GPIO_InitStruct.Pin = GPIO_PIN_2;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : DISP_BUSY_Pin */
  GPIO_InitStruct.Pin = DISP_BUSY_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(DISP_BUSY_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : SW_Pin */
  GPIO_InitStruct.Pin = SW_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(SW_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : ENTER_Pin */
  GPIO_InitStruct.Pin = ENTER_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(ENTER_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : Red_User_LED_Pin Blue_User_LED_Pin */
  GPIO_InitStruct.Pin = Red_User_LED_Pin|Blue_User_LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : DISP_CS_Pin */
  GPIO_InitStruct.Pin = DISP_CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(DISP_CS_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PD6 */
  GPIO_InitStruct.Pin = GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 1, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

}

/* USER CODE BEGIN 4 */
//printf()
int __io_putchar(int ch)
{
	uint8_t c[1];
	c[0] = ch & 0x00FF;
	HAL_UART_Transmit(&huart3, &*c, 1, 10);
	return ch;
}

//printf()
int io_putchar(int ch)
{
	uint8_t c[1];
	c[0] = ch & 0x00FF;
	HAL_UART_Transmit(&huart3, &*c, 1, 10);
	return ch;
}

int _write(int file,char *ptr, int len)
{
	int DataIdx;
	for(DataIdx= 0; DataIdx< len; DataIdx++)
	{
		io_putchar(*ptr++);
	}
	return len;
}
//printf() end


// GPIO-Button Debouncing
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {

	Display.button_pressed_flag = true;	// set here to make sure that the display will be processed and updated when for example a note or octave is changed

	if((GPIO_Pin == BACK_Pin) && (Display.BACK_Debounce_State == true)) {

		// keyboard goes down by one octave if not in drumcomputer settings, sequencer settings and adsr reset
		if(! ((Display.pagePosition==3 && Display.currentDrumcomputer>0) || (Display.pagePosition==4 && Display.currentSequencer>0) || (Display.pagePosition == 5 && Display.currentADSR == 7)) ) {
			if(Display.Keyboard_Octave > 0)
				Display.Keyboard_Octave--;
		}

		// ACHTUNG ACHTUNG, SEITENZAHL USW. BEACHTEN!!!
		// Tremolo Rate Index setting to change the rate by button pressing
		if(Display.pagePosition == 9 && Display.JoystickParameterPosition == 2) {
			if(Display.Tremolo_Rate_Index > 0)
				Display.Tremolo_Rate_Index--;
		}

		// ACHTUNG ACHTUNG, SEITENZAHL USW. BEACHTEN!!!
		// Auto-WahWah LFO Frequency Index setting to change the rate by button pressing
		if(Display.pagePosition == 8 && Display.currentWahWah > 0 && Display.JoystickParameterPosition == 4) {
			if(Display.WahWah_LFOfreq_Index > 0)
				Display.WahWah_LFOfreq_Index--;
		}

		// ACHTUNG ACHTUNG, SEITENZAHL USW. BEACHTEN!!!
		// Sequencer notes and octaves changed by putton pressing
		if(Display.pagePosition == 3 && Display.currentDrumcomputer == 0) {
			if(Display.JoystickParameterPosition == 3) {	// Sequencer Note 1 down
				if(Display.Sequencer_Noteindex[0] > 0)
					Display.Sequencer_Noteindex[0]--;
			}
			else if(Display.JoystickParameterPosition == 4) {	// Sequencer Octave 1 down
				if(Display.Sequencer_Octave[0] > 0)
					Display.Sequencer_Octave[0]--;
			}
			else if(Display.JoystickParameterPosition == 5) {	// Sequencer Note 2 down
				if(Display.Sequencer_Noteindex[1] > 0)
					Display.Sequencer_Noteindex[1]--;
			}
			else if(Display.JoystickParameterPosition == 6) {	// Sequencer Octave 2 down
				if(Display.Sequencer_Octave[1] > 0)
					Display.Sequencer_Octave[1]--;
			}
			else if(Display.JoystickParameterPosition == 7) {	// Sequencer Note 3 down
				if(Display.Sequencer_Noteindex[2] > 0)
					Display.Sequencer_Noteindex[2]--;
			}
			else if(Display.JoystickParameterPosition == 8) {	// Sequencer Octave 3 down
				if(Display.Sequencer_Octave[2] > 0)
					Display.Sequencer_Octave[2]--;
			}
		}

		// ACHTUNG ACHTUNG, SEITENZAHL USW. BEACHTEN!!!
		// Voices notes and octaves changed by putton pressing
		if(Display.pagePosition == 5 && Display.currentVoice > 0) {

			if(Display.JoystickParameterPosition == 1) {	// Voices [1,2,3] Note down
				if(Display.Voices_Noteindex[Display.currentVoice-1] > 0)
					Display.Voices_Noteindex[Display.currentVoice-1]--;
			}
			else if(Display.JoystickParameterPosition == 2) {	// Voices [1,2,3] Octave down
				if(Display.Voices_Octave[Display.currentVoice-1] > 0)
					Display.Voices_Octave[Display.currentVoice-1]--;
			}
		}

		// ACHTUNG ACHTUNG, SEITENZAHL USW. BEACHTEN!!!
		// Sources down
		if(Display.pagePosition == 2) {	// Drumfilter Cutoff Source
			if(Display.currentDrumcomputer == 6 && Display.Drumfilter_Cutoff_Source > 0)
				Display.Drumfilter_Cutoff_Source--;
		}
		else if(Display.pagePosition == 5) {
			if(Display.currentVoice > 0) {	// Voices Sources
				if(Display.JoystickParameterPosition == 3 && Display.Voice_Note_Sources[Display.currentVoice-1] > 0)
					Display.Voice_Note_Sources[Display.currentVoice-1]--;
				if(Display.JoystickParameterPosition == 4 && Display.Voice_Octave_Sources[Display.currentVoice-1] > 0)
					Display.Voice_Octave_Sources[Display.currentVoice-1]--;
			}
		}
		else if(Display.pagePosition == 6) {
			if(Display.currentADSR > 0) {	// ADSR Sources
				if(Display.JoystickParameterPosition == 1 && Display.ADSR_Sources[0] > 0)
					Display.ADSR_Sources[0]--;
				else if(Display.JoystickParameterPosition == 2 && Display.ADSR_Sources[1] > 0)
					Display.ADSR_Sources[1]--;
				else if(Display.JoystickParameterPosition == 3 && Display.ADSR_Sources[2] > 0)
					Display.ADSR_Sources[2]--;
				else if(Display.JoystickParameterPosition == 4 && Display.ADSR_Sources[3] > 0)
					Display.ADSR_Sources[3]--;
				else if(Display.JoystickParameterPosition == 5 && Display.ADSR_Sources[4] > 0)
					Display.ADSR_Sources[4]--;
			}
		}
		else if(Display.pagePosition == 7) {
			if(Display.currentBand > 0) {	// EQ Sources
				if(Display.JoystickParameterPosition == 4 && Display.EQ_Q_factor_Sources[Display.currentBand-1] > 0)
					Display.EQ_Q_factor_Sources[Display.currentBand-1]--;
				else if(Display.JoystickParameterPosition == 5 && Display.EQ_Cutoff_Sources[Display.currentBand-1] > 0)
					Display.EQ_Cutoff_Sources[Display.currentBand-1]--;
				else if(Display.JoystickParameterPosition == 6 && Display.EQ_Gain_Sources[Display.currentBand-1] > 0)
					Display.EQ_Gain_Sources[Display.currentBand-1]--;
			}
		}
		else if(Display.pagePosition == 8) {
			if(Display.currentWahWah == 0) {	// Distortion Sources
				if(Display.JoystickParameterPosition == 4 && Display.Distortion_Sources > 0) {
					Display.Distortion_Sources--;
				}
			}
			else if(Display.currentWahWah > 0) {	// WahWah Sources
				if(Display.JoystickParameterPosition == 3 && Display.WahWah_Sources[0] > 0)
					Display.WahWah_Sources[0]--;
				else if(Display.JoystickParameterPosition == 4 && Display.WahWah_Sources[1] > 0)
					Display.WahWah_Sources[1]--;
				else if(Display.JoystickParameterPosition == 5 && Display.WahWah_Sources[2] > 0)
					Display.WahWah_Sources[2]--;
				else if(Display.JoystickParameterPosition == 6 && Display.WahWah_Sources[3] > 0)
					Display.WahWah_Sources[3]--;
				else if(Display.JoystickParameterPosition == 7 && Display.WahWah_Sources[4] > 0)
					Display.WahWah_Sources[4]--;
				else if(Display.JoystickParameterPosition == 8 && Display.WahWah_Sources[5] > 0)
					Display.WahWah_Sources[5]--;
			}
		}
		else if(Display.pagePosition == 9) {	// Tremolo Sources
			if(Display.JoystickParameterPosition == 4 && Display.Tremolo_Sources[0] > 0)
				Display.Tremolo_Sources[0]--;
			else if(Display.JoystickParameterPosition == 5 && Display.Tremolo_Sources[1] > 0)
				Display.Tremolo_Sources[1]--;
		}

		//		HAL_GPIO_TogglePin(Red_User_LED_GPIO_Port, Red_User_LED_Pin);		// red led for visual feedback
		HAL_TIM_Base_Start_IT(&htim2);
		Display.BACK_Debounce_State = false;
	}

	else if((GPIO_Pin == ENTER_Pin) && (Display.ENTER_Debounce_State == true)) {

		// ACHTUNG ACHTUNG, SEITENZAHL USW. BEACHTEN!!!
		// keyboard goes up by one octave if not in drumcomputer settings, sequencer settings and adsr reset
		if(! ((Display.pagePosition==3 && Display.currentDrumcomputer>0) || (Display.pagePosition==4 && Display.currentSequencer>0) || (Display.pagePosition == 5 && Display.currentADSR == 7)) ) {
			if(Display.Keyboard_Octave < LUT_OCTAVES-1)
				Display.Keyboard_Octave++;
		}

		// set drumcomputer steps
		if(Display.EditDrums == true) {
			// invert/toggle state of the drum matrix entry, where the cursor points at at the moment
			Display.DrumMatrix[Display.CurrentSampleRow-1][Display.CurrentDrumstep-1] = !Display.DrumMatrix[Display.CurrentSampleRow-1][Display.CurrentDrumstep-1];

			if(Display.DrumMatrix[Display.CurrentSampleRow-1][Display.CurrentDrumstep-1] == true) {
				DISPLAY_SetDrumcomputerStep();
				Display.UpdateDisplay = true;
			}
			else if(Display.DrumMatrix[Display.CurrentSampleRow-1][Display.CurrentDrumstep-1] == false) {
				DISPLAY_DeleteDrumcomputerStep();
				Display.UpdateDisplay = true;
			}
		}

		// set sequencer steps
		if(Display.EditSteps == true) {
			// invert/toggle state of the sequencer matrix entry, where the cursor points at at the moment
			Display.SequencerMatrix[Display.CurrentNoteRow-1][Display.CurrentSequencestep-1] = !Display.SequencerMatrix[Display.CurrentNoteRow-1][Display.CurrentSequencestep-1];

			if(Display.SequencerMatrix[Display.CurrentNoteRow-1][Display.CurrentSequencestep-1] == true) {
				DISPLAY_SetSequencerStep();
				Display.UpdateDisplay = true;
			}
			else if(Display.SequencerMatrix[Display.CurrentNoteRow-1][Display.CurrentSequencestep-1] == false) {
				DISPLAY_DeleteSequencerStep();
				Display.UpdateDisplay = true;
			}
		}

		// ACHTUNG ACHTUNG, SEITENZAHL USW. BEACHTEN!!!
		// Load Drumkit from SD card
		if(Display.pagePosition==3 && Display.currentDrumcomputer>0 && Display.JoystickParameterPosition==3)
			Display.LoadDrumkit = true;

		//		// ACHTUNG ACHTUNG, SEITENZAHL USW. BEACHTEN!!!
		//		// Load Drumkit from SD card
		//		if(Display.pagePosition==3 && Display.currentDrumcomputer>0 && Display.JoystickParameterPosition==3)
		//			Display.LoadDrumkit = true;

		// ACHTUNG ACHTUNG, SEITENZAHL USW. BEACHTEN!!!
		// Tremolo Rate Index setting to change the rate by button pressing
		if(Display.pagePosition == 9 && Display.JoystickParameterPosition == 2) {
			if(Display.Tremolo_Rate_Index < 7)
				Display.Tremolo_Rate_Index++;
		}

		// ACHTUNG ACHTUNG, SEITENZAHL USW. BEACHTEN!!!
		// Auto-WahWah LFO Frequency Index setting to change the rate by button pressing
		if(Display.pagePosition == 8 && Display.currentWahWah > 0 && Display.JoystickParameterPosition == 4) {
			if(Display.WahWah_LFOfreq_Index < 7)
				Display.WahWah_LFOfreq_Index++;
		}

		// ACHTUNG ACHTUNG, SEITENZAHL USW. BEACHTEN!!!
		// Sequencer notes and octaves changed by putton pressing
		if(Display.pagePosition == 3 && Display.currentDrumcomputer == 0) {

			if(Display.JoystickParameterPosition == 3) {	// Sequencer Note 1 up
				if(Display.Sequencer_Noteindex[0] < 12)	// 12 keys per octave
					Display.Sequencer_Noteindex[0]++;
			}
			else if(Display.JoystickParameterPosition == 4) {	// Sequencer Octave 1 up
				if(Display.Sequencer_Octave[0] < 5)	// maximum 6 octaves
					Display.Sequencer_Octave[0]++;
			}
			else if(Display.JoystickParameterPosition == 5) {	// Sequencer Note 2 up
				if(Display.Sequencer_Noteindex[1] < 12)	// 12 keys per octave
					Display.Sequencer_Noteindex[1]++;
			}
			else if(Display.JoystickParameterPosition == 6) {	// Sequencer Octave 2 up
				if(Display.Sequencer_Octave[1] < 5)	// maximum 6 octaves
					Display.Sequencer_Octave[1]++;
			}
			else if(Display.JoystickParameterPosition == 7) {	// Sequencer Note 3 up
				if(Display.Sequencer_Noteindex[2] < 12)	// 12 keys per octave
					Display.Sequencer_Noteindex[2]++;
			}
			else if(Display.JoystickParameterPosition == 8) {	// Sequencer Octave 3 up
				if(Display.Sequencer_Octave[2] < 5)	// maximum 6 octaves
					Display.Sequencer_Octave[2]++;
			}
		}

		// ACHTUNG ACHTUNG, SEITENZAHL USW. BEACHTEN!!!
		// Voices notes and octaves changed by putton pressing
		if(Display.pagePosition == 5 && Display.currentVoice > 0) {

			if(Display.JoystickParameterPosition == 1) {	// Voices [1,2,3] Note up
				if(Display.Voices_Noteindex[Display.currentVoice-1] < 12)	// 12 keys per octave
					Display.Voices_Noteindex[Display.currentVoice-1]++;
			}
			else if(Display.JoystickParameterPosition == 2) {	// Voices [1,2,3] Octave up
				if(Display.Voices_Octave[Display.currentVoice-1] < 5)	// maximum 6 octaves
					Display.Voices_Octave[Display.currentVoice-1]++;
			}
		}

		// ACHTUNG ACHTUNG, SEITENZAHL USW. BEACHTEN!!!
		// Set preset by putton pressing
		if(Display.pagePosition == -1)
			Display.SetPreset = true;

		// ACHTUNG ACHTUNG, SEITENZAHL USW. BEACHTEN!!!
		// Reset of different modules by putton pressing
		if(Display.pagePosition == 2 && Display.currentDrumcomputer == 8)				// Drumcomputer Reset
			Display.Reset = true;
		else if(Display.pagePosition == 3 && Display.currentSequencer == 8)				// Sequencer Reset
			Display.Reset = true;
		else if(Display.pagePosition == 4 && Display.currentVoice == 5)					// Voices Reset
			Display.Reset = true;
		else if(Display.pagePosition == 5 && Display.currentADSR == 7)					// ADSR Reset
			Display.Reset = true;
		else if(Display.pagePosition == 6 && Display.currentBand == 6)					// EQ Reset
			Display.Reset = true;
		else if(Display.pagePosition == 7 && Display.currentWahWah == 3)				// WahWah Reset
			Display.Reset = true;
		else if(Display.pagePosition == 8 && Display.JoystickParameterPosition == 5)	// Distortion Reset
			Display.Reset = true;
		else if(Display.pagePosition == 9 && Display.JoystickParameterPosition == 6)	// Tremolo Reset
			Display.Reset = true;

		// ACHTUNG ACHTUNG, SEITENZAHL USW. BEACHTEN!!!
		// Sources up
		if(Display.pagePosition == 2) {	// Drumfilter Cutoff Source
			if(Display.currentDrumcomputer == 6 && Display.Drumfilter_Cutoff_Source < (NUMBER_OF_SOURCES-1))
				Display.Drumfilter_Cutoff_Source++;
		}
		else if(Display.pagePosition == 5) {
			if(Display.currentVoice > 0) {	// Voices Sources
				if(Display.JoystickParameterPosition == 3 && Display.Voice_Note_Sources[Display.currentVoice-1] < (NUMBER_OF_SOURCES-1))
					Display.Voice_Note_Sources[Display.currentVoice-1]++;
				if(Display.JoystickParameterPosition == 4 && Display.Voice_Octave_Sources[Display.currentVoice-1] < (NUMBER_OF_SOURCES-1))
					Display.Voice_Octave_Sources[Display.currentVoice-1]++;
			}
		}
		else if(Display.pagePosition == 6) {
			if(Display.currentADSR > 0) {	// ADSR Sources
				if(Display.JoystickParameterPosition == 1 && Display.ADSR_Sources[0] < (NUMBER_OF_SOURCES-1))
					Display.ADSR_Sources[0]++;
				else if(Display.JoystickParameterPosition == 2 && Display.ADSR_Sources[1] < (NUMBER_OF_SOURCES-1))
					Display.ADSR_Sources[1]++;
				else if(Display.JoystickParameterPosition == 3 && Display.ADSR_Sources[2] < (NUMBER_OF_SOURCES-1))
					Display.ADSR_Sources[2]++;
				else if(Display.JoystickParameterPosition == 4 && Display.ADSR_Sources[3] < (NUMBER_OF_SOURCES-1))
					Display.ADSR_Sources[3]++;
				else if(Display.JoystickParameterPosition == 5 && Display.ADSR_Sources[4] < (NUMBER_OF_SOURCES-1))
					Display.ADSR_Sources[4]++;
			}
		}
		else if(Display.pagePosition == 7) {
			if(Display.currentBand > 0) {	// EQ Sources
				if(Display.JoystickParameterPosition == 4 && Display.EQ_Q_factor_Sources[Display.currentBand-1] < (NUMBER_OF_SOURCES-1))
					Display.EQ_Q_factor_Sources[Display.currentBand-1]++;
				else if(Display.JoystickParameterPosition == 5 && Display.EQ_Cutoff_Sources[Display.currentBand-1] < (NUMBER_OF_SOURCES-1))
					Display.EQ_Cutoff_Sources[Display.currentBand-1]++;
				else if(Display.JoystickParameterPosition == 6 && Display.EQ_Gain_Sources[Display.currentBand-1] < (NUMBER_OF_SOURCES-1))
					Display.EQ_Gain_Sources[Display.currentBand-1]++;
			}
		}
		else if(Display.pagePosition == 8) {
			if(Display.currentWahWah == 0) {	// Distortion Sources
				if(Display.JoystickParameterPosition == 4 && Display.Distortion_Sources < (NUMBER_OF_SOURCES-1)) {
					Display.Distortion_Sources++;
				}
			}
			else if(Display.currentWahWah > 0) {	// WahWah Sources
				if(Display.JoystickParameterPosition == 3 && Display.WahWah_Sources[0] < (NUMBER_OF_SOURCES-1))
					Display.WahWah_Sources[0]++;
				else if(Display.JoystickParameterPosition == 4 && Display.WahWah_Sources[1] < (NUMBER_OF_SOURCES-1))
					Display.WahWah_Sources[1]++;
				else if(Display.JoystickParameterPosition == 5 && Display.WahWah_Sources[2] < (NUMBER_OF_SOURCES-1))
					Display.WahWah_Sources[2]++;
				else if(Display.JoystickParameterPosition == 6 && Display.WahWah_Sources[3] < (NUMBER_OF_SOURCES-1))
					Display.WahWah_Sources[3]++;
				else if(Display.JoystickParameterPosition == 7 && Display.WahWah_Sources[4] < (NUMBER_OF_SOURCES-1))
					Display.WahWah_Sources[4]++;
				else if(Display.JoystickParameterPosition == 8 && Display.WahWah_Sources[5] < (NUMBER_OF_SOURCES-1))
					Display.WahWah_Sources[5]++;
			}
		}
		else if(Display.pagePosition == 9) {	// Tremolo Sources
			if(Display.JoystickParameterPosition == 4 && Display.Tremolo_Sources[0] < (NUMBER_OF_SOURCES-1))
				Display.Tremolo_Sources[0]++;
			else if(Display.JoystickParameterPosition == 5 && Display.Tremolo_Sources[1] < (NUMBER_OF_SOURCES-1))
				Display.Tremolo_Sources[1]++;
		}

		//		HAL_GPIO_TogglePin(Blue_User_LED_GPIO_Port, Blue_User_LED_Pin);		// blue led
		HAL_TIM_Base_Start_IT(&htim4);
		Display.ENTER_Debounce_State = false;
	}
	else {
		__NOP();
	}
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	// Prevent unused argument(s) compilation warning
	UNUSED(htim);

	// NOTE : This function should not be modified, when the callback is needed,
	//        the HAL_TIM_PeriodElapsedCallback could be implemented in the user file

	if(htim->Instance == TIM2) {
		//if(HAL_GPIO_ReadPin(BACK_GPIO_Port, BACK_Pin) == GPIO_PIN_SET) {
		if(HAL_GPIO_ReadPin(BACK_GPIO_Port, BACK_Pin) == GPIO_PIN_RESET) {	// check regarding pullup/pulldown
			Display.BACK = true;
			Display.BACK_Debounce_State = true;
			HAL_TIM_Base_Stop_IT(&htim2);
		}
	}
	else if(htim->Instance == TIM4) {
		//if(HAL_GPIO_ReadPin(ENTER_GPIO_Port, ENTER_Pin) == GPIO_PIN_SET) {
		if(HAL_GPIO_ReadPin(ENTER_GPIO_Port, ENTER_Pin) == GPIO_PIN_RESET) {	// check regarding pullup/pulldown
			Display.ENTER = true;
			Display.ENTER_Debounce_State = true;
			HAL_TIM_Base_Stop_IT(&htim4);
		}
	}
	else {
		__NOP();
	}
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
	/* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
