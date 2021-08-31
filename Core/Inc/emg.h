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
//#define EMG_SR 100 //Hz

/* Variables */
ADC_HandleTypeDef* EMG_ADC;
uint32_t emg_buffer[EMG_READ_LENGTH];

uint32_t detectionThreshold;
uint32_t peak;
uint32_t toggled;
uint32_t toggleCounter;
uint32_t toggleThreshold;

uint32_t halfcounter;
uint32_t fullcounter;

/* Funktions */
//void emg_init(ADC_HandleTypeDef* ADC_Handler);
HAL_StatusTypeDef emg_init();
HAL_StatusTypeDef emg_start_read();
HAL_StatusTypeDef emg_stop_read();
HAL_StatusTypeDef emg_peak_detection();

#endif /* INC_EMG_H_ */
