/*
 * effects.h
 *
 *  Created on: 12.08.2020
 *      Author: Marc Bielen
 */

#ifndef INC_EFFECTS_H_
#define INC_EFFECTS_H_

#include "main.h"

void tanh_Distortion_Process(double distortion_gain, uint32_t end);
void Tremolo_Process(double fsignal, double LFO_Depth, double LFO_Rate, uint32_t end,  UART_HandleTypeDef huart);
void Tremolo();

#endif /* INC_EFFECTS_H_ */
