/*
 * SPI_Connection.h
 *
 *  Created on: Jul 24, 2021
 *      Author: paul
 */

#ifndef INC_SPI_CONNECTION_H_
#define INC_SPI_CONNECTION_H_
#include "main.h"
typedef enum  tilt_direction_t{

	TILT_NONE  = 0x00,
	TILT_RIGHT = 0x01,
	TILT_LEFT,
	TILT_FRONT,
	TILT_BACK
}tilt_direction_t;

#pragma pack(push, 1)
typedef struct sensor_data{
 uint8_t	dump_zeroes_start[3];
 uint8_t gyro_initilized;
 uint8_t tilt_detected;
 uint8_t	dump_zeroes_end[3];
}sensor_data_t;
#pragma pack(pop)

sensor_data_t sensorData;
SPI_HandleTypeDef* hSensorSPI;
uint8_t pTxData[ sizeof(sensor_data_t)];
uint8_t pRxData[ sizeof(sensor_data_t)];

void spiC_Init(SPI_HandleTypeDef *hspi, TIM_HandleTypeDef *htim);


#define BUFFERSIZE sizeof(sensor_data_t)
#define SPI_SR 50 //spi SAMPLE rate

#endif /* INC_SPI_CONNECTION_H_ */



