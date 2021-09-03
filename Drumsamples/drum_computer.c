/*
 * drum_computer.c
 *
 *  Created on: 05.08.2021
 *      Author: Marc Bielen
 */

#include "drum_computer.h"

void Drum_Computer_Process() {

	float kick_output = 0;
	float closed_hh_output = 0;
	float* calculate_vector = 0;

	calculate_vector = calculate_vector2;

	//kick_output = kick_LUT[drum_computer_counter];
	closed_hh_output = closed_hh_LUT[drum_computer_counter];

	calculate_vector[drum_computer_counter] = kick_output + closed_hh_output;

	// Signal adjustment for the DAC
	*((uint32_t *)(&calculate_vector[drum_computer_counter] )) = (uint32_t)(((calculate_vector[drum_computer_counter]+1)/2) * 4095 + 145 ); // +1.5 fir middle of 0-3V3
	//*((uint32_t *)(&calculate_vector[drum_computer_counter] )) = (uint32_t)(((calculate_vector[drum_computer_counter]+1)/2) * maxValueDAC + OFFSET ); // +1.5 fir middle of 0-3V3

	drum_computer_counter++;
	//if(drum_computer_counter >= (sizeof(kick_LUT)/sizeof(kick_LUT[0]))) {
	if(drum_computer_counter >= 40000) {
		drum_computer_counter = 0;
	}
}
