/*
 * effects.h
 *
 *  Created on: 12.08.2020
 *      Author: Marc Bielen
 */

#ifndef INC_EFFECTS_H_
#define INC_EFFECTS_H_

#include "main.h"

//Effects
enum effects_using_LFO{
	TREMOLLO = 0,
};

struct effects_LFO{
	uint8_t name;
	uint32_t index;
	uint8_t quarter;
	float lfo_frequency;
	uint32_t lfo_blocksizecounter;
	float lfo_depth;
};

struct effects_distortion{
	float distortion_gain;
};

void tanh_Distortion_Process(double distortion_gain, uint32_t end);	// not in use
void Tremolo_Process(double fsignal, double LFO_Depth, double LFO_Rate, uint32_t end,  UART_HandleTypeDef huart);	// not in use
float tanh_Distortion(double distortion_gain, float calculate_vector);	// not in use

float Tremolo(struct effects_LFO* effect, float LFO_Depth, float calculate_vector);
float HardClippingDistortion(struct effects_distortion* effect, float Distortion_Gain, float calculate_vector);

#endif /* INC_EFFECTS_H_ */
