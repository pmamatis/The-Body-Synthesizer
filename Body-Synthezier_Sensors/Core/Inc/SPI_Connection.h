/*
 * SPI_Connection.h
 *
 *  Created on: Jul 24, 2021
 *      Author: paul
 */

#ifndef INC_SPI_CONNECTION_H_
#define INC_SPI_CONNECTION_H_

#include "main.h"
#pragma pack(push, 1)
typedef struct sensor_data{
 uint8_t	dump_zeroes_start[3];
 uint8_t gyro_initilized;
 uint8_t tilt_detecded;
 uint8_t movement_detected;
 uint8_t HIGH_DOWN_MovementDetected;
 uint8_t RIGHT_LEFT_MovementDetected;

 uint8_t	dump_zeroes_end[3];
}sensor_data_t;
#pragma pack(pop)

#define BUFFERSIZE sizeof(sensor_data_t)


#endif /* INC_SPI_CONNECTION_H_ */



