/*
 * input_interfaces.h
 *
 *  Created on: Aug 15, 2021
 *      Author: Marc Bielen
 */

#ifndef INC_INPUT_INTERFACES_H_
#define INC_INPUT_INTERFACES_H_

#include "main.h"


#define II_MAX_VOICES 3
#define II_SR 50
#define II_TREM_DEPTH_STEP_SIZE 20
#define II_FILTER_CUTTOFF_STEP_SIZE 400

// Processing Delays
#define II_TREM_RATE_DELAY II_SR/4
#define II_TREM_DEPTH_DELAY II_SR/4


uint8_t ii_voice_IDs[II_MAX_VOICES];
//uint8_t II_raiseNote(uint8_t ID,uint8_t octave,char oldKey);

/** value for Frequency as ln*/
double log_mapping_F;
/** actual step of the filter cuttoff */
int16_t filter_step_counter[5];
int16_t drum_filter_step_counter;

bool gyrochanged;

/**
 * 0: tremolo rate
 * 1: tremolo depth
 */
uint32_t gyro_delay_counter[2];

bool emg_triggerd_flag;

void II_init();
void II_startInterface(TIM_HandleTypeDef* htim);
void II_raiseNote(uint8_t ID);
void II_decreaseNote(uint8_t ID);

// EMG trigger functions
void II_pVwEMG(void);
void II_pSwEMG(void);

uint8_t II_Display_Voices(void);
uint8_t II_Display_Effects(void);

#endif /* INC_INPUT_INTERFACES_H_ */
