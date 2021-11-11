/*
 * emg.c
 *
 *  Created on: May 23, 2021
 *      Author: paul
 */

#include "emg.h"


//void emg_init(ADC_HandleTypeDef *ADC_Handler){
//	EMG_ADC = ADC_Handler;
//}

HAL_StatusTypeDef emg_init(ADC_HandleTypeDef *hadc, TIM_HandleTypeDef *htim){

	EMG_ADC = hadc;
	EMG_TIM = htim;
	detectionThreshold = 250;
	emg_peak = 0;
	toggled = 0;

	toggleThreshold = 20;
	toggleCounter = toggleThreshold;

	// TODO: Werte durch Testen anpassen!!
	maxDetectionThreshold = 500;
	maxToggleThreshold = 50;

	return HAL_OK;
}

HAL_StatusTypeDef emg_start_read(void){

	SetTimerSettings(EMG_TIM, EMG_SR);
	HAL_TIM_Base_Start(EMG_TIM);
	printf("start emg\r\n");
//	return HAL_ADC_Start_DMA(EMG_ADC, emg_buffer, EMG_READ_LENGTH);
	return HAL_ADC_Start_DMA(EMG_ADC, (uint32_t*)adctest, 1);
}

HAL_StatusTypeDef emg_stop_read(void){

	return HAL_ADC_Stop_DMA(EMG_ADC);
}

HAL_StatusTypeDef emg_peak_detection(){

	uint16_t ADC_BLOCKSIZE_startIndex=0, ADC_BLOCKSIZE_endIndex=0;

	if (inputBuffer_position == HALF_BLOCK){
		ADC_BLOCKSIZE_startIndex = 0;
		ADC_BLOCKSIZE_endIndex = EMG_READ_LENGTH/2;
	}
	else if(inputBuffer_position == FULL_BLOCK){
		ADC_BLOCKSIZE_startIndex = EMG_READ_LENGTH/2;
		ADC_BLOCKSIZE_endIndex = EMG_READ_LENGTH;
	}

	for(int i = ADC_BLOCKSIZE_startIndex; i < ADC_BLOCKSIZE_endIndex; i++){
//		printf("%i\r\n",emg_buffer[i]);
		if(emg_buffer[i] > detectionThreshold && toggleCounter > toggleThreshold){
			printf("emg peak\r\n%i\r\n",i);
			emg_peak = 1;
			toggleCounter = 0;
		}

		toggleCounter++;
	}


	return HAL_OK;
}

