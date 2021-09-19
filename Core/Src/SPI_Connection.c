/*
 * SPI_Connection.c
 *
 *  Created on: Aug 24, 2021
 *      Author: paul
 */

#include "SPI_Connection.h"

void spiC_Init(SPI_HandleTypeDef *hspi, TIM_HandleTypeDef *htim) {

	hSensorSPI = hspi;
	for (int spiinit_counter=0; spiinit_counter < BUFFERSIZE;spiinit_counter++) {
		pTxData[spiinit_counter] = 0;
		pRxData[spiinit_counter] = 0;
	}
	SetTimerSettings(htim,SPI_SR);
	HAL_TIM_Base_Start_IT(htim);
}
