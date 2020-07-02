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
/**@brief Maximum of SIgnals which can be played at the same time */
#define MAX_SIGNAL_KOMBINATION 10

/**@brief struct to store signals*/
struct signal{
	unsigned int kind[MAX_SIGNAL_KOMBINATION];
	double freq[MAX_SIGNAL_KOMBINATION];
	uint8_t freqIndex[MAX_SIGNAL_KOMBINATION];
	uint32_t current_LUT_Index[MAX_SIGNAL_KOMBINATION];

};
enum singnal_synthesis_enum{
	note_key = 0,
	mixed
};
/**@brief Signal kinds*/
enum signal_kind_enum{
	SIN = 0,
	SAWTOOTH,
	TRIANGLE,
	PWM,
};





//functions
HAL_StatusTypeDef Signal_Synthesis_Init(TIM_HandleTypeDef htim, DAC_HandleTypeDef hdac);
void Signal_Synthesis(uint8_t count,uint8_t signal_composition,...);
HAL_StatusTypeDef Output_Signal(DAC_HandleTypeDef hdac, uint8_t channel);
//void TEST(DAC_HandleTypeDef hdac);


#endif /* INC_SIGNALERZEUGUNG_H_ */




#endif /* INC_SIGNAL_SYNTHESIS_H_ */
