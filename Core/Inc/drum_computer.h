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
#define sample_length 40000
#define FourFour 16
#define ThreeFour 12

// Tempo
float BPM;
uint32_t MasterClock;

// Counter
uint32_t counter_master;
uint32_t counter_kick [FourFour];
uint32_t counter_hihat[FourFour];
uint32_t counter_clap [FourFour];

// Timing positions
uint32_t timing_kick [FourFour];
uint32_t timing_hihat[FourFour];
uint32_t timing_clap [FourFour];

// Methods
HAL_StatusTypeDef Drum_Computer_Init();
HAL_StatusTypeDef Drum_Computer_Process();

#endif /* INC_DRUM_COMPUTER_H_ */
