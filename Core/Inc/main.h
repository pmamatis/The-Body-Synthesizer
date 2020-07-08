/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "stm32f7xx_hal.h"
#include "signal_synthesis.h"
#include "music_notes.h"
#include "sinLUT.h"


/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
/* USER CODE BEGIN Private defines */



/**@brief number of support points for a single period*/
#define SUPPORT_POINTS 20

/**@brief output array size */
#define BLOCKSIZE 24000

/**@brief minimal frequency fittinig in the output-array */
#define F_MIN 5

/**@brief maximal frequency available with selected SUPPORT_POINTS*/
#define F_MAX 4800

/**@brief counter period of the timer 8 */
#define COUNTER_PERIOD 200-1

/**@brief timer clock */
#define CLOCK 9600000

/**@brief frequency of SIgnal if just one  whole period is writen into the vector, calculatet with Matlab */
#define SAMPLE_FREQ CLOCK/COUNTER_PERIOD
//#define SAMPLE_FREQ_REAL 96354

//Variables

/** @brief signal array*/
//float calculate_vector[BLOCKSIZE+1];

/** @brief DAC output array*/
uint32_t output_vector1[BLOCKSIZE];
uint32_t output_vector2[BLOCKSIZE];

float sigFreq_sampleFreq_ratio;

/** @brief index from the calculate vector with the last zero*/
uint32_t lastIndex;



/** @brief enum for DMA Output buffer position */
enum outputBuffer_position_enum{
	HALF_BLOCK = 0,
	FULL_BLOCK
};

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
