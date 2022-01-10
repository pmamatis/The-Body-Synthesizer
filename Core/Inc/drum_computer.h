/** TODO
 * @file drum_computer.h
 * @author Marc Bielen & max lehmer
 * @brief Drumcomputer 
 * @version 0.1
 * @date 05.08.2021
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#ifndef INC_DRUM_COMPUTER_H_
#define INC_DRUM_COMPUTER_H_

#include "main.h"
#include <stdint.h>
#include "wav_LUT.h"

/*********************************
 * @brief		Defines
 *********************************/

/** @brief Common Sample Length & Time Signature */
#define FourFour 8
#define ThreeFour 12



/*********************************
 * @brief	Variables
 *********************************/
/** @brief Tempo */
float BPM;
float BPM_MAX;
float last_BPM;
uint32_t MasterClock;

/** @brief Index */
uint32_t drum_index;

/** @brief Counter */
uint32_t counter_master;
uint32_t counter_DS1[FourFour];
uint32_t counter_DS2[FourFour];
uint32_t counter_DS3[FourFour];
uint32_t counter_DS4[FourFour];

/** @brief Flag drums */
uint32_t flag_DS1[FourFour];
uint32_t flag_DS2[FourFour];
uint32_t flag_DS3[FourFour];
uint32_t flag_DS4[FourFour];

/** @brief Timing positions drums */
bool timing_DS1[FourFour];
bool timing_DS2[FourFour];
bool timing_DS3[FourFour];
bool timing_DS4[FourFour];
uint32_t timing_position_in_samples[FourFour];

/** @brief Sound bins */
float DS1s;
float DS2s;
float DS3s;
float DS4s;
float PSSs;
float drums;
float drums_filtered;

bool timing_SN1[FourFour];
bool timing_SN2[FourFour];
bool timing_SN3[FourFour];
bool timing_SN4[FourFour];

/** @brief Frequency index sequencer */
uint16_t freq_index_SN1;
uint16_t freq_index_SN2;
uint16_t freq_index_SN3;
uint16_t freq_index_SN4;

/** @brief Current LUT index sequencer */
uint32_t current_LUT_index_SN1[FourFour];
uint32_t current_LUT_index_SN2[FourFour];
uint32_t current_LUT_index_SN3[FourFour];
uint32_t current_LUT_index_SN4[FourFour];

/** @brief Sound bins sequencer */
float SN1;
float SN2;
float SN3;
float SN4;

float SN1_temp;
float SN2_temp;
float SN3_temp;
float SN4_temp;

float sequencer;

/*********************************
 * @brief	Functions
 *********************************/
HAL_StatusTypeDef Drum_Computer_Init(void);
HAL_StatusTypeDef Drum_Computer_Reset(void);
HAL_StatusTypeDef Drum_Computer_Process(void);
HAL_StatusTypeDef Drum_Computer_CalcSample(void);
HAL_StatusTypeDef Sequencer_Reset(void);
HAL_StatusTypeDef Sequencer_ADSR_Init(struct adsr* env);

/** @brief Single Sample */
float single_sample;
uint32_t counter_single_sample;
bool play_single_sample_flag;
void PlaySingleSample(void);

#endif /* INC_DRUM_COMPUTER_H_ */
