/**
 * @file SPI_Connection.h
 * @author paul mamatis
 * @brief spi connection to other STM, where the MPU6050 is processed
 * @version 0.1
 * @date 2022-01-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef INC_SPI_CONNECTION_H_
#define INC_SPI_CONNECTION_H_

/**
 * @defgroup Gyro Groyscop and accelerometer sensor SPI connection
 * @ingroup InputDevice
 * @brief functions and variables to decode the Gyro/Accl information receiced via the SPI
 * @{
 */

#include "main.h"

/*********************************
 * @brief		Defines
 *********************************/
#define BUFFERSIZE sizeof(sensor_data_t)
#define SPI_SR 50 // SPI sampling rate

/*********************************
 * @brief		Structs
 *********************************/

/**
 * @brief tilt directions Flags, from MPU6050
 * 
 */
typedef enum  tilt_direction_t{
  TILT_NONE  = 0x00,
  TILT_RIGHT = 0x01,
  TILT_LEFT,
  TILT_FRONT,
  TILT_BACK,
  TILT_RIGHT_S,
  TILT_LEFT_S,
  TILT_FRONT_S,
  TILT_BACK_S
} tilt_direction_t;

#pragma pack(push, 1)
typedef struct sensor_data{
	uint8_t gyro_initilized;
	uint8_t tilt_detected;
} sensor_data_t;
#pragma pack(pop)

/*********************************
 * @brief		Variables
 *********************************/
sensor_data_t sensorData;
SPI_HandleTypeDef* hSensorSPI;
uint8_t pTxData[sizeof(sensor_data_t)];
uint8_t pRxData[sizeof(sensor_data_t)];

/*********************************
 * @brief		Functions
 *********************************/
void spiC_Init(SPI_HandleTypeDef *hspi, TIM_HandleTypeDef *htim);
/** @} */ 
#endif /* INC_SPI_CONNECTION_H_ */
