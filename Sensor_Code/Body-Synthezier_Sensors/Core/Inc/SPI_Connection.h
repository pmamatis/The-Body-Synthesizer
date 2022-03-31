/**
 * @file SPI_Connection.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date Jul 24, 2021
 * 
 * @copyright Copyright (c) 2022
 * 
 */



/**
 * @defgroup SPI SPI-Connection  
 * @ingroup SensorSTM
 * @brief SPI-Connection on the STMF4 side
 * @{
 */

#ifndef INC_SPI_CONNECTION_H_
#define INC_SPI_CONNECTION_H_

#include "main.h"
#pragma pack(push, 1)
typedef struct sensor_data{
 uint8_t	dump_zeroes_start[3];

 uint8_t gyro_initilized;
 uint8_t tilt_detected;
// uint8_t Movement_detected;

 uint8_t	dump_zeroes_end[3];
}sensor_data_t;
#pragma pack(pop)

#define BUFFERSIZE sizeof(sensor_data_t)

/**
 * @} 
 * 
 */

#endif /* INC_SPI_CONNECTION_H_ */



