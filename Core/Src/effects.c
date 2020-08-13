/*
 * effects.c
 *
 *  Created on: 12.08.2020
 *      Author: Marc Bielen
 */

#include "effects.h"

void tanh_Distortion_Process(double distortion_gain, uint32_t end) {
	//	output = tanh(gain * input)
	//	But any function like this which maps an unbounded input signal to an output in the range [-1,1] will produce some sort of saturation/distortion. To name a few others:
	//	output = mod(gain*input+1,2)-1
	//	output = abs(mod(2*gain*input+2,4)-2)-1
	//	output = sin(gain*input)
	//	output = input * input * input;

	for(int i=0; i<end; i++) {
		calculate_vector1[i] = tanh(distortion_gain * calculate_vector1[i]);
	}
}

void Tremolo() {
	Signal_Synthesis_LFO(&tremollo);	// calculates new LFO value and saves it into effects_LFO
	// ... tremolo effect
}


void Tremolo_Process(double fsignal, double LFO_Depth, double LFO_Rate, uint32_t end,  UART_HandleTypeDef huart) {

	char uart_buffer[32];

	float lfo[end];

	/* Assume first element as maximum and minimum */
	float max = calculate_vector1[0];
	float min = calculate_vector1[0];

	/*for(int i=0; i<end; i++) {
		lfo[i] = (1 + LFO_Depth*sin( i * 2*M_PI*LFO_Rate/96000 ));
	}

	// check if LFO frequency lower than F_MIN
	if(LFO_Rate < 5) {

		LFO_Rate = round(LFO_Rate);

		for(int i=0; i<end; i+=LFO_Rate*(5/LFO_Rate)) {
			if(LFO_Rate == 1) {
				lfo[i]   = lfo[i];
				lfo[i+1] = lfo[i];
				lfo[i+2] = lfo[i];
				lfo[i+3] = lfo[i];
				lfo[i+4] = lfo[i];
			}
		}
	}*/

	for(int i=0; i<end; i++) {

		//(1 + LFO_Depth*sin( i * 2*M_PI*LFO_Rate/96000 ))
		//calculate_vector[i] = lfo[i] * calculate_vector[i];
		//calculate_vector[i] = lfo[i];
		calculate_vector1[i] =  (1 + LFO_Depth*sin( i * 2*M_PI*LFO_Rate/96000 ));

		// calculate maximum and minimum element in calculate_vector
		// If current element is greater than max
		if(calculate_vector1[i] > max) {
			max = calculate_vector1[i];
		}
		// If current element is smaller than min
		if(calculate_vector1[i] < min) {
			min = calculate_vector1[i];
		}
	}

	// scale signal to -1:1
	for(int i=0; i<end; i++) {
		calculate_vector1[i] = (calculate_vector1[i] - min) * (1 - (-1)) / (max - min) + (-1);
	}

	int test=1;
	/*for(int i=0; i<end; i++) {	// UART Debugging
		sprintf(uart_buffer, "%f\n\r", calculate_vector[i]);
		HAL_UART_Transmit(&huart, (uint8_t*) uart_buffer, sizeof(uart_buffer), HAL_MAX_DELAY);
	}*/
}
