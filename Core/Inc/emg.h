/**
 * @file emg.h
 * @author paul mamatis
 * @brief emg and ecg 
 * @version 0.1
 * @date 2022-01-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef INC_EMG_H_
#define INC_EMG_H_

#include "main.h"

/*********************************
 * @brief		Defines
 *********************************/
#define EMG_READ_LENGTH 20
#define EMG_SR 5000
#define EMG_MI 1 // Measuring Intervall in seconds


/*********************************
 * @brief	Variables
 *********************************/
ADC_HandleTypeDef* EMG_ADC;
TIM_HandleTypeDef* EMG_TIM;

// buffer for ADC which senses the ecg and emg signal
uint32_t emg_buffer[EMG_READ_LENGTH];

// EMG variables
uint32_t emg_detectionThreshold;
uint8_t  emg_peak;
uint32_t emg_toggleCounter;
uint32_t emg_toggleThreshold;
uint32_t emg_maxDetectionThreshold;
uint32_t emg_maxToggleThreshold;
bool emg_toggled;

// ECG variables
uint32_t ecg_measInt; // Measuring Intervall in seconds
uint32_t ecg_detectionThreshold;
uint8_t  ecg_peaks;
uint32_t ecg_toggleCounter;
uint32_t ecg_toggleThreshold;
uint32_t ecg_maxDetectionThreshold;
uint32_t ecg_maxToggleThreshold;
uint32_t ecg_intCount; // Interval Counter
bool ecg_peak;
bool ecg_toggled;
float heartrate;

uint8_t inputBuffer_position;

/*********************************
 * @brief	Functions
 *********************************/
HAL_StatusTypeDef emg_init(ADC_HandleTypeDef *hadc, TIM_HandleTypeDef *htim);
HAL_StatusTypeDef ecg_init(void);
HAL_StatusTypeDef emg_start_read(void);
HAL_StatusTypeDef emg_stop_read(void);
HAL_StatusTypeDef emg_peak_detection(void);
void ecg_heartrate(void);

#endif /* INC_EMG_H_ */
