/**
 * @file SPI_Connection.c
 * @author paul mamatis
 * @brief spi connetcion to another STM32
 * @version 0.1
 * @date 2022-01-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "SPI_Connection.h"

/**
 * @brief spi connection init
 * 
 * @param hspi 
 * @param htim timer which triggers the spi read command
 */
void spiC_Init(SPI_HandleTypeDef *hspi, TIM_HandleTypeDef *htim){

	hSensorSPI= hspi;

	for (int spiinit_counter=0; spiinit_counter < BUFFERSIZE;spiinit_counter++){
		pTxData[spiinit_counter] = 0;
		pRxData[spiinit_counter] = 0;
	}

	SetTimerSettings(htim,SPI_SR);
	HAL_TIM_Base_Start_IT(htim);
}
