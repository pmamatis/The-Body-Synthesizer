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

//#define COLORED      0
//#define UNCOLORED    1

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

UART_HandleTypeDef huart2;
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
static void MX_USART2_UART_Init(void);
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

//void Load_SD_File(uint8_t JoystickPatchPosition, uint16_t VRy, bool SW, Paint paint, EPD epd, unsigned char* frame_buffer);

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */


void HAL_ADC_ConvHalfCpltCallback(ADC_HandleTypeDef* hadc) {

	inputBuffer_position = HALF_BLOCK;
	if(hadc->Instance == ADC3){
//				HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_7);
		emg_peak_detection();

	}
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc) {

	inputBuffer_position = FULL_BLOCK;
	if(hadc->Instance == ADC3){
		//		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_7);
		emg_peak_detection();
	}
}


/* DAC CHANNEL FUnktions */
//DAC_CHANNEL_1
void HAL_DAC_ConvHalfCpltCallbackCh1(DAC_HandleTypeDef* hdac) {
	outputBuffer_position = HALF_BLOCK;
	Signal_Synthesis(&signals1, 1);
}

void HAL_DAC_ConvCpltCallbackCh1(DAC_HandleTypeDef* hdac) {
	outputBuffer_position = FULL_BLOCK;
	Signal_Synthesis(&signals1,1);
}

// DAC_CHANNEL_2
void HAL_DACEx_ConvHalfCpltCallbackCh2(DAC_HandleTypeDef* hdac) {
	outputBuffer_position = HALF_BLOCK;
	//Signal_Synthesis(&signals2, 2);
	Signal_Synthesis(&signals1, 1);
}

void HAL_DACEx_ConvCpltCallbackCh2(DAC_HandleTypeDef* hdac) {
	outputBuffer_position = FULL_BLOCK;
	//Signal_Synthesis(&signals2, 2);
	Signal_Synthesis(&signals1, 1);
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
  MX_USART2_UART_Init();
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
		//while(1);
		//exit(EXIT_FAILURE);	// #include <stdlib.h>
	}

	effects_init();

	if(Filters_Init() == FILTER_FAIL) {
		printf("Filters init failed\n");
		//while(1);
	}
	//SetupLowpass(&EQ_BAND1_I, 200, 0.707);

	if(Tremolo_Init() == TREMOLO_FAIL) {
		printf("Tremolo init failed\n");
		//while(1);
	}

	if(Distortion_Init() == DISTORTION_FAIL) {
		printf("Distortion init failed\n");
		//while(1);
	}

	//ADSR_Linear_Init(&envelope);
	if(ADSR_Init() == ADSR_FAIL) {
		printf("ADSR init failed\n");
		//while(1);
	}

	if(Display_Init(&Display) == DISPLAY_FAIL) {
		printf("Display init failed\n");
		//while(1);
	}

	keyboard_init(&hadc1, &htim5);

	//Gyros SPI
	spiC_Init(&hspi4, &htim7);

	//EMG init
	emg_init(&hadc3,&htim1);


	printf("End Init\r\n");



	/* START FUNCTIONS *******************
	 * */

	printf("Begin Start Functions\r\n");
	//Start Display

	frame_buffer = (unsigned char*)malloc(EPD_WIDTH * EPD_HEIGHT / 8);
//	Display_Start(&epd, &paint, frame_buffer);	// https://github.com/soonuse/epd-library-stm32


	// Start DAC-DMA
	printf("start DAC\r\n");
	HAL_DAC_Start_DMA(&hdac, DAC_CHANNEL_1, (uint32_t*)calculate_vector1 ,BLOCKSIZE, DAC_ALIGN_12B_R);
	//HAL_DAC_Start_DMA(&hdac, DAC_CHANNEL_2, (uint32_t*)calculate_vector2 ,BLOCKSIZE, DAC_ALIGN_12B_R);
//	HAL_DAC_Start_DMA(&hdac, DAC_CHANNEL_2, (uint32_t*)calculate_vector1 ,BLOCKSIZE, DAC_ALIGN_12B_R);



	// Start Timer and ADC-DMA for the keyboard (ADC1)
//	keyboard_start_read();


	// Start Timer and ADC-DMA for the joystick and the potentiometer (ADC2)
	SetTimerSettings(&htim6, 20);	// Timer 6 default: 2000 Hz
	printf("start Button ADC\r\n");
//	HAL_TIM_Base_Start(&htim6);
//	HAL_ADC_Start_DMA(&hadc2, (uint32_t*)Display.ADC2inputs, 3);

	// Start Timer and ADC-DMA for the EMG-sensor (ADC3)
//	emg_start_read();


	//Start Interface
	II_startInterface(&htim3);


	printf("End Start Functions\r\n");

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */


//	NewSignal(&signals1,NOISE,'C',0,0);
	//NewSignal(&signals1,NOISE,'C',0);
	//NewSignal(&signals1,NOISE,'C',0);
	//NewSignal(&signals1,SIN, 'C',0);
//	NewSignal(&signals1,SIN, 'C',1);
	NewSignal(&signals1,SIN, 'C',2,0);
	NewSignal(&signals1,SIN, 'C',3,1);
	NewSignal(&signals1,SIN, 'C',4,2);
	NewSignal(&signals1,SIN, 'G',0,3);
//	NewSignal(&signals1,SIN, 'G',1);
//	NewSignal(&signals1,SIN, 'G',2);
	//NewSignal(&signals1,SIN, 'G',3);
	//NewSignal(&signals1,SIN, 'G',4);
//	NewSignal(&signals2,SIN, 'C',1);
	//NewSignal(&signals2,SIN, 'C',2);
	//NewSignal(&signals2,SIN, 'C',3);
	//NewSignal(&signals2,SIN, 'C',4);

	//effects_add(EQ, 0);
	//effects_add(DIST_S, 0);


	/* Manuel setings
	 *
	 */
	Display.mode = BODYSYNTH;

//	Display.Voices_Note[0] = 'C';
//	Display.Voices_Octave[0] = 2;
//	Display.Voices_ONOFF[0] = true;
//	Display.Voice_Note_Sources[0] = EKG;
//	Display.Voice_Note_Sources[0] = GYRO_FB;
//	Display.Voice_Note_Sources[0] = POTI;

//	Display.Distortion_ONOFF = true;
//	Display.Distortion_Gain = 5;
//	Display.Distortion_Sources = GYRO_LR;
//	Display.Tremolo_ONOFF = true;
//	Display.Tremolo_Sources[0] = GYRO_FB;
//	Display.Tremolo_Sources[1] = GYRO_LR;
//	Display.Tremolo_Depth = 1;
//	Display.Tremolo_Rate = 3;
	Display.EQ_Cutoff_Sources[0] = GYRO_LR;
	Display.currentBand =0;
	Display.Filter_ONOFF[0] = true;
//	Display.Filter_ONOFF[0] = false;
	Display.Filter_Cutoff[0] = 4000;

//HAL_Delay(1000);
	while(1) {
		//		printf("Gyro: \r\n");

//	HAL_Delay(1000);
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

		/* USER CODE END WHILE */
	}
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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
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
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_USART2|RCC_PERIPHCLK_USART3
                              |RCC_PERIPHCLK_I2C2;
  PeriphClkInitStruct.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
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
  hadc2.Init.NbrOfConversion = 3;
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
  hadc3.Init.NbrOfConversion = 1;
  hadc3.Init.DMAContinuousRequests = ENABLE;
  hadc3.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  if (HAL_ADC_Init(&hadc3) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_5;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_15CYCLES;
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
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_64;
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
  htim5.Init.Period = 100;
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
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

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

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 1, 0);
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

