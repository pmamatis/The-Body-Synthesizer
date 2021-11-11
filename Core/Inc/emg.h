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
#define EMG_READ_LENGTH 10//8192/4
//#define EMG_SR 500 //Hz
#define EMG_SR 20

/* Variables */
ADC_HandleTypeDef* EMG_ADC;
TIM_HandleTypeDef* EMG_TIM;
uint32_t emg_buffer[EMG_READ_LENGTH];

uint32_t adctest;

uint32_t detectionThreshold;
uint8_t emg_peak;
uint32_t toggled;
uint32_t toggleCounter;
uint32_t toggleThreshold;
uint32_t maxDetectionThreshold;
uint32_t maxToggleThreshold;

uint32_t halfcounter;
uint32_t fullcounter;
uint8_t inputBuffer_position;
/* Funktions */
//void emg_init(ADC_HandleTypeDef* ADC_Handler);

HAL_StatusTypeDef emg_init(ADC_HandleTypeDef *hadc, TIM_HandleTypeDef *htim);
HAL_StatusTypeDef emg_start_read();
HAL_StatusTypeDef emg_stop_read();
HAL_StatusTypeDef emg_peak_detection();

#endif /* INC_EMG_H_ */
