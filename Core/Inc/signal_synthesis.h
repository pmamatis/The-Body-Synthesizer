/**
  ******************************************************************************
  * @file    SignalErzeugung.c
  * @author  Paul Mamatis
  * @date 	27 Apr 2020
  * @brief	Funktionsgenerator für HAL-Libary auf Nucleo-144 F4.....
  *
  *         Diese H-Datei beinhaltet die wichtige voreinstellungen zur Signalerzeugung von 1Hz bis 8000Hz.
  *
  *@todo SIgnaladdierung testen, bzw fehler berechnen
  *
  *
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



//defines
/**@brief number of support points for the output vector*/
#define SUPPORT_POINTS  32768

/**@brief maximale Amplitude der Signale in milli Volt*/
#define AMPLITUDE 	2000
/**@brief DAC wert für maximale Spannung(3,3V) */
#define DAC_MAX 	4095
 /** @brief 100mV */
#define OFFSET 		145
/**@brief 4096/3300 */
#define DAC_MAXVALUE_TO_AMPLITUDE_RATIO  1.24121212121212
/**@brief normiert die Stützsetellen auf 2*Pi */
#define normierung(stuetzstellen) 2*M_PI/stuetzstellen


/**@brief timer clock */
#define CLOCK 108000000
/**@brief counter period of the timer */
#define COUNTER_PERIOD 100
/**@brief frequency of SIgnal if just one  whole period is writen into the vector */
#define SAMPLE_FREQ CLOCK/(COUNTER_PERIOD*SUPPORT_POINTS)



/**@brief Signalarten zur eingabe in Funktionen*/
enum signal_kind{
	SIN = 0,
	SAWTOOTH,
	TRIANGLE,
	PWM,
};

/**@brief wird zur Signal addierung gebraucht*/
struct signal{
	unsigned int kind[10];
	double freq[10];
};

//Variables
/** @brief signal support point array*/
float calculate_vector[SUPPORT_POINTS];
float sigFreq_sampleFreq_ratio;
int lastIndex;


//Funktionen

HAL_StatusTypeDef Signal_Synthesis_Init(TIM_HandleTypeDef htim, DAC_HandleTypeDef hdac);
float Signal_Synthesis(uint8_t count, ...);
HAL_StatusTypeDef Output_Signal(DAC_HandleTypeDef hdac);
#endif /* INC_SIGNALERZEUGUNG_H_ */




#endif /* INC_SIGNAL_SYNTHESIS_H_ */
