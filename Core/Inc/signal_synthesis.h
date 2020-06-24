/**
  ******************************************************************************
  * @file    signal_sythesis.c
  * @author  Paul Mamatis
  * @date 	27 Apr 2020
  * @brief	Signal sythesis for HAL-Libary on Nucleo-144 F4.....
  *
  *@todo implement 	SAWTOOTH, TRIANGLE, PWM in signal_sythesis function
*/

#ifndef INC_SIGNAL_SYNTHESIS_H_
#define INC_SIGNAL_SYNTHESIS_H_








#ifndef INC_SIGNALERZEUGUNG_H_
#define INC_SIGNALERZEUGUNG_H_

#include <math.h>
#include "main.h"
#include<stdio.h>
#include<stdlib.h>
#include <stdarg.h>






/**@brief maximal amplitude of output voltage in millivolts*/
#define AMPLITUDE 	2000
/**@brief digital DAC value for maximal output voltage (3,3V) */
#define DAC_MAX 	4095
 /** @brief digital value for 100mV */
#define OFFSET 		145
/**@brief 4096/3300 */
#define DAC_MAXVALUE_TO_AMPLITUDE_RATIO  1.24121212121212

/**@brief Signal kinds*/
enum signal_kind{
	SIN = 0,
	SAWTOOTH,
	TRIANGLE,
	PWM,
};

/**@brief struct to store signals*/
struct signal{
	unsigned int kind[10];
	double freq[10];
	uint32_t maxIndex[10];
};

//functions
HAL_StatusTypeDef Signal_Synthesis_Init(TIM_HandleTypeDef htim, DAC_HandleTypeDef hdac);
float Signal_Synthesis(uint8_t count, ...);
HAL_StatusTypeDef Output_Signal(DAC_HandleTypeDef hdac, uint8_t channel);
//void TEST(DAC_HandleTypeDef hdac);


#endif /* INC_SIGNALERZEUGUNG_H_ */




#endif /* INC_SIGNAL_SYNTHESIS_H_ */
