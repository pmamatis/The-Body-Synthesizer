/*
 * emg.c
 *
 *  Created on: May 23, 2021
 *      Author: paul
 */

#include "emg.h"


void emg_init(ADC_HandleTypeDef *ADC_Handler){
	EMG_ADC = ADC_Handler;
}

HAL_StatusTypeDef emg_start_read(){
	return HAL_ADC_Start_DMA(EMG_ADC, emg_buffer, EMG_READ_LENGTH);
}

HAL_StatusTypeDef emg_stop_read(){
	return HAL_ADC_Stop_DMA(EMG_ADC);
}
