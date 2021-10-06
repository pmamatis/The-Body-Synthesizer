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
//#include "sd_card.h"

//typedef enum {
//	CLAP_909 = '909_Clap.txt',
//	CLOSED_HH_909 = '909_ClosedHiHat.txt'
////	HITOM_909,
////	KICK_909,
////	LOWTOM_909,
////	MIDTOM_909,
////	OPEN_HH_909,
////	RIMSHOT_909
//} sample_names;

// Common Sample Length & Time Signature
#define FourFour 8
#define ThreeFour 12

// Tempo
float BPM;
float BPM_MAX;
float last_BPM;
uint32_t MasterClock;

// Index
uint32_t drum_index;

// Counter
uint32_t counter_master;
uint32_t counter_DS1[FourFour];
uint32_t counter_DS2[FourFour];
uint32_t counter_DS3[FourFour];
uint32_t counter_DS4[FourFour];

// Flag drums
uint32_t flag_DS1[FourFour];
uint32_t flag_DS2[FourFour];
uint32_t flag_DS3[FourFour];
uint32_t flag_DS4[FourFour];

// Timing positions drums
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
float drums_filtered;

// Sequencer mode ON / OFF control
bool sequencer_state;

// Timing positions sequencer
uint32_t timing_SN1[FourFour];
uint32_t timing_SN2[FourFour];
uint32_t timing_SN3[FourFour];
uint32_t timing_SN4[FourFour];

// Frequency index sequencer
uint16_t freq_index_SN1;
uint16_t freq_index_SN2;
uint16_t freq_index_SN3;
uint16_t freq_index_SN4;

// Current LUT index sequencer
uint32_t current_LUT_index_SN1[FourFour];
uint32_t current_LUT_index_SN2[FourFour];
uint32_t current_LUT_index_SN3[FourFour];
uint32_t current_LUT_index_SN4[FourFour];

// Sound bins sequencer
float SN1;
float SN2;
float SN3;
float SN4;

float SN1_temp;
float SN2_temp;
float SN3_temp;
float SN4_temp;

float sequencer;

// Methods
HAL_StatusTypeDef Drum_Computer_Init(void);
HAL_StatusTypeDef Drum_Computer_Process();
HAL_StatusTypeDef Drum_Computer_CalcSample();
HAL_StatusTypeDef Drum_Computer_CalcSample_Reverse();
HAL_StatusTypeDef Sequencer_ADSR_Init(struct adsr* env);

// Single Sample
float single_sample;
uint32_t counter_single_sample;
bool play_single_sample_flag;
void PlaySingleSample(void);

#endif /* INC_DRUM_COMPUTER_H_ */
