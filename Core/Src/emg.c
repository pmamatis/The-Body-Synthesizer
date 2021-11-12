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
	emg_detectionThreshold = 250;
	emg_peak = 0;
	emg_toggleThreshold = 20;
	emg_toggleCounter = emg_toggleThreshold;

	// TODO: Werte durch Testen anpassen!! // Minimawerte ebenfalls einfügen!
	emg_maxDetectionThreshold = 500;
	emg_maxToggleThreshold = 50;

	return HAL_OK;
}

/**ECG init
 * need to be called after emg_init()
 */
HAL_StatusTypeDef ecg_init(void){


	ecg_detectionThreshold = 250;
	ecg_peaks = 0;
	ecg_toggleThreshold = 20;
	ecg_toggleCounter = ecg_toggleThreshold;
	ecg_measInt = EMG_SR *4;
	// TODO: Werte durch Testen anpassen!! // Minimalwerte ebenfalls einfügen!
	ecg_maxDetectionThreshold = 500;
	ecg_maxToggleThreshold = 50;

	return HAL_OK;
}

HAL_StatusTypeDef emg_start_read(void){

	SetTimerSettings(EMG_TIM, EMG_SR);
	HAL_TIM_Base_Start(EMG_TIM);
	printf("start emg\r\n");
	return HAL_ADC_Start_DMA(EMG_ADC, emg_buffer, EMG_READ_LENGTH);
//	return HAL_ADC_Start_DMA(EMG_ADC, (uint32_t*)adctest, 1);
}

HAL_StatusTypeDef emg_stop_read(void){

	return HAL_ADC_Stop_DMA(EMG_ADC);
}

HAL_StatusTypeDef emg_peak_detection(){

	uint16_t ADC_BLOCKSIZE_startIndex=0, ADC_BLOCKSIZE_endIndex=0;

	if (inputBuffer_position == HALF_BLOCK){
		ADC_BLOCKSIZE_startIndex =1+ 0; //+1 to get the second ADC Channel (AC of emg/ecg)
		ADC_BLOCKSIZE_endIndex = EMG_READ_LENGTH/2;
	}
	else if(inputBuffer_position == FULL_BLOCK){
		ADC_BLOCKSIZE_startIndex =1+ EMG_READ_LENGTH/2;
		ADC_BLOCKSIZE_endIndex = EMG_READ_LENGTH;
	}

	for(int i = ADC_BLOCKSIZE_startIndex; i < ADC_BLOCKSIZE_endIndex; i+=2){
//		printf("%i\r\n",emg_buffer[i]);
		if(emg_buffer[i] > emg_detectionThreshold && emg_toggleCounter > emg_toggleThreshold){
			printf("emg peak\r\n%i\r\n",i);
			emg_peak = 1;
			emg_toggleCounter = 0;
		}

		emg_toggleCounter++;
	}


	return HAL_OK;
}

float ecg_heartrate(){

	uint16_t ADC_BLOCKSIZE_startIndex=0, ADC_BLOCKSIZE_endIndex=0;

	if (inputBuffer_position == HALF_BLOCK){
		ADC_BLOCKSIZE_startIndex = 0; //+0 to get the first ADC Channel (DC of emg/ecg)
		ADC_BLOCKSIZE_endIndex = EMG_READ_LENGTH/2;
	}
	else if(inputBuffer_position == FULL_BLOCK){
		ADC_BLOCKSIZE_startIndex = EMG_READ_LENGTH/2;
		ADC_BLOCKSIZE_endIndex = EMG_READ_LENGTH;
	}

	for(int i = ADC_BLOCKSIZE_startIndex; i < ADC_BLOCKSIZE_endIndex; i+=2){
//		printf("%i\r\n",emg_buffer[i]);
		if(emg_buffer[i] > ecg_detectionThreshold && ecg_toggleCounter > ecg_toggleThreshold){
			printf("emg peak\r\n%i\r\n",i);
			ecg_peaks += 1;
			ecg_toggleCounter = 0;
		}
		if (ecg_measInt == ecg_intCount){
			heartrate = (60/ecg_measInt)*ecg_peaks; //bpm
			ecg_peaks = 0;
			ecg_intCount = 0;
			if (Display.realtimeBPM_ONOFF){
				BPM = heartrate;
			}

		}
		ecg_toggleCounter++;
		ecg_intCount++;
	}


	return -1;
}
