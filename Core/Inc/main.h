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
#include "effects.h"

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
#define BLOCKSIZE 8192
//#define BLOCKSIZE 2048

//Variables

/** @brief DAC output array*/
uint32_t output_vector1[BLOCKSIZE];
float calculate_vector1[BLOCKSIZE];

uint32_t output_vector2[BLOCKSIZE];
float calculate_vector2[BLOCKSIZE];

struct effects_LFO tremollo;
float effect_LFO[BLOCKSIZE/2];
//float effect_LFO[BLOCKSIZE];	// DEBUG
uint32_t effect_LFO_output[BLOCKSIZE];

struct effects_distortion distortion;
float atan_LUT_y[BLOCKSIZE];
float aquidistance;

float sigFreq_sampleFreq_ratio;

/*// Basic Delay Effect Variables
float *delayData; // Our own circular buffer of samples
#define delayBufLength 1000 // Length of our delay buffer in samples
uint32_t dpr, dpw; // Read/write pointers into delay buffer
float delay_out;
// User-adjustable effect parameters:
float dryMix; // Level of the dry (undelayed) signal
float wetMix; // Level of the wet (delayed) signal
float feedback_level; // Feedback level (0 if no feedback)*/


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
