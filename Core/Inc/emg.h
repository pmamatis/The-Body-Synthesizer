/*
 * emg.h
 *
 *  Created on: August 31, 2021
 *      Author: Max
 */

#ifndef INC_EMG_H_
#define INC_EMG_H_

#include "main.h"

/* defines */
#define EMG_READ_LENGTH 20//8192/4
//#define EMG_SR 500 // in Hz
#define EMG_SR 5000
//#define EMG_MI 2 // Measuring Intervall in seconds
#define EMG_MI 1 // Measuring Intervall in seconds
/* Variables */
ADC_HandleTypeDef* EMG_ADC;
TIM_HandleTypeDef* EMG_TIM;

//buffer for ADC which senses the ecg and emg signal
uint32_t emg_buffer[EMG_READ_LENGTH];

uint32_t adctest;

//EMG varaibles
uint32_t emg_detectionThreshold;
uint8_t  emg_peak;
uint32_t emg_toggleCounter;
uint32_t emg_toggleThreshold;
uint32_t emg_maxDetectionThreshold;
uint32_t emg_maxToggleThreshold;
bool emg_toggled;
//ECG varaibles
uint32_t ecg_measInt; //measurement Interval
uint32_t ecg_detectionThreshold;
uint8_t  ecg_peaks;
uint32_t ecg_toggleCounter;
uint32_t ecg_toggleThreshold;
uint32_t ecg_maxDetectionThreshold;
uint32_t ecg_maxToggleThreshold;
uint32_t ecg_intCount; //Interval Counter
bool ecg_peak;
bool ecg_toggled;
float heartrate;


uint32_t halfcounter;
uint32_t fullcounter;
uint8_t inputBuffer_position;
/* Funktions */
//void emg_init(ADC_HandleTypeDef* ADC_Handler);

HAL_StatusTypeDef emg_init(ADC_HandleTypeDef *hadc, TIM_HandleTypeDef *htim);
HAL_StatusTypeDef ecg_init(void);
HAL_StatusTypeDef emg_start_read(void);
HAL_StatusTypeDef emg_stop_read(void);
HAL_StatusTypeDef emg_peak_detection(void);
void ecg_heartrate();

#endif /* INC_EMG_H_ */
