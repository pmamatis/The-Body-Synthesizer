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
#include "filters.h"
#include "tremolo.h"
#include "distortion.h"
#include "adsr.h"
#include <stdbool.h>

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
#define ENTER_USER_Pin GPIO_PIN_13
#define ENTER_USER_GPIO_Port GPIOC
#define ENTER_USER_EXTI_IRQn EXTI15_10_IRQn
#define SD_CS_Pin GPIO_PIN_10
#define SD_CS_GPIO_Port GPIOF
#define Poti_Pin GPIO_PIN_0
#define Poti_GPIO_Port GPIOC
#define EMG_AC1_Pin GPIO_PIN_2
#define EMG_AC1_GPIO_Port GPIOC
#define EMG_DC1_Pin GPIO_PIN_3
#define EMG_DC1_GPIO_Port GPIOC
#define DISP_DC_Pin GPIO_PIN_0
#define DISP_DC_GPIO_Port GPIOA
#define DISP_RST_Pin GPIO_PIN_3
#define DISP_RST_GPIO_Port GPIOA
#define DISP_CLK_Pin GPIO_PIN_5
#define DISP_CLK_GPIO_Port GPIOA
#define VRx_Pin GPIO_PIN_6
#define VRx_GPIO_Port GPIOA
#define DISP_DIN_Pin GPIO_PIN_7
#define DISP_DIN_GPIO_Port GPIOA
#define VRy_Pin GPIO_PIN_0
#define VRy_GPIO_Port GPIOB
#define DISP_BUSY_Pin GPIO_PIN_1
#define DISP_BUSY_GPIO_Port GPIOB
#define SD_DI_MOSI_Pin GPIO_PIN_2
#define SD_DI_MOSI_GPIO_Port GPIOB
#define SW_Pin GPIO_PIN_0
#define SW_GPIO_Port GPIOG
#define ENTER_Pin GPIO_PIN_8
#define ENTER_GPIO_Port GPIOE
#define ENTER_EXTI_IRQn EXTI9_5_IRQn
#define Red_User_LED_Pin GPIO_PIN_14
#define Red_User_LED_GPIO_Port GPIOB
#define DISP_CS_Pin GPIO_PIN_8
#define DISP_CS_GPIO_Port GPIOC
#define BACK_Pin GPIO_PIN_9
#define BACK_GPIO_Port GPIOC
#define BACK_EXTI_IRQn EXTI9_5_IRQn
#define SD_CLK_Pin GPIO_PIN_10
#define SD_CLK_GPIO_Port GPIOC
#define SD_DO_MISO_Pin GPIO_PIN_11
#define SD_DO_MISO_GPIO_Port GPIOC
#define Blue_User_LED_Pin GPIO_PIN_7
#define Blue_User_LED_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/**@brief number of support points for a single period*/
#define SUPPORT_POINTS 20

/**@brief output array size */
#define BLOCKSIZE 8192
//#define BLOCKSIZE 2048

//Variables

/** @brief DAC output array*/
//uint32_t output_vector1[BLOCKSIZE];
float calculate_vector1[BLOCKSIZE];

//uint32_t output_vector2[BLOCKSIZE];
float calculate_vector2[BLOCKSIZE];

float effect_LFO[BLOCKSIZE/2];	// Original!!!
//float effect_LFO[BLOCKSIZE];
//uint32_t effect_LFO_output[BLOCKSIZE];

float sigFreq_sampleFreq_ratio;

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
