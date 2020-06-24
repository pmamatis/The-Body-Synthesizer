/*
 * sinus_LUT.h
 *
 *  Created on: 19.06.2020
 *      Author: Paul Mamatis
 */

#ifndef INC_SINUS_LUT_H_
#define INC_SINUS_LUT_H_

const struct sinTable{
	uint16_t maxIndex[5];
	float sinTable100[960];
	float sinTable200[480];

};

float GetSin(float freq,uint16_t index);

#endif /* INC_SINUS_LUT_H_ */