/*void SetPatchParameters(struct display_variables* Display, struct BQFilter* Filter, struct adsr* envelope, struct effects_distortion* HardClipping, struct effects_LFO* Tremolo, Paint paint, EPD epd, unsigned char* frame_buffer) {

	// FOR DEBUGGING ONLY PATCH 1!
	Display->PatchSelected[0] = true;

	// PATCH 1 SELECTED
	while(Display->PatchSelected[0] == true) {

		// effect order for patch 1
		Display->Distortion_EffectPosition = 0;
		Display->Tremolo_EffectPosition = 1;
		Display->ADSR_EffectPosition = 2;
		Display->Filter_EffectPosition = 3;

		// #############################################
		// ########### BEGIN VOICES SUBMENU ############
		// #############################################
		while(Display->CurrentModule == 0) {

			Paint_DrawStringAt(&paint, 1, 10, "Voices", &Font16, COLORED);
			Paint_DrawStringAt(&paint, 1, 30, "Voice1 ON/OFF", &Font12, COLORED);
			Paint_DrawStringAt(&paint, 1, 50, "Voice1 Note", &Font12, COLORED);
			Paint_DrawStringAt(&paint, 1, 70, "Voice1 Octave", &Font12, COLORED);

			Display->VRx = Display->ADC2inputs[0];		// read joystick x-value
			Display->VRy = Display->ADC2inputs[1];		// read joystick y-value
			Display->Poti_raw = Display->ADC2inputs[2];	// read poti-value

			uint8_t note, last_note;
			char octave, last_octave;

			if( (Display->JoystickParameterPosition == 1) && (Display->VRy > Display->LowerLimit) ) {
				Paint_DrawStringAt(&paint, 110, 30, "<---", &Font12, COLORED);	// arrow to Voice1 ON/OFF
			}
			else if( (Display->JoystickParameterPosition == 1) && (Display->VRy < Display->LowerLimit) ) {
				Paint_DrawFilledRectangle(&paint, 110, 30, 150, 40, UNCOLORED);	// switch from Voice1 ON/OFF to Voice1 Note
				Paint_DrawStringAt(&paint, 110, 50, "<---", &Font12, COLORED);
				Display->JoystickParameterPosition = 2;
			}
			else if( (Display->JoystickParameterPosition == 2) && (Display->VRy > Display->UpperLimit) ) {
				Paint_DrawFilledRectangle(&paint, 110, 50, 150, 60, UNCOLORED);	// switch from Voice1 Note to Voice1 ON/OFF
				Paint_DrawStringAt(&paint, 110, 30, "<---", &Font12, COLORED);
				Display->JoystickParameterPosition = 1;
			}
			else if( (Display->JoystickParameterPosition == 2) && (Display->VRy < Display->LowerLimit) ) {
				Paint_DrawFilledRectangle(&paint, 110, 50, 150, 60, UNCOLORED);	// switch from Voice1 Note to Voice1 Octave
				Paint_DrawStringAt(&paint, 110, 70, "<---", &Font12, COLORED);
				Display->JoystickParameterPosition = 3;
			}
			else if( (Display->JoystickParameterPosition == 2) && (Display->VRy > Display->LowerLimit) && (Display->VRy < Display->UpperLimit) ) {
				Paint_DrawStringAt(&paint, 110, 50, "<---", &Font12, COLORED);	// arrow to Voice1 Note
			}
			else if( (Display->JoystickParameterPosition == 3) && (Display->VRy > Display->UpperLimit) ) {
				Paint_DrawFilledRectangle(&paint, 110, 70, 150, 80, UNCOLORED);	// switch from Note1 Octave to Voice1 Note
				Paint_DrawStringAt(&paint, 110, 50, "<---", &Font12, COLORED);
				Display->JoystickParameterPosition = 2;
			}
			else if( (Display->JoystickParameterPosition == 3) && (Display->VRy < Display->UpperLimit) ) {
				Paint_DrawStringAt(&paint, 110, 70, "<---", &Font12, COLORED);	// arrow to Voice1 Octave
			}

			// check state of the potentiometer and assign parameter value
			// Voice1 ON/OFF
			if( (Display->JoystickParameterPosition == 1) && (Display->Poti_raw < Display->ADC_FullRange/2) ) {
				Paint_DrawFilledRectangle(&paint, 150, 30, 200, 50, UNCOLORED);
				Paint_DrawStringAt(&paint, 150, 30, "OFF", &Font12, COLORED);
				Display->Voices_ONOFF[0] = false;
			}
			else if( (Display->JoystickParameterPosition == 1) && (Display->Poti_raw >= Display->ADC_FullRange/2) ) {
				Paint_DrawFilledRectangle(&paint, 150, 30, 200, 50, UNCOLORED);
				Paint_DrawStringAt(&paint, 150, 30, "ON", &Font12, COLORED);
				Display->Voices_ONOFF[0] = true;
			}

			// Voice1 Note
			else if(Display->JoystickParameterPosition == 2) {
				Paint_DrawFilledRectangle(&paint, 150, 50, 200, 70, UNCOLORED);
				float noteindex = ((float)Display->Poti_raw/4096) * (sizeof(keys)/sizeof(keys[0]));
				note = keys[(uint8_t)noteindex];
				Display->Voices_Note[0] = note;	// assign Voice1 Note
			}

			// Voice1 Octave
			else if(Display->JoystickParameterPosition == 3) {
				Paint_DrawFilledRectangle(&paint, 150, 70, 200, 90, UNCOLORED);
				octave = (char) (((float)Display->Poti_raw/4096) * 6);	// 5 0ctaves
				Display->Voices_Octave[0] = (uint8_t)octave;	// assign Voice1 Octave
			}

			if(Display->Voices_ONOFF[0] == true) {	// if Voice1 ON

				if( (last_note != note) || (last_octave != octave) ) {	// if voice parameters changed

					if(signals1.count == 1)		// Delete the last generated signal
						DeleteSignal(&signals1, 1);

					NewSignal(&signals1, SIN, Display->Voices_Note[0], Display->Voices_Octave[0]);	// create signal and assign selected parameters
					outputBuffer_position = HALF_BLOCK;
				}
			}
			else if(Display->Voices_ONOFF[0] == false) {	// if Voice1 OFF
				if(signals1.count == 1)
					DeleteSignal(&signals1, 1);
			}
			last_note = note;
			last_octave = octave;

			Paint_DrawCharAt(&paint, 150, 50, note, &Font12, COLORED);
			Paint_DrawCharAt(&paint, 150, 70, octave+'0', &Font12, COLORED);	// '0' wird draufaddiert, um den Wert korrekt darzustellen
			// Display the frame_buffer
			EPD_SetFrameMemory(&epd, frame_buffer, 0, 0, Paint_GetWidth(&paint), Paint_GetHeight(&paint));
			EPD_DisplayFrame(&epd);

			//			// reset BACK-switch
			//			if(HAL_GPIO_ReadPin(BACK_GPIO_Port, BACK_Pin) == GPIO_PIN_RESET) {		// BACK is false and LED turned off in case that BACK-Button is not pressed anymore
			//				Display->BACK = false;
			//			}
			//			// reset ENTER-switch
			//			if(HAL_GPIO_ReadPin(ENTER_GPIO_Port, ENTER_Pin) == GPIO_PIN_RESET) {	// ENTER is false and LED turned off in case that ENTER is not pressed anymore
			//				Display->ENTER = false;
			//			}

			if(Display->VRx < Display->LowerLimit) {
				Display->CurrentModule = 1;	// forward to Distortion
				Display->JoystickParameterPosition = 1;	// reset JoystickParameterPosition
				Paint_DrawFilledRectangle(&paint, 1, 1, 200, 200, UNCOLORED);
				// Display the frame_buffer
				EPD_SetFrameMemory(&epd, frame_buffer, 0, 0, Paint_GetWidth(&paint), Paint_GetHeight(&paint));
				EPD_DisplayFrame(&epd);
			}
		}
		// #############################################
		// ############ END VOICES SUBMENU #############
		// #############################################


		// #############################################
		// ########## BEGIN DISTORTION SUBMENU #########
		// #############################################
		while(Display->CurrentModule == 1) {

			Paint_DrawStringAt(&paint, 1, 10, "Distortion", &Font16, COLORED);
			Paint_DrawStringAt(&paint, 1, 30, "Dist. ON/OFF", &Font12, COLORED);
			Paint_DrawStringAt(&paint, 1, 50, "Type", &Font12, COLORED);
			Paint_DrawStringAt(&paint, 1, 70, "Gain", &Font12, COLORED);

			Display->VRx = Display->ADC2inputs[0];		// read joystick x-value
			Display->VRy = Display->ADC2inputs[1];		// read joystick y-value
			Display->Poti_raw = Display->ADC2inputs[2];	// read poti-value

			char distortion_gain_string[9];
			sprintf(distortion_gain_string, "%f", Display->Distortion_Gain);

			if( (Display->JoystickParameterPosition == 1) && (Display->VRy > Display->LowerLimit) ) {
				Paint_DrawStringAt(&paint, 110, 30, "<---", &Font12, COLORED);	// arrow to Distortion ON/OFF
			}
			else if( (Display->JoystickParameterPosition == 1) && (Display->VRy < Display->LowerLimit) ) {
				Paint_DrawFilledRectangle(&paint, 110, 30, 150, 40, UNCOLORED);	// switch from Distortion ON/OFF to Type
				Paint_DrawStringAt(&paint, 110, 50, "<---", &Font12, COLORED);
				Display->JoystickParameterPosition = 2;
			}
			else if( (Display->JoystickParameterPosition == 2) && (Display->VRy > Display->UpperLimit) ) {
				Paint_DrawFilledRectangle(&paint, 110, 50, 150, 60, UNCOLORED);	// switch from Type to Distortion ON/OFF
				Paint_DrawStringAt(&paint, 110, 30, "<---", &Font12, COLORED);
				Display->JoystickParameterPosition = 1;
			}
			else if( (Display->JoystickParameterPosition == 2) && (Display->VRy < Display->LowerLimit) ) {
				Paint_DrawFilledRectangle(&paint, 110, 50, 150, 60, UNCOLORED);	// switch from Type to Gain
				Paint_DrawStringAt(&paint, 110, 70, "<---", &Font12, COLORED);
				Display->JoystickParameterPosition = 3;
			}
			else if( (Display->JoystickParameterPosition == 2) && (Display->VRy > Display->LowerLimit) && (Display->VRy < Display->UpperLimit) ) {
				Paint_DrawStringAt(&paint, 110, 50, "<---", &Font12, COLORED);	// arrow to Type
			}
			else if( (Display->JoystickParameterPosition == 3) && (Display->VRy > Display->UpperLimit) ) {
				Paint_DrawFilledRectangle(&paint, 110, 70, 150, 80, UNCOLORED);	// switch from Gain to Type
				Paint_DrawStringAt(&paint, 110, 50, "<---", &Font12, COLORED);
				Display->JoystickParameterPosition = 2;
			}
			else if( (Display->JoystickParameterPosition == 3) && (Display->VRy < Display->UpperLimit) ) {
				Paint_DrawStringAt(&paint, 110, 70, "<---", &Font12, COLORED);	// arrow to Gain
			}

			// check state of the potentiometer and assign parameter value
			// Distortion ON/OFF
			if(Display->JoystickParameterPosition == 1) {

				Paint_DrawFilledRectangle(&paint, 150, 30, 200, 50, UNCOLORED);

				if(Display->Poti_raw < Display->ADC_FullRange/2) {
					Paint_DrawStringAt(&paint, 150, 30, "OFF", &Font12, COLORED);
					Display->Distortion_ONOFF = false;
				}
				else if(Display->Poti_raw >= Display->ADC_FullRange/2) {
					Paint_DrawStringAt(&paint, 150, 30, "ON", &Font12, COLORED);
					Display->Distortion_ONOFF = true;
				}
			}

			// Distortion Type
			else if(Display->JoystickParameterPosition == 2) {

				Paint_DrawFilledRectangle(&paint, 150, 50, 200, 70, UNCOLORED);

				if(Display->Poti_raw < Display->ADC_FullRange/2) {
					Paint_DrawStringAt(&paint, 150, 50, "Soft Clipping", &Font12, COLORED);
					Display->Distortion_Type = 1;
				}
				else if(Display->Poti_raw >= Display->ADC_FullRange/2) {
					Paint_DrawStringAt(&paint, 150, 50, "Hard Clipping", &Font12, COLORED);
					Display->Distortion_Type = 1;
				}
			}

			// Distortion Gain
			else if(Display->JoystickParameterPosition == 3) {

				Paint_DrawFilledRectangle(&paint, 150, 70, 200, 90, UNCOLORED);
				Display->Distortion_Gain = (((float)Display->Poti_raw/4096) * HardClipping->distortion_maximum_gain) + 1;	// +1 to prevent 0
				sprintf(distortion_gain_string, "%f", Display->Distortion_Gain);
				distortion_gain = (uint16_t)(Display->Distortion_Gain * 1000);
			}

			if(Display->Distortion_ONOFF == true) {	// if Distortion ON

				if( abs(last_distortion_gain-distortion_gain)>1000 ) {

					HardClipping->distortion_gain = Display->Distortion_Gain;

					process_dist = true;

					//					if(Display->Distortion_EffectAdded == false) {	// if no distortion effect added yet
					//
					//						effects_add(DIST_H, Display->Distortion_EffectPosition);
					//						Display->Distortion_EffectAdded = true;
					//					}
				}
			}
			else if(Display->Distortion_ONOFF == false) {	// if Distortion OFF

				process_dist = false;

				//				if(Display->Distortion_EffectAdded == true) {
				//
				//					effects_delete(DIST_H, Display->Distortion_EffectPosition);
				//					Display->Distortion_EffectAdded = false;
				//				}
			}
			last_distortion_gain = distortion_gain;

			Paint_DrawStringAt(&paint, 150, 70, distortion_gain_string, &Font12, COLORED);
			// Display the frame_buffer
			EPD_SetFrameMemory(&epd, frame_buffer, 0, 0, Paint_GetWidth(&paint), Paint_GetHeight(&paint));
			EPD_DisplayFrame(&epd);

			//			// reset BACK-switch
			//			if(HAL_GPIO_ReadPin(BACK_GPIO_Port, BACK_Pin) == GPIO_PIN_RESET) {		// BACK is false and LED turned off in case that BACK-Button is not pressed anymore
			//				Display->BACK = false;
			//			}
			//			// reset ENTER-switch
			//			if(HAL_GPIO_ReadPin(ENTER_GPIO_Port, ENTER_Pin) == GPIO_PIN_RESET) {	// ENTER is false and LED turned off in case that ENTER is not pressed anymore
			//				Display->ENTER = false;
			//			}

			if(Display->VRx > Display->UpperLimit) {
				Display->CurrentModule = 0;	// back to Voices
				Display->JoystickParameterPosition = 1;	// reset JoystickParameterPosition
				Paint_DrawFilledRectangle(&paint, 1, 1, 200, 200, UNCOLORED);
				// Display the frame_buffer
				EPD_SetFrameMemory(&epd, frame_buffer, 0, 0, Paint_GetWidth(&paint), Paint_GetHeight(&paint));
				EPD_DisplayFrame(&epd);
			}
			else if(Display->VRx < Display->LowerLimit) {
				Display->CurrentModule = 2;	// forward to Tremolo
				Display->JoystickParameterPosition = 1;	// reset JoystickParameterPosition
				Paint_DrawFilledRectangle(&paint, 1, 1, 200, 200, UNCOLORED);
				// Display the frame_buffer
				EPD_SetFrameMemory(&epd, frame_buffer, 0, 0, Paint_GetWidth(&paint), Paint_GetHeight(&paint));
				EPD_DisplayFrame(&epd);
			}
		}
		// #############################################
		// ########## END DISTORTION SUBMENU ###########
		// #############################################


		// #############################################
		// ########### BEGIN TREMOLO SUBMENU ###########
		// #############################################
		while(Display->CurrentModule == 2) {

			Paint_DrawStringAt(&paint, 1, 10, "Tremolo", &Font16, COLORED);
			Paint_DrawStringAt(&paint, 1, 30, "Tremolo ON/OFF", &Font12, COLORED);
			Paint_DrawStringAt(&paint, 1, 50, "Rate", &Font12, COLORED);
			Paint_DrawStringAt(&paint, 1, 70, "Depth", &Font12, COLORED);

			Display->VRx = Display->ADC2inputs[0];		// read joystick x-value
			Display->VRy = Display->ADC2inputs[1];		// read joystick y-value
			Display->Poti_raw = Display->ADC2inputs[2];	// read poti-value

			//uint16_t last_rate, rate, last_depth, depth;
			char tremolo_rate_string[9];
			//sprintf(tremolo_rate_string, "%f", Display->Tremolo_Rate);
			char tremolo_depth_string[9];
			//sprintf(tremolo_depth_string, "%f", Display->Tremolo_Depth);

			if( (Display->JoystickParameterPosition == 1) && (Display->VRy > Display->LowerLimit) ) {
				Paint_DrawStringAt(&paint, 110, 30, "<---", &Font12, COLORED);	// arrow to Tremolo ON/OFF
			}
			else if( (Display->JoystickParameterPosition == 1) && (Display->VRy < Display->LowerLimit) ) {
				Paint_DrawFilledRectangle(&paint, 110, 30, 150, 40, UNCOLORED);	// switch from Tremolo ON/OFF to Rate
				Paint_DrawStringAt(&paint, 110, 50, "<---", &Font12, COLORED);
				Display->JoystickParameterPosition = 2;
			}
			else if( (Display->JoystickParameterPosition == 2) && (Display->VRy > Display->UpperLimit) ) {
				Paint_DrawFilledRectangle(&paint, 110, 50, 150, 60, UNCOLORED);	// switch from Rate to Tremolo ON/OFF
				Paint_DrawStringAt(&paint, 110, 30, "<---", &Font12, COLORED);
				Display->JoystickParameterPosition = 1;
			}
			else if( (Display->JoystickParameterPosition == 2) && (Display->VRy < Display->LowerLimit) ) {
				Paint_DrawFilledRectangle(&paint, 110, 50, 150, 60, UNCOLORED);	// switch from Rate to Depth
				Paint_DrawStringAt(&paint, 110, 70, "<---", &Font12, COLORED);
				Display->JoystickParameterPosition = 3;
			}
			else if( (Display->JoystickParameterPosition == 2) && (Display->VRy > Display->LowerLimit) && (Display->VRy < Display->UpperLimit) ) {
				Paint_DrawStringAt(&paint, 110, 50, "<---", &Font12, COLORED);	// arrow to Rate
			}
			else if( (Display->JoystickParameterPosition == 3) && (Display->VRy > Display->UpperLimit) ) {
				Paint_DrawFilledRectangle(&paint, 110, 70, 150, 80, UNCOLORED);	// switch from Depth to Rate
				Paint_DrawStringAt(&paint, 110, 50, "<---", &Font12, COLORED);
				Display->JoystickParameterPosition = 2;
			}
			else if( (Display->JoystickParameterPosition == 3) && (Display->VRy < Display->UpperLimit) ) {
				Paint_DrawStringAt(&paint, 110, 70, "<---", &Font12, COLORED);	// arrow to Depth
			}

			// check state of the potentiometer and assign parameter value
			// Tremolo ON/OFF
			if(Display->JoystickParameterPosition == 1) {

				Paint_DrawFilledRectangle(&paint, 150, 30, 200, 50, UNCOLORED);

				if(Display->Poti_raw < Display->ADC_FullRange/2) {
					Paint_DrawStringAt(&paint, 150, 30, "OFF", &Font12, COLORED);
					Display->Tremolo_ONOFF = false;
				}
				else if(Display->Poti_raw >= Display->ADC_FullRange/2) {
					Paint_DrawStringAt(&paint, 150, 30, "ON", &Font12, COLORED);
					Display->Tremolo_ONOFF = true;
				}
			}

			// Tremolo Rate
			else if(Display->JoystickParameterPosition == 2) {

				Paint_DrawFilledRectangle(&paint, 150, 50, 200, 70, UNCOLORED);
				Display->Tremolo_Rate = round( (((float)Display->Poti_raw/4096) * Tremolo->tremolo_maximum_rate) + 1);	// +1 to prevent 0
				sprintf(tremolo_rate_string, "%f", Display->Tremolo_Rate);
				rate = (uint16_t)(Display->Tremolo_Rate * 1000);
			}

			// Tremolo Depth
			else if(Display->JoystickParameterPosition == 3) {

				Paint_DrawFilledRectangle(&paint, 150, 70, 200, 90, UNCOLORED);
				Display->Tremolo_Depth = ((float)Display->Poti_raw/4096) * Tremolo->tremolo_maximum_depth;
				sprintf(tremolo_depth_string, "%f", Display->Tremolo_Depth);
				depth = (uint16_t)(Display->Tremolo_Depth * 1000);
			}

			if(Display->Tremolo_ONOFF == true) {	// if Tremolo ON

				Tremolo->lfo_frequency = Display->Tremolo_Rate;
				Tremolo->lfo_depth = Display->Tremolo_Depth;

				if( abs(last_rate-rate)>=1000 || abs(last_depth-depth)>=100 ) {

					process_trem = true;

//					if(Display->Tremolo_EffectAdded == false) {	// if no tremolo effect added yet
//
//						effects_add(TREM, Display->Tremolo_EffectPosition);
//						Display->Tremolo_EffectAdded = true;
//					}
				}
			}
			else if(Display->Tremolo_ONOFF == false) {	// if Tremolo OFF

				process_trem = false;

//				if(Display->Tremolo_EffectAdded == true) {
//
//					effects_delete(TREM, Display->Tremolo_EffectPosition);
//					Display->Tremolo_EffectAdded = false;
//				}
			}
			last_rate = rate;
			last_depth = depth;

			Paint_DrawStringAt(&paint, 150, 50, tremolo_rate_string, &Font12, COLORED);
			Paint_DrawStringAt(&paint, 150, 70, tremolo_depth_string, &Font12, COLORED);
			// Display the frame_buffer
			EPD_SetFrameMemory(&epd, frame_buffer, 0, 0, Paint_GetWidth(&paint), Paint_GetHeight(&paint));
			EPD_DisplayFrame(&epd);

//			// reset BACK-switch
//			if(HAL_GPIO_ReadPin(BACK_GPIO_Port, BACK_Pin) == GPIO_PIN_RESET) {		// BACK is false and LED turned off in case that BACK-Button is not pressed anymore
//				Display->BACK = false;
//			}
//			// reset ENTER-switch
//			if(HAL_GPIO_ReadPin(ENTER_GPIO_Port, ENTER_Pin) == GPIO_PIN_RESET) {	// ENTER is false and LED turned off in case that ENTER is not pressed anymore
//				Display->ENTER = false;
//			}

			if(Display->VRx > Display->UpperLimit) {
				Display->CurrentModule = 1;	// back to Distortion
				Display->JoystickParameterPosition = 1;	// reset JoystickParameterPosition
				Paint_DrawFilledRectangle(&paint, 1, 1, 200, 200, UNCOLORED);
				// Display the frame_buffer
				EPD_SetFrameMemory(&epd, frame_buffer, 0, 0, Paint_GetWidth(&paint), Paint_GetHeight(&paint));
				EPD_DisplayFrame(&epd);
			}
			else if(Display->VRx < Display->LowerLimit) {
				Display->CurrentModule = 3;	// forward to ADSR
				Display->JoystickParameterPosition = 1;	// reset JoystickParameterPosition
				Paint_DrawFilledRectangle(&paint, 1, 1, 200, 200, UNCOLORED);
				// Display the frame_buffer
				EPD_SetFrameMemory(&epd, frame_buffer, 0, 0, Paint_GetWidth(&paint), Paint_GetHeight(&paint));
				EPD_DisplayFrame(&epd);
			}
		}
		// #############################################
		// ########### END TREMOLO SUBMENU #############
		// #############################################


		// #############################################
		// ############ BEGIN ADSR SUBMENU #############
		// #############################################
		while(Display->CurrentModule == 3) {

			Paint_DrawStringAt(&paint, 1, 10, "ADSR", &Font16, COLORED);
			Paint_DrawStringAt(&paint, 1, 30, "ADSR ON/OFF", &Font12, COLORED);
			Paint_DrawStringAt(&paint, 1, 50, "Attack", &Font12, COLORED);
			Paint_DrawStringAt(&paint, 1, 70, "Decay", &Font12, COLORED);
			Paint_DrawStringAt(&paint, 1, 90, "Sustain", &Font12, COLORED);
			Paint_DrawStringAt(&paint, 1, 110, "Release", &Font12, COLORED);

			Display->VRx = Display->ADC2inputs[0];		// read joystick x-value
			Display->VRy = Display->ADC2inputs[1];		// read joystick y-value
			Display->Poti_raw = Display->ADC2inputs[2];	// read poti-value

			char attack_string[9];
			sprintf(attack_string, "%f", Display->ADSR_Attack);
			char decay_string[9];
			sprintf(decay_string, "%f", Display->ADSR_Decay);
			char sustain_string[9];
			sprintf(sustain_string, "%f", Display->ADSR_Sustain);
			char release_string[9];
			sprintf(release_string, "%f", Display->ADSR_Release);

			if( (Display->JoystickParameterPosition == 1) && (Display->VRy > Display->LowerLimit) ) {
				Paint_DrawStringAt(&paint, 110, 30, "<---", &Font12, COLORED);	// arrow to ADSR ON/OFF
			}
			else if( (Display->JoystickParameterPosition == 1) && (Display->VRy < Display->LowerLimit) ) {
				Paint_DrawFilledRectangle(&paint, 110, 30, 150, 40, UNCOLORED);	// switch from ADSR ON/OFF to Attack
				Paint_DrawStringAt(&paint, 110, 50, "<---", &Font12, COLORED);
				Display->JoystickParameterPosition = 2;
			}
			else if( (Display->JoystickParameterPosition == 2) && (Display->VRy > Display->UpperLimit) ) {
				Paint_DrawFilledRectangle(&paint, 110, 50, 150, 60, UNCOLORED);	// switch from Attack to ADSR ON/OFF
				Paint_DrawStringAt(&paint, 110, 30, "<---", &Font12, COLORED);
				Display->JoystickParameterPosition = 1;
			}
			else if( (Display->JoystickParameterPosition == 2) && (Display->VRy < Display->LowerLimit) ) {
				Paint_DrawFilledRectangle(&paint, 110, 50, 150, 60, UNCOLORED);	// switch from Attack to Decay
				Paint_DrawStringAt(&paint, 110, 70, "<---", &Font12, COLORED);
				Display->JoystickParameterPosition = 3;
			}
			else if( (Display->JoystickParameterPosition == 2) && (Display->VRy > Display->LowerLimit) && (Display->VRy < Display->UpperLimit) ) {
				Paint_DrawStringAt(&paint, 110, 50, "<---", &Font12, COLORED);	// arrow to Attack
			}
			else if( (Display->JoystickParameterPosition == 3) && (Display->VRy > Display->UpperLimit) ) {
				Paint_DrawFilledRectangle(&paint, 110, 70, 150, 80, UNCOLORED);	// switch from Decay to Attack
				Paint_DrawStringAt(&paint, 110, 50, "<---", &Font12, COLORED);
				Display->JoystickParameterPosition = 2;
			}
			else if( (Display->JoystickParameterPosition == 3) && (Display->VRy > Display->LowerLimit) && (Display->VRy < Display->UpperLimit) ) {
				Paint_DrawStringAt(&paint, 110, 70, "<---", &Font12, COLORED);	// arrow to Decay
			}
			else if( (Display->JoystickParameterPosition == 3) && (Display->VRy < Display->LowerLimit) ) {
				Paint_DrawFilledRectangle(&paint, 110, 70, 150, 80, UNCOLORED);	// switch from Decay to Sustain
				Paint_DrawStringAt(&paint, 110, 90, "<---", &Font12, COLORED);
				Display->JoystickParameterPosition = 4;
			}
			else if( (Display->JoystickParameterPosition == 4) && (Display->VRy > Display->UpperLimit) ) {
				Paint_DrawFilledRectangle(&paint, 110, 90, 150, 100, UNCOLORED);	// switch from Sustain to Decay
				Paint_DrawStringAt(&paint, 110, 70, "<---", &Font12, COLORED);
				Display->JoystickParameterPosition = 3;
			}
			else if( (Display->JoystickParameterPosition == 4) && (Display->VRy > Display->LowerLimit) && (Display->VRy < Display->UpperLimit) ) {
				Paint_DrawStringAt(&paint, 110, 90, "<---", &Font12, COLORED);	// arrow to Sustain
			}
			else if( (Display->JoystickParameterPosition == 4) && (Display->VRy < Display->LowerLimit) ) {
				Paint_DrawFilledRectangle(&paint, 110, 90, 150, 100, UNCOLORED);	// switch from Sustain to Release
				Paint_DrawStringAt(&paint, 110, 110, "<---", &Font12, COLORED);
				Display->JoystickParameterPosition = 5;
			}
			else if( (Display->JoystickParameterPosition == 5) && (Display->VRy > Display->UpperLimit) ) {
				Paint_DrawFilledRectangle(&paint, 110, 110, 150, 120, UNCOLORED);	// switch from Release to Sustain
				Paint_DrawStringAt(&paint, 110, 90, "<---", &Font12, COLORED);
				Display->JoystickParameterPosition = 4;
			}
			else if( (Display->JoystickParameterPosition == 5) && (Display->VRy < Display->UpperLimit) ) {
				Paint_DrawStringAt(&paint, 110, 110, "<---", &Font12, COLORED);	// arrow to Release
			}

			// check state of the potentiometer and assign parameter value
			// ADSR ON/OFF
			if( (Display->JoystickParameterPosition == 1) && (Display->Poti_raw < Display->ADC_FullRange/2) ) {
				Paint_DrawFilledRectangle(&paint, 150, 30, 200, 50, UNCOLORED);
				Paint_DrawStringAt(&paint, 150, 30, "OFF", &Font12, COLORED);
				Display->ADSR_ONOFF = false;
			}
			else if( (Display->JoystickParameterPosition == 1) && (Display->Poti_raw >= Display->ADC_FullRange/2) ) {
				Paint_DrawFilledRectangle(&paint, 150, 30, 200, 50, UNCOLORED);
				Paint_DrawStringAt(&paint, 150, 30, "ON", &Font12, COLORED);
				Display->ADSR_ONOFF = true;
			}

			// ADSR Attack
			else if(Display->JoystickParameterPosition == 2) {
				Paint_DrawFilledRectangle(&paint, 150, 50, 200, 70, UNCOLORED);
				Display->ADSR_Attack = ((float)Display->Poti_raw/4096) * envelope->adsr_maximum_attack;
				sprintf(attack_string, "%f", Display->ADSR_Attack);
				attack = (uint16_t)(Display->ADSR_Attack * 1000);
			}

			// ADSR Decay
			else if(Display->JoystickParameterPosition == 3) {
				Paint_DrawFilledRectangle(&paint, 150, 70, 200, 90, UNCOLORED);
				Display->ADSR_Decay = ((float)Display->Poti_raw/4096) * envelope->adsr_maximum_decay;
				sprintf(decay_string, "%f", Display->ADSR_Decay);
				decay = (uint16_t)(Display->ADSR_Decay * 1000);
			}

			// ADSR Sustain
			else if(Display->JoystickParameterPosition == 4) {
				Paint_DrawFilledRectangle(&paint, 150, 90, 200, 110, UNCOLORED);
				Display->ADSR_Sustain = ((float)Display->Poti_raw/4096) * envelope->adsr_max_amp;
				sprintf(sustain_string, "%f", Display->ADSR_Sustain);
				sustain = (uint16_t)(Display->ADSR_Sustain * 1000);
			}

			// ADSR Release
			else if(Display->JoystickParameterPosition == 5) {
				Paint_DrawFilledRectangle(&paint, 150, 110, 200, 130, UNCOLORED);
				Display->ADSR_Release = ((float)Display->Poti_raw/4096) * envelope->adsr_maximum_release;
				sprintf(release_string, "%f", Display->ADSR_Release);
				release = (uint16_t)(Display->ADSR_Release * 1000);
			}

			if(Display->ADSR_ONOFF == true) {	// if ADSR ON

				if( abs(last_attack-attack)>=100 || abs(last_decay-decay)>=100 || abs(last_sustain-sustain)>=100 || abs(last_release-release)>=100 ) {

					envelope->adsr_attack_time = Display->ADSR_Attack * LUT_SR;
					envelope->adsr_decay_time = Display->ADSR_Decay * LUT_SR;
					envelope->adsr_sustain_amplitude = Display->ADSR_Sustain;
					envelope->adsr_release_time = Display->ADSR_Release * LUT_SR;

					process_adsr = true;

//					if(Display->ADSR_EffectAdded == false) {	// if no adsr effect added yet
//						effects_add(ADSR, Display->ADSR_EffectPosition);
//						Display->ADSR_EffectAdded = true;
//					}
				}
			}
			else if(Display->ADSR_ONOFF == false) {	// if ADSR OFF

				process_adsr = false;

//				if(Display->ADSR_EffectAdded == true) {
//
//					effects_delete(ADSR, Display->ADSR_EffectPosition);
//					Display->ADSR_EffectAdded = false;
//				}
			}
			last_attack = attack;
			last_decay = decay;
			last_sustain = sustain;
			last_release = release;

			Paint_DrawStringAt(&paint, 150, 50, attack_string, &Font12, COLORED);
			Paint_DrawStringAt(&paint, 150, 70, decay_string, &Font12, COLORED);
			Paint_DrawStringAt(&paint, 150, 90, sustain_string, &Font12, COLORED);
			Paint_DrawStringAt(&paint, 150, 110, release_string, &Font12, COLORED);
			// Display the frame_buffer
			EPD_SetFrameMemory(&epd, frame_buffer, 0, 0, Paint_GetWidth(&paint), Paint_GetHeight(&paint));
			EPD_DisplayFrame(&epd);

//			// reset BACK-switch
//			if(HAL_GPIO_ReadPin(BACK_GPIO_Port, BACK_Pin) == GPIO_PIN_RESET) {		// BACK is false and LED turned off in case that BACK-Button is not pressed anymore
//				Display->BACK = false;
//			}
//			// reset ENTER-switch
//			if(HAL_GPIO_ReadPin(ENTER_GPIO_Port, ENTER_Pin) == GPIO_PIN_RESET) {	// ENTER is false and LED turned off in case that ENTER is not pressed anymore
//				Display->ENTER = false;
//			}

			if(Display->VRx > Display->UpperLimit) {
				Display->CurrentModule = 2;	// back to Tremolo
				Display->JoystickParameterPosition = 1;	// reset JoystickParameterPosition
				Paint_DrawFilledRectangle(&paint, 1, 1, 200, 200, UNCOLORED);
				// Display the frame_buffer
				EPD_SetFrameMemory(&epd, frame_buffer, 0, 0, Paint_GetWidth(&paint), Paint_GetHeight(&paint));
				EPD_DisplayFrame(&epd);
			}
			else if(Display->VRx < Display->LowerLimit) {
				Display->CurrentModule = 4;	// forward to Equalizer
				Display->JoystickParameterPosition = 1;	// reset JoystickParameterPosition
				Paint_DrawFilledRectangle(&paint, 1, 1, 200, 200, UNCOLORED);
				// Display the frame_buffer
				EPD_SetFrameMemory(&epd, frame_buffer, 0, 0, Paint_GetWidth(&paint), Paint_GetHeight(&paint));
				EPD_DisplayFrame(&epd);
			}

		}
		// #############################################
		// ############# END ADSR SUBMENU ##############
		// #############################################


		// #############################################
		// ########## BEGIN EQUALIZER SUBMENU ##########
		// #############################################
		while(Display->CurrentModule == 4) {

//			Paint_DrawStringAt(&paint, 1, 10, "Equalizer", &Font16, COLORED);
//			Paint_DrawStringAt(&paint, 1, 30, "Band1 ON/OFF", &Font12, COLORED);
//			Paint_DrawStringAt(&paint, 1, 50, "Band1 Q", &Font12, COLORED);
//			Paint_DrawStringAt(&paint, 1, 70, "Band1 Gain", &Font12, COLORED);
//			Paint_DrawStringAt(&paint, 1, 90, "Band1 Cutoff", &Font12, COLORED);
			Paint_DrawStringAt(&paint, 1, 10, "Tiefpassfilter", &Font16, COLORED);
			Paint_DrawStringAt(&paint, 1, 30, "Filter ON/OFF", &Font12, COLORED);
			Paint_DrawStringAt(&paint, 1, 50, "Cutoff", &Font12, COLORED);
			Paint_DrawStringAt(&paint, 1, 70, "Güte", &Font12, COLORED);

			Display->VRx = Display->ADC2inputs[0];		// read joystick x-value
			Display->VRy = Display->ADC2inputs[1];		// read joystick y-value
			Display->Poti_raw = Display->ADC2inputs[2];	// read poti-value

			char filter_cutoff_string[9];
			//sprintf(filter_cutoff_string, "%f", Display->Filter_Cutoff);
			char filter_Q_string[9];
			//sprintf(filter_Q_string, "%f", Display->Filter_Q);

			if( (Display->JoystickParameterPosition == 1) && (Display->VRy > Display->LowerLimit) ) {
				Paint_DrawStringAt(&paint, 110, 30, "<---", &Font12, COLORED);	// arrow to Filter ON/OFF
			}
			else if( (Display->JoystickParameterPosition == 1) && (Display->VRy < Display->LowerLimit) ) {
				Paint_DrawFilledRectangle(&paint, 110, 30, 150, 40, UNCOLORED);	// switch from Filter ON/OFF to Cutoff
				Paint_DrawStringAt(&paint, 110, 50, "<---", &Font12, COLORED);
				Display->JoystickParameterPosition = 2;
			}
			else if( (Display->JoystickParameterPosition == 2) && (Display->VRy > Display->UpperLimit) ) {
				Paint_DrawFilledRectangle(&paint, 110, 50, 150, 60, UNCOLORED);	// switch from Cutoff to Filter ON/OFF
				Paint_DrawStringAt(&paint, 110, 30, "<---", &Font12, COLORED);
				Display->JoystickParameterPosition = 1;
			}
			else if( (Display->JoystickParameterPosition == 2) && (Display->VRy < Display->LowerLimit) ) {
				Paint_DrawFilledRectangle(&paint, 110, 50, 150, 60, UNCOLORED);	// switch from Cutoff to Q
				Paint_DrawStringAt(&paint, 110, 70, "<---", &Font12, COLORED);
				Display->JoystickParameterPosition = 3;
			}
			else if( (Display->JoystickParameterPosition == 2) && (Display->VRy > Display->LowerLimit) && (Display->VRy < Display->UpperLimit) ) {
				Paint_DrawStringAt(&paint, 110, 50, "<---", &Font12, COLORED);	// arrow to Cutoff
			}
			else if( (Display->JoystickParameterPosition == 3) && (Display->VRy > Display->UpperLimit) ) {
				Paint_DrawFilledRectangle(&paint, 110, 70, 150, 80, UNCOLORED);	// switch from Q to Cutoff
				Paint_DrawStringAt(&paint, 110, 50, "<---", &Font12, COLORED);
				Display->JoystickParameterPosition = 2;
			}
			else if( (Display->JoystickParameterPosition == 3) && (Display->VRy < Display->UpperLimit) ) {
				Paint_DrawStringAt(&paint, 110, 70, "<---", &Font12, COLORED);	// arrow to Q
			}

			// check state of the potentiometer and assign parameter value
			// Filter ON/OFF
			if(Display->JoystickParameterPosition == 1) {

				Paint_DrawFilledRectangle(&paint, 150, 30, 200, 50, UNCOLORED);

				if(Display->Poti_raw < Display->ADC_FullRange/2) {
					Paint_DrawStringAt(&paint, 150, 30, "OFF", &Font12, COLORED);
					Display->Filter_ONOFF = false;
				}
				else if(Display->Poti_raw >= Display->ADC_FullRange/2) {
					Paint_DrawStringAt(&paint, 150, 30, "ON", &Font12, COLORED);
					Display->Filter_ONOFF = true;
				}
			}

			// Filter Cutoff
			else if(Display->JoystickParameterPosition == 2) {

				Paint_DrawFilledRectangle(&paint, 150, 50, 200, 70, UNCOLORED);
				Display->Filter_Cutoff = round( (((float)Display->Poti_raw/4096) * 4000) + 1);	// +1 to prevent 0; 4000 Hz maximum cutoff
				sprintf(filter_cutoff_string, "%f", Display->Filter_Cutoff);
				cutoff = (uint16_t)(Display->Filter_Cutoff * 1000);
			}

			// Filter Q
			else if(Display->JoystickParameterPosition == 3) {

				Paint_DrawFilledRectangle(&paint, 150, 70, 200, 90, UNCOLORED);
				Display->Filter_Q = (float)Display->Poti_raw/4096;	// maximum Q of 1
				sprintf(filter_Q_string, "%f", Display->Filter_Q);
				Q = (uint16_t)(Display->Filter_Q * 1000);
			}

			if(Display->Filter_ONOFF == true) {	// if Filter ON

				if( abs(last_cutoff-cutoff)>=1000 || abs(last_Q-Q)>=100 ) {

					SetupLowpass(&EQ_BAND1_I, Display->Filter_Cutoff, Display->Filter_Q);

					process_filter = true;

//					if(Display->Filter_EffectAdded == false) {	// if no filter effect added yet
//
//						effects_add(EQ, Display->Filter_EffectPosition);
//						Display->Filter_EffectAdded = true;
//					}
				}
			}
			else if(Display->Filter_ONOFF == false) {	// if Filter OFF

				process_filter = false;

//				if(Display->Filter_EffectAdded == true) {
//					effects_delete(EQ, Display->Filter_EffectPosition);
//					Display->Filter_EffectAdded = false;
//				}
			}
			last_cutoff = cutoff;
			last_Q = Q;

			Paint_DrawStringAt(&paint, 150, 50, filter_cutoff_string, &Font12, COLORED);
			Paint_DrawStringAt(&paint, 150, 70, filter_Q_string, &Font12, COLORED);
			// Display the frame_buffer
			EPD_SetFrameMemory(&epd, frame_buffer, 0, 0, Paint_GetWidth(&paint), Paint_GetHeight(&paint));
			EPD_DisplayFrame(&epd);

			if(Display->VRx > Display->UpperLimit) {
				Display->CurrentModule = 3;	// back to ADSR
				Display->JoystickParameterPosition = 1;	// reset JoystickParameterPosition
				Paint_DrawFilledRectangle(&paint, 1, 1, 200, 200, UNCOLORED);
				// Display the frame_buffer
				EPD_SetFrameMemory(&epd, frame_buffer, 0, 0, Paint_GetWidth(&paint), Paint_GetHeight(&paint));
				EPD_DisplayFrame(&epd);
			}
		}
		// #############################################
		// ########## END EQUALIZER SUBMENU ############
		// #############################################
	}
}*/

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {

	if((GPIO_Pin == BACK_Pin) && (Display.BACK_Debounce_State == true)) {
		HAL_GPIO_TogglePin(Red_User_LED_GPIO_Port, Red_User_LED_Pin);		// red led
		HAL_TIM_Base_Start_IT(&htim2);
		Display.BACK_Debounce_State = false;
	}
	else if((GPIO_Pin == ENTER_Pin) && (Display.ENTER_Debounce_State == true)) {
		HAL_GPIO_TogglePin(Blue_User_LED_GPIO_Port, Blue_User_LED_Pin);		// blue led
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
		//if(HAL_GPIO_ReadPin(BACK_GPIO_Port, BACK_Pin) == GPIO_PIN_RESET) {
		if(HAL_GPIO_ReadPin(BACK_GPIO_Port, BACK_Pin) == GPIO_PIN_SET) {
			Display.BACK = true;
			Display.BACK_Debounce_State = true;
			HAL_TIM_Base_Stop_IT(&htim2);
		}
	}
	else if(htim->Instance == TIM4) {
		if(HAL_GPIO_ReadPin(ENTER_GPIO_Port, ENTER_Pin) == GPIO_PIN_SET) {
			Display.ENTER = true;
			Display.ENTER_Debounce_State = true;
			HAL_TIM_Base_Stop_IT(&htim4);
		}
	}
	else {
		__NOP();
	}
}


