/**
 * @file emg.c
 * @author Paul Mamatis
 * @brief emg/ecg processing
 * @version 0.1
 * @date May 23, 2021
 * 
 * @copyright Copyright (c) 2022
 * 
 */
 
 


#include "emg.h"

/** @brief EMG Init*/
HAL_StatusTypeDef emg_init(ADC_HandleTypeDef *hadc, TIM_HandleTypeDef *htim){

	EMG_ADC = hadc;
	EMG_TIM = htim;
	emg_detectionThreshold = 2500;
	emg_peak = 0;
	emg_toggleThreshold = 50;
	emg_toggleCounter = emg_toggleThreshold;
	emg_toggled = 0;
	emg_maxDetectionThreshold = 2850;
	emg_maxToggleThreshold = EMG_SR/5;

	return HAL_OK;
}

/** @brief ECG init
 *  @note need to be called after emg_init()
 */
HAL_StatusTypeDef ecg_init(void){

	heartrate = 0;

	ecg_detectionThreshold = 2500;
	ecg_peaks = 0;
	ecg_toggled = false;
	ecg_peak = false;
	ecg_toggleThreshold = EMG_SR/10;
	ecg_toggleCounter = ecg_toggleThreshold;
	ecg_measInt = EMG_SR * EMG_MI;
	ecg_intCount = 0;
	ecg_maxDetectionThreshold = 2850;
	ecg_maxToggleThreshold = EMG_SR/5;

	return HAL_OK;
}
/** @brief start all necessary peripherals for the EMG/ECG */
HAL_StatusTypeDef emg_start_read(void){

	SetTimerSettings(EMG_TIM, EMG_SR);
	HAL_TIM_Base_Start(EMG_TIM);
	printf("start emg\r\n");
	return HAL_ADC_Start_DMA(EMG_ADC, emg_buffer, EMG_READ_LENGTH);
}

/** @brief Only stops the ADC reading of the connected EMG/ECG board */
HAL_StatusTypeDef emg_stop_read(void){
	return HAL_ADC_Stop_DMA(EMG_ADC);
}

/** @brief detects an EMG peak and sets flags for further processing
 *  @note needs to be called in an ADC interrupt*/
HAL_StatusTypeDef emg_peak_detection(void){

	uint16_t ADC_BLOCKSIZE_startIndex=0, ADC_BLOCKSIZE_endIndex=0;

	//decide which buffer half
	if(inputBuffer_position == HALF_BLOCK) {
		ADC_BLOCKSIZE_startIndex = 0;
		ADC_BLOCKSIZE_endIndex = EMG_READ_LENGTH/2;
	}
	else if(inputBuffer_position == FULL_BLOCK) {
		ADC_BLOCKSIZE_startIndex = EMG_READ_LENGTH/2;
		ADC_BLOCKSIZE_endIndex = EMG_READ_LENGTH;
	}

	//peak detection
	for(int i = ADC_BLOCKSIZE_startIndex; i < ADC_BLOCKSIZE_endIndex; i+=2){
		if(emg_buffer[i] > emg_detectionThreshold && emg_toggleCounter > emg_toggleThreshold){
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

	//sample playing controlled by EMG
	if(Display.PlaySingleSample_ONOFF == true && emg_peak == 1) {

		play_single_sample_flag = true;
		emg_peak = 0;
	}

	return HAL_OK;
}

/** @brief detect heartrate and change the Drumcoputer BPM in realtime*/
void ecg_heartrate(void){

	uint16_t ADC_BLOCKSIZE_startIndex=0, ADC_BLOCKSIZE_endIndex=0;

	//detect buffer half
	if(inputBuffer_position == HALF_BLOCK) {
		ADC_BLOCKSIZE_startIndex = 0;
		ADC_BLOCKSIZE_endIndex = EMG_READ_LENGTH/2;
	}
	else if(inputBuffer_position == FULL_BLOCK) {
		ADC_BLOCKSIZE_startIndex = EMG_READ_LENGTH/2;
		ADC_BLOCKSIZE_endIndex = EMG_READ_LENGTH;
	}

	//detect ECG peak
	for(int i = ADC_BLOCKSIZE_startIndex; i < ADC_BLOCKSIZE_endIndex; i+=2){
		if(emg_buffer[i] > ecg_detectionThreshold && ecg_toggleCounter > ecg_toggleThreshold){
			ecg_peaks += 1;
			HAL_GPIO_WritePin(Blue_User_LED_GPIO_Port, Blue_User_LED_Pin,SET);
			ecg_toggleCounter = 0;
			ecg_peak = 1;
		}

		if(ecg_peak){
			ecg_peak = 0;
			ecg_toggled = 1;

		}
		//delay to avoid false peaks rigth after another peak
		if(ecg_toggleCounter > ecg_toggleThreshold && ecg_toggled == 1){
			ecg_toggled = 0;
		}

		//calculate heartrate when finishing a measurement Interval
		if (ecg_intCount == ecg_measInt){
			heartrate = ((float)(60/(EMG_MI))*ecg_peaks)/2;
			ecg_peaks = 0;
			ecg_intCount = 0;

			//direct transfer of the heartrate to Drumcomputer
			if(Display.Drumcomputer_BPMbyECG_ONOFF == true) {

				BPM = heartrate;
			}
		}

		//update drumcoputer-page and reset values drumcoputer when bpm changed, to avoid "plop"-noise
		if(abs(last_BPM-BPM) > 3) {

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

			Display.UpdateDisplay = true;
			last_BPM = BPM;
		}

		ecg_toggleCounter++;
		ecg_intCount++;
	}
}
