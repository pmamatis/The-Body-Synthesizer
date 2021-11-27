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
	//	emg_detectionThreshold = 250;
	emg_detectionThreshold = 2500;
	emg_peak = 0;
	emg_toggleThreshold = 50;
	emg_toggleCounter = emg_toggleThreshold;
	emg_toggled = 0;
	// TODO: Werte durch Testen anpassen!! // Minimawerte ebenfalls einfügen!
	//	emg_maxDetectionThreshold = 2500;
	emg_maxDetectionThreshold = 2850;
	emg_maxToggleThreshold = EMG_SR/5;

	return HAL_OK;
}

/**ECG init
 * need to be called after emg_init()
 */
HAL_StatusTypeDef ecg_init(void){

	heartrate = 0;

	//	ecg_detectionThreshold = 250;
	ecg_detectionThreshold = 2500;
	ecg_peaks = 0;
	ecg_toggled = false;
	ecg_peak = false;
	ecg_toggleThreshold = EMG_SR/10;
	ecg_toggleCounter = ecg_toggleThreshold;
	ecg_measInt = EMG_SR * EMG_MI;
	ecg_intCount = 0;

	// TODO: Werte durch Testen anpassen!! // Minimalwerte ebenfalls einfügen!
	//	ecg_maxDetectionThreshold = 2500;
	ecg_maxDetectionThreshold = 2850;
	ecg_maxToggleThreshold = EMG_SR/5;

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

HAL_StatusTypeDef emg_peak_detection(void){

	uint16_t ADC_BLOCKSIZE_startIndex=0, ADC_BLOCKSIZE_endIndex=0;

	if(inputBuffer_position == HALF_BLOCK) {
		//		ADC_BLOCKSIZE_startIndex = 1;	// +1 to get the second ADC Channel (AC of emg/ecg)
		ADC_BLOCKSIZE_startIndex = 0;	// +1 to get the second ADC Channel (AC of emg/ecg)
		ADC_BLOCKSIZE_endIndex = EMG_READ_LENGTH/2;
	}
	else if(inputBuffer_position == FULL_BLOCK) {
		ADC_BLOCKSIZE_startIndex = EMG_READ_LENGTH/2;
		ADC_BLOCKSIZE_endIndex = EMG_READ_LENGTH;
	}

	for(int i = ADC_BLOCKSIZE_startIndex; i < ADC_BLOCKSIZE_endIndex; i+=2){
		//				printf("%i\r\n",emg_buffer[i]);
		if(emg_buffer[i] > emg_detectionThreshold && emg_toggleCounter > emg_toggleThreshold){
			//			printf("emg peak\r\n");
			emg_peak = 1;
			emg_toggleCounter = 0;
			HAL_GPIO_WritePin(Red_User_LED_GPIO_Port, Red_User_LED_Pin,SET);
			emg_toggled = 1;
		}
		if(emg_toggleCounter > emg_toggleThreshold && emg_toggled == 1){
			HAL_GPIO_WritePin(Red_User_LED_GPIO_Port, Red_User_LED_Pin,RESET);
			emg_toggled = 0;
		}

		emg_toggleCounter++;
	}

	if(Display.PlaySingleSample_ONOFF == true && emg_peak == 1) {

		play_single_sample_flag = true;
		emg_peak = 0;
	}

	return HAL_OK;
}

void ecg_heartrate(void){

	uint16_t ADC_BLOCKSIZE_startIndex=0, ADC_BLOCKSIZE_endIndex=0;

	if(inputBuffer_position == HALF_BLOCK) {
		ADC_BLOCKSIZE_startIndex = 0;	// +0 to get the first ADC Channel (DC of emg/ecg)
		ADC_BLOCKSIZE_endIndex = EMG_READ_LENGTH/2;
	}
	else if(inputBuffer_position == FULL_BLOCK) {
		ADC_BLOCKSIZE_startIndex = EMG_READ_LENGTH/2;
		ADC_BLOCKSIZE_endIndex = EMG_READ_LENGTH;
	}

	for(int i = ADC_BLOCKSIZE_startIndex; i < ADC_BLOCKSIZE_endIndex; i+=2){
		//			printf("1:  %u\r\n",emg_buffer[i-1]);
		//			printf("2:  %u\r\n",emg_buffer[i]);
		if(emg_buffer[i] > ecg_detectionThreshold && ecg_toggleCounter > ecg_toggleThreshold){

			ecg_peaks += 1;
			//			printf("ecg peak\r\n");
			//			printf("1:  %u\r\n",emg_buffer[i-1]);
			//			printf("2:  %u\r\n",emg_buffer[i]);
			HAL_GPIO_WritePin(Blue_User_LED_GPIO_Port, Blue_User_LED_Pin,SET);
			ecg_toggleCounter = 0;
			ecg_peak = 1;
		}

		if(ecg_peak){
			//			HAL_GPIO_TogglePin(Red_User_LED_GPIO_Port, Red_User_LED_Pin);
			ecg_peak = 0;
			ecg_toggled = 1;

		}

		if(ecg_toggleCounter > ecg_toggleThreshold && ecg_toggled == 1){
			HAL_GPIO_WritePin(Blue_User_LED_GPIO_Port, Blue_User_LED_Pin,RESET);
			ecg_toggled = 0;
		}

		//		printf("%u == %u\r\n", ecg_measInt ,ecg_intCount);

		if (ecg_intCount == ecg_measInt){
			heartrate = ((float)(60/(EMG_MI))*ecg_peaks)/2; //bpm
			ecg_peaks = 0;
			ecg_intCount = 0;

			if(Display.Drumcomputer_BPMbyECG_ONOFF == true) {

				BPM = heartrate;
				//				printf("BPM: %f\r\n", BPM);
			}
		}
		if(abs(last_BPM-BPM) > 3) {
			//		if(last_BPM != BPM) {

			for(int i=0; i<FourFour; i++) {

				// INIT: Counter
				counter_DS1[i] = 0;
				counter_DS2[i] = 0;
				counter_DS3[i] = 0;
				counter_DS4[i] = 0;

				drum_index = 0;
				counter_master = 0;

				// RESET: Drum sound bins
				DS1s = 0;
				DS2s = 0;
				DS3s = 0;
				DS4s = 0;

				drums = 0;

				timing_position_in_samples[i] = (FourFour / 4 ) * (i + 1) * (MasterClock / FourFour) * (60 / BPM);
			}

			sprintf(Display.value_str_drumcomputer[8], "%.f", BPM);

			// ACHTUNG ACHTUNG, SEITENZAHL USW. BEACHTEN!!!
			// BPM set by ECG and display only updated with new BPM value on drumcomputer settings page
			if(Display.pagePosition == 3 && Display.currentDrumcomputer > 0) {
				Paint_DrawFilledRectangle(&paint, Display.value_start_x_position-50, CASE2, Display.value_end_x_position, CASE2+VALUE_ROW_LENGTH, UNCOLORED);
				Paint_DrawStringAt(&paint, Display.value_start_x_position-50, CASE2, Display.value_str_drumcomputer[8], &Font12, COLORED);
			}
			//			last_BPM = BPM;
			Display.UpdateDisplay = true;
			last_BPM = BPM;
		}

		ecg_toggleCounter++;
		ecg_intCount++;
	}
}
