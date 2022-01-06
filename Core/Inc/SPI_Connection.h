#ifndef INC_SPI_CONNECTION_H_
#define INC_SPI_CONNECTION_H_
#include "main.h"

/*********************************
 * @brief		Defines
 *********************************/
#define BUFFERSIZE sizeof(sensor_data_t)
#define SPI_SR 50 // SPI sampling rate

/*********************************
 * @brief		Structs
 *********************************/
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

#endif /* INC_SPI_CONNECTION_H_ */
