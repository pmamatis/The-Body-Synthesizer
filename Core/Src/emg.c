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

HAL_StatusTypeDef emg_init(){

	detectionThreshold = 220;
	peak = 0;
	toggled = 0;
	toggleCounter = 200;
	toggleThreshold = 200;

	return HAL_OK;
}

HAL_StatusTypeDef emg_start_read(){
	return HAL_ADC_Start_DMA(EMG_ADC, emg_buffer, EMG_READ_LENGTH);
}

HAL_StatusTypeDef emg_stop_read(){
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

		if(emg_buffer[i] > detectionThreshold && toggleCounter > toggleThreshold){

			peak = 1;
			toggleCounter = 0;
		}

		if(peak){

			HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_7);
			peak = 0;
			toggled = 1;
		}

		if(toggleCounter > toggleThreshold && toggled == 1){

			HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_7);
			toggled = 0;
		}

		toggleCounter = toggleCounter + 1;
	}
	//		if(emg_buffer[i] > detectionThreshold){
	//
	//			HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_7);
	//		}


	return HAL_OK;
}

