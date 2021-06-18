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

// for filters
#include "filters.h"
#include "arm_math.h"
#include "math_helper.h"

// for tremolo
#include "tremolo.h"

// for distortion
#include "distortion.h"

// EMG
#include "emg.h"

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
#define GYRO_I2C_SDA_Pin GPIO_PIN_0
#define GYRO_I2C_SDA_GPIO_Port GPIOF
#define GYRO_I2C_SCL_Pin GPIO_PIN_1
#define GYRO_I2C_SCL_GPIO_Port GPIOF
#define ADC_EMG_DC_Pin GPIO_PIN_6
#define ADC_EMG_DC_GPIO_Port GPIOF
#define ADC_EMG_AC_Pin GPIO_PIN_7
#define ADC_EMG_AC_GPIO_Port GPIOF
#define SD_CS_Pin GPIO_PIN_10
#define SD_CS_GPIO_Port GPIOF
#define ADC_Poti_Pin GPIO_PIN_0
#define ADC_Poti_GPIO_Port GPIOC
#define ADC_Keyboard_Pin GPIO_PIN_2
#define ADC_Keyboard_GPIO_Port GPIOC
#define DISP_DC_Pin GPIO_PIN_0
#define DISP_DC_GPIO_Port GPIOA
#define Joystick_VRx_Pin GPIO_PIN_6
#define Joystick_VRx_GPIO_Port GPIOA
#define Joystick_VRy_Pin GPIO_PIN_0
#define Joystick_VRy_GPIO_Port GPIOB
#define DISP_BUSY_Pin GPIO_PIN_1
#define DISP_BUSY_GPIO_Port GPIOB
#define SD_DI_MOSI_Pin GPIO_PIN_2
#define SD_DI_MOSI_GPIO_Port GPIOB
#define DISP_RST_Pin GPIO_PIN_12
#define DISP_RST_GPIO_Port GPIOF
#define Joystick_SW_Pin GPIO_PIN_0
#define Joystick_SW_GPIO_Port GPIOG
#define Button_Enter_Pin GPIO_PIN_8
#define Button_Enter_GPIO_Port GPIOE
#define DISP_CS_Pin GPIO_PIN_8
#define DISP_CS_GPIO_Port GPIOC
#define Button_Back_Pin GPIO_PIN_9
#define Button_Back_GPIO_Port GPIOC
#define SD_CLK_Pin GPIO_PIN_10
#define SD_CLK_GPIO_Port GPIOC
#define SD_DO_MISO_Pin GPIO_PIN_11
#define SD_DO_MISO_GPIO_Port GPIOC
#define DISP_CLK_Pin GPIO_PIN_3
#define DISP_CLK_GPIO_Port GPIOB
#define DISP_DIN_Pin GPIO_PIN_5
#define DISP_DIN_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/**@brief number of support points for a single period*/
#define SUPPORT_POINTS 20

/**@brief output array size */
//#define BLOCKSIZE 8192 //
#define BLOCKSIZE 8192/4 // Latenz

//Variables

/** @brief DAC output array*/
//uint32_t output_vector1[BLOCKSIZE];
float calculate_vector1[BLOCKSIZE];

//uint32_t output_vector2[BLOCKSIZE];
float calculate_vector2[BLOCKSIZE];

float effect_LFO[BLOCKSIZE/2];
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
