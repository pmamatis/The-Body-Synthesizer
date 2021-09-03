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

uint32_t MasterClock = 0;
uint32_t drum_computer_counter = 0;

void Drum_Computer_Process();

#endif /* INC_DRUM_COMPUTER_H_ */
