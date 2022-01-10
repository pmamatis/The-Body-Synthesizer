/**
 * @file input_interfaces.h
 * @author paul mamatis
 * @brief input device data processing, e.g. gyro emg ekc etc.
 * @version 0.1
 * @date 2022-01-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef INC_INPUT_INTERFACES_H_
#define INC_INPUT_INTERFACES_H_

#include "main.h"


/*********************************
 * @brief		Defines
 *********************************/
#define II_MAX_VOICES 3
#define II_SR 50
#define II_TREM_DEPTH_STEP_SIZE 20
// to ensure minimum frequency of 10 Hz -> especially for the drums (ratio II_MINIMUM_STEPCOUNTER to II_FILTER_CUTTOFF_STEP_SIZE = 440:1600)
// increase ratio to increase sensitivity
#define II_FILTER_CUTTOFF_STEP_SIZE 1600
#define II_MINIMUM_STEPCOUNTER 440 // formula used to determine this value: cutoff = exp(((float)drum_filter_step_counter/II_FILTER_CUTTOFF_STEP_SIZE) * log_mapping_F);
#define II_FILTER_CUTOFF_MIN 10

// Processing Delays
#define II_TREM_RATE_DELAY II_SR/4
#define II_TREM_DEPTH_DELAY II_SR/4



/*********************************
 * @brief	Variables
 *********************************/

/** value for Frequency as ln*/
double log_mapping_F;

/** actual step of the filter cuttoff */
int16_t filter_step_counter[5];
int16_t drum_filter_step_counter;

/** Flag to detect gyromovement in general */
bool gyrochanged;

/**
 * 0: tremolo rate
 * 1: tremolo depth
 */
uint32_t gyro_delay_counter[2];

bool emg_triggerd_flag;

/*********************************
 * @brief	Functions
 *********************************/
void II_init();
void II_startInterface(TIM_HandleTypeDef* htim);
void II_raiseNote(uint8_t ID);
void II_decreaseNote(uint8_t ID);

uint8_t II_Display_Voices(void);
uint8_t II_Display_Effects(void);

#endif /* INC_INPUT_INTERFACES_H_ */
