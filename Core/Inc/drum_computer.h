/*
 * drum_computer.h
 *
 *  Created on: 05.08.2021
 *      Author: Marc Bielen
 */

#ifndef INC_DRUM_COMPUTER_H_
#define INC_DRUM_COMPUTER_H_

#include "main.h"
#include <stdint.h>
#include "wav_LUT.h"

// Common Sample Length & Time Signature
#define FourFour 8
#define ThreeFour 12

// Tempo
float BPM;
uint32_t MasterClock;

// Index
uint32_t drum_index;

// Counter
uint32_t counter_master;
uint32_t counter_DS1[FourFour];
uint32_t counter_DS2[FourFour];
uint32_t counter_DS3[FourFour];
uint32_t counter_DS4[FourFour];

// Oversampling
uint32_t OS_DS1[FourFour];
uint32_t OS_DS2[FourFour];
uint32_t OS_DS3[FourFour];
uint32_t OS_DS4[FourFour];

// Flag
uint32_t flag_DS1[FourFour];
uint32_t flag_DS2[FourFour];
uint32_t flag_DS3[FourFour];
uint32_t flag_DS4[FourFour];

// Timing positions
uint32_t timing_DS1[FourFour];
uint32_t timing_DS2[FourFour];
uint32_t timing_DS3[FourFour];
uint32_t timing_DS4[FourFour];
uint32_t timing_position_in_samples[FourFour];

// Sound bins
float DS1s;
float DS2s;
float DS3s;
float DS4s;
float drums;

// Methods
HAL_StatusTypeDef Drum_Computer_Init(UART_HandleTypeDef *huart);
HAL_StatusTypeDef Drum_Computer_Process();
HAL_StatusTypeDef Drum_Computer_CalcSample();

#endif /* INC_DRUM_COMPUTER_H_ */
