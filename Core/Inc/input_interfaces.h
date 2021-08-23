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

uint8_t ii_voice_IDs[II_MAX_VOICES];

uint8_t II_Display_Voices(void);

#endif /* INC_INPUT_INTERFACES_H_ */