/*void RequestPatchParameters(struct PatchControls* Patch1, bool* ChosenGadget, bool* PatchParameterAssign, bool* Patch, Paint paint, EPD epd, unsigned char* frame_buffer) {

	if((Patch[0]==true) && (PatchParameterAssign[0]==false)) {		// Patch 1 selected

		// VCO1 Frequency-gadget-assignment
		Paint_Clear(&paint, UNCOLORED);	// clear display

		Paint_DrawStringAt(&paint, 1, 10, "Choose a Trigger", &Font12, COLORED);
		Paint_DrawStringAt(&paint, 1, 20, "for OSC1 Frequency!", &Font12, COLORED);
		Paint_DrawStringAt(&paint, 1, 40, "Move a gadget!", &Font12, COLORED);
		EPD_SetFrameMemory(&epd, frame_buffer, 0, 0, Paint_GetWidth(&paint), Paint_GetHeight(&paint));	// Display the frame_buffer
		EPD_DisplayFrame(&epd);

		while( (ChosenGadget[0]==false) && (ChosenGadget[2]==false) && (ChosenGadget[5]==false)) {

			Poti_raw	= ADC2inputs[2];
			EMG_DC1		= ADC2inputs[4];
			GyroX		= ADC3inputs[2];

			if((abs(last_Poti_raw-Poti_raw)>=50))		ChosenGadget[0] = true;

			else if((abs(last_EMG_DC1-EMG_DC1)>=50))	ChosenGadget[2] = true;

			//else if((abs(last_GyroX-GyroX)>=50))		ChosenGadget[5] = true;
		}

		Paint_Clear(&paint, UNCOLORED);	// clear display

		if(ChosenGadget[0]) {
			Paint_DrawStringAt(&paint, 1, 20, "Poti controls OSC1 Frequency", &Font12, COLORED);
			ChosenGadget[0] = false;

			// Reihenfolge der Eingabegeräte: Poti_raw, EMG_AC1, EMG_DC1, EMG_AC2, EMG_DC2, GyroX, GyroY, GyroZ
			strcpy(Patch1->Gadgetname[0], "Poti");
			strcpy(Patch1->Parametername[0], "Osc1Frequency");
			Patch1->ParameterValue[0] = Poti_raw;
		}
		else if(ChosenGadget[2]) {
			Paint_DrawStringAt(&paint, 1, 20, "EMG_DC1 controls OSC1 Frequency", &Font12, COLORED);
			ChosenGadget[2] = false;

			strcpy(Patch1->Gadgetname[2], "EMG1_DC1");
			strcpy(Patch1->Parametername[1], "Osc1Frequency");
			Patch1->ParameterValue[2] = EMG_DC1;
		}
		else if(ChosenGadget[5]) {
			Paint_DrawStringAt(&paint, 1, 20, "GyroX controls OSC1 Frequency", &Font12, COLORED);
			ChosenGadget[5] = false;
		}
		EPD_SetFrameMemory(&epd, frame_buffer, 0, 0, Paint_GetWidth(&paint), Paint_GetHeight(&paint));	// Display the frame_buffer
		EPD_DisplayFrame(&epd);

		last_Poti_raw 	= ADC2inputs[2];
		last_EMG_DC1 	= ADC2inputs[4];
		last_GyroX 		= ADC3inputs[2];

		// VCF1 Cutoff-gadget-assignment
		Paint_Clear(&paint, UNCOLORED);	// clear display

		Paint_DrawStringAt(&paint, 1, 10, "Choose a Trigger", &Font12, COLORED);
		Paint_DrawStringAt(&paint, 1, 20, "for VCF1 Cutoff-Frequency!", &Font12, COLORED);
		Paint_DrawStringAt(&paint, 1, 40, "Move a gadget!", &Font12, COLORED);
		EPD_SetFrameMemory(&epd, frame_buffer, 0, 0, Paint_GetWidth(&paint), Paint_GetHeight(&paint));	// Display the frame_buffer
		EPD_DisplayFrame(&epd);

		while( (ChosenGadget[0]==false) && (ChosenGadget[2]==false) && (ChosenGadget[5]==false)) {

			Poti_raw	= ADC2inputs[2];
			EMG_DC1		= ADC2inputs[4];
			GyroX		= ADC3inputs[2];

			if((abs(last_Poti_raw-Poti_raw)>=50))		ChosenGadget[0] = true;

			else if((abs(last_EMG_DC1-EMG_DC1)>=50))	ChosenGadget[2] = true;

			//else if((abs(last_GyroX-GyroX)>=50))		ChosenGadget[5] = true;
		}

		Paint_Clear(&paint, UNCOLORED);	// clear display
		EPD_SetFrameMemory(&epd, frame_buffer, 0, 0, Paint_GetWidth(&paint), Paint_GetHeight(&paint));
		EPD_DisplayFrame(&epd);

		if(ChosenGadget[0]) {
			Paint_DrawStringAt(&paint, 1, 20, "Poti controls VCF1 Cutoff", &Font12, COLORED);
			ChosenGadget[0] = false;
		}
		else if(ChosenGadget[2]) {
			Paint_DrawStringAt(&paint, 1, 20, "EMG_DC1 controls VCF1 Cutoff", &Font12, COLORED);
			ChosenGadget[2] = false;
		}
		else if(ChosenGadget[5]) {
			Paint_DrawStringAt(&paint, 1, 20, "GyroX controls VCF1 Cutoff", &Font12, COLORED);
			ChosenGadget[5] = false;
		}
		EPD_SetFrameMemory(&epd, frame_buffer, 0, 0, Paint_GetWidth(&paint), Paint_GetHeight(&paint));	// Display the frame_buffer
		EPD_DisplayFrame(&epd);
		EPD_SetFrameMemory(&epd, frame_buffer, 0, 0, Paint_GetWidth(&paint), Paint_GetHeight(&paint));
		EPD_DisplayFrame(&epd);

		last_Poti_raw 	= Poti_raw;
		last_EMG_DC1	= EMG_DC1;
		//last_GyroX 	= GyroX;

		PatchParameterAssign[0] = true;
	}

	else if((Patch[1]==true) && (PatchParameterAssign[1]==false)) {	// Patch 2 selected
		// ...
		PatchParameterAssign[1] = true;
	}

	else if((Patch[2]==true) && (PatchParameterAssign[2]==false)) {	// Patch 3 selected
		// ...
		PatchParameterAssign[2] = true;
	}
}*/
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
